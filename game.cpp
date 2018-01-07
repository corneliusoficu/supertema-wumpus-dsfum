#include "inc/game.h"

int8_t winner      = -1;
uint8_t wumpus_left = ITEMS - 2;
uint8_t in_game[ITEMS - 2] = {1, 1, 1, 1};

void initialize_game(char **matrix, uint16_t **points)
{
    if(*matrix == NULL && *points == NULL)
    {   
        uint8_t size_matrix = (NR_ROWS * NR_COLS) / 8;
        *matrix = (char*)     malloc(size_matrix * sizeof(char));
        *points = (uint16_t*) malloc(ITEMS * sizeof(uint16_t));
    }
    
    generate_matrix(*matrix);
    generate_maze(*matrix);

    find_accesible_points(*matrix, *points, ITEMS);

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







