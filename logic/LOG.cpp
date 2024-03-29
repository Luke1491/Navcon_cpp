
#include "LOG.h"
#include "common.h"
#include "NAVCON_SYMBOLS.h"


LOG::LOG() 
{
	distanceMadeFrom1MinutePast = 0;
	char nameText[] = "LOG ver 1.0.0";
	if(sizeof(nameText) < (14*(sizeof(char)))) 
	{
		strncpy(this -> name , nameText, sizeof(this -> name) - 1);
		status = 0;
		consoleMainArray[NAVCON_LOG_ID] = NAVCON_STATUS_ON;
	}
	else
	{
		status = 1; //name text too long
		consoleMainArray[NAVCON_LOG_ID] = NAVCON_STATUS_ERROR;
	}
	
}

	
LOG::~LOG(){}

//---------------------------------------------------------------------------------
/*
update one minute (speed in cables) --- function returns distance in ucables after each 1 minute of voyage, other returns 0 (ex in 24s of voyage)

*/
char LOG::update1minute(const int speed)														//speed in cables
{
	static char timeTo1Minute = 0;																//timer for time counting check
	static char distanceInMicroCables = 0;														//distance made after 1 minute

	unsigned int microDistance = speed * 2778 * consoleMainArray[NAVCON_MAIN_REFRESH_RATING];    //microdistance in uCable [ucables/s * s]
	distanceInMicroCables += microDistance;
	
	timeTo1Minute += consoleMainArray[NAVCON_MAIN_REFRESH_RATING];							    //add time of seconds which represents console update interval
	
	if(timeTo1Minute >= 60)																		//one minute reached
	{
		unsigned int result = distanceInMicroCables;		
		distanceInMicroCables = 0;
		timeTo1Minute = 0;
		return result;
	}
	
	return 0;
}

char * LOG::WhatIsYourName(void)	{return this -> name;}
char LOG::showStatus(void)			{return this ->status;}
	
void LOG::reset(void)
{
	this->status = 0;
	this->distanceMadeFrom1MinutePast = 0;
	consoleMainArray[NAVCON_LOG_ID] = NAVCON_STATUS_ON;
}