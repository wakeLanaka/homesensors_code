#ifndef MOCK_SQL_STORAGE_H_
#define MOCK_SQL_STORAGE_H_
#include "../../include/drivers/SqlStorage.h"
#include "gmock/gmock.h"


struct MockStorage : Drivers::IHistoryStorage {
    MOCK_METHOD(void, addMeasurement, (Domain::EnvironmentalMetric const), (const, override));
    MOCK_METHOD(std::vector<Domain::EnvironmentalMetric>, getMetricsForLastHours, (int const), (const, override));
};
#endif
