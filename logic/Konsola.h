#ifndef KONSOLA_H
#define KONSOLA_H
#include "Statek.h"
#include "Interface.h"

class Konsola
{
	public:
	Konsola();
	
	~Konsola();
	
	void ShowDataFromShipToInterface(const Statek *shipVoyageData, Interface* interf);
	
};
#endif