#include "CsBoBo_STM32F4XX_delay.h"

/**********ʹ�÷���***************************************************************/
/*
	Imprecise_delay_us(1024);	//��ʱ1024us
	Imprecise_delay_ms(1024);	//��ʱ1024ms
	
ע:
����ʱʱ�䲻׼ȷ��delay_us���������ӻ����__NOP();

__NOP();����:��ʱһ����������
ʱ������:ͨ��Ϊ���������T����,����Ƶ�ĵ���,���Ǵ��������������ĵ�λ��

*/

/*********************************************************************************/

//��ͨ��ʱ����
void Imprecise_delay_us(u32 nTimer)  
{  
	u32 i=0; 
	for(i=0;i<nTimer;i++){  
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();

		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();

		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();

		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();

		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();

		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();

		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();

		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();

		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();

//		__NOP();__NOP();__NOP();
//		__NOP();__NOP();__NOP();__NOP();__NOP();
//		__NOP();__NOP();__NOP();__NOP();__NOP();
		
//		__NOP();__NOP();__NOP();__NOP();__NOP();
//		__NOP();__NOP();__NOP();__NOP();__NOP();
	}  
}  
//��ͨ��ʱ����
void Imprecise_delay_ms(u32 nTimer)  
{  
    u32 i=1000*nTimer;  
    Imprecise_delay_us(i);  
} 

/*
  * log:

  *	2018��5��7��
	�½�����
	ʵ�ֻ�����ʼ������
	ʵ�ֻ�����������չ���
	Programmer:����
	
*/


