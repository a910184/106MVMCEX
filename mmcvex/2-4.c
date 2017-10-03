#include "ASA_Lib.h"
#include<stdlib.h>
int main(void)
{
	ASA_M128_set();
	int i=1,j=1;
	while(i<10)
	{
		printf("%d\n",i);
		while(j<10)
		{

			printf("%d,%d\n",j,i*j);
			j=j+1;
		}
		i=i+1;
		j=1;
	}

	return 0;
}
