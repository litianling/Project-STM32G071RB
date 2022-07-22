#include "TFT32.h"

bit flag=0;
bit busy=1;

u8 x_h=0,x_l=0;
u8 y_h=0,y_l=0;
u16 x=0,y=0;
void spi_interruput() interrupt 9 using 1
{
	clear_spi_status();
	busy=0;
}

void touch_interrtupt() interrupt 2 using 2
{
	 SS=0;
	 write_spi_data(0xD0);
	 while(busy);
	 busy=1;
	 write_spi_data(0x00);
	 while(busy);
	 x_h=read_spi_data();
	 busy=1; 
	 write_spi_data(0x00);
   while(busy);
	 x_l=read_spi_data();
	 x=(x_h<<5)+(x_l>>3);
	 busy=1;
	 write_spi_data(0x90);
	 while(busy);
	 busy=1;
	 write_spi_data(0x00);
	 while(busy);
	 y_h=read_spi_data();
	 busy=1; 
	 write_spi_data(0x00);
   while(busy);
	 y_l=read_spi_data(); 
	 busy=1;
	 SS=1;
	 y=(y_h<<5)+(y_l>>3);
	 
}
 
void main()
{
	 u16 i=0;
	 set_p0_drive_mode(0x00,0x00);
	 set_p2_drive_mode(0x00,0x00);
	 set_spi_level(0x02,0x02);
	 set_spi_pin(0x08);
	 set_spi_mode(0xd3);
   clear_spi_status();
	 SPSTAT=0xc0;
	 int1_falling_edge;
	 enable_int1;
   enable_spi_int;
   gol_int;
	 reset_TFT();
   ini_ILI9341();
	 while(1)
	 {

 		/* if(flag==1)
			  flag=0;
	   display_horizontal_line();
     Delayms(3000);
	   display_vertical_line();
     Delayms(3000);
	   display_squares();
	   Delayms(3000);
	   display_circle();
	   Delayms(3000);
     displayPIC();
	   Delayms(3000);  */
	 }
}