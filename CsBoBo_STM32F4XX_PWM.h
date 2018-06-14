#ifndef _CSBOBO_STM32F10X_PWM_H_ 
#define _CSBOBO_STM32F10X_PWM_H_
#include "stm32f4xx.h" 


void TIM_PWM_Init(	TIM_TypeDef * TIMx,
					GPIO_TypeDef* GPIOx,
					u16 GPIO_PIN,
					uint16_t TIM_Prescaler,
					uint16_t TIM_Period,
					uint16_t TIM_CounterMode,
					uint16_t TIM_OCMode,
					uint32_t TIM_Pulse,
					uint16_t TIM_OCPolarity,
					u16 TIM_channeX
				);

#endif
