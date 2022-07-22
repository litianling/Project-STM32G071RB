#include "main.h"
#include "stdio.h"
#include "string.h"

//MODE大抗干扰强，MODE小传输速率高  要求大于等于6（否则出现误码）
//当前配置下，发射端MODE值必须是接收端MODE值的二分之一
#define MODE 10
#define unit8_t unsigned char
#define PUTCHAR_PROTOTYPE int fputc(int ch,FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#define BACKSPACE_PROTOTYPE int _backspace(FILE *f)


unsigned char Char_Out[10][10]=
{
	' ', ' ', '!', '"', '#', '$', '%', '&', ' ', '(',
	')', '*', '+', ',', '-', '.', '/', '0', '1', '2',
	'3', '4', '5', '6', '7', '8', '9', ':', ';', '<',
	'=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F',
	'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',

	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
  '[', '\ ', ']', '^', ' ', '、', 'a', 'b', 'c', 'd',	//92反斜留空隙     96顿号   
 	'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
	'y', 'z', '{', '|', '}', '~', ' ', ' ', ' ', ' ' 	
};
volatile int  High_number=0;		//脉冲数量
volatile int Transfer_Data=0;		//传输数据
volatile int Output_Y=0;				//解码矩阵坐标
volatile int Output_X=0;				//
int  Flag_TIM2=0; 							//定时器2通道1标志位  1打开0关闭  增加计数的准确性
int	 Flag_Transfer=1;						//传输标志，判断传输十位（1）传输个位（0）

UART_HandleTypeDef hlpuart1;
TIM_HandleTypeDef htim2;


void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_LPUART1_UART_Init(void);
static void MX_TIM2_Init(void);


int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_LPUART1_UART_Init();
  MX_TIM2_Init();
	printf("开始接收 \r\n");
  while (1)
  {
		HAL_Delay(10);
  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_LPUART1_UART_Init(void)
{
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 112500;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  hlpuart1.FifoMode = UART_FIFOMODE_DISABLE;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_TIM2_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 1023;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 375*MODE;//3750;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 375*MODE/2;//1875;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_TIM_MspPostInit(&htim2);
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
}



PUTCHAR_PROTOTYPE	//重定向 fputc()函数
{
	HAL_UART_Transmit(&hlpuart1,(unit8_t*) &ch,1,0xFFFF);  //调用串口发送函数
	return ch;		//返回发送的字符
}


GETCHAR_PROTOTYPE //重定向 fgetc()函数 
{ 
	uint8_t value; //定义无符号字符型变量 value 
	while((LPUART1->ISR & 0x00000020)==0){} //判断串口是否接收到字符 
	value=(uint8_t)LPUART1->RDR; //读取串口接收到的字符 
	HAL_UART_Transmit(&hlpuart1,(uint8_t *)&value,1,0x1000); //回显接收到的字符 
	return value; //返回接收到的值 value 
}

BACKSPACE_PROTOTYPE //重定向__backspace 函数 
{ 
	return 0; 
}


void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==0x0010) //PC4 定时器-----输出+清零
	{
		//计时结束关闭定时器2通道1
		HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
		Flag_TIM2=0;
		Transfer_Data=(High_number-MODE/2)/MODE;	//解码公式
		if(Transfer_Data!=0)	//传输数据是不可能等于0的（防止误触发）
		{
			if(Flag_Transfer==1)	//传输的是十位
			{
				Output_Y=Transfer_Data-1;	//接收数据1-10返回0-9
				Flag_Transfer=0;		//转变传输标志位准备接收个位
			}
			else									//传输的是个位
			{
				Output_X=Transfer_Data-1;									//个位也传输完毕
				printf("%c",Char_Out[Output_Y][Output_X]);//输出对应字符
				Output_Y=0;Output_X=0;										//清除输出寻址
				Flag_Transfer=1;		//转变传输标志位准备接收下一个十位
			}
			Transfer_Data=0;			//数据用完了及时清零——防止误触发
		}
		High_number=0;					//清除脉冲计数
	}
	
	else if(GPIO_Pin==0x0020) //PC5 中断来临  如果定时器关闭则将其打开  并计数
	{
		if(Flag_TIM2==0)
		{
			HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
			Flag_TIM2=1;
		}
		High_number++;
	}
	
	else ;
}


void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
