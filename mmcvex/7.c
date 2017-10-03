#include "ASA_Lib.h"
#include "math.h"
#include<stdlib.h>
char KeyResolver();
char KeyInCumulator();
char Calculator();
char DisplaySelector ();
int a,keyboard,zero= 0x30;// a為數值暫存,b為轉換後的實際數值
int norc=0,eq=0,cal,value,b,fir,tem,play,shortclear,special=0,cal1,enter,sp0=0,sp1=0,bit;//bit等號後輸入數字sp0 溢位 enter 數字鍵輸入專屬 special 等號輸入顯示旗標
long int cal2,display=0;//c為運算結果
char I[4];
int main(void)
{
	ASA_M128_set();

	char ddata=0;
	int temp=0;
	int keyflag=0;

	ASA_7S00_set(1, 200,0xff ,0, ddata);
	ASA_KB00_set(2,200 , 0xff,0, ddata=1);//data= 1 ascii,= 0 keyboard #
	fir=0;


	ASA_7S00_put(1,3,1,&zero);

	while(1)
{
_delay_ms(175);
ASA_KB00_get(2,100,1,&keyboard);

temp=(int)keyboard;
if(temp==0)
{
 keyflag=1;
}
if(keyboard!=0)
{

if(keyflag==1)
{
	 KeyResolver();
	 KeyInCumulator();
	 Calculator();
	 DisplaySelector ();
	  ASA_7S00_put(1,0,4,&I);
	keyflag=0;


}
}

}
	return 0;
}



char KeyResolver() // 判斷鍵號 ASCII norc 1 為數值 0為符號 eq等號四則旗標eq=1等號 cal 1-4四則運算 play螢幕顯示 1 功能鍵 2 數字鍵 0 清除
{
	case 'A'://+
	if(bit1==2)
	{
		bit1=bit1+1;
	}
	else if (bit1==2)
	{
	 bit1=4;
	}
	play=1;
	norc=0;
	cal=1;
	eq=0;
	shortclear = 1;
	break;

	case 'B'://-
	if(bit1==2)
	{
		bit1=bit1+1;
	}
	else if (bit1==1)
	{
		bit1=4;
	}
	play=1;
	norc=0;
	cal=2;
	eq=0;
	shortclear = 1;
	break;

	case 'C'://*
	if(bit1==2)
	{
		bit1=bit1+1;
	}
	else if (bit1==1)
	{
		bit1=4;
	}
	play=1;
	eq=0;
	norc=0;
	cal=3;
	shortclear = 1;
	break;

	case 'D':///
	if(bit1==2)
	{
		bit1=bit1+1;
	}
	else if (bit1==1)
	{
		bit1=4;
	}
	play=1;
	eq=0;
	norc=0;
	cal=4;
	shortclear = 1;
	break;

	case 'E'://=

	if(bit==0)
	{
	 bit=1;
	 bit1=1;
	 }
	if(bit1==2)
	{
		bit1=5;
	}
	printf("= bit:%d\n",bit);

	sp1=1;
	eq=1;
	norc=0;
	play = 1;
	shortclear=1;
	break;

	case 'F'://clear
	b=0;
	sp0=0;
	fir=-1;
	norc=0;
	eq=0;
	cal = 0;
	play = 0;
	cal2=0;
	bit1=0;
	value=0;
	bit=0;
	break;



	default:
	if(bit==1)
	{
	bit=bit+1;
	}
	printf("bit:%d\n",bit);
	printf("bit1:%d\n",bit1);

	norc =1;
	enter=1;
	play=2;
	eq=0;
	a=(int)keyboard-48;
	break;
	}

	if(bit1==3) // =#+非等號的加減
	{
		printf("3\n");
		value=0;
		cal2=b;
		if(cal==3||cal==4)
			{
				b=1;
			}
		else
			{
				b=0;
			}
		tem=cal;
		bit1=0;
	}
	else if(bit1 ==4) //=cal# 繼續計算
	{
	printf("4\n");


	tem=cal;
	bit1=0;
	if(cal==3||cal==4)
	{
		b=1;
	}
	else if (cal==2)
	{
		b=0;
	}
	else
	{
		b=0;
	}
	}
	else if(bit1==5)//=#=
	{
	 printf("5\n");

	 cal=0;
	 bit1=0;
	}
	else if(bit==2)//=#
	{
	 bit=0;
	 value=0;
	 bit1=2;
	}

	else if (bit==100)
	{
		b=100000;
		value=100000;
		cal2=100000;
	}
}

char KeyInCumulator() // 累加進位  累進暫存器value 累進值b
{


if(norc==1&&value<1000)
{
 	value= value*10+a;
	b=value;
}
else
{
	value=value;



}
}

char Calculator()//運算執行器 eq norc cal
{
 //cal1,cal2儲存數值cal存運算
if(norc==0&&eq==0)
{
	if(fir==0||fir==-1)
	{
		tem=cal;
		cal2=b;
		b=0;
		if(cal==3||cal==4)
		{
			b=1;
		}
		fir=fir+1;
	}
	if(enter==0)
	{
	  if(tem==1||tem==2)
	  {
		b=0;
	  }
	  else if(tem==3||tem==4)
	  {
		b=1;
	  }
	}
	printf("A前:  b=%d,cal2=%d tem=%d cal %d\n",b,cal2,tem,cal);
	switch(tem)
	{
		case 1:
		cal2= cal2+b;
		value=0;
		b=0;
		break;
		case 2:
		cal2=cal2-b;
		value=0;
		b=0;
		break;
		case 3:
		cal2=cal2*b;
		value=0;
		b=1;
		break;
		case 4:
		if(b==0)
		{
			sp0=1;
			cal2=10000;
		}
		else
		{
		cal2=cal2/b;
		}
		value=0;
		b=1;
		break;

	}
	tem=cal;
	printf("A:  b=%d,cal2=%d tem=%d cal %d\n",b,cal2,tem,cal);
	enter=0;
}
else if (norc==0&&eq==1)
{

	if(fir==0||fir==-1)
	{
		tem=cal;
		cal2=b;
		b=0;
		if(cal==3||cal==4)
		{
			b=1;
		}
		fir=fir+1;
	}

	printf("B前:  b=%d,cal2=%d tem=%d cal %d\n",b,cal2,tem,cal);
	switch(cal)
	{
		case 1:
		cal2= cal2+b;

		break;
		case 2:
		cal2=cal2-b;

		break;
		case 3:
		cal2=cal2*b;

		break;
		case 4:
		if(b==0)
		{
			sp0=1;
			cal2=10000;
		}
		else
		{
			cal2=cal2/b;
		}

		break;
	}

	tem=0;
	printf("B:  b=%d,cal2=%d tem=%d cal %d\n",b,cal2,tem,cal);
}


}

char DisplaySelector ()//顯示選擇器ASA_7S00_put(1,0,1,&value);
{
 int i,j,n,count=1,caldisplay;
 display=cal2;
 caldisplay=display;
 if(play==1)
 {

	//printf("calculate\n");

	if(display<9999&&display>0)
	{

		while(caldisplay/ 10 != 0)
		{
			count++;
			caldisplay = caldisplay / 10;
		}
		for(i=3;i>(3-count);i--)

		{
			switch(count)
			{
				case 3:
				I[0]=0x00;
				break;
				case 2:
				I[0]=0x00;
				I[1]=0x00;
				break;
				case 1:
				I[0]=0x00;
				I[1]=0x00;
				I[2]=0x00;

				break;
			}
			n= display%10;
			I[i]=n+0x30;
			display=display/10;
		}
		//printf("I=%c%c%c%c  count=%d\n",I[0],I[1],I[2],I[3],count);
	}
	 else if(display<0&&display>=-999)
	 {
	while(caldisplay/ 10 != 0)
	{
		count++;
		caldisplay = caldisplay / 10;
	}
	for(i=3;i>(3-count);i--)

	{
		switch(count)
		{
			case 3:
			I[0]=0x2d;
			break;
			case 2:
			I[0]=0x00;
			I[1]=0x2d;
			break;
			case 1:
			I[0]=0x00;
			I[1]=0x00;
			I[2]=0x2d;

			break;
		}
		n= abs(display)%10;
		I[i]=n+0x30;
		display=abs(display)/10;

	}
	 }
	 else if(display>9999||display<-999)
	 {
		 printf("bomb");
		 sp0=1;
		 I[0]=0x2d;
		 I[1]=0x2d;
		 I[2]=0x2d;
		 I[3]=0x2d;
	 }
	special=1;

 }

else if(play==0)
{

I[3]=0x30;
I[2]=0x00;
I[1]=0x00;
I[0]=0x00;

}
else if( play==2&&sp0==0)
{


	 display=b;
	 caldisplay=display;
	// printf("key shortclear%d\n",shortclear);
	if(shortclear==1)
	{


	I[3]=0x00;
	I[2]=0x00;
	I[1]=0x00;
	I[0]=0x00;
	shortclear=0;


	}
		if(special==1)//clear後去掉0
		{
		I[3]=0x00;
		I[2]=0x00;
		I[1]=0x00;
		I[0]=0x00;
		special=0;
		}

		while(caldisplay/ 10 != 0)
		{
			count++;
			caldisplay = caldisplay / 10;
		}
		for(i=3;i>(3-count);i--)

		{
			switch(count)
			{
				case 3:
				I[0]=0x00;
				break;
				case 2:
				I[0]=0x00;
				I[1]=0x00;
				break;
				case 1:
				I[0]=0x00;
				I[1]=0x00;
				I[2]=0x00;

				break;
			}
			n= display%10;
			I[i]=n+0x30;
			display=display/10;
		}



		//printf("I=%c%c%c%c\n",I[0],I[1],I[2],I[3]);



}
else if(sp0=1)
 {
	 printf("bomb");
	 cal2=10000;
	 value=10000;
	 b=10000;
	 I[0]=0x2d;
	 I[1]=0x2d;
	 I[2]=0x2d;
	 I[3]=0x2d;
	 bit=100;
	 norc=1;
	 eq=1;
 }

}
