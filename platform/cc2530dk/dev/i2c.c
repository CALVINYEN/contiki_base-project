#include "dev/i2c.h"

/*
* 开始信号
*/
void I2C_STARTING(void)
{
	SDA_OUT;
	SCL_OUT;
	SDA_1;
	SCL_1;
	clock_delay_usec(5);
	SDA_0;
	clock_delay_usec(5);
	SCL_0;
}

/*
* 结束信号
*/
void I2C_ENDING(void)
{
	SDA_OUT;
	SCL_OUT;
	SDA_0;
	SCL_1;
	clock_delay_usec(5);
	SDA_1;
	clock_delay_usec(5);
}

/*
* 等待应答信号
*/
unsigned char I2C_WAIT_ACK(void)
{
	unsigned int time_out = 0; 
	SDA_OUT;
	SCL_OUT;
	SDA_1; 
	//clock_delay_usec(5);
	SDA_IN;
	SCL_1;
	clock_delay_usec(5);
	while(SDA) {
		time_out++;
		clock_delay_usec(1);
		if (time_out > 50) {
			printf("wait ack time out. \n\r");
			I2C_ENDING();
			return 1;
		}
	}
	SCL_0;
	return 0;
}

/*
* 发出应答信号
*/
void I2C_ACK(void)
{
	SDA_OUT;
	SCL_OUT;
	SCL_0;
	SDA_0;
	clock_delay_usec(2);
	SCL_1;
	clock_delay_usec(5);
	SCL_0;
	clock_delay_usec(5);
}

/*
* 发出NACK信号
*/
void I2C_NACK(void)
{
	SDA_OUT;
	SCL_OUT;
	SCL_0;
	SDA_1;
	clock_delay_usec(2);
	SCL_1;
	clock_delay_usec(5);
	SCL_0;
	clock_delay_usec(5);
}

/*
* 发送一个位
*/
unsigned char I2C_SEND_BYTE(unsigned char byte)
{
	unsigned char i;
	
	SDA_OUT;
	SCL_OUT;
	SCL_0;
	for (i = 0; i < 8; i++) {
		SDA = (byte & 0x80) >> 7;
		byte <<= 1;
		SCL_1;
		clock_delay_usec(5);
		SCL_0;
		clock_delay_usec(5);
	}
	return I2C_WAIT_ACK();
}

/*
* 接受一个字节
*/
void I2C_RECEIVE_BYTE(unsigned char *res)
{
	unsigned char i;
	unsigned char recive = 0;
	SDA_IN;
	SCL_OUT;
	for(i = 0; i < 8; i++) {
		SCL_0;
		clock_delay_usec(5);
		SCL_1;
		clock_delay_usec(5);
		recive <<= 1;
		if(SDA) {
			recive++;
		}
	}
	
	*res = recive;
}

/*
* 写入指定设备 指定寄存器一个字节
*/
unsigned char I2C_WRITE_BYTE(unsigned char i2c_addr, unsigned char reg_addr, unsigned char data)
{
	unsigned char  res;
	
	I2C_STARTING();
	
	if((res = I2C_SEND_BYTE(i2c_addr))) {
		return res;
	}
	
	if((res = I2C_SEND_BYTE(reg_addr))) {
		return res;
	}

	if((res = I2C_SEND_BYTE(data))) {
		return res;
	}

	return 0;
}

/*
* 读取指定设备 指定寄存器的一个值。
*/
unsigned char I2C_READ_BYTE(unsigned char i2c_addr, unsigned char reg_addr, unsigned char *data)
{
	unsigned char res;
	I2C_STARTING();
	
	if((res = I2C_SEND_BYTE(i2c_addr))) {
		return res;
	}

	if((res = I2C_SEND_BYTE(reg_addr))) {
		return res;
	}

	I2C_STARTING();
	
	if((res = I2C_SEND_BYTE(i2c_addr + 1))) {
		return res;
	}

	I2C_RECEIVE_BYTE(data);
	
	I2C_NACK();
	I2C_ENDING();
	
	return res;
}