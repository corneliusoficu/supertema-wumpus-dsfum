#include "inc/game_heuristics.h"

uint16_t wumpus_unvisited = WUMPUS_MAXIMUM_UNVISITED_CELLS;
uint16_t wumpus_stack[WUMPUS_MAXIMUM_UNVISITED_CELLS];
char     wumpus_visited_array [(NR_ROWS * NR_COLS) / 8];
uint16_t *wumpus_sp;

void next_suitable_positions(char *matrix, int16_t curr_position, int16_t *next_available_positions)
{   
    
    uint8_t index = 0; //random(0,5);

    next_available_positions[ index ] = curr_position;

    if((curr_position + 1) % NR_COLS < NR_COLS - 1 &&
       get_value_at_cell(matrix, curr_position + 1) == 0)                   //EAST
    {
        next_available_positions[(index + 1) % 5] = curr_position + 1;
    }
    else
    {
        next_available_positions[(index + 1) % 5] = -1;
    }

    if(curr_position % NR_COLS > 0 &&                              //WEST
       get_value_at_cell(matrix, curr_position - 1) == 0)
    {

        next_available_positions[(index + 2) % 5] = curr_position - 1;
    }
    else
    {
        next_available_positions[(index + 2) % 5] = -1;
    }

    if(curr_position - NR_COLS >= 0 &&                             //NORTH
       get_value_at_cell(matrix, curr_position - NR_COLS) == 0)
    {
        next_available_positions[(index + 3) % 5] = curr_position - NR_COLS;
    }
    else
    {
        next_available_positions[(index + 3) % 5] = -1;
    }

    if(curr_position / NR_COLS < NR_ROWS - 2 &&                        //SOUTH
       get_value_at_cell(matrix, curr_position + NR_COLS) == 0)
    {
        next_available_positions[(index + 4) % 5] = curr_position + NR_COLS;
    }
    else
    {
        next_available_positions[(index + 4) % 5] = -1;
    }
    
}

void DFS_iterate(char *matrix, uint16_t *current_move)
{
    if(wumpus_unvisited == WUMPUS_MAXIMUM_UNVISITED_CELLS || wumpus_unvisited == 0)
    {
        memset(wumpus_visited_array, 0, (NR_ROWS * NR_COLS) / 8);   
        wumpus_sp = wumpus_stack;

        if(wumpus_unvisited == 0)
        {
            wumpus_unvisited = WUMPUS_MAXIMUM_UNVISITED_CELLS;
        }

        set_value_at_cell(wumpus_visited_array, *current_move, 1);
        wumpus_unvisited--;
    }
    
    int16_t wumpus_neighbours[5];

    next_suitable_positions(matrix, *current_move, wumpus_neighbours);

    // Serial.println(*current_move);
    // print_array(wumpus_neighbours, 5);

    if(checkVisited(wumpus_visited_array, wumpus_neighbours, 5))
    {
        set_value_at_cell(wumpus_visited_array, wumpus_neighbours[0], 1);

        *current_move = wumpus_neighbours[0];
        uint16_t val  = *current_move;
        *wumpus_sp    = val;

        ++wumpus_sp;
        --wumpus_unvisited;
    }
    else
    {
        // Serial.println(F("Backtracking!"));
        --wumpus_sp;
        *current_move = *wumpus_sp;
        *wumpus_sp = 0x00;
    }
}

void move_player(char *matrix, uint16_t *current_move, uint8_t player_index)
{
    if(player_index == POS_WUMPUS)
    {
        DFS_iterate(matrix, current_move);
    }
}

