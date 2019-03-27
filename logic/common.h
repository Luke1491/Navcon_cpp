#ifndef COMM_H
#define COMM_H
#include "Statek.h"
#include "Interface.h"
#include "Konsola.h"


extern char hardwareInfo [];

//class Konsola;
extern Konsola console;
extern Statek ship;
extern Interface interface;
void init(void);
//create main console modules
void createModules(void);



#endif

