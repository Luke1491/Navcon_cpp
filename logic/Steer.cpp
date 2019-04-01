#include "Steer.h"
#include "NAVCON_SYMBOLS.h"
#include "common.h"

Steer::Steer(const Ship_model* model, char* steerAngle)
{
	steerVoyageAngle = steerAngle;
	currentAngle = 0;
	maxAngle = model->maxSteerAngle;
	moveRatting = model->steerOneDegreeMoveRatting;
	consoleMainArray[NAVCON_STEER_REFRESH_RATING] = moveRatting; //time in seconds/100 to move steer by 1 degree (set timer to call move steer function)
	consoleMainArray[NAVCON_STEER_ID] = NAVCON_STATUS_ON; //change status steer to "on"
}


Steer::~Steer(){}

//this function is used by autopilot for write new required angle
void Steer::moveSteer(char _requestedSteerAngle)
{
	requestedSteerAngle = _requestedSteerAngle;
}

//this function is call in common.h timer interrupt
void Steer::pletwaSterowaInterruptFunction(void)
{
	if(this->requestedSteerAngle > maxAngle){this->requestedSteerAngle = maxAngle;}
	if((-(this->requestedSteerAngle)) < (-maxAngle)){this->requestedSteerAngle = (-maxAngle);} 
		
		
	char diff = this->requestedSteerAngle - currentAngle;
	if(diff != 0)
	{
		if(diff > 0){currentAngle += 1;}
		if(diff < 0){currentAngle -= 1;}
	}
	*steerVoyageAngle = currentAngle;
}