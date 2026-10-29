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
- The browser diagnostic box is computed in the visitor's browser and shown
  only to them. Since 2026-10-29 the badge does keep visit stats (time,
  OS/browser family, link copied, time on page, a salted MAC hash): the page
  must therefore never claim that nothing is collected. The "rien n'est
  conservé" / "rien n'est envoyé" sentences were removed, not replaced
  (user's choice).
- The LCD shows only counts and the hotspot name, never MAC addresses,
  device names or other identifiers.

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

## LCD v2 (2026-10-29)

- **Chosen:** A "Fenêtre propre". Same night-blue LCD, five screens in
  rotation: "CONNECTE-TOI" + the current hotspot name scrolling back and
  forth (pause at each end), name/role, "Etudiant 42 / stage pentest",
  ALTERNANCE / des juin 2027, stats (curieux + liens copiés, zero-padded,
  right column). "+1 CURIEUX !" alert with backlight flash kept.
- **Rule:** columns 0 and 15 hold glyphs only; text lives in the 14 middle
  columns, centered. Fixes glyphs overwriting letters ("P☠EGE A CURIEU☠")
  and the one left-aligned screen.
- **Rejected:** B "Téléscripteur" (fixed top row + continuous ticker),
  C "Clippy parle" (2×2 Clippy face typing in a speech bubble), and any
  "sac jaune" text on the LCD ("c'est nul").
- Mock-ups: artifact "EventBadge LCD directions".

## Contact card (2026-10-29)

- Links cannot leave the captive portal (Android's portal window keeps
  http(s) links in its own Wi-Fi-bound WebView; iOS stopped opening Safari
  years ago) and the badge has no internet. Visitors who only copy a link
  tend to forget it.
- **Added**, next to (not instead of) the copy buttons: an explicit
  "Télécharger mon contact" button, labelled as a 1 KB .vcf text file so it
  does not look like a suspicious download on a "trap" network. This revisits
  the earlier "no add contact button" choice at the user's request.
- **Rejected:** a .txt file (ends up unread in Downloads), validating the
  network to redirect into the real browser (Android just closes the portal,
  and the phone loses its 4G while connected).
