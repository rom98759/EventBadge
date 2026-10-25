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

## Redesign (2026-10-25, v3)

- **Tone:** funny and friendly, not scary. Dev-crowd humor. The trap SSID is
  the joke; the counter is "curieux" (curious visitors), not "pieges".
- **LCD:** mix of clean identity (dir 1) + terminal flavor (dir 2): honeypot
  gag screen, name/role, terminal "etudiant 42", alternance juin 2027.
- **Portal:** C's bold/funny tone + B's card/info display + A's prominent
  "who I am / what I can do" with skills. More browser-reveal infos, each with
  a short witty aside. No "add contact" button: plain links instead
  (github / linkedin / site / email). Keep it simple, few elements.

## Final direction (2026-10-25, v4 — SHIPPED)

- **Chosen:** retro **Windows 95** desktop portal. A `piege.exe` window:
  a ⚠ warning dialog ("Vous êtes tombé dans le piège"), then a prominent
  "Qui suis-je" card (pixel-art avatar, name, role, a yellow highlight box
  with the alternance in red + a blinking NEW! badge), a 90s marquee, the
  Contact links, and the browser diagnostic demoted to the bottom
  ("Au passage, détecté sur vous"). Taskbar with Start menu + clock.
- **Palette:** Win95 — teal desktop #007a7a, grey #c0c0c0 3D bevels, navy
  title bars, yellow highlight, red for the key alternance words.
- **Fonts:** system only (Tahoma / MS Sans Serif) — the portal is served
  offline, so no web font loads.
- **Easter eggs:** Fichier/Édition dropdowns, ? → "À propos" dialog, OK →
  dismiss + counter, × / Quitter / Arrêter → fake BSOD, Démarrer menu.
- **Avatar:** the user's pixel-art maker profile picture, embedded.
- **Rejected on the way here:** editorial red/white incident report,
  technical-drawing (exploded / cross-section / patent), neon/glitch, and the
  earlier card/terminal honeypot layouts — all felt generic or "AI slop".
- **Source:** `web/index.html`; `web/build.py` embeds it into `portal.h`.

## Guardrails (part of the design, not optional)

- The SSID openly says it is a trap/demo; never mimic a real network
  (venue, operator, brand).
- No credential, form or login page of any kind.
- Device details are computed by JavaScript in the visitor's browser and
  shown only to them: nothing is sent to, logged or stored on the ESP.
- The LCD shows only an anonymous count of connections, never MAC
  addresses, device names or other identifiers.
- The page states plainly that nothing is collected and how to disconnect.
