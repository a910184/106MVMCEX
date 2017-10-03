#include "ASA_Lib.h"
void cloc();//時間計算
void set_tmr2();//時間中斷暫存器腳位寫入
void display();//選擇顯示時間來源
void alarm();//鬧鐘

int keyboard,a=0,func=0,chooseclock=0,key=0,state=0,finish=0,settime=0,alar=0,timeup=0,countdown=0,rupt=0,alarmmin,alarmsec;
char ddata=0;
int min=0;
volatile long tick = 0;
char I[4]={48,48,48,48};
char buffer[4]={48,48,48,48};

ISR(TIMER2_COMP_vect)
{
	static int counter = 0;
	counter++;
	if (counter == 200) {
		counter = 0;
		tick++;

	}
}

void main()
{
	ASA_M128_set();
	ASA_7S00_set(1, 200,0xff ,0, ddata);
	ASA_KB00_set(2,200 , 0xff,0, ddata=1);//data= 1 ascii,= 0 keyboard #
	set_tmr2();
	int keyflag,temp;
	long min=0,sec=0;
	while (1)
	{
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
				  event();
				  keyflag=0;
			  }
		  }
		   cloc();
		  alarm();

		 display();
		 // printf("%ld,%ld,%ld\n",min,sec,tick);
	}
}
	void set_tmr2() {

		// Use pre-scaler that clk/256
		TCCR2 |= 0x01 << CS22;
		TCCR2 &= ~(0x01 << CS21);
		TCCR2 &= ~(0x01 << CS20);

		// Use CTC Mode
		TCCR2 |= 0x01 << WGM21;
		TCCR2 &= ~(0x01 << WGM20);
		// Without output any signal for CTC mode
		TCCR2 &= ~(0x01 << COM21);
		TCCR2 &= ~(0x01 << COM20);
		// Set compare register to  110592 / (2*256) = 215 For 100 Hz, 10 ms
		OCR2 = 215;

		// Clear TMR2 Output Compare interrupt Flag
		TIFR &= ~(0x01 << OCF2);
		// Enable Output Compare interrupt
		TIMSK |= 0x01 << OCIE2;

	}
void	KeyResolver()
{
	if(func==4||func==5||func==2)
	{

		switch (keyboard)
		{
			case 'A':func=1;key=0;break;//finish
			case 'B':func=2;key=1;break;//dicard
			case 'C':key=0;break;//clockonoff
			case 'D':key=0;break;//set time
			case 'E':key=0;break;//set alarm

			default:key=1;a=keyboard;break;

		}
	}
	else
	{
			switch (keyboard)
			{
				case 'A':break;//finish
				case 'B':break;//dicard
				case 'C':func=3;key=0;break;//clockonoff
				case 'D':func=4;key=0;break;//set time
				case 'E':func=5;key=0;break;//set alarm
				default:key=1;a=keyboard;break;

			}
	}

}


void event()//(1)state=1 設定時間 no blink(2)設定鬧鈴state=2 blink(3) state=0鬧鈴關閉  no blink，(4)state=3時間未到no blink(5)state=4 blink 時間到
{

	switch (func)
	{
		case 1:

		if(state==2)
		{
			alarmmin=(buffer[0]-48)*10+buffer[1]-48;
			alarmsec=(buffer[2]-48)*10+buffer[3]-48;
			if(alarmmin>59||alarmsec>59)
			{
				alarmmin=0;
				alarmsec=0;
			}
			alar=1;
		}
		else if(state==1)
		{
			min=(buffer[0]-48)*10+buffer[1]-48;
			tick=(buffer[2]-48)*10+buffer[3]-48;
			if(min>59||tick>59)
			{
			 min=0;
			 tick=0;
			}

		}
		printf("%d,%d\n",alarmmin,alarmsec);
		buffer[0]=48;buffer[1]=48;buffer[2]=48;buffer[3]=48;
		state=0;
		break;
		case 2:buffer[0]=48;buffer[1]=48;buffer[2]=48;buffer[3]=48;func=state+3;break;
		case 3:alar=~alar;chooseclock=0; ASA_7S00_set(1, 200,0xff ,0,0x00);break;
		case 4:state=1;enter();break;//set time
		case 5:state=2;enter();break;//set alarm

	}
	switch(state)
	{
		case 0:ASA_7S00_set(1, 200,0xff ,0,0x00);chooseclock=0;break;
		case 1:ASA_7S00_set(1, 200,0xff ,0,0x00);chooseclock=1;break;//set time
		case 2:ASA_7S00_set(1, 200,0xff ,0,0x0f);chooseclock=1;break;//set alarm

	}
}

void enter()
{
	int i=0;
	if(key==1)
	{
		for(i=0;i<3;i++)
		{buffer[i]=buffer[i+1];}
	buffer[3]=a;
	}
}

void alarm()
{
	if(alar==1&&alarmmin==min&&alarmsec==tick)
	{
	 ASA_7S00_set(1, 200,0xff ,0,0x0f);
	 chooseclock=0;
	printf("times up %d\n%d\n%s\n",alarmmin,alarmsec,buffer);
	}
}

void cloc()
{
			if(min>59)
			{
				min=0;
			}
			if(tick==60)
			{
				tick=0;
				min++;
			}

			I[0]=(char)min/10+48;
			I[1]=(char)min%10+48;
			I[2]=(char)(tick/10)+48;
			I[3]=(char)(tick%10)+48;

}

void display()
{
	if(chooseclock==0)
	{
		  ASA_7S00_put(1,0,4,&I);
	}
	else if(chooseclock==1)
	{
		ASA_7S00_put(1,0,4,&buffer);
	}


}
