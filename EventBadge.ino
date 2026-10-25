#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#include "config.h"
#include "portal.h"

const IPAddress AP_IP(192, 168, 4, 1);
const uint32_t SCREEN_MS = 4500;   // time on each resting screen
const uint32_t ALERT_MS = 3000;    // time the "new connection" alert stays up
const uint32_t FLASH_MS = 160;     // backlight blink half-period during an alert

hd44780_I2Cexp lcd;
DNSServer dns;
ESP8266WebServer server(80);
WiFiEventHandler onConnect;

enum Glyph : uint8_t { SKULL, WIFI, ARROW };

uint8_t glyphs[][8] = {
  {0b01110, 0b11111, 0b10101, 0b11111, 0b01110, 0b01010, 0b00000, 0b00000},  // skull
  {0b00000, 0b00001, 0b00011, 0b00111, 0b01111, 0b11111, 0b00000, 0b00000},  // wifi bars
  {0b00100, 0b01110, 0b11111, 0b00100, 0b00100, 0b00100, 0b00100, 0b00000},  // up arrow
};

// Only an anonymous count. Set from the AP connect event (ISR-like context),
// so it is volatile and read with interrupts briefly disabled.
volatile uint16_t connections = 0;

uint8_t screen = 0;
uint32_t screenAt = 0;
uint32_t alertUntil = 0;
uint32_t flashAt = 0;
bool backlightOn = true;
bool alertPending = false;

void printLine(uint8_t row, const char *text) {
  char buf[17];
  snprintf(buf, sizeof(buf), "%-16s", text);
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

void drawResting(uint8_t which) {
  lcd.clear();
  char buf[17];
  switch (which) {
    case 0:
      printLine(0, " HONEYPOT ACTIF");
      putGlyph(0, 0, SKULL);
      snprintf(buf, sizeof(buf), "  pieges: %u", readConnections());
      printLine(1, buf);
      putGlyph(0, 1, WIFI);
      break;
    case 1:
      printLine(0, CFG_NAME);
      printLine(1, CFG_ROLE);
      break;
    case 2:
      printLine(0, CFG_SCHOOL);
      printLine(1, "cherche alternance");
      break;
  }
}

void drawAlert() {
  lcd.clear();
  printLine(0, " CIBLE +1 !");
  putGlyph(0, 0, ARROW);
  char buf[17];
  snprintf(buf, sizeof(buf), "  total: %u", readConnections());
  printLine(1, buf);
}

void handleRoot() {
  server.send_P(200, "text/html; charset=utf-8", PORTAL_HTML);
}

void handleVcf() {
  server.sendHeader("Content-Disposition", "attachment; filename=\"" CFG_NAME ".vcf\"");
  server.send_P(200, "text/vcard; charset=utf-8", PORTAL_VCF);
}

// Captive-portal probes (and anything else) get redirected to the portal so
// the page pops up on its own.
void handleCaptive() {
  server.sendHeader("Location", "http://192.168.4.1/", true);
  server.send(302, "text/plain", "");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  int status = lcd.begin(16, 2);
  if (status) hd44780::fatalError(status);
  for (uint8_t i = 0; i < 3; i++) lcd.createChar(i, glyphs[i]);
  printLine(0, "EventBadge");
  printLine(1, "demarrage...");

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(AP_IP, AP_IP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(CFG_SSID, nullptr, 1, false, CFG_MAX_CLIENTS);

  onConnect = WiFi.onSoftAPModeStationConnected(
    [](const WiFiEventSoftAPModeStationConnected &) {
      connections++;
      alertPending = true;
    });

  dns.setErrorReplyCode(DNSReplyCode::NoError);
  dns.start(53, "*", AP_IP);

  server.on("/", handleRoot);
  server.on("/contact.vcf", handleVcf);
  // Common captive-portal detection URLs across platforms.
  server.on("/generate_204", handleCaptive);
  server.on("/gen_204", handleCaptive);
  server.on("/hotspot-detect.html", handleCaptive);
  server.on("/ncsi.txt", handleCaptive);
  server.onNotFound(handleCaptive);
  server.begin();

  screen = 0;
  drawResting(screen);
  screenAt = millis();

  Serial.printf("AP \"%s\" up at %s\n", CFG_SSID, AP_IP.toString().c_str());
}

void loop() {
  dns.processNextRequest();
  server.handleClient();

  uint32_t now = millis();

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
      backlightOn ? lcd.backlight() : lcd.noBacklight();
    }
    if (now >= alertUntil) {
      alertUntil = 0;
      if (!backlightOn) { lcd.backlight(); backlightOn = true; }
      screenAt = now;
      drawResting(screen);
    }
    return;  // hold the alert; resting rotation resumes after it
  }

  if (now - screenAt >= SCREEN_MS) {
    screen = (screen + 1) % 3;
    screenAt = now;
    drawResting(screen);
  }
}
