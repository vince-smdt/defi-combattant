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
  // SERVO_Enable(0);
  // SERVO_SetAngle(0, 90);
  // delay(500);
  // while(true){
  //   if (IR_to_cm(IR_GAUCHE)< 15){
  //     SERVO_SetAngle(0, 0);
  //     delay(500);
  //     RetouneEtatInitial();
  //   }
  //   if (IR_to_cm(IR_DROIT)< 15){
  //     SERVO_SetAngle(0, 180);
  //     delay(500);
  //     RetouneEtatInitial();
  //   }
  // }


//   while (true) {
//     // Serial.println(detecterCouleur());
//     detecterCouleur();

//     Serial.print("[");
//     for (int i = 0; i < NB_DERNIERES_COULEURS; i++) {
//       Serial.print(g_dernieresCouleurs[i]);
//       Serial.print(", ");
//     }
//     Serial.print("] = ");
//     Serial.println(couleurMoyenne());
//   }

  // Ce switch va determiner ce que le robot doit faire dependemment de son etat actuel
   switch (SUIVRE_LIGNE) {
    case DEPART: { depart(); break; }
    case SUIVRE_MUR_JUSQUA_POUTRE: { suivreMurDuree(8000, 35, 40); break; }
    case FAIRE_TOMBER_VERRE: { verre(); break; }
    case SUIVRE_LIGNE: { /*suivreLigne();*/  break; }
    case METTRE_VERRE_SUR_BALLE: { pousserleverre(); break;}
    case RETOURNER_SUR_PARCOURS: { /* Mettre la fonction de sa partie ici */ break; }
    case TRAVERSER_JUMP: { /* Mettre la fonction de sa partie ici */ break; }
    case TOUR_AVEC_RACCOURCI: { raccourci(); break; }
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
