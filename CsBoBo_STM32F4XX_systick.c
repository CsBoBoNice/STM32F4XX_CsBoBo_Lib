#include "CsBoBo_STM32F4XX_systick.h"
#include "CsBoBo_STM32F4XX_NVIC.h"
/**********ʹ�÷���***************************************************************/
/*
	SysTick_delay_init(1000);	//��ʼ��SysTick��ʱ���ж� ÿ 1000um �ж�һ��

	����freeROTSʱ�����³�ʼ��SysTick
	SysTick_delay_init(SYSTEMTICK_PERIOD_MS);	//��ʼ��SysTick��ʱ���ж� ÿ1/configTICK_RATE_HZ���ж�һ��

	SysTick_delay_cycle(6);	//��ʱ 6 ��SysTick�ж�����

	SysTick_Handler(void)//SysTick��ʱ���жϺ����� stm32f10x_it.c ��
	
	��SysTick_Handler()�����м��� TimingDelay_Decrement();
	//extern void TimingDelay_Decrement(void);	
	//void SysTick_Handler(void)
	//{
	//	TimingDelay_Decrement();
	//}
*/

/*********************************************************************************/
/*************************************************************************/
static __IO u32 TimingDelay;	//���ж��еݼ�����	

//��ʼ��SysTick
//SYSTICK��ʱ�ӹ̶�ΪAHBʱ��
//����Ϊ�˼���FreeRTOS�����Խ�SYSTICK��ʱ��Ƶ�ʸ�ΪAHB��Ƶ�ʣ�

// �����ж����ȼ�Ϊ 1<<4-1 = 15�����ȼ�Ϊ���
// ����systick ��ʱ��Ϊ 72M
// ʹ���ж�
// ʹ��systick
void SysTick_delay_init(uint32_t SysTick_IRQn_Tim)
{
	//�ڿ⺯��SysTick_Config()���Ѿ���SYSTICK��ʱ��Ƶ�ʸ�ΪAHB��Ƶ��
	//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);//ѡ���ⲿʱ��  HCLK ��SYSTICK��ʱ��Ƶ�ʸ�ΪAHB��Ƶ��
	if (SysTick_Config(SystemCoreClock / 1000000 * SysTick_IRQn_Tim))	// ST3.5.0��汾
	{ 
		/* Capture error */ 
		while (1);
	}	
}	
/*
SysTick_Config(SystemCoreClock / 1000)		1ms�ж�һ��
SysTick_Config(SystemCoreClock / 100000)	10us�ж�һ��
SysTick_Config(SystemCoreClock / 1000000)	1us�ж�һ��
*/
//// ��� �̼��⺯�� �� core_cm3.h��
//static __INLINE uint32_t SysTick_Config(uint32_t ticks)
//{ 
//  // reload �Ĵ���Ϊ24bit�����ֵΪ2^24
//	if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);
//  
//  // ���� reload �Ĵ����ĳ�ʼֵ	
//  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;
//	
//	// �����ж����ȼ�Ϊ 1<<4-1 = 15�����ȼ�Ϊ���
//  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1); 
//	
//	// ���� counter ��������ֵ
//  SysTick->VAL   = 0;
//	
//	// ����systick ��ʱ��Ϊ 72M
//	// ʹ���ж�
//	// ʹ��systick
//  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | 
//                   SysTick_CTRL_TICKINT_Msk   | 
//                   SysTick_CTRL_ENABLE_Msk;                    
//  return (0); 
//}

//��ʱnTime��SysTick�ж�����
void SysTick_delay_cycle(u16 nTime)
{
	TimingDelay = nTime;	

	// ʹ�ܵδ�ʱ��  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
}

/**
  * @brief  ��ȡ���ĳ���
  * @attention  �� SysTick �жϺ��� SysTick_Handler()����
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
  *	2018��5��18��
	�޸���SysTick��ʼ��������ʹ�ùٷ��⺯����ʼ��
	�޸���ʱ���� ȥ���ɵ���ʱ������������SysTick_delay_cycle()��ȷ��ʱ����
	Programmer:����

  *	2018��5��18��
	�½�����
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/

