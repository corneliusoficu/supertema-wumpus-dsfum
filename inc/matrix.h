#ifndef MATRIX_H
#define MATRIX_H

#define START_CELL 64

#include "printers.h"
#include "helpers.h"

void generate_maze  (char *matrix, uint16_t &total_available_cells);
void generate_matrix(char *matrix);
void find_neighbours(int16_t *neighbours, int16_t cell);
uint8_t get_value_at_cell(char *arr, uint16_t cell);

#endif