#ifndef _1602_
#define _1602_
//#include "reg51.h"
#include "intrins.h"
#include "stdio.h"

#define u8  unsigned char
#define u16 unsigned int
#define  EN_GOL_INT  EA=1

//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_****)    //sbit LCD1602_RS=P2^5;
//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_****)    //sbit LCD1602_RW=P2^6;
//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_****)    //sbit LCD1602_E =P2^7;
sfr  LCD1602_DB=0x80;

sfr  P0M1=0x93;
sfr  P0M0=0x94;
sfr  P2M1=0x95;
sfr  P2M0=0x96;

void delay(void);
void set_P0_mode(u8 a,u8 b);
void set_P2_mode(u8 a,u8 b);
void lcdwait();
void lcdwritecmd(unsigned char cmd);
void lcdwritedata(unsigned char dat);
void lcdinit();
void lcdsetcursor(unsigned char x, unsigned char y);
void lcdshowstr(unsigned char x, unsigned char y,
	              unsigned char *str);

#endif