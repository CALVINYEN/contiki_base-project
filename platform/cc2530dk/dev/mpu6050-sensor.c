#include "dev/mpu6050-sensor.h"
#include <stdio.h>
/*
* mpu6050初始化
*/
void mpu6050_init(void)
{
	I2C_WRITE_BYTE(SlaveAddress, PWR_MGMT_1, 0x00);
	I2C_WRITE_BYTE(SlaveAddress, SMPLRT_DIV, 0x07);
	I2C_WRITE_BYTE(SlaveAddress, CONFIG, 0x06);
	I2C_WRITE_BYTE(SlaveAddress, GYRO_CONFIG, 0x18);
	I2C_WRITE_BYTE(SlaveAddress, ACCEL_CONFIG, 0x01);
}

/*
* 合成数据
*/
int getdate(unsigned char address)
{
	unsigned char hi, low;
	mpu6050_init();
	hi = I2C_READ_BYTE(SlaveAddress, address);
	mpu6050_init();
	low = I2C_READ_BYTE(SlaveAddress, address + 1);
	printf("hi = %d, low = %d\n\r", hi, low);
	return ((hi << 8) + low);
}