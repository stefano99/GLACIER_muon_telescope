# GLACIER Muon Telescope — Arduino firmware

## Overview
GLACIER Muon Telescope firmware for Arduino/PlatformIO.  
This repository contains firmware for an UNO R4 WiFi-based muon telescope: sensor acquisition, local SD logging, and MQTT publishing over WiFi.

## Key Features
- Reads muon detector sensor pulses and environmental sensors.
- Publishes measurements via MQTT.
- Logs data to an SD card.
- Configurable WiFi and MQTT credentials via an included secrets header.
- Built with PlatformIO for UNO R4 WiFi (see [platformio.ini](platformio.ini)).

## Repository structure
- [platformio.ini](platformio.ini): PlatformIO build configuration and environments.
- [src/main.cpp](src/main.cpp): Application entry point and main loop.
- [src/muonSensor.cpp](src/muonSensor.cpp) / [src/muonSensor.h](src/muonSensor.h): Muon sensor driver and sampling logic.
- [src/publisher_mqtt.cpp](src/publisher_mqtt.cpp) / [src/publisher_mqtt.h](src/publisher_mqtt.h): MQTT publishing implementation.
- [src/sdcard.cpp](src/sdcard.cpp) / [src/sdcard.h](src/sdcard.h): SD card logging helpers.
- [src/tempSensor.cpp](src/tempSensor.cpp) / [src/tempSensor.h](src/tempSensor.h): Temperature sensor support.
- [include/arduino_secrets-template.h](include/arduino_secrets-template.h): Template for secret credentials.
- [include/arduino_secrets.h](include/arduino_secrets.h): Your local copy (not committed) with WiFi/MQTT credentials.
- [lib/](lib/): Third-party libraries and local library modules (WiFiS3, MQTT client, UNO bridge helpers).
- [test/](test/): Experimental/test code and notes.

## Hardware & Wiring (suggested mapping)
Below is a recommended starting pin mapping for an UNO R4 WiFi. Adjust pins to match your detector breakout and SD module.

Muon detector pulse -> D2 (INT0)  
Temp sensor (DS18B20) -> D3 (1-Wire, needs pull-up)  
Status LED -> D6 (optional)

SD Card (SPI):
- MOSI -> D11
- MISO -> D12
- SCK  -> D13
- CS   -> D10

I2C (if used): SDA -> A4, SCL -> A5 (or board-specific SDA/SCL pins)

Power/Ground:
- 3.3V or 5V -> as required by sensor modules
- GND -> common ground

Diagram (simplified):

 [Muon Detector] ----- D2 (pulse input)  
 [DS18B20] ----------- D3 (+ pull-up 4.7k to VCC)  
 [Status LED] -------- D6 (with resistor)  
 [SD Module]  
     MOSI --------- D11  
     MISO --------- D12  
     SCK ---------- D13  
     CS  ---------- D10  
     VCC ---------- 3.3V or 5V (module dependent)  
     GND ---------- GND

Notes:
- Use D2 (external interrupt) for reliable pulse counting; it's configured in `src/muonSensor.*`.
- If using a different microcontroller pin or a hardware interrupt, update the mapping in `src/muonSensor.h`.

## Configuration
1. Copy [include/arduino_secrets-template.h](include/arduino_secrets-template.h) to [include/arduino_secrets.h](include/arduino_secrets.h).
2. Fill in your WiFi SSID/password, MQTT broker, credentials, and device ID.

Example:

    #define WIFI_SSID "your-ssid"
    #define WIFI_PASS "your-password"
    #define MQTT_HOST "broker.example.com"
    #define MQTT_PORT 1883
    #define MQTT_USER "user"
    #define MQTT_PASS "pass"
    #define DEVICE_ID "glacier-muon-001"

Do NOT commit `include/arduino_secrets.h`.
It's already added in the .gitignore, but be sure it's not in the commit before pushing the code to any git server!

## Build & Upload
Build and upload using PlatformIO (CLI) or the VS Code PlatformIO extension.

Build:

    pio run --environment uno_r4_wifi

Upload:

    pio run --target upload --environment uno_r4_wifi

## Runtime behavior
- On boot the firmware initializes WiFi, the MQTT client, SD card, and sensors.
- Muon pulses are counted via the interrupt pin and debounced in software.
- Events/measurements are appended to the SD log and published to MQTT topics.
- Serial output provides debug and status messages.

## MQTT topics and payloads
Topic patterns and JSON payloads are defined in `src/publisher_mqtt.*`. Typical messages include timestamp, device id, counts, and sensor readings. See `src/publisher_mqtt.*` for exact topic names and JSON formats.

## Troubleshooting
- Check serial output for startup errors and WiFi/MQTT connection status.
- Verify `include/arduino_secrets.h` contains correct credentials.
- If SD logging fails, confirm wiring and card format (FAT32 recommended).
- Use a local MQTT client to subscribe and verify messages, for example:
    
    mosquitto_sub -h broker.example.com -t "glacier/+/telemetry" -v

## Development notes
- Libraries are under `lib/`. Modify or replace if you target different WiFi modules.
- `lib/UNOR4USBBridge` contains helper code for UNO R4 USB/WiFi specifics.
- Tests and experimental sketches are in `test/` and `lib/.../examples/`.
- To activate serial output, modify the main.h file and set the DEBUG constant to 1. Default behavior is having it set to 0, with serial disabled and sending data and logs only through MQTT.

## Contributing
- Open issues for bug reports or feature requests.
- For code contributions, fork and submit pull requests with a clear description and testing steps.

## License
No license file detected. Add a LICENSE to clarify reuse terms (e.g., MIT, Apache-2.0).