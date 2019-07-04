/*
 * MAX7219.h
 *
 * Created: 2017-05-26 18:52:22
 *  Author: LUKE
 */ 
#include "avr/io.h"

#ifndef MAX7219_H_
#define MAX7219_H_
#ifdef __cplusplus
extern "C" {
	#endif
	void SPI_init();
	void MAX7219_Init(char pin_ss);
	void spiSendByte (char databyte);
	void MAX7219_writeData(char data_register, char data);
	void MAX7219_clearDisplay(void);
	void MAX7219_displayNumber(volatile long number);
	void MAX7219_autopilotOFF(void); //wyœwietla kreski na wyœwietlaczu
	void MAX7219DisplayFirstFourDigits(int number, unsigned char displayActive); //if displayActive is not 0 or 1 -> display error"-E1-"
	void MAX7219DisplaySecondFourDigits(int number, unsigned char displayActive);//if displayActive is not 0 or 1 -> display error"-E1-"
	void MAX7219DisplayErrorE(unsigned char numberOfError);
	
	#ifdef __cplusplus
}
#endif

#endif /* MAX7219_H_ */
