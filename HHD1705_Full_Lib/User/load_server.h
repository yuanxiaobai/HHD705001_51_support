#ifndef __LOADSERVER_H__
#define __LOADSERVER_H__


#define CMD_CANCEL 		0x21212121  /* ȡ������ָ�� */

#define STATE_ERASE_START		0x88    /* ��ʼFlash ����*/
#define STATE_VERIFY_ERR		0x00    /* FlashУ����� */
#define START_FRAME_ERR			0x01	/* ֡���д��� */



enum tcp_work_states
{
  ES_GETINFO = 3,
  ES_FILEINFO,
  ES_SENDDATA,
  ES_CANCEL,

};

void load_server_init(void);


#endif

