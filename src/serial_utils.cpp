#include "serial_utils.h"

void printSensorData(const SensorReadings& readings) {
  Serial.println("Temperature: " + String(readings.dhtData.temperatureF, 1) + " °F  |  Humidity: " +
    String(readings.dhtData.humidity, 1) + " %");
    Serial.println("Light level: " + String(readings.lightLevel));
    Serial.println("Water level: " + String(readings.waterLevel));
    Serial.println("Fan speed: " + readings.fanSpeed);
    Serial.println("-----------------------------");
}

void printSensorError() {
  Serial.println("Failed to read from sensor");
}

void printProgramInfo(const SensorThresholds& thresholds) {
  Serial.println("=============================");
  Serial.println("  Environment Sensor Hub ");
  Serial.println("  Monitors temperature, humidity, water level, and light Level.");
  Serial.println("=============================");
  Serial.println();
  Serial.println("--- Buzzer Thresholds ---");
  Serial.println("  Temperature > " + String(thresholds.tempLevelBuzzer, 1) + " °F  →  Buzzer ON");
  Serial.println("  Water level > " + String(thresholds.waterLevelBuzzer) + "       →  Buzzer ON");
  Serial.println();
  Serial.println("--- Fan Thresholds ---");
  Serial.println("  Temperature <= " + String(thresholds.tempLevelFan.low, 1) + " °F  →  Fan OFF");
  Serial.println("  Temperature > " + String(thresholds.tempLevelFan.low, 1) + " °F  →  Fan LOW");
  Serial.println("  Temperature > " + String(thresholds.tempLevelFan.medium, 1) + " °F  →  Fan MEDIUM");
  Serial.println("  Temperature > " + String(thresholds.tempLevelFan.high, 1) + " °F  →  Fan HIGH");
  Serial.println();
    Serial.println("--- LCD Screen Backlight ---");
  Serial.println("  Adjusts automatically based on ambient light level (0-255).");
  Serial.println("=============================");
  Serial.println();
}
