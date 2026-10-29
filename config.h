#pragma once

// Default hotspot names, used until a list is saved from the admin page.
// They must stay self-declared as a demo: never the name of a real network.
#define CFG_SSIDS "Ce_WiFi_est_un_piege", \
                  "Ca_marche_sur_ma_machine", \
                  "Alternance_cherchee_ici", \
                  "Le_piege_etait_le_CV", \
                  "Recruteur_connecte_toi", \
                  "Qui_a_casse_la_prod", \
                  "Embauchez_moi.exe", \
                  "Le_reseau_est_en_pause_cafe"
// Phones connected at the same time; 8 is the ESP8266 SDK maximum.
#define CFG_MAX_CLIENTS 8

// 1 = print every HTTP request (host, path, user agent) on the USB serial, to
// see which captive-portal probes a phone sends. Serial only, never stored.
#define CFG_LOG_HTTP 0

// LCD strings (ASCII only: the LCD ROM has no accents). The portal's own text
// lives in web/index.html.
#define CFG_NAME "Romain"
#define CFG_ROLE "Dev + Pentest"
#define CFG_WHEN "des juin 2027"
