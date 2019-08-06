/*******************************************************************************************************
  * Company: Hiwafer Technology Co., Ltd.
  ******************************************************************************************************
  * 文件名称：can_task.h
  * 功能说明：
  * 版    本：V1.0
  * 作    者：EnderWigg	
  * 日    期：2019.6.14

*******************************************************************************************************/
#ifndef __CAN_TASK_H__
#define __CAN_TASK_H__

#include <rtthread.h>

#define RECV_BUFF_NUM  20

typedef struct st_frameHeaderbit
{
	uint32_t type				:3;
	uint32_t direction			:2;
	uint32_t dest				:7;
	uint32_t reseve0			:1;
	uint32_t src				:7;
	uint32_t reseve1			:1;
	uint32_t msgID				:8;

}ST_FRAMEHEADER;

typedef union un_frameHeader
{
	uint32_t all;
	ST_FRAMEHEADER bit; 

}UN_FRAMEHEADER;

void can_rx_ind(void);
void can_entry(void *arg);
void can_task_init(void);
void spi_irq(void);

#endif
