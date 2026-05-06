#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include "display_utils.h"
#include "buzzer_utils.h"
#include "dht_utils.h"
#include "serial_utils.h"
#include "water_utils.h"

#define DHTTYPE DHT11

#define DHT_PIN 3
#define BUZZER_PIN 13
#define LDR_PIN A1
#define BACKLIGHT_TRANSISTOR_PIN 9
#define WATER_SENSOR_PIN A5

// globals
float temperatureThreshold = 85.0;
int waterLevelThreshold = 250;

// lcd display: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

// dht11 temp and humidity sensor
DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(BACKLIGHT_TRANSISTOR_PIN, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  initLcdDisplay(&lcd, BACKLIGHT_TRANSISTOR_PIN);
}

void loop() {
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
  
  bool tempAlarm = checkTempThreshold(BUZZER_PIN, dhtData.temperatureF, temperatureThreshold);
  bool waterAlarm = checkWaterLevelThreshold(BUZZER_PIN, waterLevel, waterLevelThreshold);
  
  if (tempAlarm) {
    displayWarning(&lcd, "High Temperature");
    delay(1000);
  }

  if (waterAlarm) {
    displayWarning(&lcd, "High Water Level");
    delay(1000);
  }
}
