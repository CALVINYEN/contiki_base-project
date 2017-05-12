/*
* calvinyen 20170510
*/

#include "dev/bh1750fvi.h"

void bh1750fvi_init(void)
{
	i2c_start();
	i2c_send_byte(SLAVE_ADDR);
	i2c_send_byte(0x01);
	i2c_stop();
}

void set_meansure_mode(unsigned char mode)
{
	i2c_start();
	i2c_send_byte(SLAVE_ADDR);
	i2c_send_byte(mode);
	i2c_stop();
}

void read_meansure_value(unsigned char *hi, unsigned char *low)
{
	int i = 0;
	bh1750fvi_init();
	set_meansure_mode(0x10);
	while(i < 1000) {
		i++;
		clock_delay_usec(180);
	}
	i = 0;
	i2c_start();
	i2c_send_byte(SLAVE_ADDR + 1);
	i2c_recive_byte(hi);
	i2c_ack(0);
	i2c_recive_byte(low);
	i2c_ack(1);
	i2c_stop();
}