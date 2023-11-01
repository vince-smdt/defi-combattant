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
    if(valeurSenseur > 750 && valeurSenseur < 850){
        return LIGNE_GAUCHE;
    } 
    if (valeurSenseur > 380 && valeurSenseur < 470){
        return LIGNE_DROITE;
    }
    if (valeurSenseur > 620 && valeurSenseur < 710){
        return LIGNE_CENTRE;
    } 
    return g_derniereManoeuvre;
}

void suivreLigne(){
    while (true /* Détecter fin de la ligne*/)
    {
        EtatSuiveurLigne etatCourant = obtenirEtatLigne();
        Serial.println("Etat: ");
        switch (etatCourant)
        {
        case LIGNE_DROITE:
            avancer(VITESSE_LIGNE_BASE + VITESSE_DIFF_TOURNER, VITESSE_LIGNE_BASE - VITESSE_DIFF_TOURNER);
            Serial.println("Tourne à droite");
            g_debutCentre = 0;
            g_derniereManoeuvre = etatCourant;
            break;
        case LIGNE_GAUCHE:
            avancer(VITESSE_LIGNE_BASE - VITESSE_DIFF_TOURNER, VITESSE_LIGNE_BASE + VITESSE_DIFF_TOURNER);
            Serial.println("Tourne à gauche");
            g_debutCentre = 0;
            g_derniereManoeuvre = etatCourant;
            break;
        case LIGNE_CENTRE:
            avancer(VITESSE_LIGNE_BASE, VITESSE_LIGNE_BASE);
            Serial.println("Reste au centre");
            if(g_debutCentre == 0){
                g_debutCentre = millis();
                g_dureeCentre = 0;
            }else{
                g_dureeCentre = millis() - g_debutCentre;
            }
            break;
        default:
            avancer(VITESSE_LIGNE_BASE, VITESSE_LIGNE_BASE);
            Serial.println("wtf");
            break;
        }
    }
    
}

#endif // DEPART_H
