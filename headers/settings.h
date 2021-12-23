//
// Created by antoine on 22/12/2021.
//

#ifndef L2_PROJET_C_SETTINGS_H
#define L2_PROJET_C_SETTINGS_H
#include "enemy.h"
#include "stdio.h"

#define MAX_LINE 7 ///< C'est le nombre max de lignes
/**
 * On prétend qu'une ligne à une taille max,
 * car on a un écran fixe et une fonctionnalité
 * qui noue permet de voir le niveau
 * (pour l'instant)
 */
#define MAX_LINE_LENGTH 9

/**
 * Lit un fichier de niveau
 * @param nom_fichier
 * @param money retour du montant d'argent disponible au début du niveau
 * @param enemy_list liste ou sont stockés les ennemis
 * @return le nombre d'ennemis dans le niveau
 */
int lire_fichier_niveau(char * nom_fichier, int * money, Enemy ** enemy_list);

/**
 * Lis le fichier définition des types
 * d'ennemis
 * @param nom_fichier
 * @param enemy_list les ennemis sont stocké comme objet enemy
 * lié via l'attribut "next"
 * @return
 */
int lire_fichier_types_enemy(char * nom_fichier, Enemy ** enemy_list);

#endif //L2_PROJET_C_SETTINGS_H
