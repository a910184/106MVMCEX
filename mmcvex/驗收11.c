#include "ASA_Lib.h"
#include<stdlib.h>
int main(void)
{
	int i=0,j,a,n,digit_n=0,SEG7CODE;
	ASA_M128_set();
	DDRA=0x0f;
	DDRC=0xff;
	PORTA=0x0f;
	printf("----start---\n");
	char Display[33][4]={{1,1,1,1},{0,1,1,2},{0,0,1,3},{0,0,5,3},{0,5,5,6},{5,5,5,5},{7,5,5,0},{8,5,0,0},{9,10,10,0},{10,10,10,10},{0,10,10,11},{0,0,10,12},{0,0,0,13},{0,0,1,14},{0,1,1,2},{1,1,1,1},{15,1,1,0},{16,1,0,0},{17,0,0,0},{18,10,0,0},{9,10,10,0},{10,10,10,10},{0,10,10,11},{0,0,10,12},{0,0,0,13},{0,0,1,14},{0,1,1,2},{1,1,1,1},{15,1,1,0},{19,1,0,0},{19,5,0,0},{20,5,5,0},{5,5,5,5}}; /*4 個字元矩陣內部為要顯示的 ASCII 碼*/
	int SEGTABLE[2][20]={{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20},{0xff,~(0x01),~(0x03),~(0x43),~(0x41),~(0x40),~(0x42),~(0x50),~(0x58),~(0x18),~(0x08),~(0x0c),~(0x0e),~(0x0f),~(0x07),~(0x21),~(0x31),~(0x39),~(0x38),~(0x61),~(0x60)}};
	/* 七節管碼表，第一行為 ASCII ，第二行為七節管碼，共 12 個值由 0到9，然後是 'E' 及'-' */

	while (1)
	{
		if(i<34)
		{
			PORTA=0x0f;
			_delay_ms(5);
			if (digit_n > 3){digit_n=0; a++;} /* 若高於萬位，回到個數 */

			for (j=0;j<21;j++)
			{
				if( Display[i][digit_n]==SEGTABLE[0][j])
				{
					SEG7CODE=(int)SEGTABLE[1][j];
					printf("%x\n",(int)SEG7CODE);

				}

			}
					PORTC=(int)SEG7CODE;
					PORTA=~(0x01<<digit_n);

			digit_n=digit_n+1;

			_delay_ms(50);
			if(a==5)
			{
			if(i==32)
			{
				i=32;
			}
			else if(i<32)
			{
			i=i+1;
			}

			a=0;
			}

		}

	}


	return 0;
}
