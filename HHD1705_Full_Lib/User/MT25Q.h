/*****************************************************************************************
*																				
*
*	MTQ25 SPI Flash 
*
*
*
*
*******************************************************************************************/

#ifndef __MT25Q_H__
#define __MT25Q_H__
#include <stdint.h>

#define ERSET_ENABLE	0x66
#define RESET_MEMORY	0x99
#define READ_ID			0x9E
#define BYTE_4_READ		0x13
#define BYTE_3_READ		0x03
#define WRITE_ENABLE	0x06
#define WRITE_DISABLE	0x04
#define READ_STATUS     0x05
#define READ_FLAG_STATUS 0x70
#define PROGRAM_PAGE	0x12
#define ERASE_64K_SECTOR	0xDC
#define ENABLE_4BYTE_MODE	0xB7
#define DISABLE_4BYTE_MODE	0xE9

#define PAGE_SIZE	0x100
#define SECTOR_SIZE	0x10000

#define ERASE_ERR	0x20
#define PROGRAM_ERR 0x10

#define MT25Q_ID	0x0020BB21
#define SECTOR_TO_ADDR(n) ((n)*0x10000)


void mt25q_init(void);
uint32_t mt25q_read_id(void);
int mt25q_erase(uint32_t addr);
uint32_t mt25q_read(uint32_t addr, uint8_t *buff, uint32_t len );
int mt25q_wirte(uint32_t addr, uint8_t *data, int len);

void Flash_erase(uint32_t addr, uint32_t len);




#endif

