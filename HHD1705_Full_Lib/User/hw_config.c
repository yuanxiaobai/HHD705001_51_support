/******************************************************************
**	  ����107�����壨V1.0��
**	  ���������ļ�
**
**	  ��    ̳��bbs.openmcu.com
**	  ��    ����www.openmcu.com
**	  ��    �䣺support@openmcu.com
**
**    ��    ����V1.1
**	  ��    �ߣ�openmcu
**	  �������:	2014.3.5
********************************************************************/

#include "hw_config.h"

/*********************************************
*�������ƣ�void NVIC_Configuration(void)
*
*��ڲ�������
*
*���ڲ�������
*
*����˵�����ж�Ƕ�׹���
**********************************************/
/*
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			  //�жϷ���2

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 		  //USART1�����ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
*/
/*************************************************
*�������ƣ�void LED_Configuration(void)
*
*��ڲ�������
*
*���ڲ�������
*
*����˵����LED��ʼ������
***************************************************/
void LED_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_LED, ENABLE);
    GPIO_InitStructure.GPIO_Pin = LED1_PIN | LED3_PIN | LED4_PIN | LED5_PIN ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);

    LED1(0);	//�ĸ�LEDȫOFF
    LED3(0);
    LED4(0);
    LED5(0);
}


/*********************************************
*�������ƣ�void USART_Configuration(void)
*
*��ڲ�������
*
*���ڲ�������
*
*����˵����USART1��2 ��ʼ������ ����GPIO��ʼ�� TX��������Ϊ�������
**********************************************/
void USART_Configuration(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD
                            | RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    /*USART1�˿�����
      PA9 TX ����������� PA10 RX ��������ģʽ*/
    /*	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9 ;
    	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    	GPIO_Init(GPIOA, &GPIO_InitStructure);

    	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 ;
    	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    	GPIO_Init(GPIOA, &GPIO_InitStructure);
    */
    /*USART2�˿�����
      PD5 TX ����������� PD6 RX ��������ģʽ*/
    GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5 ;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 ;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /*--------------USART1 USART2����-------------------*/
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    //	USART_Init(USART1, &USART_InitStructure);
    USART_Init(USART2, &USART_InitStructure);
    //	USART_Cmd(USART1, ENABLE);
    USART_Cmd(USART2, ENABLE);

    //	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}
/*********************************************
*�������ƣ�void USART2_SendString(uint8_t *ch)
*
*��ڲ�������
*
*���ڲ�������
*
*����˵����USART2 �����ַ���
**********************************************/
void USART2_SendString(uint8_t *ch)
{
    while(*ch != 0)
    {
        while(!USART_GetFlagStatus(USART2, USART_FLAG_TXE));
        USART_SendData(USART2, *ch);
        ch++;
    }
}

