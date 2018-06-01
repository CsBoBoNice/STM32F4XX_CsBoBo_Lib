#include "CsBoBo_STM32F4XX_Basic_TIM.h"
#include "CsBoBo_STM32F4XX_LIB.h"



/**********基本定时器函数使用方法***************************************************************/
/*
*********************************************************************************************

	Basic_TIM_Init(TIM7,10,9000,1,0);	//初始化定时器TIM7,1MS进入一次中断
	
	注：默认不使能定时器，用TIM_Cmd()使能定时器
	TIM_Cmd(TIM6, ENABLE);		// 计数器使能
	
*********************************************************************************************
*********************************************************************************************

	TIM_Cmd(TIM6, ENABLE);		// 计数器使能

*********************************************************************************************
*********************************************************************************************
void Basic_TIM_Init(TIM_TypeDef* TIMx,uint16_t TIM_Period,uint16_t TIM_Prescaler,uint8_t PreemptionPriority,uint8_t SubPriority)
//默认90M的时钟频率，不使能定时器

//参数1：选用的定时器
			TIM6
			TIM7
//参数2：自动重装载寄存器的值，累计TIM_Period个频率后产生一个更新或者中断 (不需要减1)
			取值范围：0——65535

//参数3：时钟预分频值(不用减1)
			取值范围：0——65535
			
//参数4：对应抢断优先级级别
			数值越低优先级越高

//参数5：对应响应优先级级别
			数值越低优先级越高
*/
/*********************************************************************************/




#if defined(STM32F40_41xxx)||defined(STM32F427_437xx)||defined(STM32F429_439xx)||defined(STM32F410xx)||defined(STM32F469_479xx) || defined(STM32F446xx)|| defined(STM32F413_423xx)
void TIM6_DAC_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
    {	
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update); /* 清除溢出中断标志 */
		/* Do anything */

    }
}
#endif

#if defined(STM32F412xG)
void TIM6_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
	{	
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update); /* 清除溢出中断标志 */
		/* Do anything */

	}
}
#endif	

#if defined(STM32F40_41xxx)||defined(STM32F427_437xx)||defined(STM32F429_439xx)||defined(STM32F469_479xx) || defined(STM32F446xx)||defined(STM32F412xG)||defined(STM32F413_423xx)
void TIM7_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
    {	
		TIM_ClearITPendingBit(TIM7,TIM_IT_Update); /* 清除溢出中断标志 */
		/* Do anything */
		
    }
}
#endif

static uint8_t Get_NVIC_IRQChannel_Basic_TIM(TIM_TypeDef* TIMx)
{
	#if defined(STM32F40_41xxx)||defined(STM32F427_437xx)||defined(STM32F429_439xx)||defined(STM32F410xx)||defined(STM32F469_479xx) || defined(STM32F446xx)|| defined(STM32F413_423xx)
	if(TIMx==TIM6)
	{
		return TIM6_DAC_IRQn;
	}
	#endif
	#if defined(STM32F412xG)
	if(TIMx==TIM6)
	{
		return TIM6_IRQn;
	}
	#endif	
	#if defined(STM32F40_41xxx)||defined(STM32F427_437xx)||defined(STM32F429_439xx)||defined(STM32F469_479xx) || defined(STM32F446xx)||defined(STM32F412xG)||defined(STM32F413_423xx)
	if(TIMx==TIM7)
	{
		return TIM7_IRQn;		
	}
	#endif	
	return 0;
}

static uint32_t RCC_APB1Periph_Basic_TIM(TIM_TypeDef* TIMx)
{
	if(TIMx==TIM6)
	{
		return RCC_APB1Periph_TIM6;
	}else if(TIMx==TIM7)
	{
		return RCC_APB1Periph_TIM7;		
	}
	return 0;
}

void Basic_TIM_Init(TIM_TypeDef* TIMx,uint16_t TIM_Period,uint16_t TIM_Prescaler,uint8_t PreemptionPriority,uint8_t SubPriority)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	uint32_t Basic_TIM_CLK=0;
	uint8_t Basic_TIM_NVIC_IRQChannel=0;
	Basic_TIM_CLK=RCC_APB1Periph_Basic_TIM(TIMx);
	
    RCC_APB1PeriphClockCmd(Basic_TIM_CLK, ENABLE);		// 开启定时器时钟,即内部时钟CK_INT=72M

	Basic_TIM_NVIC_IRQChannel=Get_NVIC_IRQChannel_Basic_TIM(TIMx);
	NVIC_Init_IRQChannel(Basic_TIM_NVIC_IRQChannel,PreemptionPriority,SubPriority,ENABLE);//配置 NVIC

	
    TIM_TimeBaseStructure.TIM_Period = TIM_Period-1;		// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Prescaler= TIM_Prescaler-1;  // 时钟预分频数为
	
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);  // 初始化定时器			
    TIM_ClearFlag(TIMx, TIM_FLAG_Update);	// 清除计数器中断标志位	  	
    TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE);	// 开启计数器中断			
    TIM_Cmd(TIMx, DISABLE);		// 计数器不使能

}



/*
  * log:

  *	2018年5月29日
	新建工程
	实现基本初始化功能
	Programmer:陈述
	
*/

