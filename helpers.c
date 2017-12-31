#include "inc/helpers.h"

void freeRam() 
{
    extern int __heap_start, *__brkval; 
    int v; 
    int free_ram = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 

    Serial.print("Free ram = ");
    Serial.print(free_ram);
    Serial.print(" bytes");

    Serial.println();
}