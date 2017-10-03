#include "ASA_Lib.h"
#include<stdlib.h>


int main(void)
{
	ASA_M128_set();

	char a[5][5]={'-','-','-','-','-','-','-','-','-','-','-','-','o','-','-','-','-','x','-','-','-','-','-','-','-'};
	char temp;

	int i,j,x1=2,y1=2,x2=3,y2=2;
	//initail 33 23
	for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {

            printf("%c",a[i][j]);
        }
       printf("\n");
    }
    int control=0,num=1;


   while(1)
   {
    printf("2,4,6,8,:");
    scanf("%d",&control);
    switch(control)
    {
    case 2:
    for(i=0;i<5;i++)
        {
        for(j=0;j<5;j++)
        {

           a[i][j]='-';
        }
        }
        if(x2<4&&x1<=4)
        {
        a[x2=x2+num][y2]='x';

        }
  else{

            a[x2][y2]='x';

    }

 if(x1-x2==0&&y1-y2==0&&x1<4)
 {
 a[x1=x1+num][y1]='o';
 }
 else
 {
      a[x1][y1]='o';
 }

 if(x1==x2&&y2==y1)
 {

    a[x2=x2-1][y2]='x';
 }




        for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {

            printf("%c",a[i][j]);
        }
       printf("\n");
    }
        break;
    case 4:
        for(i=0;i<5;i++)
        {
        for(j=0;j<5;j++)
        {

           a[i][j]='-';
        }
        }
     if(y2>0&&y1>=0||y2!=y1&&x1!=x2)
     {
        a[x2][y2=y2-num]='x';

     }
      else{

            a[x2][y2]='x';

    }
if(x1-x2==0&&y1-y2==0&&y1>0)
 {
 a[x1][y1=y1-num]='o';
 }
 else
 {
      a[x1][y1]='o';
 }
 if(x1==x2&&y2==y1)
 {

    a[x2][y2=y2+1]='x';
 }




         for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {

            printf("%c",a[i][j]);
        }
       printf("\n");
    }
        break;
    break;
    case 6:
    for(i=0;i<5;i++)
        {
        for(j=0;j<5;j++)
        {

           a[i][j]='-';
        }
        }
        if(y2<4&&y1<4||y2!=y1&&x1!=x2)
        {
        a[x2][y2=y2+num]='x';

        }
        else{

            a[x2][y2]='x';
        }
   if(x1-x2==0&&y1-y2==0&&y1<4)
 {
 a[x1][y1=y1+num]='o';
 }
 else
 {
      a[x1][y1]='o';
 }

if(x1==x2&&y2==y1)
 {

    a[x2][y2=y2-1]='x';
 }



        for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {

            printf("%c",a[i][j]);
        }
       printf("\n");
    }
        break;
    case 8:
    for(i=0;i<5;i++)
        {
        for(j=0;j<5;j++)
        {

           a[i][j]='-';
        }
        }

    if(x2>0&&x1>=0||x1!=x2&&y1!=y2)
    {
    a[x2=x2-num][y2]='x';

    }
        else{

            a[x2][y2]='x';
         }
if(x1-x2==0&&y1-y2==0&&x1>0)
 {
 a[x1=x1-num][y1]='o';
 }
 else
 {
      a[x1][y1]='o';
 }
        if(x1==x2&&y2==y1)
 {

    a[x2=x2+1][y2]='x';
 }



        for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {

            printf("%c",a[i][j]);
        }
       printf("\n");
    }
        break;
    }

   }


	return 0;
}

