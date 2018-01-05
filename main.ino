#include "inc/game.h"

char *matrix;
uint16_t *points;

void setup()
{
    Serial.begin(74880);
    while(!Serial);

    randomSeed(analogRead(0));

    Serial.println(F("Wumpus starting..."));

    Serial.println(F("Generating maze..."));  

    initialize_game(matrix, points);
    
}

void loop()
{
    
}