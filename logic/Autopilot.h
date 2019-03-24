

#ifndef AUTOPILOT_H
#define AUTOPILOT_H

#include "Ship_model.h"
#include "Ship_voyage_data.h"

//class Statek;
class Autopilot
{
	
	private:
	//PletwaSterowa steer;
	//Sruba propeller;
	char mode;
	char requestedSteerAngle;
	char requestedPropelerRotation;
	char status;
	
	public:

	Autopilot(void);
	Autopilot(int autopilotMode);

	~Autopilot();

	void calculateAndUpdate(Ship_model*model, Ship_voyage_data*voyage);
	void changeMode(char autopilotMode);
	int calculateNewSteerAngle(Ship_model**model, Ship_voyage_data**voyage);
	int calculateNewPropelerRotation(Ship_model**model, Ship_voyage_data**voyage);
};
#endif