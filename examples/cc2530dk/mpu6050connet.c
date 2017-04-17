/*
*	Author：calvin yen
*	Date: 20170412
*/

#include <stdio.h>
#include "contiki.h"
#include "dev/mpu6050-sensor.h"

PROCESS(get_mpu6050_val, "get mpu6050 value");
AUTOSTART_PROCESSES(&get_mpu6050_val);

/*
*	主进程
*/
PROCESS_THREAD(get_mpu6050_val, ev, data)
{
	PROCESS_BEGIN();
	printf("init\n");
	mpu6050_init();
	while(1) {
		int i = 50000;
		while(i--);
		printf("X轴加速度: %d\n\r", getdate(ACCEL_XOUT_H));	//显示X轴加速度
		printf("Y轴加速度: %d\n\r", getdate(ACCEL_YOUT_H));	//显示Y轴加速度
		printf("Z轴加速度: %d\n\r", getdate(ACCEL_ZOUT_H));	//显示Z轴加速度
		printf("X轴角速度: %d\n\r", getdate(GYRO_XOUT_H));	//显示X轴角速度
		printf("Y轴角速度: %d\n\r", getdate(GYRO_YOUT_H));	//显示Y轴角速度
		printf("Z轴角速度: %d\n\r", getdate(GYRO_ZOUT_H));	//显示Z轴角速度
	}
	PROCESS_END();
}