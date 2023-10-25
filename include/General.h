#ifndef GENERAL_H
#define GENERAL_H

#include <LibRobus.h>
#include "Constantes.h"

/****************************************/
/**** FONCTIONS (DECLARATIONS) ****/
/****************************************/

void beep(int count, int ms);
void MOTOR_SetSpeedAll(float vitesseG, float vitesseD);
void arret();
void avancer(float vitesseG, float vitesseD);
void correction(float vitesseG, float vitesseD, uint32_t distG, uint32_t distD);


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

// Permet de specifier la vitesse du moteur droit et gauche en un seul appel de fonction
void MOTOR_SetSpeedAll(float vitesseG, float vitesseD) {
  MOTOR_SetSpeed(LEFT, vitesseG);
  MOTOR_SetSpeed(RIGHT, vitesseD);
}

// Fait arreter le robot
void arret() {
  MOTOR_SetSpeedAll(0, 0);
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

#endif // GENERAL_H
