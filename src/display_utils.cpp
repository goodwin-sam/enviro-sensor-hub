#include "display_utils.h"

void initLcdDisplay(LiquidCrystal *lcd, int BACKLIGHT_TRANSISTOR_PIN) {
    lcd->begin(16, 2);
    analogWrite(BACKLIGHT_TRANSISTOR_PIN, 255);
    lcd->print("Initializing");
    delay(3000);
    lcd->clear();
}

void displaySensorData(LiquidCrystal *lcd, SensorReadings readings, bool tempAlarm, bool waterAlarm) {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Temp: ");
    lcd->print(String(readings.dhtData.temperatureF, 1));
    lcd->print(static_cast<char>(223));
    lcd->print("F");
    lcd->setCursor(0, 1);
    lcd->print("Humidity: ");
    lcd->print(String(readings.dhtData.humidity, 1));
    lcd->print("%");
    delay(4000);
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Water Level: ");
    lcd->print(String(readings.waterLevel));
    lcd->setCursor(0, 1);
    lcd->print("Light Level: ");
    lcd->print(String(readings.lightLevel));
    delay(4000);
    displayWarning(lcd, "Fan: " + readings.fanSpeed);
    delay(1000);
    if (tempAlarm) {
        displayWarning(lcd, "High Temperature");
        delay(1000);
    }
    if (waterAlarm) {
        displayWarning(lcd, "High Water Level");
        delay(1000);
    }
    
}

void displaySensorError(LiquidCrystal *lcd) {
    lcd->clear();
    lcd->print("Sensor error");
}

void changeLcdBacklight(int lightLevel, int BACKLIGHT_TRANSISTOR_PIN) {
    analogWrite(BACKLIGHT_TRANSISTOR_PIN, lightLevel);
}

void displayWarning(LiquidCrystal *lcd, String message) {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print(message);
    delay(5000);
}
