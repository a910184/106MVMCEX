#include "ASA_Lib.h"
#include<stdlib.h>

int main(void)
{
	ASA_M128_set();
 DDRE = DDRE & ~(0x01<<5);
	return 0;
}
