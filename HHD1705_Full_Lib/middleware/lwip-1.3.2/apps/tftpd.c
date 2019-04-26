#include <rtthread.h>
#include <dfs_posix.h>
#include <lwip/sockets.h>

//#include <finsh.h>
#include "Gpio_IO.h"
#include "g32f10x_conf.h"

#define TFTP_PORT	69
#define NEW_PORT	0
/* opcode */
#define TFTP_RRQ			1 	/* read request */
#define TFTP_WRQ			2	/* write request */
#define TFTP_DATA			3	/* data */
#define TFTP_ACK			4	/* ACK */
#define TFTP_ERROR			5	/* error */



int request_handler(char *data, int *len, int *fdd)
{
	static int fd  = -1;
	static int rw_flag = 0;
	int ret = 0;
	int temp = 0;
	static int block_number = 0;

	if((data != NULL) && (*len > 0))
	{
		switch(data[1])
		{
			case TFTP_RRQ:
				block_number = 1;
			
				rt_kprintf("%s\n",&data[2]);
				fd = open(&data[2], O_RDONLY, 0);
				if (fd < 0)
				{
					rt_kprintf("can't open local filename\n");
					return -1;
				}
				data[1] = TFTP_DATA;
				data[2] = ((block_number >> 8) & 0xff); 
				data[3] = (block_number & 0xff);
				*len = read(fd, (char*)&data[4], 512);

				*len += 4;
				*fdd = fd;
				rw_flag = TFTP_RRQ;
				rt_kprintf("#");
			return 6;


			case TFTP_WRQ:
				block_number = 0;
				fd = open(&data[2], O_RDWR | O_CREAT, 0);
				if (fd < 0)
				{
					rt_kprintf("can't open local filename\n");
					return -1;
				}
				data[1] = TFTP_ACK;
				data[2] = ((block_number >> 8) & 0xff); 
				data[3] = (block_number & 0xff);
				*len = 4;
				rw_flag = TFTP_WRQ;
				*fdd = fd;
			return 6;
		

			case TFTP_DATA:	
				
			temp = ((data[2] << 8)|(data[3]));
			if(temp == (block_number+1))
			{
				write(fd, (char*)&data[4], *len - 4);
			}
			block_number++;
			rt_kprintf("#");
			if(*len < 512)
			{
				close(fd);
				rt_kprintf("\n");
				ret = 6;
			}
			
			data[1] = TFTP_ACK;
			data[2] = ((block_number >> 8) & 0xff); 
			data[3] = (block_number & 0xff);
			*len = 4;
			
			return ret;
				
			case TFTP_ACK:

				if(rw_flag == TFTP_RRQ)
				{
					temp = ((data[2] << 8)|(data[3]));
					if(temp == block_number)
					{
						*len = read(fd, (char*)&data[4], 512);
					}
					block_number++;

					data[1] = TFTP_DATA;
					data[2] = ((block_number >> 8) & 0xff); 
					data[3] = (block_number & 0xff);
					rt_kprintf("#");
					if(*len < 512)
					{
						close(fd);
						rt_kprintf("\n");
						ret = TFTP_DATA;	
					}
					*len += 4;
					
					return 0;
				}

			break;

			case TFTP_ERROR:
				rt_kprintf("ERROR :error code %d ,%s\n",((data[2] << 8)|(data[3])),(data+4));
				close(fd);
				ret = -1;
			break;
			
		}
	}
	
	return ret ;
}



int create_new_sock(int port)
{
	int sock_fd = 0;
	int ret = 0;
//	int sock_opt = 20000; /* 20 seconds */
	struct sockaddr_in tftp_addr; 
	
	/* connect to tftp server */
	tftp_addr.sin_addr.s_addr=INADDR_ANY;
	tftp_addr.sin_family = AF_INET;
	tftp_addr.sin_port = htons(port);

	sock_fd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (sock_fd < 0)
	{
		lwip_close(sock_fd);
		rt_kprintf("can't create a socket\n");
	return -1;
	}
	/* set socket option */

//	lwip_setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, &sock_opt, sizeof(sock_opt));	
	ret = bind(sock_fd, (struct sockaddr *) &tftp_addr, sizeof(struct sockaddr_in));
	if ( ret < 0)
	{
		close(sock_fd);
		rt_kprintf("can't create a socket\n");
		return -1;
	}
	return sock_fd;
}

char tftp_buffer[512 + 4];
void tftpd(void *argv)
{
	int ret = 0;
	int fd = -1;
	int sock_fd = -1;
	int sock_new = -1;
	struct sockaddr_in from_addr;
	int length = 0;
	
	
	socklen_t fromlen = sizeof(struct sockaddr);

	sock_fd = create_new_sock(TFTP_PORT);
	
	while(1)
	{
		GPIO_ResetPin(GPIOE, PIN2);
		length = lwip_recvfrom(sock_fd, tftp_buffer, sizeof(tftp_buffer), 0, 
			(struct sockaddr *)&from_addr, &fromlen);
		
		if(length == 0)
		{
			GPIO_SetPin(GPIOE, PIN2);
			lwip_close(sock_fd);
			return ;
		}
		
		ret = request_handler(tftp_buffer, &length, &fd);
		if(ret >= 6)
		{
			sock_new = create_new_sock(NEW_PORT);
		}
		else if(ret < 0)
		{
			break;		
		}
		lwip_sendto(sock_new, tftp_buffer, length, 0, (struct sockaddr *)&from_addr, fromlen);
		
		while(1)
		{

			length = lwip_recvfrom(sock_new, tftp_buffer, sizeof(tftp_buffer), 0, 
			(struct sockaddr *)&from_addr, &fromlen);
			if(length == 0)
			{
				close(fd);
				lwip_close(sock_new);
				break;
			}
			ret = request_handler(tftp_buffer, &length, &fd);
			if(ret < 0)
			{
				lwip_close(sock_new);
				
				break;
			}
			
			lwip_sendto(sock_new, tftp_buffer, length, 0, (struct sockaddr *)&from_addr, fromlen);

			if(ret == TFTP_DATA)
			{
				sock_new = -1;
				lwip_close(sock_new);

				break;
			}
		}
	}
	
	close(fd);
	lwip_close(sock_new);
	lwip_close(sock_fd);
}

int tftpd_start(void)
{
	rt_thread_t tid;

    tid = rt_thread_create("tftpd",
        tftpd, RT_NULL,
        1024, 15, 20);
    if (tid != RT_NULL) rt_thread_startup(tid);
	return 0;
}
 


#ifdef RT_USING_FINSH
#include <finsh.h>

MSH_CMD_EXPORT(tftpd_start, start tftp server)
#endif




