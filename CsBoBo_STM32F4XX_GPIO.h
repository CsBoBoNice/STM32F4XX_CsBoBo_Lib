#ifndef _CSBOBO_STM32F4XX_GPIO_H_
#define _CSBOBO_STM32F4XX_GPIO_H_
#include "stm32f4xx.h" 



void GPIO_Common_Init(GPIO_TypeDef* GPIOx,u16 GPIO_PIN,GPIOMode_TypeDef GPIO_Mode,GPIOOType_TypeDef GPIO_OType,GPIOPuPd_TypeDef GPIO_PuPd,GPIOSpeed_TypeDef GPIO_Speed);/*≥ı ºªØGPIO*/


#endif
