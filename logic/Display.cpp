#include "Display.h"
#include "common.h"
#include "NAVCON_SYMBOLS.h"
#include <avr/io.h>
#include "../hardware/I2CBase.h"

#include "../hardware/MAX7219.h"



Display::Display(char typeOfCommunication)
{
	if(typeOfCommunication == USE_SPI)
	{
		//ENABLE SPI (if not enabled)
		// SPI Enable, Master mode
		if(consoleMainArray[NAVCON_SPI] != NAVCON_STATUS_ON)
		{
			SPI_init();
			consoleMainArray[NAVCON_SPI] = NAVCON_STATUS_ON;
		}
	}
	if(typeOfCommunication == USE_I2C)
	{
		//enable I2C (if not enabled)
		if(consoleMainArray[NAVCON_I2C] != NAVCON_STATUS_ON)
		{
			I2C_Init();
			consoleMainArray[NAVCON_I2C] = NAVCON_STATUS_ON;
		}
	}
	

	//--------------------------------------------------------------------------------------

	

}


