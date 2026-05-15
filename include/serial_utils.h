#ifndef INCLUDE_SERIAL_UTILS_H_
#define INCLUDE_SERIAL_UTILS_H_

#include <Arduino.h>
#include "dht_utils.h"

void printSensorData(const SensorReadings& readings);
void printSensorError();

#endif  // INCLUDE_SERIAL_UTILS_H_
