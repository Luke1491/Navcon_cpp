#include "Display.h"
#include "common.h"
#include "NAVCON_SYMBOLS.h"
#include <avr/io.h>
#include "../hardware/I2CBase.h"
#include "../hardware/MAX7219.h"



Display::Display()
{
#if (defined(NAVCON_MAIN_DISPLAYS_SPI_USED)||defined(NAVCON_DISPLAYS_MANIP_SPI_USED)) //check if main displays uses SPI bus or manipulator displays uses SPI bus

//pin definition
#define NAVCON_DISPLAY_PIN_SCK                   PB5
#define NAVCON_DISPLAY_PIN_MOSI                  PB3



#ifdef NAVCON_MAIN_DISPLAYS_SPI_USED // if main displays uses SPI bus
#define NAVCON_MAIN_DISPLAYS_PIN_SS              PB1 
// SCK MOSI CS/LOAD/SS for main displays
DDRB |= (1 << NAVCON_DISPLAY_PIN_SCK) | (1 << NAVCON_DISPLAY_PIN_MOSI) | (1 << NAVCON_MAIN_DISPLAYS_PIN_SS);
#endif //end NAVCON_MAIN_DISPLAYS_SPI_USED

#ifdef NAVCON_DISPLAYS_MANIP_SPI_USED// if manipulator displays uses SPI bus
#define NAVCON_MANIP_DISPLAYS_PIN_SS             PB2
// SCK MOSI CS/LOAD/SS for manip displays
DDRB |= (1 << NAVCON_DISPLAY_PIN_SCK) | (1 << NAVCON_DISPLAY_PIN_MOSI) | (1 << NAVCON_MANIP_DISPLAYS_PIN_SS);
#endif //end NAVCON_MAIN_DISPLAYS_SPI_USED

//ENABLE SPI
// SPI Enable, Master mode
SPI_init();
consoleMainArray[NAVCON_SPI] = NAVCON_STATUS_ON;

#endif // end check if displays uses SPI
//--------------------------------------------------------------------------------------


#ifdef NAVCON_MAIN_DISPLAYS_I2C_USED // check if main displays uses I2C bus
//enable I2C
I2C_Init();
consoleMainArray[NAVCON_I2C] = NAVCON_STATUS_ON;
#endif // end main displays uses I2C


}


