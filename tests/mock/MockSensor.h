#ifndef AIRLOG_MOCKSENSOR_H_
#define AIRLOG_MOCKSENSOR_H_
#include "../../include/drivers/ISensor.h"
#include "gmock/gmock.h"

namespace Drivers {
    struct MockSensor : ISensor {
        MOCK_METHOD(Domain::EnvironmentalMetric, readData, (), (const, override));
    };
}
#endif
