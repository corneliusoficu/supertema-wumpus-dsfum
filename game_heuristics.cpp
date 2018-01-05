#include "inc/game_heuristics.h"

void next_suitable_position(char *matrix, uint16_t curr_position, int16_t *next_available_positions)
{
    next_available_positions[0] = curr_position;

    uint8_t pos_available = 1;
    
    if(curr_position + 1 % NR_COLS < NR_COLS - 1)                   //EAST
    {
        if(get_value_at_cell(matrix, curr_position + 1) == 0)
        {
            next_available_positions[pos_available++] = curr_position + 1;
        }
        else
        {
            next_available_positions[pos_available++] = -1;
        }
    }
    if(curr_position % NR_COLS > 0 )                                //WEST
    {
        if(get_value_at_cell(matrix, curr_position - 1) == 0)
        {
            next_available_positions[pos_available++] = curr_position - 1;
        }
        else
        {
            next_available_positions[pos_available++] = -1;
        }
    }
    if(curr_position - NR_COLS >= 0)                                //NORTH
    {
        if(get_value_at_cell(matrix, curr_position - NR_COLS) == 0)
        {
            next_available_positions[pos_available++] = curr_position - NR_COLS;
        }
        else
        {
            next_available_positions[pos_available++] = -1;
        }
    }
    if(curr_position / NR_COLS < NR_ROWS - 2)                        //SOUTH
    {
        if(get_value_at_cell(matrix, curr_position + NR_COLS) == 0)
        {
            next_available_positions[pos_available++] = curr_position + NR_COLS;
        }
        else
        {
            next_available_positions[pos_available++] = -1;
        }
    }
}

