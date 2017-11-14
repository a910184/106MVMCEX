#include "ASA_Lib.h"

int main(){
	ASA_M128_set();
	int data;
	while (1) {
		DDRA = 0xff;

		PORTA = 0x00;
		printf("%d\n",data );
	}
}
