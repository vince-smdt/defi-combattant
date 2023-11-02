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
void suivreLigneJank();


/****************************************/
/**** FONCTIONS (DEFINITIONS) ****/
/****************************************/

EtatSuiveurLigne obtenirEtatLigne(){
    int valeurSenseur = analogRead(A5);
    if(valeurSenseur > 400 && valeurSenseur < 500){
        return LIGNE_GAUCHE;
    } 
    if (valeurSenseur > 800 && valeurSenseur < 900){
        return LIGNE_DROITE;
    }
    if (valeurSenseur > 650 && valeurSenseur < 750){
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
            avancer(VITESSE_LIGNE_TOURNE_BASE + VITESSE_DIFF_TOURNER, -1*(VITESSE_LIGNE_TOURNE_BASE - VITESSE_DIFF_TOURNER));
            Serial.println("Tourne à droite");
            g_debutCentre = 0;
            g_derniereManoeuvre = etatCourant;
            break;
        case LIGNE_GAUCHE:
            avancer(-1*(VITESSE_LIGNE_TOURNE_BASE - VITESSE_DIFF_TOURNER), VITESSE_LIGNE_TOURNE_BASE + VITESSE_DIFF_TOURNER);
            Serial.println("Tourne à gauche");
            g_debutCentre = 0;
            g_derniereManoeuvre = etatCourant;
            break;
        case LIGNE_CENTRE:
            avancer(VITESSE_LIGNE_TOURNE_BASE, VITESSE_LIGNE_TOURNE_BASE);
            Serial.println("Reste au centre");
            if(g_debutCentre == 0){
                g_debutCentre = millis();
                g_dureeCentre = 0;
            }else{
                g_dureeCentre = millis() - g_debutCentre;
            }
            break;
        default:
            avancer(VITESSE_LIGNE_TOURNE_BASE, VITESSE_LIGNE_TOURNE_BASE);
            Serial.println("wtf");
            break;
        }
    }
    
}

// Fuck la balle
void suivreLigneJank() {
    if (g_couleurDebut == JAUNE) {
        avancerDuree(0.2, 0, 500);
        avancerDuree(0.4, 0.335, 9500);
    }
    else
        avancerDuree(0.4, 0.3, 7500);

    arret();
    beep(5, 100);
}

#endif // DEPART_H
