#include "ASA_Lib.h"
#include<stdlib.h>

int main(void)
{
	ASA_M128_set();
	int odata=0,idata=0,times=0,oshift,omask,imask,ishift,a,b;
	int  data=0,pdata=0,pshift,pmask,gmask,gshift;
	while(1)
	{
		times=0;
		printf("set output mask\n");scanf("%x",&omask);//提示取得設定輸出埠MASK
		printf("set output shift\n");scanf("%d",&oshift);//提示取得設定輸出埠Shift
		printf("output 16 bit data\n");scanf("%x",&odata);//提示取得設定輸出方向旗標Data
		M128_DIO_set(202,(char)omask,(char)oshift,&odata);//設定輸出埠指定位元為輸出方向
		printf("set input mask\n");scanf("%x",&imask);//提示取得設定輸入埠MASK
		printf("set input shift\n");scanf("%d",&ishift);//提示取得設定輸入埠Shift
		printf("input 16 bit data\n");scanf("%x",&idata);//提示取得設定輸出方向旗標Data
		M128_DIO_set(200,(char)imask,(char)ishift,&idata);//設定輸出埠指定位元為輸出方向

		while(times<10)
		{
			printf("set get mask\n");scanf("%x",&gmask);//提示取得使用者提供讀取MASK
			printf("set get shift\n");scanf("%d",&gshift);//提示取得使用者提供讀取Shift。
			a=M128_DIO_fgt(100,(char)gmask,(char)gshift,&data);// 取得經MASK過濾後往左平移Shift位元後之旗標群數值。
			printf("a=%d\n",a);
			printf("%x\n",data);// 將前面取得值送回PC。
			printf("set put mask\n");scanf("%x",&pmask);//取得提示使用者提供輸出前MASK
			printf("set put shift\n");scanf("%d",&pshift);//取得提示使用者提供輸出前Shift。
			printf("put data\n");scanf("%x",&pdata);//取得提示使用者提供輸出旗標群值。
			b=M128_DIO_fpt(2,(char)pmask,(char)pshift,pdata);//將輸出旗標群值平移後，以MASK處理蓋寫輸出。
			printf("b=%d\n,pdata=%x",b,pdata);
			times++;
		}

	}
	return 0;
}
