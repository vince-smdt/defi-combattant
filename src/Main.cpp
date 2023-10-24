/****************************************/
/**** INCLUDES ****/
/****************************************/

#include <LibRobus.h>
#include "General.h"


/****************************************/
/**** ENUMS ****/
/****************************************/

// Les etats possibles que le robot peut avoir, sont obligatoirement sequentiels (un apres l'autre)
// N'oubliez pas de modifier les nombres si vous ajoutez des etats
enum Etat {
  DEPART = 0,
  SUIVRE_LIGNE = 1,
  PARTIE_GRISE = 2,
  SUIVRE_LIGNE_JUSQUA_POUTRE = 3,
  FAIRE_TOMBER_VERRE = 4,
  SUIVRE_LIGNE_JUSQUA_PARTIE_BLANCHE = 5,
  METTRE_VERRE_SUR_BALLE = 6,
  RETOURNER_SUR_PARCOURS = 7,
  TRAVERSER_JUMP = 8,
  SUIVRE_LIGNE_SHORTCUT = 9,
  PARTIE_GRISE_SHORTCUT = 10,
  ALLER_AU_SHORTCUT = 11,
  PRENDRE_LE_SHORTCUT = 12,
  TRAVERSER_JUMP_APRES_SHORTCUT = 13,
  ARRIVE = 14
};


/****************************************/
/**** VARIABLES GLOBALES ****/
/****************************************/

// !!! Le prefixe "g_" indique une variable globale, ajoutez le si vous declarez d'autres variables globales !!!

int g_etat = DEPART; // Etat actuel du robot, est un int et non un type "Etat" pour qu'on puisse l'incrementer avec l'operateur ++
bool g_erreur = false; // Indique si une erreur a eu lieu dans le programme
bool g_fini = false; // Indique si le robot a fini la course


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
    case DEPART: { /* Mettre la fonction de sa partie ici */ break; }
    case SUIVRE_LIGNE: { /* Mettre la fonction de sa partie ici */ break; }
    case PARTIE_GRISE: { /* Mettre la fonction de sa partie ici */ break; }
    case SUIVRE_LIGNE_JUSQUA_POUTRE: { /* Mettre la fonction de sa partie ici */ break; }
    case FAIRE_TOMBER_VERRE: { /* Mettre la fonction de sa partie ici */ break; }
    case SUIVRE_LIGNE_JUSQUA_PARTIE_BLANCHE: { /* Mettre la fonction de sa partie ici */ break; }
    case METTRE_VERRE_SUR_BALLE: { /* Mettre la fonction de sa partie ici */ break; }
    case RETOURNER_SUR_PARCOURS: { /* Mettre la fonction de sa partie ici */ break; }
    case TRAVERSER_JUMP: { /* Mettre la fonction de sa partie ici */ break; }
    case SUIVRE_LIGNE_SHORTCUT: { /* Mettre la fonction de sa partie ici */ break; }
    case PARTIE_GRISE_SHORTCUT: { /* Mettre la fonction de sa partie ici */ break; }
    case ALLER_AU_SHORTCUT: { /* Mettre la fonction de sa partie ici */ break; }
    case PRENDRE_LE_SHORTCUT: { /* Mettre la fonction de sa partie ici */ break; }
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
