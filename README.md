# SCD41 Arduino Firmware

This repo now uses Arduino IDE instead of PlatformIO.

Open the sketch in [`arduino/scd41_monitor/scd41_monitor.ino`](/home/brwa/proj/co2/arduino/scd41_monitor/scd41_monitor.ino). The sketch reads an `SCD41` over I2C and prints CO2, temperature, and humidity to the serial monitor.

## Wiring

- `SCD41 VDD -> ESP32 3V3`
- `SCD41 GND -> ESP32 GND`
- `SCD41 SDA -> ESP32 GPIO21`
- `SCD41 SCL -> ESP32 GPIO22`

The pin config lives in [`arduino/scd41_monitor/app_config.h`](/home/brwa/proj/co2/arduino/scd41_monitor/app_config.h). Change it only if your wiring differs.

## Arduino IDE setup

1. Install Arduino IDE.
2. Add the Espressif board manager URL:

```text
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```

3. In Boards Manager, install `esp32`.
4. In Library Manager, install:
   `Sensirion I2C SCD4x`
   `Sensirion Core`
5. Open [`arduino/scd41_monitor/scd41_monitor.ino`](/home/brwa/proj/co2/arduino/scd41_monitor/scd41_monitor.ino).
6. Select your ESP32 board.
7. Select the serial port for the board.
8. Upload.
9. Open Serial Monitor at `115200`.

## Expected serial output

```text
[boot] scd41-monitor
[boot] sensor=Sensirion SCD41
[reading] sensor=Sensirion SCD41 co2_ppm=612 temp_c=23.48 humidity_rh=41.20
```
