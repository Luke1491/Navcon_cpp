#include "Console.h"
#include "Ship.h"
#include "Interface.h"


Console::Console()
{

						
}

Console::~Console(){};
	
void Console::ShowDataFromShipToInterface(const void *shipVoyageData, void* interf)
{
	Ship* shipPtr = (Ship*)shipVoyageData;
	Interface* interfPtr = (Interface*) interf;
	
 	interfPtr->getDataToDisplay(   shipPtr->shipVoyageData->course, 
								shipPtr->shipVoyageData->speed, 
								shipPtr->shipVoyageData->rzadanyCourse, 
								shipPtr->shipVoyageData->rzadanaSpeed	);
}
