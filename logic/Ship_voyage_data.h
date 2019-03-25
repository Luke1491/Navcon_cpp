#ifndef SHIP_VOYAGE_DATA_H
#define SHIP_VOYAGE_DATA_H

struct Ship_voyage_data
{
	unsigned int course;            //current course (times 10, ex: course = 45,0 -> course = 450)
	int speed;						//current speed (accuracy = 0,1 kt (speed times 10))
	long posLong;					//longitude with no comma (times 6, ex: 045,345123 -> posLong = 45345123)
	long posLat;					//latitude with no comma (times 6, ex: 45,123456 -> posLong = 45123456)
	char destination[21];			//voyage destination(all 21 char must be filled, not used chars fill with @ ex: SZCZECIN@@@@@@@@@@@@@)
	unsigned char draught;			//current draught precission to 0,1m, ex: 6,6m -> draught = 66;
	unsigned char ETA_month;        //1 d0 12
	unsigned char ETA_day;          //1 do 31
	unsigned char ETA_hour;         //0 do 24
	unsigned char ETA_minute ;      //0 do 59
	unsigned char distance1Minute;	//distance made in 1 minute
	unsigned int distance1H;		//distance made in 1 hour
	unsigned int distance24H;		//distance made in 24 hours
	unsigned int totalVoyageDistance;//total yourney distance
	long currentROT;				//precission 0,01degree/minute ex: ROT = 10degrees/minute -> currentRoot = 1000
	int computedROT;                // kierunek ROT aktualny inicjowany przez -5 tylko do pierwszego rozruchu funkcji
	char currentSteerWheelPos;		//current steerwheel position
	char currentSteerPos;			//current steer position
	int currentPropellerRevolution; // current propeller revolution
	int rzadanaSpeed;               //rzadana predkosc w oparciu o nastawe pr?dko?ci nastawaSpeed
	char nastawaSpeed;              //0d -8 do +8 nastawa pr?dko?ci zmieniana dotykowymi przyciskami
	int rzadanyCourse;
	char rzadaneUstawienieSteru;    // od -35 do +35
	long totalTimeofVoyage;			//total time of voyage in seconds
};

#endif