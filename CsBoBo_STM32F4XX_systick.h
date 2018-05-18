#ifndef _CSBOBO_STM32F4XX_SYSTICK_H__
#define _CSBOBO_STM32F4XX_SYSTICK_H__

#include "stm32f4xx.h" 

#ifndef configTICK_RATE_HZ			//ÿ1/configTICK_RATE_HZ���ж�һ��
#define configTICK_RATE_HZ	(1000)	//ʱ�ӽ���Ƶ�ʣ���������Ϊ1000�����ھ���1ms
#endif

//�������δ��ж� SysTick_Handler ʱ��(us)
#define SYSTEMTICK_PERIOD_MS  1000000*1/configTICK_RATE_HZ

void SysTick_delay_init(uint32_t SysTick_IRQn_Tim);
void SysTick_delay_cycle(u16 nTime);	//��ʱnTime��SysTick�ж�����

#endif

