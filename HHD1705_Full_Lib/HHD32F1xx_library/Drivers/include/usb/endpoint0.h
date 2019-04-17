/****************************************

  endpoint0.h
  Endpoint 0 header file for MUSBFSFC firmware

  Copyright Mentor Graphics Corporation and Licensors 2000
  V1.0  4 September 2000

 $Log: endpoint0.h,v $
 Revision 1.3  2001/05/31
 CVS Log Added


****************************************/

#ifndef _ENDPOINT0_H_
#define _ENDPOINT0_H_


/* Endpoint 0 states */
#define M_EP0_IDLE      0
#define M_EP0_RX        1
#define M_EP0_TX        2

/* Endpoint 0 status structure */
typedef struct M_EP0_STATUS {
  int   nState;         /* IDLE/RX/TX */
  int   nBytesLeft;     /* Number of bytes left to send in TX mode */
  void *pData;          /* Pointer to data to transmit/receive */
  int   nBytesRecv;     /* Number of bytes received in RX mode */
  BYTE  byFAddr;        /* New function address */
  } M_EP0_STATUS;
typedef M_EP0_STATUS * PM_EP0_STATUS;

#endif /* _ENDPOINT0_H_ */

