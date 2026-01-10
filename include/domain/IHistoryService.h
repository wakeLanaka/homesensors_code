#ifndef AIRLOG_IHISTORY_SERVICE_H
#define AIRLOG_IHISTORY_SERVICE_H

#include <vector>
#include "../drivers/IHistoryStorage.h"

namespace Domain {
    struct IHistoryService {
        virtual ~IHistoryService() = default;

        virtual void processMeasurement(EnvironmentalMetric) const = 0;

        virtual std::vector<EnvironmentalMetric> getMetricsForLastHours(int) const = 0;
    };
}
#endif
