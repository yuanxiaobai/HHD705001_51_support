/*****************************************************************************
 *   hhd_dac.h:  Header file for  HHD32F1xx Family Microprocessors
 *
 *   Copyright(C) 2015,  tech. Ltd.
 *   All rights reserved.
 *
 *   History
 *   2015  ver 2.00    Prelimnary version, first Release
 *
******************************************************************************/

#ifndef __DAC_H
#define __DAC_H

#include "hhd32f1xx.h"

//--ADC Registers BITS Field---------------------------------------------------------------------------------------
struct DAC_CR_BITS	{
			uint32_t DIV:8;	  	//		DAC divder
			uint32_t MODE:1;	  // 		DAC mode, sync or burst mode
			uint32_t CLR:1;		  // 		DAC controller & buffer clear
			uint32_t INTEN:1;	  // 		DAC interrupt enable
			uint32_t DMAEN:1;	  // 		DAC DMA request enable
			uint32_t DACEN:1;	  // 		DAC enable to start
			uint32_t RSVD:2;	  //
			uint32_t BUFSTAT:1;	// 		DAC Buffer state,0 : no empty
						//                               1 : empty
			uint32_t RSVD2:16;	//
};
union DAC_CR_REG {
				uint32_t			all;
				struct  DAC_CR_BITS		bit;
};

struct DAC_BUF_BITS	{
			uint32_t DACBUF:10;	//		DAC buffer port
			uint32_t RSVD:22;	  // 
};
union DAC_BUF_REG {
				uint32_t			all;
				struct  DAC_BUF_BITS		bit;
};

/* ================================================================================ */
/* ================                       DAC                      ================ */
/* ================================================================================ */


/**
  * @brief Digital-to-Analog Converter (DAC)
  */

typedef struct                                            /*!< DAC Structure                                                         */
{
    __IO union  DAC_CR_REG
        CR;                         /*!< DAC control register                                                  */
    __IO union  DAC_BUF_REG
        BUF;                        /*!< DAC Data Register                                              */
} HHD32F_DAC_TypeDef;

#define HHD_DAC1_BASE HHD_DAC_BASE
#define HHD_DAC2_BASE (HHD_DAC_BASE+0x10)

#define		DAC1	((HHD32F_DAC_TypeDef	*) HHD_DAC1_BASE)
#define		DAC2	((HHD32F_DAC_TypeDef	*) HHD_DAC2_BASE)

//DAC mode
#define SINGLEMODE 		0x0
#define BURSTMODE 		0x1

#define   ENABLEDACCLK							SYSCON->SYSAPB1CLKCTRL.all |= (1<<29)
#define   DISABLEDACCLK							SYSCON->SYSAPB1CLKCTRL.all &= ~1<<29)

#define   RESETDAC							    SYSCON->APB1RESET.all &= ~(1<<29)

#define   OpenDAC1_OUT              IOCON->PA8.all = 7;
#define   OpenDAC2_OUT              IOCON->PA9.all = 7;

#define   BUFFER_is_not_EMPTY 0

void DAC_Init(HHD32F_DAC_TypeDef *DAC, uint32_t conversionrate, uint32_t mode);
void DAC_DeInit(HHD32F_DAC_TypeDef *DAC);
void DAC_EnableInt(HHD32F_DAC_TypeDef *DAC);
void DAC_SendData(HHD32F_DAC_TypeDef *DAC, uint16_t dr);
uint32_t Get_DACBufferState(HHD32F_DAC_TypeDef *DAC);

#endif /* end __DAC_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
