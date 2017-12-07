#include <at89c51ed2.h>
#include <mcs51reg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lcd.h"
#include "i2c.h"
#include "eeprom.h"
#include "user_input.h"

//WRITE BYTE CODE
 void eeprom_write_byte(unsigned char address, unsigned char datavalue, unsigned char PageNo)
{
    i2c_start();               // Start i2c communication
   	i2c_write(DEV_ID|(PageNo<<1));	   // connect to AT2404 by sending its ID on I2c Bus
	while(i2c_ack());
   	i2c_write(address); // Select the Specified EEPROM address of AT2404
	while(i2c_ack());
   	i2c_write(datavalue);    // Write the data at specified address
	while(i2c_ack());
    i2c_stop();           	   // Stop i2c communication after Writing the data
	lcd_delay(5);               // Write operation takes max 5ms, refer At2404 datasheet
}

//READ BYTE CODE
unsigned char eeprom_read_byte(unsigned char address,unsigned char PageNo)
{
    unsigned char data_value;
    i2c_start();               // Start i2c communication
   	i2c_write(DEV_ID|(PageNo<<1));	   // connect to eeprom by sending its ID via I2C
	while(i2c_ack());
   	i2c_write(address); // Select the Specified EEPROM address
    while(i2c_ack());
    i2c_start();    // Start i2c communication
    i2c_write(0xA1|(PageNo<<1));    // connect to AT2404(read) by sending its ID on I2c Bus
    while(i2c_ack());
	data_value = i2c_read();  // Read the data from specified address
	i2c_nack();
    i2c_stop(); // Stop i2c communication after Reading the data
	lcd_delay(1);
  return data_value;
}

void eereset()
{
    unsigned char i=0;
    i2c_start();
    while(i<9)
    {
        SDA=1;
        i2c_clk();
        i++;
    }
    i2c_start();;
    i2c_stop();

    printf_tiny("\n\rEEPROM reset successful\n\r");
}

