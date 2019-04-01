/*
common.h

Created: 22-03-2018 by Luke1491
Modified: 22-03-2018 by Luke1491

*/

#include "common.h"
#include "Console.h"
#include "Ship.h"
#include "Interface.h"
#include <string.h>
#include <avr/pgmspace.h>
#include "Ship_model.h"
#include "Ship_data.h"
#include "Ship_voyage_data.h"

//###########MAIN CONSOLE ARRAY###################
//------------------------------------------------

const unsigned char hardwareArrayLen = 100;
volatile char consoleMainArray [hardwareArrayLen];

//################################################
//##############system timers#####################
//------------------------------------------------
volatile char mainRefreshTimer = 0;
volatile char steerTimer = 0;
volatile char propellerTimer = 0;
volatile char buzzerTimer = 0;
volatile char roseEngineTimer = 0;
volatile char changeSpeedInManualTimer = 0;
volatile char touchTimer = 0;

//################################################

//---------data in flash memory-------------
const Ship_model defaultShipModel PROGMEM = {
	35,		//maxSteerAngle
	29,  	//steerOneDegreeMoveRatting - 0,29 s to move steer by 1 degree
	160,	//propelerMaxRevolution - max propeller revolution is 160 rpm
	10,		//propelerChangeRevolutionRatting - 0,1s to change propeller rotation by +/- one revolution
	10		//propellerRevolutionToSpeedRating - 10 means 10 propeller revolution for one knot of speed
};
	
const Ship_data defaultShipData PROGMEM = {
	"123456789",			//mmsi [9 digits + null (end of string)]
	1,						//navstatus
	0,						//pas
	1,						//type of communicate
	1234567,				//IMO number
	"BWX12SD",				//call sign
	"JAN KUSOCINSKI@@@@@@",//ship name (21 digits)
	5,						//type of ship
	130,					//dimension A - length OA
	18,						//dimension B - width
	27						//dimension C - height
};	

const Ship_voyage_data defaultShipVoyageData PROGMEM = {
	0,						//current course
	100,					//current speed
	54000000L,				//posLat - latitude
	15000000L,				//posLong - longitude
	"SZCZECIN@@@@@@@@@@@@",	//destination (21 digits; @ to the end if name is shorter than 20 letters + end of string sign)
	72,						//draught in dm (meters/10)
	1,						//ETA_month - represents day part of ETA
	4,						//ETA_day - represents month part of ETA
	10,						//ETA_hour
	40,						//ETA_minute
	0,						//distance1Minute - distance made in 1 minute (changed by LOG object)
	0,						//distance1H - distance made in 1 hour (changed by LOG object)
	0,						//distance24H - distance made in 24 hours changed by LOG object)
	0,						//totalVoyageDistance - changed by LOG object
	0,						//currentROT - used by Ship object and autopilot object, changed by Ship object (ship)
	0,						//computedROT - used and changed by Ship object (ship)
	0,						//currentSteerWheelPos - used by autopilot object, changed by steerWeel object
	0,						//currentSteerPos - used by Ship object, changed by Steer object
	120,					//currentPropellerRevolution = 120 rpm, changed by propeller object used by Ship object
	10,						//rzadanaSpeed - required speed - used by autopilot object, changed by autopilot object and przyciski_poj object
	10,						//nastawaSpeed - set speed - changed by przyciski_poj object used by autopilot object
	0,						//rzadanyCourse - set course - changed by Galka_cog used by autopilot object
	0,						//rzadaneUstawienieSteru - set steer - changed by steerwheel object and autopilot object used by autopilot object
	0,						//totalTimeofVoyage - used by Ship object (ship)
	0						//computed max speed (is computed in Ship constructor)

};
	


//------------------------------------------
//-----------CREATE MAIN MODULES------------
//------------------------------------------
Ship ship;
Console console;
Interface interface(ship.shipVoyageData->course, ship.shipVoyageData->speed, ship.shipVoyageData->rzadanyCourse, ship.shipVoyageData->rzadanaSpeed );
//Ethernet ethernet;

//------------------------------------------



void init(void)
{
	//configure ports which are used with many components
	//otherwise configuration is provided by actual component
	
}

void createModules(void)
{
}