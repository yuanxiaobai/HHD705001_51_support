/*******************************************************************************************************
  * Company: Hiwafer Technology Co., Ltd.
  ******************************************************************************************************
  * �ļ����ƣ�main.c
  * ����˵����
  * ��    ����V1.0
  * ��    �ߣ�EnderWigg	
  * ��    �ڣ�1019.1.21

*******************************************************************************************************/
#include "hhd32f1xx.h"
#include "hhd32f107.h"

#include "load_server.h"
#include "IO_Init.h"
#include "lib_xvc_v1_0.h"
#include "HHD1705_lib.h"
#include "rtthread.h"       // RTOS ��غ����ͻ���
#include "can_task.h"



/*****************************************************************************************************
*
*	Pin  �������ñ�
*   �����������õ���PinӦ���ڴ�ָ������
*****************************************************************************************************/
static ST_PINS pins_table[] = 
{
//			port,   pin,  af,   dir,			Mode	
	__HHD_PIN(D,    0,    0,    OUTPUT,  		GPIO_Mode_DEF),		//LED1
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
	__HHD_PIN(D,    15,   0,    OUTPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO17

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
	
	__HHD_PIN(D,    2,   0,    OUTPUT,  		GPIO_Mode_DEF),		//ARM_FPGA1_IO31

};

/**
 * @brief  LED ��˸����

 * @param arg �ò����Ӵ�������ʱ���룬�ú�����δʹ��
 * @return void 
 * @details ����LED ��˸�����ִ�к��������������ڱ�ʾϵͳ�Ƿ�������״̬
 */
void task_led(void *arg)
{
	while(1)
	{
		Delay(500);
#ifdef CFG_USING_LED_BLINK			
		GPIO_ResetPin(GPIOE, PIN2);
//		GPIO_ResetPin(GPIOD, PIN2);
		GPIO_ResetPin(GPIOD, PIN15);
		
		Delay(500);
		GPIO_SetPin(GPIOE, PIN2);
//		GPIO_SetPin(GPIOD, PIN15);
		GPIO_SetPin(GPIOD, PIN2);
#endif		
	}
}
	

/**
 * @brief �������

 * @param void
 * @return 
 * @details ��ʾ���ʹ�� HHD1705_LIB_v2.0
*/

int main(void)
{
	uint32_t fpga_bootMark = 0;
	uint32_t count = 0;
	rt_thread_t task_led_id = NULL; // ���������� 
// ���ų�ʼ��	
	IO_init(pins_table, sizeof(pins_table)/sizeof(ST_PINS));
// spiӲ���ӿڳ�ʼ��
	spi_Init();
#ifdef CFG_USING_MARK	
// ȷ��FPGA�Ѿ���������	
	while(count < 100)                                  
	{
		SPI_To_FPGA_Read(CHECK_FPGA_NUM, CHECK_FPGA_ADDR, (uint8_t *)&fpga_bootMark, 4);
		if(fpga_bootMark == FPGA_BOOT_OK)
		{
			break;
		}
		rt_thread_delay(50);
		count++;
	}

#endif
#ifdef 	CFG_USING_NET
// ����ӿڳ�ʼ��
extern 	int rt_hw_hhd_eth_init(void);
	rt_hw_hhd_eth_init();
	Ethernet_Configuration(ETH_PATH);        
#endif				
// ��������Э��ջ	
extern void lwip_system_init(void);	
	lwip_system_init();
// ��������Ӧ��	
	application_init();
// ����CAN ����
	can_task_init();			
// ���� LED ����	
	task_led_id = rt_thread_create("LED", task_led, RT_NULL, 256, 20, 20);
// ���� LED ����	
	if(task_led_id != NULL)
	{
		rt_thread_startup(task_led_id);
	}				
		
}




