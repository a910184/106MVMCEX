#include "ASA_Lib.h"
#include<stdlib.h>

void swap(int *x,int *y)
{
	int temp;
	temp = *x;
	*x=*y;
	*y=temp;

}
int main(void)
{
	ASA_M128_set();
	int x,y,ans ;
	printf("X:");
	scanf("%d",&x);
	printf("Y:");
	scanf("%d",&y);
	swap(&x,&y);
	printf("%d,%d",x,y);
	return 0;
}

