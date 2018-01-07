#ifndef GAME_H
#define GAME_H

#define START_GAME_DELAY 3

#include "game_heuristics.h"
#include "memory_handler.h"

#define NR_ITERATIONS_SAVE_GUARD 200
#define MATRIX_ADRESS           0x01
#define POSITIONS_ADDRESS       0xC8
#define SCOREBOARD_ADRESS      0x190
#define WUMPUS_LEFT_ADDRESS    0x258
#define IN_GAME_ADDRESS        0x320
     
char    symbols[][24]    = {"♠", "♥", "♦", "♣", "Ö", "★"};
uint8_t iterations = 0;

void    initialize_game               (char **matrix, uint16_t **points);
void    find_accesible_points         (char *matrix, uint16_t *positions, uint8_t count);
uint8_t play_game                     (char *matrix, uint16_t *positions, uint8_t players);
void    update_messages               (char messages[][20], uint8_t &len_messages);

#endif