/*
LOG - class used to compute voyage distance

*/

#include "NAVCON_SYMBOLS.h"


#ifndef LOG_H
#define LOG_H

///////////////////////////////////////////////////////////////////
class LOG
{
	int distanceMadeFrom1MinutePast;

	public:
	//constructor
	LOG();

	//destructor
	~LOG();
	
	//methods
	char update1minute(const int speed);							//return distance after made 1 minute update work distance
};

#endif