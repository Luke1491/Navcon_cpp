/*
Statek - class used to compute ship param and stored it in class array


*/
#ifndef STATEK_H
#define STATEK_H


#include "NAVCON_SYMBOLS.h"
#include "GPS.h"
#include "LOG.h"

#include <string.h>



///////////////////////////////////////////////////////////////////
class Statek
{
private:
	struct Ship_data				    //ship constants data
	{
		char mmsi[10];					//9 digits in ""
		char navStatus;					//0d 0 do 15
		char pas;
		char typKomunikatu;
		long imoNumber;					//7 digits 
		char callSign[8];
		char shipName[21];
		char typeOfShip;				// 1 do 99
		int dimA;						//length overall
		int dimB;						//width overall
		int dimC;						//height overall
	};
	
	struct Ship_voyage_data
	{
		unsigned int course;            //current course (times 10, ex: course = 45,0 -> course = 450)
		int speed;						//current speed (accuracy = 0,1 kt (speed times 10))
		long posLong;					//longitude with no comma (times 6, ex: 045,345123 -> posLong = 45345123)
		long posLat;					//latitude with no comma (times 6, ex: 45,123456 -> posLong = 45123456)
		char destination[21];			//voyage destination(all 21 char must be filled, not used chars fill with @ ex: SZCZECIN@@@@@@@@@@@@@)
		unsigned char draught;			//current draught precission to 0,1m, ex: 6,6m -> draught = 66;
		unsigned char ETA_month;        //1 d0 12
		unsigned char ETA_day;          //1 do 31
		unsigned char ETA_hour;         //0 do 24
		unsigned char ETA_minute ;      //0 do 59
		unsigned char distance1Minute;	//distance made in 1 minute
		unsigned int distance1H;		//distance made in 1 hour
		unsigned int distance24H;		//distance made in 24 hours
		unsigned int totalVoyageDistance;//total yourney distance
		long currentROT;				//precission 0,01degree/minute ex: ROT = 10degrees/minute -> currentRoot = 1000
		int computedROT;                // kierunek ROT aktualny inicjowany przez -5 tylko do pierwszego rozruchu funkcji
		char currentSteerWheelPos;		//current steerwheel position
		int rzadanaSpeed;               //rzadana predkosc w oparciu o nastawe pr?dko?ci nastawaSpeed
		char nastawaSpeed;              //0d -8 do +8 nastawa pr?dko?ci zmieniana dotykowymi przyciskami
		int rzadanyCourse;
		char rzadaneUstawienieSteru;    // od -35 do +35
		long totalTimeofVoyage;			//total time of voyage in seconds
	};
	
	struct Ship_model
	{
		char maxSteerAngle;				//maximum steer angle on each side (used by steerwheel and steer)
		
	};

	Ship_model shipmodel;
	Ship_data shipData;
	Ship_voyage_data shipVoyageData;
		
	
	//members
	//Autopilot autopliot(NAVCON_AUTOPILOT_ON , const Ship_model &shipmodel, const Ship_voyage_data &voyageData);			//initialize autopilot with mode and 
																				//initialize ship's log with current position (or default position)
	GPS gps;
	LOG log;
public:	
	
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
};

#endif