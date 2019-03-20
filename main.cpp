/*
 * NAVCON_MK3.cpp
 *
 * Created: 2019-03-13 10:31:20
 * Author : Luke_DELL
 */ 

#include <avr/io.h>
#include "logic/Navcon_avr_os.h"
#include "logic/Statek.h"

Navcon_avr_os os;
//extern Statek ship;

int main(void)
{
	os.init();
	Statek ship;
	ship.updateAll();
    while (1) 
    {
		
    }
}

