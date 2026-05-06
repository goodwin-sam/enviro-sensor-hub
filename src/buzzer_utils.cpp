#include "buzzer_utils.h"
#include "display_utils.h"

bool checkTempThreshold(uint8_t buzzerPin, float temperatureF, float temperatureThreshold) {
    if (temperatureF > temperatureThreshold) {
        digitalWrite(buzzerPin, HIGH);
        return true;
    } else {
        digitalWrite(buzzerPin, LOW);
        return false;
    }
}

bool checkWaterLevelThreshold(uint8_t buzzerPin, int waterLevel, int waterLevelThreshold) {
    if (waterLevel > waterLevelThreshold) {
        digitalWrite(buzzerPin, HIGH);
        return true;
    } else {
        digitalWrite(buzzerPin, LOW);
        return false;
    }
}
