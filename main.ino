#include "inc/game.h"

char     *matrix;
uint16_t *points;
uint16_t total_available_cells;

void setup()
{
    Serial.begin(1000000);
    while(!Serial);

    randomSeed(analogRead(0));

    Serial.println(F("Wumpus starting..."));

    Serial.println(F("Generating maze..."));  
    freeRam();
    initialize_game(&matrix, &points, total_available_cells);
    play_game(matrix, points);

    Serial.println(total_available_cells);
}

void loop()
{
    // play_game(matrix, points);
    // delay(500);
    // clear_serial_monitor();
}