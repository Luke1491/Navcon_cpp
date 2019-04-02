#ifndef ETHERNET_H
#define ETHERNET_H

#include <avr/io.h>
#include "Com_pc.h"

#define BUFFER_SIZE 650  //buffer for UDP data

class Ethernet : public Com_pc
{
	// MAC adress
	const uint8_t mymac[6] = {'N','A','V','D','E','C'};
	// ustalamy adres IP urz?dzenia
	const unsigned char myip[4] = {169,254,131,153};

	// ustalamy porty UDP z jakich b?dziemy korzysta?
	// mo?e ich by? dowolna ilo??
	const unsigned int myport[2] = {8095,24478};
	// ustalamy adres IP bramy domy?lnej w sieci LAN
	//static unsigned char gwip[4] = {169,254,255,255};
		
	// ustalamy wielko?? bufora dla ramek TCP/UDP

	unsigned char buf[BUFFER_SIZE+1];
	public:
	Ethernet();
	~Ethernet();
	
	
	
};

#endif