
#include "main.h"

#include "stdio.h"
#include "string.h"


#define unit8_t unsigned char
#define PUTCHAR_PROTOTYPE int fputc(int ch,FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#define BACKSPACE_PROTOTYPE int _backspace(FILE *f)

char a[50][50];
volatile int  PSWD;
volatile int  GK,p=1;    //GK关卡选择变量 p可选关卡限制 
volatile int  Player_Coordinates_Y,Player_Coordinates_X; //记录S的起始位置  前行后列          
volatile int  Box1_Destination_Y,Box1_Destination_X;     //记录箱子目的地1
volatile int  Box2_Destination_Y,Box2_Destination_X;     //记录箱子目的地2
volatile int  Box3_Destination_Y,Box3_Destination_X;     //记录箱子目的地3
volatile int  Box4_Destination_Y,Box4_Destination_X;     //记录箱子目的地4

UART_HandleTypeDef hlpuart1;


void level_pushbox(int k);   //关卡地图初始化 
void input_pushbox(int ch);  //输入按键判断逻辑
void supplement_pushbox();    //目标点补充函数 
void success_pushbox();       //通关之后运行 
void output_pushbox();        //推箱子显示输出函数 

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_LPUART1_UART_Init(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_LPUART1_UART_Init();

	
	printf("\r\n 请输入密码查看通关攻略: \r\n");
	scanf("%d",&PSWD);
	HAL_Delay(100);
	printf("\r\n Receive PSWD=%d",PSWD);			
  if(PSWD==19991015)   //判断密码是否正确  
	{
		level_pushbox(0);
		output_pushbox();
	}
	else
		printf("\r\n 密码错误 \r\n");
	
	
	printf("\r\n 请输入密码解锁所有关卡: \r\n");
	scanf("%d",&PSWD);
	HAL_Delay(100);
	printf("\r\n Receive PSWD=%d",PSWD);		
  if(PSWD==19991015)   //判断密码是否正确  
	{
		p=5;
		printf("\r\n 密码正确，所有关卡已解锁！！！ \r\n");
	}
	else
		printf("\r\n 密码错误，解锁失败。 \r\n");
	
	
	printf("\r\n 请输入密码预览通关结果: \r\n");
	scanf("%d",&PSWD);
	HAL_Delay(100);
	printf("\r\n Receive PSWD=%d",PSWD);		
  if(PSWD==19991015)   //判断密码是否正确  
	  success_pushbox();
	else
		printf("\r\n 密码错误 \r\n");
	
	do
	{
		printf("请选择关卡(1-5): \r\n");
		scanf("%d",&GK);
		HAL_Delay(50);
		printf("\r\n");
		HAL_Delay(50);
		if (GK<1||GK>5) 
	    	printf("关卡选择错误 \r\n");
		else if(GK>p) 
	    	printf("禁止白嫖 \r\n");
	}while(GK<1||GK>5||GK>p);
	
	
   while(GK>=1&&GK<=5) //游戏执行
    {
	    level_pushbox(GK);  //关卡初始化函数 
      output_pushbox();  //初始状态显示 
	    while(1)  //运行模块 
	    {
		    int ch;
				printf("请执行操作：");
				scanf("%d",&ch);
		    input_pushbox(ch);     //输入按键判断逻辑 
		    supplement_pushbox();  //目标点补充函数 
		    output_pushbox(); //状态显示刷新 
		    if(a[Box1_Destination_Y][Box1_Destination_X]=='@'&&a[Box2_Destination_Y][Box2_Destination_X]=='@'  //获胜条件
		     &&a[Box3_Destination_Y][Box3_Destination_X]=='@'&&a[Box4_Destination_Y][Box4_Destination_X]=='@')
		    {
		    	GK++;
		    	if(GK>=p) p=GK; //选关限制----即检查点 
          HAL_Delay(150);
          break; //确认获胜则跳出while(1)循环 
		    }
	    }
    }
		
    success_pushbox();//通关之后运行 
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
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
  /** Initializes the peripherals clocks
  */
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
  hlpuart1.Init.BaudRate = 115200;
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

static void MX_GPIO_Init(void)
{
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
}

/* USER CODE BEGIN 4 */


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

 
 
/* USER CODE END 4 */

void level_pushbox(int GK)  //关卡地图初始化
{
	switch(GK)
	{
		case 1:
			{
				strcpy(a[0],"   ###                                           ");
				strcpy(a[1],"   #*#                                           ");
				strcpy(a[2],"   # #                                           ");
				strcpy(a[3],"####O######                                      ");
				strcpy(a[4],"#*  OM O *#                                      ");
				strcpy(a[5],"#####O#####                                      ");
				strcpy(a[6],"    # #                                          ");
				strcpy(a[7],"    #*#                                          ");
				strcpy(a[8],"    ###                                          ");
				strcpy(a[9],"                                                 ");
				strcpy(a[10],"关卡 1/5                                        ");
				strcpy(a[11],"                                                ");
				strcpy(a[12],"                                                ");
				strcpy(a[13],"                                                ");
				strcpy(a[14],"                                                ");
	            Player_Coordinates_Y=4,Player_Coordinates_X=5;         
	            Box1_Destination_Y=1,Box1_Destination_X=4;
	            Box2_Destination_Y=4,Box2_Destination_X=1;
	            Box3_Destination_Y=4,Box3_Destination_X=9;
	            Box4_Destination_Y=7,Box4_Destination_X=5;
			}
		break;
		case 2:
			{
				strcpy(a[0],"######                                           ");
				strcpy(a[1],"#*   #                                           ");
				strcpy(a[2],"###  #                                           ");
				strcpy(a[3],"#  O ######                                      ");
				strcpy(a[4],"#*  OM O *#                                      ");
				strcpy(a[5],"#####O#####                                      ");
				strcpy(a[6],"    # #                                          ");
				strcpy(a[7],"    #*#                                          ");
				strcpy(a[8],"    ###                                          ");
				strcpy(a[9],"                                                 ");
				strcpy(a[10],"关卡 2/5                                        ");
				strcpy(a[11],"                                                ");
				strcpy(a[12],"                                                ");
				strcpy(a[13],"                                                ");
				strcpy(a[14],"                                                ");
	            Player_Coordinates_Y=4,Player_Coordinates_X=5;         
	            Box1_Destination_Y=1,Box1_Destination_X=1;
	            Box2_Destination_Y=4,Box2_Destination_X=1;
	            Box3_Destination_Y=4,Box3_Destination_X=9;
	            Box4_Destination_Y=7,Box4_Destination_X=5;
			}
		break;
		case 3:
			{
				strcpy(a[0],"  ####                                           ");
				strcpy(a[1],"  #  #                                           ");
				strcpy(a[2],"  #  #                                           ");
				strcpy(a[3],"  #M #                                           ");
				strcpy(a[4],"### ######                                       ");
				strcpy(a[5],"#   O  O*#                                       ");
				strcpy(a[6],"# O*   ###                                       ");
				strcpy(a[7],"#####* O*#                                       ");
				strcpy(a[8],"    ######                                       ");
				strcpy(a[9],"                                                 ");
				strcpy(a[10],"关卡 3/5                                        ");
				strcpy(a[11],"                                                ");
				strcpy(a[12],"                                                ");
				strcpy(a[13],"                                                ");
				strcpy(a[14],"                                                ");
	            Player_Coordinates_Y=3,Player_Coordinates_X=3;         
	            Box1_Destination_Y=6,Box1_Destination_X=3;
	            Box2_Destination_Y=5,Box2_Destination_X=8;
	            Box3_Destination_Y=7,Box3_Destination_X=5;
	            Box4_Destination_Y=7,Box4_Destination_X=8;
			}
		break;
		case 4:
			{
				strcpy(a[0]," ########                                        ");
				strcpy(a[1]," #     ###                                       ");
				strcpy(a[2],"##O###   #                                       ");
				strcpy(a[3],"#M  O  O #                                       ");
				strcpy(a[4],"# **# O ##                                       ");
				strcpy(a[5],"##**#   #                                        ");
				strcpy(a[6]," ########                                        ");
				strcpy(a[7],"                                                 ");
				strcpy(a[8],"                                                 ");
				strcpy(a[9],"                                                 ");
				strcpy(a[10],"关卡 4/5                                        ");
				strcpy(a[11],"                                                ");
				strcpy(a[12],"                                                ");
				strcpy(a[13],"                                                ");
				strcpy(a[14],"                                                ");
	            Player_Coordinates_Y=3,Player_Coordinates_X=1;         
	            Box1_Destination_Y=4,Box1_Destination_X=2;
	            Box2_Destination_Y=4,Box2_Destination_X=3;
	            Box3_Destination_Y=5,Box3_Destination_X=2;
	            Box4_Destination_Y=5,Box4_Destination_X=3;
			}
		break;
		case 5:
			{
				strcpy(a[0],"  ####                                           ");
				strcpy(a[1],"  #**#                                           ");
				strcpy(a[2]," ## *##                                          ");
				strcpy(a[3]," #  O*#                                          ");
				strcpy(a[4],"## O  ##                                         ");
				strcpy(a[5],"#  #OO #                                         ");
				strcpy(a[6],"#  M   #                                         ");
				strcpy(a[7],"########                                         ");
				strcpy(a[8],"                                                 ");
				strcpy(a[9],"                                                 ");
				strcpy(a[10],"关卡 5/5                                        ");
				strcpy(a[11],"                                                ");
				strcpy(a[12],"                                                ");
				strcpy(a[13],"                                                ");
				strcpy(a[14],"                                                ");
	            Player_Coordinates_Y=6,Player_Coordinates_X=3;         
	            Box1_Destination_Y=1,Box1_Destination_X=3;
	            Box2_Destination_Y=1,Box2_Destination_X=4;
	            Box3_Destination_Y=2,Box3_Destination_X=4;
	            Box4_Destination_Y=3,Box4_Destination_X=5;
			}
		break;	
		case 0:
			{                                                                      
		    		strcpy(a[0],"             通关攻略                           ");   
	    			strcpy(a[1],"关卡 1/5 :                                       ");   
		    		strcpy(a[2],"  SS WW DDD AAAAAA DD WW                         "); 
    				strcpy(a[3],"关卡 2/5 :                                       "); 
	    			strcpy(a[4],"  SS WW DDD AAAAAA DWW DWAA                      ");  
		    		strcpy(a[5],"关卡 3/5 :                                       ");
			    	strcpy(a[6],"  SSSDDDWDA SSDAWWAASAW AASDDDWDS AAWWWD WWASSSS ");
    				strcpy(a[7],"关卡 4/5 :                                       ");
	    			strcpy(a[8],"  DDDD SSDDWWA WWAAAA SSASDWDS WAWWDDDD SSAAADDD ");
		    		strcpy(a[9],"  WWAAAA SSASD WDDDDD SASAW DWAAA DDDWW AAAA SSS ");
			    	strcpy(a[10],"  WDDDDDD WAS AAAAA WWDDDD SDS AAAA DDDWW AAAASS");
    				strcpy(a[11],"关卡 5/5 :                                      ");
	    			strcpy(a[12],"  AWW DDWW SSAASS DDWWW SSSDD WASAAA WWWDDD SAAA");
		    		strcpy(a[13],"  SSDD WW DWA SAWW SSASS DDDWW                  ");
			    	strcpy(a[14],"                                                ");
			}
		break;
	}
}


void input_pushbox(int ch)     //输入按键判断逻辑
{
	switch(ch)  //按键判断逻辑 
	{
	    case 8:
		    if(a[Player_Coordinates_Y-1][Player_Coordinates_X]!='#')                 //上边不是墙 
		    {
			    if(a[Player_Coordinates_Y-1][Player_Coordinates_X]!='O'&&a[Player_Coordinates_Y-1][Player_Coordinates_X]!='@')      //上边不是箱子 
			    {
				   a[Player_Coordinates_Y][Player_Coordinates_X]=' ';   //当前位置人物消失 
				   Player_Coordinates_Y--;                              //人物上移 
				   a[Player_Coordinates_Y][Player_Coordinates_X]='M';   //人物出现 
			    }
			    else if(a[Player_Coordinates_Y-2][Player_Coordinates_X]!='#'&&a[Player_Coordinates_Y-2][Player_Coordinates_X]!='@'&&a[Player_Coordinates_Y-2][Player_Coordinates_X]!='O')
			    {                                                                    //上边是箱子  上上不是墙也不是箱子 
				   a[Player_Coordinates_Y][Player_Coordinates_X]=' ';   //同 
				   Player_Coordinates_Y--;                              // 
				   a[Player_Coordinates_Y][Player_Coordinates_X]='M';   //上 
				   a[Player_Coordinates_Y-1][Player_Coordinates_X]='O'; //箱子出现在人上方  推箱操作成功 
				   if(((Player_Coordinates_Y-1==Box1_Destination_Y)&&(Player_Coordinates_X==Box1_Destination_X))
				    ||((Player_Coordinates_Y-1==Box2_Destination_Y)&&(Player_Coordinates_X==Box2_Destination_X))
				    ||((Player_Coordinates_Y-1==Box3_Destination_Y)&&(Player_Coordinates_X==Box3_Destination_X))
					||((Player_Coordinates_Y-1==Box4_Destination_Y)&&(Player_Coordinates_X==Box4_Destination_X)))
				       a[Player_Coordinates_Y-1][Player_Coordinates_X]='@';//判断箱子是否在目标点 
			    }
		    }
		break;   
		case 4:
		    if(a[Player_Coordinates_Y][Player_Coordinates_X-1]!='#')
		    {
			    if(a[Player_Coordinates_Y][Player_Coordinates_X-1]!='O'&&a[Player_Coordinates_Y][Player_Coordinates_X-1]!='@')
			    {
				   a[Player_Coordinates_Y][Player_Coordinates_X]=' ';
				   Player_Coordinates_X--;
				   a[Player_Coordinates_Y][Player_Coordinates_X]='M';
			    }
			    else if(a[Player_Coordinates_Y][Player_Coordinates_X-2]!='#'&&a[Player_Coordinates_Y][Player_Coordinates_X-2]!='@'&&a[Player_Coordinates_Y][Player_Coordinates_X-2]!='O')
			    {
				   a[Player_Coordinates_Y][Player_Coordinates_X]=' ';
				   Player_Coordinates_X--;
				   a[Player_Coordinates_Y][Player_Coordinates_X]='M';
				   a[Player_Coordinates_Y][Player_Coordinates_X-1]='O';
			       if(((Player_Coordinates_Y==Box1_Destination_Y)&&(Player_Coordinates_X-1==Box1_Destination_X))
				    ||((Player_Coordinates_Y==Box2_Destination_Y)&&(Player_Coordinates_X-1==Box2_Destination_X))
				    ||((Player_Coordinates_Y==Box3_Destination_Y)&&(Player_Coordinates_X-1==Box3_Destination_X))
					||((Player_Coordinates_Y==Box4_Destination_Y)&&(Player_Coordinates_X-1==Box4_Destination_X)))
				       a[Player_Coordinates_Y][Player_Coordinates_X-1]='@';
			    }
		    }
		break;
		case 2:
		    if(a[Player_Coordinates_Y+1][Player_Coordinates_X]!='#')
		    {
			    if(a[Player_Coordinates_Y+1][Player_Coordinates_X]!='O'&&a[Player_Coordinates_Y+1][Player_Coordinates_X]!='@')
			    {
				   a[Player_Coordinates_Y][Player_Coordinates_X]=' ';
				   Player_Coordinates_Y++;
				   a[Player_Coordinates_Y][Player_Coordinates_X]='M';
			    }
			    else if(a[Player_Coordinates_Y+2][Player_Coordinates_X]!='#'&&a[Player_Coordinates_Y+2][Player_Coordinates_X]!='@'&&a[Player_Coordinates_Y+2][Player_Coordinates_X]!='O')
			    {
				   a[Player_Coordinates_Y][Player_Coordinates_X]=' ';
				   Player_Coordinates_Y++;
				   a[Player_Coordinates_Y][Player_Coordinates_X]='M';
				   a[Player_Coordinates_Y+1][Player_Coordinates_X]='O';
				   if(((Player_Coordinates_Y+1==Box1_Destination_Y)&&(Player_Coordinates_X==Box1_Destination_X))
				    ||((Player_Coordinates_Y+1==Box2_Destination_Y)&&(Player_Coordinates_X==Box2_Destination_X))
				    ||((Player_Coordinates_Y+1==Box3_Destination_Y)&&(Player_Coordinates_X==Box3_Destination_X))
					||((Player_Coordinates_Y+1==Box4_Destination_Y)&&(Player_Coordinates_X==Box4_Destination_X)))
				       a[Player_Coordinates_Y+1][Player_Coordinates_X]='@';
			    }
			}
		break;
    case 6:
		    if(a[Player_Coordinates_Y][Player_Coordinates_X+1]!='#')
		    {
			    if(a[Player_Coordinates_Y][Player_Coordinates_X+1]!='O'&&a[Player_Coordinates_Y][Player_Coordinates_X+1]!='@')
			    {
				   a[Player_Coordinates_Y][Player_Coordinates_X]=' ';
				   Player_Coordinates_X++;
				   a[Player_Coordinates_Y][Player_Coordinates_X]='M';
			    }
			    else if(a[Player_Coordinates_Y][Player_Coordinates_X+2]!='#'&&a[Player_Coordinates_Y][Player_Coordinates_X+2]!='@'&&a[Player_Coordinates_Y][Player_Coordinates_X+2]!='O')
			    {
				   a[Player_Coordinates_Y][Player_Coordinates_X]=' ';
				   Player_Coordinates_X++;
				   a[Player_Coordinates_Y][Player_Coordinates_X]='M';
				   a[Player_Coordinates_Y][Player_Coordinates_X+1]='O';
				   if(((Player_Coordinates_Y==Box1_Destination_Y)&&(Player_Coordinates_X+1==Box1_Destination_X))
				    ||((Player_Coordinates_Y==Box2_Destination_Y)&&(Player_Coordinates_X+1==Box2_Destination_X))
				    ||((Player_Coordinates_Y==Box3_Destination_Y)&&(Player_Coordinates_X+1==Box3_Destination_X))
					||((Player_Coordinates_Y==Box4_Destination_Y)&&(Player_Coordinates_X+1==Box4_Destination_X)))
				       a[Player_Coordinates_Y][Player_Coordinates_X+1]='@';					  
			    }
		    }
		break;
		default: 
			printf("\r\n  违规操作！！！ \r\n");;   //按下其他按键不响应 
		break;
	}
} 


void supplement_pushbox()  //目标点补充函数 
{
	if(a[Box1_Destination_Y][Box1_Destination_X]==' ')  
	    a[Box1_Destination_Y][Box1_Destination_X]='*'; 
	if(a[Box2_Destination_Y][Box2_Destination_X]==' ')  
	    a[Box2_Destination_Y][Box2_Destination_X]='*';
	if(a[Box3_Destination_Y][Box3_Destination_X]==' ')  
	    a[Box3_Destination_Y][Box3_Destination_X]='*';
	if(a[Box4_Destination_Y][Box4_Destination_X]==' ')  
	    a[Box4_Destination_Y][Box4_Destination_X]='*';
}


void success_pushbox()  //通关之后运行
{
    printf("\r\n！！！恭喜通关！！！\r\n");
    printf("\r\n 密码是 19991015 \r\n"); 
    for (float y = 1.3f; y > -1.0f; y -= 0.1f)  //画爱心图 
    {
        for (float x = -1.5f; x < 1.5f; x += 0.05f) 
		{
            float a = x * x + y * y - 1;
            putchar(a * a * a - x * x * y * y * y <= 0.0f ? '*' : ' ');
        }
        printf("\r\n");
    }
} 


void output_pushbox()  //推箱子显示输出函数
{
	int i;
	int j;
	printf("\r\n");
	for(i=0;i<15;i++)
  {
	  for(j=0;j<50;j++)
		{
			printf("%c",a[i][j]);  
		}
		HAL_Delay(20); //必须有延时
		printf("\r\n");
  }
}


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
