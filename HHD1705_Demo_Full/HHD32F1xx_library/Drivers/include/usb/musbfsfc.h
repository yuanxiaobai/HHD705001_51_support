/****************************************

  musbfsfc.h
  Header file for MUSBFSFC firmware

  Copyright Mentor Graphics Corporation and Licensors 2000
  V1.0  4 September 2000

 $Log: musbfsfc.h,v $
 Revision 1.4  2001/05/31
 CVS Log Added


****************************************/

#ifndef _MUSBFSFC_H_
#define _MUSBFSFC_H_

/* Define MUSBFSFC register addresses */
#define BASE_ADDR 0x40005c00

#define M_REG_FADDR     BASE_ADDR
#define M_REG_POWER     BASE_ADDR+1*4
#define M_REG_INTRIN1   BASE_ADDR+2*4
#define M_REG_INTRIN2   BASE_ADDR+3*4
#define M_REG_INTROUT1  BASE_ADDR+4*4
#define M_REG_INTROUT2  BASE_ADDR+5*4
#define M_REG_INTRUSB   BASE_ADDR+6*4
#define M_REG_INTRIN1E  BASE_ADDR+7*4
#define M_REG_INTRIN2E  BASE_ADDR+8*4
#define M_REG_INTROUT1E BASE_ADDR+9*4
#define M_REG_INTROUT2E BASE_ADDR+10*4
#define M_REG_INTRUSBE  BASE_ADDR+11*4
#define M_REG_FRAME1    BASE_ADDR+12*4
#define M_REG_FRAME2    BASE_ADDR+13*4
#define M_REG_INDEX     BASE_ADDR+14*4

#define M_REG_CSR0      BASE_ADDR+17*4
#define M_REG_INMAXP    BASE_ADDR+16*4
#define M_REG_INCSR1    BASE_ADDR+17*4
#define M_REG_INCSR2    BASE_ADDR+18*4
#define M_REG_OUTMAXP   BASE_ADDR+19*4
#define M_REG_OUTCSR1   BASE_ADDR+20*4
#define M_REG_OUTCSR2   BASE_ADDR+21*4
#define M_REG_OUTCOUNT1 BASE_ADDR+22*4
#define M_REG_OUTCOUNT2 BASE_ADDR+23*4

#define M_FIFO_EP0      BASE_ADDR+32*4


/* Interrupt register bit masks */
#define M_INTR_SUSPEND  0x01
#define M_INTR_RESUME   0x02
#define M_INTR_RESET    0x04
#define M_INTR_EP0      0x0001

/* CSR0 bit masks */
#define M_CSR0_OUTPKTRDY        0x01
#define M_CSR0_INPKTRDY         0x02
#define M_CSR0_SENTSTALL        0x04
#define M_CSR0_DATAEND          0x08
#define M_CSR0_SETUPEND         0x10
#define M_CSR0_SENDSTALL        0x20
#define M_CSR0_SVDOUTPKTRDY     0x40
#define M_CSR0_SVDSETUPEND      0x80

/* Endpoint CSR register bits */
#define M_INCSR2_ISO    0x40
#define M_INCSR2_MODE   0x20
#define M_INCSR_CDT     0x40
#define M_INCSR_FF      0x08
#define M_INCSR_IPR     0x01
#define M_OUTCSR2_ISO   0x40
#define M_OUTCSR_CDT    0x80
#define M_OUTCSR_FF     0x10
#define M_OUTCSR_OPR    0x01


/* Define integer types for 8/16 bit registers */
#ifndef BYTE
typedef unsigned char BYTE;
#endif
#ifndef WORD
typedef unsigned short WORD;
#endif


/* Register read/write macros */
#define MREAD_BYTE(addr) *((BYTE *)(addr))
#define MWRITE_BYTE(addr,data) *((BYTE *)(addr)) = data

/* Define endpoint call status values */
#define M_EP_NORMAL     0
#define M_EP_RESET      1

/* Define device states */
#define DEVSTATE_DEFAULT        0
#define DEVSTATE_ADDRESS        1
#define DEVSTATE_CONFIG         2

/* Define standard constants */
#define TRUE  1
#define FALSE 0
#ifndef NULL
#define NULL 0
#endif

/* Function prototypes */
void FIFORead (int, int, void*);
void FIFOWrite (int, int, void*);
void USBReset (void);
void InitialiseDesc (void);
void Endpoint0 (int);

#endif /* _MUSBFSFC_H_ */

