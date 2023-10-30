#ifndef VERRE_H
#define VERRE_H 

#include "General.h"

void RetouneEtatInitial(){
  SERVO_SetAngle(0, 90);
  delay(500);
}



// Detecte et fait tomber le verre
void verre(){
  SERVO_Enable(1);
  while(true){
    Serial.println(IR_to_cm(IR_GAUCHE));
    if (IR_to_cm(IR_GAUCHE)< 15){
      SERVO_SetAngle(0, 0);
      delay(3000);
      RetouneEtatInitial();
    }
    if (IR_to_cm(IR_DROIT)< 15){
      SERVO_SetAngle(0, 180);
      delay(3000);
      RetouneEtatInitial();
    }
  }
}


#endif // VERRE_H