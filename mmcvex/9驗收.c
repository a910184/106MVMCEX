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
		a=M128_DIO_get(100,1,&data);
		printf("%d,%d",a,data);
		if(data>0)
		{
			b=M128_DIO_fpt(2,0xff,0,0x81);
			_delay_ms(5000);
			b=M128_DIO_fpt(2,0xff,0,0x42);
			_delay_ms(5000);
			b=M128_DIO_fpt(2,0xff,0,0x24);
			_delay_ms(5000);
			b=M128_DIO_fpt(2,0xff,0,0x18);
			_delay_ms(5000);
			b=M128_DIO_fpt(2,0xff,0,0x99);
			_delay_ms(5000);
			b=M128_DIO_fpt(2,0xff,0,0x5a);
			_delay_ms(5000);
			b=M128_DIO_fpt(2,0xff,0,0x3c);
			_delay_ms(5000);
			b=M128_DIO_fpt(2,0xff,0,0xbd);
			_delay_ms(5000);
			b=M128_DIO_fpt(2,0xff,0,0x7e);
			_delay_ms(5000);
			b=M128_DIO_fpt(2,0xff,0,0xff);
			_delay_ms(5000);
		}
		else
		{
			b=M128_DIO_fpt(2,0xff,0,~0x81);
			_delay_ms(5000);
			b=M128_DIO_fpt(2,0xff,0,~0x42);
			_delay_ms(5000);
			b=M128_DIO_fpt(2,0xff,0,~0x24);
			_delay_ms(5000);
			b=M128_DIO_fpt(2,0xff,0,~0x18);
			_delay_ms(5000);
			b=M128_DIO_fpt(2,0xff,0,~0x99);
			_delay_ms(5000);
			b=M128_DIO_fpt(2,0xff,0,~0x5a);
			_delay_ms(5000);
			b=M128_DIO_fpt(2,0xff,0,~0x3c);
			_delay_ms(5000);
			b=M128_DIO_fpt(2,0xff,0,~0xbd);
			_delay_ms(5000);
			b=M128_DIO_fpt(2,0xff,0,~0x7e);
			_delay_ms(5000);
			b=M128_DIO_fpt(2,0xff,0,~0xff);
			_delay_ms(5000);
		}
	}
	printf("%d",b);
	return 0;
}
