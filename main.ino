#include "inc/game.h"

char     *matrix;
uint16_t *points;

void setup()
{
    Serial.begin(1000000);
    while(!Serial);

    randomSeed(analogRead(0));

    Serial.println(F("Wumpus starting..."));

    Serial.println(F("Generating maze..."));  
    // freeRam();
    initialize_game(&matrix, &points);
    // play_game(matrix, points);

    uint16_t cell1, cell2;
    find_accesible_points(matrix, &cell1, 1);
    find_accesible_points(matrix, &cell2, 1);

}

void loop()
{

    find_new_player_positions(matrix, points, ITEMS - 1);
    print_matrix_with_positions(matrix, points, symbols, ITEMS);

    delay(100);
    clear_serial_monitor();
}