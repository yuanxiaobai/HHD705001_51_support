#ifndef __ETH_H__
#define __ETH_H__
#include <rtthread.h>
#include <netif/ethernetif.h>
#include "hhd_eth.h"

#define ETH_RXBUFNB        			6
#define ETH_TXBUFNB        			4

#define MAX_ADDR_LEN				6
#define ETH_DMARxDesc_FrameLengthShift           16

struct rt_stm32_eth
{
	/* inherit from ethernet device */
	struct eth_device parent;

	/* interface address info. */
	rt_uint8_t  dev_addr[MAX_ADDR_LEN];			/* hw address	*/

	uint32_t    ETH_Speed; /*!< @ref ETH_Speed */
	uint32_t    ETH_Mode;  /*!< @ref ETH_Duplex_Mode */

	uint32_t ETH_HashTableHigh;
	uint32_t ETH_HashTableLow;
};

void Delay_1ms(unsigned int nCount);
void IRQHandler(void);

#endif
