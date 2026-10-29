#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <EEPROM.h>
#include <LittleFS.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#include "config.h"
#include "portal.h"
#include "admin.h"
#include "EventLog.h"
#include "WifiNames.h"

#if __has_include("secrets.h")
#include "secrets.h"
#else
#error "Copy secrets.example.h to secrets.h and set ADMIN_KEY"
#endif

extern "C" {
#include <user_interface.h>
}

// Deliberately not a private address: some Android builds (seen on a Samsung
// S23, Android 16) treat a probe hostname resolving to a private IP as "no
// internet" and never send the captive-portal probe. The network is isolated,
// so this public-looking address is never routed anywhere.
const IPAddress AP_IP(4, 3, 2, 1);
const uint32_t SCREEN_MS = 4500;   // time on each resting screen
const uint32_t ALERT_MS = 3000;    // time the "new connection" alert stays up
const uint32_t FLASH_MS = 160;     // backlight blink half-period during an alert
const uint32_t LCD_CHECK_MS = 2000; // how often to look for the screen / check it is still there

hd44780_I2Cexp lcd;
DNSServer dns;
ESP8266WebServer server(80);
WiFiEventHandler onConnect;
WiFiEventHandler onDisconnect;

enum Glyph : uint8_t { SKULL, WIFI, DOT, CHIP };

uint8_t glyphs[][8] = {
  {0b01110, 0b11111, 0b10101, 0b11111, 0b10101, 0b01110, 0b01010, 0b00000},  // skull
  {0b00000, 0b10000, 0b10100, 0b10101, 0b10101, 0b10101, 0b00000, 0b00000},  // wifi bars
  {0b00000, 0b00000, 0b00110, 0b01111, 0b01111, 0b00110, 0b00000, 0b00000},  // middle dot
  {0b00000, 0b01110, 0b10001, 0b10101, 0b10001, 0b01110, 0b00000, 0b00000},  // chip
};

// Anonymous counts, kept across reboots in EEPROM. `connections` is set from
// the AP connect event (ISR-like context), so it is volatile and read with
// interrupts briefly disabled. `clicks` is bumped from the web handler.
volatile uint16_t connections = 0;
uint16_t clicks = 0;

// Persistence: a tiny record in EEPROM-emulated flash, saved debounced.
struct Stats { uint16_t magic; uint16_t conn; uint16_t clk; };
const uint16_t STATS_MAGIC = 0x4201;
const uint32_t SAVE_AFTER_MS = 8000;  // debounce flash writes
bool statsDirty = false;
uint32_t statsChangedAt = 0;

uint8_t screen = 0;
uint32_t screenAt = 0;
uint32_t alertUntil = 0;
uint32_t flashAt = 0;
bool backlightOn = true;
bool alertPending = false;

// The portal must keep working with the screen missing or unplugged, so the
// LCD is optional: drawing is skipped while it is absent and it is brought up
// whenever it (re)appears on the bus.
bool lcdReady = false;
uint32_t lcdCheckAt = 0;

// hd44780_I2Cexp's auto-locate counter is static and advances on every failed
// begin(), so retrying begin() with no device would later skip the real one.
// Probe the expander ranges ourselves and only call begin() once one answers.
bool expanderPresent() {
  for (uint8_t a = 0x20; a <= 0x3F; a++) {
    if (a == 0x28) a = 0x38;  // PCF8574/MCP23008 0x20-0x27, PCF8574A 0x38-0x3F
    Wire.beginTransmission(a);
    if (Wire.endTransmission() == 0) return true;
  }
  return false;
}

bool lcdAnswers() {
  uint8_t addr = lcd.getProp(hd44780_I2Cexp::Prop_addr);
  if (!addr) return expanderPresent();
  Wire.beginTransmission(addr);
  return Wire.endTransmission() == 0;
}

// A replugged LCD has lost its state, so (re)appearing always means a full begin().
void syncLcd() {
  bool present = lcdAnswers();
  if (present == lcdReady) return;
  lcdReady = false;
  if (!present) {
    Serial.println(F("LCD: lost, running without it"));
    return;
  }
  int status = lcd.begin(16, 2);
  if (status) {
    Serial.printf("LCD: init failed (%d), will retry\n", status);
    return;
  }
  for (uint8_t i = 0; i < sizeof(glyphs) / sizeof(glyphs[0]); i++)
    lcd.createChar(i, glyphs[i]);
  lcdReady = true;
  backlightOn = true;
  Serial.println(F("LCD: ready"));
}

void printLine(uint8_t row, const char *text) {
  char buf[17];
  snprintf(buf, sizeof(buf), "%-16s", text);
  lcd.setCursor(0, row);
  lcd.print(buf);
}

// Center text on a 16-char row, blanking the rest.
void printCentered(uint8_t row, const char *text) {
  char buf[17];
  int len = strlen(text);
  if (len > 16) len = 16;
  int pad = (16 - len) / 2;
  memset(buf, ' ', 16);
  memcpy(buf + pad, text, len);
  buf[16] = '\0';
  lcd.setCursor(0, row);
  lcd.print(buf);
}

// setCursor/write lets a custom glyph sit inside a text line.
void putGlyph(uint8_t col, uint8_t row, uint8_t g) {
  lcd.setCursor(col, row);
  lcd.write(g);
}

uint16_t readConnections() {
  noInterrupts();
  uint16_t c = connections;
  interrupts();
  return c;
}

void loadStats() {
  Stats s;
  EEPROM.get(0, s);
  if (s.magic == STATS_MAGIC) {
    connections = s.conn;
    clicks = s.clk;
  }
}

void saveStats() {
  Stats s = { STATS_MAGIC, readConnections(), clicks };
  EEPROM.put(0, s);
  EEPROM.commit();
}

void markDirty() {
  statsDirty = true;
  statsChangedAt = millis();
}

void drawResting(uint8_t which) {
  if (!lcdReady) return;
  lcd.clear();
  char buf[17];
  switch (which) {
    case 0:
      printCentered(0, "PIEGE A CURIEUX");
      putGlyph(1, 0, SKULL);
      putGlyph(14, 0, SKULL);
      snprintf(buf, sizeof(buf), "curieux: %u", readConnections());
      printCentered(1, buf);
      break;
    case 1:
      printCentered(0, CFG_NAME);
      printCentered(1, CFG_ROLE);
      putGlyph(0, 1, CHIP);
      putGlyph(15, 1, CHIP);
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print(">_ etudiant 42");
      printCentered(1, "stage pentest");
      break;
    case 3:
      printCentered(0, ">> ALTERNANCE <<");
      printCentered(1, "des juin 2027");
      break;
  }
}

void drawAlert() {
  if (!lcdReady) return;
  lcd.clear();
  printCentered(0, "+1 CURIEUX !");
  putGlyph(1, 0, WIFI);
  putGlyph(14, 0, WIFI);
  printCentered(1, "bienvenue a toi");
}

void logRequest(const char *reply) {
#if CFG_LOG_HTTP
  Serial.printf("[http] %s %s%s -> %s | %s\n",
                server.method() == HTTP_GET ? "GET" : "OTHER",
                server.hostHeader().c_str(), server.uri().c_str(), reply,
                server.header("User-Agent").c_str());
#endif
}

// HTTP handlers only see an IP; the AP's station list maps it back to the MAC.
// Changing the name restarts the AP, which drops every connected phone.
void startAp() {
  WiFi.softAP(ssidCurrent(), nullptr, 1, false, CFG_MAX_CLIENTS);
  logEvent(EV_SSID, 0, ssidHash(ssidCurrent()), 0);
  Serial.printf("AP \"%s\" up at %s\n", ssidCurrent(), AP_IP.toString().c_str());
}

uint32_t apRestartAt = 0;  // deferred so the admin's reply gets out before the AP drops

uint32_t clientVisitor() {
  IPAddress ip = server.client().remoteIP();
  uint32_t v = 0;
  for (station_info *s = wifi_softap_get_station_info(); s; s = STAILQ_NEXT(s, next)) {
    if (IPAddress(s->ip.addr) == ip) {
      v = visitorId(s->bssid);
      break;
    }
  }
  wifi_softap_free_station_info();
  return v;
}

uint32_t argU32(const char *name) {
  return strtoul(server.arg(name).c_str(), nullptr, 10);
}

void handleRoot() {
  logRequest("portal");
  server.send_P(200, "text/html; charset=utf-8", PORTAL_HTML);
}

// "connections,clicks" — the page shows these as the real counters.
void handleCount() {
  char buf[16];
  snprintf(buf, sizeof(buf), "%u,%u", readConnections(), clicks);
  server.send(200, "text/plain", buf);
}

// Beacon fired by the page when a contact link is copied.
void handleClick() {
  clicks++;
  markDirty();
  logEvent(EV_CLICK, argU32("l"), 0, clientVisitor());
  server.send(204, "text/plain", "");
}

// Sent by the page on load: the phone's clock is the badge's only time source.
void handleHi() {
  logEvent(EV_VIEW, argU32("d"), argU32("t"), clientVisitor());
  server.send(204, "text/plain", "");
}

void handleBye() {
  logEvent(EV_LEAVE, 0, argU32("s"), clientVisitor());
  server.send(204, "text/plain", "");
}

// The admin page itself is public and holds no data; only the data endpoints
// check the key.
bool adminOk() {
  if (server.header("X-Key") == ADMIN_KEY) return true;
  server.send(401, "text/plain", "bad key");
  return false;
}

void handleAdmin() {
  server.send_P(200, "text/html; charset=utf-8", ADMIN_HTML);
}

// Raw log plus "boot,uptime_ms,connections,clicks,requester,full" in a header,
// so the page can date the current boot from its own clock and hide its owner.
void handleAdminLog() {
  if (!adminOk()) return;
  logFlush(true);
  char meta[64];
  snprintf(meta, sizeof(meta), "%u,%lu,%u,%u,%lu,%u", logBoot(), (unsigned long)millis(),
           readConnections(), clicks, (unsigned long)clientVisitor(), logFull());
  server.sendHeader("X-Badge", meta);
  server.sendHeader("Cache-Control", "no-store");
  File f = LittleFS.open(LOG_PATH, "r");
  if (f) server.streamFile(f, "application/octet-stream");
  else server.send(200, "application/octet-stream", "");
}

void handleAdminWifi() {
  if (!adminOk()) return;
  if (server.method() == HTTP_POST) {
    int r = ssidSetConfig(server.arg("plain"));
    if (r < 0) {
      server.send(400, "text/plain", "no name");
      return;
    }
    if (r > 0) apRestartAt = millis() + 1500;
  }
  server.send(200, "text/plain; charset=utf-8", ssidConfigText());
}

void handleAdminReset() {
  if (!adminOk()) return;
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "POST only");
    return;
  }
  logReset();
  noInterrupts();
  connections = 0;
  interrupts();
  clicks = 0;
  saveStats();
  drawResting(screen);
  server.send(204, "text/plain", "");
}

// OS captive-portal probes expect their own success response (Android wants
// HTTP 204, iOS wants the word "Success"). Serving the portal HTML with 200
// instead is what makes the phone decide it is behind a portal and pop the
// page open on its own, rather than just showing a silent "no internet".
void handleCaptive() {
  logRequest("portal (probe)");
  server.send_P(200, "text/html; charset=utf-8", PORTAL_HTML);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  EEPROM.begin(sizeof(Stats));
  loadStats();
  logBegin();
  ssidBegin();

  Wire.begin();
  syncLcd();
  if (lcdReady) {
    printLine(0, "EventBadge");
    printLine(1, "demarrage...");
  }

  // The SDK otherwise rewrites its config sector on every softAP() call,
  // which the name rotation would turn into steady flash wear.
  WiFi.persistent(false);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(AP_IP, AP_IP, IPAddress(255, 255, 255, 0));
  startAp();

  onConnect = WiFi.onSoftAPModeStationConnected(
    [](const WiFiEventSoftAPModeStationConnected &e) {
      connections++;
      alertPending = true;
      markDirty();
      logEvent(EV_CONNECT, e.aid, 0, visitorId(e.mac));
    });
  onDisconnect = WiFi.onSoftAPModeStationDisconnected(
    [](const WiFiEventSoftAPModeStationDisconnected &e) {
      logEvent(EV_DISCONNECT, e.aid, 0, visitorId(e.mac));
    });

  dns.setErrorReplyCode(DNSReplyCode::NoError);
  dns.start(53, "*", AP_IP);

  server.collectHeaders("User-Agent", "X-Key");
  server.on("/", handleRoot);
  server.on("/count", handleCount);
  server.on("/click", handleClick);
  server.on("/hi", handleHi);
  server.on("/bye", handleBye);
  server.on("/admin", handleAdmin);
  server.on("/admin/log.bin", handleAdminLog);
  server.on("/admin/reset", handleAdminReset);
  server.on("/admin/wifi", handleAdminWifi);
  // Common captive-portal detection URLs across platforms.
  server.on("/generate_204", handleCaptive);
  server.on("/gen_204", handleCaptive);
  server.on("/hotspot-detect.html", handleCaptive);
  server.on("/ncsi.txt", handleCaptive);
  server.onNotFound(handleCaptive);
  server.begin();

  screen = 0;
  drawResting(screen);
  screenAt = lcdCheckAt = millis();
}

void loop() {
  dns.processNextRequest();
  server.handleClient();

  uint32_t now = millis();

  if (now - lcdCheckAt >= LCD_CHECK_MS) {
    lcdCheckAt = now;
    bool wasReady = lcdReady;
    syncLcd();
    if (lcdReady && !wasReady) alertUntil ? drawAlert() : drawResting(screen);
  }

  logFlush();

  if (apRestartAt && (int32_t)(now - apRestartAt) >= 0) {
    apRestartAt = 0;
    startAp();
  } else if (ssidTick(WiFi.softAPgetStationNum())) {
    startAp();
  }

  // Persist the counts a few seconds after the last change (limits flash wear).
  if (statsDirty && now - statsChangedAt >= SAVE_AFTER_MS) {
    statsDirty = false;
    saveStats();
  }

  if (alertPending) {
    alertPending = false;
    alertUntil = now + ALERT_MS;
    flashAt = now;
    drawAlert();
  }

  if (alertUntil) {
    if (now - flashAt >= FLASH_MS) {
      flashAt = now;
      backlightOn = !backlightOn;
      if (lcdReady) backlightOn ? lcd.backlight() : lcd.noBacklight();
    }
    if (now >= alertUntil) {
      alertUntil = 0;
      if (!backlightOn) {
        backlightOn = true;
        if (lcdReady) lcd.backlight();
      }
      screenAt = now;
      drawResting(screen);
    }
    return;  // hold the alert; resting rotation resumes after it
  }

  if (now - screenAt >= SCREEN_MS) {
    screen = (screen + 1) % 4;
    screenAt = now;
    drawResting(screen);
  }
}
