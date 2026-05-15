#include "sensor_utils.h"
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
