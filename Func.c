#include "Func.h"
#define uchar unsigned char
#define uint unsigned int


sbit erflags=PSW^5;

extern data uchar  param[9];
extern data da;
extern uchar disp[8];
extern uchar d2;
extern uchar k;

data uint g _at_ 0x2f;

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
	if(temp==0x55)
	{
		param[0]=0x55;
		for(i=1;i<8;i++)
		{
			Ack();
			param[i]=RcvByte();
		}
		NoAck();
		Stop();
	}
	else
	{
		write24c02();
		Stop();
	}
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
	for(i=0;i<8;i++)
	{
		SendByte(param[i]); 						
		cAck( );
	}
	Stop();
}
