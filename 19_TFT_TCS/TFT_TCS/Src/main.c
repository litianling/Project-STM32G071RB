#include "main.h"
#include "stdlib.h"
#include "string.h"
#define u8  unsigned char
#define u16 unsigned int


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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	},
	
	{		//		A
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
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


int WZK[20][20]=  //文字模式显存 20行 20列 （数值不同字符不同）
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

int TCSK[20][20]=  //贪吃模式显存 20行 20列 （数值不同颜色不同）
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

char tstr[20]; //字符串显示缓存数组
int hang=0;    //指定行数--定位


void comm_out(unsigned char m);											//输出命令
void data_out(unsigned char b);											//输出数据
void write_data(unsigned char i,unsigned char j);		//TFT写颜色

void reset_TFT(void);				//TFT彩屏初始化
void ini_ILI9341(void);			//控制器初始化

void printff(int hang,char tstr[]);		//根据字符串TSTR改文字模式显存
void display_TCS(void);								//按照贪吃蛇模式显示
void display_ZF(void);								//按照字符模式显示
void clear_TCS(void);									//贪吃蛇显存清除
void clear_WZ(void);									//文字显存清除


const int flg[4][2]={{1,0},{0,1},{0,-1},{-1,0}};//下右左上坐标变化规律 
int n=20,m=20;  //n和m是蛇的活动范围20行20列+边框=可视化窗口大小
struct xcw{int x,y;}tang[5][15],foodd[2];//结构体tan存储每条蛇的坐标  结构体foodd记录两个食物坐标 
int tot[5];     //tot[0123]是四条蛇的长度 
int f[5];       //存储蛇的运行状态0123下右左上   搭配flg使用 
int score;      //得分 
int food;       //食物个数
int ms=0;       //初始--模式选择
int ans_len=1e9; 
int vis[20][20];//记录食物存在点的矩阵  例如(foddd[0].x,foddd[0].y)有食物则vis[foddd[0].x][foddd[0].y]=1 


int  stop=0;				 //暂停请求
void  mods(void);         //对应模式小蛇初始化
void draw(void);         //初始化贪吃蛇显存的边框数据
void rand_food(void);    //没有食物时随机投喂
void  change(int t);  //没有按键按下蛇的运行
int check(int x,int y);         //检验某一个点
void machine(int t,int x,int y); //机器人寻路 
void result(int t);              //积分够了-胜利
void fnd(int t,int x,int y);     //撞到障碍物--失败
int  ads(int x);                 //取绝对值
int  other(int x);               //03交换、12交换
int get_food(int x,int y,int xxx,int yyy); //辅助机器人找寻食物

//****************************************************************

ITStatus EXTI_GetITStatus(uint32_t EXTI_Line) //判断中断管脚
{
    ITStatus bitstatus = RESET; //初始位状态0
    uint32_t enablestatus = 0;  //初始使能状态0
    assert_param(IS_GET_EXTI_LINE(EXTI_Line));
    enablestatus =  EXTI->IMR1 & EXTI_Line;  
    if (((EXTI->FPR1 & EXTI_Line) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET)) 
		      bitstatus = SET;
    else
        bitstatus = RESET;
    return bitstatus;
}

void EXTI_ClearITPendingBit(uint32_t EXTI_Line) //释放对应管脚标志位
{
  assert_param(IS_EXTI_LINE(EXTI_Line));
  EXTI->FPR1 = EXTI_Line;
}

//*****************************************************************

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

//*****************************************************************


int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  reset_TFT();
	ini_ILI9341();
	
	
    while (1)
  {
		while(ms==0)
		{
			strcpy(tstr,"     SELECT MOOD        ");
			printff(2,tstr);
			strcpy(tstr," SINGLE MDDE           ");
			printff(4,tstr);			
			strcpy(tstr," DOUBLE COOPERATION    ");
			printff(5,tstr);
			strcpy(tstr," PLAYER AGAINST        ");
			printff(6,tstr);
			strcpy(tstr," ROBOTS AGAINST         ");
			printff(7,tstr);
			strcpy(tstr," PLAYER VS ROBOT       ");
			printff(8,tstr);
			strcpy(tstr," DOUBLE CHALLANGE      ");
			printff(9,tstr);
			strcpy(tstr,"   PUSH USER STOP      ");
			printff(12,tstr);			
			
			display_ZF();
			HAL_Delay(100);
		}
		
		while(ms==1)  //1单人模式
		{
			while(stop==1)
				HAL_Delay(100);
			display_TCS();	//TFT显示
			rand_food();
			if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_4)==0&&f[0]^0)       //左右上下
				f[0]=3;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_5)==0&&f[0]^3)
				f[0]=0;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6)==0&&f[0]^1)
				f[0]=2;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_8)==0&&f[0]^2)
				f[0]=1;
			else ;
			change(0);
		}
		
		while(ms==2)	//2双人合作
		{
			while(stop==1)
				HAL_Delay(100);
			display_TCS();	//TFT显示
			rand_food();
			if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_0)==0&&f[0]^0) // 上
				f[0]=3;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_1)==0&&f[0]^3) //下
				f[0]=0;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2)==0&&f[0]^1) //左
				f[0]=2;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_3)==0&&f[0]^2) //右
				f[0]=1;
			else ;
			if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_4)==0&&f[1]^0) // 上
				f[1]=3;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_5)==0&&f[1]^3) //下
				f[1]=0;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6)==0&&f[1]^1) //左
				f[1]=2;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_8)==0&&f[1]^2) //右
				f[1]=1;
			else ;
			change(0);
			change(1);
		}
		
		while(ms==3)	//3双人对抗
		{
			while(stop==1)
				HAL_Delay(100);
			display_TCS();	//TFT显示
			rand_food();
			if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_0)==0&&f[0]^0) // 上
				f[0]=3;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_1)==0&&f[0]^3) //下
				f[0]=0;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2)==0&&f[0]^1) //左
				f[0]=2;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_3)==0&&f[0]^2) //右
				f[0]=1;
			else ;
			if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_4)==0&&f[1]^0) // 上
				f[1]=3;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_5)==0&&f[1]^3) //下
				f[1]=0;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6)==0&&f[1]^1) //左
				f[1]=2;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_8)==0&&f[1]^2) //右
				f[1]=1;
			else ;
			change(0);
			change(1);
		}
		
		while(ms==4)	//4机机对抗抢分
		{
			while(stop==1)
				HAL_Delay(100);
			display_TCS();	//TFT显示
			rand_food();
			change(2),change(3);
		}
		
		while(ms==5)	//5人机对抗抢分
		{
			while(stop==1)
				HAL_Delay(100);
			display_TCS();	//TFT显示
			rand_food();
			if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_4)==0&&f[0]^0) // 上
				f[0]=3;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_5)==0&&f[0]^3) //下
				f[0]=0;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6)==0&&f[0]^1) //左
				f[0]=2;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_8)==0&&f[0]^2) //右
				f[0]=1;
			else ;
			change(0);
			change(2);
		}
		
		while(ms==6)	//6双人对抗抢分
		{
			while(stop==1)
				HAL_Delay(100);
			display_TCS();	//TFT显示
			rand_food();
			if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_0)==0&&f[0]^0) // 上
				f[0]=3;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_1)==0&&f[0]^3) //下
				f[0]=0;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2)==0&&f[0]^1) //左
				f[0]=2;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_3)==0&&f[0]^2) //右
				f[0]=1;
			else ;
			if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_4)==0&&f[1]^0) // 上
				f[1]=3;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_5)==0&&f[1]^3) //下
				f[1]=0;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6)==0&&f[1]^1) //左
				f[1]=2;
			else if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_8)==0&&f[1]^2) //右
				f[1]=1;
			else ;
			change(0);
			change(1);
		}
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC11 PC13 PC6 PC7
                           PC8 PC9 PC10 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

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

  /*Configure GPIO pins : PD8 PD0 PD1 PD2
                           PD3 PD4 PD5 PD6 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 4 */



void comm_out(unsigned char m) //输出命令
{
	GPIOB->ODR=0x0A;
	GPIOA->ODR=m;
	GPIOB->ODR=0x1E;
}

void data_out(unsigned char b) //输出数据
{
	GPIOB->ODR=0x0B;
	GPIOA->ODR=b;
	GPIOB->ODR=0x1E;
}

void write_data(unsigned char i,unsigned char j) //TFT写颜色
{
	GPIOB->ODR=0x0F;
	GPIOA->ODR=i;
	GPIOB->ODR=0x0B;
	GPIOB->ODR=0x0F;
	GPIOA->ODR=j;
	GPIOB->ODR=0x0B;
	GPIOB->ODR=0x1F;
}

void reset_TFT() //TFT彩屏复位
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1); //RST=1
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0); //RST=0
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1); //RST=1
	HAL_Delay(5);
}

void ini_ILI9341() //彩屏控制器初始化
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


//**********************************************************

void printff(int hang,char tstr[])  //根据字符串TSTR改文字模式显存
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

void display_TCS(void)	//按照贪吃蛇模式显示
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


void display_ZF(void) 	//按照字符模式显示
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


void clear_TCS(void)  //贪吃蛇显存清除
{
	for(int i=0;i<20;i++)
		for(int j=0;j<20;j++)
			TCSK[i][j]=0;
}

void clear_WZ(void)	//文字显存清除
{
	for(int i=0;i<20;i++)
		for(int j=0;j<20;j++)
			WZK[i][j]=0;	
}

//*****************************************

void EXTI4_15_IRQHandler(void)   // 中断控制----改变游戏模式以及暂停
{
  if (EXTI_GetITStatus(0x0040) != 0x00)  // 0x0040==EXTI_PIN_6
  {
		EXTI_ClearITPendingBit(0x0040); 
		ms=1;
  }
	else if (EXTI_GetITStatus(0x0080) != 0x00)  // 0x0080==EXTI_PIN_7
  {
		EXTI_ClearITPendingBit(0x0080); 
		ms=2;
  }
	else if (EXTI_GetITStatus(0x0100) != 0x00)  // 0x0100==EXTI_PIN_8
  {
		EXTI_ClearITPendingBit(0x0100); 
		ms=3;
  }
	else if (EXTI_GetITStatus(0x0200) != 0x00)  // 0x0200==EXTI_PIN_9
  {
		EXTI_ClearITPendingBit(0x0200); 
		ms=4;
  }
	else if (EXTI_GetITStatus(0x0400) != 0x00)  // 0x0400==EXTI_PIN_10
  {
		EXTI_ClearITPendingBit(0x0400); 
		ms=5;
  }
	else if (EXTI_GetITStatus(0x0800) != 0x00)  // 0x0800==EXTI_PIN_11
  {
		EXTI_ClearITPendingBit(0x0800); 
		ms=6;
  }
	else ;
	
	if (EXTI_GetITStatus(0x2000) != 0x00)  // 0x2000==GPIO_PIN_13
  {
		EXTI_ClearITPendingBit(0x2000);  //Clear interrupt flag bit
		if(stop==1) stop=0;
		else stop=1;
  }
	else
	{
		clear_WZ();
		clear_TCS();
		score=0;
		food=0;
		draw();
		mods();    //对应模式小蛇初始化
	}
}




void mods(void)  //对应模式小蛇初始化 
{
	if(ms!=4)											                                   
	{                                        		                            		                            		                     
		tang[0][1].x=1;							
		tang[0][1].y=3;
		tang[0][2].x=1;
		tang[0][2].y=2;
		tang[0][tot[0]=3].x=1;
		tang[0][tot[0]=3].y=1;
		f[0]=1;   //玩家1初始方向  向右 
		for(int i=1;i<=tot[0];i++)
			TCSK[tang[0][i].x][tang[0][i].y]=4;
	}
	if(ms==2||ms==3||ms==6)
	{
		tang[1][1].x=n-2;
		tang[1][1].y=m-4;
		tang[1][2].x=n-2;
		tang[1][2].y=m-3;
		tang[1][tot[1]=3].x=n-2;
		tang[1][tot[1]=3].y=m-2;
		f[1]=2;    //玩家2初始方向  向左
		for(int i=1;i<=tot[1];i++)
			TCSK[tang[1][i].x][tang[1][i].y]=5;
	}
	if(ms==5||ms==4)
	{	
		tang[2][1].x=n-2;
		tang[2][1].y=m-4;
		tang[2][2].x=n-2;
		tang[2][2].y=m-3;
		tang[2][tot[2]=3].x=n-2;
		tang[2][tot[2]=3].y=m-2;
		f[2]=2;    //电脑1初始方向  向左
		for(int i=1;i<=tot[2];i++)
			TCSK[tang[2][i].x][tang[2][i].y]=6;
	}
	if(ms==4)
	{
		tang[3][1].x=1;
		tang[3][1].y=3;
		tang[3][2].x=1;
		tang[3][2].y=2;
		tang[3][tot[3]=3].x=1;
		tang[3][tot[3]=3].y=1;
		f[3]=1;   //电脑2初始方向  向右 
		for(int i=1;i<=tot[3];i++)
			TCSK[tang[3][i].x][tang[3][i].y]=7;
	}
}


void draw(void)  //初始化贪吃蛇显存的边框数据 
{
	for(int i=0;i<n;i++)
	{
		TCSK[i][0]=1; 
		TCSK[i][m-1]=1;
	}
	for(int i=0;i<m;i++) 
	{
		TCSK[0][i]=1;
		TCSK[n-1][i]=1;
	}
}

void rand_food(void)  //没有食物时随机投喂
{
    if(!vis[foodd[0].x][foodd[0].y]) //如果0号食物不见了 
	{	
		int x=(rand()%(n-3))+2,y=(rand()%(m-3))+2; //随机产生xy坐标y为偶数 
		while(!check(x,y)) 
			x=(rand()%(n-3))+2,y=(rand()%(m-3))+2; //检验随机投喂的点，是否需要重新投喂 
		TCSK[x][y]=10;
	    food++;
		vis[x][y]=1;
		foodd[0].x=x;
		foodd[0].y=y;
	}
	if(!vis[foodd[1].x][foodd[1].y])  //第二个食物--同上 
	{
		int x=rand()%n,y=rand()%m;
		while(!check(x,y)) 
			x=rand()%n,y=(rand()%m);
		TCSK[x][y]=10;
		food++;
		vis[x][y]=1;
		foodd[1].x=x;
		foodd[1].y=y;
	}
}

void change(int t)  //没有按键按下蛇的运行--第t条蛇 
{
	int x=tang[t][1].x,y=tang[t][1].y;    //x和y是蛇头位置的xy 
	if(t==2||t==3)                      //2号和3号蛇是电脑
		machine(t,x,y);                   //机器人寻路
	x+=flg[f[t]][0],y+=flg[f[t]][1];    //蛇头(x,y)按规律变化 
	for(int i=tot[t];i;i--)             //蛇的身子位置数据库刷新 
	   {
	        tang[t][i+1]=tang[t][i];  
	        TCSK[tang[t][i].x][tang[t][i].y]=t+4; //身子显示刷新  t+4颜色不同
		} 
	TCSK[tang[t][tot[t]+1].x][tang[t][tot[t]+1].y]=0; //原来的蛇尾消失 
	if(vis[x][y])  //如果吃掉一个食物的话 
	{
		vis[x][y]=0,score+=(t==0||t==1),food--;
		if(++tot[t]>=10&&((ms==4)||(ms==5)||(ms==6)))  //有一方吃够分 
			result(t);
		TCSK[tang[t][tot[t]].x][tang[t][tot[t]].y]=t+4; //尾巴处+1 
	}
	fnd(t,x,y);   //一方撞墙撞蛇则失败   
	tang[t][1].x=x;    //把蛇头位置反馈到全局变量中 
	tang[t][1].y=y;
	TCSK[tang[t][1].x][tang[t][1].y]=5;  //新蛇头出现 
}

int check(int x,int y)   //检验某一个点
{
	if(x<1||x>(n-2)||y<1||y>(m-2))  //边界以及边界上外返回0 
		return 0;  
	int t=1;
	if(ms!=4)
	    for(int i=1;i<=tot[0];i++)   //在蛇身上返回0 
	        if(x==tang[0][i].x&&y==tang[0][i].y)
			    {t=0;break;}
	if(ms==2||ms==3||ms==6)
	    for(int i=1;i<=tot[1];i++)
	        if(x==tang[1][i].x&&y==tang[1][i].y)
			    {t=0;break;}
	if(ms==5||ms==4)
		for(int i=1;i<=tot[2];i++)
			if(x==tang[2][i].x&&y==tang[2][i].y)
					{t=0;break;}
	if(ms==4)
		for(int i=1;i<=tot[3];i++)
			if(x==tang[3][i].x&&y==tang[3][i].y)
					{t=0;break;}
	return t;    //都不在这些点返回1 
}

void machine(int t,int x,int y)  //机器人寻路
{ 
	int foodid,minn=1e9,newf=f[t];//最小距离初始值很大
	if((get_food(x,y,foodd[0].x,foodd[0].y)<=get_food(x,y,foodd[1].x,foodd[1].y)&&vis[foodd[0].x][foodd[0].y])||!vis[foodd[1].x][foodd[1].y]) 
		foodid=0;
	else 
		foodid=1;
	for(int i=0;i<4;i++)
		if(f[t]^other(i))//确保不是身后
		{
			if(check(x+flg[i][0],y+flg[i][1])) //确保前方不是障碍
			{	
				int now=get_food(x+flg[i][0],y+flg[i][1],foodd[foodid].x,foodd[foodid].y); //计算新的距离————下一方向下一时刻距离
				if(now<minn) 
					newf=i,minn=now; 
			}
		}
	f[t]=newf;
}

void result(int t)  //积分够了--胜利 
{
	if(ms==5)           //人机对抗-抢分
		if(t==0)
		{
			strcpy(tstr,"         WIN         ");
			printff(10,tstr);
			display_ZF();
		}
		else
		{
			strcpy(tstr,"         LOSE         ");
			printff(10,tstr);
			display_ZF();
		}
	else if(ms==4)      //机机对抗-抢分
	  if(t==2)
		{
			strcpy(tstr," ROBOT ONE WIN ENOUGH      ");
			printff(10,tstr);
			display_ZF();
		}		
		else
		{
			strcpy(tstr," ROBOT TWO WIN ENOUGH      ");
			printff(10,tstr);
			display_ZF();
		}
	else if(ms==6)      //对抗模式-抢分
	    if(t==1) 
		{
			strcpy(tstr," PLAYER ONE WIN ENOUGH      ");
			printff(10,tstr);
			display_ZF();
		}
		  else 
		{
			strcpy(tstr," PLAYER TWO WIN ENOUGH   ");
			printff(10,tstr);
			display_ZF();
		}
	else ;
	while(1); //结束
}

void fnd(int t,int x,int y)  //撞到障碍物--失败
{
	if(check(x,y)) return;   //check(x,y)为0则相撞 
	if(ms==4)        //机机对抗-抢分 
	    if(t==3)
		{
			strcpy(tstr,"   ROBOT TWO DIE     ");
			printff(10,tstr);
			display_ZF();
		}
	    else
		{
			strcpy(tstr,"   ROBOT ONE DIE     ");
			printff(10,tstr);
			display_ZF();
		}
	else if(ms==3||ms==6)   //对抗模式  对抗模式-抢分 
	    if(t==1) 
		{
			strcpy(tstr,"   PLAYER TWO DIE     ");
			printff(10,tstr);
			display_ZF();
		}
		else 
		{
			strcpy(tstr,"   PLAYER ONE WIN E     ");
			printff(10,tstr);
			display_ZF();
		}
	else
	{
		if(t==2) 
		{
			strcpy(tstr,"      WIN               ");
			printff(10,tstr);
			display_ZF();
		}
		else 
		{
			strcpy(tstr,"      LOSE              ");
			printff(10,tstr);
			display_ZF();
		}
		//printf("\n 玩家分数:%d\n",score);
		score=0;
	}
	while(1);  //结束 
}

int ads(int x)  //取绝对值 
{
    return x<0?-x:x; //x是否<0,如果x<0的话就执行:前面的语句，如果x不小于0的话就执行:后面的语句 
}

int other(int x)  //03交换、12交换  对立方向
{
	if     (x==0) return 3;
	else if(x==1) return 2;
	else if(x==2) return 1;
	else          return 0;
}

int get_food(int x,int y,int xxx,int yyy)  //辅助机器人找寻食物 
{
    return ads(x-xxx)+ads(y-yyy);
}



/* USER CODE END 4 */

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
