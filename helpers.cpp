#include "inc/helpers.h"

void freeRam() 
{
    extern int __heap_start, *__brkval; 
    int v; 
    int free_ram = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 

    Serial.print(F("Free ram = "));
    Serial.print(free_ram);
    Serial.println(F(" bytes"));
}

void print_array(uint16_t *array, uint8_t size)
{
    for(uint8_t index = 0; index < size; index++)
    {
        Serial.print(array[index]);
        Serial.print(" ");
    }
    Serial.println();
}

