/***************************************************************************************
//                                                                                    //
//								 SPI TCP Server (RAW) 版                              //
//                                                                                    //
//                                                                                    //
// 该TCP服务器用于转发网络数据到SPI接口												  //
// 1、连接到服务器后，客户端通过"getinfo:"，查询服务器每次能接收的最大数据长度和spi接 //
//    口操作位宽，服务器返回一次能接收的最大数据长度和spi操作位宽(当前未使用)   	  //
// 2、客户端根据获取到的flash起始地址和文件长度信息，通过"fileinfo:"xxxx              //
//    反馈给服务器，服务器会依据文件大小对Flash进行擦出，这可能需要一段时间			  //
// 3、服务器接收数据时，会检擦帧序号是否连续，不连续会返回给客户端错误，并指明期望的帧//
//    的序号；校验写入到Flash的数据是否正确，服务器将接收的数据通过SPI发送完成后，    //
//    才会反馈客户端接收完成，客户端必须在收到应答后再发送下一帧数据  				  //
//    													                              //
// 4、当服务器收到数据的帧数等于"fileinfo:"xxxx所指示的数量，认为数据接收完成，等待   //
//    "fileinfo:"xxxx 指令，来发起新的通信                                            //
// 5、加载数据过程中，允许取消加载客户端发出取消指令"!!!!"(0x21212121),服务器回到等到 //
//    “fileinfo:”状态                                                                  //
//	@Ender     																		  //			
 **************************************************************************************/


#include <string.h>
#include "hhd32f107.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "simulator_spi.h"
#include "load_server.h"
#include "MT25Q.h"
#include "FPGA_Manager.h"
#include "HHD1705_lib.h"

#define  uint8_t	u8_t
#define  uint16_t	u16_t


#if LWIP_TCP

static struct tcp_pcb *tcp_echoserver_pcb;

/* ECHO protocol states */
enum tcp_echoserver_states
{
  ES_NONE = 0,
  ES_ACCEPTED,
  ES_RECEIVED,
  ES_CLOSING
};



/* structure for maintaing connection infos to be passed as argument 
   to LwIP callbacks*/
struct tcp_echoserver_struct
{
  u8_t state;             /* current connection state */
  u8_t retries;
  struct tcp_pcb *pcb;    /* pointer on the current tcp_pcb */
  struct pbuf *p;         /* pointer on the received/to be transmitted pbuf */
};


static err_t tcp_echoserver_accept(void *arg, struct tcp_pcb *newpcb, err_t err);
static err_t tcp_echoserver_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static void tcp_echoserver_error(void *arg, err_t err);
static err_t tcp_echoserver_poll(void *arg, struct tcp_pcb *tpcb);
static err_t tcp_echoserver_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
static void tcp_echoserver_send(struct tcp_pcb *tpcb, struct tcp_echoserver_struct *es);
static void tcp_echoserver_connection_close(struct tcp_pcb *tpcb, struct tcp_echoserver_struct *es);

//uint8_t *temp_buff = NULL; 
uint32_t fileLen = 0;
uint8_t data_buff[MAX_PACKAGE_LEN+10] = {0};
uint8_t test_read[MAX_PACKAGE_LEN] = {0};
enum tcp_work_states en_WorkState = ES_GETINFO;
uint8_t buff[10] = {0};
uint32_t startaddr = 0;
uint32_t err_count = 0;

static int read_data(struct tcp_pcb *tpcb, struct tcp_echoserver_struct *es, uint8_t *data)
{
	struct pbuf *ptr;
	int count = 0;
	u16_t plen;
	u8_t freed;
 
	while ((es->p != NULL) && 
			(es->p->len <= tcp_sndbuf(tpcb)))
	{
		/* get pointer on pbuf from es structure */
		ptr = es->p;
		memcpy(data+count, ptr->payload, ptr->len);  

		count += ptr->len;
		plen = ptr->len;

		es->p = ptr->next;
		if(es->p != NULL)
		{
			pbuf_ref(es->p);
		}
		do
		{
			freed = pbuf_free(ptr);
		}
		while(freed == 0);
		
		tcp_recved(tpcb, plen);
	}
	
	return count;
}


/**************************************************************************************
*
*	帧下发处理
*
*
**************************************************************************************/
uint32_t file_count = 0;
uint8_t fpga = 0;
int frame_handler(uint8_t *data)
{
	static uint16_t frame_count = 0;
	uint16_t count = 0;
	uint16_t len = 0;
	
	if(*(uint32_t *)data == 0x21212121)    //"!!!!"
	{
											//提示接收端，放弃已接收的数据
		file_count = 0;
		frame_count = 0;

		return -2;
	}
	
	count = *(uint16_t *)data;
	len   = *((uint32_t *)(data+2));
	
	if(frame_count == count)
	{
		FPGA_cmd_clean();
		FPGA_cmd_select_fpga(fpga);
		FPGA_cmd_select_flash(fpga);
		
		mt25q_wirte(startaddr+file_count, data+6, len);
		
		mt25q_read(startaddr+file_count, test_read, len);
		
		if(memcmp(data+6, test_read, len) != 0)
		{
			err_count++;
			*((uint32_t *)(data+2)) = 0;
		}
		
		file_count += len;
		frame_count++;
	

	}
	else
	{
		*(uint16_t *)data = frame_count;
		*((uint16_t *)data+2) = 1;
	}

	if(file_count == fileLen)
	{
		frame_count = 0;
		file_count = 0;
		fileLen = 0;
		memcpy(buff,"ENDT",4);

		return 6;
	}
	else
	{
		return 6;
	}	
}

int info_deal(uint8_t *data)
{
	uint32_t lp_fpga = 0;
	if(memcmp(data, "getinfo:", 8) == 0)
	{
		((uint16_t *)data)[0] = MAX_PACKAGE_LEN;	    //缓冲区大小
		((uint16_t *)data)[1] = 8;				        //数据对其
		
		return 4;
	}
	else if(memcmp(data, "fileinfo:", 9) == 0)
	{
		startaddr = *(uint32_t*)(data+9);
		fileLen = *(uint32_t*)(data+13);
		lp_fpga = *(uint32_t*)(data+17);
		fpga = lp_fpga & 0xFF;
		
		FPGA_cmd_clean();
		FPGA_cmd_select_fpga(fpga);
		FPGA_cmd_select_flash(fpga);
		
		mt25q_init();
//		
		memcpy(data, data+9, 8);			
		file_count = 0;
		Flash_erase(startaddr, fileLen);
		
		return 8; 
	}
	else 
	{
		return frame_handler(data);
		
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
//												网络功能										    //
//																									//
//////////////////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief  Initializes the tcp load server
  * @param  None
  * @retval None
  */
void load_server_init(void)
{
  /* create new tcp pcb */
  tcp_echoserver_pcb = tcp_new();

  if (tcp_echoserver_pcb != NULL)
  {
    err_t err;
    
    /* bind echo_pcb to port 7 (ECHO protocol) */
    err = tcp_bind(tcp_echoserver_pcb, IP_ADDR_ANY, SPI_PORT);
    
    if (err == ERR_OK)
    {
      /* start tcp listening for echo_pcb */
      tcp_echoserver_pcb = tcp_listen(tcp_echoserver_pcb);
      
      /* initialize LwIP tcp_accept callback function */
      tcp_accept(tcp_echoserver_pcb, tcp_echoserver_accept);
    }
    else 
    {
      /* deallocate the pcb */
      memp_free(MEMP_TCP_PCB, tcp_echoserver_pcb);
    }
  }
}

/**
  * @brief  This function is the implementation of tcp_accept LwIP callback
  * @param  arg: not used
  * @param  newpcb: pointer on tcp_pcb struct for the newly created tcp connection
  * @param  err: not used 
  * @retval err_t: error status
  */
static err_t tcp_echoserver_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
  err_t ret_err;
  struct tcp_echoserver_struct *es;

  LWIP_UNUSED_ARG(arg);
  LWIP_UNUSED_ARG(err);

  /* set priority for the newly accepted tcp connection newpcb */
  tcp_setprio(newpcb, TCP_PRIO_MIN);

  /* allocate structure es to maintain tcp connection informations */
  es = (struct tcp_echoserver_struct *)mem_malloc(sizeof(struct tcp_echoserver_struct));
  if (es != NULL)
  {
    es->state = ES_ACCEPTED;
    es->pcb = newpcb;
    es->retries = 0;
    es->p = NULL;
    
    /* pass newly allocated es structure as argument to newpcb */
    tcp_arg(newpcb, es);
    
    /* initialize lwip tcp_recv callback function for newpcb  */ 
    tcp_recv(newpcb, tcp_echoserver_recv);
    
	   /* initialize LwIP tcp_sent callback function */
    tcp_sent(newpcb, tcp_echoserver_sent);
    /* initialize lwip tcp_err callback function for newpcb  */
    tcp_err(newpcb, tcp_echoserver_error);
    
    /* initialize lwip tcp_poll callback function for newpcb */
    tcp_poll(newpcb, tcp_echoserver_poll, 0);
  
    ret_err = ERR_OK;
	  
//	apb1_peripheral_clock( DISABLE);
  }
  else
  {
    /*  close tcp connection */
    tcp_echoserver_connection_close(newpcb, es);
    /* return memory error */
    ret_err = ERR_MEM;
  }
  return ret_err;  
}


/**
  * @brief  This function is the implementation for tcp_recv LwIP callback
  * @param  arg: pointer on a argument for the tcp_pcb connection
  * @param  tpcb: pointer on the tcp_pcb connection
  * @param  pbuf: pointer on the received pbuf
  * @param  err: error information regarding the reveived pbuf
  * @retval err_t: error code
  */

int ret = 0;
static err_t tcp_echoserver_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	struct tcp_echoserver_struct *es;
	err_t ret_err;
//	int ret = 0;
	
  LWIP_ASSERT("arg != NULL",arg != NULL);
  
  es = (struct tcp_echoserver_struct *)arg;
  
  /* if we receive an empty tcp frame from client => close connection */
  if (p == NULL)
  {
    /* remote host closed connection */
    es->state = ES_CLOSING;
    if(es->p == NULL)
    {
       /* we're done sending, close connection */
       tcp_echoserver_connection_close(tpcb, es);
    }
    else
    {
      /* we're not done yet */
      /* acknowledge received packet */
      tcp_sent(tpcb, tcp_echoserver_sent);
      
      /* send remaining data*/
      tcp_echoserver_send(tpcb, es);
    }
    ret_err = ERR_OK;
  }   
  /* else : a non empty frame was received from client but for some reason err != ERR_OK */
  else if(err != ERR_OK)
  {
    /* free received pbuf*/
    if (p != NULL)
    {
      es->p = NULL;
      pbuf_free(p);
    }
    ret_err = err;
  }
  else if((es->state == ES_RECEIVED) || (es->state == ES_ACCEPTED) )
  {
	if(es->state == ES_ACCEPTED)
	{
		es->state = ES_RECEIVED;
	}
	  /* first data chunk in p->payload */
    
    
    /* store reference to incoming pbuf (chain) */
	if(es->p == NULL)
	{	
		es->p = p;
		/* send back received data */
	////////////////////////////////////////////////////////////////////////////////////////////////
		ret =  read_data(tpcb, es, data_buff);                    //接收数据
		if((ret > 0) /*&& en_WorkState !=  ES_SENDDATA*/)			   
		{
			ret = info_deal(data_buff);                            //协商通信参数

			tcp_write(tpcb, data_buff, ret, 1);
		}

	}
    else
    {
      struct pbuf *ptr;

      /* chain pbufs to the end of what we recv'ed previously  */
      ptr = es->p;
      pbuf_chain(ptr,p);
    }
///////////////////////////////////////////////////////////////////////////////////////////////	  
   
    ret_err = ERR_OK;
  }

  else if(es->state == ES_CLOSING)
  {
    /* odd case, remote side closing twice, trash data */
	  
    tcp_recved(tpcb, p->tot_len);
    es->p = NULL;
    pbuf_free(p);
    ret_err = ERR_OK;
  }
  else
  {
	
    /* unkown es->state, trash data  */
    tcp_recved(tpcb, p->tot_len);
    es->p = NULL;
    pbuf_free(p);
    ret_err = ERR_OK;
  }
  return ret_err;
}

/**
  * @brief  This function implements the tcp_err callback function (called
  *         when a fatal tcp_connection error occurs. 
  * @param  arg: pointer on argument parameter 
  * @param  err: not used
  * @retval None
  */
static void tcp_echoserver_error(void *arg, err_t err)
{
  struct tcp_echoserver_struct *es;

  LWIP_UNUSED_ARG(err);

  es = (struct tcp_echoserver_struct *)arg;
  if (es != NULL)
  {
    /*  free es structure */
    mem_free(es);
  }
}

/**
  * @brief  This function implements the tcp_poll LwIP callback function
  * @param  arg: pointer on argument passed to callback
  * @param  tpcb: pointer on the tcp_pcb for the current tcp connection
  * @retval err_t: error code
  */
static err_t tcp_echoserver_poll(void *arg, struct tcp_pcb *tpcb)
{
  err_t ret_err;
  struct tcp_echoserver_struct *es;

  es = (struct tcp_echoserver_struct *)arg;
  if (es != NULL)
  {
    if (es->p != NULL)
    {
      tcp_sent(tpcb, tcp_echoserver_sent);
      /* there is a remaining pbuf (chain) , try to send data */
      tcp_echoserver_send(tpcb, es);
    }
    else
    {
      /* no remaining pbuf (chain)  */
      if(es->state == ES_CLOSING)
      {
        /*  close tcp connection */
        tcp_echoserver_connection_close(tpcb, es);
      }
    }
    ret_err = ERR_OK;
  }
  else
  {
    /* nothing to be done */
    tcp_abort(tpcb);
    ret_err = ERR_ABRT;
  }
  return ret_err;
}

/**
  * @brief  This function implements the tcp_sent LwIP callback (called when ACK
  *         is received from remote host for sent data) 
  * @param  None
  * @retval None
  */
static err_t tcp_echoserver_sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
  struct tcp_echoserver_struct *es;

  LWIP_UNUSED_ARG(len);

  es = (struct tcp_echoserver_struct *)arg;
  es->retries = 0;
  
  if(es->p != NULL)
  {
    /* still got pbufs to send */
    tcp_sent(tpcb, tcp_echoserver_sent);
    tcp_echoserver_send(tpcb, es);
  }
  else
  {
    /* if no more data to send and client closed connection*/
    if(es->state == ES_CLOSING)
      tcp_echoserver_connection_close(tpcb, es);
  }
  return ERR_OK;
}


/**
  * @brief  This function is used to send data for tcp connection
  * @param  tpcb: pointer on the tcp_pcb connection
  * @param  es: pointer on echo_state structure
  * @retval None
  */
static void tcp_echoserver_send(struct tcp_pcb *tpcb, struct tcp_echoserver_struct *es)
{
  struct pbuf *ptr;
  err_t wr_err = ERR_OK;
 
  while ((wr_err == ERR_OK) &&
         (es->p != NULL) && 
         (es->p->len <= tcp_sndbuf(tpcb)))
  {
    
    /* get pointer on pbuf from es structure */
    ptr = es->p;

    /* enqueue data for transmission */
    wr_err = tcp_write(tpcb, ptr->payload, ptr->len, 1);
    
    if (wr_err == ERR_OK)
    {
      u16_t plen;
      u8_t freed;
		
		
      plen = ptr->len;
     
      /* continue with next pbuf in chain (if any) */
      es->p = ptr->next;
      
      if(es->p != NULL)
      {
        /* increment reference count for es->p */
        pbuf_ref(es->p);
      }
      
     /* chop first pbuf from chain */
      do
      {
        /* try hard to free pbuf */
        freed = pbuf_free(ptr);
      }
      while(freed == 0);
     /* we can read more data now */
     tcp_recved(tpcb, plen);
   }
   else if(wr_err == ERR_MEM)
   {
      /* we are low on memory, try later / harder, defer to poll */
     es->p = ptr;
   }
   else
   {
     /* other problem ?? */
   }
  }
}

/**
  * @brief  This functions closes the tcp connection
  * @param  tcp_pcb: pointer on the tcp connection
  * @param  es: pointer on echo_state structure
  * @retval None
  */
static void tcp_echoserver_connection_close(struct tcp_pcb *tpcb, struct tcp_echoserver_struct *es)
{
  
  /* remove all callbacks */
  tcp_arg(tpcb, NULL);
  tcp_sent(tpcb, NULL);
  tcp_recv(tpcb, NULL);
  tcp_err(tpcb, NULL);
  tcp_poll(tpcb, NULL, 0);
  
  //apb1_peripheral_clock( ENABLE);
  /* delete es structure */
  if (es != NULL)
  {
    mem_free(es);
  }  
  
  /* close tcp connection */
  tcp_close(tpcb);
}

#endif /* LWIP_TCP */
