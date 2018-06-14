#ifndef _CSBOBO_STM32F10X_TIMx_H_
#define _CSBOBO_STM32F10X_TIMx_H_
#include "stm32f4xx.h"

void TIMx_Init_Complete(TIM_TypeDef * TIMx,uint16_t TIM_Prescaler,uint16_t TIM_Period,uint16_t TIM_CounterMode,FunctionalState NVIC_IRQChannelCmd,uint8_t PreemptionPriority,uint8_t SubPriority);
void TIMx_Init(TIM_TypeDef * TIMx,uint16_t TIM_Prescaler,uint16_t TIM_Period,uint16_t TIM_CounterMode,uint8_t PreemptionPriority,uint8_t SubPriority);

#endif

