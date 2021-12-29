#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>

#include "../headers/entity_type.h"
#include "../headers/enemy.h"
#include "../headers/cli.h"
#include "../headers/game_master.h"


int main() {


    // test fichier niveau //
    //printf("\n[#########] ---------- Lectures d'un niveau ---------- [#########]\n");
    int money = 0;
    char * nom_fichier = "./data/level1";
    Enemy * waiting_enemies = lire_fichier_niveau(nom_fichier, &money);

    //printf("\n[#########] ---------- Configuration des ennemis ---------- [#########]\n");
    // test lecture type enemy //
    nom_fichier = "./data/enemy_types";
    //printf("\n lecture fichier types ennemis \n");
    DListe types = lire_fichier_types(nom_fichier);

    // association des effets aux types
    nom_fichier = "./data/effects_by_enemy_types";
    lire_fichier_effets(nom_fichier, types);

    // association des caractéristiques des ennemis par type //
    //printf("\n initialisation des ennemis d'après leur type\n");
    init_enemies(waiting_enemies, types);

    //printf("\n[#########] ---------- Configuration des tourelles ---------- [#########]\n");
    // test lecture type tower //
    nom_fichier = "./data/tower_types";
    //printf("\n Lecture fichier des types de tourelles: \n");
    DListe t_types = lire_fichier_types(nom_fichier);

    // association des effets aux types
    nom_fichier = "./data/effects_by_tower_types";
    //printf("\n association des effets aux type de tourelles: \n");
    lire_fichier_effets(nom_fichier, t_types);

    //printf("\n[#########] ---------- Lancement du jeu ---------- [#########]\n");
    // Game
    // à déclarer dans play() dans game_master.c
    Game game = {NULL, NULL, 0, money};
    // ça râle si on ne crée pas de fenêtre alors qu'on importe libMLV (voir: valgrind ./main


    //printf("AJOUT TOURELLE: \n");
    Tower * towers = NULL;
    Tower * t1 = alloue_tower('A', 0, 2, 1, 0);
    tower_add(&towers,t1);
    game_add_entity(&game, &towers, TOWER);
    gm_add_entities(&game, &towers, TOWER);

    // affichage du jeu
    /*  @todo créer une classe game_state pour le tour, les points, les stats, etc...  */

    LEVEL_MENU_ACTION act = 0;
    DListe tmp = NULL;
    char tmp2[2] = {0};
    //CLI_display_title();printf("\n");
    CLI_clear_screen();
    while((act = CLI_scan_choice_level_menu())!= START_LEVEL){
        CLI_clear_screen();
        switch (act) {
            case SHOW_WAVE:
                CLI_show_wave(waiting_enemies);
                break;
            case BUILD_DEFENSE:
                break;
            case ENEMIES_INFO:
                if(!(tmp = CLI_scan_choice_entity_types_menu(&types))) break;
                CLI_clear_screen();
                CLI_entity_type_display_full(*((Entity_type *) tmp->element), ENEMY);
                break;
            case TOWERS_INFO:
                if(!(tmp = CLI_scan_choice_entity_types_menu(&t_types))) break;
                CLI_clear_screen();
                CLI_entity_type_display_full(*((Entity_type *) tmp->element), TOWER);
                break;
            default:
                break;
        }
        act = 0;
        printf("\n\nContinue (y): ");
        tmp2[0] = 0;
        while(scanf(" %1s", tmp2) != 1 || *tmp2 != 'y');
        printf("\n");
        CLI_clear_screen();
    }

    // jouer le niveau
    clock_t t_1 = clock();
    clock_t t_2;
    Enemy * dead_e = NULL;
    while(game.turn < MAX_LINE_LENGTH) {
            // Si on se renseigne sur time.h (par ex: https://fr.wikipedia.org/wiki/Time.h
            // on apprend l'existence de clock_t CLOCKS_PER_SEC (nombre de tick d'horloge par seconde).
            // (ce qu'on préfère, car time_t donné par time(NULL) est trop grand (seconde))
            // Comme nous souhaitons avoir des millisecondes on multiplie par 1000,
            // puis par 500 pour la latence souhaitée
            // Mince, en fait non. Impossible d'obtenir une précision inférieure à la seconde
            // alternative : utiliser POSIX (clock_gettime())
            t_2 = clock();
            if(((unsigned int)(t_2 - t_1) % CLOCKS_PER_SEC) == 0){
                // retirer les ennemis à court de vies
                enemy_add(&dead_e,gm_remove_dead_enemies(&game));

                game.turn += 1;
                // ajouter les ennemis du tour courant (mais d'abord ceux ayants un ou des tours de retard)
                gm_add_entities(&game, &waiting_enemies, ENEMY);
                CLI_clear_screen();
                CLI_display_game(game);printf("\n");
                // on fait jouer les tourelles
                gm_entity_play_effects(game, game.towers, TOWER, t_types);
                // on fait jouer les ennemis
                // --
                // déplacement des ennemis
                gm_move_all(&game);
                // vérifier si la partie est finie, savoir qui a gagné n'est pas important ici
                gm_is_game_over(game);
            }

    }

    // fin de partie
    if(gm_ennemis_won(game)){
        printf("Vous avez perdu !\n");
    }else if(gm_player_won(game)){
        printf("Vous avez gagné !\n");
    }else{
        printf("Qui à gagné Q_Q ?\n");
    }
    // détail de la partie
    printf("\n[Récapitulatif de la vague]\n"
           "Nombre d'ennemis tués: %d\n"
    , enemy_count(dead_e));

    // free //
    printf("\n");
    enemy_free_all(&dead_e);
    enemy_free_all(&waiting_enemies);
    enemy_free_all(&game.enemies);
    tower_free_all(&game.towers);
    entity_type_dliste_free(&types);
    entity_type_dliste_free(&t_types);
    printf("\n");
    return 0;
}
//enemy->prev_line = enemy->next_line = NULL;