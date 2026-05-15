#ifndef INCLUDE_SERIAL_UTILS_H_
#define INCLUDE_SERIAL_UTILS_H_

#include <Arduino.h>
#include "sensor_utils.h"
#include "threshold_utils.h"

void printSensorData(const SensorReadings& readings);
void printSensorError();
void printProgramInfo(const SensorThresholds& thresholds);

#endif  // INCLUDE_SERIAL_UTILS_H_
