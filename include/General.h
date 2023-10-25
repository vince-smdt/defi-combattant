#ifndef GENERAL_H
#define GENERAL_H

#include <LibRobus.h>

/****************************************/
/**** FONCTIONS (DECLARATIONS) ****/
/****************************************/

void beep(int count, int ms);
void MOTOR_SetSpeedAll(float speedLeft, float speedRight);
void arret();


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
void MOTOR_SetSpeedAll(float speedLeft, float speedRight) {
  MOTOR_SetSpeed(LEFT, speedLeft);
  MOTOR_SetSpeed(RIGHT, speedRight);
}

// Fait arreter le robot
void arret() {
  MOTOR_SetSpeedAll(0, 0);
}

#endif // GENERAL_H
