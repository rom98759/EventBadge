# EventBadge — boîtier imprimé 3D

Boîtier porte-badge du projet [EventBadge](https://github.com/rom98759/EventBadge)
(Wemos D1 mini + LCD1602 I²C) : une fenêtre Windows 95 `piege.exe` avec Clippy en relief,
accrochée à une sangle de sac, alimentée par une powerbank via un câble micro-USB verrouillé.

![Façade](images/final/final_front.png)

**État (2026-10-31) :** façade, coque et verrou imprimés et validés. Imprimante Creality
Ender 3 V3 SE, buse 0,4, PLA mono-couleur.

## Arborescence

```
scripts/                      sources CAO (versionnées)
  enclosure.py                boîtier final : façade, coque, verrou, coin de test, façade en marqueterie
  strap_clip.py               pince à coller au dos pour la sangle du sac
  explorations_abc.py         premières directions A/B/C (refusées, gardées pour l'historique)
images/
  final/                      rendus du boîtier retenu
  explorations/               planches des directions A/B/C et des variantes V1/V2
PRINT.md                      guide d'impression, couleurs, montage, quincaillerie
stl/                          STL prêts à imprimer          ┐
cad/                          fichiers FreeCAD .FCStd       ├ générés, non versionnés
archive/                      STL des directions refusées   ┘
```

## Régénérer

Dans FreeCAD 1.1 (AppImage), console Python (Affichage › Panneaux › Console Python) :

```python
exec(open("/home/romain/Documents/FreeCAD/EventBadge/scripts/enclosure.py").read())
exec(open("/home/romain/Documents/FreeCAD/EventBadge/scripts/strap_clip.py").read())
```

`enclosure.py` affiche un rapport : `clashes` doit être vide et `valid` à `True`
(contrôle d'interférences entre pièces imprimées et composants modélisés).
Les STL sortent déjà orientés pour l'impression dans `stl/`, le modèle dans `cad/`.

## Repères de conception

- Axes : X largeur, Z hauteur, Y profondeur ; y = 0 = arrière de la façade, le visiteur regarde depuis −Y.
- Cotes mesurées en tête de `enclosure.py` : LCD (PCB 80,2 × 35,8, cadre 70,9 × 24,5 × 6,3),
  Wemos 33,7 × 25,1 × 11,5, prise micro-USB moulée 10 × 6 × 21.
- LCD pris en sandwich : cadre métal contre la façade, 4 piliers du dos avec picots Ø 2 dans ses trous.
- Wemos libre dans la boîte (collé si besoin). Câble USB : trou dans le flanc droit + verrou coulissant.
- Choix et refus de design détaillés dans `DESIGN.md` du dépôt EventBadge (section *Enclosure*).
