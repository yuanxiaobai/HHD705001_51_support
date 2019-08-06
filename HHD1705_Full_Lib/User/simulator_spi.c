/*******************************************************************************
*
*	ʹ��GPIO ģ��SPIʵ��
*
*	��ģ��spiʵ��ʹ��ģʽ0����ʱ����ЧʱΪ�ͣ��������ز���,����λ��Ϊ8bit��
*	�ṩ��ͬʱд�����Ͷ�д�����API��
*	ͨ����ָ��ʹ�õ����ţ�
*	�ڶ�д�ӿ��в���CS���п��ƣ������Ҫ�Զ���CS�����߼�
*******************************************************************************/
#include <string.h>
#include "spi.h"
#include "HHD32f1xx.h"
#include "HHD1705_lib.h"
#include "simulator_spi.h"


/********************************************************************************
*
*	��ʼ������
*
********************************************************************************/
void spi_Init(void)
{	
	ENABLEGPIODCLK;

	GPIO_ConfigPinsAsOutput(SPI4_CS_PORT, SPI4_CS_PIN);
	GPIO_ConfigPinsAsOutput(SPI4_SCK_PORT, SPI4_SCK_PIN);	
	GPIO_ConfigPinsAsInput(SPI4_MISO_PORT, SPI4_MISO_PIN);
	GPIO_ConfigPinsAsOutput(SPI4_MOSI_PORT, SPI4_MOSI_PIN);		


}

/*****************************************************************************
*
*ģ��SPI�ײ�ӿ�
*ģʽ0��ʱ��Ĭ���ǵͣ������ز�����
*
*****************************************************************************/
unsigned char readWriteByte(unsigned char data)
{
   unsigned char Out = 0;

	SPI4_CLK = 0;
	SPI4_MOSI = (data >> 7) & 0x1 ;
	SPI4_CLK = 1;
	Out |= (SPI4_MISO << 7) ;
	SPI4_CLK = 0;
	SPI4_MOSI = (data >> 6) & 0x1 ;
	SPI4_CLK = 1;
	Out |= (SPI4_MISO << 6);
	SPI4_CLK = 0;
	SPI4_MOSI = (data >> 5) & 0x1;
	SPI4_CLK = 1;
	Out |= (SPI4_MISO << 5);
	SPI4_CLK = 0;
	SPI4_MOSI = (data >> 4) & 0x1;
	SPI4_CLK = 1;
	Out |= (SPI4_MISO << 4);
	SPI4_CLK = 0;
	SPI4_MOSI = (data >> 3) & 0x1;
	SPI4_CLK = 1;
	Out |= (SPI4_MISO << 3);
	SPI4_CLK = 0;
	SPI4_MOSI = (data >> 2) & 0x1;
	SPI4_CLK = 1;
	Out |= (SPI4_MISO << 2);
	SPI4_CLK = 0;
	SPI4_MOSI = (data >> 1) & 0x1;
	SPI4_CLK = 1;
	Out |= (SPI4_MISO << 1);
	SPI4_CLK = 0;
	SPI4_MOSI = (data >> 0) & 0x1;
	SPI4_CLK = 1;
	Out |= (SPI4_MISO << 0);
	SPI4_CLK = 0;
	
    return Out;	
}

/***************************************************************************
*
*	ֻ���ӿڣ��ýӿڻ���������ʱ��
*
****************************************************************************/
unsigned char readByte(void)
{
   unsigned char Out = 0;

	SPI4_CLK = 0;
	
	SPI4_CLK = 1;
	Out |= (SPI4_MISO << 7) ;
	SPI4_CLK = 0;
	
	SPI4_CLK = 1;
	Out |= (SPI4_MISO << 6);
	SPI4_CLK = 0;
	
	SPI4_CLK = 1;
	Out |= (SPI4_MISO << 5);
	SPI4_CLK = 0;
	
	SPI4_CLK = 1;
	Out |= (SPI4_MISO << 4);
	SPI4_CLK = 0;
	
	SPI4_CLK = 1;
	Out |= (SPI4_MISO << 3);
	SPI4_CLK = 0;
	
	SPI4_CLK = 1;
	Out |= (SPI4_MISO << 2);
	SPI4_CLK = 0;
	
	SPI4_CLK = 1;
	Out |= (SPI4_MISO << 1);
	SPI4_CLK = 0;
	
	SPI4_CLK = 1;
	Out |= (SPI4_MISO << 0);
	SPI4_CLK = 0;
	
    return Out;	
}

/***************************************************************************
*
*	ֻд�ӿڣ��ýӿڻ���������ʱ��
*
****************************************************************************/
void WriteByte(unsigned char data)
{
	SPI4_CLK = 0;
	SPI4_MOSI = (data >> 7) & 0x1 ;
	SPI4_CLK = 1;
	
	SPI4_CLK = 0;
	SPI4_MOSI = (data >> 6) & 0x1 ;
	SPI4_CLK = 1;

	SPI4_CLK = 0;
	SPI4_MOSI = (data >> 5) & 0x1;
	SPI4_CLK = 1;

	SPI4_CLK = 0;
	SPI4_MOSI = (data >> 4) & 0x1;
	SPI4_CLK = 1;

	SPI4_CLK = 0;
	SPI4_MOSI = (data >> 3) & 0x1;
	SPI4_CLK = 1;
	
	SPI4_CLK = 0;
	SPI4_MOSI = (data >> 2) & 0x1;
	SPI4_CLK = 1;

	SPI4_CLK = 0;
	SPI4_MOSI = (data >> 1) & 0x1;
	SPI4_CLK = 1;

	SPI4_CLK = 0;
	SPI4_MOSI = (data >> 0) & 0x1;
	SPI4_CLK = 1;

	SPI4_CLK = 0;

}






