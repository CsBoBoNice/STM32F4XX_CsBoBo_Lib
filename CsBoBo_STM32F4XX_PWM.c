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
//Ĭ��90M��ʱ��Ƶ��

//����1��ѡ�õĶ�ʱ��
			TIM2
			TIM3
			TIM4
			TIM5

//����2��TIM GPIO 

//����3��TIM GPIO_Pin

//����4��ʱ��Ԥ��Ƶֵ(���ü�1)
			ȡֵ��Χ��0����65535
			
//����5���Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period��Ƶ�ʺ����һ�����»����ж� (����Ҫ��1)
			ȡֵ��Χ��0����65535
			
//����6������ģʽ
				TIM_CounterMode_Up 				TIM ���ϼ���ģʽ
				TIM_CounterMode_Down 			TIM ���¼���ģʽ
				TIM_CounterMode_CenterAligned1 	TIM �������ģʽ 1 ����ģʽ
				TIM_CounterMode_CenterAligned2 	TIM �������ģʽ 2 ����ģʽ
				TIM_CounterMode_CenterAligned3 	TIM �������ģʽ 3 ����ģʽ
//����7���Ƚ����ģʽѡ��
				TIM_OCMode_Timing 		(����Ƚ�ʱ��ģʽ)	�Ƚϳɹ����ڶ�Ӧ����ܽ��ϲ������
				TIM_OCMode_Active		(����Ƚ�����ģʽ)	ƥ��ʱ�����������Ϊ��Ч��ƽ��������ֵΪ�Ƚ�/����Ĵ���ֵ��ͬʱ��ǿ�����Ϊ�ߵ�ƽ
				TIM_OCMode_Inactive		(����ȽϷ�����ģʽ)	ƥ��ʱ�����������Ϊ��Ч��ƽ��������ֵΪ�Ƚ�/����Ĵ���ֵ��ͬʱ��ǿ�����Ϊ�͵�ƽ
				TIM_OCMode_Toggle		(����Ƚϴ���ģʽ)	�Ƚϳɹ���ת��Ӧ����ܽ��ϵĵ�ƽ
				TIM_OCMode_PWM1			������ CNT ���㷽ʽΪ���� CNT<CCR��ͨ�� CH Ϊ��Ч������Ϊ��Ч
										������ CNT ���㷽ʽΪ�ݼ� CNT>CCR��ͨ�� CH Ϊ��Ч������Ϊ��Ч
				TIM_OCMode_PWM2			������ CNT ���㷽ʽΪ���� CNT<CCR��ͨ�� CH Ϊ��Ч������Ϊ��Ч
										������ CNT ���㷽ʽΪ�ݼ� CNT>CCR��ͨ�� CH Ϊ��Ч������Ϊ��Ч

//����8��TIM_Pulse	�Ƚ����������
				ʵ���趨�ȽϼĴ��� CCR ��ֵ������������
				ȡֵ��Χ��0����65535

//����9��TIM_OCPolarity	�Ƚ��������
				��ѡ OCx Ϊ�ߵ�ƽ��Ч��͵�ƽ��Ч���������Ŷ�ʱ��ͨ����Ч��ƽ��
				���趨 CCER �Ĵ����� CCxP λ��ֵ��

//����10�����ͨ����ʼ��
				ȡֵ��Χ1����4
*/
/*
----------------------------------------------------|
��ʱ��		ͨ��	CH1		CH2		CH3		CH4		|
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
	GPIO_PinAFConfig(GPIOx,PWM_GPIO,GPIO_AF); /* ��ʱ��ͨ�����Ÿ��� */
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode;	    //����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse = TIM_Pulse-1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity;  	  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
	
	switch(TIM_channeX)
	{
		case 1:TIM_OC1Init(TIMx, &TIM_OCInitStructure);break; //ʹ��ͨ��1
		case 2:TIM_OC2Init(TIMx, &TIM_OCInitStructure);break; //ʹ��ͨ��2
		case 3:TIM_OC3Init(TIMx, &TIM_OCInitStructure);break; //ʹ��ͨ��3
		case 4:TIM_OC4Init(TIMx, &TIM_OCInitStructure);break; //ʹ��ͨ��4
	}
	// ʹ�ܶ�ʱ��
	TIM_Cmd(TIMx, ENABLE);
	
}

/*
  * log:

  *	2018��6��14��
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/
