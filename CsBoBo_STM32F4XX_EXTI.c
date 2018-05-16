#include "CsBoBo_STM32F4XX_EXTI.h"
#include "CsBoBo_STM32F4XX_NVIC.h"



void EXTI0_IRQHandler(void)
{		
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		if(GPIO_ReadOutputDataBit(GPIOH, GPIO_Pin_11)==1)//��ȡָ���˿ڹܽŵ����
		{
			GPIO_ResetBits(GPIOH,GPIO_Pin_11);
		}else{
			GPIO_SetBits(GPIOH,GPIO_Pin_11);
		}
		EXTI_ClearITPendingBit(EXTI_Line0);  //����жϱ�־λ
	}  
}

void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line1);  //����жϱ�־λ
	}  
}

void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line2);  //����жϱ�־λ
	}  	
}

void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line3);  //����жϱ�־λ
	}	
}

void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line4);  //����жϱ�־λ
	}
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line5);  //����жϱ�־λ
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line6);  //����жϱ�־λ
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line7) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line7);  //����жϱ�־λ
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line8) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line8);  //����жϱ�־λ
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line9) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line9);  //����жϱ�־λ
	}		
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line10);  //����жϱ�־λ
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line11) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line11);  //����жϱ�־λ
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line12) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line12);  //����жϱ�־λ
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line13) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		if(GPIO_ReadOutputDataBit(GPIOH, GPIO_Pin_12)==1)//��ȡָ���˿ڹܽŵ����
		{
			GPIO_ResetBits(GPIOH,GPIO_Pin_12);
		}else{
			GPIO_SetBits(GPIOH,GPIO_Pin_12);
		}		
		EXTI_ClearITPendingBit(EXTI_Line13);  //����жϱ�־λ
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line14) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line14);  //����жϱ�־λ
	}	
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line15) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line15);  //����жϱ�־λ
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

/*������ص�GPIO����ʱ��*/
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

/*�õ�GPIO��ţ������ʼ��*/
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
	
	/* ���� EXTI �ж�Դ ��key1���� */
	SYSCFG_EXTILineConfig(EXTI_PortSource,EXTI_PortSource_PIN);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line_V;/* ѡ�� EXTI �ж�Դ */
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;/* �ж�ģʽ */
	EXTI_InitStructure.EXTI_Trigger = EXTI_Mode;	/* ������ʽ */  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;/* ʹ���ж�/�¼��� */
	EXTI_Init(&EXTI_InitStructure);	
}

/*****************************************************************************/
/*
	�жϳ�ʼ������
*/
void EXTIX_Init(GPIO_TypeDef* GPIOx,u16 GPIO_PIN,EXTITrigger_TypeDef  EXTI_Mode,uint8_t PreemptionPriority,uint8_t SubPriority)
{
	u8 GPIO_num;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	uint8_t exti_NVIC_IRQChannel;
	
	GPIO_num=Get_GPIO_num(GPIOx);
	RCC_AHB1PeriphClockCmd_GPIO_Init(GPIO_num);//������ص�GPIO����ʱ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);	//ʹ�� SYSCFG ʱ�� ��ʹ��GPIO�ⲿ�ж�ʱ����ʹ��SYSCFGʱ��

	exti_NVIC_IRQChannel=Get_NVIC_IRQChannel(GPIO_PIN);
	NVIC_Init_IRQChannel(exti_NVIC_IRQChannel,PreemptionPriority,SubPriority,ENABLE);//���� NVIC

	 
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN;/*ѡ������ */	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;/* ��������Ϊ����ģʽ */ 	    			
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;/* �������Ų�����Ҳ������ */	
	GPIO_Init(GPIOx, &GPIO_InitStructure); /* ʹ������Ľṹ���ʼ��*/

	EXIT_Init_Config(GPIOx,GPIO_PIN,EXTI_Mode);
}	

