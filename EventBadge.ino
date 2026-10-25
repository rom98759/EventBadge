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

enum Glyph : uint8_t { SKULL, WIFI, DOT, CHIP };

uint8_t glyphs[][8] = {
  {0b01110, 0b11111, 0b10101, 0b11111, 0b10101, 0b01110, 0b01010, 0b00000},  // skull
  {0b00000, 0b10000, 0b10100, 0b10101, 0b10101, 0b10101, 0b00000, 0b00000},  // wifi bars
  {0b00000, 0b00000, 0b00110, 0b01111, 0b01111, 0b00110, 0b00000, 0b00000},  // middle dot
  {0b00000, 0b01110, 0b10001, 0b10101, 0b10001, 0b01110, 0b00000, 0b00000},  // chip
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

void drawResting(uint8_t which) {
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
  lcd.clear();
  printCentered(0, "+1 CURIEUX !");
  putGlyph(1, 0, WIFI);
  putGlyph(14, 0, WIFI);
  printCentered(1, "bienvenue a toi");
}

void handleRoot() {
  server.send_P(200, "text/html; charset=utf-8", PORTAL_HTML);
}

// OS captive-portal probes expect their own success response (Android wants
// HTTP 204, iOS wants the word "Success"). Serving the portal HTML with 200
// instead is what makes the phone decide it is behind a portal and pop the
// page open on its own, rather than just showing a silent "no internet".
void handleCaptive() {
  server.send_P(200, "text/html; charset=utf-8", PORTAL_HTML);
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
    screen = (screen + 1) % 4;
    screenAt = now;
    drawResting(screen);
  }
}
