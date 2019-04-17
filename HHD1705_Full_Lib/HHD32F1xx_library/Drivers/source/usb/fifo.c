/****************************************

  fifo.c
  FIFO access routines for MUSBFSFC firmware

  Copyright Mentor Graphics Corporation and Licensors 2000
  V1.0  4 September 2000

 $Log: fifo.c,v $
 Revision 1.3  2001/05/31
 CVS Log Added


****************************************/
#include "musbfsfc.h"



/****************************************
  FIFORead
****************************************/
void FIFORead (int nEP, int nBytes, void * pDst)
{
int     nCount;
BYTE *  pby;
int     nAddr;

if (nBytes) {
  nAddr = M_FIFO_EP0+nEP;
  nCount = nBytes;
  pby = (BYTE *)pDst;
  while (nCount) {
    *pby++ = *((BYTE *)nAddr);
    nCount--;
    }
  }

return;
}


/****************************************
  FIFOWrite
****************************************/
void FIFOWrite (int nEP, int nBytes, void * pSrc)
{
int     nCount;
BYTE *  pby;
int     nAddr;

if (nBytes) {
  nAddr = M_FIFO_EP0+nEP;
  nCount = nBytes;
  pby = (BYTE *)pSrc;
  while (nCount) {
   *((BYTE *)nAddr) = *pby++;
    nCount--;
    }
  }

return;
}
