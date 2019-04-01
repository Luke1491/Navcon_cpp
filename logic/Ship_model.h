#ifndef SHIP_MODEL_H
#define SHIP_MODEL_H

	struct Ship_model
	{
		char maxSteerAngle;				//maximum steer angle on each side (used by steerwheel and steer)
		char steerOneDegreeMoveRatting; //time from 0 to 1 degrees in (seconds / 100) -> one second is 100 (max 2,55 seconds)
		int propelerMaxRevolution;		//max revolution in rpm
		char propelerChangeRevolutionRatting;//time from n-1 to n revlolution in seconds*100 ex: 10 -> increase/reduction 1rpm takes 0,1s
		char propellerRevolutionToSpeedRating; //what revolution is equal to requested speed
		//for ex: 10 means 1 knot is 10 propeller revolution
		
	};

#endif