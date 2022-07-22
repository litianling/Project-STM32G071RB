#include "main.h"
#include "stm32g0xx_it.h"

void NMI_Handler(void)
{
  while (1)
  {
  }
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
}


void EXTI4_15_IRQHandler(void)
{
  if (LL_EXTI_IsActiveRisingFlag_0_31(LL_EXTI_LINE_13) != RESET)
  {
    LL_EXTI_ClearRisingFlag_0_31(LL_EXTI_LINE_13);
		USER_Interrupt_CallBack();
  }
}

void DMA1_Channel1_IRQHandler(void)
{
}

void DMA1_Channel2_3_IRQHandler(void)
{
}
