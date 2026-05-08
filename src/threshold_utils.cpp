#include "threshold_utils.h"
#include "display_utils.h"
#include "config.h"

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

String checkTempThresholdFan(uint8_t fanPin, float temperatureF, FanThresholds fanThresholds) {
       if (temperatureF > fanThresholds.high) {
        analogWrite(fanPin, 255);  // High speed
        return "high";
    } else if (temperatureF > fanThresholds.medium) {
        analogWrite(fanPin, 200);  // Medium speed
        return "medium";
    } else if (temperatureF > fanThresholds.low) {
        analogWrite(fanPin, 150);  // Low speed
        return "low";
    } else {
        analogWrite(fanPin, 0);  // Fan off
        return "off";
    }
}
