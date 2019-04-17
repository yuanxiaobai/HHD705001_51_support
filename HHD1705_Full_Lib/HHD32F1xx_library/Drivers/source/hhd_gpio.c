/*****************************************************************************
 *   GT_GPIO:  Sourse file for Gorge MCU GPIO application
 *
 *   Copyright(C) 2015, Gorge Technology
 *   All rights reserved.
 *
 *   History
 *   2015.08.14  ver 1.00
 *
******************************************************************************/
#include "hhd_gpio.h"
#include "hhd_sys.h"

/*****************************************************************************
Function Name	GPIO_SetPinsAsInput
Function Definition	void GPIO_SetPinsAsInput(G32F_GPIO_TypeDef *port, uint16_t pins)
Function Description	Setup GPIO pins as digital input
Input Parameters	* port : pointer to GPIO device, GT_GPIO0/GT_GPIO1/GT_GPIO2
Pins: combination of IO_PIN0~IO_PIN15, predefine in sys.h
Return Value	No
Condition	#include sys.h
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void GPIO_ConfigPinsAsInput(HHD32F_GPIO_TypeDef *port, uint16_t pins)
{
	port->DIR.all &= ~pins;
	return;
}
/*****************************************************************************
Function Name	GPIO_SetPinsAsOutput
Function Definition	void GPIO_SetPinsAsOutput(G32F_GPIO_TypeDef *port, uint16_t pins)
Function Description	Setup GPIO pins as digital Output
Input Parameters	* port : pointer to GPIO device, GT_GPIO0/GT_GPIO1/GT_GPIO2
Pins: combination of IO_PIN0~IO_PIN15, predefine in sys.h
Return Value	No
Condition	#include sys.h
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void GPIO_ConfigPinsAsOutput(HHD32F_GPIO_TypeDef *port, uint16_t pins)
{
	port->DIR.all |= pins;
	return;
}

/*****************************************************************************
Function Name	GPIO_SetPin
Function Definition	void GPIO_SetPin (G32F_GPIO_TypeDef *port, uint16_t pin)
Function Description	Set GPIO pin Output as 1
Input Parameters	* port : pointer to GPIO device, GT_GPIO0/GT_GPIO1/GT_GPIO2
Pin: IO_PIN0~IO_PIN15, predefine in sys.h
Return Value	No
Condition	#include sys.h
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void GPIO_SetPin(HHD32F_GPIO_TypeDef *port, uint16_t pin)
{
	port->SET.all |= pin;
	return;
}

/*****************************************************************************
Function Name	GPIO_ResetPin
Function Definition	void GPIO_ResetPin (G32F_GPIO_TypeDef *port, uint16_t pin)
Function Description	Reset GPIO pin Output as 0
Input Parameters	* port : pointer to GPIO device, GT_GPIO0/GT_GPIO1/GT_GPIO2
Pin: IO_PIN0~IO_PIN15, predefine in sys.h
Return Value	No
Condition	#include sys.h
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void GPIO_ResetPin (HHD32F_GPIO_TypeDef *port, uint16_t pin)
{
    port->CLR.all |= pin;
    return;
}
	

void GPIO_WriteBit(HHD32F_GPIO_TypeDef* port, uint16_t GPIO_Pin, BitAction BitVal)
{
	if (BitVal != Bit_RESET)
	{
		port->SET.all |= GPIO_Pin;
	}
	else
	{
		port->CLR.all |= GPIO_Pin;
	}

}



/*****************************************************************************
Function Name	GPIO_InvertOutPin
Function Definition	void GPIO_InvertOutPin (G32F_GPIO_TypeDef *port, uint16_t pin)
Function Description	Invert GPIO pin Output 
Input Parameters	* port : pointer to GPIO device, GT_GPIO0/GT_GPIO1/GT_GPIO2
Pin: IO_PIN0~IO_PIN15, predefine in sys.h
Return Value	No
Condition	#include sys.h
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void GPIO_InvertOutPin (HHD32F_GPIO_TypeDef *port, uint16_t pin)
{
	port->NOT.all |= pin;
	return;
}
	
/*****************************************************************************
Function Name	GPIO_GetPinState
Function Definition	uint8_t GPIO_GetPinState(G32F_GPIO_TypeDef *port, uint16_t pin)
Function Description	get GPIO pin state
Input Parameters	* port : pointer to GPIO device, GT_GPIO0/GT_GPIO1/GT_GPIO2
Pin: IO_PIN0~IO_PIN15, predefine in sys.h
Return Value	GPIO pin state, 0 is low and 1is high
Condition	#include sys.h
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
uint8_t GPIO_GetPinState(HHD32F_GPIO_TypeDef *port, uint16_t pin)
{
	if (port->PIN.all & pin)
		return 1;
	else
		return 0;
}

/*****************************************************************************
Function Name	GPIO_GetPortState
Function Definition	uint16_t GPIO_GetPortState(G32F_GPIO_TypeDef *port)
Function Description	get GPIO port state
Input Parameters	* port : pointer to GPIO device, GT_GPIO0/GT_GPIO1/GT_GPIO2
Return Value	GPIO port state value
Condition	-
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
uint16_t GPIO_GetPortState(HHD32F_GPIO_TypeDef *port)
{
	return (uint16_t)port->PIN.all;
}


/*****************************************************************************
Function Name	GPIO_SetPortMask
Function Definition	void GPIO_SetPortMask(G32F_GPIO_TypeDef *port, uint16_t pins)
Function Description	Set GPIO port IO mask
Input Parameters	* port : pointer to GPIO device, GT_GPIO0/GT_GPIO1/GT_GPIO2
Pins: combination of IO_PIN0~IO_PIN15, predefine in sys.h
Return Value	No
Condition	#include sys.h
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void GPIO_SetPortMask(HHD32F_GPIO_TypeDef *port, uint16_t pins)
{
	port->MASK.all |= pins;
	return;
}
/*****************************************************************************
Function Name	GPIO_ResetPortMask
Function Definition	void GPIO_ResetPortMask(G32F_GPIO_TypeDef *port, uint16_t pins)
Function Description	Remove GPIO port IO mask
Input Parameters	* port : pointer to GPIO device, GT_GPIO0/GT_GPIO1/GT_GPIO2
Pins: combination of IO_PIN0~IO_PIN15, predefine in sys.h
Return Value	No
Condition	#include sys.h
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void GPIO_ResetPortMask(HHD32F_GPIO_TypeDef *port, uint16_t pins)
{
	port->MASK.all &= ~pins;
	return;
}

/*****************************************************************************
Function Name	GPIO_ReadPort
Function Definition	uint16_t GPIO_ReadPort(G32F_GPIO_TypeDef *port)
Function Description	Read GPIO port value
Input Parameters	* port : pointer to GPIO device, GT_GPIO0/GT_GPIO1/GT_GPIO2
Return Value	Return GPIO port value
Condition	#include sys.h
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
uint16_t GPIO_ReadPort(HHD32F_GPIO_TypeDef *port)
{
	return (uint16_t) port->PIN.all;
}

/*****************************************************************************
Function Name	GPIO_WritePort
Function Definition	void GPIO_WritePort(G32F_GPIO_TypeDef *port, uint16_t data)
Function Description	Write value to GPIO port
Input Parameters	* port : pointer to GPIO device, GT_GPIO0/GT_GPIO1/GT_GPIO2
Data: data to be write to GPIO port
Return Value	No
Condition	#include sys.h
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void GPIO_WritePort(HHD32F_GPIO_TypeDef *port, uint16_t data)
{
	port->OUT.all|=data;
	return;
}

/*****************************************************************************
Function Name	GPIO_EnableInt
Function Definition	void GPIO_EnableInt(G32F_GPIO_TypeDef *port, uint16_t pin, uint8_t triggeredge)
Function Description	Setup GPIO pin interrupt
Input Parameters	* port : pointer to GPIO device, GT_GPIO0/GT_GPIO1/GT_GPIO2
pin: IO_PIN0~IO_PIN15, predefine in sys.h
triggeredge: RISE_EDGE/FALL_EDGE/BOTH_EDGE
Return Value	Return GPIO port value
Condition	#include sys.h
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void GPIO_EnableInt(HHD32F_GPIO_TypeDef *port, uint16_t pin, uint8_t triggeredge)
{
//	port->IS.all &= ~pin;
//	port->IE.all |= pin;
	


	if(triggeredge==FALL_EDGE)
	{
    SYSCON->EXTICTL.all |= pin;
	}	else {
		SYSCON->EXTICTL.all &= ~pin;
	}

	

	
	if(port==GPIOA)
	{
		SYSCON->EXTICTL.bit.GPIOSEL = 0;
	} else if(port==GPIOB)
	{
		SYSCON->EXTICTL.bit.GPIOSEL = 1;
	} else if(port==GPIOC)
	{
		SYSCON->EXTICTL.bit.GPIOSEL = 2;
	} else if(port==GPIOD)
	{
		SYSCON->EXTICTL.bit.GPIOSEL = 3;
	} else if(port==GPIOE)
	{
		SYSCON->EXTICTL.bit.GPIOSEL = 4;
	} 
    else if(port == GPIOF)
    {
        SYSCON->EXTICTL.bit.GPIOSEL = 5;
    }
    else if(port == GPIOF)
    {
        SYSCON->EXTICTL.bit.GPIOSEL = 6;
    }


	SYSCON->EXTICTL.bit.SYNCMODE = 1;
	
	if(pin==PIN0)
	{
		NVIC_EnableIRQ(EXTI0_IRQn);
	}
	else if(pin==PIN1)
	{
		NVIC_EnableIRQ(EXTI1_IRQn);
	}	
	else if(pin==PIN2)
	{
		NVIC_EnableIRQ(EXTI2_IRQn);
	}	
	else if(pin==PIN3)
	{
		NVIC_EnableIRQ(EXTI3_IRQn);
	}	
	else if(pin==PIN4)
	{
		NVIC_EnableIRQ(EXTI4_IRQn);
	}	
	else if((pin==PIN9)|(pin==PIN8)|(pin==PIN7)|(pin==PIN6)|(pin==PIN5))
	{
		NVIC_EnableIRQ(EXTI9_5_IRQn);
	}	
    else if((pin == PIN15) | (pin == PIN14) | (pin == PIN13) | (pin == PIN12) | (pin == PIN11) |
            (pin == PIN10))
	{
		NVIC_EnableIRQ(EXTI15_10_IRQn);
	}		
	
	SYSCON->EXTIEN.all = pin;
	
	return;
}

/*****************************************************************************
Function Name	GPIO_ClrIntflag
Function Definition	void GPIO_ClrIntflag(G32F_GPIO_TypeDef *port, uint16_t pin)
Function Description	Setup GPIO pin interrupt
Input Parameters	* port : pointer to GPIO device, GT_GPIO0/GT_GPIO1/GT_GPIO2
pin: IO_PIN0~IO_PIN15, predefine in sys.h
triggeredge: RISE_EDGE/FALL_EDGE/BOTH_EDGE
Return Value	Return GPIO port value
Condition	#include sys.h
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void GPIO_ClrIntflag(HHD32F_GPIO_TypeDef *port, uint16_t pin)
{
//	port->IS.all &= ~pin;
//	port->IE.all |= pin;
	
	SYSCON->EXTICLR.all |= pin;
	return;
}

/*****************************************************************************
Function Name	GPIO_DisableInt
Function Definition	void GPIO_DisableInt(G32F_GPIO_TypeDef *port, uint16_t pin)
Function Description	Setup GPIO pin interrupt
Input Parameters	* port : pointer to GPIO device, GT_GPIO0/GT_GPIO1/GT_GPIO2
pin: IO_PIN0~IO_PIN15, predefine in sys.h
triggeredge: RISE_EDGE/FALL_EDGE/BOTH_EDGE
Return Value	Return GPIO port value
Condition	#include sys.h
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void GPIO_DisableInt(HHD32F_GPIO_TypeDef *port, uint16_t pin)
{
//	port->IS.all &= ~pin;
//	port->IE.all |= pin;
	
	SYSCON->EXTIEN.all &= ~pin;
	
	if(pin==PIN0)
	{
		NVIC_DisableIRQ(EXTI0_IRQn);
	}
	else if(pin==PIN1)
	{
		NVIC_DisableIRQ(EXTI1_IRQn);
	}	
	else if(pin==PIN2)
	{
		NVIC_DisableIRQ(EXTI2_IRQn);
	}	
	else if(pin==PIN3)
	{
		NVIC_DisableIRQ(EXTI3_IRQn);
	}	
	else if(pin==PIN4)
	{
		NVIC_DisableIRQ(EXTI4_IRQn);
	}	
	else if((pin==PIN9)|(pin==PIN8)|(pin==PIN7)|(pin==PIN6)|(pin==PIN5))
	{
		NVIC_DisableIRQ(EXTI9_5_IRQn);
	}	
    else if((pin == PIN15) | (pin == PIN14) | (pin == PIN13) | (pin == PIN12) | (pin == PIN11) |
            (pin == PIN10))
	{
		NVIC_DisableIRQ(EXTI15_10_IRQn);
	}		
	

	return;
}

