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

void print_array(int16_t *array, uint8_t size)
{
    for(uint8_t index = 0; index < size; index++)
    {
        Serial.print(array[index]);
        Serial.print(" ");
    }
    Serial.println();
}

void delay_countdown(uint8_t delay_time)
{
    Serial.print(F("Waiting "));
    Serial.print(delay_time);
    Serial.println(F(" seconds..."));

    delay(delay_time * 1000);

}

void clear_serial_monitor()
{
    Serial.write(27);       // ESC command
    Serial.print("[2J");    // clear screen command
    Serial.write(27);
    Serial.print("[H");     // cursor to home command
}



