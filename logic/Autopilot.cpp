
#include "Autopilot.h"


Autopilot::Autopilot(void):mode(1){}
	
Autopilot::Autopilot(int autopilotMode){this ->mode = autopilotMode;}
	
Autopilot::~Autopilot(){}
	
void Autopilot::calculateAndUpdate(Ship_model*model, Ship_voyage_data*voyage)
{
	if(this -> mode == 1)
	{
		status = 1;
		requestedSteerAngle = this -> calculateNewSteerAngle(&model, &voyage);
		requestedPropelerRotation = this -> calculateNewPropelerRotation(&model, &voyage);
	
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

int Autopilot::calculateNewSteerAngle(Ship_model**model, Ship_voyage_data**voyage)
{
	return 0;
}

int Autopilot::calculateNewPropelerRotation(Ship_model**model, Ship_voyage_data**voyage)
{
	return 0;
}
