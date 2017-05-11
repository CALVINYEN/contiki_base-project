#include "dht11.h"



unsigned char dht11_read(unsigned char *temp_integer, unsigned char *humidity_integer, unsigned char *temp_decimal, unsigned char *humidity_decimal)
{
	int i = 0;
	unsigned char crc = 0;
	for(i = 0; i < 1000; i++) {
		clock_delay_usec(1500);
	}
	
	SET_OUT();
	DATA = 0;
	clock_delay_usec(15000);
	DATA = 1;
	SET_IN();
	clock_delay_usec(30);
	
	while(DATA == 1) {
		;
	}
	while(DATA == 0) {
		;
	}
	while(DATA == 1) {
		;
	}
	
	/*读湿度的整数部分*/
	for(i = 0; i < 8; i++) {
		while(DATA == 0) {
			;
		}
		clock_delay_usec(35);
		*humidity_integer <<= 1;
		if(DATA == 1) {
			*humidity_integer += 1;
			clock_delay_usec(40);
		}
	}
	/*读湿度的小数部分*/
	for(i = 0; i < 8; i++) {
		while(DATA == 0) {
			;
		}
		clock_delay_usec(35);
		*humidity_decimal <<= 1;
		if(DATA == 1) {
			*humidity_decimal += 1;
			clock_delay_usec(40);
		}
	}
	/*读温度的整数部分*/
	for(i = 0; i < 8; i++) {
		while(DATA == 0) {
			;
		}
		clock_delay_usec(35);
		*temp_integer <<= 1;
		if(DATA == 1) {
			*temp_integer += 1;
			clock_delay_usec(40);
		}
	}
	/*读温度的小数部分*/
	for(i = 0; i < 8; i++) {
		while(DATA == 0) {
			;
		}
		clock_delay_usec(35);
		*temp_decimal <<= 1;
		if(DATA == 1) {
			*temp_decimal += 1;
			clock_delay_usec(40);
		}
	}
	/*读校验部分*/
	for(i = 0; i < 8; i++) {
		while(DATA == 0) {
			;
		}
		clock_delay_usec(35);
		crc <<= 1;
		if(DATA == 1) {
			crc += 1;
			clock_delay_usec(40);
		}
	}
	
	return 0;
	
}