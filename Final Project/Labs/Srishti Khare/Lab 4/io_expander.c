#include <at89c51ed2.h>
#include <mcs51reg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lcd.h"
#include "i2c.h"
#include "io_expander.h"

void PCF8574_write_byte(unsigned char address)
{
    i2c_start();               // Start i2c communication
   	i2c_write(device_ID_read);	   // connect to AT2404 by sending its ID on I2c Bus
	while(i2c_ack());
   	i2c_write(address); // Select the Specified EEPROM address of AT2404
	while(i2c_ack());
    i2c_stop();          	   // Stop i2c communication after Writing the data
	lcd_delay(5);               // Write operation takes max 5ms, refer At2404 datasheet
}

unsigned char PCF8574_read_byte()
{
    unsigned char data_value;
    i2c_start();               // Start i2c communication
   	i2c_write(device_ID_write);	   // connect to eeprom by sending its ID via I2C
	while(i2c_ack());
	data_value = i2c_read();  // Read the data from specified address
	i2c_nack();
    i2c_stop(); // Stop i2c communication after Reading the data
	lcd_delay(1);
    return data_value;
}
