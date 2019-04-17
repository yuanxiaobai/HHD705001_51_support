/*
 *-----------------------------------------------------------------------------
 * The confidential and proprietary information contained in this file may
 * only be used by a person authorised under and to the extent permitted
 * by a subsisting licensing agreement from ARM Limited.
 *
 *            (C) COPYRIGHT 2010-2011 ARM Limited.
 *                ALL RIGHTS RESERVED
 *
 * This entire notice must be reproduced on all copies of this file
 * and copies of this file may only be made by a person if such person is
 * permitted to do so under the terms of a subsisting license agreement
 * from ARM Limited.
 *
 *      SVN Information
 *
 *      Checked In          : $Date: 2011/05/20 06:42:13 $
 *
 *      Revision            : $Revision: 1.1 $
 *
 *      Release Information : BP200-r0p0-00rel0
 *-----------------------------------------------------------------------------
 */
/* Functions for stdout during simulation */
/* The functions are implemented in shared/software/common/uart_stdout.c */

extern void UartStdOutInit(void);
extern unsigned char UartPutc(unsigned char my_ch);
extern unsigned char UartGetc(void);
extern unsigned char UartEndSimulation(void);
extern void Uart_PutStr(const void *str);
extern void Uart_PutHex(unsigned int hexnum, unsigned char type);
