#ifndef HELPERS_H
#define HELPERS_H

#include "Arduino.h"

void freeRam ();
void print_array(int16_t *array, uint8_t size);
void delay_countdown(uint8_t delay);
void clear_serial_monitor();
#endif