#include "GPS.h"
#include <math.h>
#include "LOG.h"
#include "Statek.h"



GPS::GPS()
{
	char nameText[] = "GPS ver 1.0.0";
	if(sizeof(nameText) < (14*(sizeof(char))))
	{
		strncpy(this -> name , nameText, sizeof(this -> name) - 1);
		status = 0;
	}
	else
	{
		status = 1; //name text too long
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
	deltaLat = microDistance * cos(courseRadians); // delta z precyzj? do 0,000001
	*latitude = tempLat + deltaLat;//nowa pozycja z dok?adno?ci? do 0,000001
	//compute longitude
	long zboczeniaNawig = microDistance * sin(courseRadians);
	deltaLong = zboczeniaNawig/cos(latitudeRadians);
	*longitude = tempLong + deltaLong;
}

char * GPS::WhatIsYourName(void)	{return this -> name;}
char GPS::showStatus(void)			{return this ->status;}