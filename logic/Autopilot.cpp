
#include "Autopilot.h"
#include "common.h"
#include "NAVCON_SYMBOLS.h"

Autopilot::Autopilot(Ship_model* model, Ship_voyage_data* shipVoyageDat):mode(1)
{
	shipModel = model;
	shipVoyageData = shipVoyageDat;
	Steer PL_STER(shipModel, &shipVoyageDat->currentSteerPos);
	steer = &PL_STER;
	
	Propeller PROP(model->propelerMaxRevolution, model->propelerChangeRevolutionRatting, &shipVoyageDat->currentPropellerRevolution);
	propeller = &PROP;
	
	requestedSteerAngle = 0;
	requestedPropelerRotation = shipVoyageData->currentPropellerRevolution;
}
	
Autopilot::Autopilot(int autopilotMode, Ship_model* model, Ship_voyage_data* shipVoyageDat)
{
	shipModel = model;
	shipVoyageData = shipVoyageDat;
	
	Steer PL_STER(shipModel, &shipVoyageDat->currentSteerPos);
	steer = &PL_STER;
	
	Propeller PROP(model->propelerMaxRevolution, model->propelerChangeRevolutionRatting, &shipVoyageDat->currentPropellerRevolution);
	propeller = &PROP;
	
	this ->mode = autopilotMode;
	requestedSteerAngle = 0;
	requestedPropelerRotation = shipVoyageDat->currentPropellerRevolution;
	
	consoleMainArray[NAVCON_AUTOPILOT_ID] = NAVCON_STATUS_ON;
	consoleMainArray[NAVCON_AUTOPILOT_MODE] = NAVCON_AUTOPILOT_MODE_ON;
}
	
Autopilot::~Autopilot(){}
	
void Autopilot::calculateAndUpdate()
{
	if(this -> mode == 1) //autopilot in auto mode
	{
		status = 1;
		requestedSteerAngle = this -> calculateNewSteerAngle();
		requestedPropelerRotation = this -> calculateNewPropelerRotation();
		steer->moveSteer(requestedSteerAngle);
		propeller->propelerChangeRevolution(requestedPropelerRotation);
	
	}
	else //autopilot in manual mode
	{
		status = 0;
		requestedSteerAngle = shipVoyageData->rzadaneUstawienieSteru;
		requestedPropelerRotation = shipVoyageData->rzadanaSpeed * shipModel->propellerRevolutionToSpeedRating;
		steer->moveSteer(requestedSteerAngle);
		propeller->propelerChangeRevolution(requestedPropelerRotation);
	}
}
 
void Autopilot::changeMode(char autopilotMode)
{
	if(autopilotMode != 0 || autopilotMode != 1){consoleMainArray[NAVCON_AUTOPILOT_ID] = NAVCON_STATUS_ERROR; return;} //error if mode is not 0 or 1
 	this -> mode = autopilotMode;
	consoleMainArray[NAVCON_AUTOPILOT_MODE] = autopilotMode; 
}

int Autopilot::calculateNewSteerAngle()
{
	return 0;
	//TO DO claculate steer angle
}

int Autopilot::calculateNewPropelerRotation()
{
	return 0;
	//TO DO claculate propeller rotation
}

void Autopilot::reset(void)
{
	requestedSteerAngle = 0;
	requestedPropelerRotation = shipVoyageData->currentPropellerRevolution;
	consoleMainArray[NAVCON_AUTOPILOT_ID] = NAVCON_STATUS_ON;
}
