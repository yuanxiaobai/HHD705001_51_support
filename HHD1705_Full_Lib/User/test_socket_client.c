/*******************************************************************************************************
  * Company: Hiwafer Technology Co., Ltd.
  ******************************************************************************************************
  * �ļ����ƣ�socket_api.h
  * ����˵����
  * ��    ����V1.0
  * ��    �ߣ�EnderWigg	
  * ��    �ڣ�2019.4.10
  *
  * ���ļ��������ÿ��ļ���ع���
*******************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "hhd32f1xx.h"
#include "socket_api.h"
struct socket_info * client = NULL;
struct socket_info * server = NULL;

void recv_callback(uint8_t *data, int len)
{
	socket_client_write(client , data, len);
	
	if(*data == 12)
	{
		socket_client_close(client);
	}
	
}

void server_recv_callback(uint8_t *data, int len)
{
	int ret = 0;
extern	int info_deal(uint8_t *data);
	   
  ret = info_deal(data);
	
  socket_server_write(server, data, ret);	
	
}




void client_init(void)
{
	uint8_t server_ip[] = {192, 168,2,23};
	
	client = socket_client(server_ip, 45456, recv_callback);
}

void server_load(void)
{
	server = socket_server(2590,  server_recv_callback);

}



