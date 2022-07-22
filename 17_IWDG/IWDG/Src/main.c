#include "main.h"

static volatile uint8_t ubKeyPressed = 0;  //volatile关键字，即可被未知因素更改   外部复位按键标志位初始为0没复位请求

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_IWDG_Init(void);

void     Check_IWDG_Reset(void);  //检测独立看门狗复位
void     LED_On(void);						//LD4灯状态

int main(void)
{

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);		//APB总线————系统时钟使能
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);			//APB总线————PWR时钟使能

  LL_SYSCFG_DisableDBATT(LL_SYSCFG_UCPD1_STROBE | LL_SYSCFG_UCPD2_STROBE);

  SystemClock_Config();	//系统时钟初始化
  MX_GPIO_Init();		//GPIO初始化
  MX_IWDG_Init();		//看门狗初始化
	Check_IWDG_Reset();		//检测独立看门狗复位
  while (1)
  {
		if (1 != ubKeyPressed)  //没有外部复位请求则→
    {
      LL_IWDG_ReloadCounter(IWDG);		//重新加载看门狗向下计数器（更新）————喂狗
      
      LL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin); //LD4状态反转——闪烁
      LL_mDelay(200);	//延时
    }
  }
}


void SystemClock_Config(void)
{
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  }

  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(16000000);
  LL_SetSystemCoreClock(16000000);
}

static void MX_IWDG_Init(void)
{

  LL_IWDG_Enable(IWDG);
  LL_IWDG_EnableWriteAccess(IWDG);
  LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_4);
  LL_IWDG_SetReloadCounter(IWDG, 4078);
  while (LL_IWDG_IsReady(IWDG) != 1)
  {
  }

  LL_IWDG_ReloadCounter(IWDG);
}

static void MX_GPIO_Init(void)
{
  LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  LL_GPIO_ResetOutputPin(LED4_GPIO_Port, LED4_Pin);

  LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTC, LL_EXTI_CONFIG_LINE13);

  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_13;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;
  LL_EXTI_Init(&EXTI_InitStruct);

  LL_GPIO_SetPinPull(USER_BUTTON_GPIO_Port, USER_BUTTON_Pin, LL_GPIO_PULL_UP);

  LL_GPIO_SetPinMode(USER_BUTTON_GPIO_Port, USER_BUTTON_Pin, LL_GPIO_MODE_INPUT);

  GPIO_InitStruct.Pin = LED4_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED4_GPIO_Port, &GPIO_InitStruct);

  NVIC_SetPriority(EXTI4_15_IRQn, 0);
  NVIC_EnableIRQ(EXTI4_15_IRQn);

}

void Check_IWDG_Reset(void) 
{
  if (LL_RCC_IsActiveFlag_IWDGRST()) //如果RCC时钟计数到了预设的复位值
  {
    LL_RCC_ClearResetFlags(); //清除RCC复位标志

    LED_On(); //让LD4灯点亮
    
    while(ubKeyPressed != 1)  //外部复位按键标志位是0，即没有复位请求，则LD4常亮
    {
    }

    ubKeyPressed = 0;		//清空外部复位按键标志位
  }
}

void LED_On(void)
{
  LL_GPIO_SetOutputPin(LED4_GPIO_Port, LED4_Pin);	//点亮LD4
}

void UserButton_Callback(void)  //中断回调函数，生成外部中断复位请求
{
  ubKeyPressed = 1;
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif 
