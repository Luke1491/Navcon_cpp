#include <avr/io.h>
#include "Interface.h"
#include "common.h"
#include "NAVCON_SYMBOLS.h"
#include "Disp_manip_cog.h"

Interface::Interface(const unsigned int &course, const int &speed, const int &rzadanyCourse, const int &rzadanaSpeed)
{
	interfaceMAINSpeed = course;
	interfaceMAINSpeed = speed;
	interfaceManipCourse = rzadanyCourse;
	interfaceManipSpeed = rzadanaSpeed;
	
	//create components
	Disp_manip_cog courseManipDispl(USE_SPI, NAVCON_MANIP_DISP_SPI_SS_PIN, interfaceManipCourse, consoleMainArray[NAVCON_AUTOPILOT_MODE]);
	dispManipCog = &courseManipDispl;
}

Interface::~Interface(){}


void Interface::getDataToDisplay(const unsigned int &course, const int &speed, const int &rzadanyCourse, const int &rzadanaSpeed)
{
	interfaceMAINSpeed = course;
	interfaceMAINSpeed = speed;
	interfaceManipCourse = rzadanyCourse;
	interfaceManipSpeed = rzadanaSpeed;
}

void Interface::reset(void)
{
// 	rose->reset();
// 	mainDispCog->reset();
// 	mainDispSog->reset();
// 	dispManipCog->reset();
// 	dispManipSog->reset();
// 	cogLed->reset();
// 	sogLed->reset()->reset();
	
}

void Interface::refreshDisplays()
{
	dispManipCog->ShowRequiredCourse(interfaceManipCourse, consoleMainArray[NAVCON_AUTOPILOT_ID]);
}