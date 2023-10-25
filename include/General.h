#ifndef GENERAL_H
#define GENERAL_H

#include <LibRobus.h>
#include "Constantes.h"

/****************************************/
/**** FONCTIONS (DECLARATIONS) ****/
/****************************************/

void beep(int count, int ms);
void arret();
void avancer(float vitesseG, float vitesseD);
void correction(float vitesseG, float vitesseD, uint32_t distG, uint32_t distD);
void avancerDuree(float vitesseG, float vitesseD, uint32_t duree);
void accelerer(float vitesseDebut, float vitesseFin, uint32_t duree);


/****************************************/
/**** FONCTIONS (DEFINITIONS) ****/
/****************************************/

// Fait beeper le robot un certain nombre de fois
void beep(int count, int ms){
  for(int i = 0; i < count; i++) {
    AX_BuzzerON();
    delay(ms);
    AX_BuzzerOFF();
    delay(ms);
  }
}

// Fait arreter le robot
void arret() {
  MOTOR_SetSpeed(LEFT, 0);
  MOTOR_SetSpeed(RIGHT, 0);
}

// Fait avancer le robot avec l'ajustement PID et ajuste les coefficients de correction
void avancer(float vitesseG, float vitesseD) {
  MOTOR_SetSpeed(LEFT, vitesseG * g_correctionG);
  MOTOR_SetSpeed(RIGHT, vitesseD * g_correctionD);
  delay(DELAI_AVANCER);
  correction(vitesseG, vitesseD, ENCODER_ReadReset(LEFT), ENCODER_ReadReset(RIGHT));
}

// Fait le calcul des coefficients de correction
void correction(float vitesseG, float vitesseD, uint32_t distG, uint32_t distD) {
  distG = abs(distG);
  distD = abs(distD);

  const float RAPPORT_G = distG / vitesseG;
  const float RAPPORT_D = distD / vitesseD;
  const float RAPPORT_MOY = (RAPPORT_G + RAPPORT_D) / 2;

  g_correctionG -= 1 - (RAPPORT_MOY / RAPPORT_G);
  g_correctionD -= 1 - (RAPPORT_MOY / RAPPORT_D);
}

// Avance pendant une duree de temps fixe
void avancerDuree(float vitesseG, float vitesseD, uint32_t duree) {
  uint32_t debut = millis();
  while (millis() - debut < duree)
    avancer(vitesseG, vitesseD);
}

// Fait graduellement augmenter la vitesse du robot
// NOTE: Il est possible de ralentir avec cette fonction en mettant une vitesse de debut plus grande que celle de fin
void accelerer(float vitesseDebut, float vitesseFin, uint32_t duree) {
  const int NB_INCR = duree / DELAI_AVANCER; // Nb de fois qu'on modifie la vitesse
  const float INCR_VITESSE = (vitesseFin - vitesseDebut) / NB_INCR; // Increment de vitesse par iteration de boucle

  for (int i = 0; i < NB_INCR - 1; i++) {
    const float VITESSE = INCR_VITESSE * i + vitesseDebut;
    avancer(VITESSE, VITESSE);
  }
  avancer(vitesseFin, vitesseFin);
}

#endif // GENERAL_H
