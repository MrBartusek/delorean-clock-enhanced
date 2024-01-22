# Delorean Clock Enhanced

![cover](https://cdn.thingiverse.com/assets/52/9c/2a/16/34/large_display_eb6220e4-8f30-42ba-a9af-b5bb5369c7cb.jpg)

> Custom firmware for **[Delorean clock - Back to the future style by jeje95](https://www.thingiverse.com/thing:2980120)** with couple of bugfixes, improvements and cleaner code.

This project assumes you are running the device under following conditions:

- Wiring diagram is same or similar to the original project
- You are using 24 hour time (this code doesn't support 12 hour time)

## Changes original code (V4)

- 👽 **PlatformIO** - This project is using [PlatformIO](https://platformio.org) insteed of Arduino IDE
- ⚙️ **Cleaner Configuration** - Pin numbers are much easier to configure
- ☀️ **Daylight saving time** - This variant uses [RTC_DS3231_DST.h](https://github.com/simmlemming/arduino_lib_RTC_DS3231_DST) to implement daylight saving time
- 🚨 **Red & Orange AM light** - You can connect both Red and Orange lights to `D2` (or any other) pin instead of 5v (configurable via `PIN_RED_ORANGE_AM`)
- 🐞 **Blink Disabled** - Month, day, hour and minute screens have blinking dots disabled. This causes clock to run very slowly.
- 🧹 **Code Improvements** - Original code was very cluttered, this project aims to clean it up

## Contributing

All contributions are welcome, feel free to open an [issue](https://github.com/MrBartusek/delorean-clock-enhanced/issues) or [Pull Request](https://github.com/MrBartusek/delorean-clock-enhanced)
