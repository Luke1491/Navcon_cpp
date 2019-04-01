
#ifndef LOG_H
#define LOG_H

#include <string.h>

///////////////////////////////////////////////////////////////////
class LOG
{
	char name [14];
	int distanceMadeFrom1MinutePast;
	char status;
	

public:
	//constructor
	LOG();

	//destructor
	~LOG();
	
	//methods
	char update1minute(const int speed);
	char * WhatIsYourName(void);
	char showStatus(void);
	void reset(void);
};

#endif