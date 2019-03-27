#include "Interface.h"
#include "common.h"
#include "NAVCON_SYMBOLS.h"

Interface::Interface(const unsigned int &course, const int &speed, const int &rzadanyCourse, const int &rzadanaSpeed)
{
	interfaceMAINSpeed = course;
	interfaceMAINSpeed = speed;
	interfaceManipCourse = rzadanyCourse;
	interfaceManipSpeed = rzadanaSpeed;
}

Interface::~Interface(){}


void Interface::getDataToDisplay(const unsigned int &course, const int &speed, const int &rzadanyCourse, const int &rzadanaSpeed)
{
	interfaceMAINSpeed = course;
	interfaceMAINSpeed = speed;
	interfaceManipCourse = rzadanyCourse;
	interfaceManipSpeed = rzadanaSpeed;
}

// void Interface::updateShipData(long data)
// {
	
//}