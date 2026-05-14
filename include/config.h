#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_

const float TEMPERATURE_THRESHOLD_BUZZER = 85.0;
const int WATER_LEVEL_THRESHOLD = 250;

struct FanThresholds {
    float low;
    float medium;
    float high;
};

struct DhtData{
    float humidity;
    float temperatureF;
    float temperatureC;
};

struct SensorReadings {
    DhtData dhtData;
    int waterLevel;
    int lightLevel;
};

const FanThresholds FAN_THRESHOLDS = {70.0, 75.0, 80.0};

#endif  // INCLUDE_CONFIG_H_
