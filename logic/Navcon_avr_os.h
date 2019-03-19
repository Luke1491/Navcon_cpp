/*
Navcon_avr_os - main class to provide hardware handling of NAVCON console
Contains timers setup, hardware data. All classes can get hardware data from main array 
to perform stability working


*/

#include "NAVCON_SYMBOLS.h"
#include "Statek.h"

#ifndef NAVCON_AVR_OS_H
#define NAVCON_AVR_OS_H

const unsigned char hardwareArrayLen = 100;
///////////////////////////////////////////////////////////////////
class Navcon_avr_os
{

public:
char hardwareInfo [hardwareArrayLen];


//constructor
Navcon_avr_os();

//destructor
~Navcon_avr_os();

char showHardwareInfo( unsigned char IndexNo);
void getHardwareInfo(char data, char IndexNo);

	
};

#endif