#ifndef AIRLOG_MOCKSERVICE_H
#define AIRLOG_MOCKSERVICE_H

#include "../../include/drivers/ISensor.h"
#include "../../include/drivers/SqlStorage.h"
#include "gmock/gmock.h"

namespace Domain {
    struct MockService : IHistoryService {
        MOCK_METHOD(void, processMeasurement, (Domain::EnvironmentalMetric), (const, override));
        MOCK_METHOD(std::vector<Domain::EnvironmentalMetric>, getMetricsForLastHours, (int), (const, override));
    };
}
#endif
