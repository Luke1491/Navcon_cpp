#ifndef NAVCON_SYMBOLS
#define NAVCON_SYMBOLS

//###############CONFIGURATION###############

//CALL UPDATE AND REFRESH TIME (IN SECONDS) - DEFAULT 1s
#define NAVCON_MAIN_REFRESH_RATING_VALUE	1 //1 second - refresh rating


//-------------------I2C---------------------
//I2c used by main display - i2c enable in Display.cpp (in class constructor)
//COMMENT DEFINED BELOW IF I2C IS NOT USED(NAVCON variant 2)
#define NAVCON_MAIN_DISPLAYS_I2C_USED


//-------------------SPI---------------------
//SPi is used by manip display, ethernet card - SPI is enabled in display.cpp(in constuctor)
//and / or in Com_pc.cpp (in class constructor)
//COMMENT / UNCOMMENT IF NEEDED 
//#define NAVCON_MAIN_DISPLAYS_SPI_USED	//spi used for main displays
#define NAVCON_DISPLAYS_MANIP_SPI_USED	//spi used for manipulator displays
#define NAVCON_ETHERNET_SPI_USED		//spi used for ethernet ic connection

//-----------------PINOUT--------------------
//______modify if connected differently______
#define NAVCON_STEERWHEEL_PIN				PC0
#define NAVCON_BUZZER_PIN					PC1
#define NAVCON_ROSE_TRANSOPTOR_PIN			PC2
#define NAVCON_I2C_SDA_PIN					PC4
#define NAVCON_I2C_SCL_PIN					PC5
#define NAVCON_SPEED_ENCODER_A_PIN			PD0
#define NAVCON_SPEED_ENCODER_B_PIN			PD1
#define NAVCON_COURSE_ENCODER_A_PIN			PD2
#define NAVCON_COURSE_ENCODER_B_PIN			PD3
#define NAVCON_LED_SPEED_PIN				PD4
#define NAVCON_LED_ROSE_PIN					PD5
#define NAVCON_LED_STEERWHEEL_PIN			PD6
#define NAVCON_ETHERNET_RST_PIN				PB0
#define NAVCON_MANIP_DISP_SPI_SS_PIN		PB1
#define NAVCON_ETHERNET_SPI_SS_PIN			PB2
#define NAVCON_SPI_MOSI_PIN					PB3
#define NAVCON_SPI_MISO_PIN					PB4
#define NAVCON_SPI_SCK_PIN					PB5

//##########---END CONFIGURATION---##########

//Symbols used in entire program
//-------main array indexes---------
#define NAVCON_TIMER_1						0 
#define NAVCON_TIMER_2						1 
#define NAVCON_TIMER_3						2 
#define NAVCON_ADC							3
#define NAVCON_SPI							4
#define NAVCON_MAIN_REFRESH_RATING			5		//index of refresh rating (all console refresh rating depends on this variable) 1s = 100 - max 2,55s (255 in char variable)
#define NAVCON_STEER_REFRESH_RATING			6
#define NAVCON_PROPELLER_REFRESH_RATING		7
#define NAVCON_CONSOLE_ID					8
#define NAVCON_SHIP_ID						9
#define NAVCON_AUTOPILOT_ID					10
#define NAVCON_LOG_ID						11
#define NAVCON_GPS_ID						12
#define NAVCON_STEER_ID						13
#define NAVCON_PROPELLER_ID					14
#define NAVCON_ETHERNET_ID					15
#define NAVCON_MAIN_DISPLAY_COG_ID			16
#define NAVCON_MAIN_DISPLAY_SOG_ID			17
#define NAVCON_MANIP_DISPLAY_COG_ID			18
#define NAVCON_MANIP_DISPLAY_SOG_ID			19
#define NAVCON_ROSE_ID						20
#define NAVCON_ROSE_MOTOR_ID				21
#define NAVCON_TRANSOPTOR_ID				22
#define NAVCON_KNOB_COG_ID					23
#define NAVCON_KNOB_SOG_ID					24
#define NAVCON_STEER_WHEEL_ID				25
#define NAVCON_LED_COG_ID					26
#define NAVCON_LED_SOG_ID					27
#define NAVCON_CAP_BUTTON_ID				28
#define NAVCON_I2C							29
#define NAVCON_AUTOPILOT_MODE				30
#define NAVCON_LUMINATION_LEVEL				31
#define NAVCON_MAIN_MODE					32


//----symbols used for values description-----
#define NAVCON__ON							1
#define NAVCON__OFF							0

#define NAVCON_BUZZER_ON					1
#define NAVCON_BUZZER_OFF					0

//----status code-----
#define NAVCON_STATUS_OFF					0
#define NAVCON_STATUS_ON					1
#define NAVCON_STATUS_PAUSE					2
#define NAVCON_STATUS_ERROR					3



//Ship (ship) actual voyage param
#define NAVCON_SHIP_COG						0


//Autopilot class
#define NAVCON_AUTOPILOT_MODE_ON			1
#define NAVCON_AUTOPILOT_MODE_OFF			0

//lumination level 
#define NAVCON_LUMINATION_LEVEL_BRIGHT_DAY	0xF
#define NAVCON_LUMINATION_LEVEL_NORMAL_DAY	0xA
#define NAVCON_LUMINATION_LEVEL_DARK_DAY	0x6
#define NAVCON_LUMINATION_LEVEL_NIGHT		0x0

#endif