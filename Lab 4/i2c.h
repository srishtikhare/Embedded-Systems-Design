#ifndef I2C_H
#define I2C_H

#include <at89c51ed2.h>
#include <mcs51reg.h>
#include <stdio.h>
#include <stdlib.h>

//I2C Pins
#define SDA P1_3
#define SCL P1_7

void i2c_clk();
void i2c_delay(uint8_t delay);
void i2c_start();
void i2c_stop();
unsigned char i2c_read();
void i2c_write(unsigned char);
int i2c_ack();
void i2c_nack();

#endif
