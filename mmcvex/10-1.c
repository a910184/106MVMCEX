#include "ASA_Lib.h"
#include<stdlib.h>
/****/
int set(int port,int mask,int shift,int data);
int fgt(int port,int mask,int shift,int* data);
int fpt(int port,int mask,int shift,int data);
int main(void)
{
	ASA_M128_set();
	int omask,imask,smask,sshift,oshift,ishift,sdata,ismask,isshift,isdata,data=0;
	char oport,iport;
	printf("output port,input\n");
	scanf("%d,%d",&oport,&iport);
	printf("omask\n");
	scanf("%x",&smask);
	printf("oshift\n");
	scanf("%x",&sshift);
	printf("set pin direction 0 input 1 output \n");
	scanf("%x",&sdata);
	printf("inputmask\n");
	scanf("%x",&ismask);
	printf("inputshift\n");
	scanf("%x",&isshift);
	printf("set pin direction 0 input 1 output\n");
	scanf("%x",&isdata);

	printf("omask\n");
	scanf("%x",&omask);
	printf("oshift\n");
	scanf("%x",&oshift);
	printf("imask\n");
	scanf("%x",&imask);
	printf("ishift\n");
	scanf("%x",&ishift);

	set(oport,smask,sshift,sdata);
	set(iport,ismask,isshift,isdata);

	while(1)
	{
		fgt(iport,imask,ishift,&data);

		fpt(oport,omask,oshift,data/0x0f);
		printf("%x\n",data);
	}

	return 0;
}
int set(int port,int mask,int shift,int data)
{
	switch(port)
	{
		case 200:  DDRA= (data&mask)<<shift;break;
		case 201:  DDRB= (data&mask)<<shift;break;
		case 202:  DDRC= (data&mask)<<shift;break;
		case 204:  DDRE= (data&mask)<<shift;break;
		case 205:  DDRF= (data&mask)<<shift;break;
		default:break;
	}
}
int fpt(int port,int mask,int shift,int data)
{
	switch(port)
	{
		case 0:  PORTA = (data&mask)<<shift;break;
		case 1:  PORTB = (data&mask)<<shift;break;
		case 2:  PORTC = (data&mask)<<shift;break;
		case 4:  PORTE = (data&mask)<<shift;break;
		case 5:  PORTF = (data&mask)<<shift;break;
		default:break;
	}
}
int fgt(int port,int mask,int shift,int* data)
{
	switch(port)
	{
		case 100: * data = (PINA&mask)<<shift;break;
		case 101: * data = (PINB&mask)<<shift;break;
		case 102: * data = (PINC&mask)<<shift;break;
		case 104: * data = (PINE&mask)<<shift;break;
		case 105: * data = (PINF&mask)<<shift;break;
		default:break;
	}
}
