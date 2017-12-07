#ifndef EEPROM_H
#define EEPROM_H

#include <at89c51ed2.h>
#include <mcs51reg.h>
#include <stdio.h>
#include <stdlib.h>

void eeprom_write_byte(unsigned char address, unsigned char datavalue, unsigned char PageNo);
unsigned char eeprom_read_byte(unsigned char address,unsigned char PageNo);
void eereset();

#endif
