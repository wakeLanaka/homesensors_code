#ifndef AIRLOG_AIR_QUALITY_CONTROLLER_H_
#define AIRLOG_AIR_QUALITY_CONTROLLER_H_

#include "../drivers/ISensor.h"
#include <memory>
#include "../domain/IHistoryService.h"


namespace App {
    struct AirQualityController {
        explicit AirQualityController(std::shared_ptr<Drivers::ISensor>, std::shared_ptr<Domain::IHistoryService>);

        void update() const;

    private:
        std::shared_ptr<Drivers::ISensor> const m_sensor;
        std::shared_ptr<Domain::IHistoryService> m_historyService;
    };
}
#endif
