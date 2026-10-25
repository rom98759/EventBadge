# EventBadge

Wearable portfolio badge for tech events: a Wemos D1 mini (ESP8266) opens a
Wi-Fi hotspot whose captive portal is a tongue-in-cheek **Windows 95** desktop.
It springs a friendly "trap" on the curious, introduces Romain (student at
École 42, looking for an apprenticeship from June 2027), and links to his work.
An LCD1602 on the badge cycles identity + alternance and counts the curious.

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

## How it works

- `WIFI_AP` hotspot `Ce_WiFi_est_un_piege` (open), IP 192.168.4.1.
- A catch-all DNS server + replies to the OS captive-portal probes make the
  page pop up on its own when a phone joins.
- The web server serves one self-contained page (`PORTAL_HTML`) for every
  route. No internet, no external resource: everything is inline, fonts are
  system fonts, the avatar is an embedded data URI.
- The LCD cycles four screens (trap + counter, name/role, student 42,
  alternance June 2027) and flashes `+1 CURIEUX` on each connection.
- Two anonymous counters are kept (`connections`, `clicks`), persisted in
  EEPROM-emulated flash (debounced writes) so they survive a reboot. The page
  reads them from `/count` ("connections,clicks") and a link click fires a
  beacon to `/click`. Only totals are stored: no MAC address, device name or
  any identifier is ever read or kept.

## The portal page

- **Source of truth:** `web/index.html` (a standalone page — open it directly
  or serve it: `cd web && python3 -m http.server 8123`).
- **Avatar:** `web/assets/profil-128p.png` (128 px, 64-colour, ~9 KB).
- **Reaching the links:** a captive-portal mini-browser has no internet and
  won't open new tabs, so tapping a link just fails — and QR codes are useless
  when the visitor is already on the phone that shows them. Instead the page
  highlights one short memorable address (`caillier-romain.fr`, which links to
  everything) and the links are **tap-to-copy** buttons (clipboard, with an
  execCommand fallback since the portal is http, not a secure context): copy,
  leave the Wi-Fi, paste in a real browser.
- **Generate the firmware copy:** `python3 web/build.py` → rewrites
  `portal.h`, embedding every `assets/*.png` (the avatar) as data URIs.
  Always edit `index.html` and regenerate; never hand-edit `portal.h`.
- **Easter eggs:** menu *Fichier* / *Édition* (dropdowns, incl. "Copier mon
  lien"), **?** opens an "À propos de piège.exe" dialog, **OK** dismisses the
  warning and bumps the counter, **×** / *Quitter* / *Arrêter* trigger a fake
  BSOD, **Démarrer** opens a start menu.
- **Diagnostic:** the "Au passage, détecté sur vous" box is computed in the
  visitor's own browser (OS/browser, screen, language, timezone, battery) and
  shown only to them; nothing is sent to or stored on the badge. If a value is
  unavailable, a punchline is shown instead of a fake one.

## Libraries and core

- ESP8266 core 3.1.2 (board manager URL
  `https://arduino.esp8266.com/stable/package_esp8266com_index.json`)
- hd44780 (Bill Perry) 1.3.2

## Usage

```sh
arduino-cli config add board_manager.additional_urls https://arduino.esp8266.com/stable/package_esp8266com_index.json
arduino-cli core update-index && arduino-cli core install esp8266:esp8266
arduino-cli lib install hd44780
python3 web/build.py          # regenerate portal.h from web/index.html
arduino-cli compile && arduino-cli upload
```

Then join the Wi-Fi `Ce_WiFi_est_un_piege` on a phone; the portal opens on its
own (on Android a "Sign in to network" notification may need a tap).

## Config

`config.h` holds the SSID and the strings shown on the **LCD** (name, role,
school, alternance timing). The portal's own text lives in `web/index.html`.

## Troubleshooting

- `Permission denied` on `/dev/ttyUSB0`: `sudo setfacl -m u:$USER:rw /dev/ttyUSB0`
  (lost on unplug) or log out and back in after joining `dialout`.
- Serial garbage at boot is the ROM bootloader at 74880 baud; the sketch
  logs at 115200.
- Portal doesn't auto-open: some phones only show a notification to tap; the
  page is always reachable at `http://192.168.4.1`.
