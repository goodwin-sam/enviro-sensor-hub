#include "water_utils.h"

int readWaterLevel(int waterSensorPin) {
    int waterLevel = analogRead(waterSensorPin);
    return waterLevel;
}
