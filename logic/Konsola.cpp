#include "Konsola.h"
#include "Statek.h"
#include "Interface.h"


Konsola::Konsola()
{

						
}

Konsola::~Konsola(){};
	
void Konsola::ShowDataFromShipToInterface(const Statek *shipVoyageData, Interface* interf)
{
	
 	interf->getDataToDisplay(   shipVoyageData->shipVoyageData->course, 
								shipVoyageData->shipVoyageData->speed, 
								shipVoyageData->shipVoyageData->rzadanyCourse, 
								shipVoyageData->shipVoyageData->rzadanaSpeed	);
}
