/*****************************************************************************
 *   gt_uart.h:  Header file for Gorgetek G32F1xx
 *
 *   Copyright(C) 2015, Gorge Technology
 *   All rights reserved.
 *
 *   History
 *   2015.01.21  ver 1.0    Prelimnary version
 *
******************************************************************************/
//#define __UART0

#ifndef __UART_H 
#define __UART_H
#include "g32f1xx.h"
//stauts and int bit
#define UART_NO_PARITY    0x0 
#define UART_EVEN_PARITY  0x1
#define UART_ODD_PARITY   0x2
#define UART_RX_NO_INT    0x0
#define UART_TX_EMPTY     0x1
#define UART_RX_NOT_EMPTY 0x2
#define UART_TX_FULL      0x4 
#define UART_RX_FULL      0x8
#define UART_TX_HALF_FULL 0x10 
#define UART_RX_HALF_FULL 0x20
#define UART_PARIERRINT   0x40 
#define UART_OVERRUNINT   0x80

//--UART Registers BITS Field---------------------------------------------------------------------------------------
struct UARTDAT_BITS	{
				uint32_t DATA:8;							// 7:0 UART receiver buffer register
				uint32_t RSVD:24;						  // 31:8 reserved
};
union UARTDAT_REG {
				uint32_t					all;
				struct  UARTDAT_BITS		bit;
};

struct UARTSTATE_BITS {
				uint32_t STATE:1; 		        //Transmit FIFO  empty flag
				uint32_t RSVD3:31;						// 31:8 reserved
};
union UARTSTATE_REG {
				uint32_t					all;
				struct UARTSTATE_BITS		bit;
};

struct UARTCTRL_BITS {
				uint32_t PARIEN:1;		        //Parity Check enable
				uint32_t INVMOD:1;		        //Inverse mode enable
				uint32_t TMODE:1;		          //T mode
				uint32_t FTIME:2;		          //Force Time
				uint32_t RSVD1:27;
};
union UARTCTRL_REG {
				uint32_t					all;
				struct UARTCTRL_BITS		bit;
};

struct TRANSSTATUS_BITS {
				uint32_t TXRESEND:1;		        //TX resend request
				uint32_t PTYERR:1;		          //Parity check error.
				uint32_t RSVD1:30;
};
union TRANSSTATUS_REG {
				uint32_t					all;
				struct TRANSSTATUS_BITS		bit;
};

struct FIFOSTATUS_BITS {
				uint32_t FIFOFULL:1;		        //FIFO full
				uint32_t FIFOEMPTY:1;		        //FIFO empty
				uint32_t RSVD1:30;
};
union FIFOSTATUS_REG {
				uint32_t					all;
				struct FIFOSTATUS_BITS		bit;
};



struct UARTINTSTATUS_BITS {
				uint32_t TXEINT:1;		//Interrupt status. The interrupt occurs when data transmit completed. 
				uint32_t RXNEINT:1;		//Interrupt status. The interrupt occurs when received data. 
				uint32_t RSINT:1;		  //Interrupt status. The interrupt occurs when detect RX start bit.
				uint32_t RSVD:24;	
};
union UARTINTSTATUS_REG {
				uint32_t									all; 
				struct UARTINTSTATUS_BITS	bit;
};

union UARTRAWINTSTATUS_REG {
				uint32_t									all; 
				struct UARTINTSTATUS_BITS	bit;
};
struct UARTBAUDDIV_BITS {
				uint32_t  BAUDDIV:11;					// 11:0 baud-rate generation pre-scalar divisor value  0x10
				uint32_t  RSVD1:21;						// 31:12  reserved
};
union UARTBAUDDIV_REG {
				uint32_t									all; 
				struct  UARTBAUDDIV_BITS	bit;
};



typedef struct
{
	__IO   union UARTDAT_REG				DAT;				/*!< Offset: 0x000 Write Data Register    (R/W) 	 */
	__IO   union UARTDAT_REG				RDAT;				/*!< Offset: 0x004 Read Data Register    (R/W) 		 */
	__IO   union UARTSTATE_REG			TXSTAT;			/*!< Offset: 0x008 Status Register  (R/W) 				 */
	__IO   union UARTSTATE_REG			RXSTAT;			/*!< Offset: 0x00c Status Register  (R/W) 				 */
	__IO   union UARTSTATE_REG			STARTDET;	  /*!< Offset: 0x010 Status Register  (R/W) 				 */
	__IO   union UARTSTATE_REG			CLRTXSTAT;	/*!< Offset: 0x014 Status Register  (R/W) 				 */
	__IO   union UARTSTATE_REG			CLRRXSTAT;	/*!< Offset: 0x018 Status Register  (R/W) 				 */
	__IO   union UARTSTATE_REG			CLRSTARTDET;/*!< Offset: 0x01c Status Register  (R/W) 				 */
	__IO   union TRANSSTATUS_REG		TRANSSTATUS;/*!< Offset: 0x020 Status Register  (R/W) 				 */
	__IO   union FIFOSTATUS_REG			FIFOSTATUS; /*!< Offset: 0x024 Status Register  (R/W) 				 */
	__IO   union UARTINTSTATUS_REG	INTMASK;	  /*!< Offset: 0x028 Interrupt Mask         				 */
	__IO   union UARTCTRL_REG				CTRL;				/*!< Offset: 0x02C Control Register (R/W) 				 */
	__IO   union UARTBAUDDIV_REG		BAUDDIV;		/*!< Offset: 0x030 Baudrate Divider Register (R/W) */
	__IO   union UARTINTSTATUS_REG	RAWINT;	  	/*!< Offset: 0x034 Raw interrupt status 					 */
	__IO   union UARTINTSTATUS_REG	INTSTATUS;	/*!< Offset: 0x038 Interrupt Status     					 */
} G32F1_UART7816_TypeDef;

#define UART4       ((G32F1_UART7816_TypeDef     *) GT_UART4_BASE)
#define UART5       ((G32F1_UART7816_TypeDef     *) GT_UART5_BASE)



#define UART4_TX_to_PC10	 0x1;
#define UART4_RX_from_PC11 0x1;

#define UART5_TX_to_PC12	 0x1;
#define UART5_RX_from_PD2  0x1;

void UART7816_Open(G32F1_UART7816_TypeDef *uart, uint32_t baudrate, uint8_t parityoption, uint8_t rxinttriggerlevel);
void UART7816_Close(G32F1_UART7816_TypeDef *uart);
uint8_t UART7816_ByteRead(G32F1_UART7816_TypeDef *uart, uint8_t *data);
void UART7816_Read(G32F1_UART7816_TypeDef *uart, uint8_t * rxbuf, uint8_t *readBytes);
uint8_t UART7816_ByteWrite(G32F1_UART7816_TypeDef *uart, uint8_t data);
uint8_t UART7816_Write(G32F1_UART7816_TypeDef *uart, uint8_t * txbuf, uint32_t writebytes);
void UART7816_Send(G32F1_UART7816_TypeDef *uart, uint8_t * txbuf, uint32_t sendbytes);
void UART7816_PutString (G32F1_UART7816_TypeDef *uart, uint8_t * str);
void UART7816_PutHex (G32F1_UART7816_TypeDef *uart, uint32_t data);
void UART7816_EnableInt(G32F1_UART7816_TypeDef *uart, uint32_t intcon);
void UART7816_DisableInt(G32F1_UART7816_TypeDef *uart);
void UART7816_ClearIntFlag(G32F1_UART7816_TypeDef *uart);
uint8_t UART7816_GetStatus(G32F1_UART7816_TypeDef*uart);


#endif /* end __UART_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
