#include "WifiNames.h"
#include <LittleFS.h>
#include "config.h"

static const char CFG_PATH[] = "/wifi.txt";
static const char *const DEFAULT_NAMES[] = { CFG_SSIDS };

static char names[SSID_MAX_NAMES][33];  // 32 bytes is the 802.11 SSID limit
static uint8_t count = 0;
static uint8_t current = 0;
static SsidMode mode = SSID_FIXED;
static uint16_t everyMin = 15;
static bool waitEmpty = true;
static uint32_t changedAt = 0;

struct Parsed {
  char names[SSID_MAX_NAMES][33];
  uint8_t count = 0;
  SsidMode mode = SSID_FIXED;
  uint16_t everyMin = 15;
  bool waitEmpty = true;
};

// "key=value" lines: mode=fixed|seq|random, every=<minutes>, wait=0|1 and one
// ssid=<name> per name. Unknown keys are ignored.
static bool parse(const String &text, Parsed &p) {
  int start = 0;
  while (start < (int)text.length()) {
    int end = text.indexOf('\n', start);
    if (end < 0) end = text.length();
    String line = text.substring(start, end);
    start = end + 1;
    line.trim();
    int eq = line.indexOf('=');
    if (eq < 0) continue;
    String key = line.substring(0, eq), val = line.substring(eq + 1);
    val.trim();
    if (key == "mode") p.mode = val == "seq" ? SSID_SEQ : val == "random" ? SSID_RANDOM : SSID_FIXED;
    else if (key == "every") p.everyMin = constrain(val.toInt(), 1, 1440);
    else if (key == "wait") p.waitEmpty = val != "0";
    else if (key == "ssid" && val.length() && p.count < SSID_MAX_NAMES) {
      strncpy(p.names[p.count], val.c_str(), 32);
      p.names[p.count][32] = '\0';
      p.count++;
    }
  }
  return p.count > 0;
}

static void apply(const Parsed &p) {
  memcpy(names, p.names, sizeof(names));
  count = p.count;
  mode = p.mode;
  everyMin = p.everyMin;
  waitEmpty = p.waitEmpty;
}

static uint8_t pick() {
  if (mode == SSID_RANDOM && count > 1) return (current + 1 + random(count - 1)) % count;
  if (mode == SSID_SEQ) return (current + 1) % count;
  return 0;
}

void ssidBegin() {
  Parsed p;
  File f = LittleFS.open(CFG_PATH, "r");
  bool ok = f && parse(f.readString(), p);
  f.close();
  if (!ok) {
    p = Parsed();
    for (const char *n : DEFAULT_NAMES) {
      if (p.count == SSID_MAX_NAMES) break;
      strncpy(p.names[p.count], n, 32);
      p.names[p.count++][32] = '\0';
    }
  }
  apply(p);
  randomSeed(RANDOM_REG32);
  current = mode == SSID_RANDOM ? random(count) : 0;
  changedAt = millis();
}

const char *ssidCurrent() { return names[current]; }

bool ssidTick(uint8_t stations) {
  if (mode == SSID_FIXED || count < 2) return false;
  if (millis() - changedAt < everyMin * 60000UL) return false;
  if (waitEmpty && stations) return false;
  current = pick();
  changedAt = millis();
  return true;
}

String ssidConfigText() {
  String s;
  s += F("mode=");
  s += mode == SSID_SEQ ? F("seq") : mode == SSID_RANDOM ? F("random") : F("fixed");
  s += F("\nevery=");
  s += everyMin;
  s += F("\nwait=");
  s += waitEmpty ? '1' : '0';
  s += F("\ncurrent=");
  s += names[current];
  for (uint8_t i = 0; i < count; i++) {
    s += F("\nssid=");
    s += names[i];
  }
  return s;
}

int ssidSetConfig(const String &text) {
  Parsed p;
  if (!parse(text, p)) return -1;
  String before = names[current];
  apply(p);
  // Keep the running name when it is still listed, so saving other settings
  // does not drop connected visitors; fixed mode always means the first name.
  current = 0;
  if (mode != SSID_FIXED)
    for (uint8_t i = 0; i < count; i++)
      if (before == names[i]) current = i;
  changedAt = millis();

  File f = LittleFS.open(CFG_PATH, "w");
  if (f) {
    String saved = ssidConfigText();
    f.print(saved);
  }
  f.close();
  return before != names[current];
}

// The rotation timer restarts from a manual pick, so it is not overridden at once.
int ssidUse(const String &name) {
  for (uint8_t i = 0; i < count; i++) {
    if (name != names[i]) continue;
    bool changed = i != current;
    current = i;
    changedAt = millis();
    return changed;
  }
  return -1;
}

// Plain FNV-1a; the admin page computes the same hash to put names back on the
// logged SSID changes.
uint32_t ssidHash(const char *name) {
  uint32_t h = 2166136261u;
  while (*name) h = (h ^ (uint8_t)*name++) * 16777619u;
  return h;
}
