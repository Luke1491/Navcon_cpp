#ifndef DISP_MANIP_COG_H
#define DISP_MANIP_COG_H
#include "NAVCON_SYMBOLS.h"

//this class uses SPI communication to display data

class Disp_manip_cog
{


public:
Disp_manip_cog();
~Disp_manip_cog();	

void ShowRequiredCourse(int requiredCourse);
};
#endif