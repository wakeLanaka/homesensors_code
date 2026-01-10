#ifndef AIRLOG_SCD40_H
#define AIRLOG_SCD40_H
#include "ISensor.h"

namespace Drivers {
    struct Scd40 : ISensor {
        Domain::EnvironmentalMetric readData() const override;
    };
}
#endif
