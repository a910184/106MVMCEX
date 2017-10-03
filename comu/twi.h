#ifndef _TWI_H
#define _TWI_H
/**twi master trasitor***/
#define START 0x08
#define RESTART 0x10
#define SLAW_A 0x18
#define SLAW_N 0x20
#define DATA_A 0x28
#define DATA_N 0x30
#define LOST 0x38

/****twi master reciever***/
void twiini()
{
    DDRB |= (1<<PB5)|(1<<PB6)|(1<<PB7); // asa address use PB 5:7 set output
    PORTB = (1<<PB5);
    TWBR = 4; //baud rate set

}
int twistart()
{

    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    return (TWSR & 0xF8) ;
}
int msend(int data)
{
    TWDR = data ;
    TWCR = (1<<TWINT) |(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    return (TWSR & 0xf8);
}
void mrecieveack()
{
    TWCR = ( 0x01 << TWINT ) | ( 0x01 << TWEN ) | ( 0x01 << TWEA );
}

int mrecieve(int* data)
{
        //printf("memory %x\n", &data);
        while (!(TWCR & (1<<TWINT)));
        *data = TWDR;
        //printf("data %x\n",data);
        TWCR = (1<<TWINT) |(1<<TWEN) | ( 0x01 << TWEA );

        return (TWSR & 0xf8);
}

int twistop()
{
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}
#endif
