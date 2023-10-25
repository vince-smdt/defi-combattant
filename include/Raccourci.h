#ifndef RACCOURCI_H
#define RACCOURCI_H

#include <LibRobus.h>
#include "General.h"
#include "Constantes.h"

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
  while (ROBUS_ReadIR(FRONT) >= DIST_MUR_AVANT_RACCOURCI) {
    if (ROBUS_ReadIR(RIGHT) >= DIST_MUR_DROIT_RACCOURCI)
      // Si on s'eloigne du mur de droit, on veut se rapprocher
      MOTOR_SetSpeedAll(0.55, 0.45);
    else
      // Si on est trop pres, on s'eloigne
      MOTOR_SetSpeedAll(0.45, 0.55);
    delay(DELAI_BOUCLE);
  }

  // On avance en courbe pour retourner sur la piste
  MOTOR_SetSpeedAll(0.75, 0.5);
  delay(500);

  // On arrete les moteurs
  arret();
}

#endif // RACCOURCI_H
