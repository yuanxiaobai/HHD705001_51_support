/*******************************************************************************
*
*	使用GPIO 模拟SPI实现
*
*	该模拟spi实现使用模式0，及时钟无效时为低，在上升沿采样,数据位宽为8bit；
*	提供：同时写读，和读写分离的API；
*	通过宏指定使用的引脚；
*	在读写接口中不对CS进行控制，因此需要自定义CS控制逻辑
*******************************************************************************/
#include <string.h>
#include "spi.h"
#include "HHD32f1xx.h"
#include "HHD1705_lib.h"
#include "simulator_spi.h"


/********************************************************************************
*
*	初始化引脚
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
*模拟SPI底层接口
*模式0（时钟默认是低，上升沿采样）
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
*	只读接口，该接口会主动驱动时钟
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
*	只写接口，该接口会主动驱动时钟
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






