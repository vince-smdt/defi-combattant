#ifndef RACCOURCI_H
#define RACCOURCI_H

#include <LibRobus.h>
#include "General.h"
#include "Constantes.h"
#include "Globales.h"

/****************************************/
/**** CONSTANTES ****/
/****************************************/

const float DISTANCE_RAPPROCHER = 17.0; // Le robot se rapproche du mur s'il s'en eloigne plus loin que cette distance en cm
const float DISTANCE_ELOIGNER = 12.0; // Le robot s'eloigne du mur s'il en est plus proche que cette distance en cm
const float VITESSE_RACCOURCI = 0.2; // Vitesse des roues du robot pendant qu'il fait le tour avec le raccourci


/****************************************/
/**** FONCTIONS (DECLARATIONS) ****/
/****************************************/

void raccourci();


/****************************************/
/**** FONCTIONS (DEFINITIONS) ****/
/****************************************/

// Fait passer le robot par le raccourci et retourne ensuite sur la piste
void raccourci() {
  // On longe le mur pendant tout le tour
  while (true /* Detecter fin de tour */) {
    float dist = IR_to_cm(IR_DROIT);

    if (dist > DISTANCE_RAPPROCHER)
      avancer(VITESSE_RACCOURCI, 0);
    else if (dist < DISTANCE_ELOIGNER)
      avancer(0, VITESSE_RACCOURCI);
    else
      avancer(VITESSE_RACCOURCI, VITESSE_RACCOURCI);
  }
}

#endif // RACCOURCI_H
