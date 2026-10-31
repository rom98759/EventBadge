# EventBadge keychain enclosure: three simple box mock-ups around the real parts.
# Run inside FreeCAD: exec(open("/home/romain/Documents/FreeCAD/EventBadge/scripts/explorations_abc.py").read())
# Axes: X = width, Z = height, Y = depth (y=0 is the inner face of the front wall,
# visitors look at the box from -Y).
import os
import FreeCAD as App
import FreeCADGui as Gui
import Part
from FreeCAD import Vector as V

DOC = "EventBadge"
OUT = "/home/romain/Documents/FreeCAD/EventBadge"  # rejected A/B/C directions, kept for the record

T = 2.0                    # wall thickness
W, D = 96.0, 29.0          # inner width and depth (depth set by Dupont plugs + wire bend)
LCD_X, LCD_Z = 14.0, 28.5  # LCD PCB bottom-left; 14 mm on the left for the I2C plugs
WEM_Z = 1.0
WEM_L, WEM_W = 33.7, 25.1
WEM_YB = 2.6               # front face of the Wemos PCB (pin tips touch the front wall)
SEC_DZ = -140.0            # section row offset

COL = {
    "white": (0.94, 0.94, 0.91), "black": (0.11, 0.11, 0.13), "blue": (0.12, 0.18, 0.43),
    "pink": (0.94, 0.50, 0.70), "red": (0.77, 0.14, 0.18), "purple": (0.42, 0.25, 0.63),
    "pcb_g": (0.13, 0.42, 0.25), "pcb_b": (0.10, 0.36, 0.62), "pcb_w": (0.23, 0.24, 0.60),
    "metal": (0.78, 0.79, 0.82), "lcd": (0.18, 0.36, 1.0), "led": (1.0, 1.0, 1.0),
    "plug": (0.08, 0.08, 0.08), "w_y": (0.95, 0.85, 0.15), "w_b": (0.15, 0.35, 0.85),
    "w_k": (0.05, 0.05, 0.05), "w_p": (0.65, 0.55, 0.85),
}


def box(x, y, z, dx, dy, dz):
    return Part.makeBox(dx, dy, dz, V(x, y, z))


def cyl_y(x, z, r, y0, length):
    return Part.makeCylinder(r, length, V(x, y0, z), V(0, 1, 0))


def cyl_x(y, z, r, x0, length):
    return Part.makeCylinder(r, length, V(x0, y, z), V(1, 0, 0))


def fillet_y(shape, r):
    edges = [e for e in shape.Edges
             if abs(e.Vertexes[0].Point.y - e.Vertexes[-1].Point.y) > 1e-3]
    return shape.makeFillet(r, edges)


def fuse_all(shapes):
    s = shapes[0]
    for o in shapes[1:]:
        s = s.fuse(o)
    return s


# ---------------------------------------------------------------- components
def components(wem_x):
    p = []
    # LCD1602: PCB 80x36x1.6, metal bezel 71x26x7, visible area 64.5x16
    pcb = box(LCD_X, 7.0, LCD_Z, 80, 1.6, 36)
    for dx in (2.5, 77.5):
        for dz in (2.5, 33.5):
            pcb = pcb.cut(cyl_y(LCD_X + dx, LCD_Z + dz, 1.25, 6.0, 4.0))
    p.append(("LCD_PCB", pcb, "pcb_g"))
    p.append(("LCD_Bezel", box(LCD_X + 4.5, 0.0, LCD_Z + 5, 71, 7.0, 26), "black"))
    p.append(("LCD_Screen", box(LCD_X + 7.75, -0.05, LCD_Z + 10, 64.5, 0.3, 16), "lcd"))
    p.append(("LCD_Led", box(LCD_X + 75.6, 1.0, LCD_Z + 15, 3.0, 3.0, 6), "led"))
    p.append(("LCD_Header", box(LCD_X + 7, 8.6, LCD_Z + 31.5, 40.6, 2.5, 2.5), "black"))
    # PCF8574 backpack on the back, total module depth 17.1 (measured)
    p.append(("I2C_PCB", box(LCD_X + 6, 11.1, LCD_Z + 16.4, 41.5, 1.6, 19.3), "pcb_b"))
    p.append(("I2C_Pot", box(LCD_X + 30, 12.7, LCD_Z + 20, 7, 4.4, 7), "w_b"))
    p.append(("I2C_Chip", box(LCD_X + 14, 12.7, LCD_Z + 22, 10, 1.6, 4), "black"))
    # 4 female Dupont housings on the I2C pins: 10 mm wide, 6.2 mm below the LCD top
    p.append(("I2C_Plugs", box(LCD_X - 8, 11.5, LCD_Z + 19.8, 14, 2.6, 10), "plug"))

    # Wemos D1 mini, PCB parallel to the front, stacking headers towards the back
    p.append(("Wemos_PCB", box(wem_x, WEM_YB, WEM_Z, WEM_L, 1.2, WEM_W), "pcb_w"))
    hy = WEM_YB + 1.2
    hl = 11.5 - 2.6 - 1.2  # measured 11.5 mm includes pin tips and headers
    p.append(("Wemos_HeaderTop", box(wem_x + 4.5, hy, WEM_Z + WEM_W - 2.6, 20.3, hl, 2.5), "black"))
    p.append(("Wemos_HeaderBot", box(wem_x + 4.5, hy, WEM_Z + 0.1, 20.3, hl, 2.5), "black"))
    p.append(("Wemos_ESP", box(wem_x + 1.5, hy, WEM_Z + 5, 15, 3.0, 15), "metal"))
    p.append(("Wemos_PinTips", box(wem_x + 4.5, 0.0, WEM_Z + 0.4, 20.3, WEM_YB, 1.0), "metal"))
    zc = WEM_Z + WEM_W / 2
    # micro-B socket on the same side as the headers (back), as on this clone
    p.append(("Wemos_USB", box(wem_x + WEM_L - 5.5, hy, zc - 3.75, 5.6, 2.6, 7.5), "metal"))
    # micro-B plug overmold + cable, captive inside the box
    yc = hy + 1.3
    x_end = wem_x + WEM_L + 0.3
    p.append(("USB_Plug", box(x_end, yc - 3.5, zc - 5.5, 18, 7, 11), "plug"))
    p.append(("USB_Cable", cyl_x(yc, zc, 2.0, x_end + 18, W + T + 22 - (x_end + 18)), "plug"))
    # male Dupont housings in the Wemos header (D1, D2, G, 5V, all on the same row)
    zw = WEM_Z + WEM_W - 1.3
    xs = [wem_x + WEM_L - 4.0 - 2.54 * i for i in (0, 1, 4, 5)]
    plugs = [box(x - 1.25, hy + hl, zw - 1.25, 2.5, 14, 2.5) for x in xs]
    p.append(("Wemos_Plugs", fuse_all(plugs), "plug"))
    # wires
    y_end = hy + hl + 14
    for k, col in enumerate(("w_k", "w_p", "w_b", "w_y")):
        zl = LCD_Z + 19.8 + 1.25 + k * 2.54
        yk = 24.6 + k * 1.05
        xw = xs[k]
        pts = [V(LCD_X - 8, 12.8, zl), V(3.2, 13.8, zl), V(3.2, 23.0, zl - 9),
               V(18, yk, 36 - k), V(xw, yk, zw + 5), V(xw, y_end, zw)]
        bs = Part.BSplineCurve()
        bs.interpolate(pts)
        edge = bs.toShape()
        tan = edge.tangentAt(edge.FirstParameter)
        circ = Part.Wire(Part.makeCircle(0.75, pts[0], tan))
        wire = Part.Wire(edge).makePipeShell([circ], True, True)
        p.append(("Wire%d" % k, wire, col))
    return p


# ---------------------------------------------------------------- enclosure
def shell_parts(H, wem_x, outer_r=0.0, cav_r=0.0, chamfer=0.0):
    """Return (front_shell, lid) for an inner cavity W x D x H."""
    outer = box(-T, -T, -T, W + 2 * T, D + T, H + 2 * T)
    lid = box(-T, D, -T, W + 2 * T, T, H + 2 * T)
    if outer_r:
        outer = fillet_y(outer, outer_r)
        lid = fillet_y(lid, outer_r)
    if chamfer:
        front = [e for e in outer.Edges
                 if all(abs(v.Point.y + T) < 1e-6 for v in e.Vertexes)]
        outer = outer.makeChamfer(chamfer, front)
    cav = box(0, 0, 0, W, D + 1, H)
    if cav_r:
        cav = fillet_y(cav, cav_r)
    s = outer.cut(cav)

    corners = [(3.0, 3.0), (W - 3.0, 3.0), (3.0, H - 3.0), (W - 3.0, H - 3.0)]
    adds = [cyl_y(x, z, 4.0, 12.0, D - 12.0) for x, z in corners]
    # LCD posts through the 75 x 31 mounting holes
    for dx in (2.5, 77.5):
        for dz in (2.5, 33.5):
            adds.append(cyl_y(LCD_X + dx, LCD_Z + dz, 2.0, 0.0, 7.0))
            adds.append(cyl_y(LCD_X + dx, LCD_Z + dz, 1.1, 7.0, 3.0))
    zc = WEM_Z + WEM_W / 2
    s = s.fuse(adds)

    cuts = []
    for x, z in corners:
        cuts.append(cyl_y(x, z, 2.05, D - 5.5, 6.0))           # M3x4 heat insert
        lid = lid.cut(cyl_y(x, z, 1.7, D - 1, T + 2))          # screw clearance
        lid = lid.cut(Part.makeCone(1.7, 3.3, 1.6, V(x, D + T - 1.6, z), V(0, 1, 0)))
    cuts.append(box(LCD_X + 5, -T - 1, LCD_Z + 7, 70, T + 2, 22))  # LCD window
    cuts.append(box(W - 1, 0.5, LCD_Z + 14, T + 3, 5, 8))          # backlight LED slit
    cuts.append(cyl_x(WEM_YB + 2.5, zc, 2.2, W - 1, T + 3))        # cable hole
    s = s.cut(cuts)
    return s, lid


def variant_a():
    H = 74.0
    wem_x = 40.0
    s, lid = shell_parts(H, wem_x, chamfer=1.4)
    # title bar pocket, keyring "icon" through the whole box
    s = s.cut(box(0.5, -T - 0.1, H - 13, W - 1, 0.9, 11.5))
    kx, kz = 10.0, H - 7.0
    s = s.fuse(cyl_y(kx, kz, 4.2, 0, D))
    s = s.cut(cyl_y(kx, kz, 2.4, -T - 2, D + T + 4))
    lid = lid.cut(cyl_y(kx, kz, 2.4, D - 1, T + 2))
    # sunken frame around the screen (Win95 inset border)
    s = s.cut(box(LCD_X + 2, -T - 0.1, LCD_Z + 4, 76, 0.9, 28))
    # vent slots over the Wemos
    for i in range(6):
        s = s.cut(box(wem_x + 2 + i * 5.2, -T - 1, WEM_Z + 4, 3.4, T + 2, 17))
    s = s.removeSplitter()
    title = box(1.0, -T - 0.8, H - 12.5, W - 2, 1.6, 10.5).cut(cyl_y(kx, kz, 2.4, -T - 2, 5))
    btns = fuse_all([box(W - 27 + i * 8.2, -T - 1.8, H - 11.0, 7.0, 1.2, 7.5) for i in range(3)])
    return H, wem_x, [("Shell", s, "white"), ("TitleBar", title, "blue"),
                      ("Buttons", btns, "white"), ("Lid", lid, "black")]


def variant_b():
    H = 96.0
    wem_x = (W - WEM_L) / 2
    s, lid = shell_parts(H, wem_x)
    # 3.5" floppy corner chamfer (top right)
    cut = Part.makeBox(14, D + 2 * T + 2, 14, V(0, -T - 1, 0))
    cut.rotate(V(0, 0, 0), V(0, 1, 0), 45)
    cut.translate(V(W + T, 0, H + T - 9.9))
    s = s.cut(cut)
    lid = lid.cut(cut)
    # label pocket + shutter zone window + write-protect / HD squares
    s = s.cut(box(4, -T - 0.1, 31, W - 8, 0.9, H - 33))
    s = s.cut(box(wem_x + 1, -T - 1, WEM_Z + 1, WEM_L - 2, T + 2, WEM_W - 2))
    s = s.cut(box(3, -T - 0.1, 2, 5, 1.6, 6))
    s = s.cut(box(W - 8, -T - 0.1, 2, 5, 1.6, 6))
    kx, kz = 9.0, H - 8.0
    s = s.fuse(cyl_y(kx, kz, 4.2, 0, D))
    s = s.cut(cyl_y(kx, kz, 2.4, -T - 2, D + T + 4))
    lid = lid.cut(cyl_y(kx, kz, 2.4, D - 1, T + 2))
    s = s.removeSplitter()
    label = box(4.5, -T - 0.7, 31.5, W - 9, 1.6, H - 34).cut(
        box(LCD_X + 5, -T - 2, LCD_Z + 7, 70, 4, 22)).cut(cyl_y(kx, kz, 4.4, -T - 3, 5))
    shutter = box(wem_x - 7, -T - 1.2, -T, WEM_L + 14, 1.2, 31).cut(
        box(wem_x + 1, -T - 2, WEM_Z + 1, WEM_L - 2, 3, WEM_W - 2))
    hub = cyl_y(W / 2, 60, 13, D + T, 1.0).cut(box(W / 2 + 3, D + T - 1, 57, 5, 3, 6))
    return H, wem_x, [("Shell", s, "blue"), ("Label", label, "pink"),
                      ("Shutter", shutter, "white"), ("Lid", lid, "blue"),
                      ("Hub", hub, "metal")]


def variant_c():
    H = 66.0
    wem_x = 40.0
    s, lid = shell_parts(H, wem_x, outer_r=7.0, cav_r=5.0)
    # speech-bubble tail (bottom left), solid
    tri = Part.Face(Part.makePolygon([V(10, -T + 0.5, -1), V(-10, -T + 0.5, -16),
                                      V(26, -T + 0.5, -1), V(10, -T + 0.5, -1)]))
    tail = tri.extrude(V(0, D + T - 1, 0))
    s = s.fuse(tail).removeSplitter()
    # "..." typing dots in the lid, over the Wemos
    for i in range(3):
        lid = lid.cut(cyl_y(wem_x + 7 + i * 10, 13.5, 3.8, D - 1, T + 2))
    # Clippy: 6 mm wire bent like a paperclip, in the XZ plane at mid depth
    yc = D / 2
    segs = [
        Part.LineSegment(V(-24, yc, -8), V(-24, yc, 66)),
        Part.Arc(V(-24, yc, 66), V(-16.5, yc, 73.5), V(-9, yc, 66)),
        Part.LineSegment(V(-9, yc, 66), V(-9, yc, 4)),
        Part.Arc(V(-9, yc, 4), V(-13.5, yc, -0.5), V(-18, yc, 4)),
        Part.LineSegment(V(-18, yc, 4), V(-18, yc, 54)),
    ]
    path = Part.Wire([sg.toShape() for sg in segs])
    prof = Part.Wire(Part.makeCircle(3.0, V(-24, yc, -8), V(0, 0, 1)))
    clippy = path.makePipeShell([prof], True, False)
    clippy = clippy.fuse(box(-10, yc - 3, 30, 9.5, 6, 10))   # bracket to the bubble
    eyes = fuse_all([cyl_y(x, 56, 4.5, yc - 6.5, 2.0) for x in (-21.5, -11.5)])
    pupils = fuse_all([cyl_y(x, 55.5, 1.8, yc - 7.3, 1.0) for x in (-20.5, -10.5)])
    return H, wem_x, [("Bubble", s, "white"), ("Lid", lid, "white"),
                      ("Clippy", clippy, "pink"), ("Eyes", eyes, "white"),
                      ("Pupils", pupils, "black")]


# ---------------------------------------------------------------- build
if App.listDocuments().get(DOC):
    App.closeDocument(DOC)
doc = App.newDocument(DOC)

report = {}
for tag, fn, ox in (("A", variant_a, 0.0), ("B", variant_b, 170.0), ("C", variant_c, 350.0)):
    H, wem_x, enc = fn()
    comps = components(wem_x)
    # interference check enclosure vs parts
    clashes = []
    for en, es, _ in enc:
        for cn, cs, _ in comps:
            if cn.startswith("USB_Cable") or cn.startswith("Wire"):
                continue
            v = es.common(cs).Volume
            if v > 0.5:
                clashes.append("%s/%s %.1f" % (en, cn, v))
    xc = wem_x + WEM_L - 4.0 - 2.54   # section through the G plug
    keep = box(-60, -40, -60, 60 + xc, 120, 220)
    for kind, items in (("Enc", enc), ("Cmp", comps)):
        for name, shp, col in items:
            for sec in (False, True):
                sh = shp.copy()
                if sec:
                    sh = sh.common(keep)
                    if sh.Volume < 1e-3 and not sh.Faces:
                        continue
                    sh.translate(V(0, 0, SEC_DZ))
                sh.translate(V(ox, 0, 0))
                o = doc.addObject("Part::Feature", "%s%s_%s_%s" % ("S" if sec else "", tag, kind, name))
                o.Shape = sh
                o.ViewObject.ShapeColor = COL[col]
    bb = fuse_all([s for _, s, _ in enc]).BoundBox
    report[tag] = {"outer": (round(bb.XLength, 1), round(bb.ZLength, 1), round(bb.YLength, 1)),
                   "clashes": clashes}
    vdir = os.path.join(OUT, "archive", "variantes", tag)
    os.makedirs(vdir, exist_ok=True)
    for name, shp, _ in enc:
        shp.exportStl(os.path.join(vdir, "%s_%s.stl" % (tag, name)))

doc.recompute()
doc.saveAs(os.path.join(OUT, "cad", "EventBadge.FCStd"))


def show(prefixes):
    for o in doc.Objects:
        o.ViewObject.Visibility = any(o.Name.startswith(p) for p in prefixes)


def snap(prefixes, view, fname, hide=()):
    show(prefixes)
    for o in doc.Objects:
        if any(o.Name.startswith(h) for h in hide):
            o.ViewObject.Visibility = False
    v = Gui.getDocument(DOC).activeView()
    getattr(v, "view" + view)()
    v.fitAll()
    os.makedirs(os.path.join(OUT, "images", "explorations"), exist_ok=True)
    v.saveImage(os.path.join(OUT, "images", "explorations", fname), 2000, 1000, "White")


print(report)
