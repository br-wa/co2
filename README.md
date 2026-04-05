# SCD41 Monitor Firmware

This project is a clean ESP32 firmware scaffold for an `SCD41` CO2, temperature, and humidity monitor over I2C.

The firmware prints readings like this over the serial monitor:

```text
[reading] sensor=Sensirion SCD41 co2_ppm=612 temp_c=23.48 humidity_rh=41.20
```

## 1. Match the pin configuration

Edit [`include/app_config.h`](/home/brwa/proj/co2/include/app_config.h):

```cpp
constexpr int I2C_SDA_PIN = 21;
constexpr int I2C_SCL_PIN = 22;
```

Default wiring in this scaffold is `SDA=GPIO21` and `SCL=GPIO22`.

Typical wiring:

- `SCD41 VDD -> ESP32 3V3`
- `SCD41 GND -> ESP32 GND`
- `SCD41 SDA -> ESP32 SDA pin`
- `SCD41 SCL -> ESP32 SCL pin`

## 2. Install the build tool

This repo is set up for PlatformIO.

Option A:

- Install the PlatformIO VS Code extension
- Open this folder in VS Code
- Use the build, upload, and monitor actions from PlatformIO

Option B:

```bash
python3 -m pip install --user platformio
```

If you already use `uv`, this also works:

```bash
uv tool run platformio --version
```

## 3. Build and flash

From this folder:

```bash
pio run
pio run -t upload --upload-port /dev/ttyUSB0
pio device monitor -b 115200
```

Replace `/dev/ttyUSB0` with the serial device for your ESP32.

## 4. What to expect

- The `SCD41` produces fresh measurements roughly every 5 seconds in periodic mode
- The firmware prints CO2, temperature, and humidity to the serial monitor at `115200`

## Current limitation

This is being compiled in the current environment now, but it has not been flashed to a physical board here. If your `SDA` and `SCL` pins are not `21` and `22`, update [`include/app_config.h`](/home/brwa/proj/co2/include/app_config.h) before upload.
