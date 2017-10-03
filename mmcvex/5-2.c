#include "ASA_Lib.h"
#include<stdlib.h>
int main(void)
{
	char data2=0;
	ASA_M128_set();
while(1)
{
	ASA_DIO00_fgt(3,100,0xff,0,&data2);
	temp=ASA_DIO00_fpt(3,0,0xff,0,data2);
}

	return 0;
}

