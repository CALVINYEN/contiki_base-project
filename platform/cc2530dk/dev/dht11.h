
#ifndef DHT11_H_
#define DHT11_H_

#include "cc253x.h"
#include "sys/clock.h"
#include <stdio.h>



#define DATA            P0_7                //����IO��

#define SET_OUT()   P0DIR |=  0x80  //����IO����,out����IO����Ϊ���
#define SET_IN()    P0DIR &= ~0x80  //����IO����,in�豸IO����Ϊ����

extern unsigned char dht11_read(unsigned char *temp_integer, unsigned char *humidity_integer, unsigned char *temp_decimal, unsigned char *humidity_decimal);

#endif