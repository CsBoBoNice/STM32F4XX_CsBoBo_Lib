#include "CsBoBo_STM32F4XX_NVIC.h"
/*//取值范围:
  *   This parameter can be one of the following values:
  *     @arg NVIC_PriorityGroup_0: 0 bits for pre-emption priority
  *                                4 bits for subpriority
  *     @arg NVIC_PriorityGroup_1: 1 bits for pre-emption priority
  *                                3 bits for subpriority
  *     @arg NVIC_PriorityGroup_2: 2 bits for pre-emption priority
  *                                2 bits for subpriority
  *     @arg NVIC_PriorityGroup_3: 3 bits for pre-emption priority
  *                                1 bits for subpriority
  *     @arg NVIC_PriorityGroup_4: 4 bits for pre-emption priority
  *                                0 bits for subpriority
*/
//设置优先级分组：抢断优先级和相应优先级 (默认：4个抢断优先级，4个相应优先级)
void NVIC_Configuration(uint32_t NVIC_PriorityGroup)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup);
}

//初始化中断线
void NVIC_Init_IRQChannel(	uint8_t NVIC_IRQChannel,\
							uint8_t NVIC_IRQChannelPreemptionPriority,\
							uint8_t NVIC_IRQChannelSubPriority,\
							FunctionalState NVIC_IRQChannelCmd\
							)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 配置中断源*/
  NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQChannel;
  /* 配置抢占优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;
  /* 配置子优先级*/
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriority;
  /* 使能中断通道*/
  NVIC_InitStructure.NVIC_IRQChannelCmd = NVIC_IRQChannelCmd;
	
  NVIC_Init(&NVIC_InitStructure);

}


/*
  * log:

  *	2018年5月13日
	新建工程
	实现基本初始化功能
	Programmer:陈述
	
*/

