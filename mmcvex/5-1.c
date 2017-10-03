#include "ASA_Lib.h"
#include<stdlib.h>
int main(void)
{
	ASA_M128_set();

int i,j;
for(i=1;i<=5;i++)
{
	for(j=1;j<=5;j++)
	{
		printf("%d x %d=%d,",i,j,i*j);
	}
	printf("\n");
}
	return 0;
}

