/*文件说明:main.c:主函数文件				【包含:暂停按键--外部中断0+主函数】	
					 Func.c:自定义功能函数文件【包含:读取PCF8591电压值并写入24c02|显示DAC电压值|PCF8591初始化(A->D)|24c02读写】
					 DISP.c:显示函数文件			【包含:数码管动态显示&5s记录电压值】
					 */

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
	IT0=1;																//外部中断0设置为跳沿触发					
	TMOD|=0x01;														//计时器0设置为方式1
	TH0=(65536-500)/256;									//数码管动态显示计时器0初值
	TL0=(65536-500)%256;
	TR0=1;																//计时器0运行
	flag=0xff;														//运行状态
	DAC();																//调用I2C PCF8591初始化(A->D)
	disDAC();															//显示电压值
	write24c02();													//写入24c02
	while(1)
	{
		if(flag==0xff)											//运行状态时
		{
			DAC();														//调用I2C PCF8591初始化(A->D)
			disDAC();													//显示电压值
		}
		else																//暂停时
		{
			disp[5]=param[0];									//显示24c02中存储的电压值
			disp[6]=param[1]/10;
			disp[7]=param[1]%10;
		}
		if(result>=250)											//超出2.5V报警
			over=0;
		else																//不报警
			over=1;
	}
}
	
void Pause() interrupt 0								//按下暂停按键
{
	flag=~flag;														//状态翻转
}
