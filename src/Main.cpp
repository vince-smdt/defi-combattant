#include <LibRobus.h>
#include "Globales.h"
#include "Types.h"
#include "General.h"
#include "Depart.h"
#include "Raccourci.h"
#include "Verre.h"
#include "SuivreLigne.h"
#include "Sifflet.h"
#include "Balle.h"
#include "SuivreMur.h"

/****************************************/
/**** SETUP & LOOP ****/
/****************************************/

// Fonction d'initialisation du robot, est execute une seule fois
void setup() {
  BoardInit();
  pinMode(A0, INPUT);
  pinMode(A5, INPUT);
  g_tcs.setInterrupt(false); // Allume la LED du capteur de couleur
}

// Boucle principale du programme, est execute plusieurs fois
void loop() {
  // Ce switch va determiner ce que le robot doit faire dependemment de son etat actuel
  switch (g_etat) {
    case DEPART: { depart(); break; }
    case TOUR_AVEC_RACCOURCI: { raccourci(); break; }
    case SUIVRE_MUR_JUSQUA_POUTRE: { suivreMurCouleur(); break; }
    case FAIRE_TOMBER_VERRE: { verre(); break; }
    case SUIVRE_LIGNE: { suivreLigneJank(); break; }
    case METTRE_VERRE_SUR_BALLE: { arret(); break;}
    case FINIR_TOUR: { 
      avancerDuree(VITESSE_BASE, VITESSE_BASE, 3000);
      if (g_couleurDebut == VERT)
        suivreMurDuree(3000, 33, 38);
      else
        suivreMurDuree(3000, 74.5, 79.5);
      break; 
    }
    case ARRIVE: { g_fini = true; break; }
    default: { g_erreur = true; break; } // Etat invalide, on indique qu'il y a une erreur
  }

  // Si le robot a fini la course, on quitte le programme
  if (g_fini) {
    beep(1, 1000); // Signal d'arrivee
    exit(EXIT_SUCCESS); // Quitte le programme
  }

  // Si une erreur est detectee, le robot beep et on quitte le programme
  if (g_erreur) {
    beep(5, 100); // Signal d'erreur
    exit(EXIT_FAILURE); // Quitte le programme
  }

  // Le robot passe a son prochain etat
  g_etat++;
}
