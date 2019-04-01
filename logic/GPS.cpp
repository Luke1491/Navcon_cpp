#include "GPS.h"
#include <math.h>
#include "LOG.h"
#include "Ship.h"
#include "NAVCON_SYMBOLS.h"
#include "common.h"



GPS::GPS()
{
	char nameText[] = "GPS ver 1.0.0";
	if(sizeof(nameText) < (14*(sizeof(char))))
	{
		strncpy(this -> name , nameText, sizeof(this -> name) - 1);
		status = 0;
		consoleMainArray[NAVCON_GPS_ID] = NAVCON_STATUS_ON;
	}
	else
	{
		status = 1; //name text too long
		consoleMainArray[NAVCON_GPS_ID] = NAVCON_STATUS_ERROR;
	}
}

GPS::~GPS() {}

void GPS::calculatePosition(unsigned int course, int speed, long* latitude, long* longitude, char durationTime)
{
	long microDistance=0; //distance made within last call of this function
	long deltaLat, deltaLong;
	long tempLat = *latitude;
	long tempLong = *longitude;
	
    microDistance = speed * 277 * durationTime;  //microdistance in microNauticalMiles
	
	double courseRadians = ((double)course/573);
	double latitudeRadians = ((double)tempLat/57295779);
	//compute latitude
	deltaLat = microDistance * cos(courseRadians); // delta wit accuracy to 0,000001
	*latitude = tempLat + deltaLat;//new latitude accuracy to 0,000001
	//compute longitude
	long zboczeniaNawig = microDistance * sin(courseRadians);
	deltaLong = zboczeniaNawig/cos(latitudeRadians);
	*longitude = tempLong + deltaLong;
}

char * GPS::WhatIsYourName(void)	{return this -> name;}
char GPS::showStatus(void)			{return this ->status;}
	
void GPS::reset(void)
{
	this->status = 0;
	this->distanceMadeFrom1MinutePast = 0;
	consoleMainArray[NAVCON_GPS_ID] = NAVCON_STATUS_ON;
}