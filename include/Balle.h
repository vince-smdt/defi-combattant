#ifndef BALLE_H
#define BALLE_H

#include "General.h"
// Detecter la balle et fait tomber le verre sur la balle
void balle(){
  SERVO_Enable(1);
  int position;
  SERVO_SetAngle(1, 180);
  while(IR_to_cm(IR_GAUCHE)> 5 || IR_to_cm(IR_DROIT) > 5){
    if (IR_to_cm(IR_GAUCHE)< 5 || IR_to_cm(IR_DROIT)< 5){
      for (position = 180; position <= 0; position -= 1){
        SERVO_SetAngle(1, position);
        delay(1);
      }
    }
  }
}

#endif // BALLE_H