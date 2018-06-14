#include "CsBoBo_STM32F4XX_TIMx.h"
#include "CsBoBo_STM32F4XX_LIB.h"



/**********������ʱ������ʹ�÷���***************************************************************/
/*
*********************************************************************************************

	TIMx_Init(TIM2,9000,10000,TIM_CounterMode_Up,0,0,ENABLE);	//��ʱ����ʼ��	
	//��ʱ��2��Ԥ��Ƶ7200,1�����һ���жϣ����ϼ���ģʽ���������ȼ�����0����Ӧ���ȼ�����0
	
	ע��Ĭ�ϲ�ʹ�ܶ�ʱ������TIM_Cmd()ʹ�ܶ�ʱ��
	TIM_Cmd(TIM2, ENABLE);		// ������ʹ��
	
*********************************************************************************************
*********************************************************************************************

	TIM_Cmd(TIM2, ENABLE);		// ������ʹ��

*********************************************************************************************
*********************************************************************************************
*/
/*
TIMx_Init(TIM_TypeDef * TIMx,uint16_t TIM_Prescaler,uint16_t TIM_Period,uint16_t TIM_CounterMode,uint8_t PreemptionPriority,uint8_t SubPriority)

//Ĭ��90M��ʱ��Ƶ�ʣ���ʹ�ܶ�ʱ��

//����1��ѡ�õĶ�ʱ��
			TIM2
			TIM3
			TIM4
			TIM5
			
//����2��ʱ��Ԥ��Ƶֵ(���ü�1)
			ȡֵ��Χ��0����65535
			
//����3���Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period��Ƶ�ʺ����һ�����»����ж� (����Ҫ��1)
			ȡֵ��Χ��0����65535
			
//����4������ģʽ
				TIM_CounterMode_Up 				TIM ���ϼ���ģʽ
				TIM_CounterMode_Down 			TIM ���¼���ģʽ
				TIM_CounterMode_CenterAligned1 	TIM �������ģʽ 1 ����ģʽ
				TIM_CounterMode_CenterAligned2 	TIM �������ģʽ 2 ����ģʽ
				TIM_CounterMode_CenterAligned3 	TIM �������ģʽ 3 ����ģʽ
				
//����4����Ӧ�������ȼ�����
			��ֵԽ�����ȼ�Խ��

//����5����Ӧ��Ӧ���ȼ�����
			��ֵԽ�����ȼ�Խ��
			
*/
/********************************************************************************/
/***�жϺ���**********************************************************************/

#if defined(STM32F40_41xxx)||defined(STM32F427_437xx)||defined(STM32F429_439xx)||defined(STM32F401xx) || defined(STM32F411xE)||defined(STM32F469_479xx)||defined(STM32F446xx)||defined(STM32F412xG)||defined(STM32F413_423xx)
void TIM2_IRQHandler(void)
{ 
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {	
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update); /* �������жϱ�־ */
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
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update); /* �������жϱ�־ */
		/* Do anything */
    }	
}

void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update); /* �������жϱ�־ */
		/* Do anything */
    }	
}

void TIM5_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
    {
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update); /* �������жϱ�־ */
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
	
    RCC_APB1PeriphClockCmd(TIMx_CLK, ENABLE);		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=90M

	if(NVIC_IRQChannelCmd==ENABLE)
	{
		TIMx_NVIC_IRQChannel=Get_NVIC_IRQChannel_TIMx(TIMx);
		NVIC_Init_IRQChannel(TIMx_NVIC_IRQChannel,PreemptionPriority,SubPriority,NVIC_IRQChannelCmd);//���� NVIC	
	}
	
    TIM_TimeBaseStructure.TIM_Period = TIM_Period-1;		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Prescaler= TIM_Prescaler-1;  // ʱ��Ԥ��Ƶ��Ϊ
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode; // ����������ģʽ������Ϊ���ϼ���			
		
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;// ʱ�ӷ�Ƶ���� ��û�õ����ù�				
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;// �ظ���������ֵ��û�õ����ù�	
	
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);  // ��ʼ����ʱ��			
    TIM_ClearFlag(TIMx, TIM_FLAG_Update);	// ����������жϱ�־λ	  	
    TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE);	// �����������ж�			
    TIM_Cmd(TIMx, DISABLE);		// ��������ʹ��	

}

void TIMx_Init(TIM_TypeDef * TIMx,uint16_t TIM_Prescaler,uint16_t TIM_Period,uint16_t TIM_CounterMode,uint8_t PreemptionPriority,uint8_t SubPriority)
{
	TIMx_Init_Complete(TIMx,TIM_Prescaler,TIM_Period,TIM_CounterMode,ENABLE,PreemptionPriority,SubPriority);
}

/*
  * log:

  *	2018��4��27��
	�Ż��������룬�ô�����ӦSTM32F10Xȫϵ��оƬ
	Programmer:����

  *	2018��4��6��
	�޸��˳�ʼ����ʱ�������Ͻ���һ�ζ�ʱ��������
	ɾ�����ж����ȼ���ʼ������CsBoBo_STM32F10X_nvic.c��ͳһ��ʼ��
	Programmer:����

  *	2016��7��7��
	�½�����
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/

