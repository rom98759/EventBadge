"""Belt-style clip glued on the back of the tub; one or two per badge.

The clip is closed at the top and open at the bottom: the badge hangs under
the strap. The tongue leans towards the base so it pinches the strap, and
flares out at its tip so the strap slides in.
Run in the FreeCAD Python console:
    exec(open("/home/romain/Documents/FreeCAD/EventBadge/scripts/strap_clip.py").read())
"""
import os
import FreeCAD as App
import Part
import Mesh

V = App.Vector
OUT = "/home/romain/Documents/FreeCAD/EventBadge/stl"

CLIP_W = 20.0      # along the strap
CLIP_L = 40.0      # height of the glued base
WALL = 2.4
STRAP_T = 5.0
PINCH = 3.5        # gap at the pinch point, below the strap thickness


def poly(pts):
    pts = [V(x, y, 0) for x, y in pts]
    return Part.Face(Part.makePolygon(pts + [pts[0]]))


def build():
    # profile in XY (x away from the badge, y up), printed lying on its side
    # so the tongue bends along the layers, not across them
    top = CLIP_L - WALL
    x_in = WALL + STRAP_T                     # tongue inner face at the top
    x_out = x_in + WALL
    faces = [
        poly([(0, 0), (WALL, 0), (WALL, CLIP_L), (0, CLIP_L)]),                  # glued base
        poly([(0, top), (x_out, top), (x_out, CLIP_L), (0, CLIP_L)]),            # top bend
        poly([(WALL, top), (WALL + 2.5, top), (WALL, top - 2.5)]),               # inner gusset
        poly([(x_in, top), (x_out, top), (WALL + PINCH + WALL, 6), (WALL + PINCH + 5.2, 0),
              (WALL + PINCH + 2.8, 0), (WALL + PINCH, 6)]),                       # tongue + flare
    ]
    s = faces[0].extrude(V(0, 0, CLIP_W))
    s = s.fuse([f.extrude(V(0, 0, CLIP_W)) for f in faces[1:]]).removeSplitter()
    return s


part = build()
doc = App.newDocument("StrapClip")
Part.show(part, "V2_Strap_Clip")
bb = part.BoundBox
part.translate(V(-bb.XMin, -bb.YMin, -bb.ZMin))
Mesh.Mesh(part.tessellate(0.05)).write(os.path.join(OUT, "V2_Strap_Clip.stl"))
bb = part.BoundBox
print({"valid": part.isValid(), "solids": len(part.Solids), "volume_cm3": round(part.Volume / 1000, 1),
       "stl": (round(bb.XLength, 1), round(bb.YLength, 1), round(bb.ZLength, 1))})
