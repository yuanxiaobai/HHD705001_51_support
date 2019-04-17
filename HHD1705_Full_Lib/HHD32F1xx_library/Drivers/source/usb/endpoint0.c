/****************************************

  endpoint0.c
  Endpoint 0 interrupt routine for MUSBFSFC firmware

  Copyright Mentor Graphics Corporation and Licensors 2000
  V1.0  4 September 2000

 $Log: endpoint0.c,v $
 Revision 1.5  2001/09/07
 Dataend for no data commands

 Revision 1.4  2001/07/26
  MaxP value rounded up

 Revision 1.3  2001/05/31
 CVS Log Added

****************************************/
#include "musbfsfc.h"
#include "endpoint0.h"
#include "descript.h"
#include "config.h"

extern STD_DEV_DSCR	stddevdsc;

/* Add configuration structures as defined in config.h */
extern M_CFG_1  cfg1;
extern M_CFG_2  cfg2;
extern M_CFG	cfg;

/* Global status */
extern int		gnDevState;
extern void *		gpCurCfg;
extern PSTD_IF_DSCR	gpCurIf[M_MAXIFS];
extern BYTE		gbyCurIfVal[M_MAXIFS];


/* Local functions */
void Endpoint0_Command (PM_EP0_STATUS, PCOMMAND);
void Endpoint0_Tx (PM_EP0_STATUS);
void StdDevReq (PM_EP0_STATUS, PCOMMAND);
int ConfigureIfs (void);


/****************************************
  Endpoint 0 interrupt service routine
****************************************/
void Endpoint0 (int nCallState)
{
static M_EP0_STATUS	ep0state;
static COMMAND		cmd;
BYTE			byCSR0;

/* Check for USB reset of endpoint 0 */
if (nCallState == M_EP_RESET) {
  ep0state.nState = M_EP0_IDLE;
  ep0state.byFAddr = 0xFF;
  /* Clear current configuration pointer */
  gpCurCfg = NULL;
  return;
  }

/* Read CSR0 */
MWRITE_BYTE(M_REG_INDEX, 0);
byCSR0 = MREAD_BYTE(M_REG_CSR0);

/* Check for status stage of a request */
if (!(byCSR0 & M_CSR0_OUTPKTRDY)) {
  /* Complete SET_ADDRESS command */
  if (ep0state.byFAddr != 0xFF) {
    MWRITE_BYTE(M_REG_FADDR, ep0state.byFAddr);
    if ((gnDevState == DEVSTATE_DEFAULT) && ep0state.byFAddr)
      gnDevState = DEVSTATE_ADDRESS;
    else if ((gnDevState == DEVSTATE_ADDRESS) && !ep0state.byFAddr)
      gnDevState = DEVSTATE_DEFAULT;
    }
  }
/* Clear pending commands */
ep0state.byFAddr = 0xFF;

/* Check for SentStall */
if (byCSR0 & M_CSR0_SENTSTALL) {
  MWRITE_BYTE(M_REG_CSR0, (byCSR0 & ~M_CSR0_SENDSTALL));
  ep0state.nState = M_EP0_IDLE;
  }

/* Check for SetupEnd */
if (byCSR0 & M_CSR0_SETUPEND) {
  MWRITE_BYTE(M_REG_CSR0, (byCSR0 | M_CSR0_SVDSETUPEND));
  ep0state.nState = M_EP0_IDLE;
  }

/* Call relevant routines for endpoint 0 state */

if (ep0state.nState == M_EP0_IDLE) {
  /* If no packet has been received, */
  /* assume that this was a STATUS phase complete. */
  /* Otherwise load new command */
  if (byCSR0 & M_CSR0_OUTPKTRDY) {
    /* Read the 8-byte command from the FIFO */
    /* There is no need to check that OutCount is set to 8 */
    /* as the MUSBFSFC will reject SETUP packets that are not 8 bytes long. */
    FIFORead (0, 8, &cmd);
    Endpoint0_Command (&ep0state, &cmd);
    }
  }
if (ep0state.nState == M_EP0_TX)
  Endpoint0_Tx(&ep0state);


return;
}


/****************************************
  Endpoint 0 command
  This routine is called when a command has been received in the SETUP phase.
****************************************/
void Endpoint0_Command (PM_EP0_STATUS pep0state, PCOMMAND pcmd)
{
BYTE	byType;

/* Check request type */
switch (byType = pcmd->bmRequestType & M_CMD_TYPEMASK) {

  case M_CMD_STDREQ:
    StdDevReq (pep0state, pcmd);
    break;

  case M_CMD_CLASSREQ:
    /* Add call to external routine for handling class requests */

  case M_CMD_VENDREQ:
    /* Add call to external routine for handling vendor requests */

  default:
    /* Stall the command if a reserved request is received */
    MWRITE_BYTE(M_REG_CSR0, M_CSR0_SVDOUTPKTRDY | M_CSR0_SENDSTALL);
    break;
  }

return;
}


/****************************************
  Standard Device Request
  This routine is called when a standard device request has been received.
  The bRequest field of the received command is decoded.
****************************************/
void StdDevReq (PM_EP0_STATUS pep0state, PCOMMAND pcmd)
{
int		bError = FALSE, bNoData = FALSE, n;
BYTE		by;
BYTE		byConfig;
PSTD_CFG_DSCR	pcfg;
BYTE *		*ppby;

switch (pcmd->bRequest) {

  case SET_ADDRESS:
    /* Store device function address until status stage of request */
    if (pcmd->bmRequestType != M_CMD_STDDEVOUT)
      bError = TRUE;
    else if (gnDevState <= DEVSTATE_ADDRESS) {
      pep0state->byFAddr = (BYTE)pcmd->wValue;
      bNoData = TRUE;
      }
    else
      bError = TRUE;
    break;

  case GET_DESCRIPTOR:
    /* Decode the required descriptor from the command */
    if (pcmd->bmRequestType != M_CMD_STDDEVIN)
      bError = TRUE;
    else {
      switch (pcmd->wValue & M_CMD_DESCMASK) {
	case M_CMD_DEVICE:
	  /* Prepare to return Standard Device Descriptor */
	  pep0state->nBytesLeft = sizeof(STD_DEV_DSCR);
	  /* Check host is allowing a descriptor this long */
	  if (pcmd->wLength < pep0state->nBytesLeft)
	    pep0state->nBytesLeft = pcmd->wLength;
	  pep0state->pData = (void*)&stddevdsc;
	  pep0state->nState = M_EP0_TX;
	  break;
	case M_CMD_DEVQUAL:
	  /* No alternate speed supported */
	  bError = TRUE;
	  break;
	case M_CMD_CONFIG:
	  byConfig = (BYTE)(pcmd->wValue & 0x00FF);
	  if (byConfig >= stddevdsc.bNumConfigurations)
	    bError = TRUE;
	  else {
	    /* Get pointer to requested configuration descriptor */
	    ppby = (BYTE**)&cfg;
	    ppby += byConfig;
	    pcfg = (PSTD_CFG_DSCR)*ppby;
	    /* Prepare to return Configuration Descriptors */
	    pep0state->nBytesLeft = (int)pcfg->wTotalLength;
	    pep0state->pData = (void*)pcfg;
	    pep0state->nState = M_EP0_TX;
	    /* Check host is allowing a descriptor this long */
	    if (pcmd->wLength < pep0state->nBytesLeft)
	      pep0state->nBytesLeft = pcmd->wLength;
	    }
	  break;
	case M_CMD_OTHERSPEED:
	  /* No alternate speed supported */
	  bError = TRUE;
	  break;
	default: bError = TRUE;
	}
      }
    break;

  case SET_CONFIGURATION:
    byConfig = (BYTE)(pcmd->wValue & 0x00FF);
    if (gnDevState == DEVSTATE_DEFAULT)
      bError = TRUE;
    /* Assumes configurations are numbered 1 to NumConfigurations */
    else if (byConfig > stddevdsc.bNumConfigurations)
      bError = TRUE;
    else if (!byConfig)
      gnDevState = DEVSTATE_ADDRESS;
    else {
      /* Get pointer to requested configuration descriptor */
      ppby = (BYTE**)&cfg;
      ppby += byConfig-1;
      gpCurCfg = (void *)*ppby;
      /* Set all alternate settings to zero */
      for (n=0; n<M_MAXIFS; n++)
	gbyCurIfVal[n] = 0;
      /* Configure endpoints */
      ConfigureIfs ();
      gnDevState = DEVSTATE_CONFIG;
      MWRITE_BYTE(M_REG_INDEX, 0);
      bNoData = TRUE;
      }
    break;

  case SET_INTERFACE:
    if (gnDevState > DEVSTATE_ADDRESS) {
      n = (int)pcmd->wIndex;
      pcfg = (PSTD_CFG_DSCR)gpCurCfg;
      if ((BYTE)n >= pcfg->bNumInterfaces)
	bError = TRUE;
      else {
	gbyCurIfVal[n] = (BYTE)pcmd->wValue;
	if (ConfigureIfs() == FALSE)
	  bError = TRUE;
	MWRITE_BYTE(M_REG_INDEX, 0);
	bNoData = TRUE;
	}
      }
    else
      bError = TRUE;
    break;

  case GET_CONFIGURATION:
    if ((gnDevState == DEVSTATE_ADDRESS) && (!pcmd->wValue)) {
      /* Prepare to return zero */
      pep0state->nBytesLeft = 1;
      pep0state->pData = (void*)&pcmd->wValue;
      pep0state->nState = M_EP0_TX;
      }
    else if (gnDevState > DEVSTATE_ADDRESS) {
      /* Prepare to return configuration value */
      pcfg = (PSTD_CFG_DSCR)gpCurCfg;
      pep0state->nBytesLeft = 1;
      pep0state->pData = (void*)&pcfg->bConfigurationValue;
      pep0state->nState = M_EP0_TX;
      }
    else
      bError = TRUE;
    break;

  case GET_INTERFACE:
    if (gnDevState > DEVSTATE_ADDRESS) {
      n = (int)pcmd->wIndex;
      pcfg = (PSTD_CFG_DSCR)gpCurCfg;
      if ((BYTE)n >= pcfg->bNumInterfaces)
	bError = TRUE;
      else {
        /* Prepare to return interface value */
        pep0state->nBytesLeft = 1;
        pep0state->pData = (void*)&gpCurIf[n]->bInterfaceNumber;
        pep0state->nState = M_EP0_TX;
	}
      }
    else
      bError = TRUE;
    break;

  case SET_FEATURE:
    switch (pcmd->bmRequestType) {
      case M_CMD_STDDEVOUT:
	switch (pcmd->wValue) {
	  case M_FTR_DEVREMWAKE:
	  default:
	    bError = TRUE;
	    break;
	  }
	break;
      case M_CMD_STDIFIN:
	/* Add interface features here */
      case M_CMD_STDEPIN:
	/* Add endpoint features here */
      default:
	bError = TRUE;
	break;
      }
    break;

  default:
    /* Stall the command if an unrecognized request is received */
    bError = TRUE;
    break;
  }

/* Stall command if an error occurred */
if (bError)
  by = M_CSR0_SVDOUTPKTRDY | M_CSR0_SENDSTALL;
else if (bNoData)
  by = M_CSR0_SVDOUTPKTRDY | M_CSR0_DATAEND;
else
  by = M_CSR0_SVDOUTPKTRDY;
MWRITE_BYTE(M_REG_CSR0, by);

return;
}


/****************************************
  Endpoint 0 Tx
  This routine is called when data is to be sent to the host.
****************************************/
void Endpoint0_Tx (PM_EP0_STATUS pep0state)
{
int	nBytes;
BYTE	by;

/* Determine number of bytes to send */
if (pep0state->nBytesLeft <= M_EP0_MAXP) {
  nBytes = pep0state->nBytesLeft;
  pep0state->nBytesLeft = 0;
  }
else {
  nBytes = M_EP0_MAXP;
  pep0state->nBytesLeft -= M_EP0_MAXP;
  }

FIFOWrite (0, nBytes, pep0state->pData);
pep0state->pData = (BYTE *)pep0state->pData + nBytes;
if (nBytes < M_EP0_MAXP) {
  by = M_CSR0_INPKTRDY | M_CSR0_DATAEND;
  pep0state->nState = M_EP0_IDLE;
  }
else
  by = M_CSR0_INPKTRDY;
MWRITE_BYTE(M_REG_CSR0, by);

return;
}


/****************************************
  ConfigureIfs
  This routine is called when a SET_CONFIGURATION or SET_INTERFACE
  command is received and will set the gpCurIF pointers
  to the selected interface descriptors and will set the
  maximum packet size and operating mode for the endpoints in
  the selected interfaces
****************************************/
int ConfigureIfs ()
{
PSTD_CFG_DSCR	pcfg;
BYTE		byIf, byAltIf, byEP, byNumEPs, by;
BYTE		*pby;
BYTE		*pbyIfVal;
PSTD_IF_DSCR	pif;
PSTD_EP_DSCR	pep;

/* Set pointer to first interface descriptor in current configuration */
pby = (BYTE *)gpCurCfg;
pby += sizeof(STD_CFG_DSCR);
pif = (PSTD_IF_DSCR)pby;

/* Loop through all interfaces in the current configuration */
pcfg = (PSTD_CFG_DSCR)gpCurCfg;
pbyIfVal = (BYTE*)&gbyCurIfVal;
for (byIf=0; byIf<pcfg->bNumInterfaces; byIf++, pbyIfVal++) {

  /* Advance pointer to selected alternate interface descriptor */
  if (*pbyIfVal) {
    for (byAltIf=0; byAltIf<*pbyIfVal; byAltIf++) {
      byNumEPs = pif->bNumEndpoints;
      pby += sizeof(STD_IF_DSCR) + byNumEPs * sizeof(STD_EP_DSCR);
      pif = (PSTD_IF_DSCR)pby;
      /* Check an alternate setting > number of alternates not specified */
      if (!pif->bAlternateSetting)
	return FALSE;
      } 
    }

  /* Store pointer to interface in global array */
  gpCurIf[byIf] = pif;

  /* Loop through all endpoints in interface */
  byNumEPs = pif->bNumEndpoints;
  pby += sizeof(STD_IF_DSCR);
  for (byEP=0; byEP<byNumEPs; byEP++) {
    pep = (PSTD_EP_DSCR)pby;

    /* Configure the endpoint */
    MWRITE_BYTE(M_REG_INDEX, (pep->bEndpointAddress & 0x0F));
    /* Round up max packet size to a multiple of 8 for writing to MaxP registers */
    by = (BYTE)((pep->wMaxPacketSize+7)>>3);
    if (pep->bEndpointAddress & 0x80) {
      MWRITE_BYTE(M_REG_INMAXP, by);
      by = MREAD_BYTE(M_REG_INCSR2);
      switch (pep->bmAttributes & M_EP_TFMASK) {
	case M_EP_ISO:
	  by |= M_INCSR2_ISO;
	  break;
	case M_EP_BULK:
	case M_EP_INTR:
	  by &= ~M_INCSR2_ISO;
	  break;
	}
      /* Set mode bit high (only strictly necessary if sharing a FIFO) */
      by |= M_INCSR2_MODE;
      MWRITE_BYTE(M_REG_INCSR2, by);
      /* Other configuration for an IN endpoint */
      /* e.g. AutoClr, DMA */
      /* should be added here */
      }
    else {
      MWRITE_BYTE(M_REG_OUTMAXP, by);
      by = MREAD_BYTE(M_REG_OUTCSR2);
      switch (pep->bmAttributes & M_EP_TFMASK) {
	case M_EP_ISO:
	  by |= M_OUTCSR2_ISO;
	  break;
	case M_EP_BULK:
	case M_EP_INTR:
	  by &= ~M_OUTCSR2_ISO;
	  break;
	}
      MWRITE_BYTE(M_REG_OUTCSR2, by);
      /* Other configuration for an OUT endpoint */
      /* e.g. AutoSet, DMA */
      /* should be added here */
      }
    pby += sizeof(STD_EP_DSCR);
    }

  /* Skip any alternate setting interfaces */
  pif = (PSTD_IF_DSCR)pby;
  while (pif->bAlternateSetting) {
    byNumEPs = pif->bNumEndpoints;
    pby += sizeof(STD_IF_DSCR) + byNumEPs * sizeof(STD_EP_DSCR);
    pif = (PSTD_IF_DSCR)pby;
    }
  }

return TRUE;
}
