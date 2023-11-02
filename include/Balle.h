#ifndef BALLE_H
#define BALLE_H

#include "General.h"
// Detecter la balle et fait tomber le verre sur la balle
void pousserleverre(){
  Serial.print ("debut pousser le verre");
  SERVO_Enable (2);
  SERVO_SetAngle(1, 0);
}

#endif // BALLE_H