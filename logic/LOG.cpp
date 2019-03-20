
#include "LOG.h"
#include "Navcon_avr_os.h"

extern Navcon_avr_os os;

// LOG::LOG() 
// {
// 	/*distanceMadeFrom1MinutePast = 0;*/
// }
// 
// 	
// LOG::~LOG(){}

//---------------------------------------------------------------------------------
/*
update one minute (speed in cables) --- function returns distance in ucables after each 1 minute of voyage, other returns 0 (ex in 24s of voyage)

*/
char LOG::update1minute(const int speed)														//speed in cables
{
	static char timeTo1Minute = 0;																//timer for time counting check
	static char distanceInMicroCables = 0;														//distance made after 1 minute

	unsigned int microDistance = speed * 2778 * os.hardwareInfo[NAVCON_MAIN_REFRESH_RATING];    //microdistance in uCable [ucables/s * s]
	distanceInMicroCables += microDistance;
	
	timeTo1Minute += os.hardwareInfo[NAVCON_MAIN_REFRESH_RATING];							    //add time of seconds which represents console update interval
	
	if(timeTo1Minute >= 60)																		//one minute reached
	{
		unsigned int result = distanceInMicroCables;		
		distanceInMicroCables = 0;
		timeTo1Minute = 0;
		return result;
	}
	
	return 0;
}