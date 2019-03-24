#ifndef PLETWA_STEROWA_H
#define PLETWA_STEROWA_H

#include "Ship_model.h"
#include "Ship_voyage_data.h"

class Pletwa_sterowa
{
	private:
	char currentAngle;
	char maxAngle;
	char moveRatting; //time from 0 to 1 degrees in (seconds / 100)
	char requestedSteerAngle;
	Ship_voyage_data* steerShipVoyageData;
	
	public:
	
	Pletwa_sterowa(const Ship_model* model, Ship_voyage_data* steerVoyageData);
	
	~Pletwa_sterowa();
	
	void moveSteer(char _requestedSteerAngle);	
	void pletwaSterowaInterruptFunction(void);
};
#endif