#ifndef SUIVRELIGNE_H
#define SUIVRELIGNE_H

#include <LibRobus.h>
#include "General.h"
#include "Globales.h"

/****************************************/
/**** CONSTANTES ****/
/****************************************/



/****************************************/
/**** FONCTIONS (DECLARATIONS) ****/
/****************************************/

void suivreLigne();
void obtenirEtatLigne();


/****************************************/
/**** FONCTIONS (DEFINITIONS) ****/
/****************************************/

void obtenirEtatLigne(){}

void suivreLigne(){
    int valeurSenseur = 0;

    while (true /* Détecter fin de la ligne*/)
    {
        valeurSenseur = analogRead(A5);
        Serial.println("Valeur analogue: ");
        Serial.println(valeurSenseur);
        delay(2000);
    }
    
}

#endif // DEPART_H
