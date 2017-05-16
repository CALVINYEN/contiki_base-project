#include "contiki.h"
#include "dev/dht11.h"
#include "contiki-conf.h"
#include "dev/adc-sensor.h"
#include <stdio.h> 
/*---------------------------------------------------------------------------*/
static struct etimer et_process1;
static struct etimer et_process2;

unsigned char temp_integer = 0, humidity_integer = 0, temp_decimal = 0, humidity_decimal = 0;

static int rv;
static float sane = 0;
static int dec;
static float frac;
static struct sensors_sensor *sensor;
/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process, "Hello world process");
PROCESS(blink_process, "LED blink process");
AUTOSTART_PROCESSES(&hello_world_process, &blink_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hello_world_process, ev, data)
{
  PROCESS_BEGIN();

  etimer_set(&et_process1, CLOCK_SECOND * 4);

  while(1) {
    PROCESS_WAIT_EVENT();

    if(ev == PROCESS_EVENT_TIMER) {
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

      etimer_reset(&et_process1);
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(blink_process, ev, data)
{
  PROCESS_BEGIN();


  while(1) {
    etimer_set(&et_process2, CLOCK_SECOND);

    PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);

    printf("Blink... (state)\n");
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
