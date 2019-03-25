#include "Sruba.h"
#include "NAVCON_SYMBOLS.h"
#include "common.h"

Sruba::Sruba(int shipModelMaxRevolution, char revRatting, int* currentPropelerRevolution)
{
	maxRevolution = shipModelMaxRevolution;
	currentRevolution = currentPropelerRevolution;
	rotationRating = revRatting;		//time from n-1 to n revlolution in seconds*100 
										//ex: 10 -> increase/reduction 1rpm takes 0,1s -> function SrubaInterruptFunction calls every 0,1 s
	requestedRevolution = *currentRevolution;
	hardwareInfo[NAVCON_PROPELLER_REFRESH_RATING] = revRatting; 
}

Sruba::~Sruba(){}
	
void Sruba::propelerChangeRevolution(int _requestedRevolution)
{
	this ->requestedRevolution = _requestedRevolution;	
}
	
void Sruba::SrubaInterruptFunction(void) // functions calls in common.h in time intervals equals (rotationRating/100)s
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