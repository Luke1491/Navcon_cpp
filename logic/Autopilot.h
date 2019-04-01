

#ifndef AUTOPILOT_H
#define AUTOPILOT_H

#include "Ship_model.h"
#include "Ship_voyage_data.h"
#include "Steer.h"
#include "Propeller.h"

//class Ship;
class Autopilot
{
	
	private:
	Ship_model *shipModel;
	Ship_voyage_data *shipVoyageData;
	Steer *steer;
	Propeller *propeller;
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
	void reset(void);
};
#endif