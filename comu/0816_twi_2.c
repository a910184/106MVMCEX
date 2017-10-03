// F_CPU is used by utils/delay.h for _delay_ms function calcutation delay ticks
#define F_CPU 11059200UL

// Main header for ASA M128 Dev board
#include "ASA_Lib.h"

// AVR TWI Bit mask
#include <util/twi.h>

#include "twi-avr-master/twi.h"

#define _BV(X) (0x01 << X)

char ASA_ID_set(unsigned char ASA_ID);

//#define _TWI_DEBUG

void main() {
	
	// Initialize the ASA M128 Library
	ASA_M128_set();


	#ifdef _TWI_DEBUG
	
	// Setup SDA & SCL AS INPUT
	TWI_DDR |=  (_BV(TWI_SCL) | _BV(TWI_SDA));
	TWI_PORT &= ~(_BV(TWI_SCL) | _BV(TWI_SDA) );

	// Polling data
	while(1) printf("TWI_SDA = %d, TWI_SCL = %d\n",
	TWI_PIN & _BV(TWI_SDA),
	TWI_PIN & _BV(TWI_SCL));
	
	// Block the program
	while(1);

	#else

	// SCL freq = (CPU Clock) / (16 + 2(TWBR) * (prescale value))
	// 400 kHz = (16MHz) / (16 + 2(12) * (1))
	TWBR = 12;
	TWSR = 0;   // TWPS = 0 => prescale value = 1
	TWCR = (1 << TWEN) |                               // Enable TWI interface and release TWI pins.
	(0 << TWIE) | (0 << TWINT) |                // Disable TWI interupt.
	(0 << TWEA) | (0 << TWSTA) | (0 << TWSTO) | // No signal requests.
	(0 << TWWC);

	uint8_t sla = 0b01001111;

	uint8_t rx[128];

	while(1) {

		TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTA);

		while(!(TWCR & _BV(TWINT)));

		printf("2TWSR = %x\n", TWSR & 0XF8);

		TWDR = sla << 1 | 1;
		
		TWCR = _BV(TWINT) | _BV(TWEN); // NACK

		while(!(TWCR & _BV(TWINT)));

		printf("2TWSR = %x\n", TWSR & 0XF8);


		TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);

		while(!(TWCR & _BV(TWINT)));

		printf("2TWSR = %x\n", TWSR & 0XF8);

		rx[0] = TWDR;

		TWCR = _BV(TWINT) | _BV(TWEN);

		while(!(TWCR & _BV(TWINT)));

		printf("2TWSR = %x\n", TWSR & 0XF8);

		rx[1] = TWDR;

		TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);

		//while(!(TWCR & _BV(TWINT)));



		


		//twi_read(sla, rx, 2);
		_delay_ms(250);

		int thm_data = rx[0] << 4 | rx[1] >> 4;
		printf("rx[0] = %x, rx[1] = %x, thermal = %f\n", rx[0], rx[1], thm_data * 0.0625);
	}

	#endif // _DEBUG

}