#include "main.h"


/* 定义环境模拟电压，模拟电压值单位mV */
#define VDDA_APPLI  ((uint32_t)3300)
  
/* 12位分辨率的满量程数字值，电压范围由模拟电压参考Vref+和Vref-确定。                                       */
#define DIGITAL_SCALE_12BITS  (__LL_DAC_DIGITAL_SCALE(LL_DAC_RESOLUTION_12B))


/* 波形生成:波形参数 */
#define WAVEFORM_AMPLITUDE     (VDDA_APPLI)			  /* 波形振幅(单位mV) */
#define WAVEFORM_FREQUENCY     ((uint32_t)1000)	  /* 波形频率(单位:Hz) */
#define WAVEFORM_SAMPLES_SIZE  (sizeof(WaveformSine_12bits_32samples)/ sizeof(uint16_t)) /* 包含DAC波形样本的阵列大小 */
  
/* 波形产生:定时器参数(用作DAC触发器) */
/*定时器频率(单位:Hz)。与计时器16位和时基频率最小1Hz，范围是最小=1Hz，最大=32kHz。*/
#define WAVEFORM_TIMER_FREQUENCY                (WAVEFORM_FREQUENCY * WAVEFORM_SAMPLES_SIZE)
#define WAVEFORM_TIMER_FREQUENCY_RANGE_MIN      ((uint32_t)    1)			   /* 定时器最小频率(单位:Hz)，用于计算频率范围。 使用16位的定时器，最大频率将是这个值的32000倍。  */
#define WAVEFORM_TIMER_PRESCALER_MAX_VALUE      ((uint32_t)0xFFFF-1)		  /* 定时器预分频器最大值(0xFFFF为一个定时器16位) */



//从数字刻度上的最大值12位(对应于电压Vdda)到新刻度上的值(对应于由WAVEFORM_AMPLITUDE定义的电压)的计算。
#define __WAVEFORM_AMPLITUDE_SCALING(__DATA_12BITS__)                                     \
  (__DATA_12BITS__                                                                        \
   * __LL_DAC_CALC_VOLTAGE_TO_DATA(VDDA_APPLI, WAVEFORM_AMPLITUDE, LL_DAC_RESOLUTION_12B) \
   / __LL_DAC_DIGITAL_SCALE(LL_DAC_RESOLUTION_12B)                                        \
  )

//__IO uint8_t ubButtonPress = 0;  //按键按下的标志位


//存储正弦信号纵坐标
const uint16_t WaveformSine_12bits_32samples[] =
{
__WAVEFORM_AMPLITUDE_SCALING(2048),
__WAVEFORM_AMPLITUDE_SCALING(2447), 
__WAVEFORM_AMPLITUDE_SCALING(2831), 
__WAVEFORM_AMPLITUDE_SCALING(3185), 
__WAVEFORM_AMPLITUDE_SCALING(3495), 
__WAVEFORM_AMPLITUDE_SCALING(3750), 
__WAVEFORM_AMPLITUDE_SCALING(3939), 
__WAVEFORM_AMPLITUDE_SCALING(4056), 
__WAVEFORM_AMPLITUDE_SCALING(4095), 
__WAVEFORM_AMPLITUDE_SCALING(4056),
__WAVEFORM_AMPLITUDE_SCALING(3939),
__WAVEFORM_AMPLITUDE_SCALING(3750),
__WAVEFORM_AMPLITUDE_SCALING(3495),
__WAVEFORM_AMPLITUDE_SCALING(3185),
__WAVEFORM_AMPLITUDE_SCALING(2831),
__WAVEFORM_AMPLITUDE_SCALING(2447),
__WAVEFORM_AMPLITUDE_SCALING(2048),
__WAVEFORM_AMPLITUDE_SCALING(1649),
__WAVEFORM_AMPLITUDE_SCALING(1265),
__WAVEFORM_AMPLITUDE_SCALING(911),
__WAVEFORM_AMPLITUDE_SCALING(601),
__WAVEFORM_AMPLITUDE_SCALING(346),
__WAVEFORM_AMPLITUDE_SCALING(157),
__WAVEFORM_AMPLITUDE_SCALING(40),
__WAVEFORM_AMPLITUDE_SCALING(0),
__WAVEFORM_AMPLITUDE_SCALING(40),
__WAVEFORM_AMPLITUDE_SCALING(157),
__WAVEFORM_AMPLITUDE_SCALING(346),
__WAVEFORM_AMPLITUDE_SCALING(601),
__WAVEFORM_AMPLITUDE_SCALING(911),
__WAVEFORM_AMPLITUDE_SCALING(1265),
__WAVEFORM_AMPLITUDE_SCALING(1649)
};

void     SystemClock_Config(void);
//void     LED_Init(void);
//void     UserButton_Init(void);
//void     WaitForUserButtonPress(void);
//void     LED_Off(void);
void     Configure_DMA(void);
void     Configure_TIM_TimeBase_DAC_trigger(void);
void     Configure_DAC(void);
void     Activate_DAC(void);
//void     LED_On(void);
//void     LED_Blinking(uint32_t Period);

int main(void)
{
  SystemClock_Config();   
  //LED_Init();  
  //UserButton_Init();   				/* 用户按键设置在中断模式 */
  //WaitForUserButtonPress(); 	/* 等待用户按键按下 */
	
  //LED_Off();									/* 关闭LED4灯 */
	
  Configure_DMA();						/* 为从DAC传输数据配置DMA */
  Configure_TIM_TimeBase_DAC_trigger();  /* 配置定时器作为一个时间基准，用于触发DAC转换的启动 */
  Configure_DAC();						/* 配置DAC通道1 */
  Activate_DAC();  						/* 使能DAC通道1 */
	
  //LED_On();  									/* 打开 LED4 */
	
  while (1)
  {
  }
}


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 56000000
  *            HCLK(Hz)                       = 56000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16000000
  *            Flash Latency(WS)              = 2
  *            PLLM                           = 4
  *            PLLN                           = 70
  *            PLLP                           = 10
  *            PLLQ                           = 5
  *            PLLR                           = 5
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  /* HSI configuration and activation */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1) 
  {
  }
  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_4, 70, LL_RCC_PLLR_DIV_5);
  LL_RCC_PLL_Enable();
  LL_RCC_PLL_EnableDomain_SYS();
  while(LL_RCC_PLL_IsReady() != 1) 
  {
  }
  /* Sysclk activation on the main PLL */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) 
  {
  }
  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  /* Set systick to 1ms in using frequency set to 56MHz */
  /* This frequency can be calculated through LL RCC macro */
  /* ex: __LL_RCC_CALC_PLLCLK_FREQ(__LL_RCC_CALC_HSI_FREQ(), 
                                  LL_RCC_PLLM_DIV_4, 70, LL_RCC_PLLR_DIV_5)*/
  LL_Init1msTick(56000000);
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(56000000);
}

/*
void LED_Init(void)
{
  // 使能 LED4 时钟
  LED4_GPIO_CLK_ENABLE();
  // 将IO端口配置在上拉下拉输出模式驱动外部LED4 
  LL_GPIO_SetPinMode(LED4_GPIO_PORT, LED4_PIN, LL_GPIO_MODE_OUTPUT);
  // Reset value is LL_GPIO_OUTPUT_PUSHPULL 
  //LL_GPIO_SetPinOutputType(LED4_GPIO_PORT, LED4_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  // Reset value is LL_GPIO_SPEED_FREQ_LOW 
  //LL_GPIO_SetPinSpeed(LED4_GPIO_PORT, LED4_PIN, LL_GPIO_SPEED_FREQ_LOW);
  // Reset value is LL_GPIO_PULL_NO 
  //LL_GPIO_SetPinPull(LED4_GPIO_PORT, LED4_PIN, LL_GPIO_PULL_NO);
}


void UserButton_Init(void)
{
  // 使能按键时钟 
  USER_BUTTON_GPIO_CLK_ENABLE();
  // 配置按键的GPIO端口 
  LL_GPIO_SetPinMode(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN, LL_GPIO_PULL_NO);
  // 将外部线连接到GIO端口 
  USER_BUTTON_SYSCFG_SET_EXTI();
  // 使能上升沿触发的13号外部中断线 
  USER_BUTTON_EXTI_LINE_ENABLE();
  USER_BUTTON_EXTI_FALLING_TRIG_ENABLE();
  // 给USER_BUTTON_EXTI_IRQn 配置NVIC  
  NVIC_EnableIRQ(USER_BUTTON_EXTI_IRQn); 
  NVIC_SetPriority(USER_BUTTON_EXTI_IRQn,0x03);  
}


void WaitForUserButtonPress(void)
{
  while (ubButtonPress == 0) //按键没有按下时，LED4提示灯闪烁不停
  {
    LL_GPIO_TogglePin(LED4_GPIO_PORT, LED4_PIN);
    LL_mDelay(LED_BLINK_FAST);
  }
  ubButtonPress = 0; //（有按键按下时在中断那里将其置一跳出上边的while），之后清除按键按下标志位
}


void LED_Off(void)
{
  LL_GPIO_ResetOutputPin(LED4_GPIO_PORT, LED4_PIN);
} */


void Configure_DMA(void)
{
  /* 配置NVIC 以使能DMA中断 */
  NVIC_SetPriority(DMA1_Channel2_3_IRQn, 1); /* DMA IRQ优先级低于DAC IRQ */
  NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
  /* 使能送给DMA的外部时钟 */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
  /* 配置DMA传输 */
  /*  - DMA传输在循环模式下有无限的DAC信号产生。  */
  /*  - 直接存储器存取转移到DAC没有地址增量。  	*/
  /*  - 直接存储器存取转移与地址增量。          	*/
  /*  - DMA传输到DAC以半字匹配DAC分辨率12位				*/
  /*  - DMA从存储器通过半字转移到与DAC数据缓冲区匹配的变量类型:半字。  */
  LL_DMA_ConfigTransfer(DMA1,LL_DMA_CHANNEL_3,LL_DMA_DIRECTION_MEMORY_TO_PERIPH | LL_DMA_MODE_CIRCULAR |
                        LL_DMA_PERIPH_NOINCREMENT | LL_DMA_MEMORY_INCREMENT | LL_DMA_PDATAALIGN_HALFWORD |
                        LL_DMA_MDATAALIGN_HALFWORD | LL_DMA_PRIORITY_HIGH );
  /* 选择DAC作为DMA传输请求 */
  LL_DMA_SetPeriphRequest(DMA1,LL_DMA_CHANNEL_3,LL_DMAMUX_REQ_DAC1_CH1);
  /* 设置源和目的的DMA传输地址 */
  LL_DMA_ConfigAddresses(DMA1,LL_DMA_CHANNEL_3,(uint32_t)&WaveformSine_12bits_32samples,LL_DAC_DMA_GetRegAddr(DAC1, LL_DAC_CHANNEL_1,
												LL_DAC_DMA_REG_DATA_12BITS_RIGHT_ALIGNED),LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
  /* 设置DMA传输大小 */
  LL_DMA_SetDataLength(DMA1,LL_DMA_CHANNEL_3,WAVEFORM_SAMPLES_SIZE);
  /* 使能DMA传输中断: 传输错误 */
  LL_DMA_EnableIT_TE(DMA1,LL_DMA_CHANNEL_3);
  /* 注: 在本例中，唯一激活的DMA中断是传输错误。如果需要，DMA中断传输的一半和传输完成可以被激活。参考DMA示例。     */
  /* 启用DMA传输 */
	LL_DMA_EnableChannel(DMA1,LL_DMA_CHANNEL_3);
}


void Configure_TIM_TimeBase_DAC_trigger(void)
{
  uint32_t timer_clock_frequency = 0;             /* 定时器的时钟频率 */
  uint32_t timer_prescaler = 0;                   /* 时基预分频器，使时基按可能的最小频率对齐 */
  uint32_t timer_reload = 0;                      /* 定时器预分频器功能中的定时器重新加载值，以实现时间基准周期 */
  /* 配置NVIC */ 
  /* Note: In this example, timer interruptions are not activated.            */
  /*       If needed, timer interruption at each time base period is          */
  /*       possible.                                                          */
  /*       Refer to timer examples.                                           */
  /* 配置定时器 */
  /* Configuration of timer as time base:                                     */ 
  /* Caution: Computation of frequency is done for a timer instance on APB1   */
  /*          (clocked by PCLK1)                                              */
  /* Timer frequency is configured from the following constants:              */
  /* - WAVEFORM_TIMER_FREQUENCY: timer frequency (unit: Hz).                  */
  /* - WAVEFORM_TIMER_FREQUENCY_RANGE_MIN: timer minimum frequency possible   */
  /*   (unit: Hz).                                                            */
  /* Note: Refer to comments at these literals definition for more details.   */
  /* Retrieve timer clock source frequency */
  /* If APB1 prescaler is different of 1, timers have a factor x2 on their    */
  /* clock source.                                                            */
  if (LL_RCC_GetAPB1Prescaler() == LL_RCC_APB1_DIV_1)
  {
    timer_clock_frequency = __LL_RCC_CALC_PCLK1_FREQ(SystemCoreClock, LL_RCC_GetAPB1Prescaler());
  }
  else
  {
    timer_clock_frequency = (__LL_RCC_CALC_PCLK1_FREQ(SystemCoreClock, LL_RCC_GetAPB1Prescaler()) * 2);
  }
  /* 计时器预分频器计算 */
  /* (computation for timer 16 bits, additional + 1 to round the prescaler up) */
  timer_prescaler = ((timer_clock_frequency / (WAVEFORM_TIMER_PRESCALER_MAX_VALUE * WAVEFORM_TIMER_FREQUENCY_RANGE_MIN)) +1);
  /* 定时器重载计算 */
  timer_reload = (timer_clock_frequency / (timer_prescaler * WAVEFORM_TIMER_FREQUENCY));
  /* 使能定时器外围时钟 */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);
  /* 设置定时器预分频器值 */
  LL_TIM_SetPrescaler(TIM6, (timer_prescaler - 1));
  /* 设置定时器自动重载值 */
  LL_TIM_SetAutoReload(TIM6, (timer_reload - 1));
  /* 设置当前模式 */
  LL_TIM_SetCounterMode(TIM6, LL_TIM_COUNTERMODE_UP); 
  /* 注: 在本例中，计时器中断没有被激活。如果需要，在每个时间基准周期上定时器中断是可能的。 */
  /* 设置定时器触发输出 (TRGO) */
  LL_TIM_SetTriggerOutput(TIM6, LL_TIM_TRGO_UPDATE);
  /* 使能计数器 */
  LL_TIM_EnableCounter(TIM6);
}


void Configure_DAC(void)
{
  /* 使能DAC相关的GPIO时钟*/
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA); 
  /* 将GPIO配置在模拟模式作为DAC的输出端 */
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_ANALOG);
  /* 配置NVIC使能DAC1中断 */
  NVIC_SetPriority(TIM6_DAC_LPTIM1_IRQn, 0);
  NVIC_EnableIRQ(TIM6_DAC_LPTIM1_IRQn);
  /* 使能DAC时钟 */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_DAC1);
  /* 设置模式以DAC通道1 */
  // LL_DAC_SetMode(DAC1, LL_DAC_CHANNEL_1, LL_DAC_MODE_NORMAL_OPERATION);
  /* 选择触发源 */
  LL_DAC_SetTriggerSource(DAC1, LL_DAC_CHANNEL_1, LL_DAC_TRIG_EXT_TIM6_TRGO);
  /* 设置DAC通道1的输出 */
  LL_DAC_ConfigOutput(DAC1, LL_DAC_CHANNEL_1, LL_DAC_OUTPUT_MODE_NORMAL, LL_DAC_OUTPUT_BUFFER_ENABLE, LL_DAC_OUTPUT_CONNECT_GPIO);
  /* Note: DAC channel output configuration can also be done using            */
  /*       LL unitary functions:                                              */
  // LL_DAC_SetOutputMode(DAC1, LL_DAC_CHANNEL_1, LL_DAC_OUTPUT_MODE_NORMAL);
  // LL_DAC_SetOutputBuffer(DAC1, LL_DAC_CHANNEL_1, LL_DAC_OUTPUT_BUFFER_ENABLE);
  // LL_DAC_SetOutputConnection(DAC1, LL_DAC_CHANNEL_1, LL_DAC_OUTPUT_CONNECT_GPIO);
  /* 设置DAC模式采样-保持时间 */
  // LL_DAC_SetSampleAndHoldSampleTime (DAC1, LL_DAC_CHANNEL_1, 0x3FF);
  // LL_DAC_SetSampleAndHoldHoldTime   (DAC1, LL_DAC_CHANNEL_1, 0x3FF);
  // LL_DAC_SetSampleAndHoldRefreshTime(DAC1, LL_DAC_CHANNEL_1, 0xFF);
  /* 启用DAC通道DMA请求 */
  LL_DAC_EnableDMAReq(DAC1, LL_DAC_CHANNEL_1);
  /* 使能DAC通道一中断 */
  LL_DAC_EnableIT_DMAUDR1(DAC1);
}


void Activate_DAC(void)
{
  __IO uint32_t wait_loop_index = 0;
  /* 使能DAC通道1 */
  LL_DAC_Enable(DAC1, LL_DAC_CHANNEL_1);
  /* Delay for DAC channel voltage settling time from DAC channel startup.    */
  /* Compute number of CPU cycles to wait for, from delay in us.              */
  /* Note: Variable divided by 2 to compensate partially                      */
  /*       CPU processing cycles (depends on compilation optimization).       */
  /* Note: If system core clock frequency is below 200kHz, wait time          */
  /*       is only a few CPU processing cycles.                               */
  wait_loop_index = ((LL_DAC_DELAY_STARTUP_VOLTAGE_SETTLING_US * (SystemCoreClock / (100000 * 2))) / 10);
  while(wait_loop_index != 0)
  {
    wait_loop_index--;
  }
  /* Enable DAC channel trigger */
  /* Note: DAC channel conversion can start from trigger enable:              */
  /*       - if DAC channel trigger source is set to SW:                      */
  /*         DAC channel conversion will start after trig order               */
  /*         using function "LL_DAC_TrigSWConversion()".                      */
  /*       - if DAC channel trigger source is set to external trigger         */
  /*         (timer, ...):                                                    */
  /*         DAC channel conversion can start immediately                     */
  /*         (after next trig order from external trigger)                    */
  LL_DAC_EnableTrigger(DAC1, LL_DAC_CHANNEL_1);
}

/*
void LED_On(void)
{
  LL_GPIO_SetOutputPin(LED4_GPIO_PORT, LED4_PIN);
}


void LED_Blinking(uint32_t Period)
{
  LL_GPIO_SetOutputPin(LED4_GPIO_PORT, LED4_PIN);
  while (1)
  {
    LL_GPIO_TogglePin(LED4_GPIO_PORT, LED4_PIN);  
    LL_mDelay(Period);
  }
}*/ 

//******************************************************************中断回调函数

void UserButton_Callback(void)
{
  //if(ubButtonPress == 0)	//按键按下触发此中断
  //  ubButtonPress = 1;		//并将按键标志置拉高代表按键已经按下
}

void DacDmaTransferError_Callback()
{
  //LED_Blinking(LED_BLINK_ERROR);
}

void DacUnderrunError_Callback(void)
{
  // 注意:在进入下面的无限循环之前，禁用导致此错误的DAC中断。 
  // 关闭中断DAC channel1 underrun 
  //LL_DAC_DisableIT_DMAUDR1(DAC1);
  //LED_Blinking(LED_BLINK_ERROR);
} 

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


