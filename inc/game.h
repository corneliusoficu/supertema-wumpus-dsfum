#ifndef GAME_H
#define GAME_H

#define ITEMS            6

#define POS_P1           0
#define POS_P2           1
#define POS_P3           2
#define POS_P4           3
#define POS_WUMPUS       4
#define POS_TREASURE     5

#define START_GAME_DELAY 3

#include "matrix.h"
#include "game_heuristics.h"

char symbols[][24]    = {"♠", "♥", "♦", "♣", "Ö", "★"};

void    print_initial_game_information();
void    initialize_game               (char **matrix, uint16_t **points, uint16_t &total_available_cells);
void    find_accesible_points         (char *matrix, uint16_t *positions, uint8_t count);
uint8_t play_game                     (char *matrix, uint16_t *positions, uint8_t players);

#endif