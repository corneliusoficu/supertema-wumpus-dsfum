#ifndef MEMORY_HANDLER_H
#define MEMORY_HANDLER_H

#define DIFFERENTIATION_BYTE_ADRESS 0x00
#define DIFFERENTIATION_BYTE        0x6E

#include <EEPROMex.h>
#include <EEPROMvar.h>

void store_matrix(uint16_t byte_location, char *matrix, uint8_t size);
void read_matrix (uint16_t byte_location, char *matrix, uint8_t size);

uint8_t is_differentiation_byte_in_eeprom();
void write_differentiaion_byte_in_eeprom();

void store_positions(uint16_t byte_location, uint16_t *positions, uint8_t size);
void read_positions(uint16_t byte_location, uint16_t *positions, uint8_t size);

#endif

