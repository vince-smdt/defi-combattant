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
  SUIVRE_LIGNE_JUSQUA_PARTIE_BLANCHE = 2,
  METTRE_VERRE_SUR_BALLE = 3,
  RETOURNER_SUR_PARCOURS = 4,
  TRAVERSER_JUMP = 5,
  TOUR_AVEC_RACCOURCI = 6,
  ARRIVE = 7
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
