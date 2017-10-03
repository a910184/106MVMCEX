//#include "ASA_Lib.h"
#include<stdlib.h>
int main(void)
{
	//ASA_M128_set();
	long	int input;
	int i,ans,rans,var1,var2,score=0;
	printf("ID:");
	scanf("%ld",&input);
	printf("ld\n",input);
	for(i=0;i<10;i++)
	{
	 var1=rand()%10;
	 var2=rand()%10;
	 rans=var1+var2;
	 printf("%d+%d=\n",var1,var2);
	 scanf("%d",&ans);
	 if(rans==ans)
		 {score=score+10;}
    else{
        score=score;
    }
	 printf("ans:%d\nscore:%d\n",rans,score);
	}


	switch(score)
	{
		case 100:
		printf("A\n");
		break;
		case 90:
		printf("A\n");
		break;
		case 80:
		printf("B\n");
		break;
		case 70:
		printf("C\n");
		break;
		case 60:
		printf("D\n");
		break;
		default:
	printf("F\n");
		break;
	}
  printf("End of test");

	return 0;
}

