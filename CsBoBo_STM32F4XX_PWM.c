#include "CsBoBo_STM32F4XX_PWM.h"
#include "CsBoBo_STM32F4XX_LIB.h"



/*
	TIM_PWM_Init(	TIM2,
					GPIOA,
					GPIO_Pin_0,
					90,
					20000,
					TIM_CounterMode_Up,
					TIM_OCMode_PWM1,
					2300,
					TIM_OCPolarity_High,
					1
				);
*/
/*
//默认90M的时钟频率

//参数1：选用的定时器
			TIM2
			TIM3
			TIM4
			TIM5

//参数2：TIM GPIO 

//参数3：TIM GPIO_Pin

//参数4：时钟预分频值(不用减1)
			取值范围：0——65535
			
//参数5：自动重装载寄存器的值，累计TIM_Period个频率后产生一个更新或者中断 (不需要减1)
			取值范围：0——65535
			
//参数6：计数模式
				TIM_CounterMode_Up 				TIM 向上计数模式
				TIM_CounterMode_Down 			TIM 向下计数模式
				TIM_CounterMode_CenterAligned1 	TIM 中央对齐模式 1 计数模式
				TIM_CounterMode_CenterAligned2 	TIM 中央对齐模式 2 计数模式
				TIM_CounterMode_CenterAligned3 	TIM 中央对齐模式 3 计数模式
//参数7：比较输出模式选择
				TIM_OCMode_Timing 		(输出比较时间模式)	比较成功后不在对应输出管脚上产生输出
				TIM_OCMode_Active		(输出比较主动模式)	匹配时设置输出引脚为有效电平，当计数值为比较/捕获寄存器值相同时，强制输出为高电平
				TIM_OCMode_Inactive		(输出比较非主动模式)	匹配时设置输出引脚为无效电平，当计数值为比较/捕获寄存器值相同时，强制输出为低电平
				TIM_OCMode_Toggle		(输出比较触发模式)	比较成功后翻转对应输出管脚上的电平
				TIM_OCMode_PWM1			计数器 CNT 计算方式为递增 CNT<CCR，通道 CH 为有效，否则为无效
										计数器 CNT 计算方式为递减 CNT>CCR，通道 CH 为无效，否则为有效
				TIM_OCMode_PWM2			计数器 CNT 计算方式为递增 CNT<CCR，通道 CH 为无效，否则为有效
										计数器 CNT 计算方式为递减 CNT>CCR，通道 CH 为有效，否则为无效

//参数8：TIM_Pulse	比较输出脉冲宽度
				实际设定比较寄存器 CCR 的值，决定脉冲宽度
				取值范围：0——65535

//参数9：TIM_OCPolarity	比较输出极性
				可选 OCx 为高电平有效或低电平有效。它决定着定时器通道有效电平。
				它设定 CCER 寄存器的 CCxP 位的值。

//参数10：输出通道初始化
				取值范围1——4
*/
/*
----------------------------------------------------|
定时器		通道	CH1		CH2		CH3		CH4		|
----------------------------------------------------|
TIM2				PA0		PA1		PA2		PA3		|
					PA5		PB3		PB10	PB11	|
					PA15							|
----------------------------------------------------|
TIM3				PA6		PA7		PB0		PB1		|
					PC6		PC7		PC8		PC9		|
					PB4		PB5						|
----------------------------------------------------|
TIM4				PD12	PD13	PD14	PD15	|
					PB6		PB7		PB8		PB9		|
----------------------------------------------------|
TIM5				PA0		PA1		PA2		PA3		|
					PH10	PH11	PH12	PH13	|
----------------------------------------------------|					
TIM9				PE5		PE6						|
					PA2		PA3						|
----------------------------------------------------|
TIM10				PF6								|
					PB8								|
----------------------------------------------------|
TIM11				PF7								|
					PB9								|
----------------------------------------------------|					
TIM12				PH6		PH9						|
					PB14	PB15					|
----------------------------------------------------|					
TIM13				PF8								|
					PA6								|
----------------------------------------------------|
TIM14				PA7								|
					PF9								|
----------------------------------------------------|
*/


static uint8_t Get_GPIO_PinSourceX(u16 GPIO_PIN)
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

static uint8_t Get_GPIO_AF(TIM_TypeDef * TIMx)
{

	if(TIMx==TIM2){return GPIO_AF_TIM2;}
	if(TIMx==TIM3){return GPIO_AF_TIM3;}
	if(TIMx==TIM4){return GPIO_AF_TIM4;}
	if(TIMx==TIM5){return GPIO_AF_TIM5;}

	if(TIMx==TIM9){return GPIO_AF_TIM9;}
	if(TIMx==TIM10){return GPIO_AF_TIM10;}
	if(TIMx==TIM11){return GPIO_AF_TIM11;}
	if(TIMx==TIM12){return GPIO_AF_TIM12;}
	if(TIMx==TIM13){return GPIO_AF_TIM13;}
	if(TIMx==TIM14){return GPIO_AF_TIM14;}
	return 0;
}

void TIM_PWM_Init(	TIM_TypeDef * TIMx,
					GPIO_TypeDef* GPIOx,
					u16 GPIO_PIN,
					uint16_t TIM_Prescaler,
					uint16_t TIM_Period,
					uint16_t TIM_CounterMode,
					uint16_t TIM_OCMode,
					uint32_t TIM_Pulse,
					uint16_t TIM_OCPolarity,
					u16 TIM_channeX
				)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	uint16_t PWM_GPIO=0; 
	uint8_t GPIO_AF=0;
	TIMx_Init_Complete(TIMx,TIM_Prescaler,TIM_Period,TIM_CounterMode,ENABLE,0,0);
	GPIO_Common_Init(GPIOx,GPIO_PIN,GPIO_Mode_AF,GPIO_OType_PP,GPIO_PuPd_NOPULL,GPIO_Speed_100MHz);
	
	PWM_GPIO=Get_GPIO_PinSourceX(GPIO_PIN);
	GPIO_AF = Get_GPIO_AF(TIMx);
	GPIO_PinAFConfig(GPIOx,PWM_GPIO,GPIO_AF); /* 定时器通道引脚复用 */
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode;	    //配置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse = TIM_Pulse-1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity;  	  //当定时器计数值小于CCR1_Val时为高电平
	
	switch(TIM_channeX)
	{
		case 1:TIM_OC1Init(TIMx, &TIM_OCInitStructure);break; //使能通道1
		case 2:TIM_OC2Init(TIMx, &TIM_OCInitStructure);break; //使能通道2
		case 3:TIM_OC3Init(TIMx, &TIM_OCInitStructure);break; //使能通道3
		case 4:TIM_OC4Init(TIMx, &TIM_OCInitStructure);break; //使能通道4
	}
	// 使能定时器
	TIM_Cmd(TIMx, ENABLE);
	
}

/*
  * log:

  *	2018年6月14日
	实现基本初始化功能
	Programmer:陈述
	
*/
