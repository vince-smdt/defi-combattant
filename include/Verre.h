#ifndef VERRE_H
#define VERRE_H 

#include "General.h"
#include "SuivreMur.h"

void RetouneEtatInitial(){
  SERVO_SetAngle(0, 90);
  delay(500);
}

// Detecte et fait tomber le verre
void verre(){
  arret();
  beep(3, 100);

  uint32_t debut = millis();
  const uint16_t TEMPS_POUR_CENTRER = 3000;
  float distLast = 0;
  float distCurr = millis();
  float distDiff = 0;

  while (couleurMoyenne() != BLANC) {

    distLast = distCurr;
    distCurr = millis();
    distDiff = distCurr - distLast;

    if (millis() - debut > TEMPS_POUR_CENTRER || distDiff == 0)
      avancer(VITESSE_BASE, VITESSE_BASE);
    else if (distDiff > 0)
      avancer(VITESSE_BASE, VITESSE_BASE - 0.05);
    else
      avancer(VITESSE_BASE - 0.05, VITESSE_BASE);

    if (couleurMoyenne() == JAUNE)
    {
      suivreMur(0, 10.5);
      if (digitalRead(33) == 0 || digitalRead(49) == 0)
      {
        SERVO_SetAngle(0, 180);
        delay(3000);
        RetouneEtatInitial();
      }
    }
    if (couleurMoyenne() == VERT)
    {
      if (IR_to_cm(IR_GAUCHE)< 15){
        SERVO_SetAngle(0, 0);
        delay(3000);
        RetouneEtatInitial();
      }
    }
  }

  arret();

  // SERVO_Enable(1);
  // while(true){
  //   Serial.println(IR_to_cm(IR_GAUCHE));
  //   if (IR_to_cm(IR_GAUCHE)< 15){
  //     SERVO_SetAngle(0, 0);
  //     delay(3000);
  //     RetouneEtatInitial();
  //   }
  //   if (IR_to_cm(IR_DROIT)< 15){
  //     SERVO_SetAngle(0, 180);
  //     delay(3000);
  //     RetouneEtatInitial();
  //   }
  // }
  }


#endif // VERRE_H