#include "dev/mpu6050-sensor.h"
#include <stdio.h>
/*
* mpu6050初始化
*/
unsigned char mpu6050_init(void)
{
	unsigned char id;
	unsigned char res;
	
/*	res = I2C_READ_BYTE(SlaveAddress, WHO_AM_I, &id);
	if(res)	{
		return res;	//IIC總線錯誤
	}
	else {
		id &= 0x7e;//除去最高位最低位
		id >>= 1;
		if(id != 0x34) return 1;	//獲取到的芯片ID錯誤
	}
*/	
	printf("_____________________________________________________________mpu6050 init\n\r");
	I2C_WRITE_BYTE(SlaveAddress, PWR_MGMT_1, 0x80);
	I2C_WRITE_BYTE(SlaveAddress, SMPLRT_DIV, 0x07);
	I2C_WRITE_BYTE(SlaveAddress, CONFIG, 0x06);
	I2C_WRITE_BYTE(SlaveAddress, GYRO_CONFIG, 0x18);
	I2C_WRITE_BYTE(SlaveAddress, ACCEL_CONFIG, 0x01);
	printf("_______________________________________________________________mpu6050 init end\n\r");
}

/*
* 合成数据
*/
int getdate(unsigned char address)
{
	unsigned char hi, low;
	//mpu6050_init();
	I2C_READ_BYTE(SlaveAddress, address, &hi);
	I2C_READ_BYTE(SlaveAddress, address + 1, &low);
	printf("hi = %d, low = %d\n\r", hi, low);
	return (int)(((int)hi << 8) + low);
}