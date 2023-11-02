// Ce fichier contient tous les types globaux utilises dans le code

#ifndef TYPES_H
#define TYPES_H

/****************************************/
/**** ENUMS ****/
/****************************************/

// Les etats possibles que le robot peut avoir, sont obligatoirement sequentiels (un apres l'autre)
// N'oubliez pas de modifier les nombres si vous ajoutez des etats
enum Etat {
  DEPART,
  SUIVRE_MUR_JUSQUA_POUTRE,
  FAIRE_TOMBER_VERRE,
  SUIVRE_LIGNE,
  METTRE_VERRE_SUR_BALLE,
  RETOURNER_SUR_PARCOURS,
  TRAVERSER_JUMP,
  TOUR_AVEC_RACCOURCI,
  ARRIVE
};

// Les couleurs de la piste
enum Couleur {
  AUCUNE_COULEUR = 0,
  BLEU = 1,
  VERT = 2,
  JAUNE = 3,
  ROUGE = 4,
  BLANC = 5
};

enum EtatSuiveurLigne {
  AUCUNE_LIGNE = 0,
  LIGNE_DROITE = 1,
  LIGNE_GAUCHE = 2,
  LIGNE_CENTRE = 3,
};

#endif // TYPES_H
