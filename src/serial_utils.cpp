#include "serial_utils.h"

void printSensorData(const SensorReadings& readings) {
  Serial.println("Temperature: " + String(readings.dhtData.temperatureF, 1) + " °F  |  Humidity: " +
    String(readings.dhtData.humidity, 1) + " %");
    Serial.println("Light level: " + String(readings.lightLevel));
    Serial.println("Water level: " + String(readings.waterLevel));
}

void printSensorError() {
  Serial.println("Failed to read from sensor");
}
