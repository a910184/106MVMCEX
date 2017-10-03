#include "ASA_Lib.h"
#include<stdlib.h>

int main(void)
{
	ASA_M128_set();
	char I_PORT,O_PORT;
	int I_bit,O_bit,reset,ibyte,obyte,omask,imask,idata,odata,time,pshift,pmask,pbyte,gmask,gbyte,data=0,gshift,check1,check2;

	while(1)
	{
		time=0;
		printf("input port out put:\n");//PA7:0, PB7:4, PC7:0, PE7:2, PF3:0，
		scanf("%c%d%c%d",&I_PORT,&I_bit,&O_PORT,&O_bit);


		//設定腳位輸出與輸入
		switch (O_PORT)//LSBYTE
		{
			case 'a':obyte= 200;pbyte=0;break;
			case 'b':obyte= 201;pbyte=1; break;
			case 'c':obyte= 202;pbyte=2; break;
			case 'e':obyte= 204;pbyte=4; break;
			case 'f':obyte= 205;pbyte=5; break;//3:0
		}
		switch (I_PORT)
		{
			case 'a':ibyte=200;gbyte=100;  break;
			case 'b':ibyte=201;gbyte=101;  break;
			case 'c':ibyte=202;gbyte=102;  break;
			case 'e':ibyte=204;gbyte=104;  break;
			case 'f':ibyte=205;gbyte=105;  break; //3:0
		}
		switch (I_bit)//MASK
		{
			case 0:imask=0x01;idata=~0x01; break;
			case 1:imask=0x02;idata=~0x02; break;
			case 2:imask=0x04;idata=~0x04; break;
			case 3:imask=0x08;idata=~0x08; break;
			case 4:imask=0x10;idata=~0x10; break;
			case 5:imask=0x20;idata=~0x20; break;
			case 6:imask=0x40;idata=~0x40; break;
			case 7:imask=0x80;idata=~0x80; break;
		}
		switch (O_bit)
		{
			case 0:omask=0x01;odata=0x01; break;
			case 1:omask=0x02;odata=0x02; break;
			case 2:omask=0x04;odata=0x04; break;
			case 3:omask=0x08;odata=0x08; break;
			case 4:omask=0x10;odata=0x10; break;
			case 5:omask=0x20;odata=0x20; break;
			case 6:omask=0x40;odata=0x40; break;
			case 7:omask=0x80;odata=0x80; break;
		}
		M128_DIO_set(obyte,omask,0,odata);
		M128_DIO_set(ibyte,imask,0,idata);


		printf("pdata:\n");
		scanf("%d",&data);
		check2=M128_DIO_fpt(pbyte,omask,0,data);
		for(time=0;time<=100;time++)
		{

			check1=M128_DIO_fgt(gbyte,imask,0,&data);
			printf("get:%d , put:%d\n",check1,check2);
			printf("data %d\n",data);
			time++;

		}
	}
	return 0;
}
