/*
Statek

Created: 15-03-2018 by Luke1491
Modified: 23-03-2018 by Luke1491

*/
#include "Statek.h"
#include "common.h"
#include <string.h>
//#include <cstdlib>

Statek::Statek()
{
	shipModel->maxSteerAngle = 35;
	shipModel->steerOneDegreeMoveRatting = 29;			//0,29 s to move steer by 1 degree
	shipModel->propelerMaxRevolution = 160;				//max propeller revolution is 160 rpm
	shipModel->propelerChangeRevolutionRatting = 10;	//0,1s to change propeller rotation by +/- one revolution
	
	strncpy(shipData->mmsi, "123456789", sizeof(shipData->mmsi) - 1);
	shipData->navStatus = 1;
	shipData->pas = 0; 
	shipData->typKomunikatu = 1;
	shipData->imoNumber = 1234567;
	strncpy(shipData->callSign, "BWX12SD", sizeof(shipData->callSign) - 1);
	strncpy(shipData->shipName, "JAN KUSOCINSKI", sizeof(shipData->shipName) - 1);
	shipData->typeOfShip = 5;
	shipData->dimA = 130;
	shipData->dimB = 18;
	shipData->dimC = 27;
	
	shipVoyageData->course = 0;
	shipVoyageData->speed = 100;
	shipVoyageData->posLat = 54000000L;
	shipVoyageData->posLong = 15000000L;
	strncpy(shipVoyageData->destination, "SZCZECIN@@@@@@@@@@@@", sizeof(shipVoyageData->destination) - 1);
	shipVoyageData->draught = 72;
	shipVoyageData->ETA_day = 1;
	shipVoyageData->ETA_month = 4;
	shipVoyageData->ETA_hour = 10;
	shipVoyageData->ETA_minute = 40;
	shipVoyageData->distance1Minute = 0;
	shipVoyageData->distance1H = 0;
	shipVoyageData->distance24H = 0;
	shipVoyageData->totalVoyageDistance = 0;
	shipVoyageData->currentROT = 0;
	shipVoyageData->computedROT = 0;
	shipVoyageData->currentSteerWheelPos = 0;
	shipVoyageData->currentSteerPos = 0;
	shipVoyageData->currentPropellerRevolution = 120; //120 rpm
	shipVoyageData->rzadanaSpeed = 10;
	shipVoyageData->nastawaSpeed = 10;
	shipVoyageData->rzadanyCourse = 0;
	shipVoyageData->rzadaneUstawienieSteru = 0;
	shipVoyageData->totalTimeofVoyage = 0;
	
	Ship_model shipM;
	shipModel = &shipM;
	
	Ship_data shipD;
	shipData = &shipD;
	
	Ship_voyage_data shipVD;
	shipVoyageData = &shipVD;
	
	GPS GP;
	gps = &GP;
	
	LOG LG;
	log = &LG;
	
	Autopilot autoP(NAVCON_AUTOPILOT_ON, shipModel, shipVoyageData);
	autopilot = &autoP;
	
	
}
//destructor
Statek::~Statek(){}
//methods
//**********************************************************
void Statek::updateAll(void)
{
	static char countOfCalls = 0;												//call counter which represents seconds
	countOfCalls += hardwareInfo[NAVCON_MAIN_REFRESH_RATING];			//add seconds depend of NAVCON_MAIN_REF...  to voyage time
	
	//------------------LOG----------------------------
	if(countOfCalls >=60)
	{
		countOfCalls = 0;													//reset timer
		shipVoyageData->distance1Minute = log->update1minute(					//compute distance after minute												
											shipVoyageData->speed);	
	}												
	shipVoyageData->totalTimeofVoyage += 
	hardwareInfo[NAVCON_MAIN_REFRESH_RATING];				//add seconds depend of NAVCON_MAIN_REF...  to voyage time
	
	//-------------------GPS---------------------------
	gps->calculatePosition(									//function update lat and long in ship::shipVoyageData->lat and long
					shipVoyageData->course, 
					shipVoyageData->speed, 
					&shipVoyageData->posLat, 
					&shipVoyageData->posLong, 
					hardwareInfo[NAVCON_MAIN_REFRESH_RATING]);	//last parameter is required to calculate distance needed to claculate position
	
	//-------------------AUTOPILOT---------------------
	autopilot->calculateAndUpdate();				//update autopilot settings
	
	//------------------OWN SHIP-----------------------
	this -> calculateMovement();											//calculate ship movement
}

//*********************************************************
void Statek::calculateMovement()
{
	//calculating ship movement
}

Ship_voyage_data* Statek::showVoyageData()
{
	return shipVoyageData;
}


