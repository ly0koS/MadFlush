#ifndef _I2C_
#define _I2C_
#include <intrins.h>
#include <reg52.h>

#define uchar unsigned char

void Start(void);                           //��ʼ�ź�
void Stop(void);                            //��ֹ�ź�
void Ack(void);                             //Ӧ���ź�
void NoAck(void);                           //��Ӧ���ź�
void cAck(void);
void SendByte(unsigned char send);
unsigned char RcvByte(void);
void delay4us(void);
void delay5us();

#endif