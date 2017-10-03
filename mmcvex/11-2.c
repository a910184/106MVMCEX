#include "ASA_Lib.h"
#include<stdlib.h>
int main(void)
{
	int i,a;
	ASA_M128_set();
	DDRA=0x0f;
	DDRC=0x0f;
  PORTA=0x00;
	printf("----start---\n");
	while (1)
	{
		for(i=0;i<10;i++)
		{
      switch (i)
			{
        case 0:a=0x40 ;break;
        case 1:a=0x79 ;break;
        case 2:a=0x24 ;break;
        case 3:a=0x30 ;break;
        case 4:a=0x19 ;break;
        case 5:a=0x12 ;break;
        case 6:a=0x03 ;break;
        case 7:a=0x78 ;break;
        case 8:a=0x00 ;break;
        case 9:a=0x18 ;break;
      }
      PORTC=a;
			printf("%d",i);
			_delay_ms(10000);
		}
	}
	return 0;
}
