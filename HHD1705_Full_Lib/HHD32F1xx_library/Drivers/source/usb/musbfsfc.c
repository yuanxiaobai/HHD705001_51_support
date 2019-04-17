/****************************************

  musbfsfc.c
  Interrupt handler for MUSBFSFC firmware

  Copyright Mentor Graphics Corporation and Licensors 2000
  V1.0  4 September 2000

 $Log: musbfsfc.c,v $
 Revision 1.3  2001/05/31
 CVS Log Added


****************************************/
#include "musbfsfc.h"
#include "descript.h"
#include "config.h"
#include "endpoint.h"

/* Device descriptor is global */
STD_DEV_DSCR            stddevdsc;

/* Configuration structures as defined in config.h */
M_CFG_1 cfg1;
M_CFG_2 cfg2;
M_CFG   cfg;

/* Current device state */
int             gnDevState = DEVSTATE_DEFAULT;

/* Pointer to current configuration descriptor */
void *          gpCurCfg = NULL;

/* Pointer to current interface descriptors */
PSTD_IF_DSCR    gpCurIf[M_MAXIFS];

/* Current alternate interface values */
BYTE            gbyCurIfVal[M_MAXIFS];

/* Status for 2 Bulk In endpoints */
M_EPBIN_STATUS  gepbin1, gepbin2;

/* Status for 2 Bulk Out endpoints */
M_EPBOUT_STATUS gepbout1, gepbout2;


/****************************************
  Top level interrupt handler
****************************************/
void USB_IRQHandler ()
{
BYTE    IntrUSB;
WORD    IntrIn;
WORD    IntrOut;

/* Read interrupt registers */
/* Mote if less than 8 IN endpoints are configured then */
/* only M_REG_INTRIN1 need be read. */
/* Similarly if less than 8 OUT endpoints are configured then */
/* only M_REG_INTROUT1 need be read. */
IntrUSB = MREAD_BYTE(M_REG_INTRUSB);
IntrIn  = (WORD)MREAD_BYTE(M_REG_INTRIN2);
IntrIn <<= 8;
IntrIn  |= (WORD)MREAD_BYTE(M_REG_INTRIN1);
IntrOut  = (WORD)MREAD_BYTE(M_REG_INTROUT2);
IntrOut <<= 8;
IntrOut  |= (WORD)MREAD_BYTE(M_REG_INTROUT1);

/* Check for resume from suspend mode */
/*
Add call to resume routine here
if (IntrUSB & M_INTR_RESUME) USBResume();
*/

/* Check for system interrupts */
if (IntrUSB & M_INTR_RESET) USBReset();

/* Check for endpoint 0 interrupt */
if (IntrIn & M_INTR_EP0) Endpoint0 (M_EP_NORMAL);

/* Check for each configured endpoint interrupt */
/* This example assumes 2 bulk IN endpoints with endpoint numbers 1,2, */
/* and 2 bulk out endpoints with endpoint numbers 1,2 */
if (IntrIn & 2) EndpointBulkIn (&gepbin1, M_EP_NORMAL);
if (IntrIn & 4) EndpointBulkIn (&gepbin2, M_EP_NORMAL);
if (IntrOut & 2) EndpointBulkOut (&gepbout1, M_EP_NORMAL);
if (IntrOut & 4) EndpointBulkOut (&gepbout2, M_EP_NORMAL);

/* Check for suspend mode */
/*
Add call to suspend routine here
if (IntrUSB & M_INTR_RESUME) USBSuspend();
*/

return;
}
