/**********SRISHTI KHARE*************/
/**********ESD LAB, FALL 2016*************/
#include <at89c51ed2.h>
#include <mcs51reg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lcd.h"
#include "i2c.h"
#include "eeprom.h"
#include "user_input.h"
#include "custom_char.h"
#include "io_expander.h"
#include "wdt.h"

int wtd_flag;

static int ta;
static char l,x;
static char temp_alarm[4];
static char temp_alarm2[4];
static char temp_alarm3[4];
static char option[3], option_val;
static char alarm_set1[3] = {0, 0, 0};
static char alarm_set2[3] = {0, 0, 0};
static char alarm_set3[3] = {0, 0, 0};
static unsigned int minute, sec, one_tenth_sec=0, one_tenth;
static unsigned int alarm_minute1[3], alarm_sec1[3], alarm_one_tenth_sec1[3] = {0, 0, 0}, alarm_one_tenth1[3];
static unsigned int alarm_minute2[3], alarm_sec2[3], alarm_one_tenth_sec2[3] = {0, 0, 0}, alarm_one_tenth2[3];
static unsigned int alarm_minute3[3], alarm_sec3[3], alarm_one_tenth_sec3[3] = {0, 0, 0}, alarm_one_tenth3[3];

void wdt_user()
{
    printf_tiny("\n\rWatchdog Timer Enabled\n\r");
    wtd_init();
    wtd_flag=1;
}
//STARTUP CODE
_sdcc_external_startup()//Startup function that is executed first when the microcontroller is turned on
{
    AUXR|=0x0C;  //Set the XRS1:XRS0 bit to 1 to enable 1 KB of internal extended RAM
    TMOD=0X21;   //Enable Timer 1 Mode 2
    TCON=0X11;
    TH1=0xFF;    //Load TH1 with FD for 9600 baud rate
    PCON |= 0x80;
    SCON=0x50;   //Select Mode 1 for full duplex with variable baud rate
    TR1=1;       //Start Timer
    TI=1;        //Set TI flag to 0

    return 0;
}

//PUTCHAR CODE
void putchar (char c)//Definition for putchar function to display characters on the serial terminal
{
    if(wtd_flag == 1)
        wtd_reset();
    SBUF = c;    //SBUF stores the character to be dsiplayed
	while (!TI); //Wait for TI flag
	TI = 0;      //Set TI flag to 0
}

//GETCHAR CODE
char getchar()      //Definition of getchar function to fetch input from the user
{
    if(wtd_flag == 1)
        wtd_reset();
    while(RI==0);   //Wait for RI flag
    RI=0;           //Set RI to 0
    return SBUF;    //Return the value in the buffer
}
unsigned char hex_to_ascii(unsigned n)
{
    if (n < 10) {
        return n + '0';
    } else {
        return (n - 10) + 'A';
    }
}

unsigned char counter_val= '0';
unsigned char counter;

void io_expander_user()
{
    unsigned char var1,var,data_value,mask,counter,c;
    IEN0 |= 0x01;
    counter = hex_to_ascii(counter_val);
    lcd_gotoxy(3,0);
    lcd_putch(counter);

    printf_tiny("\n\r**********************I/O Expander********************\n\r");

    printf_tiny("\n\r\Wish to reset counter Y/N?\n\r");
    c=getchar();
    if(c=='Y')
    {
        lcd_gotoxy(3,0);
        lcd_putch('0');
    }

    printf_tiny("\n\rEnter output mask for the pins\n\r");
    var=getchar();
    putchar(var);
    var1=getchar();
    putchar(var1);
    var=ascii_to_hex(var);
    var1=ascii_to_hex(var1);
    mask=var;
    mask=mask<<4;
    mask|=var1;

    printf_tiny("\n\rEnter output pin data between 00 to FF\n\r");
    var=getchar();
    putchar(var);
    var1=getchar();
    putchar(var1);
    var=ascii_to_hex(var);
    var1=ascii_to_hex(var1);
    data_value=var;
    data_value=data_value<<4;
    data_value|=var1;

    PCF8574_write_byte(data_value&mask);
}

void print_pin_status()
{
    unsigned char return_value;

    return_value = PCF8574_read_byte();
    printf_tiny("\n\rCurrent status of the pins: %x\n\r",return_value);
}

void external_interrupt(void)interrupt 0//isr for external interrupt
{
    if(counter_val< 0x0F)
    {
        counter_val++;
        counter = hex_to_ascii(counter_val);
        lcd_gotoxy(3,0);
        lcd_putch(counter);
    }
    else
    {
        counter_val = 0x00;
        lcd_gotoxy(3,0);
        lcd_putch('0');
    }

    printf_tiny("\n\rINTERRUPT OCCURED!!!\n\r");
    IEN0 &= 0xFE;
  //  print_pin_status();
}

void timer0() //Start Timer 0
{
    TL0=0x4B;
    TH0=0xFD;
    TR0=1;

   // IEN0 = 0x82;
}

void external_interrupt1() __interrupt(1) // ISR for the Timer0 mode1
{
    TR0 = 0;
    TH0 = 0x4B;
    TL0 = 0xFD;
    TF0 = 0;
    TR0 = 1;
    if (ta == 2)
    {
        ta = 0;
    }
    ta++;

    //MAIN TIMER
    lcd_gotoaddr(0x59);
    one_tenth = one_tenth_sec % 10;

    sec = (one_tenth_sec / 10) % 60;
    minute = (one_tenth_sec / (60 * 10)) % 60;

    lcd_putch(((minute / 10) + 0x30));
    lcd_putch(((minute % 10) + 0x30));
    lcd_putch(':');
    lcd_putch(((sec/ 10) + 0x30));
    lcd_putch(((sec % 10) + 0x30));
    lcd_putch(':');
    lcd_putch((one_tenth + 0x30));
    one_tenth_sec++;

    if (alarm_set1[0])
    {
        alarm_one_tenth_sec1[0]--;

        if (alarm_one_tenth_sec1[0] == 0)
        {
            alarm_set1[0] = 0;
            lcd_gotoaddr(0x00);
            lcd_putstr("Alarm 1");
        }
        lcd_gotoaddr(0x09);

        alarm_one_tenth1[0] = alarm_one_tenth_sec1[0] % 10;

        alarm_sec1[0] = (alarm_one_tenth_sec1[0] / 10) % 60;
        alarm_minute1[0] = (alarm_one_tenth_sec1[0] / (60 * 10)) % 60;

        lcd_putch(((alarm_minute1[0] / 10) + 0x30));
        lcd_putch(((alarm_minute1[0] % 10) + 0x30));
        lcd_putch(':');
        lcd_putch(((alarm_sec1[0]/ 10) + 0x30));
        lcd_putch(((alarm_sec1[0] % 10) + 0x30));
        lcd_putch(':');
        lcd_putch((alarm_one_tenth1[0] + 0x30));
    }

    if (alarm_set2[0])
    {
        alarm_one_tenth_sec2[0]--;

        if (alarm_one_tenth_sec2[0] == 0)
        {
            alarm_set2[0] = 0;
            lcd_gotoaddr(0x40);
            lcd_putstr("Alarm 2");
        }
        lcd_gotoaddr(0x49);

        alarm_one_tenth2[0] = alarm_one_tenth_sec2[0] % 10;

        alarm_sec2[0] = (alarm_one_tenth_sec2[0] / 10) % 60;
        alarm_minute2[0] = (alarm_one_tenth_sec2[0] / (60 * 10)) % 60;

        lcd_putch(((alarm_minute2[0] / 10) + 0x30));
        lcd_putch(((alarm_minute2[0] % 10) + 0x30));
        lcd_putch(':');
        lcd_putch(((alarm_sec2[0]/ 10) + 0x30));
        lcd_putch(((alarm_sec2[0] % 10) + 0x30));
        lcd_putch(':');
        lcd_putch((alarm_one_tenth2[0] + 0x30));
    }

    if (alarm_set3[0])
    {
        alarm_one_tenth_sec3[0]--;

        if (alarm_one_tenth_sec3[0] == 0)
        {
            alarm_set3[0] = 0;
            lcd_gotoaddr(0x10);
            lcd_putstr("Alarm 3");
        }
        lcd_gotoaddr(0x19);

        alarm_one_tenth3[0] = alarm_one_tenth_sec3[0] % 10;

        alarm_sec3[0] = (alarm_one_tenth_sec3[0] / 10) % 60;
        alarm_minute3[0] = (alarm_one_tenth_sec3[0] / (60 * 10)) % 60;

        lcd_putch(((alarm_minute3[0] / 10) + 0x30));
        lcd_putch(((alarm_minute3[0] % 10) + 0x30));
        lcd_putch(':');
        lcd_putch(((alarm_sec3[0]/ 10) + 0x30));
        lcd_putch(((alarm_sec3[0] % 10) + 0x30));
        lcd_putch(':');
        lcd_putch((alarm_one_tenth3[0] + 0x30));
    }
}

void alaramset1()
{
    while (1)
    {
        /* Accept Alarm 1 value */
        printf_tiny("\n\n\n\r*********************************************************");
        printf_tiny("\n\rAlarm 1 operations");
        printf_tiny("\n\r*********************************************************");
        printf_tiny("\n\r1. Edit Alarm 1: (mm:ss:s)");
        printf_tiny("\n\r2. Enable Alarm");
        printf_tiny("\n\r3. Disable Alarm");
        printf_tiny("\n\r4. Back to Clock menu");
        printf_tiny("\n\r*********************************************************");
        /* Accept user choice */
        printf_tiny("\n\rEnter you choice: (1-4)");
        l=getchar();

        option_val = ascii_to_hex(l);

        if (option_val == 1)
        {
            if (alarm_set1[0] == 0)
            {
                lcd_gotoaddr(0x09);
                lcd_putch(((alarm_minute1[0] / 10) + 0x30));
                lcd_putch(((alarm_minute1[0] % 10) + 0x30));
                lcd_putch(':');
                lcd_putch(((alarm_sec1[0]/ 10) + 0x30));
                lcd_putch(((alarm_sec1[0] % 10) + 0x30));
                lcd_putch(':');
                lcd_putch((alarm_one_tenth1[0] + 0x30));

                /* Accept minutes */
                while (1)
                {
                    printf_tiny("\n\rEnter minute:(Range 0 - 59)\t");
                    gets(temp_alarm);
                    alarm_minute1[0] = atoi(temp_alarm);
                    break;
                }

                while (1)
                {
                    /* Accept seconds */
                    printf_tiny("\n\rEnter seconds:\t");
                    gets(temp_alarm);
                    alarm_sec1[0] = atoi(temp_alarm);

                    if (!((alarm_sec1[0] >= 0) && (alarm_sec1[0] <= 59)))
                    {
                        printf_tiny("\n\rEntered value not within range.. Please try again..");
                        continue;
                    }

                    break;
                }
                alarm_one_tenth1[0] = 0;
                lcd_gotoaddr(0x09);

                lcd_putch(((alarm_minute1[0] / 10) + 0x30));
                lcd_putch(((alarm_minute1[0] % 10) + 0x30));
                lcd_putch(':');
                lcd_putch(((alarm_sec1[0]/ 10) + 0x30));
                lcd_putch(((alarm_sec1[0] % 10) + 0x30));
                lcd_putch(':');
                ((alarm_one_tenth1[0] + 0x30));

                /* Calculate alarm_one_tenth_sec */
                alarm_one_tenth_sec1[0] = (alarm_minute1[0] * 60 * 10) + (alarm_sec1[0] * 10);
            }

            else
            {
                printf_tiny("Please disable the alarm to edit..");
            }
        }

        else if (option_val == 2)
        {
            alarm_set1[0] = 1;
        }

        else if (option_val == 3)
        {
            alarm_set1[0] = 0;
            lcd_gotoaddr(0x00);
            lcd_putstr("                ");
        }

        else if (option_val == 4)
        {
            break;
        }

        else
        {
            printf_tiny("\n\rInvalid option chosen");
        }
    }
}

void alaramset2()
{
    while (1)
    {
        /* Accept Alarm 1 value */
        printf_tiny("\n\n\n\r*********************************************************");
        printf_tiny("\n\rAlarm 2 operations");
        printf_tiny("\n\r*********************************************************");
        printf_tiny("\n\r1. Edit Alarm 2: (mm:ss:s)");
        printf_tiny("\n\r2. Enable Alarm");
        printf_tiny("\n\r3. Disable Alarm");
        printf_tiny("\n\r4. Back to Clock menu");
        printf_tiny("\n\r*********************************************************");
        /* Accept user choice */
        printf_tiny("\n\rEnter you choice: (1-4)");
        l=getchar();

        option_val = ascii_to_hex(l);

        if (option_val == 1)
        {
            if (alarm_set2[0] == 0)
            {
                lcd_gotoaddr(0x49);
                lcd_putch(((alarm_minute2[0] / 10) + 0x30));
                lcd_putch(((alarm_minute2[0] % 10) + 0x30));
                lcd_putch(':');
                lcd_putch(((alarm_sec2[0]/ 10) + 0x30));
                lcd_putch(((alarm_sec2[0] % 10) + 0x30));
                lcd_putch(':');
                lcd_putch((alarm_one_tenth2[0] + 0x30));

                /* Accept minutes */
                while (1)
                {
                    printf_tiny("\n\rEnter minute:(Range 0 - 59)\t");
                    gets(temp_alarm2);
                    alarm_minute2[0] = atoi(temp_alarm2);
                    break;
                }

                while (1)
                {
                    /* Accept seconds */
                    printf_tiny("\n\rEnter seconds:\t");
                    gets(temp_alarm2);
                    alarm_sec2[0] = atoi(temp_alarm2);

                    if (!((alarm_sec2[0] >= 0) && (alarm_sec2[0] <= 59)))
                    {
                        printf_tiny("\n\rEntered value not within range.. Please try again..");
                        continue;
                    }

                    break;
                }
                alarm_one_tenth2[0] = 0;
                lcd_gotoaddr(0x49);

                lcd_putch(((alarm_minute2[0] / 10) + 0x30));
                lcd_putch(((alarm_minute2[0] % 10) + 0x30));
                lcd_putch(':');
                lcd_putch(((alarm_sec2[0]/ 10) + 0x30));
                lcd_putch(((alarm_sec2[0] % 10) + 0x30));
                lcd_putch(':');
                ((alarm_one_tenth2[0] + 0x30));

                /* Calculate alarm_one_tenth_sec */
                alarm_one_tenth_sec2[0] = (alarm_minute2[0] * 60 * 10) + (alarm_sec2[0] * 10);
            }

            else
            {
                printf_tiny("Please disable the alarm to edit..");
            }
        }

        else if (option_val == 2)
        {
            alarm_set2[0] = 1;
        }

        else if (option_val == 3)
        {
            alarm_set2[0] = 0;
            lcd_gotoaddr(0x40);
            lcd_putstr("                ");
        }

        else if (option_val == 4)
        {
            break;
        }

        else
        {
            printf_tiny("\n\rInvalid option chosen");
        }
    }
}

void alaramset3()
{
    while (1)
    {
        /* Accept Alarm 1 value */
        printf_tiny("\n\n\n\r*********************************************************");
        printf_tiny("\n\rAlarm 3 operations");
        printf_tiny("\n\r*********************************************************");
        printf_tiny("\n\r1. Edit Alarm 3: (mm:ss:s)");
        printf_tiny("\n\r2. Enable Alarm");
        printf_tiny("\n\r3. Disable Alarm");
        printf_tiny("\n\r4. Back to Clock menu");
        printf_tiny("\n\r*********************************************************");

        /* Accept user choice */
        printf_tiny("\n\rEnter you choice: (1-4)");
        l=getchar();

        option_val = ascii_to_hex(l);

        if (option_val == 1)
        {
            if (alarm_set3[0] == 0)
            {
                lcd_gotoaddr(0x19);
                lcd_putch(((alarm_minute3[0] / 10) + 0x30));
                lcd_putch(((alarm_minute3[0] % 10) + 0x30));
                lcd_putch(':');
                lcd_putch(((alarm_sec3[0]/ 10) + 0x30));
                lcd_putch(((alarm_sec3[0] % 10) + 0x30));
                lcd_putch(':');
                lcd_putch((alarm_one_tenth3[0] + 0x30));

                /* Accept minutes */
                while (1)
                {
                    printf_tiny("\n\rEnter minute:(Range 0 - 59)\t");
                    gets(temp_alarm3);
                    alarm_minute3[0] = atoi(temp_alarm3);
                    break;
                }

                while (1)
                {
                    /* Accept seconds */
                    printf_tiny("\n\rEnter seconds:\t");
                    gets(temp_alarm3);
                    alarm_sec3[0] = atoi(temp_alarm3);

                    if (!((alarm_sec3[0] >= 0) && (alarm_sec3[0] <= 59)))
                    {
                        printf_tiny("\n\rEntered value not within range.. Please try again..");
                        continue;
                    }

                    break;
                }
                alarm_one_tenth3[0] = 0;
                lcd_gotoaddr(0x49);

                lcd_putch(((alarm_minute3[0] / 10) + 0x30));
                lcd_putch(((alarm_minute3[0] % 10) + 0x30));
                lcd_putch(':');
                lcd_putch(((alarm_sec3[0]/ 10) + 0x30));
                lcd_putch(((alarm_sec3[0] % 10) + 0x30));
                lcd_putch(':');
                ((alarm_one_tenth3[0] + 0x30));

                /* Calculate alarm_one_tenth_sec */
                alarm_one_tenth_sec3[0] = (alarm_minute3[0] * 60 * 10) + (alarm_sec3[0] * 10);
            }

            else
            {
                printf_tiny("Please disable the alarm to edit..");
            }
        }

        else if (option_val == 2)
        {
            alarm_set3[0] = 1;
        }

        else if (option_val == 3)
        {
            alarm_set3[0] = 0;
            lcd_gotoaddr(0x10);
            lcd_putstr("                ");
        }

        else if (option_val == 4)
        {
            break;
        }

        else
        {
            printf_tiny("\n\rInvalid option chosen");
        }
    }
}

void reset() //Function to reset the timer
{
    printf_tiny("\n\Reset Timer\n\r");
    minute=0; sec=0; one_tenth_sec = 0; one_tenth=0;
}


void stop() //Function to stop/pause the timer
{
    printf_tiny("\n\Timer Off \n\r");
    TR0=0;
}

void start() //Function to stop/pause the timer
{
    printf_tiny("\n\Timer on \n\r");
    TL0=0x4B;
    TH0=0xFD;
    TR0=1;
}

//MAIN CODE
void chara()
{
    uint8_t choice;
    //menu functions
    printf_tiny("\n\r***************************MENU******************************\n\r");
    printf_tiny("\n\rEnter 1 for a demo of the LCD functions\n\r");
    printf_tiny("\n\rEnter 2 for writing a byte into the EEPROM\n\r");
    printf_tiny("\n\rEnter 3 for reading a byte from the EEPROM\n\r");
    printf_tiny("\n\rEnter 4 for LCD display with EEPROM address and contents\n\r");
    printf_tiny("\n\rEnter 5 to clear the LCD screen\n\r");
    printf_tiny("\n\rEnter 6 for Hex Dump\n\r");
    printf_tiny("\n\rEnter 7 for DDRAM Dump\n\r");
    printf_tiny("\n\rEnter 8 for CGRAM Dump\n\r");
    printf_tiny("\n\rEnter 9 for NEW LCD CODE\n\r");
    printf_tiny("\n\rEnter A to print a custom LCD character\n\r");
    printf_tiny("\n\rEnter B to print logo on LCD screen\n\r");
    printf_tiny("\n\rEnter C to implement I/O Expander\n\r");
    printf_tiny("\n\rEnter D to print the current pin status\n\r");
    printf_tiny("\n\rEnter E to implement Watchdog Timer\n\r");
    printf_tiny("\n\rEnter F to implement hang condition\n\r");
    printf_tiny("\n\rEnter G to implement EEPROM eerest\n\r");
    printf_tiny("\n\rEnter H to reset the timer\n\r");
    printf_tiny("\n\rEnter I to start the timer\n\r");
    printf_tiny("\n\rEnter J to stop the timer\n\r");
    printf_tiny("\n\rEnter K for alarm1\n\r");
    printf_tiny("\n\rEnter L for alarm2\n\r");
    printf_tiny("\n\rEnter M for alarm3\n\r");

    while(1)
    {
        if(wtd_flag == 1)
            wtd_reset();
        printf_tiny("\n\r*********************************************************\n\r");
        printf_tiny("\n\rSelect an option from menu\n\r");
        choice=getchar();
        putchar(choice);

        switch(choice)  //switch case to access different menu options
        {
            case '1':lcd_code();
            break;

            case '2':write_byte_code();
            break;

            case '3':read_byte_code();
            break;

            case '4':lcd_display_code();
            break;

            case '5':lcd_command(0x01);
            break;

            case '6':HexDump();
            break;

            case '7':ddram_dump_code();
            break;

            case '8':cgram_dump_code();
            break;

            case '9':lcd_code_NEW();
            break;

            case 'A':lcd_build_char();
            break;

            case 'B':demo_custom_char();
            break;

            case 'C':io_expander_user();
            break;

            case 'D':print_pin_status();
            break;

            case 'E':wdt_user();
            break;

            case 'F':hang_condition();
            break;

            case 'G':eereset();
            break;

            case 'H':reset();
            break;

            case 'I':start();
            break;

            case 'J':stop();
            break;

            case 'K':alaramset1();
            break;

            case 'L':alaramset2();
            break;

            case 'M':alaramset3();
            break;

            default:printf_tiny("\n\rInvalid Input\n\r");
            break;
        }
    }
}

void main()
{
    IEN0 = 0x82;
    minute=0; sec=0; one_tenth_sec = 0; one_tenth=0;

 alarm_set1[3] = 0;
 alarm_set2[3] = 0;
 alarm_set3[3] = 0;

    ta = 0;
    l=0;
	lcd_init();
	timer0();
	chara();
    while(1);
}
