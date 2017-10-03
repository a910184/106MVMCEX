#include "ASA_Lib.h"
#include<stdlib.h>

int main(void)
{
	ASA_M128_set();

	int n;
	printf("number:");
	scanf("%d",&n);
	int i,j,grade[n],temp;
	for(i=0;i<n;i++)
	{
		scanf("%d",&grade[i]);
	}
	for(i=n;i>1;i--)
	{
		for(j=0;j<i-1;j++)
		{
			if (grade[j] > grade[j+1])
			{
				temp=grade[j];
				grade[j]=grade[j+1];
				grade[j+1]=temp;
			}
		}
	}
for(i=0;i<n;i++)
	{
		printf("%d,",grade[i]);
	}

	return 0;
}

