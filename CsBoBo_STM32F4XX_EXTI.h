#ifndef _CSBOBO_STM32F4XX_EXTI_H_
#define _CSBOBO_STM32F4XX_EXTI_H_
#include "stm32f4xx.h" 


void EXTIX_Init(GPIO_TypeDef* GPIOx,u16 GPIO_PIN,EXTITrigger_TypeDef  EXTI_Mode,uint8_t PreemptionPriority,uint8_t SubPriority);



#endif
