/**
  ******************************************************************************
  * @file    hhd32f107.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11/20/2009
  * @brief   This file contains all the functions prototypes for the G32F107 
  *          file.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HHD32F107_H
#define __HHD32F107_H

#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "hhd32f1xx.h"
	 
extern uint32_t rcc_apb1_peripheral[] ;

typedef enum net_path
{
	EN_TO_SWITCH = 0,
	EN_TO_MDI

}EN_NET_PATH;

void System_Setup(void);
//void Ethernet_Configuration(void);
//void Ethernet_Configuration(EN_NET_PATH path);
void Ethernet_Configuration(EN_NET_PATH path);
void apb1_peripheral_clock( FunctionalState NewState);
void Delay_1ms(uint32_t nCount);

#ifdef __cplusplus
}
#endif

#endif /* __HHD32F10F107_H */


/***********END OF FILE****/
