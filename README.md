# EventBadge

Wearable portfolio badge for tech events: a Wemos D1 mini (ESP8266) drives an
LCD1602 I²C display that says who I am, and opens a Wi-Fi hotspot whose
captive portal serves a lightweight portfolio page (no internet needed).

## Hardware

- Wemos D1 mini (ESP8266EX, 4 MB flash, CH340 USB-serial)
- LCD1602 + PCF8574 backpack, detected at 0x27
- USB power bank (about 100 mA draw)

## Wiring

| LCD backpack | D1 mini |
|---|---|
| GND | G |
| VCC | 5V |
| SDA | D2 (GPIO4) |
| SCL | D1 (GPIO5) |

The backpack pulls SDA/SCL up to 5 V. The ESP8266 tolerates it in practice
but this is outside its spec: if the bus becomes flaky, add a BSS138 level
shifter first.

## Libraries and core

- ESP8266 core 3.1.2 (board manager URL
  `https://arduino.esp8266.com/stable/package_esp8266com_index.json`)
- hd44780 (Bill Perry) 1.3.2

## Usage

```sh
arduino-cli config add board_manager.additional_urls https://arduino.esp8266.com/stable/package_esp8266com_index.json
arduino-cli core update-index && arduino-cli core install esp8266:esp8266
arduino-cli lib install hd44780
arduino-cli compile && arduino-cli upload
```

## Troubleshooting

- `Permission denied` on `/dev/ttyUSB0`: `sudo setfacl -m u:$USER:rw /dev/ttyUSB0`
  (lost on unplug) or log out and back in after joining `dialout`.
- Serial garbage at boot is the ROM bootloader at 74880 baud; the sketch
  logs at 115200.
