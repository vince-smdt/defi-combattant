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
uint8_t DIST_MUR_AVANT_RACCOURCI = 15; // Distance du mur avant que le robot doit atteindre avant de faire la courbe pour sortir du raccourci (en cm)


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
    if (dist >= DIST_MUR_DROIT_RACCOURCI)
      // Si on s'eloigne du mur de droit, on veut se rapprocher
      avancer(dist > DIST_MUR_DROIT_RACCOURCI + 5 ? 0.3 : 0.25, 0.20);
    else
      // Si on est trop pres, on s'eloigne
      avancer(0.20, 0.25);
  }

  arret();
}

#endif // RACCOURCI_H
