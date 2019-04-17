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

 /*

 UART functions for retargetting

 */
#ifdef CORTEX_M0
#include "CMSDK_CM0.h"
#endif

#ifdef CORTEX_M3
#include "g32f1xx.h"
#endif

#ifdef CORTEX_M4
#include "CMSDK_CM4.h"
#endif

void UartStdOutInit(void)
{
  GT_SYSCON->SYSAPB2CLKCTRL |= 1<<14;
  GT_SYSCON->UARTCLKDIV = 1;
  GT_UART1->BAUDDIV = 54;
  GT_UART1->CTRL    = 0x01<<23; // High speed test mode, TX only
//  GT_GPIO1->ALTFUNCSET = (1<<5);
  return;
}
// Output a character
unsigned char UartPutc(unsigned char my_ch)
{
  while ((GT_UART1->STATE & 1)); // Wait if Transmit Holding register is full
  GT_UART1->DATA = my_ch; // write to transmit holding register
  return (my_ch);
}
// Get a character
unsigned char UartGetc(void)
{
  while ((GT_UART1->STATE & 2)==0); // Wait if Receive Holding register is empty
  return (GT_UART1->DATA);
}


void UartEndSimulation(void)
{
  UartPutc((char) 0x4); // End of simulation
  while(1);
}

void Uart_PutStr(const void *str)
{
  unsigned char *s=(unsigned char *)str;
  while((*s!='\0')||(*s!=0))
  {
    UartPutc(*s++);
  }
}
void Uart_PutHex(unsigned int hexnum, unsigned char type)
{
  unsigned char buff[16];
  unsigned int  i = 0;
  unsigned int  k = 1;

  Uart_PutStr("0x");

  while(hexnum)
  {
    buff[i++] = hexnum%16;
    hexnum = hexnum/16;
  }
  i--;

  if(type == 8) {
    k=1;
  }else if(type==16){
    k=3;
  }else if(type==32){
    k=7;
  }else{
    k=i;
  }

  while((k-i)>0){
    UartPutc('0');
    k--;
  }

  while((i+1)>0){
    if(buff[i]<=9){
      UartPutc(buff[i]+'0');
    }else{
      UartPutc(buff[i]-10+'A');
    }
    if(i==0)break;
    i--;
  }
}


