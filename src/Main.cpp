#include <LibRobus.h>
#include "Globales.h"
#include "Types.h"
#include "General.h"
#include "Depart.h"
#include "Raccourci.h"
#include "Verre.h"

/****************************************/
/**** SETUP & LOOP ****/
/****************************************/

// Fonction d'initialisation du robot, est execute une seule fois
void setup() {
  BoardInit();
}

// Boucle principale du programme, est execute plusieurs fois
void loop() {
  // Ce switch va determiner ce que le robot doit faire dependemment de son etat actuel
  switch (g_etat) {
    case DEPART: { depart(); break; }
    case SUIVRE_LIGNE: { /* Mettre la fonction de sa partie ici */ break; }
    case PARTIE_GRISE: { /* Mettre la fonction de sa partie ici */ break; }
    case SUIVRE_LIGNE_JUSQUA_POUTRE: { /* Mettre la fonction de sa partie ici */ break; }
    case FAIRE_TOMBER_VERRE: { /*verre()*/; break; }
    case SUIVRE_LIGNE_JUSQUA_PARTIE_BLANCHE: { /* Mettre la fonction de sa partie ici */ break; }
    case METTRE_VERRE_SUR_BALLE: { /* Mettre la fonction de sa partie ici */ break; }
    case RETOURNER_SUR_PARCOURS: { /* Mettre la fonction de sa partie ici */ break; }
    case TRAVERSER_JUMP: { /* Mettre la fonction de sa partie ici */ break; }
    case SUIVRE_LIGNE_SHORTCUT: { /* Mettre la fonction de sa partie ici */ break; }
    case PARTIE_GRISE_SHORTCUT: { /* Mettre la fonction de sa partie ici */ break; }
    case ALLER_AU_SHORTCUT: { /* Mettre la fonction de sa partie ici */ break; }
    case PRENDRE_LE_SHORTCUT: { raccourci(); break; }
    case TRAVERSER_JUMP_APRES_SHORTCUT: { /* Mettre la fonction de sa partie ici */ break; }
    case ARRIVE: { g_fini = true; break; }
    default: { g_erreur = true; break; } // Etat invalide, on indique qu'il y a une erreur
  }

  // Si le robot a fini la course, on quitte le programme
  if (g_fini) {
    beep(1, 1000); // Signal d'arrivee
    exit(EXIT_SUCCESS); // Quitte le programme
  }

  // Si une erreur est detectee, le robot beep et on quitte le programme
  if (g_erreur) {
    beep(5, 100); // Signal d'erreur
    exit(EXIT_FAILURE); // Quitte le programme
  }

  // Le robot passe a son prochain etat
  g_etat++;
}
