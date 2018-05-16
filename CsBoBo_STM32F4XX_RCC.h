#ifndef _CSBOBO_STM32F4XX_RCC_H_
#define _CSBOBO_STM32F4XX_RCC_H_
#include "stm32f4xx.h" 


void Stm32_Clock_Init(u32 plln,u32 pllm,u32 pllp,u32 pllq);	//系统时钟初始化函数

#endif
