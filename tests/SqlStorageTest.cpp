#include <gtest/gtest.h>

#include "../include/drivers/SqlStorage.h"

using std::chrono::system_clock;

static int setResultInt(void *data, int argc, char **argv, char **azColName) {
    if (data == nullptr) {
        return -1;
    }
    *static_cast<int *>(data) = atoi(argv[0]);
    return 0;
}

static int setResultFloat(void *data, int argc, char **argv, char **azColName) {
    if (data == nullptr) {
        return -1;
    }
    *static_cast<float *>(data) = atof(argv[0]);
    return 0;
}

static int setResultTimestamp(void *data, int argc, char **argv, char **azColName) {
    if (data == nullptr) {
        return -1;
    }
    *static_cast<system_clock::time_point *>(data) = system_clock::time_point(
        std::chrono::seconds(atoi(argv[0])));
    return 0;
}

TEST(SqlStorageTest, CanCreateSqlStorage) {
    EXPECT_NO_THROW(Drivers::SqlStorage{":memory:"});
}

TEST(SqlStorageTest, OnCreateSchemaIsCreate) {
    Drivers::SqlStorage sql_storage{":memory:"};
    const auto db = sql_storage.getDB();
    ASSERT_EQ(SQLITE_OK,
              sqlite3_exec(db, "SELECT name FROM sqlite_master WHERE type='table' AND name='EnvironmentalMetrics'",
                  nullptr, nullptr, nullptr));
}

TEST(SqlStorageTest, CanAddValuesToSqlDatabase) {
    Drivers::SqlStorage sql_storage{":memory:"};
    const auto db = sql_storage.getDB();
    const Domain::EnvironmentalMetric metrics{system_clock::now(), 200.1, 0, 0};
    ASSERT_NO_THROW(sql_storage.addMeasurement(metrics));
    int count = 0;
    ASSERT_EQ(SQLITE_OK,
              sqlite3_exec(db, "SELECT count(*) FROM EnvironmentalMetrics",
                  setResultInt, &count, nullptr));
    ASSERT_EQ(1, count);
    float database_co2 = 0;
    ASSERT_EQ(SQLITE_OK,
              sqlite3_exec(db, "SELECT co2_ppm FROM EnvironmentalMetrics",
                  setResultFloat, &database_co2, nullptr));
    ASSERT_EQ(metrics.co2Ppm, database_co2);
    system_clock::time_point time{};
    ASSERT_EQ(SQLITE_OK,
              sqlite3_exec(db, "SELECT timestamp FROM EnvironmentalMetrics",
                  setResultTimestamp, &time, nullptr));
    const auto diff = std::chrono::abs(metrics.timestamp - time);
    ASSERT_LE(diff, std::chrono::seconds(1));
}

TEST(SqlStorageTest, CanAddMultipleMetricPoints) {
    const auto oldTime = system_clock::now() - std::chrono::hours(36);
    const Drivers::SqlStorage sql_storage{":memory:"};
    const Domain::EnvironmentalMetric oldMetrics{oldTime, 200.1, 0, 0};
    EXPECT_NO_THROW(sql_storage.addMeasurement(oldMetrics));
    const Domain::EnvironmentalMetric interestingMetric{system_clock::now(), 1000.1, 0, 0};
    EXPECT_NO_THROW(sql_storage.addMeasurement(interestingMetric));
}

TEST(SqlStorageTest, ReturnsOnlyRecentData) {
    const auto oldTime = system_clock::now() - std::chrono::hours(36);
    const Drivers::SqlStorage sql_storage{":memory:"};
    const Domain::EnvironmentalMetric oldMetrics{oldTime, 200.1, 0, 0};
    EXPECT_NO_THROW(sql_storage.addMeasurement(oldMetrics));
    const Domain::EnvironmentalMetric interestingMetric{system_clock::now(), 1000.1, 0, 0};
    EXPECT_NO_THROW(sql_storage.addMeasurement(interestingMetric));

    const auto result = sql_storage.getMetricsForLastHours(24);
    ASSERT_EQ(1, result.size());
    EXPECT_NEAR(1000.1, result.at(0).co2Ppm, 0.3f);
}
