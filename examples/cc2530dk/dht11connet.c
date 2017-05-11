/*
*	Author：calvin yen
*	Date: 20170412
*/

#include <stdio.h>
#include "contiki.h"
#include "dev/dht11.h"

PROCESS(get_dht11_val, "get dht11 value");
AUTOSTART_PROCESSES(&get_dht11_val);

unsigned char temp_integer = 0, humidity_integer = 0, temp_decimal = 0, humidity_decimal = 0;

/*
*	主进程
*/
PROCESS_THREAD(get_dht11_val, ev, data)
{
	PROCESS_BEGIN();
	
	while(1) {
		printf("dht11_debug\n\r");
		dht11_read(&temp_integer, &humidity_integer, &temp_decimal, &humidity_decimal);
		printf("temp_integer = %d, humidity_integer = %d, temp_decimal = %d, humidity_decimal = %d\n\r",temp_integer, humidity_integer, temp_decimal, humidity_decimal);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
		clock_delay_usec(70000);
	}
	
	PROCESS_END();
}