#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_

const float TEMP_THRESHOLD_BUZZER = 85.0;
const int WATER_LEVEL_THRESHOLD_BUZZER = 250;

struct TempThresholdsFan {
    float low;
    float medium;
    float high;
};
const TempThresholdsFan TEMP_THRESHOLDS_FAN = {70.0, 75.0, 80.0};

struct SensorThresholds {
    float tempLevelBuzzer;
    int waterLevelBuzzer;
    TempThresholdsFan tempLevelFan;
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

#endif  // INCLUDE_CONFIG_H_
