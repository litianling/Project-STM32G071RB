#include "stm32g0xx_it.h"

void NMI_Handler(void)
{
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

void USER_BUTTON_IRQHANDLER(void)
{
  if(LL_EXTI_IsActiveFallingFlag_0_31(USER_BUTTON_EXTI_LINE) != RESET)
  {
    UserButton_Callback();
    LL_EXTI_ClearFallingFlag_0_31(USER_BUTTON_EXTI_LINE);
  }
}

void TIM6_DAC_LPTIM1_IRQHandler(void)
{
  if(LL_DAC_IsActiveFlag_DMAUDR1(DAC1) != 0)
  {
    LL_DAC_ClearFlag_DMAUDR1(DAC1);
    DacUnderrunError_Callback();
  }
}

void DMA1_Channel2_3_IRQHandler(void)
{
  if(LL_DMA_IsActiveFlag_TE3(DMA1) == 1)
  {
    LL_DMA_ClearFlag_TE3(DMA1);
    DacDmaTransferError_Callback();
  }
}