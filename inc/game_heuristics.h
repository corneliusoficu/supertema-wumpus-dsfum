#ifndef GAMEHEURISTICS_H
#define GAMEHEURISTICS_H

#define POS_WUMPUS                       4
#define POS_TREASURE                     5

#define WUMPUS_MAXIMUM_UNVISITED_CELLS 100 


#include "matrix.h"

void move_player(char *matrix, uint16_t *current_move, uint8_t index);

#endif