#ifndef _CSBOBO_STM32F4XX_SYSTICK_H__
#define _CSBOBO_STM32F4XX_SYSTICK_H__

#include "stm32f4xx.h" 

#ifndef configTICK_RATE_HZ			//每1/configTICK_RATE_HZ秒中断一次
#define configTICK_RATE_HZ	(1000)	//时钟节拍频率，这里设置为1000，周期就是1ms
#endif

//定义进入滴答中断 SysTick_Handler 时间(us)
#define SYSTEMTICK_PERIOD_MS  1000000*1/configTICK_RATE_HZ

void SysTick_delay_init(uint32_t SysTick_IRQn_Tim);
void SysTick_delay_cycle(u16 nTime);	//延时nTime个SysTick中断周期

#endif

