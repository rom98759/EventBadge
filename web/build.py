#!/usr/bin/env python3
"""Generate ../portal.h from index.html, embedding the avatar as a data URI
so the captive portal is fully self-contained offline.

Usage: python3 web/build.py   (run from the project root or the web/ folder)
"""
import base64, os, sys

HERE = os.path.dirname(os.path.abspath(__file__))
HTML = os.path.join(HERE, "index.html")
AVATAR = os.path.join(HERE, "assets", "profil-128p.png")
OUT = os.path.join(HERE, os.pardir, "portal.h")

html = open(HTML, encoding="utf-8").read()
uri = "data:image/png;base64," + base64.b64encode(open(AVATAR, "rb").read()).decode()
html = html.replace('src="assets/profil-128p.png"', 'src="' + uri + '"')

if 'src="' + uri + '"' not in html:
    sys.exit("error: avatar <img> src not found in index.html")
if ')HTML"' in html:
    sys.exit("error: raw-string delimiter )HTML\" appears in the payload")

out = (
    '#pragma once\n#include <pgmspace.h>\n\n'
    '// Full captive-portal page, generated from web/index.html by web/build.py\n'
    '// with the avatar embedded as a data URI. Edit index.html, then rerun.\n'
    'const char PORTAL_HTML[] PROGMEM = R"HTML(\n' + html + '\n)HTML";\n'
)
open(OUT, "w", encoding="utf-8").write(out)
print("portal.h written: %d KB" % (len(out) // 1024))
