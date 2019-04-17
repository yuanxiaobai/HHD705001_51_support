/*******************************************************************************************************
  * Company: Hiwafer Technology Co., Ltd.
  ******************************************************************************************************
  * 文件名称：main.c
  * 功能说明：
  * 版    本：V1.0
  * 作    者：EnderWigg	
  * 日    期：1019.1.21

*******************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "hhd32f1xx.h"
#include "hhd32f10x_conf.h"
#include "HHD1705_lib.h"

#include "IO_Init.h"



/* ------------------------Private variables ---------------------------------------------------------*/


/*****************************************************************************************************
*
*	Pin  功能配置表
*   工程中所有用到的Pin应该在此指定功能
*****************************************************************************************************/
ST_PINS user_pins_table[] = 
{
//			port,   pin,  af,   dir,			Mode	

	
//	连接到FPGA未使用的IO引脚	默认置为输入功能
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



int main(void)
{ 
	
	 base_init();
	
#ifdef CFG_USING_CAN1	
	can_init(CAN1, CAN_BAUD_1M, 0x6789, 0);
#endif
	
	 IO_init(user_pins_table, sizeof(user_pins_table)/sizeof(ST_PINS));
	
	while(1)
	{
#ifdef BUG_GMII_TO_SGMII
		uint16_t data[32] = {0,1,2,3,4,5,6};
		int i = 0;
		uint16_t phyaddr = 0;
		phyaddr = get_phyaddr();
		for(i = 0; i < 0x20; i++)
		{
			data[i] = ETH_ReadPHYRegister(phyaddr, i);
		}
#endif	
		Delay(500);
		GPIO_ResetPin(GPIOE, PIN2);
		Delay(500);
		GPIO_SetPin(GPIOE, PIN2);
		
	}
}

