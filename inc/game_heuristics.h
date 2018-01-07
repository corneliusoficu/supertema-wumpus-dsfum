#ifndef GAMEHEURISTICS_H
#define GAMEHEURISTICS_H

#define POS_WUMPUS                       4
#define POS_TREASURE                     5

#define ITEMS                            6

#define WUMPUS_MAXIMUM_UNVISITED_CELLS 100 

#include <QueueList.h>
#include "matrix.h"

void dummy_iterate(char *matrix, uint16_t *current_move, uint8_t curr_index, uint16_t wumpus_pos);
uint16_t get_distance_between_maze_points(char *matrix, uint16_t src_cell, uint16_t dest_cell);

#endif