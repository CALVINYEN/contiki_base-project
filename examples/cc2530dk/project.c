#include <stdio.h>
#include "contiki.h"
#include "dev/dht11.h"
#include "contiki-conf.h"
#include "dev/adc-sensor.h"



/*---------------------------------------------------------------------------*/
PROCESS(project_process, "project process");
PROCESS(send_message, "send message to phone");
AUTOSTART_PROCESSES(&project_process, &send_message);

unsigned char temp_integer = 0, humidity_integer = 0, temp_decimal = 0, humidity_decimal = 0;

static int rv;
static float sane = 0;
static int dec;
static float frac;
static struct sensors_sensor *sensor;

static struct etimer et_data_meansure;
static struct etimer et_test;
PROCESS_THREAD(project_process, ev, data)
{

	PROCESS_BEGIN();
	
	etimer_set(&et_data_meansure, CLOCK_SECOND * 4);
	
	while(1) {
		printf("process1\n\r");
		PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);
		/*温湿度采集*/
		dht11_read(&temp_integer, &humidity_integer, &temp_decimal, &humidity_decimal);
		printf("temp_integer = %d, humidity_integer = %d, temp_decimal = %d, humidity_decimal = %d\n\r",temp_integer, humidity_integer, temp_decimal, humidity_decimal);
		
		/*光照采集*/
		sensor = sensors_find(ADC_SENSOR);
		P0DIR &= ~(0x10); //端口P0_4
		rv = sensor->value(ADC_SENSOR_TYPE_AIN4);
		if(rv != -1) {
			sane = rv * 1.25 / 2047;
			dec = sane;
			frac = sane - dec;
			printf("光照=%d.%02u V(%d)\n\r", dec, (unsigned int)(frac*100), rv);
		}
		
		/*土壤湿度采集*/
		P0DIR &= ~(0x40);// 端口P0_6
		rv = sensor->value(ADC_SENSOR_TYPE_AIN6);
		if(rv != -1) {
			sane = rv * 1.25 / 2047;
			dec = sane;
			frac = sane - dec;
			printf("土壤湿度=%d.%02u V(%d)\n\r", dec, (unsigned int)(frac*100), rv);
		}
			
		etimer_reset(&et_data_meansure);
	}
	printf("process1 end\n\r");
	PROCESS_END();
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(send_message, ev, data)
{
	PROCESS_BEGIN();
	etimer_set(&et_test, CLOCK_SECOND * 5);
	while(1) {
		PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);
		printf("process2\n\r");
		etimer_reset(&et_test);
	}
	
	
	PROCESS_END();
}