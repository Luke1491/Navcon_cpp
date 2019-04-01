#ifndef COMM_H
#define COMM_H
#include "Ship.h"
#include "Interface.h"
#include "Console.h"


extern volatile char consoleMainArray [];

//class Console;
extern Console console;
extern Ship ship;
extern Interface interface;

extern const Ship_model defaultShipModel;
extern const Ship_data defaultShipData;
extern const Ship_voyage_data defaultShipVoyageData;

void init(void);
//create main console modules
void createModules(void);



#endif

