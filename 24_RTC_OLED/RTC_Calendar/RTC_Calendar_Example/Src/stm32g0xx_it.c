#include "main.h"
#include "stm32g0xx_it.h"


/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/

void NMI_Handler(void)
{

}


void HardFault_Handler(void)
{
  
  while (1)
  {
    
  }
}


void SysTick_Handler(void)
{
  
  HAL_IncTick();
  
}

