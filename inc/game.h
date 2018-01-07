#ifndef GAME_H
#define GAME_H

#define START_GAME_DELAY 3

#include "game_heuristics.h"

char symbols[][24]    = {"♠", "♥", "♦", "♣", "Ö", "★"};

// void    print_initial_game_information();
void    initialize_game               (char **matrix, uint16_t **points);
void    find_accesible_points         (char *matrix, uint16_t *positions, uint8_t count);
uint8_t play_game                     (char *matrix, uint16_t *positions, uint8_t players);
void    update_messages               (char messages[][20], uint8_t &len_messages);

#endif