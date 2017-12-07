#include <at89c51ed2.h>
#include <mcs51reg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lcd.h"
#include "eeprom.h"
#include "user_input.h"
#include "clock.h"
#include "custom_char.h"
#include "io_expander.h"
#include "wdt.h"

//ASCII TO HEX CONVERSION CODE
unsigned char ascii_to_hex(unsigned char a)
{
    unsigned char h = ZERO_HEX;
    if (a>='0' && a<='9')
        h |= (a-'0');
    else if(a>='A' && a<='F')
        h |= (0x0A + (a-'A'));
    else if(a>='a' && a<='f')
        h |= (0x0A+(a-'a'));
    else
        h = h-5;

    return h;
}

//ASCII TO DECIMAL CONVERSION CODE
unsigned char ascii_to_dec(unsigned char a)
{
    unsigned char d = ZERO;
    if (a>='0' && a<='9')
        d = a-'0';
    else
        d = -5;

    return d;
}

unsigned int_to_bin(unsigned k)
{
    if (k == 0) return 0;
    if (k == 1) return 1;                       /* optional */
    return (k % 2) + 10 * int_to_bin(k / 2);
}

//LCD CODE
void lcd_code()
{
    char *c="Enter string to be displayed on the LCD screen";
    char buffer[64];
    uint8_t row,column;
    int i=0;
    unsigned char var=ZERO, var1=ZERO;
    lcd_init();
    lcd_putstr(c);
    printf_tiny("\n\rEnter string to be displayed.\n\rHit enter to terminate.\n\r");

    while(i<64)
    {
        *(buffer+i)=getchar();
        putchar(*(buffer+i));
        if(*(buffer+i)=='\r')
        {
            *(buffer+i)='\0';
            break;
        }
            i++;
    }

    printf_tiny("\n\rEnter the row location from 0 to 3 \n\r ");
    row=getchar();
    putchar(row);
    row=ascii_to_dec(row);
    printf_tiny("\n\rEnter the column location from 0 to 15\n\r ");
    var=getchar();
    putchar(var);
    var1=getchar();
    putchar(var1);
    var=ascii_to_dec(var);
    var1=ascii_to_dec(var1);
    column=var*10+var1;
    lcd_command(0x01);
    lcd_gotoxy(row,column);
    lcd_delay(25);
    lcd_putstr(buffer);
}

//LCD DISPLAY CODE
void lcd_display_code()
{

    char var=ZERO_HEX;
    char var1=ZERO_HEX;
    char addrhigh;
    char addrlow;
    char pagenumber;
    unsigned char address=ZERO_HEX;
    unsigned int row_no=ZERO;
    unsigned char PageBlock=ZERO;
    unsigned char datavalue;
    unsigned char strdata[2];

    printf_tiny("\n\rEnter an EEPROM address\n\r");
    var=getchar();
    putchar(var);
    addrhigh=var;
    var1=getchar();
    putchar(var1);
    addrlow=var1;
    var=ascii_to_hex(var);
    var1=ascii_to_hex(var1);
    if(var<0||var1<0)
    {
        printf_tiny("\n\rInvalid Input\n\r");
        return;
    }
    address|=var;
    address=address<<4;
    address|=var1;
    printf("\n\rEntered address is %03x \n\r",address);
    printf_tiny("\n\rEnter an EEPROM page block from 0 to 7\n\r");
    var=getchar();
    putchar(var);
    pagenumber=var;
    var=ascii_to_dec(var);
    if(var<0||var>7)
    {
        printf_tiny("\n\rInvalid Input\n\r");
        return;
    }
    PageBlock=var;
    printf("\n\rEnter a row number between 0 and 3\n\r");
    var=getchar();
    putchar(var);
    var=ascii_to_dec(var);
    row_no=var;
    datavalue=eeprom_read_byte(address,PageBlock);
    lcd_gotoxy(row_no,ZERO);
    lcd_putch(pagenumber);
    lcd_putch(addrhigh);
    lcd_putch(addrlow);
    sprintf(strdata,"%x",datavalue);
    lcd_putch(':');
    lcd_putch(strdata[0]);
    lcd_putch(strdata[1]);
    printf_tiny("\n\rOutput is available on the LCD\n\r");
}

//WRITE BYTE CODE
void write_byte_code()
{
    char var=ZERO_HEX;
    char var1=ZERO_HEX;
    unsigned int address=ZERO_HEX;
    unsigned char PageBlock=ZERO;
    unsigned char datavalue=ZERO_HEX;
    printf_tiny("\n\rEnter an EEPROM address\n\r");
    var=getchar();
    putchar(var);
    var1=getchar();
    putchar(var1);
    var=ascii_to_hex(var);
    var1=ascii_to_hex(var1);
    if(var<0||var1<0)
    {
        printf_tiny("\n\rInvalid Input\n\r");
        return;
    }
    address|=var;
    address=address<<4;
    address|=var1;
    printf("\n\rEntered address is %03x \n\r",address);
    printf_tiny("\n\rEnter an EEPROM page block from 0 to 7\n\r");
    var=getchar();
    putchar(var);
    var=ascii_to_dec(var);
    if(var<0||var>7)
    {
        printf_tiny("\n\rInvalid Input\n\r");
        return;
    }
    PageBlock=var;
    printf_tiny("\n\rEntered page block is %d \n\r",PageBlock);
    printf_tiny("\n\rEnter data between 0x00 to 0xFF\n\r");
    var=getchar();
    putchar(var);
    var1=getchar();
    putchar(var1);
    var=ascii_to_hex(var);
    var1=ascii_to_hex(var1);
    if(var<0||var1<0)
    {
        printf_tiny("\n\rInvalid Input\n\r");
        return;
    }
    datavalue|=var;
    datavalue=datavalue<<4;
    datavalue|=var1;
    eeprom_write_byte(address,datavalue,PageBlock);
    printf("\n\rData %03x written successfully to %03x addresss at %d Page block\n\r", datavalue, address, PageBlock);
}

//READ BYTE CODE
void read_byte_code()
{
    char var=ZERO_HEX;
    char var1=ZERO_HEX;
    unsigned int address=ZERO_HEX;
    unsigned char PageBlock=ZERO;
    unsigned int datavalue;
    printf_tiny("\n\rEnter an EEPROM address\n\r");
    var=getchar();
    putchar(var);
    var1=getchar();
    putchar(var1);
    var=ascii_to_hex(var);
    var1=ascii_to_hex(var1);
    if(var<0||var1<0)
    {
        printf_tiny("\n\rInvalid Input\n\r");
        return;
    }
    address|=var;
    address=address<<4;
    address|=var1;
    printf("\n\rEntered address is %03x \n\r",address);
    printf_tiny("\n\rEnter an EEPROM page block from 0 to 7\n\r");
    var=getchar();
    putchar(var);
    var=ascii_to_dec(var);

    if(var<0||var>7)
    {
        printf_tiny("\n\rInvalid Input\n\r");
        return;
    }

    PageBlock=var;
    printf_tiny("\n\rEntered page block is %d \n\r",PageBlock);
    datavalue=eeprom_read_byte(address,PageBlock);
    printf("\n\r%x : %x\n\r",address, datavalue);
}

//DDRAM DUMP CODE
void ddram_dump_code()
{
    unsigned char addr=ZERO_HEX;
    unsigned char dump=ZERO_HEX;
    int i=0;
    xdata uint8_t* LCD;
    LCD=(xdata uint8_t*)0x8000;
    lcd_busywait();
    //Set DDRAM address
    RS=0;
    RW=0;
    lcd_delay(2);
    *LCD=0x80;
    lcd_delay(2);
    printf_tiny("\n\r");
    printf_tiny("\n\r************************DDRAM DUMP**********************\n\r");

    lcd_gotoaddr(0x00);
    while(i<16)
    {
        RS=1;
        RW=1;
        lcd_delay(2);
        dump=*LCD;
        printf("0x%02x %x ",addr, dump);
        addr++;
        i++;
    }
    printf_tiny("\n\r");
    i=0;
    lcd_gotoaddr(0x40);
    addr=0x40;
    while(i<16)
    {
        RS=1;
        RW=1;
        lcd_delay(2);
        dump=*LCD;
        printf("0x%02x %x ",addr, dump);
        addr++;
        i++;
    }
    printf_tiny("\n\r");
    i=0;
    lcd_gotoaddr(0x10);
    addr=0x10;
    while(i<16)
    {
        RS=1;
        RW=1;
        lcd_delay(2);
        dump=*LCD;
        printf("0x%02x %x ",addr, dump);
        i++;
        addr++;
    }
    printf_tiny("\n\r");
    i=0;
    lcd_gotoaddr(0x50);
    addr=0x50;
    while(i<16)
    {
        RS=1;
        RW=1;
        lcd_delay(2);
        dump=*LCD;
        printf("0x%02x %x ",addr, dump);
        i++;
        addr++;
    }
    printf_tiny("\n\r");
    i=0;
    lcd_gotoaddr(0x20);
    addr=0x20;
    while(i<8)
    {
        RS=1;
        RW=1;
        lcd_delay(2);
        dump=*LCD;
        printf("0x%02x %x ",addr, dump);
        i++;
        addr++;
    }
    i=0;
    lcd_gotoaddr(0x60);
    addr=0x60;
    while(i<8)
    {
        RS=1;
        RW=1;
        lcd_delay(2);
        dump=*LCD;
        printf("0x%02x %x ",addr, dump);
        i++;
        addr++;
    }

}

//CGRAM DUMP CODE
void cgram_dump_code()
{
    unsigned char addr=ZERO_HEX;
    unsigned char dump=ZERO_HEX;
    int i=0;
    xdata uint8_t* LCD;
    LCD=(xdata uint8_t*)0x8000;

    lcd_busywait();
    RS=0;
    RW=0;
    lcd_delay(2);
    *LCD=0x40;
    lcd_delay(2);
    while(addr<=0x3F)
    {
        RS=1;
        RW=0;
        lcd_delay(5);
       // *LCD=0xA0;
        addr++;
        lcd_delay(2);
    }
    printf_tiny("\n\r");
    printf_tiny("\n\r*******************CGRAM DUMP*********************\n\r");
    addr=ZERO_HEX;
    while(addr<=0x3F)
    {
        RS=1;
        RW=1;
        lcd_delay(2);
        dump=*LCD;
        if(i==5)
        {
            i=0;
            printf_tiny("\n\r");
        }
        printf("%04x %x ",addr, dump);
        addr++;
        lcd_delay(2);
        i++;
    }
}

void HexDump()
{
    int i=0;
    char var=ZERO_HEX;
    char var1=ZERO_HEX;
    unsigned int addressStart=ZERO_HEX;
    unsigned int addressEnd=ZERO_HEX;
    unsigned int addressCurr=ZERO_HEX;
    unsigned char PageBlockStart=ZERO;
    unsigned char PageBlockEnd=ZERO;
    unsigned char PageBlockCurr=ZERO;
    unsigned char datavalue;
    printf_tiny("\n\rEnter starting EEPROM address\n\r");
    var=getchar();
    putchar(var);
    var1=getchar();
    putchar(var1);
    var=ascii_to_hex(var);
    var1=ascii_to_dec(var1);
    if(var<0||var1<0)
    {
        printf_tiny("\n\rInvalid Input\n\r");
        return;
    }
    addressStart|=var;
    addressStart=addressStart<<4;
    addressStart|=var1;
    printf("\n\rEntered address is %03x \n\r",addressStart);
    printf_tiny("\n\rEnter an EEPROM page block from 0 to 7\n\r");
    var=getchar();
    putchar(var);
    var=ascii_to_dec(var);
    if(var<0||var>7)
    {
        printf_tiny("\n\rInvalid Input\n\r");
        return;
    }
    PageBlockStart=var;
    printf_tiny("\n\rEntered page block is %d \n\r",PageBlockStart);

    printf_tiny("\n\rEnter last EEPROM address\n\r");
    var=getchar();
    putchar(var);
    var1=getchar();
    putchar(var1);
    var=ascii_to_hex(var);
    var1=ascii_to_hex(var1);
    if(var<0||var1<0)
    {
        printf_tiny("\n\rInvalid Input\n\r");
        return;
    }
    addressEnd|=var;
    addressEnd=addressEnd<<4;
    addressEnd|=var1;
    printf("\n\rEntered address is %03x \n\r",addressEnd);
    printf_tiny("\n\rEnter an EEPROM page block from 0 to 7\n\r");
    var=getchar();
    putchar(var);
    var=ascii_to_dec(var);
    if(var<0||var>7)
    {
        printf_tiny("\n\rInvalid Input\n\r");
        return;
    }
    PageBlockEnd=var;
    printf_tiny("\n\rEntered page block is %d\n\r",PageBlockEnd);

    if((PageBlockStart>PageBlockEnd)||((PageBlockStart==PageBlockEnd)&&(addressStart>addressEnd)))
    {
        printf_tiny("\n\rEnd address is smaller than start address\n\r");
        return;
    }
    else if(PageBlockStart==PageBlockEnd&&addressStart==addressEnd)
    {
        printf_tiny("\n\rEnd address is same start address\n\r");
        return;
    }

    PageBlockCurr=PageBlockStart;
    addressCurr=addressStart;


    for(PageBlockCurr=PageBlockStart;PageBlockCurr<=PageBlockEnd;PageBlockCurr++)
    {
        for(addressCurr;addressCurr<=0xFF;addressCurr++)
        {
            if(PageBlockCurr==PageBlockEnd&&addressCurr==addressEnd+1)
                return;
            if(i%16==0)
            {
                printf_tiny("\n\r");
                printf("%x %02x:",PageBlockCurr,addressCurr);
            }
            datavalue=eeprom_read_byte(addressCurr,PageBlockCurr);
            printf_tiny("%x ",datavalue);
            i++;
        }
        addressCurr=0;
    }
}

void lcd_code_NEW()
{
    char buffer[64];
    volatile int P;
    uint8_t row, column;
    int i=0;
    unsigned char var=ZERO, var1=ZERO;
    lcd_init();

    printf_tiny("\n\rEnter the row location from 0 to 3 \n\r ");
    row=getchar();
    putchar(row);
    row=ascii_to_dec(row);
    printf_tiny("\n\rEnter the column location from 0 to 15\n\r ");
    var=getchar();
    putchar(var);
    var1=getchar();
    putchar(var1);
    var=ascii_to_dec(var);
    var1=ascii_to_dec(var1);
    column=var*10+var1;
    lcd_command(0x01);
    lcd_gotoxy(row,column);
    lcd_delay(25);
    P = lcd_getaddr();

    printf_tiny("\n\rEnter string to be displayed.\n\rHit enter to terminate.\n\r");

    while(1)
    {
        while(((lcd_getaddr()) >=0x00) && ((lcd_getaddr()) <= 0x0F))
        {
            *(buffer+i)=getchar();
            putchar(*(buffer+i));
            lcd_putch(*(buffer+i));
            if(*(buffer+i)=='\r')
            {
                *(buffer+i)='\0';
                break;
            }
                i++;
        }
        lcd_gotoxy(1,0);
        while(((lcd_getaddr()) >= 0x40) && ((lcd_getaddr()) <= 0x4F))
        {

            *(buffer+i)=getchar();
            putchar(*(buffer+i));
            lcd_putch(*(buffer+i));
            if(*(buffer+i)=='\r')
            {
                *(buffer+i)='\0';
                break;
            }
                i++;
        }
        lcd_gotoxy(2,0);
        while(((lcd_getaddr()) >= 0x10) && ((lcd_getaddr()) <= 0x1F))
        {

            *(buffer+i)=getchar();
            putchar(*(buffer+i));
            lcd_putch(*(buffer+i));
            if(*(buffer+i)=='\r')
            {
                *(buffer+i)='\0';
                break;
            }
                i++;
        }
        lcd_gotoxy(3,0);
        while(((lcd_getaddr()) >= 0x50) && ((lcd_getaddr()) <= 0x5F))
        {

            *(buffer+i)=getchar();
            putchar(*(buffer+i));
            lcd_putch(*(buffer+i));
            if(*(buffer+i)=='\r')
            {
                *(buffer+i)='\0';
                break;
            }
                i++;
        }
        lcd_gotoxy(0,0);
    }
}

void lcd_build_char()
{
    unsigned char code1,temp;
    uint8_t i;
    unsigned char rows[8];
    unsigned char var=ZERO, var1=ZERO;
    unsigned char row,column;
    printf_tiny("\n\rEnter the custom character location from 0-7\n\r");
    code1=getchar();
    putchar(code1);
    code1=ascii_to_dec(code1);
    if((code1==0)||(code1==1)||(code1==2)||(code1==3)||(code1==4)||(code1==5)||(code1==6)||(code1==7))
    {
        printf_tiny("\n\rEnter row values\n\r");
        for(i=0;i<8;i++)
        {
            rows[i]=0x00;
            temp=getchar();
            putchar(temp);
            temp=ascii_to_hex(temp);
            rows[i]|=temp;
            rows[i]=rows[i]<<4;
            temp=getchar();
            putchar(temp);
            temp=ascii_to_hex(temp);
            rows[i]|=temp;
            printf_tiny("\n\r");
            printf_tiny("Current state -->");
            printf_tiny("\n\r");

            if(i==0)
            {
                printf_tiny("\n\rRow %d : %x\n\r",0,rows[0]);
            }
            else if(i==1)
            {
                printf_tiny("\n\rRow %d : %x %x\n\r",1,rows[0],rows[1]);
            }
            else if(i==2)
            {
                printf_tiny("\n\rRow %d : %x %x %x\n\r",2,rows[0],rows[1],rows[2]);
            }
            else if(i==3)
            {
                printf_tiny("\n\rRow %d : %x %x %x %x\n\r",3,rows[0],rows[1],rows[2],rows[3]);
            }
            else if(i==4)
            {
                printf_tiny("\n\rRow %d : %x %x %x %x %x\n\r",4,rows[0],rows[1],rows[2],rows[3],rows[4]);
            }
            else if(i==5)
            {
                printf_tiny("\n\rRow %d : %x %x %x %x %x %x\n\r",5,rows[0],rows[1],rows[2],rows[3],rows[4],rows[5]);
            }
            else if(i==6)
            {
                printf_tiny("\n\rRow %d : %x %x %x %x %x %x %x\n\r",6,rows[0],rows[1],rows[2],rows[3],rows[4],rows[5],rows[6]);
            }
            else if(i==7)
            {
                printf_tiny("\n\rRow %d : %x %x %x %x %x %x %x %x\n\r",7,rows[0],rows[1],rows[2],rows[3],rows[4],rows[5],rows[6],rows[7]);
            }
            printf_tiny("\n\r");
        }

        printf_tiny("\n\rEnter the row location from 0 to 3\n\r ");
        row=getchar();
        putchar(row);
        row=ascii_to_dec(row);
        printf_tiny("\n\rEnter the column location from 0 to 15\n\r ");
        var=getchar();
        putchar(var);
        var1=getchar();
        putchar(var1);
        var=ascii_to_dec(var);
        var1=ascii_to_dec(var1);
        column=var*10+var1;

        lcdcreatechar(code1,rows,row,column);
    }
    else
    {
        printf_tiny("\n\rInvalid input\n\r");
    }
}

void hang_condition()
{
    wtd_init();
    while(1)
    {
        printf_tiny("\n\rSYSTEM MALFUNCTION\n\r");
    }
}
