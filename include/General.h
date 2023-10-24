#ifndef GENERAL_H
#define GENERAL_H

/****************************************/
/**** INCLUDES ****/
/****************************************/

#include <LibRobus.h>


/****************************************/
/**** FONCTIONS (DECLARATIONS) ****/
/****************************************/

void beep(int count, int ms);


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

#endif // GENERAL_H