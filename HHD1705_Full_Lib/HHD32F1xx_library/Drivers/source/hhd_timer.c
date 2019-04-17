/*   Copyright(C) 2015, Gorge Technology
 *   All rights reserved.
 *
 *   History
 *   2015.07  ver 1.01    Prelimnary version
 *
******************************************************************************/
/* Includes ------------------------------------------------------------------*/

#include "hhd32f1xx.h"
#include "hhd_timer.h"
#include "hhd_sys.h"

extern uint32_t SystemCoreClock;
/*****************************************************************************
Function Name	TIM_Init
Function Definition	void TIM_Init(G32F1_TIM_TypeDef *ct, uint32_t tickpersecond)
Function Description	Initial basic timer
Input Parameters	*ct: pointer to TIM/TIM
tickpersecond: timer count frequency, less than system clock
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_Init(HHD32F1_TIM_TypeDef *ct, uint32_t tickpersecond)
{
    if (ct == TIM2)
    {
        SYSCON->SYSAPB1CLKCTRL.bit.TIM2CLK = 1;
        SYSCON->APB1RESET.bit.TIM2RSTN = 1;
        SYSCON->APB1RESET.bit.TIM2RSTN = 0;
    }
    else if (ct == TIM3)
    {
        SYSCON->SYSAPB1CLKCTRL.bit.TIM3CLK = 1;
        SYSCON->APB1RESET.bit.TIM3RSTN = 1;
        SYSCON->APB1RESET.bit.TIM3RSTN = 0;
    }
    else if (ct == TIM4)
    {
        SYSCON->SYSAPB1CLKCTRL.bit.TIM4CLK = 1;
        SYSCON->APB1RESET.bit.TIM4RSTN = 1;
        SYSCON->APB1RESET.bit.TIM4RSTN = 0;
    }
    else if (ct == TIM5)
    {
        SYSCON->SYSAPB1CLKCTRL.bit.TIM5CLK = 1;
        SYSCON->APB1RESET.bit.TIM5RSTN = 1;
        SYSCON->APB1RESET.bit.TIM5RSTN = 0;
    }
    else if (ct == TIM6)
    {
        SYSCON->SYSAPB1CLKCTRL.bit.TIM6CLK = 1;
        SYSCON->APB1RESET.bit.TIM6RSTN = 1;
        SYSCON->APB1RESET.bit.TIM6RSTN = 0;
    }
    else if (ct == TIM7)
    {
        SYSCON->SYSAPB1CLKCTRL.bit.TIM7CLK = 1;
        SYSCON->APB1RESET.bit.TIM7RSTN = 1;
        SYSCON->APB1RESET.bit.TIM7RSTN = 0;
    }
#if 0 //modify by wang 2019-1-11
    else if (ct == TIM9)
    {
        SYSCON->SYSAPB2CLKCTRL.bit.TIM9CLK = 1;
        SYSCON->APB2RESET.bit.TIM9RSTN = 1;
        SYSCON->APB2RESET.bit.TIM9RSTN = 0;
    }
    else if (ct == TIM10)
    {
        SYSCON->SYSAPB2CLKCTRL.bit.TIM10CLK = 1;
        SYSCON->APB2RESET.bit.TIM10RSTN = 1;
        SYSCON->APB2RESET.bit.TIM10RSTN = 0;
    }
    else if (ct == TIM11)
    {
        SYSCON->SYSAPB2CLKCTRL.bit.TIM11CLK = 1;
        SYSCON->APB2RESET.bit.TIM11RSTN = 1;
        SYSCON->APB2RESET.bit.TIM11RSTN = 0;
    }
    else if (ct == TIM12)
    {
        SYSCON->SYSAPB1CLKCTRL.bit.TIM12CLK = 1;
        SYSCON->APB1RESET.bit.TIM12RSTN = 1;
        SYSCON->APB1RESET.bit.TIM12RSTN = 0;
    }
    else if (ct == TIM13)
    {
        SYSCON->SYSAPB1CLKCTRL.bit.TIM13CLK = 1;
        SYSCON->APB1RESET.bit.TIM13RSTN = 1;
        SYSCON->APB1RESET.bit.TIM13RSTN = 0;
    }
    else if (ct == TIM14)
    {
        SYSCON->SYSAPB1CLKCTRL.bit.TIM14CLK = 1;
        SYSCON->APB1RESET.bit.TIM14RSTN = 1;
        SYSCON->APB1RESET.bit.TIM14RSTN = 0;
    }
#endif
    else return;

    if (tickpersecond > SystemCoreClock)
        tickpersecond = SystemCoreClock;
    ct->PR.bit.PCVAL = SystemCoreClock / tickpersecond;

    return;
}
/*****************************************************************************
Function Name	TIM_ConfigMatch
Function Definition	void TIM_ConfigMatch(G32F1_TIM_TypeDef *ct, uint16_t ticks, uint8_t action)
Function Description	Setup Match
Input Parameters	*ct: pointer to TIM/TIM
ticks: match value
action: combination of following action when counter reach match value
	TIM_MATCH_TRIGGER_INT 0x1
	TIM_MATCH_RESET_COUNTER 0x2
	TIM_MATCH_STOP_COUNTER 0x4
	TIM_MATCH_DO_NOTHING 0x0
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_ConfigMatch(HHD32F1_TIM_TypeDef *ct, uint16_t ticks, uint8_t action)
{
	ct->MR0.bit.MATCH=ticks;
	ct->MCR.all=action;
	return;
}
/*****************************************************************************
Function Name	TIM_SetTimerCounter
Function Definition	void TIM_SetTimerCounter(G32F1_TIM_TypeDef *ct, uint16_t tick)
Function Description	*ct: pointer to TIM/TIM
tick: set current value
Input Parameters	No
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_SetTimerCounter(HHD32F1_TIM_TypeDef *ct, uint16_t tick)
{
	ct->PC.bit.PC=tick;
	return;
}
/*****************************************************************************
Function Name	TIM_ResetTimerCounter
Function Definition	void TIM_ResetTimerCounter(G32F1_TIM_TypeDef *ct)
Function Description	Reset Timer Counter value
Input Parameters	*ct: pointer to TIM/TIM
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_ResetTimerCounter(HHD32F1_TIM_TypeDef *ct)
{
	ct->PC.bit.PC=0;
	return;
}
/*****************************************************************************
Function Name	TIM_GetTimerCounter
Function Definition	uint16_t TIM_GetTimerCounter(G32F1_TIM_TypeDef *ct)
Function Description	Get current timer counter value
Input Parameters	*ct: pointer to TIM/TIM
Return Value	Timer Counter value
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
uint16_t TIM_GetTimerCounter(HHD32F1_TIM_TypeDef *ct)
{
	return ct->PC.bit.PC;
}
/*****************************************************************************
Function Name	TIM_ClearIntFlag
Function Definition	void TIM_ClearIntFlag(G32F1_TIM_TypeDef *ct)
Function Description	Clear Match event interrupt
Input Parameters	*ct: pointer to TIM/TIM
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_ClearIntFlag(HHD32F1_TIM_TypeDef *ct)
{
	ct->IR.bit.MR0INT=1;
	return;
}
/*****************************************************************************
Function Name	TIM_ClearIntFlag
Function Definition	void TIM_ClearIntFlag(HHD32F1_TIM_TypeDef *ct)
Function Description	Clear Match event interrupt
Input Parameters	*ct: pointer to TIM/TIM
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_EnableInt(HHD32F1_TIM_TypeDef *ct)
{
	ct->MCR.bit.MR0I=1;
	return;
}
/*****************************************************************************
Function Name	TIM_DisableInt
Function Definition	void TIM_DisableInt(HHD32F1_TIM_TypeDef *ct)
Function Description	Disable Match event interrupt
Input Parameters	*ct: pointer to TIM/TIM
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_DisableInt(HHD32F1_TIM_TypeDef *ct)
{
	ct->MCR.bit.MR0I=0;
	return;	
}

/*****************************************************************************
Function Name	TIM_SetCTType
Function Definition	void TIM_SetCTType(HHD32F1_TIM_TypeDef *ct, uint8_t mode)
Function Description	Initial timer/counter mode
Input Parameters	*ct: pointer to TIM2/TIM3
mode: counter/timer mode
			000 	Timer Mode, every PCLK
			001 	Counter Mode, Primary select signal rise edge
			010 	Counter Mode, Primary select signal fall edge 
			011 	Edge Count Mode  
			100	Quadrature mode
			101	Trigger count mode.
			110	Signed count mode.
			111	Gate count mode.
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_SetCTType(HHD32F1_TIM_TypeDef *ct, uint8_t mode)
{
	ct->CTCR.bit.CTM=mode;
	return;
}
/*****************************************************************************
Function Name	TIM_SelectTimerClearSignal
Function Definition	void TIM_SelectTimerClearSignal(G32F1_TIM_TypeDef *ct, uint8_t capsignal, uint8_t edge)
Function Description	Select capture event to clear timer
Input Parameters	*ct: pointer to TIM2/TIM3
capsignal: capture signal
					0, CAP0
					1, CAP1
					2, CAP2
					4, CAP3
					5, Other Timer CAP0
					6, Other Timer CAP1
					7, Other Timer CAP2
					8, Other Timer CAP3
Edge: RISE_EDGE/FALL_EDGE
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_SelectTimerClearSignal(HHD32F1_TIM_TypeDef *ct, uint8_t capsignal, uint8_t edge)
{
	//set counter clear singal
	ct->CTCR.bit.SELCC=capsignal<<1;
	if (edge==FALL_EDGE)
			ct->CTCR.bit.SELCC++;
	//enable counter clear action
	ct->CTCR.bit.ENCC=1;
	return;
}	
/*****************************************************************************
Function Name	TIM_SelectPriSrc
Function Definition	void TIM_SelectPriSrc(G32F1_TIM_TypeDef *ct, uint8_t clksrc)
Function Description	Initial basic timer
Input Parameters	*ct: pointer to TIM2/TIM3
clksrc: clock source
				0000	CAP0 pin
				0001	CAP1 pin
				0010	CAP2 pin
				0011	CAP3 pin
				0100	PWM Event
				0101	TIM_MAT0./ TIM3_MAT0
				0110	Reserved
				0111	Reserved.
				1xxx	Prescale counter
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_SelectPriSrc(HHD32F1_TIM_TypeDef *ct, uint8_t clksrc)
{
	ct->CTCR.bit.PRISEL=clksrc;
	return;
}
/*****************************************************************************
Function Name	TIM_SelectPriSrc
Function Definition	void TIM_SelectSecSrc (G32F1_TIM_TypeDef *ct, uint8_t clksrc, uint8_t polarity)
Function Description	Initial basic timer
Input Parameters	*ct: pointer to TIM2/TIM3
clksrc: clock source
				0000	CAP0 pin
				0001	CAP1 pin
				0010	CAP2 pin
				0011	CAP3 pin
				0100	PWM Event
				0101	TIM_MAT0./ TIM3_MAT0
				0110	Reserved
				0111	Reserved.
				1xxx	Prescale counter
polarity: inverse clock source

Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_SelectSecSrc (HHD32F1_TIM_TypeDef *ct, uint8_t clksrc, uint8_t polarity)
{
	ct->CTCR.bit.SECSEL=clksrc;
	ct->CTCR.bit.IPS=polarity;
	return;
}
/*****************************************************************************
Function Name	TIM_ConfigMatch0
Function Definition	void TIM_ConfigMatch0(HHD32F1_TIM_TypeDef *ct, uint16_t ticks, uint8_t internalaction, uint8_t externalaction)
Function Description	Setup timer match 0 and internal action when match even occurs
Input Parameters	*ct: pointer to TIM2/TIM3
ticks: match 0 value
internalaction: combination of following action when counter reach match value
               TIM_MATCH_TRIGGER_INT 0x1
               TIM_MATCH_RESET_COUNTER 0x2
               TIM_MATCH_STOP_COUNTER 0x4
               TIM_MATCH_DO_NOTHING 0x0 
externalaction: one of following action when counter reach match value
               TIM_MATCH_OUT_DO_NOTHING 0x0
               TIM_MATCH_OUT_RESET 0x1
               TIM_MATCH_OUT_SET	 0x2
               TIM_MATCH_OUT_TRIGGER_PLUS	 0x3

Return Value	No
Condition	No
Function called	-

Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_ConfigMatch0(HHD32F1_TIM_TypeDef *ct, uint16_t ticks, uint8_t internalaction,
                      uint8_t externalaction)
{
	ct->MR0.bit.MATCH=ticks;
	
	ct->MCR.all=(ct->MCR.all&(~0x7))|(internalaction&0x7);
	
	ct->EMR.bit.EMC0=externalaction;
	ct->EMR.bit.EM0=1;	
	return;
}
/*****************************************************************************
Function Name	TIM_ConfigMatch1
Function Definition	void TIM_ ConfigMatch1(G32F1_TIM_TypeDef *ct, uint16_t ticks, uint8_t internalaction, uint8_t externalaction)
Function Description	Setup timer match 1 and internal action and TIM_MAT1/ TIM_MAT1 output external action when match even occurs
Input Parameters	*ct: pointer to TIM2/TIM3
ticks: match 1 value
internalaction: combination of following action when counter reach match value
			TIM_MATCH_TRIGGER_INT 0x1
			TIM_MATCH_RESET_COUNTER 0x2
			TIM_MATCH_STOP_COUNTER 0x4
			TIM_MATCH_DO_NOTHING 0x0 
externalaction: one of following action when counter reach match value
			TIM_MATCH_OUT_DO_NOTHING 0x0
			TIM_MATCH_OUT_RESET 0x1
			TIM_MATCH_OUT_SET	 0x2
			TIM_MATCH_OUT_TRIGGER_PLUS	 0x3
Return Value	No
Condition	No
Function called	-


Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_ConfigMatch1(HHD32F1_TIM_TypeDef *ct, uint16_t ticks, uint8_t internalaction,
                      uint8_t externalaction)
{
	ct->MR1.bit.MATCH=ticks;
	ct->MCR.all=(ct->MCR.all&(~(0x7<<3)))|((internalaction&0x7)<<3);

	ct->EMR.bit.EMC1=externalaction;
	ct->EMR.bit.EM1=1;	
	return;
}	
/*****************************************************************************
Function Name	TIM_ConfigMatch2
Function Definition	void TIM_ConfigMatch2(G32F1_TIM_TypeDef *ct, uint16_t ticks, uint8_t internalaction, uint8_t externalaction)
Function Description	Setup timer match 2 and internal action and TIM_MAT2/ TIM_MAT2 output external action when match even occurs
Input Parameters	*ct: pointer to TIM2/TIM3
ticks: match 2 value
internalaction: combination of following action when counter reach match value
		TIM_MATCH_TRIGGER_INT 0x1
		TIM_MATCH_RESET_COUNTER 0x2
		TIM_MATCH_STOP_COUNTER 0x4
		TIM_MATCH_DO_NOTHING 0x0 
externalaction: one of following action when counter reach match value
		TIM_MATCH_OUT_DO_NOTHING 0x0
		TIM_MATCH_OUT_RESET 0x1
		TIM_MATCH_OUT_SET	 0x2
		TIM_MATCH_OUT_TRIGGER_PLUS	 0x3
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_ConfigMatch2(HHD32F1_TIM_TypeDef *ct, uint16_t ticks, uint8_t internalaction,
                      uint8_t externalaction)
{
	ct->MR2.bit.MATCH=ticks;
	ct->MCR.all=(ct->MCR.all&(~(0x7<<6)))|((internalaction&0x7)<<6);
	
	ct->EMR.bit.EMC2=externalaction;
	ct->EMR.bit.EM2=1;		
	return;
}
/*****************************************************************************
Function Name	TIM_ConfigMatch3
Function Definition	void TIM_ConfigMatch3(G32F1_TIM_TypeDef *ct, uint16_t ticks, uint8_t internalaction, uint8_t externalaction)
Function Description	Setup timer match 3 and internal action and TIM_MAT3/ TIM_MAT3 output external action when match even occurs
Input Parameters	*ct: pointer to TIM2/TIM3
ticks: match 3 value
internalaction: combination of following action when counter reach match value
		TIM_MATCH_TRIGGER_INT 0x1
		TIM_MATCH_RESET_COUNTER 0x2
		TIM_MATCH_STOP_COUNTER 0x4
		TIM_MATCH_DO_NOTHING 0x0 
externalaction: one of following action when counter reach match value
		TIM_MATCH_OUT_DO_NOTHING 0x0
		TIM_MATCH_OUT_RESET 0x1
		TIM_MATCH_OUT_SET	 0x2
		TIM_MATCH_OUT_TRIGGER_PLUS	 0x3
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_ConfigMatch3(HHD32F1_TIM_TypeDef *ct, uint16_t ticks, uint8_t internalaction,
                      uint8_t externalaction)
{
	ct->MR1.bit.MATCH=ticks;
	ct->MCR.all=(ct->MCR.all&(~(0x7<<9)))|((internalaction&0x7)<<9);
	
	ct->EMR.bit.EMC3=externalaction;
	ct->EMR.bit.EM3=1;			
	return;
}

/*****************************************************************************
Function Name	TIM_ConfigCapture0
Function Definition	void TIM_ConfigCapture0 (G32F1_TIM_TypeDef *ct, uint8_t edge, uint8_t intreq)
Function Description	Set up Capture 0 
Input Parameters	*ct: pointer to TIM2/TIM3
edge: CAP0 signal edge, RISE_EDGE/FALL_EDGE/BOTH_EDGE. Deifned in sys.h
intreq: interrupt request
			TIM_CAPTURE_DO_NOTHING
			TIM_CAPTURE_TRIGGER_INT
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_ConfigCapture0(HHD32F1_TIM_TypeDef *ct, uint8_t edge, uint8_t intreq)
{
	switch(edge)
	{
		case RISE_EDGE:
				ct->CCR.bit.CAP0RE=1;
				ct->CCR.bit.CAP0FE=0;
			break;
		case FALL_EDGE:
				ct->CCR.bit.CAP0RE=0;
				ct->CCR.bit.CAP0FE=1;
			break;
		case BOTH_EDGE:
				ct->CCR.bit.CAP0RE=1;
				ct->CCR.bit.CAP0FE=1;
			break;
		default:
			break;
	}
	if (intreq==TIM_CAPTURE_TRIGGER_INT)
		ct->CCR.bit.CAP0I=1;
	else
		ct->CCR.bit.CAP0I=0;
	return;
}
/*****************************************************************************
Function Name	TIM_ConfigCapture1
Function Definition	void TIM_ConfigCapture1 (HHD32F1_TIM_TypeDef *ct, uint8_t edge, uint8_t intreq)
Function Description	Set up Capture 1
Input Parameters	*ct: pointer to TIM2/TIM3
edge: CAP0 signal edge, RISE_EDGE/FALL_EDGE/BOTH_EDGE. Deifned in sys.h
intreq: interrupt request
			TIM_CAPTURE_DO_NOTHING
			TIM_CAPTURE_TRIGGER_INT
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_ConfigCapture1(HHD32F1_TIM_TypeDef *ct, uint8_t edge, uint8_t intreq)
{
	switch(edge)
	{
		case RISE_EDGE:
				ct->CCR.bit.CAP1RE=1;
				ct->CCR.bit.CAP1FE=0;
			break;
		case FALL_EDGE:
				ct->CCR.bit.CAP1RE=0;
				ct->CCR.bit.CAP1FE=1;
			break;
		case BOTH_EDGE:
				ct->CCR.bit.CAP1RE=1;
				ct->CCR.bit.CAP1FE=1;
			break;
		default:
			break;
	}
	if (intreq==TIM_CAPTURE_TRIGGER_INT)
		ct->CCR.bit.CAP1I=1;
	else
		ct->CCR.bit.CAP1I=0;
	return;
}
/*****************************************************************************
Function Name	TIM_ConfigCapture2
Function Definition	void TIM_ConfigCapture2 (HHD32F1_TIM_TypeDef *ct, uint8_t edge, uint8_t intreq)
Function Description	Set up Capture 2
Input Parameters	*ct: pointer to TIM2/TIM3
edge: CAP0 signal edge, RISE_EDGE/FALL_EDGE/BOTH_EDGE. Deifned in sys.h
intreq: interrupt request
			TIM_CAPTURE_DO_NOTHING
			TIM_CAPTURE_TRIGGER_INT
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_ConfigCapture2(HHD32F1_TIM_TypeDef *ct, uint8_t edge, uint8_t intreq)
{
	switch(edge)
	{
		case RISE_EDGE:
				ct->CCR.bit.CAP2RE=1;
				ct->CCR.bit.CAP2FE=0;
			break;
		case FALL_EDGE:
				ct->CCR.bit.CAP2RE=0;
				ct->CCR.bit.CAP2FE=1;
			break;
		case BOTH_EDGE:
				ct->CCR.bit.CAP2RE=1;
				ct->CCR.bit.CAP2FE=1;
			break;
		default:
			break;
	}
	if (intreq==TIM_CAPTURE_TRIGGER_INT)
		ct->CCR.bit.CAP2I=1;
	else
		ct->CCR.bit.CAP2I=0;
	return;
}
/*****************************************************************************
Function Name	TIM_ConfigCapture3
Function Definition	void TIM_ConfigCapture3 (G32F1_TIM_TypeDef *ct, uint8_t edge, uint8_t intreq)
Function Description	Set up Capture 3 
Input Parameters	*ct: pointer to TIM2/TIM3
edge: CAP0 signal edge, RISE_EDGE/FALL_EDGE/BOTH_EDGE. Deifned in sys.h
intreq: interrupt request
			TIM_CAPTURE_DO_NOTHING
			TIM_CAPTURE_TRIGGER_INT
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_ConfigCapture3(HHD32F1_TIM_TypeDef *ct, uint8_t edge, uint8_t intreq)
{
	switch(edge)
	{
		case RISE_EDGE:
				ct->CCR.bit.CAP3RE=1;
				ct->CCR.bit.CAP3FE=0;
			break;
		case FALL_EDGE:
				ct->CCR.bit.CAP3RE=0;
				ct->CCR.bit.CAP3FE=1;
			break;
		case BOTH_EDGE:
				ct->CCR.bit.CAP3RE=1;
				ct->CCR.bit.CAP3FE=1;
			break;
		default:
			break;
	}
	if (intreq==TIM_CAPTURE_TRIGGER_INT)
		ct->CCR.bit.CAP3I=1;
	else
		ct->CCR.bit.CAP3I=0;
	return;
}
/*****************************************************************************
Function Name	TIM_GetCapture0Value
Function Definition	void TIM_GetCapture0Value(G32F1_TIM_TypeDef *ct)
Function Description	Return timer Capture 0 register value
Input Parameters	*ct: pointer to TIM2/TIM3
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
uint16_t TIM_GetCapture0Value (HHD32F1_TIM_TypeDef *ct)
{
	return ct->CR0.bit.CAP;
}
/*****************************************************************************
Function Name	TIM_GetCapture1Value
Function Definition	void TIM_GetCapture1Value(G32F1_TIM_TypeDef *ct)
Function Description	Return timer Capture 1 register value
Input Parameters	*ct: pointer to TIM2/TIM3
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
uint16_t TIM_GetCapture1Value (HHD32F1_TIM_TypeDef *ct)
{
	return ct->CR1.bit.CAP;
}
/*****************************************************************************
Function Name	TIM_GetCapture2Value
Function Definition	void TIM_GetCapture2Value(G32F1_TIM_TypeDef *ct)
Function Description	Return timer Capture 2 register value
Input Parameters	*ct: pointer to 
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
uint16_t TIM_GetCapture2Value (HHD32F1_TIM_TypeDef *ct)
{
	return ct->CR2.bit.CAP;
}
/*****************************************************************************
Function Name	TIM_GetCapture3Value
Function Definition	void TIM_GetCapture3Value(G32F1_TIM_TypeDef *ct)
Function Description	Return timer Capture 3 register value
Input Parameters	*ct: pointer to 
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
uint16_t TIM_GetCapture3Value (HHD32F1_TIM_TypeDef *ct)
{
	return ct->CR3.bit.CAP;
}

/*****************************************************************************
Function Name	TIM_START
Function Definition	void TIM_START(G32F1_TIM_TypeDef *ct)
Function Description	
Input Parameters	*ct: pointer to 
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_START (HHD32F1_TIM_TypeDef *ct)
{
	ct->TCR.bit.CEN = 1;
}

/*****************************************************************************
Function Name	TIM_STOP
Function Definition	void TIM_STOP(G32F1_TIM_TypeDef *ct)
Function Description	
Input Parameters	*ct: pointer to 
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_STOP(HHD32F1_TIM_TypeDef *ct)
{
	ct->TCR.bit.CEN = 0;
}

/*****************************************************************************
Function Name	TIM_RESET
Function Definition	void TIM_RESET(G32F1_TIM_TypeDef *ct)
Function Description	
Input Parameters	*ct: pointer to 
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void TIM_RESET(HHD32F1_TIM_TypeDef *ct)
{
	ct->TCR.bit.CRST = 1;
	ct->TCR.bit.CRST = 0;
}


