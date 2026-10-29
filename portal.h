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
.find .photo{background:#fff;border:2px solid;border-color:var(--sh) var(--lt) var(--lt) var(--sh);padding:3px;max-width:260px;margin:2px auto 8px}
.find img{display:block;width:100%;height:auto}
.find .hint{text-align:center;margin:0}
.links .b95{display:flex;align-items:center;gap:9px;padding:9px 12px;width:100%;text-align:left}
.links .b95 svg,.vcf svg{width:20px;height:20px;flex:none}
.vcf{display:flex;align-items:center;gap:9px;padding:9px 12px;color:inherit;text-decoration:none;font-weight:700}
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
        <span><span class="ssid">Ce_WiFi_est_un_piege</span>.exe</span>
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
        <div class="msg"><b>Vous êtes tombé dans le piège.</b><br>Votre seul tort : avoir été curieux.</div>
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

      <fieldset class="find"><legend>Où me trouver ?</legend>
        <div class="photo"><img src="data:image/jpeg;base64,/9j/4AAQSkZJRgABAQAAAQABAAD/2wBDAAoHCAkIBgoJCAkMCwoMDxoRDw4ODx8WGBMaJSEnJiQhJCMpLjsyKSw4LCMkM0Y0OD0/QkNCKDFITUhATTtBQj//2wBDAQsMDA8NDx4RER4/KiQqPz8/Pz8/Pz8/Pz8/Pz8/Pz8/Pz8/Pz8/Pz8/Pz8/Pz8/Pz8/Pz8/Pz8/Pz8/Pz8/Pz//wgARCAGQAZADASIAAhEBAxEB/8QAGwAAAgMBAQEAAAAAAAAAAAAAAQIAAwQFBgf/xAAaAQEBAQEBAQEAAAAAAAAAAAAAAQIDBAUG/9oADAMBAAIQAxAAAAHT0M2j53sr816LztmPscdvf5M1nX5Flb0WY6d++nT8/wBgKEmW7l6lFKn08W6PP7ONVX6L/P1y7Qc29ZM2skiraAxYFSbESxRFdQEQYRR7arVsErjFS9XXNnD7fF68vaGLw60+d73A688FOnN7vJ6ridjgpiuy3zfo9/K6/wA/2ULbmlz8nVi9PIo9HXlu73I7fl9FjKeGzFNWtW+UkClYCQQMgDIRQyiBlsgkLLK3HotzGPOy9s6eP3OLvHsq2p83XJwuzwvVwopuo9fmttplZduXtZ0nf5W7w+psOnmzWOkj18DRam+fY6/D7ni9VkB5bJjSx1MFYAgSjFIQCErIKmFcZLAQw9lbk5+3mbnO1YOl2xq53Wz89djNdk56x8bfzvd5aqrau/HS1e/nvk9fk9s7WBdHl9OTl7uXuVFT34KiHeOv3+d0fn+xnSzltiCskUiwJICQgkkARAMVJK7KwMllNAg2S6WYtGwCI4ltx38+zJiav6Pipi7d5zdzib+PXn2LXvHqr8+XzenPy+3wumLb9HV578z1eq+KpccuksSzJhAQSAUqQyEIAYAEBasauyGqtrlrsRtRslvO3LNHMv3Oq+O7lQBdLn5Ozj+nkarKfZ5FsqFC288ulNd9Fz3nxdPz+lOXZfrGvZnv8nclWgwxY6tEHIHXHYHKB1Ry2OlObJeiOeTdMLmkSY01iWQ1dlUqqw3nNzt3N7Ze2prN9uPVz1bdmtxeThuo93mTNZT24y7P1Mb1Van8nqwc3ucP0+bqdPT6nN8Hb7G8823oVxeA/bU4866JzT0Vrxae2no4+KPsweOb1sPKT1SnmG9JDzt/ZkKwnLo1lGuWvPpmdcYFPL6ceDZl74MJWzZi14XizLjXFpsz/S8KoVsHd4/e4dzr5/T83fP5z0/nPRw9T0+Zb381WEdC3Nj7fA6c7Bjs1NDYyaZnBsWqs0KlRpNUL+tzva415Sv0GfLHzPbeZXTk9Rijxvb4tnXPoNnnu/5u3IrbN4fdnpcdchoZW149Ma8lujDylEX6XhAIN3YxdLx+unbm08tp530Pm+/H1tNvd9fk8n2txOHy/XxPHn14rx49iDxj+vB5I+rh5KetC+Unq4nlup1YvDnbkc7n+jJzKe08ePPsX3PMdzdz+HXj5LsXk9iNns6ZvYX43TZUDRdymTkAj3eIFbZe4qN4/XX1cWvNHA7/AAevP1fqPL+p9HlAIzYpSyHzd2s90YOXZ6IePq1n2p8Qp7ieH0y+vHlMh7YeINe2niYe2niontj4qHt38p6vPScfsecxvj4Tfz64bXoNrc58dOjlbPZGD7xXR1Ks65etdtm+K/m9GdNOXU1YzbZ2fR8Tt+nxwQWSt0TzmvFu9Xz9D4l7eXTQF1LKHTWDBLlgCtqJJpwIWSsIHrfXHF6/yXrfn/oZ5P1vj48u9Jx1uSG5QGGlq7KLKS/Lps8fs52xs3Tl6E8Tfw7Nk6TZ1xKu5i6Z9B3+H3PR5ACLAjJZ5rq8rpdvNVVdm9ny7RQtbEySXS2U1pbIUd6DrO3OszYYenKNDjS+j836P5/3z472PjI4VuO7l3qKP15LIIusqvomOd6tsXy/octqbvo+EQrvJsoGNahlqxv3na876LXMSQFdgPJZfWU15ev1S2eRr9gDxg9kK8cPYoeRHrAeVPqUXzTd8ScSzrGuM/XUt9RyOrDeK9n4k8+rpdNZVdYodZJpz6Kd6nO1i2YPne7nX03e/wAUWDUEaFZ1pnfp/QcDvzEqODHbS2N29spu1wEMZEMWAxATFEIADBQYCQIWRgspWeJ9tybPBLtx2pdRbTxSG/PZZeUsOxzelyvB7c1tdnu8SggIjmnWG4enr93i9rp5q6bMc7alxvNW6sey8pJLmEQmDd5avQZ+d51PcXeN6y9dvBdevVtxuxEBEhKlWKshptzHl/N9/wA/urbS5bFtAWli30oek5PW5Pg9tTQe/wAQgkMpJ6pPI9Lj19X1ef0Nc6MW3LPUjl0GrNq1wgIZBgB5X1Pjq6fG7HOo9Ll9ROLqw7Drdfj9iCIIjKRirBzaM9eU5W/habK81807at3Lrgs6tPLpx8vWzbz2eN0eRjVywevyCCK0UJl3c8y/TNXGsy6eWu3PpZoivpov15oCEgIF8j6/nVz+H7DmnH6duyvK6Nzmrr4N8gBBCDDFQPnvory/P7eHz+qqyHn0Fwvza0vrjMuhqop6S2cxdU3MB3Szn1dWvWeSvSGs+q2+Ox75fRJ8/le9XxF6+4fxUZ9pPHWJ6yeWc9LPPPXenFsjrTm2G4ZbC0KUKkUWRirl9jhnR0V8KVsF9Pl9gcX409pbnqmu6mxbA9vI63nuh259JLt3DfIOii1UvlmV9DlWHqLJy8nbw9c5rmlUY+jj3jKLB15KHlKHgkeCR4VyyFbGI1lMNdmCHSt5AO9z8mnG+g0t8voOtLudiWJLXWw1DYtkvmrbm9HO7o8XZi9bJ0svLWU2BUJNKTXFOW5emazaaz5+hn1MI1neMg2wxzZDJNplwnaTDN8lwjoMc6dKHMnRCc6dCGHVbqzqXNZx2GZMlrNeisj1YyvlzszYPRi/tLr53XnvXnrKLa1UGWCm6ms7M+ors2VVOtKynSTOdDGeajGRtUXM2kxlOmRnmmGeaYZl1QyTSTNeWAxEKjJVaMui2rZBMMea6nN9J3w7A+bpcjDUrquqlQQWBWNVOzCsxhI5EjyVSSAhiSEEMJBAkQhEAYRYywGgsKFSIVpFeaFocjGEvP6Vbjmli4CXMqtSarSxLEMlOyvEkAWWQSpUwCxoArFDDLJYYsGimGlcqyVAulMLRWpYqimiSwmQsIma6GAL151RfLEaKdZgglCWCqCYF4QQyWSQBEsBEDBFMWIVijRSMAQCSpJKUCWGVinNYLDWS1qiWmsyORIlvM6Sx67Oeor1by0UykoUWMWirLIRBRAgQoGCwcAgkNKYAwJTlFRwi06gUVDUoKJJE0axCEqYY1MXHOT/xAAuEAABAwIEBQMEAwEBAAAAAAABAAIDBBEFEBIhExQgMUEVMjMiMDRAIzVCJEP/2gAIAQEAAQUCp+6cquwlY9zXYU/iGQcN7Ow7s90PtzKe5PfcntH7wgFw7psLQmADIrSFpCstA+6MypkOze8/zwiwT1Ve9U0vBqsRj01zRpH+mdqf2nNxUrsiod3Mag1AZD9MIZFSZNVT8w7J52qjvundqj+fD5V58Ux+hHKRycblOVMEwfrjNyfkxVXyop6n95TlhdpqWS9ih7aQoJycVI7MlU4+lvboH6QzenHdqaqz5ESpFPu5FQzPgmqZOJMO8jNDKR299nFSHZxyPZR7JvboH6QyKlKLt2FNVazJykOzzd5XmNt3+5/mnDXtNKYXg7OKkKJQUib7mH629v2D2lR7xhNCqW3iKcpSjsjkNo4BkyPXTRO4sRTipDl2RKBsacXcP2SnNujCmttk8XaSnlTdtKcgn9oG/wAJ92HkEQkxvqG2c87OO6fkNzTss39Q9BKvkERmSnlTFXTim95PewWhd8kLtElSN4iJIZ/pJTBczx/RHA5yjpbICw/UPQ5y1prk1yKvk4qR1k46iu6YwWkYb08hIk+Zvug/lpIn6JK1mygYtAIAA/XObjs9yumFAq68hPKmcuwcU33OddbqK4c/3j3Ur9DqtmiYSARPg4csQsP1hkcibKQpxQQTSgrodnlSH6rJyCcmxt0lShf6i9sv8tHKbUtL9cY2+xLWNbLz0a56Nc7GhWxrnYlzkS5yJc5EubiXNxKOdkh6TkVIj3GTShkCnldi5yOUbeIdP0liqB/Ge8Ac4UmoTVMEgEUEoXDeVw3rhPXCkXCkXCkXCkXCkUmH1TpvTqtenVa9Nq16ZVr0uqXpdUvSqpek1K9JqV6PUKLCZmScm9cm5cm5cquVU0HDYipCvOTUMuykKKOdOPpVlOP4SsDP0kprrLUFrauIxcVi40a5iJczCuahXNQrm4FzcC5yBc5AudgXOwLnoFz8C5+BeoQL1CBeowr1GFeoxL1GJSThjYakSms+JFP6AmoKR253Lijl5iFmBW2kF2FYH7ajSXmq1SQx8czU5iBC+lf6uAdrXRIQAXZbWuFcZNbqd6c5TUZhip6XjN5BqfDpqvT2Kej4cSc5xUBkmmrPiTk7oCYvGnUT2ORUQu8dvI7OG0gs7A/bVSniu1TungDSzUcPk2jcGtj/APcbpwuz6eMdV2/THJ3ZckgXcTrabvg/Iuq78LD/AMbupP7e11W/iBNc5hp3OfV1nxpxR6Amq6YNnHopm72WncJ3aQ/yYJ7KjepUdWwtqanih4DhYKyIR9rQbmxV9rrZXV0SmP0P9RkUta+WOCqfEzn5rGR5qecmU1VLJHlSj/rrPYU5X6BlqQf00zbNV9wn9pD/ACYH8T4GPdy0a5aNctGuWjXLxrlo1y8a5eJcvGuXjXLRrlYly0a5WJcrGuWjXLRrlo1y0a5aNcvGuXYuAxcBi4LFwmoMAVb7XFOKugUF48uWpauhvubs10iY+729nqb5ME+L7N8r5XV8rq6urq+V1dX6K/s8pxyagU6ReHOyAJ6Ixdwa4rgpsQBundp22fgnwdBVQdWIQRRkuoolJA1GGVcGoXCqVwqpcOrUcVQTLDUBaK1aa1aa1aa1aa1aK1aK1aK1FtY1uGSyOnyxaThjXqNmp7QrrUmu3dJfIGy1FOpnowSBGJ6ph9QRVyg5DcTNusHFoOgqb+zZ8Ub3AXD3Foysndx2d3Ht/wAgbC3EbvkwAqUAFH2YSP5ssb7hy4r1qcjn3Qzci4pziVBHdu7cinIOsr6lhotF0FTf2cfw+GnSda1BamryHEBxugVcLUgQHbBbBB27jqyPswfeTLG/fvcgtIXjJvYZkpzsoJNIaQ4Fic14Trq61WWEm9P0FS/2cAvTu7odv8kABttbbaTa2lM96ane89B+PCxYZY38sHy1SHQzt5y4Tk2mUzWsFkxxYmzrihXBTmMKfTtKwtnDg6Cpf7OGRrI3yMRe1cVoXHZfjxoTxhCojB48d+NHbixriRoOYVxBfUCdltlL9EeG7S5Y184NnTO1IdDO+QCsnGwkdqlzuQhKVxiuOsMdqg6Cqj+xDp1eVF0iLnouervV3q8ivIvrVpFaVaJSuFMuDOuFOgyoCbHUtMklVfCZHSvyxn8lyPSOglSnYe/qesG/E6ZKeCU8jSLkKNen0a9Oo16bSL0ylXpdKvS6VHCadekQr0iFekQr0eNejhejr0dekOC9LmRwqdyoaM0jcsY/MK8DM5BDIqXs3qKdC8twcWpMi5akHfsYuDzaHYIdDew7oqbszt00+njVb3PfhH4icdnk30uyjNx+tNS8aSogkp5B7ghkEEztfdFT9me3ppo9ckjWrCPw04XTg1A3T7KLrnqWQmOZkkUdZBLJNUxQlsrXsZURPc+VjE1wI+xffGPn8+ege4q6KnTe3Q0DUz6XSCYDC/xU82TpGpri1zntAh7dJWJ/JSf0uG/2GMfl0f8AT4f+fiv5OGfifY/1ix/6z0aStBRa1amhGROU6b26CqTRwKmQcPD26adPQH1gfXZRdurE/lphbB8PjDa7Eww1VOLYTQtHMYobT4Z+J9j/AFibHOrOCiyIK7AuIhxXptLIUaVrU6IBaU5TLx0uLte4dSfEnoe9vvKi7dWLflUptg1BcVmKu/6oXasKoDasxRwFRhf4X2POLOPOXybG4pkSYLZFOCLU9SnfqJ3imc51J8RcAnIe5vvcou3VijSamH+kwz+wxb82DbBMPtzmLb1eF/g/Y84jHrqxAEI2jMZ230qd1kTc6gr9B9qadLsKN6PjScWnfri/0E51lGLN6p6TjSctajpMNdT1NbQSVFQymc3DqSgniq6+klmqKKJ0VL1Xy81f5GYCA6LKeMuLadcIanR2WlaVoRatK0rCdqGSnbIgxrGAIhBu4/Uf7TNdU0oljHes/JzGRzCY7U1/ZgK0rQtKsi1aFoQDgDJO1wlqVzdUEK6rQrqteo1IXqk69WkXqy9WavVo16rAvU6dDEqZDEKZc7TLmoFx4lxGFX6juDSysEEQiY+ukbUyycV+TQgMj0QSaXHcRNTm2KsrIhaUGrSpGXJj+nh7hisnBEfctlcriSBcxOEKupC56qQxCqQxKpTcVmCDzLOMmhAfYglTDYkAh7ei2elP7EZuTuqysrKysrKysrKysrKytkAox9QQCAzPSQoxuXaVTy6k8IjreeghELSrLStK0rStK0rStK0rStK0rQtK0LStK0prdwzdoQCGRRXkZuYo22NQdoRoRRCIVugpysrKysiFZaVpWlaVpWlaVpWlaVpWlaFoWhaFoWhaEGLSgFZWyOYHQ99lA3iSW38FFHodnZWVkQtK0rStK0rStK0rStK0rStK0qystKstK0oNVlbo752zcUbyPhj0Nt9gqyA6LKysrKysrKysrKysrfYt1Fd8h0SOVJDYZnsV5z79NlZWVv1TmUcxnA3iSN2Cb3zOR/d3VlbIheLdUDLDLt9ofp7/AGDlbLYZeMxsgtW99+go9ffpvl2z8Z2y8dFwrq4tdbWutsrq6ur5AJ/ZncD7Pb7livCtl4W2Vwr5XV8rlE7alqQJV1cq6urrZdl36fORR7hDLx1b9O2Wyurq6urrdbrxvnuvG+W6shfK5VypC4jx5RzurZ2y83V89+nZbLZXvldb5b9G1ltntbztZbK4y2zw8O4eQTs++ffK+fno2XnbPdb5brbLa3nZbK+V1fK62yurq6ur73arr//EACgRAAICAAUDBQEAAwAAAAAAAAABAhEDEBIhMRMgMCIyQEFRUgRCUP/aAAgBAwEBPwHDXpMX25x5zew3sYfHnxfaJGL7c0LjKTJPYhx58T25YzzSIcDGPkj5WIkrWWK98sNWyPIiQ8orb4DJO3lhOjiWUmKFoWGl8HEdLNRrcfOXL7eojXE1xNcTXE1LteaMR5QVsoxNmdT6NdHWOsddnXZZaLRaLRqo6zOtIjiSb7nvlhL7yxkN0L1ko0yiisqKIqytxoaE6MJ3LwQVLLF4GrEmijSaTSaTSaTSUUUaTCXqGXneS5NxGLx2Smo8kpxjyzr4f6dbD/Tqw/Tqw/TrYf6dbD/o62H/AEdbD/rKDpksRCkaxzR1EPDiRjvnyS2ef+d7URxdkmNwJ0+B1pFVFxNqG46aF7lkiu1psb0MjiJ5NMfOePHVRLCmvoUZfhUr9ppdVpKd+0UZJ8Erf0aZfhGEr4yQn6K7WSe+Sk0dVjd+ddsuB5xV5Qj9spPgfkXbPgecY6VkrOHsS5zXmnx2Ra+x8kOD/Ylz5UmLC/TpxJQJvuhwfdj58kYqiuykaUaBwNA4NG56iiivClZHZdsX20OJRJd1FFFFEVv3Uffe0aTSaTSaTSaTSaTQKPc2JV8iKvcfyEP/AKMXe/yf/8QAJxEAAgIBAwQCAwEBAQAAAAAAAAECERIDEDETICFRIjAyQEEUQoH/2gAIAQIBAT8B1X8jQ/LZEuB87RViRqvyZF/bo/kSds0Py2QyfIiCI8mq/P2rbS/PbQW8jU5Io4FwT+2JLgg6ltorxtqOkT4Gaa31Hb+3gy2iiKpbaqtH/O0CWpTJazf2pDRW2lHzu52L8T+nCH2dKR0p+jpz9HTl6OnL0YSWzFtHZoZpLabpFml5iYmNnRs6B/nR/nPKPJ8j5HyGmzoL0PRiiWnFLaOz2S21X/Bmg/4Y2P4EXa75toyeJGTYpOxqzWVRFuzjfUdyGaApUyUkxSSMzMzMzMzMkzJGSLRmazuJFFb47Pg8EvJo8j3UbFBvg6UvR0pHTkjps6UvR0pejpS9HSkUTTaojptDRgRgzBi1JEpeNkLwcrfRHp/1CjIja5Kd7UzzYlLIkPvTihLNEtOSLoUkLeDojNFr2eK5L88n/o2q5I+DJEpIezXzvtirIqls4pnSRVb2WWWWWWWWWWLuhyLdsY/tQ+3T57JPyPvr7dPnslH9G6Hq+jqyZGZprsaKr75SdjZe1mTXgyZmKZmKVng8fa+Rli2nH+7WWOQpURkWRZZZZe1lll7SfgbG+zLwNeO1FiZkZGRmZGZmZmZmOQ32xiTlb7rLMizIssssssvv1ZYql3X+nJ2L9Kiu6/0a7aKJrHx+vRR//8QAQxAAAQICBgUJBQYFBAMAAAAAAAECETEDEiEyQZEQIDNxoTBAUWFygZKi4RMiQlDiNFKCk7HBBBRDYnMjg7LwJGPx/9oACAEBAAY/Al0xEc2aFPQUn9RIithdWC6F5aRLTIlolzRRdKaGP67R33aRKwqdYpH5Ymmhp/uWLoUT5fT/AMMuMiDppYvzBBH0cxz1sVbdCKkl5FE5/HUXTu0KJRUknSEha1ddPkym8VRRj0m1RW461vyFddE0OHUS/Ebitg7XT5Kmho4iJSNk8qrgKnRpRSRb8mtmRKrsBdCsxbah1Fdvfpt+VRI6EUWEltPeliWWtWXyeOpEsG6Ud8VHMTrPZu/DyKthIkpJSS5FsTHLRMmTJkGrzKOumj3WqorHsdVekLUGMaxyw6ENm7IjVWJdUuKXFLpcUul0cqUNm82PE2XmNl5jZp4i43xEmeI+DxH9PMnR5l+jK3tGQLyF5C+ha4vlatHma6KTTMmheTMvtzL7czaNzNo3M2jczatzNqzM2rczatNqhtDacFL/AAUv+UvL4SbvCfF4T4vCfF4T48iT8hXWwbegWNc1FsSJ38zVNFIe9SeyVvSt4pXq2NCqIm8cjFsb0kZtJaOothrxjYT0I1FmbbgK+tWgVq0EiX+AlDPrJiuasYaFexq0lDSKjnI2cRtI+j9k1smqsxN/JR5JSlHMc1r0RbIoMa5EakZIe77thTe17hw2F43IOijIxxGWxTGBYg6sjZ/EWqg0jFu5o77se4bBUhMWLk3IM7SaKTcfi0N3p+mik3aPccre8oqzo24jd/NFiUm8pN5ZMhSUYjUSqxMCEjDRbBSyESLlyLYGBNCyCEyZggjktVDYtzFo1o2tR3WVWsiXGiUsErFxsBWq1qR0TKMbv5othSbyKtQuIXELiFxC43I2bcjZtyNm3IuIXELjcjZoXELiFxC4hcQuIXELiFxC6hdQuoXULqEhu/mtJv56zWs1LE5N+/WRqqtWpGET/URVTtKRbX8anu+08aliv/MLz/zC8/8AMLz/AMwvP/MPepaRE/yCeypaVd9IhfpPGX3+Mvv8ZtH+M2jvzDaO/MNq78w2rvzBV9o6z/2Cte9zkqxtXTR9ZaXSLdMV1JliopdLpbrv363+3odDie8losGp3i2JGUB3upGwkiCrCOhVgKsOgsbFYINSCdaDlRqbh0WokEwEs6SxIaF3Cr/bpoe/RMnyMyZEt1nb9b/b0KnToWLbFLtnREu2byxBUQiQW1CVh+giwFRUW0hBYYiWe70aXbh/Z00O5SwtE5WzRLSu/WX/AB6irCIqwLUtsJEVh3kU6SELYILBuejDvHqTjqO3FixSpx00XZ0N5K3XkWKKnXrL/jKro5GOR6F6BGvabQspUIpSpEj7VDaIbRuZtG5lj2+IjXbmXkzJpmTTPQ6PQPT+3TRdkRROZqvXrLb8Ba7JIl5fB6k18Be8pe8peTIvIXkJtPh4Ek4F1OBs0yNjwPs6+E+zL4VF/wDE8ikU/hlj01VK1LRrvc0pFd8LURIaWdjXTWXkF360aSia5TYNNgmZsuJs/MXHeIk/xHx+I/qeIv0mZtaTgbV/A2rskNuvhPtHkPtHkPtCeAs/ifKWfxCcS2nau+I+s5HK7o0t7GqvILr1oQad+rbzhFwqJoXT3HdyqV0ihYkG4Id+mCE+cvWuqVkhCBUpO5enkE5N6wO/TZPRZyEHqvTI9o13u9JUo6SLhEpXo2JXa5Fb0lVlIxy9CKJXe1u9SxY8kzs668l70hfZJ7uBGFh36fdtcQWUCCWqvIfgF7Lyh3jewLueUPaKLsH415FRvY1ZFp7ylhLkUghVSa2ENKi8jBJ1BU6nlEtdF7hK8biSHQ6HFC5GSfBVGdk/GvIqJVT4EPeehapYhYhYe85ELXKpZyVVHQGpRpXglq6i8k3sEep36jV+/GI1sbKg9zsUcUTUd7taJBcaMt++vIqQj8KcyVRrIwTq0T0LySKn3T8Dij7/ANBOwg7su/Uoe1+w3sIJ2l5FSPUnMV0RI9YqI1ns0tVVIqgvJV68O4/l63wwiNpVpGrCNiIJSMVsIQgp/LxStVVBlI9Goif3CPo6OslWExGvSDorZyKi80TeTVIzhiVW2Jpt5qo9KOhrVUtX9yKbtC8lHQvIQRyllI/M2zszbONrwLyZEm5FrGFtE3MtofMW0K+I2by6/I+Pwl9fCbXgbZptmZm1Z4ix7cz10S1atDSJU6yrmUjEa2q1YFdUhyVuheezXMspHZm2f4jbvzNsptE8J8C/hLWUajnrNyx17NWCkfmcPlPpyEBvyyWrFZJoT5VPVqp8gnykierFZ/JJav8A80ehInx1KyyIc0s5KWiWiWjHTLgehLgeh0dxb8jkS4EuBLgS4HoS4Hoeh6HoS8pLykuB6avpphzPq1pEuBLykvKS8p9JLyn0mGRhxJpxMI95NId58PEwzJoYZqTTMnxJ8T11IEebS4HoS8pLykreyehJI7jDiYZk0zMPEfUT8x+1bgTXfW4n1GMO0T83E+rgXl31uJjurcCfEx8R9Re8xhnr+h661vIS4HoSt7JLykuB6GBgYZk++sfUQR3fWMczExMYbsDGPTDHpJLuhmeh17sSSw3YHX0wx6SS7quHQdfTVyUl5cyNu+rkpJ26zIx32ZmO6sQo72t/1D1PTXnxPUx0Y5EuBLynoYZGBhmWf8ixfMfUTXfHiYw6LJGMf3Mcj6cjr7OZ1dnAwrR6MSyW7DEwyyJJlmdW7AwjHoxJWbsDDLHAknHvMOPcpJsei2fQYQ6avEupHsZln/DIWleqrGxNX0PUxU9DDPUnxPU9TrPQlwPQ/YwPUn5j6jHMxJcD6cTq7OBK3s4nVuwMI/uWQ/7MwzMI9EcegnZvw6Tr7WJ6lq+Y6+iPA6t+BhGPTiT82BPzZH7VuBe763Ew3VsegmkOmKyPhjuWZ//EACkQAAIBAgQFBQEBAQAAAAAAAAABESExEEFRYXGBkaHwILHB0fHhMED/2gAIAQEAAT8hSXaLFAZ4G9pPlTYfGoZ9h+fDjoZNmsxo0ZHh+AkqWJwahAr4BVUXhBrFDUyIZAKYG26MSbKNdCrMRJKyxgaGvQiRvAhYGlQUYCkJ9uMahVNmmNJIZkajwCnooPgxrrIp3RobUVKKZkkBlmZYJKSojIPQfokkn0MeECwYmJ6DSxuhWXRYRDwE2sLUPzSOs2bkug1FN1fcbgEwmQdRB0IEVgQ1YJJZQF6E/wDGfQ16iGPQao3kIX8VrkbtuMWLiM1bH1DJAigbjVY0oyhTBcQGUNiJGyJN8afWn/F+ohjUwySxRYkM3BqWkbljoiphx0LlqOREzJIqqsJqG2yODFcwK4rYPBV0joHpowT6J/wY8VgQ9CNPCUCTKSDHyKoczuWwZSIbtUyHA8xKhuOizNgwnyT0IIFAyyZlxckVlJAsYpCXpkknGSScXihE4Vcis0SAk9hhs3YTWoyoWY5NRXMSNuSM+ItLjMRlEar2KBVY2TAYxVUVosEL0v8AynBjxRI1MA9w0QBEC1WMV0ZjqKRKcWPBIeNiQjcsgUIqq7QygyqCYKrEsNvUUJw0IQvQx4T65JweJYkZqKJqJQ0jIbIjUsWBioy2MsgGxZ7j0Jk0xDthPMhWOL0F+GUoqoZ6BTCMSwQsZweEeicWJixZiG6ETLsYaUKZViCAMYx0Q5aKlzJbyTZrqO7phRiYE2ZktU81yS+jsLsnhlMQSwkLFCJ9E4L0ySSIXpRCoKrApIVBET1EKJTYnuPAaEcTAuiWN6pH7kVLqwHSdLMRtEEh1RaETK7fYgPQsF6H/i8EL0rBQKnEsLqlAbA8i4NdNRUyHrQdJyVwREJITCQQJh0DGnatjgIAs4+11bQV0O6uLBYoyGpZproX8s/Fw1liciQN99Bx3dDedDzrBsVRihektwrBOMJ6UERGkKGCQao2P4AkSJFWSqaPCaaBopESJMOgSg9qChShiCt+oL+dgiA3uALWm5HRJOlB4FPOhtugX8Wfi8KbGEq0vm+hMuvmxWbVJSKAfzhfwBPk8kT/AAbyNPQGgsGLRIbkivEiD4MikJYJuBhkRwFJc4Fu06cTbdSP7h/y2GGq/SDRfox/y+BtfBMoG/XGv+ps+j+hr8XsSWZluuo/ZG5cw9Z+fFm2Ra2s61H2PEmYlDLUibIVHeg1GB6YcxejQiuHlc4LDFURg1RI0E2agtNyO/Ik+6W0JbBCKgBPqQhMq06pQr0su4zEL+BOSVFJkUWVY4ZkaG0k3BBxWdCQMDSatOJMHYTFDqDQqhVUrgQYJukpE4YYcyVBIvZqVKF8+dRtMZtLIhPWV8L9xNPqsmSed41MoyYiKI9ug5HKV4a4w9B8Eig1SA3Ak7QN6BAEEpOGrCF7iwx5stE0TQNBQ1li86ySGiuKaV47YTrBR9KOJFzbfunak1K1roewVGJQssiBTHsELc1Q7ddQ7p21J6gdAavRVuKMyPI5mTaHutNm0w+DEiuMmNKeIbTQlbYrCLQ5lFKDDtqTZ49LhtOj7AxGzXGkQsKBhyoIWCbwZJMtEqUswpcwhpeFVgv5ITqyhYS2m9oaGyGubiMeZehZVyUJshM0m0iW6OITodUtJKpTEJJRFhJxIUOnSEOSqzYUZlNpQaaBIsjQiW25NEkXamUhKmOvE4QiUzF5ettNsmsuLZTSaxkL7x/REg0XIi8rjQUWEPPfbHr4ExIguJgVZGNyx4ZjJBNJFQtLg5JeCnx03dxhkH0jZ9Z+CPHiN/kB/wAs/PJyQW6J+cfhn45+YfmH5h+afniwhl/OPxhfwhfzB/KRFO+xQwnXhVkCA0YF6KyiHS0bgwGFmAvprJJ2ZOz6DezOB9CduxwPoTs+hwYJxIYIE+gJrF6W79GMLIElcWk8KS4D5GWDHIgSVFK4oiRIqDpFZ+q2GQ7PAyqVAykul3IMENvuFG1E91fJ9zfseR1H2PI8HE8R9i8d8iZwgggbU0Bp9Z//AL40EQfFqSXEh+kvCaGnjZcuQkhqWwv1kLQuihF4okAdTKJEuYSCcfAQuxC0MLwhoTZqjBG9dKzxe5a4snonCUSFQ1olNaCjeZCaTUVSKtTNaAnzeQ3QbYMkLpRpQxIsiUnBBQThpQxw0oV+RknMd5ElKnATErg1EZLjUqYI7hI7lCZpZ1EpsSWo4CH6ovyzqOgsLEMVhKcCRcBLDcVFxaXxkrMiXGfOovViXyC6LIEh0wkUj1wPFxElHuxuIQbIho3WQUm0F1XYDIeVC2fo4cHraZGMNNtOUxryvCXEQk0SVo4LyfDTgck0qWlpBkl1hOKidCUKTUljhMoRuohIqTNnxJUxGqVpzYjuPsVHQLC0CGgki7GJKoDspkO5crUobxXgRSSFTFhoS60MaUUofMywtmuS1+o8zcgOL9xIDFUyhFBqqg5UIarazclXI97MVmfRCqhCq7U6FR7Dg5spHAslOFYoROXMlZNAilOIahqsFydysvFHe/YShzPRKqEMahufcyXmhVWjJxFlwHZln3Li0FibiarkIVxLA8o6CXRsTDPIu6l2kVzm71G82pESabtIcdO+J5vqE/Km2TIHo6oY7MI4Mbyg+ZADbMSmSV3qWDy8yarmsPxY3ht8AqdO70DnG98BP8Q8SCjVdTQblG4qiIcX3EMbrfci7IjbD5Cy44Zchojqh0SeEhBCmEFt6FaMRzGaea+u0pig9bg0dsqHcZJC8nc1brMyvUP+wPxClHsEn0I8owCn+kay5D85Woc4jrOmdXECe5VS4D6JGlRhUIzFAEjOcWpaI7b4HlIVjXSTTiaD1ClqlxWFgMkVO09DwaoUR6tgp3GJaPGY/wCi+zyubnqG/I4MfvcHbswZsvkPwh+f9MLnk9EeT+iOnxxPN/QrS6l8kHyfuKISaMxMLKsiIEM/D3ZUZyz+mrdKTYdeBiX2ZEV0eB5VMTwa22+N8WqkTTAzZIJ4lp6nGVfd6YIIIwj/ACnFlJHCoOwspw/DWDj1IpF+odnwkah+wqTJDLB4PvYMWM7IAZaQ3oIvYIhAXGJVZGUF1y/wp6Zwf+DkMRvLDwndFkL3Au5mUWX4WK9KamToNboZiJeJzaweE4UqUluaCKyWMkJEqZQFUaCQbYtfH1MTpBqyVCqc6bkotcWFXWUNSNYiSpn4FVpqUjocXEtl9BaJSSJSPNOV/gxQcdtd0vmNwZC+S1smPOmZXo5KESN1QprC5bGPF1AjRMs0tjzFK6ZOUqG3phcCcqWhhmJyvKaHuepqD0bP7nmNzyNi12+7wp2ost3uX9F6hYsqTohrMxMT5ia5T80apLmXMpkhoC0YoUbwWERKClXFJCc6JDJt08LUdjJOENUxKuPqZVnlPUc/iUq/ETB1N0WweLLQUN2KXlGeMRNIk2cMVZvvuPLyoyOn+Dwn5QgllNvsi5rGYURyBoqvdMEhVQOvGVvpiqK6k4ld70iykduTUN5YWnsBK+Bee76mSaNluLLBmHRrUUkStJtmMbLKouLv7Dniamm4xvNqWrh1EGqkcbsRq8nVnl61jJRNCoDdlXZD20IQriGoTCHbRJgWkgy9CE4ZJvCT7RokhKLJjaGg8pNHZIv8C5+tZk9r7soekfYxm9lR6hZ8CrOVCtMzO4SHKWpxZOo5f+Ou8SuyELmUEJWQhR2GhyDK5FQZDmQeZJJI6TJMiADJ2bCjIS2Et7QOpythFBORSNsgE7+uGRYqIchIxLmp6iESiSM1BChlZrViry8xWlk7c5allBQgaUFDUlT/AA5av1xVyZQi7dY5ndwWmNEVIMok1CeKyEMcBwjG2PZgQCaTTqlgLCoLISpNFl00lBJJJP8AhL1E2hufU7TpjccjaNPMzo2JmzDCVFfBRzEhIWBITWBiwJVmHaaBxPmybuOGKseDFVWiY+pAJKYxMpz2ag+KGveUiVaUq76i+BsJ/pC+AoLNXwaFmJ5BPu0DORxYZyriwmGn2Om26IVwOCiV2afIV0K6uh1JJETk7MaljOb5X2KKXbltWP62apkYxBnkjMWBAPBnQV7CKFYxFOi0HyQU5+glVg04DAGCEQWNR/jBC0RDQgS7K5hWB4OKw64sncCX86QlmcUErviD2rWhI8SiRZ9CW3CCVntFNV2G+HOB5Bqf0SgQ6Mg0xachOEJ0IjBqRCiwayIhUIwSUINEEEEf7gMEYUCCUP7yX/PGJUoc/cfd82Or16HbqdOwqYFKXOQu7R2wapGCxnAdSBLAp/8ACgLvAcOF4VEkdiWH5yPs82E8v4isW7FH9DNLTr5sN6p1qmJt2Zz7ieU4FwEtEzOSCzUziDlgjB4iwEo8NWL0GisfwltsfcvQNhwF3AidkLbt/OJOtfn+i3TnT3X0amuY1stMhlkuyHOkRs/Pwmc55yeBCmZr3OHyNoi0HnCL4BO+DMNVIyHbA0JCwHQVPQUEeg3oU4oIw8yLbcjkPDNEbR8HX58kfPMjg5SW5Oc8h+fO5f8AXnQg878BUxG1ctnsXdq+z3K7x7/0str5DictMjUqzsuQ1EPLg0LxP2KF0uiI7bEV/hTwAWlIVY6D86jVuR52L+bDHQ0i6sBLQivAaphWszm8zUx8nnmhGNDcuPz9l/Mh55kQ05e6+RLeupCiZ8/hH55qU+3yUtHKexHmX4Needzh88sRFXx/v2W5a+WOKen8Z5kN0md7o0dpXF/wfdok/KGctFya8/pTfur59CVv4RHLgRw6ojUK7NXlzIWSGi5cz+ZnjrgjTcfcJVoJUoIiD2G4srzIK/MjUgjTzQSWVj20O7Oen8OXmaK857i40K+dyH3NodrbaEOd/OxFJr8/py+uHAjemvybQ0j4KXml5XuV+NvwTRduxy7Ib3rfi1LIqlysvlCPNcaeL+GJVycmvNBOoQij7oyuq7k6OBuSHQXAdFZ4XHWSueY6pxn9Hj3HnHmZwyIIgiLkRdEUFvhbl4z38+DbxoUmFn57nLl7kPmKN0vIOXL3Kzv8jiHCy08sXmnYiPuO4vxHYWuesdzhRpHYc/Mx3IpEo4djfOZzuNTR0c7Gqd7O42tFsofQ5oesPWY9RkwmmYsvmhxVDsnLW2T+GPbR069BUsjaq806C3rN68/NxOyb76k5p9z44iVbCIFFGpNq9xuTsOvb6LRy+hxCk082Fv5kLLzY3eZCq4fP2PPgvVnHP8KZrj7MquRGnL4MvLG7XH5LPf5KRty5E6rlTmeZCq9uQr2ryuWVfZFfyiKVaOAS4nBcSroMV8ZFqk4MVr3TK3cRk/cQ9K2vuQ0pGu2pDmyZ4J+mQ4I1TH2hqtkzMTv9MjQ4tvNmK0cqt+bE6urJ8ktGipmQ4s5zqFSQdg5qlpjAT37sflRrbsOidfLiwnTX7LnG4y4ql+fyXtmT3Foz+R15/JOb5+zK8/lfwW3DLkQ07LC8sLxTkc/YrNq8uQnuiNFYrxTorlIuiNFiHN0zouPciL6CHOubaimSmunUztnSVyjVqcVsyiU0Z38htfRrmHnIUX0ZMpdqlpu0NUaps15DTVHOt2XJjeuvSXPmholv3TfJ8yfoXMXK5K1OeH/GQz5vHJiqm68eLkKKU1xEHnXO/P8Apyc6Q/OBI4Q0Ajq3ihIJ9eLE633uX/Cd+5ExTTIzTe30OVygVLUj4FRwmOQ6cvgty+KjUcvipCt5sQntPDP+lL01y4MtRcLrIyj6MvzmeZHWI2Nxwhc1Q41iJOdWmo4kR0DWyq2rQhaIjXbUz6Cd9BUaNYs1JUvtlfQyMi87alWeqJeVJWT+/wCEIinKffzJ1vqJt2bKR4sjead4hfTmapoTZb+Es3vVwvlzEr1iLQ58hYQOYocvgJnV3J2efyLFXGMVz+Bb4aQmnyi6G1NtD/jEszRv7vhk1KeCfT5QlCRq929xXws9OcE+UZ4sJiarkOVuDEo1x2EmjObcCp8fkSib2+jPJMfRkm937FEr2+DVTtdcUTM/azJbz7rmVdq9ORG7tNlY6lrLkUtThsQ57A7PYRF0vruRpUReVtSl4lpDuUKmS8u2pDOrSfQaWSxu9Sis7pLtNQ0+Uns5enMn3brl0NsXaaXzfMbm2laE7OJfGYrHAKxTOiG2Qa1mKTTbLoX2u08XU6DaPJyFVnVk8HwIpSKHY4hdnZxQlETzUdr6GbkNQ+GpXSuoKzP5IV2Z8Cr+WY+FjJmmXFXEVqlYdivB3PCik94HLylbqR005yFdUKq3MLpa8o01o9RQnb4GlVcfspJ0z+xSzveuooJ0By6LgqLj4tzWZdas7DU5dC39HPjchR4eMd7Kn76HBZq5dS7W+PPoTC8Y1+VIXFw9nIl/L7+ZZnF49hOSaYoXEukKhNXIFXetEwuYulSHDbNDmarSWFdMyW4aqtr2BynbiPlQPSUVqCivolyFHaRtxVfINaVGrg7lfktPrBNZWbT4u4t6pVZhkjNhRyPooTZCro8ESnn2UcQJ3rIdR0y6hKaZhQs2Ql3RxRyqozcUZNBXpqN5yVPCsUNXHulrL8eQTpwj2/LLLdJz++xq3nWZrzYnJdD+QOusueDuKjmutupQquvMnZ1CarDcN95Wqd7OpVxR7KckKy949TbJSH0ohUmOM+bOBZZuSG9UdZfXkPJThPpzJ0SddWvInjRaLf0mV25OXQsp2Ln1Gq3RSabZF05zeHEOhynT9JDTsr8eRwqLz4u5uVqkPgJoqXir8QNwvCLytk+ZdRVJqhSiVqJn4ITZ3PVTJ1LL0im3NchxFGyly5PmXWVTu3zEwvZeXOK+TecnQhGiNVc3Q3qrS11OZKaQ683MRjRRbOXwJ7k5vF0VKVaD2R9S61W0nDwg/9oADAMBAAIAAwAAABDX/pnb5DL8mGQrrIrH1fc0i6jv0PIXm1jn3DsmOF+/aKrd/VvIQH9/1muPRB2wL9oAhjL6fuk3nZEzyfmVRNC88iR2uPFHV2ngPN3dfaIMyZZJC9lscsOPR9J8pz1p2gin+jekPLfQwWzKB7MfOQf12T5HZc8gSBfV1rgAruubWPlI97hf1q7tkWiaETXJCvL3huwjbzkXj1HpVF/JPc5x2DpHsw63LyBqHWduzlBWPlyEIFiwUXiwXN4Hq24DCzERs7ajqtgxJ2+iXrv8yzl+RVqIA3bN0uRlQ+yiSMtn+UEOkX8vixhqlu13XTckSQjije3NO5yFyh+oiNZ+oZroeu6sOq4/82oJfNO2p76blcpBTcr86yQImWaA9NUOu7haZpSFf0uNMhGxy21HfBO95PwVZaVpCQn38fwE2vv/AP8AardnYrYYz9Dqmt3aZd+d3L3HAtMHGzosv0EMAIPUQ50tz834D/oagIutKm03QoduALa6ik7DicveMAVOL4vnU9IP2cca6Z6CPlZt0Cp+sg41uKCHJNHLD5WziDZFVHaj5UfZzjdLkRUzZUR0nQTEDl28kT+UuiRQKdpgvgMyKu4rQ1S1XuzF1eX6w6LoMzbeJ2YY4yf/xAAjEQADAAICAgIDAQEAAAAAAAAAAREQMSAhQWFRkTBx8KFA/9oACAEDAQE/EIJnZrF2sPBZhSkJJYhCZnBnnBJJD4MeMeoMt0agsVfgnFnnGkdCQhKuFioGiGrGqo0wsUubx0Hd7KKxachO40HiKSou2QjCH+J9iSGMWWeBDNPyIF2izgiL/NbYmUXeEo0PZDobEmKREPPys9x7j3HsE/q4WGMIQxdzHTkMUaSHboteC/jINH5PYe49x7BI1TPeJmmKKbGPCNDVcbgjQxOw62EQ4BKvB9KKTslTBSkFwoILHw3mSsaic1g3brZ+5Y2+SvkosTLTLbtLfkblEkGgreH0LBahp0V5EbKzDuU0sj0z0fsT3Ev2NG1+z0ftHofY/ifZRxJ9jYtLY1oU+xJoXWx+DAUuuWojEqsMVuPyyHZpDzqk7/tESX8/waSWx4f3ZqSKHXl2f7CjVkS8dENBHs6Z4xdXDHyl2MIm+iJJv9DekafofaN9EEab6Lxv9Co6b6PY+hxXW0ToQRXE0RZnjTMQ0NvExCIixMRERF8DWG49BtmJv4wloJwkc/GzYfE2ET4GTb2SNoukloacxsyleduD4MXCNm0fDNmNDdldHjmxUa0W7CT4EeDqhGR4Tha2NDAetlS/hmMSLSJiUbOxu8ECXnMVCbdDcoojIyPkxohGlMRM+FlxCDR9MUxIsUIQhMP0P0wkmjEhKcF3E6yFweyFOHSkkkkkkCEJcESXWybsXCEIQhCEIQhCEXKyjohcFmZ0XN5rCJKDC53CHhFxSlzSlKNX/npConGlLwv4qXP/xAAkEQADAAMAAgEFAAMAAAAAAAAAAREQITEgQVEwYYGh8EBx8f/aAAgBAgEBPxCz42tYd0NssVEmkhCLb0Nn3FZX4LxS0dywxQmdC1GjmxFUS0UfLGL6GzJEOH03N40tjRUVO0WYlAkZi7xfprWQhEYlWRvO1uhLsoyJuDSS2cAeZ5IhBUNnpieyjJaw5DXoew1sSKm3OHrD8oQYsXNI4HorkqkbibI21lXfhzaXiJk0K14CF0NYEIq436LQwNbRxnwNW6TgSL5EkSH+pPgT4E+AmjR7x1EPrSEcDeKVJLHIaiWmEzxCPj2PoxMpSlLsaqMpV9lCmspzlZCC0sbly4hZFYpx00JIkT8E/BPwT8EfBPwPuRpkEjiEp8JKhQcIbjJWO8NGOqxlwMlud4Qzg1KY32BqWCbxeASh1Fomx1B60N+jb2sXuD7uIZT0TgxCPb8FLoYot/37FZf5+xbL4NO2f8FvbJT8f3SI/RwJsZdwmFjaURsGuuCZtof6RFMIgf4GVtjtUE6XYfRC1Rh+Bs2z7hBKNGUbAfhQKQjp1kMY0RS5JJ8eoTodDbH6GLKBMsTiOxsL6cnB6wsIVwZRr0Goz0LwQhFYNTwSPWFirEh4i6hcQz0LmV0eiC6PvghcGvRMVdGez3lRViiNEGehZThUUqo/BFZUY+sYTNRCJXsTDcVnbg4E0/ptxUes0NB7DDZTQbaYqFgOYbBs/CIIKsIyVG4iBQgtIbGgSrZYUp00X+A2gxDGW2+HH4h9EIQ3go816KxsbbwhDZT9hC6MQhMYo2X6aIUeGvRWMQsPwhCEIQhCYIQg0QQmo8IvmsQgkQQhCEHgq+0WITEJmYmEQSEiCQkQmFH/xAAnEAEAAgIBAgYDAQEBAAAAAAABABEhMUFRYXGBkaGxwRDR8OHxIP/aAAgBAQABPxAOwkcYIqHNMITZHUvx5ZhpAN27nMoDmg1bZT1iDYiKqkppgEiItOZsdLIjUNHX1nJkq/GZsZ9dwthd8QXOZSsw1uFQHtG9VMhekZIxphgEYiNz4QagPKVwA8oDoRn1QhWC9aiMIYLZb4QzAeUamIl4gzJEqc/gUwymSbfmXWKo6zAvdRu2My/EzMQbpFe4jgKu6aYC7KABgrsQYdHUAzQPEIMpzT3Ra/S+cw94i+cY9qlLAAL6S4OeDtMnnU5KbjUC4z4Sk5941IYW2YsDvL30xKGEDEESoqYLUyZUMS40/FtBl4iwrBcSNIsR1Fb+AVLqVp5j+fKdtR2M2ytoB4T1smJV1M0y2UF77fvwmNZGcfPh0j2tu4w3FBVFRSUnbpQr8wl1bgyxTUperAghE8IkHZEGjUVGOl6iItX+NMLHUZUYamIsHMxfhlxYsv8ABGLKjdRJgiTJFxOYsfiqlfiloiqxUGYK1eUaCo8do6u81S75z06vhAo4Rt1OYfDWXBGJcJxdwhFoDxTD61CjjKHQafieZsArRhlxOHRlK6sAd0qOfOXtNSxZpcuXlM33AKQajhBuXF+GLUYdy4MuMNzj8KLFuLcINRZlgK2zMzR1mRmZNgFY1K3S4sbx3lZt5xG1gH8ecWs1v1X9QtmsdIQXe9VNfUPAcjL4QxwYISzxomDxz1PGZC3wyoBxHS2U0NSxN3Ltl/1Znc21K9cCPH8bgQgZ/BYqxZtLz+Lm4S451+GG5qO5v+CxKIWtiO78wMw4hA7xjqzLMhxec9orWmZRs5b1j/YCDawaOxGiSWxtbdC7ueRsJ3oK+cMNwggGhxE27S9v0TaDTK1PlBtniZ200EzhULxhpPWV4MDUNeFDZDX5SsTMWiLGAV+FxfyGUcxLJjLjBHBRUmsEsAtdoo1YXxFQ03KRwy+pkQAzvj+z/MGnzH96Q9HQ46/5qDKXZZfS4z0uAuK0F1HVbFXFPYSmojdzaK1s05B5i0qux6pzHASlUkUVsuS5kjmzK5tYlAWTEYHe5gZlDAxAnEWLMWOvxqDL/Fy8wgYYqgw2TEjniCpeOCM1rDicqTiV97msq8ytEwOeay/7/YmBDD8RYrFqR32gCVGUoDo3csG7TMMfG3JUJl36xLU4+8dGkfEqCS4s3sxWLUj0aiGaMkDE8VRuCasneIBUxaKTSb/ia/C4ixFF/G5cwGJxcuDGjAMGBSbQc1K4YtWxMXkcZiwFXP8Af8jR6sVAQg1BMjEKIBKvHM3N+MuEs0zfP/dQxV2555jOISlmO0N7OD1nJwGJbJnPxuGroWolqOM8ZrmKfdGF73ECq2pbqRWnrEDEtbDaIZFW7QcjUIlQEqoYYGItRhyTSLiGVzn8LiaRZcReJkr8F/EHSYk1KjIDnkNwNs45p84KZy7vXxXWEgDLFGLqUnEtMjUINAPVr3zLFE8/+9JkNWswjLuAWa2JDsZ+kKji7I80wCp2EcxYvUjMr4qrmKbZQl3cKgPQwUgpmUEqLB0SGBBDAiTc/DSLcYtEYdzT8cfhY4RxmUc1lY/GqzBjpfJUudt8nbwitjfWsxRM56mf96y6yvPf3NJeeZ3wgXzgit8fvjylIX5PPXjyh1OTbMT9zviKuN4AuO01/wDKVcoUwlDhMR5zG8GjqMBNG/s/7CuvITZR/ecoYD6d6PKHShqO4fgk3hgz+Hf4LiJLpg4/Dv8ADNIuIvwX47IuYgYanDz/AHH/ACXtuHyQv++Y6Fmv76uIEry1+u00246mmUyFIdvwFYu17/2UEUNxTNmhDBEGSs25gHqxaLiOgA6ARXCsvEwa1bLEPtK1SkxzfmL0ceV/5Kdcu+5XTwhlVJQ7zWO/wI7l4tZcTM1hvXpFNp3N3BK4JZ0hN7fElpUeaWpr5zllw98trFZyo9f6oMWe1j0EZpK/BDDHBM5slUzxGCL8f79xYE8WXcePhOEaXH925iO668X7jzpv3mgtzfhnUCDK6uI9YiKcRjxIAtqOHoo4mEevEpo6MxYPYlAHtdSLBe5LcWw0ixaYHX19o6hsl0RjSEsF27xBiZXXoyt9MyxqSAMxvfvIw4tVdnrDr/P98uqgfz1lkdTkPGIvB3gOZH+9pfsv52l+0ef9Re/GNHyAP1Gxx3H2myu7DDl9dCb9TD3axjqzDkeUk6aoVhuEeMLp1LBDUDKaFzeYVZWXf5/yWBlriY1rWpe9kKtGoQNResdtTWssFcvlNSyYwZLFzU7YlgUlrMz+kydl1fSJdUW7aZTs/JHYPywOz/rrEf0Yvg9n900T/jrAGf7O8sHOG8cRPT8sLvgMrtEjl9TOS/C31K/38CLTHcgyhO36olkfnC49JnCy+cfxL9cDHTuCMeEyYuZ6FuNPnzhxryG2b1zBdNriVfW2DFjkNxde6CatBrryXjCepFpJ0Yss6UrJzNz0/cepCvfSK99Kj2TJ1Ezk9Zi4PWDIHt7f3eAHe8tSgPNLBwG6qK5lmIqWBAOWDjZqBjEMOI7aSgOsQY8szMF0AstU0I9VK3J994oljYEAKtX/AJGN4LmxrwiBHAHTh5S3wK6hlA4F0Gf9iNAuewKfDpCGadKHrDwQm9V/f5L1WE0rVV5xRBz4dCv5gA4DqNS2Mo7dQsBaWgOU36/Vy0zhbtXNnl8TTy2jL9d6g2FWpFc8nj28tRlgK4K19wQcEf7uKYJGzUvOOdxxIqAWet+cuwJ4Ft51ADMnKgl/uEAdNq3B4fxle1cRVA2plteb4hZXQIGg0bC3Gq8Is9BZnJDoU0yMUHsEtzNKOl9/AiwyeMrSb1qIucxL1OtNA4hbExat7/3Woaqy0lDQOkAokec6i25i6Sm1zmAQeIah3BROhUJCrviZ9xkY4jCKB+Ig0ND0nMAEwYtt+moNVYx7rqcw1ATQV4e9Q82sd/3xBBIkI4XuopBjl9R6xhshRFBjNPjGJgSGVa2aNeUNQq5ThZx5nvCCsVDSqYqtlVTGZpAtLKXHkQtrVTqqoW83Bq/UClvb08YrXTDoFo6D9wuQ23OguuAbrrCZYOWisXb4sYdkzXzhMMsxhqy3yQlUK39cwhsLjDdGfCzAyKYzovaKkUCKri5QBfQYOOnQ8DW8rEt0LKjDfT1/yOeySyo3zmVZL+WJjyy67NS+94JgysQ2/wAjAN1KuT0hYKGEOFjJmXmZS6cL0IgRFI6f3NMCVTFacGHoRjvQS94QoDOKvSMFRcWEJ5lQE4K1yjTwrtCBWUppHB2IEKEaOoUoXXMvZHUnpBdSGmleBApdFGDq9WVaQMFro4i3ZdqveHiy9qZ1+FtbdMzJBadX23XdtgmLy6QT+3FJrD9ZA8xb06xQJrrd61LudDgLtooh34SI5dd5b3W2fK4gUFrBb0UBzqDDGsl0qukVNjES0vx1K3B00cOA/qlI0XWw6e2b+WIBAT0LfuPB3Y8pQF/mY3PlUaMul0MYMiFxZRApSQRWIqLFGbFSwjc6BlaDrFxj8UNwqCrh7RqqbPwTIGLkTMLadoGgfytaZBPnlRSlawjyr4iKFPoJVr+LtMDg7YsJ7eO83khoHN6zHWHpWf8APzsh0DGO2c+8Mzo+mmGsRqDqlQDQ+BMv0QMx4P2zbg4fpINedQjojn4Ezsz+bgcprmTMTwIUWZTxLXtjjLu38JieL01KohmKa1BZbuLR5rMybdd+kYY8Y1AO7+sAlFxJiIlR09NS/Y8J0vqJh5PCPD3E8b1T+Cn9FPG9GUevpK9PZiOntKTse0p/Eya9pX+JTo+jAdH0YDp7MYhCOCZFrR5Slc4l7V1KttlDlg0t4l0rUSrKpEVFxK9Y2Db0iq/B5lFbRg5wOk2lbFqqTNyiEQuNnWZpNFx2kcRcy4sqITZRmtqHDmMrrpmnWMwCNexihDYqki3hERG/KSff7hpxb4otZo7KOrRW97sdmabelMeShOp/cP8AN/uPRvL+521/G18h0GVR114DIPC5ehUKoUl63COpRBtrnBVfuGhsOyV8lxtUM8BkvELDBRTpkcEEQ6S7u8dIj3uqXE1IHbHxLxJOmGZMnurJq3KFUnDAdDEZK3OOEuXRh7CXiFysdbS4xYsdx+TI8n9WwhYYKDcGIWEGS1vnGY9qhJkQ03XHWWt12y3vN326yqgRVel3dN9ussdswdM1KwQUpu3HhABpbaaU0S5V1Lhu36lOHC6XkHbEuKmardx32JYAGGa05CumJeJy0oMh56d4Fo8C1Cjv0ic7qgxADfjGBqzRO48Yp/D8Msw3cDbl+DqchofxHlqU+Mc1NmGtS7W62samLd6YjeVxiDVWbrcACAU3cDMSDVsHMdXGjYEHoHjEKvIy43YlQU6PuKXDY8wCUYmW0irtG9SulUrUdRjHU0jbdnHRb7GbfBBb1TcdGWlA6vhrmtwFJqDU2UY1eZQ3y823Zeb89SwutDgVlzWYFNKFXP1l4MRBAH2gO1tVbUG47NAixZdZ82PLCqsMat5231jCGjUcgIZ5c7iRVMRhTp0O0vsvogRvdZlfHQXRsprHEswsigpcpwczOzcsFJ6Dv+G10+VEq3QB5p+DqLKd/KQbQt0RRfizEgC6s3fzMsAvrq/3GuGhEKgPVdpcdvCBCCqsx3DOIq810lzRLZIKdC4vAjucsHJHTyVGIK7DuRGrlshs2bxj+GazPsCLlWftRUEmEqObA7ptzrOIfELraG9enMb0prbaG77NcQC2p0oalwnSq84UiIBshezNwZDSUQtKHXIZhZQirvWb8/eoHMlFq89NPaaHhBK8yjC5z3DpzcLdVAbrHFlOPKHYA0ClNZ8x5/FQQuLcWVIzoa1x6U8lfhpLOnynGkQJ/GOSH6GxlqoKaFDCqDaitJ6zDIAmuv7liZqqB/mpmblBWKZM5nErEWrMRCJVTLBKgSXN+2FFB7wkyIyjgb4YJyOSWD5niKtnYZxGMZrMF1BFabIKEW7xE6x4wYyfj+qWXaLtfEzRTdNfaUL6FDwa44mGhVZw9ItwAbNvtCBgRWz14itpNBroo9opEwAamINquFq0MBl6m+kenmtX35S7GSFMV/xzBbEKQHVoAqrogQaVlsmK6wSFEA3RUPv8FiWH0GrOVF2JZiju7RJmtByfcAo3TAG/ZmwrolwbFUX4M/csU0WBN2Aumy2VbOEwJYeEdu0Yl2K5dEu5dTjOYFwIbrGZIJnZ7y8R/DqHEyY7QB21lYAxBFRGTV2faX7U8R9QVAVd8Jw3d/3RZoLtCZebPSi3x/8AERQqd4/SLC08Z9vkYK3S32r8wQUtfzuLr62v1sEcNO5XzA3RP55hShXu/wBzCgzTjPDOJQr0Fe8KvD3lYoYaDxQYSOLxAtL1V5g4i4lig7g5wVfZeI9riY8CwciRyotBXn3jdgcGJ+iFiKpLEv74iD9k1UKR1a4Wl2Z5iofSVjnMcExBWlTZKqMFwIlrsOsdibu7l83VOJzEiBuId2QWUZNddMVFP2/tEfUML8Tw/bFuPw/bP4o/OO0DwwTsHwX6gGv1/U2E+J8kXugOin1KMSjwH4/omZROLi3Yx7iM0BvrzHIGH4fGkbwuaGKj5kBe7OYMGAD13v8AIhB0AzbLDBxSDh5iX2GLQeOKQBGaP8a+5ewVAbsTzdsocMWl/RBW93bnqyjhqq5ahUBAeWdmNpv1lhRnvNWzhAxFqJwiSsRLDQs6YoerXQEd4LfU4/CoC3aLXCDtTBQUzgE3ElSvyaTCV+FSp5x7xe8XvEuXBesO6GYNTIiL9YCzlv5mVN1YU3OyhcbgV08DMrBBc6UIuyWOS/CtRyVaw9FnW5SjVgFV7TK1Cti2PsZbpwwFxpoYziXN64ILT1UpjxBWpUaCAJUqHV3uabXGm6o8uZZZ5a/hMe2Ko3MroOrNiPEqBaXpFPlgx/8ABPSbaxNuh3nlFOkdcS7BlH8dkv8ABCEI4IShaBBlnPjMrFwV6Fn64joHN0iCrXiPuLJy7MI+lxg4hVjdwilUJ4bdCUE4NvNes1TtUFmMNJbOcw0Kb7Qxa9cQZOVZr8R/Bp84xjQKsTajfwHGjxqdlG1jxLlmNA3KRBqXpDxJha3iDu6bIr6N/mX/AOCLG4E4kDum3EDnGHAOQclU3DwQ8eZaUB+YshghKGHRqM3BkgN5enN6gB5tCpWcBvylO+Y1VbmBtShJ4JBsfwwhCEWIphdxz3YhWsoBswb3iwuwtWEiitU4P+OphVyAln2SxaIUAvV9BjsRa2ZltNN9idJXqV1tmm/7+xLCls3D+Mib1AxmBDSttNMHUdMN3YIdZr0c3BYNghsPw9aL2JSZJQBxfWJEUDIaYjxSoPmZsrqPf/yb3LIq7w905v8AJAsc0N9HEotD+s73dPul/wCzTHn1RifHNV0IcGoa3+HcuE2hHUXqRlrgFZxawOMrluUwW046GJdZmxxeJxYIHkMmV+Nzkj2lfp46zoAd4u5lji9wU+0sjr8b6RopLhlquWLjaz6LqyrZewch/HQcw7a2faDjYr8xQ0X1lDd/zDX/AIuLEaxLS6Moio2JVgVG5fqMdjPbqa8MZTl31zKMhUNqzHrIxkiBXcF8ox0rWuGdPhGWLzg1iM1iZtiwYQhNI+5DQNhiLzzHkjq3AMr2iG+tLNGp7ET0J1WggIJelqAKr6QvgqV4QWL194Mo57w0PaMuag3MwvbnMeLdpBgeMA2yTZMqt21uMb1t6GcTRD6Mel/mHKbPF8zj8v41lW3Y2FpLJOe1YIF96iciVHotQ5SqvowqxHQFRPkCW9CkUxhgOgQv3UnAEehhvZSHg08Kh4GCBT4oMUNx3CDBijqfMxsJijjM2SsDnfKDl8AfhQynbGP+R1TFdI4LIiSsS91GC6POpiSqhr4EdRi3FTMjjBLB2qUylpT1IkCEAVKQD3dQs4GBmD0P43yvz/5uaxQLTIbT/SU7Y/OQMlYS7hTQHrtQulB0NjlMqdsIaLcGoSts7tqItsjKt22EGo3t3HDrMHNwYQjqe8QnvacR8tzDSi94MMGcWQa74/v1Kap1j+/TEYj2461Nwet5m4PadqAiy/7+8JkDHxKgNXvHWEZp1lDmGAWlBcDp3HAwmpY5VWc7WZkwELWDN7gxBUFNZdR5OEIwZCcxgMnEfgi3syo/liXEW0XUNNiesNiiQrSluvOFHmCKrsve/KPkNVXLNg9Y4dyM5yma1ncvcesjbFFdWCNB1sixTXUbmjc0KaLRrRcCVWo5YECXUUAgXi8wGDJPdMRcllXhiNZujg5uWhphaG68ef38wlrjArN/vwlQhjHoTmXXTPT9S4LsTq0/2oAuuOsMgzXeUhOW/wDf7iG7FTHGBbMaz4RcKhKsIltzRCnFVKGu1Z6y3jgXu7pmUCzQEDFNu7h3dfaGm5NXogASkR1j+C5iKXLO085bVXiW3dxQowmkaiK1z+H8BAxCQKG3HeDI7gp7ARpwZigpZJ1JenViBGzzsThrbr0+/mUZcvfNn38xlyUOXnH347lLIPW3+8kiZumm0T143CF8zJ4uz+zAOsh0v6YDFhn1gc4Vgfzy7MPhs+f9hQMlsEOV+sBY+IPeYFNRw4uFesQs6nLjxoRMyOEdVGi89YVSvAfqBqvHL6gqsfeWyvvSK+zD7hnK8FOO+b+pxn4j6jffHGfLn3NoPe/wwCnwy+J8Gv8AUGxl6qfULLnkPmb3f31nuBP7nsfJ9zLSfDMr/aj3B5QBvHjA9oMYgiPIzeIWoHhpqnfjGYrIoOVc5YLAJTRi1GH0wFWqP7cusjF+n6e8KuRu+cevR7xcDjOkpv6fZmpXhR9fUGCslazn35fSYBleBRP3z8RBuBzrC/uFAPqvPrCHGTrXH+/TFJut2m1A5INiWVjwI/GF3UFVeP8AEQr0mWj2mDXtLNPaZf8AIVYC9aiCBERpiORCyFCq9JfKlqOUqJ+X8OpbKPBH/Ij0EKaU8FJ7CwfccvwJfc1V/jrPkh9k0CeL+pt/En6mX8GfqoliOh8VgtnNCL0mIKpNfp+pZVbcHx+piUw6rpzXU7QaDAfDz2VjqQL07eX3eUPNZe5ovHrFagms1fw+L5TUzXR09SPod8H6fCF3b15/XWDIcRSMvBgQp0a6VBZCOoBTq2S3Ki4C1ZBWsXDqncDKGpXF41EWdsGg8IAnm4Hf9/VKrfhLGsvSLbRZxMv4rl+kvLS0v+e88Mt0lrzLy8vLy0XWorGc9I+Dq8j07/smVXrWjPF1z3ma21yOFeL6dDzKuR3i9+RhuNm0Vdvu/wBhU2A9Qr1ODHgko2DkAJ+np7wpwrbHC/W/5gAt6cij++oAOBDPHGHnrKHJEUJnprCUVDsPWXD4dP7pKnjF17/7Bef9+pXJ/fwwY7yuTJv+95k3L1nH9/kt1f8Af9lk1zB2Yx0956P9/eUcEvPaXLEVc54ngngngyzh3h2S96ng9oWvH90mOJkXUcbrHLPD/dIdntC/FRVWxrW399RfB/vSYbpxzUbhnp3/ALUtAbXFMvh37cwQFasDp1+xKK4aomSuvenHDKy9YDs7PWmniIsF52voNvoyycFVmjXK562PbMrCICkxrzH+JEVYz7j1zTEGxU9A+H+xLqunu+zv8zRRjw41x1lmjO9QLzi4i+caJasZosMWOIenS6fAZa8WvP8A2GIcYH3INPvyv6hrVZuvf4YcU6MPufqNpev/AGK3GfP+4Zc0719fUy0eA+v7gLvX99XOpfj7P1HVKz26/wDYYk50e8CsZhiOHjxhng/v+S6Yt+4jWL+4KDXOPT7hZrnhr3+o4XVHfj/kxHkf3n18J0tuDl6ee5vQDpv78IGixPHYfs+I4djRz289kM7EbqmsN6fB14zfpjnNVv056kWNVm6o31rxTJHLATpx/wAeO8z2t8/3r0j0nLIGf+/JKBaCr6U/Wd8Mv2sti6b4Tx0PMYMNm7MKPg+8upAlzG+ocPDGBoVoXjlLcnaVcng54Ocn3EJTe8vpovzae0AA0slHYyRmRAOxB4J4+0C9D0HhY9UPSUYO5oXX++8zgtVZxTG/ffRjG2v1/VCfVqZpuQvmHRrmJdjotL8GweWE+oGtcY72XMEcWvwyqmkfSmvuFQTbgvpsnqJd+X7IgFx/l3LWk5q/b9TXjLz0/kl2jKWfJ9ynTHFc/wATPHRh+PhJbllcvw+8LvTy0v8AsBVhlzrX84hkGDp9e+JahVc+HT3xEb2d+mfp9mJu6ovBov6Z8i69/wBkVCiWiVtrXmZJY43e1w2YfPT6xKtmLyafsfZuGEdMUfUPkgV5Lro326PzA1d0GbZTO/EcPWJ7KPkZfFyekDjqdulTfgMVwxbIoGb5K09+D1ImtzYjLrV+49MRKFoytsdfB12YjhxfX0z34hwCJxe2Pv4QVbRTdhg8HuOs0gA0y+x0MBkF24rK+wOHmFiwVryNrr2HPWNMOvGthyQoGSqM1t2eDx3jWqqIK3eLe49wmAFLF+UWvX1iOgrLi6zodj0YQzDls14OrfTMxyicr6N3nrv1jfM3h3zt53x3giLlfltynSGRlnO6x0roYC5UVsac9/4yotjk1rZKsO9c9UfJGwoop4XdvkiwVrP0/uI0rC+WR+4TwHHnX2SzeFh88fJE4N5rx/0iPQv/AE+4Cjx8N/DNbjnwMfDOtKee3D9MHAKHfw/TKVbd2ns/uG1Oc16Po5hgnK8vs/ucnpvvWH1MwYGLeO7X2SoAS6KfhYBGxW91n6ZmJ1QfD6QwU25X1ax6mHvKatrG3gvnut9psEqqZb/Zp0gWUW3gV0+ZhgQSoOuSuPFe05YHNNt2ZPkdJXIXhPDgXhpJVAraUyxnls2PSWR0229Sm97fMFuxqrVLenTfHZNq2Wkr4a43BRQ0OYcdHZ4QpUUaUhq9D1XDxAsyDqG6vPc6Mdom+wv1dhDoK8EHHCfZ0lKdrsR4YeO1DZ27LbKZcdRfiRDAC5czF8eXlKVdiZxi50nXPiusLOhDTlrPn9nhACqBpdPif7kxC6GN1dUZzvp06ajbBqqAZ3ktAD4SjRtgK4tqrr/YUTAp1Z0Zk04vWdB+40bVTybro8GN8tBj0f8AYgC8a9MnxEvlgOfRhoXvD1M+5LMG8nmX8jOpZyd+T7hDQNf9PZZqOmPT/GIMdVL4Yfaa1rp+H2mCaZ/wyhmqZp6P0y4qL5a7YfUpmKZtOnKH2TcGWUDwu/VqUgVLT0HT5OIBmyqN2rF5PJzOS9msZf8ASIIUMtGvV9Sy80MtG68DY5IiHnJzTTHknvBtFYN3YcPiOHtKAWO3Be+H2Rw1wG870PhwyuAnQb6vEOTtK1m09GrrfiN95klUrYOB9H2iIgixROTvhts7yxlxZGZDVseSTFFBvC8mcu2xnYbc7y1y4SGlUJ3IvZ4zXSLhW2gHetJXZxE5VSdFQ2+MSlpRyWgteB0x0qFGzNEtDuZO0dd1irErkK40eZALPdKXhji/cRQ79Kyxlqza58RmBTRVJzZxjXTvZLzpORUq2+mNeTG4qJFy56arp+5QK6QeWVgNGovRgUOsmhL5s6tpiVStnGB4TibnUavGw6+Etg0/Iv8ArjE6Jz4h+pkNY3jxD6cwU9x+QfcozQ2+bIUKrT8N/DCrWA9af0wFNqfh/TCgos+mvhlmjr+H6lL5av4f3LrLxs9n6ZSMt2bvmsezMbGjIfVD7jN2ClU30289QMAAKK4F35CdbVIrTjQ8tzKB0VtFPpIKYEBlvBy8nEreQO8vJvzlWZspmvI70mIwXbYaON8pSqZp0b5N8mYjToaLDjbjUs1eVo009dvOBV0wcOem3lAMWumLV27ecAXHIOrxt0xFPEKoXXO2+SI2ZciqcL8Kwwegaqrcq8RPSLYusRJQcHwrcIUYYWYp3k9cks4t3V44bdnEumAUUaLxtu9kS6CqY7HU0mSBYwAoYObwYELdSRvgbtTy9mCidC2ybT4hdcuguXyw/wACI0Ct+dZ49ThzMbRWUROTBo38zpaJ3VQ79L9HErcoG6hKKM/Eo5ffP+xAWpyW6+oWKCm/D7QGBTdXp5/v+EtDN5C4etcRDKpDLTi2EaHNZD2XlKGWqunVKfHnANrvHatxiGmrv1f25rY6C+6Dk5xd+a+pmbRPs+oJZfNXnrl7hAqW01R1vC+xBL6dvPL3qCi7qtP8doUUZVmi7TfqMUO+62zWV5mIArYeOlkd8OJlNIFPQcDfDUtpq7hWM+rkhWgAAL4Zy3u8RFNBu9PZ9xUcmbDx8PnGCNYLrE554ZZx74DMMepuYwGms5w6984iHGSUJz1k30zBCwYU7jjndzCvdVYOo3qoFMsLFN1e97vEui7Ih9W9VAocmvmdd7gCnYcFXo3pmc7N5OqY9ogKTBTnoea6LKgKOgcg2Oeksb3Js5ndsY5Dtqv0TnRzGm3htbG3nZ7Slt+NSFaN6feOYWCqDwaX19CIqqBcA1ex8MLyYaFWiirtzeOmE8GNuUu0zUTB516kqlkwJutGfReeGDAbWMpvaPfWOTMAaV/Z/wB6TIu6J0jYiqAy+vEo6qaKePKbNlxzeGSK7BHGqdO/9VHMa3IMgWOjxr6gNtd0XZhORMIQBSitV4IDRLNO5f1OYbLo6WWeHzKcALbMY2WeGfOUuJluiupfyQTE23LzS/ki3rSzu9l/JG1hiyJVbLPeJxWUZeNj3ImtCG1jgwfRjwV5Gc/zcKaLGxrIePKgwFDg14uXlLLqmV+96MwGzO/GbPTPjKChcVlz/wBMXGLZVa8/pxAQrcFVvvyO2bAbh22X11HOjCK5enwr3jTzpnf2vHhFbYgosro8Kg80RdF929uoB1uHZ3W9VmJUja1k5927xKeBfQq4m9JAIpoO7kbb2RyQmwGDseDzB5zATYV9M1BlgAvB9nTMEoCMS9305J1mHXOr40VG0UOBUHBfQz4zQUVbPS7Pial4oacW/EMMLsqaQAa2HfVLrc6lSgTfg47MMCI9S5wqVsqjwZRmUdhbCg1oddkwBhDgoyZ6Lp4cR4QBk38Sew85VuEtWSjweIZXJEpHPHSHWwYPeUtl9hEQlX2bfplCW0KtZYBeylQee/N+/hKKUCNC5lZOHV+rFWXQWqWZqm7x+oX05WS2xOGJkLq6DjlbgovFF0CmudfMDQzZ3WrU+GHxgorhQcW8ejBVLqjXmHr0ZTbHJCnlh6MAIdVNdVPUmZLbaGTnPLrZGzWGT0Hm6Ib0GVV2QpTQogMN5fG4JgbF8aOvO/aW1VC7VzOnkOO8BdmcZR28HpllNLVCbBqO3xvBBOZspU048KIYuOubGM53tYNmdzIVhrejcOfdqX372ssUxDk6w6HVTMUN2UUvfmvEoyKW8H9VZiKBw4ob+68QsFTZqmGPOZmMFGGK234zURpbZgsmjwOYiY0pwLYyev2iSGrwZr4osqlZjG9P3mUU0C42fBFKeEWABT4DELVgWxX3KGDKDSA9DVhiF0lNlf8AQdoByAYTO/BTKAUIQlEP8KQtylS26dPCmXeVq6tipmAeLnuRpiVsczLo4bOjLRC+brD29TRLqMuEv0q55p5QlW6ypj1lrBWmuq9QHEFcf39qWNC44tz79pdANKwX/wARS2ii5pBK/wAc9B6ygbTlspq3WuU10MxYBj6lUN4EyZa67gBaWbaKKb48csqJiua05NywFQlpyEr9soZZSLegPXZtzLrAs2s2Kx4hBKW5A8CKfaWtjCtGtvaPdKZE3g8ckOAd+isn7hyCr4wHDxv2iA6m86zENCWRgL337MsaBlBWz2cvm6iW3VpaA48AywNG5XCXNt+K+0ymzZoCr9dB7yjORTC3cuztZahZ0KuVm9EdFJ6n+xcTBWt9xGtV5GY1bVwoe3zcQ22q3rf7cRg1iwWf2oO2zZK3jz7llsLpgtc8eNRUKWrWqjPyTmpWCb7v5SthSVFMQewuXlNkThWsehz4Ro0ikhy3sVh+YoCARJjHytpAV2hIs6vitzTkXA0BT2D36xpC51ra/eqfCDHdg4Ij0Ey78zIKGo7kvr3kPSJcNxdQzbqcaYbXLChr9+/tCAF6AH/lae6WW+cBNMl5/RApSsNkDRToMDhghKzMBpTHuYdpZgYJyGcuNQglp2Yer1P9gVQ6A2ZdeG7ZhKppNXX+TIWFmt3gaYAz3xiu9cYz2DrKKlF2VlXsejWV4KJaK6XihbeDZhawcEZAhsLpSnF44vRyxUda2MDYnS/aJhWNLBLI099fEYhLbFtpavky0/qEpQBJx0PEpMotLeiU46ygXRyBTAya6wFZLu+sxf0RBZbVBUjIfvvFeiBbVtLKd1jag3sMs35B7sQcVY3ZY817QJbBlb1pvyCO+qA52jo8VAFa0NqwGsvAalBSgoJS1w8VLVrANZNMG6BAFgtbGGogdllW/DaCYobSulb+CLcNQqnDry7l6mi7elvmMQzG5Fj+XMW+hu45V4AxAwCq0KofeXMoslXhXPM7GmFbAoQN9cfBNMb3HCq15+8dxXSjaiotXkoDLWlBN/cOvmN2BRYVjWfnzHqmB0vpVkjVeEq1ueXibSgsHBuKflAFCp31XDezSZOW6rmGXgmGCiyxe8z8NxTmAsQb+ZeUpmwRYLHpVk+oECSAsktbtmD2iDWcN5WrpMneAOpUXoZeTD9QThVouG/p5M11Vd7vxL4wcwAqbdXQuPRysV9DnodPqaFsmAQfRx5xVkgbMOt44N+Qmy+YRxdr9TriUiVMWNls+uy8QuEAaCHNWByuB0tiRWDSAIAy74cvLDTlJw+A78aiLeyJscVo8S1gYmGrZYnmMTdAVgcWG71o13YwHWA2+bnr0mCuwURMGGnsHnLIWhNXn+LgLgUFcjVDTzoJRdjgbHLf2MbLM1uh28rRLwKcChdK9R2y99YtHOkdtCItHXg4NfIwV4yaBhh1GuEtWcbKLMsnjtLKrLLqm0vyfpFYtndZa6/pEQimnATj4iWyr6OavMO9VqEakqJv9lxyKcKwaduLRFsbqV2drxPZHDyTcD2fM3MtGhyb0fhGLjB4yvP0ZZxNoeTR8NZmoCaM5t2bWK6RyWAimDJTwMQaUKl21/tI8ACgcB168DF5FtBIY+lWSUPF33WzjxjiJDwxSJ09g5RppZovIj27Wu0LFIYI4rsdGZVaxZ9F4Rs+44a8aCur0djl8Sht2pLphwcODvLS352nL1TB6kAjVa0AjPjZePHM/9k=" alt="Le badge piege.exe accroché sur un sac à dos jaune moutarde" width="400" height="400"></div>
        <p class="hint">Cherche <b>le sac jaune</b> qui diffuse ce Wi-Fi : c'est moi. Viens discuter !</p>
      </fieldset>

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
        <p class="hint">Ou garde-moi dans tes contacts (fichier texte .vcf, 1 Ko) :</p>
        <a class="b95 vcf" id="vcf" href="/contact.vcf" download="Romain-Caillier.vcf"><svg viewBox="0 0 20 20" aria-hidden="true"><rect x="1" y="3" width="18" height="14" fill="#fff" stroke="#000"/><circle cx="6.5" cy="8.5" r="2.2" fill="#000080"/><path d="M3 15c0-2.4 1.6-3.4 3.5-3.4s3.5 1 3.5 3.4" fill="#000080"/><rect x="11.5" y="7" width="5.5" height="1.4" fill="#000"/><rect x="11.5" y="10" width="5.5" height="1.4" fill="#000"/><rect x="11.5" y="13" width="3.5" height="1.4" fill="#000"/></svg><span class="lbl">Télécharger mon contact</span></a>
      </fieldset>

      <div class="prog">
        <div class="lbl">Analyse de votre curiosité… <b id="pct">0%</b></div>
        <div class="pbar" id="pbar"></div>
      </div>

      <fieldset><legend>Au passage, détecté sur vous</legend>
        <div class="field" id="diag"><noscript>Activez JavaScript pour voir ce que votre navigateur révèle, en direct et sans rien envoyer.</noscript></div>
        <p class="note" style="margin-bottom:0">Mesuré dans votre navigateur, à l'instant.</p>
      </fieldset>

      <div class="status"><span id="st">Piège armé et opérationnel.</span><span class="r" id="cnt">Curieux : 023</span></div>
      <p class="note">Pour partir : oubliez le réseau « <span class="ssid">Ce_WiFi_est_un_piege</span> ». Il ne vous en voudra pas.</p>

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
document.getElementById("vcf").addEventListener("click",function(){fireBeacon("/click?l=4");});
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
    var p=t.split(","),c=parseInt(p[0],10),k=parseInt(p[1],10),ssid=p.slice(2).join(",");
    if(cnt&&!isNaN(c))cnt.textContent="Curieux : "+pad(c)+(!isNaN(k)?" · liens "+k:"");
    // The hotspot name changes from the admin page; the markup only holds a default.
    if(ssid){document.title=ssid;[].forEach.call(document.querySelectorAll(".ssid"),function(el){el.textContent=ssid;});}
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
