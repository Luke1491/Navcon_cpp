#include "Disp_manip_cog.h"
#include "NAVCON_SYMBOLS.h"
#include "common.h"
#include "../hardware/MAX7219.h"

#define NEGATIVE_NUMBER_ERROR			1
#define TO_BIG_NEGATIVE_NUMBER_ERROR	2

Disp_manip_cog::Disp_manip_cog(char typeOfCommunication, unsigned char ss_pin, unsigned int reqCourse, char autopilotMode):Display(typeOfCommunication)
{
	MAX7219_Init(ss_pin);		//initialize MAX7219 and specify ss pin to communicate with this ic
	this -> ShowRequiredCourse(reqCourse, autopilotMode); //display required course
	consoleMainArray[NAVCON_SPI] = NAVCON_STATUS_ON;
}

void Disp_manip_cog::ShowRequiredCourse(int requiredCourse, char autopilotMode)//course is displayed in second max7219 tetrade (see pcb)
{
	if(requiredCourse < 0) {MAX7219DisplayErrorE(NEGATIVE_NUMBER_ERROR);} //display "-E1-"
	else{MAX7219DisplaySecondFourDigits(requiredCourse, autopilotMode);}
	
}
	