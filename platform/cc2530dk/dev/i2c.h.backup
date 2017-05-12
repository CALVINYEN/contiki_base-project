#ifndef I2C_H_
#define I2C_H_

#include "cc253x.h"
#include <stdio.h>    /* For debug */
#include "sys/clock.h"    /* For temporisation */

/*---------------------------------------------------------------------------*/
/** \name I2C PIN
 * @{
 */
#define SDA P1_7
#define SCL P1_5

#define MASK(n)      (1 << (n))
#define st(x)      do { x } while (0)

#define  SDA_DIR  P0DIR
#define  SDA_MASK   MASK(7)

#define  SCL_DIR  P0DIR
#define  SCL_MASK   MASK(5)

#define  SDA_IN  st((SDA_DIR) &= ~(SDA_MASK);)
#define  SDA_OUT st((SDA_DIR) |= (SDA_MASK);)
#define  SCL_IN  st((SCL_DIR) &= ~(SCL_MASK);)
#define  SCL_OUT st((SCL_DIR) |= (SCL_MASK);)

#define  SDA_1   SDA = 1//st(SDA_OUT; SDA=1;)
#define  SDA_0   SDA = 0//st(SDA_OUT; SDA=0;)
#define  SCL_1   SCL = 1//st(SCL_OUT; SCL=1;)
#define  SCL_0   SCL = 0//st(SCL_OUT; SCL=0;)

/* 写入指定设备 指定寄存器一个字节 */
extern unsigned char I2C_WRITE_BYTE(unsigned char i2c_addr, unsigned char reg_addr, unsigned char date);

/* 读取指定设备 指定寄存器的一个值。 */
extern unsigned char I2C_READ_BYTE(unsigned char i2c_addr, unsigned char reg_addr, unsigned char *data);
#endif