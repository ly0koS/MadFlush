#ifndef _Func_
#define _Func_
#include "IIC.h"
#include "DISP.h"
#define uchar unsigned char
void Calculate();
void write24c02(void);
void read24c02(void);
uchar keyscan();
void ParamProcess();
void NumProcess(unsigned int keynum);
#endif