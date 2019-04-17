#include "g32f1xx.h"
//#include "misc.h"
#include "delay.h"

static	uint8_t  sysclk = 72;   /*Ĭ��ϵͳʱ��Ϊ72MHz*/
static  uint8_t  fac_us=0;      /*us��ʱ������	*/
static  uint16_t fac_ms=0;      /*ms��ʱ������ */

/**
	*���ƣ�void Delay_Init(void)
	*��������
	*���أ���
	*���ܣ���׼��ʱ��ʼ����ʹ��SysTick
	*��ע��SysTickʱ��Դ��HCLK/8�ṩ����ϵͳƵ��Ϊ72MHzʱ
           ��С��������Ϊ1/9MHz,����9��Ϊ1us��fac_us��9Ϊ��λ  
**/

void Delay_Init(void)
{
	fac_us = sysclk/8;		    
	fac_ms=(u16)fac_us*1000;
}


/**
	*���ƣ�void Delay_ms(u16 nms)
	*������nms(ms number) ������ ���ܳ���1864
	*���أ���
	*���ܣ����뼶��ʱ
	*��ע��SysTick->LOADΪ24λ�Ĵ���,���������ʱС�ڻ����1864ms��
**/
void Delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;/*ʱ�����(SysTick->LOADΪ24bit)*/
	SysTick->VAL =0x00;           /*��ռ����� */
	SysTick->CTRL=0x01 ;          /*��ʼ����  */  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16))); /*�ȴ�ʱ�䵽��   */
	SysTick->CTRL=0x00;       /*�رռ�����	 */
	SysTick->VAL =0X00;       /*��ռ�����	*/  	    
} 


/**
	*���ƣ�void Delay_us(u32 nus)
	*������us(number us) ��ʱ΢���� ���1864135
	*���أ���
	*����: ʵ��΢�뼶��ʱ�������ʱ1864ms
	*��ע��������������ͨ���Ĵ������õģ�û�ж�Ӧ�Ĺ̼��⺯�����ο�misc.h
**/		    								   
void Delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; /*ʱ����� fac_us=9,��9�ξ���1us	*/  		 
	SysTick->VAL=0x00;        /*��ռ����� */
	SysTick->CTRL=0x01 ;      /*��ʼ���� */	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));/*�ȴ�ʱ�䵽��*/   
	SysTick->CTRL=0x00;       /*�رռ�����	*/
	SysTick->VAL =0X00;       /*��ռ�����	*/
}

