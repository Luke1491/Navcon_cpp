/*
Ship - class used to compute ship param and stored it in class array


*/
#ifndef SHIP_H
#define SHIP_H


#include "GPS.h"
#include "LOG.h"
#include "Ship_data.h"
#include "Ship_model.h"
#include "Ship_voyage_data.h"
#include "Autopilot.h"


///////////////////////////////////////////////////////////////////
class Ship
{
public:
	
	Ship_model* shipModel;
	Ship_data* shipData;
	Ship_voyage_data* shipVoyageData;
	GPS* gps;
	LOG* log;
	
	Autopilot* autopilot;
	
	//constructor
	Ship();

	//destructor
	~Ship();
	
	//methods
	void updateAll(void);	//run all object in ship - it calls every time interval specify in consoleMainArray array 																						
	void changeModel(Ship_model * newModel); 
	void reset(void);			//reset all voyage data and starts from starting point (written in defaultShipVoyageData in flash)															
	void calculateMovement();	//calculate ship manuvering
	void changeAutopilotMode(char autopilotMode); //change autopilot mode pass only 0-off or 1-on
	
	
};

#endif