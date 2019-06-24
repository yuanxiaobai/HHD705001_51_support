/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
/*
 * STM32 Eth Driver for RT-Thread
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-05     Bernard      eth interface driver for STM32F107 CL
 */
#include <rtthread.h>
#include <stdlib.h>
#include <netif/etharp.h>
#include <lwip/icmp.h>
#include "lwipopts.h"

#include "eth.h"
#include "hhd32f107.h"
#include "hhd32f10x_conf.h"




#ifdef ETH_DEBUG
#define STM32_ETH_PRINTF          rt_kprintf
#else
#define STM32_ETH_PRINTF(...)
#endif


static ETH_DMADESCTypeDef  DMARxDscrTab[ETH_RXBUFNB], DMATxDscrTab[ETH_TXBUFNB];
static rt_uint8_t Rx_Buff[ETH_RXBUFNB][ETH_MAX_PACKET_SIZE], Tx_Buff[ETH_TXBUFNB][ETH_MAX_PACKET_SIZE];



struct rt_stm32_eth stm32_eth_device;
static struct rt_semaphore tx_wait;
//static rt_bool_t tx_is_waiting = RT_FALSE;

extern ETH_DMADESCTypeDef  *DMATxDescToSet;
extern ETH_DMADESCTypeDef  *DMARxDescToGet;




/*******************************************************************************
* Function Name  : ETH_RxPkt_ChainMode
* Description    : Receives a packet.
* Input          : None
* Output         : None
* Return         : frame: farme size and location
*******************************************************************************/
FrameTypeDef ETH_RxPkt_ChainMode(void)
{ 
  u32 framelength = 0;
  FrameTypeDef frame = {0,0}; 

  /* Check if the descriptor is owned by the ETHERNET DMA (when set) or CPU (when reset) */
  if((DMARxDescToGet->Status & ETH_DMARxDesc_OWN) != (u32)RESET)
  {	
	frame.length = 0;

    if ((HHD_ETH->DMASR & ETH_DMASR_RBUS) != (u32)RESET)  
    {
      /* Clear RBUS ETHERNET DMA flag */
      HHD_ETH->DMASR = ETH_DMASR_RBUS;
      /* Resume DMA reception */
      HHD_ETH->DMARPDR = 0;
    }

	/* Return error: OWN bit set */
    return frame; 
  }
  
  if(((DMARxDescToGet->Status & ETH_DMARxDesc_ES) == (u32)RESET) && 
     ((DMARxDescToGet->Status & ETH_DMARxDesc_LS) != (u32)RESET) &&  
     ((DMARxDescToGet->Status & ETH_DMARxDesc_FS) != (u32)RESET))  
  {      
    /* Get the Frame Length of the received packet: substruct 4 bytes of the CRC */
    framelength = ((DMARxDescToGet->Status & ETH_DMARxDesc_FL) >> ETH_DMARxDesc_FrameLengthShift) - 4;
	
	/* Get the addrees of the actual buffer */
	frame.buffer = DMARxDescToGet->Buffer1Addr;	
  }
  else
  {
    /* Return ERROR */
    framelength = RT_ERROR;
  }

  frame.length = framelength;


  frame.descriptor = DMARxDescToGet;
  
  /* Update the ETHERNET DMA global Rx descriptor with next Rx decriptor */      
  /* Chained Mode */    
  /* Selects the next DMA Rx descriptor list for next buffer to read */ 
  DMARxDescToGet = (ETH_DMADESCTypeDef*) (DMARxDescToGet->Buffer2NextDescAddr);    
  
  /* Return Frame */
  return (frame);  
}

/*******************************************************************************
* Function Name  : ETH_TxPkt_ChainMode
* Description    : Transmits a packet, from application buffer, pointed by ppkt.
* Input          : - FrameLength: Tx Packet size.
* Output         : None
* Return         : ETH_ERROR: in case of Tx desc owned by DMA
*                  ETH_SUCCESS: for correct transmission
*******************************************************************************/
u32 ETH_TxPkt_ChainMode(u16 FrameLength)
{   
	//u32 i=0;
  /* Check if the descriptor is owned by the ETHERNET DMA (when set) or CPU (when reset) */
  if((DMATxDescToSet->Status & ETH_DMATxDesc_OWN) != (u32)RESET)
  {  
	/* Return ERROR: OWN bit set */
    return RT_ERROR;
  }
        
  /* Setting the Frame Length: bits[12:0] */
  DMATxDescToSet->ControlBufferSize = (FrameLength & ETH_DMATxDesc_TBS1);   //

  /* Setting the last segment and first segment bits (in this case a frame is transmitted in one descriptor) */    
  DMATxDescToSet->ControlBufferSize |= ETH_DMATxDesc_LS | ETH_DMATxDesc_FS;
	DMATxDescToSet->ControlBufferSize |= ETH_DMATxDesc_TCH;  // /*!< Second Address Chained 和ST不一样 

  /* Set Own bit of the Tx descriptor Status: gives the buffer back to ETHERNET DMA */
  DMATxDescToSet->Status |= ETH_DMATxDesc_OWN;
  /* When Tx Buffer unavailable flag is set: clear it and resume transmission */
  if ((HHD_ETH->DMASR & ETH_DMASR_TBUS) != (u32)RESET)
  {
    /* Clear TBUS ETHERNET DMA flag */
    HHD_ETH->DMASR = ETH_DMASR_TBUS;
    /* Resume DMA transmission*/
    HHD_ETH->DMATPDR = 0;
  }
  /* Update the ETHERNET DMA global Tx descriptor with next Tx decriptor */  
  /* Chained Mode */
  /* Selects the next DMA Tx descriptor list for next buffer to send */ 
 if((DMATxDescToSet->ControlBufferSize & ETH_DMATxDesc_TCH) != (uint32_t)RESET)
 {
   DMATxDescToSet = (ETH_DMADESCTypeDef*) (DMATxDescToSet->Buffer2NextDescAddr); 
 }
  return RT_EOK;   
}



/*******************************************************************************
* Function Name  : ETH_GetCurrentTxBuffer
* Description    : Return the address of the buffer pointed by the current descritor.
* Input          : None
* Output         : None
* Return         : Buffer address
*******************************************************************************/
u32 ETH_GetCurrentTxBuffer(void)
{ 
  /* Return Buffer address */
  return (DMATxDescToSet->Buffer1Addr);   
}

///* interrupt service routine */
//void IRQHandler(void)
//{
//    rt_uint32_t status, ier;

//    /* enter interrupt */
//    rt_interrupt_enter();

//    status = HHD_ETH->DMASR;
//    ier = HHD_ETH->DMAIER;

//    if(status & ETH_DMA_IT_NIS)
//    {
//        rt_uint32_t nis_clear = ETH_DMA_IT_NIS;

//        /* [6]:Receive Interrupt. */
//        if((status & ier) & ETH_DMA_IT_R) /* packet reception */
//        {
//            //STM32_ETH_PRINTF("ETH_DMA_IT_R\r\n");
//            /* a frame has been received */
//            eth_device_ready(&(stm32_eth_device.parent));

//            nis_clear |= ETH_DMA_IT_R;
//        }

//        /* [14]:Early Receive Interrupt. */

//        ETH_DMAClearITPendingBit(nis_clear);
//    }

//       /* leave interrupt */
//    rt_interrupt_leave();
//}



uint16_t get_phy_addr(void)
{
	uint16_t i = 0;   
	rt_uint16_t temp;

	for(i=0; i<=0x1F; i++)
	{
		temp = ETH_ReadPHYRegister(i, 0x02);

		if( temp != 0xFFFF )
		{
			return i;

		}
	}
	
	return 0x20;

}

/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
void low_level_init(void)
{
 
  /* Initialize Tx Descriptors list: Chain Mode */
  ETH_DMATxDescChainInit(DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);
  /* Initialize Rx Descriptors list: Chain Mode  */
  ETH_DMARxDescChainInit(DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFNB);

  /* Enable Ethernet Rx interrrupt */
  { int i;
    for(i=0; i<ETH_RXBUFNB; i++)
    {
      ETH_DMARxDescReceiveITConfig(&DMARxDscrTab[i], ENABLE);
    }
  }

#ifdef CHECKSUM_BY_HARDWARE
  /* Enable the checksum insertion for the Tx frames */
  { int i;
    for(i=0; i<ETH_TXBUFNB; i++)
    {
      ETH_DMATxDescChecksumInsertionConfig(&DMATxDscrTab[i], ETH_DMATxDesc_ChecksumTCPUDPICMPFull);
    }
  }
#endif
	
  /* Enable MAC and DMA transmission and reception */
  ETH_Start();

}



/* initialize the interface */
static rt_err_t rt_stm32_eth_init(rt_device_t dev)
{

    struct rt_stm32_eth * stm32_eth = (struct rt_stm32_eth *)dev;
 
	
	ETH_MACAddressConfig(ETH_MAC_Address0, (u8*)&stm32_eth->dev_addr[0]);
	low_level_init();
		
    return RT_EOK;
}

static rt_err_t rt_stm32_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_stm32_eth_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t rt_stm32_eth_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_size_t rt_stm32_eth_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_err_t rt_stm32_eth_control(rt_device_t dev, int cmd, void *args)
{
	switch(cmd)
	{
	case NIOCTL_GADDR:
		/* get mac address */
		if(args) rt_memcpy(args, stm32_eth_device.dev_addr, 6);
		else return -RT_ERROR;
		break;

	default :
		break;
	}

	return RT_EOK;
}

/* ethernet device interface */
/* transmit packet. */
rt_err_t rt_stm32_eth_tx( rt_device_t dev, struct pbuf* p)
{
    struct pbuf* q;

    rt_uint32_t offset = 0;
 
	uint8_t *buffer =  (rt_uint8_t*)ETH_GetCurrentTxBuffer();

	for(q = p; q != NULL; q = q->next) 
	{
		memcpy((rt_uint8_t*)&buffer[offset], q->payload, q->len);

		offset = offset + q->len;
	}
	
#ifdef ETH_TX_DUMP
    {
        rt_uint32_t i;
        rt_uint8_t *ptr = buffer;

        STM32_ETH_PRINTF("tx_dump, len:%d\r\n", p->tot_len);
        for(i=0; i<p->tot_len; i++)
        {
            STM32_ETH_PRINTF("%02x ",buffer[i]);
            

            if(((i+1)%8) == 0)
            {
                STM32_ETH_PRINTF("  ");
            }
            if(((i+1)%16) == 0)
            {
                STM32_ETH_PRINTF("\r\n");
            }
        }
        STM32_ETH_PRINTF("\r\ndump done!\r\n");
    }
#endif
	
	ETH_TxPkt_ChainMode(offset);
	 
#ifdef CHECKSUM_BY_HARDWARE
    DMATxDescToSet->Status |= ETH_DMATxDesc_ChecksumTCPUDPICMPFull;
    /* clean ICMP checksum STM32F need */
    {
        struct eth_hdr *ethhdr = (struct eth_hdr *)(DMATxDescToSet->Buffer1Addr);
        /* is IP ? */
        if( ethhdr->type == htons(ETHTYPE_IP) )
        {
            struct ip_hdr *iphdr = (struct ip_hdr *)(DMATxDescToSet->Buffer1Addr + SIZEOF_ETH_HDR);
            /* is ICMP ? */
            if( IPH_PROTO(iphdr) == IP_PROTO_ICMP )
            {
                struct icmp_echo_hdr *iecho = (struct icmp_echo_hdr *)(DMATxDescToSet->Buffer1Addr + SIZEOF_ETH_HDR + sizeof(struct ip_hdr) );
                iecho->chksum = 0;
            }
        }
    }
#endif
    /* Return SUCCESS */
    return RT_EOK;
}

/* reception packet. */
struct pbuf *rt_stm32_eth_rx(rt_device_t dev)
{
    struct pbuf* p;
    rt_uint32_t offset = 0, framelength = 0;

    /* init p pointer */
    p = RT_NULL;

    /* Check if the descriptor is owned by the ETHERNET DMA (when set) or CPU (when reset) */
    if(((DMARxDescToGet->Status & ETH_DMARxDesc_OWN) != (uint32_t)RESET))
        return p;

    if (((DMARxDescToGet->Status & ETH_DMARxDesc_ES) == (uint32_t)RESET) &&
            ((DMARxDescToGet->Status & ETH_DMARxDesc_LS) != (uint32_t)RESET) &&
            ((DMARxDescToGet->Status & ETH_DMARxDesc_FS) != (uint32_t)RESET))
    {
        /* Get the Frame Length of the received packet: substruct 4 bytes of the CRC */
        framelength = ((DMARxDescToGet->Status & ETH_DMARxDesc_FL) >> ETH_DMARXDESC_FRAME_LENGTHSHIFT) - 4;
		rt_kprintf("%pkg len %d\n", framelength);
        /* allocate buffer */
        p = pbuf_alloc(PBUF_LINK, framelength, PBUF_RAM);
        if (p != RT_NULL)
        {
            struct pbuf* q;

            for (q = p; q != RT_NULL; q= q->next)
            {
                /* Copy the received frame into buffer from memory pointed by the current ETHERNET DMA Rx descriptor */
                memcpy(q->payload, (uint8_t *)((DMARxDescToGet->Buffer1Addr) + offset), q->len);
                offset += q->len;
            }
#ifdef ETH_RX_DUMP
            {
                rt_uint32_t i;
                rt_uint8_t *ptr = (rt_uint8_t*)(DMARxDescToGet->Buffer1Addr);

                STM32_ETH_PRINTF("rx_dump, len:%d\r\n", p->tot_len);
                for(i=0; i<p->tot_len; i++)
                {
                    STM32_ETH_PRINTF("%02x ", *ptr);
                    ptr++;

                    if(((i+1)%8) == 0)
                    {
                        STM32_ETH_PRINTF("  ");
                    }
                    if(((i+1)%16) == 0)
                    {
                        STM32_ETH_PRINTF("\r\n");
                    }
                }
                STM32_ETH_PRINTF("\r\ndump done!\r\n");
            }
#endif
        }
    }

    /* Set Own bit of the Rx descriptor Status: gives the buffer back to ETHERNET DMA */
    DMARxDescToGet->Status = ETH_DMARxDesc_OWN;

    /* When Rx Buffer unavailable flag is set: clear it and resume reception */
    if ((HHD_ETH->DMASR & ETH_DMASR_RBUS) != (uint32_t)RESET)
    {
        /* Clear RBUS ETHERNET DMA flag */
        HHD_ETH->DMASR = ETH_DMASR_RBUS;
        /* Resume DMA reception */
        HHD_ETH->DMARPDR = 0;
    }

    /* Update the ETHERNET DMA global Rx descriptor with next Rx decriptor */
    /* Chained Mode */
    if((DMARxDescToGet->ControlBufferSize & ETH_DMARxDesc_RCH) != (uint32_t)RESET)
    {
        /* Selects the next DMA Rx descriptor list for next buffer to read */
        DMARxDescToGet = (ETH_DMADESCTypeDef*) (DMARxDescToGet->Buffer2NextDescAddr);
    }
    else /* Ring Mode */
    {
        if((DMARxDescToGet->ControlBufferSize & ETH_DMARxDesc_RER) != (uint32_t)RESET)
        {
            /* Selects the first DMA Rx descriptor for next buffer to read: last Rx descriptor was used */
            DMARxDescToGet = (ETH_DMADESCTypeDef*) (HHD_ETH->DMARDLAR);
        }
        else
        {
            /* Selects the next DMA Rx descriptor list for next buffer to read */
            DMARxDescToGet = (ETH_DMADESCTypeDef*) ((uint32_t)DMARxDescToGet + 0x10 + ((HHD_ETH->DMABMR & ETH_DMABMR_DSL) >> 2));
        }
    }

    return p;
}



 



int rt_hw_hhd_eth_init(void)
{

	uint32_t rand_mac = 0;
    stm32_eth_device.ETH_Speed = ETH_Speed_100M;
    stm32_eth_device.ETH_Mode  = ETH_Mode_FullDuplex;
	
    /* OUI 00-80-E1 STMICROELECTRONICS. */
    stm32_eth_device.dev_addr[0] = 0x00;
    stm32_eth_device.dev_addr[1] = 0x80;
    stm32_eth_device.dev_addr[2] = 0xE1;
	
	srand(get_mark());
	rand_mac = rand();
	
	
    /* generate MAC addr from 96bit unique ID (only for test). */
    stm32_eth_device.dev_addr[3] = rand_mac & 0xFF;
    stm32_eth_device.dev_addr[4] = (rand_mac >> 8) & 0xFF;
    stm32_eth_device.dev_addr[5] = ((rand_mac ^= 8)>> 5) & 0xFF;

    stm32_eth_device.parent.parent.init       = rt_stm32_eth_init;
    stm32_eth_device.parent.parent.open       = rt_stm32_eth_open;
    stm32_eth_device.parent.parent.close      = rt_stm32_eth_close;
    stm32_eth_device.parent.parent.read       = rt_stm32_eth_read;
    stm32_eth_device.parent.parent.write      = rt_stm32_eth_write;
    stm32_eth_device.parent.parent.control    = rt_stm32_eth_control;
    stm32_eth_device.parent.parent.user_data  = RT_NULL;

    stm32_eth_device.parent.eth_rx     = rt_stm32_eth_rx;
    stm32_eth_device.parent.eth_tx     = rt_stm32_eth_tx;
	
	
    /* init tx semaphore */
    rt_sem_init(&tx_wait, "tx_wait", 0, RT_IPC_FLAG_FIFO);

    /* register eth device */
    eth_device_init(&(stm32_eth_device.parent), "NT");
	
	

	return 0;	
}
//INIT_PREV_EXPORT(rt_hw_stm32_eth_init);



