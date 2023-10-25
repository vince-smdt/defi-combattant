#ifndef DEPART_H
#define DEPART_H

#include <LibRobus.h>
#include "General.h"
#include "Globales.h"

/****************************************/
/**** CONSTANTES ****/
/****************************************/

const uint16_t TEMPS_MIN_BUMPER_ARRIERE = 500; // Temps min avant qu'on puisse rappuyer sur le bumper arriere (en ms)
const uint16_t TEMPS_MAX_BUMPER_ARRIERE = 1500; // Temps max pour rappuyer sur le bumper arriere (en ms)
const uint8_t MAX_APPUIES = 8; // Nb max de fois qu'on peut appuyer sur le bumper


/****************************************/
/**** FONCTIONS (DECLARATIONS) ****/
/****************************************/

void depart();
void position_robot();


/****************************************/
/**** FONCTIONS (DEFINITIONS) ****/
/****************************************/

// Determine la position du robot avec les appuis sur le bumper arriere
// Detecte la couleur de depart
// Attend le signal de depart
void depart() {
  position_robot();
  // TODO - Fonction pour attendre le sifflet
  // TODO - Fonction pour detecter la couleur
}

// Determine la position de depart du robot en fonction du nombre d'appuis sur le bumper arriere
void position_robot() {
  while (!ROBUS_IsBumper(REAR)); // Attend que le bumper arriere soit appuye

  uint8_t appuis = 1;
  uint16_t begin = millis();
  uint16_t now = begin;

  // Detecte le nombre de fois que le bumper se fait appuyer
  while (now - begin < TEMPS_MAX_BUMPER_ARRIERE && appuis < MAX_APPUIES) {
    if (ROBUS_IsBumper(REAR) && now - begin > TEMPS_MIN_BUMPER_ARRIERE) {
      appuis++;
      begin = millis();
    }
    now = millis();
  }
  g_position = appuis;

  beep(g_position, 50);
}

#endif // DEPART_H
