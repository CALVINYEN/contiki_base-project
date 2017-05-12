/*
*	clavinyen 20170510
*/

#include "dev/i2c.h"

void i2c_start(void)
{
	SDA_OUT;
	SCL_OUT;
	printf("start_P2DIR=%d\n\r", P2DIR);
	SDA = 1;
	SCL = 1;
	clock_delay_usec(5);
	SDA = 0;
	clock_delay_usec(5);
	SCL = 0;
}

void i2c_stop(void)
{
	SDA_OUT;
	SDA = 0;
	SCL = 1;
	clock_delay_usec(5);
	SDA = 1;
	clock_delay_usec(5);
}

void i2c_ack(unsigned char ack)
{
	SDA_OUT;
	SDA = ack;
	SCL = 1;
	clock_delay_usec(5);
	SCL = 0;
	clock_delay_usec(5);
}

unsigned char i2c_wait_ack(void)
{
	unsigned char ack = 0;
	SDA_IN;
	printf("in_P2DIR = %d\n\r", P2DIR);
	SCL = 1;
	clock_delay_usec(5);
	ack = SDA;
	SCL = 0;
	clock_delay_usec(5);
	printf("ack = %d\r\n", ack);
	return ack;
}

void i2c_send_byte(unsigned char byte)
{
	unsigned char i = 0;
	SDA_OUT;
	for(i = 0; i < 8; i++) {
		SDA = ((byte & 0x80) >> 7);
		printf("byte = %d\n\r", ((byte & 0x80) >> 7));
		SCL = 1;
		clock_delay_usec(5);
		SCL = 0;
		clock_delay_usec(5);
		byte <<= 1;
	}
	i2c_wait_ack();
}

void i2c_recive_byte(unsigned char *byte)
{
	unsigned char i = 0;
	*byte = 0;
	SDA_IN;
	for(i = 0; i < 8; i++) {
		*byte <<= 1;
		SCL = 1;
		clock_delay_usec(5);
		printf("SDA = %d\n\r", SDA);
		*byte |= SDA;
		SCL = 0;
		clock_delay_usec(5);
	}
}
/*
void i2c_write(unsigned char reg_addr)
{
	SCL_OUT();
	i2c_start();
	i2c_send_byte(SLAVE_ADDR);
	i2c_send_byte(reg_addr);
	i2c_stop();
}

void i2c_read(unsigned char *data)
{
	unsigned char i = 0;
	SCL_OUT();
	i2c_start();
	i2c_send_byte(SLAVE_ADDR + 1);
	i2c_recive_byte(data);
}
*/
