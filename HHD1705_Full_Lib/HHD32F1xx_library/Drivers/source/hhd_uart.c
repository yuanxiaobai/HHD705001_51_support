/*****************************************************************************
 *   gt_uart.h:  Header file for  HHD32F1xx
 *
 *   Copyright(C) 2015,  Technology
 *   All rights reserved.
 *
 *   History
 *   2015.01.21  ver 1.0    Prelimnary version
 *
******************************************************************************/
/* Includes ------------------------------------------------------------------*/

#include "hhd32f1xx.h"
#include "hhd_uart.h"
#include "hhd_sys.h"


extern uint32_t MainClock;
/*****************************************************************************
Function Name	UART_Open
Function Definition	void UART_Open(HHD32F1_UART_TypeDef *uart, uint32_t baudrate, uint8_t parityoption, uint8_t rxinttriggerlevel);
Function Description	Initial UART
Input Parameters	*uart : pointer to UART device, HHD_UART0/HHD_UART1
									Baudrate: baudrate value
									Parityoption: NO_PARITY, EVEN_PARITY, ODD_PARITY
									Rxinttriggerlevel; 1(not empty), 8(half full), 16(full)
Return Value	No
Condition	No
Function called	-
Last Chang Date: 2015/09/12
*****************************************************************************/
void UART_Open(HHD32F1_UART_TypeDef *uart, uint32_t baudrate, uint8_t parityoption,
               uint8_t rxinttriggerlevel)
{
  
	//All Uarts use same divider.
	SYSCON->UARTCLKDIV.bit.DIV = 0x1;     	/* divided by 1 */
	
	if (uart==UART1)
	{
		//disable UART1 IRQ during setup
		NVIC_DisableIRQ(UART1_IRQn);
		//Enable UART1 clock
		SYSCON->SYSAPB2CLKCTRL.bit.UART1CLK=1;	//enable UART1 PCLK

		//reset UART1
		SYSCON->APB2RESET.bit.UART1RSTN=1;
		SYSCON->APB2RESET.bit.UART1RSTN=0;

	}else if (uart==UART2)
	{
		//disable UART2 IRQ during setup
		NVIC_DisableIRQ(UART2_IRQn);
		/* Enable UART2 clock */
		SYSCON->SYSAPB1CLKCTRL.bit.UART2CLK=1;	//enable UART2 PCLK
		//reset UART2
		SYSCON->APB1RESET.bit.UART2RSTN=1;
		SYSCON->APB1RESET.bit.UART2RSTN=0;
	}else if (uart==UART3)
	{
		//disable UART3 IRQ during setup
		NVIC_DisableIRQ(UART3_IRQn);
		/* Enable UART3 clock */
		SYSCON->SYSAPB1CLKCTRL.bit.UART3CLK=1;	//enable UART3 PCLK
		//reset UART3
		SYSCON->APB1RESET.bit.UART3RSTN=1;
		SYSCON->APB1RESET.bit.UART3RSTN=0;
    }
    else if(uart == UART4)
    {
        //disable UART4 IRQ during setup
        NVIC_DisableIRQ(UART4_IRQn);
        /* Enable UART4 clock */
        SYSCON->SYSAPB1CLKCTRL.bit.UART4CLK = 1;	//enable UART4 PCLK
        //reset UART4
        SYSCON->APB1RESET.bit.UART4RSTN = 1;
        SYSCON->APB1RESET.bit.UART4RSTN = 0;
    }
    else if(uart == UART5)
    {
        //disable UART5 IRQ during setup
        NVIC_DisableIRQ(UART5_IRQn);
        /* Enable UART5 clock */
        SYSCON->SYSAPB1CLKCTRL.bit.UART5CLK = 1;	//enable UART5 PCLK
        //reset UART5
        SYSCON->APB1RESET.bit.UART5RSTN = 1;
        SYSCON->APB1RESET.bit.UART5RSTN = 0;
    }

	
  //set up baudrate
  uart->BAUDDIV.bit.BAUDDIV = MainClock/baudrate;
	
	//set parity
	if (parityoption==UART_ODD_PARITY)
		uart->CTRL.bit.PARISEL=1;
	if (parityoption!=UART_NO_PARITY)
		uart->CTRL.bit.PARIEN=1;
	
	//setup rx int trigger level
	if (rxinttriggerlevel==UART_RX_NOT_EMPTY)
		uart->CTRL.bit.RXNEIE=1;
	if (rxinttriggerlevel==UART_RX_HALF_FULL)
		uart->CTRL.bit.RXHLFIE=1;
	if (rxinttriggerlevel==UART_RX_FULL)
		uart->CTRL.bit.RXFIE=1;
	
	//enable rx,tx function
  uart->CTRL.bit.TXEN=1; 
	uart->CTRL.bit.RXEN=1;
	
	//clr FIFO
	uart->FIFOCLR.all=0xFF;
  return;	
}
/*****************************************************************************
Function Name	UART_Close
Function Definition	void UART_Close(G32F1_UART_TypeDef *uart);
Function Description	close UART
Input Parameters	*uart : pointer to UART device, UART0/UART1
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void UART_Close(HHD32F1_UART_TypeDef *uart)
{
	
	
	if (uart==UART1)
	{
		//Disable UART1 IRQ during setup
		NVIC_DisableIRQ(UART1_IRQn);
		//Disable UART1 clock
		SYSCON->SYSAPB2CLKCTRL.bit.UART1CLK=0;	//Disable UART1 PCLK

	}else if (uart==UART2)
	{
		//Disable UART2 IRQ during setup
		NVIC_DisableIRQ(UART2_IRQn);
		/* Disable UART2 clock */
		SYSCON->SYSAPB1CLKCTRL.bit.UART2CLK=0;	//Disable UART2 PCLK

	}else if (uart==UART3)
	{
		//Disable UART3 IRQ during setup
		NVIC_DisableIRQ(UART3_IRQn);
		/* Disable UART3 clock */
		SYSCON->SYSAPB1CLKCTRL.bit.UART3CLK=0;	//Disable UART3 PCLK

	}else return ;
	
	//Disable UART int
	UART_DisableInt(uart);
	UART_ClearIntFlag(uart);	
	
	return;
}
/*****************************************************************************
Function Name	UART_ByteRead
Function Definition	Uint8_t UART_ByteRead(G32F1_UART_TypeDef *uart, uint8_t *data);
Function Description	Read one byte from UART
Input Parameters	*uart : pointer to UART device, UART0/UART1
*data: if RX FIFO is not empty, return value
Return Value	If read success, return 0; otherwise return 1.
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
uint8_t UART_ByteRead(HHD32F1_UART_TypeDef *uart, uint8_t *data)
{
	if (uart->STAT.bit.RXNE)
	{
		*data=uart->DAT.bit.DATA;
		return 0;
	}else
		return 1;
}
/*****************************************************************************
Function Name	UART_Read
Function Definition	Uint8_t UART_Read(G32F1_UART_TypeDef *uart, uint8_t * rxbuf, uint8_t *readbytes);
Function Description	Read data bytes from UART
Input Parameters	*uart : pointer to UART device, UART0/UART1
*rxbuf: data buffer used to store data from UART
*readbytes: number of read data in byte. return no of bytes got.
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void UART_Read(HHD32F1_UART_TypeDef *uart, uint8_t *rxbuf, uint8_t *readbytes)
{
	uint8_t temp=0;
	//get all data
	while ((uart->STAT.bit.RXNE)&&((*readbytes)--))
	{
		*rxbuf++=uart->DAT.bit.DATA;
		temp++;
	}
	//return number of read
	*readbytes=temp;
	return;
}
/*****************************************************************************
Function Name	UART_ByteWrite
Function Definition	Uint8_t UART_ByteWrite(G32F1_UART_TypeDef *uart, uint8_t data);
Function Description	Write one byte to UART
Input Parameters	*uart : pointer to UART device, UART0/UART1
Data: data write to TX FIFO of UART
Return Value	If write success, return 0; otherwise return 1.
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
uint8_t UART_ByteWrite(HHD32F1_UART_TypeDef *uart, uint8_t data)
{
	if (uart->STAT.bit.TXF)
		return 1;
	
	uart->DAT.bit.DATA=data;
	return 0;
}
/*****************************************************************************
Function Name	UART_Write
Function Definition	Uint8_t UART_Write(G32F1_UART_TypeDef *uart, uint8_t * txbuf, uint8_t writebytes);
Function Description	Write bytes to UART FIFO
Input Parameters	*uart : pointer to UART device, UART0/UART1
*txbuf: data buffer to UART
writebytes: number of read data in byte. Maxum is 16. if TX FIFO is not empty, function return fail.
Return Value	If write success, return 0; otherwise return 1.
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
uint8_t  UART_Write(HHD32F1_UART_TypeDef *uart, uint8_t *txbuf, uint32_t writebytes)
{
	if ((uart->STAT.bit.TXF)||(writebytes>=16))
		return 1;
	while (writebytes--)
	{
		uart->DAT.bit.DATA=*txbuf++;
	}
	return 0;
}	

/*****************************************************************************
Function Name	UART_Send
Function Definition	void UART_Send(G32F1_UART_TypeDef *uart, uint8_t * txbuf, uint32_t sendbytes);
Function Description	Send bytes data via UART 
Input Parameters	*uart : pointer to UART device, UART0/UART1
*txbuf: data buffer to UART
sendbytes: number of data in byte to be sent 
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void UART_Send(HHD32F1_UART_TypeDef *uart, uint8_t *txbuf, uint32_t sendbytes)
{
	while (sendbytes--)
	{
		while (uart->STAT.bit.TXF);
		uart->DAT.bit.DATA=*txbuf++;
	}
	return;
}	
/*****************************************************************************
Function Name	UART_PutString
Function Definition	void UART_PutString (G32F1_UART_TypeDef *uart, uint8_t * str);
Function Description	Send data string via UART 
Input Parameters	*uart : pointer to UART device, UART0/UART1
*str: data string 
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void UART_PutString (HHD32F1_UART_TypeDef *uart, uint8_t *str)
{
	while (!(* str=='\0'))
	{
		while (uart->STAT.bit.TXF);
		uart->DAT.all=*str++;
	}
	return;
}
/*****************************************************************************
Function Name	UART_PutHex
Function Definition	void UART_PutString (G32F1_UART_TypeDef *uart, uint32_t data);
Function Description	Send data in hex format via UART 
Input Parameters	*uart : pointer to UART device, UART0/UART1
data: data to send 
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void UART_PutHex (HHD32F1_UART_TypeDef *uart, uint32_t data)
{
	uint8_t hex;
	do
	{
		hex=data & 0xF;
		if (hex>9)
			hex=hex+'A'-10;
		else
			hex+='0';
		while (uart->STAT.bit.TXF);
		uart->DAT.bit.DATA=hex;
	}while (!(data>>4));
	return;
}	
/*****************************************************************************
Function Name	UART_EnableInt
Function Definition	void UART_EnableInt(G32F1_UART_TypeDef *uart, uint32_t intcon);
Function Description	Set UART interrupt type 
Input Parameters	*uart : pointer to UART device, UART0/UART1
intcon: interrupt type combination: TXEINT, RXNEINT, TXFINT, RXFINT, TXHLFINT, RXHLFINT, PARIERRINT, OVERRUNINT
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void UART_EnableInt(HHD32F1_UART_TypeDef *uart, uint32_t intcon)
{
	uart->CTRL.all |= intcon;
	return;
}
/*****************************************************************************
Function Name	UART_DisableInt
Function Definition	void UART_EnableInt(G32F1_UART_TypeDef *uart);
Function Description	Disable UART interrupt 
Input Parameters	*uart : pointer to UART device, UART0/UART1
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void UART_DisableInt(HHD32F1_UART_TypeDef *uart)
{
	uart->CTRL.all &= 0xFFFFFF00;
	return;
}
/*****************************************************************************
Function Name	UART_ClearIntFlag
Function Definition	void UART_ClearIntFlag(G32F1_UART_TypeDef *uart);
Function Description	Clear UART interrupt flag
Input Parameters	*uart : pointer to UART device, UART0/UART1
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void UART_ClearIntFlag(HHD32F1_UART_TypeDef *uart)
{
	uart->INTSTATUS.all |= 0xFF;
	return;
}
/*****************************************************************************
Function Name	UART_GetStatus
Function Definition	void UART_GetStatus (G32F1_UART_TypeDef *uart);
Function Description	Get UART Status 
Input Parameters	*uart : pointer to UART device, UART0/UART1
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
uint8_t UART_GetStatus(HHD32F1_UART_TypeDef *uart)
{
	return (uint8_t) uart->STAT.all;
}
/*****************************************************************************
Function Name	UART_ClearFIFO
Function Definition	void UART_ClearFIFO(G32F1_UART_TypeDef *uart,);
Function Description	Clear UART FIFO
Input Parameters	*uart : pointer to UART device, UART0/UART1
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void UART_ClearFIFO(HHD32F1_UART_TypeDef *uart)
{
	uart->FIFOCLR.all=0xFF;
	return ;
}




/******************************************************************************
**                            End Of File
******************************************************************************/
