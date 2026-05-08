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
#define FAN_PIN 8

// globals
// float temperatureThreshold = 85.0;
// int waterLevelThreshold = 250;

// lcd display: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

// dht11 temp and humidity sensor
DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(BACKLIGHT_TRANSISTOR_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  initLcdDisplay(&lcd, BACKLIGHT_TRANSISTOR_PIN);
}

void loop() {
  digitalWrite(FAN_PIN, HIGH);
  analogWrite(10, 255);
  DhtData dhtData = readTempAndHumidity(&dht);

  int waterLevel = readWaterLevel(WATER_SENSOR_PIN);
  printWaterLevel(waterLevel);

  int ldrValue = analogRead(LDR_PIN);
  int lightLevel = map(ldrValue, 0, 1023, 0, 255);

  if (isnan(dhtData.humidity) || isnan(dhtData.temperatureF)) {
    printSensorError();
    displaySensorError(&lcd);
    return;
  }
  displaySensorData(&lcd, dhtData, waterLevel, lightLevel);
  printSensorData(dhtData);
  changeLcdBacklight(lightLevel, BACKLIGHT_TRANSISTOR_PIN);
  printLightLevel(lightLevel);
  bool tempAlarm = checkTempThresholdBuzzer(BUZZER_PIN, dhtData.temperatureF, TEMPERATURE_THRESHOLD_BUZZER);
  bool waterAlarm = checkWaterLevelThresholdBuzzer(BUZZER_PIN, waterLevel, WATER_LEVEL_THRESHOLD);
  String fanSpeed = checkTempThresholdFan(FAN_PIN, dhtData.temperatureF, FAN_THRESHOLDS);
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
