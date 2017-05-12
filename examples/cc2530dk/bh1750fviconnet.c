/*
*	Author：calvin yen
*	Date: 20170510
*/

#include <stdio.h>
#include "contiki.h"
#include "dev/bh1750fvi.h"

PROCESS(get_bh1750fvi_val, "get bh1750fvi value");
AUTOSTART_PROCESSES(&get_bh1750fvi_val);

unsigned char hi = 0, low = 0;

/*
*	主进程
*/
PROCESS_THREAD(get_bh1750fvi_val, ev, data)
{
	PROCESS_BEGIN();
	
	while(1) {
		int i = 0;
		printf("_debug\n\r");
		read_meansure_value(&hi, &low);
		printf("hi = %d, low = %d\n\r", hi, low);
		for (i = 0; i < 100; i++) {
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

	}
	
	PROCESS_END();
}