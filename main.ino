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
    freeRam();
    initialize_game(&matrix, &points);
    // play_game(matrix, points);

}

void loop()
{
    play_game(matrix, points);
    delay(200);
    clear_serial_monitor();
}