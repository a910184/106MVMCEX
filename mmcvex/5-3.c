/*
char ASA_DIO00_put(char ASA_ID, char LSByte, char Bytes, void* Data_p);
char ASA_DIO00_get(char ASA_ID, char LSByte, char Bytes, void* Data_p);
char ASA_DIO00_fpt(char ASA_ID, char LSByte, char Mask, char shift, char Data);
char ASA_DIO00_fgt(char ASA_ID, char LSByte, char Mask, char shift, void *Data_p);

*/
#include "ASA_Lib.h"
#include<stdlib.h>
char data=0,data2=0,temp=0;
int main(void)
{
	ASA_M128_set();
	int mask,shift;
	while(1)
	{
		data=0,data2=0,temp=0;
		printf("get then fpt,enter mask,shift\n");
		printf("mask\n");
		scanf("%d",&mask);
		printf("shift\n");
		scanf("%d",&shift);
		
		ASA_DIO00_get(3,100,1,&data);
		temp=ASA_DIO00_fpt(3,0,(char)mask,(char)shift,data);
		printf("\n%x,%x\n",data,temp);
		
		printf("fgt then put,enter mask,shift\n");
		printf("mask\n");
		scanf("%d",&mask);
		printf("shift\n");
		scanf("%d",&shift);
		ASA_DIO00_fgt(3,100,(char)mask,(char)shift,&data2);
		ASA_DIO00_put(3,0,1,&data2);
	
	
	
	}
	return 0;
}

