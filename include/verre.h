#ifndef VERRE_H
#define VERRE_H 

#include "General.h"


void RetourEtatIniaial(){
  SERVO_SetAngle(0, 90);
  delay(500);
}


void FairTomberLeVerre(){

  SERVO_Enable(1);
  RetourEtatIniaial();
  while(IR_to_cm(IR_GAUCHE)> 15 || IR_to_cm(IR_DROIT) > 15){
    Serial.println(IR_to_cm(IR_DROIT));
    if (IR_to_cm(IR_GAUCHE)< 15){
      Serial.println("gauche");
      SERVO_SetAngle(0, 0);
      delay(3000);
      RetourEtatIniaial();
    }
    if (IR_to_cm(IR_DROIT)< 15){
      Serial.println("droit");
      SERVO_SetAngle(0, 180);
      delay(3000);
      RetourEtatIniaial();
    }
 }
}



#endif // VERRE_H