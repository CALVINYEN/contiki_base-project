#include "contiki.h"
#include "contiki-conf.h"
#include <stdio.h>
#include "dev/adc-sensor.h"
#include "sys/clock.h"
PROCESS(sensors_test_process, "Sensor Test Process");

AUTOSTART_PROCESSES(&sensors_test_process);
/*---------------------------------------------------------------------------*/

void mma7260qt_init(void)
{
	P1DIR |= 0x38;
	/* Sensitivity: 800 mV/g*/
	P1_3 = 0;
	P1_4 = 0;
	/* sleep mode setting */
	P1_5 = 1;
}



PROCESS_THREAD(sensors_test_process, ev, data)
{

  /* Sensor Values */
  static int rv;
  static struct sensors_sensor *sensor;
  static float sane = 0;
  static int dec;
  static float frac;
  static int i;
  static unsigned char fall_flag;	
  PROCESS_BEGIN();

	
  while(1) {
	mma7260qt_init();
    /*
     * Request some ADC conversions
     * Return value -1 means sensor not available or turned off in conf
     */
    sensor = sensors_find(ADC_SENSOR);
    if(sensor) {

	  rv = sensor->value(ADC_SENSOR_TYPE_AIN4);
      if(rv != -1) {
        sane = rv * 3.3 / 2047;
        dec = sane;
        frac = sane - dec;
        //printf("X轴=%d.%02u V (%d)\n", dec, (unsigned int)(frac*100), rv);
      }
	  
	   rv = sensor->value(ADC_SENSOR_TYPE_AIN5);
      if(rv != -1) {
        sane = rv * 3.3 / 2047;
        dec = sane;
        frac = sane - dec;
        //printf("y轴=%d.%02u V (%d)\n", dec, (unsigned int)(frac*100), rv);
      }
	  
	   rv = sensor->value(ADC_SENSOR_TYPE_AIN6);
      if(rv != -1) {
        sane = rv * 3.5 / 2047;
        dec = sane;
        frac = sane - dec;
        //printf("z轴=%d.%02u V (%d)\n", dec, (unsigned int)(frac*100), rv);
      }
	  	  if((unsigned int)(frac*100) > 60 && fall_flag == 0) {
		  fall_flag = 1;
			printf("AT+CMGF=1\r");
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			printf("AT+CSCS=\"GSM\"\r");
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			printf("AT+CMGS=\"661825\"\r");
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			printf("Warning! Someone fall down!%c", 0x1A);
	  }else if(((unsigned int)(frac*100)) < 70) {
		  fall_flag = 0;
	  }else {
		  ;
	  }
		for (i = 0;i < 2000; i++) {
			clock_delay_usec(1000);
		}
    }
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
