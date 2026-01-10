#include "../../include/domain/EnvironmentalMetric.h"

namespace Domain {
    EnvironmentalMetric::EnvironmentalMetric(std::chrono::system_clock::time_point timestamp, float co2,
                                             float temperature, float humidity) : co2Ppm{co2},
        temperature{temperature},
        humidity{humidity},
        timestamp{timestamp} {
    }

    AirQualityLevel EnvironmentalMetric::getLevel() const {
        if (co2Ppm < 1000) return AirQualityLevel::GOOD;
        if (co2Ppm < 2000) return AirQualityLevel::WARNING;
        return AirQualityLevel::UNACCEPTABLE;
    }

    std::string EnvironmentalMetric::getLevelAsText() const {
        switch (getLevel()) {
            case AirQualityLevel::GOOD: return "Good";
            case AirQualityLevel::WARNING: return "Warning";
            case AirQualityLevel::UNACCEPTABLE: return "Unacceptable";
            default: return "Not available";
        }
    }

    long EnvironmentalMetric::getUnixTimestamp() const {
        return std::chrono::duration_cast<std::chrono::seconds>(
            timestamp.time_since_epoch()
        ).count();
    }
}
