/* Includes ------------------------------------------------------------------*/

#include "hhd32f1xx.h"
#include "hhd_timer.h"
#include "hhd_sys.h"

extern uint32_t SystemCoreClock;
/*****************************************************************************
Function Name	SYS_SystemInitial
Function Definition	void SYS_SystemInitial(void)
Function Description	Initial system-configure clocl, IO pin function
Input Parameters	*ct: pointer to TIM0/TIM1
tickpersecond: timer count frequency, less than system clock
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			
*****************************************************************************/
void SYS_SystemInitial(void)
{
    SystemInit();

    //Configure MainClock and SystemClock(defaul MainClock=40MHz and SystemClock=20MHz)
//    SYSCON->IRCCTRL.all = HHD_CIB->IRCTRIM;
    SYSCON->INTNMI.all = 255;

    //Configure WDT clock if need

    //Configure RTC clock if need
#ifdef ENABLE_RTCOSC
    IOCON->PC14.all = 0x101;						  //Enable RTC OSC PIN
    IOCON->PC15.all = 0x101;						  //Enable RTC OSC PIN
    SYSCON->PDRUNCFG.bit.RTCOSC_PD = 0; 		//Enable RTC OSC Power
    PMU->RTCCFG.bit.RTCCLK = 0; 						//Select RTC Source clock type: 1Hz
#endif


	//Configure peripheral IO pin
	
	#ifdef ENABLE_UART0
	/**********UART0************************************************************/
	//RXD0 	v	v	v	v	I	PA3 	PA10
	IOCON->PA3.all=0x233;
	//TXD0 	v	v	v	v	O	PA2 	PA9 
	IOCON->PA2.all=0x233;

	#endif
	
	/**********UART1************************************************************/
	//RXD1 	v	v	v		I	PA15 	PB7
	//TXD1 	v	v	v		O	PA14	PB6 

	
	/**********TIM2************************************************************/
	//TIM2_CAP0 	v	v	v	v	I	PA6	PB4
	//TIM2_CAP1 	v		v	v	I	PA7	PB5
	//TIM2_CAP2 	v	v	v		I	PB0	PA11
	//TIM2_CAP3 	v		v		I	PB1	PB14
	//TIM2_MAT0 	v	v	v	v	O	PA6 PB4
	//TIM2_MAT1	  v		v	v	O	PA7	PB5
	//TIM2_MAT2 	v	v	v		O	PB0	PA11
	//TIM2_MAT3	  v		v		I	PB1	PB14

	
	/**********TIM3************************************************************/
	//TIM3_CAP0 	v	v	v	v	I	PA2 	PB6
	//TIM3_CAP1 	v	v	v	v	I	PA3	PB7
	//TIM3_CAP2	v		v	v	I	PA4	PB8
	//TIM3_CAP3	v	v	v		I	PB15	PA8
	//TIM3_MAT0 	v	v	v	v	O	PA2 	PB6
	//TIM3_MAT1 	v	v	v	v	O	PA3	PB7
	//TIM3_MAT2	v		v	v	O	PA4	PB8
	//TIM3_MAT3	v	v	v		O	PB15	PA8

	#ifdef ENABLE_SPI
	/**********SPI***************************************************************/
	//SSEL 	v	v	v	v	I/O	PA4	P0_15	PB12
	IOCON->PA15.all=0x231;				 //ssel
	//SCK 	v	v	v	v	I/O	PA5	P1_3	PB13
	IOCON->PB3.all=0x231;				 //sck
	//MISO 	v	v	v	v	I/O	PA6	P1_4	PB14
	IOCON->PB4.all=0x231;				 //miso
	//MOSI 	v	v	v	v	I/O	PA7	P1_5	PB15
	IOCON->PB5.all=0x231;				 //mosi
	#endif
	
	#ifdef ENABLE_IIC
	/**********IIC************************************************************/
	//SCL 	v	v	v	v	I/O	PB10 	PA9 	PB8	PC10 	PB6
	IOCON->PB8.all=0x231;
	//SDA 	v	v	v	v	I/O	PB11 	PA10 	PB9	PC11	PB7
	IOCON->PB9.all=0x231;
	#endif
	
	#ifdef ENABLE_ADC
	/**********ADC************************************************************/
	//AD0	v	v	v	v	I	PA0 
	IOCON->PA0.all=0x102;
	//AD1 	v	v	v	v	I	PA1 
	//IOCON->PA1.all=0x102;
	//AD2 	v	v	v	v	I	PA2 
	//IOCON->PA2.all=0x105;
	//AD3 	v	v	v	v	I	PA3 
	//IOCON->PA3.all=0x105;
	//AD4 	v	v	v	v	I	PA4 
	//IOCON->PA4.all=0x105;
	//AD5 	v	v	v	v	I	PA5 
	//IOCON->PA5.all=0x103;
	//AD6 	v	v	v	v	I	PA6 
	//IOCON->PA6.all=0x106;
	//AD7 	v	v	v	v	I	PA7 
	//IOCON->PA7.all=0x106;
	#endif
	

	
	#ifdef ENABLE_PWM
	/**********PWM************************************************************/
	//PWM_OUT0	v	v	v		O	PA8
	IOCON->PA8.all = 0x231;
	//PWM_OUT1	v	v	v	v	O	PA7	PB13
	IOCON->PA7.all = 0x231;
	//PWM_OUT2	v	v	v	v	O	PA9	
	IOCON->PA9.all = 0x231;
	//PWM_OUT3	v	v	v		O	PB0	PB14
	IOCON->PB0.all = 0x231;
	//PWM_OUT4	v	v	v	v	O	PA10	
	IOCON->PA10.all = 0x231;
	//PWM_OUT5	v	v	v	v	O	PB1	PB15
	IOCON->PB1.all = 0x231;
	//PWM_FAULT	v	v	v	v	I	PA6	PB12
	#endif
	
	
	return;
}
/*****************************************************************************
Function Name	SYS_SelectMainClkSrc
Function Definition	Void SYS_SelectMainClkSrc(uint8_t src)
Function Description	Select Main clcok source
Input Parameters	src:IRC_CLK
								WDT_CLK
Other are invalid
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_SelectMainClkSrc(uint8_t src)
{
	//switch main clk source
	SYSCON->MAINCLKUEN.bit.ENA= 1;					//disable main clk update
	//switch main clk source to Specifyed source
	if (src==IRC_CLK)
		SYSCON->MAINCLKSEL.bit.SEL=0;
	else if (src==WDT_CLK)
		SYSCON->MAINCLKSEL.bit.SEL=2; 	
	SYSCON->MAINCLKUEN.bit.ENA=0; 						//enable main clk update
	
	SystemCoreClockUpdate ();
	return;
}
/*****************************************************************************
Function Name	SYS_SetAHBClkDivider
Function Definition	Void SYS_SetAHBClkDivider (uint8_t div)
Function Description	Set divider, that divides the main clock to provide the system clock to the core, memories,and the peripherals.
Input Parameters	div:1~255, 0 is forbidented
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_SetAHBClkDivider (uint8_t div)
{
// 	if (((*SYSCON).MAINCLKSEL.bit.SEL==0)&&(div<2))
// 			(*FMC).FLASH_RDCYC = 1;
	
	(*SYSCON).SYSAHBCLKDIV.bit.DIV = div;
	SystemCoreClockUpdate ();   
	return;
}
/*****************************************************************************
Function Name	SYS_SelectWDTClkSrc
Function Definition	Void SYS_SelectWDTClkSrc(uint8_t src)
Function Description	Select clock source as WDT counter clock.
Input Parameters	src:IRC_CLK
WDT_CLK
Other are invalid
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_SelectWDTClkSrc(uint8_t src)
{
	if (src==IRC_CLK)
		(*SYSCON).WDTOSCCTRL.bit.WDTCLKSRC = 0;
	else if (src==WDT_CLK)
		(*SYSCON).WDTOSCCTRL.bit.WDTCLKSRC = 1;
 
	return;
}

/*****************************************************************************
Function Name	SYS_SelectClkOutSrc
Function Definition	SYS_SelectClkOutSrc(uint8_t src)
Function Description	Select clock source as clock output
Input Parameters	src:IRC_CLK
											SYS_CLK
											WDT_CLK
											MAIN_CLK
											RTC_CLK
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_SelectClkOutSrc(uint8_t src)
{
	switch (src)
	{
		case IRC_CLK:
			src=0;
		break;
		case SYS_CLK:
			src=1;
		break;
		case WDT_CLK:
			src=2;
		break;
		case MAIN_CLK:
			src=3;
		break;
		case RTC_CLK:
			src=4;
		break;
		default:
			return;
	}
	//switch clock
	(*SYSCON).CLKOUTUEN.bit.ENA = 1;
	(*SYSCON).CLKOUTCLKSEL.bit.SEL = src; 	//select clk out source
	(*SYSCON).CLKOUTUEN.bit.ENA = 0;
 
	return;
}

/*****************************************************************************
Function Name	SYS_SetClkOutDivider
Function Definition	SYS_SetClkOutDivider(uint8_t src)
Function Description	Select clock source as clock output
Input Parameters	div:Clock output divider, valid 1~255 
											0: clock is disable
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_SetClkOutDivider(uint8_t div)
{
	(*SYSCON).CLKOUTDIV.bit.DIV = div;
 
	return;
}

/*****************************************************************************
Function Name	SYS_EnableClkOut
Function Description	Enable clock output
Input Parameters	No
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_EnableClkOut(void)
{
	(*IOCON).PA8.all = 0x235;   							//enable clock out pin 
 
	return;
}

/*****************************************************************************
Function Name	SYS_DisableClkOut
Function Definition	Void SYS_DisableClkOut(void)
Function Description	Disable clock output
Input Parameters	No
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_DisableClkOut(void)
{
	(*SYSCON).CLKOUTDIV.bit.DIV = 0;
	(*IOCON).PC8.all = 0x230;   							//enable clock out pin 
 
	return;
}
/*****************************************************************************
Function Name	SYS_SetIOFilter
Function Definition	Void SYS_SetIOFilter(uint8_t ticks)
Function Description	Set IO filter 
Input Parameters	Ticks: 1~255, every ticks sample IO input
0, no sample
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_SetIOFilter(uint8_t ticks)
{
	(*SYSCON).IOCONFIGCLKDIV.bit.DIV = ticks;
 
	return;
}
/*****************************************************************************
Function Name	SYS_PowerDownAngIP
Function Definition	SYS_PowerDownAngIP(uint32_t angips)
Function Description	Shut down specific analog IPs power supply
Input Parameters	Angips: analog IPs bit
Valid bit values are PD_IRC, PD_BOD, PD_ADC, PD_RTC, PD_WDTOSC, PD_LCD, PD_TOUCH
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_PowerDownAngIP(uint32_t angips)
{
	(*SYSCON).PDRUNCFG.all |= angips;
 
	return;
}
/*****************************************************************************
Function Name	SYS_PowerUpAngIP
Function Definition	SYS_PowerUpAngIP(uint32_t angips)
Function Description	Power up specific analog IPs power supply
Input Parameters	Angips: analog IPs bit 
Valid bit values are PD_IRC, PD_BOD, PD_ADC, PD_RTC, PD_WDTOSC, PD_LCD, PD_TOUCH
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_PowerUpAngIP(uint32_t angips)
{
	(*SYSCON).PDRUNCFG.all &= ~angips;
 
	return;
}
/*****************************************************************************
Function Name	SYS_EnablePhrClk
Function Definition	void SYS_EnablePhrClk(uint32_t phrs)
Function Description	Enable specific peripherals clock
Input Parameters	phrs: peripherals clock bit 
Valid bit values are AHB_IIC, AHB_CRC, AHB_TIM0, AHB_TIM1, AHB_TIM2, 
	AHB_TIM3, AHB_SPI, AHB_UART0, AHB_UART1,AHB_ADC, AHB_WDT, AHB_IOCON, 
	AHB_PWM,AHB_LCD, AHB_RTC,AHB_TOUCH 
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_EnablePhrClk(uint32_t phrs)
{
	(*SYSCON).SYSAHBCLKCTRL.all  |= phrs;
  (*SYSCON).SYSAPB2CLKCTRL.all |= phrs;
	(*SYSCON).SYSAPB1CLKCTRL.all |= phrs;
	return;
}
/*****************************************************************************
Function Name	SYS_DisablePhrClk
Function Definition	void SYS_DisablePhrClk(uint32_t phrs)
Function Description	Disable specific peripherals clock
Input Parameters	phrs: peripherals clock bit 
Valid bit values are AHB_IIC, AHB_CRC,  AHB_TIM1, AHB_TIM2, 
AHB_TIM3, AHB_SPI, AHB_UART1,AHB_ADC, AHB_WDT, AHB_IOCON, 
AHB_PWM,AHB_LCD, AHB_RTC,AHB_TOUCH 
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_DisablePhrClk(uint32_t phrs)
{
	(*SYSCON).SYSAHBCLKCTRL.all &= ~phrs;
 
	return;
}
/*****************************************************************************
Function Name	SYS_ResetPhr
Function Definition	void SYS_ResetPhr(uint32_t phrs)
Function Description	Reset specific peripherals 
Input Parameters	phrs: peripherals clock bit 
Valid bit values are RTS_IIC, RST_CRC, RST_TIM0, RST_TIM1, RST_TIM2, 
RST_TIM3, RST_SPI, RST_UART0, RST_UART1,RST_ADC, RST_WDT, 
RST_IOCON, RST_PWM,RST_LCD, RST_RTC,RST_TOUCH 
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_ResetPhr(uint32_t phrs)
{
	(*SYSCON).APB2RESET.all &= ~phrs;
	(*SYSCON).APB2RESET.all |= phrs;
	(*SYSCON).APB1RESET.all &= ~phrs;
	(*SYSCON).APB1RESET.all |= phrs;
	return;
}
/*****************************************************************************
Function Name	SYS_ResetSystem
Function Definition	void SYS_ResetSystem(void)
Function Description	Software Reset system
Input Parameters	No
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_ResetSystem(void)
{
//	NVIC_SystemReset();
	
	*(uint32_t *)0xE000ED0C = 0x05FA0004;
	
	
}
/*****************************************************************************
Function Name	SYS_BODResetSystem
Function Definition	void SYS_BODResetSystem (uint8_t bodsel)
Function Description	Enable BOD and config BOD Reset option
Input Parameters	Bodsel: 
BOD_INT
BOD_RESET
Other values are invalid
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_BODResetSystem (uint8_t bodsel)
{
	if (bodsel==BOD_RESET)
	{
		SYSCON->BODCTRL.bit.BODRSTEN=1 ;
	}
	else
	{
		SYSCON->BODCTRL.bit.BODRSTEN = 0 ;
		SYSCON->BODCTRL.bit.BODINTCLR = 1;
	}
	return;
}
/*****************************************************************************
Function Name	SYS_GetResetStatus
Function Definition	uint32_t SYS_GetResetStatus(void)
Function Description	Return reset status
Input Parameters	No
Return Value	Reset status
				Bit0 	POR 
				Bit1 	EXTRST
				Bit2 	WDT 
				Bit3 	BOD 
				Bit4 	SYSRST
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
uint32_t SYS_GetResetStatus(void)
{
	return SYSCON->SYSRESSTAT.all;
}
/*****************************************************************************
Function Name	SYS_ClearResetStatus
Function Definition	void SYS_ClearResetStatus (void)
Function Description	Clear reset status
Input Parameters	No
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_ClearResetStatus (void)
{
	SYSCON->SYSRESSTAT.all=0xFF;
	return;
}
/*****************************************************************************
Function Name	SYS_EnterSleep
Function Definition	void SYS_EnterSleep (void)
Function Description	Enter sleep mode
Input Parameters	No
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_EnterSleep (void)
{
	//Sleep
	(*PMU).PCON.bit.DPDEN = 0;			//sleep
	SCB->SCR &= ~(1<<2);							//sleep
	
	//issue sleep command
	__WFI();	//enter sleep
	return;
}
/*****************************************************************************
Function Name	SYS_SetDeepSleepWakeupPin
Function Definition	void SYS_SetDeepSleepWakeupPin (uint16_t selio, uint16_t edge)
Function Description	Set deep sleep wake up pin
Input Parameters	Selio:IO_PIN0~PIN11
Edge: FALL_EDGE/RISE_EDGE
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_SetDeepSleepWakeupPin (uint16_t selio, uint16_t edge)
{
	(*SYSCON).EXTIEN.all		= selio;		//enable the pin
	
	if(edge == RISE_EDGE)
	{
		(*SYSCON).EXTICTL.all &=~ selio;
	}
	else
	{
		(*SYSCON).EXTICTL.all	= selio;			//wake up signal
	}
	
	NVIC_EnableIRQ(EXTI0_IRQn); 				//enable Wakeup IRQ
	
	return;
}
/*****************************************************************************
Function Name	SYS_ResetDeepSleepWakeupPin
Function Definition	void SYS_ResetDeepSleepWakeupPin(void)
Function Description	Reset all deep sleep wake pin . The wakeup pin must be reset before use.
Input Parameters	No
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_ResetDeepSleepWakeupPin(void)
{
	(*SYSCON).EXTIEN.all		= 0;
	(*SYSCON).EXTICLR.all	= 0xFFF;			//clear int status

}
/*****************************************************************************
Function Name	SYS_EnterDeepSleep
Function Definition	void SYS_EnterDeepSleep (uint32_t deepsleepconfig, uint32_t wakeupconfig)
Function Description	Enter deep sleep mode
Input Parameters	deepsleepconfig: config PDSLEEPCFG. Avalable bit PD_BOD, PD_RTCOSC and PD_WDTOSC. 
									If WDTOSC_PD bit is not set, the system won't wakeup except power up
			Wakeupconfig: config PDAWAKECFG. Avalable bit PD_IRC, PD_BOD, PD_ADC, PD_RTC, PD_WDTOSC, PD_LCD, PD_TOUCH. 
			If bit is set, the IP will power down after wake up from deep sleep.
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_EnterDeepSleep(uint32_t deepsleepconfig, uint32_t wakeupconfig)
{
	uint32_t i;
	//if WDT osc is not powered, power osc and wait for stable
	if ((*SYSCON).PDRUNCFG.bit.WDTOSC_PD != 0)
	{
		(*SYSCON).PDRUNCFG.bit.WDTOSC_PD = 0;
		
		//wait for a while
		while(i++<0xff);
	}
	
	//set WDT osc as back up clk for powerdown
	(*SYSCON).PDSLEEPCFG.all = deepsleepconfig;
	
	(*SYSCON).PDAWAKECFG.all = wakeupconfig;
	//switch main clk to WDT osc
	(*SYSCON).MAINCLKUEN.bit.ENA = 1;
	(*SYSCON).MAINCLKSEL.bit.SEL = 2;
	(*SYSCON).MAINCLKUEN.bit.ENA = 0;

	//Deep Sleep
	(*PMU).PCON.bit.DPDEN = 1; 		//deep power down
	SCB->SCR |= (1<<2);								//deep sleep
	
	//issue deep sleep command
	__WFI();	//enter deep sleep
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	
	//switch back to IRC
	(*SYSCON).MAINCLKUEN.bit.ENA = 1;
	(*SYSCON).MAINCLKSEL.bit.SEL = 0;
	(*SYSCON).MAINCLKUEN.bit.ENA = 0;

	return;
}
/*****************************************************************************
Function Name	SYS_EnterPowerDown
Function Definition	void SYS_EnterPowerDown (uint32_t powerdownconfig)
Function Description	Enter sleep mode
Input Parameters	powerdownconfig : config PDSLEEPCFG. Avalable bit  PD_RTCOSC . 
	If bit is set, the IP will power down duing deep sleep.
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_EnterPowerDown(uint32_t powerdownconfig)
{
	if (powerdownconfig & PD_RTCOSC)
		(*SYSCON).PDSLEEPCFG.bit.RTCOSC_PD	=0;
	else
		(*SYSCON).PDSLEEPCFG.bit.RTCOSC_PD	= 1;
	
	(*SYSCON).PDSLEEPCFG.bit.BOD_PD = 1;
	(*SYSCON).PDSLEEPCFG.bit.WDTOSC_PD	= 1;
	
	//Power Down
	(*PMU).PCON.bit.DPDEN = 1;
	
	SCB->SCR |= (1<<2);	//deep sleep	
	__WFI();	//enter power down
}
/*****************************************************************************
Function Name	SYS_IOConfig
Function Definition	void SYS_IOConfig(IOCON_REG *pio, uint32_t config)
Function Description	Config IO pin
Input Parameters	*pio : pointer to IOCON. IOCON->PA0~ IOCON->PA15, IOCON->PB0~ IOCON->PB15, IOCON->PC7~ IOCON->PA15
Config: IO config value
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_IOConfig(union IOCON_REG *pio, uint32_t config)
{
	pio->all=config;
	return;
}
/*****************************************************************************
Function Name	SYS_IOSetPullup
Function Definition	void SYS_IOSetPullup(IOCON_REG *pio)
Function Description	Config IO pin pull up
Input Parameters	*pio : pointer to IOCON’s IO. IOCON->PA0~ IOCON->PA15, IOCON->PB0~ IOCON->PB15, IOCON->PC7~ IOCON->PA15
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_IOSetPullup(union IOCON_REG *pio)
{
	pio->bit.PDE=0;
	pio->bit.PUE=1;
	
	return;
}
/*****************************************************************************
Function Name	SYS_IOSetPulldown
Function Definition	void SYS_IOSetPulldown (IOCON_REG *pio)
Function Description	Config IO pin pull down
Input Parameters	*pio : pointer to IOCON’s IO. IOCON->PA0~ IOCON->PA15, IOCON->PB0~ IOCON->PB15, IOCON->PC7~ IOCON->PA15
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_IOSetPulldown (union IOCON_REG *pio)
{
	pio->bit.PUE=0;
	pio->bit.PDE=1;
	return;
}

/*****************************************************************************
Function Name	SYS_IOEnableFilter
Function Definition	void SYS_IOEnableFilter (IOCON_REG *pio)
Function Description	Enable IO pin filter function
Input Parameters	*pio : pointer to IOCON’s IO. IOCON->PA0~ IOCON->PA15, IOCON->PB0~ IOCON->PB15, IOCON->PC7~ IOCON->PA15
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_IOEnableFilter (union IOCON_REG *pio)
{
	pio->bit.S_MODE=1;
	return;
}
/*****************************************************************************
Function Name	SYS_ IODisableFilter
Function Definition	void SYS_ IODisableFilter (IOCON_REG *pio)
Function Description	Disable IO pin filter function
Input Parameters	*pio : pointer to IOCON’s IO. IOCON->PA0~ IOCON->PA15, IOCON->PB0~ IOCON->PB15, IOCON->PC7~ IOCON->PA15
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12			By:
*****************************************************************************/
void SYS_IODisableFilter (union IOCON_REG *pio)
{
	pio->bit.S_MODE=0;
	return;
}

