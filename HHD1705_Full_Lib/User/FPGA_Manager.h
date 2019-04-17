/*******************************************************************************************************
  * Company: Hiwafer Technology Co., Ltd.
  ******************************************************************************************************
  * �ļ����ƣ�FPGA_Manager.h
  * ����˵����
  * ��    ����V1.0
  * ��    �ߣ�EnderWigg	
  * ��    �ڣ�2019.1.21

*******************************************************************************************************/

#ifndef __FPGA_MANAGER_H__
#define __FPGA_MANAGER_H__
#include "HHD32f1xx.h"
#include "hhd32f10x_conf.h"

#define MAX_PACKAGE_LEN		1280
#define SPI_PORT			2590

#define SPI_CMD_CLR		        0x33	//�������
#define SPI_CMD_SELECT_FPGA 	0x39	//ѡ��FPGA
#define SPI_CMD_SELECT_FLASH    0x3A	//ѡ��Flash
#define SPI_CMD_READ			0xCC	//������״̬
#define SPI_CMD_WRITE			0x1C	//д����״̬

#define FPGA_CLR_ADDR			0xFF	//��������Ĵ���
#define FPGA_SELECT_FPGA_ADDR	0xAA	//ѡ��FPGA�Ĵ���
#define FPGA_SELECT_FLASH       0xBB	////ѡ��Flash�Ĵ���
// ����״̬�Ĵ��� [0,3F]


typedef struct st_spi_cmd
{
	unsigned char cmd;
	unsigned char addr;
	unsigned char value;

}ST_SPI_CMD;


void FPGA_cmd_clean(void);
void FPGA_cmd_select_fpga(uint8_t fpga);
void FPGA_cmd_select_flash(uint8_t flash);
void FPGA_cmd_write(uint8_t addr, uint8_t data);
uint8_t FPGA_cmd_read(uint8_t addr);

#endif

