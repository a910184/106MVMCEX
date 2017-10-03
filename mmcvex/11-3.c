#include "ASA_Lib.h"
#include<stdlib.h>
int main(void)
{
	int j,a,n,digit_n=0,SEG7CODE;
	ASA_M128_set();
	DDRA=0x0f;
	DDRC=0xff;
	PORTA=0x00;
	printf("----start---\n");
	char Display[4]; /*4 個字元矩陣內部為要顯示的 ASCII 碼*/
	char SEGTABLE[2][12]={{'0','1','2','3','4','5','6','7','8','9','a','b','c'},{0x40,0x79,0x24,0x30,0x19,0x12,0x03,0x78,0x00,0x18,0xa7,0xb3}};
	/* 七節管碼表，第一行為 ASCII ，第二行為七節管碼，共 12 個值由 0到9，然後是 'E' 及'-' */
	printf("ex:abc1");
	scanf("%c%c%c%c",&Display[0],&Display[1],&Display[2],&Display[3]);
	printf("%s",Display);
	while (1)
	{
		PORTA=0x0f;
		_delay_ms(10);
		if (digit_n > 3){digit_n=0;} /* 若高於萬位，回到個數 */

		for (j=0;j<12;j++)
		{
			if( Display[digit_n]==SEGTABLE[0][j])
			{
				SEG7CODE=(int)SEGTABLE[1][j];
				printf("%x\n",(int)SEG7CODE);
			}

		}

		PORTC=(int)SEG7CODE;
		PORTA=~(0x01<<digit_n);
		digit_n=digit_n+1;
		_delay_ms(30);

	}


	return 0;
}
