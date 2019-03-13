/*
Navcon_avr_os - main class to provide hardware handling of NAVCON console
Contains timers setup, hardware data. All classes can get hardware data from main array 
to perform stability working


*/

#include "NAVCON_SYMBOLS.h"

#ifdef NAVCON_AVR_OS_H
#define NAVCON_AVR_OS_H


constexpr uint8_t hardwareArrayLen = 100;
///////////////////////////////////////////////////////////////////
class Navcon_avr_os
{
uint8_t hardwareInfo [hardwareArrayLen];

public:
//constructors
Navcon_avr_os();
Navcon_avr_os(uint8_t mode);
//destructor
~Navcon_avr_os();

uint8_t showHandwareInfo( uint8_t IndexNo);
void pushHardwareInfo(uint8_t data, uint8_t IndexNo);
	
};

#endif