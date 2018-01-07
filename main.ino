#include "inc/game.h"

char     *matrix = NULL;
uint16_t *positions = NULL;
char     messages[10][20];
uint8_t  len_messages;
extern uint8_t scores[ITEMS - 1];

void print_initial_status(uint8_t countdown)
{
    char buffer[20];
    len_messages = 1;
    for(uint8_t index = countdown; index >= 1; index--)
    {
        sprintf(buffer, "%s: %d", "Starting in", index);
        strcpy(messages[0], buffer);
        print_matrix_with_positions(matrix, positions, symbols, ITEMS, messages, len_messages);
        delay(1000);
        clear_serial_monitor();
    }
}

void update_messages()
{
    for(uint8_t index = 0; index < ITEMS - 1; index++)
    {
        char buffer[20];
        sprintf(buffer, "%s: %d", symbols[index], scores[index]);
        strcpy(messages[index], buffer);
    }
    len_messages = ITEMS - 1;
}

void setup()
{
    Serial.begin(1000000);
    while(!Serial);
    randomSeed(analogRead(0));
    initialize_game(&matrix, &positions);
    print_initial_status(3);

}

void loop()
{

    find_new_player_positions(matrix, positions, ITEMS - 1);
    if(winner != -1)
    {
        scores[winner]++;
        update_messages();
        char buffer[20];
        sprintf(buffer, "%s has won", symbols[winner]);
        strcpy(messages[len_messages++], buffer);
        print_matrix_with_positions(matrix, positions, symbols, ITEMS, messages, len_messages);
        delay(3000);
        initialize_game(&matrix, &positions);
        print_initial_status(30);

        winner = -1;
        for(uint8_t index = 0; index < ITEMS - 2; index++)
        {
            in_game[index] = 1;
        }

        wumpus_left = ITEMS - 2;
    }
    else
    {
        update_messages();
        print_matrix_with_positions(matrix, positions, symbols, ITEMS, messages, len_messages);

        delay(50);
        clear_serial_monitor();
    }
    
}