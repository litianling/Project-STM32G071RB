#include "main.h"

#define MASTER_BOARD	//不注释此行是从板  注释掉此行是主板
#define MASTER_REQ_READ    0x12
#define MASTER_REQ_WRITE   0x34

I2C_HandleTypeDef hi2c1;

uint8_t bTransferRequest = 0;  //传输请求：主服务器是发送还是接收

/* Buffer used for transmission 发送缓存区*/
uint8_t aTxBuffer[] = " ****I2C_TwoBoards communication based on IT****  ****I2C_TwoBoards communication based on IT****  ****I2C_TwoBoards communication based on IT**** ";
__IO uint16_t hTxNumData = 0;

/* Buffer used for reception 接收缓存区*/
uint8_t aRxBuffer[RXBUFFERSIZE];  //光定义大小不赋值
__IO uint16_t hRxNumData = 0;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);

static uint16_t Buffercmp(uint8_t *pBuffer1, uint8_t *pBuffer2, uint16_t BufferLength);
static void Flush_Buffer(uint8_t *pBuffer, uint16_t BufferLength);



int main(void)
{
  /* USER CODE BEGIN 1 */
  /*STM32G0xx HAL library initialization:
		- Configure the Flash prefetch
		- Systick timer is configured by default as source of time base, but user
		can eventually implement his proper time base source (a general purpose
		timer for example or other time source), keeping in mind that Time base
		duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
		handled in milliseconds basis.
		- Low Level Initialization 
	
	STM32G0xx HAL库初始化:
		—设置Flash预取
		—系统stick定时器默认配置为时间源，而不是用户
		最终能否实现自己的适当时基源(通用目的
		例如定时器或其他时间源)，记住时间基数
		duration应该保持1ms，因为定义了PPP_TIMEOUT_VALUEs
		以毫秒为基础处理。
		-低级别初始化
     */

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_I2C1_Init();
  BSP_LED_Init(LED4);


#ifdef MASTER_BOARD
  /* Configure User push-button 配置用户按钮*/
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

  /* 在开始通信之前，等待用户按下按钮*/
  while (BSP_PB_GetState(BUTTON_USER) != GPIO_PIN_RESET) ; //按下为0  不为0则没按下
		
  /*在开始通信之前，等待用户按钮释放*/
  while (BSP_PB_GetState(BUTTON_USER) != GPIO_PIN_SET) ;
	
#endif /* MASTER_BOARD */

  while (1)
  {
/*
		while(1)
		{
			if (HAL_I2C_Master_Transmit_IT(&hi2c1, (uint16_t)I2C_ADDRESS, (uint8_t *)&hTxNumData, 2) != HAL_OK)
        Error_Handler();
			HAL_Delay(1);
		}
*/
		
#ifdef MASTER_BOARD
    /* Initialize number of data variables 初始化数据变量的数量*/
    hTxNumData = TXBUFFERSIZE;	//*hTxNumData 指向最后一个要发送的字符
    hRxNumData = RXBUFFERSIZE;	//大小同TXBUFFERSIZE
		

    /* Update bTransferRequest to send buffer write request for Slave 更新bTransferRequest为从服务器发送缓冲区写请求*/
    bTransferRequest = MASTER_REQ_WRITE; //请求置为0x34 开始写
		
		
    /*##-2- Master sends write request for slave 主服务器向从服务器发送写请求*/
    do
    {
      if (HAL_I2C_Master_Transmit_IT(&hi2c1, (uint16_t)I2C_ADDRESS, (uint8_t *)&bTransferRequest, 1) != HAL_OK)
        Error_Handler();
      /*  在开始新的通信传输之前，您需要检查外设的当前状态;如果忙，您需要等待当前传输结束后再开始新的传输。
			为了简单起见，本示例只是等待传输结束，但是应用程序可以在传输操作进行时执行其他任务。*/
			while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);
      /* 当确认失败发生时(从服务器不确认它的地址)主服务器重新启动通信*/
    }
    while (HAL_I2C_GetError(&hi2c1) == HAL_I2C_ERROR_AF);


		
    /*##-3- Master sends number of data to be written 主服务器发送要写入的数据数*/
    do
    {
      if (HAL_I2C_Master_Transmit_IT(&hi2c1, (uint16_t)I2C_ADDRESS, (uint8_t *)&hTxNumData, 2) != HAL_OK)
        Error_Handler();
      while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) ;  /* 检查外设传输状态*/
    }
    while (HAL_I2C_GetError(&hi2c1) == HAL_I2C_ERROR_AF);/* 当确认失败发生时(从服务器不确认它的地址)主服务器重新启动通信 */
		

		
    /*##-4- Master sends aTxBuffer to slave   主服务器将aTxBuffer发送给从服务器*/
    do
    {
      if (HAL_I2C_Master_Transmit_IT(&hi2c1, (uint16_t)I2C_ADDRESS, (uint8_t *)aTxBuffer, TXBUFFERSIZE) != HAL_OK)
        Error_Handler();
      while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) ;   /*  检查外设传输状态 */
    }
    while (HAL_I2C_GetError(&hi2c1) == HAL_I2C_ERROR_AF);		/* 当确认失败发生时(从服务器不确认它的地址)主服务器重新启动通信 */
		

		
    /* Update bTransferRequest to send buffer read request for Slave 更新bTransferRequest————为从服务器发送缓冲区读请求*/
    bTransferRequest = MASTER_REQ_READ;  //0x12开始读
		
		
		
    /*##-5- Master sends read request for slave 主服务器向从服务器发送读请求*/
    do
    {
      if (HAL_I2C_Master_Transmit_IT(&hi2c1, (uint16_t)I2C_ADDRESS, (uint8_t *)&bTransferRequest, 1) != HAL_OK)
        Error_Handler();
      while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) ;   /* 检查外设传输状态 */
    }
    while (HAL_I2C_GetError(&hi2c1) == HAL_I2C_ERROR_AF);/* 当确认失败发生时(从服务器不确认它的地址)主服务器重新启动通信 */

		
		
    /*##-6- Master sends number of data to be read 主服务器发送要读取的数据数*/
    do
    {
      if (HAL_I2C_Master_Transmit_IT(&hi2c1, (uint16_t)I2C_ADDRESS, (uint8_t *)&hRxNumData, 2) != HAL_OK)
        Error_Handler();
      while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) ;   /*  检查外设传输状态 */
    }
    while (HAL_I2C_GetError(&hi2c1) == HAL_I2C_ERROR_AF);/* 当确认失败发生时(从服务器不确认它的地址)主服务器重新启动通信 */

	

    /*##-7- Master receives aRxBuffer from slave 主服务器从从服务器接收aRxBuffer*/
    do
    {
      if (HAL_I2C_Master_Receive_IT(&hi2c1, (uint16_t)I2C_ADDRESS, (uint8_t *)aRxBuffer, RXBUFFERSIZE) != HAL_OK)
        Error_Handler();
      while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) ;      /* 检查外设传输状态 */
    }
    while (HAL_I2C_GetError(&hi2c1) == HAL_I2C_ERROR_AF);/* 当确认失败发生时(从服务器不确认它的地址)主服务器重新启动通信 */

		
		
		
    /* Check correctness of received buffer 检查接收缓冲区的正确性*/
    if (Buffercmp((uint8_t *)aTxBuffer, (uint8_t *)aRxBuffer, hRxNumData))
      Error_Handler();
		
    /* Flush Rx buffers 刷新接收缓冲区*/
    Flush_Buffer((uint8_t *)aRxBuffer, RXBUFFERSIZE);

    /* 灯LED4反转*/
    BSP_LED_Toggle(LED4);

    /*这个延迟允许看到LED4的切换*/
    HAL_Delay(25);
		
#else /* MASTER_BOARD */

    /* Initialize number of data variables 初始化数据变量的数量*/
    hTxNumData = 0;
    hRxNumData = 0;

    /*##-2- Slave receive request from master 从板接收主板的请求*/
    while (HAL_I2C_Slave_Receive_IT(&hi2c1, (uint8_t *)&bTransferRequest, 1) != HAL_OK) ;
		
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) ; /*  检查外设传输状态 */

    /* If master request write operation 如果主板请求写操作*/
    if (bTransferRequest == MASTER_REQ_WRITE)
    {
      /*##-3- Slave receive number of data to be read 接收准备读的数据*/
      while (HAL_I2C_Slave_Receive_IT(&hi2c1, (uint8_t *)&hRxNumData, 2) != HAL_OK);

      while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) ;  /*  检查外设传输状态 */

      /*##-4- Slave receives aRxBuffer from master 从主机接收aRxBuffer*/
      while (HAL_I2C_Slave_Receive_IT(&hi2c1, (uint8_t *)aRxBuffer, hRxNumData) != HAL_OK);

      while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)  ;  /*  检查外设传输状态 */

      /* Check correctness of received buffer 检查接收缓冲区的正确性*/
      if (Buffercmp((uint8_t *)aTxBuffer, (uint8_t *)aRxBuffer, hRxNumData))
        Error_Handler();

      /* Flush Rx buffers 刷新接收缓冲区*/
      Flush_Buffer((uint8_t *)aRxBuffer, RXBUFFERSIZE);

      /* Toggle LED4 反转LED4灯*/
      BSP_LED_Toggle(LED4);
    }
    /* If master request write operation  如果主板请求读操作*/
    else
    {
      /*##-3- Slave receive number of data to be written 从板接收要写入的数据数*/
      while (HAL_I2C_Slave_Receive_IT(&hi2c1, (uint8_t *)&hTxNumData, 2) != HAL_OK);

      while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) ;   /*  检查外设传输状态 */
			
      /*##-4- Slave transmit aTxBuffer to master 从板将aTxBuffer传输给主板*/
      while (HAL_I2C_Slave_Transmit_IT(&hi2c1, (uint8_t *)aTxBuffer, RXBUFFERSIZE) != HAL_OK);
      
			/* 检查外设传输状态 */
      while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) ;
    }
#endif /* MASTER_BOARD */  
	}
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
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
  /** Initializes the CPU, AHB and APB buses clocks  初始化CPU、AHB与APB总线*/
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


static void MX_I2C1_Init(void)
{
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00303D5B;
  hi2c1.Init.OwnAddress1 = I2C_ADDRESS;
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
  /** Configure Analogue filter  配置模拟滤波器*/
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter  配置数字滤波器*/
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /** I2C Fast mode Plus enable     IIC极速模式使能*/
  HAL_I2CEx_EnableFastModePlus(I2C_FASTMODEPLUS_I2C1);
}


static void MX_GPIO_Init(void)
{
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

static uint16_t Buffercmp(uint8_t *pBuffer1, uint8_t *pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if ((*pBuffer1) != *pBuffer2)
      return BufferLength;
    pBuffer1++;
    pBuffer2++;
  }
  return 0;
}


static void Flush_Buffer(uint8_t *pBuffer, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    *pBuffer = 0;
    pBuffer++;
  }
}


void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *I2cHandle)
{
  /** 1- When Slave doesn't acknowledge its address, Master restarts communication.
    * 2- When Master doesn't acknowledge the last data transferred, Slave doesn't care in this example. */
  if (HAL_I2C_GetError(I2cHandle) != HAL_I2C_ERROR_AF)
    Error_Handler();
}


void Error_Handler(void)
{
  while (1)
  {
    BSP_LED_Toggle(LED4);
    HAL_Delay(1000);
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
  Error_Handler();
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
