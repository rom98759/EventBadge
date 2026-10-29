#pragma once
#include <pgmspace.h>

// Stats page served at /admin. It holds no data: it fetches the raw event log
// with the admin key and decodes it in the browser, so the badge does no work.
const char ADMIN_HTML[] PROGMEM = R"HTML(<!doctype html>
<html lang="fr"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>EventBadge stats</title>
<style>
body{font:14px system-ui,sans-serif;margin:0;padding:10px;background:#008080;color:#000}
.w{background:#c0c0c0;border:2px outset #fff;max-width:760px;margin:0 auto 10px}
.t{background:#000080;color:#fff;font-weight:bold;padding:3px 6px}
.c{padding:6px 8px}
button,input,select,textarea{font:inherit}
textarea{width:100%;box-sizing:border-box}
.note{font-size:12px;color:#333;margin:2px 0 6px}
table{border-collapse:collapse;width:100%;background:#fff}
td,th{border:1px solid #808080;padding:2px 5px;text-align:left;font-size:13px;vertical-align:top}
th{width:38%;font-weight:600}
.bar{display:inline-block;height:9px;background:#000080;margin-right:4px}
.h{font:12px monospace;white-space:pre}
#err{color:#a00}
</style></head><body>
<div class="w" id="login"><div class="t">EventBadge</div><div class="c">
<input id="key" type="password" placeholder="clé admin" autocomplete="current-password">
<button id="go">Ouvrir</button> <span id="err"></span></div></div>
<div id="app" hidden>
<div class="w"><div class="t">Badge</div><div class="c" id="head"></div>
<div class="c"><label><input type="checkbox" id="me" checked> m'exclure</label>
<button id="reload">Rafraîchir</button> <button id="csv">Export CSV</button>
<button id="reset">Remise à zéro</button></div></div>
<div class="w"><div class="t">Nom du Wi-Fi</div><div class="c">
Actuel : <b id="cur"></b>
<textarea id="names" rows="5" spellcheck="false"></textarea>
<div class="note">Un nom par ligne, 32 caractères max, sans accents (écran LCD). Jamais le nom d'un vrai réseau.
Changer de nom redémarre le Wi-Fi et déconnecte tout le monde.</div>
<select id="mode"><option value="fixed">fixe (1er nom)</option><option value="seq">à la suite</option><option value="random">aléatoire</option></select>
toutes les <input id="every" type="number" min="1" max="1440" style="width:4em"> min
<label><input type="checkbox" id="wait"> seulement quand personne n'est connecté</label>
<button id="saveWifi">Enregistrer</button> <span id="wmsg"></span>
</div></div>
<div id="days"></div>
<div class="w"><div class="t">Journal (200 derniers)</div><div class="c" style="overflow-x:auto"><table id="log"></table></div></div>
</div>
<script>
var K="",info=null,evs=[],wifi={names:[]};
var TYPES={1:"démarrage",2:"connexion",3:"déconnexion",4:"page ouverte",5:"clic",6:"quitte la page",7:"nom du Wi-Fi"};
var OS=["?","iOS","Android","Windows","macOS","Linux"],BR=["?","Safari","Chrome","Firefox","Edge","Samsung","Opera"];
var LINKS=["autre","portfolio","GitHub","LinkedIn"];
function $(i){return document.getElementById(i);}
function dev(a){return (OS[a>>4]||"?")+" / "+(BR[a&15]||"?");}
function vid(v){return v?"#"+("0000"+(v>>>0).toString(16)).slice(-5):"?";}
function dur(s){s=Math.round(s);return s<60?s+" s":s<3600?Math.floor(s/60)+" min "+("0"+s%60).slice(-2):Math.floor(s/3600)+" h "+("0"+Math.floor(s%3600/60)).slice(-2);}
function med(a){if(!a.length)return null;a=a.slice().sort(function(x,y){return x-y;});return a[a.length>>1];}
function p2(n){return ("0"+n).slice(-2);}
function hms(t){var d=new Date(t);return p2(d.getHours())+":"+p2(d.getMinutes())+":"+p2(d.getSeconds());}
function when(e){return e.t?hms(e.t):"boot "+e.boot+" +"+dur(e.ms/1000);}
function detail(e){return e.type==4?dev(e.arg):e.type==5?(LINKS[e.arg]||"?"):e.type==6?dur(e.data):e.type==7?ssidName(e.data):"";}
// Same FNV-1a as ssidHash() on the badge: the log stores hashes, not names.
function fnv(s){var b=new TextEncoder().encode(s),h=2166136261;for(var i=0;i<b.length;i++)h=Math.imul(h^b[i],16777619)>>>0;return h;}
function ssidName(h){var n=wifi.names.concat(wifi.current||[]);for(var i=0;i<n.length;i++)if(fnv(n[i])===h)return n[i];return "ancien nom";}
function loadWifi(){return fetch("/admin/wifi",{headers:{"X-Key":K},cache:"no-store"}).then(function(r){return r.ok?r.text():"";}).then(showWifi);}
function showWifi(t){var c={names:[]};
  t.split("\n").forEach(function(l){var i=l.indexOf("=");if(i<0)return;var k=l.slice(0,i),v=l.slice(i+1);if(k=="ssid")c.names.push(v);else c[k]=v;});
  wifi=c;$("cur").textContent=c.current||"?";$("names").value=c.names.join("\n");
  $("mode").value=c.mode||"fixed";$("every").value=c.every||15;$("wait").checked=c.wait!="0";}
function load(){
  $("err").textContent="";
  fetch("/admin/log.bin",{headers:{"X-Key":K},cache:"no-store"}).then(function(r){
    if(r.status==401)throw new Error("clé refusée");
    if(!r.ok)throw new Error("HTTP "+r.status);
    var h=(r.headers.get("X-Badge")||"").split(",").map(Number);
    info={boot:h[0],up:h[1],conn:h[2],clicks:h[3],you:h[4],full:h[5],at:Date.now()};
    return r.arrayBuffer();
  }).then(function(b){
    parse(b);return loadWifi();
  }).then(function(){
    render();
    $("login").hidden=true;$("app").hidden=false;
    try{localStorage.setItem("k",K);}catch(e){}
  }).catch(function(e){$("err").textContent=e.message;$("login").hidden=false;$("app").hidden=true;});
}
function parse(b){
  var d=new DataView(b),n=Math.floor(b.byteLength/16),off={},m={};
  evs=[];
  for(var i=0;i<n;i++){var o=i*16;evs.push({boot:d.getUint16(o,true),type:d.getUint8(o+2),arg:d.getUint8(o+3),
    ms:d.getUint32(o+4,true),data:d.getUint32(o+8,true),v:d.getUint32(o+12,true)});}
  // The badge has no clock: each boot's start is estimated from the phone
  // clocks sent with page views (median, so one phone set wrong cannot skew it).
  evs.forEach(function(e){if(e.type==4&&e.data>1.6e9)(off[e.boot]=off[e.boot]||[]).push(e.data*1000-e.ms);});
  (off[info.boot]=off[info.boot]||[]).push(info.at-info.up);
  for(var k in off)m[k]=med(off[k]);
  var ss={};
  evs.forEach(function(e){e.t=m[e.boot]!=null?m[e.boot]+e.ms:null;if(e.type==7)ss[e.boot]=e.data;e.ssid=ss[e.boot];});
}
function dayOf(e){
  if(!e.t)return {k:"0-"+e.boot,l:"Heure inconnue (démarrage "+e.boot+")"};
  var d=new Date(e.t);
  return {k:d.getFullYear()+"-"+p2(d.getMonth()+1)+"-"+p2(d.getDate()),
    l:d.toLocaleDateString("fr-FR",{weekday:"long",day:"numeric",month:"long"})};
}
function visible(){var me=$("me").checked?info.you:-1;return evs.filter(function(e){return !e.v||e.v!==me;});}
function tally(o){var a=[];for(var k in o)a.push([k,o[k]]);a.sort(function(x,y){return y[1]-x[1];});
  return a.map(function(x){return x[0]+" "+x[1];}).join(" · ")||"—";}
function stats(es,seen){
  var s={conn:0,uniq:{},views:0,viewers:{},links:{},dev:{},hours:{},stay:{},wifi:[],open:{},ssid:{}};
  es.forEach(function(e){
    var k=e.boot+":"+e.v;
    if(e.type==2&&e.ssid!=null){var n=ssidName(e.ssid);s.ssid[n]=(s.ssid[n]||0)+1;}
    if(e.type==2){s.conn++;if(e.v)s.uniq[e.v]=1;s.open[k]=e.ms;if(e.t){var h=new Date(e.t).getHours();s.hours[h]=(s.hours[h]||0)+1;}}
    else if(e.type==3){if(s.open[k]!=null){s.wifi.push((e.ms-s.open[k])/1000);delete s.open[k];}}
    else if(e.type==4){s.views++;s.viewers[e.v]=1;s.dev[e.v]=e.arg;}
    else if(e.type==5){var l=LINKS[e.arg]||"?";s.links[l]=(s.links[l]||0)+1;}
    else if(e.type==6){s.stay[e.v]=Math.max(s.stay[e.v]||0,e.data);}
  });
  var u=Object.keys(s.uniq),back=u.filter(function(v){return seen[v];}).length;
  u.forEach(function(v){seen[v]=1;});
  var devs={};for(var v in s.dev){var n=dev(s.dev[v]);devs[n]=(devs[n]||0)+1;}
  var stay=[];for(v in s.stay)stay.push(s.stay[v]);
  var nclk=0;for(var l in s.links)nclk+=s.links[l];
  var rows=[
    ["Connexions Wi-Fi",s.conn],
    ["Par nom de Wi-Fi",tally(s.ssid)],
    ["Visiteurs uniques",u.length+(back?" (dont "+back+" revenus)":"")],
    ["Pages ouvertes",s.views+" ("+Object.keys(s.viewers).length+" visiteurs)"],
    ["Liens copiés",nclk+(nclk?" : "+tally(s.links):"")],
    ["Appareils",tally(devs)],
    ["Temps sur la page",stay.length?"médiane "+dur(med(stay))+", max "+dur(Math.max.apply(null,stay)):"—"],
    ["Temps connecté",s.wifi.length?"médiane "+dur(med(s.wifi))+", max "+dur(Math.max.apply(null,s.wifi)):"—"]
  ];
  var hk=Object.keys(s.hours).map(Number).sort(function(a,b){return a-b;}),top=0,hist="";
  hk.forEach(function(h){top=Math.max(top,s.hours[h]);});
  if(hk.length)for(var h=hk[0];h<=hk[hk.length-1];h++){var c=s.hours[h]||0;
    hist+='<div class="h">'+p2(h)+'h <span class="bar" style="width:'+Math.round(c/top*160)+'px"></span>'+c+'</div>';}
  return '<table>'+rows.map(function(r){return "<tr><th>"+r[0]+"</th><td>"+r[1]+"</td></tr>";}).join("")+
    '</table>'+(hist?'<div class="c">Connexions par heure'+hist+'</div>':"");
}
function render(){
  var list=visible(),days={},order=[],seen={};
  $("head").innerHTML="Compteurs totaux : <b>"+info.conn+"</b> connexions, <b>"+info.clicks+"</b> liens copiés<br>"+
    "Allumé depuis "+dur(info.up/1000)+" (démarrage n°"+info.boot+") · toi = "+vid(info.you)+
    " · "+evs.length+" événements"+(info.full?" · <b>journal plein</b>":"");
  list.forEach(function(e){var d=dayOf(e);if(!days[d.k]){days[d.k]={l:d.l,e:[]};order.push(d.k);}days[d.k].e.push(e);});
  order.sort();
  var html="";
  order.forEach(function(k){html='<div class="w"><div class="t">'+days[k].l+'</div><div class="c">'+stats(days[k].e,seen)+'</div></div>'+html;});
  $("days").innerHTML=html||'<div class="w"><div class="c">Aucun événement.</div></div>';
  $("log").innerHTML="<tr><th>Heure</th><th>Événement</th><th>Visiteur</th><th>Détail</th></tr>"+
    list.slice(-200).reverse().map(function(e){
      return "<tr><td>"+when(e)+"</td><td>"+(TYPES[e.type]||e.type)+"</td><td>"+vid(e.v)+"</td><td>"+detail(e)+"</td></tr>";
    }).join("");
}
$("go").onclick=function(){K=$("key").value;load();};
$("key").onkeydown=function(e){if(e.key=="Enter")$("go").onclick();};
$("reload").onclick=load;
$("me").onchange=render;
$("saveWifi").onclick=function(){
  var n=$("names").value.split("\n").map(function(x){return x.trim();}).filter(Boolean);
  var long=n.filter(function(x){return new TextEncoder().encode(x).length>32;});
  if(!n.length||long.length){$("wmsg").textContent=n.length?"trop long : "+long[0]:"il faut au moins un nom";return;}
  var body="mode="+$("mode").value+"\nevery="+($("every").value||15)+"\nwait="+($("wait").checked?1:0)+"\n"+
    n.map(function(x){return "ssid="+x;}).join("\n");
  var was=wifi.current;
  fetch("/admin/wifi",{method:"POST",headers:{"X-Key":K,"Content-Type":"text/plain"},body:body})
  .then(function(r){if(!r.ok)throw new Error("HTTP "+r.status);return r.text();})
  .then(function(t){showWifi(t);$("wmsg").textContent=wifi.current!=was?
    "Enregistré. Le Wi-Fi redémarre sous « "+wifi.current+" » : reconnecte-toi.":"Enregistré.";})
  .catch(function(e){$("wmsg").textContent="échec : "+e.message;});
};
$("csv").onclick=function(){
  var rows=[["time","boot","uptime_s","event","visitor","detail"]];
  visible().forEach(function(e){rows.push([e.t?new Date(e.t).toISOString():"",e.boot,(e.ms/1000).toFixed(1),
    TYPES[e.type]||e.type,vid(e.v),e.type==6?e.data:detail(e)]);});
  var a=document.createElement("a");
  a.href=URL.createObjectURL(new Blob([rows.map(function(r){return r.join(",");}).join("\n")],{type:"text/csv"}));
  a.download="eventbadge.csv";document.body.appendChild(a);a.click();a.remove();
};
$("reset").onclick=function(){
  if(!confirm("Effacer le journal et remettre les compteurs à zéro ?"))return;
  fetch("/admin/reset",{method:"POST",headers:{"X-Key":K}}).then(load);
};
try{K=localStorage.getItem("k")||"";}catch(e){}
if(K)load();
</script></body></html>
)HTML";
