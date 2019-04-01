/*
Ship

Created: 15-03-2018 by Luke1491
Modified: 01-04-2018 by Luke1491

*/
#include "Ship.h"
#include "common.h"
#include <string.h>
#include <avr/pgmspace.h>
#include "NAVCON_SYMBOLS.h"

Ship::Ship()
{
	
	Ship_model shipM;									//create new Ship_model object instance
	memcpy_P(&shipM, &defaultShipModel, sizeof(shipM)); //load data from flash (defaulatShipModel) to shipM object
	shipModel = &shipM;									//assign pointer to object
	
	Ship_data shipD;
	memcpy_P(&shipD, &defaultShipData, sizeof(shipD));
	shipData = &shipD;
	
	Ship_voyage_data shipVD;
	memcpy_P(&shipVD, &defaultShipVoyageData, sizeof(shipVD));
	shipVoyageData = &shipVD;
	
	GPS GP;
	gps = &GP;
	
	LOG LG;
	log = &LG;
	
	Autopilot autoP(NAVCON_AUTOPILOT_MODE_ON, shipModel, shipVoyageData); //mode auto
	autopilot = &autoP;
	
	consoleMainArray[NAVCON_SHIP_ID] = NAVCON_STATUS_ON; //change status to ON
	
	//----URGENT----computing max speed
	shipVoyageData->computedMaxSpeed = shipModel->propelerMaxRevolution / shipModel->propellerRevolutionToSpeedRating;
	
	
}
//destructor
Ship::~Ship(){}
//methods
//**********************************************************
void Ship::updateAll(void)
{
	if(consoleMainArray[NAVCON_SHIP_ID] != NAVCON_STATUS_ON){return;}	//check if something is wrong with ship module (OFF, PAUSED or have some ERRORS)
	else
	{ //ship is active (is in "ON" mode)
		static char countOfCalls = 0;												//call counter which represents seconds
		countOfCalls += consoleMainArray[NAVCON_MAIN_REFRESH_RATING];			//add seconds depend of NAVCON_MAIN_REF...  to voyage time
		
		//------------------LOG----------------------------
		if(countOfCalls >=60)
		{
			countOfCalls = 0;													//reset timer
			shipVoyageData->distance1Minute = log->update1minute(					//compute distance after minute
			shipVoyageData->speed);
		}
		shipVoyageData->totalTimeofVoyage +=
		consoleMainArray[NAVCON_MAIN_REFRESH_RATING];				//add seconds depend of NAVCON_MAIN_REF...  to voyage time
		
		//-------------------GPS---------------------------
		gps->calculatePosition(									//function update lat and long in ship::shipVoyageData->lat and long
		shipVoyageData->course,
		shipVoyageData->speed,
		&shipVoyageData->posLat,
		&shipVoyageData->posLong,
		consoleMainArray[NAVCON_MAIN_REFRESH_RATING]);	//last parameter is required to calculate distance needed to calculate position
		
		//-------------------AUTOPILOT---------------------
		autopilot->calculateAndUpdate();				//update autopilot settings
		
		//------------------OWN SHIP-----------------------
		this -> calculateMovement();											//calculate ship movement
	}
	
}

//*********************************************************
void Ship::calculateMovement()
{
	//calculating ship movement
}
//----------------------------------------------------------
void Ship::reset(void)
{
	Ship_model shipM;									//create new Ship_model object instance
	memcpy_P(&shipM, &defaultShipModel, sizeof(shipM)); //load data from flash (defaulatShipModel) to shipM object
	shipModel = &shipM;									//assign pointer to object
	
	Ship_data shipD;
	memcpy_P(&shipD, &defaultShipData, sizeof(shipD));
	shipData = &shipD;
	
	Ship_voyage_data shipVD;
	memcpy_P(&shipVD, &defaultShipVoyageData, sizeof(shipVD));
	shipVoyageData = &shipVD;
	
	gps->reset();
	log->reset();
	autopilot->reset();
	consoleMainArray[NAVCON_SHIP_ID] = NAVCON_STATUS_ON;
}
//-------------------------------------------------------------
void Ship::changeModel(Ship_model * newModel)
{
	this->shipModel = newModel;
}
//--------------------------------------------------------------
void Ship::changeAutopilotMode(char autopilotMode)
{
	consoleMainArray[NAVCON_AUTOPILOT_MODE] = autopilotMode;	//change autopilot mode in global main array
	autopilot->changeMode(autopilotMode);						//change autopilot mode
}




