#include "stm32f10x.h"

volatile uint32_t OSTime;

#define  OS_CPU_CM3_NVIC_ST_CTRL    (*((volatile uint32_t *)0xE000E010uL)) /* SysTick Ctrl & Status Reg. */
#define  OS_CPU_CM3_NVIC_ST_RELOAD  (*((volatile uint32_t *)0xE000E014uL)) /* SysTick Reload  Value Reg. */
#define  OS_CPU_CM3_NVIC_ST_CURRENT (*((volatile uint32_t *)0xE000E018uL)) /* SysTick Current Value Reg. */
#define  OS_CPU_CM3_NVIC_ST_CAL     (*((volatile uint32_t *)0xE000E01CuL)) /* SysTick Cal     Value Reg. */
#define  OS_CPU_CM3_NVIC_PRIO_ST    (*((volatile uint8_t  *)0xE000ED23uL)) /* SysTick Handler Prio  Reg. */

#define  OS_CPU_CM3_NVIC_ST_CTRL_COUNT                    0x00010000uL   /* Count flag.                */
#define  OS_CPU_CM3_NVIC_ST_CTRL_CLK_SRC                  0x00000004uL   /* Clock Source.              */
#define  OS_CPU_CM3_NVIC_ST_CTRL_INTEN                    0x00000002uL   /* Interrupt enable.          */
#define  OS_CPU_CM3_NVIC_ST_CTRL_ENABLE                   0x00000001uL   /* Counter mode.              */
#define  OS_CPU_CM3_NVIC_PRIO_MIN                               0xFFu    /* Min handler prio.          */


void  SysTickInit (uint32_t  cnts)
{
    OSTime = 0;
	OS_CPU_CM3_NVIC_ST_RELOAD = cnts - 1u;
                                                 /* Set prio of SysTick handler to min prio.           */
    OS_CPU_CM3_NVIC_PRIO_ST   = OS_CPU_CM3_NVIC_PRIO_MIN;
                                                 /* Enable timer.                                      */
    OS_CPU_CM3_NVIC_ST_CTRL  |= OS_CPU_CM3_NVIC_ST_CTRL_CLK_SRC | OS_CPU_CM3_NVIC_ST_CTRL_ENABLE;
                                                 /* Enable timer interrupt.                            */
    OS_CPU_CM3_NVIC_ST_CTRL  |= OS_CPU_CM3_NVIC_ST_CTRL_INTEN;
}

void  SysTickDisable()
{                                              
    OS_CPU_CM3_NVIC_ST_CTRL = 0;
}



void timer_init(void)
{
    SysTickInit(SystemCoreClock/1000);
}


void SysTick_Handler(void)
{ 	
    OSTime++; 
    
}

