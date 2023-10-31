#ifndef GENERAL_H
#define GENERAL_H

#include <LibRobus.h>
#include "Constantes.h"
#include "Globales.h"

/****************************************/
/**** FONCTIONS (DECLARATIONS) ****/
/****************************************/

void beep(int count, int ms);
void arret();
void avancer(float vitesseG, float vitesseD);
void correction(float vitesseG, float vitesseD, int32_t pulsesG, int32_t pulsesD);
void avancerDuree(float vitesseG, float vitesseD, uint32_t ms);
void accelerer(float vitesseDebut, float vitesseFin, uint32_t ms);
void suivreCouleur();

float IR_to_cm(uint8_t id);

uint8_t detecterCouleur();


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

// Fait arreter le robot
void arret() {
  MOTOR_SetSpeed(LEFT, 0);
  MOTOR_SetSpeed(RIGHT, 0);
}

// Fait avancer le robot avec l'ajustement PID et ajuste les coefficients de correction
void avancer(float vitesseG, float vitesseD) {
  MOTOR_SetSpeed(LEFT, vitesseG * g_correctionG);
  MOTOR_SetSpeed(RIGHT, vitesseD * g_correctionD);
  Serial.print("Vitesses: ");
  Serial.print(vitesseG * g_correctionG);
  Serial.print(", ");
  Serial.println(vitesseD * g_correctionD);
  delay(DELAI_AVANCER);
  correction(vitesseG, vitesseD, ENCODER_ReadReset(LEFT), ENCODER_ReadReset(RIGHT));
}

// Fait le calcul des coefficients de correction, les pulses representent la dist parcourue depuis la derniere mesure
void correction(float vitesseG, float vitesseD, int32_t pulsesG, int32_t pulsesD) {
  if (vitesseG == 0 || vitesseD == 0 || pulsesG == 0 || pulsesD == 0)
    return;

  pulsesG = abs(pulsesG);
  pulsesD = abs(pulsesD);

  const float RAPPORT_G = pulsesG / vitesseG;
  const float RAPPORT_D = pulsesD / vitesseD;
  const float RAPPORT_MOY = (RAPPORT_G + RAPPORT_D) / 2;

  // On modifie le coefficient de correction
  g_correctionG -= 1 - (RAPPORT_MOY / RAPPORT_G);
  g_correctionD -= 1 - (RAPPORT_MOY / RAPPORT_D);

  // On s'assure que le coefficient depasse pas les limites
  g_correctionG = constrain(g_correctionG, CORRECTION_MIN, CORRECTION_MAX);
  g_correctionD = constrain(g_correctionD, CORRECTION_MIN, CORRECTION_MAX);
}

// Avance pendant une duree de temps fixe
void avancerDuree(float vitesseG, float vitesseD, uint32_t ms) {
  uint32_t debut = millis();
  while (millis() - debut < ms)
    avancer(vitesseG, vitesseD);
}

// Fait graduellement augmenter la vitesse du robot
// NOTE: Il est possible de ralentir avec cette fonction en mettant une vitesse de debut plus grande que celle de fin
void accelerer(float vitesseDebut, float vitesseFin, uint32_t ms) {
  const int NB_INCR = ms / DELAI_AVANCER; // Nb de fois qu'on modifie la vitesse
  const float INCR_VITESSE = (vitesseFin - vitesseDebut) / NB_INCR; // Increment de vitesse par iteration de boucle

  for (int i = 0; i < NB_INCR - 1; i++) {
    const float VITESSE = INCR_VITESSE * i + vitesseDebut;
    avancer(VITESSE, VITESSE);
  }
  avancer(vitesseFin, vitesseFin);
}

// Suit la couleur mise en parametre
void suivreCouleur() {
  uint8_t couleur = detecterCouleur();
  Serial.print("Couleur: ");
  Serial.println(couleur);

  if (couleur <= g_couleurDebut)
    // On est sur la bonne voie
    avancer(VITESSE_BASE, VITESSE_BASE);
  else
    // On est trop a gauche, on reajuste
    avancer(VITESSE_TOURNER, VITESSE_BASE);
}

// Converti la valeur analogue d'un capteur infrarouge en cm
// Le param "id" represente IR0 a IR3 (0-3)
float IR_to_cm(uint8_t id) {
  return constrain(5500.0/ROBUS_ReadIR(id), IR_DIST_MIN, IR_DIST_MAX);
}

// Retourne la couleur detectee par le senseur de couleur
uint8_t detecterCouleur() {
  uint16_t C, R, G, B;

  g_tcs.getRawData(&R, &G, &B, &C);

  // Serial.println(R);
  // Serial.println(G);
  // Serial.println(B);

  g_tcs.setInterrupt(false);

  float X,Y,Z,x,y;

  X= (-0.14282)*(R)+(1.54924)*(G)+(-0.95641)*(B);
  Y= (-0.32466)*(R)+(1.57837)*(G)+(-0.73191)*(B);
  Z=(-0.68202)*(R)+(0.77073)*(G)+(0.56332)*(B);

  x=X/(X+Y+Z);
  y=Y/(X+Y+Z);

  // Serial.println(x);
  // Serial.println(y);

  if (0.27<=x && x<=0.35 && 0.35<=y && y<=0.37)
    {
      return VERT;
    }
  else if (0.44<=x && x<=0.46 && 0.41<=y && y<=0.43)
    {
      return JAUNE;
    }
  else if (0.40<=x && x<=0.44 && 0.37<=y && y<=0.39)
    {
      return ROUGE;
    }
  else if (0.19<=x && x<=0.26 && 0.22<=y && y<=0.32)
    {
      return BLEU;
    }
    else if (0.35<=x && x<=0.38 && 0.36<=y && y<=0.38)
    {
      return BLANC;
    }
   else
   {
    return AUCUNE;
   }
}


#endif // GENERAL_H
