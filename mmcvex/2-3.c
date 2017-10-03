#include "ASA_Lib.h"
#include<stdlib.h>
int main(void)
{
	ASA_M128_set();
	int i ,j;
	for(i=1;i<10;i++)
	{
		printf("%d\n",i);
		for(j=1;j<10;j++)
		{

			printf("%d,",j);
			printf("%d\n",i*j);
		}
	}

	return 0;
}