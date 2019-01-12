#include "Func.h"
#define uchar unsigned char
#define uint unsigned int


sbit erflags=PSW^5;

extern data uchar  param[2];
extern data da;
extern uchar disp[8];
extern uchar d2;
extern uchar k;
extern uint flag;
extern unsigned long result;


void readDAC()
{
	param[0]=disp[5];
	param[1]=disp[6]*10+disp[7];
	write24c02();
}

void disDAC()
{
	result=RcvByte();
	result=(result*5*100)/256;
	Ack();
	disp[5]=result/100;
	disp[6]=result%100/10;
	disp[7]=result%10;
}

void DAC()
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
	uchar temp,i;
	sen:	erflags=0;
		Start();
		SendByte(0xa0); 				
		cAck( );							
		if(erflags==1) goto sen;			
		SendByte(0x00); 					
		cAck( );							
		if(erflags==1) goto sen;
	temp=RcvByte();
	Ack();
	for(i=0;i<3;i++)
	{
		Ack();
		param[i]=RcvByte();
	}
	NoAck();
	Stop();
	flag=1;
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
		SendByte(0xa1); 					
		cAck( );							
		if(erflags==1) goto sen;
	for(i=0;i<3;i++)
	{
		SendByte(param[i]); 						
		cAck( );
	}
	Stop();
	flag=1;
}
