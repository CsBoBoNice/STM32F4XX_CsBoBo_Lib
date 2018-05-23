#ifndef _CSBOBO_STM32F4XX_USART_H
#define _CSBOBO_STM32F4XX_USART_H



#include "stm32f4xx.h" 
#include <stdio.h>
#include <string.h>

#define USART_PERIOD_MS	1	//����ʹ�õĶ�ʱ�������жϵ�ʱ�䵥λMS

#define USING_USART1	//�����ÿ�ע��,��ʡRAM
#define USING_USART2
#define USING_USART3
#define USING_UART4
#define USING_UART5
#define USING_USART6
#define USING_UART7
#define USING_UART8
/********************����������������ѡ��***********************/
/***********************************USART1***************************************/
#ifdef USING_USART1
#define USART1_BUF_SIZE 			256		//����һ��������������С
#define USART1_RECEIVE_OVERTIME		2			//�ֽڳ�ʱʱ��, ��λΪms

extern uint8_t USART1_ready_buf[];
extern __IO uint8_t USART1_ready_buf_ok;
extern __IO uint16_t USART1_ready_buf_len;
void USART1_ISR(void);
#endif
/*************************************USART2**************************************/

#ifdef USING_USART2
#define USART2_BUF_SIZE				256	//����һ��������������С	
#define USART2_RECEIVE_OVERTIME		200		//�ֽڳ�ʱʱ��, ��λΪms

extern uint8_t USART2_ready_buf[];
extern __IO uint8_t USART2_ready_buf_ok;
extern __IO uint16_t USART2_ready_buf_len;
void USART2_ISR(void);
#endif
/*************************************USART3**************************************/

#ifdef USING_USART3
#define USART3_BUF_SIZE				128	//����һ��������������С
#define USART3_RECEIVE_OVERTIME		10		//�ֽڳ�ʱʱ��, ��λΪms

extern uint8_t USART3_ready_buf[];
extern __IO uint8_t USART3_ready_buf_ok;
extern __IO uint16_t USART3_ready_buf_len;
void USART3_Init(void);
#endif
/*************************************UART4**************************************/

#ifdef USING_UART4
#define UART4_BUF_SIZE				128	//����һ��������������С
#define UART4_RECEIVE_OVERTIME		10		//�ֽڳ�ʱʱ��, ��λΪms	

extern uint8_t UART4_ready_buf[];
extern __IO uint8_t UART4_ready_buf_ok;
extern __IO uint16_t UART4_ready_buf_len;
void UART4_Init(void);
#endif
/*************************************UART5**************************************/

#ifdef USING_UART5
#define UART5_BUF_SIZE				128	//����һ��������������С
#define UART5_RECEIVE_OVERTIME		10		//�ֽڳ�ʱʱ��, ��λΪms	

extern uint8_t UART5_ready_buf[];
extern __IO uint8_t UART5_ready_buf_ok;
extern __IO uint16_t UART5_ready_buf_len;
void UART5_ISR(void);
#endif

/*************************************USART6**************************************/

#ifdef USING_USART6
#define USART6_BUF_SIZE				128	//����һ��������������С
#define USART6_RECEIVE_OVERTIME		10		//�ֽڳ�ʱʱ��, ��λΪms

extern uint8_t USART6_ready_buf[];
extern __IO uint8_t USART6_ready_buf_ok;
extern __IO uint16_t USART6_ready_buf_len;
void USART6_Init(void);
#endif

/*************************************UART7**************************************/

#ifdef USING_UART7
#define UART7_BUF_SIZE				128	//����һ��������������С
#define UART7_RECEIVE_OVERTIME		10		//�ֽڳ�ʱʱ��, ��λΪms	

extern uint8_t UART7_ready_buf[];
extern __IO uint8_t UART7_ready_buf_ok;
extern __IO uint16_t UART7_ready_buf_len;
void UART7_ISR(void);
#endif

/*************************************UART8**************************************/

#ifdef USING_UART8
#define UART8_BUF_SIZE				128	//����һ��������������С
#define UART8_RECEIVE_OVERTIME		10		//�ֽڳ�ʱʱ��, ��λΪms	

extern uint8_t UART8_ready_buf[];
extern __IO uint8_t UART8_ready_buf_ok;
extern __IO uint16_t UART8_ready_buf_len;
void UART8_ISR(void);
#endif


#define UART_OK 1
#define UART_ERROR 0

/******************************API************************************************/
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
void USART_SendChars(USART_TypeDef* USARTx,const uint8_t* SendChars,uint16_t len);	//����һ������

void USART_ReceiveOvertimeProcess(void);	//���ж���ִ�еĴ���
//�жϴ����Ƿ�������
//���ճɹ����� UART_OK
//����ʧ�ܷ��� UART_ERROR
int Get_USART_ready_buf_ok(USART_TypeDef * usart);
void Clean_USART_ready_buf_OK(USART_TypeDef * usart);//��������Ƿ������ϱ�־
void Clean_USART_ready_buf(USART_TypeDef * usart);//������ڻ�������

#endif

