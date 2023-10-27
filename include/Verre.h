#ifndef VERRE_H
#define VERRE_H 

#include "General.h"

/****************************************/
/**** CONSTANTES ****/
/****************************************/

const uint16_t DELAI_SERVO = 250; // Temps attendu apres avoir fait un mouvement avec le servo


/****************************************/
/**** FONCTIONS (DECLARATIONS) ****/
/****************************************/

void verre();
void tournerServo(uint8_t angle);

bool pousserVerre();


/****************************************/
/**** FONCTIONS (DEFINITIONS) ****/
/****************************************/

// Detecte et fait tomber le verre
void verre(){
  SERVO_Enable(SERVO_TOMBER_VERRE);
  // while (!pousserVerre()); // Tant qu'on n'a pas pousse le verre on attend
  while (true) pousserVerre();
  SERVO_Disable(SERVO_TOMBER_VERRE);
}

// Fait tourner le servo a un angle de 0 a 180 degres pendant un delai de temps fixe
void tournerServo(uint8_t angle) {
  SERVO_SetAngle(SERVO_TOMBER_VERRE, angle);
  delay(DELAI_SERVO);
  SERVO_SetAngle(SERVO_TOMBER_VERRE, 90);
  delay(DELAI_SERVO);
}

// Detecte s'il y a un verre, dans le cas echeant fait tourner le bras dans la dir detectee
// Retourne true si le bras a ete bouge
bool pousserVerre() {
  if (IR_to_cm(IR_GAUCHE) < 15)
    tournerServo(0);
  else if (IR_to_cm(IR_DROIT) < 15)
    tournerServo(180);
  else
    return false;
  return true;
}

#endif // VERRE_H
