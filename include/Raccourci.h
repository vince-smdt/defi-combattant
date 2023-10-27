#ifndef RACCOURCI_H
#define RACCOURCI_H

#include <LibRobus.h>
#include "General.h"
#include "Constantes.h"
#include "Globales.h"

/****************************************/
/**** CONSTANTES ****/
/****************************************/

uint8_t DIST_MUR_DROIT_RACCOURCI = 15; // Distance que le robot garde on mur droit quand il prend le raccourci (en cm)
float VITESSE_INF = 0.2; // Vitesse moins rapide pour l'ajustement via le mur
float VITESSE_SUP = 0.25; // Vitesse plus rapide pour l'ajustement via le mur
float VITESSE_MAX_G = 0.45; // Vitesse proportionnelle maximum que la roue de gauche peut avoir


/****************************************/
/**** FONCTIONS (DECLARATIONS) ****/
/****************************************/

void raccourci();


/****************************************/
/**** FONCTIONS (DEFINITIONS) ****/
/****************************************/

// Fait passer le robot par le raccourci et retourne ensuite sur la piste
void raccourci() {
  // On longe le mur de droit jusqu'a ce qu'on soit proche de la sortie
  while (true /* Tant que le detecteur de couleur ne voit pas du vert (sortie du shortcut) */) {
    float dist = IR_to_cm(IR_DROIT);
    if (dist >= DIST_MUR_DROIT_RACCOURCI) {
      // Si on s'eloigne du mur de droit, on veut se rapprocher
      float ajustementG = (VITESSE_MAX_G - VITESSE_SUP)/(IR_DIST_MAX - IR_DIST_MIN)*(dist - DIST_MUR_DROIT_RACCOURCI);
      float vitesseG = VITESSE_SUP + min(VITESSE_MAX_G, ajustementG);
      avancer(vitesseG, VITESSE_INF);
    } else
      // Si on est trop pres, on s'eloigne
      avancer(VITESSE_INF, VITESSE_SUP);
  }

  arret();
}

#endif // RACCOURCI_H
