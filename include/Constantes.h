// Ce fichier contient toutes les constantes globales utilises dans le code

#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <LibRobus.h>
#include "Types.h"

/****************************************/
/**** CONSTANTES ****/
/****************************************/

const uint16_t DELAI_AVANCER = 50; // Delai de temps attendu a chaque iteration de boucle
const float VITESSE_MIN = 0.15;
const float VITESSE_BASE = 0.4; // Quand le robot suit la ligne de couleur
const float VITESSE_TOURNER = 0.6; // QUand le robot doit tourner pour rester sur sa couleur
const float VITESSE_LIGNE_BASE = 0.15;
const float VITESSE_LIGNE_TOURNE_BASE = 0.2;
const float VITESSE_DIFF_TOURNER = 0.05;
const float VITESSE_MAX = 1.0;
const float CORRECTION_MIN = 0.9;
const float CORRECTION_MAX = 1.1;

const uint8_t IR_GAUCHE = 1;
const uint8_t IR_DROIT = 2;
const uint8_t IR_DIST_MIN = 10;
const uint8_t IR_DIST_MAX = 80;

// Les couleurs RGB du circuit
const uint8_t NB_COULEURS = 5;
uint8_t COULEURS[NB_COULEURS][4] = {
  {50, 80, 100, BLEU},  // BLEU
  {60, 100, 70, VERT},  // VERT
  {107, 90, 38, JAUNE}, // JAUNE
  {130, 60, 50, ROUGE}, // ROUGE
  {88, 85, 65, BLANC}   // BLANC
};
const uint8_t NB_DERNIERES_COULEURS = 10; // Nb couleurs gardees dans le buffer pour calculer la moyenne

#endif // CONSTANTES_H
