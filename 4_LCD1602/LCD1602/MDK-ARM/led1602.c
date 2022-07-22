#include "led1602.h"

void delay(void)
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}	
void lcdwait()
{
	LCD1602_DB=0xFF;
	delay();
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET); //	LCD1602_RS=0;
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);  //LCD1602_RW=1;
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);// LCD1602_E=1;
	while(LCD1602_DB & 0x80);
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET);// LCD1602_E=0;
}

void lcdwritecmd(unsigned char cmd)
{
	lcdwait();
	delay();
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);// LCD1602_RS=0;
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET); // LCD1602_RW=0;
	LCD1602_DB=cmd;
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);// LCD1602_E=1;
	delay();
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET);//	LCD1602_E=0;
}

void lcdwritedata(unsigned char dat)
{
	lcdwait();
  delay();
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);//	LCD1602_RS=1;
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);// LCD1602_RW=0;
	LCD1602_DB=dat;
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);// LCD1602_E=1;
	delay();
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET);// LCD1602_E=0;
}

void lcdinit()
{
	lcdwritecmd(0x38);
	lcdwritecmd(0x0c);
	lcdwritecmd(0x06);
	lcdwritecmd(0x01);
}

void lcdsetcursor(unsigned char x, unsigned char y)
{
	unsigned char address;
	if(y==0)
		address=0x00+x;
	else
		address=0x40+x;
	lcdwritecmd(address|0x80);
}

void lcdshowstr(unsigned char x, unsigned char y,
	              unsigned char *str)
{
	lcdsetcursor(x,y);
	while((*str)!='\0') 
	{
		 lcdwritedata(*str);
		 str++;
	}
}				

void set_P0_mode(u8 a,u8 b)
{
	 P0M0=a;
	 P0M1=b;
}
void set_P2_mode(u8 a,u8 b)
{
   P2M0=a;
	 P2M1=b;
}