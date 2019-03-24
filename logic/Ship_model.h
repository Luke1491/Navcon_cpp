#ifndef SHIP_MODEL_H
#define SHIP_MODEL_H

	struct Ship_model
	{
		char maxSteerAngle;				//maximum steer angle on each side (used by steerwheel and steer)
		char SteerOneDegreeMoveRatting; ////time from 0 to 1 degrees in (seconds / 100) -> one second is 100 (max 2,55 seconds)
		
	};

#endif