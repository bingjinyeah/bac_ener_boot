#include "stm32f10x.h"
#include "led.h"

void led_init(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
	LED_RUN_OFF
	LED_WIFI_OFF
	LED_COM1_OFF
	LED_COM2_OFF
}

