# EventBadge "Fenetre" enclosure, printable on a single-extruder printer.
# Parts: Skin (front plate, printed face up, colours by filament change at layer
# heights), Tub (sides + back + inner supports, printed back down), Gate (sliding
# USB lock), and for V1 a Clippy that holds the keyring.
# Run inside FreeCAD: exec(open("/home/romain/Documents/FreeCAD/EventBadge/scripts/enclosure.py").read())
# Axes: X = width, Z = height, Y = depth (y=0 is the back face of the skin,
# visitors look from -Y).
import os
import FreeCAD as App
import FreeCADGui as Gui
import Part
from FreeCAD import Vector as V

DOC = "EventBadge_Fenetre"
ROOT = "/home/romain/Documents/FreeCAD/EventBadge"
STL_DIR = os.path.join(ROOT, "stl")
CAD_DIR = os.path.join(ROOT, "cad")
FONT = "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"

T = 2.0                    # wall / skin thickness
W, D, H = 96.0, 29.0, 74.0  # inner cavity
LCD_X, LCD_Z = 14.0, 28.5
LCD_L, LCD_H = 80.2, 35.8     # PCB, measured
BEZ_L, BEZ_H = 70.9, 24.5     # metal frame, measured
BEZ_T = 6.3                   # frame front -> PCB front, measured
BEZ_X = (LCD_L - BEZ_L) / 2
BEZ_Z = LCD_H - 8.0 - BEZ_H   # frame top is 8 mm below the PCB top
LCD_HOLE = 2.75               # hole centre from the PCB edges (1.4 mm to the rim)
LCD_HX = (LCD_HOLE, LCD_L - LCD_HOLE)
LCD_HZ = (LCD_HOLE, LCD_H - LCD_HOLE)
PCB_Y = BEZ_T
PCB_B = PCB_Y + 1.6
WEM_L, WEM_W = 33.7, 25.1
WEM_Z = 1.0
WEM_YB = 6.0               # illustrative only: the Wemos sits loose in the box
PLUG_L = 21.0              # micro-B overmold + strain relief, measured
PLUG_W, PLUG_T = 10.0, 6.0  # overmold width (Z) x thickness (Y), measured
PLUG_CLR = 0.3             # clearance per side in the tunnel
VARIANTS = (("V2", 0.0, False),)   # V1 (Clippy on the roof) = ("V1", 0.0, True)
WEM_X = W + T - PLUG_L - 0.5 - WEM_L
ZC = WEM_Z + WEM_W / 2     # USB axis height
YC = 7.1                   # USB hole axis depth
BAND = 0.8                 # blue title-bar band on the skin
PINK = 1.0                 # Clippy relief band above the blue one
TITLE_Z = H - 12.5
SCREWS = [(3.0, 3.0), (W - 3.0, 3.0), (3.0, H - 3.0), (W - 3.0, H - 3.0)]
KEY = (10.0, H - 7.0)
GATE_CH, GATE_T = 2.4, 1.6  # rail channel depth / gate thickness: 0.4 mm play per side
GATE_CLR = 0.5             # gate height play per side in the rails

COL = {
    "white": (0.94, 0.94, 0.91), "black": (0.11, 0.11, 0.13), "blue": (0.12, 0.18, 0.43),
    "pink": (0.94, 0.50, 0.70), "pcb_g": (0.13, 0.42, 0.25), "pcb_b": (0.10, 0.36, 0.62),
    "pcb_w": (0.23, 0.24, 0.60), "metal": (0.78, 0.79, 0.82), "lcd": (0.18, 0.36, 1.0),
    "led": (1.0, 1.0, 1.0), "plug": (0.08, 0.08, 0.08), "w_y": (0.95, 0.85, 0.15),
    "w_b": (0.15, 0.35, 0.85), "w_k": (0.05, 0.05, 0.05), "w_p": (0.65, 0.55, 0.85),
    "grey": (0.70, 0.70, 0.68),
}


def box(x, y, z, dx, dy, dz):
    return Part.makeBox(dx, dy, dz, V(x, y, z))


def cyl_y(x, z, r, y0, length):
    return Part.makeCylinder(r, length, V(x, y0, z), V(0, 1, 0))


def cyl_x(y, z, r, x0, length):
    return Part.makeCylinder(r, length, V(x0, y, z), V(1, 0, 0))


def fuse_all(shapes):
    s = shapes[0]
    for o in shapes[1:]:
        s = s.fuse(o)
    return s


def text_solid(txt, size, x, z, y0, depth):
    """Extruded text lying in the XZ plane, readable from -Y."""
    faces = []
    for char in Part.makeWireString(txt, FONT, size, 0):
        outer = [w for w in char]
        if outer:
            faces.append(Part.Face(outer, "Part::FaceMakerBullseye"))
    sol = Part.Compound(faces).extrude(V(0, 0, depth))
    sol.rotate(V(0, 0, 0), V(1, 0, 0), 90)       # XY -> XZ, extrusion towards -Y
    sol.translate(V(x, y0, z))
    return sol


def clippy_path(x0, z0, s, y):
    """Paperclip centre line in the XZ plane, s = scale (1 -> 16 x 40 mm)."""
    P = lambda x, z: V(x0 + x * s, y, z0 + z * s)
    segs = [
        Part.LineSegment(P(0, 0), P(0, 32)),
        Part.Arc(P(0, 32), P(8, 40), P(16, 32)),
        Part.LineSegment(P(16, 32), P(16, 5)),
        Part.Arc(P(16, 5), P(11, 0), P(6, 5)),
        Part.LineSegment(P(6, 5), P(6, 27)),
    ]
    return Part.Wire([sg.toShape() for sg in segs])


def sausage(path, r, y0, depth):
    """Flat Clippy wire: the 2D offset of the path, extruded along Y."""
    flat = path.copy()
    flat.rotate(V(0, path.Vertexes[0].Point.y, 0), V(1, 0, 0), -90)   # XZ -> XY
    outline = flat.makeOffset2D(r, 0, False, False)
    sol = Part.Face(outline).extrude(V(0, 0, depth))
    sol.rotate(V(0, path.Vertexes[0].Point.y, 0), V(1, 0, 0), 90)
    sol.translate(V(0, y0 - sol.BoundBox.YMin, 0))
    return sol


# ---------------------------------------------------------------- components
def components():
    p = []
    pcb = box(LCD_X, PCB_Y, LCD_Z, LCD_L, 1.6, LCD_H)
    for dx in LCD_HX:
        for dz in LCD_HZ:
            pcb = pcb.cut(cyl_y(LCD_X + dx, LCD_Z + dz, 1.25, PCB_Y - 1, 4.0))
    p.append(("LCD_PCB", pcb, "pcb_g"))
    bx, bz = LCD_X + BEZ_X, LCD_Z + BEZ_Z
    p.append(("LCD_Bezel", box(bx, 0.0, bz, BEZ_L, BEZ_T, BEZ_H), "black"))
    p.append(("LCD_Screen", box(bx + (BEZ_L - 64.5) / 2, -0.05, bz + (BEZ_H - 16) / 2, 64.5, 0.3, 16), "lcd"))
    p.append(("LCD_Led", box(LCD_X + LCD_L - 4.6, PCB_Y - 2.6, bz + BEZ_H / 2 - 3, 3.0, 2.6, 6), "led"))
    p.append(("LCD_Header", box(LCD_X + 7, PCB_B, LCD_Z + LCD_H - 4.5, 40.6, 11.1 - PCB_B, 2.5), "black"))
    p.append(("I2C_PCB", box(LCD_X + 6, 11.1, LCD_Z + 16.4, 41.5, 1.6, 19.3), "pcb_b"))
    p.append(("I2C_Pot", box(LCD_X + 30, 12.7, LCD_Z + 20, 7, 4.4, 7), "w_b"))
    p.append(("I2C_Chip", box(LCD_X + 14, 12.7, LCD_Z + 22, 10, 1.6, 4), "black"))
    p.append(("I2C_Plugs", box(LCD_X - 8, 11.5, LCD_Z + 19.8, 14, 2.6, 10), "plug"))

    x = WEM_X
    p.append(("Wemos_PCB", box(x, WEM_YB, WEM_Z, WEM_L, 1.2, WEM_W), "pcb_w"))
    hy = WEM_YB + 1.2
    hl = 11.5 - 2.6 - 1.2
    p.append(("Wemos_HeaderTop", box(x + 4.5, hy, WEM_Z + WEM_W - 2.6, 20.3, hl, 2.5), "black"))
    p.append(("Wemos_HeaderBot", box(x + 4.5, hy, WEM_Z + 0.1, 20.3, hl, 2.5), "black"))
    p.append(("Wemos_Chip", box(x + 3, hy, WEM_Z + 8, 9, 1.2, 9), "black"))
    p.append(("Wemos_PinTips", box(x + 4.5, WEM_YB - 2.6, WEM_Z + 0.4, 20.3, 2.6, 1.0), "metal"))
    p.append(("Wemos_USB", box(x + WEM_L - 5.0, WEM_YB - 2.6, ZC - 3.75, 5.5, 2.6, 7.5), "metal"))
    p.append(("USB_Plug", box(W + T - PLUG_L, YC - PLUG_T / 2, ZC - PLUG_W / 2, PLUG_L, PLUG_T, PLUG_W), "plug"))
    p.append(("USB_Cable", cyl_x(YC, ZC, 2.0, W + T, 24), "plug"))
    zw = WEM_Z + WEM_W - 1.3
    xs = [x + WEM_L - 4.0 - 2.54 * i for i in (0, 1, 4, 5)]
    p.append(("Wemos_Plugs", fuse_all([box(xx - 1.25, hy + hl, zw - 1.25, 2.5, 14, 2.5)
                                       for xx in xs]), "plug"))
    y_end = hy + hl + 14
    for k, col in enumerate(("w_k", "w_p", "w_b", "w_y")):
        zl = LCD_Z + 19.8 + 1.25 + k * 2.54
        yk = 24.6 + k * 1.05
        pts = [V(LCD_X - 8, 12.8, zl), V(3.2, 13.8, zl), V(3.2, 23.0, zl - 9),
               V(26, yk, 36 - k), V(xs[k], yk, zw + 5), V(xs[k], y_end, zw)]
        bs = Part.BSplineCurve()
        bs.interpolate(pts)
        edge = bs.toShape()
        circ = Part.Wire(Part.makeCircle(0.75, pts[0], edge.tangentAt(edge.FirstParameter)))
        p.append(("Wire%d" % k, Part.Wire(edge).makePipeShell([circ], True, True), col))
    return p


# ---------------------------------------------------------------- printed parts
def skin(relief_clippy):
    """Front plate. Print face up: white 0-2.0 mm, blue 2.0-2.8, then pink/white for V2."""
    base = box(-T, -T, -T, W + 2 * T, T, H + 2 * T)
    cuts = [lcd_window()]
    cuts += [box(WEM_X + 2 + i * 5.2, -T - 1, WEM_Z + 4, 3.4, T + 2, 17) for i in range(5)]
    cuts.append(cyl_y(KEY[0], KEY[1], 2.4, -T - 5, 10))
    for x, z in SCREWS:                                                # M3 countersunk
        cuts.append(cyl_y(x, z, 1.7, -T - 1, T + 2))
        cuts.append(Part.makeCone(3.3, 1.7, 1.6, V(x, -T - 0.01, z), V(0, 1, 0)))
    base = base.cut(cuts)

    # blue band: title bar with the text and the three buttons cut through to white
    bar = box(0.5, -T - BAND, TITLE_Z, W - 1, BAND, 11.0)
    holes = [cyl_y(KEY[0], KEY[1], 4.0, -T - 2, 4)]
    holes += [cyl_y(x, z, 3.6, -T - 2, 4) for x, z in SCREWS[2:]]
    holes.append(text_solid("piege.exe", 6.0, 17.0, TITLE_Z + 3.0, -T + 0.5, BAND + 1))
    for i in range(3):
        bx = W - 33 + i * 8.2
        holes.append(box(bx, -T - 2, TITLE_Z + 2.0, 6.6, 4, 6.6))
    bar = bar.cut(holes)
    # button glyphs stay blue inside the white squares: _ , box outline, x
    g0 = W - 33
    glyphs = [box(g0 + 1.5, -T - BAND, TITLE_Z + 2.9, 3.6, BAND, 0.9),
              box(g0 + 8.2 + 1.4, -T - BAND, TITLE_Z + 3.4, 3.8, BAND, 3.8).cut(
                  box(g0 + 8.2 + 2.2, -T - 2, TITLE_Z + 4.2, 2.2, 4, 2.2))]
    for a in (45, -45):
        b = box(-2.4, -T - BAND, -0.45, 4.8, BAND, 0.9)
        b.rotate(V(0, 0, 0), V(0, 1, 0), a)
        b.translate(V(g0 + 16.4 + 3.3, 0, TITLE_Z + 5.3))
        glyphs.append(b)
    parts = [("Skin", base, "white"), ("Skin_Blue", fuse_all([bar] + glyphs), "blue")]

    if relief_clippy:
        path = clippy_path(8.0, 3.0, 0.62, -T)
        wire = sausage(path, 1.5, -T - BAND - PINK, BAND + PINK)
        eyes = fuse_all([cyl_y(8.0 + ex * 0.62, 3.0 + 27.5 * 0.62, 2.6, -T - BAND - PINK - 0.6,
                               BAND + PINK + 0.6) for ex in (2.0, 13.0)])
        pupils = [cyl_y(8.0 + ex * 0.62 + 0.6, 3.0 + 27.5 * 0.62, 0.9, -T - 5, 10)
                  for ex in (2.0, 13.0)]
        eyes = eyes.cut(pupils)
        parts[0] = ("Skin", base.cut(pupils), "white")
        parts.append(("Skin_Clippy", wire.cut(eyes), "pink"))
        parts.append(("Skin_Eyes", eyes, "white"))
    return parts


POCKET, INLAY_CLR = 0.6, 0.15


def skin_inlay():
    """Same front, as separate one-colour pieces glued into pockets of a white plate."""
    base = box(-T, -T, -T, W + 2 * T, T, H + 2 * T)
    cuts = [lcd_window()]
    cuts += [box(WEM_X + 2 + i * 5.2, -T - 1, WEM_Z + 4, 3.4, T + 2, 17) for i in range(5)]
    cuts.append(cyl_y(KEY[0], KEY[1], 2.4, -T - 5, 10))
    for x, z in SCREWS:
        cuts.append(cyl_y(x, z, 1.7, -T - 1, T + 2))
        cuts.append(Part.makeCone(3.3, 1.7, 1.6, V(x, -T - 0.01, z), V(0, 1, 0)))
    c = INLAY_CLR
    cuts.append(box(0.5 - c, -T - 0.1, TITLE_Z - c, W - 1 + 2 * c, POCKET + 0.1, 11 + 2 * c))
    path = clippy_path(8.0, 3.0, 0.62, -T)
    eye_xz = [(8.0 + ex * 0.62, 3.0 + 27.5 * 0.62) for ex in (2.0, 13.0)]
    cuts.append(sausage(path, 1.5 + c, -T - 0.1, POCKET + 0.1))
    cuts += [cyl_y(x, z, 2.6 + c, -T - 0.1, POCKET + 0.1) for x, z in eye_xz]
    base = base.cut(cuts)

    # white buttons rise from the pocket floor through the blue bar, glyphs engraved
    top = -T - BAND
    g0 = W - 33
    btns = [box(g0 + i * 8.2 + c, top, TITLE_Z + 2.0 + c, 6.6 - 2 * c, BAND + POCKET, 6.6 - 2 * c)
            for i in range(3)]
    engr = [box(g0 + 1.5, top - 0.1, TITLE_Z + 2.9, 3.6, 0.5, 0.9),
            box(g0 + 8.2 + 1.4, top - 0.1, TITLE_Z + 3.4, 3.8, 0.5, 3.8).cut(
                box(g0 + 8.2 + 2.2, top - 1, TITLE_Z + 4.2, 2.2, 2, 2.2))]
    for a in (45, -45):
        b = box(-2.4, top - 0.1, -0.45, 4.8, 0.5, 0.9)
        b.rotate(V(0, 0, 0), V(0, 1, 0), a)
        b.translate(V(g0 + 16.4 + 3.3, 0, TITLE_Z + 5.3))
        engr.append(b)
    base = base.fuse(btns).cut(engr).removeSplitter()

    bar = box(0.5, top, TITLE_Z, W - 1, BAND + POCKET, 11.0)
    holes = [cyl_y(KEY[0], KEY[1], 4.0, -T - 2, 4)]
    holes += [cyl_y(x, z, 3.6, -T - 2, 4) for x, z in SCREWS[2:]]
    # letters engraved 1.0 mm leaving a 0.4 mm floor (cut-through letters would drop
    # the counters of e/p/g): swap white -> blue at 0.4 mm, or paint the letters
    holes.append(text_solid("piege.exe", 6.0, 17.0, TITLE_Z + 3.0, -T + POCKET - 0.4, 1.4))
    holes += [box(g0 + i * 8.2, -T - 2, TITLE_Z + 2.0, 6.6, 4, 6.6) for i in range(3)]
    bar = bar.cut(holes).removeSplitter()

    clip = sausage(path, 1.5, -T - 1.0, 1.0 + POCKET)
    clip = clip.fuse([cyl_y(x, z, 2.6, -T - 1.0, 1.0 + POCKET) for x, z in eye_xz]).removeSplitter()
    eyes = fuse_all([cyl_y(x, z, 2.5, -T - 1.8, 0.8) for x, z in eye_xz])
    eyes = eyes.cut(fuse_all([cyl_y(x + 0.6, z, 0.9, -T - 1.9, 0.5) for x, z in eye_xz]))
    return [("Plate", base, "white"), ("Bar", bar, "blue"),
            ("Clippy", clip, "pink"), ("Eyes", eyes, "white")]


def lcd_window():
    # the metal frame bears on the skin: 0.5 mm hidden left/right, 1.5 mm top/bottom
    return box(LCD_X + BEZ_X + 0.5, -T - 1, LCD_Z + BEZ_Z + 1.5, BEZ_L - 1, T + 2, BEZ_H - 3)


def tub(clippy_mount):
    outer = box(-T, 0, -T, W + 2 * T, D + T, H + 2 * T)
    s = outer.cut(box(0, -1, 0, W, D + 1, H))
    adds = [cyl_y(x, z, 4.0, 0, D) for x, z in SCREWS]                  # insert bosses
    adds.append(cyl_y(KEY[0], KEY[1], 4.2, 0, D))                      # keyring tube
    for dx in LCD_HX:                                                  # LCD clamp posts
        for dz in LCD_HZ:
            adds.append(cyl_y(LCD_X + dx, LCD_Z + dz, 2.0, PCB_B, D - PCB_B))
            # 2.0 pin: fits a 2.5 or a 3.0 hole whatever the exact centre
            adds.append(cyl_y(LCD_X + dx, LCD_Z + dz, 1.0, PCB_Y + 0.2, 1.5))
    cy, cz = PLUG_T / 2 + PLUG_CLR, PLUG_W / 2 + PLUG_CLR
    # rails for the sliding gate on the right outer face
    x0 = W + T
    for zb, zl in ((1.0, 1.0), (23.7, 21.9)):
        adds.append(box(x0 - 0.1, 0, zb, GATE_CH + 0.1, 15.4, 2.4))
        adds.append(box(x0 + GATE_CH, 0, zl, 1.2, 15.4, 4.2))
    adds.append(box(x0 - 0.1, 0, 1.0, GATE_CH + 1.3, 0.6, 25.1))      # front stop for the gate
    if clippy_mount:
        adds.append(clippy_slot()[0])
    s = s.fuse(adds)

    cuts = []
    for x, z in SCREWS:
        cuts.append(cyl_y(x, z, 2.05, -0.1, 5.6))                      # M3x4 heat insert
    cuts.append(cyl_y(KEY[0], KEY[1], 2.4, -1, D + T + 2))
    cuts.append(box(W - 1, YC - cy, ZC - cz, T + 2, 2 * cy, 2 * cz))  # plug hole, gate keeps it in
    cuts.append(box(W - 1, PCB_Y - 3.6, LCD_Z + BEZ_Z + BEZ_H / 2 - 4, T + 3, 4.6, 8))  # backlight LED slit
    if clippy_mount:
        cuts += clippy_slot()[1]
    s = s.cut(cuts)
    return s.removeSplitter()


def gate():
    x0 = W + T + (GATE_CH - GATE_T) / 2
    g = box(x0, 0.7, 3.4 + GATE_CLR, GATE_T, 15.0, 20.3 - 2 * GATE_CLR)
    g = g.fuse(box(x0, 15.7, 3.4 + GATE_CLR, 4.0, 1.6, 20.3 - 2 * GATE_CLR))   # grip
    slot = box(x0 - 1, -1, ZC - 2.3, 4, YC + 1, 4.6).fuse(cyl_x(YC, ZC, 2.3, x0 - 1, 4))
    return g.cut(slot)


# --- V1: Clippy on the roof, the keyring goes through its top loop
CX0 = 8.0


def clippy_slot():
    """T-slot block on the roof (fused to the tub) and its channel (cut)."""
    zt = H + T
    block = box(CX0 - 2, 3.0, zt, 24, 22, 4.0)
    cx = CX0 + 10
    chan = box(cx - 4.0, 5.0, zt + 0.6, 8.0, 21, 1.8).fuse(box(cx - 2.0, 5.0, zt + 2.0, 4.0, 21, 2.5))
    return block, [chan]


def clippy_part():
    zt = H + T
    cx = CX0 + 10
    yf = 8.0                       # wire plane depth (front half of the roof)
    foot = box(cx - 3.8, 5.2, zt + 0.8, 7.6, 19.6, 1.2).fuse(
        box(cx - 1.8, 5.2, zt + 1.9, 3.6, 19.6, 2.3))
    plate = box(CX0, 5.2, zt + 4.0, 20, 6.0, 2.0)
    path = clippy_path(CX0 + 2.0, zt + 6.0, 1.0, yf)
    wire = sausage(path, 1.8, yf - 3.0, 6.0)
    eyes = fuse_all([cyl_y(CX0 + 2.0 + ex, zt + 6.0 + 29.0, 3.2, yf - 4.2, 1.2) for ex in (1.6, 14.4)])
    pupils = fuse_all([cyl_y(CX0 + 2.0 + ex + 0.8, zt + 6.0 + 29.0, 1.3, yf - 4.8, 0.6)
                       for ex in (1.6, 14.4)])
    body = fuse_all([foot, plate, wire])
    return [("Clippy", body, "pink"), ("Clippy_Eyes", eyes, "white"),
            ("Clippy_Pupils", pupils, "black")]


# ---------------------------------------------------------------- build
if App.listDocuments().get(DOC):
    App.closeDocument(DOC)
doc = App.newDocument(DOC)

report = {}
for tag, ox, roof in VARIANTS:
    printed = skin(relief_clippy=not roof)
    printed.append(("Tub", tub(roof), "white"))
    printed.append(("Gate", gate(), "blue"))
    if roof:
        printed += clippy_part()
    comps = components()
    clashes = []
    for pn, ps, _ in printed:
        for cn, cs, _ in comps:
            if cn.startswith(("Wire", "USB_Cable")):
                continue
            v = ps.common(cs).Volume
            if v > 0.3:
                clashes.append("%s/%s %.1f" % (pn, cn, v))
    for i, (an, a, _) in enumerate(printed):
        for bn, b, _ in printed[i + 1:]:
            if an.split("_")[0] == bn.split("_")[0]:
                continue
            v = a.common(b).Volume
            if v > 0.3:
                clashes.append("%s/%s %.1f" % (an, bn, v))
    bb = fuse_all([s for _, s, _ in printed]).BoundBox
    report[tag] = {"outer_WxHxD": (round(bb.XLength, 1), round(bb.ZLength, 1), round(bb.YLength, 1)),
                   "clashes": clashes,
                   "valid": all(s.isValid() for _, s, _ in printed)}
    # exploded copy: skin forward, tub back, gate right, clippy up
    explode = {"Skin": V(0, -45, 0), "Tub": V(0, 45, 0), "Gate": V(25, 0, 0), "Clippy": V(0, 45, 25)}
    for kind, items in (("Prt", printed), ("Cmp", comps)):
        for name, shp, col in items:
            for ex in (False, True):
                sh = shp.copy()
                if ex:
                    off = explode.get(name.split("_")[0], V(0, 0, 0)) if kind == "Prt" else V(0, 0, 0)
                    sh.translate(off + V(0, 0, -170))
                sh.translate(V(ox, 0, 0))
                o = doc.addObject("Part::Feature", "%s%s_%s_%s" % ("X" if ex else "", tag, kind, name))
                o.Shape = sh
                o.ViewObject.ShapeColor = COL[col]
    # STL per printed part (colour bands stay merged in one body per plate)
    vdir = STL_DIR
    os.makedirs(vdir, exist_ok=True)
    groups = {}
    for name, shp, _ in printed:
        groups.setdefault(name.split("_")[0], []).append(shp)
    # print orientation: skin face up / tub back down (front -Y -> +Z), gate flat
    for g, shps in groups.items():
        sh = fuse_all(shps).removeSplitter()
        if g == "Gate":
            sh.rotate(V(0, 0, 0), V(0, 1, 0), -90)
        else:
            sh.rotate(V(0, 0, 0), V(1, 0, 0), -90)
        bb = sh.BoundBox
        sh.translate(V(-bb.XMin, -bb.YMin, -bb.ZMin))
        sh.exportStl(os.path.join(vdir, "%s_%s.stl" % (tag, g)))
        report[tag]["stl_" + g] = (round(sh.BoundBox.XLength, 1), round(sh.BoundBox.YLength, 1),
                                   round(sh.BoundBox.ZLength, 1))
    # quick test print: bottom-right corner of the tub (USB tunnel, rails, Wemos cradle)
    corner = tub(roof).common(box(WEM_X - 4, -1, -T - 1, W + T + 10 - WEM_X, D + T + 2, 32))
    corner.rotate(V(0, 0, 0), V(1, 0, 0), -90)
    bb = corner.BoundBox
    corner.translate(V(-bb.XMin, -bb.YMin, -bb.ZMin))
    corner.exportStl(os.path.join(vdir, "%s_TEST_coin_USB.stl" % tag))
    report[tag]["stl_TEST"] = (round(corner.BoundBox.XLength, 1), round(corner.BoundBox.YLength, 1),
                               round(corner.BoundBox.ZLength, 1))

    # alternative front: inlay pieces to glue (no filament change needed)
    if not roof:
        inl = skin_inlay()
        idir = os.path.join(vdir, "facade_marqueterie")
        os.makedirs(idir, exist_ok=True)
        for i, (an, a_, _) in enumerate(inl):
            for cn, cs, _ in comps:
                if not cn.startswith(("Wire", "USB_Cable")) and a_.common(cs).Volume > 0.3:
                    clashes.append("Inlay_%s/%s" % (an, cn))
            for bn, b_, _ in inl[i + 1:]:
                if a_.common(b_).Volume > 0.05:
                    clashes.append("Inlay_%s/%s" % (an, bn))
        report[tag]["inlay_valid"] = all(sh.isValid() for _, sh, _ in inl)
        lift = {"Plate": 0, "Bar": 12, "Clippy": 12, "Eyes": 24}
        for name, shp, col in inl:
            o = doc.addObject("Part::Feature", "M%s_%s" % (tag, name))
            sh = shp.copy()
            sh.translate(V(ox, -lift[name], 0))
            o.Shape = sh
            o.ViewObject.ShapeColor = COL[col]
            sh = shp.copy()
            sh.rotate(V(0, 0, 0), V(1, 0, 0), -90)
            bb = sh.BoundBox
            sh.translate(V(-bb.XMin, -bb.YMin, -bb.ZMin))
            sh.exportStl(os.path.join(idir, "%s_Facade_%s.stl" % (tag, name)))
            report[tag]["inlay_" + name] = (round(bb.XLength, 1), round(bb.YLength, 1), round(bb.ZLength, 1))

doc.recompute()
os.makedirs(CAD_DIR, exist_ok=True)
doc.saveAs(os.path.join(CAD_DIR, "EventBadge_Fenetre.FCStd"))
print(report)
