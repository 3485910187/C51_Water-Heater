#ifndef __LCD1602_H
#define __LCD1602_H

#include"reg51.h"
#include "delay.h"

#define lcddata P0

sbit RS=P2^0;
sbit RW=P2^1;
sbit E=P2^2;

void writecom(char dat);
void writedat(char dat);
void LcdInit(void);
void display(char x,char y,char *dat);

#endif
