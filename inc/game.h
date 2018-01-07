#ifndef GAME_H
#define GAME_H

#define START_GAME_DELAY 3

#include "game_heuristics.h"
#include "memory_handler.h"

#define NR_ITERATIONS_SAVE_GUARD                              200
#define MATRIX_ADRESS                                        0x01
#define POSITIONS_ADDRESS MATRIX_ADRESS + ((NR_COLS * NR_ROWS)/8)
#define SCOREBOARD_ADRESS           POSITIONS_ADDRESS + 2 * ITEMS
#define WUMPUS_LEFT_ADDRESS         SCOREBOARD_ADRESS + ITEMS - 1
#define IN_GAME_ADDRESS                   WUMPUS_LEFT_ADDRESS + 1
     
char    symbols[][24]    = {"♠", "♥", "♦", "♣", "Ö", "★"};
uint8_t iterations = 0;

// void    print_initial_game_information();
void    initialize_game               (char **matrix, uint16_t **points);
void    find_accesible_points         (char *matrix, uint16_t *positions, uint8_t count);

uint8_t play_game                     (char *matrix, uint16_t *positions, uint8_t players);
void    update_messages               (char messages[][20], uint8_t &len_messages);

#endif