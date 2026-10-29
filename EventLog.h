#pragma once
#include <Arduino.h>

// Visitor activity, appended to a flash file as fixed 16-byte records. The
// admin page downloads the raw file and does all decoding and maths itself,
// so the badge only ever appends.
enum EventType : uint8_t {
  EV_BOOT = 1,
  EV_CONNECT,     // arg: AP association id
  EV_DISCONNECT,
  EV_VIEW,        // arg: device code (os << 4 | browser), data: phone clock (epoch s)
  EV_CLICK,       // arg: link code
  EV_LEAVE,       // data: seconds spent on the page
  EV_SSID,        // data: ssidHash() of the hotspot name now in use
};

struct __attribute__((packed)) LogRecord {
  uint16_t boot;
  uint8_t type;
  uint8_t arg;
  uint32_t ms;       // millis() at the event: the badge has no clock of its own
  uint32_t data;
  uint32_t visitor;  // salted hash of the MAC, 0 = unknown
};
static_assert(sizeof(LogRecord) == 16, "the admin page parses 16-byte records");

extern const char LOG_PATH[];

void logBegin();
void logEvent(EventType type, uint8_t arg, uint32_t data, uint32_t visitor);
void logFlush(bool force = false);
void logReset();
uint16_t logBoot();
bool logFull();
uint32_t visitorId(const uint8_t mac[6]);
