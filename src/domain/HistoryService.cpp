#include "../../include/domain/HistoryService.h"
#include "../../include/domain/IHistoryService.h"
#include <memory>
#include <utility>

namespace Domain {
    HistoryService::HistoryService(std::shared_ptr<Drivers::IHistoryStorage> storage)
        : m_storage{std::move(storage)} {
    }

    void HistoryService::processMeasurement(EnvironmentalMetric const metric) const {
        m_storage->addMeasurement(metric);
    }

    std::vector<EnvironmentalMetric> HistoryService::getMetricsForLastHours(int const hours) const {
        return m_storage->getMetricsForLastHours(hours);
    }
}
