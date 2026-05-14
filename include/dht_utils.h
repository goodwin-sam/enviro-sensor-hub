#ifndef INCLUDE_DHT_UTILS_H_
#define INCLUDE_DHT_UTILS_H_

#include <Arduino.h>
#include <DHT.h>

#include "config.h"

DhtData readTempAndHumidity(DHT *dht);

#endif  // INCLUDE_DHT_UTILS_H_
