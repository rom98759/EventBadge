#pragma once
#include <pgmspace.h>
#include "config.h"

// Static page: the badge serves this to anyone who joins the AP. It reads
// nothing about the visitor and sends nothing back.
const char PORTAL_HTML[] PROGMEM = R"HTML(<!doctype html>
<html lang="fr"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>)HTML" CFG_SSID R"HTML(</title>
<style>
:root{--bg:#0b1636;--fg:#dfe8ff;--dim:#8fa9e8;--line:#2c4387;--warn:#ffb020}
*{box-sizing:border-box}
body{margin:0;background:var(--bg);color:var(--fg);font:17px/1.45 ui-monospace,Menlo,Consolas,monospace;padding:22px 16px 34px}
main{max-width:34rem;margin:0 auto;display:grid;gap:16px}
h1{font-size:1.4rem;margin:0;color:var(--warn)}
p{margin:0}
.box{border:1px solid var(--line);padding:12px}
.cta{display:block;background:var(--warn);color:var(--bg);text-align:center;padding:12px;text-decoration:none;font-weight:700}
.links{display:grid;gap:6px}
.links a{color:var(--fg)}
small{color:var(--dim)}
.blink{animation:b 1s steps(1) infinite}
@keyframes b{50%{opacity:0}}
@media (prefers-reduced-motion:reduce){.blink{animation:none}}
</style></head><body><main>
<h1>&gt; CONNEXION ETABLIE<span class="blink">_</span></h1>
<div class="box">Tu viens de rejoindre un Wi-Fi inconnu en quelques secondes, juste parce qu'il s'ouvrait tout seul. C'est exactement comme ca qu'un faux reseau piege les gens.</div>
<p><strong>Rien n'est collecte ici.</strong> Ce badge ne garde que le nombre de connexions, sans aucune info sur toi. C'est une demo, pas un vrai piege.</p>
<p>Moi c'est )HTML" CFG_NAME R"HTML(, )HTML" CFG_TITLE R"HTML(. Je cherche une alternance pour apprendre a defendre contre ce genre d'attaques.</p>
<a class="cta" href="/contact.vcf">[ RECUPERER MON CONTACT ]</a>
<div class="links">
<span class="dim">Hors de ce Wi-Fi (pas d'Internet ici) :</span>
<a href=")HTML" CFG_SITE R"HTML(">)HTML" CFG_SITE R"HTML(</a>
<a href=")HTML" CFG_GITHUB R"HTML(">)HTML" CFG_GITHUB R"HTML(</a>
<a href=")HTML" CFG_LINKEDIN R"HTML(">)HTML" CFG_LINKEDIN R"HTML(</a>
<span>)HTML" CFG_EMAIL R"HTML(</span>
</div>
<small>Pour te deconnecter : oublie le reseau ")HTML" CFG_SSID R"HTML(" dans tes reglages Wi-Fi.</small>
</main></body></html>)HTML";

// Downloadable contact card (vCard 3.0).
const char PORTAL_VCF[] PROGMEM =
  "BEGIN:VCARD\r\nVERSION:3.0\r\n"
  "FN:" CFG_NAME "\r\n"
  "TITLE:" CFG_TITLE "\r\n"
  "EMAIL;TYPE=INTERNET:" CFG_EMAIL "\r\n"
  "URL:" CFG_SITE "\r\n"
  "X-SOCIALPROFILE;TYPE=github:" CFG_GITHUB "\r\n"
  "X-SOCIALPROFILE;TYPE=linkedin:" CFG_LINKEDIN "\r\n"
  "END:VCARD\r\n";
