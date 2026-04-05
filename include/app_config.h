#pragma once

#include <Arduino.h>

constexpr char DEVICE_NAME[] = "scd41-monitor";
constexpr uint32_t SERIAL_BAUD_RATE = 115200;
constexpr uint32_t STARTUP_DELAY_MS = 1500;
constexpr uint32_t SENSOR_POLL_INTERVAL_MS = 1000;
constexpr uint32_t STATUS_INTERVAL_MS = 10000;

// Default ESP32 I2C pins. Change these if you wired your SCD41 elsewhere.
constexpr int I2C_SDA_PIN = 21;
constexpr int I2C_SCL_PIN = 22;
constexpr uint32_t I2C_FREQUENCY_HZ = 100000;

