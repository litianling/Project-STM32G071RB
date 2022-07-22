#include "TFT32.h"
#include "PICTURE.h"

void set_p0_drive_mode(u8 a, u8 b)
{
	P0M1=a;
	P0M0=b;
}
void set_p2_drive_mode(u8 a, u8 b)
{
	P2M1=a;
	P2M0=b;
}

void set_spi_level(u8 a, u8 b)
{
	 IP2=a;
	 IP2H=b;
}

void set_spi_pin(u8 a)
{
   P_SW1=a;
}

void clear_spi_status(void)
{
	SPSTAT=0xc0;
}

void set_spi_mode(u8 a)
{
	 SPCTL=a;   
}

void write_spi_data(u8 a)
{
	SPDAT=a;
}

u8 read_spi_data(void)
{
	return(SPDAT);
}


void Delayms(u16 ms)    //delay function  
{
	u16 a,b;
	for(b=0;b<ms;b++)
	  for(a=0;a<250;a++)
	  {
		  ;
		  ;
    }
}

void reset_TFT()
{
	 TFT32_RST=1;
   Delayms(60);
   TFT32_RST=0;
   Delayms(60);
   TFT32_RST=1;
   Delayms(90);
}
void write_data(u8 i, u8 j)   
{
	TFT32_RS=1;
	TFT32_CS=0;
	TFT32_WR=1;
	TFT32_RD=1;
	TFT32_DATA=i;
	TFT32_WR=0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	TFT32_WR=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	TFT32_DATA=j;
	TFT32_WR=0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	TFT32_WR=1;
	TFT32_CS=1;
}

void data_out(u8 b)
{
	TFT32_CS=0;
	TFT32_RS=1;
	TFT32_RD=1;
	TFT32_WR=0;
	TFT32_DATA=b;
  _nop_();
	_nop_();
	_nop_();
	_nop_();
	TFT32_WR=1;
	TFT32_RS=0;
	TFT32_RD=1;
	TFT32_CS=1;
}

void comm_out(u8 m)
{
	TFT32_CS=0;
	TFT32_RS=0;
	TFT32_RD=1;
	TFT32_WR=0;
	TFT32_DATA=m;
  _nop_();
	_nop_();
	_nop_();
	TFT32_WR=1;
	TFT32_RS=0;
	TFT32_RD=1;
	TFT32_CS=1;
}

void ini_ILI9341()
{
	TFT32_RST = 1; 
  Delayms(200);             //delay             
  TFT32_RST = 0; 
  Delayms(400);             //delay
  TFT32_RST = 1; 
  Delayms(400);             //delay 
 
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
  Delayms(120);            //Delay 
  comm_out(0x29);          //Display on,address is 0x29 
}


void display_horizontal_line(void)
{ 
	u8 j;
	u16 i;
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
	for(i=0;i<80;i++)
	 for(j=0;j<240;j++)
	   write_data(0x00,0x1f);  //blue color,80*240 
	for(i=0;i<80;i++)
	 for(j=0;j<240;j++)
	    write_data(0xff,0xff); //white color,80*240
	for(i=0;i<80;i++)
	 for(j=0;j<240;j++)
	    write_data(0xf8,0x00); //red color ,80*320
	for(i=0;i<80;i++)
	  for(j=0;j<240;j++)
	    write_data(0x07,0xe0); //green color, 80*320
}

void display_vertical_line(void)
{
	u8 j;
	u16 i;
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

void display_squares(void)
{
	u8 j,k;
	u16 i;
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
void display_circle(void)
{
	u8 j;
	u16 i,m,c;
	u16 k,l;
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
	 Delayms(1000);
	 m+=10;
 }
}
 void displayPIC()
{
	u16 i,j,k;
	u8 m;
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
	for(m=0;m<4;m++)
	{	
		k=0;
		for(i=0;i<80;i++)
		{
			for(j=0;j<240;j++)
			{
				write_data(imagepict[k],imagepict[k+1]);
				k++;
				k++;
			}
		}
	}
}
