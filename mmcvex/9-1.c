#include "ASA_Lib.h"
#include<stdlib.h>

int main(void)
{
	ASA_M128_set();
	int data=0,data2=0,a=0,b=0;
	M128_DIO_set(200,0xff,0,0x00);//A輸入
	M128_DIO_set(202,0xff,0,0xff);//C輸出
	while(1)
	{

		a=M128_DIO_get(100,1,&data);
		//printf("data %d a:%d\n",data,a);//列出輸入值。
		//printf("輸出值:16bit\n");//提示使用者提供輸出值。
		//scanf("%x",&data);//取得欲輸出值。
		b=M128_DIO_put(2,1,&data);//輸出已取得欲輸出值
		printf("data:%d\n",data);//列出輸入值。

	}
	return 0;
}
