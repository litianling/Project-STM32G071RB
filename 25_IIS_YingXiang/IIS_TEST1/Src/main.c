#include "main.h"
I2C_HandleTypeDef hi2c1;
I2S_HandleTypeDef hi2s1;
DMA_HandleTypeDef hdma_spi1_tx;
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2S1_Init(void);
static void MX_I2C1_Init(void);


#include "wave_data.h"
#define WM8960_ADDRESS  0x1A
#define AUIDO_START_ADDRESS       58 /* 相对于音频文件头大小的偏移量 */
#define DMA_MAX(x)      (((x) <= 0xFFFF)? (x):0xFFFF)
//寄存器值
static uint16_t WM8960_REG_VAL[56] =
{  
  0x0097, 0x0097, 0x0000, 0x0000, 0x0000, 0x0008, 0x0000, 0x000A,
  0x01C0, 0x0000, 0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x007B, 0x0100, 0x0032, 0x0000, 0x00C3, 0x00C3, 0x01C0,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0100, 0x0100, 0x0050, 0x0050, 0x0050, 0x0050, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0040, 0x0000, 0x0000, 0x0050, 0x0050, 0x0000,
  0x0000, 0x0037, 0x004D, 0x0080, 0x0008, 0x0031, 0x0026, 0x00ED
};


//extern uint32_t AudioRemSize;   /* 此变量保存音频文件中的剩余数据 */
//extern uint16_t *CurrentPos;    /* 此变量保存音频指针的当前位置 */
uint32_t AudioTotalSize;  			/* 这个变量保存音频文件的总大小 */
uint32_t AudioRemSize;    			/* 此变量保存音频文件中的剩余数据 */
uint16_t *CurrentPos;     			/* 此变量保存音频指针的当前位置 */
uint32_t WaveDataLength=0;
uint8_t XferCplt;

uint8_t WM8960_Write_Reg(uint8_t reg, uint16_t dat);
uint8_t WM89060_Init(void);
uint32_t AudioFlashPlay(uint16_t* pBuffer, uint32_t FullSize, uint32_t StartAdd); //缓存区


int main(void)
{
	uint8_t res=1;
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2S1_Init();
  MX_I2C1_Init();
	
  res = WM89060_Init();
  if(res == 0)
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1); //  WM89060模块初始化成功，之后有杂音
  else
    while(1)
		{
			HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5); // WM89060模块初始化失败
      HAL_Delay(1000);
    }
  WaveDataLength = sizeof(WaveData) - AUIDO_START_ADDRESS; //计算音频数据长度 = 总长度 - 开头
  while (1)
  {
    XferCplt = 0;
    AudioFlashPlay((uint16_t*)(WaveData + AUIDO_START_ADDRESS),WaveDataLength,AUIDO_START_ADDRESS);
//    while(XferCplt != 1)
//      HAL_Delay(10);
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 70;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV10;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV5;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x10606DA4;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2S1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2S1_Init(void)
{

  /* USER CODE BEGIN I2S1_Init 0 */

  /* USER CODE END I2S1_Init 0 */

  /* USER CODE BEGIN I2S1_Init 1 */

  /* USER CODE END I2S1_Init 1 */
  hi2s1.Instance = SPI1;
  hi2s1.Init.Mode = I2S_MODE_MASTER_TX;
  hi2s1.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s1.Init.DataFormat = I2S_DATAFORMAT_16B;
  hi2s1.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
  hi2s1.Init.AudioFreq = I2S_AUDIOFREQ_44K;
  hi2s1.Init.CPOL = I2S_CPOL_LOW;
  if (HAL_I2S_Init(&hi2s1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S1_Init 2 */

  /* USER CODE END I2S1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

//************************************************************************************************************
void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
  /* 管理剩余文件大小和新地址偏移量: */  
  /* 检查是否已经到达文件的末尾 */
  if (AudioRemSize > 0)
	{
    /* 更新媒体层并启用播放 */  
    HAL_I2S_Transmit_DMA(&hi2s1,CurrentPos ,(uint16_t)(DMA_MAX(AudioRemSize)));
    /* 更新要播放的剩余数据数 */
    AudioRemSize = AudioRemSize - DMA_MAX(AudioRemSize);
    /* 更新当前音频指针位置 */
    CurrentPos = CurrentPos + DMA_MAX(AudioRemSize);
    //printf("AudioRemSize:%d\r\n",AudioRemSize);
	}
	else
	{
		XferCplt = 1; 
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);
		//printf("Data transmission to complete.\r\n\r\n");
	}
}
//************************************************************************************************************
uint8_t WM8960_Write_Reg(uint8_t reg, uint16_t dat)  
{
  uint8_t res,I2C_Data[2];
  I2C_Data[0] = (reg<<1)|((uint8_t)((dat>>8)&0x0001));  //寄存器地址
  I2C_Data[1] = (uint8_t)(dat&0x00FF);                  //寄存器数据
  res = HAL_I2C_Master_Transmit(&hi2c1,(WM8960_ADDRESS<<1),I2C_Data,2,10);
  if(res == HAL_OK)
    WM8960_REG_VAL[reg] = dat; 
  return res;
}

uint8_t WM89060_Init(void)  
{
  uint8_t res;
  //重置设备
  res = WM8960_Write_Reg(0x0f, 0x0000);
  if(res != 0)
    return res;
  else ; //WM8960复位成功
  //设置电源
  res =  WM8960_Write_Reg(0x19, 1<<8 | 1<<7 | 1<<6);
  res += WM8960_Write_Reg(0x1A, 1<<8 | 1<<7 | 1<<6 | 1<<5 | 1<<4 | 1<<3);
  res += WM8960_Write_Reg(0x2F, 1<<3 | 1<<2);
  if(res != 0)  	//电源设置失败
    return res;
  //配置时钟
  //MCLK->div1->SYSCLK->DAC/ADC sample Freq = 25MHz(MCLK)/2*256 = 48.8kHz
  WM8960_Write_Reg(0x04, 0x0000);
  //配置ADC和DAC
  WM8960_Write_Reg(0x05, 0x0000);
  //配置音频接口
  //I2S格式16位字长
  WM8960_Write_Reg(0x07, 0x0002);
  //Configure HP_L and HP_R OUTPUTS
  WM8960_Write_Reg(0x02, 0x006F | 0x0100);  //LOUT1 Volume Set
  WM8960_Write_Reg(0x03, 0x006F | 0x0100);  //ROUT1 Volume Set
  //Configure SPK_RP and SPK_RN
  WM8960_Write_Reg(0x28, 0x007F | 0x0100); //Left Speaker Volume
  WM8960_Write_Reg(0x29, 0x007F | 0x0100); //Right Speaker Volume
  //输出使能
  WM8960_Write_Reg(0x31, 0x00F7); //Enable Class D Speaker Outputs
  //配置DAC体积
  WM8960_Write_Reg(0x0a, 0x00FF | 0x0100);
  WM8960_Write_Reg(0x0b, 0x00FF | 0x0100);
  //3D
	//WM8960_Write_Reg(0x10, 0x001F);
  //配置 MIXER
  WM8960_Write_Reg(0x22, 1<<8 | 1<<7);
  WM8960_Write_Reg(0x25, 1<<8 | 1<<7);
  //Jack Detect
  WM8960_Write_Reg(0x18, 1<<6 | 0<<5);
  WM8960_Write_Reg(0x17, 0x01C3);
  WM8960_Write_Reg(0x30, 0x0009);//0x000D,0x0005
  return 0;
}
//************************************************************************************************************
uint32_t AUDIO_Play(uint16_t* pBuffer, uint32_t Size)
{
  uint8_t res;
  /* 设置要播放的数据总数(以半字计数) */
  AudioTotalSize = Size;
  /* 更新媒体层并启用播放 */
  res = HAL_I2S_Transmit_DMA(&hi2s1,pBuffer, (uint32_t)(DMA_MAX(Size/2)));
	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
	//printf("DMA_MAX(Size/2): %d\r\n",DMA_MAX(Size/2));
  /*更新要播放的剩余数据数 */
  AudioRemSize = (Size/2) - DMA_MAX(AudioTotalSize);
  //printf("AudioRemSize = %d\r\n",AudioRemSize);
  /* 更新当前音频指针位置 */
  CurrentPos = pBuffer + DMA_MAX(AudioTotalSize);
  return res;
}
uint32_t AudioFlashPlay(uint16_t* pBuffer, uint32_t FullSize, uint32_t StartAdd)
{ 
  AUDIO_Play((uint16_t*)pBuffer, (uint32_t)(FullSize - StartAdd));
  return 0;
}
//************************************************************************************************************

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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
