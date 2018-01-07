#include "inc/printers.h"

void print_matrix(char *matrix, uint8_t show_binary)
{
    char *c;
    char wall = WALL_CHAR;
    for(uint8_t row = 0; row < NR_ROWS; row++)
    {
        for(uint8_t col = 0; col < NR_COLS / 8; col++)
        {
            if(PAD_FIRST_COL && col == 0)
            {
                Serial.print(wall);
            }
            c = matrix + ((NR_COLS / 8) * row + col);
            
            for(uint8_t bit = 0; bit < 8; bit++)
            {
                uint8_t bit_value =  (*c & (1 << (7 - bit))) != 0;

                if(show_binary == 0)
                {
                    (bit_value == 1)? Serial.print(wall): Serial.print(" ");
                }
                else
                {
                    Serial.print(bit_value);
                }
            }
        }

        Serial.println();
    }
}

//TODO: Remove Duplicated code, maybe with callbacks.
void print_matrix_with_positions(char *matrix, uint16_t *positions, char symbols[][24], uint8_t size, const char messages[][20], uint8_t nr_messages)
{
    char *c;
    char wall = WALL_CHAR;
    for(uint8_t row = 0; row < NR_ROWS; row++)
    {
        for(uint8_t col = 0; col < NR_COLS / 8; col++)
        {
            if(PAD_FIRST_COL && col == 0)
            {
                Serial.print(wall);
            }
            uint8_t current_byte_index = ((NR_COLS / 8) * row + col);
            c = matrix + current_byte_index;
            for(uint8_t bit = 0; bit < 8; bit++)
            {
                uint8_t bit_value =  (*c & (1 << (7 - bit))) != 0;

                if(bit_value == 1)
                {
                    Serial.print(wall);
                }
                else
                {
                    uint16_t current_index = ( current_byte_index * 8 ) + bit;

                    uint8_t index = 0;
                    uint8_t is_player = 0;
                    while(index < size && !is_player)
                    {
                        if(positions[index] == current_index)
                        {
                            Serial.print(symbols[index]);
                            is_player = 1;
                        }
                        else
                        {
                            index++;
                        }
                    }
                    if(is_player == 0)
                    {
                        Serial.print(' ');
                    }
                }
                
                
            }
        }
        if(messages != NULL)
        {
            if(row < nr_messages)
            {
                Serial.print(messages[row]);
            }
            
        }

        Serial.println();
    }
}