#include "inc/memory_handler.h"

void store_matrix(uint16_t byte_location, char *matrix, uint8_t size)
{
    for(uint8_t byte_index = 0; byte_index < size; byte_index++)
    {
        EEPROM.write(byte_location + byte_index, matrix[byte_index]);
    }
}

void store_positions(uint16_t byte_location, uint16_t *positions, uint8_t size)
{
    EEPROM.writeBlock<uint16_t>(byte_location, positions, size);
}

void read_positions(uint16_t byte_location, uint16_t *positions, uint8_t size)
{
    EEPROM.readBlock<uint16_t>(byte_location, positions, size);
}

void read_matrix(uint16_t byte_location, char *matrix, uint8_t size)
{
    for(uint8_t byte_index = 0; byte_index < size; byte_index++)
    {
        matrix[byte_index] = EEPROM.read(byte_location + byte_index);
    }
}

uint8_t is_differentiation_byte_in_eeprom()
{
    uint8_t byte_eeprom = EEPROM.read(DIFFERENTIATION_BYTE_ADRESS);
    if(byte_eeprom == DIFFERENTIATION_BYTE)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void write_differentiaion_byte_in_eeprom()
{
    EEPROM.write(DIFFERENTIATION_BYTE_ADRESS, DIFFERENTIATION_BYTE);
}