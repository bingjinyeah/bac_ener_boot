#include "stm32f10x.h"
#include "led.h"
#include "eth_app.h"
#include "flash.h"
#include "wdt.h"
#include "w5500.h"

extern void timer_init(void);
extern uint32_t OSTime;
uint8_t gw_update[4];
uint8_t gw_update_completed = 0;
typedef void (*pfunc)(void);
pfunc jump_to_app;

static void prvSetupHardware( void )
{
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );

	SysTick_CLKSourceConfig( SysTick_CLKSource_HCLK );
}


int main(void)
{
	prvSetupHardware();
	
	led_init();
	timer_init();
	W5500_Initialization();
	flash_read_pages(CFG_UPDATE_PAGE, gw_update, 4);
	if((gw_update[0]==0x12)&&(gw_update[1]==0x34)&&
		(gw_update[2]==0x56)&&(gw_update[3]==0x78)){
		//get update fireware command
		gw_update[0] = 0;
		gw_update[1] = 0;
		gw_update[2] = 0;
		gw_update[3] = 0;
		flash_write_pages(CFG_UPDATE_PAGE, gw_update, 4);
		while(1) {
			eth_app_task();
			if(gw_update_completed) {
				NVIC_SystemReset();
			} 
			
		}
	} else {
		while(OSTime < 6000) {
			if((OSTime % 200)==0) {
				LED_RUN_BLINK;
				LED_WIFI_BLINK;
				LED_COM1_BLINK;
				LED_COM2_BLINK;
			}
			eth_app_task();
		}
		if(((*(uint32_t*)APP_ADDRESS) & 0x2ffe0000) == 0x20000000) { 
			__set_MSP (*(uint32_t *)APP_ADDRESS);
			jump_to_app = (pfunc)(*(uint32_t*)(APP_ADDRESS + 4));
			jump_to_app();
		} else {
			NVIC_SystemReset();
		}
	}
	
    
}


