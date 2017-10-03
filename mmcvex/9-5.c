#include "ASA_Lib.h"
#include<stdlib.h>

int main(void)
{
	ASA_M128_set();
	int data=0,temp=0,a=0,b=0,UP_EVENT,DOWN_EVENT;
	M128_DIO_set(200,0xff,0,0x00);//A輸入
	M128_DIO_set(202,0xff,0,0xff);//C輸出
	while(1)
	{
		M128_DIO_fgt(100,0xff,0,&data);//執行監測PORTA旗標值存入HILO。新HILO與上次HILO比較，由HI變LO，或LO變HI，分別更新DOWN_EVENT，UP_EVENT。

		if(temp-data<0)
		{UP_EVENT=1; break;}
		else if(temp-data>0)
		{DOWN_EVENT=1;break;}
		//將所讀旗標HILO新狀態，上昇緣事件旗標UP_EVENT，下降緣事件旗標DOWN_EVENT，分別送回超級終端機。
		temp=data;
	}
	printf("up:%d,down:%d",UP_EVENT,DOWN_EVENT);
	return 0;
}
