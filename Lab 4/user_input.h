#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <at89c51ed2.h>
#include <mcs51reg.h>
#include <stdio.h>
#include <stdlib.h>

#define ZERO 0
#define DEV_ID 0xA0
#define ZERO_HEX 0x00
#define MSB_BIT 0x80

unsigned char ascii_to_hex(unsigned char a);
unsigned char ascii_to_dec(unsigned char a);
unsigned int_to_bin(unsigned k);
void lcd_code();
void write_byte_code();
void read_byte_code();
void lcd_display_code();
void HexDump();
void lcd_code_NEW();
void lcd_build_char();
void wdt_user();
void hang_condition();
void enable_alarm();
void set_alarm();
void disable_alarm();

#endif
