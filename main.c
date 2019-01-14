#include "IIC.h"
#include "Func.h"
#include "DISP.h"

#define uchar unsigned char
#define uint 	unsigned int

sbit over=P1^0;													//超过2.5V警示灯

data uchar param[2] _at_ 0x20;					//存储电压值数组param[0]:整数,param[1]:小数
unsigned long result;										//DAC读出的电压值
data uchar flag _at_ 0x30;							//暂停|继续标志位

extern uchar disp[8];										//数码管显示数组

void main()
{
	EA=1;																	//总中断允许
	EX0=1;																//外部中断0中断允许
	ET0=1;																//计时器0中断允许
	IT0=0;																//外部中断0设置为电平触发					
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
		else
		{
			disp[5]=param[0];
			disp[6]=param[1]/10;
			disp[7]=param[1]%10;
		}
		if(result>=250)
			over=0;
		else
			over=1;
	}
}
	
void Pause() interrupt 0
{
	flag=~flag;
}
