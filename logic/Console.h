#ifndef CONSOLE_H
#define CONSOLE_H

class Console
{
	public:
	Console();
	
	~Console();
	
	void ShowDataFromShipToInterface(const void *shipVoyageData, void* interf);
	
};
#endif