
/* 
 * File:   i2c.h
 * Author: Le Hai Chau
 * Comments:
 * Revision history: v2.
 */

#define FCY 2000000UL
#define FSCL 400000

#include<p30F6010A.h>
#include<xc.h>
#include<stdio.h>
#include<libpic30.h>

void UART_Init();
void I2C_Stop();
void I2C_Stop();
void I2C_Repeated_Start();
int I2C_Read();
void I2C_Write(int);
void I2C_Init();
void I2C_ACK();
void I2C_NACK();