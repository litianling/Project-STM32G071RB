/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"


int ZFK[27][16][12]=  //字符库 27个 16行 12列 (0亮1灭)
{
		{		//		空格
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		//		A
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,0,0,0,0,0},
		{0,0,0,0,1,1,1,0,0,0,0,0},
		{0,0,0,1,1,0,1,1,0,0,0,0},
		{0,0,0,1,0,0,0,1,0,0,0,0},
		{0,0,1,1,0,0,0,1,1,0,0,0},
		{0,0,1,1,1,1,1,1,1,0,0,0},
		{0,1,1,1,1,1,1,1,1,1,0,0},
		{0,1,1,0,0,0,0,0,1,1,0,0},
		{0,1,1,0,0,0,0,0,1,1,0,0},
		{0,1,1,0,0,0,0,0,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		//		B
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,1,1,1,1,0,0,0,0,0},
		{0,1,1,1,1,1,1,0,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},

	{		 //		C
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,1,1,1,0,0,0,0},
		{0,0,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,1,1,1,0,0,0,0},
		{0,0,0,1,1,1,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},

	{		 //		D
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		E
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		F
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,0,0,0,0,0,0},
		{0,1,1,1,1,1,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		G
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,1,1,1,0,0,0,0},
		{0,0,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,1,1,1,0,0,0,0},
		{0,1,1,0,0,1,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,1,0,0,1,1,0,0,0,0},
		{0,0,1,1,1,1,1,1,0,0,0,0},
		{0,0,0,1,1,1,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		H
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		I
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,1,1,1,0,0,0,0},
		{0,0,1,1,1,1,1,1,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,1,1,1,1,1,1,0,0,0,0},
		{0,0,1,1,1,1,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		J
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,1,1,1,0,0,0,0},
		{0,0,1,1,1,1,1,1,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,1,0,0,1,1,0,0,0,0,0,0},
		{0,1,1,1,1,1,0,0,0,0,0,0},
		{0,0,1,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		K
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,0,0,1,1,0,0,0,0,0},
		{0,1,1,0,1,1,0,0,0,0,0,0},
		{0,1,1,1,1,0,0,0,0,0,0,0},
		{0,1,1,1,0,0,0,0,0,0,0,0},
		{0,1,1,1,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,0,0,0,0,0,0,0},
		{0,1,1,0,1,1,0,0,0,0,0,0},
		{0,1,1,0,0,1,1,0,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		L
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		M
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,1,1,0,0},
		{0,1,1,1,0,0,0,1,1,1,0,0},
		{0,1,1,1,1,0,1,1,1,1,0,0},
		{0,1,1,0,1,1,1,0,1,1,0,0},
		{0,1,1,0,1,1,1,0,1,1,0,0},
		{0,1,1,0,0,1,0,0,1,1,0,0},
		{0,1,1,0,0,0,0,0,1,1,0,0},
		{0,1,1,0,0,0,0,0,1,1,0,0},
		{0,1,1,0,0,0,0,0,1,1,0,0},
		{0,1,1,0,0,0,0,0,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		N
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,1,1,0,0},
		{0,1,1,1,0,0,0,0,1,1,0,0},
		{0,1,1,1,0,0,0,0,1,1,0,0},
		{0,1,1,1,1,0,0,0,1,1,0,0},
		{0,1,1,0,1,1,0,0,1,1,0,0},
		{0,1,1,0,0,1,1,0,1,1,0,0},
		{0,1,1,0,0,0,1,1,1,1,0,0},
		{0,1,1,0,0,0,0,1,1,1,0,0},
		{0,1,1,0,0,0,0,1,1,1,0,0},
		{0,1,1,0,0,0,0,0,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		O
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,1,1,0,0,0,0,0},
		{0,0,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,0,0,1,1,1,0,0,0},
		{0,1,1,0,0,0,0,1,1,0,0,0},
		{0,1,1,0,0,0,0,1,1,0,0,0},
		{0,1,1,0,0,0,0,1,1,0,0,0},
		{0,1,1,0,0,0,0,1,1,0,0,0},
		{0,1,1,1,0,0,1,1,1,0,0,0},
		{0,0,1,1,1,1,1,1,0,0,0,0},
		{0,0,0,1,1,1,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		P
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,1,1,1,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		Q
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,1,1,0,0,0,0,0},
		{0,0,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,0,0,1,1,1,0,0,0},
		{0,1,1,0,0,0,0,1,1,0,0,0},
		{0,1,1,0,0,0,0,1,1,0,0,0},
		{0,1,1,0,0,0,0,1,1,0,0,0},
		{0,1,1,0,0,0,0,1,1,0,0,0},
		{0,1,1,1,0,0,1,1,1,0,0,0},
		{0,0,1,1,1,1,1,1,1,1,0,0},
		{0,0,0,1,1,1,1,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		R
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,1,1,1,0,0,0,0,0},
		{0,1,1,1,1,0,0,0,0,0,0,0},
		{0,1,1,0,1,1,0,0,0,0,0,0},
		{0,1,1,0,0,1,1,0,0,0,0,0},
		{0,1,1,0,0,0,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		S
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,1,1,1,0,0,0,0},
		{0,0,1,1,1,1,1,1,1,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,1,1,0,0,0,0,0},
		{0,0,0,1,1,1,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,0,1,1,1,1,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		T
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,0,0,0},
		{0,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		U
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,1,1,0,0,0},
		{0,1,1,0,0,0,0,1,1,0,0,0},
		{0,1,1,0,0,0,0,1,1,0,0,0},
		{0,1,1,0,0,0,0,1,1,0,0,0},
		{0,1,1,0,0,0,0,1,1,0,0,0},
		{0,1,1,0,0,0,0,1,1,0,0,0},
		{0,1,1,0,0,0,0,1,1,0,0,0},
		{0,1,1,1,0,0,1,1,1,0,0,0},
		{0,0,1,1,1,1,1,1,0,0,0,0},
		{0,0,0,1,1,1,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		V
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,0,0,0,0,0,0,1,0,0,0},
		{0,1,0,0,0,0,0,0,1,0,0,0},
		{0,1,1,0,0,0,0,1,1,0,0,0},
		{0,1,1,0,0,0,0,1,1,0,0,0},
		{0,0,1,1,0,0,1,1,0,0,0,0},
		{0,0,1,1,0,0,1,1,0,0,0,0},
		{0,0,0,1,0,0,1,0,0,0,0,0},
		{0,0,0,1,1,1,1,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		W
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,1,1,0,0},
		{0,1,1,0,0,0,0,0,1,1,0,0},
		{0,1,1,0,0,0,0,0,1,1,0,0},
		{0,1,1,0,0,0,0,0,1,1,0,0},
		{0,1,1,0,0,1,0,0,1,1,0,0},
		{0,1,1,0,1,1,1,0,1,1,0,0},
		{0,1,1,1,1,0,1,1,1,1,0,0},
		{0,1,1,1,0,0,0,1,1,1,0,0},
		{0,1,1,0,0,0,0,0,1,1,0,0},
		{0,1,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		X
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,1,1,0,0,0,0,0},
		{0,1,1,0,0,1,1,0,0,0,0,0},
		{0,0,1,1,1,1,0,0,0,0,0,0},
		{0,0,1,1,1,1,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,0,0},
		{0,0,1,1,1,1,0,0,0,0,0,0},
		{0,0,1,1,1,1,0,0,0,0,0,0},
		{0,1,1,0,0,1,1,0,0,0,0,0},
		{0,1,1,0,0,1,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		Y
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,1,1,0,0,0,0,0},
		{0,1,1,0,0,1,1,0,0,0,0,0},
		{0,1,1,0,0,1,1,0,0,0,0,0},
		{0,0,1,1,1,1,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		 //		Z
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,0,0,0,0,0,1,1,0,0,0,0},
		{0,0,0,0,0,1,1,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,0,0},
		{0,0,1,1,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,1,1,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	}
};


int WZK[20][20]=  //文字库 20行 20列 （数值不同字符不同）
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

int TCSK[20][20]=  //贪吃蛇库 20行 20列 （数值不同颜色不同）
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

char tstr[20]; //需要显示的某一行
int hang=0;    //指定行数

void comm_out(unsigned char m);											//输出命令
void data_out(unsigned char b);											//输出数据
void write_data(unsigned char i,unsigned char j);		//写颜色

void reset_TFT();				//TFT彩屏初始化
void ini_ILI9341();			//控制器初始化

void display_horizontal_line(void);		//横条纹
void display_vertical_line(void);			//纵条纹
void display_squares(void);						//方格
void display_circle(void);						//圆形

void display_TCS(void);								//贪吃蛇坐标20*20
void printff(int hang,char tstr[]);		//根据字符串TSTR改文字库WZK
void display_ZF(void);								//字符显示模式
void clear_TCS(void);									//贪吃蛇清除
void clear_WZ(void);									//文字清除

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);




int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
	
	reset_TFT();
	ini_ILI9341();
	
	strcpy(tstr,"HELLO WORLD");
	printff(5,tstr);
	strcpy(tstr,"I AM LI TIANLING    ");
	printff(6,tstr);	
	
  while (1)
 {
	 display_TCS();
	 HAL_Delay(6000);
	 display_ZF();
	 HAL_Delay(6000);
   clear_TCS();
   clear_WZ();
 }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB3
                           PB4 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}



void comm_out(unsigned char m)
{
	GPIOB->ODR=0x0A;
	GPIOA->ODR=m;
//	HAL_Delay(1);
	GPIOB->ODR=0x1E;
}

void data_out(unsigned char b)
{
	GPIOB->ODR=0x0B;
	GPIOA->ODR=b;
//	HAL_Delay(1);
	GPIOB->ODR=0x1E;
}

void write_data(unsigned char i,unsigned char j)
{
	GPIOB->ODR=0x0F;
	GPIOA->ODR=i;
	GPIOB->ODR=0x0B;
//	HAL_Delay(1);
	GPIOB->ODR=0x0F;
//	HAL_Delay(1);
	GPIOA->ODR=j;
	GPIOB->ODR=0x0B;
//	HAL_Delay(1);
	GPIOB->ODR=0x1F;
}

void reset_TFT()
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1); //RST=1
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0); //RST=0
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1); //RST=1
	HAL_Delay(5);
}


void ini_ILI9341()
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1); //RST=1
  HAL_Delay(20);
 	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0); //RST=0
  HAL_Delay(40);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1); //RST=1
  HAL_Delay(40); 

	//************* Start Initial Sequence **********// 
  comm_out(0xCF);          //power control,address is 0xCF
  data_out(0x00);          //parameter #1
  data_out(0xC1);          //parameter #2
  data_out(0X30);          //parameter #3
 
  comm_out(0xED);          //Power on sequence control,address is 0xED
  data_out(0x64);          //parameter #1
  data_out(0x03);          //parameter #2
  data_out(0X12);          //parameter #3
  data_out(0X81);          //parameter #4
 
  comm_out(0xE8);          //Driver timing control A, address is 0xE8
  data_out(0x85);          //parameter #1
  data_out(0x10);          //parameter #2
  data_out(0x7A);          //parameter #3
 
  comm_out(0xCB);          //Power control A, address is 0xCB
  data_out(0x39);          //parameter #1
  data_out(0x2C);          //parameter #2
  data_out(0x00);          //parameter #3
  data_out(0x34);          //parameter #4
  data_out(0x02);          //parameter #5
 
  comm_out(0xF7);          //Pump ratio control,address is 0xF7
  data_out(0x20);          //parameter #1
 
  comm_out(0xEA);          //Driver timing control B,address is 0xEA
  data_out(0x00);          //parameter #1
  data_out(0x00);          //parameter #2
 
  comm_out(0xC0);          //Power control 1,address is 0xC0
  data_out(0x21);          //parameter #1,VRH[5:0] 
 
  comm_out(0xC1);          //Power control 2,address is 0xC1 
  data_out(0x13);          //parameter #1,SAP[2:0];BT[3:0] 
 
  comm_out(0xC5);          //VCM control 1,address is 0xC5
  data_out(0x3F);          //parameter #1
  data_out(0x3C);          //parameter #2
 
  comm_out(0xC7);          //VCM control 2,address is 0xC7 
  data_out(0XB3);          //parameter #1
 
  comm_out(0x36);          //Memory Access Control, address is 0x36
  data_out(0x08);          //parameter #1
 
  comm_out(0x3A);          //Pixel Format Set,address is 0x3A
  data_out(0x55);          //parameter #1

  comm_out(0xB1);          //Frame Rate Control,address is 0xB1
  data_out(0x00);          //parameter #1
  data_out(0x1B);          //parameter #2
 
  comm_out(0xB6);          //Display Function Control,address is 0xB6 
  data_out(0x0A);          //parameter #1
  data_out(0xA2);          //parameter #2

  comm_out(0xF6);          //Interface Control,address is 0xF6
  data_out(0x01);          //parameter #1
  data_out(0x30);          //parameter #2
 
  comm_out(0xF2);          //Enable 3 gamma,address is 0xF2
  data_out(0x00);          //parameter #1,3Gamma Function Disable 
 
  comm_out(0x26);          //Gamma Set,address is 0x26
  data_out(0x01);          //Gamma curve selected 
 
  comm_out(0xE0);          //Positive Gamma Correction,address is 0xE0
  data_out(0x0F);          //parameter #1
  data_out(0x24);          //parameter #2
  data_out(0x21);          //parameter #3
  data_out(0x0C);          //parameter #4
  data_out(0x0F);          //parameter #5
  data_out(0x09);          //parameter #6
  data_out(0x4D);          //parameter #7
  data_out(0XB8);          //parameter #8
  data_out(0x3C);          //parameter #9
  data_out(0x0A);          //parameter #10
  data_out(0x13);          //parameter #11
  data_out(0x04);          //parameter #12
  data_out(0x0A);          //parameter #13
  data_out(0x05);          //parameter #14
  data_out(0x00);          //parameter #15
 
  comm_out(0XE1);          //Negative Gamma Correction,address is 0xE1
  data_out(0x00);          //parameter #1
  data_out(0x1B);          //parameter #2
  data_out(0x1E);          //parameter #3
  data_out(0x03);          //parameter #4
  data_out(0x10);          //parameter #5
  data_out(0x06);          //parameter #6
  data_out(0x32);          //parameter #7
  data_out(0x47);          //parameter #8
  data_out(0x43);          //parameter #9
  data_out(0x05);          //parameter #10
  data_out(0x0C);          //parameter #11
  data_out(0x0B);          //parameter #12
  data_out(0x35);          //parameter #13
  data_out(0x3A);          //parameter #14
  data_out(0x0F);          //parameter #15
 
  comm_out(0x11);          //Sleep Out, address is 0x11 
  HAL_Delay(120); 
  comm_out(0x29);          //Display on,address is 0x29 
}



void display_horizontal_line(void)	//横条纹
{
	unsigned int j;
	unsigned int i;
	comm_out(0x2A);
	data_out(0x00);
	data_out(0x00);
	data_out(0x00);
	data_out(0xEF);

	comm_out(0x2B);
	data_out(0x00);
	data_out(0x00);
	data_out(0x01);
	data_out(0x3F);

	comm_out(0x2C);
	for(i=0;i<80;i++)
		for(j=0;j<240;j++)
			write_data(0x00,0x1F);
	for(i=0;i<80;i++)
		for(j=0;j<240;j++)
			write_data(0xFF,0xFF);
	for(i=0;i<80;i++)
		for(j=0;j<240;j++)
			write_data(0xF8,0x00);
	for(i=0;i<80;i++)
		for(j=0;j<240;j++)
			write_data(0x07,0xE0);
}


void display_vertical_line(void)	//竖条纹
{
	unsigned int j;
	unsigned int i;
  comm_out(0x2A); 
  data_out(0x00); 
  data_out(0x00); 
  data_out(0x00); 
  data_out(0xef);         
  comm_out(0x2b); 
  data_out(0x00); 
  data_out(0x00); 
  data_out(0x01); 
  data_out(0x3f); 
  comm_out(0x2C);  
	for(i=0;i<320;i++)
	{
	 for(j=0;j<60;j++)
	   write_data(0x00,0xff);  //color,80*240 
	 for(j=0;j<60;j++)
	    write_data(0x0f,0xff); //color,80*240
	 for(j=0;j<60;j++)
	    write_data(0x48,0x00); //color ,80*320
	  for(j=0;j<60;j++)
	    write_data(0xa1,0xe0); //color, 80*320
	}
}


void display_squares(void)  //方格
{
	unsigned int j,k;
	unsigned int i;
  comm_out(0x2A); 
  data_out(0x00); 
  data_out(0x00); 
  data_out(0x00); 
  data_out(0xef);         
  comm_out(0x2b); 
  data_out(0x00); 
  data_out(0x00); 
  data_out(0x01); 
  data_out(0x3f); 
  comm_out(0x2C);
  for(k=0;k<4;k++)
   {  
	   for(i=0;i<80;i++)
	    {
	      for(j=0;j<60;j++)
	        write_data(0x00+k*60,0x00);  //color,80*240 
	      for(j=0;j<60;j++)
	        write_data(0x1f+k*20,0xff); //color,80*240
	      for(j=0;j<60;j++)
	        write_data(0x2f+k*50,0x00); //color ,80*320
	      for(j=0;j<60;j++)
	        write_data(0x3f+k*20,0xe0); //color, 80*320
	    }
	  }
}


void display_circle(void)		//圆形
{
	unsigned int j;
	unsigned int i,m,c;
	unsigned int k,l;
	m=10;
 for(c=0;c<10;c++)
 {
  comm_out(0x2A); 
  data_out(0x00); 
  data_out(0x00); 
	data_out(0x00); 
  data_out(0xef);         
  comm_out(0x2b); 
  data_out(0x00); 
  data_out(0x00); 
  data_out(0x01); 
  data_out(0x3f); 
  comm_out(0x2C);
	
	for(i=0;i<320;i++)
	 {
	   for(j=0;j<240;j++)
		  {
		   if(i<160 && j<120) 
			 {    
			  k=160-i;
        l=120-j;
       }
       else if(i>160&& j<120)
       {
        k=i-160;
        l=120-j;
       }
       else if(i<160 && j>120)
		   {
        k=160-i;
        l=j-120;
       }
		   else
			 {
        k=i-160;
        l=j-120;
       }	
			 if((k*k+l*l)<=m*m)
	        write_data(0xf8,0x00);  //color,80*240 
			 else
				  write_data(0x07,0xe0);
		 }
	 }
	 HAL_Delay(100);
	 m+=10;
 }
}







void display_TCS(void)	//贪吃蛇显示模式
{
	unsigned int H,h; //H L 块坐标
	unsigned int L,l;	//h l 点坐标
  comm_out(0x2A); 
  data_out(0x00); 
  data_out(0x00); 
  data_out(0x00); 
  data_out(0xef);         
  comm_out(0x2b); 
  data_out(0x00); 
  data_out(0x00); 
  data_out(0x01); 
  data_out(0x3f); 
  comm_out(0x2C);
  for(H=0;H<20;H++)  		 	//20*16=320  
		for(h=0;h<16;h++)
			for(L=0;L<20;L++)		//20*12=240
				for(l=0;l<12;l++)
				{
					if(TCSK[H][L]!=0)
						write_data(0x00+TCSK[H][L]*20,0x00+TCSK[H][L]*20);
					else
					  write_data(0x00,0x00);
				}
}

void printff(int hang,char tstr[])			//根据字符串TSTR改文字库WZK
{
	//i循环辅助变量  （0-19）某一列
	for(int l=0;l<19;l++)
	{
		if(tstr[l]==' ')	    WZK[hang][l]=0;
		else if(tstr[l]=='A') WZK[hang][l]=1;
		else if(tstr[l]=='B') WZK[hang][l]=2;
		else if(tstr[l]=='C') WZK[hang][l]=3;
		else if(tstr[l]=='D') WZK[hang][l]=4;
		else if(tstr[l]=='E') WZK[hang][l]=5;
		else if(tstr[l]=='F') WZK[hang][l]=6;
		else if(tstr[l]=='G') WZK[hang][l]=7;
		else if(tstr[l]=='H') WZK[hang][l]=8;
		else if(tstr[l]=='I') WZK[hang][l]=9;
		else if(tstr[l]=='J') WZK[hang][l]=10;
		else if(tstr[l]=='K') WZK[hang][l]=11;
		else if(tstr[l]=='L') WZK[hang][l]=12;
		else if(tstr[l]=='M') WZK[hang][l]=13;
		else if(tstr[l]=='N') WZK[hang][l]=14;
		else if(tstr[l]=='O') WZK[hang][l]=15;
		else if(tstr[l]=='P') WZK[hang][l]=16;
		else if(tstr[l]=='Q') WZK[hang][l]=17;
		else if(tstr[l]=='R') WZK[hang][l]=18;
		else if(tstr[l]=='S') WZK[hang][l]=19;
		else if(tstr[l]=='T') WZK[hang][l]=20;
		else if(tstr[l]=='U') WZK[hang][l]=21;
		else if(tstr[l]=='V') WZK[hang][l]=22;
		else if(tstr[l]=='W') WZK[hang][l]=23;
		else if(tstr[l]=='X') WZK[hang][l]=24;
		else if(tstr[l]=='Y') WZK[hang][l]=25;
		else if(tstr[l]=='Z') WZK[hang][l]=26;
		else ;
	}
}

void display_ZF(void) 	//字符显示模式
{
	unsigned int H,h; //H L 块坐标
	unsigned int L,l;	//h l 点坐标
  comm_out(0x2A); 
  data_out(0x00); 
  data_out(0x00); 
  data_out(0x00); 
  data_out(0xef);         
  comm_out(0x2b); 
  data_out(0x00); 
  data_out(0x00); 
  data_out(0x01); 
  data_out(0x3f); 
  comm_out(0x2C);
  for(H=0;H<20;H++)  		 	//20*16=320  
		for(h=0;h<16;h++)
			for(L=0;L<20;L++)		//20*12=240
				for(l=0;l<12;l++)
				{
					if(WZK[H][L]<27) //满足显示要求
					{
						if(ZFK[WZK[H][L]][h][l]==1)
							write_data(0x00,0xFF);
						else
							write_data(0x00,0x00);
					}
					else //显示黑
						write_data(0x00,0x00);
				}
}


void clear_TCS(void)  //贪吃蛇清除
{
	for(int i=0;i<20;i++)
		for(int j=0;j<20;j++)
			TCSK[i][j]=0;
}

void clear_WZ(void)	//文字清除
{
	for(int i=0;i<20;i++)
		for(int j=0;j<20;j++)
			WZK[i][j]=0;	
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
