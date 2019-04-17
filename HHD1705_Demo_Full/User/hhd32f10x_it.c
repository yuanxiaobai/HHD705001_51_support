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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
extern void LwIP_Pkt_Handle(void);
//extern void tcp_led_control(Led_TypeDef Led);
extern void Time_Update(void);

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
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
	//int i;

  while (1)
  {
//		i--;
	}
}

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

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  /* Update the LocalTime by adding SYSTEMTICK_PERIOD_MS each SysTick interrupt */
  Time_Update();
}



/**
  * @brief  This function handles ETH interrupt request.
  * @param  None
  * @retval None
  */
void ETH_IRQHandler(void)
{
  /* Handles all the received frames */
  while(ETH_GetRxPktSize() != 0) 
  {		
    LwIP_Pkt_Handle();
  }

  /* Clear the Eth DMA Rx IT pending bits */
  ETH_DMAClearITPendingBit(ETH_DMA_IT_R);
  ETH_DMAClearITPendingBit(ETH_DMA_IT_NIS);
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
	
	
	
/////////////////////////////////////////////////////////////////////////////////////////	
	CAN_SetCMD(CAN1, ReleaseRecBuf); // release recieve buffer

}


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
