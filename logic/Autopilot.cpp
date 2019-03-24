
#include "Autopilot.h"
#include "common.h"


Autopilot::Autopilot(Ship_model* model, Ship_voyage_data* shipVoyageDat):mode(1)
{
	shipModel = model;
	shipVoyageData = shipVoyageDat;
	Pletwa_sterowa PL_STER(shipModel, shipVoyageDat);
	steer = &PL_STER;
}
	
Autopilot::Autopilot(int autopilotMode, Ship_model* model, Ship_voyage_data* shipVoyageDat)
{
	shipModel = model;
	shipVoyageData = shipVoyageDat;
	Pletwa_sterowa PL_STER(shipModel, shipVoyageDat);
	steer = &PL_STER;
	this ->mode = autopilotMode;
}
	
Autopilot::~Autopilot(){}
	
void Autopilot::calculateAndUpdate()
{
	if(this -> mode == 1)
	{
		status = 1;
		requestedSteerAngle = this -> calculateNewSteerAngle();
		requestedPropelerRotation = this -> calculateNewPropelerRotation();
		steer->moveSteer(requestedSteerAngle);
	
	}
	else
	{
		status = 0;
	}
}
 
void Autopilot::changeMode(char autopilotMode)
{
 	this -> mode = autopilotMode;
}

int Autopilot::calculateNewSteerAngle()
{
	return 0;
}

int Autopilot::calculateNewPropelerRotation()
{
	return 0;
}
