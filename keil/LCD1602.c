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
	writecom(0x38); //����16x2��ʾ��5x7����8λ���ݽӿ�
	writecom(0x0c); //���ÿ���ʾ������ʾ���
	writecom(0x06); //дһ���ַ����ַ��һ
	writecom(0x01); //��ʾ���㣬����ָ������
}

void display(char x,char y,char *strdat)
{
    char addr;

    if(x == 0)
        addr = 0x00 + y;
    else
        addr = 0x40 + y;
    writecom(addr | 0x80);  // ������ʾ��ʼ��ַ xΪ�У�yΪ��
    while(*strdat != '\0')
    {
        writedat(*strdat++);      // д�����ݲ��ƶ�ָ��
    }
}