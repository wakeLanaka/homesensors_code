#include "../../include/drivers/Scd40.h"
#include "../../include/domain/EnvironmentalMetric.h"

namespace Drivers {
    Domain::EnvironmentalMetric Scd40::readData() const {
        return Domain::EnvironmentalMetricalMetric{std::chrono::system_clock::now(), 0, 0, 0};
    }
}
