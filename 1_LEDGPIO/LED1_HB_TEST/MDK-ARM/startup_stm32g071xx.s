;******************************************************************************
;* File Name          : startup_stm32g071xx.s
;* Author             : MCD Application Team
;* Description        : STM32G071xx devices vector table for MDK-ARM toolchain.
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == Reset_Handler
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the CortexM0 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;* <<< Use Configuration Wizard in Context Menu >>>
;****************************************************************************** 
;* @attention
;*
;* Copyright (c) 2018 STMicroelectronics. All rights reserved.
;*
;* This software component is licensed by ST under Apache License, Version 2.0,
;* the "License"; You may not use this file except in compliance with the
;* License. You may obtain a copy of the License at:
;*                        opensource.org/licenses/Apache-2.0
;*
;******************************************************************************

; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size		EQU     0x400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size      EQU     0x200

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

__Vectors       DCD     __initial_sp                   ; Top of Stack
                DCD     Reset_Handler                  ; Reset Handler
                DCD     NMI_Handler                    ; NMI Handler
                DCD     HardFault_Handler              ; Hard Fault Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     SVC_Handler                    ; SVCall Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     PendSV_Handler                 ; PendSV Handler
                DCD     SysTick_Handler                ; SysTick Handler

                ; External Interrupts
                DCD     WWDG_IRQHandler                ; Window Watchdog
                DCD     PVD_IRQHandler                 ; PVD through EXTI Line detect
                DCD     RTC_TAMP_IRQHandler            ; RTC through EXTI Line
                DCD     FLASH_IRQHandler               ; FLASH
                DCD     RCC_IRQHandler                 ; RCC
                DCD     EXTI0_1_IRQHandler             ; EXTI Line 0 and 1
                DCD     EXTI2_3_IRQHandler             ; EXTI Line 2 and 3
                DCD     EXTI4_15_IRQHandler            ; EXTI Line 4 to 15
                DCD     UCPD1_2_IRQHandler             ; UCPD1, UCPD2
                DCD     DMA1_Channel1_IRQHandler       ; DMA1 Channel 1
                DCD     DMA1_Channel2_3_IRQHandler     ; DMA1 Channel 2 and Channel 3
                DCD     DMA1_Ch4_7_DMAMUX1_OVR_IRQHandler ; DMA1 Channel 4 to Channel 7, DMAMUX1 overrun
                DCD     ADC1_COMP_IRQHandler           ; ADC1, COMP1 and COMP2 
                DCD     TIM1_BRK_UP_TRG_COM_IRQHandler ; TIM1 Break, Update, Trigger and Commutation
                DCD     TIM1_CC_IRQHandler             ; TIM1 Capture Compare
                DCD     TIM2_IRQHandler                ; TIM2
                DCD     TIM3_IRQHandler                ; TIM3
                DCD     TIM6_DAC_LPTIM1_IRQHandler     ; TIM6, DAC & LPTIM1
                DCD     TIM7_LPTIM2_IRQHandler         ; TIM7 & LPTIM2
                DCD     TIM14_IRQHandler               ; TIM14
                DCD     TIM15_IRQHandler               ; TIM15
                DCD     TIM16_IRQHandler               ; TIM16
                DCD     TIM17_IRQHandler               ; TIM17
                DCD     I2C1_IRQHandler                ; I2C1
                DCD     I2C2_IRQHandler                ; I2C2
                DCD     SPI1_IRQHandler                ; SPI1
                DCD     SPI2_IRQHandler                ; SPI2
                DCD     USART1_IRQHandler              ; USART1
                DCD     USART2_IRQHandler              ; USART2
                DCD     USART3_4_LPUART1_IRQHandler    ; USART3, USART4, LPUART1
                DCD     CEC_IRQHandler                 ; CEC

__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler routine
Reset_Handler    PROC
                 EXPORT  Reset_Handler                 [WEAK]
        IMPORT  __main
        IMPORT  SystemInit  
                 LDR     R0, =SystemInit
                 BLX     R0
                 LDR     R0, =__main
;                 BX      R0


				
;				MOVS R1, #0x00000040 ;Clock control register (RCC_set0)
;				MOVS R3, #12
;				LSLS R1, R3
;				MOVS R3, #0x00000021
;				ADDS R1, R3
;				MOVS R3, #12
;				LSLS R1, R3			;Base address #40021000
;				MOVS R2, #0x00		;Address offset #0x00
;				MOVS R0, #0x0050
;				MOVS R3, #4
;				LSLS R0, R3			;Set value #0x0500
;				STR  R0, [R1,R2]


				MOVS R1, #0x00000040 ;I/O port clock enable register(RCC_IOPENR)
				MOVS R3, #12
				LSLS R1, R3
				MOVS R3, #0x00000021
				ADDS R1, R3
				MOVS R3, #12
				LSLS R1, R3			;Base address #40021000
				MOVS R2, #0x34		;Address offset #0x34
				MOVS R0, #0x01		;Set value #0x01
				STR  R0, [R1,R2]


;				MOVS R1, #0x00000050 ;GPIO port configuration lock regester(GPIO_set0)
;				MOVS R3, #24
;				LSLS R1, R3			;Base address #50000000
;				MOVS R2, #0x1C		;Address offset #0x1C
;				MOVS R0, #0x00		;Set value #0x00
;				STR  R0, [R1,R2]	;success


				MOVS R1, #0x00000050 ;GPIO port mode regester(GPIO_set1)
				MOVS R3, #24
				LSLS R1, R3			;Base address #50000000
				MOVS R2, #0x00		;Address offset #0x00
				MOVS R0, #0xEB
				
				MOVS R3, #8
				LSLS R0, R3	
				MOVS R3, #0xFF
				ADDS R0, R3
				
				MOVS R3, #8
				LSLS R0, R3
				MOVS R3, #0xF7
				ADDS R0, R3
				
				MOVS R3, #8
				LSLS R0, R3
				MOVS R3, #0xFF
				ADDS R0, R3			;Set value #0xEBFFF7FF
				STR  R0, [R1,R2]
				
				
;				MOVS R1, #0x00000050 ;GPIO port output type register(GPIO_set2)
;				MOVS R3, #24
;				LSLS R1, R3			;Base address #50000000
;				MOVS R2, #0x04		;Address offset #0x04
;				MOVS R0, #0x00		;Set value #0x00
;				STR  R0, [R1,R2]
				
				
;				MOVS R1, #0x00000050 ;GPIO port output speed regester(GPIO_set3)
;				MOVS R3, #24
;				LSLS R1, R3			;Base address #50000000
;				MOVS R2, #0x08		;Address offset #0x08
;				MOVS R0, #0x0040
;				MOVS R3, #8
;				LSLS R0, R3			;Set value #0x0400
;				STR  R0, [R1,R2]


;				MOVS R1, #0x00000050 ;GPIO port pull_up/pull_down regester(GPIO_set4)
;				MOVS R3, #24
;				LSLS R1, R3			;Base address #50000000
;				MOVS R2, #0x0C		;Address offset #0x0C
;				MOVS R0, #0x0000	;Set value #0x0000
;				STR  R0, [R1,R2]


LEBEL                                 ;The big cycle,LD4 twinlle


				MOVS R4, #0xFF        ;The number one cycle,LD4 light
				MOVS R3, #8
				LSLS R4, R3
LEBEL1
				MOVS R1, #0x00000050
				MOVS R3, #24
				LSLS R1, R3
				MOVS R2, #0x14
				MOVS R0, #0x20
				STR  R0, [R1,R2]		
				
				
				SUBS R4, #1
				CMP  R4, #1
				BGE LEBEL1


				MOVS R5, #0xFF        ;The number two cycle,LD4 don't light
				MOVS R3, #8
				LSLS R5, R3
LEBEL2
				MOVS R1, #0x00000050
				MOVS R3, #24
				LSLS R1, R3
				MOVS R2, #0x14
				MOVS R0, #0x00
				STR  R0, [R1,R2]
				
				SUBS R5, #1
				CMP  R5, #1
				BGE LEBEL2
				
				B LEBEL

                 ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                    [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler              [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                    [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                 [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WWDG_IRQHandler                [WEAK]
                EXPORT  PVD_IRQHandler                 [WEAK]
                EXPORT  RTC_TAMP_IRQHandler            [WEAK]
                EXPORT  FLASH_IRQHandler               [WEAK]
                EXPORT  RCC_IRQHandler                 [WEAK]
                EXPORT  EXTI0_1_IRQHandler             [WEAK]
                EXPORT  EXTI2_3_IRQHandler             [WEAK]
                EXPORT  EXTI4_15_IRQHandler            [WEAK]
                EXPORT  UCPD1_2_IRQHandler             [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler       [WEAK]
                EXPORT  DMA1_Channel2_3_IRQHandler     [WEAK]
                EXPORT  DMA1_Ch4_7_DMAMUX1_OVR_IRQHandler [WEAK]
                EXPORT  ADC1_COMP_IRQHandler           [WEAK]
                EXPORT  TIM1_BRK_UP_TRG_COM_IRQHandler [WEAK]
                EXPORT  TIM1_CC_IRQHandler             [WEAK]
                EXPORT  TIM2_IRQHandler                [WEAK]
                EXPORT  TIM3_IRQHandler                [WEAK]
                EXPORT  TIM6_DAC_LPTIM1_IRQHandler     [WEAK]
                EXPORT  TIM7_LPTIM2_IRQHandler         [WEAK]
                EXPORT  TIM14_IRQHandler               [WEAK]
                EXPORT  TIM15_IRQHandler               [WEAK]
                EXPORT  TIM16_IRQHandler               [WEAK]
                EXPORT  TIM17_IRQHandler               [WEAK]
                EXPORT  I2C1_IRQHandler                [WEAK]
                EXPORT  I2C2_IRQHandler                [WEAK]
                EXPORT  SPI1_IRQHandler                [WEAK]
                EXPORT  SPI2_IRQHandler                [WEAK]
                EXPORT  USART1_IRQHandler              [WEAK]
                EXPORT  USART2_IRQHandler              [WEAK]
                EXPORT  USART3_4_LPUART1_IRQHandler    [WEAK]
                EXPORT  CEC_IRQHandler                 [WEAK]


WWDG_IRQHandler
PVD_IRQHandler
RTC_TAMP_IRQHandler
FLASH_IRQHandler
RCC_IRQHandler
EXTI0_1_IRQHandler
EXTI2_3_IRQHandler
EXTI4_15_IRQHandler
UCPD1_2_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_3_IRQHandler
DMA1_Ch4_7_DMAMUX1_OVR_IRQHandler
ADC1_COMP_IRQHandler
TIM1_BRK_UP_TRG_COM_IRQHandler
TIM1_CC_IRQHandler
TIM2_IRQHandler
TIM3_IRQHandler
TIM6_DAC_LPTIM1_IRQHandler
TIM7_LPTIM2_IRQHandler
TIM14_IRQHandler
TIM15_IRQHandler
TIM16_IRQHandler
TIM17_IRQHandler
I2C1_IRQHandler
I2C2_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART3_4_LPUART1_IRQHandler
CEC_IRQHandler

                B       .

                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
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


;************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE*****
