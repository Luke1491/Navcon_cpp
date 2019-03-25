#include "Pletwa_sterowa.h"
#include "NAVCON_SYMBOLS.h"
#include "common.h"

Pletwa_sterowa::Pletwa_sterowa(const Ship_model* model, char* steerAngle)
{
	steerVoyageAngle = steerAngle;
	currentAngle = 0;
	maxAngle = model->maxSteerAngle;
	moveRatting = model->steerOneDegreeMoveRatting;
	hardwareInfo[NAVCON_STEER_REFRESH_RATING] = moveRatting; //time in seconds/100 to move steer by 1 degree (set timer to call move steer function)
	
}


Pletwa_sterowa::~Pletwa_sterowa(){}

//this function is call in common.h timer interrupt
void Pletwa_sterowa::moveSteer(char _requestedSteerAngle)
{
	requestedSteerAngle = _requestedSteerAngle;
}

void Pletwa_sterowa::pletwaSterowaInterruptFunction(void)
{
	if(this->requestedSteerAngle > maxAngle){this->requestedSteerAngle = maxAngle;}
	if((-this->requestedSteerAngle) < (-maxAngle)){this->requestedSteerAngle = (-maxAngle);} 
		
		
	char diff = this->requestedSteerAngle - currentAngle;
	if(diff != 0)
	{
		if(diff > 0){currentAngle += 1;}
		if(diff < 0){currentAngle -= 1;}
	}
	*steerVoyageAngle = currentAngle;
}