#include <at89c51ed2.h>
#include <mcs51reg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lcd.h"

//LCD DELAY CODE
void lcd_delay(int delay)
{
    int i;
    int j = 100*delay;

    for(i=0;i<=j;i++);
}

//LCD BUSY-WAIT CODE
void lcd_busywait()
{
    xdata uint8_t* lcd_data;
    lcd_data=(xdata uint8_t*)0x8000;

    do
    {
        RS=0;
        RW=1;
    }
    while(((*lcd_data)&0x80));
}

//LCD GET ADDRESS CODE
int lcd_getaddr()
{
    char lcd_en;
    uint8_t addr;
    xdata uint8_t* lcd_data;
    lcd_data=(xdata uint8_t*)0x8000;



    RS=0;
    RW=1;

    lcd_en=(*lcd_data)&0x80;
    while(lcd_en!=0)
    {
        lcd_en=(*lcd_data)&0x80;
    }
    addr=(*lcd_data)&0x7F;
    return(addr);
}

//LCD INIT CODE
 void lcd_init()
 {

    xdata uint8_t* lcd_data;
    lcd_data=(xdata uint8_t*)0x8000;

    lcd_delay(25);
    RS=0;
    RW=0;
   // lcd_delay(2);
    *lcd_data=0x30;
    lcd_busywait();
  //  lcd_delay(2);


    lcd_delay(10);
    //Unlock Command
    RS=0;
    RW=0;
   // lcd_delay(2);
    *lcd_data=0x30;
    lcd_busywait();
   // lcd_delay(2);


    lcd_delay(10);
    //Unlock Command
    RS=0;
    RW=0;
   // lcd_delay(2);
    *lcd_data=0x30;
    lcd_busywait();
  //  lcd_delay(2);


    lcd_busywait();//Polling for Busy Flag == 0
    //Function Set command
    RS=0;
    RW=0;
  //  lcd_delay(2);
    *lcd_data=0x38;
    lcd_busywait();
   // lcd_delay(2);


    lcd_busywait();//Polling for Busy Flag == 0
    //Turning the display off
    RS=0;
    RW=0;
   // lcd_delay(2);
    *lcd_data=0x08;
    lcd_busywait();
   // lcd_delay(2);


    lcd_busywait();//Polling for Busy Flag == 0
    //Turning the display on
    RS=0;
    RW=0;
   // lcd_delay(2);
    *lcd_data=0x0C;
    lcd_busywait();
   // lcd_delay(2);


    lcd_busywait();//Polling for Busy Flag == 0
    //Entry mode set command
    RS=0;
    RW=0;
   // lcd_delay(2);
    *lcd_data=0x06;
    lcd_busywait();
   // lcd_delay(2);


    lcd_busywait();//Polling for Busy Flag == 0
    //Clear screen and send the cursor home
    RS=0;
    RW=0;
  //  lcd_delay(2);
    *lcd_data=0x01;
    lcd_busywait();
   // lcd_delay(2);
}

//LCD GOTO ADDRESS CODE
void lcd_gotoaddr(unsigned char addr)//DDRAM Address set
{
    xdata uint8_t* lcd_data;
    lcd_data=(xdata uint8_t*)0x8000;

    lcd_busywait();
    RS=0;
    RW=0;

  //  lcd_delay(2);
    *lcd_data=0x80|addr;
    lcd_busywait();
   // lcd_delay(2);
}

//LCD GOTO XY CODE
void lcd_gotoxy(unsigned char row, unsigned char column)
{
    if(row==0)
        lcd_gotoaddr(column);
    else if(row==1)
        lcd_gotoaddr(0x40+column);
    else if(row==2)
        lcd_gotoaddr(0x10+column);
    else if(row==3)
        lcd_gotoaddr(0x50+column);
}

//LCD PUTCHAR CODE
void lcd_putch(char c)
{
    xdata uint8_t* lcd_data;
    lcd_data=(xdata uint8_t*)0x8000;

    lcd_busywait();
    RS=1;
    RW=0;
   // lcd_delay(2);
  // lcd_busywait();
    *lcd_data=c;
    lcd_busywait();
    //lcd_delay(2);
}

//LCD COMMAND CODE
void lcd_command(char a)
{
    xdata uint8_t* lcd_data;
    lcd_data=(xdata uint8_t*)0x8000;

    lcd_busywait();
    RS=0;
    RW=0;
   // lcd_delay(1);
    *lcd_data=a;
    lcd_busywait();
   // lcd_delay(1);
}

//LCD PUTSTR CODE
void lcd_putstr(char *a)
{
    int i=0;
    int flag=0;
    volatile int P;


    while(*(a+i)!='\0')
    {
    P=lcd_getaddr();
    if(P==0x0F)
        flag=1;
    else if(P==0x4F)
        flag=2;
    else if(P==0x1F)
        flag=3;
    else if(P==0x5F)
        flag=4;

        lcd_putch(*(a+i));
        i++;
    if(flag==1)
        {
            lcd_gotoaddr(0x40);
            flag=0;
        }
    else if(flag==2)
        {
            lcd_gotoaddr(0x10);
            flag=0;
        }
    else if(flag==3)
        {
            lcd_gotoaddr(0x50);
            flag=0;
        }
    else if(flag==4)
        {
            lcd_gotoaddr(0x00);
            flag=0;
        }

    }
}
