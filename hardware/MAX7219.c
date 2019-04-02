/*
 * MAX7219.c
 *
 * Created: 2017-05-26 18:49:22
 *  Author: LUKE
 */ 
// 16MHz clock
//#define F_CPU 16000000UL

#include "../logic/NAVCON_SYMBOLS.h"

// Outputs, pin definitions
#define PIN_SCK                   NAVCON_SPI_SCK_PIN
#define PIN_MOSI                  NAVCON_SPI_MOSI_PIN
#define PIN_SS                    NAVCON_MANIP_DISP_SPI_SS_PIN

#define ON                        1
#define OFF                       0

#define MAX7219_LOAD1             PORTB |= (1<<PIN_SS)
#define MAX7219_LOAD0             PORTB &= ~(1<<PIN_SS)

#define MAX7219_MODE_DECODE       0x09
#define MAX7219_MODE_INTENSITY    0x0A
#define MAX7219_MODE_SCAN_LIMIT   0x0B
#define MAX7219_MODE_POWER        0x0C
#define MAX7219_MODE_TEST         0x0F
#define MAX7219_MODE_NOOP         0x00

// I only have 3 digits, no point having the
// rest. You could use more though.
#define MAX7219_DIGIT0            0x01
#define MAX7219_DIGIT1            0x02
#define MAX7219_DIGIT2            0x03
#define MAX7219_DIGIT3            0x04
#define MAX7219_DIGIT4            0x05
#define MAX7219_DIGIT5            0x06
#define MAX7219_DIGIT6            0x07
#define MAX7219_DIGIT7            0x08

#define MAX7219_CHAR_BLANK        0xF
#define MAX7219_CHAR_NEGATIVE     0xA

#define MAX7219_CHAR_E		      0xB

#include <avr/io.h>
#include "MAX7219.h"
#include <util/atomic.h>




char digitsInUse = 8;

void SPI_init()
{
	// SPI Enable, Master mode
	SPCR |= (1 << SPE) | (1 << MSTR)| (1<<SPI2X); //TRYB MASTER, PRESKALER F_CPU/2
}

void spiEnableSSInPORTB(char ss_pin) //set actual pin as an output (pin is required to be in group B)
{
	
	DDRB |= (1 << ss_pin);
}

void MAX7219_Init(char pin_ss) {
	//SPI inicjalization made in enc28j60.c in enc28j60Init() function. Parameters set as below:
	//If you not using enc28j60, uncomment below lines
	
	// SCK MOSI CS/LOAD/SS 
	DDRB |= (1 << PIN_SCK) | (1 << PIN_MOSI);
	spiEnableSSInPORTB(pin_ss);
	SPI_init();
	

	// Decode mode to "Font Code-B"
	MAX7219_writeData(MAX7219_MODE_DECODE, 0xFF);

	// Scan limit runs from 0.
	MAX7219_writeData(MAX7219_MODE_SCAN_LIMIT, digitsInUse - 1);
	MAX7219_writeData(MAX7219_MODE_INTENSITY, 10);
	MAX7219_writeData(MAX7219_MODE_POWER, ON);
}

void spiSendByte (char databyte)
{
	// Copy data into the SPI data register
	SPDR = databyte;
	// Wait until transfer is complete
	while (!(SPSR & (1 << SPIF)));
}

void MAX7219_writeData(char data_register, char data)
{
	MAX7219_LOAD0;
	// Send the register where the data will be stored
	spiSendByte(data_register);
	// Send the data to be stored
	spiSendByte(data);
	MAX7219_LOAD1;
}

void MAX7219_clearDisplay(void)
{
	char i = digitsInUse;
	// Loop until 0, but don't run for zero
	do {
		// Set each display in use to blank
		MAX7219_writeData(i, MAX7219_CHAR_BLANK);
	} while (--i);
}

void MAX7219_displayNumber(volatile long number)
{
	char negative = 0;

	// Convert negative to positive.
	// Keep a record that it was negative so we can
	// sign it again on the display.
	if (number < 0) {
		negative = 1;
		number *= -1;
	}


	MAX7219_clearDisplay();

	// If number = 0, only show one zero then exit
	if (number == 0) {
		MAX7219_writeData(MAX7219_DIGIT0, 0);
		return;
	}
	
	// Initialization to 0 required in this case,
	// does not work without it. Not sure why.
	char i = 0;
	
	// Loop until number is 0.
	do {
		MAX7219_writeData(++i, number % 10);
		// Actually divide by 10 now.
		number /= 10;
	} while (number);

	// Bear in mind that if you only have three digits, and
	// try to display something like "-256" all that will display
	// will be "256" because it needs an extra fourth digit to
	// display the sign.
	if (negative) {
		MAX7219_writeData(i, MAX7219_CHAR_NEGATIVE);
	}
}

void MAX7219DisplayFirstFourDigits(int number, unsigned char displayActive) //disply first tetrade
{
	if(displayActive)
	{
		unsigned char positive = 1; //check if number id positive (1 -positive | 0 - negative)
		if(number < 0) positive = 0; //check if number is negative
		if(positive == 0 && number > 999) // no space for display minus in digit four -> display -E1-
		{
			MAX7219_writeData(MAX7219_DIGIT0, MAX7219_CHAR_NEGATIVE); //minus
			MAX7219_writeData(MAX7219_DIGIT1, 1); //1
			MAX7219_writeData(MAX7219_DIGIT2, MAX7219_CHAR_E); //E
			MAX7219_writeData(MAX7219_DIGIT3, MAX7219_CHAR_NEGATIVE); //minus
		}
		else if(positive == 0 && number < 999)
		{ //display negative number
			MAX7219_writeData(MAX7219_DIGIT0, number % 10 ); //cyfra dziesiêtna
			MAX7219_writeData(MAX7219_DIGIT1, ((number / 10) % 10) | 0x80 ); //cyfra jednosci + kropka
			MAX7219_writeData(MAX7219_DIGIT2, (number / 100) % 10 ); //cyfra dziêsiêtnych
			MAX7219_writeData(MAX7219_DIGIT3, MAX7219_CHAR_NEGATIVE );
		}
		else //display positive number
		{
			MAX7219_writeData(MAX7219_DIGIT0, number % 10 ); //cyfra dziesiêtna
			MAX7219_writeData(MAX7219_DIGIT1, ((number / 10) % 10) | 0x80 ); //cyfra jednosci + kropka
			MAX7219_writeData(MAX7219_DIGIT2, (number / 100) % 10 ); //cyfra dziêsiêtnych
			MAX7219_writeData(MAX7219_DIGIT3, (number / 1000) % 10 ); //cyfra setnych
		}
		
	}
	else // displyActive in 0 -> no display
	{
		MAX7219_writeData(MAX7219_DIGIT0, MAX7219_CHAR_NEGATIVE); //wyœwitl kreskê
		MAX7219_writeData(MAX7219_DIGIT1, MAX7219_CHAR_NEGATIVE); //wyœwitl kreskê
		MAX7219_writeData(MAX7219_DIGIT2, MAX7219_CHAR_NEGATIVE); //wyœwitl kreskê
		MAX7219_writeData(MAX7219_DIGIT3, MAX7219_CHAR_NEGATIVE); //wyœwitl kreskê
	}
	
}

void MAX7219DisplaySecondFourDigits(int number, unsigned char displayActive) //disply first tetrade
{
	if(displayActive == 1)
	{
		unsigned char positive = 1; //check if number id positive (1 -positive | 0 - negative)
		if(number < 0) positive = 0; //check if number is negative
		if(positive == 0 && number > 999) // no space for display minus in digit four -> display -E1-
		{
			 MAX7219DisplayErrorE(1);
		}
		else if(positive == 0 && number < 999)
		{ //display negative number
			MAX7219_writeData(MAX7219_DIGIT0, number % 10 ); //cyfra dziesiêtna
			MAX7219_writeData(MAX7219_DIGIT1, ((number / 10) % 10) | 0x80 ); //cyfra jednosci + kropka
			MAX7219_writeData(MAX7219_DIGIT2, (number / 100) % 10 ); //cyfra dziêsiêtnych
			MAX7219_writeData(MAX7219_DIGIT3, MAX7219_CHAR_NEGATIVE );
		}
		else //all is ok - display number
		{
			MAX7219_writeData(MAX7219_DIGIT0, number % 10 ); //cyfra dziesiêtna
			MAX7219_writeData(MAX7219_DIGIT1, ((number / 10) % 10) | 0x80 ); //cyfra jednosci + kropka
			MAX7219_writeData(MAX7219_DIGIT2, (number / 100) % 10 ); //cyfra dziêsiêtnych
			MAX7219_writeData(MAX7219_DIGIT3, (number / 1000) % 10 ); //cyfra setnych
		}
		
	}
	else if(displayActive == 0)// displyActive == 0 -> no display
	{
		MAX7219_writeData(MAX7219_DIGIT0, MAX7219_CHAR_NEGATIVE); //wyœwitl kreskê
		MAX7219_writeData(MAX7219_DIGIT1, MAX7219_CHAR_NEGATIVE); //wyœwitl kreskê
		MAX7219_writeData(MAX7219_DIGIT2, MAX7219_CHAR_NEGATIVE); //wyœwitl kreskê
		MAX7219_writeData(MAX7219_DIGIT3, MAX7219_CHAR_NEGATIVE); //wyœwitl kreskê
	}
	else //status is not ON or OFF -> display error
	{
		
	}
	
}

void MAX7219_autopilotOFF(void)
{
	MAX7219_writeData(MAX7219_DIGIT0, MAX7219_CHAR_NEGATIVE); //wyœwitl kreskê
	MAX7219_writeData(MAX7219_DIGIT1, MAX7219_CHAR_NEGATIVE); //wyœwitl kreskê
	MAX7219_writeData(MAX7219_DIGIT2, MAX7219_CHAR_NEGATIVE); //wyœwitl kreskê
	MAX7219_writeData(MAX7219_DIGIT3, MAX7219_CHAR_NEGATIVE); //wyœwitl kreskê
	MAX7219_writeData(MAX7219_DIGIT4, MAX7219_CHAR_NEGATIVE); //wyœwitl kreskê
	MAX7219_writeData(MAX7219_DIGIT5, MAX7219_CHAR_NEGATIVE); //wyœwitl kreskê
	MAX7219_writeData(MAX7219_DIGIT6, MAX7219_CHAR_NEGATIVE); //wyœwitl kreskê
	MAX7219_writeData(MAX7219_DIGIT7, MAX7219_CHAR_NEGATIVE); //wyœwitl kreskê
}

void MAX7219DisplayErrorE(unsigned char numberOfError) //dispaly "-E'numberOfError'-"
{
	MAX7219_writeData(MAX7219_DIGIT0, MAX7219_CHAR_NEGATIVE); //minus
	MAX7219_writeData(MAX7219_DIGIT1, numberOfError);
	MAX7219_writeData(MAX7219_DIGIT2, MAX7219_CHAR_E); //E
	MAX7219_writeData(MAX7219_DIGIT3, MAX7219_CHAR_NEGATIVE); //minus
}


	

