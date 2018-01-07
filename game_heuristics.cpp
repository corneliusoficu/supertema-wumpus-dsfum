#include "inc/game_heuristics.h"


uint16_t last_visited_cell[ITEMS - 1]  = {0,0,0,0,0};

extern uint16_t total_accesible_points;

void next_suitable_positions(char *matrix, int16_t curr_position, int16_t *next_available_positions, uint8_t nr_pos, uint8_t is_random)
{   
    
    uint8_t index;

    if(is_random)
    {
        index = random(0, nr_pos);
    }
    else
    {
        index = 0;
    }

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

    //TODO: Solve for standing
    last_visited_cell[itm_index] = current_cell;

    return av_items[idx];
}

uint16_t get_distance_between_maze_points(char *matrix, uint16_t src_cell, uint16_t dest_cell)
{

    struct Node
    {
        uint16_t distance;
        uint16_t cell;
    };

    QueueList <Node> queue;
    
    char visited[(NR_ROWS * NR_COLS) / 8];
    memset(visited, 0, (NR_ROWS * NR_COLS) / 8);

    Node node = {0, src_cell};
    queue.push(node);

    // freeRam();
    
    while(!queue.isEmpty())
    {
        
        node = queue.pop();

        if(node.cell == dest_cell)
        {
            return node.distance;
        }

        int16_t neighbours[4];
        next_suitable_positions(matrix, node.cell, neighbours, 4, 0);

        for(uint8_t index = 0; index < 4; index++)
        {
            if(neighbours[index] != -1)
            {
                if(!get_value_at_cell(visited, neighbours[index]))
                {
                    set_value_at_cell(visited, neighbours[index], 1);
                    Node new_node = {node.distance + 1, (uint16_t)neighbours[index]};
                    queue.push(new_node);
                }
            }
        }
    }
}

uint16_t get_best_pos_to_escape(char *matrix, int16_t *arr, uint8_t size, uint8_t itm_index, uint16_t current_cell, uint16_t away_cell)
{
    uint8_t max_distance = 0;
    uint16_t max_distance_pos = arr[0];

    int16_t *p = arr;
    while(p < arr + size)
    {
        if(*p != -1)
        {
            uint16_t dst = get_distance_between_maze_points(matrix, (*p), away_cell);

            if(dst > max_distance)
            {
                max_distance = dst;
                max_distance_pos = *(p);
            }
        }
        p++;
    }

    last_visited_cell[itm_index] = current_cell;
    return max_distance_pos;
}

float euclidian_distance(uint16_t src_cell, uint16_t dest_cell)
{
    uint8_t x_src = src_cell % NR_COLS;
    uint8_t y_src = src_cell / NR_COLS;

    uint8_t x_dest = dest_cell % NR_COLS;
    uint8_t y_dest = dest_cell / NR_COLS;

    float distance = sqrt(pow((x_dest - x_src),2) + pow((y_dest - y_src),2));
    return distance;
}

uint8_t is_wumpus_too_close(char *matrix, uint16_t src_cell, uint16_t dest_cell)
{
    uint8_t ret_val = 0;
    if(euclidian_distance(src_cell, dest_cell) > 5 )
    {
        ret_val = 0;
    }
    else
    {
        uint16_t distance = get_distance_between_maze_points(matrix, src_cell, dest_cell);
        if(distance > 10)
        {
            ret_val = 0;
        }
        else
        {   
            ret_val = 1;
        }
    }
    return ret_val;
}

void dummy_iterate(char *matrix, uint16_t *current_move, uint8_t curr_index, uint16_t wumpus_pos)
{
    
    int16_t neighbours[5];

    if(wumpus_pos == 0)
    {
        next_suitable_positions(matrix, *current_move, neighbours, 4, 1);  
        *current_move = get_random_item(neighbours, 4, curr_index, *current_move);
    }
    else if(is_wumpus_too_close(matrix, *current_move, wumpus_pos) == 1)
    {
        next_suitable_positions(matrix, *current_move, neighbours, 5, 1);
        *current_move = get_best_pos_to_escape(matrix, neighbours, 5, curr_index, *current_move, wumpus_pos);
    }
    else
    {
        next_suitable_positions(matrix, *current_move, neighbours, 5, 1);  
        *current_move = get_random_item(neighbours, 5, curr_index, *current_move);
    }
    
}




