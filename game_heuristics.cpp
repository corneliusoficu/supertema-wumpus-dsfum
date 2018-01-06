#include "inc/game_heuristics.h"

uint16_t wumpus_unvisited = WUMPUS_MAXIMUM_UNVISITED_CELLS;
uint16_t wumpus_stack[WUMPUS_MAXIMUM_UNVISITED_CELLS];
char     wumpus_visited_array [(NR_ROWS * NR_COLS) / 8];
uint16_t *wumpus_sp;

uint16_t last_visited_cell[ITEMS - 2]  = {0,0,0,0};

void next_suitable_positions(char *matrix, int16_t curr_position, int16_t *next_available_positions, uint8_t nr_pos)
{   
    
    uint8_t index = random(0, nr_pos);

    if((curr_position + 1) % NR_COLS < NR_COLS - 1 &&
       get_value_at_cell(matrix, curr_position + 1) == 0)                   //EAST
    {
        next_available_positions[index] = curr_position + 1;
    }
    else
    {
        next_available_positions[index] = -1;
    }

    if(curr_position % NR_COLS > 0 &&                              //WEST
       get_value_at_cell(matrix, curr_position - 1) == 0)
    {

        next_available_positions[(index + 1) % nr_pos] = curr_position - 1;
    }
    else
    {
        next_available_positions[(index + 1) % nr_pos] = -1;
    }

    if(curr_position - NR_COLS >= 0 &&                             //NORTH
       get_value_at_cell(matrix, curr_position - NR_COLS) == 0)
    {
        next_available_positions[(index + 2) % nr_pos] = curr_position - NR_COLS;
    }
    else
    {
        next_available_positions[(index + 2) % nr_pos] = -1;
    }

    if(curr_position / NR_COLS < NR_ROWS - 2 &&                        //SOUTH
       get_value_at_cell(matrix, curr_position + NR_COLS) == 0)
    {
        next_available_positions[(index + 3) % nr_pos] = curr_position + NR_COLS;
    }
    else
    {
        next_available_positions[(index + 3) % nr_pos] = -1;
    }

    if(nr_pos == 5)
    {
        next_available_positions[(index + 4) % nr_pos] = curr_position;
    }
    
}

uint16_t get_random_item(int16_t *arr, uint8_t size, uint8_t itm_index, uint16_t current_cell)
{
    int16_t *p = arr;
    int16_t av_items[size];
    uint8_t itm = 0;
    uint8_t is_different = 0;

    while(p < arr + size)
    {
        if(*p != -1)
        {
            av_items[itm++] = *p;
            if(*p != last_visited_cell[itm_index])
            {
                is_different = 1;
            }
        }
        p++;
    }

    // Serial.print(F("Last visited item: "));
    // Serial.println(last_visited_cell[itm_index]);

    // Serial.print(F("Nr found: "));
    // Serial.println(itm);

    // Serial.print(F("Found the following next itms: "));
   
    uint16_t found = 0;
    uint8_t idx = 0;
    while(!found)
    {
        idx = random(0, itm);
        // Serial.print(" Index: ");
        // Serial.println(idx);
        if(is_different == 1)
        {
            if(av_items[idx] != last_visited_cell[itm_index])
            {
                found = 1;
            }
        }
        else
        {
            found = 1;
        }
    }

    // Serial.print(F("Chosen index: "));
    // Serial.println(idx);

    last_visited_cell[itm_index] = current_cell;

    return av_items[idx];
}

void dummy_iterate(char *matrix, uint16_t *current_move, uint8_t curr_index)
{
    int16_t neighbours[4];
    next_suitable_positions(matrix, *current_move, neighbours, 4);
    // print_array(neighbours, 4);
    // Serial.print(F("Current Move: "));
    // Serial.println(*current_move);
    // Serial.print(" -> ");
    *current_move = get_random_item(neighbours, 4, curr_index, *current_move);


    
    // Serial.print(F("Next move: "));
    // Serial.println(*current_move);
    // Serial.println();
    // Serial.println(*current_move);
   

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
    
    int16_t wumpus_neighbours[4];

    next_suitable_positions(matrix, *current_move, wumpus_neighbours, 4);

    // Serial.println(*current_move);
    // print_array(wumpus_neighbours, 5);

    if(checkVisited(wumpus_visited_array, wumpus_neighbours, 4))
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
        if(wumpus_sp == wumpus_stack)
        {
            wumpus_unvisited = 0;
        }
        else
        {
            *current_move = *wumpus_sp;
            *wumpus_sp = 0x00;
        }
        
    }
}



void move_player(char *matrix, uint16_t *current_move, uint8_t player_index)
{
    if(player_index == POS_WUMPUS)
    {
        DFS_iterate(matrix, current_move);
    }
    else
    {
        dummy_iterate(matrix, current_move, player_index);
    }
}

