# EventBadge — boîtier « Fenêtre » V2 (Clippy en relief)

Sources : `scripts/enclosure.py` (boîtier) et `scripts/strap_clip.py` (pince sac), à lancer dans
la console Python de FreeCAD avec `exec(open("<chemin>").read())`.
STL prêts à imprimer, déjà orientés : `stl/`. Ils sont générés par les scripts
et ne sont pas versionnés (ni les `.FCStd`) : relancer les scripts pour les recréer.

| Pièce | Fichier | Orientation | Taille (mm) | Couleur |
|---|---|---|---|---|
| Façade | `V2_Skin.stl` | face vers le haut | 100 × 78 × 4,4 | changements de filament (ci-dessous) |
| Coque | `V2_Tub.stl` | dos sur le plateau | 103 × 78 × 31 | blanc |
| Verrou USB | `V2_Gate.stl` | à plat | 20 × 17 × 4 | bleu |
| Pince sangle (×1 ou ×2, collée au dos) | `V2_Strap_Clip.stl` | couchée sur le côté | 11 × 40 × 20 | n'importe |
| **Test** coin USB | `V2_TEST_coin_USB.stl` | dos sur le plateau | 63 × 31 × 31 | n'importe |

Ordre conseillé : 1) `V2_TEST_coin_USB` + `V2_Gate` (prise, verrou, Wemos),
2) `V2_Skin` (LCD dans la fenêtre, couleurs), 3) `V2_Tub` (la plus longue).

## Changements de filament de la façade (couche 0,2 mm)

| Hauteur | Filament | Ce qui apparaît |
|---|---|---|
| 0 – 2,0 mm | blanc | plaque, `piege.exe` et boutons (ajourés dans le bleu) |
| 2,0 – 2,8 mm | bleu foncé | barre de titre |
| 2,8 – 3,8 mm | rose | Clippy |
| 3,8 – 4,4 mm | blanc | yeux (pupilles = trous) |

Dans le slicer (Creality Print / Orca / Cura) : « changement de couleur » / pause M600
aux couches commençant à **2,0 / 2,8 / 3,8 mm**.

## Variante façade en marqueterie (sans changement de filament)

Dossier `stl/facade_marqueterie/`, pièces collées dans des logements
de 0,6 mm (jeu 0,15 mm par côté), toutes à plat face vers le haut :

| Pièce | Fichier | Taille (mm) | Filament |
|---|---|---|---|
| Plaque | `V2_Facade_Plate.stl` | 100 × 78 × 2,8 | blanc (boutons _ □ × en relief, symboles gravés) |
| Bandeau | `V2_Facade_Bar.stl` | 95 × 11 × 1,4 | bleu foncé |
| Clippy | `V2_Facade_Clippy.stl` | 13 × 28 × 1,6 | rose |
| Yeux | `V2_Facade_Eyes.stl` | 2 × Ø 5 × 0,8 | blanc |

- `piege.exe` est gravé de 1 mm dans le bandeau (fond de 0,4 mm, sinon l'intérieur
  des lettres tomberait) : soit un changement blanc → bleu à **0,4 mm** sur ce petit
  bandeau, soit peindre les lettres au feutre-peinture blanc.
- Pupilles : creux dans les yeux, à remplir au feutre noir.
- Collage : cyanoacrylate (super glue) en petits points, ou colle contact.
- Bandeau : **pas de lissage (ironing)**, il traîne du plastique dans les lettres gravées ;
  activer « éviter de traverser les parois », paroi extérieure à 30–40 mm/s.
  Tester l'emboîtement à sec d'abord ; si ça force, poncer le chant de la pièce.

## Quincaillerie

- 4 inserts laiton M3 × 4 (trou Ø 4,1) dans les bossages de la coque, posés au fer.
- 4 vis M3 tête fraisée, longueur 6–8 mm, par l'avant.
- Anneau porte-clé standard dans l'icône de la fenêtre (trou Ø 4,8).
- Sac : `V2_Strap_Clip` (source `scripts/strap_clip.py`), pince type ceinture collée au dos (époxy),
  ouverture vers le bas ; serre une sangle de 5 mm (pincement 3,5 mm).

## Montage

1. LCD contre la façade, plaqué par les 4 picots de la coque dans ses trous de fixation.
2. Wemos libre dans la boîte (placement au choix, colle chaude si besoin).
3. Fermer (4 vis). Brancher le câble par le trou du flanc droit, glisser le verrou
   dans les rails (fente vers l'avant) jusqu'à la butée.

## Hypothèses à vérifier au premier tirage

- LCD mesuré (PCB 80,2 × 35,8, cadre 70,9 × 24,5 × 6,3 mm, cadre à 8 mm du haut du PCB) ; trous à
  1,4 mm du bord, diamètre supposé 2,5–3 mm : picots Ø 2,0 centrés à 2,75 mm des bords.
- Jeu verrou / rails : 0,4 mm en épaisseur, 0,5 mm en hauteur par côté (`GATE_CH`, `GATE_T`, `GATE_CLR`).
- Faire d'abord un test rapide de la coque à 15 % de remplissage.
