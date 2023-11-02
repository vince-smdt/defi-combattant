#ifndef SUIVREMUR_H
#define SUIVREMUR_H

#include "General.h"

/****************************************/
/**** FONCTIONS (DECLARATIONS) ****/
/****************************************/

void suivreMur(float dist_eloigner, float dist_rapprocher);
void suivreMurDuree(uint32_t ms, float dist_eloigner, float dist_rapprocher);
float moyenneDistMur();
void suivreMurCouleur();


/****************************************/
/**** FONCTIONS (DEFINITIONS) ****/
/****************************************/

// Suit le long du mur
void suivreMur(float dist_eloigner, float dist_rapprocher) {
  float dist = IR_to_cm(IR_DROIT);

  g_dernieresMesures[g_indexDerniereMesure] = dist;
  ++g_indexDerniereMesure %= NB_DERNIERES_MESURES;

  if (dist > dist_rapprocher)
    avancer(VITESSE_TOURNER, VITESSE_BASE);
  else if (dist < dist_eloigner)
    avancer(VITESSE_BASE, VITESSE_TOURNER);
  else
    avancer(VITESSE_BASE, VITESSE_BASE);
}

// Longe le mur pendant un certain temps
void suivreMurDuree(uint32_t ms, float dist_eloigner, float dist_rapprocher) {
  uint32_t debut = millis();
  while (millis() - debut < ms)
    suivreMur(dist_eloigner, dist_rapprocher);
}

float moyenneDistMur() {
  float sommeMesures = 0;

  if (g_nbMesures < NB_DERNIERES_MESURES)
    g_nbMesures++;

  for (int i = 0; i < g_nbMesures; i++)
    sommeMesures += g_dernieresMesures[i];

  return sommeMesures / g_nbMesures;
}

void suivreMurCouleur() {
  if (g_couleurDebut == VERT) {
    suivreMurDuree(8000, 33, 38);
  }
  else {
    delay(50);

    while (g_nbMesures < NB_DERNIERES_MESURES || moyenneDistMur() > 15)
      suivreMur(77, 79.5);

    arret();
    beep(5, 100);
  }
}

#endif // SUIVREMUR_H