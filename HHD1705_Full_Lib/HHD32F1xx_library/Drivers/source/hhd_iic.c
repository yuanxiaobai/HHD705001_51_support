/*****************************************************************************
 *   hhd_iic:  Sourse file for  MCU IIC(I2C compatible) application
 *
 *   Copyright(C) 2012,  Technology
 *   All rights reserved.
 *
 *   History
 *   2012.08.14  ver 1.00
 *
******************************************************************************/

#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_iic.h"


//#define SYS_CLK 10000 // Default clock is 10MHz
extern uint32_t SystemClock;

extern IIC_CtrlBlk_TypeDef I2C1Ctrl;
extern IIC_CtrlBlk_TypeDef I2C2Ctrl;
IIC_CtrlBlk_TypeDef IIC1_CtrlBlk;
IIC_CtrlBlk_TypeDef IIC2_CtrlBlk;

// uint8_t SlaveSendArry[8] = {0xaa,0x11, 0x22, 0x33, 0x44, 0x55, 0x66,0xff};
//uint8_t SlaveSendArry[3] = {0xCC,0x11, 0x33};

unsigned char index = 0;
void SendArry(unsigned char *buff, unsigned int len)
{
    unsigned int i = 0;
    for(; i < len; i++)
    {
        IIC_SendByte(I2C2, *(buff + i));
    }
}
/*****************************************************************************
** Function name:		IIC initial
**
** Descriptions:		IIC initial function
**
** parameters:      Mode: 1---Master 0---Slave
**                  ClockRate: unit in KHz
**                  SlaveAddress: Slave address in slave mode
**                  IICInterrupt: 1---Enable IIC Interrupt 0---Disable IIC Interrupt
**
** Returned value:	None
** 
*****************************************************************************/
void IIC_Init(HHD32F1_IIC_TypeDef *IIC, uint8_t Mode, uint32_t ClockRate, uint32_t SlaveAddress)
{
    /*---  Enable IIC clock and de-assert reset  ---*/
    if(IIC == I2C1)
    {
        SYSCON->APB1RESET.bit.I2C1RSTN      = 1;
        SYSCON->APB1RESET.bit.I2C1RSTN      = 0;
        SYSCON->SYSAPB1CLKCTRL.bit.I2C1CLK  = 1;
    }
    else if(IIC == I2C2)
    {
        SYSCON->APB1RESET.bit.I2C2RSTN      = 1;
        SYSCON->APB1RESET.bit.I2C2RSTN      = 0;
        SYSCON->SYSAPB1CLKCTRL.bit.I2C2CLK  = 1;
    }



    /*--- Clear flags ---*/
    IIC->CONCLR.all = 0xFF;

    /*--- Set Clock rate ---*/
    IIC->SCLH.bit.SCLH = SystemCoreClock / (ClockRate * 2000);
    IIC->SCLL.bit.SCLL = SystemCoreClock / (ClockRate * 2000);

    if (!Mode)
    {
        IIC->ADR0.all = SlaveAddress; // Slave address
    }

    if (Mode)
    {

        IIC->CONSET.all = 0x42; // Master mode
    }
    else
    {
        IIC->DAT.all = 0;
        IIC->CONSET.all = 0x40; // Slave mode
    }

    /* Enable the IIC Interrupt */
    if(IIC == I2C1)
    {
        NVIC_EnableIRQ(I2C1_IRQn);
    }
    else if(IIC == I2C2)
    {
        NVIC_EnableIRQ(I2C2_IRQn);
    }

}


/*****************************************************************************
** Function name:		IIC_GetIICStatus
**
** Descriptions:		Get IIC Status
**
** parameters:      None
**
** Returned value:	None
** 
*****************************************************************************/
uint16_t IIC_GetIICStatus(HHD32F1_IIC_TypeDef *IIC)
{
    return (IIC->STAT.all);
}

/*****************************************************************************
** Function name:		IIC_ReadFlag
**
** Descriptions:		Read IIC Flag
**
** parameters:      Read bit
**
** Returned value:	None
** 
*****************************************************************************/
uint8_t IIC_ReadFlag(HHD32F1_IIC_TypeDef *IIC, uint8_t IIC_CONSET )
{
    return(IIC->CONSET.all & IIC_CONSET);      /* retuen flag */
}

/*****************************************************************************
** Function name:		IIC_SetFlag
**
** Descriptions:		Set IIC Flag
**
** parameters:      Set bit
**
** Returned value:	None
** 
*****************************************************************************/
void IIC_SetFlag(HHD32F1_IIC_TypeDef *IIC, uint8_t IIC_CONSET )
{
	IIC->CONSET.all = IIC_CONSET;      /* Set flag */
}

/*****************************************************************************
** Function name:		IIC_ClearFlag
**
** Descriptions:		Clear IIC Flag
**
** parameters:      Clear bit
**
** Returned value:	None
** 
*****************************************************************************/
void IIC_ClearFlag(HHD32F1_IIC_TypeDef *IIC, uint8_t IIC_CONCLR )
{
	IIC->CONCLR.all = IIC_CONCLR;      /* Clear flag */
}

/*****************************************************************************
** Function name:		IIC_SendByte
**
** Descriptions:		Send Byte
**
** parameters:      Send data
**
** Returned value:	None
** 
*****************************************************************************/
void IIC_SendByte(HHD32F1_IIC_TypeDef *IIC, uint8_t DataByte )
{
	IIC->DAT.all = DataByte; 
}


/*****************************************************************************
** Function name:		IIC_GetByte
**
** Descriptions:		Get IIC Byte
**
** parameters:      None
**
** Returned value:	IIC Data
** 
*****************************************************************************/

uint8_t IIC_GetByte(HHD32F1_IIC_TypeDef *IIC)
{
	return(IIC->DAT.all);
}

/*****************************************************************************
* Function name:    IIC_IRQHandler
*
* Descriptions:     Use status to control process
*
* parameters:       None
* Returned value:   None
* 
*****************************************************************************/
void IIC_IRQHandler(HHD32F1_IIC_TypeDef *IIC)
{
	uint16_t StatValue;

	IIC_CtrlBlk_TypeDef* IICCtrl;

	if(IIC==I2C1)
		IICCtrl = &IIC1_CtrlBlk;
	else
		IICCtrl = &IIC2_CtrlBlk;
	
	StatValue = IIC_GetIICStatus(IIC);
	// 0x4B--SLA+W transmitted but no ACK 
	// 0x54--Data byte in DAT transmitted;no ACK received.
	if 	((StatValue&0xff == 0x4B) || (StatValue&0xff == 0x54))
	{
			IIC_SetFlag(IIC,IIC_CONSET_STO);				// Set Stop flag
			IICCtrl->IICMasterState = IIC_OK;
			IIC_ClearFlag(IIC,IIC_CONCLR_SIC| IIC_CONCLR_STAC |IIC_CONCLR_TXRXC );
			return;	
	}
 
	if(IIC->CONSET.all&IIC_CONSET_MASL)
	{
		StatValue &= ~(0x740);
		switch ( StatValue&0xff )
		{
			case IIC_M_TX_START:				/* 0x01: A Start condition is issued. */
				if (IICCtrl->Restart == 1)
				{
					//RX SLAD IIC_M_TX_RESTART:
					IICCtrl->Restart = 0;
					IICCtrl->RdIndex = 0;
					IIC_SendByte(IIC,IICCtrl->IICMasterBuffer[0] + 1); 			/* Send SLA with R bit set */
					IICCtrl->WrIndex++;
					IIC_ClearFlag(IIC,IIC_CONCLR_SIC | IIC_CONCLR_STAC |IIC_CONCLR_TXRXC);
				}
				else
				{
					// Start master transmit process
					IICCtrl->WrIndex = 0;
					IICCtrl->RdIndex = 0;
					IIC_SetFlag(IIC,IIC_CONSET_TXRX); 		 // Set tx flag
					IIC_SendByte(IIC,IICCtrl->IICMasterBuffer[0]);  // Transmit address first 
					IICCtrl->WrIndex++;
					IIC_ClearFlag(IIC,IIC_CONCLR_SIC | IIC_CONCLR_STAC);
				}
				break;
		
			case IIC_M_TX_RESTART:			/* 0x10: A repeated started is issued */
				IICCtrl->RdIndex = 0;
				IIC_SendByte(IIC,IICCtrl->IICMasterBuffer[IICCtrl->WrIndex++]); 			/* Send SLA with R bit set */
				IIC_ClearFlag(IIC,IIC_CONCLR_SIC | IIC_CONCLR_STAC);
				break;
		
			case IIC_M_TX_SLAW_ACK:			/* 0x0B: Regardless, it's a ACK */
				if ((IIC->CONSET.all & 0x1)==0x1) // Transmit
				{
					if (IICCtrl->IICWriteLength == 1)
					{
						IIC_SetFlag(IIC,IIC_CONSET_STO);      			// Set Stop flag
						IICCtrl->IICMasterState = IIC_NO_DATA;
					}
					else
					{
						IIC_SendByte(IIC,IICCtrl->IICMasterBuffer[IICCtrl->WrIndex++]); // Transmit
					}
					IIC_ClearFlag(IIC,IIC_CONCLR_SIC);
				}
				else
				{
					if ( (IICCtrl->RdIndex + 1) < IICCtrl->IICReadLength ) // Read form slave device
					{
						/* Will go to State 0x50 */
						IIC_SetFlag(IIC,IIC_CONSET_AA);					/* assert ACK after data is received */
					}
					else
					{
						/* Last byte will no ack, Will go to State 0x58 */
						IIC_ClearFlag(IIC,IIC_CONCLR_AAC);				/* assert NACK after data is received */
					}
					IIC_ClearFlag(IIC,IIC_CONCLR_SIC | IIC_CONCLR_STAC);
				}
				break;	
		
			case IIC_M_TX_DAT_ACK:			/* 0x14: Data byte has been transmitted, regardless ACK or NACK */
				if ( IICCtrl->WrIndex < IICCtrl->IICWriteLength )
				{   
					IIC_SendByte(IIC,IICCtrl->IICMasterBuffer[IICCtrl->WrIndex++]);	
				}
				else		/* this should be the last one */
				{
					if ( IICCtrl->IICReadLength != 0 )	  
					{
						IICCtrl->Restart = 0;
						IICCtrl->RdIndex = 0;
						if(IICCtrl->Re_Start)
						{
							IIC_SendByte(IIC,IICCtrl->IICMasterBuffer[0] + 1); 			/* Send SLA with R bit set */
							IIC_SetFlag(IIC,IIC_CONSET_STA);				/* Set Repeated-start flag */
						}

                        else
                        {
                            IIC_SendByte(IIC, IICCtrl->IICMasterBuffer[0] + 1); 			/* Send SLA with R bit set */
                        }

                        IIC_ClearFlag(IIC, IIC_CONCLR_SIC  | IIC_CONCLR_TXRXC);
                        break;
                    }
                    else
                    {
                        IIC_SetFlag(IIC, IIC_CONSET_STO);				/* Set Stop flag */
                        IICCtrl->IICMasterState = IIC_OK;
                    }
                }
                IIC_ClearFlag(IIC, IIC_CONCLR_SIC);
                break;

            case IIC_M_RX_DAT_ACK:			/* 0x1D, 0x5D: Data byte has been received, regardless following ACK or NACK */

                IICCtrl->IICSlaveBuffer[IICCtrl->RdIndex++] = IIC_GetByte(IIC);
                if ( (IICCtrl->RdIndex + 1) < IICCtrl->IICReadLength )
                {
                    IIC_SetFlag(IIC, IIC_CONSET_AA);					/* assert ACK after data is received */
                    IIC_ClearFlag(IIC, IIC_CONCLR_SIC);
                }
                else
                {
                    if ((IIC->CONSET.all & 0x04) == 0x04)
                        IIC_ClearFlag(IIC, IIC_CONCLR_AAC | IIC_CONCLR_SIC);
                    else
                    {
                        IICCtrl->IICMasterState = IIC_OK;
                        IIC_SetFlag(IIC, IIC_CONSET_STO);	/* assert NACK on last byte */
                        IIC_ClearFlag(IIC, IIC_CONCLR_SIC);
                    }
                }
                break;

            default:
                IICCtrl->IICMasterState = IIC_ARBITRATION_LOST;
                IIC_ClearFlag(IIC, IIC_CONCLR_SIC);
                break;
        }
    }
    else
    {
        uint32_t temp;
        /*
        		switch(StatValue&0xff)
        		{

        			case IIC_S_SLWRITE_ACK:		//0xa: SLA+W has been received, acked; will receive data and ack
        				temp = IIC_GetByte(IIC);
        				IICCtrl->WrIndex=0;
        				IICCtrl->RdIndex=0;
        				if(StatValue&0x100)
        					IIC->STAT.bit.SLVADDMATCH=1;
        				if(temp==(IIC->ADR0.all))
        				{
        					IICCtrl->SelAddr=0;
        				}
        				else if(temp==(IIC->ADR1.all))
        				{
        					IICCtrl->SelAddr=1;
        				}
        				else if(temp==(IIC->ADR2.all))
        				{
        					IICCtrl->SelAddr=2;

        				}
        				else if(temp==(IIC->ADR3.all))
        				{
        					IICCtrl->SelAddr=3;
        				}
        				break;
        			case IIC_S_SLREAD_ACK:	  //0x4a: SLA+R has been received, acked; will send data and ack
        				temp = IIC->DAT.all;
        				if(temp==(IIC->ADR1.all+1))
        				{
        					IIC->DAT.all=IICCtrl->IICSlaveBuffer[IICCtrl->RdIndex++];;
        					IIC->CONSET.all |= IIC_CONSET_TXRX;
        				}
        				break;
        			case IIC_S_RX_ACK:
        				IICCtrl->IICMasterBuffer[IICCtrl->WrIndex++] = IIC->DAT.all;
        				break;
        			case IIC_S_TX_ACK:
        				IIC->DAT.all=IICCtrl->IICSlaveBuffer[IICCtrl->RdIndex++];
        				if(IICCtrl->RdIndex>=IICCtrl->IICReadLength)
        					IICCtrl->RdIndex=0;
        				break;
        			case IIC_S_STOP:
        			case IIC_S_TX_NOACK:
        				break;
        			case 0:
        				IIC->DAT.all=0;

        		}
        */
        if(StatValue & 0x100)
        {
            //int i;
            IIC->CONCLR.all = 0x100;		//clear addr match interrupt
            temp = IIC_GetByte(IIC);
            IICCtrl->WrIndex = 0;
            IICCtrl->RdIndex = 0;

            if(temp == (IIC->ADR0.all))
            {
                IICCtrl->SelAddr = 0;
            }
            else if(temp == (IIC->ADR1.all))
            {
                IICCtrl->SelAddr = 1;
            }
            else if(temp == (IIC->ADR2.all))
            {
                IICCtrl->SelAddr = 2;

            }
            else if(temp == (IIC->ADR3.all))
            {
                IICCtrl->SelAddr = 3;
            }
            if((temp & 0x01)) //如果是读指令,填充第一个将要发送的数据。
            {
                IIC->DAT.all = IICCtrl->IICSlaveBuffer[IICCtrl->RdIndex++];
                if(IICCtrl->RdIndex >= IICCtrl->IICReadLength)
                    IICCtrl->RdIndex = 0;
            }
            /*Modify By wangkui*/
            // 		  i = 0;
            // 			for( ; i<8; i++)
            // 			{
            // 				 IICCtrl->IICSlaveBuffer[i] = SlaveSendArry[i];
            // 			}
            // 		  IICCtrl->IICReadLength  = 8;
            // 			IICCtrl->RdIndex  = 0;
            // 			/*end of Modify*/

        }
        else if(StatValue & 0x200)
        {
            uint8_t temp = 0;
            //IICCtrl->IICMasterBuffer[IICCtrl->WrIndex++] = IIC->DAT.all;

            temp = IIC->DAT.all;
            IICCtrl->IICMasterBuffer[IICCtrl->WrIndex++] = temp;
            //			I2C2Ctrl.IICMasterBuffer[I2C2Ctrl.WrIndex++] = temp;
            //IIC_WriteArray(I2C2, 0x70, 0xaa, I2C2Ctrl, 7);
            //printf("\r\nI2C2 Interrupt\r\n");SlaveSendrry

        }
        else if(StatValue & 0x400)
        {
            IIC->DAT.all = IICCtrl->IICSlaveBuffer[IICCtrl->RdIndex++];
            if(IICCtrl->RdIndex >= IICCtrl->IICReadLength)
                IICCtrl->RdIndex = 0;
        }

        IIC->CONCLR.all = IIC_CONCLR_SIC + IIC_CONCLR_STAC;

    }
    return;
}
/*****************************************************************************
* Function name:    I2C1_IRQHandler
*
* Descriptions:     Use status to control process
*
* parameters:       None
* Returned value:   None
*
*****************************************************************************/
void IIC1_IRQHandler(HHD32F1_IIC_TypeDef *IIC)
{
    uint16_t StatValue;
    //	uint16_t temp;

    IIC_CtrlBlk_TypeDef *IICCtrl;

    if(IIC == I2C1)
        IICCtrl = &IIC1_CtrlBlk;
    else
        IICCtrl = &IIC2_CtrlBlk;

    StatValue = IIC_GetIICStatus(IIC);
    // 0x4B--SLA+W transmitted but no ACK
    // 0x54--Data byte in DAT transmitted;no ACK received.
    if 	((StatValue & 0xff == 0x4B) || (StatValue & 0xff == 0x54))
    {
        IIC_SetFlag(IIC, IIC_CONSET_STO);				// Set Stop flag
        IICCtrl->IICMasterState = IIC_OK;
        IIC_ClearFlag(IIC, IIC_CONCLR_SIC | IIC_CONCLR_STAC | IIC_CONCLR_TXRXC );
        return;
    }

    if(IIC->CONSET.all & IIC_CONSET_MASL)
    {
        StatValue &= ~(0x740);
        switch ( StatValue & 0xff )
        {
            case IIC_M_TX_START:				/* 0x01: A Start condition is issued. */
                if (IICCtrl->Restart == 1)
                {
                    //RX SLAD IIC_M_TX_RESTART:
                    IICCtrl->Restart = 0;
                    IICCtrl->RdIndex = 0;
                    IIC_SendByte(IIC, IICCtrl->IICMasterBuffer[0] + 1); 			/* Send SLA with R bit set */
                    IICCtrl->WrIndex++;
                    IIC_ClearFlag(IIC, IIC_CONCLR_SIC | IIC_CONCLR_STAC | IIC_CONCLR_TXRXC);
                }
                else
                {
                    //--printf("IIC_M_TX_START, StatValue = %x\r\n", StatValue);
                    // Start master transmit process
                    IICCtrl->WrIndex = 0;
                    IICCtrl->RdIndex = 0;
                    IIC_SetFlag(IIC, IIC_CONSET_TXRX); 		 // Set tx flag
                    IIC_SendByte(IIC, IICCtrl->IICMasterBuffer[0]); // Transmit address first
                    IICCtrl->WrIndex++;
                    IIC_ClearFlag(IIC, IIC_CONCLR_SIC | IIC_CONCLR_STAC);
                }
                break;

            case IIC_M_TX_RESTART:			/* 0x10: A repeated started is issued */
                IICCtrl->RdIndex = 0;
                IIC_SendByte(IIC, IICCtrl->IICMasterBuffer[IICCtrl->WrIndex++]); 			/* Send SLA with R bit set */
                IIC_ClearFlag(IIC, IIC_CONCLR_SIC | IIC_CONCLR_STAC);
                break;

            case IIC_M_TX_SLAW_ACK:			/* 0x0B: Regardless, it's a ACK */
                if ((IIC->CONSET.all & 0x1) == 0x1) // Transmit
                {
                    //--printf("IIC_M_TX_SLAW_ACK, Transmit. StatValue = %x\r\n", StatValue);
                    if (IICCtrl->IICWriteLength == 1)
                    {
                        IIC_SetFlag(IIC, IIC_CONSET_STO);      			// Set Stop flag
                        IICCtrl->IICMasterState = IIC_NO_DATA;
                    }
                    else
                    {
                        IIC_SendByte(IIC, IICCtrl->IICMasterBuffer[IICCtrl->WrIndex++]); // Transmit
                    }
                    IIC_ClearFlag(IIC, IIC_CONCLR_SIC);
                }
                else
                {
                    if ( (IICCtrl->RdIndex + 1) < IICCtrl->IICReadLength ) // Read form slave device
                    {
                        //--printf("IIC_M_TX_SLAW_ACK, Read, ACK. StatValue = %x\r\n", StatValue);
                        /* Will go to State 0x50 */
                        IIC_SetFlag(IIC, IIC_CONSET_AA);					/* assert ACK after data is received */

                    }
                    else
                    {
                        //--printf("IIC_M_TX_SLAW_ACK, Read, NACK. StatValue = %x\r\n", StatValue);
                        /* Last byte will no ack, Will go to State 0x58 */
                        IIC_ClearFlag(IIC, IIC_CONCLR_AAC);				/* assert NACK after data is received */

                    }
                    IIC_ClearFlag(IIC, IIC_CONCLR_SIC | IIC_CONCLR_STAC);
                }
                break;

            case IIC_M_TX_DAT_ACK:			/* 0x14: Data byte has been transmitted, regardless ACK or NACK */
                if ( IICCtrl->WrIndex < IICCtrl->IICWriteLength )
                {
                    //--printf("IIC_M_TX_DAT_ACK, transmit. StatValue = %x\r\n", StatValue);
                    IIC_SendByte(IIC, IICCtrl->IICMasterBuffer[IICCtrl->WrIndex++]);

                }
                else		/* this should be the last one */
                {
                    if ( IICCtrl->IICReadLength != 0 )
                    {
                        //--printf("IIC_M_TX_DAT_ACK, transmit SLA with R. StatValue = %x\r\n", StatValue);
                        IICCtrl->Restart = 0;
                        IICCtrl->RdIndex = 0;
                        if(IICCtrl->Re_Start)
                        {
                            IIC_SendByte(IIC, IICCtrl->IICMasterBuffer[0] + 1); 			/* Send SLA with R bit set */
                            IIC_SetFlag(IIC, IIC_CONSET_STA);				/* Set Repeated-start flag */
                        }

                        else
                        {
                            IIC_SendByte(IIC, IICCtrl->IICMasterBuffer[0] + 1); 			/* Send SLA with R bit set */
                        }

                        IIC_ClearFlag(IIC, IIC_CONCLR_SIC  | IIC_CONCLR_TXRXC);
                        break;
                    }
                    else
                    {
                        IIC_SetFlag(IIC, IIC_CONSET_STO);				/* Set Stop flag */
                        IICCtrl->IICMasterState = IIC_OK;
                    }
                }
                IIC_ClearFlag(IIC, IIC_CONCLR_SIC);
                break;

            case IIC_M_RX_DAT_ACK:			/* 0x1D, 0x5D: Data byte has been received, regardless following ACK or NACK */
                // delay_us(100);
                IICCtrl->IICSlaveBuffer[IICCtrl->RdIndex++] = IIC_GetByte(IIC);
                // 			 //uint16_t  temp;
                // 			 temp = IIC_GetByte(IIC);
                //  			 IICCtrl->IICSlaveBuffer[IICCtrl->RdIndex++] = temp;
                //  			 printf("The temp data is: %x\r\n", temp);
                if ( (IICCtrl->RdIndex + 1) < IICCtrl->IICReadLength )
                {
                    //--printf("IIC_M_RX_DAT_ACK, ACK. StatValue = %x\r\n", StatValue);
                    IIC_SetFlag(IIC, IIC_CONSET_AA);					/* assert ACK after data is received */
                    IIC_ClearFlag(IIC, IIC_CONCLR_SIC);
                }
                else
                {
                    //--printf("IIC_M_RX_DAT_ACK, NACK. StatValue = %x\r\n", StatValue);
                    if ((IIC->CONSET.all & 0x04) == 0x04)
                        IIC_ClearFlag(IIC, IIC_CONCLR_AAC | IIC_CONCLR_SIC);
                    else
                    {
                        IICCtrl->IICMasterState = IIC_OK;
                        IIC_SetFlag(IIC, IIC_CONSET_STO);	/* assert NACK on last byte */
                        IIC_ClearFlag(IIC, IIC_CONCLR_SIC);
                    }
                }
                break;

            default:
                IICCtrl->IICMasterState = IIC_ARBITRATION_LOST;
                IIC_ClearFlag(IIC, IIC_CONCLR_SIC);
                break;
        }
    }
    else
    {
        uint32_t temp;
        /*
        		switch(StatValue&0xff)
        		{

        			case IIC_S_SLWRITE_ACK:		//0xa: SLA+W has been received, acked; will receive data and ack
        				temp = IIC_GetByte(IIC);
        				IICCtrl->WrIndex=0;
        				IICCtrl->RdIndex=0;
        				if(StatValue&0x100)
        					IIC->STAT.bit.SLVADDMATCH=1;
        				if(temp==(IIC->ADR0.all))
        				{
        					IICCtrl->SelAddr=0;
        				}
        				else if(temp==(IIC->ADR1.all))
        				{
        					IICCtrl->SelAddr=1;
        				}
        				else if(temp==(IIC->ADR2.all))
        				{
        					IICCtrl->SelAddr=2;

        				}
        				else if(temp==(IIC->ADR3.all))
        				{
        					IICCtrl->SelAddr=3;
        				}
        				break;
        			case IIC_S_SLREAD_ACK:	  //0x4a: SLA+R has been received, acked; will send data and ack
        				temp = IIC->DAT.all;
        				if(temp==(IIC->ADR1.all+1))
        				{
        					IIC->DAT.all=IICCtrl->IICSlaveBuffer[IICCtrl->RdIndex++];;
        					IIC->CONSET.all |= IIC_CONSET_TXRX;
        				}
        				break;
        			case IIC_S_RX_ACK:
        				IICCtrl->IICMasterBuffer[IICCtrl->WrIndex++] = IIC->DAT.all;
        				break;
        			case IIC_S_TX_ACK:
        				IIC->DAT.all=IICCtrl->IICSlaveBuffer[IICCtrl->RdIndex++];
        				if(IICCtrl->RdIndex>=IICCtrl->IICReadLength)
        					IICCtrl->RdIndex=0;
        				break;
        			case IIC_S_STOP:
        			case IIC_S_TX_NOACK:
        				break;
        			case 0:
        				IIC->DAT.all=0;

        		}
        */
        if(StatValue & 0x100)
        {
            IIC->CONCLR.all = 0x100;		//clear addr match interrupt //SLVADDMATCH 从机地址匹配
            temp = IIC_GetByte(IIC);
            IICCtrl->WrIndex = 0;
            IICCtrl->RdIndex = 0;

            if(temp == (IIC->ADR0.all))
            {
                IICCtrl->SelAddr = 0;
            }
            else if(temp == (IIC->ADR1.all))
            {
                IICCtrl->SelAddr = 1;
            }
            else if(temp == (IIC->ADR2.all))
            {
                IICCtrl->SelAddr = 2;

            }
            else if(temp == (IIC->ADR3.all))
            {
                IICCtrl->SelAddr = 3;
            }
            if((temp & 0x01)) //如果是读指令,填充第一个将要发送的数据。
            {
                IIC->DAT.all = IICCtrl->IICSlaveBuffer[IICCtrl->RdIndex++];
                if(IICCtrl->RdIndex >= IICCtrl->IICReadLength)
                    IICCtrl->RdIndex = 0;
            }

        }
        else if(StatValue & 0x200) //SLVRXBUFFULL 从机接收缓冲器满
        {
            // 			uint8_t temp = 0;
            IICCtrl->IICMasterBuffer[IICCtrl->WrIndex++] = IIC->DAT.all;

            // 			temp = IIC->DAT.all;
            // 			IICCtrl->IICMasterBuffer[IICCtrl->WrIndex++] = temp;
            //I2C2Ctrl.IICMasterBuffer[I2C2Ctrl.WrIndex++] = temp;
            //IIC_WriteArray(I2C2, 0x70, 0xaa, I2C2Ctrl, 7);
            //printf("\r\nI2C2 Interrupt\r\n");SlaveSendrry


        }
        else if(StatValue & 0x400) //SLVTXBUFEMPTY 从机发送缓冲器空
        {
            IIC->DAT.all = IICCtrl->IICSlaveBuffer[IICCtrl->RdIndex++];
            if(IICCtrl->RdIndex >= IICCtrl->IICReadLength)
                IICCtrl->RdIndex = 0;
        }
        IIC->CONCLR.all = IIC_CONCLR_SIC + IIC_CONCLR_STAC;

    }
    return;
}

/*****************************************************************************
* Function name:    I2C2_IRQHandler
*
* Descriptions:     Use status to control process
*
* parameters:       None
* Returned value:   None
*
*****************************************************************************/
void IIC2_IRQHandler(HHD32F1_IIC_TypeDef *IIC)
{
    uint16_t StatValue;

    IIC_CtrlBlk_TypeDef *IICCtrl;

    if(IIC == I2C1)
        IICCtrl = &IIC1_CtrlBlk;
    else
        IICCtrl = &IIC2_CtrlBlk;

    StatValue = IIC_GetIICStatus(IIC);
    // 0x4B--SLA+W transmitted but no ACK
    // 0x54--Data byte in DAT transmitted;no ACK received.
    if 	((StatValue & 0xff == 0x4B) || (StatValue & 0xff == 0x54))
    {
        IIC_SetFlag(IIC, IIC_CONSET_STO);				// Set Stop flag
        IICCtrl->IICMasterState = IIC_OK;
        IIC_ClearFlag(IIC, IIC_CONCLR_SIC | IIC_CONCLR_STAC | IIC_CONCLR_TXRXC );
        return;
    }

    if(IIC->CONSET.all & IIC_CONSET_MASL) //Master Mode
    {
        StatValue &= ~(0x740);
        switch ( StatValue & 0xff )
        {
            case IIC_M_TX_START:				/* 0x01: A Start condition is issued. */
                if (IICCtrl->Restart == 1)
                {
                    //RX SLAD IIC_M_TX_RESTART:
                    IICCtrl->Restart = 0;
                    IICCtrl->RdIndex = 0;
                    IIC_SendByte(IIC, IICCtrl->IICMasterBuffer[0] + 1); 			/* Send SLA with R bit set */
                    IICCtrl->WrIndex++;
                    IIC_ClearFlag(IIC, IIC_CONCLR_SIC | IIC_CONCLR_STAC | IIC_CONCLR_TXRXC);
                }
                else
                {
                    // Start master transmit process
                    IICCtrl->WrIndex = 0;
                    IICCtrl->RdIndex = 0;
                    IIC_SetFlag(IIC, IIC_CONSET_TXRX); 		 // Set tx flag
                    IIC_SendByte(IIC, IICCtrl->IICMasterBuffer[0]); // Transmit address first
                    IICCtrl->WrIndex++;
                    IIC_ClearFlag(IIC, IIC_CONCLR_SIC | IIC_CONCLR_STAC);
                }
                break;

            case IIC_M_TX_RESTART:			/* 0x10: A repeated started is issued */
                IICCtrl->RdIndex = 0;
                IIC_SendByte(IIC, IICCtrl->IICMasterBuffer[IICCtrl->WrIndex++]); 			/* Send SLA with R bit set */
                IIC_ClearFlag(IIC, IIC_CONCLR_SIC | IIC_CONCLR_STAC);
                break;

            case IIC_M_TX_SLAW_ACK:			/* 0x0B: Regardless, it's a ACK */
                if ((IIC->CONSET.all & 0x1) == 0x1) // Transmit
                {
                    if (IICCtrl->IICWriteLength == 1)
                    {
                        IIC_SetFlag(IIC, IIC_CONSET_STO);      			// Set Stop flag
                        IICCtrl->IICMasterState = IIC_NO_DATA;
                    }
                    else
                    {
                        IIC_SendByte(IIC, IICCtrl->IICMasterBuffer[IICCtrl->WrIndex++]); // Transmit
                    }
                    IIC_ClearFlag(IIC, IIC_CONCLR_SIC);
                }
                else
                {
                    if ( (IICCtrl->RdIndex + 1) < IICCtrl->IICReadLength ) // Read form slave device
                    {
                        /* Will go to State 0x50 */
                        IIC_SetFlag(IIC, IIC_CONSET_AA);					/* assert ACK after data is received */
                    }
                    else
                    {
                        /* Last byte will no ack, Will go to State 0x58 */
                        IIC_ClearFlag(IIC, IIC_CONCLR_AAC);				/* assert NACK after data is received */
                    }
                    IIC_ClearFlag(IIC, IIC_CONCLR_SIC | IIC_CONCLR_STAC);
                }
                break;

            case IIC_M_TX_DAT_ACK:			/* 0x14: Data byte has been transmitted, regardless ACK or NACK */
                if ( IICCtrl->WrIndex < IICCtrl->IICWriteLength )
                {
                    IIC_SendByte(IIC, IICCtrl->IICMasterBuffer[IICCtrl->WrIndex++]);
                }
                else		/* this should be the last one */
                {
                    if ( IICCtrl->IICReadLength != 0 )
                    {
                        IICCtrl->Restart = 0;
                        IICCtrl->RdIndex = 0;
                        if(IICCtrl->Re_Start)
                        {
                            IIC_SendByte(IIC, IICCtrl->IICMasterBuffer[0] + 1); 			/* Send SLA with R bit set */
                            IIC_SetFlag(IIC, IIC_CONSET_STA);				/* Set Repeated-start flag */
                        }

                        else
                        {
                            IIC_SendByte(IIC, IICCtrl->IICMasterBuffer[0] + 1); 			/* Send SLA with R bit set */
                        }

                        IIC_ClearFlag(IIC, IIC_CONCLR_SIC  | IIC_CONCLR_TXRXC);
                        break;
                    }
                    else
                    {
                        IIC_SetFlag(IIC, IIC_CONSET_STO);				/* Set Stop flag */
                        IICCtrl->IICMasterState = IIC_OK;
                    }
                }
                IIC_ClearFlag(IIC, IIC_CONCLR_SIC);
                break;

            case IIC_M_RX_DAT_ACK:			/* 0x1D, 0x5D: Data byte has been received, regardless following ACK or NACK */
                IICCtrl->IICSlaveBuffer[IICCtrl->RdIndex++] = IIC_GetByte(IIC);
                if ( (IICCtrl->RdIndex + 1) < IICCtrl->IICReadLength )
                {
                    IIC_SetFlag(IIC, IIC_CONSET_AA);					/* assert ACK after data is received */
                    IIC_ClearFlag(IIC, IIC_CONCLR_SIC);
                }
                else
                {
                    if ((IIC->CONSET.all & 0x04) == 0x04)
                        IIC_ClearFlag(IIC, IIC_CONCLR_AAC | IIC_CONCLR_SIC);
                    else
                    {
                        IICCtrl->IICMasterState = IIC_OK;
                        IIC_SetFlag(IIC, IIC_CONSET_STO);	/* assert NACK on last byte */
                        IIC_ClearFlag(IIC, IIC_CONCLR_SIC);
                    }
                }
                break;

            default:
                IICCtrl->IICMasterState = IIC_ARBITRATION_LOST;
                IIC_ClearFlag(IIC, IIC_CONCLR_SIC);
                break;
        }
    }
    else
    {
        uint32_t temp;
        /*
        		switch(StatValue&0xff)
        		{

        			case IIC_S_SLWRITE_ACK:		//0xa: SLA+W has been received, acked; will receive data and ack
        				temp = IIC_GetByte(IIC);
        				IICCtrl->WrIndex=0;
        				IICCtrl->RdIndex=0;
        				if(StatValue&0x100)
        					IIC->STAT.bit.SLVADDMATCH=1;
        				if(temp==(IIC->ADR0.all))
        				{
        					IICCtrl->SelAddr=0;
        				}
        				else if(temp==(IIC->ADR1.all))
        				{
        					IICCtrl->SelAddr=1;
        				}
        				else if(temp==(IIC->ADR2.all))
        				{
        					IICCtrl->SelAddr=2;

        				}
        				else if(temp==(IIC->ADR3.all))
        				{
        					IICCtrl->SelAddr=3;
        				}
        				break;
        			case IIC_S_SLREAD_ACK:	  //0x4a: SLA+R has been received, acked; will send data and ack
        				temp = IIC->DAT.all;
        				if(temp==(IIC->ADR1.all+1))
        				{
        					IIC->DAT.all=IICCtrl->IICSlaveBuffer[IICCtrl->RdIndex++];;
        					IIC->CONSET.all |= IIC_CONSET_TXRX;
        				}
        				break;
        			case IIC_S_RX_ACK:
        				IICCtrl->IICMasterBuffer[IICCtrl->WrIndex++] = IIC->DAT.all;
        				break;
        			case IIC_S_TX_ACK:
        				IIC->DAT.all=IICCtrl->IICSlaveBuffer[IICCtrl->RdIndex++];
        				if(IICCtrl->RdIndex>=IICCtrl->IICReadLength)
        					IICCtrl->RdIndex=0;
        				break;
        			case IIC_S_STOP:
        			case IIC_S_TX_NOACK:
        				break;
        			case 0:
        				IIC->DAT.all=0;

        		}
        */
        if(StatValue & 0x100) ////slave Mode
        {
            //			int i = 0;
            IIC_SetFlag(IIC, IIC_CONSET_AA);					/* assert ACK after data is received */
            IIC_ClearFlag(IIC, IIC_CONCLR_SIC);

            IIC->CONCLR.all = 0x100;		//clear addr match interrupt //SLVADDMATCH 从机地址匹配
            temp = IIC_GetByte(IIC);
            IICCtrl->WrIndex = 0;
            IICCtrl->RdIndex = 0;

            if(temp == (IIC->ADR0.all))
            {
                IICCtrl->SelAddr = 0;
            }
            else if(temp == (IIC->ADR1.all))
            {
                IICCtrl->SelAddr = 1;
            }
            else if(temp == (IIC->ADR2.all))
            {
                IICCtrl->SelAddr = 2;

            }
            else if(temp == (IIC->ADR3.all))
            {
                IICCtrl->SelAddr = 3;
            }
            if((temp & 0x01)) //读指令，开始发送第一个字节
            {
                IIC->DAT.all = IICCtrl->IICSlaveBuffer[IICCtrl->RdIndex++];
                if(IICCtrl->RdIndex >= IICCtrl->IICReadLength)
                    IICCtrl->RdIndex = 0;
            }

            //--	printf("SLVADDMATCH. StatValue = %x\r\n", StatValue);
            //IIC_WriteArray(I2C2, 0x70, 0xaa, SlaveSendArry, 7);
            //IIC_SendByte(I2C2, 0xaa);
            /*Fill the data to send*/
            // 			i = 0;
            // 			for( ; i<8; i++)
            // 			{
            // 				 IICCtrl->IICSlaveBuffer[i] = SlaveSendArry[i];
            // 			}
            // 		  IICCtrl->IICReadLength  = 8;
            // 			IICCtrl->RdIndex  = 0;
            //SendArry(SlaveSendArry, 8);
        }
        else if(StatValue & 0x200) //SLVRXBUFFULL 从机接收缓冲器满
        {

            /*Slaver Recive data*/
            uint8_t temp = 0;
            //--printf("SLVRXBUFFULL. StatValue = %x\r\n", StatValue);
            //IICCtrl->IICMasterBuffer[IICCtrl->WrIndex++] = IIC->DAT.all;
            IIC_SetFlag(IIC, IIC_CONSET_AA);					/* assert ACK after data is received */
            IIC_ClearFlag(IIC, IIC_CONCLR_SIC);
            temp = IIC->DAT.all;
            IICCtrl->IICMasterBuffer[IICCtrl->WrIndex++] = temp;
            //I2C2Ctrl.IICMasterBuffer[I2C2Ctrl.WrIndex++] = temp;
            //IIC_WriteArray(I2C2, 0x70, 0xaa, I2C2Ctrl, 7);
            //printf("\r\nI2C2 Interrupt\r\n");SlaveSendrry

        }
        else if(StatValue & 0x400) //SLVTXBUFEMPTY 从机发送缓冲器空
        {
            IIC_SetFlag(IIC, IIC_CONSET_AA);					/* assert ACK after data is received */
            IIC_ClearFlag(IIC, IIC_CONCLR_SIC);
            //--printf("SLVTXBUFEMPTY. StatValue = %x\r\n", StatValue);
            /*Slaver Send data*/
            //   		uint8_t temp = 0,index = 0;
            // 			index = IICCtrl->RdIndex;
            // 			temp = IICCtrl->IICSlaveBuffer[IICCtrl->RdIndex++];
            // 			printf("I2C2 Send,the RdIndex is %d, the data is %x \r\n", index, temp);
            //			IIC->DAT.all = temp;
            IIC->DAT.all = IICCtrl->IICSlaveBuffer[IICCtrl->RdIndex++];
            // 			printf("I2C2 Send,the RdIndex is %d, the data is %x \r\n", (IICCtrl->RdIndex-1), IIC->DAT.all);
            if(IICCtrl->RdIndex >= IICCtrl->IICReadLength)
                IICCtrl->RdIndex = 0;

        }

        IIC->CONCLR.all = IIC_CONCLR_SIC + IIC_CONCLR_STAC;

	}
	return;
}
/*****************************************************************************
* Function name:    IIC_WriteByte
*
* Descriptions:     Write byte to slave chip
*
* parameters:       SlaveAddress: Slave chip address
					SubAddr:  Slave chip register address
					Value :   Value write to slave chip register address
* Returned value:   None
* 
*****************************************************************************/

void IIC_WriteByte(HHD32F1_IIC_TypeDef *IIC, uint8_t SlaveAddress, uint8_t SubAddr, uint8_t Value)
{
	uint8_t i;
	IIC_CtrlBlk_TypeDef* IICCtrl;

	if(IIC==I2C1)
		IICCtrl = &IIC1_CtrlBlk;
	else
		IICCtrl = &IIC2_CtrlBlk;

	IICCtrl->IICMasterBuffer[0] = SlaveAddress; // Slave chip address
	IICCtrl->IICMasterBuffer[1] = SubAddr;	   // Chip register address
	IICCtrl->IICMasterBuffer[2] = Value;
	
	IICCtrl->Re_Start = 0;

	IICCtrl->IICReadLength = 0; // Read length
	IICCtrl->IICWriteLength = 3;	// Write length


	IIC_SetFlag(IIC,IIC_CONSET_STA); //Set start signal

	IICCtrl->IICMasterState = IIC_IDLE;
	while( IICCtrl->IICMasterState != IIC_OK ); // Wait for finished

	i = 0xFF;
	while(i--);
}


/*****************************************************************************
* Function name:    IIC_WriteArray
*
* Descriptions:     Write array value to slave chip
*
* parameters:       SlaveAddress: Slave chip address
					SubAddr:  Slave chip register address
					Buff: 	  Write value pointer
					Length:   Length to write
* Returned value:   None
* 
*****************************************************************************/
void IIC_WriteArray(HHD32F1_IIC_TypeDef *IIC, uint8_t SlaveAddress, uint8_t SubAddr, uint8_t *Buff,
                    uint8_t Length)
{
	uint8_t i;
	IIC_CtrlBlk_TypeDef* IICCtrl;

	if(IIC==I2C1)
		IICCtrl = &IIC1_CtrlBlk;
	else
		IICCtrl = &IIC2_CtrlBlk;

	IICCtrl->IICMasterBuffer[0] = SlaveAddress; // Slave chip address
	IICCtrl->IICMasterBuffer[1] = SubAddr;

	for( i = 0; i < Length; i++ )
	{
	 	IICCtrl->IICMasterBuffer[i+2] = *( Buff + i ); // Write value to slave chip register  		
	}
	
	IICCtrl->Re_Start = 0;
	IICCtrl->IICReadLength = 0;
	IICCtrl->IICWriteLength = Length+2; // Write Length
	IIC_SetFlag(IIC,IIC_CONSET_STA); // Start

	IICCtrl->IICMasterState = IIC_IDLE;
	while( IICCtrl->IICMasterState != IIC_OK ); // Wait for finished

	i = 0xFF;
	while(i--);
}

/*****************************************************************************
* Function name:    IIC_ReadByte
*
* Descriptions:     Read byte from slave chip
*
* parameters:       SlaveAddress: Slave chip address
					SubAddr:  Slave chip register address
* Returned value:   return read value
* 
*****************************************************************************/
uint8_t IIC_ReadByte(HHD32F1_IIC_TypeDef *IIC, uint8_t SlaveAddress, uint8_t SubAddr)
{
	uint8_t i;
	IIC_CtrlBlk_TypeDef* IICCtrl;

	if(IIC==I2C1)
		IICCtrl = &IIC1_CtrlBlk;
	else
		IICCtrl = &IIC2_CtrlBlk;

	IICCtrl->IICMasterBuffer[0] = SlaveAddress; // Slave chip address
	IICCtrl->IICMasterBuffer[1] = SubAddr;

	IICCtrl->IICWriteLength = 2;
	IICCtrl->IICReadLength = 1;
	
	IICCtrl->Re_Start = 1;
	IIC_SetFlag(IIC,IIC_CONSET_STA); // Start

	IICCtrl->IICMasterState = IIC_IDLE;
	while( IICCtrl->IICMasterState != IIC_OK ); // Wait for finished

	i = 0xFF;
	while(i--);
	
	return(IICCtrl->IICSlaveBuffer[0]);
}

/*****************************************************************************
* Function name:    IIC_ReadArray
*
* Descriptions:     Read array value from slave chip
*
* parameters:       SlaveAddress: Slave chip address
					SubAddr:  Slave chip register address
					Length:   Length for reading
					Buffer:   Read value pointer
* Returned value:   None
*
*****************************************************************************/
void IIC_ReadArray(HHD32F1_IIC_TypeDef *IIC, uint8_t SlaveAddress, uint8_t SubAddr, uint8_t Lenth,
                   uint8_t *Buffer)
{
	uint8_t i;
	IIC_CtrlBlk_TypeDef* IICCtrl;

	if(IIC==I2C1)
		IICCtrl = &IIC1_CtrlBlk;
	else
		IICCtrl = &IIC2_CtrlBlk;
		
	IICCtrl->IICMasterBuffer[0] = SlaveAddress; // Slave chip address
	IICCtrl->IICMasterBuffer[1] = SubAddr;

	IICCtrl->IICWriteLength = 2;
	IICCtrl->IICReadLength = Lenth;
	
	IICCtrl->Re_Start = 1;
	IIC_SetFlag(IIC,IIC_CONSET_STA); // Start

    IICCtrl->IICMasterState = IIC_IDLE;
    while( IICCtrl->IICMasterState != IIC_OK ); // Wait for finished

    for(i = 0; i < Lenth; i++)
    {
        *(Buffer + i) = IICCtrl->IICSlaveBuffer[i]; // Get pointer value

    }
    for(i = 0; i < Lenth; i++)
    {
        IICCtrl->IICSlaveBuffer[i] = 0;

    }

	i = 0xFF;
	while(i--);
}


/*****************************************************************************
* Function name:    IIC_ReadByte
*
* Descriptions:     Read byte from slave chip
*
* parameters:       SlaveAddress: Slave chip address
					SubAddr:  Slave chip register address
* Returned value:   return read value
* 
*****************************************************************************/
uint8_t IIC_SlaveResponseRd(HHD32F1_IIC_TypeDef *IIC, uint8_t SubAddr, uint8_t len)
{
	uint8_t i;
	IIC_CtrlBlk_TypeDef* IICCtrl;

	if(IIC==I2C1)
		IICCtrl = &IIC1_CtrlBlk;
	else
		IICCtrl = &IIC2_CtrlBlk;

	IICCtrl->IICMasterBuffer[0] = SubAddr; // Slave chip address

	IICCtrl->IICWriteLength = 2;
	IICCtrl->IICReadLength = len;

	IICCtrl->Re_Start = 1;
//	IIC_SetFlag(IIC,IIC_CONSET_STA); // Start

	IICCtrl->IICMasterState = IIC_IDLE;
	while( IICCtrl->IICMasterState != IIC_OK ); // Wait for finished

	i = 0xFF;
	while(i--);
	
	return(IICCtrl->IICSlaveBuffer[0]);
}

/*****************************************************************************
* Function name:    IIC_ReadByte
*
* Descriptions:     Read byte from slave chip
*
* parameters:       SlaveAddress: Slave chip address
					SubAddr:  Slave chip register address
* Returned value:   return read value
* 
*****************************************************************************/
void IIC_SlaveGetData(HHD32F1_IIC_TypeDef *IIC, uint8_t SubAddr, uint8_t len)
{
    //	uint8_t i;
    IIC_CtrlBlk_TypeDef *IICCtrl;

	if(IIC==I2C1)
		IICCtrl = &IIC1_CtrlBlk;
	else
		IICCtrl = &IIC2_CtrlBlk;

//	IICCtrl->IICMasterBuffer[0] = SlaveAddress; // Slave chip address
//	IICCtrl->IICMasterBuffer[1] = SubAddr;

	IICCtrl->IICWriteLength = 0;
	IICCtrl->IICReadLength = len;
	
//	IICCtrl->Re_Start = 1;

	IICCtrl->IICSlaveState = IIC_IDLE;

  return;	
}


/* --------------------------------- End Of File ------------------------------ */
