#ifndef GPS_H
#define GPS_H
/*
GPS - class used to compute voyage distance

*/


///////////////////////////////////////////////////////////////////
class GPS
{
	int distanceMadeFrom1MinutePast;
	char status;
	char name [14];

	public:
	//constructor
	GPS();

	//destructor
	~GPS();
	
	//methods
	void calculatePosition(unsigned int course, int speed, long* latitude, long* longitude, char durationTime);
	char * WhatIsYourName(void);
	char showStatus(void);
	void reset(void);
};

#endif
