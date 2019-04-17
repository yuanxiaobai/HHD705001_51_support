/***********************************************************************
*
*	IO_Init.c
*	该文件用于初始该工程用到的所有引脚
*
*
*
***********************************************************************/
#include <stdio.h>
#include "hhd32f1xx.h"
#include "hhd32f10x_conf.h"
#include "IO_Init.h"
#include "hhd_rcc.h"



static void init_pin(ST_PINS *pin)
{

	assert_param(pin != NULL);
	
	pin->iocon_bit->bit.FUNC = pin->io_af;
	pin->iocon_bit->all |=  pin->mode;
	//	设置引脚方向		
	if(pin->direction == OUTPUT)
	{
		GPIO_ConfigPinsAsOutput(pin->port, pin->pin); 
	}
	else if(pin->direction == INPUT)
	{
		GPIO_ConfigPinsAsInput(pin->port, pin->pin); 	
	}
	
	RCC_APB2PeriphClockCmd(pin->RCC_APB2Periph, ENABLE);	
	
	
	
}

void IO_init(ST_PINS *pins_tables, int pins_table_len)
{
	int i = 0;	
	for(i = 0; i < pins_table_len; i++)
	{
		init_pin(pins_tables+i);
	}
}









