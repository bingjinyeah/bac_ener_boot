#ifdef TIMER_GLOBAL
#define TIMER_EXT
#else 
#define TIMER_EXT    extern
#endif

#ifndef _TIMER_H
#define _TIMER_H

#include "stm32f10x.h"

#define TIMER_TIME				5          //∂® ±º‰∏Ù£®µ•Œª£∫∫¡√Î£
#define	HZ_RUN					(1000/TIMER_TIME)
#define TIMER_5S_OVER  (5000*2/TIMER_TIME) //5√Î∂® ±µΩ
#define TIMER_1S_OVER  (1000*2/TIMER_TIME) //1√Î∂® ±µΩ
#define TIMER_5Hz_OVER (100*2/TIMER_TIME)  //0.1√Î∂® ±µΩ,5Hz∑Ω≤®


TIMER_EXT uint16_t TIMER_5s_Count;          //5√Î∂® ±º∆ ˝
TIMER_EXT uint16_t TIMER_1s_Count;          //1√Î∂® ±º∆ ˝
TIMER_EXT uint16_t TIMER_5Hz_Count;         //5Hz∑Ω≤®≤‚ ‘µ„º∆ ˝
TIMER_EXT uint8_t TIMER_5Hz_Flag;          //5Hz∑Ω≤®≤‚ ‘±Í÷æ


TIMER_EXT uint16_t TIMER_ADOverFlag;      //AD≥¨ ±ø™ ºº∆ ˝±Í÷æ
TIMER_EXT uint16_t TIMER_ADOverCount;     //AD≥¨ ±º∆ ˝

TIMER_EXT void timer_init(void);

#endif
