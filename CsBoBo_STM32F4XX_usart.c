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

void USART1_IRQHandler(void)
{
  uint8_t ucTemp;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{		
		ucTemp = USART_ReceiveData( USART1 );
		USART_SendData(USART1,ucTemp);    
	}	 
}

void USART2_IRQHandler(void)
{
  uint8_t ucTemp;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
	{		
		ucTemp = USART_ReceiveData( USART2 );
		USART_SendData(USART2,ucTemp);    
	}	 
}


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

static uint8_t Get_NVIC_IRQChannel(USART_TypeDef * USARTx)
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

	NVIC_IRQChannel_USART=Get_NVIC_IRQChannel(USARTx);
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



