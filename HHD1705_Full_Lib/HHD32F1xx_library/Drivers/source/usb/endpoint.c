/****************************************

  endpoint.c
  Endpoint interrupt routine for MUSBFSFC firmware

  Copyright Mentor Graphics Corporation and Licensors 2000
  V1.0  4 September 2000

 $Log: endpoint.c,v $
 Revision 1.5  2001/05/31
 CVS Log Added


****************************************/
#include "musbfsfc.h"
#include "endpoint.h"


/* Global status */
extern int              gnDevState;


/****************************************
  EndpointBulkIn service routine
  This routine provides simple handling for bulk in endpoints.
  Endpoint MaxP is defined in endpoint.h.
  While the nBytesLeft field of the pbostate structure is >= 0
  the endpoint will send packets of MaxP, with the residue in the last packet.
  If the data to send is an exact multiple of MaxP then a null data packet
  will be sent.
****************************************/
void EndpointBulkIn (PM_EPBIN_STATUS pbistate, int nCallState)
{
int     nBytes;
BYTE    byInCSR;

/* Reset endpoint */
if (nCallState == M_EP_RESET) {
  pbistate->nBytesLeft = M_EP_NODATA;
  MWRITE_BYTE(M_REG_INDEX, pbistate->byEP);
  byInCSR = M_INCSR_CDT | M_INCSR_FF;
  MWRITE_BYTE(M_REG_INCSR1, byInCSR);
  return;
  }

/* Check whether there is any data to send */ 
if (pbistate->nBytesLeft == M_EP_NODATA)
  return;

/* Determine number of bytes to send */
if (pbistate->nBytesLeft < M_EP_MAXP) {
  nBytes = pbistate->nBytesLeft;
  pbistate->nBytesLeft = M_EP_NODATA;
  }
else {
  nBytes = M_EP_MAXP;
  pbistate->nBytesLeft -= M_EP_MAXP;
  }

/* Load FIFO */
FIFOWrite ((int)pbistate->byEP, nBytes, pbistate->pData);
pbistate->pData = (BYTE *)pbistate->pData + nBytes;

MWRITE_BYTE(M_REG_INDEX, pbistate->byEP);
byInCSR = M_INCSR_IPR;
MWRITE_BYTE(M_REG_INCSR1, byInCSR);

return;
}


/****************************************
  EndpointBulkOut service routine
  This routine provides simple handling for bulk out endpoints.
  Endpoint MaxP is defined in endpoint.h.
  It assumes a transfer is complete when a packet of less than MaxP is received.
****************************************/
void EndpointBulkOut (PM_EPBOUT_STATUS pbostate, int nCallState)
{
int     nBytes;
BYTE    byOutCSR;

/* Reset endpoint */
if (nCallState == M_EP_RESET) {
  pbostate->nBytesRecv = 0;
  pbostate->nBuffLen = 0;
  MWRITE_BYTE(M_REG_INDEX, pbostate->byEP);
  byOutCSR = M_OUTCSR_CDT | M_OUTCSR_FF;
  MWRITE_BYTE(M_REG_OUTCSR1, byOutCSR);
  return;
  }

/* Set index register */
MWRITE_BYTE(M_REG_INDEX, pbostate->byEP);

/* Read OUT CSR register */
byOutCSR = MREAD_BYTE(M_REG_OUTCSR1);

/* Get packet, */
/* may need to unload more than one packet if double buffering enabled */
while (byOutCSR & M_OUTCSR_OPR) {

  /* Get packet size */
  nBytes = (int)MREAD_BYTE(M_REG_OUTCOUNT2);
  nBytes <<= 8;
  nBytes |= (int)MREAD_BYTE(M_REG_OUTCOUNT1);

  /* Check there is room in the buffer */
  if (pbostate->nBytesRecv + nBytes > pbostate->nBuffLen) {
    /* Call to function to handle buffer over run */
    MWRITE_BYTE(M_REG_OUTCSR1, 0);
    return;
    }

  /* Unload FIFO */
  FIFORead ((int)pbostate->byEP, nBytes, pbostate->pData);

  /* Update status */
  pbostate->nBytesRecv += nBytes;
  pbostate->pData = (BYTE *)pbostate->pData + nBytes;

  /* Check for end of transfer */
  if (nBytes < M_EP_MAXP) {
    /* Call function to handle received data */
    }

  /* Clear OutPktRdy */
  MWRITE_BYTE(M_REG_OUTCSR1, 0);

  /* Check for another packet */
  byOutCSR = MREAD_BYTE(M_REG_OUTCSR1);
  }

return;
}
