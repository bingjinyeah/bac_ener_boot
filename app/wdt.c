#include "stm32f10x.h"
#include "wdt.h"

void wdt_init()
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_8);
	IWDG_SetReload(0xfff);
}

void enable_wdt(){
    IWDG_Enable();
}

void disable_wdt(){
    
}

void clr_wdt(){
    IWDG_ReloadCounter();
}

