#ifdef TIMER_GLOBAL
#define TIMER_EXT
#else 
#define TIMER_EXT    extern
#endif

#ifndef _TIMER_H
#define _TIMER_H

#include "stm32f10x.h"

#define TIMER_TIME				5          //��ʱ�������λ������
#define	HZ_RUN					(1000/TIMER_TIME)
#define TIMER_5S_OVER  (5000*2/TIMER_TIME) //5�붨ʱ��
#define TIMER_1S_OVER  (1000*2/TIMER_TIME) //1�붨ʱ��
#define TIMER_5Hz_OVER (100*2/TIMER_TIME)  //0.1�붨ʱ��,5Hz����


TIMER_EXT uint16_t TIMER_5s_Count;          //5�붨ʱ����
TIMER_EXT uint16_t TIMER_1s_Count;          //1�붨ʱ����
TIMER_EXT uint16_t TIMER_5Hz_Count;         //5Hz�������Ե����
TIMER_EXT uint8_t TIMER_5Hz_Flag;          //5Hz�������Ա�־


TIMER_EXT uint16_t TIMER_ADOverFlag;      //AD��ʱ��ʼ������־
TIMER_EXT uint16_t TIMER_ADOverCount;     //AD��ʱ����

TIMER_EXT void timer_init(void);

#endif
