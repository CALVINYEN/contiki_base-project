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
	SCL_1;
	SDA_0;
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
	//SDA_OUT;
	//SCL_OUT;
	//SDA_1; 
	//clock_delay_usec(5);
	//SCL_1; //clock_delay_usec(5);
	SDA_IN;
	while(SDA) {
		time_out++;
		if (time_out > 5) {
			printf("wait ack time out. \n\r");
			//I2C_ENDING();
			return 1;
		}
		clock_delay_usec(5);
	}
	SCL_1;
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
	clock_delay_usec(5);
	SCL_1;
	clock_delay_usec(5);
	SCL_0;
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
	clock_delay_usec(5);
	SCL_1;
	clock_delay_usec(5);
	SCL_0;
}

/*
* 发送一个字节
*/
void I2C_SEND_BYTE(unsigned char byte)
{
	unsigned char i;
	
	SDA_OUT;
	SCL_OUT;
	
	for (i = 0; i < 8; i++) {
		SCL_1;
		clock_delay_usec(5);
		SDA = (byte & 0x80) >> 7;
		//SCL_0;
		//clock_delay_usec(5);
		byte <<= 1;
		SCL_0;
		clock_delay_usec(5);
	}
	SCL_0;
}

/*
* 接受一个字节
*/
unsigned char I2C_RECEIVE_BYTE(unsigned char ack)
{
	unsigned char i;
	unsigned char recive = 0;
	SDA_IN;
	SCL_OUT;
	for(i = 0; i < 8; i++) {
		SCL_1;
		clock_delay_usec(5);
		recive <<= 1;
		if(SDA) {
			recive++;
		}
		SCL_0;
		clock_delay_usec(5);
	}
	if(ack) {
		I2C_ACK();
	}
	else {
		I2C_NACK();
	}
	return recive;
}

/*
* 写入指定设备 指定寄存器一个字节
*/
unsigned char I2C_WRITE_BYTE(unsigned char i2c_addr, unsigned char reg_addr, unsigned char date)
{
	unsigned char  count = 0;
	
	I2C_STARTING();
	do {
		if (count > 0) {
			printf("time out: %d\n\r", __LINE__);
			return 1;
		}
		I2C_SEND_BYTE(i2c_addr);
		count++;
	} while(I2C_WAIT_ACK());
	count = 0;

	//I2C_STARTING();
	do {
		if (count > 0) {
			printf("time out: %d\n\r", __LINE__);
			return 1;
		}
		I2C_SEND_BYTE(reg_addr);
		count++;
	} while(I2C_WAIT_ACK());
	count = 0;

	//I2C_STARTING();
	do {
		if (count > 0) {
			printf("time out: %d\n\r", __LINE__);
			return 1;
		}
		I2C_SEND_BYTE(date);
		count++;
	} while(I2C_WAIT_ACK());
	
	I2C_ENDING();
	
	return 1;
}

/*
* 读取指定设备 指定寄存器的一个值。
*/
unsigned char I2C_READ_BYTE(unsigned char i2c_addr, unsigned char reg_addr)
{
	unsigned char count = 0;
	unsigned char res;
	I2C_STARTING();
	do {
		if (count > 0) {
			printf("time out: %d\n\r", __LINE__);
			return 1;
		}
		I2C_SEND_BYTE(i2c_addr);
		count++;
	} while(I2C_WAIT_ACK());
	count = 0;

	//I2C_STARTING();
	do {
		if (count > 0) {
			printf("time out: %d\n\r", __LINE__);
			return 1;
		}
		I2C_SEND_BYTE(reg_addr);
		count++;
	} while(I2C_WAIT_ACK());
	count = 0;

	I2C_STARTING();
	do {
		if (count > 0) {
			printf("time out: %d\n\r", __LINE__);
			return 1;
		}
		I2C_SEND_BYTE(i2c_addr + 1);
		count++;
	} while(I2C_WAIT_ACK());
	count = 0;

	res = I2C_RECEIVE_BYTE(0);
	I2C_ENDING();
	
	return res;
}