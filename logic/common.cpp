/*
common.h

Created: 22-03-2018 by Luke1491
Modified: 22-03-2018 by Luke1491

*/

#include "common.h"
#include "Konsola.h"
#include "Statek.h"
#include "Interface.h"


const unsigned char hardwareArrayLen = 100;
char hardwareInfo [hardwareArrayLen];

Statek ship;
Konsola console;
Interface interface(ship.shipVoyageData->course, ship.shipVoyageData->speed, ship.shipVoyageData->rzadanyCourse, ship.shipVoyageData->rzadanaSpeed );


void init(void)
{
	//configure ports which are used with many components
	//otherwise configuration is provided by actual component
	
}

void createModules(void)
{
}