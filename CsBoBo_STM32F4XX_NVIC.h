#ifndef _CSBOBO_STM32F4XX_NVIC_H_
#define _CSBOBO_STM32F4XX_NVIC_H_
#include "stm32f4xx.h" 

void NVIC_Configuration(uint32_t NVIC_PriorityGroup);
void NVIC_Init_IRQChannel(	uint8_t NVIC_IRQChannel,\
							uint8_t NVIC_IRQChannelPreemptionPriority,\
							uint8_t NVIC_IRQChannelSubPriority,\
							FunctionalState NVIC_IRQChannelCmd\
							);//初始化中断线


#endif
