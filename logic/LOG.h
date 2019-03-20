
#ifndef LOG_H
#define LOG_H



///////////////////////////////////////////////////////////////////
class LOG
{
	int distanceMadeFrom1MinutePast;

public:
	//constructor
	LOG(){}

	//destructor
	~LOG(){}
	
	//methods
	char update1minute(const int speed);
};

#endif