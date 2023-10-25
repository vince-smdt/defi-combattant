#ifndef DEPART_H
#define DEPART_H

#include <LibRobus.h>
#include "General.h"
#include "Globales.h"

/****************************************/
/**** CONSTANTES ****/
/****************************************/

const uint16_t TEMPS_MIN_BUMPER_ARR = 500; // Temps min avant qu'on puisse rappuyer sur le bumper arriere (en ms)
const uint16_t TEMPS_MAX_BUMPER_ARR = 1500; // Temps max pour rappuyer sur le bumper arriere (en ms)
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
  // TODO - Detecter la couleur
  // TODO - Attendre le sifflet
}

// Determine la position du robot en fonction du nombre d'appuis sur le bumper arriere
void position_robot() {
  while (!ROBUS_IsBumper(REAR)); // Attend que le bumper arriere soit appuye

  uint8_t appuis = 1;
  uint32_t begin = millis();
  uint32_t now = begin;

  // Detecte le nombre de fois que le bumper se fait appuyer
  while (now - begin < TEMPS_MAX_BUMPER_ARR && appuis < MAX_APPUIES) {
    if (ROBUS_IsBumper(REAR) && now - begin > TEMPS_MIN_BUMPER_ARR) {
      appuis++;
      begin = millis();
    }
    now = millis();
  }
  g_position = appuis;

  beep(g_position, 50);
}

#endif // DEPART_H
