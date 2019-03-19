/*
 * ws2812b.h
 *
 * Created: 2017-05-27 17:48:07
 *  Author: LUKE
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>


#ifndef WS2812B_H_
#define WS2812B_H_

///////////////////////////////////////////////////////////////////////
// Define Reset time in �s.
//
// This is the time the library spends waiting after writing the data.
//
// WS2813 needs 300 �s reset time
// WS2812 and clones only need 50 �s
//
///////////////////////////////////////////////////////////////////////

#define ws2812_resettime 100

///////////////////////////////////////////////////////////////////////
// Define I/O pin
///////////////////////////////////////////////////////////////////////


#define ws2812_port B     // Data port
#define ws2812_pin  2     // Data out pin


/*
 *  Structure of the LED array
 *
 * cRGB:     RGB  for WS2812S/B/C/D, SK6812, SK6812Mini, SK6812WWA, APA104, APA106
 * cRGBW:    RGBW for SK6812RGBW
 */

typedef struct  { uint8_t g; uint8_t r; uint8_t b; } cRGB;
struct cRGBW { uint8_t g; uint8_t r; uint8_t b; uint8_t w;};
	
#define TARCZA_MAXPIX 95 //liczba led�w na tarczy g��wnej
#define STER_MAXPIX 20 //liczba led�w na wska�niku wychylenia steru
#define PREDKOSC_MAXPIX 20 //liczba led�w na wska�niku nastawy pr�dko�ci

#define TARCZA_PIN (1<<5)   //PORTB pin do kt�rego b�dzie pod��czona tarcza
#define PREDKOSC_PIN (1<<4) //PORTD pin do kt�rego bedzie podl�czony pasek z nastaw� pr�dko�ci
#define STER_PIN (1<<6)     //PORTB pin do kt�rego b�dzie pod��czony pasek z wychyleniem steru

extern cRGB kolory[10];
extern cRGB TARCZA_led[TARCZA_MAXPIX];
extern cRGB STER_led[STER_MAXPIX];
extern cRGB PREDKOSC_led[PREDKOSC_MAXPIX];


/* User Interface
 * 
 * Input:
 *         ledarray:           An array of GRB data describing the LED kolory
 *         number_of_leds:     The number of LEDs to write
 *         pinmask (optional): Bitmask describing the output bin. e.g. _BV(PB0)
 *
 * The functions will perform the following actions:
 *         - Set the data-out pin as output
 *         - Send out the LED data 
 *         - Wait 50�s to reset the LEDs
 */



void ws2812_setleds     (cRGB  *ledarray, uint16_t number_of_leds);
void ws2812_setleds_pin (cRGB  *ledarray, uint16_t number_of_leds,uint8_t pinmask);
void ws2812_setleds_rgbw(struct cRGBW *ledarray, uint16_t number_of_leds);

/* 
 * Old interface / Internal functions
 *
 * The functions take a byte-array and send to the data output as WS2812 bitstream.
 * The length is the number of bytes to send - three per LED.
 */

void ws2812_sendarray     (uint8_t *array,uint16_t length);
void ws2812_sendarray_mask(uint8_t *array,uint16_t length, uint8_t pinmask);


/*
 * Internal defines
 */

#define CONCAT(a, b)            a ## b
#define CONCAT_EXP(a, b)   CONCAT(a, b)

#define ws2812_PORTREG  CONCAT_EXP(PORT,ws2812_port)
#define ws2812_DDRREG   CONCAT_EXP(DDR,ws2812_port)
//****************************G��WNA FUNKCJA************************************

//funkcja u�ywana w innej funkcji - normalnie nie b�d� jej u�ywa�
void ws2812_wyslij_dane_PORTB(uint8_t *data,uint16_t datlen,uint8_t maskhi);
void ws2812_wyslij_dane_PORTC(uint8_t *data,uint16_t datlen,uint8_t maskhi);
void ws2812_wyslij_dane_PORTD(uint8_t *data,uint16_t datlen,uint8_t maskhi);
//data --> wskaznik do tablicy
//datlen --> ilo�� bajt�w do wys�ania (w strukturze o wielko�ci 3 bajt�w ta zmienna musi by� powi�kszona 3 razy)
//maskhi  --> numer pinu rejestru - mo�e by� np _BV(2) lub (1<<2)





#endif /* WS2812B_H_ */