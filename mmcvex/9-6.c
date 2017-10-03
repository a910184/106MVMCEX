/**自動測試邏輯電路真質表
A　low 4 bit ->input A high 4 bit -> output **/
#include "ASA_Lib.h"
#include<stdlib.h>

int main(void)
{
	ASA_M128_set();
	int data=0,temp=0,a=0,b=0,i=0;
	M128_DIO_set(200,0x0f,0,0x0f);//A high4 bit輸出
	M128_DIO_set(202,0x0f,0,0x00);//A low 4 bit輸入
  for(i=0;i<=16;i++)
  {
  data=i;
  b=M128_DIO_fpt(0,0xf0,0,data);
  M128_DIO_fgt(102,0x0f,0,&data);
  printf("%x,%x\n",i,data );
}
	return 0;
}
