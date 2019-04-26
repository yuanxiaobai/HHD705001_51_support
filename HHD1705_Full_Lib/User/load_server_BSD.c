/*******************************************************************************************************
  * Company: Hiwafer Technology Co., Ltd.
  ******************************************************************************************************
  * 文件名称：load_server_BSD.c
  * 功能说明：
  * 版    本：V2.0
  * 作    者：EnderWigg	
  * 日    期：2019.4.20
  *
  * 该文件用于配置库文件相关功能
*******************************************************************************************************/
#include <rtthread.h>
#include "lwip/sockets.h" /* 使用BSD socket，需要包含socket.h头文件 */
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
 * @brief Flash 擦除任务

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
			/* 发送失败，关闭这个连接 */
			closesocket(connected);
			rt_kprintf("\nsend error,close the socket.\r\n");
			break;
		}
		else if (ret == 0)
		{
			/* 打印send函数返回值为0的警告信息 */
//                rt_kprintf("\n Send warning,send function return 0.\r\n");
		}	

	}
}
 

/**
 * @brief 协商下载信息
 *
 * @param socket 连接描述符
 * @param 数据缓存区
 * @return 将要发送出去的数据长度，如果返回0 则出错
*/
int frame_consultation(int fd, uint8_t *data)
{
	int32_t ret = 0;
	uint32_t lp_fpga = 0;
	
	ret = recv(fd, data, 8, 0);
	if (ret <= 0)
	{
		/* 接收失败，关闭这个connected socket */
		closesocket(fd);
		fileLen = 0;
		return 0;
	}
	
	if(memcmp(data, "getinfo:", 8) == 0)
	{
		((uint16_t *)data)[0] = MAX_PACKAGE_LEN;	    //缓冲区大小
		((uint16_t *)data)[1] = 8;				        //数据对其
		
		return 4;
	}
	else if(memcmp(data, "fileinfo", 8) == 0)
	{
		ret = recv(fd, data, 13, 0);
		if (ret <= 0)
		{
			/* 接收失败，关闭这个connected socket */
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
 * @brief 文件下载处理
 *
 * @param socket 连接描述符
 * @param 数据缓存区
 * @return 将要发送出去的数据长度，如果返回0 则出错
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
		/* 接收失败，关闭这个connected socket */
		closesocket(fd);
		fileLen = 0;
		return 0;
	}
	
	if(*(uint32_t *)data == 0x21212121)    //"!!!!"
	{
											//提示接收端，放弃已接收的数据
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
				/* 接收失败，关闭这个connected socket */
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
	
	
    /* 一个socket在使用前，需要预先创建出来，指定SOCK_STREAM为TCP的socket */
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        /* 创建失败的错误处理 */
        rt_kprintf("Socket error\n");

        
        return;
    }

    /* 初始化服务端地址 */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SPI_PORT); /* 服务端工作的端口 */
    server_addr.sin_addr.s_addr = INADDR_ANY;
	
  
    /* 绑定socket到服务端地址 */
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        /* 绑定失败 */
        rt_kprintf("Unable to bind\n");
        return;
    }

    /* 在socket上进行监听 */
    if (listen(sock, 1) == -1)
    {
        rt_kprintf("Listen error\n");
        return;
    }
	
	sin_size = sizeof(struct sockaddr_in);
	
	erase_sem = rt_sem_create("erase", 0, RT_IPC_FLAG_FIFO);                
	rt_thread_t erase_id = RT_NULL;//线程句柄
	erase_id = rt_thread_create("erase_task",erase_task, NULL, 1024, 16,20);
	if(erase_id != NULL)
	{
		rt_thread_startup(erase_id);
	}
	
	
    while (1)
    {

        /* 接受一个客户端连接socket的请求，这个函数调用是阻塞式的 */
        connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);
        /* 返回的是连接成功的socket */
        if (connected < 0)
        {
            rt_kprintf("accept connection failed! errno = %d\n", errno);
            continue;
        }

        /* 客户端连接的处理 */
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
					/* 发送失败，关闭这个连接 */
					closesocket(connected);
					rt_kprintf("\nsend error,close the socket.\r\n");
					break;
				}
				else if (ret == 0)
				{
					/* 打印send函数返回值为0的警告信息 */
	//                rt_kprintf("\n Send warning,send function return 0.\r\n");
				}	
			}
        }
    }

    /* 退出服务 */
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



