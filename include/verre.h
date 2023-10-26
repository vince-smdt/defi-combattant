#ifndef VERRE_H
#define VERRE_H 

#include "General.h"


void FairTomberLeVerre(){

  SERVO_Enable(1);
  int position;
  while(IR_to_cm(IR_GAUCHE)> 15 || IR_to_cm(IR_DROIT) > 15){
    Serial.println(IR_to_cm(IR_GAUCHE));
  if (IR_to_cm(IR_GAUCHE)< 15){
    for (position = 90; position <= 180; position += 1){
    SERVO_SetAngle(1, position);
    delay(1);
    }
    delay(3000);
    for (position = 180; position >= 90; position -= 1){
      SERVO_SetAngle(1, position);
      delay(1);
    }
    
  }
  if (IR_to_cm(IR_DROIT)< 15){
    for (position = 90; position >= 0; position -= 1){
      SERVO_SetAngle(1, position);
      delay(1);
    }
    delay(3000);
    for (position = 0; position <= 90; position += 1){
      SERVO_SetAngle(1, position);
      delay(1);
    }
  }
}
}




#endif // VERRE_H