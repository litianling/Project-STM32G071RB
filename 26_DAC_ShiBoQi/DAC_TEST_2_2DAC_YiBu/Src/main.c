#include "main.h"

//#define CIRCLE //图形选择，注释掉此行，输出即为正方形
#define MOVE 0 //定义为0静态图像，定义为1动态图像

#define VDDA_APPLI  ((uint32_t)3300)			/* 定义环境模拟电压，模拟电压值单位mV */
#define DIGITAL_SCALE_12BITS  (__LL_DAC_DIGITAL_SCALE(LL_DAC_RESOLUTION_12B))		/* 12位分辨率的满量程数字值，电压范围由模拟电压参考Vref+和Vref-确定。 */

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

#ifdef CIRCLE
//存储正弦信号（作为圆的纵坐标）
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

//存储正弦信号（作为圆的横坐标）  数组顺序控制90°相位差
const uint16_t WaveformSine_12bits_32samples1[] =  
{
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
__WAVEFORM_AMPLITUDE_SCALING(1649),

__WAVEFORM_AMPLITUDE_SCALING(2048),
__WAVEFORM_AMPLITUDE_SCALING(2447), 
__WAVEFORM_AMPLITUDE_SCALING(2831), 
__WAVEFORM_AMPLITUDE_SCALING(3185), 
__WAVEFORM_AMPLITUDE_SCALING(3495), 
__WAVEFORM_AMPLITUDE_SCALING(3750), 
__WAVEFORM_AMPLITUDE_SCALING(3939), 
__WAVEFORM_AMPLITUDE_SCALING(4056)
};

#else

//0-3500 间隔500绘制正方形
const uint16_t WaveformSine_12bits_32samples[] =
{	
__WAVEFORM_AMPLITUDE_SCALING(0), 
__WAVEFORM_AMPLITUDE_SCALING(500),
__WAVEFORM_AMPLITUDE_SCALING(1000),
__WAVEFORM_AMPLITUDE_SCALING(1500),
__WAVEFORM_AMPLITUDE_SCALING(2000),
__WAVEFORM_AMPLITUDE_SCALING(2500),
__WAVEFORM_AMPLITUDE_SCALING(3000),
__WAVEFORM_AMPLITUDE_SCALING(3500),
	
__WAVEFORM_AMPLITUDE_SCALING(3500),
__WAVEFORM_AMPLITUDE_SCALING(3500),
__WAVEFORM_AMPLITUDE_SCALING(3500),
__WAVEFORM_AMPLITUDE_SCALING(3500),
__WAVEFORM_AMPLITUDE_SCALING(3500),
__WAVEFORM_AMPLITUDE_SCALING(3500),
__WAVEFORM_AMPLITUDE_SCALING(3500),
__WAVEFORM_AMPLITUDE_SCALING(3500),

__WAVEFORM_AMPLITUDE_SCALING(3500),
__WAVEFORM_AMPLITUDE_SCALING(3000),
__WAVEFORM_AMPLITUDE_SCALING(2500),
__WAVEFORM_AMPLITUDE_SCALING(2000),
__WAVEFORM_AMPLITUDE_SCALING(1500),
__WAVEFORM_AMPLITUDE_SCALING(1000),
__WAVEFORM_AMPLITUDE_SCALING(500),
__WAVEFORM_AMPLITUDE_SCALING(0), 

__WAVEFORM_AMPLITUDE_SCALING(0),
__WAVEFORM_AMPLITUDE_SCALING(0), 
__WAVEFORM_AMPLITUDE_SCALING(0), 
__WAVEFORM_AMPLITUDE_SCALING(0), 
__WAVEFORM_AMPLITUDE_SCALING(0), 
__WAVEFORM_AMPLITUDE_SCALING(0), 
__WAVEFORM_AMPLITUDE_SCALING(0),
__WAVEFORM_AMPLITUDE_SCALING(0)
};

const uint16_t WaveformSine_12bits_32samples1[] =  
{
__WAVEFORM_AMPLITUDE_SCALING(0),
__WAVEFORM_AMPLITUDE_SCALING(0), 
__WAVEFORM_AMPLITUDE_SCALING(0), 
__WAVEFORM_AMPLITUDE_SCALING(0), 
__WAVEFORM_AMPLITUDE_SCALING(0), 
__WAVEFORM_AMPLITUDE_SCALING(0), 
__WAVEFORM_AMPLITUDE_SCALING(0),
__WAVEFORM_AMPLITUDE_SCALING(0),
	
__WAVEFORM_AMPLITUDE_SCALING(0), 
__WAVEFORM_AMPLITUDE_SCALING(500),
__WAVEFORM_AMPLITUDE_SCALING(1000),
__WAVEFORM_AMPLITUDE_SCALING(1500),
__WAVEFORM_AMPLITUDE_SCALING(2000),
__WAVEFORM_AMPLITUDE_SCALING(2500),
__WAVEFORM_AMPLITUDE_SCALING(3000),
__WAVEFORM_AMPLITUDE_SCALING(3500),
	
__WAVEFORM_AMPLITUDE_SCALING(3500),
__WAVEFORM_AMPLITUDE_SCALING(3500),
__WAVEFORM_AMPLITUDE_SCALING(3500),
__WAVEFORM_AMPLITUDE_SCALING(3500),
__WAVEFORM_AMPLITUDE_SCALING(3500),
__WAVEFORM_AMPLITUDE_SCALING(3500),
__WAVEFORM_AMPLITUDE_SCALING(3500),
__WAVEFORM_AMPLITUDE_SCALING(3500),
	
__WAVEFORM_AMPLITUDE_SCALING(3500),
__WAVEFORM_AMPLITUDE_SCALING(3000),
__WAVEFORM_AMPLITUDE_SCALING(2500),
__WAVEFORM_AMPLITUDE_SCALING(2000),
__WAVEFORM_AMPLITUDE_SCALING(1500),
__WAVEFORM_AMPLITUDE_SCALING(1000),
__WAVEFORM_AMPLITUDE_SCALING(500),
__WAVEFORM_AMPLITUDE_SCALING(0)
};

#endif


void     SystemClock_Config(void);
void     Configure_DMA(void);
void     Configure_TIM_TimeBase_DAC_trigger(void);
void     Configure_DAC(void);
void     Activate_DAC(void);

int main(void)
{
  SystemClock_Config();   
  Configure_DMA();						/* 为从DAC传输数据配置DMA */
  Configure_TIM_TimeBase_DAC_trigger();  /* 配置定时器作为一个时间基准，用于触发DAC转换的启动 */
  Configure_DAC();						/* 配置DAC通道1 */
  Activate_DAC();  						/* 使能DAC通道1 */
  while (1)
  {
  }
}


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


void Configure_DMA(void)
{
  /* 配置NVIC 以使能DMA中断 */
	NVIC_SetPriority(DMA1_Channel1_IRQn,2); /* DMA IRQ优先级低于DAC IRQ */
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  NVIC_SetPriority(DMA1_Channel2_3_IRQn,3); /* DMA IRQ优先级低于DAC IRQ */
  NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
	
  /* 使能送给DMA的外部时钟 */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
  /* 配置DMA传输 */
  /*  - DMA传输在循环模式下有无限的DAC信号产生。  */
  /*  - 直接存储器存取转移到DAC没有地址增量。  	*/
  /*  - 直接存储器存取转移与地址增量。          	*/
  /*  - DMA传输到DAC以半字匹配DAC分辨率12位				*/
  /*  - DMA从存储器通过半字转移到与DAC数据缓冲区匹配的变量类型:半字。  */
  LL_DMA_ConfigTransfer(DMA1,LL_DMA_CHANNEL_1,LL_DMA_DIRECTION_MEMORY_TO_PERIPH | LL_DMA_MODE_CIRCULAR |
                        LL_DMA_PERIPH_NOINCREMENT | LL_DMA_MEMORY_INCREMENT | LL_DMA_PDATAALIGN_HALFWORD |
                        LL_DMA_MDATAALIGN_HALFWORD | LL_DMA_PRIORITY_HIGH );
	LL_DMA_ConfigTransfer(DMA1,LL_DMA_CHANNEL_2,LL_DMA_DIRECTION_MEMORY_TO_PERIPH | LL_DMA_MODE_CIRCULAR |
                        LL_DMA_PERIPH_NOINCREMENT | LL_DMA_MEMORY_INCREMENT | LL_DMA_PDATAALIGN_HALFWORD |
                        LL_DMA_MDATAALIGN_HALFWORD | LL_DMA_PRIORITY_HIGH );
	
  /* 选择DAC作为DMA传输请求 */
  LL_DMA_SetPeriphRequest(DMA1,LL_DMA_CHANNEL_1,LL_DMAMUX_REQ_DAC1_CH1);
	LL_DMA_SetPeriphRequest(DMA1,LL_DMA_CHANNEL_2,LL_DMAMUX_REQ_DAC1_CH2);
	
  /* 设置源和目的的DMA传输地址 */
  LL_DMA_ConfigAddresses(DMA1,LL_DMA_CHANNEL_1,(uint32_t)&WaveformSine_12bits_32samples,LL_DAC_DMA_GetRegAddr(DAC1, LL_DAC_CHANNEL_1,
												LL_DAC_DMA_REG_DATA_12BITS_RIGHT_ALIGNED),LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_ConfigAddresses(DMA1,LL_DMA_CHANNEL_2,(uint32_t)&WaveformSine_12bits_32samples1,LL_DAC_DMA_GetRegAddr(DAC1, LL_DAC_CHANNEL_2,
												LL_DAC_DMA_REG_DATA_12BITS_RIGHT_ALIGNED),LL_DMA_DIRECTION_MEMORY_TO_PERIPH);

  /* 设置DMA传输大小 */
  LL_DMA_SetDataLength(DMA1,LL_DMA_CHANNEL_1,WAVEFORM_SAMPLES_SIZE);
  LL_DMA_SetDataLength(DMA1,LL_DMA_CHANNEL_2,WAVEFORM_SAMPLES_SIZE);
	
  /* 使能DMA传输中断: 传输错误 */
  LL_DMA_EnableIT_TE(DMA1,LL_DMA_CHANNEL_1);
	LL_DMA_EnableIT_TE(DMA1,LL_DMA_CHANNEL_2);
	
  /* 注: 在本例中，唯一激活的DMA中断是传输错误。如果需要，DMA中断传输的一半和传输完成可以被激活。参考DMA示例。     */
  /* 启用DMA传输 */
	LL_DMA_EnableChannel(DMA1,LL_DMA_CHANNEL_1);
	LL_DMA_EnableChannel(DMA1,LL_DMA_CHANNEL_2);
}


//动态显示
void Configure_TIM_TimeBase_DAC_trigger(void)
{
  uint32_t timer_clock_frequency = 0;             /* 定时器的时钟频率 */
  uint32_t timer_prescaler = 0;                   /* 时基预分频器，使时基按可能的最小频率对齐 */
  uint32_t timer_reload = 0;                      /* 定时器预分频器功能中的定时器重新加载值，以实现时间基准周期 */
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
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);
  /* 设置定时器预分频器值 */
  LL_TIM_SetPrescaler(TIM6, (timer_prescaler - 1));
	LL_TIM_SetPrescaler(TIM7, (timer_prescaler - 1)+MOVE);//频率差造成动态图像
  /* 设置定时器自动重载值 */
  LL_TIM_SetAutoReload(TIM6, (timer_reload - 1));
  LL_TIM_SetAutoReload(TIM7, (timer_reload - 1));
  /* 设置当前模式 */
  LL_TIM_SetCounterMode(TIM6, LL_TIM_COUNTERMODE_UP);
  LL_TIM_SetCounterMode(TIM7, LL_TIM_COUNTERMODE_UP);	
  /* 注: 在本例中，计时器中断没有被激活。如果需要，在每个时间基准周期上定时器中断是可能的。 */
  /* 设置定时器触发输出 (TRGO) */
  LL_TIM_SetTriggerOutput(TIM6, LL_TIM_TRGO_UPDATE);
  LL_TIM_SetTriggerOutput(TIM7, LL_TIM_TRGO_UPDATE);
  /* 使能计数器 */
  LL_TIM_EnableCounter(TIM6);
  LL_TIM_EnableCounter(TIM7);
}


void Configure_DAC(void)
{
  /* 使能DAC相关的GPIO时钟*/
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA); 
  /* 将GPIO配置在模拟模式作为DAC的输出端 */
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_ANALOG);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_ANALOG);
  /* 配置NVIC使能DAC1中断 */
  NVIC_SetPriority(TIM6_DAC_LPTIM1_IRQn, 0);
  NVIC_EnableIRQ(TIM6_DAC_LPTIM1_IRQn);
  NVIC_SetPriority(TIM7_LPTIM2_IRQn, 1);
  NVIC_EnableIRQ(TIM7_LPTIM2_IRQn);
  /* 使能DAC时钟 */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_DAC1);
  /* 选择触发源 */
  LL_DAC_SetTriggerSource(DAC1, LL_DAC_CHANNEL_1, LL_DAC_TRIG_EXT_TIM6_TRGO);
	LL_DAC_SetTriggerSource(DAC1, LL_DAC_CHANNEL_2, LL_DAC_TRIG_EXT_TIM7_TRGO);
  /* 设置DAC通道1的输出 */
  LL_DAC_ConfigOutput(DAC1, LL_DAC_CHANNEL_1, LL_DAC_OUTPUT_MODE_NORMAL, LL_DAC_OUTPUT_BUFFER_ENABLE, LL_DAC_OUTPUT_CONNECT_GPIO);
	LL_DAC_ConfigOutput(DAC1, LL_DAC_CHANNEL_2, LL_DAC_OUTPUT_MODE_NORMAL, LL_DAC_OUTPUT_BUFFER_ENABLE, LL_DAC_OUTPUT_CONNECT_GPIO);
  /* 启用DAC通道DMA请求 */
  LL_DAC_EnableDMAReq(DAC1, LL_DAC_CHANNEL_1);
	LL_DAC_EnableDMAReq(DAC1, LL_DAC_CHANNEL_2);
  /* 使能DAC通道一中断 */
  LL_DAC_EnableIT_DMAUDR1(DAC1);
}


void Activate_DAC(void)
{
  __IO uint32_t wait_loop_index = 0;
  /* 使能DAC通道1 */
  LL_DAC_Enable(DAC1, LL_DAC_CHANNEL_1);
	LL_DAC_Enable(DAC1, LL_DAC_CHANNEL_2);
	
  wait_loop_index = ((LL_DAC_DELAY_STARTUP_VOLTAGE_SETTLING_US * (SystemCoreClock / (100000 * 2))) / 10);
  while(wait_loop_index != 0)
  {
    wait_loop_index--;
  }
  LL_DAC_EnableTrigger(DAC1, LL_DAC_CHANNEL_1);
	LL_DAC_EnableTrigger(DAC1, LL_DAC_CHANNEL_2);
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


