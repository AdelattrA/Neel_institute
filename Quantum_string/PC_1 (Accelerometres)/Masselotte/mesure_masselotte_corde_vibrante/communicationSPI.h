#ifndef _COMMUNICATION_SPI_H
#define _COMMUNICATION_SPI_H


#include <arduino.h>

void initSPI(void);
byte read_single_byte_register_SPI(byte registre);
void write_single_byte_register_SPI(byte registre, byte val);
int read_axis_data_register_SPI(byte registre);
int read_double_byte_register_SPI(byte registre);
void write_double_byte_register_SPI(byte registre, int val);

#endif
