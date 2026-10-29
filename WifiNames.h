#pragma once
#include <Arduino.h>

// The hotspot name, picked from a list edited on the admin page: fixed (the
// first name), in turn or at random every few minutes.
enum SsidMode : uint8_t { SSID_FIXED, SSID_SEQ, SSID_RANDOM };

const uint8_t SSID_MAX_NAMES = 16;

void ssidBegin();
const char *ssidCurrent();
// True when the name should change now; the new one is already current.
bool ssidTick(uint8_t stations);
String ssidConfigText();
// -1 = rejected, 0 = saved with the same current name, 1 = saved and the name changed.
int ssidSetConfig(const String &text);
uint32_t ssidHash(const char *name);
