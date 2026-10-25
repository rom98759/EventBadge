# Design choices

## Event badge identity (2026-10-25)

- **Chosen:** C "Honeypot" for the Wi-Fi and captive portal: self-declared
  trap SSID, the page shows visitors what their own browser already exposes,
  then introduces me (pentest intern, looking for an apprenticeship).
  Palette: LCD night blue, white, amber alert. Font: VT323.
- **LCD:** alternates the honeypot screens (visitor counter, skull glyph)
  with who I am (name, role, 42 Angoulême, apprenticeship search).
- **Not chosen:** A "Business card" (clean but forgettable); B "Datasheet"
  (person as an electronic component: kept as a possible print/CV idea).

## Guardrails (part of the design, not optional)

- The SSID openly says it is a trap/demo; never mimic a real network
  (venue, operator, brand).
- No credential, form or login page of any kind.
- Device details are computed by JavaScript in the visitor's browser and
  shown only to them: nothing is sent to, logged or stored on the ESP.
- The LCD shows only an anonymous count of connections, never MAC
  addresses, device names or other identifiers.
- The page states plainly that nothing is collected and how to disconnect.
