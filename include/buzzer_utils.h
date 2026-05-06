#ifndef INCLUDE_BUZZER_UTILS_H_
#define INCLUDE_BUZZER_UTILS_H_

#include <Arduino.h>

bool checkTempThreshold(uint8_t buzzerPin, float temperatureF, float temperatureThreshold);
bool checkWaterLevelThreshold(uint8_t buzzerPin, int waterLevel, int waterLevelThreshold);

#endif  // INCLUDE_BUZZER_UTILS_H_
