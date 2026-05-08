#ifndef INCLUDE_THRESHOLD_UTILS_H_
#define INCLUDE_THRESHOLD_UTILS_H_

#include <Arduino.h>
#include "config.h"

bool checkTempThresholdBuzzer(uint8_t buzzerPin, float temperatureF, float temperatureThreshold);
bool checkWaterLevelThresholdBuzzer(uint8_t buzzerPin, int waterLevel, int waterLevelThreshold);
String checkTempThresholdFan(uint8_t fanPin, float temperatureF, FanThresholds fanThresholds);

#endif  // INCLUDE_THRESHOLD_UTILS_H_
