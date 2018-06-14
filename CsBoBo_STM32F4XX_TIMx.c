#include "CsBoBo_STM32F4XX_TIMx.h"
#include "CsBoBo_STM32F4XX_LIB.h"



/**********基本定时器函数使用方法***************************************************************/
/*
*********************************************************************************************

	TIMx_Init(TIM2,9000,10000,TIM_CounterMode_Up,0,0,ENABLE);	//定时器初始化	
	//定时器2，预分频7200,1秒进入一次中断，向上计数模式，抢断优先级级别0，响应优先级级别0
	
	注：默认不使能定时器，用TIM_Cmd()使能定时器
	TIM_Cmd(TIM2, ENABLE);		// 计数器使能
	
*********************************************************************************************
*********************************************************************************************

	TIM_Cmd(TIM2, ENABLE);		// 计数器使能

*********************************************************************************************
*********************************************************************************************
*/
/*
TIMx_Init(TIM_TypeDef * TIMx,uint16_t TIM_Prescaler,uint16_t TIM_Period,uint16_t TIM_CounterMode,uint8_t PreemptionPriority,uint8_t SubPriority)

//默认90M的时钟频率，不使能定时器

//参数1：选用的定时器
			TIM2
			TIM3
			TIM4
			TIM5
			
//参数2：时钟预分频值(不用减1)
			取值范围：0——65535
			
//参数3：自动重装载寄存器的值，累计TIM_Period个频率后产生一个更新或者中断 (不需要减1)
			取值范围：0——65535
			
//参数4：计数模式
				TIM_CounterMode_Up 				TIM 向上计数模式
				TIM_CounterMode_Down 			TIM 向下计数模式
				TIM_CounterMode_CenterAligned1 	TIM 中央对齐模式 1 计数模式
				TIM_CounterMode_CenterAligned2 	TIM 中央对齐模式 2 计数模式
				TIM_CounterMode_CenterAligned3 	TIM 中央对齐模式 3 计数模式
				
//参数4：对应抢断优先级级别
			数值越低优先级越高

//参数5：对应响应优先级级别
			数值越低优先级越高
			
*/
/********************************************************************************/
/***中断函数**********************************************************************/

#if defined(STM32F40_41xxx)||defined(STM32F427_437xx)||defined(STM32F429_439xx)||defined(STM32F401xx) || defined(STM32F411xE)||defined(STM32F469_479xx)||defined(STM32F446xx)||defined(STM32F412xG)||defined(STM32F413_423xx)
void TIM2_IRQHandler(void)
{ 
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {	
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update); /* 清除溢出中断标志 */
		/* Do anything */
		if(GPIO_ReadOutputDataBit(GPIOH, GPIO_Pin_11)==0)
		{
			PHout(11)=1;
		}else{
			PHout(11)=0;
		}		
    }
	
}
void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update); /* 清除溢出中断标志 */
		/* Do anything */
    }	
}

void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update); /* 清除溢出中断标志 */
		/* Do anything */
    }	
}

void TIM5_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
    {
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update); /* 清除溢出中断标志 */
		/* Do anything */
    }	
}
#endif

/********************************************************************************/
/********************************************************************************/
static uint8_t Get_NVIC_IRQChannel_TIMx(TIM_TypeDef* TIMx)
{
	#if defined(STM32F40_41xxx)||defined(STM32F427_437xx)||defined(STM32F429_439xx)||defined(STM32F401xx) || defined(STM32F411xE)||defined(STM32F469_479xx)||defined(STM32F446xx)||defined(STM32F412xG)||defined(STM32F413_423xx)
	if(TIMx==TIM2)
	{
		return TIM2_IRQn;
	}
	if(TIMx==TIM3)
	{
		return TIM3_IRQn;
	}	
	if(TIMx==TIM4)
	{
		return TIM4_IRQn;
	}
	if(TIMx==TIM5)
	{
		return TIM5_IRQn;
	}
	#endif

	return 0;
}

static uint32_t RCC_APB1Periph_TIMx(TIM_TypeDef* TIMx)
{
	#if defined(STM32F40_41xxx)||defined(STM32F427_437xx)||defined(STM32F429_439xx)||defined(STM32F401xx) || defined(STM32F411xE)||defined(STM32F469_479xx)||defined(STM32F446xx)||defined(STM32F412xG)||defined(STM32F413_423xx)
	if(TIMx==TIM2)
	{
		return RCC_APB1Periph_TIM2;
	}
	if(TIMx==TIM3)
	{
		return RCC_APB1Periph_TIM3;
	}	
	if(TIMx==TIM4)
	{
		return RCC_APB1Periph_TIM4;
	}
	if(TIMx==TIM5)
	{
		return RCC_APB1Periph_TIM5;
	}
	#endif
	return 0;
}

void TIMx_Init_Complete(	
							TIM_TypeDef * TIMx,
							uint16_t TIM_Prescaler,
							uint16_t TIM_Period,
							uint16_t TIM_CounterMode,
							FunctionalState NVIC_IRQChannelCmd,
							uint8_t PreemptionPriority,
							uint8_t SubPriority
						)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	uint32_t TIMx_CLK=0;
	uint8_t TIMx_NVIC_IRQChannel=0;
	TIMx_CLK=RCC_APB1Periph_TIMx(TIMx);
	
    RCC_APB1PeriphClockCmd(TIMx_CLK, ENABLE);		// 开启定时器时钟,即内部时钟CK_INT=90M

	if(NVIC_IRQChannelCmd==ENABLE)
	{
		TIMx_NVIC_IRQChannel=Get_NVIC_IRQChannel_TIMx(TIMx);
		NVIC_Init_IRQChannel(TIMx_NVIC_IRQChannel,PreemptionPriority,SubPriority,NVIC_IRQChannelCmd);//配置 NVIC	
	}
	
    TIM_TimeBaseStructure.TIM_Period = TIM_Period-1;		// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Prescaler= TIM_Prescaler-1;  // 时钟预分频数为
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode; // 计数器计数模式，设置为向上计数			
		
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;// 时钟分频因子 ，没用到不用管				
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;// 重复计数器的值，没用到不用管	
	
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);  // 初始化定时器			
    TIM_ClearFlag(TIMx, TIM_FLAG_Update);	// 清除计数器中断标志位	  	
    TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE);	// 开启计数器中断			
    TIM_Cmd(TIMx, DISABLE);		// 计数器不使能	

}

void TIMx_Init(TIM_TypeDef * TIMx,uint16_t TIM_Prescaler,uint16_t TIM_Period,uint16_t TIM_CounterMode,uint8_t PreemptionPriority,uint8_t SubPriority)
{
	TIMx_Init_Complete(TIMx,TIM_Prescaler,TIM_Period,TIM_CounterMode,ENABLE,PreemptionPriority,SubPriority);
}

/*
  * log:

  *	2018年4月27日
	优化条件编译，让代码适应STM32F10X全系列芯片
	Programmer:陈述

  *	2018年4月6日
	修复了初始化定时器后马上进入一次定时器的问题
	删除了中断优先级初始化，在CsBoBo_STM32F10X_nvic.c中统一初始化
	Programmer:陈述

  *	2016年7月7日
	新建工程
	实现基本初始化功能
	Programmer:陈述
	
*/

