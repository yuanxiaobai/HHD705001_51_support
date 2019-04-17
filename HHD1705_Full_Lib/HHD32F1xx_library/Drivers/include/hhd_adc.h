/*****************************************************************************
 *   HHD_adc.h:  Header file for  HHD32F1xx32F1xx Family Microprocessors
 *
 *   Copyright(C) 2015,  tech. Ltd.
 *   All rights reserved.
 *
 *   History
 *   2015  ver 2.00    Prelimnary version, first Release
 *
******************************************************************************/

#ifndef __ADC_H 
#define __ADC_H

#include "hhd32f1xx.h"

//--ADC Registers BITS Field---------------------------------------------------------------------------------------
struct ADC_CR_BITS	{
			uint32_t CNVEN:8;	  //		Enable ADC conversion value to DR0~DR7
			uint32_t CLKDIV:8;	// 		The APB clock (PCLK) divider 
			uint32_t BURST:1;	  // 		Burst mode control. 
			uint32_t RSVD0:7;	  // 
			uint32_t START:4;	  // 		Conversion starts control.
			uint32_t EDGE:1;	  // 		Edge control. This bit is significant only when the START field contains 010-111. 
			uint32_t SCMODE:1;	//		ADC converter sample clock selection, must be 1
			uint32_t PD:1;  	  //    ADC Power -down
	    uint32_t DMAEN:1;  	//    ADC DMA EN
};
union ADC_CR_REG {
				uint32_t				all;
				struct  ADC_CR_BITS		bit;
};

struct ADC_GDR_BITS	{
			uint32_t RESULT:12;	//		Last conversion results
			uint32_t CHN:3;	    // 		Last conversion ADC channel 
			uint32_t OVERRUN:1;	// 		Results override flag 
			uint32_t DONE:1;	  // 		Conversion complete flag
			uint32_t RSVD:15;	  // 
};
union ADC_GDR_REG {
				uint32_t				all;
				struct  ADC_GDR_BITS		bit;
};

struct ADC_CHSEL_BITS	{
			uint32_t DR0CHSEL:4;	//		Select AD channel to be converted in DR0
			uint32_t DR1CHSEL:4;	//		Select AD channel to be converted in DR1 
			uint32_t DR2CHSEL:4;	//		Select AD channel to be converted in DR2 
			uint32_t DR3CHSEL:4;	//		Select AD channel to be converted in DR3 
			uint32_t DR4CHSEL:4;	//		Select AD channel to be converted in DR4 
			uint32_t DR5CHSEL:4;	//		Select AD channel to be converted in DR5 
			uint32_t DR6CHSEL:4;	//		Select AD channel to be converted in DR6
			uint32_t DR7CHSEL:4;	//		Select AD channel to be converted in DR7 
};
union ADC_CHSEL_REG {
				uint32_t				all;
				struct  ADC_CHSEL_BITS		bit;
};

struct ADC_INTEN_BITS	{
			uint32_t INTEN:8;	   //		Eenable interrupt when Selected DRn receive conversin result
			uint32_t GINTEN:1;	 //		Eenable interrupt when every conversin complete 
			uint32_t RSVD:23;
};

union ADC_INTEN_REG {
				uint32_t				all;
				struct  ADC_INTEN_BITS		bit;
};

struct ADC_DR_BITS	{
			uint32_t RESULT:12;	//		Conversin result
			uint32_t RSVD:18;
			uint32_t OVERRUN:1;	//		Override flag 
			uint32_t DONE:1;	  //		Conversion complete flag 
};
union ADC_DR_REG {
				uint32_t				all;
				struct  ADC_DR_BITS		bit;
};

struct ADC_STAT_BITS	{
			uint32_t DONE:8;	      //These bits mirror the DONE status flags that appear in the result register for each A/D channel. 
			uint32_t OVERRUN:8;	    //These bits mirror the OVERRRUN status flags that appear in the result register for each A/D channel. 
			uint32_t ADINT:1;	      //This bit is the A/D interrupt flag.  
			uint32_t HILMTFLAG0:1;	//High limit 0 status. 
			uint32_t HILMTFLAG1:1;	//High limit 1 status. 
			uint32_t LOLMTFLAG0:1;	//Low limit 0 status.
			uint32_t LOLMTFLAG1:1;	//Low limit 1 status. 
			uint32_t ADCRDY:1;	    //The bit value 1 indicates ADC_ converter is ready to use after ADC is enable.
			uint32_t RSVD:10; 
};
union ADC_STAT_REG {
				uint32_t				all;
				struct  ADC_STAT_BITS		bit;
};

struct ADC_HILMT_BITS	{
			uint32_t HILMT0:12;	// High Limit value0
			uint32_t CHNSEL0:3;	// channel to be compared with the high limit value0
			uint32_t INTEN0:1;	// Enable High Limit0 interrupt 
			uint32_t HILMT1:12;	// High Limit value1
			uint32_t CHNSEL1:3;	// channel to be compared with the high limit value1
			uint32_t INTEN1:1;	// Enable High Limit1 interrupt
};
union ADC_HILMT_REG {
				uint32_t				all;
				struct  ADC_HILMT_BITS		bit;
};

struct ADC_LOLMT_BITS	{
			uint32_t LOLMT0:12;	// Low Limit value0
			uint32_t CHNSEL0:3;	// channel to be compared with the low limit value0
			uint32_t INTEN0:1;	// Enable low Limit0 interrupt 
			uint32_t LOLMT1:12;	// low Limit value1
			uint32_t CHNSEL1:3;	// channel to be compared with the low limit value1
			uint32_t INTEN1:1;	// Enable low Limit1 interrupt
};
union ADC_LOLMT_REG {
				uint32_t				all;
				struct  ADC_LOLMT_BITS		bit;
};

struct ADC_SSCR_BITS	{
			uint32_t ADC_TRIG:1;	// Set this bit to trigger ADC_ to do one time conversion.
			uint32_t RSVD:31;
};
union ADC_SSCR_REG {
				uint32_t				all;
				struct  ADC_SSCR_BITS		bit;
};

/* ================================================================================ */
/* ================                       ADC                      ================ */
/* ================================================================================ */


/**
  * @brief Analog-to-Digital Converter (ADC)
  */

typedef struct {                                              /*!< ADC Structure                                                         */
  __IO union  ADC_CR_REG      CR;                             /*!< ADC_ control register                                                  */
  __IO union  ADC_GDR_REG     GDR;                            /*!< ADC Global Data Register                                              */
  __IO union  ADC_CHSEL_REG   CHSEL;                          /*!< Channel select control register                                       */
  __IO union  ADC_INTEN_REG   INTEN;                          /*!< ADC Interrupt Enable Register                                         */
  __IO union  ADC_DR_REG      DR[8];                          /*!< A/D Channel 0 Data Register                                           */
  __IO union  ADC_STAT_REG    STAT;                           /*!< ADC Status Register                                                   */
  __IO union  ADC_HILMT_REG   HILMT;                          /*!< ADC High Limit Control Register                                       */
  __IO union  ADC_LOLMT_REG   LOLMT;                          /*!< ADC Low Limit Control Register                                        */
  __I  uint32_t  RESERVED0;
  __IO union  ADC_SSCR_REG   SSCR;                            /*!< ADC software trigger convert register                                 */
} HHD32F_ADC_TypeDef;

#define		ADC1	((HHD32F_ADC_TypeDef	*) HHD_ADC1_BASE)
#define		ADC2	((HHD32F_ADC_TypeDef	*) HHD_ADC2_BASE)
#define		ADC3	((HHD32F_ADC_TypeDef	*) HHD_ADC3_BASE)

//AD channel sel
#define DR0EN 	0x01
#define DR1EN 	0x02
#define DR2EN 	0x04
#define DR3EN 	0x08
#define DR4EN 	0x10
#define DR5EN 	0x20
#define DR6EN 	0x40
#define DR7EN 	0x80

//AD channel sel
#define CHN0 	0x0f
#define CHN1 	0x01
#define CHN2 	0x02
#define CHN3 	0x03
#define CHN4 	0x04
#define CHN5 	0x05
#define CHN6 	0x06
#define CHN7 	0x07

//DR select
#define ADC_DR0SEL 	0
#define ADC_DR1SEL 	4
#define ADC_DR2SEL 	8
#define ADC_DR3SEL 	12
#define ADC_DR4SEL 	16
#define ADC_DR5SEL 	20
#define ADC_DR6SEL 	24
#define ADC_DR7SEL 	28

//DR int
#define ADC_DR0INT 	0x1
#define ADC_DR1INT 	0x2
#define ADC_DR2INT 	0x4
#define ADC_DR3INT 	0x8
#define ADC_DR4INT 	0x10
#define ADC_DR5INT 	0x20
#define ADC_DR6INT 	0x40
#define ADC_DR7INT 	0x80
#define ADC_GINT 		0x100

//DR index
#define ADC_DR0 	0x0
#define ADC_DR1 	0x1
#define ADC_DR2 	0x2
#define ADC_DR3 	0x3
#define ADC_DR4 	0x4
#define ADC_DR5 	0x5
#define ADC_DR6 	0x6
#define ADC_DR7 	0x7


//#define CHN1_DR0 		0xf
#define CHN1_DR0 		0x0
#define CHN2_DR0 		0x1
#define CHN3_DR0 		0x2
#define CHN4_DR0 		0x3
#define CHN5_DR0 		0x4
#define CHN6_DR0 		0x5
#define CHN7_DR0 		0x6
#define CHN8_DR0 		0x7
#define CHN9_DR0 		0x8
#define CHN10_DR0 	0x9
#define CHN11_DR0 	0xa
#define CHN12_DR0 	0xb
#define CHN13_DR0 	0xc
#define CHN14_DR0 	0xd
#define CHN15_DR0 	0xe
#define CHN16_DR0 	0xf

#define CHN1_DR1 		(0x0<<4)
#define CHN2_DR1 		(0x1<<4)
#define CHN3_DR1 		(0x2<<4)
#define CHN4_DR1 		(0x3<<4)
#define CHN5_DR1 		(0x4<<4)
#define CHN6_DR1 		(0x5<<4)
#define CHN7_DR1 		(0x6<<4)
#define CHN8_DR1 		(0x7<<4)
#define CHN9_DR1 		(0x8<<4)
#define CHN10_DR1 	(0x9<<4)
#define CHN11_DR1 	(0xa<<4)
#define CHN12_DR1 	(0xb<<4)
#define CHN13_DR1 	(0xc<<4)
#define CHN14_DR1 	(0xd<<4)
#define CHN15_DR1 	(0xe<<4)
#define CHN16_DR1 	(0xf<<4)

#define CHN1_DR2 		(0x0<<8)
#define CHN2_DR2 		(0x1<<8)
#define CHN3_DR2 		(0x2<<8)
#define CHN4_DR2 		(0x3<<8)
#define CHN5_DR2 		(0x4<<8)
#define CHN6_DR2 		(0x5<<8)
#define CHN7_DR2 		(0x6<<8)
#define CHN8_DR2 		(0x7<<8)
#define CHN9_DR2 		(0x8<<8)
#define CHN10_DR2 	(0x9<<8)
#define CHN11_DR2 	(0xa<<8)
#define CHN12_DR2 	(0xb<<8)
#define CHN13_DR2 	(0xc<<8)
#define CHN14_DR2 	(0xd<<8)
#define CHN15_DR2 	(0xe<<8)
#define CHN16_DR2 	(0xf<<8)

#define CHN1_DR3 		(0x0<<12)
#define CHN2_DR3 		(0x1<<12)
#define CHN3_DR3		(0x2<<12)
#define CHN4_DR3 		(0x3<<12)
#define CHN5_DR3 		(0x4<<12)
#define CHN6_DR3 		(0x5<<12)
#define CHN7_DR3 		(0x6<<12)
#define CHN8_DR3 		(0x7<<12)
#define CHN9_DR3 		(0x8<<12)
#define CHN10_DR3 	(0x9<<12)
#define CHN11_DR3 	(0xa<<12)
#define CHN12_DR3 	(0xb<<12)
#define CHN13_DR3 	(0xc<<12)
#define CHN14_DR3 	(0xd<<12)
#define CHN15_DR3 	(0xe<<12)
#define CHN16_DR3 	(0xf<<12)

#define CHN1_DR4 		(0x0<<16)
#define CHN2_DR4 		(0x1<<16)
#define CHN3_DR4 		(0x2<<16)
#define CHN4_DR4 		(0x3<<16)
#define CHN5_DR4 		(0x4<<16)
#define CHN6_DR4 		(0x5<<16)
#define CHN7_DR4 		(0x6<<16)
#define CHN8_DR4 		(0x7<<16)
#define CHN9_DR4 		(0x8<<16)
#define CHN10_DR4 	(0x9<<16)
#define CHN11_DR4 	(0xa<<16)
#define CHN12_DR4 	(0xb<<16)
#define CHN13_DR4 	(0xc<<16)
#define CHN14_DR4 	(0xd<<16)
#define CHN15_DR4 	(0xe<<16)
#define CHN16_DR4 	(0xf<<16)

#define CHN1_DR5 		(0x0<<20)
#define CHN2_DR5 		(0x1<<20)
#define CHN3_DR5 		(0x2<<20)
#define CHN4_DR5 		(0x3<<20)
#define CHN5_DR5 		(0x4<<20)
#define CHN6_DR5 		(0x5<<20)
#define CHN7_DR5 		(0x6<<20)
#define CHN8_DR5 		(0x7<<20)
#define CHN9_DR5 		(0x8<<20)
#define CHN10_DR5 	(0x9<<20)
#define CHN11_DR5 	(0xa<<20)
#define CHN12_DR5 	(0xb<<20)
#define CHN13_DR5 	(0xc<<20)
#define CHN14_DR5 	(0xd<<20)
#define CHN15_DR5 	(0xe<<20)
#define CHN16_DR5 	(0xf<<20)

#define CHN1_DR6 		(0x0<<24)
#define CHN2_DR6 		(0x1<<24)
#define CHN3_DR6 		(0x2<<24)
#define CHN4_DR6 		(0x3<<24)
#define CHN5_DR6 		(0x4<<24)
#define CHN6_DR6 		(0x5<<24)
#define CHN7_DR6 		(0x6<<24)
#define CHN8_DR6 		(0x7<<24)
#define CHN9_DR6 		(0x8<<24)
#define CHN10_DR6 	(0x9<<24)
#define CHN11_DR6 	(0xa<<24)
#define CHN12_DR6 	(0xb<<24)
#define CHN13_DR6 	(0xc<<24)
#define CHN14_DR6 	(0xd<<24)
#define CHN15_DR6 	(0xe<<24)
#define CHN16_DR6 	(0xf<<24)

#define CHN1_DR7 		(0x0<<28)
#define CHN2_DR7 		(0x1<<28)
#define CHN3_DR7 		(0x2<<28)
#define CHN4_DR7 		(0x3<<28)
#define CHN5_DR7 		(0x4<<28)
#define CHN6_DR7 		(0x5<<28)
#define CHN7_DR7 		(0x6<<28)
#define CHN8_DR7 		(0x7<<28)
#define CHN9_DR7 		(0x8<<28)
#define CHN10_DR7 	(0x9<<28)
#define CHN11_DR7 	(0xa<<28)
#define CHN12_DR7 	(0xb<<28)
#define CHN13_DR7 	(0xc<<28)
#define CHN14_DR7 	(0xd<<28)
#define CHN15_DR7 	(0xe<<28)
#define CHN16_DR7 	(0xf<<28)

//ADC mode
#define TRIGGERMODE 	0x0
#define BURSTMODE 		0x1

//ADC trigger option
#define ADC_NONE_START 0x0 							//No start (this value should be used when clearing PDN to 0).
#define ADC_START_BY_SOFTWAER 0x1 			//Start conversion now.
#define ADC_START_BY_CT16B2_CAP0 0x2 		//Start conversion when the edge selected by bit 28 occurs on CT16B2_CAP0.
#define ADC_START_BY_CT16B2_CAP1 0x3 		//Start conversion when the edge selected by bit 28 occurs on CT16B2_CAP1.
#define ADC_START_BY_CT16B2_MAT0 0x4 		//Start conversion when the edge selected by bit 28 occurs on CT16B2_MAT0.
#define ADC_START_BY_CT16B2_MAT1 0x5 		//Start conversion when the edge selected by bit 28 occurs on CT16B2_MAT1.
#define ADC_START_BY_CT16B3_MAT0 0x6 		//Start conversion when the edge selected by bit 28 occurs on CT16B3_MAT0.
#define ADC_START_BY_CT16B3_MAT1 0x7 		//Start conversion when the edge selected by bit 28 occurs on CT16B3_MAT1.
#define ADC_START_BY_PWM 0x8 						//Start conversion when PWM1 cycle Reload,

//ADC trigger signal edge
#define ADC_TRIGGER_RISE_EDGE 0x0
#define ADC_TRIGGER_FALL_EDGE 0x1

#define   ADC1_IssueSoftTrigger 		(ADC1->SSCR.bit.ADC_TRIG = 1)
#define   ADC1_EnableHighCmp0Int 	  (ADC1->HILMT.bit.INTEN0 = 1)
#define   ADC1_EnableHighCmp1Int 	  (ADC1->HILMT.bit.INTEN1 = 1)
#define   ADC1_EnableLowCmp0Int 		(ADC1->LOLMT.bit.INTEN0 = 1)
#define   ADC1_EnableLowCmp1Int 		(ADC1->LOLMT.bit.INTEN1 = 1)
#define   ADC1_DisableHighCmp0Int 	(ADC1->HILMT.bit.INTEN0 = 0)
#define   ADC1_DisableHighCmp1Int 	(ADC1->HILMT.bit.INTEN1 = 0)
#define   ADC1_DisableLowCmp0Int 	  (ADC1->LOLMT.bit.INTEN0 = 0)
#define   ADC1_DisableLowCmp1Int 	  (ADC1->LOLMT.bit.INTEN1 = 0)

#define   ADC2_IssueSoftTrigger 		(ADC2->SSCR.bit.ADC_TRIG = 1)
#define   ADC2_EnableHighCmp0Int 	  (ADC2->HILMT.bit.INTEN0 = 1)
#define   ADC2_EnableHighCmp1Int 	  (ADC2->HILMT.bit.INTEN1 = 1)
#define   ADC2_EnableLowCmp0Int 		(ADC2->LOLMT.bit.INTEN0 = 1)
#define   ADC2_EnableLowCmp1Int 		(ADC2->LOLMT.bit.INTEN1 = 1)
#define   ADC2_DisableHighCmp0Int 	(ADC2->HILMT.bit.INTEN0 = 0)
#define   ADC2_DisableHighCmp1Int 	(ADC2->HILMT.bit.INTEN1 = 0)
#define   ADC2_DisableLowCmp0Int 	  (ADC2->LOLMT.bit.INTEN0 = 0)
#define   ADC2_DisableLowCmp1Int 	  (ADC2->LOLMT.bit.INTEN1 = 0)

#define   ADC3_IssueSoftTrigger 		(ADC3->SSCR.bit.ADC_TRIG = 1)
#define   ADC3_EnableHighCmp0Int 	  (ADC3->HILMT.bit.INTEN0 = 1)
#define   ADC3_EnableHighCmp1Int 	  (ADC3->HILMT.bit.INTEN1 = 1)
#define   ADC3_EnableLowCmp0Int 		(ADC3->LOLMT.bit.INTEN0 = 1)
#define   ADC3_EnableLowCmp1Int 		(ADC3->LOLMT.bit.INTEN1 = 1)
#define   ADC3_DisableHighCmp0Int 	(ADC3->HILMT.bit.INTEN0 = 0)
#define   ADC3_DisableHighCmp1Int 	(ADC3->HILMT.bit.INTEN1 = 0)
#define   ADC3_DisableLowCmp0Int 	  (ADC3->LOLMT.bit.INTEN0 = 0)
#define   ADC3_DisableLowCmp1Int 	  (ADC3->LOLMT.bit.INTEN1 = 0)


#define   ENABLEADC1CLK							SYSCON->SYSAPB2CLKCTRL.all |= (1<<9)
#define   ENABLEADC2CLK							SYSCON->SYSAPB2CLKCTRL.all |= (1<<10)
#define   ENABLEADC3CLK							SYSCON->SYSAPB2CLKCTRL.all |= (1<<15)

#define   RESETADC1							    SYSCON->APB2RESET.all &= ~(1<<9)
#define   RESETADC2							    SYSCON->APB2RESET.all &= ~(1<<10)
#define   RESETADC3							    SYSCON->APB2RESET.all &= ~(1<<15)

#define   OpenADC1_IN1              IOCON->PA0.all = 7;
#define   OpenADC1_IN2              IOCON->PA1.all = 7;
#define   OpenADC1_IN3              IOCON->PA2.all = 7;
#define   OpenADC1_IN4              IOCON->PA3.all = 7;
#define   OpenADC1_IN5              IOCON->PA4.all = 7;
#define   OpenADC1_IN6              IOCON->PA5.all = 7;
#define   OpenADC1_IN7              IOCON->PA6.all = 7;
#define   OpenADC1_IN8              IOCON->PA7.all = 7;
#define   OpenADC1_IN9              IOCON->PB0.all = 7;
#define   OpenADC1_IN10             IOCON->PB1.all = 7;
#define   OpenADC1_IN11             IOCON->PC0.all = 7;
#define   OpenADC1_IN12             IOCON->PC1.all = 7;
#define   OpenADC1_IN13             IOCON->PC2.all = 7;
#define   OpenADC1_IN14             IOCON->PC3.all = 7;
#define   OpenADC1_IN15             IOCON->PC4.all = 7;
#define   OpenADC1_IN16             IOCON->PC5.all = 7;

#define   OpenADC2_IN1              IOCON->PA0.all = 7;
#define   OpenADC2_IN2              IOCON->PA1.all = 7;
#define   OpenADC2_IN3              IOCON->PA2.all = 7;
#define   OpenADC2_IN4              IOCON->PA3.all = 7;
#define   OpenADC2_IN5              IOCON->PA4.all = 7;
#define   OpenADC2_IN6              IOCON->PA5.all = 7;
#define   OpenADC2_IN7              IOCON->PA6.all = 7;
#define   OpenADC2_IN8              IOCON->PA7.all = 7;
#define   OpenADC2_IN9              IOCON->PB0.all = 7;
#define   OpenADC2_IN10             IOCON->PB1.all = 7;
#define   OpenADC2_IN11             IOCON->PC0.all = 7;
#define   OpenADC2_IN12             IOCON->PC1.all = 7;
#define   OpenADC2_IN13             IOCON->PC2.all = 7;
#define   OpenADC2_IN14             IOCON->PC3.all = 7;
#define   OpenADC2_IN15             IOCON->PC4.all = 7;
#define   OpenADC2_IN16             IOCON->PC5.all = 7;

#define   OpenADC3_IN1              IOCON->PA0.all = 7;
#define   OpenADC3_IN2              IOCON->PA1.all = 7;
#define   OpenADC3_IN3              IOCON->PA2.all = 7;
#define   OpenADC3_IN4              IOCON->PA3.all = 7;
#define   OpenADC3_IN5              IOCON->PF6.all = 7;
#define   OpenADC3_IN6              IOCON->PF7.all = 7;
#define   OpenADC3_IN7              IOCON->PF8.all = 7;
#define   OpenADC3_IN8              IOCON->PF9.all = 7;
#define   OpenADC3_IN9              IOCON->PF10.all= 7;
#define   OpenADC3_IN11             IOCON->PC0.all = 7;
#define   OpenADC3_IN12             IOCON->PC1.all = 7;
#define   OpenADC3_IN13             IOCON->PC2.all = 7;
#define   OpenADC3_IN14             IOCON->PC3.all = 7;


void ADC_Init(HHD32F_ADC_TypeDef *ADC, uint32_t conversionrate);
void ADC_DeInit(HHD32F_ADC_TypeDef *ADC);
void ADC_SetupChannels (HHD32F_ADC_TypeDef *ADC, uint32_t channelassign, uint32_t triggermode);
void ADC_SetTrigger(HHD32F_ADC_TypeDef *ADC, uint8_t triggersrc, uint8_t edge);
void ADC_SetHighCmp0(HHD32F_ADC_TypeDef *ADC, uint32_t val, uint8_t selchannel);
void ADC_SetHighCmp1(HHD32F_ADC_TypeDef *ADC, uint32_t val, uint8_t selchannel);
void ADC_SetLowCmp0 (HHD32F_ADC_TypeDef *ADC, uint32_t val, uint8_t selchannel);
void ADC_SetLowCmp1 (HHD32F_ADC_TypeDef *ADC, uint32_t val, uint8_t selchannel);
void ADC_EnableConversionInt(HHD32F_ADC_TypeDef *ADC, uint32_t inttype);
uint32_t ADC_GetConversionData(HHD32F_ADC_TypeDef *ADC, uint8_t dr);


#endif /* end __ADC_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
