

#ifndef L2_PROJET_C_ENEMY_H
#define L2_PROJET_C_ENEMY_H

/**
 * Les types d'ennemis.
 * La valeur d'un type
 * est l'indice de la lettre
 * le représentant en ASCII
 */
typedef enum{
    ENEMY_E = (int) 'E',
    ENEMY_D = (int) 'D',
    ENEMY_S = (int) 'S',
    ENEMY_M = (int) 'M',
    ENEMY_B = (int) 'B'
} ENEMY_TYPE;

/**
 * Modélise un ennemi.
 */
typedef struct enemy{
    int type; /**< Le type de l'ennemi*/
    int life;
    int line;
    int position;
    int speed;
    int turn;
    struct enemy* next; /**< l'ennemi courant est apparu avant l'ennemi pointé par *next */
    struct enemy *next_line, *prev_line; /**< les ennemis suivant (droite) et précédent (gauche) sur la ligne */
}Enemy;

/**
 * Alloue un ennemi
 * @param type le type de l'ennemi
 * @param life les points de vie
 * @param line la ligne initiale
 * @param speed sa vitesse
 * @param turn le tour d'apparition
 * @return un pointeur sur un ennemi
 */
Enemy * alloue_enemy(int type, int life, int line, int speed, int turn);

/**
 * Lie l'ennemi à un suivant sur la ligne (à la fin de la liste)
 * @param to_e La ligne d'ennemis
 * @param from_e l'ennemi à lier
 * @return 0 si l'ennemi à ajouté n'est pas sur la même ligne
 */
int enemy_add_next_line(Enemy** to_e, Enemy * from_e);

/**
 * Ajoute un ennemi en fin d'une liste d'ennemis (next)
 * (fin de liste)
 * @param to_e tête de liste
 * @param from_e l'ennemi à ajouter
 * @return 0 ou 1
 */
int enemy_add_next(Enemy** to_e, Enemy* from_e);

/**
 * Extrait un ennemi de sa ligne
 * @param e_from adresse de la ligne d'ennemi depuis laquelle retirer l'ennemi
 * @param enemy adresse de l'ennemi à retirer
 * @return l'ennemi s'il se trouvait dans la ligne, NULL sinon
 */
Enemy* enemy_extract_from_line(Enemy** e_from, Enemy * enemy);

/**
 * Extrait un ennemi d'une liste (next)
 * @param e_from adresse de la ligne d'ennemi depuis laquelle retirer l'ennemi
 * @param enemy adresse de l'ennemi à retirer
 * @return l'adresse de l'ennemi s'il se trouvait dans la ligne, NULL sinon
 * @param e_from
 * @param enemy
 * @return
 */
Enemy * enemy_extract_from_next(Enemy** e_from, Enemy * enemy);


Enemy * enemy_extract_from_all(Enemy** e_from, Enemy * enemy);


/*
void enemy_delete_from_line(Enemy** enemy);
*/

/**
 * Remplit les caractéristiques de l'ennemi
 * en fonction de son type
 * @param enemy un pointeur sur ennemi
 * @param e_type le type de l'ennemi
 * @return 0 si une initialisation n'a pas pu être réalisée
 */
int init_enemy(Enemy * enemy, Enemy * type_list);

/**
 *
 * Renvoie l'adresse du premier ennemi d'un type donné
 *  (next)
 * @param enemy
 * @param e_type
 * @return
 */
Enemy * find_first_type_next(Enemy * enemy, ENEMY_TYPE e_type);


void enemy_delete_line(Enemy** enemy);

void enemy_delete_next(Enemy** enemy);

void enemy_delete_all(Enemy** enemy);

#endif //L2_PROJET_C_ENEMY_H
