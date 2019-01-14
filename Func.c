#include "Func.h"
#define uchar unsigned char
#define uint unsigned int


sbit erflags=PSW^5;

extern data uchar  param[2];
extern uchar disp[8];
extern uchar d2;
extern unsigned long result;


void readDAC()												//读取PCF8591电压值并写入24c02
{
	param[0]=disp[5];
	param[1]=disp[6]*10+disp[7];
	write24c02();
}

void disDAC()													//显示DAC电压值
{
	result=RcvByte();										//读取PCF8591转换的电压值
	result=(result*5*100)/256;					//电压值处理
	NoAck();														//发送非应答，释放I2C总线	
	disp[5]=result/100;									//数码管显示电压值
	disp[6]=result%100/10;
	disp[7]=result%10;
}

void DAC()														//PCF8591初始化(A->D)
{
	sen:	erflags=0;
			Start();
			SendByte(0x90);
			cAck();
			if(erflags) goto sen;
			SendByte(0x00);
			cAck();
			if(erflags) goto sen;
	sen1:	Start();
			SendByte(0x91);
			cAck();
			if(erflags) goto sen1;
}

void read24c02(void)
{
	uchar i;
	sen:	erflags=0;
		Start();
		SendByte(0xa0); 				
		cAck( );							
		if(erflags==1) goto sen;			
		SendByte(0x00); 					
		cAck( );							
		if(erflags==1) goto sen;
		SendByte(0xa0); 				
		cAck( );							
		if(erflags==1) goto sen;
	for(i=0;i<2;i++)
	{
		param[i]=RcvByte();
		Ack();
	}
	NoAck();
}


void write24c02(void)
{
	uchar i;
	sen:	erflags=0;						  
		Start( ); 							
		SendByte(0xa0); 				
		cAck( );							
		if(erflags==1) goto sen;			
		SendByte(0x00); 					
		cAck( );							
		if(erflags==1) goto sen;
	for(i=0;i<2;i++)
	{
		SendByte(param[i]); 						
		Ack( );
	}
	Stop();
}
