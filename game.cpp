#include "inc/game.h"

int8_t winner      = -1;
uint8_t wumpus_left = ITEMS - 2;
uint8_t in_game[ITEMS - 2] = {1, 1, 1, 1};
extern uint8_t  scores[ITEMS - 1];

void create_new_instance(char *matrix, uint16_t *points)
{
    generate_matrix(matrix);
    generate_maze(matrix);

    find_accesible_points(matrix, points, ITEMS);

    store_matrix(MATRIX_ADRESS, matrix, (NR_ROWS * NR_COLS) / 8);
    store_positions(POSITIONS_ADDRESS, points, ITEMS);

    const char empty_scores[] = {0, 0, 0, 0, 0};
    store_matrix(SCOREBOARD_ADRESS, (char*)empty_scores, 5);

    store_matrix(WUMPUS_LEFT_ADDRESS, (char*)&wumpus_left, 1);
    store_matrix(IN_GAME_ADDRESS, (char*)in_game, ITEMS - 2);

}

void initialize_game(char **matrix, uint16_t **points)
{
    if(*matrix == NULL && *points == NULL)
    {   
        uint8_t size_matrix = (NR_ROWS * NR_COLS) / 8;
        *matrix = (char*)     malloc(size_matrix * sizeof(char));
        *points = (uint16_t*) malloc(ITEMS * sizeof(uint16_t));

        if(!is_differentiation_byte_in_eeprom())
        {
            Serial.println("No configuration found in eeprom, creating a new one!");

            write_differentiaion_byte_in_eeprom();

            create_new_instance(*matrix, *points);
            
        }
        else
        {
            Serial.println("Found cofiguration in eeprom...");
            read_matrix   (MATRIX_ADRESS, *matrix, (NR_ROWS * NR_COLS) / 8);
            read_positions(POSITIONS_ADDRESS, *points, ITEMS);

            read_matrix(SCOREBOARD_ADRESS, (char*)scores, ITEMS - 1);
            read_matrix(WUMPUS_LEFT_ADDRESS, (char*)&wumpus_left, 1);
            read_matrix(IN_GAME_ADDRESS, (char*)in_game, ITEMS - 2);

            print_int_array(*points, ITEMS);

            Serial.println(wumpus_left);
            print_array(in_game, ITEMS - 2);

        }
    }
    else
    {
        create_new_instance(*matrix, *points);
    }
}

void find_accesible_points(char *matrix, uint16_t *positions, uint8_t nr_positions)
{
    uint8_t  count = 0;
    uint16_t random_point;

    while(count < nr_positions)
    {
        random_point = random(64, 1406);
        uint8_t value = get_value_at_cell(matrix, random_point);
        if(value == 0)
        {
            if(count == 0)
            {
                positions[count++] = random_point;
            }
            else
            {
                for(uint8_t index = 0; index < count; index++)
                {
                    if(random_point != positions[index])
                    {
                        positions[count++] = random_point;
                        break;
                    }
                }
            }
        }
    }
}

void find_new_player_positions(char *matrix, uint16_t *positions, uint8_t nr_players)
{
    for(int index = 0; index < nr_players; index++)
    {
        if(index == POS_WUMPUS)
        {
            if(wumpus_left == 0)
            {
                winner = POS_WUMPUS;
            }
            else
            {
                dummy_iterate(matrix, positions + index, index, 0);
            }
            
        }
        else
        {
            if(in_game[index])
            {
                
                if(positions[index] == positions[POS_WUMPUS])
                {
                    in_game[index] = 0;
                    wumpus_left--;
                }

                if(positions[index] == positions[ITEMS - 1])
                {
                    winner = index;
                }
                else
                {
                    dummy_iterate(matrix, positions + index, index, *(positions + POS_WUMPUS));
                }   
            } 
        }
    }
}







