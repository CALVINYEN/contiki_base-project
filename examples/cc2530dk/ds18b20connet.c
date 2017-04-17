/*
*	Author：calvin yen
*	Date: 20170412
*/

#include <stdio.h>
#include "contiki.h"
#include "dev/ds18b20.h"

PROCESS(get_ds18b20_val, "get ds18b20 value");
AUTOSTART_PROCESSES(&get_ds18b20_val);


unsigned char integer, decimal;

/*
*	主进程
*/
PROCESS_THREAD(get_ds18b20_val, ev, data)
{
	PROCESS_BEGIN();
	
	DS18B20_SendConvert();
	while(1) {
		DS18B20_SendConvert();
		DS18B20_GetTem(&integer, &decimal);
		printf("temp: %d.%d\n\r", integer, decimal);
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