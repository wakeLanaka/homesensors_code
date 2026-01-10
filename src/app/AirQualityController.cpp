#include "../../include/app/AirQualityController.h"
#include <memory>
#include <utility>

namespace App {
    AirQualityController::AirQualityController(std::shared_ptr<Drivers::ISensor> sensor,
                                               std::shared_ptr<Domain::IHistoryService> historyService)
        : m_sensor{std::move(sensor)}, m_historyService{std::move(historyService)} {
    }

    void AirQualityController::update() const {
        try {
            auto currentMetric = m_sensor->readData();
            m_historyService->processMeasurement(currentMetric);
            auto history = m_historyService->getMetricsForLastHours(24);
        } catch (const Drivers::I2CException &e) {
        } catch (const std::exception &e) {
        }
    }
}
