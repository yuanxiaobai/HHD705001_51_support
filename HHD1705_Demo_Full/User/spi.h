#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hhd32f1xx.h"
#include "hhd_spi.h"
#define SPI1_USE_ENABLE
#define SPI1_6LINE
//#define SPI2_USE_ENABLE
//#define SPI2_6LINE
#define SPI_8BIT_MODE    0x07   	
#define SPI_16BIT_MODE   0x0F
	
/************ SPI1 CS PA4 *******************/
#define SPI1_CS_LOW    SPI_Reset_SSEL_Low(SPI1)
#define SPI1_CS_HIGH   SPI_Set_SSEL_High(SPI1)
#ifdef SPI1_6LINE
#define SPI1_6LINE_WRITE	GPIO_ResetPin(GPIOA, PIN10)
#define SPI1_6LINE_READ		GPIO_SetPin(GPIOA, PIN10)
#define SPI1_6LINE_EXTI		GPIO_GetPinState(GPIOA, PIN9)
#endif

/************ SPI2 CS PB12 *******************/
#define SPI2_CS_LOW    SPI_Reset_SSEL_Low(SPI2)
#define SPI2_CS_HIGH   SPI_Set_SSEL_High(SPI2)
#ifdef SPI2_6LINE
#define SPI2_6LINE_WRITE	GPIO_ResetPin(GPIOA, PIN2)
#define SPI2_6LINE_READ		GPIO_SetPin(GPIOA, PIN2)
#define SPI2_6LINE_EXTI		GPIO_GetPinState(GPIOA, PIN1)
#endif



	
	
void SPI1_Init(void);

void SPI4_Init(uint32_t freq);
void SPI4_simulator_Init(void);
void SPI5_Init(uint32_t freq);

uint16_t jtag_handler(uint8_t* tms, uint8_t *tdo, uint8_t *tdi, uint16_t wordToRead);
uint16_t write_handler(HHD32F1_SPI_TypeDef *SPIx, uint8_t *data, uint16_t byteLen);

unsigned char readWriteByte(unsigned char data);

#ifdef __cplusplus
}
#endif

#endif
