#pragma once

// Default hotspot names, used until a list is saved from the admin page.
// They must stay self-declared as a demo: never the name of a real network.
#define CFG_SSIDS "Ce_WiFi_est_un_piege", "Clique_si_t_es_curieux", \
                  "Pas_un_virus_promis", "Alternance_cherchee_ici"
#define CFG_MAX_CLIENTS 8

// 1 = print every HTTP request (host, path, user agent) on the USB serial, to
// see which captive-portal probes a phone sends. Nothing is stored.
#define CFG_LOG_HTTP 0

#define CFG_NAME "Romain"
#define CFG_ROLE "Dev + Pentest"
#define CFG_SCHOOL "Ecole 42 Angouleme"
#define CFG_TITLE "Etudiant 42, stagiaire pentest"
#define CFG_WHEN "des juin 2027"
#define CFG_EMAIL "contact@example.com"
#define CFG_GITHUB "https://github.com/your-handle"
#define CFG_LINKEDIN "https://www.linkedin.com/in/your-handle"
#define CFG_SITE "https://example.com"
