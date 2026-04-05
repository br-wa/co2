#include <Arduino.h>

#include "app_config.h"
#include "sensor_hal.h"

namespace {
bool sensorReady = false;
uint32_t lastStatusMs = 0;

void printReading(const SensorReading& reading) {
    Serial.print("[reading] sensor=");
    Serial.print(sensorName());
    Serial.print(" co2_ppm=");
    Serial.print(reading.co2Ppm);

    if (reading.hasTemperature) {
        Serial.print(" temp_c=");
        Serial.print(reading.temperatureC, 2);
    }

    if (reading.hasHumidity) {
        Serial.print(" humidity_rh=");
        Serial.print(reading.humidityPercent, 2);
    }

    Serial.println();
}
}  // namespace

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    delay(STARTUP_DELAY_MS);

    Serial.println();
    Serial.printf("[boot] %s\n", DEVICE_NAME);
    Serial.printf("[boot] sensor=%s\n", sensorName());
    Serial.printf("[boot] i2c_sda=%d i2c_scl=%d\n", I2C_SDA_PIN, I2C_SCL_PIN);

    sensorReady = beginSensor();
    if (!sensorReady) {
        Serial.println("[boot] sensor init failed; check wiring and include/app_config.h");
        return;
    }

    Serial.println("[boot] sensor initialized");
}

void loop() {
    if (!sensorReady) {
        delay(1000);
        return;
    }

    SensorReading reading;
    if (readSensor(reading)) {
        printReading(reading);
        lastStatusMs = millis();
        delay(SENSOR_POLL_INTERVAL_MS);
        return;
    }

    const uint32_t now = millis();
    if (now - lastStatusMs >= STATUS_INTERVAL_MS) {
        Serial.println("[status] waiting for the next sensor reading");
        lastStatusMs = now;
    }

    delay(SENSOR_POLL_INTERVAL_MS);
}

