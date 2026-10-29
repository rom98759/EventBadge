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

## Enclosure (2026-10-25)

- **Use:** keychain on the bag strap; power bank stays in the bag, micro-USB
  cable to the badge. LCD + Wemos in the box, Dupont wires kept (box ~35 mm
  thick because of the straight plugs on the Wemos).
- **Chosen:** A "Fenêtre" — the box is a Win95 window: navy title bar
  `piege.exe` with _ □ × buttons, LCD as the window content, vent slots over
  the Wemos, white LED slit on the right side. Plus Clippy (the user loves
  it) in relief on the front (V2, chosen): pink paperclip with white eyes,
  bottom-left of the window, no size added (104×78×35 mm).
- **Print strategy (single-extruder Ender 3 V3 SE):** few parts. Front skin
  either printed face up with filament changes at layer heights (white base →
  navy title bar → pink/white for Clippy), or as inlays glued into 0.6 mm
  pockets (plate, title bar, Clippy, eyes); one-colour tub printed back down;
  M3x4 heat inserts.
- **LCD:** clamped between the skin (the metal frame bears on the window
  edge, frame hidden 0.5 mm left/right, 1.5 mm top/bottom) and four posts
  from the back with pins in the PCB holes. Measured: PCB 80.2×35.8, frame
  70.9×24.5×6.3, frame 8 mm below the PCB top.
- **USB:** cable must plug/unplug from outside and be locked: the overmold
  goes through a hole in the right side and a sliding gate in rails holds it.
- **Wemos:** left loose in the box (user's choice, hot glue if needed); the
  cradle, stops and inner tunnel were removed after test prints.
- **Bag:** belt-style clip(s) glued on the back, open downwards, pinching a
  40×5 mm bag strap.
- **Rejected:** V1 Clippy standing on the roof holding the keyring (126 mm
  tall, fragile), B floppy (100×100, liked but less than A), C full Clippy
  bubble (loved, too big at 126×93), web-page mock-ups instead of CAD views,
  a full back plate with a strap tunnel (too bulky), double-sided tape.
- **CAD source:** `~/Documents/FreeCAD/EventBadge/` (`build_fenetre_clippy.py`).
