#include "IIC.h"
#include "Func.h"
#include "DISP.h"

#define uchar unsigned char
#define uint 	unsigned int

sbit over=P1^0;													//����2.5V��ʾ��

data uchar param[2] _at_ 0x20;					//�洢��ѹֵ����param[0]:����,param[1]:С��
unsigned long result;										//DAC�����ĵ�ѹֵ
data uchar flag _at_ 0x30;							//��ͣ|������־λ

extern uchar disp[8];										//�������ʾ����

void main()
{
	EA=1;																	//���ж�����
	EX0=1;																//�ⲿ�ж�0�ж�����
	ET0=1;																//��ʱ��0�ж�����
	IT0=0;																//�ⲿ�ж�0����Ϊ��ƽ����					
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
