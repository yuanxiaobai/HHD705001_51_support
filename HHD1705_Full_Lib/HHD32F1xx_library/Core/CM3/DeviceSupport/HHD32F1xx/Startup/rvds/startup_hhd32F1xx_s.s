;/*
; *-----------------------------------------------------------------------------
; * The confidential and proprietary information contained in this file may
; * only be used by a person authorised under and to the extent permitted
; * by a subsisting licensing agreement from ARM Limited.
; *
; *            (C) COPYRIGHT 2010-2011 ARM Limited.
; *                ALL RIGHTS RESERVED
; *
; * This entire notice must be reproduced on all copies of this file
; * and copies of this file may only be made by a person if such person is
; * permitted to do so under the terms of a subsisting license agreement
; * from ARM Limited.
; *
; *-----------------------------------------------------------------------------
; */

;/*****************************************************************************/
;/* Startup.s: Startup file for ARM Cortex-M3 Device Family                   */
;/*****************************************************************************/


;// <h> Stack Configuration
;//   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;// </h>

Stack_Size      EQU     0x000002000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


;// <h> Heap Configuration
;//   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;// </h>

Heap_Size       EQU     0x000001000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemoryManagement_Handler  ; Memory Management Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMonitor_Handler      ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler
                ; External Interrupts
                DCD     WWDT_IRQHandler           ; 16+ 0: Window Watchdog
                DCD     BOD_IRQHandler            ; 16+ 1: Brown Out Detect
                DCD     DAC_IRQHandler            ; 16+ 2: DAC
                DCD     RTC_IRQHandler            ; 16+ 3: RTC
                DCD     0                         ; 16+ 4: Reserved
                DCD     0                         ; 16+ 5: Reserved
                DCD     EXTI0_IRQHandler          ; 16+ 6: EXTI line0
                DCD     EXTI1_IRQHandler          ; 16+ 7: EXTI line1
                DCD     EXTI2_IRQHandler          ; 16+ 8: EXTI line2
                DCD     EXTI3_IRQHandler          ; 16+ 9: EXTI line3
                DCD     EXTI4_IRQHandler          ; 16+10: EXTI line4
                DCD     DMA1_CHANNEL1_IRQHandler  ; 16+11: DMA1 channel 1
                DCD     DMA1_CHANNEL2_IRQHandler  ; 16+12: DMA1 channel 2
                DCD     DMA1_CHANNEL3_IRQHandler  ; 16+13: DMA1 channel 3
                DCD     DMA1_CHANNEL4_IRQHandler  ; 16+14: DMA1 channel 4
                DCD     DMA1_CHANNEL5_IRQHandler  ; 16+15: DMA1 channel 5
                DCD     DMA1_CHANNEL6_IRQHandler  ; 16+16: DMA1 channel 6
                DCD     DMA1_CHANNEL7_IRQHandler  ; 16+17: DMA1 channel 7
                DCD     ADC1_2_IRQHandler         ; 16+18: ADC1 and ADC2 Converter
                DCD     USB_IRQHandler            ; 16+19: Reserved
                DCD     0                         ; 16+20: Reserved
                DCD     CAN1_IRQHandler            ; 16+21: Reserved
                DCD     0                         ; 16+22: Reserved
                DCD     EXTI9_5_IRQHandler        ; 16+23: EXTI line9 and line5
                DCD     TIM1FAULT_TIM9_IRQHandler ; 16+24: TIM1 Fault & TIM9
                DCD     TIM10_IRQHandler          ; 16+25: TIM10
                DCD     TIM11_IRQHandler          ; 16+26: TIM11
                DCD     TIM1_IRQHandler           ; 16+27: TIM1 
                DCD     TIM2_IRQHandler           ; 16+28: TIM2 
                DCD     TIM3_IRQHandler           ; 16+29: TIM3 
                DCD     TIM4_IRQHandler           ; 16+30: TIM4 
                DCD     I2C1_IRQHandler           ; 16+31: I2C1
                DCD     0                         ; 16+32: Reserved
                DCD     I2C2_IRQHandler           ; 16+33: I2C2
                DCD     0                         ; 16+34: Reserved
                DCD     SPI1_IRQHandler           ; 16+35: SPI1
                DCD     SPI2_IRQHandler           ; 16+36: SPI2
                DCD     UART1_IRQHandler          ; 16+37: UART1
                DCD     UART2_IRQHandler          ; 16+38: UART2
                DCD     UART3_IRQHandler          ; 16+39: UART3
                DCD     EXTI15_10_IRQHandler      ; 16+40: EXTI line[15:10]
                DCD     0                         ; 16+41: Reserved
                DCD     USBWAKEUP_IRQHandler      ; 16+42: 
                DCD     TIM8FAULT_TIM12_IRQHandler; 16+43: TIM8 Fault & TIM12
                DCD     TIM13_IRQHandler          ; 16+44: TIM13 
                DCD     TIM14_IRQHandler          ; 16+45: TIM14 
                DCD     TIM8_IRQHandler           ; 16+46: TIM8
                DCD     ADC3_IRQHandler           ; 16+47: ADC3
                DCD     SPI4_IRQHandler           ; 16+48: Reserved
                DCD     SPI5_IRQHandler           ; 16+49: Reserved
                DCD     TIM5_IRQHandler           ; 16+50: TIM5
                DCD     SPI3_IRQHandler           ; 16+51: SPI3
                DCD     UART4_IRQHandler          ; 16+52: UART4
                DCD     UART5_IRQHandler          ; 16+53: UART5
                DCD     TIM6_IRQHandler           ; 16+54: TIM6
                DCD     TIM7_IRQHandler           ; 16+55: TIM7
                DCD     DMA2_CHANNEL1_IRQHandler  ; 16+56: DMA2 channel 1
                DCD     DMA2_CHANNEL2_IRQHandler  ; 16+57: DMA2 channel 2
                DCD     DMA2_CHANNEL3_IRQHandler  ; 16+58: DMA2 channel 3
                DCD     DMA2_CHANNEL4_5_IRQHandler; 16+59: DMA2 channel 4&5
                DCD     0                         ; 16+60: 
                DCD     0                         ; 16+61: 
                DCD     ETH_IRQHandler            ; 16+62: 
				DCD     ETH_PMT_IRQHandler	      ; 16+63:
                DCD     0                         ; 16+64: 
                DCD     CAN2_IRQHandler           ; 16+65: 
 
__Vectors_End

__Vectors_Size         EQU     __Vectors_End - __Vectors
                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  __main
                IMPORT  SystemInit

                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler      PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemoryManagement_Handler   PROC
                EXPORT  MemoryManagement_Handler  [WEAK]
                B       .
                ENDP
BusFault_Handler    PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler  PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMonitor_Handler   PROC
                EXPORT  DebugMonitor_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
               EXPORT  SysTick_Handler            [WEAK]
               B       .
               ENDP



Default_Handler PROC
             EXPORT  WWDT_IRQHandler          		[WEAK] 
             EXPORT  BOD_IRQHandler           		[WEAK] 
			 EXPORT  DAC_IRQHandler           		[WEAK]
             EXPORT  RTC_IRQHandler           		[WEAK] 
             EXPORT  EXTI0_IRQHandler         		[WEAK] 
             EXPORT  EXTI1_IRQHandler         		[WEAK] 
             EXPORT  EXTI2_IRQHandler         		[WEAK] 
             EXPORT  EXTI3_IRQHandler         		[WEAK] 
             EXPORT  EXTI4_IRQHandler         		[WEAK] 
             EXPORT  DMA1_CHANNEL1_IRQHandler 		[WEAK] 
             EXPORT  DMA1_CHANNEL2_IRQHandler 		[WEAK] 
             EXPORT  DMA1_CHANNEL3_IRQHandler 		[WEAK] 
             EXPORT  DMA1_CHANNEL4_IRQHandler 		[WEAK] 
             EXPORT  DMA1_CHANNEL5_IRQHandler 		[WEAK] 
             EXPORT  DMA1_CHANNEL6_IRQHandler 		[WEAK] 
             EXPORT  DMA1_CHANNEL7_IRQHandler 		[WEAK] 
             EXPORT  ADC1_2_IRQHandler        		[WEAK] 
             EXPORT  EXTI9_5_IRQHandler       		[WEAK]
             EXPORT  TIM1FAULT_TIM9_IRQHandler     	[WEAK] 
             EXPORT  TIM10_IRQHandler         		[WEAK] 
             EXPORT  TIM11_IRQHandler         		[WEAK] 
             EXPORT  TIM1_IRQHandler          		[WEAK] 
             EXPORT  TIM2_IRQHandler          		[WEAK] 
             EXPORT  TIM3_IRQHandler          		[WEAK] 
             EXPORT  TIM4_IRQHandler          		[WEAK] 
             EXPORT  I2C1_IRQHandler          		[WEAK] 
             EXPORT  I2C2_IRQHandler          		[WEAK] 
             EXPORT  SPI1_IRQHandler          		[WEAK] 
             EXPORT  SPI2_IRQHandler          		[WEAK] 
             EXPORT  UART1_IRQHandler         		[WEAK] 
             EXPORT  UART2_IRQHandler         		[WEAK] 
             EXPORT  UART3_IRQHandler         		[WEAK] 
             EXPORT  EXTI15_10_IRQHandler     		[WEAK] 
             EXPORT  USBWAKEUP_IRQHandler     		[WEAK] 
             EXPORT  TIM8FAULT_TIM12_IRQHandler     [WEAK] 
             EXPORT  TIM13_IRQHandler         		[WEAK] 
             EXPORT  TIM14_IRQHandler         		[WEAK] 
             EXPORT  TIM8_IRQHandler          		[WEAK] 
             EXPORT  ADC3_IRQHandler          		[WEAK] 
             EXPORT  TIM5_IRQHandler          		[WEAK] 
             EXPORT  SPI3_IRQHandler          		[WEAK] 
             EXPORT  UART4_IRQHandler         		[WEAK] 
             EXPORT  UART5_IRQHandler         		[WEAK] 
             EXPORT  TIM6_IRQHandler          		[WEAK] 
             EXPORT  TIM7_IRQHandler          		[WEAK] 
             EXPORT  DMA2_CHANNEL1_IRQHandler 		[WEAK] 
             EXPORT  DMA2_CHANNEL2_IRQHandler 		[WEAK] 
             EXPORT  DMA2_CHANNEL3_IRQHandler 		[WEAK] 
             EXPORT  DMA2_CHANNEL4_5_IRQHandler 	[WEAK] 
             EXPORT  USB_IRQHandler           		[WEAK] 
             EXPORT  CAN1_IRQHandler           		[WEAK]
		     EXPORT  ETH_IRQHandler                 [WEAK]
             EXPORT  ETH_PMT_IRQHandler        		[WEAK] 
             EXPORT  CAN2_IRQHandler           		[WEAK] 
			 EXPORT  SPI4_IRQHandler                [WEAK]
		     EXPORT  SPI5_IRQHandler                [WEAK]				 
		  

WWDT_IRQHandler           
BOD_IRQHandler 
DAC_IRQHandler
RTC_IRQHandler            
EXTI0_IRQHandler          
EXTI1_IRQHandler          
EXTI2_IRQHandler          
EXTI3_IRQHandler          
EXTI4_IRQHandler          
DMA1_CHANNEL1_IRQHandler  
DMA1_CHANNEL2_IRQHandler  
DMA1_CHANNEL3_IRQHandler  
DMA1_CHANNEL4_IRQHandler  
DMA1_CHANNEL5_IRQHandler  
DMA1_CHANNEL6_IRQHandler  
DMA1_CHANNEL7_IRQHandler  
ADC1_2_IRQHandler         
EXTI9_5_IRQHandler       
TIM1FAULT_TIM9_IRQHandler      
TIM10_IRQHandler          
TIM11_IRQHandler          
TIM1_IRQHandler           
TIM2_IRQHandler           
TIM3_IRQHandler           
TIM4_IRQHandler           
I2C1_IRQHandler           
I2C2_IRQHandler           
SPI1_IRQHandler           
SPI2_IRQHandler           
UART1_IRQHandler          
UART2_IRQHandler          
UART3_IRQHandler          
EXTI15_10_IRQHandler      
USBWAKEUP_IRQHandler       
TIM8FAULT_TIM12_IRQHandler      
TIM13_IRQHandler          
TIM14_IRQHandler          
TIM8_IRQHandler           
ADC3_IRQHandler           
TIM5_IRQHandler           
SPI3_IRQHandler           
UART4_IRQHandler          
UART5_IRQHandler          
TIM6_IRQHandler           
TIM7_IRQHandler           
DMA2_CHANNEL1_IRQHandler  
DMA2_CHANNEL2_IRQHandler  
DMA2_CHANNEL3_IRQHandler  
DMA2_CHANNEL4_5_IRQHandler  
CAN1_IRQHandler
CAN2_IRQHandler
USB_IRQHandler           
ETH_IRQHandler
ETH_PMT_IRQHandler
SPI4_IRQHandler 
SPI5_IRQHandler
               B       .
               ENDP

                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END

