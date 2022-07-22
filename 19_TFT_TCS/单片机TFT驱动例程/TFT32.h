#ifndef _TFT32_
#define _TFT32_
#include "reg51.h"
#include "intrins.h"

#define u16 unsigned int
#define u8 unsigned char
#define enable_int1 IT1=1
#define enable_spi_int IE2=0x02
#define gol_int EA=1
#define int1_falling_edge EX1=1

sbit TFT32_RST=P2^3;
sbit TFT32_CS=P2^4;
sbit TFT32_RS=P2^5;
sbit TFT32_RD=P2^6;
sbit TFT32_WR=P2^7;

sfr  TFT32_DATA=0x80;

sfr  P0M1=0x93;
sfr  P0M0=0x94;
sfr  P2M1=0X95;
sfr  P2M0=0x96;

sfr  SPCTL=0xCE;
sfr  SPDAT=0xCF;
sfr  SPSTAT=0xCD;
sfr  P_SW1=0xA2;

sfr  IPH=0xB7;
sfr  IP2=0xB5;
sfr  IP2H=0xB6;

sfr P7=0xf8;
sfr IE2=0xAF;
sbit SS=P7^0;
sfr P_SW2=0xba;

void set_p0_drive_mode(u8 a, u8 b);
void set_p2_drive_mode(u8 a, u8 b);
void set_spi_level(u8 a, u8 b);
void set_spi_pin(u8 a);
void clear_spi_status(void);
void set_spi_mode(u8 a);
void write_spi_data(u8 a);
u8 read_spi_data(void);
void Delayms(u16 ms);
void reset_TFT();
void ini_ILI9341();
void write_regCOM(u8 com1,u8 com2);
void write_DAT(u8 dat1,u8 dat2);
void display_eprom(u8 p);
void displayPIC();
void display_horizontal_line(void);
void display_vertical_line(void);
void display_squares(void);
void display_circle(void);
#endif