#include "sensors.h"
#include "config.h"

#include <DHT.h>

DhtData readTempAndHumidity(DHT *dht) {
    DhtData data;
    data.humidity = dht->readHumidity();
    data.temperatureC = dht->readTemperature();
    data.temperatureF = data.temperatureC * 9.0 / 5.0 + 32.0;
    return data;
}

int readWaterLevel(int waterSensorPin) {
    int waterLevel = analogRead(waterSensorPin);
    return waterLevel;
}

bool checkTempThresholdBuzzer(uint8_t buzzerPin, float temperatureF, float temperatureThreshold) {
    if (temperatureF > temperatureThreshold) {
        digitalWrite(buzzerPin, HIGH);
        return true;
    } else {
        digitalWrite(buzzerPin, LOW);
        return false;
    }
}

bool checkWaterLevelThresholdBuzzer(uint8_t buzzerPin, int waterLevel, int waterLevelThreshold) {
    if (waterLevel > waterLevelThreshold) {
        digitalWrite(buzzerPin, HIGH);
        return true;
    } else {
        digitalWrite(buzzerPin, LOW);
        return false;
    }
}

String checkTempThresholdFan(uint8_t enablePin, uint8_t pwmPin, float temperatureF, TempThresholdsFan fanThresholds) {
       if (temperatureF > fanThresholds.high) {
        digitalWrite(enablePin, HIGH);
        analogWrite(pwmPin, 255);  // High speed
        return "high";
    } else if (temperatureF > fanThresholds.medium) {
        digitalWrite(enablePin, HIGH);
        analogWrite(pwmPin, 200);  // Medium speed
        return "medium";
    } else if (temperatureF > fanThresholds.low) {
        digitalWrite(enablePin, HIGH);
        analogWrite(pwmPin, 150);  // Low speed
        return "low";
    } else {
        digitalWrite(enablePin, LOW);
        analogWrite(pwmPin, 0);  // Fan off
        return "off";
    }
}
