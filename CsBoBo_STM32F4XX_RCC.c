#include "CsBoBo_STM32F4XX_RCC.h"

//ʱ�����ú���
//Fvco=Fs*(plln/pllm);
//Fsys=Fvco/pllp=Fs*(plln/(pllm*pllp));
//Fusb=Fvco/pllq=Fs*(plln/(pllm*pllq));

//Fvco:VCOƵ��
//Fsys:ϵͳʱ��Ƶ��
//Fusb:USB,SDIO,RNG�ȵ�ʱ��Ƶ��
//Fs:PLL����ʱ��Ƶ��,������HSI,HSE��. 
//plln:��PLL��Ƶϵ��(PLL��Ƶ),ȡֵ��Χ:64~432.
//pllm:��PLL����ƵPLL��Ƶϵ��(PLL֮ǰ�ķ�Ƶ),ȡֵ��Χ:2~63.
//pllp:ϵͳʱ�ӵ���PLL��Ƶϵ��(PLL֮��ķ�Ƶ),ȡֵ��Χ:2,4,6,8.(������4��ֵ!)
//pllq:USB/SDIO/������������ȵ���PLL��Ƶϵ��(PLL֮��ķ�Ƶ),ȡֵ��Χ:2~15.

//�ⲿ����Ϊ25M��ʱ��,�Ƽ�ֵ:plln=360,pllm=25,pllp=2,pllq=8.
//�õ�:Fvco=25*(360/25)=360Mhz
//     Fsys=360/2=180Mhz
//     Fusb=360/8=45Mhz��ʹ��USBʱ��������plln=384�����ɵõ�48MhzƵ�ʣ�
//����ֵ:0,�ɹ�;1,ʧ�ܡ�
u8 Sys_Clock_Set(u32 plln,u32 pllm,u32 pllp,u32 pllq)
{ 
	u16 retry=0;
	u8 status=0;
	RCC->CR|=1<<16;				//HSE ���� 
	while(((RCC->CR&(1<<17))==0)&&(retry<0X1FFF))retry++;//�ȴ�HSE RDY
	if(retry==0X1FFF)status=1;	//HSE�޷�����
	else   
	{
		RCC->APB1ENR|=1<<28;	//��Դ�ӿ�ʱ��ʹ��
		PWR->CR|=3<<14; 		//������ģʽ,ʱ�ӿɵ�180Mhz
		RCC->CFGR|=(0<<4)|(5<<10)|(4<<13);//HCLK ����Ƶ;APB1 4��Ƶ;APB2 2��Ƶ. 
		RCC->CR&=~(1<<24);	//�ر���PLL
		RCC->PLLCFGR=pllm|(plln<<6)|(((pllp>>1)-1)<<16)|(pllq<<24)|(1<<22);//������PLL,PLLʱ��Դ����HSE
		RCC->CR|=1<<24;			//����PLL
		while((RCC->CR&(1<<25))==0);//�ȴ�PLL׼���� 
		FLASH->ACR|=1<<8;		//ָ��Ԥȡʹ��.
		FLASH->ACR|=1<<9;		//ָ��cacheʹ��.
		FLASH->ACR|=1<<10;		//����cacheʹ��.
		FLASH->ACR|=5<<0;		//5��CPU�ȴ�����. 
		RCC->CFGR&=~(3<<0);		//����
		RCC->CFGR|=2<<0;		//ѡ����PLL��Ϊϵͳʱ��	 
		while((RCC->CFGR&(3<<2))!=(2<<2));//�ȴ���PLL��Ϊϵͳʱ�ӳɹ�. 
	} 
	return status;
}  

//ϵͳʱ�ӳ�ʼ������
//plln:��PLL��Ƶϵ��(PLL��Ƶ),ȡֵ��Χ:64~432.
//pllm:��PLL����ƵPLL��Ƶϵ��(PLL֮ǰ�ķ�Ƶ),ȡֵ��Χ:2~63.
//pllp:ϵͳʱ�ӵ���PLL��Ƶϵ��(PLL֮��ķ�Ƶ),ȡֵ��Χ:2,4,6,8.(������4��ֵ!)
//pllq:USB/SDIO/������������ȵ���PLL��Ƶϵ��(PLL֮��ķ�Ƶ),ȡֵ��Χ:2~15.
void Stm32_Clock_Init(u32 plln,u32 pllm,u32 pllp,u32 pllq)
{  
	RCC->CR|=0x00000001;		//����HISON,�����ڲ�����RC��
	RCC->CFGR=0x00000000;		//CFGR���� 
	RCC->CR&=0xFEF6FFFF;		//HSEON,CSSON,PLLON���� 
	RCC->PLLCFGR=0x24003010;	//PLLCFGR�ָ���λֵ 
	RCC->CR&=~(1<<18);			//HSEBYP����,�ⲿ������·
	RCC->CIR=0x00000000;		//��ֹRCCʱ���ж� 
	Sys_Clock_Set(plln,pllm,pllp,pllq);//����ʱ�� 

}

/*
  * log:

  *	2018��5��6��
	�½�����
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/

