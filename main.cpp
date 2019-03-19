/*
 * NAVCON_MK3.cpp
 *
 * Created: 2019-03-13 10:31:20
 * Author : Luke_DELL
 */ 

#include <avr/io.h>
#include "logic/Navcon_avr_os.h"


int main(void)
{

	Navcon_avr_os os;
    /* Replace with your application code */
	extern Statek ship;
	
	ship.updateAll();
    while (1) 
    {
		
    }
}

