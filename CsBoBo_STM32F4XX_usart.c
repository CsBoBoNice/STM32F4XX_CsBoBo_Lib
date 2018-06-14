#include "CsBoBo_STM32F4XX_usart.h"
#include "CsBoBo_STM32F4XX_LIB.h"


/*

@��:	
		USART_init(	USART2,
					GPIOD,GPIO_Pin_5,	
					GPIOD,GPIO_Pin_6,
					9600,					//������
					USART_WordLength_8b,	//8λ�ֳ� �ֳ�(����λ+У��λ)
					USART_StopBits_1,		//ֹͣλ 1	λ
					USART_Parity_No,		//��ʹ��У��
					USART_Mode_Rx | USART_Mode_Tx,	//���պͷ���ģʽ
					USART_HardwareFlowControl_None,	//Ӳ��������ʧ��
					0,0
					);

	����1��USART���
						USART1
						USART2
						USART3
						UART4
						UART5
						USART6
						UART7
						UART8
	����2��TX GPIO 

	����3��TX GPIO_Pin

	����4��RX GPIO 

	����5��RX GPIO_Pin 

			��������:	(ͬһ���������ſ�������䣬����: TX(PA9) RX(PB7) )
			����		TX		RX
			USART1		PA9		PA10
						PB6		PB7

			USART2		PA2		PA3
						PD5		PD6 

			USART3		PB10	PB11
						PC10	PC11
						PD8		PD9
						
			UART4		PC10	PC11
						PA0		PA1
										
			UART5		PC12	PD2

			USART6		PG14	PG9
						PC6		PC7
						
			UART7		PF7		PF6
						PE8		PE7

			UART8		PE1		PE0
			
			
	����6��������ȡֵ��Χ(600,1200,2400,4800,9600,14400,19200,28800,38400,57600,115200,230400,460800)
	
	����7���ֳ�(����λ+У��λ)
			USART_WordLength_8b		8λ�ֳ�
			USART_WordLength_9b		9λ�ֳ�

	����8��ֹͣλ
			USART_StopBits_1		ֹͣλ 1	λ
			USART_StopBits_0_5		ֹͣλ 0.5	λ
			USART_StopBits_2		ֹͣλ 2	λ
			USART_StopBits_1_5		ֹͣλ 1.5	λ

	����9��У��λѡ��
			USART_Parity_No			��ʹ��У��
			USART_Parity_Even		żУ��
			USART_Parity_Odd		��У��

	����10��USARTģʽ���ƣ�
			USART_Mode_Tx		����ģʽ
			USART_Mode_Rx		����ģʽ
			USART_Mode_Rx | USART_Mode_Tx	���պͷ���ģʽ
	
	����11��Ӳ�������ƣ�
			USART_HardwareFlowControl_None		Ӳ��������ʧ��
			USART_HardwareFlowControl_RTS		��������RTSʹ��
			USART_HardwareFlowControl_CTS		�������CTSʹ��
			USART_HardwareFlowControl_RTS_CTS	RTS��CTSʹ��

	����12����Ӧ�������ȼ�����	��ֵԽ�����ȼ�Խ��

	����13����Ӧ��Ӧ���ȼ�����	��ֵԽ�����ȼ�Խ��
*/
/******************************************************************************************************************/
/************************************************************************
@ע:

	���մ�������ͨ���жϽ��գ�ͨ����ʱ���ж��Ƿ�ʱ��
��CsBoBo_STM32F10X_usart.h�����ó�ʱʱ�䣬����ջ�������С,���δ�õ��Ĵ��ڿ���ע�ͣ���Լ�ڴ棬

����Ϊ��ʱ����ӳ�ʱ�㷨�Ĵ���:

#if defined (USING_USART1) || defined (USING_USART2) || defined (USING_USART3)|| defined (USING_UART4)|| defined (USING_UART5)
USART_ReceiveOvertimeProcess();
#endif


������ʹ�ô���ʱ�Ĵ��ڽ��մ���

NVIC_Configuration(NVIC_PriorityGroup_4);//�������ȼ����飺�������ȼ�����Ӧ���ȼ�
TIM_Common_Init(2,7200,10,TIM_CounterMode_Up,3,0);	//��ʱ����ʼ�� 1MS
USART_init(1,115200,0,3,0);	//���ڳ�ʼ��

if(Get_USART_ready_buf_ok(USART1))	//�жϳ�ʱ��һ֡���ݽ��ճɹ�
{
	Clean_USART_ready_buf_OK(USART1);//��������Ƿ������ϱ�־
	
	USART_SendChars(USART1,USART1_ready_buf,USART1_ready_buf_len);	//�ط�
	
	Clean_USART_ready_buf(USART1);//������ڻ�������
}

USART1_ready_buf ���յ�������
USART1_ready_buf_len �������ݳ���
*/
#ifdef USING_USART1
uint8_t USART1_receive_buf[USART1_BUF_SIZE];	//���ݽ��ջ�����
uint8_t USART1_ready_buf[USART1_BUF_SIZE];		//���ճɹ����������
static int32_t USART1_ReceiveTimeCounter = 0;	//��ʱʣ��ʱ��
__IO uint16_t USART1_receive_index=0; 		//���ڽ��յ����ݳ���
__IO uint8_t USART1_ready_buf_ok = 0;		//�Ƿ�ɹ�����
__IO uint16_t USART1_ready_buf_len = 0;		//�ɹ����պ�����ݳ���
#endif

#ifdef USING_USART2
uint8_t USART2_receive_buf[USART2_BUF_SIZE],USART2_ready_buf[USART2_BUF_SIZE];
static int32_t USART2_ReceiveTimeCounter = 0;
__IO uint16_t USART2_receive_index=0; 
__IO uint8_t USART2_ready_buf_ok = 0;
__IO uint16_t USART2_ready_buf_len=0;
#endif

#ifdef USING_USART3
static int32_t USART3_ReceiveTimeCounter = 0;
uint8_t USART3_receive_buf[USART3_BUF_SIZE],USART3_ready_buf[USART3_BUF_SIZE];
__IO uint16_t USART3_receive_index=0; 
__IO uint8_t USART3_ready_buf_ok = 0;
__IO uint16_t USART3_ready_buf_len=0;
#endif

#ifdef USING_UART4
uint8_t UART4_receive_buf[UART4_BUF_SIZE],UART4_ready_buf[UART4_BUF_SIZE];
static int32_t UART4_ReceiveTimeCounter = 0;
__IO uint16_t UART4_receive_index=0; 
__IO uint8_t UART4_ready_buf_ok = 0;
__IO uint16_t UART4_ready_buf_len=0;
#endif

#ifdef USING_UART5
uint8_t UART5_receive_buf[UART5_BUF_SIZE],UART5_ready_buf[UART5_BUF_SIZE];
static int32_t UART5_ReceiveTimeCounter = 0;
__IO uint16_t UART5_receive_index=0; 
__IO uint8_t UART5_ready_buf_ok = 0;
__IO uint16_t UART5_ready_buf_len=0;
#endif

#ifdef USING_USART6
uint8_t USART6_receive_buf[USART6_BUF_SIZE];	//���ݽ��ջ�����
uint8_t USART6_ready_buf[USART6_BUF_SIZE];		//���ճɹ����������
static int32_t USART6_ReceiveTimeCounter = 0;	//��ʱʣ��ʱ��
__IO uint16_t USART6_receive_index=0; 		//���ڽ��յ����ݳ���
__IO uint8_t USART6_ready_buf_ok = 0;		//�Ƿ�ɹ�����
__IO uint16_t USART6_ready_buf_len = 0;		//�ɹ����պ�����ݳ���
#endif

#ifdef USING_UART7
uint8_t UART7_receive_buf[UART7_BUF_SIZE],UART7_ready_buf[UART7_BUF_SIZE];
static int32_t UART7_ReceiveTimeCounter = 0;
__IO uint16_t UART7_receive_index=0; 
__IO uint8_t UART7_ready_buf_ok = 0;
__IO uint16_t UART7_ready_buf_len=0;
#endif

#ifdef USING_UART8
uint8_t UART8_receive_buf[UART8_BUF_SIZE],UART8_ready_buf[UART8_BUF_SIZE];
static int32_t UART8_ReceiveTimeCounter = 0;
__IO uint16_t UART8_receive_index=0; 
__IO uint8_t UART8_ready_buf_ok = 0;
__IO uint16_t UART8_ready_buf_len=0;
#endif

void USART1_ISR(void); //�����жϺ���
void USART2_ISR(void); //�����жϺ���
void USART3_ISR(void); //�����жϺ���
void UART4_ISR(void); //�����жϺ���
void UART5_ISR(void); //�����жϺ���
void USART6_ISR(void); //�����жϺ���
void UART7_ISR(void); //�����жϺ���
void UART8_ISR(void); //�����жϺ���

/**********************�жϺ���***************************************************************************************************/
#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F411xE) || defined(STM32F446xx) 
void USART1_IRQHandler(void)
{
	#ifdef USING_USART1
	USART1_ISR();
	#endif
}	

void USART2_IRQHandler(void)
{
	#ifdef USING_USART2
	USART2_ISR();
	#endif
}
#endif

#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx) 	
void USART3_IRQHandler(void)
{
	#ifdef USING_USART3
	USART3_ISR();
	#endif
}
#endif

#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx) 	
void UART4_IRQHandler(void)
{
	#ifdef USING_UART4
	UART4_ISR();
	#endif
}

void UART5_IRQHandler(void)
{
	#ifdef USING_UART5
	UART5_ISR();
	#endif
}
#endif

#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F411xE) || defined(STM32F446xx) 	
void USART6_IRQHandler(void)
{
	#ifdef USING_USART6
	USART6_ISR();
	#endif
}
#endif

#if defined(STM32F427_437xx) || defined(STM32F429_439xx)	
void UART7_IRQHandler(void)
{
	#ifdef USING_UART7
	UART7_ISR();
	#endif
}
void UART8_IRQHandler(void)
{
	#ifdef USING_UART8
	UART8_ISR();
	#endif
}
#endif

/**********************����1�жϽ���һ���ַ�***************************************************************************************************/
/*
���жϷ�������У�����������Ӧ�ж�ʱ����֪�����ĸ��ж�Դ�����ж�����
��˱������жϷ�������ж��ж�Դ�����б�Ȼ��ֱ���д���
��Ȼ�����ֻ�漰��һ���ж������ǲ����������б�ġ���������ʲô������������б��Ǹ���ϰ��
*/
#ifdef USING_USART1
void USART1_ISR(void)   
{

	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//�ж��Ƿ����ж�
	{
		USART1_ReceiveTimeCounter = USART1_RECEIVE_OVERTIME;

		if(USART1_receive_index >= USART1_BUF_SIZE)//������λ��Խ�磬��ô��ͷ��ʼ���
			USART1_receive_index = 0;
		
		USART1_receive_buf[USART1_receive_index++] = (uint8_t)USART_ReceiveData(USART1);//�����ַ�����λ�ü�1		
	}	
	if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)//���ش���ֻҪ��״̬�Ĵ��������ݼĴ����Ϳ��Զ�����˱�־
	{
		(void)USART_ReceiveData(USART1);
	}

} 
#endif

#ifdef USING_USART2
void USART2_ISR(void)
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�ж��Ƿ����ж�
	{	
		USART2_ReceiveTimeCounter = USART2_RECEIVE_OVERTIME;
		
		if(USART2_receive_index >= USART2_BUF_SIZE)	//������λ��Խ�磬��ô��ͷ��ʼ���
			USART2_receive_index = 0;
		
		USART2_receive_buf[USART2_receive_index++] = (uint8_t)USART_ReceiveData(USART2);//�����ַ�����λ�ü�1
		
	}		
	if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)//���ش���ֻҪ��״̬�Ĵ��������ݼĴ����Ϳ��Զ�����˱�־
	{
		(void)USART_ReceiveData(USART2);
	}
}
#endif

#ifdef USING_USART3
void USART3_ISR(void)
{
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		USART3_ReceiveTimeCounter = USART3_RECEIVE_OVERTIME;
		if(USART3_receive_index >= USART3_BUF_SIZE)
			USART3_receive_index = 0;
		
		USART3_receive_buf[USART3_receive_index++] = (uint8_t)USART_ReceiveData(USART3);
		
	}
		
	if (USART_GetFlagStatus(USART3, USART_FLAG_ORE) != RESET)
	{
		(void)USART_ReceiveData(USART3);
	}
}
#endif

#ifdef USING_UART4
void UART4_ISR(void)
{
	if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{
		UART4_ReceiveTimeCounter = UART4_RECEIVE_OVERTIME;
		if(UART4_receive_index >= UART4_BUF_SIZE)
			UART4_receive_index = 0;
		
		UART4_receive_buf[UART4_receive_index++] = (uint8_t)USART_ReceiveData(UART4);
		
	}
		
	if (USART_GetFlagStatus(UART4, USART_FLAG_ORE) != RESET)
	{
		(void)USART_ReceiveData(UART4);
	}
}
#endif

#ifdef USING_UART5
void UART5_ISR(void)
{
	if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
	{		
		UART5_ReceiveTimeCounter = UART5_RECEIVE_OVERTIME;
		if(UART5_receive_index >= UART5_BUF_SIZE)
			UART5_receive_index = 0;
		
		UART5_receive_buf[UART5_receive_index++] = (uint8_t)USART_ReceiveData(UART5);
		
	}
		
	if (USART_GetFlagStatus(UART5, USART_FLAG_ORE) != RESET)
	{
		(void)USART_ReceiveData(UART5);
	}
}
#endif

#ifdef USING_USART6
void USART6_ISR(void)
{
	if (USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)
	{
		USART6_ReceiveTimeCounter = USART6_RECEIVE_OVERTIME;
		if(USART6_receive_index >= USART6_BUF_SIZE)
			USART6_receive_index = 0;
		
		USART6_receive_buf[USART6_receive_index++] = (uint8_t)USART_ReceiveData(USART6);
		
	}
		
	if (USART_GetFlagStatus(USART6, USART_FLAG_ORE) != RESET)
	{
		(void)USART_ReceiveData(USART6);
	}
}
#endif

#ifdef USING_UART7
void UART7_ISR(void)
{
	if (USART_GetITStatus(UART7, USART_IT_RXNE) != RESET)
	{		
		UART7_ReceiveTimeCounter = UART7_RECEIVE_OVERTIME;
		if(UART7_receive_index >= UART7_BUF_SIZE)
			UART7_receive_index = 0;
		
		UART7_receive_buf[UART7_receive_index++] = (uint8_t)USART_ReceiveData(UART7);
		
	}
		
	if (USART_GetFlagStatus(UART7, USART_FLAG_ORE) != RESET)
	{
		(void)USART_ReceiveData(UART7);
	}
}
#endif

#ifdef USING_UART8
void UART8_ISR(void)
{
	if (USART_GetITStatus(UART8, USART_IT_RXNE) != RESET)
	{		
		UART8_ReceiveTimeCounter = UART8_RECEIVE_OVERTIME;
		if(UART8_receive_index >= UART8_BUF_SIZE)
			UART8_receive_index = 0;
		
		UART8_receive_buf[UART8_receive_index++] = (uint8_t)USART_ReceiveData(UART8);
		
	}
		
	if (USART_GetFlagStatus(UART8, USART_FLAG_ORE) != RESET)
	{
		(void)USART_ReceiveData(UART8);
	}
}

#endif

//���ж���ִ�еĴ���
void USART_ReceiveOvertimeProcess(void)		//���ж���ִ�еĴ���
{
	#if defined (USING_USART1) || defined (USING_USART2) || defined (USING_USART3)|| defined (USING_UART4)|| defined (USING_UART5)
	uint16_t i = 0;	
	#endif
	
	#ifdef USING_USART1
	if(USART1_ReceiveTimeCounter>=USART_PERIOD_MS)
	{
		USART1_ReceiveTimeCounter -= USART_PERIOD_MS;

		if(USART1_ReceiveTimeCounter<USART_PERIOD_MS)
		{
			USART1_ready_buf_len = USART1_receive_index;

			for(i = 0;i <= USART1_ready_buf_len; i ++)
				USART1_ready_buf[i] = USART1_receive_buf[i];
	
			USART1_ready_buf_ok = UART_OK;
			USART1_receive_index=0;
			USART1_ReceiveTimeCounter = 0;
		}
	}
	#endif

	#ifdef USING_USART2
	if(USART2_ReceiveTimeCounter>=USART_PERIOD_MS)
	{
		USART2_ReceiveTimeCounter -= USART_PERIOD_MS;

		if(USART2_ReceiveTimeCounter<USART_PERIOD_MS)
		{
			USART2_ready_buf_len = USART2_receive_index;

			for(i = 0;i <= USART2_ready_buf_len; i ++)
				USART2_ready_buf[i] = USART2_receive_buf[i];
	
			USART2_ready_buf_ok = UART_OK;
			USART2_receive_index=0;
			USART2_ReceiveTimeCounter = 0;
		}
	}
	#endif

	#ifdef USING_USART3
	if(USART3_ReceiveTimeCounter>=USART_PERIOD_MS)
	{
		USART3_ReceiveTimeCounter -= USART_PERIOD_MS;

		if(USART3_ReceiveTimeCounter<USART_PERIOD_MS)
		{
			USART3_ready_buf_len = USART3_receive_index;

			for(i = 0;i <= USART3_ready_buf_len; i ++)
				USART3_ready_buf[i] = USART3_receive_buf[i];
	
			USART3_ready_buf_ok = UART_OK;
			USART3_receive_index=0;
			USART3_ReceiveTimeCounter = 0;
		}
	}
	#endif

	#ifdef USING_UART4
	if(UART4_ReceiveTimeCounter>=USART_PERIOD_MS)
	{
		UART4_ReceiveTimeCounter -= USART_PERIOD_MS;

		if(UART4_ReceiveTimeCounter<USART_PERIOD_MS)
		{
			UART4_ready_buf_len = UART4_receive_index;

			for(i = 0;i <= UART4_ready_buf_len; i ++)
				UART4_ready_buf[i] = UART4_receive_buf[i];
	
			UART4_ready_buf_ok = UART_OK;
			UART4_receive_index=0;
			UART4_ReceiveTimeCounter = 0;
		}
	}
	#endif

	#ifdef USING_UART5
	if(UART5_ReceiveTimeCounter>=USART_PERIOD_MS)
	{
		UART5_ReceiveTimeCounter -= USART_PERIOD_MS;

		if(UART5_ReceiveTimeCounter<USART_PERIOD_MS)
		{
			UART5_ready_buf_len = UART5_receive_index;

			for(i = 0;i <= UART5_ready_buf_len; i ++)
				UART5_ready_buf[i] = UART5_receive_buf[i];
	
			UART5_ready_buf_ok = UART_OK;
			UART5_receive_index=0;
			UART5_ReceiveTimeCounter = 0;
		}
	}
	#endif
	
	#ifdef USING_USART6
	if(USART6_ReceiveTimeCounter>=USART_PERIOD_MS)
	{
		USART6_ReceiveTimeCounter -= USART_PERIOD_MS;

		if(USART6_ReceiveTimeCounter<USART_PERIOD_MS)
		{
			USART6_ready_buf_len = USART6_receive_index;

			for(i = 0;i <= USART6_ready_buf_len; i ++)
				USART6_ready_buf[i] = USART6_receive_buf[i];
	
			USART6_ready_buf_ok = UART_OK;
			USART6_receive_index=0;
			USART6_ReceiveTimeCounter = 0;
		}
	}
	#endif	
	
	#ifdef USING_UART7
	if(UART7_ReceiveTimeCounter>=USART_PERIOD_MS)
	{
		UART7_ReceiveTimeCounter -= USART_PERIOD_MS;

		if(UART7_ReceiveTimeCounter<USART_PERIOD_MS)
		{
			UART7_ready_buf_len = UART7_receive_index;

			for(i = 0;i <= UART7_ready_buf_len; i ++)
				UART7_ready_buf[i] = UART7_receive_buf[i];
	
			UART7_ready_buf_ok = UART_OK;
			UART7_receive_index=0;
			UART7_ReceiveTimeCounter = 0;
		}
	}
	#endif	
	
	#ifdef USING_UART8
	if(UART8_ReceiveTimeCounter>=USART_PERIOD_MS)
	{
		UART8_ReceiveTimeCounter -= USART_PERIOD_MS;

		if(UART8_ReceiveTimeCounter<USART_PERIOD_MS)
		{
			UART8_ready_buf_len = UART8_receive_index;

			for(i = 0;i <= UART8_ready_buf_len; i ++)
				UART8_ready_buf[i] = UART8_receive_buf[i];
	
			UART8_ready_buf_ok = UART_OK;
			UART8_receive_index=0;
			UART8_ReceiveTimeCounter = 0;
		}
	}
	#endif		
}

/******************************************************************************************************************/

//�жϴ����Ƿ�������
//���ճɹ����� UART_OK
//����ʧ�ܷ��� UART_ERROR
int Get_USART_ready_buf_ok(USART_TypeDef * usart)
{
#ifdef USING_USART1
	if(usart==USART1)return USART1_ready_buf_ok;
#endif	
	
#ifdef USING_USART2
	if(usart==USART2)return USART2_ready_buf_ok;
#endif

#ifdef USING_USART3
	if(usart==USART3)return USART3_ready_buf_ok;
#endif
	
#ifdef USING_UART4
	if(usart==UART4)return UART4_ready_buf_ok;
#endif	
	
#ifdef USING_UART5
	if(usart==UART5)return UART5_ready_buf_ok;
#endif	

#ifdef USING_USART6
	if(usart==USART6)return USART6_ready_buf_ok;
#endif	

#ifdef USING_UART7
	if(usart==UART7)return UART7_ready_buf_ok;
#endif

#ifdef USING_UART8
	if(usart==UART8)return UART8_ready_buf_ok;
#endif	
	return UART_ERROR;
}

//��������Ƿ������ϱ�־
void Clean_USART_ready_buf_OK(USART_TypeDef * usart)
{
#ifdef USING_USART1
	if(usart==USART1)
	{
		USART1_ready_buf_ok=UART_ERROR;
	}
#endif	
	
#ifdef USING_USART2
	if(usart==USART2)
	{
		USART2_ready_buf_ok=UART_ERROR;
	}
#endif

#ifdef USING_USART3
	if(usart==USART3)
	{
		USART3_ready_buf_ok=UART_ERROR;
	}		
#endif
	
#ifdef USING_UART4
	if(usart==UART4)
	{
		UART4_ready_buf_ok=UART_ERROR;
	}		
#endif	
	
#ifdef USING_UART5
	if(usart==UART5)
	{
		UART5_ready_buf_ok=UART_ERROR;
	}
#endif

#ifdef USING_USART6
	if(usart==USART6)
	{
		USART6_ready_buf_ok=UART_ERROR;
	}		
#endif	

#ifdef USING_UART7
	if(usart==UART7)
	{
		UART7_ready_buf_ok=UART_ERROR;
	}
#endif	

#ifdef USING_UART8
	if(usart==UART8)
	{
		UART8_ready_buf_ok=UART_ERROR;
	}
#endif	
	
}

//������ڻ�������
void Clean_USART_ready_buf(USART_TypeDef * usart)
{
#ifdef USING_USART1
	if(usart==USART1)
	{
		memset(USART1_ready_buf,0,USART1_BUF_SIZE);
	}
#endif	
	
#ifdef USING_USART2
	if(usart==USART2)
	{
		memset(USART2_ready_buf,0,USART2_BUF_SIZE);
	}
#endif

#ifdef USING_USART3
	if(usart==USART3)
	{
		memset(USART3_ready_buf,0,USART3_BUF_SIZE);
	}		
#endif
	
#ifdef USING_UART4
	if(usart==UART4)
	{
		memset(UART4_ready_buf,0,UART4_BUF_SIZE);
	}		
#endif	
	
#ifdef USING_UART5
	if(usart==UART5)
	{
		memset(UART5_ready_buf,0,UART5_BUF_SIZE);
	}
#endif			

#ifdef USING_USART6
	if(usart==USART6)
	{
		memset(USART6_ready_buf,0,USART6_BUF_SIZE);
	}		
#endif	

#ifdef USING_UART7
	if(usart==UART7)
	{
		memset(UART7_ready_buf,0,UART7_BUF_SIZE);
	}
#endif

#ifdef USING_UART8
	if(usart==UART8)
	{
		memset(UART8_ready_buf,0,UART8_BUF_SIZE);
	}
#endif	
	
}

/******************************************************************************************************************/
static uint8_t GPIO_AF_X(USART_TypeDef * USARTx)
{
	#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F411xE) || defined(STM32F446xx) 
	if		(USARTx==USART1) {return GPIO_AF_USART1;}
	else if	(USARTx==USART2) {return GPIO_AF_USART2;}
	#endif
	
	#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx) 	
	else if	(USARTx==USART3) {return GPIO_AF_USART3;}
	#endif
	
	#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx) 	
	else if	(USARTx==UART4) {return GPIO_AF_UART4;}
	else if	(USARTx==UART5) {return GPIO_AF_UART5;}
	#endif
	
	#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F411xE) || defined(STM32F446xx) 	
	else if	(USARTx==USART6) {return GPIO_AF_USART6;}
	#endif
	
	#if defined(STM32F427_437xx) || defined(STM32F429_439xx)	
	else if	(USARTx==UART7) {return GPIO_AF_UART7;}
	else if	(USARTx==UART8) {return GPIO_AF_UART8;}
	#endif
	return 0;
}

static uint32_t Get_GPIO_PinSourceX(u16 GPIO_PIN)
{
	switch(GPIO_PIN)
	{
		case GPIO_Pin_0: return GPIO_PinSource0; 
		case GPIO_Pin_1: return GPIO_PinSource1;
		case GPIO_Pin_2: return GPIO_PinSource2; 
		case GPIO_Pin_3: return GPIO_PinSource3;
		case GPIO_Pin_4: return GPIO_PinSource4; 
		case GPIO_Pin_5: return GPIO_PinSource5;
		case GPIO_Pin_6: return GPIO_PinSource6; 
		case GPIO_Pin_7: return GPIO_PinSource7;
		case GPIO_Pin_8: return GPIO_PinSource8; 
		case GPIO_Pin_9: return GPIO_PinSource9;
		case GPIO_Pin_10: return GPIO_PinSource10; 
		case GPIO_Pin_11: return GPIO_PinSource11;
		case GPIO_Pin_12: return GPIO_PinSource12; 
		case GPIO_Pin_13: return GPIO_PinSource13;
		case GPIO_Pin_14: return GPIO_PinSource14; 
		case GPIO_Pin_15: return GPIO_PinSource15;
	}
	return 0;
}

static uint8_t Get_NVIC_IRQChannel_USART(USART_TypeDef * USARTx)
{
	#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F411xE) || defined(STM32F446xx) 
	if		(USARTx==USART1) {return USART1_IRQn;}
	else if	(USARTx==USART2) {return USART2_IRQn;}
	#endif
	
	#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx) 	
	else if	(USARTx==USART3) {return USART3_IRQn;}
	#endif
	
	#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx) 	
	else if	(USARTx==UART4) {return UART4_IRQn;}
	else if	(USARTx==UART5) {return UART5_IRQn;}
	#endif
	
	#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F411xE) || defined(STM32F446xx) 	
	else if	(USARTx==USART6) {return USART6_IRQn;}
	#endif
	
	#if defined(STM32F427_437xx) || defined(STM32F429_439xx)	
	else if	(USARTx==UART7) {return UART7_IRQn;}
	else if	(USARTx==UART8) {return UART8_IRQn;}
	#endif
	return 0;
}

static void USART_RCC_PeriphClockCmd(USART_TypeDef * USARTx)
{
	#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F411xE) || defined(STM32F446xx) 
	if		(USARTx==USART1) {	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);}
	else if	(USARTx==USART2) {	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);}
	#endif
	
	#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx) 	
	else if	(USARTx==USART3) {	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);}
	#endif
	
	#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx) 	
	else if	(USARTx==UART4) {RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);}
	else if	(USARTx==UART5) {RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);}
	#endif
	
	#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F411xE) || defined(STM32F446xx) 	
	else if	(USARTx==USART6) {RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);}
	#endif
	
	#if defined(STM32F427_437xx) || defined(STM32F429_439xx)	
	else if	(USARTx==UART7) {RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);}
	else if	(USARTx==UART8) {RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8, ENABLE);}
	#endif

}

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
				)
{

	USART_InitTypeDef USART_InitStructure;
	uint8_t NVIC_IRQChannel_USART;
	uint16_t GPIO_PinSource_RX;
	uint16_t GPIO_PinSource_TX;
	uint8_t GPIO_AF;

	USART_RCC_PeriphClockCmd(USARTx);	/* ʹ�� USART ʱ�� */
	
	GPIO_Common_Init(USART_TX_GPIOx,USART_TX_PIN,GPIO_Mode_AF,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_Speed_100MHz);
	GPIO_Common_Init(USART_RX_GPIOx,USART_RX_PIN,GPIO_Mode_AF,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_Speed_100MHz);
	
	GPIO_PinSource_TX=Get_GPIO_PinSourceX(USART_TX_PIN);
	GPIO_PinSource_RX=Get_GPIO_PinSourceX(USART_RX_PIN);
	GPIO_AF=GPIO_AF_X(USARTx);
	
	/* ���� PXx �� USARTx_Tx*/
	GPIO_PinAFConfig(USART_TX_GPIOx,GPIO_PinSource_TX,GPIO_AF);

	/*  ���� PXx �� USARTx__Rx*/
	GPIO_PinAFConfig(USART_RX_GPIOx,GPIO_PinSource_RX,GPIO_AF);
	
	USART_InitStructure.USART_BaudRate = USART_BaudRate;/* ���������ã�*/	
	USART_InitStructure.USART_WordLength = USART_WordLength;/* �ֳ�(����λ+У��λ)��8 USART_WordLength_8b*/
	USART_InitStructure.USART_StopBits = USART_StopBits;	/* ֹͣλ��1��ֹͣλ USART_StopBits_1*/
	USART_InitStructure.USART_Parity = USART_Parity;	/* У��λѡ�񣺲�ʹ��У�� USART_Parity_No*/
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl	/* Ӳ�������ƣ���ʹ��Ӳ���� USART_HardwareFlowControl_None*/;
	USART_InitStructure.USART_Mode = USART_Mode;	/* USARTģʽ���ƣ�ͬʱʹ�ܽ��պͷ��� USART_Mode_Rx | USART_Mode_Tx*/
	USART_Init(USARTx, &USART_InitStructure); 	/* ���USART��ʼ������ */

	NVIC_IRQChannel_USART=Get_NVIC_IRQChannel_USART(USARTx);
	NVIC_Init_IRQChannel(NVIC_IRQChannel_USART,PreemptionPriority,SubPriority,ENABLE);//���� NVIC	

	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);	/* ʹ�ܴ��ڽ����ж� */

	USART_Cmd(USARTx, ENABLE);	/* ʹ�ܴ��� */
}


/*****************  ����һ���ַ� **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

//����һ������
void USART_SendChars(USART_TypeDef* USARTx,const uint8_t* SendChars,uint16_t len)	//����һ������
{
	uint16_t i = 0;
	for(i = 0; i < len; i++)
	{
    	USARTx->DR = (*(SendChars + i) & (uint16_t)0x01FF);
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}
}

/*****************  ����һ��16λ�� **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}


/*
  * log:

  *	2018��6��14��
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/
