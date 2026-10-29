#!/usr/bin/env python3
"""Generate ../portal.h from index.html, embedding every assets/*.png and *.jpg image as
a data URI so the captive portal is fully self-contained offline.

Usage: python3 web/build.py   (run from anywhere)
"""
import base64, os, re, sys

HERE = os.path.dirname(os.path.abspath(__file__))
HTML = os.path.join(HERE, "index.html")
OUT = os.path.join(HERE, os.pardir, "portal.h")

html = open(HTML, encoding="utf-8").read()


MIME = {"png": "image/png", "jpg": "image/jpeg"}


def _embed(m):
    rel, ext = m.group(1), m.group(2)
    path = os.path.join(HERE, rel)
    data = base64.b64encode(open(path, "rb").read()).decode()
    return 'src="data:' + MIME[ext] + ';base64,' + data + '"'


html, n = re.subn(r'src="(assets/[^"]+\.(png|jpg))"', _embed, html)
if n == 0:
    sys.exit("error: no assets/*.png|jpg <img> src found in index.html")
if ')HTML"' in html:
    sys.exit('error: raw-string delimiter )HTML" appears in the payload')

out = (
    '#pragma once\n#include <pgmspace.h>\n\n'
    '// Full captive-portal page, generated from web/index.html by web/build.py\n'
    '// with images (avatar, QR codes) embedded as data URIs. Edit index.html,\n'
    '// then rerun this script.\n'
    'const char PORTAL_HTML[] PROGMEM = R"HTML(\n' + html + '\n)HTML";\n'
)
open(OUT, "w", encoding="utf-8").write(out)
print("portal.h written: %d KB (%d image(s) embedded)" % (len(out) // 1024, n))
