#ifndef MATRIX_H
#define MATRIX_H

#define NR_ROWS 23
#define NR_COLS 64

#include "Arduino.h"
#include "helpers.h"

// typedef struct
// {
// 	uint8_t x, y; //Node position - little waste of memory, but it allows faster generation
// 	void *parent; //Pointer to parent node
// 	char c; //Character to be displayed
// 	char dirs; //Directions that still haven't been explored
// } Node;

void generate_maze  (char *matrix);
void generate_matrix(char *matrix);
void print_matrix   (char *matrix);

#endif