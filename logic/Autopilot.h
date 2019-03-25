

#ifndef AUTOPILOT_H
#define AUTOPILOT_H

#include "Ship_model.h"
#include "Ship_voyage_data.h"
#include "Pletwa_sterowa.h"
#include "Sruba.h"

//class Statek;
class Autopilot
{
	
	private:
	Ship_model *shipModel;
	Ship_voyage_data *shipVoyageData;
	Pletwa_sterowa *steer;
	Sruba *propeller;
	char mode;
	char requestedSteerAngle;
	char requestedPropelerRotation;
	char status;
	
	public:

	Autopilot(Ship_model* model, Ship_voyage_data* shipVoyageDat);
	Autopilot(int autopilotMode, Ship_model* model, Ship_voyage_data* shipVoyageDat);

	~Autopilot();

	void calculateAndUpdate();
	void changeMode(char autopilotMode);
	int calculateNewSteerAngle();
	int calculateNewPropelerRotation();
};
#endif