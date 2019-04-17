/*******************************************************************************************************
  * Company: Hiwafer Technology Co., Ltd.
  ******************************************************************************************************
  * 文件名称：FPGA_Manager.c
  * 功能说明：
  * 版    本：V1.0
  * 作    者：EnderWigg	
  * 日    期：2019.1.21

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
*	连续写数据到FPGA
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
*	连续从FPGA读数据
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

