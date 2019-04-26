/**************************************************************************//**
 * $Id: system_G32F1xx.c,v 1.4 2015/09/22 06:28:11 jpan Exp $
 *
 * @file     system_G32F1xx.c
 * @brief    CMSIS Cortex-M3 Device Peripheral Access Layer Source File
 *           for G32F1xx Device Series
 * @version  1.0
 * @date     26. Sep. 2015
 * @author   MCU Team
 *
 * @note
 * Copyright (C) 2015 All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 ******************************************************************************/

#include <stdint.h>
#include "hhd32f1xx.h"
#include "HHD1705_lib.h"

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

/*--------------------- Clock Configuration ----------------------------------
//
// <e> Clock Configuration
//   <e1> Main Clock Setup
//     <e2> System Oscillator Enable
//       <o3.1> Select System Oscillator Frequency Range
//                     <0=> 0.4 - 2.5 MHz
//                     <1=> 2.5 - 16 MHz
//     </e2>
//     <o4.0..2> Select Input Clock for sys_pllclkin (Register: SYSPLLCLKSEL)
//                     <0=> IRC Oscillator
//                     <1=> System Oscillator
//     <e5> Use System PLL
//                     <i> F_pll = M * F_in
//                     <i> F_in must be in the range of 10 MHz to 25 MHz
//       <o6.0..4>   M: PLL Multiplier Selection
//                     <1-32><#-1>
//       <o6.5..6>   P: PLL Divider Selection
//                     <0=> 2
//                     <1=> 4
//                     <2=> 8
//                     <3=> 16
//       <o6.7>      DIRECT: Direct CCO Clock Output Enable
//       <o6.8>      BYPASS: PLL Bypass Enable
//     </e5>
//     <o7.0..2> Select Input Clock for Main clock (Register: MAINCLKSEL)
//                     <0=> IRC Oscillator
//                     <1=> Input Clock to System PLL
//                     <2=> System PLL Clock Out
//                     <3=> WDT Oscillator
//   </e1>
//   <o10.0..7> System AHB Clock Divider <0-255>    
//                     <i> 0 = is disabled
//   <o11.0..7> Select SSP PCLK Divider <0-255> 
//                     <i> 0 = is disabled
//   <o12.0..7> Select UART PCLK Divider <0-255> 
//                     <i> 0 = is disabled
//   <o14.0..7> Select SysTick PCLK Divider <0-255> 
//                     <i> 0 = is disabled
//   <e18> CLKOUT Clock Setup
//      <o19.0..2> Select CLKOUT clock source
//                     <0=> IRC Oscillator
//                     <1=> System Oscillator
//                     <2=> WDT Oscillator
//                     <3=> Main clock
//      <o20.0..7> Select CLKOUT PCLK Divider <0-255> 
//                     <i> 0 = Gate
//   </e18>
// </e>
*/
#define CLOCK_SETUP           1
#define MAINCLK_SETUP         1
#define SYSOSC_SETUP          1
#define SYSOSCCTRL_Val        0x00000002
#define SYSPLLCLKSEL_Val      0x00000001	//external OSC
#define SYSPLL_SETUP          1 
//#define SYSPLLCTRL_Val        0x00004043    //75Mhz
#ifdef CFG_SYS_60MHZ
	#define SYSPLLCTRL_Val        0x0000414C      //60Mhz
#endif
#ifdef CFG_SYS_50MHZ
	#define SYSPLLCTRL_Val        0x0000414A    //50Mhz
#endif

#define MAINCLKSEL_Val        0x00000002	//2£ºMain clock source is PLL out
#define WDTOSC_SETUP          1
#define WDTOSCCTRL_Val        0x00000001
#define SYSAHBCLKDIV_Val      0x00000001	//1
#define SSPCLKDIV_Val      	  0x00000001
#define UARTCLKDIV_Val        0x00000001
#define SysTickCLKDIV_Val     0x00000001
#define RTCCLK_SETUP          0
#define RTCCLKDIV_Val      	  0x00000002
#define RTCCLKSEL_Val         0x00000000
#define CLKOUTCLK_SETUP       0
#define CLKOUTCLKSEL_Val      0x00000000
#define CLKOUTCLKDIV_Val      0x000000FF

/*
//-------- <<< end of configuration section >>> ------------------------------
*/

/*----------------------------------------------------------------------------
  Check the register settings
 *----------------------------------------------------------------------------*/
#define CHECK_RANGE(val, min, max)                ((val < min) || (val > max))
#define CHECK_RSVD(val, mask)                     (val & mask)

/* Clock Configuration -------------------------------------------------------*/
#if (CHECK_RSVD((SYSOSCCTRL_Val),  ~0x00000003))
   #error "SYSOSCCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((WDTOSCCTRL_Val),  ~0x000001FF))
   #error "WDTOSCCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((SYSPLLCLKSEL_Val), 0, 1))
   #error "SYSPLLCLKSEL: Value out of range!"
#endif

#if (CHECK_RSVD((SYSPLLCTRL_Val),  ~0x000FFFF))
   #error "SYSPLLCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((MAINCLKSEL_Val),  ~0x00000003))
   #error "MAINCLKSEL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((SYSAHBCLKDIV_Val), 0, 255))
   #error "SYSAHBCLKDIV: Value out of range!"
#endif


/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define __XTAL             (25000000UL)    /* Oscillator frequency             */
#define __SYS_OSC_CLK     (    __XTAL)    /* Main oscillator frequency        */
#define __IRC_OSC_CLK     (40000000UL)    /* Internal RC oscillator frequency */
#define __WDT_OSC_CLK        (32768UL)    /* Internal RC oscillator frequency */


#if (CLOCK_SETUP)                         /* Clock Setup              */
  #if (MAINCLK_SETUP)                     /* Main Clock Setup         */

    /* sys_pllclkin calculation */
    #if   ((SYSPLLCLKSEL_Val & 0x03) == 0)
      #define __SYS_PLLCLKIN           (__IRC_OSC_CLK)
    #elif ((SYSPLLCLKSEL_Val & 0x03) == 1)
      #define __SYS_PLLCLKIN           (__SYS_OSC_CLK)
    #elif ((SYSPLLCLKSEL_Val & 0x03) == 2)
      #define __SYS_PLLCLKIN           (0)
    #else
      #define __SYS_PLLCLKIN           (0)
    #endif

    #if (SYSPLL_SETUP)                    /* System PLL Setup         */
#ifdef CFG_SYS_60MHZ	
      #define  __SYS_PLLCLKOUT        60000000
#endif
#ifdef CFG_SYS_50MHZ
	#define  __SYS_PLLCLKOUT          50000000
#endif
//        #define  __SYS_PLLCLKOUT         (__SYS_PLLCLKIN / 5 *12)
    #else
      #define  __SYS_PLLCLKOUT         (__SYS_PLLCLKIN * (1))
    #endif  // SYSPLL_SETUP

    /* main clock calculation */
    #if   ((MAINCLKSEL_Val & 0x03) == 0)
      #define __MAIN_CLOCK             (__IRC_OSC_CLK)
    #elif ((MAINCLKSEL_Val & 0x03) == 1)
      #define __MAIN_CLOCK             (__SYS_OSC_CLK)
    #elif ((MAINCLKSEL_Val & 0x03) == 2)
      #define __MAIN_CLOCK             (__SYS_PLLCLKOUT)
    #elif ((MAINCLKSEL_Val & 0x03) == 3)
      #define __MAIN_CLOCK             (__WDT_OSC_CLK)
    #else
      #define __MAIN_CLOCK             (0)
    #endif

    #define __SYSTEM_CLOCK             (__MAIN_CLOCK / 1)

  #else // SYSCLK_SETUP
    #if (SYSAHBCLKDIV_Val == 0)
      #define __SYSTEM_CLOCK           (0)
    #else
      #define __SYSTEM_CLOCK           (__XTAL / SYSAHBCLKDIV_Val)
    #endif
  #endif // SYSCLK_SETUP

#else
  #define __MAIN_CLOCK                 (__IRC_OSC_CLK)
  #define __SYSTEM_CLOCK               (__XTAL)
#endif  // CLOCK_SETUP


/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = __SYSTEM_CLOCK; /*!< System Clock Frequency        */
uint32_t MainClock       = __MAIN_CLOCK;   /*!< Main Clock Frequency (Main)   */
uint32_t APB1Clock       = __SYSTEM_CLOCK; /*!< APB1 Clock Frequency          */
uint32_t APB2Clock       = __SYSTEM_CLOCK; /*!< APB2 Clock Frequency          */

/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency      */
{
  uint32_t wdt_osc = 0;


    switch (HHD_SYSCON->MAINCLKSEL & 0x03)
    {
        case 0:                             /* Internal RC oscillator             */
            SystemCoreClock = __IRC_OSC_CLK;
            break;
        case 1:                             /* External oscillator          */
            SystemCoreClock = __SYS_OSC_CLK;
            break;
        case 2:                             /* System PLL Clock Out               */
            switch (HHD_SYSCON->SYSPLLCLKSEL & 0x03)
            {
                case 0:                       /* Internal RC oscillator             */
                    SystemCoreClock = __IRC_OSC_CLK * ((HHD_SYSCON->SYSPLLCTRL & 0x01F) + 1);
                    break;
                case 1:                       /* System oscillator                  */
                    SystemCoreClock = __SYS_OSC_CLK * ((HHD_SYSCON->SYSPLLCTRL & 0x01F) + 1);
                    break;
                case 2:                       /* Reserved                           */
                case 3:                       /* Reserved                           */
                    SystemCoreClock = 0;
                    break;
            }
            break;
        case 3:                             /* WDT Oscillator                     */
            SystemCoreClock = wdt_osc;
            break;
    }

    MainClock = SystemCoreClock;  /* Update MainClock */

    SystemCoreClock /= HHD_SYSCON->SYSAHBCLKDIV;  /* Update SystemCoreClock */
    if(((HHD_SYSCON->RCCCFGR >> 8) & 0x7) == 4)
        APB1Clock = SystemCoreClock / 2;
    else if(((HHD_SYSCON->RCCCFGR >> 8) & 0x7) == 5)
        APB1Clock = SystemCoreClock / 4;
    else if(((HHD_SYSCON->RCCCFGR >> 8) & 0x7) == 6)
        APB1Clock = SystemCoreClock / 8;
    else if(((HHD_SYSCON->RCCCFGR >> 8) & 0x7) == 7)
        APB1Clock = SystemCoreClock / 16;
    else
        APB1Clock = SystemCoreClock;

    if(((HHD_SYSCON->RCCCFGR >> 11) & 0x7) == 4)
        APB2Clock = SystemCoreClock / 2;
    else if(((HHD_SYSCON->RCCCFGR >> 11) & 0x7) == 5)
        APB2Clock = SystemCoreClock / 4;
    else if(((HHD_SYSCON->RCCCFGR >> 11) & 0x7) == 6)
        APB2Clock = SystemCoreClock / 8;
    else if(((HHD_SYSCON->RCCCFGR >> 11) & 0x7) == 7)
        APB2Clock = SystemCoreClock / 16;
    else
        APB2Clock = SystemCoreClock;

}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit (void)
{
	uint32_t i;
	
//  GT_AFIO->PIO0_30 = 1;
//  GT_GPIO0->OUT=0x0;
//  GT_GPIO0->DIR=0x78000000;
// #if (__DEBUG_RAM)       /* Memory Mapping Setup               */
//   GT_SYSCON->SYSMEMREMAP = 0x1;    /* remap to internal RAM */
// #else
//   GT_SYSCON->SYSMEMREMAP = 0x2;    /* remap to internal FLASH */
// #endif

#if 1
    /* First, below lines are for debugging only. For future release, WDT is
    enabled by bootrom, thus, unless a feed to WDT continuously, or WDT timeout
    will occur. If it's happen, WDT interrupt will be pending until a INT_CLEAR
    is applied. Below logic is to prevent system from going to the WDT interrupt
    during debugging.
    Second, all the peripheral clocks seem to be enabled by bootrom, it's
    not consistent with the UM. In below lines, only SYS, ROM, RAM, FLASHREG,
    FLASHARRAY, and TWS are enabled per UM dated July 14th. */
    HHD_WWDT->MOD  = 0x00;
    HHD_WWDT->FEED = 0xAA;		/* Feeding sequence */
    HHD_WWDT->FEED = 0x55;
    HHD_IWDT->MOD  = 0x00;
    HHD_IWDT->FEED = 0xAA;		/* Feeding sequence */
    HHD_IWDT->FEED = 0x55;

    NVIC->ICPR[0] |= 0xFFFFFFFF;

#endif

#if (CLOCK_SETUP)                                 /* Clock Setup              */

#if (MAINCLK_SETUP)                               /* System Clock Setup       */


#if (SYSOSC_SETUP)                                /* System Oscillator Setup  */
  /* bit 0 default is crystal bypass, 
  bit1 0=0~2.5Mhz crystal input, 1=2.5~16Mhz crystal input. */

    /* main system OSC run is cleared, bit 5 in PDRUNCFG register */
    HHD_SYSCON->PDRUNCFG     &= ~(1 << 8);          /* Power-up System Osc      */
    HHD_SYSCON->SYSOSCCTRL    = SYSOSCCTRL_Val;
    /* Wait 200us for OSC to be stablized, no status indication, dummy wait. */
    for (i = 0; i < 200; i++) __NOP();
#endif  // #if (SYSOSC_SETUP)



#if (SYSPLL_SETUP)
    HHD_SYSCON->SYSPLLCLKUEN  = 0x01;               /* Update Clock Source      */
    HHD_SYSCON->SYSPLLCLKSEL  = SYSPLLCLKSEL_Val;   /* Select PLL Input         */
    HHD_SYSCON->SYSPLLCLKUEN  = 0x00;               /* Toggle Update Register   */

    //  while (!(HHD_SYSCON->SYSPLLCLKUEN & 0x01));   /* Wait Until Updated       */

    /* System PLL Setup         */
    HHD_SYSCON->SYSPLLCTRL    = SYSPLLCTRL_Val;
    HHD_SYSCON->PDRUNCFG     &= ~(1 << 7);          /* Power-up SYSPLL          */
    for (i = 0; i < 200; i++) __NOP();
    //  while (!(HHD_SYSCON->SYSPLLSTAT & 0x01));	   /* Wait Until PLL Locked    */

#endif // #if (SYSPLL_SETUP)




    HHD_FMC->RDCYCCFG		  = 0x3;
    HHD_SYSCON->MAINCLKUEN    = 0x01;               /* Enable MCLK Source change*/
    HHD_SYSCON->MAINCLKSEL    = MAINCLKSEL_Val;     /* Select PLL Clock Output  */
    HHD_SYSCON->MAINCLKUEN    = 0x00;               /*Disable MCLK Source change*/

    HHD_SYSCON->SYSAHBCLKDIV  = SYSAHBCLKDIV_Val;
    HHD_SYSCON->UARTCLKDIV    = UARTCLKDIV_Val;
    //  while (!(HHD_SYSCON->MAINCLKUEN & 0x01));     /* Wait Until Updated       */


#endif  // #if (MAINCLK_SETUP)

#if (WDTOSC_SETUP)                               /* Watchdog Oscillator Setup*/
    HHD_SYSCON->WDTOSCCTRL    = WDTOSCCTRL_Val;
    HHD_SYSCON->PDRUNCFG     &= ~(1 << 6);          /* Power-up WDT Clock       */
#endif



#if (RTCCLK_SETUP)                               /* RTC clock Setup         */
    HHD_SYSCON->RTCCLKDIV     = RTCCLKDIV_Val;
    HHD_SYSCON->RTCOSCCTRL   &= RTCCLKSEL_Val;
#endif

#if (CLKOUTCLK_SETUP)
    HHD_SYSCON->CLKOUTCLKSEL = CLKOUTCLKSEL_Val;
    HHD_SYSCON->CLKOUTDIV    = CLKOUTCLKDIV_Val;
#endif

#endif  // #if (CLOCK_SETUP)

    /* System clock to the IOCON needs to be enabled or
    most of the I/O related peripherals won't work. */

    //HHD_SYSCON->SYSAHBCLKCTRL = 0xFFFFFFFF;
    HHD_SYSCON->SYSAPB2CLKCTRL = 0x1ff;				//Enable AFIO & GPIOA - GPIOG clock

    //Release PA8/PA9, these two IO pull-down by DAC1/DAC2.
#if 0
    HHD_SYSCON->SYSAPB1CLKCTRL |= 1 << 29;     //DAC CLK on.
    HHD_SYSCON->PDRUNCFG       &= ~(1 << 4);   //DAC analog power on.
    HHD_DAC->DAC1CTRL = 0x1048;
    HHD_DAC->DAC1BUF  = 0x1ff;
    HHD_DAC->DAC2CTRL = 0x1048;
    HHD_DAC->DAC2BUF  = 0x1ff;
#endif
	
    HHD_SYSCON->SYSAPB1CLKCTRL = 0xFFFFFFFF;
    HHD_SYSCON->SYSAPB1CLKCTRL = 0;
    HHD_SYSCON->SYSAHBCLKCTRL = 0xffffffff;
	

   
}

