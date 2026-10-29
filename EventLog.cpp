#include "EventLog.h"
#include <LittleFS.h>

const char LOG_PATH[] = "/events.bin";
static const char BOOT_PATH[] = "/boot";
// ~65k events: weeks of conference days, well inside the 2 MB filesystem.
static const size_t LOG_MAX_BYTES = 1024UL * 1024;
static const uint32_t FLUSH_MS = 3000;  // batch appends to limit flash wear

// Events also come from WiFi callbacks, so they are queued and written from
// loop(); a full queue drops events rather than blocking the portal.
static const uint8_t QUEUE_LEN = 32;
static LogRecord queue[QUEUE_LEN];
static volatile uint8_t head = 0, tail = 0;
static uint16_t boot = 0;
static bool fsOk = false;
static bool full = false;
static uint32_t flushedAt = 0;

void logBegin() {
  fsOk = LittleFS.begin();
  if (!fsOk) {
    Serial.println(F("log: filesystem unavailable, logging off"));
    return;
  }
  File b = LittleFS.open(BOOT_PATH, "r");
  if (b) b.read((uint8_t *)&boot, sizeof(boot));
  b.close();
  boot++;
  b = LittleFS.open(BOOT_PATH, "w");
  if (b) b.write((const uint8_t *)&boot, sizeof(boot));
  b.close();

  File f = LittleFS.open(LOG_PATH, "r");
  full = f && f.size() + sizeof(LogRecord) > LOG_MAX_BYTES;
  f.close();
  logEvent(EV_BOOT, 0, 0, 0);
  Serial.printf("log: boot %u%s\n", boot, full ? ", log full" : "");
}

void logEvent(EventType type, uint8_t arg, uint32_t data, uint32_t visitor) {
  noInterrupts();
  uint8_t next = (head + 1) % QUEUE_LEN;
  if (next != tail) {
    queue[head] = { boot, type, arg, millis(), data, visitor };
    head = next;
  }
  interrupts();
}

void logFlush(bool force) {
  if (head == tail) return;
  uint32_t now = millis();
  if (!force && now - flushedAt < FLUSH_MS) return;
  flushedAt = now;

  File f;
  if (fsOk && !full) f = LittleFS.open(LOG_PATH, "a");
  while (tail != head) {
    if (f) {
      if (f.size() + sizeof(LogRecord) > LOG_MAX_BYTES) full = true;
      else f.write((const uint8_t *)&queue[tail], sizeof(LogRecord));
    }
    tail = (tail + 1) % QUEUE_LEN;
  }
  f.close();
}

void logReset() {
  tail = head;
  if (fsOk) LittleFS.remove(LOG_PATH);
  full = false;
}

uint16_t logBoot() { return boot; }
bool logFull() { return full; }

// FNV-1a salted with the chip id, so the log holds a per-badge id rather than
// the MAC itself. Phones use a stable random MAC per network, which is enough
// to tell visitors apart and spot the ones who come back.
uint32_t visitorId(const uint8_t mac[6]) {
  uint32_t h = 2166136261u ^ ESP.getChipId();
  for (uint8_t i = 0; i < 6; i++) h = (h ^ mac[i]) * 16777619u;
  return h ? h : 1;
}
