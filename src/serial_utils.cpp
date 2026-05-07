#include "serial_utils.h"

void printSensorData(const DhtData& data) {
  Serial.println("Temperature: " + String(data.temperatureF, 1) + " °F  |  Humidity: " +
    String(data.humidity, 1) + " %");
}

void printSensorError() {
  Serial.println("Failed to read from DHT sensor");
}

void printLightLevel(int lightLevel) {
  Serial.println("Light level: " + String(lightLevel));
}

void printWaterLevel(int waterLevel) {
  Serial.println("Water level: " + String(waterLevel));
}
