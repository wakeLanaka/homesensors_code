#include "../include/app/AirQualityController.h"
#include "../include/drivers/Scd40.h"
#include "../include/drivers/SqlStorage.h"
#include "../include/domain/HistoryService.h"

int main(int, char **) {
    Drivers::SqlStorage storage{"/tmp/metrics.db"};
    Domain::HistoryService historyService{std::make_shared<Drivers::SqlStorage>(storage)};
    Drivers::Scd40 sensor{};

    App::AirQualityController controller{
        std::make_shared<Drivers::Scd40>(sensor),
        std::make_shared<Domain::HistoryService>(historyService)
    };


    while (true) {
        controller.update();
        // historyService.processMeasurement();
    }
}
