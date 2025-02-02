#include "DISP.h"
#include "Func.h"
sbit OE=P1^3;
sbit duan=P1^4;
sbit wei=P1^5;
sbit K1=P2^0;
sbit K2=P2^1;

#define uchar unsigned char
	
uchar disp[8]={7,1,3,18,17,16,16,16};
uchar code sled_bit[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
uchar table[19]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00,0x40,0x73};
uchar i=0;
uchar key=99;
uchar temp;
uchar d2;
uchar hide=0xff;
unsigned int count=0;

extern data uchar  param[9];
extern data uchar k;
extern bit setup;
extern uchar flag;

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
	t=disp[i];
	OE=1;
	P0=table[t];
	if(i==5) P0=P0|0x80;
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
	count=count+1;
	if(count==600&&flag==0xff)
	{
		count=0;
		readDAC();
	}
	TR0=1;
}