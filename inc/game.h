#ifndef GAME_H
#define GAME_H

#define ITEMS        6

#define POS_P1       0
#define POS_P2       1
#define POS_P3       2
#define POS_P4       3
#define POS_WUMPUS   4
#define POS_TREASURE 5

#include "matrix.h"

char symbols[][24]    = {"♠", "♥", "♦", "♣", "Ö", "★"};

void initialize_game               (char *matrix, uint16_t *points);
void find_accesible_points         (char *matrix, uint16_t *positions, uint8_t count);
void print_initial_game_information();


#endif