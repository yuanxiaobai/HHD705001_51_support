/*****************************************************************************
 *   hhd_dma.h:  Header file for  HHD32F1xx Family Microprocessors
 *
 *   Copyright(C) 2015, Gorge tech. Ltd.
 *   All rights reserved.
 *
 *   History
 *   2015 12 09  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __DMA_H 
#define __DMA_H
#include "hhd32f1xx.h"

//--DMA Status Registers BITS Field---------------------------------------------------------------------------------------
struct DMA_STATUS_BITS {						// bit description
				uint32_t MASTER_EN:1;                   // [0] Master enable
				uint32_t RSVD0:3;                       // [3:1]
				uint32_t STATE:4;                       // [7:4] DMA state
				uint32_t RSVD1:24;                      // 31:8 reserved
};
union DMA_STATUS_REG {
				uint32_t				all;
				struct DMA_STATUS_BITS	bit;
};

struct DMA_CFG_BITS {							// bit description
				uint32_t MASTER_EN:1;                   // [0] Master enable
				uint32_t RSVD0:31;                      // 31:1 reserved
};
union DMA_CFG_REG {
				uint32_t				all;
				struct DMA_CFG_BITS	bit;
};

struct CHNL_BITS {					 	    // bit description
				uint32_t CHNL1:1;            // [0] DMA request
				uint32_t CHNL2:1;            // [1] DMA request
				uint32_t CHNL3:1;            // [2] DMA request
				uint32_t CHNL4:1;            // [3] DMA request
				uint32_t CHNL5:1;            // [4] DMA request
				uint32_t CHNL6:1;            // [5] DMA request
				uint32_t CHNL7:1;            // [6] DMA request
				uint32_t RESVE:25;           // 
};

union CTRL_BASE_PTR_REG {
				uint32_t				all;
				struct CHNL_BITS	bit;
};

union CHNL_SW_REQUEST_REG {
				uint32_t				all;
				struct CHNL_BITS	bit;
};

union CHNL_USEBURST_SET_REG {
				uint32_t				all;
				struct CHNL_BITS	bit;
};

union CHNL_USEBURST_CLR_REG {
				uint32_t				all;
				struct CHNL_BITS	bit;
};

union CHNL_REQ_MASK_SET_REG {
				uint32_t				all;
				struct CHNL_BITS	bit;
};

union CHNL_REQ_MASK_CLR_REG {
				uint32_t				all;
				struct CHNL_BITS	bit;
};


union CHNL_ENABLE_SET_REG {
				uint32_t				all;
				struct CHNL_BITS	bit;
};


union CHNL_ENABLE_CLR_REG {
				uint32_t				all;
				struct CHNL_BITS	bit;
};

union CHNL_PRIORITY_SET_REG {
				uint32_t				all;
				struct CHNL_BITS	bit;
};

union CHNL_PRIORITY_CLR_REG {
				uint32_t				all;
				struct CHNL_BITS	bit;
};

union CHNL_IRQ_STATUS_REG {
				uint32_t				all;
				struct CHNL_BITS	bit;
};

union CHNL_IRQ_ENABLE_REG {
				uint32_t				all;
				struct CHNL_BITS	bit;
};


/*------------- DMA (DMA) ----------------------------*/
/** @addtogroup GT_DMA DMA Engine 
  @{
*/
typedef struct
{
    __I		union DMA_STATUS_REG				DMA_STATUS;							//DMA status
    __IO	union DMA_CFG_REG						DMA_CFG;								//DMA config/enable
    __IO 	union CTRL_BASE_PTR_REG			CTRL_BASE_PTR;					//control base pointer
    __I  uint32_t RESVEDA[2];
    __O 	union CHNL_SW_REQUEST_REG		CHNL_SW_REQUEST;				//software request
    __IO 	union CHNL_USEBURST_SET_REG	CHNL_USEBURST_SET;			//use burst mode
    __O 	union CHNL_USEBURST_CLR_REG	CHNL_USEBURST_CLR;			//use burst mode clear
    __IO 	union CHNL_REQ_MASK_SET_REG	CHNL_REQ_MASK_SET;			//request mask
    __O 	union CHNL_REQ_MASK_CLR_REG	CHNL_REQ_MASK_CLR;			//request mask clear
    __IO 	union CHNL_ENABLE_SET_REG		CHNL_ENABLE_SET;				//enable mask
    __O 	union CHNL_ENABLE_CLR_REG		CHNL_ENABLE_CLR;				//enable mask clear
    __I  uint32_t RESVEDB[2];
    __IO 	union CHNL_PRIORITY_SET_REG	CHNL_PRIORITY_SET;			//priority mask
    __O 	union CHNL_PRIORITY_CLR_REG	CHNL_PRIORITY_CLR;			//priority mask clear
    __I  uint32_t  RESVEDC[16];
    __IO 	union CHNL_IRQ_STATUS_REG		CHNL_IRQ_STATUS;				//channel IRQ status
    __I  uint32_t  RESVEDD;
    __IO 	union CHNL_IRQ_ENABLE_REG		CHNL_IRQ_ENABLE;				//channel IRQ enable
} HHD32F1_DMA_TypeDef;
/*@}*/ /* end of group HHD_DMA */




//--DMA channel cfg ---------------------------------------------------------------------------------------
struct DMA_CHNLCFG_BITS {						// bit description
				uint32_t CYCLE_CTRL:3;                  // [2:0]   cycle control
				uint32_t RSVD0:1;                       // [3]
				uint32_t N_MINUS_1:11;                  // [13:4]  n_minus_1
				uint32_t R_POWER:4;                     // [17:14] R Power
				uint32_t RSVD1:6;                       // [23:18] reserved
				uint32_t SRC_SIZE:2;                    // [25:24] source size
				uint32_t SRC_INC:2;                     // [27:26] source increment type
				uint32_t DST_SIZE:2;                    // [29:28] destination size
				uint32_t DST_INC:2;                     // [31:30] destination increment type
};

union DMA_CHNLCFG_REG {
				uint32_t				all;
				struct DMA_CHNLCFG_BITS	bit;
};

union DMA_SRCENDPTR_REG {
				uint32_t				all;
};

union DMA_DSTENDPTR_REG {
				uint32_t				all;
};

typedef struct
{
	__IO	union DMA_CHNLCFG_REG			DMA_CHNLCFG;			//DMA channel config
	__IO	union DMA_SRCENDPTR_REG		DMA_SRCENDPTR;		//source end pointer
	__IO	union DMA_DSTENDPTR_REG		DMA_DSTENDPTR;		//destination end pointer
	__I  uint32_t RESVD;															//
} DMA_DATASTRUCT_TypeDef;
/*@}*/ /* end of group */


//DMA1 CH1
#define ADC1_DMA1REQ	  	0x00000001            // ADC1 DMA request
#define TIM4_CH1_DMA1REQ	0x00000001            // TIM4 channel 1 DMA request

//DMA1 CH2
#define SPI1_RX_DMA1REQ		0x00000002            // SPI1 RX DMA request
#define UART3_TX_DMA1REQ	0x01000002            // UART5 TX DMA request
#define TIM1_CH1_DMA1REQ	0x00000002            // TIM1 Channel 1 DMA request
#define TIM3_CH2_DMA1REQ	0x00000002            // TIM3 Channel 2 DMA request

//DMA1 CH3
#define SPI1_TX_DMA1REQ		0x00000004            // SPI1 TX DMA request
#define UART3_RX_DMA1REQ	0x00000004            // UART5 RX DMA request

//DMA1 CH4
#define SPI2_RX_DMA1REQ		0x00000008            // SPI2 RX DMA request
#define UART1_TX_DMA1REQ	0x00000008            // UART1 TX DMA request
#define TIM4_CH2_DMA1REQ	0x00000008            // TIM4 channel 2 DMA request

//DMA1 CH5
#define SPI2_TX_DMA1REQ		0x00000010            // SPI2 TX DMA request
#define UART1_RX_DMA1REQ	0x00000010            // UART1 RX DMA request
#define TIM2_CH1_DMA1REQ	0x00000010            // TIM2 channel 1 DMA request

//DMA1 CH6
#define UART2_RX_DMA1REQ	0x00000020            // UART2 RX DMA request
#define TIM1_CH2_DMA1REQ	0x00000020            // TIM1 Channel 2 DMA request
#define TIM3_CH1_DMA1REQ	0x00000020            // TIM3 channel 1 DMA request

//DMA1 CH7
#define UART2_TX_DMA1REQ	0x00000040            // UART2 TX DMA request
#define TIM2_CH2_DMA1REQ	0x00000040            // TIM2 channel 2 DMA request

//-------------------------------------------
//-------------------------------------------
//-------------------------------------------
//DMA2 CH1
#define ADC2_DMA2REQ			0x00000001            // ADC2 DMA request
#define SPI3_RX_DMA2REQ		0x00000001            // SPI3 RX DMA request
#define TIM10_CH2_DMA2REQ	0x00000001            // TIM10 channel 2 DMA request

//DMA2 CH2
#define SPI3_TX_DMA2REQ		0x00000002            // SPI3 TX DMA request
#define TIM9_CH2_DMA2REQ	0x00000002            // TIM9 channel 2 DMA request

//DMA2 CH3
#define TIM9_CH1_DMA2REQ	0x00000004            // TIM9 channel 1 DMA request
#define DAC_DMA2REQ				0x00000004            // DAC DMA request

//DMA2 CH4
#define TIM5_CH2_DMA2REQ	0x00000008            // TIM5 channel 2 DMA request
#define TIM10_CH1_DMA2REQ	0x00000008            // TIM10 channel 1 DMA request

//DMA2 CH5
#define ADC3_DMA2REQ			0x00000010            // ADC3 DMA request
#define TIM5_CH1_DMA2REQ	0x00000010            // TIM5 channel 1 DMA request
#define USB_DMA2REQ				0x00000010            // USB DMA request



#define DMA1      ((HHD32F1_DMA_TypeDef                *) HHD_DMA1_BASE)
#define DMA2      ((HHD32F1_DMA_TypeDef                *) HHD_DMA2_BASE)


#define ENABLEDMA1CLK (SYSCON->SYSAHBCLKCTRL.bit.DMA1CLK = 1)
#define ENABLEDMA2CLK (SYSCON->SYSAHBCLKCTRL.bit.DMA2CLK = 1)

void DMA_SETBASEPTR(HHD32F1_DMA_TypeDef *DMAx, uint32_t addr);
void DMA_Enable(HHD32F1_DMA_TypeDef *DMAx);
void DMA_Disable(HHD32F1_DMA_TypeDef *DMAx);
void DMA_SWRequest(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl);
void DMA_UseBurstSet(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl);
void DMA_UseBurstClr(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl);
void DMA_ReqMaskSet(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl);
void DMA_ReqMaskClr(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl);
void DMA_CHEnableSet(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl);
void DMA_CHEnableClr(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl);
void DMA_CHPrioritySet(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl);
void DMA_CHPriorityClr(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl);
int  DMA_IRQStatus(HHD32F1_DMA_TypeDef *DMAx);
void DMA_IRQEnable(HHD32F1_DMA_TypeDef *DMAx, uint32_t chnl);

#endif /* end __DMA_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
