#ifndef VERRE_H
#define VERRE_H 

#include "General.h"

void RetouneEtatInitial(){
  SERVO_SetAngle(0, 90);
  delay(500);
}



// Detecte et fait tomber le verre
void verre(){
  arret();
  beep(3, 100);

  bool verreDetecte = false;

  float lastDist = 0;
  float currDist = IR_to_cm(IR_DROIT);
  float diffDist = 0;

  uint32_t debut = millis();

  while (couleurMoyenne() != BLANC) {
    lastDist = currDist;
    currDist = IR_to_cm(IR_DROIT);
    diffDist = currDist - lastDist;

    // Essaye de centrer la trajectoire du robot vis a vis le mur pendant les quelques premieres
    // La trajectoire est corrigee avec le taux de variation de la distance au mur
    if (millis() - debut > 2000 || diffDist == 0)
      avancer(VITESSE_BASE, VITESSE_BASE);
    else if (diffDist > 0)
      avancer(VITESSE_BASE + 0.05, VITESSE_BASE);
    else
      avancer(VITESSE_BASE, VITESSE_BASE + 0.05);

    if (g_couleurDebut == VERT) {
      if (IR_to_cm(IR_GAUCHE) < 15 && !verreDetecte) {
        arret();
        beep(10, 50);
        verreDetecte = true;
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