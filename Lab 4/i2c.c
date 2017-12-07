#include <at89c51ed2.h>
#include <mcs51reg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lcd.h"
#include "i2c.h"

//I2C delay function definition
void i2c_delay(uint8_t delay)
{
    while(delay!=0)
        delay--;
}
//I2C delay function definition
void i2c_clk()
{
    i2c_delay(0);
    SCL=1;  //pull SCL high
    i2c_delay(0);
    SCL=0;  //pull SCL low
}
//I2C start function definition
void i2c_start()    //I2C Start function definition
{
    SCL = 0;		//Pull SCL low

	SDA = 1;        //Pull SDA High
	i2c_delay(1);

	SCL = 1;		//Pull SCL high
	i2c_delay(1);

	SDA = 0;        //Now Pull SDA LOW, to generate the Start Condition
	i2c_delay(1);

	SCL = 0;        //Finally Clear the SCL to complete the cycle
}

//I2C stop function definition
void i2c_stop()
{
    SCL = 0;		//Pull SCL low

	SDA = 0;        //Pull SDA High
	i2c_delay(1);

	SCL = 1;		//Pull SCL high
	i2c_delay(1);

	SDA = 1;        //Now Pull SDA LOW, to generate the Start Condition
	i2c_delay(1);
}

//I2C read function definition
unsigned char i2c_read()
{
    unsigned char i=0;
    unsigned char datavalue=0x00;
    SDA=1;
    while(i<8)
    {
        lcd_delay(1);
        SCL=1;
        lcd_delay(1);
        datavalue=datavalue<<1;
        datavalue|=SDA;
        SCL=0;
        i++;
    }
    return datavalue;
}

//I2C write function definition
 void i2c_write(unsigned char datavalue)
{
    unsigned char i=0;

    while(i<8)
    {
        SDA=datavalue & 0x80;
        i2c_clk();
        datavalue=datavalue<<1;
        i++;
    }
    SDA=1;
}

//I2C ack function definition
 int i2c_ack()
{
    int a;

    SDA = 1;
    SCL = 1;
    a = SDA;
   // i2c_clk();
    SCL = 0;
    return a;
}

//I2C nack function definition
 void i2c_nack()
{
    SDA=0;
    SDA=1;//Test Code
    i2c_clk();
    SCL=1;
}
