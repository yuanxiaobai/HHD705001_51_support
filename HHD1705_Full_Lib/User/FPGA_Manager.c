/*******************************************************************************************************
  * Company: Hiwafer Technology Co., Ltd.
  ******************************************************************************************************
  * �ļ����ƣ�FPGA_Manager.c
  * ����˵����
  * ��    ����V1.0
  * ��    �ߣ�EnderWigg	
  * ��    �ڣ�2019.1.21

*******************************************************************************************************/

#include <string.h>
#include "spi.h"
#include "FPGA_Manager.h"
#include "simulator_spi.h"
#include "HHD1705_lib.h"



uint8_t FPGA_send_cmd(ST_SPI_CMD *cmd)
{
	uint8_t temp;
	SPI4_CS = 0;
	
	WriteByte(cmd->cmd);
	WriteByte(cmd->addr);	
	temp = readWriteByte(cmd->value);
		
	SPI4_CS = 1;
	
	return temp;
}

void FPGA_cmd_clean(void)
{
	ST_SPI_CMD cmd = 
	{
		SPI_CMD_CLR,
		FPGA_CLR_ADDR,
		0
	};
	
	 FPGA_send_cmd(&cmd);
}


void FPGA_cmd_select_fpga(uint8_t fpga)
{
	ST_SPI_CMD cmd = 
	{
		SPI_CMD_SELECT_FPGA,
		FPGA_SELECT_FPGA_ADDR,
		fpga
	};
	
	 FPGA_send_cmd(&cmd);
}


void FPGA_cmd_select_flash(uint8_t flash)
{
	ST_SPI_CMD cmd = 
	{
		SPI_CMD_SELECT_FLASH,
		FPGA_SELECT_FLASH,
		flash
	};
	
	 FPGA_send_cmd(&cmd);
}

void FPGA_cmd_write(uint8_t addr, uint8_t data)
{
	ST_SPI_CMD cmd = 
	{
		SPI_CMD_WRITE,
		addr,
		data
	};
	
	 FPGA_send_cmd(&cmd);

}


uint8_t FPGA_cmd_read(uint8_t addr)
{
	uint8_t temp = 0;
	ST_SPI_CMD cmd = 
	{
		SPI_CMD_READ,
		addr,
		0
	};
	SPI4_CS = 0;
	temp = FPGA_send_cmd(&cmd);
	SPI4_CS = 1;
	
	
	return temp;
}


/******************************************************************************
*
*	����д���ݵ�FPGA
* 
***********************************************************************/
int SPI_To_FPGA_Wirte(uint8_t fpga, uint8_t addr, uint8_t *data, int len)
{
	int i = 0;
	FPGA_cmd_clean();
	FPGA_cmd_select_fpga(fpga);
	
	for(i = 0; i < len; i++)
	{
		FPGA_cmd_write(addr+i, data[i]);
	}
	
	return len;
}

/***********************************************************************
*
*	������FPGA������
* 
*
*
***********************************************************************/
int SPI_To_FPGA_Read(uint8_t fpga, uint8_t addr, uint8_t *data, int len)
{
	int i = 0;
	
	FPGA_cmd_clean();
	FPGA_cmd_select_fpga(fpga);
	
	for(i = 0; i < len; i++)
	{
		data[i] = FPGA_cmd_read(addr+i);
	}
	
	return len;
}

