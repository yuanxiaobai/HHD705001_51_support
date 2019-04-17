/*******************************************************************************************************
  * Company: Hiwafer Technology Co., Ltd.
  ******************************************************************************************************
  * �ļ����ƣ�main.c
  * ����˵����
  * ��    ����V1.0
  * ��    �ߣ�EnderWigg	
  * ��    �ڣ�1019.1.21

*******************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "hhd32f1xx.h"

#include "netconf.h"
#include "hhd32f107.h"
#include "simulator_spi.h"
#include "load_server.h"
#include "IO_Init.h"
#include "MT25Q.h"
#include "lib_xvc_v1_0.h"

#include "lwip/ip.h"
#include "netif/etharp.h"

#include "HHD1705_lib.h"

uint8_t get_mark(void);
/* ------------------------Private variables ---------------------------------------------------------*/
__IO uint32_t LocalTime = 0; 
uint8_t Mark = 198;

/*****************************************************************************************************
*
*	Pin  �������ñ�
*   �����������õ���PinӦ���ڴ�ָ������
*****************************************************************************************************/
ST_PINS pins_table[] = 
{
//			port,   pin,  af,   dir,			Mode	
	__HHD_PIN(A,	9,    1,	AF_FUNCATIOON,	GPIO_Mode_PUE),		//uart1_tx
	__HHD_PIN(A,    10,   1,    AF_FUNCATIOON,  GPIO_Mode_PUE),		//uart1_rx
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
	
	
//	���ӵ�FPGAδʹ�õ�IO����	Ĭ����Ϊ���빦��
	__HHD_PIN(C,    7,    0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO1
	__HHD_PIN(C,    13,   0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO5
	__HHD_PIN(D,    4,    0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO6
	__HHD_PIN(D,    5,    0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO7
	__HHD_PIN(D,    6,    0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO8
	__HHD_PIN(D,    7,    0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO9
	__HHD_PIN(D,    8,    0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO10
	__HHD_PIN(D,    9,    0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO11
	__HHD_PIN(D,    10,   0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO12
	__HHD_PIN(D,    11,   0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO13
	__HHD_PIN(D,    12,   0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO14
	__HHD_PIN(D,    13,   0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO15
	__HHD_PIN(D,    14,   0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO16
	__HHD_PIN(D,    15,   0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO17

	__HHD_PIN(E,    0,    0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO18
	__HHD_PIN(E,    1,    0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO19
	__HHD_PIN(E,    2,    0,    OUTPUT,  		GPIO_Mode_DEF),		//LED
	__HHD_PIN(E,    3,    0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO20
	__HHD_PIN(E,    4,    0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO21
	__HHD_PIN(E,    5,    0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO22
	__HHD_PIN(E,    6,    0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO23
	__HHD_PIN(E,    7,    0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO24
	__HHD_PIN(E,    8,    0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO25
	__HHD_PIN(E,    9,    0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO26
	__HHD_PIN(E,    10,   0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO27
	__HHD_PIN(E,    11,   0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO28
	__HHD_PIN(E,    12,   0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO29
	__HHD_PIN(E,    13,   0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO30
	__HHD_PIN(E,    14,   0,    INPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO31

};


/*******************************************************************************************************
*
*	MCU Ӳ���ӿڳ�ʼ��
*
*******************************************************************************************************/
void peripheral_init(void)
{
	uint8_t data = 0;
	SysTick_Config(SystemCoreClock /100);  /* SystTick configuration: an interrupt every 10ms */
	NVIC_SetPriority (SysTick_IRQn, 1);    /* Update the SysTick IRQ priority should be higher than the Ethernet IRQ */
	
	NVIC_EnableIRQ(ETH_IRQn);
	spi_Init();

#ifdef CFG_USING_FIND_MARK
	while(1)                                   // ȷ��FPGA�Ѿ���������
	{
		SPI_To_FPGA_Read(1, 63, &data, 1);
		if(data == 0xAA)
		{
			break;
		}
	}

    Mark = get_mark();		                  // ��ȡMark
#endif
#ifdef 	CFG_USING_NET
	Ethernet_Configuration(EN_TO_MDI);        //�ߵ�������
//	Ethernet_Configuration(EN_TO_SWITCH);     //�߱��彻����
#endif	
}
/*******************************************************************************************************
*
*	Ӧ�ô����ʼ��
*
*******************************************************************************************************/
void application_init(void)
{
	LwIP_Init();
#ifdef 	CFG_USING_LOAD
	load_server_init();
//extern void server_load(void);
//	server_load();
#endif
#ifdef CFG_USING_XVC
	jtag_Server_init();
#endif
#ifdef CFG_USING_CLIENT_TEST
extern void client_init(void);
	client_init();
#endif
	
	
}

/*****************************************************************************************************
*
*	MAIN
*
*
*****************************************************************************************************/

#ifndef COMPILE_TO_LIB
int main(void)
{
	extern struct netif netif;
	struct ip_addr addr;
	 IP4_ADDR(&addr, 192, 168, 2, 34);
	GPIO_SetPin(GPIOE, PIN2);

	IO_init(pins_table, sizeof(pins_table)/sizeof(ST_PINS));
	peripheral_init();
	application_init();
	

	
	while(1)
	{
#ifdef BUG_GMII_TO_SGMII
		int i = 0; 
		uint16_t data[32] = {0,1,2,3,4,5,6};
		uint16_t phyaddr = 0;
		phyaddr = get_phyaddr();
		for(i = 0; i < 0x20; i++)
		{
			data[i] = ETH_ReadPHYRegister(phyaddr, i);
		}
#endif	


		Delay(500);
#ifdef CFG_USING_LED_BLINK		
		GPIO_ResetPin(GPIOE, PIN2);
#endif		
		Delay(500);
#ifdef CFG_USING_LED_BLINK	
		GPIO_SetPin(GPIOE, PIN2);
#endif	
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
	application_init();

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

	 SPI_To_FPGA_Read(1, 0, &data, 1);
	
	return data;

}



/*********************************************************************************************************
  * @brief  Updates the system local time
  * @param  None
  * @retval None
  ********************************************************************************************************/
void Time_Update(void)
{
  LocalTime += SYSTEMTICK_PERIOD_MS;
}

/*********************************************************************************************************
  * @brief  Handles the periodic tasks of the system
  * @param  None
  * @retval None
  ********************************************************************************************************/
void System_Periodic_Handle(void)
{ 
  /* LwIP periodic services are done here */
  LwIP_Periodic_Handle(LocalTime);
}
/*********************************************************************************************************
*
*	��ȡSysTick
*
**********************************************************************************************************/
uint32_t Get_Tick(void)
{
	return LocalTime;
}

/**********************************************************************************************************
*
*	����SysTick����ʱ
*
***********************************************************************************************************/
void Delay(uint32_t nCount)
{
	uint32_t timingdelay = 0;
	/* Capture the current local time */

	timingdelay = LocalTime + nCount;  

	/* wait until the desired delay finish */  
	while(timingdelay > LocalTime)
	{     
	}
	
	
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
