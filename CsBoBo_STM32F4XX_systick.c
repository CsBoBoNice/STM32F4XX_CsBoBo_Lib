#include "CsBoBo_STM32F4XX_systick.h"
#include "CsBoBo_STM32F4XX_NVIC.h"
/**********使用方法***************************************************************/
/*
	SysTick_delay_init(1000);	//初始化SysTick定时器中断 每 1000um 中断一次

	当用freeROTS时用以下初始化SysTick
	SysTick_delay_init(SYSTEMTICK_PERIOD_MS);	//初始化SysTick定时器中断 每1/configTICK_RATE_HZ秒中断一次

	SysTick_delay_cycle(6);	//延时 6 个SysTick中断周期

	SysTick_Handler(void)//SysTick定时器中断函数在 stm32f10x_it.c 中
	
	在SysTick_Handler()函数中加入 TimingDelay_Decrement();
	//extern void TimingDelay_Decrement(void);	
	//void SysTick_Handler(void)
	//{
	//	TimingDelay_Decrement();
	//}
*/

/*********************************************************************************/
/*************************************************************************/
static __IO u32 TimingDelay;	//在中断中递减的数	

//初始化SysTick
//SYSTICK的时钟固定为AHB时钟
//这里为了兼容FreeRTOS，所以将SYSTICK的时钟频率改为AHB的频率！

// 配置中断优先级为 1<<4-1 = 15，优先级为最低
// 配置systick 的时钟为 72M
// 使能中断
// 使能systick
void SysTick_delay_init(uint32_t SysTick_IRQn_Tim)
{
	//在库函数SysTick_Config()中已经将SYSTICK的时钟频率改为AHB的频率
	//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);//选择外部时钟  HCLK 将SYSTICK的时钟频率改为AHB的频率
	if (SysTick_Config(SystemCoreClock / 1000000 * SysTick_IRQn_Tim))	// ST3.5.0库版本
	{ 
		/* Capture error */ 
		while (1);
	}	
}	
/*
SysTick_Config(SystemCoreClock / 1000)		1ms中断一次
SysTick_Config(SystemCoreClock / 100000)	10us中断一次
SysTick_Config(SystemCoreClock / 1000000)	1us中断一次
*/
//// 这个 固件库函数 在 core_cm3.h中
//static __INLINE uint32_t SysTick_Config(uint32_t ticks)
//{ 
//  // reload 寄存器为24bit，最大值为2^24
//	if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);
//  
//  // 配置 reload 寄存器的初始值	
//  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;
//	
//	// 配置中断优先级为 1<<4-1 = 15，优先级为最低
//  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1); 
//	
//	// 配置 counter 计数器的值
//  SysTick->VAL   = 0;
//	
//	// 配置systick 的时钟为 72M
//	// 使能中断
//	// 使能systick
//  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | 
//                   SysTick_CTRL_TICKINT_Msk   | 
//                   SysTick_CTRL_ENABLE_Msk;                    
//  return (0); 
//}

//延时nTime个SysTick中断周期
void SysTick_delay_cycle(u16 nTime)
{
	TimingDelay = nTime;	

	// 使能滴答定时器  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
}

/**
  * @brief  获取节拍程序
  * @attention  在 SysTick 中断函数 SysTick_Handler()调用
  */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}

/*
  * log:
  *	2018年5月18日
	修改了SysTick初始化函数，使用官方库函数初始化
	修改延时函数 去除旧的延时函数，新增加SysTick_delay_cycle()精确延时函数
	Programmer:陈述

  *	2018年5月18日
	新建工程
	实现基本初始化功能
	Programmer:陈述
	
*/

