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
void suivreMur(float dist_eloigner, float dist_rapprocher);
void suivreMurDuree(uint32_t ms);
void suivreCouleur();

float IR_to_cm(uint8_t id);

uint8_t detecterCouleur();
uint8_t couleurPlusProche(uint8_t red, uint8_t green, uint8_t blue);
uint8_t couleurMoyenne();


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

// Suit le long du mur
void suivreMur(float dist_eloigner, float dist_rapprocher) {
  float dist = IR_to_cm(IR_DROIT);
  const float DIST_ELOIGNER = 35;
  const float DIST_RAPPROCHER = 40;
  //Serial.println(dist);

  if (dist > DIST_RAPPROCHER)
    avancer(VITESSE_TOURNER, VITESSE_BASE);
  else if (dist < DIST_ELOIGNER)
    avancer(VITESSE_BASE, VITESSE_TOURNER);
  else
    avancer(VITESSE_BASE, VITESSE_BASE);
}

// Longe le mur pendant un certain temps
void suivreMurDuree(uint32_t ms) {
  uint32_t debut = millis();
  while (millis() - debut < ms)
    suivreMur(35, 40);
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
  uint16_t clear, red, green, blue;

  g_tcs.getRawData(&red, &green, &blue, &clear);

  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;

  // Serial.print("\tR:\t"); Serial.print(r);
  // Serial.print("\tG:\t"); Serial.print(g);
  // Serial.print("\tB:\t"); Serial.println(b);

  uint8_t couleur = couleurPlusProche(r, g, b);
  g_dernieresCouleurs[g_indexDerniereCouleur] = couleur;
  ++g_indexDerniereCouleur %= NB_DERNIERES_COULEURS;
  return couleur;
}

// Retourne la couleur du circuit la plus proche des valeurs RGB donnees en parametre
uint8_t couleurPlusProche(uint8_t red, uint8_t green, uint8_t blue) {
  uint8_t couleur = AUCUNE_COULEUR; // Couleur la plus proche
  uint32_t distance = INT32_MAX; // Distance (relative) de la couleur la plus proche

  for (int i = 0; i < NB_COULEURS; i++) {
    uint8_t r = COULEURS[i][0];
    uint8_t g = COULEURS[i][1];
    uint8_t b = COULEURS[i][2];
    uint32_t d = pow(red - r, 2) + pow(green - g, 2) + pow(blue - b, 2);

    if (d < distance) {
      distance = d;
      couleur = COULEURS[i][3];
    }
  }

  return couleur;
}

// Retourne la couleur la plus frequente des x dernieres mesures
uint8_t couleurMoyenne() {
  uint16_t frequences[NB_COULEURS + 1] = {0}; // +1 pour le AUCUNE_COULEUR
  uint8_t plusFrequente = AUCUNE_COULEUR;
  uint8_t occurences = 0;

  // On determine les frequences de chaque couleur
  for (int i = AUCUNE_COULEUR; i < NB_DERNIERES_COULEURS; i++)
    frequences[g_dernieresCouleurs[i]]++;

  // On trouve la couleur la plus frequente
  for (int i = AUCUNE_COULEUR; i <= NB_COULEURS; i++) {
    if (occurences < frequences[i]) {
      plusFrequente = i;
      occurences = frequences[i];
    }
  }

  return plusFrequente;
}


#endif // GENERAL_H
