#ifndef	_LED_H
#define	_LED_H

#include "stm32f10x.h"
#include "pin_map.h"

#define LED_RUN			PAout(4)
#define LED_WIFI		PAout(5)
#define LED_COM1		PAout(7)
#define LED_COM2		PAout(6)

#define LED_RUN_ON		LED_RUN = 0; 
#define LED_RUN_OFF		LED_RUN = 1;
#define LED_WIFI_ON		LED_WIFI = 0; 
#define LED_WIFI_OFF	LED_WIFI = 1;
#define LED_COM1_ON		LED_COM1 = 0;
#define LED_COM1_OFF	LED_COM1 = 1;
#define LED_COM2_ON		LED_COM2 = 0;
#define LED_COM2_OFF	LED_COM2 = 1;

#define LED_RUN_BLINK	LED_RUN = (~LED_RUN) & 0x01;
#define LED_WIFI_BLINK	LED_WIFI = (~LED_WIFI) & 0x01;
#define LED_COM1_BLINK	LED_COM1 = (~LED_COM1) & 0x01;
#define LED_COM2_BLINK	LED_COM2 = (~LED_COM2) & 0x01;

typedef enum{
	LED_EVENT_LED_RUN,
	LED_EVENT_WIFI_RXD,
	LED_EVENT_WIFI_TXD,
	LED_EVENT_MODBUS_RXD,
	LED_EVENT_MODBUS_TXD,
	LED_EVENT_BACNET_RXD,
	LED_EVENT_BACNET_TXD,
	LED_EVENT_ERR
}led_event_t;

void led_init(void);

#endif
