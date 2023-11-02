#ifndef RACCOURCI_H
#define RACCOURCI_H

#include <LibRobus.h>
#include "General.h"
#include "Constantes.h"
#include "Globales.h"

/****************************************/
/**** CONSTANTES ****/
/****************************************/

const float DISTANCE_RAPPROCHER = 12.0; // Le robot se rapproche du mur s'il s'en eloigne plus loin que cette distance en cm
const float DISTANCE_ELOIGNER = 10.1; // Le robot s'eloigne du mur s'il en est plus proche que cette distance en cm


/****************************************/
/**** FONCTIONS (DECLARATIONS) ****/
/****************************************/

void raccourci();


/****************************************/
/**** FONCTIONS (DEFINITIONS) ****/
/****************************************/

// Fait passer le robot par le raccourci et retourne ensuite sur la piste
void raccourci() {
  uint32_t debut = millis();

  // Ajustement pour que le robot soit a cote du mur (setup shortcut)
  avancerDuree(VITESSE_BASE, 0, 750);
  avancerDuree(VITESSE_BASE, VITESSE_BASE, g_couleurDebut == VERT ? 500 : 1400);
  avancerDuree(0, VITESSE_BASE, 750);

  // Loop pour longer le mur pour le shortcut
  while (millis() - debut < 25000) {
    float dist = IR_to_cm(IR_DROIT);

    if (dist > DISTANCE_RAPPROCHER)
      avancer(VITESSE_BASE, 0);
    else if (dist < DISTANCE_ELOIGNER)
      avancer(0, VITESSE_BASE);
    else
      avancer(VITESSE_BASE, VITESSE_BASE);
  }

  arret();
  beep(3, 100);
  g_fini = true;
}

#endif // RACCOURCI_H
