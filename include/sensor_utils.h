#ifndef INCLUDE_SENSOR_UTILS_H_
#define INCLUDE_SENSOR_UTILS_H_

#include <Arduino.h>
#include <DHT.h>
#include "config.h"

DhtData readTempAndHumidity(DHT *dht);
int readWaterLevel(int waterSensorPin);

#endif  // INCLUDE_SENSOR_UTILS_H_
