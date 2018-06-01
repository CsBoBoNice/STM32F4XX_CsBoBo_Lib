#include "CsBoBo_STM32F4XX_systick.h"
/**********使用方法***************************************************************/
/*

*********************************************************************************************
	SysTick_delay_init(1000);	//初始化SysTick定时器中断 每 1000um 中断一次
	
	当用freeROTS时用以下初始化SysTick
	SysTick_delay_init(SYSTEMTICK_PERIOD_MS);	//初始化SysTick定时器中断 每1/configTICK_RATE_HZ秒中断一次
*********************************************************************************************
*********************************************************************************************
	delay_us(1024);//精确延时函数
	delay_ms(1024);//精确延时函数
*********************************************************************************************
*********************************************************************************************
	//SysTick定时器中断函数在 stm32f10x_it.c 中
	SysTick_Handler(void)
*********************************************************************************************
*********************************************************************************************
注意:SysTick定时器中断与精确延时函数冲突，不能同时使用！！！	
*/
/*********************************************************************************/

static u8 fac_us=0;//us延时倍乘数

//初始化SysTick
//SYSTICK的时钟固定为AHB时钟！
// 配置中断优先级为 1<<4-1 = 15，优先级为最低
// 配置systick 的时钟为 SYSTICK的时钟频率改为AHB的频率
// 使能中断
// 使能systick
void SysTick_delay_init(uint32_t SysTick_IRQn_Tim)
{
	//在库函数SysTick_Config()中已经将SYSTICK的时钟频率改为AHB的频率
	//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);//选择外部时钟  HCLK 将SYSTICK的时钟频率改为AHB的频率
	/*
	SysTick_Config(SystemCoreClock / 1000)		1ms中断一次
	SysTick_Config(SystemCoreClock / 100000)	10us中断一次
	SysTick_Config(SystemCoreClock / 1000000)	1us中断一次
	*/
	if (SysTick_Config(SystemCoreClock / 1000000 * SysTick_IRQn_Tim))	// ST3.5.0库版本
	{ 
		while (1);		/* Capture error */ 
	}
	if(SysTick->CTRL&SysTick_CTRL_CLKSOURCE_Msk)
	{
		fac_us=SystemCoreClock/1000000;
	}
	else
	{
		fac_us=SystemCoreClock/1000000/8;
	}

}	
		    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; //开始倒数 	
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	 
}
	
void delay_ms(u16 nms)
{	 		  	  
	while(nms)
	{
		nms--;
		delay_us(1000-1);	//此处减1更精确
	}

}

/*
  * log:
  *	2018年5月29日
	将精确延时函数加上，有的地方还是需要精确延时的
	Programmer:陈述

  *	2018年5月18日
	修改了SysTick初始化函数，使用官方库函数初始化
	修改延时函数 去除旧的延时函数，新增加SysTick_delay_cycle()精确延时函数
	Programmer:陈述

  *	2018年5月18日
	新建工程
	实现基本初始化功能
	Programmer:陈述
	
*/

