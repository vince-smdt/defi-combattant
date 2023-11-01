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
EtatSuiveurLigne obtenirEtatLigne();


/****************************************/
/**** FONCTIONS (DEFINITIONS) ****/
/****************************************/

EtatSuiveurLigne obtenirEtatLigne(){
    int valeurSenseur = analogRead(A5);
    if(valeurSenseur > 750 && valeurSenseur < 850) return LIGNE_GAUCHE;
    if (valeurSenseur > 380 && valeurSenseur < 470) return LIGNE_DROITE;
    if (valeurSenseur > 620 && valeurSenseur < 710) return LIGNE_CENTRE;
    return AUCUNE_LIGNE;
}

void suivreLigne(){

    while (true /* Détecter fin de la ligne*/)
    {
        EtatSuiveurLigne etatCourant = obtenirEtatLigne();
        Serial.println("Etat: ");
        switch (etatCourant)
        {
        case LIGNE_DROITE:
            avancer(0.6f, 0.5f);
            Serial.println("Tourne à droite");
            break;
        case LIGNE_GAUCHE:
            avancer(0.5f, 0.6f);
            Serial.println("Tourne à gauche");
            break;
        case LIGNE_CENTRE:
            avancer(0.5f, 0.5f);
            Serial.println("Reste au centre");
            break;
        default:
            avancer(0.5f, 0.5f);
            Serial.println("wtf");
            break;
        }
    }
    
}

#endif // DEPART_H
