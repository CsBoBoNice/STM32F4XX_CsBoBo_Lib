#ifndef _CSBOBO_STM32F4XX_BASIC_TIM_H_
#define _CSBOBO_STM32F4XX_BASIC_TIM_H_
#include "stm32f4xx.h" 


void Basic_TIM_Init(TIM_TypeDef* TIMx,uint16_t TIM_Prescaler,uint16_t TIM_Period,uint8_t PreemptionPriority,uint8_t SubPriority);


#endif
