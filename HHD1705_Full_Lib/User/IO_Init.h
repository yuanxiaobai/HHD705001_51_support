/***********************************************************************
*
*	IO_Init.h
*	���ļ����ڳ�ʼ�ù����õ�����������
*
*	
*
***********************************************************************/
#ifndef __IO_INIT_H__
#define __IO_INIT_H__

#include "hhd32f1xx.h"
#include "hhd32f10x_conf.h"


#define __HHD_PIN(gpio, gpio_index, af, dir,mode)\
			{RCC_APB2Periph_GPIO##gpio,\
			GPIO##gpio,\
			PIN##gpio_index,\
			&IOCON->P##gpio##gpio_index,\
			af,\
			dir,\
			mode\
			}
			
#define __HHD_GET_PIN(gpio, gpio_index) \
				GPIO##gpio->PIN.bit.IO##gpio_index
			
			
enum pin_direction
{
	OUTPUT = 0,
	INPUT  = 1,
	AF_FUNCATIOON
	
};

typedef struct st_pins
{
	uint32_t RCC_APB2Periph;
	HHD32F_GPIO_TypeDef *port;
	uint32_t	pin;
	volatile union IOCON_REG 	*iocon_bit;                           /*!< Pin config register                                                   */
	uint8_t		io_af;
	enum pin_direction direction;
	GPIOMode_TypeDef mode;
	
}ST_PINS;



void IO_init(ST_PINS *pins_tables, int pins_table_len);


#endif
