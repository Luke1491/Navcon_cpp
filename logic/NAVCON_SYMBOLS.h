#ifndef NAVCON_SYMBOLS
#define NAVCON_SYMBOLS

//Symbols used in Navcon_avr_os class
//-------main array indexes---------
#define NAVCON_TIMER_1_ON					0 
#define NAVCON_TIMER_2_ON					1 
#define NAVCON_TIMER_3_ON					2 
#define NAVCON_ADC_ON						3
#define NAVCON_SPI_ON						4
#define NAVCON_MAIN_REFRESH_RATING			5		//index of refresh rating (all console refresh rating depends on this variable) 1s = 100 - max 2,55s (255 in char variable)
#define NAVCON_STEER_REFRESH_RATING			6

//critical parameters


//Statek (ship) actual voyage param
#define NAVCON_SHIP_COG						0


//Autopilot class
#define NAVCON_AUTOPILOT_ON					1
#define NAVCON_AUTOPILOT_OFF				0


#endif