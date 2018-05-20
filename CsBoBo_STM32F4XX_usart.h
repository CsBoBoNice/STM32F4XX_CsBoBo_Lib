#ifndef _CSBOBO_STM32F4XX_USART_H
#define _CSBOBO_STM32F4XX_USART_H



#include "stm32f4xx.h" 
#include <stdio.h>
#include <string.h>

//���ڳ�ʼ������

void USART_init	(	USART_TypeDef * USARTx,			
					GPIO_TypeDef* USART_TX_GPIOx,	
					u16 USART_TX_PIN,
					GPIO_TypeDef* USART_RX_GPIOx,
					u16 USART_RX_PIN,
					uint32_t USART_BaudRate,			//����������
					uint16_t USART_WordLength,			//�ֳ�(����λ+У��λ)
					uint16_t USART_StopBits,			//ֹͣλ		
					uint16_t USART_Parity,				//У��λѡ��
					uint16_t USART_Mode,				//USARTģʽ����
					uint16_t USART_HardwareFlowControl,	//Ӳ��������
					uint8_t PreemptionPriority,			//��ռ���ȼ�
					uint8_t SubPriority					//�����ȼ�
				);

/*****************  ����һ���ַ� **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);

/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);

#endif

