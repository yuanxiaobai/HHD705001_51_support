#ifndef __LOADSERVER_H__
#define __LOADSERVER_H__


#define CMD_CANCEL 		0x21212121  /* 取消操作指令 */

#define STATE_ERASE_START		0x88    /* 开始Flash 擦除*/
#define STATE_VERIFY_ERR		0x00    /* Flash校验错误 */
#define START_FRAME_ERR			0x01	/* 帧序列错误 */



enum tcp_work_states
{
  ES_GETINFO = 3,
  ES_FILEINFO,
  ES_SENDDATA,
  ES_CANCEL,

};

void load_server_init(void);


#endif

