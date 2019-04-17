/****************************************

  reset.c
  Reset interrupt routine for MUSBFSFC firmware

  Copyright Mentor Graphics Corporation and Licensors 2000
  V1.0  4 September 2000

 $Log: reset.c,v $
 Revision 1.3  2001/05/31
 CVS Log Added


****************************************/
#include "musbfsfc.h"
#include "endpoint.h"

extern int      gnDevState;

extern M_EPBIN_STATUS   gepbin1, gepbin2;
extern M_EPBOUT_STATUS  gepbout1, gepbout2;


/****************************************
  USB Reset
****************************************/
void USBReset ()
{

/* Set device into default state */
gnDevState = DEVSTATE_DEFAULT;

/* Initialise descriptors */
InitialiseDesc ();

/* Reset any state machines for each endpoint */
/* This example assumes 2 bulk IN endpoints with endpoint numbers 1,2, */
/* and 2 bulk out endpoints with endpoint numbers 1,2 */
Endpoint0 (M_EP_RESET);

/* Initialise endpoint status structures with endpoint numbers */
gepbin1.byEP = 1;
gepbin2.byEP = 2;
gepbout1.byEP = 1;
gepbout2.byEP = 2;

EndpointBulkIn (&gepbin1, M_EP_RESET);
EndpointBulkIn (&gepbin2, M_EP_RESET);
EndpointBulkOut (&gepbout1, M_EP_RESET);
EndpointBulkOut (&gepbout2, M_EP_RESET);

return;
}
