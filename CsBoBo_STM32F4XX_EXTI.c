#include "CsBoBo_STM32F4XX_EXTI.h"
#include "CsBoBo_STM32F4XX_NVIC.h"



void EXTI0_IRQHandler(void)
{		
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)//确保是否产生了EXTI Line中断 
	{
		//中断处理代码
		if(GPIO_ReadOutputDataBit(GPIOH, GPIO_Pin_11)==1)//读取指定端口管脚的输出
		{
			GPIO_ResetBits(GPIOH,GPIO_Pin_11);
		}else{
			GPIO_SetBits(GPIOH,GPIO_Pin_11);
		}
		EXTI_ClearITPendingBit(EXTI_Line0);  //清除中断标志位
	}  
}

void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)//确保是否产生了EXTI Line中断 
	{
		//中断处理代码
		
		EXTI_ClearITPendingBit(EXTI_Line1);  //清除中断标志位
	}  
}

void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)//确保是否产生了EXTI Line中断 
	{
		//中断处理代码
		
		EXTI_ClearITPendingBit(EXTI_Line2);  //清除中断标志位
	}  	
}

void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3) != RESET)//确保是否产生了EXTI Line中断 
	{
		//中断处理代码
		
		EXTI_ClearITPendingBit(EXTI_Line3);  //清除中断标志位
	}	
}

void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)//确保是否产生了EXTI Line中断 
	{
		//中断处理代码
		
		EXTI_ClearITPendingBit(EXTI_Line4);  //清除中断标志位
	}
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)//确保是否产生了EXTI Line中断 
	{
		//中断处理代码
		
		EXTI_ClearITPendingBit(EXTI_Line5);  //清除中断标志位
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)//确保是否产生了EXTI Line中断 
	{
		//中断处理代码
		
		EXTI_ClearITPendingBit(EXTI_Line6);  //清除中断标志位
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line7) != RESET)//确保是否产生了EXTI Line中断 
	{
		//中断处理代码
		
		EXTI_ClearITPendingBit(EXTI_Line7);  //清除中断标志位
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line8) != RESET)//确保是否产生了EXTI Line中断 
	{
		//中断处理代码
		
		EXTI_ClearITPendingBit(EXTI_Line8);  //清除中断标志位
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line9) != RESET)//确保是否产生了EXTI Line中断 
	{
		//中断处理代码
		
		EXTI_ClearITPendingBit(EXTI_Line9);  //清除中断标志位
	}		
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10) != RESET)//确保是否产生了EXTI Line中断 
	{
		//中断处理代码
		
		EXTI_ClearITPendingBit(EXTI_Line10);  //清除中断标志位
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line11) != RESET)//确保是否产生了EXTI Line中断 
	{
		//中断处理代码
		
		EXTI_ClearITPendingBit(EXTI_Line11);  //清除中断标志位
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line12) != RESET)//确保是否产生了EXTI Line中断 
	{
		//中断处理代码
		
		EXTI_ClearITPendingBit(EXTI_Line12);  //清除中断标志位
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line13) != RESET)//确保是否产生了EXTI Line中断 
	{
		//中断处理代码
		if(GPIO_ReadOutputDataBit(GPIOH, GPIO_Pin_12)==1)//读取指定端口管脚的输出
		{
			GPIO_ResetBits(GPIOH,GPIO_Pin_12);
		}else{
			GPIO_SetBits(GPIOH,GPIO_Pin_12);
		}		
		EXTI_ClearITPendingBit(EXTI_Line13);  //清除中断标志位
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line14) != RESET)//确保是否产生了EXTI Line中断 
	{
		//中断处理代码
		
		EXTI_ClearITPendingBit(EXTI_Line14);  //清除中断标志位
	}	
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line15) != RESET)//确保是否产生了EXTI Line中断 
	{
		//中断处理代码
		
		EXTI_ClearITPendingBit(EXTI_Line15);  //清除中断标志位
	}
}

static uint32_t Get_EXTI_Line(u16 GPIO_PIN)
{
	switch(GPIO_PIN)
	{
		case GPIO_Pin_0: return EXTI_Line0; 
		case GPIO_Pin_1: return EXTI_Line1;
		case GPIO_Pin_2: return EXTI_Line2; 
		case GPIO_Pin_3: return EXTI_Line3;
		case GPIO_Pin_4: return EXTI_Line4; 
		case GPIO_Pin_5: return EXTI_Line5;
		case GPIO_Pin_6: return EXTI_Line6; 
		case GPIO_Pin_7: return EXTI_Line7;
		case GPIO_Pin_8: return EXTI_Line8; 
		case GPIO_Pin_9: return EXTI_Line9;
		case GPIO_Pin_10: return EXTI_Line10; 
		case GPIO_Pin_11: return EXTI_Line11;
		case GPIO_Pin_12: return EXTI_Line12; 
		case GPIO_Pin_13: return EXTI_Line13;
		case GPIO_Pin_14: return EXTI_Line14; 
		case GPIO_Pin_15: return EXTI_Line15;
	}
	return 0;
}

static uint8_t Get_EXTI_PortSource(GPIO_TypeDef* GPIOx)
{
	if		(GPIOx==GPIOA){return EXTI_PortSourceGPIOA;}
	else if	(GPIOx==GPIOB){return EXTI_PortSourceGPIOB;}
	else if	(GPIOx==GPIOC){return EXTI_PortSourceGPIOC;}
	else if	(GPIOx==GPIOD){return EXTI_PortSourceGPIOD;}
	else if	(GPIOx==GPIOE){return EXTI_PortSourceGPIOE;}
	else if	(GPIOx==GPIOF){return EXTI_PortSourceGPIOF;}
	else if	(GPIOx==GPIOG){return EXTI_PortSourceGPIOG;}
	else if	(GPIOx==GPIOH){return EXTI_PortSourceGPIOH;}
	else if	(GPIOx==GPIOI){return EXTI_PortSourceGPIOI;}
	else if	(GPIOx==GPIOJ){return EXTI_PortSourceGPIOJ;}
	else if	(GPIOx==GPIOK){return EXTI_PortSourceGPIOK;}
	return 0;	
}

static uint8_t Get_EXTI_PinSource_PIN(u16 GPIO_PIN)
{
	switch(GPIO_PIN)
	{
		case GPIO_Pin_0: return EXTI_PinSource0; 
		case GPIO_Pin_1: return EXTI_PinSource1;
		case GPIO_Pin_2: return EXTI_PinSource2; 
		case GPIO_Pin_3: return EXTI_PinSource3;
		case GPIO_Pin_4: return EXTI_PinSource4; 
		case GPIO_Pin_5: return EXTI_PinSource5;
		case GPIO_Pin_6: return EXTI_PinSource6; 
		case GPIO_Pin_7: return EXTI_PinSource7;
		case GPIO_Pin_8: return EXTI_PinSource8; 
		case GPIO_Pin_9: return EXTI_PinSource9;
		case GPIO_Pin_10: return EXTI_PinSource10; 
		case GPIO_Pin_11: return EXTI_PinSource11;
		case GPIO_Pin_12: return EXTI_PinSource12; 
		case GPIO_Pin_13: return EXTI_PinSource13;
		case GPIO_Pin_14: return EXTI_PinSource14; 
		case GPIO_Pin_15: return EXTI_PinSource15;
	}
	return 0;
}

static uint8_t Get_NVIC_IRQChannel(u16 GPIO_PIN)
{
	switch(GPIO_PIN)
	{
		case GPIO_Pin_0: return EXTI0_IRQn; 
		case GPIO_Pin_1: return EXTI1_IRQn;
		case GPIO_Pin_2: return EXTI2_IRQn; 
		case GPIO_Pin_3: return EXTI3_IRQn;
		case GPIO_Pin_4: return EXTI4_IRQn; 
		case GPIO_Pin_5: return EXTI9_5_IRQn;
		case GPIO_Pin_6: return EXTI9_5_IRQn; 
		case GPIO_Pin_7: return EXTI9_5_IRQn;
		case GPIO_Pin_8: return EXTI9_5_IRQn; 
		case GPIO_Pin_9: return EXTI9_5_IRQn;
		case GPIO_Pin_10: return EXTI15_10_IRQn; 
		case GPIO_Pin_11: return EXTI15_10_IRQn;
		case GPIO_Pin_12: return EXTI15_10_IRQn; 
		case GPIO_Pin_13: return EXTI15_10_IRQn;
		case GPIO_Pin_14: return EXTI15_10_IRQn; 
		case GPIO_Pin_15: return EXTI15_10_IRQn;
	}
	return 0;
}

/*开启相关的GPIO外设时钟*/
static void RCC_AHB1PeriphClockCmd_GPIO_Init(u8 GPIOx)
{
	switch(GPIOx)
	{
		case 1:RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);return;
		case 2:RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);return;
		case 3:RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);return;
		case 4:RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);return;
		case 5:RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);return;
		case 6:RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);return;
		case 7:RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);return;
		case 8:RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);return;
		case 9:RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);return;
		case 10:RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOJ,ENABLE);return;
		case 11:RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOK,ENABLE);return;
	}
	return;
}

/*得到GPIO编号，方便初始化*/
static u8 Get_GPIO_num(GPIO_TypeDef* GPIOx)
{
	if		(GPIOx==GPIOA){return 1;}
	else if	(GPIOx==GPIOB){return 2;}
	else if	(GPIOx==GPIOC){return 3;}
	else if	(GPIOx==GPIOD){return 4;}
	else if	(GPIOx==GPIOE){return 5;}
	else if	(GPIOx==GPIOF){return 6;}
	else if	(GPIOx==GPIOG){return 7;}
	else if	(GPIOx==GPIOH){return 8;}
	else if	(GPIOx==GPIOI){return 9;}
	else if	(GPIOx==GPIOJ){return 10;}
	else if	(GPIOx==GPIOK){return 11;}
	return 0;
}

static void EXIT_Init_Config(GPIO_TypeDef* GPIOx,u16 GPIO_PIN,EXTITrigger_TypeDef  EXTI_Mode)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	uint8_t EXTI_PortSource;
	uint8_t EXTI_PortSource_PIN;
	uint32_t EXTI_Line_V;
	
	EXTI_PortSource=Get_EXTI_PortSource(GPIOx);
	EXTI_PortSource_PIN=Get_EXTI_PinSource_PIN(GPIO_PIN);
	EXTI_Line_V=Get_EXTI_Line(GPIO_PIN);
	
	/* 连接 EXTI 中断源 到key1引脚 */
	SYSCFG_EXTILineConfig(EXTI_PortSource,EXTI_PortSource_PIN);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line_V;/* 选择 EXTI 中断源 */
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;/* 中断模式 */
	EXTI_InitStructure.EXTI_Trigger = EXTI_Mode;	/* 触发方式 */  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;/* 使能中断/事件线 */
	EXTI_Init(&EXTI_InitStructure);	
}

/*****************************************************************************/
/*
	中断初始化函数
*/
void EXTIX_Init(GPIO_TypeDef* GPIOx,u16 GPIO_PIN,EXTITrigger_TypeDef  EXTI_Mode,uint8_t PreemptionPriority,uint8_t SubPriority)
{
	u8 GPIO_num;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	uint8_t exti_NVIC_IRQChannel;
	
	GPIO_num=Get_GPIO_num(GPIOx);
	RCC_AHB1PeriphClockCmd_GPIO_Init(GPIO_num);//开启相关的GPIO外设时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);	//使能 SYSCFG 时钟 ，使用GPIO外部中断时必须使能SYSCFG时钟

	exti_NVIC_IRQChannel=Get_NVIC_IRQChannel(GPIO_PIN);
	NVIC_Init_IRQChannel(exti_NVIC_IRQChannel,PreemptionPriority,SubPriority,ENABLE);//配置 NVIC

	 
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN;/*选择引脚 */	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;/* 设置引脚为输入模式 */ 	    			
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;/* 设置引脚不上拉也不下拉 */	
	GPIO_Init(GPIOx, &GPIO_InitStructure); /* 使用上面的结构体初始化*/

	EXIT_Init_Config(GPIOx,GPIO_PIN,EXTI_Mode);
}	

