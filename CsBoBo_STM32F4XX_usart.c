#include "CsBoBo_STM32F4XX_usart.h"
#include "CsBoBo_STM32F4XX_LIB.h"


/*

@例:	
		USART_init(	USART2,
					GPIOD,GPIO_Pin_5,	
					GPIOD,GPIO_Pin_6,
					9600,					//波特率
					USART_WordLength_8b,	//8位字长 字长(数据位+校验位)
					USART_StopBits_1,		//停止位 1	位
					USART_Parity_No,		//不使用校验
					USART_Mode_Rx | USART_Mode_Tx,	//接收和发送模式
					USART_HardwareFlowControl_None,	//硬件流控制失能
					0,0
					);

	参数1：USART编号
						USART1
						USART2
						USART3
						UART4
						UART5
						USART6
						UART7
						UART8
	参数2：TX GPIO 

	参数3：TX GPIO_Pin

	参数4：RX GPIO 

	参数5：RX GPIO_Pin 

			串口引脚:	(同一个串口引脚可随意搭配，例如: TX(PA9) RX(PB7) )
			串口		TX		RX
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
			
			
	参数6：波特率取值范围(600,1200,2400,4800,9600,14400,19200,28800,38400,57600,115200,230400,460800)
	
	参数7：字长(数据位+校验位)
			USART_WordLength_8b		8位字长
			USART_WordLength_9b		9位字长

	参数8：停止位
			USART_StopBits_1		停止位 1	位
			USART_StopBits_0_5		停止位 0.5	位
			USART_StopBits_2		停止位 2	位
			USART_StopBits_1_5		停止位 1.5	位

	参数9：校验位选择
			USART_Parity_No			不使用校验
			USART_Parity_Even		偶校验
			USART_Parity_Odd		奇校验

	参数10：USART模式控制：
			USART_Mode_Tx		发送模式
			USART_Mode_Rx		接收模式
			USART_Mode_Rx | USART_Mode_Tx	接收和发送模式
	
	参数11：硬件流控制：
			USART_HardwareFlowControl_None		硬件流控制失能
			USART_HardwareFlowControl_RTS		发送请求RTS使能
			USART_HardwareFlowControl_CTS		清除发送CTS使能
			USART_HardwareFlowControl_RTS_CTS	RTS和CTS使能

	参数12：对应抢断优先级级别	数值越低优先级越高

	参数13：对应响应优先级级别	数值越低优先级越高
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
				)
{

	USART_InitTypeDef USART_InitStructure;
	uint8_t NVIC_IRQChannel_USART;
	uint16_t GPIO_PinSource_RX;
	uint16_t GPIO_PinSource_TX;
	uint8_t GPIO_AF;

	USART_RCC_PeriphClockCmd(USARTx);	/* 使能 USART 时钟 */
	
	GPIO_Common_Init(USART_TX_GPIOx,USART_TX_PIN,GPIO_Mode_AF,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_Speed_100MHz);
	GPIO_Common_Init(USART_RX_GPIOx,USART_RX_PIN,GPIO_Mode_AF,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_Speed_100MHz);
	
	GPIO_PinSource_TX=Get_GPIO_PinSourceX(USART_TX_PIN);
	GPIO_PinSource_RX=Get_GPIO_PinSourceX(USART_RX_PIN);
	GPIO_AF=GPIO_AF_X(USARTx);
	
	/* 连接 PXx 到 USARTx_Tx*/
	GPIO_PinAFConfig(USART_TX_GPIOx,GPIO_PinSource_TX,GPIO_AF);

	/*  连接 PXx 到 USARTx__Rx*/
	GPIO_PinAFConfig(USART_RX_GPIOx,GPIO_PinSource_RX,GPIO_AF);

	
	USART_InitStructure.USART_BaudRate = USART_BaudRate;/* 波特率设置：*/
	
	USART_InitStructure.USART_WordLength = USART_WordLength;/* 字长(数据位+校验位)：8 USART_WordLength_8b*/

	USART_InitStructure.USART_StopBits = USART_StopBits;	/* 停止位：1个停止位 USART_StopBits_1*/

	USART_InitStructure.USART_Parity = USART_Parity;	/* 校验位选择：不使用校验 USART_Parity_No*/

	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl	/* 硬件流控制：不使用硬件流 USART_HardwareFlowControl_None*/;

	USART_InitStructure.USART_Mode = USART_Mode;	/* USART模式控制：同时使能接收和发送 USART_Mode_Rx | USART_Mode_Tx*/

	USART_Init(USARTx, &USART_InitStructure); 	/* 完成USART初始化配置 */

	NVIC_IRQChannel_USART=Get_NVIC_IRQChannel(USARTx);
	NVIC_Init_IRQChannel(NVIC_IRQChannel_USART,PreemptionPriority,SubPriority,ENABLE);//配置 NVIC	

	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);	/* 使能串口接收中断 */


	USART_Cmd(USARTx, ENABLE);	/* 使能串口 */
}


/*****************  发送一个字符 **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  发送字符串 **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* 等待发送完成 */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  发送一个16位数 **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* 取出高八位 */
	temp_h = (ch&0XFF00)>>8;
	/* 取出低八位 */
	temp_l = ch&0XFF;
	
	/* 发送高八位 */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* 发送低八位 */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}



