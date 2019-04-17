/****************************************

  descript.h
  Endpoint 0 descriptor definitions for MUSBFSFC firmware

  Copyright Mentor Graphics Corporation and Licensors 2000
  V1.0  4 September 2000

 $Log: descript.h,v $
 Revision 1.3  2001/05/31
 CVS Log Added


  Note the defined structures assume WORDS are stored little-endian.

****************************************/

#ifndef _DESCRIPT_H_
#define _DESCRIPT_H_

#pragma pack(1)

/* Command structure */
typedef struct COMMAND {
  BYTE  bmRequestType;
  BYTE  bRequest;
  WORD  wValue;
  WORD  wIndex;
  WORD  wLength;
  } COMMAND;
typedef COMMAND * PCOMMAND;

/* Command bit fields */
#define M_CMD_DATADIR   0x80

/* Request Type Field */
#define M_CMD_TYPEMASK  0x60
#define M_CMD_STDREQ    0x00
#define M_CMD_CLASSREQ  0x20
#define M_CMD_VENDREQ   0x40
#define M_CMD_STDDEVIN  0x80
#define M_CMD_STDDEVOUT 0x00
#define M_CMD_STDIFIN   0x81
#define M_CMD_STDIFOUT  0x01
#define M_CMD_STDEPIN   0x82
#define M_CMD_STDEPOUT  0x02

/* Standard Request Codes */
#define GET_STATUS              0x00
#define CLEAR_FEATURE           0x01
#define SET_FEATURE             0x03
#define SET_ADDRESS             0x05
#define GET_DESCRIPTOR          0x06
#define SET_DESCRIPTOR          0x07
#define GET_CONFIGURATION       0x08
#define SET_CONFIGURATION       0x09
#define GET_INTERFACE           0x0A
#define SET_INTERFACE           0x0B
#define SYNCH_FRAME             0x0C

/* Standard Descriptor Types */
#define M_DST_DEVICE     0x01
#define M_DST_CONFIG     0x02
#define M_DST_STRING     0x03
#define M_DST_INTERFACE  0x04
#define M_DST_ENDPOINT   0x05
#define M_DST_DEVQUAL    0x06
#define M_DST_OTHERSPEED 0x07
#define M_DST_POWER      0x08
#define M_CMD_DESCMASK   0xFF00
#define M_CMD_DEVICE     (M_DST_DEVICE<<8)
#define M_CMD_CONFIG     (M_DST_CONFIG<<8)
#define M_CMD_STRING     (M_DST_STRING<<8)
#define M_CMD_DEVQUAL    (M_DST_DEVQUAL<<8)
#define M_CMD_OTHERSPEED (M_DST_OTHERSPEED<<8)

/* Endpoint transfer types */
#define M_EP_TFMASK     0x03
#define M_EP_CONTROL    0x00
#define M_EP_ISO        0x01
#define M_EP_BULK       0x10
#define M_EP_INTR       0x11

/* Standard Device Feature Selectors */
#define M_FTR_DEVREMWAKE 0x0001

/* Standard Device Descriptor */
typedef struct STD_DEV_DSCR {
  BYTE  bLength;
  BYTE  bDescriptorType;
  WORD  bcdUSB;
  BYTE  bDeviceClass;
  BYTE  bDeviceSubClass;
  BYTE  bDeviceProtocol;
  BYTE  bMaxPacketSize0;
  WORD  idVendor;
  WORD  idProduct;
  WORD  bcdDevice;
  BYTE  iManufacturer;
  BYTE  iProduct;
  BYTE  iSerialNumber;
  BYTE  bNumConfigurations;
  } STD_DEV_DSCR;
typedef STD_DEV_DSCR * PSTD_DEV_DSCR;

/* Standard Configuration Descriptor */
typedef struct STD_CFG_DSCR {
  BYTE  bLength;
  BYTE  bDescriptorType;
  WORD  wTotalLength;
  BYTE  bNumInterfaces;
  BYTE  bConfigurationValue;
  BYTE  iConfiguration;
  BYTE  bmAttributes;
  BYTE  bMaxPower;
  } STD_CFG_DSCR;
typedef STD_CFG_DSCR * PSTD_CFG_DSCR;

/* Standard Interface Descriptor */
typedef struct STD_IF_DSCR {
  BYTE  bLength;
  BYTE  bDescriptorType;
  BYTE  bInterfaceNumber;
  BYTE  bAlternateSetting;
  BYTE  bNumEndpoints;
  BYTE  bInterfaceClass;
  BYTE  bInterfaceSubClass;
  BYTE  bInterfaceProtocol;
  BYTE  iInterface;
  } STD_IF_DSCR;
typedef STD_IF_DSCR * PSTD_IF_DSCR;

/* Standard Endpoint Descriptor */
typedef struct STD_EP_DSCR {
  BYTE  bLength;
  BYTE  bDescriptorType;
  BYTE  bEndpointAddress;
  BYTE  bmAttributes;
  WORD  wMaxPacketSize;
  BYTE  bInterval;
  } STD_EP_DSCR;
typedef STD_EP_DSCR * PSTD_EP_DSCR;


#endif /* _DESCRIPT_H_ */

