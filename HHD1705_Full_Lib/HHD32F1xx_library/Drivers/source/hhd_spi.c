/*   Copyright(C) 2015, Gorge Technology
 *   All rights reserved.
 *
 *   History
 *   2015.07  ver 1.01    Prelimnary version
 *
******************************************************************************/
/*----------- This driver is for general SPI usage ----------------*/
/* Includes ------------------------------------------------------------------*/
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_spi.h"

extern uint32_t SystemCoreClock;
/*****************************************************************************
Function Name	SPI_Open
Function Definition	void SPI_Open(uint8_t framemode, uint8_t bitwidth, uint8_t master)
Function Description	Initial SPI infterface 
Input Parameters	Framemode: SPI_FRAME/SSI_FRAME, current support SPI_FRAME only
Bitwidth: data size, from 4-bit to 16-bit
Master: selection of master or slave, SPI_MASTER/SPI_SLAVE
spionlymode: SPI_MODE0~SPI_MODE3
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12
*****************************************************************************/
void SPI_Open(HHD32F1_SPI_TypeDef *SPI, uint8_t framemode, uint8_t bitwidth, uint8_t master,
              uint8_t spionlymode, uint32_t freq)
{
	//enable SPI clock
	if(SPI==SPI1)
		SYSCON->SYSAPB2CLKCTRL.bit.SPI1CLK=1;
	else if(SPI==SPI2)
		SYSCON->SYSAPB1CLKCTRL.bit.SPI2CLK=1;
	else if(SPI==SPI3)
		SYSCON->SYSAPB1CLKCTRL.bit.SPI3CLK=1;
//	else if(SPI==SPI4)
//		SYSCON->SYSAPB1CLKCTRL.bit.SPI4CLK=1;
//	else if(SPI==SPI5)
//		SYSCON->SYSAPB1CLKCTRL.bit.SPI5CLK=1;
	
	//set spi frame SPI/SSI selcetion
	SPI->CR0.bit.FRF=framemode;
	//select bit width
	SPI->CR0.bit.DSS=bitwidth;
	SPI_SetClk(SPI,freq);
	//Set master/slave
	if (master==SPI_MASTER)
		SPI->CR1.bit.MS=0;
	else
		SPI->CR1.bit.MS=1;
	//set SPI mode
	SPI->CR0.bit.CPOL=spionlymode;
	SPI->CR0.bit.CPHA=spionlymode>>1;
	//enable SPIcontroller
	SPI->CR1.bit.SSE=1;
	
	return;
}
/*****************************************************************************
Function Name	SPI_Close
Function Definition	void SPI_Close(void)
Function Description	De-Initial SPI interface 
Input Parameters	No
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void SPI_Close(HHD32F1_SPI_TypeDef *SPI)
{
	//Disable SPI clock
	if(SPI==SPI1)
		SYSCON->SYSAPB2CLKCTRL.bit.SPI1CLK=0;
	else if(SPI==SPI2)
		SYSCON->SYSAPB1CLKCTRL.bit.SPI2CLK=0;
	else if(SPI==SPI3)
		SYSCON->SYSAPB1CLKCTRL.bit.SPI3CLK=0;
	return;
}
/*****************************************************************************
Function Name	SPI_SetClk
Function Definition	void SPI_SetClk(uint32_t freq)
Function Description	Setup SPI clock. In Master mode, SPI frequency set no more than system clock divide by 7; 
												in Slave mode, the frequency set no more than system clock divide by 12.
Input Parameters	No
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void SPI_SetClk(HHD32F1_SPI_TypeDef *SPI, uint32_t freq)
{
	uint32_t div;
	
	div=SystemCoreClock/freq;
	
	if (SPI->CR1.bit.MS)
	{
		//slave mode
		if (div<12)
			div=12;
	}else
	{
		//master mode
		if (div<7)
			div=7;
		
	}
	//set up divider
	SPI->CPSR.bit.CPSDVSR=div;
	return;
}
/*****************************************************************************
Function Name	SPI_ClearFIFO
Function Definition	void SPI_ClearFIFO(void)
Function Description	Clear SPI TX and RX FIFO.
Input Parameters	No
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void SPI_ClearFIFO(HHD32F1_SPI_TypeDef *SPI)
{
	//wait untile TX FIFO empty
	while(!SPI->SR.bit.TFE);
	//clear RX FIFO
	SPI->ICR.bit.RTIC=1;
	SPI->ICR.bit.RTIC=0;
	return;
}
/*****************************************************************************
Function Name	SPI_SingleWriteRead
Function Definition	void SPI_SingleWriteRead(uint16_t *data)
Function Description	Write data to external SPI device and same time read same size data back from SPI device.
Input Parameters	No
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void SPI_SingleWriteRead(HHD32F1_SPI_TypeDef *SPI, uint16_t *data)
{
#if 0
    //wait untile TX FIFO empty
    while(!SPI->SR.bit.TFE);
    //clear RX FIFO
    SPI->ICR.bit.RTIC = 1;
    SPI->ICR.bit.RTIC = 0;
    //Write data to FIFO
    SPI->DR.bit.DATA = *data;
    //wait untile TX FIFO empty
    while(!SPI->SR.bit.TFE);
    //Read data from FIFO
    *data = SPI->DR.bit.DATA;
#endif
#if 1  //Modify By wangkui 2017-05-02
    //wait untile TX FIFO empty
    while(!SPI->SR.bit.TNF);
    //Write data to FIFO
    SPI->DR.bit.DATA = *data;
    //wait untile TX FIFO empty
    while(!SPI->SR.bit.RNE);
    //Read data from FIFO
    *data = SPI->DR.bit.DATA;
#endif
    return;
}
/*****************************************************************************
Function Name	SPI_WritetoFIFO
Function Definition	void SPI_WritetoFIFO (uint16_t *src, uint8_t *noofdata)
Function Description	Write data to SPI FIFO, if FIFO full, stop with rest number of data and current data pointer
Input Parameters	*src: pointer to data
*noofdata: number of data to send
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void SPI_WritetoFIFO (HHD32F1_SPI_TypeDef *SPI, uint16_t *src, uint8_t *noofdata)
{
	while((SPI->SR.bit.TNF)&&(*noofdata!=0))
	{
		//Write data to FIFO
		SPI->DR.bit.DATA=*src;	
		(*noofdata)--;
	}
	return;
}
/*****************************************************************************
Function Name	SPI_ReadFIFOData
Function Definition	void SPI_ReadFIFOData (uint16_t *dst, uint8_t *noofdata)
Function Description	Read data from SPI FIFO.
Input Parameters	*dst: pointer to destination
*noofdata: number of data read
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void SPI_ReadFIFOData (HHD32F1_SPI_TypeDef *SPI, uint16_t *dst, uint8_t *noofdata)
{
	while((SPI->SR.bit.RNE)&&(*noofdata!=0))
	{
		*dst++=SPI->DR.bit.DATA;
		noofdata--;
		
	}
	return;
}
/*****************************************************************************
Function Name	SPI_ClrInt(may not need)
Function Definition	void SPI_ClrInt(void)
Function Description	Clear SPI interrupt
Input Parameters	No
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void SPI_ClrInt(HHD32F1_SPI_TypeDef *SPI)
{
	SPI->ICR.bit.RORIC;
}
/*****************************************************************************
Function Name	SPI_EnableInt
Function Definition	void SPI_EnableInt(uint8_t inttype)
Function Description	Setup SPI interrupt
Input Parameters	Inttype: combination of 
					SPI_RX_FIFO_FULL	1
					SPI_RX_FIFO_NOT_EMPTY	2
					SPI_RX_FIFO_HALF_FULL	4
					SPI_TX_FIFO_HALF_EMPTY	8
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void SPI_EnableInt(HHD32F1_SPI_TypeDef *SPI, uint8_t inttype)
{
	SPI->IMSC.all |= inttype;
	return;
}
/*****************************************************************************
Function Name	SPI_DisableInt
Function Definition	void SPI_DisableInt(uint8_t inttype)
Function Description	Setup SPI interrupt
Input Parameters	Inttype: combination of 
					SPI_RX_FIFO_FULL	1
					SPI_RX_FIFO_NOT_EMPTY	2
					SPI_RX_FIFO_HALF_FULL	4
					SPI_TX_FIFO_HALF_EMPTY	8
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void SPI_DisableInt(HHD32F1_SPI_TypeDef *SPI, uint8_t inttype)
{
	SPI->IMSC.all &= ~inttype;
	
	return;
}


/*****************************************************************************
Function Name	SPI_Set_SSEL_High
Function Definition	void SPI_Set_SSEL_High(uint8_t inttype)
Function Description	Setup SPI SSEL High
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void SPI_Set_SSEL_High(HHD32F1_SPI_TypeDef *SPI)
{
    SPI->CR1.bit.CSFL = 0;
}


/*****************************************************************************
Function Name	SPI_Reset_SSEL_Low
Function Definition	void SPI_Reset_SSEL_Low(uint8_t inttype)
Function Description	Setup SPI SSEL Low
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void SPI_Reset_SSEL_Low(HHD32F1_SPI_TypeDef *SPI)
{
    SPI->CR1.bit.CSFL = 1;
}


/*****************************************************************************
Function Name	SPI_Reset_SSEL_Low
Function Definition	void SPI_Reset_SSEL_Low(uint8_t inttype)
Function Description	Setup SPI SSEL Low
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void SPI_Write_FIFO(HHD32F1_SPI_TypeDef *SPI, uint32_t data)
{
	SPI->DR.bit.DATA=data;
}


/*****************************************************************************
Function Name	SPI_TX_FIFO_Not_Empty
Function Definition	void SPI_TX_FIFO_Not_Empty(uint8_t inttype)
Function Description	
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
int SPI_TX_FIFO_Not_Empty(HHD32F1_SPI_TypeDef *SPI)
{
	return((SPI->SR.all&0x11)!=1);
}


/*****************************************************************************
Function Name	SPI_TX_FIFO_Not_Empty
Function Definition	void SPI_TX_FIFO_Not_Empty(uint8_t inttype)
Function Description	
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void POLL_RXFIFO_NOTEMPTY(HHD32F1_SPI_TypeDef *SPI)
{
    while(SPI->SR.bit.RNE == 0);
}

/*****************************************************************************
Function Name	SPI_Read_FIFO
Function Definition	void SPI_Read_FIFO(uint8_t inttype)
Function Description	
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
int SPI_Read_FIFO(HHD32F1_SPI_TypeDef *SPI)
{
	return (SPI->DR.bit.DATA);
}


/******************************************************************************
**                            End Of File
******************************************************************************/
