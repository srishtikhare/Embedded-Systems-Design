#ifndef CUSTOM_CHAR_H
#define CUSTOM_CHAR_H

#include <at89c51ed2.h>
#include <mcs51reg.h>
#include <stdio.h>
#include <stdlib.h>

void lcdcreatechar(unsigned char ccode, unsigned char row_vals[],unsigned char row1, unsigned char column1);
void demo_custom_char();

#endif
