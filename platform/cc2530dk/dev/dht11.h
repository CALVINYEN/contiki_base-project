
#ifndef DHT11_H_
#define DHT11_H_

#include "cc253x.h"
#include "sys/clock.h"
#include <stdio.h>



#define DATA            P1_1                //数据IO口

#define SET_OUT()   P1DIR |=  0x02  //设置IO方向,out设置IO方向为输出
#define SET_IN()    P1DIR &= ~0x02  //设置IO方向,in设备IO方向为输入

extern unsigned char dht11_read(unsigned char *temp_integer, unsigned char *humidity_integer, unsigned char *temp_decimal, unsigned char *humidity_decimal);

#endif