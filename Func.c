#include "Func.h"
#define uchar unsigned char
#define uint unsigned int


sbit erflags=PSW^5;

extern data uchar  param[9];
extern data uint para1,para2;
extern data da;
extern uchar disp[8];
extern uchar d2;
extern uchar k;

data uint g _at_ 0x2f;

void Calculate()
{
	uint g1,g2;
	uint freq;
	if(param[6]==1)
	{
		freq=param[1];
		g=10^6/freq/32;
		para1=65536-g;
		para2=param[2];
		da=0;
		sen:	erflags=0;						  
			Start( ); 							
			SendByte(0x90); 				
			cAck( );							
			if(erflags==1) goto sen;			
			SendByte(0x40); 					
			cAck( );							
			if(erflags==1) goto sen;
			SendByte(0x91);
			cAck();	
			if(erflags==1) goto sen;
	}
	if(param[6]==2)
	{
		freq=param[3]*1000+param[4];
		g1=10000/freq*param[5];
		g2=10000/freq*(100-param[5]);
		para1=65536-g1;
		para2=65536-g2;
	}
}

void ParamProcess()
{
	uchar freq;
	if(disp[2]==15)
	{
		if(disp[1]==1)
			param[1]=disp[6]*10+disp[7]; 
		else 	
		{
			freq=disp[5]*100+disp[6]*10+disp[7];
			param[3]=disp[4];
			param[4]=freq%256;
		} 
	}
	else
	{
		if(disp[1]==1) 
			param[2]=disp[6]*10+disp[7]; 
		else
			param[5]=disp[6]*10+disp[7];
	}
}

void NumProcess(unsigned int keynum)
{
	uchar i;
	if(k>=4)
	{
		if(disp[1]==2&d2==15)																//Square Wave-Frequence Mode
		{
			if(k==4)
			{
				if(keynum==1)																			//Max=1000Hz
				{
					disp[k]=1;
					for(i=5;i<8;i++)
					{
						disp[i]=0;
					}
				}
				else if(keynum==0)
					disp[k]=keynum;
			}
			else
			{
				if(disp[4]==0)
				{
					disp[4]=16;																				//disp[4] off
					disp[k]=keynum;
				}
			}
		}
		else if(k==6)
		{
			if(param[6]==2&d2==10)
			{
				if(keynum>=2&&keynum<=7)
					disp[k]=keynum;
			}
			else
			{
				if(keynum>=1&&keynum<5)															//Sin Wave-Frequence Mode
					disp[k]=keynum;
				else if(keynum==5)																	//Max=50Hz
				{
					disp[k]=keynum;
					disp[7]=0;
				}
			}
		}
		else																										//maybe else if?
		{
			if(param[6]==1&d2==10&&disp[6]==5)										//Max=50Hz
			{
				disp[7]=0;
			}
			else
				disp[k]=keynum;
		}
	}
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

uchar keyscan()
{
	uchar a,b,temp; 
	P2=0xf0;
	delay(5);	
	a=P2;
	P2=0x0f;
	delay(5);
	b=P2;
	a=a|b;
	if(a!=0xff)
	{
		while(P2!=0x0f);
		switch(a)
		{
			case 0xee: temp=0;break;
			case 0xde: temp=1;break;
			case 0xbe: temp=2;break;
			case 0x7e: temp=3;break;
			case 0xed: temp=4;break;
			case 0xdd: temp=5;break;
			case 0xbd: temp=6;break;
			case 0x7d: temp=7;break;
			case 0xeb: temp=10;break;//����
			case 0xdb: temp=8;break;
			case 0xbb: temp=9;break;
			case 0x7b: temp=20;break;//����
			case 0xe7: temp=12;break;//���ü�
			case 0xd7: temp=13;break;//ѡ����
			case 0xb7: temp=14;break;//ѡ�����
			case 0x77: temp=15;	//ȷ�ϼ�
			}
  }
	return temp;
}

