/*
*	calvinyen 20170510
*/

#ifndef I2C_H_
#define I2C_H_

#include "cc253x.h"
#include "sys/clock.h"
#include <stdio.h>

#define SDA P2_1
#define SCL P2_2

#define SDA_OUT (P2DIR |= 0x02)
#define SDA_IN (P2DIR &= ~0x02)
#define SCL_OUT (P2DIR |= 0x04)

extern void i2c_start(void);
extern void i2c_stop(void);
extern void i2c_ack(unsigned char ack);
extern unsigned char i2c_wait_ack(void);
extern void i2c_send_byte(unsigned char byte);
extern void i2c_recive_byte(unsigned char *byte);

#endif