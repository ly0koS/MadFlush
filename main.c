#include "IIC.h"
#include "Func.h"
#include "DISP.h"

sbit over=P1^0;

data uchar param[2];
data da;
uchar k;

extern uchar disp[8];
extern uchar d2;
extern uchar hide;
extern uchar i;

void main()
{
	EA=1;
	EX0=1;
	ET0=1;
	TMOD|=0x01;
	TH0=(65536-500)/256;
  TL0=(65536-500)%256;
	TR0=1;
	disDAC();
	while(1)
	{
		
	}
}