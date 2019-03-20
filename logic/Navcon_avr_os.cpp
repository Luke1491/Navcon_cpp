/*
Navcon_avr_os class

Created: 15-03-2018 by Luke1491
Modified: 15-03-2018 by Luke1491

*/

#include "Navcon_avr_os.h"



Navcon_avr_os::Navcon_avr_os()
{
	//create main modules to proper console operating
	//Ethernet outputCommunication;
	//Konsola konsole;
	//Interface interface;
}
////destructor
Navcon_avr_os::~Navcon_avr_os(){}
////methods
char Navcon_avr_os::showHardwareInfo( unsigned char IndexNo)
{
	return  hardwareInfo[IndexNo];
}

void Navcon_avr_os::init(void)
{
	//Statek ship;
}
