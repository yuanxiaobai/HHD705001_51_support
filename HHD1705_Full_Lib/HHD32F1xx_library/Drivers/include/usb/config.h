/****************************************

  config.h
  Configuration for MUSBFSFC firmware
  This file defines the number of descriptors for the device.
  It must be modified by the user to match the required configuration.

  Copyright Mentor Graphics Corporation and Licensors 2000
  V1.0  4 September 2000

 $Log: config.h,v $
 Revision 1.3  2001/05/31
 CVS Log Added


****************************************/

#ifndef _CONFIG_H_
#define _CONFIG_H_

/* Define maximum packet size for endpoint 0 */
#define M_EP0_MAXP      8

/* Define maximum number of interfaces in a configuration */
#define M_MAXIFS        16

/* Define values for Standard Device Descriptor */
#define M_DEVDSC_CLASS          0x00    /* Device Class */
#define M_DEVDSC_SUBCLASS       0x00    /* Device SubClass */
#define M_DEVDSC_PROTOCOL       0x00    /* Device Protocol */
#define M_DEVDSC_VENDOR         0x0000  /* Vendor ID */
#define M_DEVDSC_PRODUCT        0x0000  /* Product ID */
#define M_DEVDSC_RELEASE        0x0000  /* Release number */
#define M_DEVDSC_MANUI          0       /* Manufacturer string index */
#define M_DEVDSC_PRODI          0       /* Product string index */
#define M_DEVDSC_SERIALI        0       /* Serial number string index */
#define M_DEVDSC_CONFIGS        2       /* Number of configurations */


/* Define values for descriptors in configuration 1 */
#define M_CFG1_NUMIFS           2       /* Number of interfaces */
#define M_CFG1_CFGI             0       /* Configuration description string index */
#define M_CFG1_ATTRIBUTES       0x00    /* Configuration attributes */
#define M_CFG1_MAXPOWER         0       /* Maximum power (units of 2 mA) */

/* Interface 0, alternate 0 */
#define M_CFG1_I0A0_NUMEPS      2       /* Number of endpoints */
#define M_CFG1_I0A0_IFCLASS     0       /* Interface class */
#define M_CFG1_I0A0_IFSUBCLASS  0       /* Interface subclass */
#define M_CFG1_I0A0_IFPROTOCOL  0       /* Interface protocol */
#define M_CFG1_I0A0_IFI         0       /* Interface string index */
#define M_CFG1_I0A0_0_EPADDR    0x81    /* Endpoint address (endpoint 1 IN) */
#define M_CFG1_I0A0_0_ATTRIB    0x02    /* Endpoint attributes (bulk) */
#define M_CFG1_I0A0_0_MAXP      0x0040  /* Endpoint max packet size (64) */
#define M_CFG1_I0A0_0_INTER     0       /* Endpoint interval */
#define M_CFG1_I0A0_1_EPADDR    0x01    /* Endpoint address (endpoint 1 OUT) */
#define M_CFG1_I0A0_1_ATTRIB    0x02    /* Endpoint attributes (bulk) */
#define M_CFG1_I0A0_1_MAXP      0x0040  /* Endpoint max packet size (64) */
#define M_CFG1_I0A0_1_INTER     0       /* Endpoint interval */

/* Interface 1, alternate 0 */
#define M_CFG1_I1A0_NUMEPS      2       /* Number of endpoints */
#define M_CFG1_I1A0_IFCLASS     0       /* Interface class */
#define M_CFG1_I1A0_IFSUBCLASS  0       /* Interface subclass */
#define M_CFG1_I1A0_IFPROTOCOL  0       /* Interface protocol */
#define M_CFG1_I1A0_IFI         0       /* Interface string index */
#define M_CFG1_I1A0_0_EPADDR    0x82    /* Endpoint address (endpoint 2 IN) */
#define M_CFG1_I1A0_0_ATTRIB    0x02    /* Endpoint attributes (bulk) */
#define M_CFG1_I1A0_0_MAXP      0x0040  /* Endpoint max packet size (64) */
#define M_CFG1_I1A0_0_INTER     0       /* Endpoint interval */
#define M_CFG1_I1A0_1_EPADDR    0x02    /* Endpoint address (endpoint 2 OUT) */
#define M_CFG1_I1A0_1_ATTRIB    0x02    /* Endpoint attributes (bulk) */
#define M_CFG1_I1A0_1_MAXP      0x0040  /* Endpoint max packet size (64) */
#define M_CFG1_I1A0_1_INTER     0       /* Endpoint interval */

/* Interface 1, alternate 1 */
#define M_CFG1_I1A1_NUMEPS      2       /* Number of endpoints */
#define M_CFG1_I1A1_IFCLASS     0       /* Interface class */
#define M_CFG1_I1A1_IFSUBCLASS  0       /* Interface subclass */
#define M_CFG1_I1A1_IFPROTOCOL  0       /* Interface protocol */
#define M_CFG1_I1A1_IFI         0       /* Interface string index */
#define M_CFG1_I1A1_0_EPADDR    0x82    /* Endpoint address (endpoint 2 IN) */
#define M_CFG1_I1A1_0_ATTRIB    0x02    /* Endpoint attributes (bulk) */
#define M_CFG1_I1A1_0_MAXP      0x0040  /* Endpoint max packet size (64) */
#define M_CFG1_I1A1_0_INTER     0       /* Endpoint interval */
#define M_CFG1_I1A1_1_EPADDR    0x02    /* Endpoint address (endpoint 2 OUT) */
#define M_CFG1_I1A1_1_ATTRIB    0x02    /* Endpoint attributes (bulk) */
#define M_CFG1_I1A1_1_MAXP      0x0040  /* Endpoint max packet size (64) */
#define M_CFG1_I1A1_1_INTER     0       /* Endpoint interval */


/* Define values for descriptors in configuration 2 */
#define M_CFG2_NUMIFS           2       /* Number of interfaces */
#define M_CFG2_CFGI             0       /* Configuration description string index */
#define M_CFG2_ATTRIBUTES       0x00    /* Configuration attributes */
#define M_CFG2_MAXPOWER         0       /* Maximum power (units of 2 mA) */

/* Interface 0, alternate 0 */
#define M_CFG2_I0A0_NUMEPS      2       /* Number of endpoints */
#define M_CFG2_I0A0_IFCLASS     0       /* Interface class */
#define M_CFG2_I0A0_IFSUBCLASS  0       /* Interface subclass */
#define M_CFG2_I0A0_IFPROTOCOL  0       /* Interface protocol */
#define M_CFG2_I0A0_IFI         0       /* Interface string index */
#define M_CFG2_I0A0_0_EPADDR    0x81    /* Endpoint address (endpoint 1 IN) */
#define M_CFG2_I0A0_0_ATTRIB    0x02    /* Endpoint attributes (bulk) */
#define M_CFG2_I0A0_0_MAXP      0x0040  /* Endpoint max packet size (64) */
#define M_CFG2_I0A0_0_INTER     0       /* Endpoint interval */
#define M_CFG2_I0A0_1_EPADDR    0x01    /* Endpoint address (endpoint 1 OUT) */
#define M_CFG2_I0A0_1_ATTRIB    0x02    /* Endpoint attributes (bulk) */
#define M_CFG2_I0A0_1_MAXP      0x0040  /* Endpoint max packet size (64) */
#define M_CFG2_I0A0_1_INTER     0       /* Endpoint interval */

/* Interface 1, alternate 0 */
#define M_CFG2_I1A0_NUMEPS      2       /* Number of endpoints */
#define M_CFG2_I1A0_IFCLASS     0       /* Interface class */
#define M_CFG2_I1A0_IFSUBCLASS  0       /* Interface subclass */
#define M_CFG2_I1A0_IFPROTOCOL  0       /* Interface protocol */
#define M_CFG2_I1A0_IFI         0       /* Interface string index */
#define M_CFG2_I1A0_0_EPADDR    0x82    /* Endpoint address (endpoint 2 IN) */
#define M_CFG2_I1A0_0_ATTRIB    0x02    /* Endpoint attributes (bulk) */
#define M_CFG2_I1A0_0_MAXP      0x0040  /* Endpoint max packet size (64) */
#define M_CFG2_I1A0_0_INTER     0       /* Endpoint interval */
#define M_CFG2_I1A0_1_EPADDR    0x02    /* Endpoint address (endpoint 2 OUT) */
#define M_CFG2_I1A0_1_ATTRIB    0x02    /* Endpoint attributes (bulk) */
#define M_CFG2_I1A0_1_MAXP      0x0040  /* Endpoint max packet size (64) */
#define M_CFG2_I1A0_1_INTER     0       /* Endpoint interval */


/*
  Define configuration structures
  The configuration structures need to be modified to match the required configuration
  Each configuration should start with a configuration descriptor
  followed by 1 or more interface descriptors (each of which is followed by
  endpoint descriptors for all the endpoints in that interface).
  The interface descriptors should start with interface 0, alternate setting 0.
  Followed by any alternate settings for interface 0.
  Then interface 1 (if more than 1 interface in the configuration), followed
  by any alternate settings for interface 1.
  This arrangement should be repeated for all interfaces in the configuration.
*/

/* Configuration 1 */
typedef struct M_CFG_1 {
  STD_CFG_DSCR  stdcfg;         /* Required Standard Configuration Descriptor */
  STD_IF_DSCR   stdif00;        /* Interface 0 Descriptor */
  STD_EP_DSCR   stdep00_0;      /* 1st Endpoint Descriptor for Interface 0 */
  STD_EP_DSCR   stdep00_1;      /* 2nd Endpoint Descriptor for Interface 0 */
  STD_IF_DSCR   stdif10;        /* Interface 1 Alternate 0 Descriptor */
  STD_EP_DSCR   stdep10_0;      /* 1st Endpoint Descriptor for Interface 1 */
  STD_EP_DSCR   stdep10_1;      /* 2nd Endpoint Descriptor for Interface 1 */
  STD_IF_DSCR   stdif11;        /* Interface 1 Alternate 1 Descriptor */
  STD_EP_DSCR   stdep11_0;      /* 1st Endpoint Descriptor for Interface 1 */
  STD_EP_DSCR   stdep11_1;      /* 2nd Endpoint Descriptor for Interface 1 */
  } M_CFG_1;
typedef M_CFG_1 * PM_CFG_1;

/* Configuration 2 */
typedef struct M_CFG_2 {
  STD_CFG_DSCR  stdcfg;         /* Required Standard Configuration Descriptor */
  STD_IF_DSCR   stdif00;        /* Interface 0 Descriptor */
  STD_EP_DSCR   stdep00_0;      /* 1st Endpoint Descriptor for Interface 0 */
  STD_EP_DSCR   stdep00_1;      /* 2nd Endpoint Descriptor for Interface 0 */
  STD_IF_DSCR   stdif10;        /* Interface 1 Descriptor */
  STD_EP_DSCR   stdep10_0;      /* 1st Endpoint Descriptor for Interface 1 */
  STD_EP_DSCR   stdep10_1;      /* 2nd Endpoint Descriptor for Interface 1 */
  } M_CFG_2;
typedef M_CFG_2 * PM_CFG_2;

/* Top level structure containing pointers to each configuration */
typedef struct M_CFG {
  PM_CFG_1      pcfg1;          /* Pointer to M_CFG_1 */
  PM_CFG_2      pcfg2;          /* Pointer to M_CFG_2 */
  } M_CFG;
typedef M_CFG * PM_CFG;

#endif /* _CONFIG_H_ */

