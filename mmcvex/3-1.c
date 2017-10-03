#include "ASA_Lib.h"
#include<stdlib.h>
int x1(int x,int n)
{
	int ans=1;
	int i;
	for(i=1;i<=n;i++)
	{
		ans=ans*x;
	}

	return (ans);
}
int main(void)
{
	ASA_M128_set();
	int x,n,ans ;
	printf("X:");
	scanf("%d",&x);
	printf("N:");
	scanf("%d",&n);
	ans=x1(x,n);
	printf("%d",ans);
	return 0;
}

