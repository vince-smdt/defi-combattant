// Ce fichier contient toutes les variables globales utilisees dans le code
// Toutes les variables globales doivent commencer avec le prefixe "g_"

#ifndef GLOBALES_H
#define GLOBALES_H

#include <LibRobus.h>
#include "Types.h"

/****************************************/
/**** VARIABLES GLOBALES ****/
/****************************************/

uint8_t g_etat = DEPART; // Etat actuel du robot, est un int et non un type "Etat" pour qu'on puisse l'incrementer avec l'operateur ++
bool g_erreur = false; // Indique si une erreur a eu lieu dans le programme
bool g_fini = false; // Indique si le robot a fini la course
uint8_t g_position = 0; // La position du robot, determine par le nombre d'appuis sur le bumper arriere

#endif // GLOBALES_H
