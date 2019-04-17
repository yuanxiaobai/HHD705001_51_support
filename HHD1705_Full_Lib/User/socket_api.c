#include <stdio.h>
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


 
static void tcp_errf(void *arg,err_t err)
{
	struct socket_info *es;
    printf("\r\ntcp_errf be called...\r\n");
    if(es == NULL)
	{
        es = (struct socket_info *)mem_malloc(sizeof(struct socket_info));
        es = (struct socket_info *)arg;
    }
    if(err == ERR_OK ){
          /* No error, everything OK. */
          return ;
     }   
    switch(err)
    { 
        case ERR_MEM:                                            /* Out of memory error.     */
            printf("\r\n ERR_MEM   \r\n");
            break;  
        case ERR_BUF:                                            /* Buffer error.            */
            printf("\r\n ERR_BUF   \r\n");
            break;
        case  ERR_TIMEOUT:                                       /* Timeout.                 */
            printf("\r\n ERR_TIMEOUT   \r\n");
            break;
        case ERR_RTE:                                            /* Routing problem.         */      
             printf("\r\n ERR_RTE   \r\n");
            break;
       case ERR_ISCONN:                                          /* Already connected.       */
             printf("\r\n ERR_ISCONN   \r\n");
            break;
        case ERR_ABRT:                                           /* Connection aborted.      */
            printf("\r\n ERR_ABRT   \r\n");
            break;
        case ERR_RST:                                            /* Connection reset.        */     
            printf("\r\n ERR_RST   \r\n");
            break;
        case ERR_CONN:                                           /* Not connected.           */
          printf("\r\n ERR_CONN   \r\n");
            break;
        case ERR_CLSD:                                           /* Connection closed.       */
            printf("\r\n ERR_CLSD   \r\n");
            break;
        case ERR_VAL:                                            /* Illegal value.           */
           printf("\r\n ERR_VAL   \r\n");
           return;
        case ERR_ARG:                                            /* Illegal argument.        */
            printf("\r\n ERR_ARG   \r\n");
            return;
        case ERR_USE:                                            /* Address in use.          */
           printf("\r\n ERR_USE   \r\n");
           return; 
        case ERR_IF:                                             /* Low-level netif error    */
            printf("\r\n ERR_IF   \r\n");
            break;
        case ERR_INPROGRESS:                                     /* Operation in progress    */
            printf("\r\n ERR_INPROGRESS   \r\n");
            break;
    }
   es->state  = ES_CLOSING;

}
    
static void tcp_client_connection_close(struct tcp_pcb *tpcb, struct socket_info *es)
{
  /* remove callbacks */
  tcp_recv(es->pcb, NULL);
  if (es != NULL)
  {
  	if(es->p_tx != NULL)
	{
		pbuf_free(es->p_tx);
  	}
	if (es->pcb != NULL) 
	{
		  /* close tcp connection */
		 tcp_close(es->pcb);
	}
    mem_free(es);
    es = NULL;
  }
 
}  

 
/**
  * @brief function used to send data
  * @param  tpcb: tcp control block
  * @param  es: pointer on structure of type client containing info on data 
  *             to be sent
  * @retval None 
  */
void tcp_client_send(struct tcp_pcb *tpcb, struct socket_info * es)
{
  struct pbuf *ptr;
		err_t wr_err = ERR_OK; 
  while ((wr_err == ERR_OK) &&
         (es->p_tx != NULL) && 
         (es->p_tx->len <= tcp_sndbuf(tpcb)))
  {
    /* get pointer on pbuf from es structure */
    ptr = es->p_tx;
 
    wr_err = tcp_write(tpcb, ptr->payload, ptr->len, 1);
    
    if (wr_err == ERR_OK)
    { 
      /* continue with next pbuf in chain (if any) */
      es->p_tx = ptr->next;
      
      if(es->p_tx != NULL)
      {
      /* increment reference count for es->p */
        pbuf_ref(es->p_tx);
      }
      pbuf_free(ptr);
   }
   else if(wr_err == ERR_MEM)
   {
      /* we are low on memory, try later, defer to poll */
     es->p_tx = ptr;                                                    
   }
   else
   {
     es->p_tx = ptr;    
     /* other problem ?? */
   }
  }
}
 
 
/**
  * @brief tcp_receiv callback
  * @param arg: argument to be passed to receive callback 
  * @param tpcb: tcp connection control block 
  * @param err: receive error code 
  * @retval err_t: retuned error  
  */
static err_t tcp_client_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{ 
  struct socket_info *es;
  err_t ret_err;
  LWIP_ASSERT("arg != NULL",arg != NULL);
  es = (struct socket_info *)arg;
  if (p == NULL)
  {
    /* remote host closed connection */
    es->state = ES_CLOSING;
    if(es->p_tx == NULL)
    {
       /* we're done sending, close connection */
       tcp_client_connection_close(tpcb, es);
    }
    ret_err = ERR_OK;
  }   
  else if(err != ERR_OK)
  {
    /* free received pbuf*/
    if (p != NULL)
    {
      pbuf_free(p);
    }
    ret_err = err;
  }
  else if(es->state == ES_CONNECTED)
  {  
    /* Acknowledge data reception */
    tcp_recved(tpcb, p->tot_len);                   //获取p中的数据。
     
	  
	es->recv_callback(p->payload, p->len);
   
    pbuf_free(p);                   
    ret_err = ERR_OK;   
  }
  /* data received when connection already closed */
  else
  {
    /* Acknowledge data reception */
    tcp_recved(tpcb, p->tot_len);
    
    /* free pbuf and do nothing */
    pbuf_free(p);
    ret_err = ERR_OK;
  }
  return ret_err;
} 

static err_t tcp_client_connected(void *arg, struct tcp_pcb *tpcb, err_t err)
{
    struct socket_info *es = NULL;
	es = (struct socket_info *)arg;
    switch(err)
	{
        case ERR_OK:  
          es->pcb = tpcb;                                  /*设置当前的状态为连接状态?*/  
          es->p_tx = NULL;
          es->state = ES_CONNECTED;  
         
          tcp_recv(tpcb, tcp_client_recv);
        
          break ;
       case ERR_MEM :
           tcp_client_connection_close(tpcb, es);                
          break ;
       default :
           break ;
           
   }
   return err;
}



 
/***********************************************************************************************
*
*	创建一个tcp 客户端连接
*
*
***********************************************************************************************/ 
struct socket_info * socket_client(const uint8_t *destip, uint16_t port, 
												void ( *recv_callback)(uint8_t *data, int len))
{
  struct tcp_pcb *client_pcb;
  struct ip_addr DestIPaddr;
 
  struct socket_info *es = NULL;
  /* create new tcp pcb */
  client_pcb = tcp_new();
  client_pcb->so_options |= SOF_KEEPALIVE;
 #if 1
  client_pcb->keep_idle = 50000;	   // ms
  client_pcb->keep_intvl = 20000;	   // ms
  client_pcb->keep_cnt = 5; 
 #endif	

		
  if (client_pcb != NULL)
  {
   
	es = (struct socket_info *)mem_malloc(sizeof(struct socket_info));
	if( es == NULL )
	{
		return NULL;
	}
	es->recv_callback = recv_callback;
	client_pcb->callback_arg = es;	
	  
   IP4_ADDR( &DestIPaddr, *destip, *(destip+1),*(destip+2), *(destip+3) );
 
    /* connect to destination address/port */
    tcp_connect(client_pcb,&DestIPaddr,port,tcp_client_connected);
   
    tcp_err(client_pcb,tcp_errf);
    
  }
  return es;
}


//user send message 
int16_t socket_client_write(struct socket_info * es, void *msg, uint16_t len)
{  
    if(es->state != ES_CONNECTED)  
	{
		return -1;
	}
    if(es->p_tx == NULL)
	{
        
          es->p_tx  = pbuf_alloc(PBUF_TRANSPORT,len,PBUF_RAM);          
          pbuf_take( es->p_tx , (char*)msg, len);
    }
    tcp_client_send(es->pcb,es);
    return len;
}
 

void socket_client_close(struct socket_info * es)
{
	tcp_client_connection_close(es->pcb, es);

}
 




#endif

