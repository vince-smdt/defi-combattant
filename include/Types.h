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
  SUIVRE_LIGNE = 1,
  PARTIE_GRISE = 2,
  SUIVRE_LIGNE_JUSQUA_POUTRE = 3,
  FAIRE_TOMBER_VERRE = 4,
  SUIVRE_LIGNE_JUSQUA_PARTIE_BLANCHE = 5,
  METTRE_VERRE_SUR_BALLE = 6,
  RETOURNER_SUR_PARCOURS = 7,
  TRAVERSER_JUMP = 8,
  SUIVRE_LIGNE_SHORTCUT = 9,
  PARTIE_GRISE_SHORTCUT = 10,
  ALLER_AU_SHORTCUT = 11,
  PRENDRE_LE_SHORTCUT = 12,
  TRAVERSER_JUMP_APRES_SHORTCUT = 13,
  ARRIVE = 14
};

#endif // TYPES_H
