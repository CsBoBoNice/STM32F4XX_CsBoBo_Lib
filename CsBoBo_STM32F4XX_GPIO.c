#include "CsBoBo_STM32F4XX_GPIO.h"
/*******使用方法***********************************************************/
/*
@例:	GPIO_Common_Init(GPIOH,GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_High_Speed);

GPIO_Common_Init(GPIO_TypeDef* GPIOx,u16 GPIO_PIN,GPIOMode_TypeDef GPIO_Mode,GPIOOType_TypeDef GPIO_OType,GPIOPuPd_TypeDef GPIO_PuPd,GPIOSpeed_TypeDef GPIO_Speed)

//参数1：		GPIO_TypeDef
					GPIOA
					GPIOB
					GPIOC
					GPIOD
					GPIOF
					GPIOG
					GPIOH
					GPIOI
					GPIOJ
					GPIOK
				
//参数2：对应引脚	
					GPIO_Pin_0
					GPIO_Pin_1
					GPIO_Pin_2
					GPIO_Pin_3
					GPIO_Pin_4
					GPIO_Pin_5
					GPIO_Pin_6
					GPIO_Pin_7
					GPIO_Pin_8
					GPIO_Pin_9
					GPIO_Pin_10
					GPIO_Pin_11
					GPIO_Pin_12
					GPIO_Pin_13
					GPIO_Pin_14
					GPIO_Pin_15

//参数3：对应模式	GPIOMode_TypeDef		描述			例子
					GPIO_Mode_IN			输入模式		按键
					GPIO_Mode_OUT			输出模式		驱动小灯
					GPIO_Mode_AF			复用模式		PWM
					GPIO_Mode_AN			模拟模式		ADC

//参数4：对应模式	GPIOOType_TypeDef		描述			例子
					GPIO_OType_PP			推挽输出		驱动小灯
					GPIO_OType_OD			开漏			IIC	
					
//参数5：对应模式	GPIOPuPd_TypeDef		描述			例子	
					GPIO_PuPd_NOPULL		浮空			按键
					GPIO_PuPd_UP			上拉			
					GPIO_PuPd_DOWN			下拉
					
注:	上(下)拉电阻在有输入的情况下，并不会导致GPIO的输入电压一直为高(低)电平。
	当输入信号不确定(即悬空时有电磁干扰)，才会将GPIO口的电压值拉高(低)。

//参数6：对应模式	GPIOSpeed_TypeDef		描述			
					GPIO_Low_Speed			GPIO_Speed_2MHz
					GPIO_Medium_Speed		GPIO_Speed_25MHz 
					GPIO_Fast_Speed			GPIO_Speed_50MHz
					GPIO_High_Speed			GPIO_Speed_100MHz
					
注:	输出速度即 I/O 支持的高低电平状态最高切换频率，
	支持的频率越高，功耗越大，如果功耗要求不严格，把速度设置成最大即可
*/



/********常用函数*****************************************************************/
/*
@例:	GPIO_ResetBits(GPIOD,GPIO_Pin_2);	//引脚拉低

@例:	GPIO_SetBits(GPIOD,GPIO_Pin_2);		//引脚置高

@例:	GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)//读取指定端口管脚的输入	

@例:	GPIO_ReadInputData(GPIOD)	//读取指定的 GPIO 端口输入

@例:	GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_2)//读取指定端口管脚的输出

@例:	GPIO_Write(GPIOD, 0x55)//向指定 GPIO 数据端口写入数据
*/
/*************************************************************************/

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

/*初始化GPIO*/
void GPIO_Common_Init	(	
							GPIO_TypeDef* GPIOx,
							u16 GPIO_PIN,
							GPIOMode_TypeDef GPIO_Mode,
							GPIOOType_TypeDef GPIO_OType,
							GPIOPuPd_TypeDef GPIO_PuPd,
							GPIOSpeed_TypeDef GPIO_Speed
						)
{	
	u8 GPIO_num;
	
	GPIO_InitTypeDef GPIO_InitStructure;	/*定义一个GPIO_InitTypeDef类型的结构体*/
	
	GPIO_num=Get_GPIO_num(GPIOx);

	RCC_AHB1PeriphClockCmd_GPIO_Init(GPIO_num);	/*开启相关的GPIO外设时钟*/
																   
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN;	/*选择要控制的GPIO引脚*/
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode;   /*设置引脚模式*/
	
	GPIO_InitStructure.GPIO_OType = GPIO_OType;	/*设置引脚的输出类型*/
	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd;	/*设置引脚为上拉/下拉模式*/
	   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed;	/*设置引脚速率*/ 
	
	GPIO_Init(GPIOx, &GPIO_InitStructure);	/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/	
}


/*
  * log:

  *	2018年6月14日
	实现基本初始化功能
	Programmer:陈述
	
*/


