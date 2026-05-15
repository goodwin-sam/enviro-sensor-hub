#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include "config.h"
#include "display_utils.h"
#include "threshold_utils.h"
#include "dht_utils.h"
#include "serial_utils.h"
#include "water_utils.h"

#define DHTTYPE DHT11

#define DHT_PIN 3
#define BUZZER_PIN 13
#define LDR_PIN A1
#define BACKLIGHT_TRANSISTOR_PIN 9
#define WATER_SENSOR_PIN A5
#define FAN_PIN_ENABLE 8
#define FAN_PIN_PWM 10

// lcd display: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

// dht11 temp and humidity sensor
DHT dht(DHT_PIN, DHTTYPE);

SensorThresholds thresholds = {TEMP_THRESHOLD_BUZZER, WATER_LEVEL_THRESHOLD_BUZZER, TEMP_THRESHOLDS_FAN};

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(BACKLIGHT_TRANSISTOR_PIN, OUTPUT);
  pinMode(FAN_PIN_ENABLE, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  initLcdDisplay(&lcd, BACKLIGHT_TRANSISTOR_PIN);
}

void loop() {
  SensorReadings readings;
  readings.dhtData = readTempAndHumidity(&dht);
  readings.waterLevel = readWaterLevel(WATER_SENSOR_PIN);
  int ldrValue = analogRead(LDR_PIN);
  readings.lightLevel = map(ldrValue, 0, 1023, 0, 255);

  bool tempAlarm = checkTempThresholdBuzzer(BUZZER_PIN, readings.dhtData.temperatureF, thresholds.tempLevelBuzzer);
  bool waterAlarm = checkWaterLevelThresholdBuzzer(BUZZER_PIN, readings.waterLevel, thresholds.waterLevelBuzzer);
  String fanSpeed = checkTempThresholdFan(FAN_PIN_ENABLE, FAN_PIN_PWM, readings.dhtData.temperatureF, thresholds.tempLevelFan);

  if (isnan(readings.dhtData.humidity) || isnan(readings.dhtData.temperatureF) || isnan(readings.waterLevel) || isnan(ldrValue) || isnan(readings.lightLevel)) {
    printSensorError();
    displaySensorError(&lcd);
    return;
  }

  displaySensorData(&lcd, readings.dhtData, readings.waterLevel, readings.lightLevel);

  printSensorData(readings);

  changeLcdBacklight(readings.lightLevel, BACKLIGHT_TRANSISTOR_PIN);
  // bool tempAlarm = checkTempThresholdBuzzer(BUZZER_PIN, readings.dhtData.temperatureF, TEMPERATURE_THRESHOLD_BUZZER);
  // bool waterAlarm = checkWaterLevelThresholdBuzzer(BUZZER_PIN, readings.waterLevel, WATER_LEVEL_THRESHOLD);
  // String fanSpeed = checkTempThresholdFan(FAN_PIN_ENABLE, FAN_PIN_PWM, readings.dhtData.temperatureF, FAN_THRESHOLDS);
  if (tempAlarm) {
    displayWarning(&lcd, "High Temperature");
    delay(1000);
  }
  if (waterAlarm) {
    displayWarning(&lcd, "High Water Level");
    delay(1000);
  }
  displayWarning(&lcd, "Fan: " + fanSpeed);
  delay(1000);
}
