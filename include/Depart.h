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
void positionRobot();
void detecterCouleurDebut();
void initPositionServo();


/****************************************/
/**** FONCTIONS (DEFINITIONS) ****/
/****************************************/

// Determine la position du robot avec les appuis sur le bumper arriere
// Detecte la couleur de depart
// Attend le signal de depart
void depart() {
  initPositionServo();
  positionRobot();
  // while (analogRead(PIN_MICRO) < MICRO_VOLUME_DEBUT); // On attend le 5k (micro)
  detecterCouleurDebut();
}

// Position initiale du servo pour faire tomber le verre sur la balle
void initPositionServo(){
  SERVO_Enable(1);
  SERVO_SetAngle(1, 90);
  delay(1000);
}

// Determine la position de depart du robot en fonction du nombre d'appuis sur le bumper arriere
void positionRobot() {
  while (!ROBUS_IsBumper(REAR)); // Attend que le bumper arriere soit appuye

  uint8_t appuis = 1;
  uint16_t debut = millis();
  uint16_t maintenant = debut;

  // Detecte le nombre de fois que le bumper se fait appuyer
  while (maintenant - debut < TEMPS_MAX_BUMPER_ARRIERE && appuis < MAX_APPUIES) {
    if (ROBUS_IsBumper(REAR) && maintenant - debut > TEMPS_MIN_BUMPER_ARRIERE) {
      appuis++;
      debut = millis();
    }
    maintenant = millis();
  }
  g_position = appuis;

  beep(g_position, 75);
}

void detecterCouleurDebut() {
  // On reverifie la couleur de debut tant qu'on en detecte pas
  uint16_t mesures = 0;

  do {
    detecterCouleur();
    g_couleurDebut = couleurMoyenne();
    mesures++;
  }
  while (mesures < NB_DERNIERES_COULEURS && g_couleurDebut != VERT && g_couleurDebut != JAUNE);



  // TEST
  if (g_couleurDebut == VERT)
    beep(4, 50);
  else
    beep(8, 50);
}

#endif // DEPART_H
