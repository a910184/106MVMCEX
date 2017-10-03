/*
char ASA_DIO00_put(char ASA_ID, char LSByte, char Bytes, void* Data_p);
char ASA_DIO00_get(char ASA_ID, char LSByte, char Bytes, void* Data_p);
char ASA_DIO00_fpt(char ASA_ID, char LSByte, char Mask, char shift, char Data);
char ASA_DIO00_fgt(char ASA_ID, char LSByte, char Mask, char shift, void *Data_p);

*/
#include "ASA_Lib.h"
#include<stdlib.h>

int main(void)
{
	ASA_M128_set();

	int pin,opin,port,oport,i,j;
	char input,output,mask,shift=0x00,data=0x00,temp;
	char omask,oshift=0x00,odata=0x00;
	
	printf("output portPIN:(a-f0-7)");
	scanf("%c%d",&output,&opin);
	
	printf("input portPIN:(a-f0-7)");
	scanf("%c%d",&input,&pin);

	
	
switch(input)
{
case 'a':
	 port= 0; 
  break;	
case 'b':
   port= 1;
   break;	
case 'c':
   port= 2;
   break;	
case 'd':
   port= 3;
   break;	
case 'e':
   port=4;
   break;	
case 'f':
port= 5; 
 break;		
}

switch(pin)
{
	case 0:
	 mask= 0x01; 
  break;	
case 1:
	 mask= 0x02; 
  break;	
case 2:
   mask= 0x04;
   break;	
case 3:
   mask= 0x08;
   break;	
case 4:
   mask= 0x10;
   break;	
case 5:
   mask= 0x20;
   break;	
case 6:
mask= 0x40; 
 break;		
case 7:
	mask= 0x80; 
  break;		
}


//input bit set 0

switch(output)
{
case 'a':
	 oport= 100; 
  break;	
case 'b':
   oport= 101;
   break;	
case 'c':
   oport= 102;
   break;	
case 'd':
   oport= 103;
   break;	
case 'e':
   oport= 104;
   break;	
case 'f':
oport= 105; 
 break;		
 }
switch(opin)
{
case 0:
	 omask= 0x01; 
  break;	
case 1:
	 omask= 0x02; 
  break;	
case 2:
   omask= 0x04;
   break;	
case 3:
   omask= 0x08;
   break;	
case 4:
   omask= 0x10;
   break;	
case 5:
   omask= 0x20;
   break;	
case 6:
omask= 0x40; 
 break;		
case 7:
	omask= 0x80; 
  break;	

}

	

	

	while(1)
{
	ASA_DIO00_fgt(3,(char)port,mask,shift,&data);
	ASA_DIO00_fpt(3,(char)oport,omask,shift,odata);
	printf("%2x\n",data);
	printf("%2x\n",odata);
_delay_ms(200);
	
}

	return 0;
}

