#ifndef PLETWA_STEROWA_H
#define PLETWA_STEROWA_H

#include "Ship_model.h"
#include "Ship_voyage_data.h"

class Pletwa_sterowa
{
	private:
	char currentAngle;
	char maxAngle;
	char moveRatting; //time from 0 to 1 degrees in (seconds * 100) -> 1s = 100
	char requestedSteerAngle;
	char* steerVoyageAngle;
	
	public:
	
	Pletwa_sterowa(const Ship_model* model, char* steerAngle);
	
	~Pletwa_sterowa();
	
	void moveSteer(char _requestedSteerAngle);	
	void pletwaSterowaInterruptFunction(void);
};
#endif