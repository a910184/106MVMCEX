/*
1 display 2 keyboard 3 DIO
寫『+』，『-』，『*』，『/』，『=』蓋貼在『A』，
『B』，『C』，『D』，『E』
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
	
	
	ASA_KB00_set(2,209 , 0xff,0, 43);
	ASA_KB00_set(2,205 , 0xff,0, 45);
	ASA_KB00_set(2,204 , 0xff,0, 42);
	ASA_KB00_set(2,203 , 0xff,0, 47);
	ASA_KB00_set(2,202 , 0xff,0, 61);

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


