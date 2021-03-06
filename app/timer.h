#ifdef TIMER_GLOBAL
#define TIMER_EXT
#else 
#define TIMER_EXT    extern
#endif

#ifndef _TIMER_H
#define _TIMER_H

#include "stm32f10x.h"

#define TIMER_TIME				5          //定时间隔（单位：毫秒�
#define	HZ_RUN					(1000/TIMER_TIME)
#define TIMER_5S_OVER  (5000*2/TIMER_TIME) //5秒定时到
#define TIMER_1S_OVER  (1000*2/TIMER_TIME) //1秒定时到
#define TIMER_5Hz_OVER (100*2/TIMER_TIME)  //0.1秒定时到,5Hz方波


TIMER_EXT uint16_t TIMER_5s_Count;          //5秒定时计数
TIMER_EXT uint16_t TIMER_1s_Count;          //1秒定时计数
TIMER_EXT uint16_t TIMER_5Hz_Count;         //5Hz方波测试点计数
TIMER_EXT uint8_t TIMER_5Hz_Flag;          //5Hz方波测试标志


TIMER_EXT uint16_t TIMER_ADOverFlag;      //AD超时开始计数标志
TIMER_EXT uint16_t TIMER_ADOverCount;     //AD超时计数

TIMER_EXT void timer_init(void);

#endif
