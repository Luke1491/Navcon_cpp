/*
common.h

Created: 22-03-2018 by Luke1491
Modified: 22-03-2018 by Luke1491

*/

#include "common.h"
#include "Statek.h"

const unsigned char hardwareArrayLen = 100;
char hardwareInfo [hardwareArrayLen];

void init(void)
{
	//configure ports which are used with many components
	//otherwise configuration is provided by actual component
	
}

void createModules(void)
{
	Statek ship;
}