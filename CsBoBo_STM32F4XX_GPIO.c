#include "CsBoBo_STM32F4XX_GPIO.h"
/*******ʹ�÷���***********************************************************/
/*
@��:	GPIO_Common_Init(GPIOH,GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_High_Speed);

GPIO_Common_Init(GPIO_TypeDef* GPIOx,u16 GPIO_PIN,GPIOMode_TypeDef GPIO_Mode,GPIOOType_TypeDef GPIO_OType,GPIOPuPd_TypeDef GPIO_PuPd,GPIOSpeed_TypeDef GPIO_Speed)

//����1��		GPIO_TypeDef
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
				
//����2����Ӧ����	
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

//����3����Ӧģʽ	GPIOMode_TypeDef		����			����
					GPIO_Mode_IN			����ģʽ		����
					GPIO_Mode_OUT			���ģʽ		����С��
					GPIO_Mode_AF			����ģʽ		PWM
					GPIO_Mode_AN			ģ��ģʽ		ADC

//����4����Ӧģʽ	GPIOOType_TypeDef		����			����
					GPIO_OType_PP			�������		����С��
					GPIO_OType_OD			��©			IIC	
					
//����5����Ӧģʽ	GPIOPuPd_TypeDef		����			����	
					GPIO_PuPd_NOPULL		����			����
					GPIO_PuPd_UP			����			
					GPIO_PuPd_DOWN			����
					
ע:	��(��)�������������������£������ᵼ��GPIO�������ѹһֱΪ��(��)��ƽ��
	�������źŲ�ȷ��(������ʱ�е�Ÿ���)���ŻὫGPIO�ڵĵ�ѹֵ����(��)��

//����6����Ӧģʽ	GPIOSpeed_TypeDef		����			
					GPIO_Low_Speed			GPIO_Speed_2MHz
					GPIO_Medium_Speed		GPIO_Speed_25MHz 
					GPIO_Fast_Speed			GPIO_Speed_50MHz
					GPIO_High_Speed			GPIO_Speed_100MHz
					
ע:	����ٶȼ� I/O ֧�ֵĸߵ͵�ƽ״̬����л�Ƶ�ʣ�
	֧�ֵ�Ƶ��Խ�ߣ�����Խ���������Ҫ���ϸ񣬰��ٶ����ó���󼴿�
*/



/********���ú���*****************************************************************/
/*
@��:	GPIO_ResetBits(GPIOD,GPIO_Pin_2);	//��������

@��:	GPIO_SetBits(GPIOD,GPIO_Pin_2);		//�����ø�

@��:	GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)//��ȡָ���˿ڹܽŵ�����	

@��:	GPIO_ReadInputData(GPIOD)	//��ȡָ���� GPIO �˿�����

@��:	GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_2)//��ȡָ���˿ڹܽŵ����

@��:	GPIO_Write(GPIOD, 0x55)//��ָ�� GPIO ���ݶ˿�д������
*/
/*************************************************************************/

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

/*��ʼ��GPIO*/
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
	
	GPIO_InitTypeDef GPIO_InitStructure;	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	
	GPIO_num=Get_GPIO_num(GPIOx);

	RCC_AHB1PeriphClockCmd_GPIO_Init(GPIO_num);	/*������ص�GPIO����ʱ��*/
																   
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN;	/*ѡ��Ҫ���Ƶ�GPIO����*/
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode;   /*��������ģʽ*/
	
	GPIO_InitStructure.GPIO_OType = GPIO_OType;	/*�������ŵ��������*/
	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd;	/*��������Ϊ����/����ģʽ*/
	   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed;	/*������������*/ 
	
	GPIO_Init(GPIOx, &GPIO_InitStructure);	/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/	
}


/*
  * log:

  *	2018��6��14��
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/


