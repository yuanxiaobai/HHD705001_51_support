/****************************************

  endpoint.h
  Endpoint header file for MUSBFSFC firmware

  Copyright Mentor Graphics Corporation and Licensors 2000
  V1.0  4 September 2000

 $Log: endpoint.h,v $
 Revision 1.3  2001/05/31
 CVS Log Added


****************************************/

#ifndef _ENDPOINT_H_
#define _ENDPOINT_H_


#define M_EP_NODATA     -1

/* Define maximum packet size for bulk endpoints */
#define M_EP_MAXP       64


/* Bulk In Endpoint status structure */
typedef struct M_EPBIN_STATUS {
  void *pData;          /* Pointer to data to transmit */
  int   nBytesLeft;     /* Number of bytes left to send */
  BYTE  byEP;           /* Endpoint number */
  } M_EPBIN_STATUS;
typedef M_EPBIN_STATUS * PM_EPBIN_STATUS;

/* Bulk Out Endpoint status structure */
typedef struct M_EPBOUT_STATUS {
  void *pData;          /* Pointer to data buffer */
  int   nBuffLen;       /* Length of data buffer */
  int   nBytesRecv;     /* Number of bytes received */
  BYTE  byEP;           /* Endpoint number */
  } M_EPBOUT_STATUS;
typedef M_EPBOUT_STATUS * PM_EPBOUT_STATUS;

/* Function prototypes */
void EndpointBulkIn (PM_EPBIN_STATUS, int);
void EndpointBulkOut (PM_EPBOUT_STATUS, int);

#endif /* _ENDPOINT_H_ */

