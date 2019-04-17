/****************************************

  desc.c
  Initialise descriptors for MUSBFSFC firmware.

  Copyright Mentor Graphics Corporation and Licensors 2000
  V1.0  4 September 2000

 $Log: desc.c,v $
 Revision 1.3  2001/05/31
 CVS Log Added


****************************************/
#include "musbfsfc.h"
#include "endpoint0.h"
#include "descript.h"
#include "config.h"

extern STD_DEV_DSCR     stddevdsc;

/* Add configuration structures as defined in config.h */
extern M_CFG_1  cfg1;
extern M_CFG_2  cfg2;
extern M_CFG    cfg;


/****************************************
  Initialise the descriptors
  This routine is called after a USB reset to set the descriptors.
****************************************/
void InitialiseDesc ()
{

/* Initialise the Standard Device Descriptor */
stddevdsc.bLength               = sizeof(STD_DEV_DSCR);
stddevdsc.bDescriptorType       = M_DST_DEVICE;
stddevdsc.bcdUSB                = 0x0200;       /* USB spec rev is 2.0 */
stddevdsc.bMaxPacketSize0       = M_EP0_MAXP;
stddevdsc.idVendor              = M_DEVDSC_VENDOR;
stddevdsc.idProduct             = M_DEVDSC_PRODUCT;
stddevdsc.bcdDevice             = M_DEVDSC_RELEASE;
stddevdsc.iManufacturer         = M_DEVDSC_MANUI;
stddevdsc.iProduct              = M_DEVDSC_PRODI;
stddevdsc.iSerialNumber         = M_DEVDSC_SERIALI;
stddevdsc.bDeviceClass          = M_DEVDSC_CLASS;
stddevdsc.bDeviceSubClass       = M_DEVDSC_SUBCLASS;
stddevdsc.bDeviceProtocol       = M_DEVDSC_PROTOCOL;
stddevdsc.bNumConfigurations    = M_DEVDSC_CONFIGS;


/* Initialise the descriptors for configuration 1 */
cfg.pcfg1 = &cfg1;
cfg1.stdcfg.bLength             = sizeof(STD_CFG_DSCR);
cfg1.stdcfg.bDescriptorType     = M_DST_CONFIG;
cfg1.stdcfg.wTotalLength        = sizeof(M_CFG_1);
cfg1.stdcfg.bNumInterfaces      = M_CFG1_NUMIFS;
cfg1.stdcfg.bConfigurationValue = 1;
cfg1.stdcfg.iConfiguration      = M_CFG1_CFGI;
cfg1.stdcfg.bmAttributes        = M_CFG1_ATTRIBUTES;
cfg1.stdcfg.bMaxPower           = M_CFG1_MAXPOWER;

/* .. Interface 0 */
cfg1.stdif00.bLength            = sizeof(STD_IF_DSCR);
cfg1.stdif00.bDescriptorType    = M_DST_INTERFACE;
cfg1.stdif00.bInterfaceNumber   = 0;
cfg1.stdif00.bAlternateSetting  = 0;
cfg1.stdif00.bNumEndpoints      = M_CFG1_I0A0_NUMEPS;
cfg1.stdif00.bInterfaceClass    = M_CFG1_I0A0_IFCLASS;
cfg1.stdif00.bInterfaceSubClass = M_CFG1_I0A0_IFSUBCLASS;
cfg1.stdif00.bInterfaceProtocol = M_CFG1_I0A0_IFPROTOCOL;
cfg1.stdif00.iInterface         = M_CFG1_I0A0_IFI;

/* .. Endpoints */
cfg1.stdep00_0.bLength          = sizeof(STD_EP_DSCR);
cfg1.stdep00_0.bDescriptorType  = M_DST_ENDPOINT;
cfg1.stdep00_0.bEndpointAddress = M_CFG1_I0A0_0_EPADDR;
cfg1.stdep00_0.bmAttributes     = M_CFG1_I0A0_0_ATTRIB;
cfg1.stdep00_0.wMaxPacketSize   = M_CFG1_I0A0_0_MAXP;
cfg1.stdep00_0.bInterval        = M_CFG1_I0A0_0_INTER;
cfg1.stdep00_1.bLength          = sizeof(STD_EP_DSCR);
cfg1.stdep00_1.bDescriptorType  = M_DST_ENDPOINT;
cfg1.stdep00_1.bEndpointAddress = M_CFG1_I0A0_1_EPADDR;
cfg1.stdep00_1.bmAttributes     = M_CFG1_I0A0_1_ATTRIB;
cfg1.stdep00_1.wMaxPacketSize   = M_CFG1_I0A0_1_MAXP;
cfg1.stdep00_1.bInterval        = M_CFG1_I0A0_1_INTER;

/* .. Interface 1, Alternate 0 */
cfg1.stdif10.bLength            = sizeof(STD_IF_DSCR);
cfg1.stdif10.bDescriptorType    = M_DST_INTERFACE;
cfg1.stdif10.bInterfaceNumber   = 1;
cfg1.stdif10.bAlternateSetting  = 0;
cfg1.stdif10.bNumEndpoints      = M_CFG1_I1A0_NUMEPS;
cfg1.stdif10.bInterfaceClass    = M_CFG1_I1A0_IFCLASS;
cfg1.stdif10.bInterfaceSubClass = M_CFG1_I1A0_IFSUBCLASS;
cfg1.stdif10.bInterfaceProtocol = M_CFG1_I1A0_IFPROTOCOL;
cfg1.stdif10.iInterface         = M_CFG1_I1A0_IFI;

/* .. Endpoints */
cfg1.stdep10_0.bLength          = sizeof(STD_EP_DSCR);
cfg1.stdep10_0.bDescriptorType  = M_DST_ENDPOINT;
cfg1.stdep10_0.bEndpointAddress = M_CFG1_I1A0_0_EPADDR;
cfg1.stdep10_0.bmAttributes     = M_CFG1_I1A0_0_ATTRIB;
cfg1.stdep10_0.wMaxPacketSize   = M_CFG1_I1A0_0_MAXP;
cfg1.stdep10_0.bInterval        = M_CFG1_I1A0_0_INTER;
cfg1.stdep10_1.bLength          = sizeof(STD_EP_DSCR);
cfg1.stdep10_1.bDescriptorType  = M_DST_ENDPOINT;
cfg1.stdep10_1.bEndpointAddress = M_CFG1_I1A0_1_EPADDR;
cfg1.stdep10_1.bmAttributes     = M_CFG1_I1A0_1_ATTRIB;
cfg1.stdep10_1.wMaxPacketSize   = M_CFG1_I1A0_1_MAXP;
cfg1.stdep10_1.bInterval        = M_CFG1_I1A0_1_INTER;

/* .. Interface 1, Alternate 1 */
cfg1.stdif11.bLength            = sizeof(STD_IF_DSCR);
cfg1.stdif11.bDescriptorType    = M_DST_INTERFACE;
cfg1.stdif11.bInterfaceNumber   = 1;
cfg1.stdif11.bAlternateSetting  = 1;
cfg1.stdif11.bNumEndpoints      = M_CFG1_I1A1_NUMEPS;
cfg1.stdif11.bInterfaceClass    = M_CFG1_I1A1_IFCLASS;
cfg1.stdif11.bInterfaceSubClass = M_CFG1_I1A1_IFSUBCLASS;
cfg1.stdif11.bInterfaceProtocol = M_CFG1_I1A1_IFPROTOCOL;
cfg1.stdif11.iInterface         = M_CFG1_I1A1_IFI;

/* .. Endpoints */
cfg1.stdep11_0.bLength          = sizeof(STD_EP_DSCR);
cfg1.stdep11_0.bDescriptorType  = M_DST_ENDPOINT;
cfg1.stdep11_0.bEndpointAddress = M_CFG1_I1A1_0_EPADDR;
cfg1.stdep11_0.bmAttributes     = M_CFG1_I1A1_0_ATTRIB;
cfg1.stdep11_0.wMaxPacketSize   = M_CFG1_I1A1_0_MAXP;
cfg1.stdep11_0.bInterval        = M_CFG1_I1A1_0_INTER;
cfg1.stdep11_1.bLength          = sizeof(STD_EP_DSCR);
cfg1.stdep11_1.bDescriptorType  = M_DST_ENDPOINT;
cfg1.stdep11_1.bEndpointAddress = M_CFG1_I1A1_1_EPADDR;
cfg1.stdep11_1.bmAttributes     = M_CFG1_I1A1_1_ATTRIB;
cfg1.stdep11_1.wMaxPacketSize   = M_CFG1_I1A1_1_MAXP;
cfg1.stdep11_1.bInterval        = M_CFG1_I1A1_1_INTER;


/* Initialise the descriptors for configuration 2 */
cfg.pcfg2 = &cfg2;
cfg2.stdcfg.bLength             = sizeof(STD_CFG_DSCR);
cfg2.stdcfg.bDescriptorType     = M_DST_CONFIG;
cfg2.stdcfg.wTotalLength        = sizeof(M_CFG_2);
cfg2.stdcfg.bNumInterfaces      = M_CFG2_NUMIFS;
cfg2.stdcfg.bConfigurationValue = 2;
cfg2.stdcfg.iConfiguration      = M_CFG2_CFGI;
cfg2.stdcfg.bmAttributes        = M_CFG2_ATTRIBUTES;
cfg2.stdcfg.bMaxPower           = M_CFG2_MAXPOWER;

/* .. Interface 0 */
cfg2.stdif00.bLength            = sizeof(STD_IF_DSCR);
cfg2.stdif00.bDescriptorType    = M_DST_INTERFACE;
cfg2.stdif00.bInterfaceNumber   = 0;
cfg2.stdif00.bAlternateSetting  = 0;
cfg2.stdif00.bNumEndpoints      = M_CFG2_I0A0_NUMEPS;
cfg2.stdif00.bInterfaceClass    = M_CFG2_I0A0_IFCLASS;
cfg2.stdif00.bInterfaceSubClass = M_CFG2_I0A0_IFSUBCLASS;
cfg2.stdif00.bInterfaceProtocol = M_CFG2_I0A0_IFPROTOCOL;
cfg2.stdif00.iInterface         = M_CFG2_I0A0_IFI;

/* .. Endpoints */
cfg2.stdep00_0.bLength          = sizeof(STD_EP_DSCR);
cfg2.stdep00_0.bDescriptorType  = M_DST_ENDPOINT;
cfg2.stdep00_0.bEndpointAddress = M_CFG2_I0A0_0_EPADDR;
cfg2.stdep00_0.bmAttributes     = M_CFG2_I0A0_0_ATTRIB;
cfg2.stdep00_0.wMaxPacketSize   = M_CFG2_I0A0_0_MAXP;
cfg2.stdep00_0.bInterval        = M_CFG2_I0A0_0_INTER;
cfg2.stdep00_1.bLength          = sizeof(STD_EP_DSCR);
cfg2.stdep00_1.bDescriptorType  = M_DST_ENDPOINT;
cfg2.stdep00_1.bEndpointAddress = M_CFG2_I0A0_1_EPADDR;
cfg2.stdep00_1.bmAttributes     = M_CFG2_I0A0_1_ATTRIB;
cfg2.stdep00_1.wMaxPacketSize   = M_CFG2_I0A0_1_MAXP;
cfg2.stdep00_1.bInterval        = M_CFG2_I0A0_1_INTER;

/* .. Interface 1, Alternate 0 */
cfg2.stdif10.bLength            = sizeof(STD_IF_DSCR);
cfg2.stdif10.bDescriptorType    = M_DST_INTERFACE;
cfg2.stdif10.bInterfaceNumber   = 1;
cfg2.stdif10.bAlternateSetting  = 0;
cfg2.stdif10.bNumEndpoints      = M_CFG2_I1A0_NUMEPS;
cfg2.stdif10.bInterfaceClass    = M_CFG2_I1A0_IFCLASS;
cfg2.stdif10.bInterfaceSubClass = M_CFG2_I1A0_IFSUBCLASS;
cfg2.stdif10.bInterfaceProtocol = M_CFG2_I1A0_IFPROTOCOL;
cfg2.stdif10.iInterface         = M_CFG2_I1A0_IFI;

/* .. Endpoints */
cfg2.stdep10_0.bLength          = sizeof(STD_EP_DSCR);
cfg2.stdep10_0.bDescriptorType  = M_DST_ENDPOINT;
cfg2.stdep10_0.bEndpointAddress = M_CFG2_I1A0_0_EPADDR;
cfg2.stdep10_0.bmAttributes     = M_CFG2_I1A0_0_ATTRIB;
cfg2.stdep10_0.wMaxPacketSize   = M_CFG2_I1A0_0_MAXP;
cfg2.stdep10_0.bInterval        = M_CFG2_I1A0_0_INTER;
cfg2.stdep10_1.bLength          = sizeof(STD_EP_DSCR);
cfg2.stdep10_1.bDescriptorType  = M_DST_ENDPOINT;
cfg2.stdep10_1.bEndpointAddress = M_CFG2_I1A0_1_EPADDR;
cfg2.stdep10_1.bmAttributes     = M_CFG2_I1A0_1_ATTRIB;
cfg2.stdep10_1.wMaxPacketSize   = M_CFG2_I1A0_1_MAXP;
cfg2.stdep10_1.bInterval        = M_CFG2_I1A0_1_INTER;

}
