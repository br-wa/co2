#pragma once

#include <Arduino.h>

struct SensorReading {
    uint16_t co2Ppm = 0;
    float temperatureC = NAN;
    float humidityPercent = NAN;
    bool hasTemperature = false;
    bool hasHumidity = false;
};

bool beginSensor();
bool readSensor(SensorReading& reading);
const char* sensorName();

