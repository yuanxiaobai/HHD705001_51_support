;/*****************************************************************************
; * @file:    startup_xdp12xx.s
; * @purpose: CMSIS Cortex-M0 Core Device Startup File 
; *           for the XINNOVA XDP12xx Device Series 
; * @version: V1.0
; * @date:    25. Nov. 2008
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; * Copyright (C) 2008 ARM Limited. All rights reserved.
; * ARM Limited (ARM) is supplying this software for use with Cortex-M0 
; * processor based microcontrollers.  This file can be freely distributed 
; * within development tools that are supporting such ARM based processors. 
; *
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; *****************************************************************************/


/*****************************************************************************/
/* startup_CMSDK_CM0.s: Startup file for CMSDK device series               */
/*****************************************************************************/
/* Version: CodeSourcery Sourcery G++ Lite (with CS3)                        */
/*****************************************************************************/

/*
//*** <<< Use Configuration Wizard in Context Menu >>> ***
*/

/*
// <h> Stack Configuration
//   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
// </h>
*/

    .equ    Stack_Size, 0x00000200
    .section ".stack", "w"
    .align  3
    .globl  __cs3_stack_mem
    .globl  __cs3_stack_size
__cs3_stack_mem:
    .if     Stack_Size
    .space  Stack_Size
    .endif
    .size   __cs3_stack_mem,  . - __cs3_stack_mem
    .set    __cs3_stack_size, . - __cs3_stack_mem

/*
// <h> Heap Configuration
//   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
// </h>
*/

    .equ    Heap_Size,  0x00000000

    .section ".heap", "w"
    .align  3
    .globl  __cs3_heap_start
    .globl  __cs3_heap_end
__cs3_heap_start:
    .if     Heap_Size
    .space  Heap_Size
    .endif
__cs3_heap_end:


/* Vector Table */

    .section ".cs3.interrupt_vector"
    .globl  __cs3_interrupt_vector_cortex_m
    .type   __cs3_interrupt_vector_cortex_m, %object

__cs3_interrupt_vector_cortex_m:
    .long   __cs3_stack                 /* Top of Stack                  */
    .long   __cs3_reset_cortex_m        /* Reset Handler                 */
    .long   NMI_Handler                 /* NMI Handler                   */
    .long   HardFault_Handler           /* Hard Fault Handler            */
    .long   MemoryManagement_Handler    /* Reserved                      */
    .long   BusFault_Handler            /* Reserved                      */
    .long   UsageFault_Handler          /* Reserved                      */
    .long   0                           /* Reserved                      */
    .long   0                           /* Reserved                      */
    .long   0                           /* Reserved                      */
    .long   0                           /* Reserved                      */
    .long   SVC_Handler                 /* SVCall Handler                */
    .long   DebugMonitor_Handler        /* Reserved                      */
    .long   0                           /* Reserved                      */
    .long   PendSV_Handler              /* PendSV Handler                */
    .long   SysTick_Handler             /* SysTick Handler               */

    /* External Interrupts */
                .long     WWDT_IRQHandler               /*  16+ 0:           */
                .long     BOD_IRQHandler                /*  16+ 1: I                   */
                .long     0                             /*  16+ 2:                    */
                .long     RTC_IRQHandler                /*  16+ 3:          */
                .long     0                             /*  16+ 4:          */
                .long     0                             /*  16+ 5       */
                .long     EXTI0_IRQHandler              /*  16+ 6       */
                .long     EXTI0_IRQHandler              /*  16+ 7       */
                .long     EXTI0_IRQHandler              /*  16+ 8       */         
                .long     EXTI0_IRQHandler              /*  16+ 9       */
                .long     EXTI0_IRQHandler              /*  16+10      */
                .long     DMA1_CHANNEL1_IRQHandler      /*  16+11      */     
                .long     DMA1_CHANNEL2_IRQHandler      /*  16+12      */
                .long     DMA1_CHANNEL3_IRQHandler      /*  16+13      */
                .long     DMA1_CHANNEL4_IRQHandler      /*  16+14      */
                .long     DMA1_CHANNEL5_IRQHandler      /*  16+15      */
                .long     DMA1_CHANNEL6_IRQHandler      /*  16+16      */
                .long     DMA1_CHANNEL7_IRQHandler      /*  16+17      */
                .long     ADC1_2_IRQHandler             /*  16+18: PWM Generator        */
                .long     USB_IRQHandler                /*  16+19: Reserved              */
                .long     0                             /*  16+20: Reserved              */
                .long     CAN_IRQHandler                /*  16+21: Reserved              */
                .long     0                             /*  16+22: Reserved              */
                .long     EXTI9_5_IRQHandler            /*  16+23: Reserved              */
                .long     TIM1FAULT_IRQHandler          /*  16+24: Reserved              */
                .long     TIM10_IRQHandler              /*  16+25: Reserved              */
                .long     TIM11_IRQHandler              /*  16+26: Reserved              */
                .long     TIM1_IRQHandler               /*  16+27: Reserved              */
                .long     TIM2_IRQHandler               /*  16+28: Reserved              */
                .long     TIM3_IRQHandler               /*  16+29: Reserved              */
                .long     TIM4_IRQHandler               /*  16+30: Reserved              */
                .long     I2C1_IRQHandler               /*  16+31: Reserved              */
                .long     0                             /*  16+31: Reserved              */
                .long     I2C2_IRQHandler               /*  16+31: Reserved              */
                .long     0                             /*  16+31: Reserved              */
                .long     SPI1_IRQHandler               /*  16+31: Reserved              */
                .long     SPI2_IRQHandler               /*  16+31: Reserved              */
                .long     UART1_IRQHandler              /*  16+31: Reserved              */
                .long     UART2_IRQHandler              /*  16+31: Reserved              */
                .long     UART3_IRQHandler              /*  16+31: Reserved              */
                .long     EXTI15_10_IRQHandler          /*  16+31: Reserved              */
                .long     RTCAlarm_IRQHandler           /*  16+31: Reserved              */
                .long     0                             /*  16+31: Reserved              */
                .long     TIM8FAULT_IRQHandler          /*  16+31: Reserved              */
                .long     TIM13_IRQHandler              /*  16+31: Reserved              */
                .long     TIM14_IRQHandler              /*  16+31: Reserved              */
                .long     TIM8_IRQHandler               /*  16+31: Reserved              */
                .long     ADC3_IRQHandler               /*  16+31: Reserved              */
                .long     0                             /*  16+31: Reserved              */
                .long     0                             /*  16+31: Reserved              */
                .long     TIM5_IRQHandler               /*  16+31: Reserved              */
                .long     SPI3_IRQHandler               /*  16+31: Reserved              */
                .long     UART4_IRQHandler              /*  16+31: Reserved              */
                .long     UART5_IRQHandler              /*  16+31: Reserved              */
                .long     TIM6_IRQHandler               /*  16+31: Reserved              */
                .long     TIM7_IRQHandler               /*  16+31: Reserved              */
                .long     DMA1_CHANNEL1_IRQHandler      /*  16+11      */     
                .long     DMA1_CHANNEL1_IRQHandler      /*  16+12      */
                .long     DMA1_CHANNEL1_IRQHandler      /*  16+13      */
                .long     DMA1_CHANNEL1_IRQHandler      /*  16+14      */
                .long     DMA1_CHANNEL1_IRQHandler      /*  16+15      */

    .size   __cs3_interrupt_vector_cortex_m, . - __cs3_interrupt_vector_cortex_m

    .thumb

/* Reset Handler */

    .section .cs3.reset,"x",%progbits
    .thumb_func
    .globl  __cs3_reset_cortex_m
    .type   __cs3_reset_cortex_m, %function
__cs3_reset_cortex_m:
    .fnstart
    LDR     R0, =SystemInit
    BLX     R0

    MOVS    R0,#0 /* Clear the registers to avoid unknown value in verilog simulations */
    MOV     R1,R0
    MOV     R2,R0
    MOV     R3,R0
    MOV     R4,R0
    MOV     R5,R0
    MOV     R6,R0
    MOV     R7,R0
    MOV     R8,R0
    MOV     R9,R0
    MOV     R10,R0
    MOV     R11,R0
    MOV     R12,R0

    LDR     R0,=_start
    BX      R0
    .pool
    .cantunwind
    .fnend
    .size   __cs3_reset_cortex_m,.-__cs3_reset_cortex_m

    .section ".text"

/* Exception Handlers */

    .weak   NMI_Handler
    .type   NMI_Handler, %function
NMI_Handler:
    B       .
    .size   NMI_Handler, . - NMI_Handler

    .weak   HardFault_Handler
    .type   HardFault_Handler, %function
HardFault_Handler:
    B       .
    .size   HardFault_Handler, . - HardFault_Handler

    .weak   MemoryManagement_Handler
    .type   MemoryManagement_Handler, %function
MemoryManagement_Handler:
    B       .
    .size   MemoryManagement_Handler, . - MemoryManagement_Handler

    .weak   BusFault_Handler
    .type   BusFault_Handler, %function
BusFault_Handler:
    B       .
    .size   BusFault_Handler, . - BusFault_Handler

    .weak   UsageFault_Handler
    .type   UsageFault_Handler, %function
UsageFault_Handler:
    B       .
    .size   UsageFault_Handler, . - UsageFault_Handler

    .weak   SVC_Handler
    .type   SVC_Handler, %function
SVC_Handler:
    B       .
    .size   SVC_Handler, . - SVC_Handler

    .weak   DebugMonitor_Handler
    .type   DebugMonitor_Handler, %function
DebugMonitor_Handler:
    B       .
    .size   DebugMonitor_Handler, . - DebugMonitor_Handler

    .weak   PendSV_Handler
    .type   PendSV_Handler, %function
PendSV_Handler:
    B       .
    .size   PendSV_Handler, . - PendSV_Handler

    .weak   SysTick_Handler
    .type   SysTick_Handler, %function
SysTick_Handler:
    B       .
    .size   SysTick_Handler, . - SysTick_Handler


/* IRQ Handlers */

    .globl  Default_Handler
    .type   Default_Handler, %function
Default_Handler:
    B       .
    .size   Default_Handler, . - Default_Handler

/* Macro to map "weak" peripheral interrupt to default handler */
    .macro  IRQ handler
    .weak   \handler
    .set    \handler, Default_Handler
    .endm

    IRQ    WWDT_IRQHandler
    IRQ    BOD_IRQHandler
    IRQ    RTC_IRQHandler
    IRQ    EXTI0_IRQHandler
    IRQ    EXTI1_IRQHandler
    IRQ    EXTI2_IRQHandler
    IRQ    EXTI3_IRQHandler
    IRQ    EXTI4_IRQHandler        
    IRQ    DMA1_CHANNEL1_IRQHandler
    IRQ    DMA1_CHANNEL2_IRQHandler
    IRQ    DMA1_CHANNEL3_IRQHandler
    IRQ    DMA1_CHANNEL4_IRQHandler
    IRQ    DMA1_CHANNEL5_IRQHandler
    IRQ    DMA1_CHANNEL6_IRQHandler
    IRQ    DMA1_CHANNEL7_IRQHandler
    IRQ    ADC1_2_IRQHandler 
    IRQ    USB_IRQHandler
    IRQ    CAN_IRQHandler
    IRQ    EXTI9_5_IRQHandler  
    IRQ    TIM1FAULT_IRQHandler
    IRQ    TIM10_IRQHandler
    IRQ    TIM11_IRQHandler
    IRQ    TIM1_IRQHandler
    IRQ    TIM2_IRQHandler
    IRQ    TIM3_IRQHandler
    IRQ    TIM4_IRQHandler
    IRQ    I2C1_IRQHandler
    IRQ    I2C2_IRQHandler
    IRQ    SPI1_IRQHandler
    IRQ    SPI2_IRQHandler 
    IRQ    UART1_IRQHandler
    IRQ    UART2_IRQHandler
    IRQ    UART3_IRQHandler    
    IRQ    EXTI15_10_IRQHandler
    IRQ    RTCAlarm_IRQHandler 
    IRQ    TIM8FAULT_IRQHandler
    IRQ    TIM13_IRQHandler
    IRQ    TIM14_IRQHandler
    IRQ    TIM8_IRQHandler
    IRQ    ADC3_IRQHandler
    IRQ    TIM5_IRQHandler
    IRQ    SPI3_IRQHandler 
    IRQ    UART4_IRQHandler
    IRQ    UART5_IRQHandler
    IRQ    TIM6_IRQHandler
    IRQ    TIM7_IRQHandler
    IRQ    DMA2_CHANNEL1_IRQHandler
    IRQ    DMA2_CHANNEL2_IRQHandler
    IRQ    DMA2_CHANNEL3_IRQHandler
    IRQ    DMA2_CHANNEL4_IRQHandler
    IRQ    DMA2_CHANNEL5_IRQHandler

  
    .end

