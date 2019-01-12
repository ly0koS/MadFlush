#include "DISP.h"
sbit OE=P1^3;
sbit duan=P1^4;
sbit wei=P1^5;
sbit K1=P2^0;
sbit K2=P2^1;

#define uchar unsigned char
	
uchar disp[8]={16,16,16,16,16,16,16,16};
uchar code sled_bit[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
uchar table[18]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00,0x40};
uchar i=0;
uchar key=99;
uchar temp;
uchar d2;
uchar hide=0xff;
unsigned int timing=0;

extern data uchar  param[9];
extern data uchar k;
extern bit setup;

void display(uchar d1,dt)
{
	d2=dt;
	disp[0]=d1;
	if(d2==0x0f)
	{
		disp[2]=15;
		switch(disp[1])
		{
			case(1):
			{
				disp[3]=17;
				disp[4]=17; 
				disp[5]=17;  
				disp[7]=param[1]%10;
				disp[6]=param[1]/10;
				break;
			}
			case(2):
			{
				disp[3]=17;
				disp[4]=param[3];
				disp[5]=param[4]/100;
				disp[6]=(param[4]/10)%10;
				disp[7]=param[4]%10;
				break;
			}
		}
	}
	else if(d2==0x0a)
	{
		switch(param[6])
		{
			case(1):
			{
				disp[2]=10;
				disp[3]=17;
				disp[4]=17; 
				disp[5]=17;  
				disp[7]=param[2]%10;
				disp[6]=param[2]/10;
				break;
			}
			case(2):
			{
				disp[2]=13;
				disp[3]=17;
				disp[4]=17; 
				disp[5]=17; 
				disp[7]=param[5]%10;
				disp[6]=param[5]/10;
				break;
			}
		}
	}
}


void delay(uchar ti)
{
	uchar t;
	while(ti--)
	{
		for(t=0;t<255;t++);
	}
}

void scan() interrupt 1
{
	uchar t;
	TR0=0;
	TH0=(65536-500)/256;
	TL0=(65536-500)%256;
	if(timing>=70)
	{
		timing=0;
		hide=~hide;
	}
	t=disp[i];
	OE=1;
	if(setup&&(k==i))
	{
		P0=table[t]&hide;
	}
	else
	{
		P0=table[t];
	}
	duan=1;
	duan=0;
	P0=sled_bit[i];
	wei=1;
	wei=0;
	OE=0;
	i++;
	if(i>=8)
	{
		i=0;
	}
	timing=timing+1;
	TR0=1;
}