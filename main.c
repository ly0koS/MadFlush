/*�ļ�˵��:main.c:�������ļ�				������:��ͣ����--�ⲿ�ж�0+��������	
					 Func.c:�Զ��幦�ܺ����ļ�������:��ȡPCF8591��ѹֵ��д��24c02|��ʾDAC��ѹֵ|PCF8591��ʼ��(A->D)|24c02��д��
					 DISP.c:��ʾ�����ļ�			������:����ܶ�̬��ʾ&5s��¼��ѹֵ��
					 */

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
	IT0=1;																//�ⲿ�ж�0����Ϊ���ش���					
	TMOD|=0x01;														//��ʱ��0����Ϊ��ʽ1
	TH0=(65536-500)/256;									//����ܶ�̬��ʾ��ʱ��0��ֵ
	TL0=(65536-500)%256;
	TR0=1;																//��ʱ��0����
	flag=0xff;														//����״̬
	DAC();																//����I2C PCF8591��ʼ��(A->D)
	disDAC();															//��ʾ��ѹֵ
	write24c02();													//д��24c02
	while(1)
	{
		if(flag==0xff)											//����״̬ʱ
		{
			DAC();														//����I2C PCF8591��ʼ��(A->D)
			disDAC();													//��ʾ��ѹֵ
		}
		else																//��ͣʱ
		{
			disp[5]=param[0];									//��ʾ24c02�д洢�ĵ�ѹֵ
			disp[6]=param[1]/10;
			disp[7]=param[1]%10;
		}
		if(result>=250)											//����2.5V����
			over=0;
		else																//������
			over=1;
	}
}
	
void Pause() interrupt 0								//������ͣ����
{
	flag=~flag;														//״̬��ת
}
