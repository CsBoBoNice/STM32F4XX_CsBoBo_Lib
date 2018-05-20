#ifndef _CSBOBO_STM32F4XX_USART_H
#define _CSBOBO_STM32F4XX_USART_H



#include "stm32f4xx.h" 
#include <stdio.h>
#include <string.h>

//串口初始化函数

void USART_init	(	USART_TypeDef * USARTx,			
					GPIO_TypeDef* USART_TX_GPIOx,	
					u16 USART_TX_PIN,
					GPIO_TypeDef* USART_RX_GPIOx,
					u16 USART_RX_PIN,
					uint32_t USART_BaudRate,			//波特率设置
					uint16_t USART_WordLength,			//字长(数据位+校验位)
					uint16_t USART_StopBits,			//停止位		
					uint16_t USART_Parity,				//校验位选择
					uint16_t USART_Mode,				//USART模式控制
					uint16_t USART_HardwareFlowControl,	//硬件流控制
					uint8_t PreemptionPriority,			//抢占优先级
					uint8_t SubPriority					//子优先级
				);

/*****************  发送一个字符 **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);

/*****************  发送字符串 **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);

#endif

