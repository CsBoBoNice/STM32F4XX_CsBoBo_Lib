#include "CsBoBo_STM32F4XX_NVIC.h"
/*//ȡֵ��Χ:
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
//�������ȼ����飺�������ȼ�����Ӧ���ȼ� (Ĭ�ϣ�4���������ȼ���4����Ӧ���ȼ�)
void NVIC_Configuration(uint32_t NVIC_PriorityGroup)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup);
}

//��ʼ���ж���
void NVIC_Init_IRQChannel(	uint8_t NVIC_IRQChannel,\
							uint8_t NVIC_IRQChannelPreemptionPriority,\
							uint8_t NVIC_IRQChannelSubPriority,\
							FunctionalState NVIC_IRQChannelCmd\
							)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* �����ж�Դ*/
  NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQChannel;
  /* ������ռ���ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;
  /* ���������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriority;
  /* ʹ���ж�ͨ��*/
  NVIC_InitStructure.NVIC_IRQChannelCmd = NVIC_IRQChannelCmd;
	
  NVIC_Init(&NVIC_InitStructure);

}


/*
  * log:

  *	2018��5��13��
	�½�����
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/

