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

  while (couleurMoyenne() != BLANC) {
    detecterCouleur();
    avancer(VITESSE_BASE + 0.01, VITESSE_BASE);

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
}


#endif // VERRE_H