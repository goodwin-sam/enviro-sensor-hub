#ifndef INCLUDE_SERIAL_UTILS_H_
#define INCLUDE_SERIAL_UTILS_H_

#include <Arduino.h>
#include "sensors.h"

void printSensorData(const SensorReadings& readings);
void printSensorError();
void printProgramInfo(const SensorThresholds& thresholds);

#endif  // INCLUDE_SERIAL_UTILS_H_
