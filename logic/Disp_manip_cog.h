#ifndef DISP_MANIP_COG_H
#define DISP_MANIP_COG_H
#include "NAVCON_SYMBOLS.h"
#include "Display.h"

//this class uses SPI communication to display data

class Disp_manip_cog : public Display
{


public:
Disp_manip_cog(char typeOfCommunication, unsigned char ss_pin, unsigned int reqCourse, char autopilotMode);
~Disp_manip_cog(){}

void ShowRequiredCourse(int requiredCourse, char autopilotMode);
};

#endif
