#include "ASA_Lib.h"
#include<stdlib.h>
/****/
void kb_scan(void);
int set(int port,int mask,int shift,int data);
int fgt(int port,int mask,int shift,int* data);
int fpt(int port,int mask,int shift,int data);

int main(void)
{
	ASA_M128_set();
	printf("----start---\n");
	while (1)
	{
		kb_scan();
	}
	return 0;
}

void kb_scan(void)
{
	static int d[4][4]={{13,9,5,1},{14,10,6,2},{15,11,7,3},{16,12,8,4}};
	static int scan[4]={0x7f,0xbf,0xdf,0xef};
	static int hmk[4]={240,240,240,240};
	static int lmk[4]={1,2,4,8};
	static int i=0,j=0,c=0,test=1,s=0;
	for(j=0;j<4;j++)
	{
		set(200,255,0,240);
		fpt(0,hmk[j],0,scan[j]);
		for(i=0;i<4;i++)
		{
			set(200,255,0,240);
			fgt(100,lmk[i],i,&test);
			if(test==0)
			{
				c=0;
				while(c==0)
				{
					set(200,255,0,240);
					fgt(100,lmk[i],i,&test);
					if(test>0)
					{

						s=d[j][i];
						printf("j=%d,i=%d\n",j,i );
						printf("%d\n",s);
						c=1;
					}
				}
			}
		}
	}




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
