#ifndef AIRLOG_ISENSOR_H_
#define AIRLOG_ISENSOR_H_
#include "../domain/EnvironmentalMetric.h"

namespace Drivers {
    struct ISensor {
        virtual ~ISensor() = default;

        virtual Domain::EnvironmentalMetric readData() const = 0;
    };
}
#endif
