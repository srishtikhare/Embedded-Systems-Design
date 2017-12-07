#ifndef IO_EXPANDER_H
#define IO_EXPANDER_H

#include <at89c51ed2.h>
#include <mcs51reg.h>
#include <stdio.h>
#include <stdlib.h>

#define device_ID_read 0x40
#define device_ID_write 0x41

void PCF8574_write_byte(unsigned char address);
unsigned char PCF8574_read_byte();

#endif
