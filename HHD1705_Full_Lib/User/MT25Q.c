/*********************************************************************************************
  * Company: Hiwafer Technology Co., Ltd.
  ********************************************************************************************
  * �ļ����ƣ�MT25Q.c
  * ����˵����MT25Q SPI Flash �����ӿ�
  * ��    ����V1.0
  * ��    �ߣ�EnderWigg	
  * ��    �ڣ�2019.3.3

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
*	�� Flash ID
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
*	дʹ��
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
* ��ֹд����
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
*	��ʼ�� Flash �ӿ�
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
	while(1)   // �ȴ�����Flash OK
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
*	�� Flash��ǰִ��״̬
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
*	��Flash�ж�����
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
		state = mt25q_read_status(READ_STATUS);   // ȷ�Ͽ��Խ��в���
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
*	����һ������
*	�ò������� ����һ���������в�����������СΪ 64KB
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
		state = mt25q_read_status(READ_STATUS);   // ȷ�Ͽ��Խ��в���
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
		state = mt25q_read_status(READ_FLAG_STATUS);   // ȷ�Ͽ��Խ��в���
		if(state & 0x80) 
		{
			break;
		}
		
		rt_thread_delay(5);
		continue;
	}
	
	return state & 0x20;    //�ɹ�����0��ʧ�ܷ��� 0x20
}
/***************************************************************************************
*
*	д 1 �� page ����
*	Flash ִ��һ�α��ָ�����ֻ��Я��һ��page���ȵ����ݣ�256Byte��
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
		state = mt25q_read_status(READ_STATUS);   // ȷ�Ͽ��Խ��в���
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
		state = mt25q_read_status(READ_STATUS);   // ȷ�Ͽ��Խ��в���
		if(state & 0x1)
		{
			continue;
		}
		state = mt25q_read_status(READ_FLAG_STATUS);   // ȷ�Ͽ��Խ��в���
		if(state & 0x80) 
		{
			break;
		}
		continue;
	}
	
	return state & 0x10;    //�ɹ�����0��ʧ�ܷ��� 0x10
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                      MIDDLE LEVEL API                                   //
/////////////////////////////////////////////////////////////////////////////////////////////
/***************************************************************************************
*
*	д���ݵ�Flash
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
*	�����������
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






