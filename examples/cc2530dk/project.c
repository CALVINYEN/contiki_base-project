#include <stdio.h>
#include <string.h>

#include "contiki.h"
#include "contiki-conf.h"
#include "contiki-lib.h"
#include "net/uip-debug.h"
#include "contiki-net.h"

#include "dev/adc-sensor.h"
#include "dev/dht11.h"



/*---------------------------------------------------------------------------*/
PROCESS(project_process, "project process");
AUTOSTART_PROCESSES(&project_process);

unsigned char temp_integer = 0, humidity_integer = 0, temp_decimal = 0, humidity_decimal = 0;

static int rv;
static float sane = 0;
static int dec;
static float frac;
static char weather_type[10] ;

static unsigned char irrigate_flag = 0;
static struct sensors_sensor *sensor;
/*
#define LOCAL_CONN_PORT 3001
static struct uip_udp_conn *l_conn;
#define GLOBAL_CONN_PORT 3002
static struct uip_udp_conn *g_conn;

void tcpip_handler(void)
{
	struct uip_udp_conn *this_conn;
	this_conn = g_conn;
	uip_udp_packet_send(this_conn, "hello", 6);
}

void udp_client_process(void)
{
	uip_ipaddr_t ipaddr;

	uip_ip6addr(&ipaddr, 0xfe80, 0, 0, 0, 0x0212, 0x4b00, 0x0ff0, 0x5c31);
	/* new connection with remote host *//*
	l_conn = udp_new(&ipaddr, UIP_HTONS(3000), NULL);
	if(!l_conn) {
		//PRINTF("udp_new l_conn error.\n");
	}
	udp_bind(l_conn, UIP_HTONS(LOCAL_CONN_PORT));

	//PRINTF("Link-Local connection with ");
	//PRINT6ADDR(&l_conn->ripaddr);
	//PRINTF(" local/remote port %u/%u\n",
	//UIP_HTONS(l_conn->lport), UIP_HTONS(l_conn->rport));

	uip_ip6addr(&ipaddr, 0xaaaa, 0, 0, 0, 0x0212, 0x4b00, 0x0ff0, 0x5c31);
	g_conn = udp_new(&ipaddr, UIP_HTONS(3000), NULL);
	if(!g_conn) {
    //PRINTF("udp_new g_conn error.\n");
	}
	udp_bind(g_conn, UIP_HTONS(GLOBAL_CONN_PORT));

	//PRINTF("Global connection with ");
	//PRINT6ADDR(&g_conn->ripaddr);
	//PRINTF(" local/remote port %u/%u\n",
    //     UIP_HTONS(g_conn->lport), UIP_HTONS(g_conn->rport));
}

*/
PROCESS_THREAD(project_process, ev, data)
{

	PROCESS_BEGIN();
	
	while(1) {

		/*温湿度采集*/
		dht11_read(&temp_integer, &humidity_integer, &temp_decimal, &humidity_decimal);

		/*光照采集*/
		sensor = sensors_find(ADC_SENSOR);
		P0DIR &= ~(0x10); //端口P0_4
		rv = sensor->value(ADC_SENSOR_TYPE_AIN4);
		/* 判断光照情况 */
		if(rv != -1) {
			sane = rv * 3.3 / 2047;
			dec = sane;
			frac = sane - dec;
			if(dec > 0) {
				strcpy(weather_type, "Night");//夜晚
			}else if((unsigned int)(frac*100) < 56) {
				strcpy(weather_type, "Fine");//晴天
			}else if((unsigned int)(frac*100) < 82) {
				strcpy(weather_type, "Cloudy");//阴天
			}else {
				strcpy(weather_type, "Rainy");//阴雨
			}
		}

		/*土壤湿度采集*/
		P0DIR &= ~(0x40);// 端口P0_6
		rv = sensor->value(ADC_SENSOR_TYPE_AIN6);
		if(rv != -1) {
			sane = rv * 3.3 / 2047;
		}

		/*判断是否需要灌溉*/
		P0DIR &= ~0x20; //端口P0_5
		if(P0_5 == 1 && irrigate_flag == 0) {
			irrigate_flag = 1;
			/*继电器控制，高电平触发，端口P1_7*/
			P1DIR |= 0x80;
			P1_7 = 1;
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
			printf("AT+CMGS=\"615217\"\r");
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			clock_delay_usec(10000);
			printf("Temperatura: %d℃, Humidity: %d, Weather: %s%c", temp_integer, humidity_integer, weather_type, 0x1A);
		}else if(P0_5 == 0) {
			irrigate_flag = 0;
			P1DIR |= 0x80;
			P1_7 = 0;
		}else {
			;
		}
	}
	PROCESS_END();
}