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
            avancer(VITESSE_TOURNER, VITESSE_BASE);
            Serial.println("Tourne à droite");
            break;
        case LIGNE_GAUCHE:
            avancer(VITESSE_BASE, VITESSE_TOURNER);
            Serial.println("Tourne à gauche");
            break;
        case LIGNE_CENTRE:
            avancer(VITESSE_BASE, VITESSE_BASE);
            Serial.println("Reste au centre");
            break;
        default:
            avancer(VITESSE_BASE, VITESSE_BASE);
            Serial.println("wtf");
            break;
        }
    }
    
}

#endif // DEPART_H
