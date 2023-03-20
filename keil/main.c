#include"reg51.h"
#include"18B20.h"
#include"LCD1602.h"

sbit add = P2^4;
sbit minus = P2^5;
sbit mode = P2^6;
sbit LED = P2^7;

float T,Set_T=0.0;
unsigned char strT[]={'T',':',' ','0','0','.','0','\0'}; // 十位个位小数分别对应 3，4，6
unsigned char strST[]={'S','e','t','_','T',':',' ','0','0','.','0','\0'}; // 十位个位小数分别对应7 ，8，10
unsigned char keymode = 0,flag=0;

void scan_T()
{
	int x;
			
	if((ReadTemperature_s() & 0x800) == 0)
	{
		T =	ReadTemperature_s() * 0.0625;
		strT[2] = '+';
	}
	else
	{
		T =	(~(ReadTemperature_s())+1) * 0.0625;
		strT[2] = '-';
	}
	x = T*10;
	strT[3] = x / 100 + '0';
	strT[4] = (x/10) % 10 + '0';
	strT[6] = x % 10 + '0';
}

void key()
{
	int x;
	
	if(add == 0)
	{
		switch(keymode)
		{
			case 0:
				Set_T+=0.1;
			break;
			case 1:
				Set_T+=1.0;
			break;
			case 2:
				Set_T+=10.0;
			break;			
		}
	}
	if(minus == 0)
	{
		switch(keymode)
		{
			case 0:
				Set_T-=0.1;
			break;
			case 1:
				Set_T-=1.0;
			break;
			case 2:
				Set_T-=10.0;
			break;			
		}	
	}
	
	if(mode == 0 && flag == 0)flag = 1;
	if(flag == 1 && mode == 1)keymode=(keymode+1)%3,flag = 0;
	
	if(Set_T > 0)
	{
		strST[6] = '+';
			x = Set_T*10;
	}
	else
	{
		strST[6] = '-';	
		x = Set_T *-10;
	}

	strST[7] = x / 100 + '0';
	strST[8] = (x/10) % 10 + '0';
	strST[10] = x % 10 + '0';	
}

void main()
{
	LcdInit();
	while(1)
	{
		key();
		scan_T();
		display(0,5,strT);
		display(1,1,strST);
		if(T<Set_T)LED = 0;
		else LED = 1;
	}
}