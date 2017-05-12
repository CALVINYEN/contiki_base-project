/*
*	clavinyen 20170510
*/

#ifndef BH1750FVI_H_
#define BH1750FVI_H_

#include "dev/i2c.h"
#define SLAVE_ADDR   0x46

extern void read_meansure_value(unsigned char *hi, unsigned char *low);

#endif
