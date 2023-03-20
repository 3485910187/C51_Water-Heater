#include"LCD1602.h"

void writecom(char com)
{
	RS=0;
	RW=0;
	E=0;
	lcddata=com;
	DelayMs(5);
	E=1;
	E=0;
}	

void writedat(char dat)
{
	RS=1;
	RW=0;
	E=0;
	lcddata=dat;
	DelayMs(5);
	E=1;
	E=0;
}	

void LcdInit()
{
	writecom(0x38); //设置16x2显示，5x7点阵，8位数据接口
	writecom(0x0c); //设置开显示，不显示光标
	writecom(0x06); //写一个字符后地址加一
	writecom(0x01); //显示清零，数据指针清零
}

void display(char x,char y,char *strdat)
{
    char addr;

    if(x == 0)
        addr = 0x00 + y;
    else
        addr = 0x40 + y;
    writecom(addr | 0x80);  // 设置显示起始地址 x为行，y为列
    while(*strdat != '\0')
    {
        writedat(*strdat++);      // 写入数据并移动指针
    }
}