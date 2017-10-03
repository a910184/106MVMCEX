// F_CPU is used by utils/delay.h for _delay_ms function calcutation delay ticks
#define F_CPU 11059200UL

// Main header for ASA M128 Dev board
#include "ASA_Lib.h"

// AVR TWI Bit mask
#include <util/twi.h>

#define _BV(X) (0x01 << X)

//SPI
#define SPI_PORT	PORTB
#define SPI_PIN		PINB
#define SPI_DDR		DDRB
#define SPI_MISO	PB3
#define SPI_MOSI	PB2
#define SPI_SCK		PB1
#define SPI_SS      PB0

//ASA_ID
#define ADDR_PORT	PORTB
#define ADDR_PIN	PINB
#define ADDR_DDR	DDRB
#define ADDR0       PB5
#define ADDR1       PB6
#define ADDR2       PB7

//TWI
#define TWI_PORT	PORTD
#define TWI_PIN		PIND
#define TWI_DDR		DDRD
#define TWI_SCL		PD0
#define TWI_SDA		PD1

#define TWI_STATUS_MASK	0xF8

char ASA_ID_set(unsigned char ASA_ID);

//#define _TWI_DEBUG

void main() {
	
	// Initialize the ASA M128 Library
	ASA_M128_set();

	ASA_ID_set(1);

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

	// Setup TWI Speed
	TWBR = 12;

	// TWPS = 0 => prescale value = 1
	TWSR = 0;

	// Setup TWI Control register for Initialize TWI Module
	TWCR =	(1 << TWEN) |								// Enable TWI interface and release TWI pins.
	(0 << TWIE) | (0 << TWINT) |                // Disable TWI interrupt.
	(0 << TWEA) | (0 << TWSTA) | (0 << TWSTO) | // No signal requests.
	(0 << TWWC);

	// Setup control flag for "Start" & "Enable TWI Module"
	TWCR = ( 0x01 << TWSTA) | ( 0x01 << TWEN) | ( 0x01 << TWINT) ;

	// Wait for Result (while finish operation, Interrupt Flag bit would be set to 1
	while( !(TWCR & (1 << TWINT)));
	

	printf("Start Handshake failed code: %x\n", (TWSR & 0XF8));


	// Write Slave address
	uint8_t slave_addr = 0b01001111;
	TWDR = (slave_addr << 1) | TW_READ;

	// Start Sending address operation
	TWCR = ( 0x01 << TWINT) | ( 0x01 << TWEN );

	// Wait for Result
	while( !(TWCR & (0x01 << TWINT)));

	printf("SLA+R sending code: %x\n", (TWSR & 0XF8));

	// Get data from slave device
	uint8_t raw_thm_data[2];

	// Start receiving data operation
	TWCR = ( 0x01 << TWINT ) | ( 0x01 << TWEN ) | ( 0x01 << TWEA );

	/**** Check Status & Get data****/
	// Wait for result
	while( !(TWCR & (0x01 << TWINT)) );

	printf("DATA+ACK  code = %x \n", TWSR & TWI_STATUS_MASK);

	raw_thm_data[0] = TWDR;
	/*******************************/

	// Start receiving data operation
	TWCR = ( 0x01 << TWINT ) | ( 0x01 << TWEN ) ;

	// Wait for result
	while( !(TWCR & (0x01 << TWINT)));

	printf("DATA+ACK code = %x \n", TWSR & TWI_STATUS_MASK);

	raw_thm_data[1] = TWDR;

	int thm_data = (raw_thm_data[0] << 4) | (raw_thm_data[1] >> 4);

	printf("Raw data %x %x ,Temperature : %f\n", raw_thm_data[0], raw_thm_data[1], thm_data * 0.0625);

	// End the TWI reading
	TWCR |= ( 0x01 << TWSTO ) | ( 0x01 << TWINT) | ( 0x01 << TWEN );
	//}

	#endif // _DEBUG

}