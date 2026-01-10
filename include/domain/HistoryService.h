#ifndef AIRLOG_HISTORY_MANAGER_H_
#define AIRLOG_HISTORY_MANAGER_H_

#include "../drivers/ISensor.h"
#include "../drivers/IHistoryStorage.h"
#include <memory>

#include "IHistoryService.h"

namespace Domain {
    struct HistoryService : IHistoryService {
        explicit HistoryService(std::shared_ptr<Drivers::IHistoryStorage> storage);

        void processMeasurement(EnvironmentalMetric data) const override;

        std::vector<EnvironmentalMetric> getMetricsForLastHours(int) const override;

    private:
        std::shared_ptr<Drivers::IHistoryStorage> const m_storage;
    };
}
#endif
