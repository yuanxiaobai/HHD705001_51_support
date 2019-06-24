/*******************************************************************************************************
  * Company: Hiwafer Technology Co., Ltd.
  ******************************************************************************************************
  * �ļ����ƣ�main.c
  * ����˵����
  * ��    ����V2.0
  * ��    �ߣ�EnderWigg	
  * ��    �ڣ�1019.4.25

*******************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "hhd32f1xx.h"

#include "netconf.h"
#include "hhd32f107.h"
#include "simulator_spi.h"
#include "load_server.h"
#include "IO_Init.h"
#include "lib_xvc_v1_0.h"
#include "HHD1705_lib.h"
#include "rtthread.h"

/* ------------------------Private variables ---------------------------------------------------------*/

/*****************************************************************************************************
*
*	Pin  �������ñ�
*   �����������õ���PinӦ���ڴ�ָ������
*****************************************************************************************************/
ST_PINS pins_table[] = 
{
//			port,   pin,  af,   dir,			Mode	
//	__HHD_PIN(A,	9,    1,	AF_FUNCATIOON,	GPIO_Mode_PUE),		//uart1_tx
//	__HHD_PIN(A,    10,   1,    AF_FUNCATIOON,  GPIO_Mode_PUE),		//uart1_rx
	__HHD_PIN(C,    6,    0,    OUTPUT,  		GPIO_Mode_DEF),		//88E1111 HW_CONFIG[4]
	
	
	__HHD_PIN(C,    9,    0,    OUTPUT,  		GPIO_Mode_DEF),		////88E1111��λ����	
	__HHD_PIN(B,    12,   2,    AF_FUNCATIOON,  GPIO_Mode_DEF),		//MII_TXD0
	__HHD_PIN(B,    13,   2,    AF_FUNCATIOON,  GPIO_Mode_DEF),		//MII_TXD1
	__HHD_PIN(C,    2,    4,    AF_FUNCATIOON,  GPIO_Mode_DEF),		//MII_TXD2
	__HHD_PIN(B,    8,    2,    AF_FUNCATIOON,  GPIO_Mode_DEF),		//MII_TXD3	
	__HHD_PIN(C,    3,    4,    AF_FUNCATIOON,  GPIO_Mode_DEF),		//TX CLK in
	__HHD_PIN(B,    11,   2,    AF_FUNCATIOON,  GPIO_Mode_DEF),		//MII_TXDEN
	
	__HHD_PIN(C,    4,    4,    AF_FUNCATIOON,  GPIO_Mode_DEF),		//MII_RXD0
	__HHD_PIN(C,    5,    4,    AF_FUNCATIOON,  GPIO_Mode_DEF),		//MII_RXD1
	__HHD_PIN(B,    0,    4,    AF_FUNCATIOON,  GPIO_Mode_DEF),		//MII_RXD2
	__HHD_PIN(B,    1,    4,    AF_FUNCATIOON,  GPIO_Mode_DEF),		//MII_RXD3
	__HHD_PIN(A,    7,    3,    AF_FUNCATIOON,  GPIO_Mode_DEF),		//RX_DV
	__HHD_PIN(A,    1,    4,    AF_FUNCATIOON,  GPIO_Mode_DEF),		//RX_CLK
	
	__HHD_PIN(B,    10,   2,    AF_FUNCATIOON,  GPIO_Mode_DEF),		//RX_EEROR
	__HHD_PIN(C,    1,    4,    AF_FUNCATIOON,  GPIO_Mode_DEF),		//MDC
	__HHD_PIN(A,    2,    4,    AF_FUNCATIOON,  GPIO_Mode_DEF),		//MDIO
	__HHD_PIN(A,    0,    4,    AF_FUNCATIOON,  GPIO_Mode_DEF),		//CRS
	__HHD_PIN(A,    3,    4,    AF_FUNCATIOON,  GPIO_Mode_DEF),		//COL

};


/*******************************************************************************************************
*
*	MCU Ӳ���ӿڳ�ʼ��
*
*******************************************************************************************************/
void peripheral_init(void)
{
	
	NVIC_SetPriority (SysTick_IRQn, 1);    /* Update the SysTick IRQ priority should be higher than the Ethernet IRQ */
	NVIC_EnableIRQ(ETH_IRQn);
#ifndef COMPILE_TO_LIB	
	spi_Init();
#ifdef CFG_USING_MARK
	
	uint32_t data = 0;
	uint32_t count = 0;
	while(1)                                   // ȷ��FPGA�Ѿ���������
	{
		SPI_To_FPGA_Read(CHECK_FPGA_NUM, CHECK_FPGA_ADDR, (uint8_t *)&data, 4);
		if(data == FPGA_BOOT_OK)
		{
			break;
		}
		rt_thread_delay(50);
		count++;
		
	}
#endif
#ifdef 	CFG_USING_NET
	Ethernet_Configuration(ETH_PATH);        
#endif
#endif

}
/*******************************************************************************************************
*
*	Ӧ�ô����ʼ��
*
*******************************************************************************************************/
void application_init(void)
{

#ifdef 	CFG_USING_LOAD
	load_server_init();
#endif
#ifdef CFG_USING_XVC
	jtag_Server_init();
#endif
}

/*******************************************************************************************************
*
*	LED ����
*
*******************************************************************************************************/
#ifndef COMPILE_TO_LIB
void task_led(void *arg)
{
	while(1)
	{
		Delay(500);
#ifdef CFG_USING_LED_BLINK			
		GPIO_ResetPin(GPIOD, PIN0);
		GPIO_ResetPin(GPIOE, PIN2);
		Delay(500);
		GPIO_SetPin(GPIOD, PIN0);
		GPIO_SetPin(GPIOE, PIN2);
#endif		
	}
}
	



/*****************************************************************************************************
*
*	MAIN
*
*
*****************************************************************************************************/


int main(void)
{
	rt_thread_t task1 = NULL;
extern int rt_hw_hhd_eth_init(void);
	rt_hw_hhd_eth_init();
extern void lwip_system_init(void);	
	lwip_system_init();
	application_init();
	task1 = rt_thread_create("LED", task_led, RT_NULL, 256, 20, 20);
	
	if(task1 != NULL)
	{
		rt_thread_startup(task1);
	}

	
}
#endif

/*******************************************************************************************************
*
*	Ӧ�ô����ʼ��
*   �� ϵͳ������ʼ��
*******************************************************************************************************/
void base_init(void)
{	
	GPIO_ResetPin(GPIOE, PIN2);

	IO_init(pins_table, sizeof(pins_table)/sizeof(ST_PINS));
	peripheral_init();

}

/*******************************************************************************************************
*
* ��ȡ�忨 MARK�� ���ݰ忨Mark ���ɰ忨��IP��ַ
*
*
********************************************************************************************************/
uint8_t get_mark(void)
{
	uint8_t data = 0;

	 SPI_To_FPGA_Read(CHECK_FPGA_NUM, MARK_FPGA_ADDR, &data, 1);
	
	if((data == 0) || (data == 0xFF))
	{
		data = 223;
	}
	
	return data;

}


/*********************************************************************************************************
*
*	��ȡSysTick
*
**********************************************************************************************************/
uint32_t Get_Tick(void)
{
	return rt_tick_get();
}

/**********************************************************************************************************
*
*	����SysTick����ʱ
*
***********************************************************************************************************/
void Delay(uint32_t nCount)
{
	rt_thread_delay(nCount);
	
}
/***********************************************************************************************************
*
*	Printf ���򵽴���Uart1
*
************************************************************************************************************/
int fputc(int data , FILE * fd)
{
	while (UART1->STAT.bit.TXF)
	{
	
	}
	UART1->DAT.all= (data & 0xFF);
	return data;
}
