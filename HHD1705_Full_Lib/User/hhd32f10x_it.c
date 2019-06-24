/**
  ******************************************************************************
  * @file    hhd32f10x_it.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************/
 

/* Includes ------------------------------------------------------------------*/
#include "hhd32f10x_it.h"

#include "hhd32f1xx.h"
#include "HHD1705_lib.h"
#include "can_task.h"



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
extern void LwIP_Pkt_Handle(void);
//extern void tcp_led_control(Led_TypeDef Led);
extern void Time_Update(void);
extern struct rt_mailbox mb;

/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{}

/**
  * @brief  This function handles Hard Fault exception.

	* @retval None
  */


/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}
#include <netif/etharp.h>
#include "rtthread.h"
	#include "eth.h"
extern struct rt_stm32_eth stm32_eth_device;
/* interrupt service routine */
void ETH_IRQHandler(void)
{
    rt_uint32_t status, ier;

    /* enter interrupt */
    rt_interrupt_enter();

    status = HHD_ETH->DMASR;
    ier = HHD_ETH->DMAIER;

    if(status & ETH_DMA_IT_NIS)
    {
        rt_uint32_t nis_clear = ETH_DMA_IT_NIS;

        /* [6]:Receive Interrupt. */
        if((status & ier) & ETH_DMA_IT_R) /* packet reception */
        {
            //STM32_ETH_PRINTF("ETH_DMA_IT_R\r\n");
            /* a frame has been received */
            eth_device_ready(&(stm32_eth_device.parent));

            nis_clear |= ETH_DMA_IT_R;
        }

        /* [14]:Early Receive Interrupt. */

        ETH_DMAClearITPendingBit(nis_clear);
    }

       /* leave interrupt */
    rt_interrupt_leave();
}



/**----------------------------------------------------------------------------
** @Function:		   CAN1_IRQHandler               
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**

** @Date: 7-September-2017
**
-------------------------------------------------------------------------------*/



void CAN1_IRQHandler(void)
{
//	CanRxMsg RxMessage;
//	rt_uint32_t info;
	if(CAN1->IR.bit.RI == 0x01) //接收中断
	{
		
#ifdef CFG_USING_CAN1_WRITE_BACK
		int i;
		uint8_t can_buff[15] = {0};
		can_buff[0] = CAN1->DATAINFO.RxDATAINFO.RxFRAME.all;
		for(i = 0; i<12; i++)
		{
			can_buff[i+1] =  CAN1->DATAINFO.RxDATAINFO.RxDATA[i].all;
			
		}
		can_write_back(CAN1,  can_buff);
#endif	
	}
//////////////////////////////////////////////////////////////////////////////////////////	
// 在此处添加CAN 数据接收处理	
	
//	CAN_Receive(CAN1, 0, &RxMessage);
//	info=RxMessage.Data[1]<<8|RxMessage.Data[0];
//	info=(rt_uint32_t)&RxMessage;
//	rt_mb_send(&mb, info);
	
	
	can_entry(NULL);
	
	
	
	
/////////////////////////////////////////////////////////////////////////////////////////	
	CAN_SetCMD(CAN1, ReleaseRecBuf); // release recieve buffer

}


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
