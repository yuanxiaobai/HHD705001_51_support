#ifndef __LOADSERVER_H__
#define __LOADSERVER_H__




enum tcp_work_states
{
  ES_GETINFO = 3,
  ES_FILEINFO,
  ES_SENDDATA,
  ES_CANCEL,

};

void load_server_init(void);


#endif

