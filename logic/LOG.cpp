

#include "LOG.h"

LOG::LOG():LOG::distanceMadeFrom1MinutePast = 0 {}
	
LOG::~LOG(){}

char LOG::update1minute(const int speed)					//speed in cables
{
	static char timeTo1Minute = 0;
	static char distanceInCables = 0;
	long 
	
	timeTo1Minute += Navcon_avr_os::hardwareInfo[NAVCON_MAIN_REFRESH_RATING];
	
	if(timeTo1Minute >= 60)
	{
		this ->distanceMadeFrom1MinutePast = distanceInCables;		
		distanceInCables = 0;
		timeTo1Minute = 0;
		return distanceInCables;
	}
	
	unsigned int partlyDistance = speed * 2778 * Navcon_avr_os::hardwareInfo[NAVCON_MAIN_REFRESH_RATING]; //partly distance in uCable [ucables/s * s]
	
	
	
}