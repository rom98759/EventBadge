#pragma once
#include <pgmspace.h>

// Full captive-portal page, generated from web/index.html by web/build.py
// with images (avatar, QR codes) embedded as data URIs. Edit index.html,
// then rerun this script.
const char PORTAL_HTML[] PROGMEM = R"HTML(
<!doctype html>
<html lang="fr">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">
<title>Ce_WiFi_est_un_piege</title>
<style>
/* Win95 nostalgia portal — phone-first, offline-safe (system fonts only).
   This standalone file is the design source; it becomes portal.h on the ESP. */
:root{
  --teal:#007a7a;--face:#c0c0c0;--hi:#fff;--lt:#dfdfdf;--sh:#808080;--dk:#000;
  --navy:#000080;--navy2:#1084d0;--yellow:#ffe15a;
  --font:Tahoma,"MS Sans Serif",Geneva,system-ui,sans-serif;--mono:ui-monospace,Menlo,Consolas,monospace;
  color-scheme:light;
}
*{box-sizing:border-box}
html,body{margin:0}
body{background:var(--teal);color:#000;font-family:var(--font);font-size:13px;line-height:1.45;overflow-x:hidden}
.desk{min-height:100vh;position:relative;background:var(--teal);
  padding:14px max(12px,env(safe-area-inset-left,0px)) calc(62px + env(safe-area-inset-bottom,0px)) max(12px,env(safe-area-inset-right,0px))}

/* window chrome */
.win{max-width:400px;margin:0 auto;background:var(--face);
  border:2px solid;border-color:var(--lt) var(--dk) var(--dk) var(--lt);
  box-shadow:1px 1px 0 var(--sh),3px 3px 10px #0000004d}
.win>.in{border:1px solid;border-color:var(--sh) var(--lt) var(--lt) var(--sh);padding:2px}
.tb{background:linear-gradient(90deg,var(--navy),var(--navy2));color:#fff;
  display:flex;justify-content:space-between;align-items:center;padding:3px 3px 3px 6px;font-weight:700;gap:8px}
.tb .name{display:flex;align-items:center;gap:6px;min-width:0}
.tb .name svg{width:16px;height:16px;flex:none}
.tb .name span{overflow:hidden;text-overflow:ellipsis;white-space:nowrap}
.tb .btns{display:flex;gap:2px;flex:none}
.tb .btns b{width:18px;height:16px;background:var(--face);border:2px solid;border-color:var(--hi) var(--dk) var(--dk) var(--hi);
  color:#000;font:700 11px/12px var(--font);text-align:center;cursor:pointer;user-select:none}
.menu{display:flex;gap:10px;padding:3px 8px;font-size:12px;position:relative}
.menu .mitem{position:relative}
.menu .mlabel{cursor:pointer;padding:1px 5px;display:inline-block;user-select:none}
.menu .mlabel.open{background:var(--navy);color:#fff}
.dropdown{position:absolute;top:100%;left:0;z-index:30;min-width:186px;margin:1px 0 0;padding:2px;list-style:none;
  background:var(--face);border:2px solid;border-color:var(--hi) var(--dk) var(--dk) var(--hi);box-shadow:3px 3px 7px #00000055}
.dropdown[hidden]{display:none}
.dropdown li a{display:block;padding:6px 18px 6px 10px;color:#000;text-decoration:none;white-space:nowrap}
.dropdown li a:hover,.dropdown li a:focus{background:var(--navy);color:#fff}
.dropdown li.sep{height:1px;background:var(--sh);border-bottom:1px solid var(--hi);margin:3px 2px}
.body{padding:12px 12px 8px}
/* about modal */
.modal{position:fixed;inset:0;z-index:50;background:#00000044;display:flex;align-items:center;justify-content:center;padding:20px}
.modal[hidden]{display:none}
.awin{max-width:300px;width:100%}
.abody{padding:14px}
.arow{display:flex;gap:12px;align-items:flex-start}
.arow .logo{flex:none;width:42px;height:42px}
.abody .ver{font-weight:700;font-size:14px}
.abody p{margin:7px 0 0}

/* buttons */
.b95{background:var(--face);border:2px solid;border-color:var(--hi) var(--dk) var(--dk) var(--hi);
  padding:6px 12px;font:13px var(--font);color:#000;text-decoration:none;cursor:pointer;display:inline-block}
.b95:active{border-color:var(--dk) var(--hi) var(--hi) var(--dk)}
.b95:focus-visible{outline:1px dotted #000;outline-offset:-4px}

/* dialog + right-aligned OK */
.dlg{display:flex;gap:12px;align-items:flex-start}
.warn{flex:none}.warn svg{width:40px;height:40px}
.dlg .msg b{font-size:14px}
.dlgbtns{display:flex;justify-content:flex-end;margin:10px 0 2px}
.dlgbtns .b95{min-width:84px;text-align:center}
.dlg[hidden],.dlgbtns[hidden]{display:none}

/* ===== HERO : Qui suis-je ===== */
.hero{margin-top:14px;border:2px solid;border-color:var(--sh) var(--lt) var(--lt) var(--sh);background:#fff}
.hero .cap{background:linear-gradient(90deg,var(--navy),var(--navy2));color:#fff;font-weight:700;padding:4px 8px;display:flex;align-items:center;gap:6px}
.hero .cap svg{width:14px;height:14px}
.hero .inner{padding:14px 13px;display:flex;gap:13px;align-items:flex-start}
.avatar{flex:none;width:84px;height:84px;border:2px solid;border-color:var(--sh) var(--lt) var(--lt) var(--sh);background:#d8e4e4}
.avatar svg,.avatar img{width:100%;height:100%;display:block;object-fit:cover}
.hero .who{min-width:0}
.hero .nm{font-size:21px;font-weight:700;line-height:1.1}
.hero .role{font-family:var(--mono);font-size:11px;color:#007a7a;text-transform:uppercase;letter-spacing:.04em;margin-top:3px}
.hero .desc{margin-top:8px}
.seek{margin:0 13px 14px;background:var(--yellow);border:2px solid;border-color:var(--dk) #b89a00 #b89a00 var(--dk);
  padding:9px 11px;font-weight:700;display:flex;gap:9px;align-items:center}
.seek .txt{min-width:0}
.seek b{color:#b5121b}
.seek .dispo{display:inline-block;margin-top:5px;font-size:14px;font-weight:700;background:var(--navy);color:#fff;padding:3px 8px}
.newbadge{flex:none;background:#c00;color:#fff;font:800 10px/1 var(--mono);padding:4px 5px;border-radius:2px;transform:rotate(-8deg);
  box-shadow:1px 1px 0 #600}
@media(prefers-reduced-motion:no-preference){.newbadge{animation:pulse 1.1s ease-in-out infinite}}
@keyframes pulse{50%{transform:rotate(-8deg) scale(1.14)}}

/* alternance marquee (decorative) */
.alt{margin-top:2px;background:var(--navy);color:#fff;overflow:hidden;white-space:nowrap;padding:7px 0;font-weight:700}
.alt .track{display:inline-block;padding-left:100%;animation:mq 18s linear infinite}
.alt .track .star{color:#ff0}
@keyframes mq{to{transform:translateX(-100%)}}
@media(prefers-reduced-motion:reduce){.alt{white-space:normal;padding:7px 10px}.alt .track{display:block;padding-left:0;animation:none}}

/* group boxes */
fieldset{border:1px solid;border-color:var(--sh) var(--lt) var(--lt) var(--sh);margin:14px 0 0;padding:14px 10px 10px;position:relative;min-width:0}
fieldset>legend{position:absolute;top:-8px;left:8px;background:var(--face);padding:0 5px;font-weight:700;font-size:12px}

/* contact */
.hint{font-size:11px;color:#303030;margin:0 0 7px}
.links{display:grid;gap:8px}
.links .b95{display:flex;align-items:center;gap:9px;padding:9px 12px;width:100%;text-align:left}
.links .b95 svg{width:20px;height:20px;flex:none}
.links .b95 .lbl{font-weight:700;flex:none}
.links .b95 .u{margin-left:auto;font-family:var(--mono);font-size:11px;color:var(--navy);min-width:0;overflow:hidden;text-overflow:ellipsis;white-space:nowrap;user-select:all}
.site{text-align:center;font:700 19px var(--mono);color:var(--navy);background:#fff;border:2px solid;border-color:var(--sh) var(--lt) var(--lt) var(--sh);padding:11px 8px;margin:0 0 12px;user-select:all;word-break:break-all;cursor:pointer}
.copied{color:#0a7a20;font-weight:700}
.warn{color:#b5121b;font-weight:700}

/* progress + diagnostic (secondary) */
.prog{margin:10px 0 2px}
.prog .lbl{font-size:12px;margin-bottom:4px}
.pbar{height:18px;background:#fff;border:2px solid;border-color:var(--sh) var(--lt) var(--lt) var(--sh);padding:2px;display:flex;gap:2px;overflow:hidden}
.pbar i{width:9px;flex:none;background:var(--navy);display:block}
.field{background:#fff;border:2px solid;border-color:var(--sh) var(--lt) var(--lt) var(--sh);padding:7px 8px;font-family:var(--mono);font-size:12px}
.field .rowi{display:flex;justify-content:space-between;gap:10px;padding:2px 0}
.field .rowi+.rowi{border-top:1px dotted #c7c7c7}
.field .an{color:var(--navy);font-family:var(--font);font-style:italic;display:block;padding:1px 0 3px}

/* status + note */
.status{display:flex;gap:4px;margin-top:12px}
.status span{border:1px solid;border-color:var(--sh) var(--lt) var(--lt) var(--sh);padding:2px 6px;font-size:11px;color:#303030}
.status span:first-child{flex:1;min-width:0;overflow:hidden;text-overflow:ellipsis;white-space:nowrap}
.status span.r{flex:none}
.note{color:#303030;font-size:11px;margin:10px 2px 0;line-height:1.5}

/* taskbar */
.task{position:fixed;left:0;right:0;bottom:0;min-height:34px;background:var(--face);
  border-top:2px solid var(--hi);display:flex;align-items:center;gap:6px;z-index:20;
  padding:3px max(6px,env(safe-area-inset-right,0px)) calc(3px + env(safe-area-inset-bottom,0px)) max(6px,env(safe-area-inset-left,0px))}
.start{display:flex;align-items:center;gap:5px;font-weight:700;padding:4px 10px 4px 7px;
  border:2px solid;border-color:var(--hi) var(--dk) var(--dk) var(--hi);background:var(--face);cursor:pointer;user-select:none}
.start.open{border-color:var(--dk) var(--hi) var(--hi) var(--dk);background:#b0b0b0}
.start svg{width:18px;height:16px}
.taskbtn{flex:1;min-width:0;display:flex;align-items:center;gap:6px;padding:4px 8px;
  border:2px solid;border-color:var(--dk) var(--hi) var(--hi) var(--dk);background:#bdbdbd;
  font-weight:700;overflow:hidden;white-space:nowrap;text-overflow:ellipsis}
.taskbtn svg{width:14px;height:14px;flex:none}
.clock{flex:none;border:1px solid;border-color:var(--sh) var(--lt) var(--lt) var(--sh);
  padding:4px 9px;font-size:12px;font-variant-numeric:tabular-nums}

/* start menu */
.startmenu{position:fixed;left:6px;bottom:calc(40px + env(safe-area-inset-bottom,0px));width:210px;z-index:25;
  background:var(--face);border:2px solid;border-color:var(--hi) var(--dk) var(--dk) var(--hi);box-shadow:3px 3px 8px #00000055}
.startmenu[hidden]{display:none}
.startmenu .rail{display:flex}
.startmenu .side{writing-mode:vertical-lr;transform:rotate(180deg);background:linear-gradient(0deg,var(--navy),var(--navy2));
  color:#fff;font-weight:800;letter-spacing:1px;padding:10px 5px;text-align:right}
.startmenu ul{list-style:none;margin:0;padding:3px;flex:1}
.startmenu li a{display:block;padding:7px 9px;color:#000;text-decoration:none}
.startmenu li a:hover,.startmenu li a:focus{background:var(--navy);color:#fff}
.startmenu .sep{height:1px;background:var(--sh);border-bottom:1px solid var(--hi);margin:3px 2px}

/* BSOD easter egg */
.bsod{position:fixed;inset:0;z-index:60;background:#0000aa;color:#fff;font-family:var(--mono);
  font-size:14px;line-height:1.7;padding:34px 20px;display:flex;flex-direction:column;gap:18px;justify-content:center}
.bsod[hidden]{display:none}
.bsod .h{background:#aaa;color:#0000aa;font-weight:700;padding:1px 10px;align-self:center}
.bsod .k{color:#fff}
.bsod .blink::after{content:"_";animation:bk 1s steps(1) infinite}
@keyframes bk{50%{opacity:0}}
@media(prefers-reduced-motion:reduce){.bsod .blink::after{animation:none}}
</style>
</head>
<body>

<div class="desk">
  <div class="win"><div class="in">
    <div class="tb">
      <span class="name">
        <svg viewBox="0 0 16 16" aria-hidden="true"><rect x="1" y="2" width="14" height="11" fill="#fff" stroke="#000"/><rect x="1" y="2" width="14" height="3" fill="#000080"/><path d="M5 14h6M8 13v1" stroke="#000"/></svg>
        <span>Ce_WiFi_est_un_piege.exe</span>
      </span>
      <span class="btns"><b id="btnMin">_</b><b>□</b><b id="btnClose" title="Fermer">×</b></span>
    </div>
    <div class="menu" id="menubar">
      <div class="mitem"><span class="mlabel" data-menu="file"><u>F</u>ichier</span>
        <ul class="dropdown" id="mFile" hidden>
          <li><a href="#" data-act="toast" data-msg="Nouveau piège : il y en a déjà un. Juste là. Autour de vous.">Nouveau piège</a></li>
          <li><a href="#" data-copy="https://caillier-romain.fr/">Copier mon portfolio</a></li>
          <li><a href="#" data-act="toast" data-msg="Curiosité enregistrée. Merci d'être passé.">Enregistrer la curiosité</a></li>
          <li class="sep"></li>
          <li><a href="#" data-act="bsod">Quitter</a></li>
        </ul>
      </div>
      <div class="mitem"><span class="mlabel" data-menu="edit"><u>É</u>dition</span>
        <ul class="dropdown" id="mEdit" hidden>
          <li><a href="#" data-act="toast" data-msg="Annuler ? Trop tard, vous êtes déjà dans le piège.">Annuler</a></li>
          <li><a href="#" data-copy="https://caillier-romain.fr/">Copier mon lien</a></li>
          <li><a href="#" data-act="toast" data-msg="Tout est déjà à vous : il suffit de regarder en dessous.">Tout sélectionner</a></li>
        </ul>
      </div>
      <div class="mitem"><span class="mlabel" id="btnHelp" data-menu="help"><u>?</u></span></div>
    </div>
    <div class="body">

      <div class="dlg" id="warnDlg">
        <span class="warn"><svg viewBox="0 0 40 40" aria-hidden="true"><path d="M20 3 L38 36 H2 Z" fill="#ffd13b" stroke="#000" stroke-width="1.8" stroke-linejoin="round"/><rect x="18" y="14" width="4" height="12" fill="#000"/><rect x="18" y="28" width="4" height="4" fill="#000"/></svg></span>
        <div class="msg"><b>Vous êtes tombé dans le piège.</b><br>Votre seul tort : avoir été curieux. Rassurez-vous, rien n'est conservé.</div>
      </div>
      <div class="dlgbtns" id="warnBtns"><a class="b95" href="#" role="button" id="btnOk">OK</a></div>

      <!-- HERO : qui suis-je -->
      <div class="hero">
        <div class="cap"><svg viewBox="0 0 16 16" aria-hidden="true"><rect x="2" y="2" width="12" height="12" fill="#fff" stroke="#000"/><circle cx="8" cy="6.5" r="2.3" fill="#000"/><path d="M4 13c0-2.6 2-3.6 4-3.6s4 1 4 3.6" fill="#000"/></svg> Qui suis-je</div>
        <div class="inner">
          <div class="avatar"><img src="data:image/png;base64,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" alt="Avatar pixel-art de Romain à son bureau de maker" width="128" height="128"></div>
          <div class="who">
            <div class="nm">Romain Caillier</div>
            <div class="role">Dév &amp; Sécurité · École 42</div>
            <div class="desc">Je construis des trucs, je cherche leurs failles et parfois je diffuse du Wi-Fi pour les curieux.</div>
          </div>
        </div>
        <div class="seek">
          <span class="newbadge" aria-hidden="true">NEW!</span>
          <span class="txt">Je cherche une <b>alternance</b> en <b>développement, sécurité ou DevSecOps</b>.<br><span class="dispo">Disponible dès juin 2027</span></span>
        </div>
      </div>

      <div class="alt"><span class="track"><span class="star">★</span> ALTERNANCE DÈS JUIN 2027 — ON VIENT DE SE RENCONTRER, QUEL HASARD <span class="star">★</span></span></div>

      <fieldset><legend>Contact</legend>
        <p class="hint">Les liens ne s'ouvrent pas ici (réseau sans Internet). Le plus simple : retiens mon site, tout y est.</p>
        <div class="site" role="button" tabindex="0" data-copy="https://caillier-romain.fr/">caillier-romain.fr</div>
        <p class="hint">Ou appuie pour copier, puis colle dans ton navigateur :</p>
        <div class="links">
          <button type="button" class="b95" data-copy="https://github.com/rom98759/"><svg viewBox="0 0 20 20" aria-hidden="true"><rect width="20" height="20" rx="2" fill="#24292e"/><path d="M10 4a6 6 0 0 0-1.9 11.7c.3.06.4-.13.4-.29v-1c-1.7.37-2-.72-2-.72-.28-.7-.68-.89-.68-.89-.56-.38.04-.37.04-.37.62.04.94.63.94.63.55.94 1.44.67 1.8.51.05-.4.21-.67.39-.82-1.36-.16-2.78-.68-2.78-3.02 0-.67.24-1.21.63-1.64-.06-.16-.27-.78.06-1.62 0 0 .51-.16 1.68.63a5.8 5.8 0 0 1 3.06 0c1.17-.79 1.68-.63 1.68-.63.33.84.12 1.46.06 1.62.39.43.63.97.63 1.64 0 2.35-1.43 2.86-2.79 3.01.22.19.41.56.41 1.13v1.67c0 .16.1.35.41.29A6 6 0 0 0 10 4z" fill="#fff"/></svg><span class="lbl">GitHub</span><span class="u">github.com/rom98759</span></button>
          <button type="button" class="b95" data-copy="https://caillier-romain.fr/"><svg viewBox="0 0 20 20" aria-hidden="true"><circle cx="10" cy="10" r="8" fill="#007a7a"/><g fill="none" stroke="#fff" stroke-width="1"><circle cx="10" cy="10" r="8"/><ellipse cx="10" cy="10" rx="3.3" ry="8"/><line x1="2" y1="10" x2="18" y2="10"/><line x1="4" y1="5.5" x2="16" y2="5.5"/><line x1="4" y1="14.5" x2="16" y2="14.5"/></g></svg><span class="lbl">Portfolio</span><span class="u">caillier-romain.fr</span></button>
          <button type="button" class="b95" data-copy="https://www.linkedin.com/in/romain-caillier"><svg viewBox="0 0 20 20" aria-hidden="true"><rect width="20" height="20" rx="2" fill="#0a66c2"/><circle cx="5.5" cy="5.5" r="1.6" fill="#fff"/><rect x="4.1" y="8.3" width="2.8" height="7.6" fill="#fff"/><path d="M8.5 8.3h2.7v1.1c.4-.7 1.3-1.3 2.6-1.3 2.1 0 2.9 1.3 2.9 3.6v4.2h-2.8v-3.8c0-1-.4-1.6-1.3-1.6-.8 0-1.3.5-1.3 1.6v3.8H8.5z" fill="#fff"/></svg><span class="lbl">LinkedIn</span><span class="u">in/romain-caillier</span></button>
        </div>
      </fieldset>

      <div class="prog">
        <div class="lbl">Analyse de votre curiosité… <b id="pct">0%</b></div>
        <div class="pbar" id="pbar"></div>
      </div>

      <fieldset><legend>Au passage, détecté sur vous</legend>
        <div class="field" id="diag"><noscript>Activez JavaScript pour voir ce que votre navigateur révèle, en direct et sans rien envoyer.</noscript></div>
        <p class="note" style="margin-bottom:0">Mesuré dans votre navigateur, à l'instant. Rien n'est envoyé, stocké, ni relié à vous.</p>
      </fieldset>

      <div class="status"><span id="st">Piège armé et opérationnel.</span><span class="r" id="cnt">Curieux : 023</span></div>
      <p class="note">Pour partir : oubliez le réseau « Ce_WiFi_est_un_piege ». Il ne vous en voudra pas.</p>

    </div>
  </div></div>
</div>

<!-- start menu -->
<nav class="startmenu" id="startmenu" hidden>
  <div class="rail">
    <div class="side">Romain&nbsp;95</div>
    <ul>
      <li><a href="#diag" id="smRun">Exécuter le diagnostic…</a></li>
      <li><a href="#" data-copy="https://caillier-romain.fr/">Mes projets</a></li>
      <li><a href="#" data-copy="https://github.com/rom98759/">Documents (GitHub)</a></li>
      <div class="sep"></div>
      <li><a href="#" id="smAbout">À propos…</a></li>
      <li><a href="#" id="smShutdown">Arrêter…</a></li>
    </ul>
  </div>
</nav>

<!-- about dialog -->
<div class="modal" id="about" hidden>
  <div class="win awin"><div class="in">
    <div class="tb"><span class="name"><svg viewBox="0 0 16 16" aria-hidden="true"><rect x="1" y="2" width="14" height="11" fill="#fff" stroke="#000"/><rect x="1" y="2" width="14" height="3" fill="#000080"/></svg> À propos de piège.exe</span><span class="btns"><b id="aboutClose">×</b></span></div>
    <div class="body abody">
      <div class="arow">
        <span class="logo"><svg viewBox="0 0 40 40" aria-hidden="true"><path d="M20 3 L38 36 H2 Z" fill="#ffd13b" stroke="#000" stroke-width="1.8" stroke-linejoin="round"/><rect x="18" y="14" width="4" height="12" fill="#000"/><rect x="18" y="28" width="4" height="4" fill="#000"/></svg></span>
        <div>
          <div class="ver">piège.exe — version 2.0</div>
          <div style="font-family:var(--mono);font-size:11px;color:#404040">« édition Curiosité »</div>
          <p>© 2026 Romain Caillier.<br>Aucun curieux n'a été blessé durant cette démo.</p>
        </div>
      </div>
      <div class="dlgbtns"><a class="b95" href="#" id="aboutOk" style="min-width:84px;text-align:center">OK</a></div>
    </div>
  </div></div>
</div>

<!-- taskbar -->
<div class="task">
  <span class="start" id="startBtn"><svg viewBox="0 0 18 16" aria-hidden="true"><g transform="skewY(-8)"><path d="M1 4 L7 3 L7 8 L1 9 Z" fill="#e8443a"/><path d="M8 3 L15 2 L15 7 L8 8 Z" fill="#45b556"/><path d="M1 10 L7 9 L7 14 L1 15 Z" fill="#2f7fd0"/><path d="M8 9 L15 8 L15 13 L8 14 Z" fill="#f2c100"/></g></svg>Démarrer</span>
  <span class="taskbtn"><svg viewBox="0 0 16 16" aria-hidden="true"><rect x="1" y="2" width="14" height="11" fill="#fff" stroke="#000"/><rect x="1" y="2" width="14" height="3" fill="#000080"/></svg>piège.exe</span>
  <span class="clock" id="clock">12:00</span>
</div>

<!-- BSOD easter egg -->
<div class="bsod" id="bsod" hidden>
  <div class="h">Windows</div>
  <div>Un problème a été détecté et le piège a été interrompu pour éviter toute fuite de curiosité.</div>
  <div class="k">*** STOP : 0xCUR1EUX (0x0042, 0x2027)<br>CURIOSITY_NOT_HANDLED</div>
  <div>Vous ne partirez pas si facilement. Au moins, embauchez-moi.</div>
  <div class="blink">Touchez l'écran pour revenir </div>
</div>

<script>
// ---- live client-side diagnostic (punchline instead of fake value) ----
(function(){
  var box=document.getElementById("diag");if(!box)return;
  var ua=navigator.userAgent,os="",br="",m;
  if(m=ua.match(/Android [\d.]+/))os=m[0];
  else if(m=ua.match(/(iPhone|iPad)[^;]*OS ([\d_]+)/))os=m[1]+" iOS "+m[2].replace(/_/g,".");
  else if(/Windows NT 10/.test(ua))os="Windows 10/11";
  else if(/Mac OS X/.test(ua))os="macOS";
  else if(/Linux/.test(ua))os="Linux";
  if(/Firefox\//.test(ua))br="Firefox";else if(/Edg\//.test(ua))br="Edge";
  else if(/OPR\//.test(ua))br="Opera";else if(/Chrome\//.test(ua))br="Chrome";
  else if(/Safari\//.test(ua))br="Safari";
  var sys=(os&&br)?os+" / "+br:(os||br||"");
  var tz="";try{tz=Intl.DateTimeFormat().resolvedOptions().timeZone||""}catch(e){}
  var gpu="";try{
    var cv=document.createElement("canvas"),gl=cv.getContext("webgl")||cv.getContext("experimental-webgl"),
    dbg=gl&&gl.getExtension("WEBGL_debug_renderer_info");
    if(dbg)gpu=gl.getParameter(dbg.UNMASKED_RENDERER_WEBGL)||"";
  }catch(e){}
  var conn=navigator.connection||{};
  var langs=(navigator.languages&&navigator.languages.slice(0,3).join(", "))||navigator.language||"";
  var dnt=(navigator.doNotTrack==="1"||window.doNotTrack==="1")?"demandé (mignon)":"non demandé";
  var rows=[
    ["Appareil",sys,sys?"":"un appareil mystérieux. J'aime."],
    ["Nom de l'appareil","hors de portée",""],
    ["Plateforme",navigator.platform||"",""],
    ["Navigateur",br,""],
    ["Écran",screen.width+"×"+screen.height+" @"+(window.devicePixelRatio||1)+"x",""],
    ["Couleurs",(screen.colorDepth||"")&&(screen.colorDepth+" bits"),""],
    ["Fenêtre",window.innerWidth+"×"+window.innerHeight,""],
    ["Carte graphique",gpu||"masquée",gpu?"oui, je la connais. non, pas pour miner.":"bien joué de l'avoir cachée."],
    ["Cœurs CPU",(navigator.hardwareConcurrency||"")&&(navigator.hardwareConcurrency+""),""],
    ["Langues",langs,""],
    ["Fuseau",tz,tz?"votre horloge a parlé.":"vous gardez vos secrets."],
    ["Thème",matchMedia("(prefers-color-scheme: dark)").matches?"sombre":"clair",""],
    ["Réseau",conn.effectiveType||"",conn.downlink?"~"+conn.downlink+" Mb/s en descente.":""],
    ["Cookies",navigator.cookieEnabled?"activés":"désactivés",""],
    ["Ne pas suivre",dnt,""],
    ["En ligne",navigator.onLine?"oui… enfin, presque":"non (vous êtes dans le piège)",""]
  ];
  box.textContent="";
  function addRow(k,v,an){var row=document.createElement("div");row.className="rowi";
    var ks=document.createElement("span");ks.textContent=k;var vs=document.createElement("span");vs.textContent=v;
    row.appendChild(ks);row.appendChild(vs);box.appendChild(row);
    if(an){var a=document.createElement("span");a.className="an";a.textContent="↳ "+an;box.appendChild(a);}}
  rows.forEach(function(r){
    var v=r[1],an=r[2];
    if(!v){if(!an)return;v="indisponible";}     // hide boring unavailable fields
    addRow(r[0],v,an);
  });
  if(navigator.getBattery)navigator.getBattery().then(function(b){
    addRow("Batterie",Math.round(b.level*100)+"%"+(b.charging?" (charge)":""),b.level<.3?"pensez à charger.":"large pour la journée.");
    done();
  }).catch(function(){addRow("Batterie","indisponible","même moi, je ne peux pas tout savoir.");done();});
  else{addRow("Batterie","indisponible","même moi, je ne peux pas tout savoir.");done();}
  function done(){var a=document.createElement("span");a.className="an";
    a.textContent="↳ … et j'ai arrêté là, par politesse.";box.appendChild(a);}
})();
// ---- segmented progress + synced % ----
(function(){
  var bar=document.getElementById("pbar"),pct=document.getElementById("pct");if(!bar)return;
  var reduce=matchMedia("(prefers-reduced-motion: reduce)").matches;
  var total=Math.max(6,Math.floor(bar.clientWidth/11)),n=0;
  function set(){if(pct)pct.textContent=Math.round(n/total*100)+"%";}
  function step(){bar.appendChild(document.createElement("i"));n++;set();
    if(n<total)setTimeout(step,70);else if(pct)pct.textContent="Terminé";}
  if(reduce){for(var k=0;k<total;k++)bar.appendChild(document.createElement("i"));if(pct)pct.textContent="Terminé";}
  else step();
})();
// ---- taskbar clock ----
(function(){var c=document.getElementById("clock");if(!c)return;
  function t(){var d=new Date();c.textContent=("0"+d.getHours()).slice(-2)+":"+("0"+d.getMinutes()).slice(-2);}
  t();setInterval(t,10000);})();
// ---- start menu ----
(function(){
  var btn=document.getElementById("startBtn"),menu=document.getElementById("startmenu");
  function toggle(open){var show=open===undefined?menu.hidden:open;menu.hidden=!show;btn.classList.toggle("open",show);}
  btn.addEventListener("click",function(e){e.stopPropagation();toggle();});
  document.addEventListener("click",function(e){if(!menu.hidden&&!menu.contains(e.target))toggle(false);});
  document.getElementById("smAbout").addEventListener("click",function(e){e.preventDefault();toggle(false);openAbout();});
  document.getElementById("smShutdown").addEventListener("click",function(e){e.preventDefault();toggle(false);showBsod();});
})();
// ---- easter egg : close button / about / shutdown -> fake BSOD ----
var bsod=document.getElementById("bsod");
function showBsod(){bsod.hidden=false;}
function hideBsod(){bsod.hidden=true;}
document.getElementById("btnClose").addEventListener("click",showBsod);
bsod.addEventListener("click",hideBsod);
document.addEventListener("keydown",function(e){if(!bsod.hidden){hideBsod();}});
// ---- status-bar helper (transient messages) ----
var stEl=document.getElementById("st"),stTimer;
function setStatus(msg){if(!stEl)return;stEl.textContent=msg;clearTimeout(stTimer);
  stTimer=setTimeout(function(){stEl.textContent="Piège armé et opérationnel.";},4000);}
// Counting beacon + clipboard copy. The portal is http (not a secure context),
// so navigator.clipboard may be unavailable: fall back to execCommand.
function fireBeacon(path){try{if(navigator.sendBeacon)navigator.sendBeacon(path);
  else fetch(path,{method:"POST",keepalive:true}).catch(function(){});}catch(e){}}
// ---- visit stats for the badge: it has no clock, so this phone's time dates the visit ----
(function(){
  var t0=Date.now(),ua=navigator.userAgent,os=0,br=0;
  if(/iPhone|iPad|iPod/.test(ua))os=1;else if(/Android/.test(ua))os=2;else if(/Windows/.test(ua))os=3;
  else if(/Mac OS X/.test(ua))os=4;else if(/Linux/.test(ua))os=5;
  if(/SamsungBrowser\//.test(ua))br=5;else if(/Firefox\/|FxiOS/.test(ua))br=3;else if(/Edg/.test(ua))br=4;
  else if(/OPR\//.test(ua))br=6;else if(/Chrome\/|CriOS/.test(ua))br=2;else if(/Safari\//.test(ua))br=1;
  fireBeacon("/hi?t="+Math.floor(t0/1000)+"&d="+(os*16+br));
  function bye(){fireBeacon("/bye?s="+Math.round((Date.now()-t0)/1000));}
  addEventListener("pagehide",bye);
  document.addEventListener("visibilitychange",function(){if(document.hidden)bye();});
})();
function linkCode(u){return /caillier-romain/.test(u)?1:/github/.test(u)?2:/linkedin/.test(u)?3:0;}
function copyText(t){
  if(navigator.clipboard&&navigator.clipboard.writeText)
    return navigator.clipboard.writeText(t).then(function(){return true;},_exec);
  return Promise.resolve(_exec());
  function _exec(){try{var ta=document.createElement("textarea");ta.value=t;ta.setAttribute("readonly","");
    ta.style.position="fixed";ta.style.top="-1000px";document.body.appendChild(ta);ta.select();
    var ok=document.execCommand("copy");document.body.removeChild(ta);return ok;}catch(e){return false;}}
}
// ---- menu-bar dropdowns (Fichier / Édition / ?) ----
(function(){
  var bar=document.getElementById("menubar");if(!bar)return;
  var labels=[].slice.call(bar.querySelectorAll(".mlabel[data-menu]"));
  var drops={file:document.getElementById("mFile"),edit:document.getElementById("mEdit")};
  function closeAll(){for(var k in drops)if(drops[k])drops[k].hidden=true;
    labels.forEach(function(l){l.classList.remove("open");});}
  labels.forEach(function(l){l.addEventListener("click",function(e){
    e.stopPropagation();var m=l.getAttribute("data-menu");
    if(m==="help"){closeAll();openAbout();return;}
    var d=drops[m],willOpen=d&&d.hidden;closeAll();
    if(willOpen){d.hidden=false;l.classList.add("open");}
  });});
  [].slice.call(bar.querySelectorAll(".dropdown a")).forEach(function(a){a.addEventListener("click",function(e){
    var act=a.getAttribute("data-act");
    if(act){e.preventDefault();
      if(act==="toast")setStatus(a.getAttribute("data-msg"));
      else if(act==="bsod")showBsod();
    }
    closeAll();
  });});
  document.addEventListener("click",function(e){if(!bar.contains(e.target))closeAll();});
})();
// ---- about dialog ----
var about=document.getElementById("about");
function openAbout(){if(about)about.hidden=false;}
function closeAbout(){if(about)about.hidden=true;}
document.getElementById("aboutOk").addEventListener("click",function(e){e.preventDefault();closeAbout();});
document.getElementById("aboutClose").addEventListener("click",closeAbout);
about.addEventListener("click",function(e){if(e.target===about)closeAbout();});
// ---- OK on the warning: dismiss + count one more curious soul ----
document.getElementById("btnOk").addEventListener("click",function(e){
  e.preventDefault();
  var d=document.getElementById("warnDlg"),b=document.getElementById("warnBtns");
  if(d)d.hidden=true;if(b)b.hidden=true;
  setStatus("Curiosité enregistrée. Bien joué.");
});
// ---- real counters from the badge (fails silently offline / standalone) ----
(function(){
  var cnt=document.getElementById("cnt");
  function pad(n){return ("00"+n).slice(-3);}
  try{fetch("/count",{cache:"no-store"}).then(function(r){return r.ok?r.text():"";}).then(function(t){
    var p=t.split(","),c=parseInt(p[0],10),k=parseInt(p[1],10);
    if(cnt&&!isNaN(c))cnt.textContent="Curieux : "+pad(c)+(!isNaN(k)?" · liens "+k:"");
  }).catch(function(){});}catch(e){}
  // Copy-to-clipboard for any [data-copy] control (links can't open here).
  document.addEventListener("click",function(e){
    var el=e.target&&e.target.closest?e.target.closest("[data-copy]"):null;
    if(!el)return;
    e.preventDefault();
    fireBeacon("/click?l="+linkCode(el.getAttribute("data-copy")));
    var fb=(el.querySelector&&el.querySelector(".u"))||el;
    copyText(el.getAttribute("data-copy")).then(function(ok){
      setStatus(ok?"Copié ! Colle-le dans ton navigateur.":"Sélectionne l'adresse, puis copie-la.");
      if(fb){
        if(!fb.getAttribute("data-full"))fb.setAttribute("data-full",fb.textContent);
        fb.textContent=ok?"✓ copié !":"à sélectionner";
        fb.classList.add(ok?"copied":"warn");
        clearTimeout(fb._t);fb._t=setTimeout(function(){
          fb.textContent=fb.getAttribute("data-full");fb.classList.remove("copied","warn");
        },1800);
      }
    });
    var sm=document.getElementById("startmenu");if(sm)sm.hidden=true;
    var sb=document.getElementById("startBtn");if(sb)sb.classList.remove("open");
  },true);
})();
</script>
</body>
</html>

)HTML";
