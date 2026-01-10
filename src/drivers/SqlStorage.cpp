#include "../../include/drivers/SqlStorage.h"
#include <stdexcept>
#include <format>

namespace Drivers {
    SqlStorage::SqlStorage(const std::string &path) {
        if (sqlite3_open_v2(path.c_str(), &m_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr)) {
            throw std::invalid_argument("Cannot open database to " + path);
        }

        createSchema();

        if (sqlite3_prepare_v2(m_db, "INSERT INTO EnvironmentalMetrics(timestamp, co2_ppm) VALUES (?, ?)", -1,
                               &m_insertEnvironmentalMetricsStmt, nullptr) != SQLITE_OK) {
            throw std::invalid_argument("Cannot create insert statement");
        }
        if (sqlite3_prepare_v2(m_db, "SELECT * FROM EnvironmentalMetrics WHERE timestamp > ? ORDER BY timestamp ASC",
                               -1,
                               &m_selectEnvironmentalMetricsStmt, nullptr) != SQLITE_OK) {
            throw std::invalid_argument("Cannot create select statement");
        }
    }

    SqlStorage::~SqlStorage() {
        sqlite3_finalize(m_insertEnvironmentalMetricsStmt);
        sqlite3_finalize(m_selectEnvironmentalMetricsStmt);
        sqlite3_close(m_db);
    }

    void SqlStorage::createSchema() const {
        const std::string sql = "CREATE TABLE IF NOT EXISTS EnvironmentalMetrics("
                "timestamp integer primary key,"
                "co2_ppm real"
                ")";
        char *errMsg = nullptr;
        if (sqlite3_exec(m_db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
            const std::string error = errMsg;
            sqlite3_free(errMsg);
            throw std::runtime_error("Could not create schema: " + error);
        }
    }

    void SqlStorage::addMeasurement(Domain::EnvironmentalMetric const metrics) const {
        sqlite3_bind_int(m_insertEnvironmentalMetricsStmt, 1, metrics.getUnixTimestamp());
        sqlite3_bind_double(m_insertEnvironmentalMetricsStmt, 2, metrics.co2Ppm);

        if (sqlite3_step(m_insertEnvironmentalMetricsStmt) != SQLITE_DONE) {
            throw std::exception{}; // TODO
        }
        sqlite3_reset(m_insertEnvironmentalMetricsStmt);
    }

    std::vector<Domain::EnvironmentalMetric> SqlStorage::getMetricsForLastHours(int const hours) const {
        std::vector<Domain::EnvironmentalMetric> metrics{};

        const auto cutoffTime = std::chrono::system_clock::now() - std::chrono::hours(hours);
        const auto cutoffSeconds = std::chrono::duration_cast<std::chrono::seconds>(
            cutoffTime.time_since_epoch()).count();

        sqlite3_bind_int64(m_selectEnvironmentalMetricsStmt, 1, cutoffSeconds);

        while (sqlite3_step(m_selectEnvironmentalMetricsStmt) == SQLITE_ROW) {
            auto timestamp = sqlite3_column_int64(m_selectEnvironmentalMetricsStmt, 0);
            auto co2 = static_cast<float>(sqlite3_column_double(m_selectEnvironmentalMetricsStmt, 1));

            auto timePoint = std::chrono::system_clock::time_point(std::chrono::seconds(timestamp));
            metrics.emplace_back(timePoint, co2, 0, 0);
        }
        sqlite3_reset(m_selectEnvironmentalMetricsStmt);
        return metrics;
    }

    sqlite3 *SqlStorage::getDB() const {
        return m_db;
    }
}
