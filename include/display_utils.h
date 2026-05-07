#ifndef INCLUDE_DISPLAY_UTILS_H_
#define INCLUDE_DISPLAY_UTILS_H_

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include "dht_utils.h"

void initLcdDisplay(LiquidCrystal *lcd, int BACKLIGHT_TRANSISTOR_PIN);
void displaySensorData(LiquidCrystal *lcd, DhtData dhtData, int waterLevel, int lightLevel);
void displaySensorError(LiquidCrystal *lcd);
void changeLcdBacklight(int lightLevel, int BACKLIGHT_TRANSISTOR_PIN);
void displayWarning(LiquidCrystal *lcd, String message);

#endif  // INCLUDE_DISPLAY_UTILS_H_
