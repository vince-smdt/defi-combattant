// Ce fichier contient tous les types globaux utilises dans le code

#ifndef TYPES_H
#define TYPES_H

/****************************************/
/**** ENUMS ****/
/****************************************/

// Les etats possibles que le robot peut avoir, sont obligatoirement sequentiels (un apres l'autre)
// N'oubliez pas de modifier les nombres si vous ajoutez des etats
enum Etat {
  DEPART = 0,
  FAIRE_TOMBER_VERRE = 1,
  SUIVRE_COULEUR_JUSQUA_PARTIE_BLANCHE = 2,
  SUIVRE_LIGNE = 3,
  METTRE_VERRE_SUR_BALLE = 4,
  RETOURNER_SUR_PARCOURS = 5,
  TRAVERSER_JUMP = 6,
  TOUR_AVEC_RACCOURCI = 7,
  ARRIVE = 8
};

// Les couleurs de la piste
enum Couleur {
  AUCUNE = 0,
  BLEU = 1,
  VERT = 2,
  JAUNE = 3,
  ROUGE = 4,
  BLANC = 5
};

#endif // TYPES_H
