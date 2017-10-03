#include "ASA_Lib.h"
#include<stdlib.h>
float a,b,c,d,x=0;
float cal(int u)
{
    float y;
	x=a*x+b*u;
	y=c*x+d*u;
	return y;
}
int main(void)
{
	ASA_M128_set();
	float u,y;
	int i;
	printf("U:");
	scanf("%f",&u);
	printf("a:");
	scanf("%f",&a);
	printf("b:");
	scanf("%f",&b);
	printf("c:");
	scanf("%f",&c);
	printf("d:");
	scanf("%f",&d);
	for(i=0;i<30;i++)
	{
		y=cal(u);
		printf("%f\n",y);
	}
	return 0;
}

