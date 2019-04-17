/*****************************************************************************
 *   hhd_iap.h:  Header file for hhd32F1x Family Microprocessors
 *
 *   Copyright(C) 2015,  tech. Ltd.
 *   All rights reserved.
 *
 *   History
 *   2015  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "hhd32f1xx.h"
#include "hhd_sys.h"

#ifndef __IAP_H 
#define __IAP_H

#define	SECTORSIZE          0x200         //512 bytes sector size
#define	IAPENTRYVECTOR			0x1FFF00FC

//�����붨��
#define	SECTORERASE			    0x11		      //��������
#define	PROGFLASH			      0x15		      //RAMд��Flash
#define BSLVER			        0x31		      //��ϵͳ��Ϣ


//IAP RETURN CODE
#define CMD_SUCC		        0x00
#define INVALID_ADDR	      0x01
#define ERASE_FAILED	      0x02
#define PROG_FAILED		      0x03
#define NOT_BLANK		        0x04
#define INVALID_CMD		      0x05
#define INVALID_PWD		      0x06
#define IRC_NOT_POWERED		  0x07

void IAP_Flash_Erase(uint32_t addr);
void IAP_Flash_Program(uint32_t addr,uint32_t data);

#endif /* end __IAP_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
