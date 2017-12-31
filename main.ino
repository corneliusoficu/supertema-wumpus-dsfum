#include "inc/matrix.h"

void setup()
{
    Serial.begin(9600);
    while(!Serial);
    randomSeed(analogRead(0));
    Serial.println(F("Wumpus starting!"));

    //TODO: Add test for good division!

    char matrix[(NR_ROWS * NR_COLS) / 8];
    

    generate_matrix(matrix);
    //print_matrix(matrix);
    generate_maze(matrix);

}

void loop()
{
    
}