#ifndef INCLUDE_SENSORS_H_
#define INCLUDE_SENSORS_H_

#include <Arduino.h>
#include <DHT.h>
#include "config.h"

DhtData readTempAndHumidity(DHT *dht);
int readWaterLevel(int waterSensorPin);

bool checkTempThresholdBuzzer(float temperatureF, float temperatureThreshold);
bool checkWaterLevelThresholdBuzzer(int waterLevel, int waterLevelThreshold);
String checkTempThresholdFan(uint8_t enablePin, uint8_t pwmPin, float temperatureF, TempThresholdsFan fanThresholds);

#endif  // INCLUDE_SENSORS_H_
