#include "CsBoBo_STM32F4XX_systick.h"
/**********ʹ�÷���***************************************************************/
/*

*********************************************************************************************
	SysTick_delay_init(1000);	//��ʼ��SysTick��ʱ���ж� ÿ 1000um �ж�һ��
	
	����freeROTSʱ�����³�ʼ��SysTick
	SysTick_delay_init(SYSTEMTICK_PERIOD_MS);	//��ʼ��SysTick��ʱ���ж� ÿ1/configTICK_RATE_HZ���ж�һ��
*********************************************************************************************
*********************************************************************************************
	delay_us(1024);//��ȷ��ʱ����
	delay_ms(1024);//��ȷ��ʱ����
*********************************************************************************************
*********************************************************************************************
	//SysTick��ʱ���жϺ����� stm32f10x_it.c ��
	SysTick_Handler(void)
*********************************************************************************************
*********************************************************************************************
ע��:SysTick��ʱ���ж��뾫ȷ��ʱ������ͻ������ͬʱʹ�ã�����	
*/
/*********************************************************************************/

static u8 fac_us=0;//us��ʱ������

//��ʼ��SysTick
//SYSTICK��ʱ�ӹ̶�ΪAHBʱ�ӣ�
// �����ж����ȼ�Ϊ 1<<4-1 = 15�����ȼ�Ϊ���
// ����systick ��ʱ��Ϊ SYSTICK��ʱ��Ƶ�ʸ�ΪAHB��Ƶ��
// ʹ���ж�
// ʹ��systick
void SysTick_delay_init(uint32_t SysTick_IRQn_Tim)
{
	//�ڿ⺯��SysTick_Config()���Ѿ���SYSTICK��ʱ��Ƶ�ʸ�ΪAHB��Ƶ��
	//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);//ѡ���ⲿʱ��  HCLK ��SYSTICK��ʱ��Ƶ�ʸ�ΪAHB��Ƶ��
	/*
	SysTick_Config(SystemCoreClock / 1000)		1ms�ж�һ��
	SysTick_Config(SystemCoreClock / 100000)	10us�ж�һ��
	SysTick_Config(SystemCoreClock / 1000000)	1us�ж�һ��
	*/
	if (SysTick_Config(SystemCoreClock / 1000000 * SysTick_IRQn_Tim))	// ST3.5.0��汾
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
	SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; //��ʼ���� 	
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	 
}
	
void delay_ms(u16 nms)
{	 		  	  
	while(nms)
	{
		nms--;
		delay_us(1000-1);	//�˴���1����ȷ
	}

}

/*
  * log:
  *	2018��5��29��
	����ȷ��ʱ�������ϣ��еĵط�������Ҫ��ȷ��ʱ��
	Programmer:����

  *	2018��5��18��
	�޸���SysTick��ʼ��������ʹ�ùٷ��⺯����ʼ��
	�޸���ʱ���� ȥ���ɵ���ʱ������������SysTick_delay_cycle()��ȷ��ʱ����
	Programmer:����

  *	2018��5��18��
	�½�����
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/

