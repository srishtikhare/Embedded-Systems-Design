#include <at89c51ed2.h>
#include <mcs51reg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lcd.h"
#include "user_input.h"
#include "custom_char.h"

void lcdcreatechar(unsigned char ccode, unsigned char *row_vals, unsigned char row1, unsigned char column1)
{
    lcd_command(0x40+(8*ccode));//Set CGRAM Address
    lcd_putch(*(row_vals++));
    lcd_putch(*(row_vals++));
    lcd_putch(*(row_vals++));
    lcd_putch(*(row_vals++));
    lcd_putch(*(row_vals++));
    lcd_putch(*(row_vals++));
    lcd_putch(*(row_vals++));
    lcd_putch(*(row_vals));
   // lcd_gotoaddr(0x00); //to change where on LCD I'm writing my code
    lcd_gotoxy(row1,column1);
    lcd_putch(ccode);
}

void demo_custom_char()
{   //1st character
    lcd_command(0x40+(8*0));    //FULL
    lcd_putch(0x1F);
    lcd_putch(0x1F);
    lcd_putch(0x1F);
    lcd_putch(0x1F);
    lcd_putch(0x1F);
    lcd_putch(0x1F);
    lcd_putch(0x1F);
    lcd_putch(0x1F);

    //2nd character
    lcd_command(0x40+(8*1));    //BOTTOM HALF
    lcd_putch(0x00);
    lcd_putch(0x00);
    lcd_putch(0x00);
    lcd_putch(0x00);
    lcd_putch(0x1F);
    lcd_putch(0x1F);
    lcd_putch(0x1F);
    lcd_putch(0x1F);

    //3rd character
    lcd_command(0x40+(8*2));    //TOP HALF
    lcd_putch(0x1F);
    lcd_putch(0x1F);
    lcd_putch(0x1F);
    lcd_putch(0x1F);
    lcd_putch(0x00);
    lcd_putch(0x00);
    lcd_putch(0x00);
    lcd_putch(0x00);

    //4th character
    lcd_command(0x40+(8*3));
    lcd_putch(0x1F);    //1
    lcd_putch(0x0F);
    lcd_putch(0x03);
    lcd_putch(0x01);
    lcd_putch(0x00);
    lcd_putch(0x00);
    lcd_putch(0x00);
    lcd_putch(0x00);

    //5th character
    lcd_command(0x40+(8*4));
    lcd_putch(0x1F);    //4
    lcd_putch(0x1E);
    lcd_putch(0x18);
    lcd_putch(0x10);
    lcd_putch(0x00);
    lcd_putch(0x00);
    lcd_putch(0x00);
    lcd_putch(0x00);

    //6th character
    lcd_command(0x40+(8*5));
    lcd_putch(0x1F);    //2
    lcd_putch(0x1F);
    lcd_putch(0x1F);
    lcd_putch(0x1F);
    lcd_putch(0x0F);
    lcd_putch(0x07);
    lcd_putch(0x03);
    lcd_putch(0x01);

    //7th character
    lcd_command(0x40+(8*6));    //3
    lcd_putch(0x1F);
    lcd_putch(0x1F);
    lcd_putch(0x1F);
    lcd_putch(0x1F);
    lcd_putch(0x1E);
    lcd_putch(0x1C);
    lcd_putch(0x18);
    lcd_putch(0x10);

    //8th character
    lcd_command(0x40+(8*7));
    lcd_putch(0x00);
    lcd_putch(0x00);
    lcd_putch(0x00);
    lcd_putch(0x00);
    lcd_putch(0x0E);
    lcd_putch(0x0E);
    lcd_putch(0x0E);
    lcd_putch(0x0E);

    lcd_gotoaddr(0x42); //to change where on LCD I'm writing my code
    lcd_putch(1);
    lcd_putch(1);
    lcd_putch(1);
    lcd_putch(1);
    lcd_putch(1);
    lcd_gotoaddr(0x49);
    lcd_putch(1);
    lcd_putch(1);
    lcd_putch(1);
    lcd_putch(1);
    lcd_putch(1);

    lcd_gotoaddr(0x40);
    lcd_putch(0);
    lcd_putch(0);
    lcd_gotoaddr(0x4E);
    lcd_putch(0);
    lcd_putch(0);

    lcd_gotoaddr(0x02);
    lcd_putch(6);

    lcd_gotoaddr(0x03);
    lcd_putch(4);

    lcd_gotoaddr(0x00);
    lcd_putch(0);
    lcd_putch(0);

    lcd_gotoaddr(0x0D);
    lcd_putch(5);

    lcd_gotoaddr(0x0C);
    lcd_putch(3);

    lcd_gotoaddr(0x0E);
    lcd_putch(0);
    lcd_putch(0);

    lcd_gotoaddr(0x47);
    lcd_putch(0);
    lcd_putch(0);

    lcd_gotoaddr(0x07);
    lcd_putch(7);
    lcd_putch(7);

    lcd_gotoaddr(0x12); //to change where on LCD I'm writing my code
    lcd_putch(2);
    lcd_gotoaddr(0x14);
    lcd_putch(2);
    lcd_putch(2);
    lcd_putch(0);
    lcd_putch(0);
    lcd_putch(0);
    lcd_putch(0);
    lcd_putch(2);
    lcd_putch(2);
    lcd_gotoaddr(0x1D);
    lcd_putch(2);

    lcd_gotoaddr(0x13);
    lcd_putch(0);
    lcd_gotoaddr(0x1C);
    lcd_putch(0);

    lcd_gotoaddr(0x10);
    lcd_putch(0);
    lcd_putch(0);
    lcd_gotoaddr(0x1E);
    lcd_putch(0);
    lcd_putch(0);

    lcd_gotoaddr(0x50);
    lcd_putch(3);
    lcd_putch(5);

    lcd_gotoaddr(0x5E);
    lcd_putch(6);
    lcd_putch(4);

    lcd_gotoaddr(0x56);
    lcd_putch(3);

    lcd_gotoaddr(0x59);
    lcd_putch(4);

    lcd_gotoaddr(0x57);
    lcd_putch(5);

    lcd_gotoaddr(0x58);
    lcd_putch(6);
}
