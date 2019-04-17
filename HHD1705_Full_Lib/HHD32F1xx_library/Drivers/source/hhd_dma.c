/*****************************************************************************
 *   hhd_crc.h:  Header file for  HHD32F0
 *
 *   Copyright(C) 2015,  Technology
 *   All rights reserved.
 *
 *   History
 *   2015.07.21  ver 1.01    Prelimnary version
 *
******************************************************************************/
/* Includes ------------------------------------------------------------------*/

#include "hhd32f1xx.h"
#include "hhd_dma.h"
#include "hhd_sys.h"


void DMA_SETBASEPTR(HHD32F1_DMA_TypeDef *DMAx, uint32_t addr)
{
    DMAx->CTRL_BASE_PTR.all = addr;

}

void DMA_Enable(HHD32F1_DMA_TypeDef *DMAx)
{
	DMAx->DMA_CFG.bit.MASTER_EN = 1;
}

void DMA_Disable(HHD32F1_DMA_TypeDef *DMAx)
{
	DMAx->DMA_CFG.bit.MASTER_EN = 0;
}

void DMA_SWRequest(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl)
{
	DMAx->CHNL_SW_REQUEST.all |= chnl;
	
}

void DMA_UseBurstSet(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl)
{
	DMAx->CHNL_USEBURST_SET.all |= chnl;
}

void DMA_UseBurstClr(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl)
{
	DMAx->CHNL_USEBURST_CLR.all |= chnl;
}

void DMA_ReqMaskSet(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl)
{
	DMAx->CHNL_REQ_MASK_SET.all |= chnl;
}

void DMA_ReqMaskClr(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl)
{
	DMAx->CHNL_REQ_MASK_CLR.all |= chnl;
}

void DMA_CHEnableSet(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl)
{
	DMAx->CHNL_ENABLE_SET.all |= chnl;
}

void DMA_CHEnableClr(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl)
{
	DMAx->CHNL_ENABLE_CLR.all |= chnl;
}

void DMA_CHPrioritySet(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl)
{
	DMAx->CHNL_PRIORITY_SET.all |= chnl;
}

void DMA_CHPriorityClr(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl)
{
	DMAx->CHNL_PRIORITY_CLR.all |= chnl;
}

int DMA_IRQStatus(HHD32F1_DMA_TypeDef *DMAx)
{
	return DMAx->CHNL_IRQ_STATUS.all;	
}

void DMA_IRQEnable(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl)
{
	DMAx->CHNL_IRQ_ENABLE.all |= chnl;
}


/******************************************************************************
**                            End Of File
******************************************************************************/
