#!/usr/bin/env python3
"""Generate ../portal.h from index.html: the page gzipped, and every assets/*.png and
*.jpg image as its own file served by the badge, so the captive portal is fully
self-contained offline.

Images get a content-hash URL: the badge can tell phones to cache them for a year,
and a new image after a reflash gets a new URL instead of a stale cached copy.

Usage: python3 web/build.py   (run from anywhere)
"""
import gzip, hashlib, os, re, sys

HERE = os.path.dirname(os.path.abspath(__file__))
HTML = os.path.join(HERE, "index.html")
OUT = os.path.join(HERE, os.pardir, "portal.h")

MIME = {"png": "image/png", "jpg": "image/jpeg"}

html = open(HTML, encoding="utf-8").read()
assets = []  # (url, mime, bytes)


def _asset(m):
    rel, ext = m.group(1), m.group(2)
    data = open(os.path.join(HERE, rel), "rb").read()
    url = "/i/%s.%s" % (hashlib.sha1(data).hexdigest()[:10], ext)
    if url not in (a[0] for a in assets):
        assets.append((url, MIME[ext], data))
    return 'src="' + url + '"'


html, n = re.subn(r'src="(assets/[^"]+\.(png|jpg))"', _asset, html)
if n == 0:
    sys.exit("error: no assets/*.png|jpg <img> src found in index.html")

# mtime=0 keeps the output identical across builds of the same page.
page = gzip.compress(html.encode("utf-8"), 9, mtime=0)
etag = '"%s"' % hashlib.sha1(page).hexdigest()[:16]


def c_bytes(name, data):
    rows = [", ".join("0x%02x" % b for b in data[i:i + 20]) for i in range(0, len(data), 20)]
    return "const uint8_t %s[] PROGMEM = {\n  %s\n};\n" % (name, ",\n  ".join(rows))


out = [
    "#pragma once\n#include <pgmspace.h>\n\n",
    "// Captive-portal page and images, generated from web/index.html by web/build.py.\n",
    "// Edit index.html or web/assets/, then rerun this script.\n\n",
    "struct PortalAsset {\n  const char *path;\n  const char *mime;\n"
    "  const uint8_t *data;\n  size_t len;\n};\n\n",
    '#define PORTAL_ETAG "%s"\n' % etag.replace('"', '\\"'),
    c_bytes("PORTAL_GZ", page),
]
for i, (_, _, data) in enumerate(assets):
    out.append(c_bytes("PORTAL_ASSET_%d" % i, data))
out.append("const PortalAsset PORTAL_ASSETS[] = {\n")
for i, (url, mime, data) in enumerate(assets):
    out.append('  { "%s", "%s", PORTAL_ASSET_%d, %d },\n' % (url, mime, i, len(data)))
out.append("};\n")

open(OUT, "w", encoding="utf-8").write("".join(out))
print("portal.h written: page %d KB gzipped (%d KB raw), %d image(s) %d KB"
      % (len(page) // 1024, len(html) // 1024, len(assets),
         sum(len(a[2]) for a in assets) // 1024))
