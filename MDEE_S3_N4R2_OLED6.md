# M'DEE ESP32-S3 N4R2 + 0.96in OLED + 6 buttons

Custom build target based on ESP32 Marauder source.

## Board
- ESP32-S3 N4R2
- 4 MB flash
- 2 MB QSPI PSRAM
- Arduino-ESP32 2.0.14

## OLED
0.96 inch SSD1306 128x64 I2C, address 0x3C.
- SDA GPIO 8
- SCL GPIO 9

## Buttons
All buttons are active LOW and connect between the GPIO and GND:
- UP GPIO 1
- DOWN GPIO 10
- LEFT GPIO 11
- RIGHT GPIO 12
- SELECT GPIO 13
- BACK/STATUS GPIO 14

The sixth button is exposed as the M'DEE local status button.

## GitHub Actions
Push the repository to GitHub. The workflow `.github/workflows/build_mdee.yml` builds:
`mdee_s3_n4r2_oled6.bin`

The binary is available under the Actions run's Artifacts section.
