#ifndef PRINTERS_H
#define PRINTERS_H

#define NR_ROWS      23
#define NR_COLS      64
#define PAD_FIRST_COL 1
#define WALL_CHAR   219

#include "Arduino.h"

void print_matrix(char *matrix, uint8_t show_binary);
void print_matrix_with_positions(char *matrix, uint16_t *positions, char symbols[][24], uint8_t size, const char messages[][20], uint8_t nr_messages);

#endif


