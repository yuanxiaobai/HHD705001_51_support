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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hhd32f107.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"

#include "HHD1705_lib.h"
#include "socket_api.h"

#define  uint8_t	u8_t
#define  uint16_t	u16_t

#if LWIP_TCP

static err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err);
static err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static void tcp_server_error(void *arg, err_t err);
static err_t tcp_server_poll(void *arg, struct tcp_pcb *tpcb);
static err_t tcp_server_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
static void tcp_server_send(struct tcp_pcb *tpcb, struct socket_info *es);
static void server_connection_close(struct tcp_pcb *tpcb, struct socket_info *es);


static void _read_data(struct socket_info *es)
{
	struct pbuf *ptr;
	int count = 0;
	u16_t plen;
	u8_t freed;
	
	uint8_t *buff = NULL;

    if(es->p_tx != NULL)
	{
		buff = (uint8_t *)malloc(es->p_tx->tot_len);
	}
    
//	while ((es->p_tx != NULL) && 
//			(es->p_tx->len <= tcp_sndbuf(es->pcb)))
	{
		/* get pointer on pbuf from es structure */
		ptr = es->p_tx;
		
		memcpy(buff+count, ptr->payload, ptr->len);
		count += ptr->len;
		es->p_tx = ptr->next;
		if(es->p_tx != NULL)
		{
			pbuf_ref(es->p_tx);
		}
		do
		{
			freed = pbuf_free(ptr);
		}
		while(freed == 0);
		
		tcp_recved(es->pcb, plen);
	}
	es->p_tx= NULL;
	es->recv_callback(buff, count); 

	free(buff);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
//												网络功能										    //
//																									//
//////////////////////////////////////////////////////////////////////////////////////////////////////


/**
  * @brief  This function is the implementation of tcp_accept LwIP callback
  * @param  arg: not used
  * @param  newpcb: pointer on tcp_pcb struct for the newly created tcp connection
  * @param  err: not used 
  * @retval err_t: error status
  */
static err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
  err_t ret_err;
  struct socket_info *es = (struct socket_info *)arg;

  LWIP_UNUSED_ARG(err);

  /* set priority for the newly accepted tcp connection newpcb */
  tcp_setprio(newpcb, TCP_PRIO_MIN);

  /* allocate structure es to maintain tcp connection informations */
 
  if (es != NULL)
  {
    es->state = ES_ACCEPTED;
    es->pcb = newpcb;
    es->p_tx= NULL;
    
    /* pass newly allocated es structure as argument to newpcb */
    tcp_arg(newpcb, es);
    
    /* initialize lwip tcp_recv callback function for newpcb  */ 
    tcp_recv(newpcb, tcp_server_recv);
    
	   /* initialize LwIP tcp_sent callback function */
    tcp_sent(newpcb, tcp_server_sent);
    /* initialize lwip tcp_err callback function for newpcb  */
    tcp_err(newpcb, tcp_server_error);
    
    /* initialize lwip tcp_poll callback function for newpcb */
    tcp_poll(newpcb, tcp_server_poll, 0);
  
    ret_err = ERR_OK;
	  
//	apb1_peripheral_clock( DISABLE);
  }
  else
  {
    /*  close tcp connection */
    server_connection_close(newpcb, es);
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


static err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	struct socket_info *es;
	err_t ret_err;
//	int ret = 0;
	
  LWIP_ASSERT("arg != NULL",arg != NULL);
  
  es = (struct socket_info *)arg;
  
  /* if we receive an empty tcp frame from client => close connection */
  if (p == NULL)
  {
    /* remote host closed connection */
    es->state = ES_CLOSING;
    if(es->p_tx== NULL)
    {
       /* we're done sending, close connection */
       server_connection_close(tpcb, es);
    }
    else
    {
      /* we're not done yet */
      /* acknowledge received packet */
      tcp_sent(tpcb, tcp_server_sent);
      
      /* send remaining data*/
      tcp_server_send(tpcb, es);
    }
    ret_err = ERR_OK;
  }   
  /* else : a non empty frame was received from client but for some reason err != ERR_OK */
  else if(err != ERR_OK)
  {
    /* free received pbuf*/
    if (p != NULL)
    {
      es->p_tx= NULL;
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
	if(es->p_tx == NULL)
	{	
		es->p_tx= p;

		_read_data(es);

	}
    else
    {
      struct pbuf *ptr;

      /* chain pbufs to the end of what we recv'ed previously  */
      ptr = es->p_tx;
      pbuf_chain(ptr,p);
    } 
   
    ret_err = ERR_OK;
  }

  else if(es->state == ES_CLOSING)
  {
    /* odd case, remote side closing twice, trash data */
	  
    tcp_recved(tpcb, p->tot_len);
    es->p_tx= NULL;
    pbuf_free(p);
    ret_err = ERR_OK;
  }
  else
  {
    /* unkown es->state, trash data  */
    tcp_recved(tpcb, p->tot_len);
    es->p_tx= NULL;
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
static void tcp_server_error(void *arg, err_t err)
{
	struct socket_info *es;

	LWIP_UNUSED_ARG(err);

	es = (struct socket_info *)arg;
	if (es != NULL)
	{
	/*  free es structure */
		mem_free(es);
	}
}


/**
  * @brief  This functions closes the tcp connection
  * @param  tcp_pcb: pointer on the tcp connection
  * @param  es: pointer on echo_state structure
  * @retval None
  */
static void server_connection_close(struct tcp_pcb *tpcb, struct socket_info *es)
{
  
	/* remove all callbacks */
	tcp_arg(tpcb, NULL);
	tcp_sent(tpcb, NULL);
	tcp_recv(tpcb, NULL);
	tcp_err(tpcb, NULL);
	tcp_poll(tpcb, NULL, 0);

	/* close tcp connection */
	tcp_close(tpcb);

//	/* delete es structure */
//	if (es != NULL)
//	{
//		mem_free(es);
//	}  

}
/**
  * @brief  This function implements the tcp_poll LwIP callback function
  * @param  arg: pointer on argument passed to callback
  * @param  tpcb: pointer on the tcp_pcb for the current tcp connection
  * @retval err_t: error code
  */
static err_t tcp_server_poll(void *arg, struct tcp_pcb *tpcb)
{
	err_t ret_err;
	struct socket_info *es;

	es = (struct socket_info *)arg;
	if (es != NULL)
	{
		if (es->p_tx!= NULL)
	{
		tcp_sent(tpcb, tcp_server_sent);
		/* there is a remaining pbuf (chain) , try to send data */
		tcp_server_send(tpcb, es);
	}
	else
	{
		/* no remaining pbuf (chain)  */
		if(es->state == ES_CLOSING)
		{
		/*  close tcp connection */
		server_connection_close(tpcb, es);
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
static err_t tcp_server_sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
  struct socket_info *es;

  LWIP_UNUSED_ARG(len);

  es = (struct socket_info *)arg;

  if(es->p_tx != NULL)
  {
    /* still got pbufs to send */
    tcp_sent(tpcb, tcp_server_sent);
    tcp_server_send(tpcb, es);
  }
  else
  {
    /* if no more data to send and client closed connection*/
    if(es->state == ES_CLOSING)
      server_connection_close(tpcb, es);
  }
  return ERR_OK;
}


/**
  * @brief  This function is used to send data for tcp connection
  * @param  tpcb: pointer on the tcp_pcb connection
  * @param  es: pointer on echo_state structure
  * @retval None
  */
static void tcp_server_send(struct tcp_pcb *tpcb, struct socket_info *es)
{
  struct pbuf *ptr;
  err_t wr_err = ERR_OK;
 
  while ((wr_err == ERR_OK) &&
         (es->p_tx != NULL) && 
         (es->p_tx->len <= tcp_sndbuf(tpcb)))
  {
    
    /* get pointer on pbuf from es structure */
    ptr = es->p_tx;

    /* enqueue data for transmission */
    wr_err = tcp_write(tpcb, ptr->payload, ptr->len, 1);
    
    if (wr_err == ERR_OK)
    {
      u16_t plen;
      u8_t freed;
		
		
      plen = ptr->len;
     
      /* continue with next pbuf in chain (if any) */
      es->p_tx = ptr->next;
      
      if(es->p_tx != NULL)
      {
        /* increment reference count for es->p */
        pbuf_ref(es->p_tx);
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
     es->p_tx = ptr;
   }
   else
   {
     /* other problem ?? */
   }
  }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
//											USER API 										        //
//																									//
//////////////////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief  使用本机IP创建TCP服务器
  * @param  port: 服务器监听的端口号
  * @param  recv_callback: 处理接收到的数据的回调函数
  * @retval 如果创建成功返回该服务器的描述符，失败返回NULL
  */
struct socket_info *socket_server(uint16_t port,  RECV_CALLBACK recv_callback)
{
	struct socket_info * es = NULL;
	struct tcp_pcb *tcp_echoserver_pcb = NULL;
	/* create new tcp pcb */
	tcp_echoserver_pcb = tcp_new();

	es = (struct socket_info *)mem_malloc(sizeof(struct socket_info));
	if(es == NULL)
	{
		return NULL;
	}
	tcp_echoserver_pcb->callback_arg = es;
	if (tcp_echoserver_pcb != NULL)
	{
		err_t err;

		/* bind echo_pcb to port 7 (ECHO protocol) */
		err = tcp_bind(tcp_echoserver_pcb, IP_ADDR_ANY, port);

		if (err == ERR_OK)
		{
		/* start tcp listening for echo_pcb */
		tcp_echoserver_pcb = tcp_listen(tcp_echoserver_pcb);

		/* initialize LwIP tcp_accept callback function */
		tcp_accept(tcp_echoserver_pcb, tcp_server_accept);
		es->recv_callback = recv_callback;	

		return es; 		

		}
		else 
		{
			/* deallocate the pcb */
			memp_free(MEMP_TCP_PCB, tcp_echoserver_pcb);

			return NULL;	
		}
	}
}



/**
  * @brief  向客户端发送数据
  * @param  es: 服务器描述符
  * @param  msg: 待发送数据指针
  * @param  len: 待发送数据长度
  * @retval 发送成功返回已发送数据的长度，否则返回 0
  */
int16_t socket_server_write(struct socket_info * es, void *msg, uint16_t len)
{

	  es->p_tx = pbuf_alloc(PBUF_TRANSPORT,len,PBUF_RAM);
	  if( es->p_tx != NULL)
	  {
		 pbuf_take( es->p_tx , (char*)msg, len);
		 tcp_server_sent(es,es->pcb,0);
		 return len;
	  }
	  else
	  {
		return 0;
	  }
 
}


/**
  * @brief  关闭服务器
  * @param  es: 服务器描述符
  * @retval 无
  */
 void socket_server_close(struct socket_info * es)
 {
	 if(es != NULL)
	 {
		server_connection_close(es->pcb, es);
		

		/* deallocate the pcb */
		memp_free(MEMP_TCP_PCB, es->pcb);
		mem_free(es);
	 }	
	 
    	 
	 
 }

#endif /* LWIP_TCP */
