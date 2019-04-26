/*******************************************************************************************************
  * Company: Hiwafer Technology Co., Ltd.
  ******************************************************************************************************
  * �ļ����ƣ�load_server_BSD.c
  * ����˵����
  * ��    ����V2.0
  * ��    �ߣ�EnderWigg	
  * ��    �ڣ�2019.4.20
  *
  * ���ļ��������ÿ��ļ���ع���
*******************************************************************************************************/
#include <rtthread.h>
#include "lwip/sockets.h" /* ʹ��BSD socket����Ҫ����socket.hͷ�ļ� */
#include "load_server.h"
#include "hhd32f1xx.h"
#include "FPGA_Manager.h"
#include "MT25Q.h"


uint32_t fileLen = 0;
uint8_t data_buff[MAX_PACKAGE_LEN] = {0};
uint8_t test_read[MAX_PACKAGE_LEN] = {0};

int sock, connected;
uint32_t startaddr = 0;
uint32_t file_count = 0;
uint8_t fpga = 0;
rt_sem_t  erase_sem;


int fast_compare(uint8_t *data1, uint8_t *data2, int len )
{

	for( ;len > 7;len -= 8, data1 += 8, data2 += 8)
	{
		if((*(uint32_t*)data1 != *(uint32_t*)data2) || 
			(*(uint32_t*)data1+4 != *(uint32_t*)data2+4))
		{
			return 2;
		}
	}
	
	for( ;len > 1;len -= 2, data1 += 2, data2 += 2)
	{
		if(*(uint16_t*)data1 != *(uint16_t*)data2) 
		{
			return 2;
		}
	}
	
	if (len > 0) 
	{ 
		if(*(uint8_t*)data1 != *(uint8_t*)data2)
		{
			return 2;
		}
	}
	
	return 0;
}

/**
 * @brief Flash ��������

 * @param the first input value
 * @return the return value 
 * @details a full description of what the function does
 * @see a reference to another function

*/

void erase_task(void *arg)
{
	int ret = 0;
	while(1)
	{
		rt_sem_take(erase_sem, RT_WAITING_FOREVER);
		Flash_erase(startaddr, fileLen);
		*(uint32_t *)test_read = startaddr;
		*(uint32_t *)(test_read+4) = fileLen;
		
		ret = send(connected, test_read, 8 , 0);
		 if (ret < 0)
		{
			/* ����ʧ�ܣ��ر�������� */
			closesocket(connected);
			rt_kprintf("\nsend error,close the socket.\r\n");
			break;
		}
		else if (ret == 0)
		{
			/* ��ӡsend��������ֵΪ0�ľ�����Ϣ */
//                rt_kprintf("\n Send warning,send function return 0.\r\n");
		}	

	}
}
 

/**
 * @brief Э��������Ϣ
 *
 * @param socket ����������
 * @param ���ݻ�����
 * @return ��Ҫ���ͳ�ȥ�����ݳ��ȣ��������0 �����
*/
int frame_consultation(int fd, uint8_t *data)
{
	int32_t ret = 0;
	uint32_t lp_fpga = 0;
	
	ret = recv(fd, data, 8, 0);
	if (ret <= 0)
	{
		/* ����ʧ�ܣ��ر����connected socket */
		closesocket(fd);
		fileLen = 0;
		return 0;
	}
	
	if(memcmp(data, "getinfo:", 8) == 0)
	{
		((uint16_t *)data)[0] = MAX_PACKAGE_LEN;	    //��������С
		((uint16_t *)data)[1] = 8;				        //���ݶ���
		
		return 4;
	}
	else if(memcmp(data, "fileinfo", 8) == 0)
	{
		ret = recv(fd, data, 13, 0);
		if (ret <= 0)
		{
			/* ����ʧ�ܣ��ر����connected socket */
			closesocket(fd);
			fileLen = 0;
			return 0;
		}
		
		startaddr = *(uint32_t*)(data+1);
		fileLen = *(uint32_t*)(data+5);
		lp_fpga = *(uint32_t*)(data+9);
		fpga = lp_fpga & 0xFF;
		
		FPGA_cmd_clean();
		FPGA_cmd_select_fpga(fpga);
		FPGA_cmd_select_flash(fpga);
		
		mt25q_init();
		
		file_count = 0;
		*(uint32_t*)data = 0;
		*(uint32_t*)(data+4) = 0x88;
		 rt_sem_release(erase_sem);	
		
		return 8; 
	}
	else
	{
		return 0;
	}	
	
}

/**
 * @brief �ļ����ش���
 *
 * @param socket ����������
 * @param ���ݻ�����
 * @return ��Ҫ���ͳ�ȥ�����ݳ��ȣ��������0 �����
*/
int frame_handler(int fd, uint8_t *data)
{
	int32_t ret = 0;
	static uint16_t frame_count = 0;
	uint16_t count = 0;
	uint16_t len = 0;
	uint32_t to_len = 0;
	
	ret = recv(fd, data, 6, 0);
	if (ret <= 0)
	{
		/* ����ʧ�ܣ��ر����connected socket */
		closesocket(fd);
		fileLen = 0;
		return 0;
	}
	
	if(*(uint32_t *)data == 0x21212121)    //"!!!!"
	{
											//��ʾ���նˣ������ѽ��յ�����
		file_count = 0;
		frame_count = 0;
		*((uint32_t *)(data+2)) = 0;
		
	}
	
	count = *(uint16_t *)data;
	len   = *((uint32_t *)(data+2));
	
	if(frame_count == count)
	{
		FPGA_cmd_clean();
		FPGA_cmd_select_fpga(fpga);
		FPGA_cmd_select_flash(fpga);
		
		while(1)
		{
			 
			ret = recv(fd, data+to_len , (len - to_len), 0);
			if (ret <= 0)
			{
				/* ����ʧ�ܣ��ر����connected socket */
				closesocket(fd);
				return 0;
			}
			if(ret < (len - to_len))
			{
				to_len += ret;
			}
			else
			{
				break;
			}
		}
		*(uint16_t*)data = count;
		*(uint32_t*)(data+2) = len;
		
		mt25q_wirte(startaddr+file_count, data, len);
		mt25q_read(startaddr+file_count, test_read, len);
		if(fast_compare(data+6, test_read, len) != 0)
		{

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
	}

	return 6;
		
}




static void tcpserv(void *parameter)
{
 
    socklen_t sin_size;
  
    struct sockaddr_in server_addr, client_addr;
    
    int ret;
	
	
    /* һ��socket��ʹ��ǰ����ҪԤ�ȴ���������ָ��SOCK_STREAMΪTCP��socket */
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        /* ����ʧ�ܵĴ����� */
        rt_kprintf("Socket error\n");

        
        return;
    }

    /* ��ʼ������˵�ַ */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SPI_PORT); /* ����˹����Ķ˿� */
    server_addr.sin_addr.s_addr = INADDR_ANY;
	
  
    /* ��socket������˵�ַ */
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        /* ��ʧ�� */
        rt_kprintf("Unable to bind\n");
        return;
    }

    /* ��socket�Ͻ��м��� */
    if (listen(sock, 1) == -1)
    {
        rt_kprintf("Listen error\n");
        return;
    }
	
	sin_size = sizeof(struct sockaddr_in);
	
	erase_sem = rt_sem_create("erase", 0, RT_IPC_FLAG_FIFO);                
	rt_thread_t erase_id = RT_NULL;//�߳̾��
	erase_id = rt_thread_create("erase_task",erase_task, NULL, 1024, 16,20);
	if(erase_id != NULL)
	{
		rt_thread_startup(erase_id);
	}
	
	
    while (1)
    {

        /* ����һ���ͻ�������socket�����������������������ʽ�� */
        connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);
        /* ���ص������ӳɹ���socket */
        if (connected < 0)
        {
            rt_kprintf("accept connection failed! errno = %d\n", errno);
            continue;
        }

        /* �ͻ������ӵĴ��� */
        while (1)
        {
			if(fileLen == 0)
			{
				ret = frame_consultation(connected, data_buff);
				if(ret == 0)
				{
					break;
				}
			}
			else
			{
				ret = frame_handler(connected, data_buff);
				if(ret == 0)
				{
					break;
				}
			}

			if(ret)
			{
				ret = send(connected, data_buff, ret , 0);
				 if (ret < 0)
				{
					/* ����ʧ�ܣ��ر�������� */
					closesocket(connected);
					rt_kprintf("\nsend error,close the socket.\r\n");
					break;
				}
				else if (ret == 0)
				{
					/* ��ӡsend��������ֵΪ0�ľ�����Ϣ */
	//                rt_kprintf("\n Send warning,send function return 0.\r\n");
				}	
			}
        }
    }

    /* �˳����� */
    closesocket(sock);

    return ;
}

void load_server_init(void)
{
	 rt_thread_t tid;
	
	tid = rt_thread_create("load", tcpserv, RT_NULL, 2048, 6, 20);
	if (tid != RT_NULL) 
	{
		rt_thread_startup(tid);
	}
	return ;
}



