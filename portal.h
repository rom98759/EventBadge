#pragma once
#include <pgmspace.h>
#include "config.h"

// Static page served to anyone who joins the AP. It reads nothing about the
// visitor server-side and sends nothing back: the device details below are
// computed by the visitor's own browser and shown only on their screen.
const char PORTAL_HTML[] PROGMEM = R"HTML(<!doctype html>
<html lang="fr"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>)HTML" CFG_SSID R"HTML(</title>
<style>
:root{
--page:#0d1426;--card:#121a30;--fg:#e6edff;--dim:#8fa9e8;--line:#28406f;
--amber:#ffb020;--mono:ui-monospace,"SF Mono",Menlo,Consolas,"DejaVu Sans Mono",monospace;
--sans:system-ui,-apple-system,"Segoe UI",Roboto,sans-serif}
*{box-sizing:border-box}
body{margin:0;background:var(--page);color:var(--fg);font:15px/1.5 var(--sans);
padding-left:max(16px,env(safe-area-inset-left,0px));padding-right:max(16px,env(safe-area-inset-right,0px));padding-block:0 34px}
main{max-width:34rem;margin:0 auto}
.top{margin:0 -16px;padding:22px 16px 18px;background:linear-gradient(180deg,#311500,#0d1426);border-bottom:1px solid var(--line)}
.tag{display:inline-block;background:var(--amber);color:#1a0e00;font:700 12px var(--mono);letter-spacing:.06em;padding:4px 9px;border-radius:4px}
.top h1{margin:10px 0 0;font-size:1.5rem;line-height:1.2;text-wrap:balance}
.top p{margin:8px 0 0;color:var(--dim)}
section{margin-top:18px}
.meter .row{display:flex;justify-content:space-between;font-size:13px;color:var(--dim);margin-bottom:6px}
.bars{display:flex;gap:5px}
.bars span{height:8px;flex:1;border-radius:2px;background:var(--line)}
.bars span.on{background:var(--amber)}
.card{background:var(--card);border:1px solid var(--line);border-radius:10px;overflow:hidden;margin-top:12px}
.r{display:flex;justify-content:space-between;gap:12px;padding:9px 13px;font-size:14px}
.r+.r{border-top:1px solid var(--line)}
.r .k{color:var(--dim)}
.r .v{font-family:var(--mono);text-align:right;min-width:0;word-break:break-word}
.note{color:var(--dim);font-size:13px;margin-top:12px}
.me{margin-top:26px;background:var(--card);border:1px solid var(--line);border-left:4px solid var(--amber);border-radius:10px;padding:16px}
.me h2{margin:0;font-size:1.25rem}
.me .role{color:var(--amber);font:600 12px var(--mono);letter-spacing:.05em;text-transform:uppercase;margin-top:3px}
.me p{margin:10px 0 0;line-height:1.55}
.me .alt{margin-top:12px;font-weight:700;font-size:1.05rem}
.me .alt b{color:var(--amber)}
.cta{display:block;text-align:center;background:var(--amber);color:#1a0e00;font-weight:700;padding:13px;border-radius:10px;text-decoration:none;margin-top:14px}
.links{display:grid;gap:7px;margin-top:14px;font-size:14px}
.links .h{color:var(--dim);font-size:12.5px}
.links a{color:var(--fg)}
small{display:block;color:var(--dim);font-size:12px;margin-top:20px}
.cur{animation:b 1s steps(1) infinite}
@keyframes b{50%{opacity:0}}
@media (prefers-reduced-motion:reduce){.cur{animation:none}}
</style></head><body><main>

<div class="top">
<span class="tag">EXPOSITION DETECTEE</span>
<h1>Ton navigateur vient de te trahir.<span class="cur">_</span></h1>
<p>Tu as rejoint un Wi-Fi inconnu en quelques secondes. Voila ce qu'il revele a n'importe quelle page, sans rien te demander :</p>
</div>

<section class="meter">
<div class="row"><span>Niveau d'exposition</span><span id="lvl">eleve</span></div>
<div class="bars" id="bars"><span></span><span></span><span></span><span></span><span></span></div>
<div class="card" id="info"><div class="r"><span class="k">lecture...</span><span class="v"></span></div></div>
<p class="note"><strong>Rien n'est collecte.</strong> Tout est calcule par ton navigateur et affiche seulement sur ton ecran. Ce badge ne garde que le nombre de connexions. C'est une demo de sensibilisation, pas un vrai piege.</p>
</section>

<div class="me">
<h2>)HTML" CFG_NAME R"HTML(</h2>
<div class="role">)HTML" CFG_ROLE R"HTML(</div>
<p>)HTML" CFG_TITLE R"HTML( a )HTML" CFG_SCHOOL R"HTML(. J'aime comprendre comment les choses se cassent pour mieux les defendre, de ce badge jusqu'aux serveurs.</p>
<p class="alt">Je cherche une <b>alternance</b> en cybersecurite / dev, <b>)HTML" CFG_WHEN R"HTML(</b>.</p>
<a class="cta" href="/contact.vcf">Ajouter mon contact</a>
<div class="links">
<span class="h">Hors de ce Wi-Fi (pas d'internet ici) :</span>
<a href=")HTML" CFG_SITE R"HTML(">)HTML" CFG_SITE R"HTML(</a>
<a href=")HTML" CFG_GITHUB R"HTML(">)HTML" CFG_GITHUB R"HTML(</a>
<a href=")HTML" CFG_LINKEDIN R"HTML(">)HTML" CFG_LINKEDIN R"HTML(</a>
<span>)HTML" CFG_EMAIL R"HTML(</span>
</div>
</div>

<small>Pour te deconnecter : oublie le reseau ")HTML" CFG_SSID R"HTML(" dans tes reglages Wi-Fi.</small>
</main>
<script>
(function(){
var ua=navigator.userAgent,os="inconnu",br="inconnu",m;
if(m=ua.match(/Android [\d.]+/))os=m[0];
else if(m=ua.match(/(iPhone|iPad)[^;]*OS ([\d_]+)/))os=m[1]+" iOS "+m[2].replace(/_/g,".");
else if(/Windows NT 10/.test(ua))os="Windows 10/11";
else if(/Mac OS X/.test(ua))os="macOS";
else if(/Linux/.test(ua))os="Linux";
if(/Firefox\//.test(ua))br="Firefox";
else if(/Edg\//.test(ua))br="Edge";
else if(/OPR\//.test(ua))br="Opera";
else if(/Chrome\//.test(ua))br="Chrome";
else if(/Safari\//.test(ua))br="Safari";
var tz="?";try{tz=Intl.DateTimeFormat().resolvedOptions().timeZone||"?"}catch(e){}
var gpu="masque";try{
var c=document.createElement("canvas"),g=c.getContext("webgl")||c.getContext("experimental-webgl"),
d=g&&g.getExtension("WEBGL_debug_renderer_info");
if(d)gpu=g.getParameter(d.UNMASKED_RENDERER_WEBGL)||"masque";
}catch(e){}
var net=(navigator.connection&&navigator.connection.effectiveType)||"?";
var dark=matchMedia("(prefers-color-scheme: dark)").matches?"sombre":"clair";
var rows=[
["Appareil",os+" / "+br],
["Ecran",screen.width+"x"+screen.height+" @"+(window.devicePixelRatio||1)+"x"],
["Langue",(navigator.languages&&navigator.languages.join(", "))||navigator.language||"?"],
["Fuseau (localisation)",tz],
["Carte graphique",gpu],
["Coeurs CPU",navigator.hardwareConcurrency||"?"],
["Theme",dark],
["Reseau",net]
];
var box=document.getElementById("info");box.textContent="";
rows.forEach(function(r){
var row=document.createElement("div");row.className="r";
var k=document.createElement("span");k.className="k";k.textContent=r[0];
var v=document.createElement("span");v.className="v";v.textContent=r[1];
row.appendChild(k);row.appendChild(v);box.appendChild(row);
});
// Exposure level scales with how much the browser actually gave up.
var score=rows.filter(function(r){return r[1]&&r[1]!=="?"&&r[1]!=="masque"}).length;
var on=Math.max(2,Math.min(5,score-3));
var bars=document.getElementById("bars").children;
for(var i=0;i<bars.length;i++)if(i<on)bars[i].className="on";
document.getElementById("lvl").textContent=on>=4?"eleve":on===3?"moyen":"faible";
})();
</script></body></html>)HTML";

// Downloadable contact card (vCard 3.0).
const char PORTAL_VCF[] PROGMEM =
  "BEGIN:VCARD\r\nVERSION:3.0\r\n"
  "FN:" CFG_NAME "\r\n"
  "TITLE:" CFG_TITLE "\r\n"
  "NOTE:Cherche une alternance cybersecurite/dev " CFG_WHEN "\r\n"
  "EMAIL;TYPE=INTERNET:" CFG_EMAIL "\r\n"
  "URL:" CFG_SITE "\r\n"
  "X-SOCIALPROFILE;TYPE=github:" CFG_GITHUB "\r\n"
  "X-SOCIALPROFILE;TYPE=linkedin:" CFG_LINKEDIN "\r\n"
  "END:VCARD\r\n";
