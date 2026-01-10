#ifndef AIRLOG_ENVIRONMENTALMETRIC_H
#define AIRLOG_ENVIRONMENTALMETRIC_H
#include <chrono>
#include <string>

namespace Domain {
    enum class AirQualityLevel { GOOD, WARNING, UNACCEPTABLE };

    struct EnvironmentalMetric {
        float co2Ppm;
        float temperature;
        float humidity;
        std::chrono::system_clock::time_point timestamp;

        EnvironmentalMetric(std::chrono::system_clock::time_point, float, float, float);

        AirQualityLevel getLevel() const;

        std::string getLevelAsText() const;

        long getUnixTimestamp() const;

        bool operator==(EnvironmentalMetric const &rhs) const {
            return co2Ppm == rhs.co2Ppm
                   && temperature == rhs.temperature
                   && humidity == rhs.humidity
                   && timestamp == rhs.timestamp;
        }
    };
}

#endif
