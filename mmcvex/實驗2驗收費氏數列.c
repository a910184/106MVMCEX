#include "ASA_Lib.h"
#include<stdlib.h>


int main(void)
{
	ASA_M128_set();
	 long int x,y,temp ;
	 int layer,i,j;
	x=0;
	y=1;
	printf("layer:");
	scanf("%d",&layer);
	printf("%d\n",y);
	for(i=1;i<layer;i++)
	{
	 for(j=1;j<=i+1;j++)
	 {
        temp=y;
        y=x+y;
        x=temp;

		printf("%ld,",y);


     }

	 printf("\n");
	}
	return 0;
}

