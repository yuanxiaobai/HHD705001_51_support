/*****************************************************************************
 *   hhd_sys.h:  Header file for HHD32F1xx Microprocessors
 *
 *   Copyright(C) 2015¡£
 *   All rights reserved.
 *
 *   History
 *   2015  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __SYS_H
#define __SYS_H
#include "hhd32f1xx.h"


//--CRC Registers BITS Field---------------------------------------------------
struct SYSMEMREMAP_BITS {									// bit description
				uint32_t MAP:2;                   // System memory remap
				uint32_t RSVD:30;                 // 31:2 reserved
};
union SYSMEMREMAP_REG {
				uint32_t				all;
				struct SYSMEMREMAP_BITS	bit;
};

struct SYSPLLCTRL_BITS {
				uint32_t PLLM:6;                  // PLL M
	      uint32_t PLLN:6;                  // PLL N
	      uint32_t OD:2;                    // output divider
		    uint32_t OEN:1;                   // PLL output enable
		    uint32_t BP:1;                    // Bypass PLL in to out.
        uint32_t RSVD:16;                 // 31:16 reserved
};

union SYSPLLCTRL_REG {
				uint32_t				all;
				struct SYSPLLCTRL_BITS	bit;
};

struct SYSPLLSTAT_BITS {
				uint32_t LOCK:1;                  // PLL Lock status
        uint32_t RSVD:31;                 // 31:1 reserved
};

union SYSPLLSTAT_REG {
				uint32_t				all;
				struct SYSPLLSTAT_BITS	bit;
};


struct SYSOSCCTRL_BITS {
				uint32_t BYPASS:1;                // PLL Lock status
        uint32_t FREQSEL:1;               // Frequence sel; 0: OSC 0.4-2.5M,
	                                        //                1: OSC 2.5-16M.
        uint32_t RSVD:30;                 // 31:1 reserved
};

union SYSOSCCTRL_REG {
				uint32_t				all;
				struct SYSPLLSTAT_BITS	bit;
};

struct SYSRESSTAT_BITS {									// bit description
				uint32_t POR:1;                   // 		POR reset status 
				uint32_t EXTRST:1;                //		reset status 
				uint32_t WDTRST:1;                // 		Status of the Watchdog reset 
				uint32_t BOD:1;                   // 		Status of the Brown-out detect reset 
				uint32_t SYSRST:1;                // 		Status of the software system reset. 
				uint32_t RSVD:27;                 // 31:5 reserved
};
union SYSRESSTAT_REG {
				uint32_t				all;
				struct SYSRESSTAT_BITS	bit;
};


struct SYSPLLCLKSEL_BITS {
				uint32_t LOCK:2;                  // PLL source select
        uint32_t RSVD:30;                 // 31:2 reserved
};

union SYSPLLCLKSEL_REG {
				uint32_t				all;
				struct SYSPLLCLKSEL_BITS	bit;
};

struct SYSPLLCLKUEN_BITS {
				uint32_t ENA:1;                   // PLL source change enable
        uint32_t RSVD:31;                 // 31:1 reserved
};

union SYSPLLCLKUEN_REG {
				uint32_t				all;
				struct SYSPLLCLKUEN_BITS	bit;
};



struct BODCTRL_BITS {									    // bit description
				uint32_t RSVD0:4;
				uint32_t BODRSTEN :1;             //		BOD reset enable 
				uint32_t RSVD1:1;                     
				uint32_t BODINTCLR:1;             // Write 1 to clear interrupt signal 
				uint32_t RSVD2:25;                      
};
union BODCTRL_REG {
				uint32_t				all;
				struct BODCTRL_BITS	bit;
};

struct WDTOSCCTRL_BITS {									// bit description
				uint32_t DIVSEL:5;                //	 		Select divider for Fclkana .  
				uint32_t CTRIM:3;                 //			trim watchdog oscillator capacitor
				uint32_t RTRIM:4;                 //			trim watchdog oscillator resistor
				uint32_t WDTCLKSRC:1;             //			Watch dog timer clock source. 
				uint32_t RSVD:19;                      
};
union WDTOSCCTRL_REG {
				uint32_t				all;
				struct WDTOSCCTRL_BITS	bit;
};

struct IRCCTRL_BITS {									    // bit description
				uint32_t CTRIM:2;                 //C Trim value
				uint32_t RTRIM:3;                 //R Trim value
				uint32_t SW:1;                    //40MHz/48MHz switch, 0:40MHz,1:48MHz
				uint32_t RSVD:26;                      
};
union IRCCTRL_REG {
				uint32_t				all;
				struct IRCCTRL_BITS	bit;
};

struct RTCCFG_BITS {									    // bit description
				uint32_t RSVD0:11;                  
				uint32_t RTCCLK:2;                //RTC clock source select
				uint32_t RSVD1:19;                      
};
union RTCCFG_REG {
				uint32_t				all;
				struct RTCCFG_BITS	bit;
};


struct MAINCLKSEL_BITS {									 // bit description
				uint32_t SEL:2;                    //Clock source for main clock 
				uint32_t RSVD:30;                      
};
union MAINCLKSEL_REG {
				uint32_t				all;
				struct MAINCLKSEL_BITS	bit;
};

struct MAINCLKUEN_BITS {									 // bit description
				uint32_t ENA:2;                    //Enable main clock source update  
				uint32_t RSVD:30;                      
};
union MAINCLKUEN_REG {
				uint32_t				all;
				struct MAINCLKUEN_BITS	bit;
};

struct SYSAHBCLKDIV_BITS {								 // bit description
				uint32_t DIV:8;                    //System AHB clock divider values  
				uint32_t RSVD:24;                      
};
union SYSAHBCLKDIV_REG {
				uint32_t				all;
				struct SYSAHBCLKDIV_BITS	bit;
};

struct ADCCLKDIV_BITS {								     // bit description
				uint32_t DIV:8;                    // ADC clock divider values  
				uint32_t RSVD:24;                      
};
union ADCCLKDIV_REG {
				uint32_t				all;
				struct ADCCLKDIV_BITS	bit;
};

struct SYSAHBCLKCTRL_BITS {								    // bit description
				uint32_t DMA1CLK:1;                   //Enables clock for DMA1 
				uint32_t DMA2CLK:1;                   //Enables clock for DMA1 
				uint32_t RAMCLK:1;                    //Enables clock for RAM. 
				uint32_t RSVD1:1;
				uint32_t FLASHCLK:1;                  //Enables clock for FLASH Control. 
				uint32_t RSVD2:1;                     // 
				uint32_t CRCCLK:1;                    //Enables clock for CRC. 
				uint32_t RSVD3:3;                     // 
				uint32_t SDIOCLK:1;                   //Enables clock for SDIO. 
				uint32_t RSVD4:21;                    //  
};
union SYSAHBCLKCTRL_REG {
				uint32_t				all;
				struct SYSAHBCLKCTRL_BITS	bit;
};

struct SYSAPB2CLKCTRL_BITS {				   			 // bit description
				uint32_t AFIOCLK:1;                   //Enables clock for AFIO 
				uint32_t RSVD1:1;                     //
				uint32_t PACLK:1;                     //Enables clock for GPIOA. 
				uint32_t PBCLK:1;                     //Enables clock for GPIOB.
				uint32_t PCCLK:1;                     //Enables clock for GPIOC.
				uint32_t PDCLK:1;                     //Enables clock for GPIOD.
				uint32_t PECLK:1;                     //Enables clock for GPIOE.
				uint32_t PFCLK:1;                     //Enables clock for GPIOF.
				uint32_t PGCLK:1;                     //Enables clock for GPIOG. 
				uint32_t ADC1CLK:1;                   //Enables clock for ADC1. 
				uint32_t ADC2CLK:1;                   //Enables clock for ADC2. 
				uint32_t TIM1CLK:1;                   //Enables clock for TIM1. 
				uint32_t SPI1CLK:1;                   //Enables clock for SPI1. 
				uint32_t TIM8CLK:1;                   //Enables clock for TIM8. 
				uint32_t UART1CLK:1;                  //Enables clock for UART1. 
				uint32_t ADC3CLK:1;                   //Enables clock for ADC3. 
				uint32_t RSVD2:3;                     //
				uint32_t TIM9CLK:1;                   //Enables clock for TIM9. 
				uint32_t TIM10CLK:1;                  //Enables clock for TIM10. 
				uint32_t TIM11CLK:1;                  //Enables clock for TIM11. 
				uint32_t RSVD3:10;                   //  
};
union SYSAPB2CLKCTRL_REG {
				uint32_t				all;
				struct SYSAPB2CLKCTRL_BITS	bit;
};


struct SYSAPB1CLKCTRL_BITS {					   		  // bit description
				uint32_t TIM2CLK:1;                   //Enables clock for TIM2 
				uint32_t TIM3CLK:1;                   //Enables clock for TIM3 
				uint32_t TIM4CLK:1;                   //Enables clock for TIM4. 
				uint32_t TIM5CLK:1;                   //Enables clock for TIM5.
				uint32_t TIM6CLK:1;                   //Enables clock for TIM6.
				uint32_t TIM7CLK:1;                   //Enables clock for TIM7.
				uint32_t TIM12CLK:1;                  //Enables clock for TIM12.
				uint32_t TIM13CLK:1;                  //Enables clock for TIM13.
				uint32_t TIM14CLK:1;                  //Enables clock for TIM14. 
				uint32_t RSVD1:2;                     // 
				uint32_t WWDTCLK:1;                   //Enables clock for WWDT. 
				uint32_t RSVD2:2;                     //
        uint32_t SPI2CLK:1;                   //Enables clock for SPI2. 
        uint32_t SPI3CLK:1;                   //Enables clock for SPI3. 
				uint32_t RSVD3:1;                     //
				uint32_t UART2CLK:1;                  //Enables clock for UART2. 
				uint32_t UART3CLK:1;                  //Enables clock for UART3. 
				uint32_t UART4CLK:1;                  //Enables clock for UART4. 
				uint32_t UART5CLK:1;                  //Enables clock for UART5. 
				uint32_t I2C1CLK:1;                   //Enables clock for I2C1. 
				uint32_t I2C2CLK:1;                   //Enables clock for I2C2. 
				uint32_t USBCLK:1;                    //Enables clock for USB.
        uint32_t RSVD4:1;                     //
    uint32_t CAN1CLK: 1;                   //Enables clock for CAN1.
    uint32_t CAN2CLK: 1;                  //Enables clock for CAN2.
    //uint32_t RSVD5:1;                     //
    uint32_t RTCCLK: 1;                   //Enables clock for RTC.
    uint32_t PMUCLK: 1;                   //Enables clock for PMU.
    uint32_t DACCLK: 1;                   //Enables clock for DAC.
    //uint32_t CAN2CLK:1;                   //Enables clock for CAN2.
    uint32_t RSVD6: 2;                    //
};
union SYSAPB1CLKCTRL_REG {
				uint32_t				all;
				struct SYSAPB1CLKCTRL_BITS	bit;
};


struct APB2RESET_BITS {							           // bit description
				uint32_t AFIORSTN:1;                   //Enables clock for AFIO 
				uint32_t RSVD1:1;                      //
				uint32_t PARSTN:1;                     //Enables clock for GPIOA. 
				uint32_t PBRSTN:1;                     //Enables clock for GPIOB.
				uint32_t PCRSTN:1;                     //Enables clock for GPIOC.
				uint32_t PDRSTN:1;                     //Enables clock for GPIOD.
				uint32_t PERSTN:1;                     //Enables clock for GPIOE.
				uint32_t PFRSTN:1;                     //Enables clock for GPIOF.
				uint32_t PGRSTN:1;                     //Enables clock for GPIOG. 
				uint32_t ADC1RSTN:1;                   //Enables clock for ADC1. 
				uint32_t ADC2RSTN:1;                   //Enables clock for ADC2. 
				uint32_t TIM1RSTN:1;                   //Enables clock for TIM1. 
				uint32_t SPI1RSTN:1;                   //Enables clock for SPI1. 
				uint32_t TIM8RSTN:1;                   //Enables clock for TIM8. 
				uint32_t UART1RSTN:1;                 //Enables clock for UART1. 
				uint32_t RSVD2:7;                   //Enables clock for ADC3. 
				//uint32_t RSVD2:3;                      //
				uint32_t GMACRST:1;
				uint32_t SPI4RST:1;                   //Enables clock for TIM9. 
				uint32_t SPI5RST:1;                  //Enables clock for TIM10. 
				
				uint32_t RSVD3:7;                     //  
};
union APB2RESET_REG {
				uint32_t				all;
				struct APB2RESET_BITS	bit;
};


struct APB1RESET_BITS {							           // bit description
				uint32_t TIM2RSTN:1;                   //Enables clock for TIM2 
				uint32_t TIM3RSTN:1;                   //Enables clock for TIM3 
				uint32_t TIM4RSTN:1;                   //Enables clock for TIM4. 
				uint32_t TIM5RSTN:1;                   //Enables clock for TIM5.
				uint32_t TIM6RSTN:1;                   //Enables clock for TIM6.
				uint32_t TIM7RSTN:1;                   //Enables clock for TIM7.
				uint32_t TIM12RSTN:1;                  //Enables clock for TIM12.
				uint32_t TIM13RSTN:1;                  //Enables clock for TIM13.
				uint32_t TIM14RSTN:1;                  //Enables clock for TIM14. 
				uint32_t RSVD1:2;                      // 
				uint32_t WWDTRSTN:1;                   //Enables clock for WWDT. 
				uint32_t RSVD2:2;                      //
        uint32_t SPI2RSTN:1;                   //Enables clock for SPI2. 
        uint32_t SPI3RSTN:1;                   //Enables clock for SPI3. 
				uint32_t RSVD3:1;                      //
				uint32_t UART2RSTN:1;                  //Enables clock for UART2. 
				uint32_t UART3RSTN:1;                  //Enables clock for UART3. 
				uint32_t UART4RSTN:1;                  //Enables clock for UART4. 
				uint32_t UART5RSTN:1;                  //Enables clock for UART5. 
				uint32_t I2C1RSTN:1;                   //Enables clock for I2C1. 
				uint32_t I2C2RSTN:1;                   //Enables clock for I2C2. 
				uint32_t USBRSTN:1;                    //Enables clock for USB.
        uint32_t RSVD4:1;                      //
    uint32_t CAN1RSTN: 1;                   //Enables clock for CAN1.
    uint32_t CAN2RSTN: 1;                  //Enables clock for CAN2.
    //uint32_t RSVD5:1;                      //
    uint32_t RTCRSTN: 1;                   //Enables clock for RTC.
    uint32_t PMURSTN: 1;                   //Enables clock for PMU.
    uint32_t DACRSTN: 1;                   //Enables clock for DAC.
    //uint32_t CAN2RSTN:1;                   //Enables clock for CAN2.
    uint32_t RSVD6: 2;                     //
};
union APB1RESET_REG {
				uint32_t				all;
				struct APB1RESET_BITS	bit;
};
struct RCCCFGR_BITS {							           // bit description
				uint32_t RSVD1:8;
				uint32_t PCLK1SEL:3;
				uint32_t PCLK2SEL:3;
				uint32_t RSVD2:18;
	
};
union RCCCFGR_REG {
				uint32_t				all;
				struct RCCCFGR_BITS		bit;
};

struct UARTCLKDIV_BITS {									 // bit description
				uint32_t DIV:8;                    //UARTn clock divider values 
				uint32_t RSVD:24;                      
};
union UARTCLKDIV_REG {
				uint32_t				all;
				struct UARTCLKDIV_BITS	bit;
};


struct CLKOUTCLKSEL_BITS {								 // bit description
				uint32_t SEL:3;                    //CLKOUT clock source 
				uint32_t RSVD:29;                      
};
union CLKOUTCLKSEL_REG {
				uint32_t				all;
				struct CLKOUTCLKSEL_BITS	bit;
};

struct CLKOUTUEN_BITS {									   // bit description
				uint32_t ENA:1;                    //Enable CLKOUT clock source update 
				uint32_t RSVD:31;                      
};
union CLKOUTUEN_REG {
				uint32_t				all;
				struct CLKOUTUEN_BITS	bit;
};

struct CLKOUTDIV_BITS {									   // bit description
				uint32_t DIV:8;                    //Clock divider value  
				uint32_t RSVD:24;                      
};
union CLKOUTDIV_REG {
				uint32_t				all;
				struct CLKOUTDIV_BITS	bit;
};

struct IOCONFIGCLKDIV_BITS {							 // bit description
				uint32_t DIV:8;                    //Clock divider value  
				uint32_t RSVD:24;                      
};
union IOCONFIGCLKDIV_REG {
				uint32_t				all;
				struct IOCONFIGCLKDIV_BITS	bit;
};

struct PCON_BITS {									       // bit description
				uint32_t RSVD0:1;
				uint32_t DPDEN:1;                  //Power-down mode enable   
				uint32_t RSVD1:6;
				uint32_t SLEEPFLAG:1;              //Sleep mode flag 
				uint32_t RSVD2:2;
				uint32_t DPDFLAG:1;                //Power-down flag 
				uint32_t RSVD3:20;                      
};
union PCON_REG {
				uint32_t				all;
				struct PCON_BITS	bit;
};

struct PDSLEEPCFG_BITS {									 // bit description
				uint32_t RSVD0:3;
				uint32_t BOD_PD:1;                 //BOD power-down control in Deep-sleep mode   
				uint32_t RSVD1:1;
				uint32_t RTCOSC_PD:1;              //RTC oscillator power-down control in Deep-sleep mode 
				uint32_t WDTOSC_PD:1;					     //Watchdog oscillator power-down in Deep-sleep mode
				uint32_t RSVD2:25;                      
};
union PDSLEEPCFG_REG {
				uint32_t				all;
				struct PDSLEEPCFG_BITS	bit;
};

struct PDAWAKECFG_BITS {									 // bit description
				uint32_t RSVD0:1;
				uint32_t IRC_PD:1;                 //IRC oscillator power-down 
				uint32_t FLASH_PD:1;
				uint32_t BOD_PD:1;                 //BOD detector power-down 
				uint32_t DAC_PD:1;                 //DAC power-down 
				uint32_t RTCOSC_PD:1;              //RTC oscillator power-down 
				uint32_t WDTOSC_PD:1;              //Watchdog oscillator power-down 
				uint32_t PLL_PD:1;                 //PLL power-down 
				uint32_t SYSOSC_PD:1;              //External OSC power-down 
				uint32_t RSVD2:23;                      
};
union PDAWAKECFG_REG {
				uint32_t				all;
				struct PDAWAKECFG_BITS	bit;
};
union PDRUNCFG_REG {
				uint32_t				all;
				struct PDAWAKECFG_BITS	bit;
};

struct USBCTRL_BITS {									 		// bit description
				uint32_t PHYPD:1;
				uint32_t SUSPEND:1;                 
				uint32_t SPEED:1;
				uint32_t RCV_EN:1;                  
				uint32_t DPPU:1;                  
				uint32_t DPPU_LO:1;               
				uint32_t DMPU:1;              
				uint32_t DMPU_LO:1;                  
				uint32_t PULLDN:1; 
				uint32_t TX_DP:1;
				uint32_t TX_DM:1;
				uint32_t TX_EN_N:1;
				uint32_t SUSST:1;
				uint32_t PULSE:1;
				uint32_t NRSTO:1;	
				uint32_t VP:1;
				uint32_t VM:1;
				uint32_t RCV:1;	
				uint32_t RSVD2:14;                      
};

union USBCTRL_REG {
				uint32_t				all;
				struct USBCTRL_BITS	bit;
};

struct GMACCTRL_BITS {									 		// bit description
				uint32_t RSVD1:14;                 
				uint32_t MODE:3;
				uint32_t RSVD2:15;                      
};
union GMACCTRL_REG {
				uint32_t				all;
				struct GMACCTRL_BITS	bit;
};
struct EXTICTL_BITS {									   // bit description
				uint32_t CTLPX0:1;   //Edge select for pin Px0 to trigger interrupt . 
				uint32_t CTLPX1:1;   //Edge select for pin Px1 to trigger interrupt. 
				uint32_t CTLPX2:1;   //Edge select for pin Px2 to trigger interrupt.
				uint32_t CTLPX3:1;   //Edge select for pin Px3 to trigger interrupt. 
				uint32_t CTLPX4:1;   //Edge select for pin Px4 to trigger interrupt. 
				uint32_t CTLPX5:1;   //Edge select for pin Px5 to trigger interrupt. 
				uint32_t CTLPX6:1;   //Edge select for Px6 to trigger interrupt. 
				uint32_t CTLPX7:1;   //Edge select for Px7 to trigger interrupt. 
				uint32_t CTLPX8:1;   //Edge select for Px8 to trigger interrupt. 
				uint32_t CTLPX9:1;   //Edge select for Px9 to trigger interrupt. 
				uint32_t CTLPX10:1;  //Edge select for Px10 to trigger interrupt. 
				uint32_t CTLPX11:1;  //Edge select for Px11 to trigger interrupt.
				uint32_t CTLPX12:1;  //Edge select for Px12 to trigger interrupt.
				uint32_t CTLPX13:1;  //Edge select for Px13 to trigger interrupt.
				uint32_t CTLPX14:1;  //Edge select for Px14 to trigger interrupt.
				uint32_t CTLPX15:1;  //Edge select for Px15 to trigger interrupt.
				uint32_t SYNCMODE:1; //SYNC Mode
				uint32_t GPIOSEL:3;  //GPIO group select, PAx - PGx
				uint32_t RSVD:12;                      
};
union EXTICTL_REG {
				uint32_t				all;
				struct EXTICTL_BITS	bit;
};

struct EXTIEN_BITS {									   // bit description
				uint32_t ERPX0:1;  //Enable pin Px0 interrupt. 
				uint32_t ERPX1:1;  //Enable pin Px1 interrupt.  
				uint32_t ERPX2:1;  //Enable pin Px2 interrupt. 
				uint32_t ERPX3:1;  //Enable pin Px3 interrupt. . 
				uint32_t ERPX4:1;  //Enable pin Px4 interrupt.  
				uint32_t ERPX5:1;  //Enable pin Px5 interrupt.  
				uint32_t ERPX6:1;  //Enable pin Px6 interrupt.  
				uint32_t ERPX7:1;  //Enable pin Px7 interrupt.  
				uint32_t ERPX8:1;  //Enable pin Px8 interrupt.  
				uint32_t ERPX9:1;  //Enable pin Px9 interrupt.  
				uint32_t ERPX10:1; //Enable pin Px10 interrupt.  
				uint32_t ERPX11:1; //Enable pin Px11 interrupt. 
				uint32_t ERPX12:1; //Enable pin Px12 interrupt. 
				uint32_t ERPX13:1; //Enable pin Px13 interrupt. 
				uint32_t ERPX14:1; //Enable pin Px14 interrupt. 
				uint32_t ERPX15:1; //Enable pin Px15 interrupt. 
				uint32_t RSVD:16;                      
};
union EXTIEN_REG {
				uint32_t				all;
				struct EXTIEN_BITS	bit;
};

struct EXTICLR_BITS {									   // bit description
				uint32_t RSRPX0:1;  // 	interrupt signal reset for pin Px0. 
				uint32_t RSRPX1:1;  // 	interrupt signal reset for pin Px1. 
				uint32_t RSRPX2:1;  // 	interrupt signal reset for pin Px2. 
				uint32_t RSRPX3:1;  // 	interrupt signal reset for pin Px3. 
				uint32_t RSRPX4:1;  // 	interrupt signal reset for pin Px4. 
				uint32_t RSRPX5:1;  // 	interrupt signal reset for pin Px5. 
				uint32_t RSRPX6:1;  // 	interrupt signal reset for pin Px6. 
				uint32_t RSRPX7:1;  // 	interrupt signal reset for pin Px7. 
				uint32_t RSRPX8:1;  // 	interrupt signal reset for pin Px8. 
				uint32_t RSRPX9:1;  // 	interrupt signal reset for pin Px9. 
				uint32_t RSRPX10:1; // 	interrupt signal reset for pin Px10. 
				uint32_t RSRPX11:1; // 	interrupt signal reset for pin Px11. 
				uint32_t RSRPX12:1; // 	interrupt signal reset for pin Px12. 
				uint32_t RSRPX13:1; // 	interrupt signal reset for pin Px13. 
				uint32_t RSRPX14:1; // 	interrupt signal reset for pin Px14. 
				uint32_t RSRPX15:1; // 	interrupt signal reset for pin Px15. 
				uint32_t RSVD:16;                      
};
union EXTICLR_REG {
				uint32_t				all;
				struct EXTICLR_BITS	bit;
};

struct EXTISTAT_BITS {									// bit description
				uint32_t SRPX0:1; // 	interrupt status for pin PX0. 
				uint32_t SRPX1:1; // 	interrupt status for pin PX1. 
				uint32_t SRPX2:1; // 	interrupt status for pin PX2. 
				uint32_t SRPX3:1; // 	interrupt status for pin PX3. 
				uint32_t SRPX4:1; // 	interrupt status for pin PX4. 
				uint32_t SRPX5:1; // 	interrupt status for pin PX5. 
				uint32_t SRPX6:1; // 	interrupt status for pin PX6. 
				uint32_t SRPX7:1; // 	interrupt status for pin PX7. 
				uint32_t SRPX8:1; // 	interrupt status for pin PX8. 
				uint32_t SRPX9:1; // 	interrupt status for pin PX9. 
				uint32_t SRPX10:1; // 	interrupt status for pin PX10. 
				uint32_t SRPX11:1; // 	interrupt status for pin PX11. 
				uint32_t SRPX12:1; // 	interrupt status for pin PX12.
				uint32_t SRPX13:1; // 	interrupt status for pin PX13.
				uint32_t SRPX14:1; // 	interrupt status for pin PX14.
				uint32_t SRPX15:1; // 	interrupt status for pin PX15.
				uint32_t RSVD:16;                      
};
union EXTISTAT_REG {
				uint32_t				all;
				struct EXTISTAT_BITS	bit;
};

struct INTNMI_BITS {									     // bit description
				uint32_t NMISRC:6;                 //NMI interrupts source select.
				uint32_t RSVD:26;                      
};
union INTNMI_REG {
				uint32_t				all;
				struct INTNMI_BITS	bit;
};


struct IOCON_BITS {									       // bit description
				uint32_t FUNC:3;                   //Selects pin function. 
				uint32_t PDE:1;                    //Pull-down mode
				uint32_t PUE:1;                    //Pull-up mode
				uint32_t CSE:1;                    //Schmitt trigger enable. 
				uint32_t INV:1;                    //Invert input 
				uint32_t SRM:1;                    //Slew rate mode 
				uint32_t RSVD1:1;                  //
				uint32_t DRV:1;                    //Drive current mode (Normal-drive pin). 
				uint32_t OD:1;                     //Open-drain mode. 
				uint32_t S_MODE:1;                 //Sample mode 
				uint32_t RSVD2:20;                      
};
union IOCON_REG {
				uint32_t				all;
				struct IOCON_BITS	bit;
};

/* ================================================================================ */
/* ================                       PMU                      ================ */
/* ================================================================================ */

/**
  * @brief Power management unit (PMU)
  */

typedef struct                             /*!< PMU Structure                        */
{
    __IO union PCON_REG  PCON;               /*!< Power control register               */
    __I  uint32_t  RESERVED0[4];
    __IO union RTCCFG_REG RTCCFG;            /*!< RTC clock control register           */
} HHD32F1_PMU_TypeDef;

/* ================================================================================ */
/* ================                      IOCON                     ================ */
/* ================================================================================ */


/**
  * @brief IO config (IOCON)
  */

typedef struct {                                          /*!< IOCON Structure                                                       */
  __IO union  IOCON_REG  PA0;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PA1;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PA2;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PA3;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PA4;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PA5;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PA6;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PA7;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PA8;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PA9;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PA10;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PA11;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PA12;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PA13;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PA14;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PA15;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PB0;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PB1;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PB2;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PB3;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PB4;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PB5;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PB6;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PB7;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PB8;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PB9;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PB10;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PB11;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PB12;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PB13;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PB14;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PB15;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PC0;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PC1;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PC2;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PC3;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PC4;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PC5;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PC6;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PC7;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PC8;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PC9;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PC10;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PC11;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PC12;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PC13;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PC14;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PC15;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PD0;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PD1;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PD2;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PD3;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PD4;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PD5;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PD6;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PD7;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PD8;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PD9;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PD10;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PD11;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PD12;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PD13;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PD14;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PD15;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PE0;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PE1;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PE2;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PE3;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PE4;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PE5;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PE6;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PE7;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PE8;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PE9;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PE10;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PE11;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PE12;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PE13;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PE14;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PE15;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PF0;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PF1;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PF2;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PF3;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PF4;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PF5;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PF6;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PF7;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PF8;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PF9;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PF10;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PF11;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PF12;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PF13;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PF14;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PF15;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PG0;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PG1;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PG2;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PG3;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PG4;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PG5;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PG6;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PG7;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PG8;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PG9;                             /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PG10;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PG11;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PG12;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PG13;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PG14;                            /*!< Pin config register                                                   */
  __IO union  IOCON_REG  PG15;                            /*!< Pin config register                                                   */
} HHD32F1_IOCON_TypeDef;


/* ================================================================================ */
/* ================                     SYSCON                     ================ */
/* ================================================================================ */


/**
  * @brief System control register (SYSCON)
  */

typedef struct {                                  /*!< SYSCON Structure                              */
  __IO union  SYSMEMREMAP_REG SYSMEMREMAP;        /*!< System memory remap register                  */
	__I  uint32_t  RESERVED11;
	__IO union  SYSPLLCTRL_REG SYSPLLCTRL;          /*!< PLL control register                          */
	__IO union  SYSPLLSTAT_REG SYSPLLSTAT;          /*!< PLL State register                            */
  __I  uint32_t  RESERVED0[4];
	__IO union  SYSOSCCTRL_REG SYSOSCCTRL;          /*!< System OSC control register                   */
  __IO union  WDTOSCCTRL_REG WDTOSCCTRL;          /*!< WDT oscillator control register               */
  __IO union  IRCCTRL_REG IRCCTRL;                /*!< Internal RC oscillator control register       */
  __I  uint32_t  RESERVED1;
  __IO union  SYSRESSTAT_REG SYSRESSTAT;          /*!< System reset status register                  */
  __I  uint32_t RESERVED2[3];
	__IO union  SYSPLLCLKSEL_REG SYSPLLCLKSEL;      /*!< System PLL source select register             */
	__IO union  SYSPLLCLKUEN_REG SYSPLLCLKUEN;      /*!< System PLL source change enable register      */
	__I  uint32_t RESERVED3[10];
  __IO union  MAINCLKSEL_REG MAINCLKSEL;          /*!< Main clock source select register             */
  __IO union  MAINCLKUEN_REG MAINCLKUEN;          /*!< Main clock source update enable register      */
  __IO union  SYSAHBCLKDIV_REG SYSAHBCLKDIV;      /*!< System AHB clock divider register             */
  __IO union  ADCCLKDIV_REG ADCCLKDIV;            /*!< ADC clock divider register                    */
  __IO union  SYSAHBCLKCTRL_REG SYSAHBCLKCTRL;    /*!< AHB clock control register                    */
	__IO union  SYSAPB2CLKCTRL_REG SYSAPB2CLKCTRL;  /*!< APB2 clock control register                   */
	__IO union  SYSAPB1CLKCTRL_REG SYSAPB1CLKCTRL;  /*!< APB1 clock control register                   */
	__IO union  APB2RESET_REG APB2RESET;            /*!< APB2 reset control register                   */
	__IO union  APB1RESET_REG APB1RESET;            /*!< APB1 reset control register                   */
	__IO union  RCCCFGR_REG RCCCFGR;				/*!< APB clock divider register                   */
  __IO union  UARTCLKDIV_REG UARTCLKDIV;          /*!< UART clock divider register                   */
  __I  uint32_t RESERVED6[17];
  __IO union  CLKOUTCLKSEL_REG CLKOUTCLKSEL;      /*!< Clockout clock source select register          */
  __IO union  CLKOUTUEN_REG CLKOUTUEN;            /*!< Clockout clock source update enable register   */
  __IO union  CLKOUTDIV_REG CLKOUTDIV;            /*!< Clockout clock divider register                */
  __I  uint32_t RESERVED7[24];
  __IO union  IOCONFIGCLKDIV_REG IOCONFIGCLKDIV;  /*!< IO input filter0 register                      */
  __IO union  BODCTRL_REG BODCTRL;                /*!< BOD power down control register                */
  __I  uint32_t RESERVED8[8];
  __IO union  INTNMI_REG INTNMI;                  /*!< NMI interrupt source configuration control     */
  __I  uint32_t  RESERVED9[34];
  __IO union  EXTICTL_REG EXTICTL;                /*!< EXTI control register                          */
  __IO union  EXTIEN_REG EXTIEN;                  /*!< EXTI enable control                            */
  __O  union  EXTICLR_REG EXTICLR;                /*!< EXTI reset register                            */
  __I  union  EXTISTAT_REG EXTISTAT;              /*!< EXTI status register                           */
  __I  uint32_t  RESERVED10[8];
  __IO union  PDSLEEPCFG_REG PDSLEEPCFG;          /*!< Power-down states in Deep-sleep mode           */
  __IO union  PDAWAKECFG_REG PDAWAKECFG;          /*!< Power-down states after wake-up from Deep-sleep mode*/
  __IO union  PDRUNCFG_REG PDRUNCFG;              /*!< Power-down configuration register              */
	__I  uint32_t RESERVED13[9];
	__IO union  USBCTRL_REG USBCTRL;
	__I  uint32_t RESERVED14[3];
	__IO union  GMACCTRL_REG GMACCTRL;

} HHD32F1_SYSCON_TypeDef;


//Re_Define PMU, IOCON and SYSCON
#define PMU					((HHD32F1_PMU_TypeDef     *) HHD_PWR_BASE    )
#define IOCON				((HHD32F1_IOCON_TypeDef   *) HHD_AFIO_BASE   )
#define SYSCON				((HHD32F1_SYSCON_TypeDef  *) HHD_SYSCON_BASE )

#define IRC_CLK 			0x0
#define MAIN_CLK 			0x1
#define SYS_CLK 			0x2
#define WDT_CLK 			0x3
#define RTC_CLK 			0x4


#define AHB_IIC 		0x20
#define AHB_CRC 		0x40
#define AHB_CT16B0 	0x80 
#define AHB_CT16B1 	0x100 
#define AHB_CT16B2 	0x200 
#define AHB_CT16B3 	0x400
#define AHB_SPI 		0x800
#define AHB_UART0 	0x1000 
#define AHB_UART1 	0x2000
#define AHB_ADC 		0x4000
#define AHB_WDT 		0x8000
#define AHB_IOCON 	0x10000
#define AHB_PWM 		0x20000
#define AHB_RTC 		0x80000


#define PD_IRC 		0x02
#define PD_BOD 		0x08
#define PD_ADC 		0x10
#define PD_RTCOSC 0x20
#define PD_WDTOSC 0x40



#define RST_SPI 		0x1
#define RST_IIC 		0x2
#define RST_UART0 	0x4 
#define RST_UART1 	0x8
#define RST_CT16B0 	0x20 
#define RST_CT16B1 	0x40 
#define RST_CT16B2 	0x80 
#define RST_CT16B3 	0x100
#define RST_PWM 		0x200
#define RST_CRC 		0x400
#define RST_ADC 		0x1000


#define BOD_INT 		0
#define BOD_RESET 	1

#define IO_PIN0 		0x00000001
#define IO_PIN1 		0x00000002
#define IO_PIN2 		0x00000004
#define IO_PIN3 		0x00000008
#define IO_PIN4 		0x00000010
#define IO_PIN5 		0x00000020
#define IO_PIN6 		0x00000040
#define IO_PIN7 		0x00000080
#define IO_PIN8  		0x00000100
#define IO_PIN9  		0x00000200
#define IO_PIN10 		0x00000400
#define IO_PIN11 		0x00000800
#define IO_PIN12 		0x00001000
#define IO_PIN13 		0x00002000
#define IO_PIN14 		0x00004000
#define IO_PIN15 		0x00008000

#define RISE_EDGE 	0
#define FALL_EDGE 	1
#define BOTH_EDGE 	2

#define SYS_MemRemaptoBSL   (SYSCON->SYSMEMREMAP.bit.MAP=0)
#define SYS_MemRemaptoSRAM  (SYSCON->SYSMEMREMAP.bit.MAP=1)
#define SYS_MemRemaptoFlash (SYSCON->SYSMEMREMAP.bit.MAP=2)

void SYS_SystemInitial(void);
void SYS_SelectMainClkSrc(uint8_t src);
void SYS_SetAHBClkDivider (uint8_t div);
void SYS_SelectWDTClkSrc(uint8_t src);
void SYS_SelectClkOutSrc(uint8_t src);
void SYS_SetClkOutDivider(uint8_t div);
void SYS_EnableClkOut(void);
void SYS_DisableClkOut(void);
void SYS_SetIOFilter(uint8_t ticks);
void SYS_PowerDownAngIP(uint32_t angips);
void SYS_PowerDownAngIP(uint32_t angips);
void SYS_EnablePhrClk(uint32_t phrs);
void SYS_DisablePhrClk(uint32_t phrs);
void SYS_ResetPhr(uint32_t phrs);
void SYS_ResetSystem(void);
void SYS_BODConfigure(uint8_t bodsel);
uint32_t SYS_GetResetStatus(void);
void SYS_ClearResetStatus (void);
void SYS_EnterSleep (void);
void SYS_SetDeepSleepWakeupPin (uint16_t selio, uint16_t edge);
void SYS_ResetDeepSleepWakeupPin(void);
void SYS_EnterDeepSleep (uint32_t deepsleepconfig, uint32_t wakeupconfig);
void SYS_EnterPowerDown (uint32_t powerdownconfig);
void SYS_IOConfig(union IOCON_REG *pio, uint32_t config);
void SYS_IOSetPullup(union IOCON_REG *pio);
void SYS_IOSetPulldown (union IOCON_REG *pio);
void SYS_IOSwitchtoAng (union IOCON_REG *pio);
void SYS_IOSwitchtoDigit (union IOCON_REG *pio);
void SYS_IOEnableFilter (union IOCON_REG *pio);
void SYS_IODisableFilter (union IOCON_REG *pio);


#endif /* end __SYS__H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
