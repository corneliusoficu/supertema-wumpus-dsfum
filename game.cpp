#include "inc/game.h"

// void print_initial_game_information()
// {
//     Serial.print(F("Player1 : ")); Serial.println(symbols[POS_P1]);
//     Serial.print(F("Player2 : ")); Serial.println(symbols[POS_P2]);
//     Serial.print(F("Player3 : ")); Serial.println(symbols[POS_P3]);
//     Serial.print(F("Player4 : ")); Serial.println(symbols[POS_P4]);
//     Serial.print(F("Wumpus  : ")); Serial.println(symbols[POS_WUMPUS]);
//     Serial.print(F("Treasure: ")); Serial.println(symbols[POS_TREASURE]);
// }

void initialize_game(char **matrix, uint16_t **points)
{
    uint8_t size_matrix = (NR_ROWS * NR_COLS) / 8;
    *matrix = (char*)     malloc(size_matrix * sizeof(char));
    *points = (uint16_t*) malloc(ITEMS * sizeof(uint16_t));

    generate_matrix(*matrix);
    generate_maze(*matrix);

    find_accesible_points(*matrix, *points, ITEMS);

    // print_initial_game_information();
    print_matrix_with_positions(*matrix, *points, symbols, ITEMS);

    //delay_countdown(3);

    // print_matrix(*matrix, 1);
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
            positions[count++] = random_point;
        }
    }

}

void find_new_player_positions(char *matrix, uint16_t *positions, uint8_t nr_players)
{
    for(int index = 0; index < nr_players; index++)
    {
        if(index == POS_WUMPUS)
        {
            dummy_iterate(matrix, positions + index, index, 0);
        }
        else
        {
            dummy_iterate(matrix, positions + index, index, *(positions + POS_WUMPUS));
        }
        
    }
}






