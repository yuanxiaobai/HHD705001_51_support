/*****************************************************************************
 *   hhd32f10x_conf.h:  Header file for Gorgetek G32F1xx
 *
 *   Copyright(C) 2015, Gorge Technology
 *   All rights reserved.
 *
 *   History
 *   2015.01.21  ver 1.0    Prelimnary version
 *
******************************************************************************/
/* Includes ------------------------------------------------------------------*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_CONF_H
#define __STM32F10x_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Uncomment the line below to enable peripheral header file inclusion */
#include "hhd_adc.h" 
#include "hhd_uart.h" 
#include "hhd_spi.h" 
#include "hhd_iic.h" 
#include "hhd_sys.h" 
#include "hhd_gpio.h" 
#include "hhd_dac.h" 
#include "hhd_wdt.h" 
#include "hhd_crc.h" 
#include "hhd_eth.h"
#include "hhd_rcc.h"
#include "hhd_can.h"


////////////////////////////////////////SysTick////////////////////////////////////////////////////
#define SYSTEMTICK_PERIOD_MS  10

////////////////////////////////////////NETWORK////////////////////////////////////////////////////

#define ETH_TIMEOUT		  1000






//////////////////////////////////////////CAN///////////////////////////////////////////////////////





/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *   which reports the name of the source file and the source
  *   line number of the call that failed. 
  *   If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */
	
  
  uint32_t Get_Tick(void);
//  void Delay(uint32_t nCount);
  
#endif
