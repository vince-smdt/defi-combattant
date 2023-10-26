// Ce fichier contient toutes les constantes globales utilises dans le code

#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <LibRobus.h>

/****************************************/
/**** CONSTANTES ****/
/****************************************/

const uint16_t DELAI_AVANCER = 50; // Delai de temps attendu a chaque iteration de boucle
const float VITESSE_MIN = 0.15;
const float VITESSE_MAX = 1.0;

uint8_t IR_GAUCHE = 1;
uint8_t IR_DROIT = 2;
uint8_t IR_DIST_MIN = 10;
uint8_t IR_DIST_MAX = 80;

#endif // CONSTANTES_H
