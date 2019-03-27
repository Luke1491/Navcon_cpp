/*
Statek - class used to compute ship param and stored it in class array


*/
#ifndef STATEK_H
#define STATEK_H

#include "NAVCON_SYMBOLS.h"
#include "GPS.h"
#include "LOG.h"
#include "Ship_data.h"
#include "Ship_model.h"
#include "Ship_voyage_data.h"
#include "Autopilot.h"


///////////////////////////////////////////////////////////////////
class Statek
{
public:
	
	Ship_model* shipModel;
	Ship_data* shipData;
	Ship_voyage_data* shipVoyageData;
	GPS* gps;
	LOG* log;
	
	Autopilot* autopilot;
	
	//constructor
	Statek();

	//destructor
	~Statek();
	
	//methods
	void updateAll(void);																								//update all components
	//void updateAutopilot(Ship_model * model, Ship_voyage_data * shipVoyageData);										//update autopilot (call this function after each update)
	//void updateLOG(const long &latitude, const long &longitude, char &PassedDistanceInOneMinute);						//update log give reference to position and variable to update
	//void updateGPS(long &latitude, long &longitude);																	//update gps - give variables to change
	void calculateMovement();																							//calculate ship maneuvring
	//friend void GPS::calculatePosition(unsigned int course, int speed, long latitude, long longitude, char durationTime);
	Ship_voyage_data* showVoyageData();
	
};

#endif