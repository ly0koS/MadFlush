#include "IIC.h"
#include "Func.h"
#include "DISP.h"

#define uchar unsigned char
#define uint 	unsigned int

sbit over=P1^0;
sbit key=P2^0;

data uchar param[2] _at_ 0x20;
data da;
unsigned long result;
uchar k;
data uchar flag _at_ 0x30;

extern uchar disp[8];
extern uchar i;
extern uint count;

void main()
{
	EA=1;
	EX0=1;
	ET0=1;
	IT1=0;
	TMOD|=0x01;
	TH0=(65536-500)/256;
	TL0=(65536-500)%256;
	TR0=1;
	flag=0xff;
	DAC();
	disDAC();
	write24c02();
	while(1)
	{
		if(flag==0xff)
		{
			DAC();
			disDAC();
		}
		if(result>=250)
			over=0;
		else
			over=1;
	}
}
	
void Pause() interrupt 0
{
	EX0=0;
	flag=~flag;
	read24c02();
	if(flag==0x00)
	{
		disp[5]=param[0];
		disp[6]=param[1]/10;
		disp[7]=param[1]%10;
	}
	EX0=1;
}
