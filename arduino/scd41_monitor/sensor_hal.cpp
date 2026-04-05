#include "sensor_hal.h"

#include "app_config.h"

#include <SensirionI2cScd4x.h>
#include <Wire.h>

namespace {
SensirionI2cScd4x sensor;

void logSensirionError(const char* operation, int16_t error) {
    Serial.printf("[sensor] %s failed with error=%d\n", operation, error);
}
}  // namespace

bool beginSensor() {
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN, I2C_FREQUENCY_HZ);
    sensor.begin(Wire, SCD41_I2C_ADDR_62);

    delay(30);
    int16_t error = sensor.wakeUp();
    if (error != 0) {
        logSensirionError("wakeUp", error);
    }

    error = sensor.stopPeriodicMeasurement();
    if (error != 0) {
        logSensirionError("stopPeriodicMeasurement", error);
    }

    error = sensor.reinit();
    if (error != 0) {
        logSensirionError("reinit", error);
        return false;
    }

    error = sensor.startPeriodicMeasurement();
    if (error != 0) {
        logSensirionError("startPeriodicMeasurement", error);
        return false;
    }

    return true;
}

bool readSensor(SensorReading& reading) {
    bool dataReady = false;
    int16_t error = sensor.getDataReadyStatus(dataReady);
    if (error != 0) {
        logSensirionError("getDataReadyStatus", error);
        return false;
    }

    if (!dataReady) {
        return false;
    }

    uint16_t co2 = 0;
    float temperature = 0.0f;
    float humidity = 0.0f;
    error = sensor.readMeasurement(co2, temperature, humidity);
    if (error != 0) {
        logSensirionError("readMeasurement", error);
        return false;
    }

    if (co2 == 0) {
        return false;
    }

    reading.co2Ppm = co2;
    reading.temperatureC = temperature;
    reading.humidityPercent = humidity;
    reading.hasTemperature = true;
    reading.hasHumidity = true;
    return true;
}

const char* sensorName() {
    return "Sensirion SCD41";
}

