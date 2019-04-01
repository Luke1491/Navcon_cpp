#ifndef STEER_H
#define STEER_H

#include "Ship_model.h"
#include "Ship_voyage_data.h"

class Steer
{
	private:
	char currentAngle;
	char maxAngle;
	char moveRatting; //time from 0 to 1 degrees in (seconds * 100) -> 1s = 100
	char requestedSteerAngle;
	char* steerVoyageAngle; //pointer to ships voyage data -> current steer angle
	
	public:
	
	Steer(const Ship_model* model, char* steerAngle);
	
	~Steer();
	
	void moveSteer(char _requestedSteerAngle);	
	void pletwaSterowaInterruptFunction(void);
};
#endif