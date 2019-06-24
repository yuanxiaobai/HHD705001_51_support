/*********************************************************************************************
  * Company: Hiwafer Technology Co., Ltd.
  ********************************************************************************************
  * 文件名称：MT25Q.c
  * 功能说明：MT25Q SPI Flash 驱动接口
  * 版    本：V1.0
  * 作    者：EnderWigg	
  * 日    期：2019.3.3

**********************************************************************************************/

#include <string.h>
#include "hhd32f107.h"
#include "hhd32f10x_conf.h"
#include "simulator_spi.h"
#include "MT25Q.h"
#include "rtthread.h"


/////////////////////////////////////////////////////////////////////////////////////////////
//                                      LOW LEVEL API                                      //
/////////////////////////////////////////////////////////////////////////////////////////////

/*********************************************************************************************
*
*	读 Flash ID
*
*
*********************************************************************************************/
uint32_t mt25q_read_id(void)
{
	uint32_t id = 0;
	SPI4_CS = 0;
	readWriteByte(READ_ID);
	
	id |= readWriteByte(0xFF) << 16;
	id |= readWriteByte(0xFF) << 8;
	id |= readWriteByte(0xFF);
	SPI4_CS = 1;
	return id;
}

/*********************************************************************************************
*
*	写使能
*
*
*********************************************************************************************/
void mt25q_enable_write(void)
{
	SPI4_CS = 0;
	WriteByte(WRITE_ENABLE);
	SPI4_CS = 1;
}
/*********************************************************************************************
*
* 禁止写操作
*
*********************************************************************************************/
void mt25q_disable_write(void)
{
	SPI4_CS = 0;
	WriteByte(WRITE_DISABLE);
	SPI4_CS = 1;
}

/*********************************************************************************************
*
*	初始化 Flash 接口
*
*
*********************************************************************************************/
uint32_t mt25q_id = 0;
void mt25q_init(void)
{
//	uint32_t mt25q_id = 0;
	
	mt25q_enable_write();
	
	SPI4_CS = 0;
	WriteByte(ERSET_ENABLE);
	SPI4_CS = 1;
	
	SPI4_CS = 0;
	WriteByte(RESET_MEMORY);
	SPI4_CS = 1;
	
	SPI4_CS = 0;
	WriteByte(ENABLE_4BYTE_MODE);
	SPI4_CS = 1;
	
	mt25q_disable_write();
	
	rt_thread_delay(50);
	while(1)   // 等待访问Flash OK
	{
		mt25q_id = mt25q_read_id();
		if(mt25q_id == MT25Q_ID)
		{
			break;
		}
		
		rt_thread_delay(50);	
	}
}

/*************************************************************************************************
*
*	读 Flash当前执行状态
*
*
*************************************************************************************************/
uint8_t mt25q_read_status(uint8_t cmd)
{
	uint8_t state = 0;
	SPI4_CS = 0;
	readWriteByte(cmd);
	
	state = readWriteByte(0xFF) ;
	
	SPI4_CS = 1;
	
	return state;
}

/***************************************************************************************
*
*	从Flash中读数据
*	
*
***************************************************************************************/
uint32_t mt25q_read(uint32_t addr, uint8_t *buff, uint32_t len )
{
	int i = 0;
	uint8_t state = 0;
	uint8_t cmd[5] = {0}; 
	
	cmd[0] = BYTE_4_READ;
	
	cmd[1] = (addr >> 24 ) & 0xFF;
	cmd[2] = (addr >> 16 ) & 0xFF;
	cmd[3] = (addr >> 8  ) & 0xFF;
	cmd[4] = (addr >> 0  ) & 0xFF;
	
	
	while(1)
	{
		state = mt25q_read_status(READ_STATUS);   // 确认可以进行操作
		if(state & 0x01)
		{
			continue;
		}
		else
		{
			break;
		}
	}
	
	SPI4_CS = 0;
	
	for(i = 0; i < 5; i++)
	{
		WriteByte(cmd[i]);
	}

	for(i = 0; i < len; i++)
	{
		buff[i] = readByte();
	}
	
	SPI4_CS = 1;

	return len;
}

/***************************************************************************************
*
*	擦出一个扇区
*	该擦除方法 是以一个扇区进行擦出，扇区大小为 64KB
*
***************************************************************************************/
int mt25q_erase(uint32_t addr)
{
	uint8_t state = 0;
	uint8_t i = 0;
	uint8_t cmd [5] = {0};

	cmd[0] = ERASE_64K_SECTOR;
	
	cmd[1] = (addr >> 24 ) & 0xFF;
	cmd[2] = (addr >> 16 ) & 0xFF;
	cmd[3] = (addr >> 8  ) & 0xFF;
	cmd[4] = (addr >> 0  ) & 0xFF;
	
	while(1)
	{
		state = mt25q_read_status(READ_STATUS);   // 确认可以进行操作
		if(state & 0x01)
		{
			rt_thread_delay(5);
			continue;
		}
		else
		{
			break;
		}
	}
	
	mt25q_enable_write();
	
	SPI4_CS = 0;
	for(i = 0; i < 5; i++)
	{
		WriteByte(cmd[i]);
	}
	SPI4_CS = 1;
	mt25q_disable_write();
		
	while(1)
	{
		state = mt25q_read_status(READ_FLAG_STATUS);   // 确认可以进行操作
		if(state & 0x80) 
		{
			break;
		}
		
		rt_thread_delay(5);
		continue;
	}
	
	return state & 0x20;    //成功返回0，失败返回 0x20
}
/***************************************************************************************
*
*	写 1 个 page 数据
*	Flash 执行一次编程指令最多只能携带一个page长度的数据（256Byte）
*
***************************************************************************************/
int mt25q_wirte_page(uint32_t addr, uint8_t *data, uint16_t len)
{
	uint8_t state = 0;
	uint16_t i = 0;
	uint8_t cmd [5] = {0};

	cmd[0] = PROGRAM_PAGE;
	
	cmd[1] = (addr >> 24 ) & 0xFF;
	cmd[2] = (addr >> 16 ) & 0xFF;
	cmd[3] = (addr >> 8  ) & 0xFF;
	cmd[4] = (addr >> 0  ) & 0xFF;
	while(1)
	{
		state = mt25q_read_status(READ_STATUS);   // 确认可以进行操作
		if(state & 0x01)
		{
			continue;
		}
		else
		{
			break;
		}
	}
	mt25q_enable_write();
	
	SPI4_CS = 0;
	for(i = 0; i < 5; i++)
	{
		WriteByte(cmd[i]);
	}
	for(i = 0; i < len; i++)
	{
		WriteByte(data[i]);
	}
	SPI4_CS = 1;
	
	mt25q_disable_write();	
	while(1)
	{
		state = mt25q_read_status(READ_STATUS);   // 确认可以进行操作
		if(state & 0x1)
		{
			continue;
		}
		state = mt25q_read_status(READ_FLAG_STATUS);   // 确认可以进行操作
		if(state & 0x80) 
		{
			break;
		}
		continue;
	}
	
	return state & 0x10;    //成功返回0，失败返回 0x10
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                      MIDDLE LEVEL API                                   //
/////////////////////////////////////////////////////////////////////////////////////////////
/***************************************************************************************
*
*	写数据到Flash
*
*
***************************************************************************************/
int mt25q_wirte(uint32_t addr, uint8_t *data, int len)
{
	int i = 0;
	int ret  = 0;
	int page_num = len / PAGE_SIZE;
	int last_len = len % PAGE_SIZE;
	
	for(i = 0; i < page_num; i++)
	{
		ret = mt25q_wirte_page((addr + (i * PAGE_SIZE)), data + (i * PAGE_SIZE), PAGE_SIZE);
		if(ret == PROGRAM_ERR)
		{
			return ret;
		}
	}
	
	if(last_len)
	{
		ret = mt25q_wirte_page((addr + (i * PAGE_SIZE)), data + (i * PAGE_SIZE), last_len);
		if(ret == PROGRAM_ERR)
		{
			return ret;
		}
	}
	
	return len;
}

/***************************************************************************************
*
*	擦出多个扇区
*
*
***************************************************************************************/
void Flash_erase(uint32_t addr, uint32_t len)
{
	uint32_t i = 0;
	uint32_t start_sector = addr / SECTOR_SIZE;
	uint32_t sector_num = len / SECTOR_SIZE;
	if( addr % SECTOR_SIZE)
	{
		start_sector = start_sector -1;
		sector_num++;
	}
	
	if(len % SECTOR_SIZE)
	{
		sector_num++;
	}
	
	for(i = 0; i <= sector_num; i++)
	{
		mt25q_erase(SECTOR_TO_ADDR(start_sector+i));
	}
}






