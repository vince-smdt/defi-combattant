// Ce fichier contient toutes les variables globales utilisees dans le code
// Toutes les variables globales doivent commencer avec le prefixe "g_"

#ifndef GLOBALES_H
#define GLOBALES_H

#include <LibRobus.h>
#include "Types.h"
#include <Adafruit_TCS34725.h>
/****************************************/
/**** VARIABLES GLOBALES ****/
/****************************************/

uint8_t g_etat = DEPART; // Etat actuel du robot, est un int et non un type "Etat" pour qu'on puisse l'incrementer avec l'operateur ++
uint8_t g_position = 0; // La position du robot, determine par le nombre d'appuis sur le bumper arriere
uint8_t g_couleurDebut = AUCUNE_COULEUR; // Couleur sur laquelle le robot se retrouve au debut

bool g_erreur = false; // Indique si une erreur a eu lieu dans le programme
bool g_fini = false; // Indique si le robot a fini la course

EtatSuiveurLigne g_derniereManoeuvre = AUCUNE_LIGNE;


unsigned long g_dureeCentre = 0;
unsigned long g_debutCentre = 0;
float g_correctionG = 1.0; // Coefficient de correction moteur gauche
float g_correctionD = 1.0; // Coefficient de correction moteur droit
Adafruit_TCS34725 g_tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

#endif // GLOBALES_H
