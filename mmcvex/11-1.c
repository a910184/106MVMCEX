#include "ASA_Lib.h"
#include<stdlib.h>
int main(void)
{
	int i;
	ASA_M128_set();
	DDRA=0x0f;
	DDRC=0x0f;
	printf("----start---\n");
	while (1)
	{
		for(i=0;i<10;i++)
		{
			PORTA=0x00;
			//fpt(2,0x0f,0,i);
			PORTC=i;
			printf("%d",i);
			_delay_ms(10000);
		}
	}
	return 0;
}
