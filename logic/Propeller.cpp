#include "Propeller.h"
#include "NAVCON_SYMBOLS.h"
#include "common.h"

Propeller::Propeller(int shipModelMaxRevolution, char revRatting, int* currentPropelerRevolution)
{
	maxRevolution = shipModelMaxRevolution;
	currentRevolution = currentPropelerRevolution;
	rotationRating = revRatting;		//time from n-1 to n revlolution in seconds*100 
										//ex: 10 -> increase/reduction 1rpm takes 0,1s -> function PropellerInterruptFunction calls every 0,1 s
	requestedRevolution = *currentRevolution;
	consoleMainArray[NAVCON_PROPELLER_REFRESH_RATING] = revRatting; 
	consoleMainArray[NAVCON_PROPELLER_ID] = NAVCON_STATUS_ON; //propeller status to "on"
}

Propeller::~Propeller(){}
	
//function call by autopilot
void Propeller::propelerChangeRevolution(int _requestedRevolution)
{
	this ->requestedRevolution = _requestedRevolution;	
}

// functions calls in common.h in time intervals equals (rotationRating/100)s	
void Propeller::PropellerInterruptFunction(void) 
{
	//max revolution guards
	if(this ->requestedRevolution > this -> maxRevolution){this ->requestedRevolution = this -> maxRevolution;}
	if(this ->requestedRevolution < -(this -> maxRevolution)){this ->requestedRevolution = -(this -> maxRevolution);}
	
	//change revolution
	int diff = 0;
	diff = this ->requestedRevolution - *this -> currentRevolution;
	if(diff > 0)
	{
		*currentRevolution += 1;
	}
	if(diff < 0)
	{
		*currentRevolution -= 1;
	}
}