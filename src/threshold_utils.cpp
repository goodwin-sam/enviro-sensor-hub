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

String checkTempThresholdFan(uint8_t enablePin, uint8_t pwmPin, float temperatureF, FanThresholds fanThresholds) {
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
