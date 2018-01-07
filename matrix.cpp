#include "inc/matrix.h"

uint16_t total_accesible_points;

void generate_matrix(char *matrix)
{
    //freeRam();
    char *c;
    for(uint8_t col = 0; col < NR_COLS / 8; col++)
    {
        for(uint8_t row = 0; row < NR_ROWS; row++)
        {
            uint8_t index = ((NR_COLS / 8) * row + col);
            c = matrix + index;
            if(row % 2)
            {
                for(uint8_t bit = 0; bit < 8; bit++)
                {
                    if(bit % 2)
                    {
                        *c |= 1 << (7 - bit);
                    }
                    else
                    {
                        *c &= ~(1 << (7 - bit));
                    }
                }
            }
            else
            {
                *c = 255;
            }
        }
    }
}

void find_neighbours(int16_t *neighbours, int16_t cell)
{
    uint8_t index = random(0,4);
    // uint8_t index = 0;
    //Serial.println(index);
    neighbours[    index    ] = ((cell - (2 * NR_COLS)) <= 0)? (-1) : (cell - 2 * NR_COLS);   //NORTH
    neighbours[(index+1) % 4] = (cell % NR_COLS == NR_COLS - 2)? (-1) : (cell + 2);           //EAST
    neighbours[(index+2) % 4] = (cell / NR_COLS == NR_ROWS - 2)? (-1) : (cell + 2 * NR_COLS); //SOUTH
    neighbours[(index+3) % 4] = (cell % NR_COLS > 1)? (cell - 2) : (-1);                      //WEST  
}

uint8_t get_value_at_cell(char *arr, uint16_t cell)
{
    uint8_t byte_val = cell / 8;
    uint8_t bit_val  = cell % 8;

    char *c = arr + byte_val;
    uint8_t bit_value =  (*c & (1 << (7 - bit_val))) != 0;
    return bit_value;
}

void set_value_at_cell(char *bit_array, uint16_t cell, uint8_t value)
{
    uint8_t byte_val = cell / 8;
    uint8_t bit_val  = cell % 8;

    char *c = bit_array + byte_val;
    if(value == 1)
    {
        *c |= 1 << (7 - bit_val);
    }
    else if(value == 0)
    {
        *c &= ~(1 << (7 - bit_val));
    }
}

uint8_t checkVisited(char *visited, int16_t *neighbours, uint16_t size)
{
    int16_t *ptr = neighbours;
    while(ptr < neighbours + size)
    {
        if((*ptr != -1) && get_value_at_cell(visited, *ptr) == 0)
        {
            if(ptr != neighbours)
            {
                neighbours[0] = *ptr;
            }
            return 1;
        }
        ++ptr;
    }
    return 0;
}

void clear_wall(char *matrix, uint16_t current_cell, int16_t destination_cell)
{
    int16_t direction = destination_cell - current_cell;
    uint16_t wall_cell;

    if((direction + (2 * NR_COLS)) == 0)      //NORTH
    {
        wall_cell = destination_cell + NR_COLS;
    }
    else if((direction - (2 * NR_COLS)) == 0) //SOUTH
    {
        wall_cell = destination_cell - NR_COLS;
    }
    else if((direction + 2) == 0)             //WEST
    {
        wall_cell = destination_cell + 1;
    }
    else if((direction - 2) == 0)             //EAST
    {
        wall_cell = destination_cell - 1;
    }

    set_value_at_cell(matrix, wall_cell, 0);
}

void generate_maze(char *matrix)
{
    uint16_t unvisited_cells = (NR_ROWS / 2) * (NR_COLS / 2);

    total_accesible_points += unvisited_cells;

    uint16_t stack[unvisited_cells];
    int16_t neighbours[4];
    char visited   [(NR_ROWS * NR_COLS) / 8];

    memset(visited, 0, (NR_ROWS * NR_COLS) / 8);

    uint16_t *sp = stack;

    uint16_t current_cell = START_CELL;
    set_value_at_cell(visited, current_cell, 1);
    unvisited_cells--;

    while(unvisited_cells)
    {  
            find_neighbours(neighbours, current_cell);
            if(checkVisited(visited, neighbours, 4))
            {
                clear_wall(matrix, current_cell, neighbours[0]);
                total_accesible_points += 1;
                
                current_cell = neighbours[0];
                set_value_at_cell(visited, current_cell, 1);

                *sp = current_cell;
                ++sp;

                --unvisited_cells;
            }
            else
            {
                --sp;
                current_cell = *sp;
                *sp = 0x00;
            }
    }
}
