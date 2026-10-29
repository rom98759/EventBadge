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

- Open `WIFI_AP` hotspot, IP 4.3.2.1 (not a private address: some Android
  builds skip portal detection when the probe resolves to one).
- **Hotspot name:** a list of up to 16 names (`WifiNames.cpp`), edited on the
  admin page and saved to `/wifi.txt`. Modes: fixed (first name), in turn or
  random every N minutes, optionally only while nobody is connected (a change
  restarts the AP and drops everyone). Defaults come from `CFG_SSIDS`.
  `WiFi.persistent(false)` keeps the SDK from rewriting flash on each change.
  Tapping a name on the admin page switches to it at once (`/admin/wifi/use`);
  the rotation timer restarts from there.
- A catch-all DNS server + replies to the OS captive-portal probes make the
  page pop up on its own when a phone joins.
- The web server serves one self-contained page (`PORTAL_HTML`) for every
  route. No internet, no external resource: everything is inline, fonts are
  system fonts, the avatar is an embedded data URI.
- The LCD cycles four screens (trap + counter, name/role, student 42,
  alternance June 2027) and flashes `+1 CURIEUX` on each connection.
- Two totals (`connections`, `clicks`) are persisted in EEPROM-emulated flash
  (debounced writes) and shown on the LCD and the page (`/count`).
- Every visit is also written to an event log; see *Stats and event log*.

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
  shown only to them; only the OS/browser family is sent to the badge (for the
  stats). If a value is unavailable, a punchline is shown instead of a fake one.

## Stats and event log

The badge has no clock and no internet, so it logs `millis()` + a boot number,
and the page sends the visitor's phone clock on load; the admin page dates
every event from the median of those clocks (and from its own clock for the
current boot).

| Event | Source | Extra data |
|---|---|---|
| boot | `setup()` | |
| connect / disconnect | Wi-Fi AP callbacks | association id |
| page opened | `/hi` beacon on load | phone time, OS + browser family |
| link copied | `/click` beacon | which link (portfolio / GitHub / LinkedIn) |
| left the page | `/bye` beacon (pagehide / hidden) | seconds on the page |
| hotspot name | each AP (re)start | FNV-1a hash of the name (the admin maps it back) |

- Each event is a 16-byte record appended to `/events.bin` on LittleFS
  (`EventLog.cpp`), batched every 3 s, capped at 1 MB (~65k events). The
  visitor id is an FNV-1a hash of the MAC salted with the chip id; HTTP
  requests are mapped to it through the AP's station list (IP → MAC).
- **Read it:** join the Wi-Fi, open `http://4.3.2.1/admin`, enter the key from
  `secrets.h`. The page downloads the raw log and computes everything in the
  browser: per-day connections, unique and returning visitors, pages opened,
  links copied per link, connections per hotspot name, devices, time on page,
  time connected, connections per hour, the last 200 events, a CSV export and a reset button (log + totals).
  "m'exclure" hides your own phone.
- On Android, if the page will not load, turn mobile data off: with a Wi-Fi
  that has no internet, Chrome may send requests over 4G instead.

## Libraries and core

- ESP8266 core 3.1.2, with its bundled LittleFS (board manager URL
  `https://arduino.esp8266.com/stable/package_esp8266com_index.json`)
- hd44780 (Bill Perry) 1.3.2

## Usage

```sh
arduino-cli config add board_manager.additional_urls https://arduino.esp8266.com/stable/package_esp8266com_index.json
arduino-cli core update-index && arduino-cli core install esp8266:esp8266
arduino-cli lib install hd44780
cp secrets.example.h secrets.h   # then set ADMIN_KEY (gitignored)
python3 web/build.py             # regenerate portal.h from web/index.html
arduino-cli compile --upload     # plain `upload` sends the last build, not the current code
```

Then join the Wi-Fi `Ce_WiFi_est_un_piege` on a phone; the portal opens on its
own (on Android a "Sign in to network" notification may need a tap).

## Config

Flash layout: the default `4MB (FS:2MB OTA:~1019KB)`; uploads use
"Only Sketch", which keeps the EEPROM totals and the log.

`config.h` holds the default hotspot names and the strings shown on the **LCD** (name, role,
school, alternance timing). The portal's own text lives in `web/index.html`.

## Troubleshooting

- `Permission denied` on `/dev/ttyUSB0`: `sudo setfacl -m u:$USER:rw /dev/ttyUSB0`
  (lost on unplug) or log out and back in after joining `dialout`.
- Serial garbage at boot is the ROM bootloader at 74880 baud; the sketch
  logs at 115200.
- Portal doesn't auto-open: some phones only show a notification to tap; the
  page is always reachable at `http://4.3.2.1`.
