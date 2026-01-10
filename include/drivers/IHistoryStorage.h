#ifndef AIRLOG_HISTORY_STORAGE_H_
#define AIRLOG_HISTORY_STORAGE_H_

#include <chrono>
#include "../domain/EnvironmentalMetric.h"

namespace Drivers {
    struct IHistoryStorage {
        virtual ~IHistoryStorage() = default;

        virtual void addMeasurement(Domain::EnvironmentalMetric) const = 0;

        virtual std::vector<Domain::EnvironmentalMetric> getMetricsForLastHours(int) const = 0;
    };
}

#endif
