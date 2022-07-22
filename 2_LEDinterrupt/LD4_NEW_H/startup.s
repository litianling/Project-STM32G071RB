
Stack_Size		EQU     0x400  ;EQR相当于C中的define

                AREA    STACK, NOINIT, READWRITE, ALIGN=3 ;AREA汇编一个新的代码段数据段
Stack_Mem       SPACE   Stack_Size ;SPACE分配内存空间
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size      EQU     0x200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

				PRESERVE8 ;当前文件堆栈需按照8字节对齐
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors ;EXPORT声明一个标号具有全局性，可被外部文件引用
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                   ; Top of Stack  DCD以字为单位分配内存
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
                DCD     EXTI4_15_IRQHandler            ; EXTI Line 4 to 15 中断向量表定义中断

__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler routine
Reset_Handler    PROC
                 EXPORT  Reset_Handler                 [WEAK]


				;RCC.IOPENR initialize
				LDR  R1, =0x40021000;Base address #4002 1000
				MOVS R2, #0x34		;Address offset #0x34
				MOVS R0, #0x05		;Set value #0x0000 0005
				STR  R0, [R1,R2]
				
				;GOIOC.MODER initialize
				LDR  R1, =0x50000800;Base address #5000 0800
				MOVS R2, #0x00		;Address offset #0x00
				LDR  R0, =0xF3FFFFFF;Set value #0xF3FF FFFF
				STR  R0, [R1,R2]
				
				;EXTI.EXTICR4 initialize
				LDR  R1, =0x40021800;Base address #4002 1800
				MOVS R2, #0x6C		 ;Address offset #0x6C
				LDR  R0, =0x00000200;Set value #0x0000 0200
				STR  R0, [R1,R2]
				
				
				;EXTI.IMR1 initialize
				;Base address #4002 1800,don't need to modify it
				MOVS R2, #0x80		;Address offset #0x80
				LDR  R0, =0xFFF82000;Set value #0xFFF8 2000
				STR  R0, [R1,R2]


				;EXTI.EMR1 initialize
				;Base address #4002 1800,don't need to modify it
				MOVS R2, #0x84		;Address offset #0x84
				;Set value #0xFFF8 2000,don't need to modify it
				STR  R0, [R1,R2]
				
				
				;EXTI.FTSR1 initialize
				;Base address #4002 1800,don't need to modify it
				MOVS R2, #0x04		;Address offset #0x04
				LDR  R0, =0x00002000;Set value #0x0000 2000
				STR  R0, [R1,R2]
				
				
				;GPIOA.MODER initialize
				LDR  R1, =0x50000000 ;Base address #50000000
				MOVS R2, #0x00		 ;Address offset #0x00
				LDR  R0, =0xEBFFF7FF;Set value #0xEBFFF7FF
				STR  R0, [R1,R2]
				
				
				;NVIC.ISER initialize
				LDR  R1, =0xE000E100
				MOVS R2, #0x00
				MOVS R0, #0x80
				STR  R0, [R1,R2]
				
				
				LDR  R1, =0x50000000 ;light
				MOVS R2, #0x14
				MOVS R0, #0x20
				STR  R0,[R1,R2]

LEBEL5				
				B    LEBEL5

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


  
WWDG_IRQHandler PROC
                EXPORT  WWDG_IRQHandler                [WEAK]
                B       .
                ENDP
PVD_IRQHandler PROC
                EXPORT  PVD_IRQHandler                [WEAK]
                B       .
                ENDP
RTC_TAMP_IRQHandler PROC
                EXPORT  RTC_TAMP_IRQHandler                [WEAK]
                B       .
                ENDP
FLASH_IRQHandler PROC
                EXPORT  FLASH_IRQHandler                [WEAK]
                B       .
                ENDP
RCC_IRQHandler PROC
                EXPORT  RCC_IRQHandler                [WEAK]
                B       .
                ENDP
EXTI0_1_IRQHandler PROC
                EXPORT  EXTI0_1_IRQHandler                [WEAK]
                B       .
                ENDP
EXTI2_3_IRQHandler PROC
                EXPORT  EXTI2_3_IRQHandler                [WEAK]
                B       .
                ENDP		
					
EXTI4_15_IRQHandler PROC
                EXPORT  EXTI4_15_IRQHandler                [WEAK]
				;PUSH {LR}
				
				;清除中断标志位————写一清零
				LDR  R1, =0x40021800;Base address #4002 1800
				MOVS R2, #0x010		 ;Address offset #0x6C
				LDR  R0, =0x00002000;Set value #0x0000 2000
				STR  R0, [R1,R2]
				
				
				LDR  R1, =0x50000000
				MOVS R2, #0x14
				LDR  R0, [R1,R2] ;GPIOA.ODR
				CMP  R0, #0x20
				BEQ  LEBEL1      ;如果亮跳转到LEBEL1 
				
				
				MOVS R0, #0x20	 ;不亮则变亮
				STR  R0, [R1,R2]
				B    LEBEL       ;跳出中断
LEBEL1
				MOVS R0,#0x00	 ;变灭
				STR  R0, [R1,R2]			
LEBEL
				;POP  {PC}
                ENDP						
					
                ALIGN ;ALIGN四字节对齐

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
