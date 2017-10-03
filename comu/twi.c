#define F_CPU  11059200UL
#include "ASA_Lib.h"
#include<stdlib.h>



void set_twi()
{
    DDRB |= (1<<PB5)|(1<<PB6)|(1<<PB7); // asa address use PB 5:7 set output
    PORTB = (1<<PB5);
    TWBR = 4; //baud rate set


}


int main()
{
	int temp;
    int raw_thm_data[2];
	ASA_M128_set();
	set_twi();

	while(1)
	{
        TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
        while (!(TWCR & (1<<TWINT)));
        printf("START status code return  %x\n",(TWSR & 0xF8) );
    //    if ((TWSR & 0xF8) != START);
/*****************************************************/
        uint8_t slave_addr = 0b01001111<<&0xfe;
        TWDR = (slave_addr << 1) &0xfe;

        TWCR = (1<<TWINT) |(1<<TWEN);
        while (!(TWCR & (1<<TWINT)));
        printf("SLA_W status code return  %x\n",(TWSR & 0xF8) );
    //    if ((TWSR & 0xF8) !=MT_SLA_ACK)
/*****************************************************/

        TWDR = 0x01 ;// TMP175 pointer register p1=0 p0=1 set to configuration register
        TWCR = ( 1 << TWINT ) | ( 1 << TWEN );
        while (!(TWCR & (1<<TWINT)));
        printf("MT_DATA_ACK status code return %x \n",(TWSR & 0xF8));

/*****************************************************/
        TWDR = (1<<6|1<<5);
        TWCR = (1<<TWINT) |(1<<TWEN);


        while (!(TWCR & (1<<TWINT)));
        printf("MT_DATA_ACK status code return  %x\n",(TWSR & 0xF8));
            /*****************************************************/
                TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        /*****************************************************/




/*********************************************************/
        TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
        while (!(TWCR & (1<<TWINT)));
        printf("START status code return  %x\n",(TWSR & 0xF8) );
    //    if ((TWSR & 0xF8) != START);
/*****************************************************/

        TWDR = (slave_addr << 1) &0xfe;

        TWCR = (1<<TWINT) |(1<<TWEN);
        while (!(TWCR & (1<<TWINT)));
        printf("SLA_W status code return  %x\n",(TWSR & 0xF8) );
    //    if ((TWSR & 0xF8) !=MT_SLA_ACK)
        TWDR = 0x00;
        TWCR = ( 1 << TWINT ) | ( 1 << TWEN );
        while (!(TWCR & (1<<TWINT)));
        printf("MT_DATA_ACK status code return %x \n",(TWSR & 0xF8));

/*****************************************************/
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
/*****************************************************/

_delay_ms(100);


/*****************************************************/
        TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
        while (!(TWCR & (1<<TWINT)));
        printf("START status code return  %x\n",(TWSR & 0xF8) );
    //    if ((TWSR & 0xF8) != START);
/*****************************************************/
        TWDR = (slave_addr << 1) | 0x01;
        TWCR = (1<<TWINT) |(1<<TWEN);
        while (!(TWCR & (1<<TWINT)));
        printf("SLA_R status code return  %x\n",(TWSR & 0xF8) );
    //    if ((TWSR & 0xF8) !=MT_SLA_ACK)
/*****************************************************/
        TWCR = ( 0x01 << TWINT ) | ( 0x01 << TWEN ) | ( 0x01 << TWEA );
        while (!(TWCR & (1<<TWINT)));
        printf("MR_DATA_ACK status code return %x \n",(TWSR & 0xF8));
    	raw_thm_data[0] = TWDR;
        TWCR = (1<<TWINT) |(1<<TWEN);
/***********************************************************/
        while (!(TWCR & (1<<TWINT)));
        printf("MR_DATA_ACK status code return  %x\n",(TWSR & 0xF8));
        raw_thm_data[1] = TWDR;
        temp = ((raw_thm_data[0]<<4)|(raw_thm_data[1]>>4));
        printf("Raw data %x %x ,Temperature : %f\n", raw_thm_data[0], raw_thm_data[1], temp * 0.0625);
/*****************************************************/
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
        _delay_ms(100);
	}
}
