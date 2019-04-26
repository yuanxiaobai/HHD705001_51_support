/**
  ******************************************************************************
  * @file    netconf.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11/20/2009
  * @brief   This file contains all the functions prototypes for the netconf.c 
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
#ifndef __NETCONF_H
#define __NETCONF_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
#define LCD_USER 0
#define UART_USER 0

#define MAXBIT_LEN		(1024*1)	

#define XVC_PACKAGE_LEN (10+MAXBIT_LEN)
#define XVC_PORT        (2542)	 
typedef struct xvcshift_package_struct
{
	int bitsLen;
	int totalRecvLen;
	int CurrentReceLen;
	int SendLen;
	int moreDataFlag;
	unsigned char pRecvBuff[XVC_PACKAGE_LEN];
	unsigned char pSenBuff[(XVC_PACKAGE_LEN)/2];
	void *context;
} XVC_SHIFT;



#ifdef __cplusplus
}
#endif

#endif /* __NETCONF_H */


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/

