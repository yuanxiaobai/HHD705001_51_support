/*******************************************************************************************************
  * Company: Hiwafer Technology Co., Ltd.
  ******************************************************************************************************
  * 文件名称：can_task.c
  * 功能说明：
  * 版    本：V1.0
  * 作    者：EnderWigg	
  * 日    期：2019.6.14

*******************************************************************************************************/
#include "HHD1705_lib.h"
#include "rtthread.h" 
#include "can_task.h"
#include "simulator_spi.h"

rt_sem_t sem_spi;
rt_mailbox_t mb_can;
CanRxMsg* RxMessage;

/**
 * @brief  can 接收中断处理

 * @param void
 * @return void 
 * @details 
 */
void can_entry(void *arg)
{
	static int count = 0;
	
	(void)(arg);
//	
//	while(rt_sem_take(sem_can, RT_WAITING_FOREVER))
	{	
		if(RT_EOK == rt_mb_control(mb_can, RT_IPC_CMD_FULL, NULL))
		{
			if(count >= RECV_BUFF_NUM)
			{
				count = 0;
			}
			
			CAN_Receive(CAN1, 0, RxMessage+count);
			
			rt_mb_send(mb_can, (rt_uint32_t)(RxMessage+count));
			count++;
		}
	}
}

/**
 * @brief  SPI 接收中断响应

 * @param void
 * @return void 
 * @details 
 */
void spi_irq(void)
{
	uint32_t stat = SYSCON->EXTISTAT.all;
	GPIO_ClrIntflag(SPI4_INT_PORT, SPI4_INT_PIN);	
	rt_sem_release(sem_spi);
}


/**
 * @brief  SPI 接收中断处理

 * @param void
 * @return void 
 * @details 
 */
void spi_user_entry(void *arg)
{
	uint8_t irq = 0;
	rt_err_t result;
	(void)(arg);
//	
	while(1)
	{	
		
		result = rt_sem_take(sem_spi, RT_WAITING_FOREVER);
		if(result == RT_EOK)
		{
		
			SPI_To_FPGA_Read(CHECK_FPGA_NUM, IRQ_FPGA_ADDR, &irq, 1);
			
			switch(irq)
			{
				/* 在此处添加处理不同中断类型的代码*/		
		
//////////////////////////////////////////////////////////////////////////////			
			}

		}
	}
}

/**
 * @brief  can 任务实体

 * @param arg 
 * @return void 
 * @details 处理接收到的CAN数据
*/
void can_user_entry(void *arg)
{
	CanRxMsg* lp_RxMessage;
	CanTxMsg TxMessage;

	while(1)
	{
		if(rt_mb_recv(mb_can, (rt_uint32_t *)&lp_RxMessage, RT_WAITING_FOREVER) == RT_EOK)
		{
			
//			lp_RxMessage = (CanRxMsg *)mb_pointer;
			
			TxMessage.DLC   = lp_RxMessage->DLC;
			TxMessage.ExtId = lp_RxMessage->ExtId;
			TxMessage.IDE   = lp_RxMessage->IDE;
			TxMessage.RTR   = lp_RxMessage->RTR;
			TxMessage.StdId = 0;
			
			rt_memcpy(TxMessage.Data, lp_RxMessage->Data, lp_RxMessage->DLC);
			
			CAN_Transmit(CAN1, &TxMessage);
				
		}
		}
}
	
/**
     * @brief  can 任务初始化
    
     * @param arg 
     * @return void 
* @details 创建CAN任务并
*/
    	
void can_task_init(void)
{
	rt_thread_t can_user_id = NULL; 
	rt_thread_t spi_user_id = NULL; 
	UN_FRAMEHEADER id;
	UN_FRAMEHEADER mask;
	
	id.all = 0;
	mask.all = 0xFFFFFFFF;
	mb_can = rt_mb_create ("m_can", RECV_BUFF_NUM, RT_IPC_FLAG_FIFO);
	RxMessage = rt_malloc(RECV_BUFF_NUM*sizeof(CanRxMsg));
	if(RxMessage == NULL)
	{
		rt_mb_delete(mb_can);
	}
	
	sem_spi = rt_sem_create("sem_spi", 0, RT_IPC_FLAG_FIFO);
	if(sem_spi == NULL)
	{
		 rt_sem_delete(sem_spi);
	}
	
	// 创建SPI 任务
	spi_user_id = rt_thread_create("spi_user_task", spi_user_entry, RT_NULL, 1024, 20, 20);
// 启动SPI任务	
	if(spi_user_id != NULL)
	{
		rt_thread_startup(spi_user_id);
	}
	
// 创建CAN 任务
	can_user_id = rt_thread_create("can_user_task", can_user_entry, RT_NULL, 1024, 14, 20);
// 启动CAN任务	
	if(can_user_id != NULL)
	{
		rt_thread_startup(can_user_id);
	}
	
#ifdef CFG_USING_CAN1	
	
	id.bit.dest = Mark & 0x7F;
	mask.bit.dest = 0;
	
	can_init(CAN1, CAN_BAUD_500K, CAN_Id_Extended, id.all, mask.all);
	
	GPIO_ConfigPinsAsInput(SPI4_INT_PORT,SPI4_INT_PIN);
	GPIO_EnableInt(SPI4_INT_PORT,SPI4_INT_PIN, FALL_EDGE); 


	
#endif

}
	
