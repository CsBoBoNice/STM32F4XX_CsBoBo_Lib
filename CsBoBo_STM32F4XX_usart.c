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
/******************************************************************************************************************/
/************************************************************************
@注:

	接收串口数据通过中断接收，通过定时器判断是否超时，
在CsBoBo_STM32F10X_usart.h里设置超时时间，与接收缓存区大小,如果未用到的串口可以注释，节约内存，

以下为定时器添加超时算法的代码:

#if defined (USING_USART1) || defined (USING_USART2) || defined (USING_USART3)|| defined (USING_UART4)|| defined (USING_UART5)
USART_ReceiveOvertimeProcess();
#endif


以下是使用带超时的串口接收代码

NVIC_Configuration(NVIC_PriorityGroup_4);//设置优先级分组：抢断优先级和相应优先级
TIM_Common_Init(2,7200,10,TIM_CounterMode_Up,3,0);	//定时器初始化 1MS
USART_init(1,115200,0,3,0);	//串口初始化

if(Get_USART_ready_buf_ok(USART1))	//判断超时，一帧数据接收成功
{
	Clean_USART_ready_buf_OK(USART1);//清除串口是否接收完毕标志
	
	USART_SendChars(USART1,USART1_ready_buf,USART1_ready_buf_len);	//回发
	
	Clean_USART_ready_buf(USART1);//清除串口缓存数据
}

USART1_ready_buf 接收到的数据
USART1_ready_buf_len 接收数据长度
*/
#ifdef USING_USART1
uint8_t USART1_receive_buf[USART1_BUF_SIZE];	//数据接收缓存区
uint8_t USART1_ready_buf[USART1_BUF_SIZE];		//接收成功后的数据区
static int32_t USART1_ReceiveTimeCounter = 0;	//超时剩余时间
__IO uint16_t USART1_receive_index=0; 		//正在接收的数据长度
__IO uint8_t USART1_ready_buf_ok = 0;		//是否成功接收
__IO uint16_t USART1_ready_buf_len = 0;		//成功接收后的数据长度
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
uint8_t USART6_receive_buf[USART6_BUF_SIZE];	//数据接收缓存区
uint8_t USART6_ready_buf[USART6_BUF_SIZE];		//接收成功后的数据区
static int32_t USART6_ReceiveTimeCounter = 0;	//超时剩余时间
__IO uint16_t USART6_receive_index=0; 		//正在接收的数据长度
__IO uint8_t USART6_ready_buf_ok = 0;		//是否成功接收
__IO uint16_t USART6_ready_buf_len = 0;		//成功接收后的数据长度
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

void USART1_ISR(void); //串口中断函数
void USART2_ISR(void); //串口中断函数
void USART3_ISR(void); //串口中断函数
void UART4_ISR(void); //串口中断函数
void UART5_ISR(void); //串口中断函数
void USART6_ISR(void); //串口中断函数
void UART7_ISR(void); //串口中断函数
void UART8_ISR(void); //串口中断函数

/**********************中断函数***************************************************************************************************/
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

/**********************串口1中断接收一个字符***************************************************************************************************/
/*
在中断服务程序中，由于主机响应中断时并不知道是哪个中断源发出中断请求，
因此必须在中断服务程序中对中断源进行判别，然后分别进行处理。
当然，如果只涉及到一个中断请求，是不用做上述判别的。但是无论什么情况，做上述判别是个好习惯
*/
#ifdef USING_USART1
void USART1_ISR(void)   
{

	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//判断是否是中断
	{
		USART1_ReceiveTimeCounter = USART1_RECEIVE_OVERTIME;

		if(USART1_receive_index >= USART1_BUF_SIZE)//若接收位置越界，那么重头开始存放
			USART1_receive_index = 0;
		
		USART1_receive_buf[USART1_receive_index++] = (uint8_t)USART_ReceiveData(USART1);//接收字符，并位置加1		
	}	
	if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)//过载处理，只要读状态寄存器和数据寄存器就可自动清理此标志
	{
		(void)USART_ReceiveData(USART1);
	}

} 
#endif

#ifdef USING_USART2
void USART2_ISR(void)
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //判断是否是中断
	{	
		USART2_ReceiveTimeCounter = USART2_RECEIVE_OVERTIME;
		
		if(USART2_receive_index >= USART2_BUF_SIZE)	//若接收位置越界，那么重头开始存放
			USART2_receive_index = 0;
		
		USART2_receive_buf[USART2_receive_index++] = (uint8_t)USART_ReceiveData(USART2);//接收字符，并位置加1
		
	}		
	if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)//过载处理，只要读状态寄存器和数据寄存器就可自动清理此标志
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

//在中断中执行的代码
void USART_ReceiveOvertimeProcess(void)		//在中断中执行的代码
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

//判断串口是否接收完毕
//接收成功返回 UART_OK
//接收失败返回 UART_ERROR
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

//清除串口是否接收完毕标志
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

//清除串口缓存数据
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

	NVIC_IRQChannel_USART=Get_NVIC_IRQChannel_USART(USARTx);
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

//发送一串数据
void USART_SendChars(USART_TypeDef* USARTx,const uint8_t* SendChars,uint16_t len)	//发送一串数据
{
	uint16_t i = 0;
	for(i = 0; i < len; i++)
	{
    	USARTx->DR = (*(SendChars + i) & (uint16_t)0x01FF);
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}
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


/*
  * log:

  *	2018年6月14日
	实现基本初始化功能
	Programmer:陈述
	
*/
