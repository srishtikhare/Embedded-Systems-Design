#ifndef LCD_H
#define LCD_H

#include <at89c51ed2.h>
#include <mcs51reg.h>
#include <stdio.h>
#include <stdlib.h>

//LCD Module Connections
#define RS P1_4
#define RW P1_5

#define DB0 P0_0
#define DB1 P0_1
#define DB2 P0_2
#define DB3 P0_3
#define DB4 P0_4
#define DB5 P0_5
#define DB6 P0_6
#define DB7 P0_7

void lcd_delay(int a);
void lcd_busywait();
void lcd_command(char a);
void lcd_gotoaddr(unsigned char addr);
void lcd_gotoxy(unsigned char row, unsigned char column);
void lcd_init();
int lcd_getaddr();
void lcd_putch(char a);
void lcd_putstr(char *a);
void ddram_dump_code();
void cgram_dump_code();

#endif
