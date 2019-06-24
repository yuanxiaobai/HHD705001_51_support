/*****************************************************************************
 *   hhd_can.C:  Sourse file for  MCU CAN application
 *
 *   Copyright(C) 2015,  Technology
 *   All rights reserved.
 *
 *   History
 *   2015.08.14  ver 1.00
 *
******************************************************************************/
#include "stdio.h"

#include "HHD1705_lib.h"




/*****************************************************************************
Function Name	CAN_SetMode
Function Definition	void CAN_SetMode(uint32_t mod)
Function Description	Set CAN mode
Input Parameters
Condition	#include sys.h
Function called	-

Last Change Date: 2015/12/12
*****************************************************************************/
void CAN_SetMode(HHD32F1_CAN_TypeDef *can, uint32_t mode)
{
    can->MOD.all = mode;

    return;
}

/*****************************************************************************
Function Name	CAN_GetStatus
Function Definition	int CAN_GetStatus()
Function Description	Get CAN SR status register
Input Parameters
Condition	#include sys.h
Function called	-

Last Change Date: 2015/12/12
*****************************************************************************/
int CAN_GetStatus(HHD32F1_CAN_TypeDef *can)
{

    return (can->SR.all);
}


/*****************************************************************************
Function Name	CAN_ClearStatus
Function Definition	int CAN_ClearStatus()
Function Description	Clear CAN SR status register
Input Parameters
Condition	#include sys.h
Function called	-

Last Change Date: 2015/12/12
*****************************************************************************/
void CAN_ClearStatus(HHD32F1_CAN_TypeDef *can, uint32_t clrbit)
{

    can->SR.all &= ~clrbit;
    return ;
}


/*****************************************************************************
Function Name	CAN_SetCMD
Function Definition	int CAN_SetCMD()
Function Description	Set CAN command register
Input Parameters
Condition	#include sys.h
Function called	-

Last Change Date: 2015/12/12
*****************************************************************************/
void CAN_SetCMD(HHD32F1_CAN_TypeDef *can, uint32_t cmddata)
{
    can->CMR.all |= cmddata;
    return;
}

/*****************************************************************************
Function Name	CAN_ClrCMD
Function Definition	int CAN_ClrCMD()
Function Description	CAN command register
Input Parameters
Condition	#include sys.h
Function called	-

Last Change Date: 2015/12/12
*****************************************************************************/
void CAN_ClrCMD(HHD32F1_CAN_TypeDef *can, uint32_t cmddata)
{
    can->CMR.all &= ~cmddata;
    return;
}

/*****************************************************************************
Function Name	CAN_EnableInt
Function Definition	void CAN_EnableInt(uint32_t intbit)
Function Description	Setup CAN interrupt
Input Parameters
Condition	#include sys.h
Function called	-

Last Change Date: 2015/12/12
*****************************************************************************/
void CAN_EnableInt(HHD32F1_CAN_TypeDef *can, uint32_t intbit)
{

    can->IER.all |= intbit ; ///int enable
    //NVIC_EnableIRQ(CAN_IRQn);
    if(can == CAN1)
    {
        NVIC_EnableIRQ(CAN1_IRQn);
    }
    else if(can == CAN2)
    {
        NVIC_EnableIRQ(CAN2_IRQn);
    }
    else return;
}

/*****************************************************************************
Function Name	CAN_DisableInt
Function Definition	void CAN_DisableInt(uint32_t intbit)
Condition	#include sys.h
Function called	-

Last Chang Date: 2015/12/12
*****************************************************************************/
void CAN_DisableInt(HHD32F1_CAN_TypeDef *can, uint32_t intbit)
{
    can->IER.all  &= ~intbit ; ///int disable
    if(can == CAN1)
    {
        NVIC_DisableIRQ(CAN1_IRQn);
    }
    else if(can == CAN2)
    {
        NVIC_DisableIRQ(CAN2_IRQn);
    }
    else return;
}


/*******************************************************************************
*
* CAN 接口初始化
*
*
* CAN使用的时钟CAN_CLK是APB1时钟，当前APB1为主频时钟;
* 波特率基于“原子时间”计算，及 一个“原子时间”的周期TQ = CAN_CLK/(2*(1+can->BTR0.bit.BRP);
* 例如 APB1 = 60M，can->BTR0.bit.BRP = 3; 1/TQ = (60/2) / ((3+1)) = 7.5M
* 波特率 BIT Period 以TQ作为单位，计算方法 Tsyncseg + Ttseg1 + Ttseg2 + 2
* Tsyncseg = 1；
* 例如 Ttseg1 = 7；Ttseg2 = 5；
  则波特率  = 7.5M/（3+7+5）= 500Kbps
********************************************************************************/
void can_init(HHD32F1_CAN_TypeDef *can, EN_BAUD baud, uint32_t canIDType, uint32_t filterID, uint32_t mask)
{
// 模块时钟	
	SYSCON->SYSAPB1CLKCTRL.bit.CAN1CLK = 1;
	SYSCON->APB1RESET.bit.CAN1RSTN=1;
	SYSCON->APB1RESET.bit.CAN1RSTN=0;
//	引脚
	HHD_AFIO -> PA11 = CAN1_RX_PA11;  			//CAN1 RX config
	HHD_AFIO -> PA12 = CAN1_TX_PA12;  			//CAN1 TX config
// 使模块进入配置模式	
	do{
		CAN_SetMode(can, ResetMode);
	}while(can->MOD.bit.RM !=  ResetMode);
// 配置波特率	
	/*
	BIT Period= Tsyncseg + Ttseg1 + Ttseg2 = 1+(7+1)+(5+1) = 15

	*/
	//TQ = 2x(1/60MHz)x2 = (1/15)us

 	can->BTR0.bit.SJW = 0x00;
	if(baud == CAN_BAUD_1M)	
	{
	
		can->BTR0.bit.BRP = 3;   			//15MHz
		can->BTR1.bit.TSEG1 = 7;
		can->BTR1.bit.TSEG2 = 0;	
	}
	else if(baud == CAN_BAUD_500K)
	{
//		can->BTR0.bit.BRP   = 2;				//10MHz
//		can->BTR1.bit.TSEG1 = 13;
//		can->BTR1.bit.TSEG2 = 4;
		
//		can->BTR0.bit.BRP   = 4;				//10MHz
//		can->BTR1.bit.TSEG1 = 13;
//		can->BTR1.bit.TSEG2 = 0;
//		
		can->BTR0.bit.BRP   = 2;				//10MHz
		can->BTR1.bit.TSEG1 = 15;
		can->BTR1.bit.TSEG2 = 2;
		
	}
	else
	{
		
//		can->BTR0.bit.BRP = 1;   
//		can->BTR1.bit.TSEG1 = 9;
//		can->BTR1.bit.TSEG2 = 3;

		can->BTR0.bit.BRP = 4;				//10MHz
		can->BTR1.bit.TSEG1 = 13;
		can->BTR1.bit.TSEG2 = 0;		
	}


 	can->BTR1.bit.SAM 	= 0;   //1,采样3次
	can->MOD.bit.AFM 	= 0x01; //Sigle filter

// 设置接收帧过滤，可以接收任何标识符
	
	if(canIDType == CAN_Id_Standard)
	{
		filterID &= 0x7FF;
		can->DATAINFO.FILTER.ACR[0].all  = ((filterID << 5) >> 8 ) & 0xFF;   //Identifier
		can->DATAINFO.FILTER.ACR[1].all  = (filterID << 5) &0xE0 ;  		 //Identifier
		can->DATAINFO.FILTER.ACR[2].all  = 0xFF;
		can->DATAINFO.FILTER.ACR[3].all  = 0xFF;

		can->DATAINFO.FILTER.AMR[0].all = ((mask << 5) >> 8 ) & 0xFF;
		can->DATAINFO.FILTER.AMR[1].all = (mask << 5) &0xE0 ;
		can->DATAINFO.FILTER.AMR[2].all = 0xff;
		can->DATAINFO.FILTER.AMR[3].all = 0xff; 
		
	}
	else
	{
		can->DATAINFO.FILTER.ACR[0].all = ((filterID << 3) >> 24) & 0xFF;   	//Identifier
		can->DATAINFO.FILTER.ACR[1].all  = ((filterID<< 3) >> 16) & 0xFF;  		//Identifier
		can->DATAINFO.FILTER.ACR[2].all  = ((filterID << 3) >> 8) & 0xFF;   	//Identifier
		can->DATAINFO.FILTER.ACR[3].all  = (filterID << 3) & 0xF8;  		    //Identifier
		
		can->DATAINFO.FILTER.AMR[0].all = ((mask << 3) >> 24) & 0xFF;   	//Identifier;
		can->DATAINFO.FILTER.AMR[1].all = ((mask<< 3) >> 16) & 0xFF;
		can->DATAINFO.FILTER.AMR[2].all = ((mask << 3) >> 8) & 0xFF;
		can->DATAINFO.FILTER.AMR[3].all = (mask << 3) & 0xF8; 
	}

// 开接收中断	
	CAN_EnableInt(can, RIE); //开启接收中断

#ifdef SELF_LOOP
	CAN_SetMode(can, ACCFMode | SelfTestMode);
#else
	CAN_SetMode(can, ACCFMode | ActiveMode);	
#endif	

}

/***********************************************************************************************
*
*
*	CAN 写数据
*
*
************************************************************************************************/
int can_write(HHD32F1_CAN_TypeDef *can, enum FRMAT_TYPE type, union UN_CAN_IDENTIFY *Identifier,  uint8_t *data, int len)
{
	int i = 0;
	int count = len / 8;									//发送帧数
	int other = len % 8;									//最后一帧数据长度
	uint8_t start = 2;
	while((CAN_GetStatus(can) & RecSt) == RecSt);
	while((CAN_GetStatus(can) & TranComplete) != TranComplete);
	while((CAN_GetStatus(can) & TranBufSt) != TranBufSt);
	
	   
	can->DATAINFO.TxDATAINFO.TxFRAME.all = 0x08 |(uint8_t)type;		// 帧长度

	can->DATAINFO.TxDATAINFO.TxDATA[0].all = Identifier->data[0];  		//Identifier
	can->DATAINFO.TxDATAINFO.TxDATA[1].all = Identifier->data[1];  		//Identifier
	
	if(type == EXT_FF)
	{
		can->DATAINFO.TxDATAINFO.TxDATA[2].all = Identifier->data[2];  		//Identifier
		can->DATAINFO.TxDATAINFO.TxDATA[3].all = Identifier->data[3];  		//Identifier
		start = 4;
	}
	
	
	for(i = 0; i < count; i++)
	{
		
		can->DATAINFO.TxDATAINFO.TxDATA[start+0].all = data[i*8+0];  //data 1
		can->DATAINFO.TxDATAINFO.TxDATA[start+1].all = data[i*8+1];  //data 2
		can->DATAINFO.TxDATAINFO.TxDATA[start+2].all = data[i*8+2];  //data 3
		can->DATAINFO.TxDATAINFO.TxDATA[start+3].all = data[i*8+3];  //data 4
		can->DATAINFO.TxDATAINFO.TxDATA[start+4].all = data[i*8+4];  //data 5
		can->DATAINFO.TxDATAINFO.TxDATA[start+5].all = data[i*8+5];  //data 5
		can->DATAINFO.TxDATAINFO.TxDATA[start+6].all = data[i*8+6];  //data 7
		can->DATAINFO.TxDATAINFO.TxDATA[start+7].all = data[i*8+7];  //data 8
#ifdef SELF_LOOP		
		CAN_SetCMD(can, SelfRecReq);                             	// 启动发送
#else		
		CAN_SetCMD(can, TransReq);                             		// 启动发送
#endif		
		while((CAN_GetStatus(can) & TranComplete) != TranComplete);	//等待发送完成
		while((CAN_GetStatus(can) & TranBufSt) != TranBufSt);	    // 等待发送缓冲被释放
	
	}
	if(other > 0)
	{
		can->DATAINFO.TxDATAINFO.TxFRAME.all = other;    			// 帧长度

		for(i = 0; i < other; i++)
		{
			can->DATAINFO.TxDATAINFO.TxDATA[2+i].all = data[count*8+i];  //data 
		}

		CAN_SetCMD(can, TransReq);                             		// 启动发送
		while((CAN_GetStatus(can) & TranComplete) != TranComplete);	//等待发送完成
		while((CAN_GetStatus(can) & TranBufSt) != TranBufSt);	    // 等待发送缓冲被释放
	
	}
	
	return len;
}

/***********************************************************************************************
*
*
*	CAN 发送一帧数据
*
*
************************************************************************************************/
uint32_t can_timeout = 1000;
int CAN_Transmit(HHD32F1_CAN_TypeDef *can, CanTxMsg *TxMessage)
{
	uint8_t start = 2;
	uint8_t i = 0;
	uint32_t time = 0;
	can->DATAINFO.TxDATAINFO.TxFRAME.all = TxMessage->DLC | TxMessage->IDE |TxMessage->RTR;		// 帧长度
	if(TxMessage->IDE == CAN_Id_Standard)
	{
		can->DATAINFO.TxDATAINFO.TxDATA[0].all = ((TxMessage->StdId << 5) >> 8 ) & 0xFF;   		//Identifier
		can->DATAINFO.TxDATAINFO.TxDATA[1].all = (TxMessage->StdId << 5) &0xE0 ;  		//Identifier
	}
	else
	{
		can->DATAINFO.TxDATAINFO.TxDATA[0].all = ((TxMessage->ExtId << 3) >> 24) & 0xFF;   		//Identifier
		can->DATAINFO.TxDATAINFO.TxDATA[1].all = ((TxMessage->ExtId << 3) >> 16) & 0xFF;  		//Identifier
		can->DATAINFO.TxDATAINFO.TxDATA[2].all = ((TxMessage->ExtId << 3) >> 8) & 0xFF;   		//Identifier
		can->DATAINFO.TxDATAINFO.TxDATA[3].all = (TxMessage->ExtId << 3) & 0xF8;  		//Identifier
		start = 4;
	}
	
	for(i = 0; i < TxMessage->DLC; i++)
	{
		
		can->DATAINFO.TxDATAINFO.TxDATA[start+i].all = TxMessage->Data[i];  //data 1
	}
#ifdef SELF_LOOP		
		CAN_SetCMD(can, SelfRecReq);                             	// 启动发送
#else		
		CAN_SetCMD(can, TransReq);                             		// 启动发送
#endif	
		time = Get_Tick();	
		while(((CAN_GetStatus(can) & TranComplete) != TranComplete) && 
			((Get_Tick() - time) < can_timeout) );	//等待发送完成
		if((Get_Tick() - time) >= can_timeout)
		{
			return CAN_TxStatus_Failed;
		}
		time = Get_Tick();	
		while(((CAN_GetStatus(can) & TranBufSt) != TranBufSt) && 
			((Get_Tick() - time) < can_timeout));	    // 等待发送缓冲被释放
		
		if((Get_Tick() - time) >= can_timeout)
		{
			return CAN_TxStatus_Failed;
		}
	
	return CAN_TxStatus_Ok;
}

/***********************************************************************************************
*
*
*	CAN 接收一帧数数据
*
*
************************************************************************************************/
int CAN_Receive(HHD32F1_CAN_TypeDef *can, uint8_t FIFONumber, CanRxMsg* RxMessage)
{
	uint8_t start = 2;
	uint8_t i = 0;
	
	RxMessage->DLC = can->DATAINFO.RxDATAINFO.RxFRAME.all & 0x0F;
	RxMessage->IDE = can->DATAINFO.RxDATAINFO.RxFRAME.all & 0x80;
	RxMessage->RTR = can->DATAINFO.RxDATAINFO.RxFRAME.all & 0x40;
	
	if(RxMessage->IDE == CAN_Id_Extended)
	{
		
		RxMessage->ExtId = ((can->DATAINFO.RxDATAINFO.RxDATA[0].all & 0xFF) << 24 ) | 
						   ((can->DATAINFO.RxDATAINFO.RxDATA[1].all & 0xFF) << 16 ) |
						   ((can->DATAINFO.RxDATAINFO.RxDATA[2].all & 0xFF) << 8  ) |
						   ((can->DATAINFO.RxDATAINFO.RxDATA[3].all & 0xF8) << 0);
	
		RxMessage->ExtId = RxMessage->ExtId >> 3;
		
		start = 4;
	
	}
	else
	{
		RxMessage->StdId = ((can->DATAINFO.RxDATAINFO.RxDATA[0].all & 0xFF )<< 8 ) | 
						   ((can->DATAINFO.RxDATAINFO.RxDATA[1].all & 0xE0 )<< 0 ) ;
		
		RxMessage->StdId = RxMessage->StdId >> 5;
	}
	
	for(i = 0; i < RxMessage->DLC; i++)
	{
		RxMessage->Data[i] =  can->DATAINFO.RxDATAINFO.RxDATA[start+i].all;
	}

	RxMessage->FMI = 0;
	
	return CAN_TxStatus_Ok;


}

/***********************************************************************************************
*
*
*	CAN 回写收到的数据
*
*
************************************************************************************************/

void can_write_back(HHD32F1_CAN_TypeDef *can,  uint8_t *data)
{
	int i = 0;

	while((CAN_GetStatus(can) & RecSt) == RecSt);
	while((CAN_GetStatus(can) & TranComplete) != TranComplete);
	while((CAN_GetStatus(can) & TranBufSt) != TranBufSt);
	
	   
	can->DATAINFO.TxDATAINFO.TxFRAME.all = data[0] ;		// 帧长度

	for(i = 0; i < 12; i++)
	{
		can->DATAINFO.TxDATAINFO.TxDATA[i].all = data[i+1];
	
	}
	
#ifdef SELF_LOOP		
		CAN_SetCMD(can, SelfRecReq);                             	// 启动发送
#else		
		CAN_SetCMD(can, TransReq);                             		// 启动发送
#endif		
		while((CAN_GetStatus(can) & TranComplete) != TranComplete);	//等待发送完成
		while((CAN_GetStatus(can) & TranBufSt) != TranBufSt);	    // 等待发送缓冲被释放

}





