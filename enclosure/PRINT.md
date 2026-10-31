# Printing and assembly

Ready-to-print STL files, already oriented, are in the
[`enclosure-v1` release](https://github.com/rom98759/EventBadge/releases/tag/enclosure-v1)
(or in `stl/` after running the scripts). Tested on a Creality Ender 3 V3 SE,
0.4 mm nozzle, PLA, 0.2 mm layers.

| Part | File | Orientation | Size (mm) | Colour |
|---|---|---|---|---|
| Front | `V2_Skin.stl` | face up | 100 × 78 × 4.4 | filament changes (below) |
| Shell | `V2_Tub.stl` | back on the bed | 103 × 78 × 31 | white |
| USB lock | `V2_Gate.stl` | flat | 20 × 17 × 4 | navy |
| Strap clip (×1 or ×2, glued on the back) | `V2_Strap_Clip.stl` | lying on its side | 11 × 40 × 20 | any |
| **Test** USB corner | `V2_TEST_coin_USB.stl` | back on the bed | 63 × 31 × 31 | any |

Suggested order: 1) `V2_TEST_coin_USB` + `V2_Gate` (plug hole and lock),
2) `V2_Skin` (LCD in the window, colours), 3) `V2_Tub` (the longest print).
No supports needed.

## Front: filament changes (0.2 mm layers)

| Height | Filament | What shows |
|---|---|---|
| 0 – 2.0 mm | white | plate, `piege.exe` and the buttons (cut through the navy) |
| 2.0 – 2.8 mm | navy | title bar |
| 2.8 – 3.8 mm | pink | Clippy |
| 3.8 – 4.4 mm | white | eyes (pupils are holes) |

In the slicer (Creality Print / Orca / Cura): colour change / M600 pause at the
layers starting at **2.0 / 2.8 / 3.8 mm**.

## Front variant: inlays (no filament change)

`stl/facade_marqueterie/`: pieces glued into 0.6 mm pockets (0.15 mm clearance per
side), all printed flat, face up.

| Piece | File | Size (mm) | Filament |
|---|---|---|---|
| Plate | `V2_Facade_Plate.stl` | 100 × 78 × 2.8 | white (raised _ □ × buttons, engraved symbols) |
| Title bar | `V2_Facade_Bar.stl` | 95 × 11 × 1.4 | navy |
| Clippy | `V2_Facade_Clippy.stl` | 13 × 28 × 1.6 | pink |
| Eyes | `V2_Facade_Eyes.stl` | 2 × Ø 5 × 0.8 | white |

- `piege.exe` is engraved 1 mm deep in the title bar (0.4 mm floor, otherwise the
  inside of the letters would fall out): either change white → navy at **0.4 mm**
  on that piece, or fill the letters with a white paint marker.
- Title bar: **no ironing** (it drags plastic into the engraved letters); enable
  "avoid crossing walls", outer wall at 30–40 mm/s.
- Pupils: recesses in the eyes, fill them with a black marker.
- Dry-fit first; if a piece is tight, sand its edge. Glue with small dots of CA
  (super glue) or contact glue.

## Hardware

- 4 brass heat-set inserts M3 × 4 (Ø 4.1 hole) in the shell bosses.
- 4 countersunk M3 screws, 6–8 mm, from the front.
- Standard keyring through the window icon (Ø 4.8 hole).
- Bag: `V2_Strap_Clip`, belt-style clip glued on the back (2-part epoxy), opening
  downwards; pinches a 40 × 5 mm strap (3.5 mm gap, `PINCH` in `strap_clip.py`).

## Assembly

1. LCD against the front: its metal frame bears on the window edge, and the 4 posts
   of the shell press on the PCB with their pins in its mounting holes.
2. Wemos loose in the box (anywhere the USB plug reaches it; hot glue if needed).
3. Close with the 4 screws. Plug the cable through the hole in the right side, then
   slide the lock into its rails (slot facing forward) until it stops.

## Measured parts (in `scripts/enclosure.py`)

- LCD1602: PCB 80.2 × 35.8, metal frame 70.9 × 24.5 × 6.3 mm, frame 8 mm below the
  PCB top; holes 1.4 mm from the edges, Ø 2.0 pins centred 2.75 mm from the edges.
- Wemos D1 mini 33.7 × 25.1 × 11.5 mm with headers; micro-USB overmold 10 × 6 × 21 mm.
- Lock / rails clearance: 0.4 mm in thickness, 0.5 mm per side in height
  (`GATE_CH`, `GATE_T`, `GATE_CLR`).
