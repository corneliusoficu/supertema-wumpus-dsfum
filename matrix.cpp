#include "inc/matrix.h"

void generate_matrix(char *matrix)
{
    freeRam();
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

uint8_t get_value_at(char *matrix, uint8_t x, uint8_t y)
{
    //print_matrix(matrix);
    char *c = (matrix + (y * (NR_COLS / 8)));
    Serial.println((uint8_t)*c);
    return 0;
}

int16_t* find_neighbours(int16_t cell)
{
    int16_t *neighbours = (int16_t*) malloc(4 * sizeof(int16_t));
    uint8_t index = 0;

    neighbours[    index    ] = ((cell - (2 * NR_COLS)) <= 0)? (-1) : (cell - 2 * NR_COLS);   //NORTH
    neighbours[(index+1) % 4] = (cell % NR_COLS == NR_COLS - 1)? (-1) : (cell + 2);           //EAST
    neighbours[(index+2) % 4] = (cell / NR_COLS == NR_ROWS - 2)? (-1) : (cell + 2 * NR_COLS); //SOUTH
    neighbours[(index+3) % 4] = (cell % NR_COLS != 1)? (cell - 2) : (-1);                     //WEST

    return neighbours;

}

void change_cell_in_bit_array(char *bit_array, uint16_t cell, uint8_t value)
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

void generate_maze(char *matrix)
{
    uint16_t unvisited_cells = (NR_ROWS / 2) * (NR_COLS / 2);

    uint16_t stack [unvisited_cells];
    char visited   [(NR_ROWS * NR_COLS) / 8];
    memset(visited, 0, (NR_ROWS * NR_COLS) / 8);

    uint16_t *sp = stack;

    uint8_t start_cell = 65;
    uint16_t current_cell = start_cell;

    change_cell_in_bit_array(visited, start_cell, 1);

    //freeRam();

    // while(unvisited_cells)
    // {
            int16_t *neighbours = find_neighbours(current_cell);

    // }


    //freeRam();



    

}

void print_matrix(char *matrix)
{
    char *c;
    for(uint8_t row = 0; row < NR_ROWS; row++)
    {
        for(uint8_t col = 0; col < NR_COLS / 8; col++)
        {
            c = matrix + ((NR_COLS / 8) * row + col);
            
            for(uint8_t bit = 0; bit < 8; bit++)
            {
                uint8_t bit_value =  (*c & (1 << (7 - bit))) != 0;
                if(bit_value == 1)
                {
                    Serial.print("#");
                }
                else if(bit_value == 0)
                {
                    Serial.print("_");
                }
            }
        }
        Serial.println();
    }
}