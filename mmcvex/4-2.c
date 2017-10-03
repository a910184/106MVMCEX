#include "ASA_Lib.h"
#include<stdlib.h>
int main(void)
{
	ASA_M128_set();

	int n;
	printf("number:");
	scanf("%d",&n);
	int i,j,grade[n][2],temp,temp2;
	for(i=0;i<n;i++)
	{
		grade[i][0]=i+1;
	}
	for(i=0;i<n;i++)
	{
		printf("%d:",grade[i][0]);
		scanf("%d",&grade[i][1]);
	}
	for(i=n;i>1;i--)
	{
		for(j=0;j<i-1;j++)
		{
			if (grade[j][1] > grade[j+1][1])
			{
				temp=grade[j][1];
				temp2=grade[j][0];
				grade[j][1]=grade[j+1][1];
				grade[j][0]=grade[j+1][0];
				grade[j+1][1]=temp;
				grade[j+1][0]=temp2;
			}
		}
	}
for(i=0;i<n;i++)
	{
		printf("%d,",grade[i][0]);
		printf("%d\n",grade[i][1]);
	}

	return 0;
}

