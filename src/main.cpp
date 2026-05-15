#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include "config.h"
#include "sensors.h"
#include "display_utils.h"
#include "serial_utils.h"

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
  printProgramInfo(thresholds);
  dht.begin();
  initLcdDisplay(&lcd, BACKLIGHT_TRANSISTOR_PIN);
}

void loop() {
  // read sensors and save to SensorReadings struct
  SensorReadings readings;
  readings.dhtData = readTempAndHumidity(&dht);
  readings.waterLevel = readWaterLevel(WATER_SENSOR_PIN);
  int ldrValue = analogRead(LDR_PIN);
  readings.lightLevel = map(ldrValue, 0, 1023, 0, 255);

  // check thresholds and update fan speed, buzzer state & lcd screen backlight
  bool tempAlarm = checkTempThresholdBuzzer(readings.dhtData.temperatureF, thresholds.tempLevelBuzzer);
  bool waterAlarm = checkWaterLevelThresholdBuzzer(readings.waterLevel, thresholds.waterLevelBuzzer);
  digitalWrite(BUZZER_PIN, (tempAlarm || waterAlarm) ? HIGH : LOW);
  readings.fanSpeed = checkTempThresholdFan(FAN_PIN_ENABLE, FAN_PIN_PWM, readings.dhtData.temperatureF, thresholds.tempLevelFan);
  changeLcdBacklight(readings.lightLevel, BACKLIGHT_TRANSISTOR_PIN);

  // check for sensor read errors and display
  if (isnan(readings.dhtData.humidity) || isnan(readings.dhtData.temperatureF)) {
    printSensorError();
    displaySensorError(&lcd);
    return;
  }

  // display sensor data
  printSensorData(readings);
  displaySensorData(&lcd, readings, tempAlarm, waterAlarm);
}
