/*
1 display 2 keyboard 3 DIO
*/
#include "ASA_Lib.h"
#include<stdlib.h>

int main(void)
{
	ASA_M128_set();
	char keyboard;
	

	char ddata=0;
	char data[4];
	int i=0;
	ASA_7S00_set(1, 200,0xff ,0, ddata);         
	ASA_KB00_set(2,200 , 0xff,0, ddata=1);

	int check=0;
	while(1)
{
	
ASA_KB00_get(2,100,1,&keyboard);

if(keyboard!=0)
{
for(i=0;i<3;i++)
{
	data[i]=data[i+1];
	
}
data[3]=keyboard;
ASA_7S00_put(1,0,4,&data);
}



	printf("%c",keyboard);


_delay_ms(100);
}

	return 0;
}

