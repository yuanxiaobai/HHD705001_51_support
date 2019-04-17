#ifndef __SIMULATOR_SPI_H__
#define __SIMULATOR_SPI_H__

#include "hhd32f1xx.h"


#if CFG_SELECT_SPI_IO_0
	#define SPI4_CS_PIN			PIN8
	#define SPI4_CS_PORT		GPIOC
	
	#define SPI4_SCK_PIN		PIN10
	#define SPI4_SCK_PORT		GPIOC

	#define SPI4_MISO_PIN		PIN11
	#define SPI4_MISO_PORT		GPIOC

	#define SPI4_MOSI_PIN		PIN12
	#define SPI4_MOSI_PORT		GPIOC
	
	#define SPI4_CS				SPI4_CS_PORT->OUT.bit.IO8 
	#define SPI4_CLK		    SPI4_SCK_PORT->OUT.bit.IO10	
	#define SPI4_MOSI			SPI4_MOSI_PORT->OUT.bit.IO12
	#define SPI4_MISO			(GPIOC->PIN.bit.IO11)
#else	
	#define SPI4_CS_PIN			PIN7
	#define SPI4_CS_PORT		GPIOC

	#define SPI4_SCK_PIN		PIN8
	#define SPI4_SCK_PORT		GPIOC

	#define SPI4_MISO_PIN		PIN11
	#define SPI4_MISO_PORT		GPIOC

	#define SPI4_MOSI_PIN		PIN10
	#define SPI4_MOSI_PORT		GPIOC

	#define SPI4_CS				SPI4_CS_PORT->OUT.bit.IO7 
	#define SPI4_CLK		    SPI4_SCK_PORT->OUT.bit.IO8	
	#define SPI4_MOSI			SPI4_MOSI_PORT->OUT.bit.IO10
	#define SPI4_MISO			(GPIOC->PIN.bit.IO11)

#endif

#define SPI5_CS_PIN			PIN4
#define SPI5_CS_PORT		GPIOD

#define SPI5_SCK_PIN		PIN5
#define SPI5_SCK_PORT		GPIOD

#define SPI5_MISO_PIN		PIN6
#define SPI5_MISO_PORT		GPIOD

#define SPI5_MOSI_PIN		PIN7
#define SPI5_MOSI_PORT		GPIOD

#define SPI5_CS				SPI5_CS_PORT->OUT.bit.IO4
#define SPI5_CLK		    SPI5_SCK_PORT->OUT.bit.IO5	
#define SPI5_MOSI			SPI5_MOSI_PORT->OUT.bit.IO7
#define SPI5_MISO			(GPIOD->PIN.bit.IO6)



unsigned char readWriteByte(unsigned char data);
unsigned char readByte(void);
void WriteByte(unsigned char data);
















#endif



