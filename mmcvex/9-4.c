#include "ASA_Lib.h"
#include<stdlib.h>

int main(void)
{
	ASA_M128_set();
  M128_DIO_set(200,0xff,0,0x00);//A輸入
  M128_DIO_set(202,0xff,0,0xff);//C輸出
	int odata=0,idata=0,times=0,oshift,omask,imask,ishift,a,b;
	int  data=0,pdata=0,pshift,pmask,gmask,gshift;
	while(1)
	{
			printf("set get mask choose 3 bit\n");scanf("%x",&gmask);//提示取得使用者提供讀取MASK
			printf("set get shift\n");scanf("%d",&gshift);//提示取得使用者提供讀取Shift。
			a=M128_DIO_fgt(100,(char)gmask,(char)gshift,&data);// 取得經MASK過濾後往左平移Shift位元後之旗標群數值。
			printf("a=%d\n",a);
			printf("%x\n",data);// 將前面取得值送回PC。
			b=M128_DIO_fpt(2,0xff,data,0x01);//將輸出旗標群值平移後，以MASK處理蓋寫輸出。
			printf("b=%d\n,pdata=%x",b,pdata);

	}
	return 0;
}
