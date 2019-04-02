#include "Ethernet.h"
#include "common.h"
#include "NAVCON_SYMBOLS.h"
#include "Com_pc.h"
#include "../hardware/enc28j60.h"
#include "../hardware/net.h"
#include <avr/io.h>


Ethernet::Ethernet()
{
	Com_pc(); // call parent constructor
	enc28j60Init((uint8_t*)this->mymac);//initilize spi and set out pins
	for (unsigned int i = 0; i < BUFFER_SIZE+1; i++)
	{
		buf[i] = 0; // create and fill buf array with 0 value
	}
}

//##############################################################################################################
//#############################################ETHERNET FUNCTION################################################
//##############################################################################################################




// wska?nik do funkcji zwrotnej w?asnego zdarzenia UDP_EVENT()
// void (*mk_udp_event_callback)(unsigned char *peer_ip, unsigned int port,
// unsigned int datapos, unsigned int len);
// 
// funkcja do rejestracji funkcji zwrotnej w zdarzeniu UDP_EVENT()
// void register_udp_event_callback(void (*callback)(unsigned char *peer_ip,
// unsigned int port, unsigned int datapos, unsigned int len))
// {
// 	mk_udp_event_callback = callback;
// }
// 
// 
// ---------------------------------- deklaracje zmiennych globalnych -------------------------------
// indeksy adres?w IP w postaci przyjaznych nazw
// enum ip_names {ip_pc, ip_sterownik1};
// adresy IP sterownik?w z kt?rymi b?dziemy si? komunikowa?
// za pomoc? protoko?u UDP  ----> pierwszy element tablicy to IP twojego komputera
// drugi element to IP np innego uk?adu ATB
// unsigned char farip[2][4] = { {169,254,131,151}, {192,168,0,180} };
// unsigned char PC_IP[4] = {169,254,131,151};
// 
// 
// 
// separator token?w we w?asnych ramkach przesy?anych przez UDP
// char sep[] = ","; //w komunikatach z navdeca s? przecinki jako separatory token?w natomiast kropki rozdzielaj? cz?c ca?kowit? od u?amkowej
// 
// _______________________________________________________________________________________________________________
// *****************funkcje do obs?ugi komend**********************
// komenda $ROZETA
// void parseROZETA(char *buffer)
// {
// 	//unsigned char przygotowanieDoTarczyZielonej;
// 	char *wsk,*wsk1;
// 	unsigned int liczba_przedzialow, nr_przedzialu, wart1, wart2;
// 	unsigned int wart1LED, wart2LED;
// 	uint32_t ulamekWart1, ulamekWart2;
// 	char str[25];
// 	wsk = strtok_r(NULL, sep, &buffer); //wy?uskujemy ilosc przedzialow
// 	liczba_przedzialow = atol(wsk);
// 	wsk = strtok_r(NULL, sep, &buffer); //nr przedzialu
// 	nr_przedzialu = atol(wsk);
// 	wsk = strtok_r(NULL, sep, &buffer); //pierwsza wartosc
// 	//-----------------------
// 	strcpy(str, wsk);
// 	wsk1 = strtok(str, ".");
// 	wart1 = atol(wsk1);
// 	wsk1 = strtok(NULL, ",");
// 	ulamekWart1 = atol(wsk1);
// 	//-----------------------
// 	wsk = strtok_r(NULL,sep, &buffer);//druga wartosc
// 	//----------------------
// 	strcpy(str, wsk);
// 	wsk1 = strtok(str, ".");
// 	wart2 = atol(wsk1);
// 	wsk1 = strtok(NULL, ",");
// 	ulamekWart2 = atol(wsk1);
// 	//----------------------
// 	wsk = strtok_r(NULL, sep, &buffer);//wsk ->NULL
// 	
// 	wart1LED = stopnieNaLED(wart1);
// 	wart2LED = stopnieNaLED(wart2);
// 	if( nr_przedzialu == 1) //gdy przyjdzie pierwszy przedzail to wyzeruj tarcz? nadaj kolor czerwony
// 	{
// 		for(unsigned char j = 0; j<TARCZA_MAXPIX; j++)
// 		{
// 			TARCZA_led[j] = kolory[1];  //wstaw na ca?ej tarczy kolor czerwony
// 		}
// 	}
// 	
// 	if(wart1LED>wart2LED)
// 	{//zamiana zmiennych wartosciami
// 		unsigned int zmiennaPomocnicza;
// 		zmiennaPomocnicza = wart1LED;
// 		wart1LED = wart2LED; 
// 		wart2LED = zmiennaPomocnicza;
// 		for(unsigned char i = 0; i<wart1LED; i++)
// 		{
// 			TARCZA_led[i] = kolory[3];//yellow
// 		}
// 		for(unsigned char i = wart2LED; i<TARCZA_MAXPIX; i++)
// 		{
// 			TARCZA_led[i] = kolory[3];//yellow
// 		}
// 	}
// 	else
// 	{
// 		
// 	if(liczba_przedzialow==1 && nr_przedzialu==1 && wart1==0 && wart2==360)
// 	{
// 		for(unsigned char i = 0; i<TARCZA_MAXPIX; i++)
// 		{
// 			TARCZA_led[i] = kolory[8];//kolor zielony
// 		}
// 	}
// 	
// 	for(unsigned char i = wart1LED; i<wart2LED; i++)
// 	{
// 		TARCZA_led[i] = kolory[3];
// 	}//end for
// 	}//end main else 
// 	//MAX7219_SendCourseAndSpeed(wart1LED, wart2LED);//wy?wietlenie testowe obliczonych warto?ci(do cel?w sprawdzaj?cych - normalnie pozostawi? zakomentarzowanym)
// }
// 
// Komenda SHIPMODEL
// void parseSHIPMODEL(char *buffer)
// {
// 	char *wsk;
// 	unsigned char numerModelu;
// 	wsk = strtok_r(NULL, sep, &buffer); //wy?uskujemy numer modelu statku
// 	numerModelu = atoi(wsk);
// 	wsk = strtok_r(NULL, sep, &buffer); //wsk ->NULL
// 	switch(numerModelu)
// 	{
// 		case 1: {
// 			//#######PRZYPISANIE WARTOSCI STATKU Z FLASHA#################
// 			memcpy_P(&ownship, &flashOwnship1, sizeof(ownship));
// 			//przypisanie warto?ci okre?laj?cych zachowanie statku
// 			memcpy_P(&shipmodel, &shipmodel1, sizeof(shipmodel));
// 		} break;
// 		case 2: {
// 			//#######PRZYPISANIE WARTOSCI STATKU Z FLASHA#################
// 			memcpy_P(&ownship, &flashOwnship2, sizeof(ownship));
// 			//przypisanie warto?ci okre?laj?cych zachowanie statku
// 			memcpy_P(&shipmodel, &shipmodel2, sizeof(shipmodel));
// 		} break;
// 		case 3: {
// 			//#######PRZYPISANIE WARTOSCI STATKU Z FLASHA#################
// 			memcpy_P(&ownship, &flashOwnship3, sizeof(ownship));
// 			//przypisanie warto?ci okre?laj?cych zachowanie statku
// 			memcpy_P(&shipmodel, &shipmodel3, sizeof(shipmodel));
// 		} break;
// 		default: {
// 			//#######PRZYPISANIE WARTOSCI STATKU Z FLASHA#################
// 			memcpy_P(&ownship, &flashOwnship1, sizeof(ownship));
// 			//przypisanie warto?ci okre?laj?cych zachowanie statku
// 			memcpy_P(&shipmodel, &shipmodel1, sizeof(shipmodel));
// 		} break;
// 	}//end switch
// 	shipparam.aktualnyROT=0;	          //dok?adno?? 0,01stopnia np 10-->ROT = 0,1stopnia
// 	shipparam.wyliczonyROT=0;             // kierunek ROT aktualny inicjowany przez -5 tylko do pierwszego rozruchu funkcji
// 	shipparam.aktualneUstawienieSteru=0;   //aktualne polozenie p?etwy sterowej
// 	shipparam.rzadanaSpeed=ownship.speed;             //rz?dana pr?dko?? w oparciu o nastaw? pr?dko?ci nastawaSpeed
// 	shipparam.nastawaSpeed=ownship.speed;              //0d -8 do +8 nastawa pr?dko?ci zmieniana dotykowymi przyciskami
// 	shipparam.rzadanyCourse=ownship.course;
// 	shipparam.rzadaneUstawienieSteru=0;
// 	
// 	int16_t roznicaDoResetuTarczy = kursNaTarczy - 1800;
// 	unsigned int iloscKrokowDoResetu;
// 	if(roznicaDoResetuTarczy>0) 
// 	{
// 		iloscKrokowDoResetu = 3600-kursNaTarczy+ownship.course; 
// 	 for(unsigned int i = 0; i<iloscKrokowDoResetu; i++)
// 	 {
// 		 ruszTarczeOjedenKrok(1);
// 		 _delay_ms(5);
// 		 kursNaTarczy++;
// 		 if(kursNaTarczy > 3600) kursNaTarczy = 0;
// 	 }
// 	}
// 	if(roznicaDoResetuTarczy<0)
// 	{
// 		iloscKrokowDoResetu = kursNaTarczy-ownship.course;
// 		for(unsigned int i = 0; i<iloscKrokowDoResetu; i++)
// 		{
// 			ruszTarczeOjedenKrok(0);
// 			_delay_ms(5);
// 			kursNaTarczy--;
// 			if(kursNaTarczy < 0) kursNaTarczy = 3599;
// 		}
// 	}
//  motorCoilOff();
// 	
// }
// /******* w?asna funkcja u?ytkownika w kt?rej mo?emy reagowa? na ramk? UDP ***********/
// /****/
// void udp_event_callback(unsigned char *peer_ip, unsigned int port, unsigned int datapos, unsigned int len) {
// 	//unsigned char i=0;
//     char str[40];
// 
//     // wska?nik na potrzeby funkcji strtok_r
//     char *wsk, *reszta;
// 	unsigned char komenda;
// 
//     // wy?wietlamy na LCD z jakiego IP nadesz?a ramka
//     // wy?wietlamy na jaki port nadesz?a ramka
// 
//     // je?li ramka przysz?a na drugi numer portu z listy myport[]
//     if(port == myport[1]) {
//     	// odpowiadamy na zapytanie UDP po ten sam port
//     	strcpy(str,"Ramka odpowiedzi UDP");
//     	make_udp_reply_from_request(buf,str,strlen(str), port);
// 
//         // wysy?amy now? ramk? na dowolny inny port
//     	strcpy((char*)&buf[datapos],"Nowa ramka UDP!");
//         send_udp_prepare(buf, 1200, farip[ip_pc], 43500);
//         send_udp_transmit(buf,strlen(str));
//     }
// 
//     // je?li ramka przysz?a na pierwszy numer portu z listy myport[]
//     if(port == myport[0]) {
//     	// sprawdzamy czy zawiera dane
//     	wsk = strtok_r((char*)&buf[datapos + 1], sep, &reszta); //buf[datapos + 1] ?eby omin?? znak $ kt?ry wywala b??d w kompilacji
//     	if( wsk ) {
//     		// je?li zawiera dane to sprawdzamy jaka komenda
// 			char charkom [10];
// 			strcpy(charkom, wsk);
// 			
// 			if(!(strcmp(charkom, "ROZETA"))) komenda = 0;
// 			else if(!(strcmp(charkom, "SHIPMODEL"))) komenda = 1;
// 			else if(!(strcmp(charkom, "set_lcd"))) komenda = 2;
// 			else komenda = 10;
//     		switch( komenda ) {
//     		// i w zale?no?ci od komendy wywo?ujemy odpowieni?
//     		// funkcj? parsuj?c? z tabeli wska?nik?w do funkcji parsuj?cych
//     		// przekazujemy jednocze?nie wska?nik do pozosta?ej cz?ci
//     		// ?a?cucha z danymi, kt?ry funkcje b?d? parsowa? we w?asnym zakresie
//     		case 0: parseROZETA(reszta); break;
//     		case 1: parseSHIPMODEL(reszta); break;
//     		case 2: ; break;
// 			case 10: ; break;
//     		}
// 			
//     	}
//     }
// }
// 
// 
// /********** zdarzenie UDP EVENT ***********************/
// void UDP_EVENT(unsigned int *port) {
// 	// zmienne tymczasowe (automatyczne)
//     unsigned int plen;//, dat_p;
//     unsigned int dport;
//     unsigned char is_my_port=0;
//     unsigned char i=0;
// 
// 
//     unsigned char udp_data_len=0;
// 
// 
//     // sprawdzamy czy istnieje nowy odebrany pakiet
//     plen = enc28j60PacketReceive(BUFFER_SIZE, buf);
//     // obs?uga ni?szych warstw stosu TCP jak ICMP, ARP itp
//     // m.inn t? drog? obs?ugiwane s? zewn?trzne PING'i
//     // w tym miejscu sprawdzane jest od razu czy odczytana ramka
//     // jest posiada typ jaki obs?ugiwany jest przez ten stos TCP
//     // oraz czy jest ona zaadresowana do nas (w numeru IP)
//     packetloop_icmp_tcp(buf,plen);
// 
//     // je?li d?ugo?? odebranej ramki jest wi?ksza ni? 0
//     // to oznacza, ?e mamy do czynienia z prawid?owo odebran?
//     // ramk? wraz z prawid?ow? sum? kontroln?
//     // sprawdzamy tak?e, czy na pewno mamy do czynienia z ramk? UDP a nie np TCP
//     if( plen && buf[IP_PROTO_P]==IP_PROTO_UDP_V ) {
// 
//     	// sprawdzamy do jakiego nr portu kierowana jest ta ramka UDP
//     	dport = (buf[UDP_DST_PORT_H_P]<<8) | buf[UDP_DST_PORT_L_P];
// 
//     	// sprawdzamy w p?tli czy jest to ramka przeznaczona do
//     	// portu nas?uchowego, kt?re obs?uguje nasze urz?dzenie
//     	// list? dowolnej ilo?ci port?w definiujemy w tablicy myport[]
//     	// kt?ra przekazywana jest jako parametr do zdarzenia/funkcji UDP_EVENT()
//     	do {
//     		if( (is_my_port = (port[i++] == dport)) ) break;
//     	} while (i<sizeof(port));
// 
//     	// sprawdzamy czy informacja przysz?a na obs?ugiwany przez nas port UDP
//     	if ( is_my_port ){
// 			udp_data_len=buf[UDP_LEN_L_P]-UDP_HEADER_LEN;
// 
// 			// je?li wszystko si? zgadza to sprawdzamy, czy zarejestrowana jest
// 			// funkcja zwrotna przez u?ytkownika. Je?li nie jest zarejestrowana
// 			// to nie wykonana si? ?adna akcja poza powy?ej obs?ug?
// 			// ni?szych warstw stosu TCP (np PING czy ARP)
// 			// Je?li jest zarejestrowana to zostanie wywo?ana z odpowiednimi parametrami
// 			// 1. podany b?dzie adres IP sk?d nadesz?a ramka
// 			// 2. podany b?dzie port na jaki zosta?a do nas skierowana ramka
// 			// 3. indeks do bufora ca?ej ramki TCP, wskazuj?cy na pocz?tek danych w ramce UDP
// 			// 4. ilo?? danych w bajtach przes?anych w ramce UDP
// 			if(mk_udp_event_callback) (*mk_udp_event_callback)(&(buf[IP_SRC_P]), dport, UDP_DATA_P, udp_data_len);
//         }
//     }
// }
// 
// void ping_callback(unsigned char *ip){
// 	//response from ping request
// }
// 
// void przygotujIWyslijRamkeOWN(void)
// {
// 	//przygotuj ramk? UDP
// 	char str [150] = {"$OWN"};
// 	char str1[21]; //tablica do przechowaywania reprezentacji wyliczonych warto?ci w postaci tekstu (jednorazowa przetrzymujemy 1 oblizon? warto??)
// 	int32_t wartoscDoWyswUDP;  //b?d? tu wpisywane po kolei wszystkie warto?ci obliczone przez symulator
// 	strcat(str, ",0,");                                 //1. pozycja zintegrowana
// 	strcat(str, ownship.MMSI);							//2. MMSI
// 	strcat(str, ",");
// 	strcat(str, ownship.NAVSTATUS);						//3. status nawigacyjny
// 	strcat(str, ",");
// 	wartoscDoWyswUDP = shipparam.aktualnyROT*6/10;
// 	itoa(wartoscDoWyswUDP, str1, 10);
// 	strcat(str, str1 );									//4. ROT - cze?? ca?kowita
// 	strcat(str, ".");								
// 	wartoscDoWyswUDP = (shipparam.aktualnyROT%100)*6/10;
// 	itoa(wartoscDoWyswUDP, str1, 10);
// 	strcat(str, str1 );									//4. ROT - cze?? u?amkowa
// 	strcat(str, ",");									
// 	wartoscDoWyswUDP = ownship.speed/10;
// 	if(ownship.speed<0){strcat(str, "-"); wartoscDoWyswUDP = -wartoscDoWyswUDP;}//umozliwia interpretacje przez navdec				
// 	itoa(wartoscDoWyswUDP, str1, 10);
// 	strcat(str, str1 );									//5. SOG - cz?? ca?kowita
// 	strcat(str, ".");	
// 	wartoscDoWyswUDP = ownship.speed%10;
// 	if(ownship.speed<0){ wartoscDoWyswUDP = -wartoscDoWyswUDP;}				
// 	itoa(wartoscDoWyswUDP, str1, 10);
// 	strcat(str, str1 );									//5. SOG - cz?? u?amkowa
// 	strcat(str, ",");	
// 	wartoscDoWyswUDP = ownship.posLong/1000000;
// 	if(ownship.posLong<0){strcat(str, "-"); wartoscDoWyswUDP = -wartoscDoWyswUDP;}//umozliwia interpretacje przez navdec
// 	itoa(wartoscDoWyswUDP, str1, 10);
// 	strcat(str, str1 );									//6. LONG - cz?? ca?kowita
// 	strcat(str, ".");
// 	wartoscDoWyswUDP = ownship.posLong%1000000;
// 	if(ownship.posLong<0){wartoscDoWyswUDP = -wartoscDoWyswUDP;}//umozliwia interpretacje przez navdec
// 	//zabezpieczenie przed ucinaniem poprzedzj?cych zer po przecinku
// 	if(wartoscDoWyswUDP<100000 && wartoscDoWyswUDP>=10000)	    strcat(str, "0");
// 	else if(wartoscDoWyswUDP<10000 && wartoscDoWyswUDP>=1000)	strcat(str, "00");
// 	else if(wartoscDoWyswUDP<1000 && wartoscDoWyswUDP>=100)		strcat(str, "000");
// 	else if(wartoscDoWyswUDP<100 && wartoscDoWyswUDP>=10)		strcat(str, "0000");
// 	else if(wartoscDoWyswUDP<10 && wartoscDoWyswUDP>=1)			strcat(str, "00000");
// 	
// 	ltoa(wartoscDoWyswUDP, str1, 10);
// 	strcat(str, str1 );									//6. LONG- cz?? u?amkowa
// 	strcat(str, ",");
// 	wartoscDoWyswUDP = ownship.posLat/1000000;
// 	if(ownship.posLat<0){strcat(str, "-"); wartoscDoWyswUDP = -wartoscDoWyswUDP;}//umozliwia interpretacje przez navdec
// 	itoa(wartoscDoWyswUDP, str1, 10);
// 	strcat(str, str1 );									//7. LAT - cz?? ca?kowita
// 	strcat(str, ".");
// 	wartoscDoWyswUDP = ownship.posLat%1000000;
// 	if(ownship.posLat<0){wartoscDoWyswUDP = -wartoscDoWyswUDP;}//umozliwia interpretacje przez navdec
// 	//zabezpieczenie przed ucinaniem poprzedzj?cych zer po przecinku
// 	if(wartoscDoWyswUDP<100000 && wartoscDoWyswUDP>=10000)		strcat(str, "0");
// 	else if(wartoscDoWyswUDP<10000 && wartoscDoWyswUDP>=1000)	strcat(str, "00");
// 	else if(wartoscDoWyswUDP<1000 && wartoscDoWyswUDP>=100)		strcat(str, "000");
// 	else if(wartoscDoWyswUDP<100 && wartoscDoWyswUDP>=10)		strcat(str, "0000");
// 	else if(wartoscDoWyswUDP<10 && wartoscDoWyswUDP>=1)			strcat(str, "00000");
// 	ltoa(wartoscDoWyswUDP, str1, 10);
// 	strcat(str, str1 );									//7. LAT- cz?? u?amkowa
// 	strcat(str, ",");
// 	wartoscDoWyswUDP = ownship.course/10;
// 	itoa(wartoscDoWyswUDP, str1, 10);
// 	strcat(str, str1 );									//8. COG - cze?? ca?kowita
// 	strcat(str, ".");
// 	wartoscDoWyswUDP = ownship.course%10;
// 	itoa(wartoscDoWyswUDP, str1, 10);
// 	strcat(str, str1 );									//8. COG - cze?? u?amkowa
// 	strcat(str, ",");
// 	wartoscDoWyswUDP = ownship.course/10;
// 	itoa(wartoscDoWyswUDP, str1, 10);
// 	strcat(str, str1 );									//9. HEADING - cze?? ca?kowita (TAKI JAK COG)
// 	strcat(str, ".");
// 	wartoscDoWyswUDP = ownship.course%10;
// 	itoa(wartoscDoWyswUDP, str1, 10);
// 	strcat(str, str1 );									//9. HEADING - cze?? u?amkowa (TAKI JAK COG)
// 	strcat(str, ",");
// 	strcat(str, "0.0,0.0," );							//10 / 11 POZYCJA WSP KARTEZJA?SKIE 
// 	strcat(str, ownship.PAS );							//12. PAS
// 	strcat(str, ",");
// 	strcat(str, ownship.TYP_COMMUNIKATU );				//13. TYP KOMUNIKATU
// 	strcat(str, ",");
// 	strcat(str, ownship.IMO_NUMBER );					//14. IMO
// 	strcat(str, ",");
// 	strcat(str, ownship.CALL_SIGN );					//15. CALLSIGN
// 	strcat(str, ",");
// 	strcat(str, ownship.SHIP_NAME);						//16. SHIP NAME
// 	strcat(str, ",");
// 	strcat(str, ownship.TYPE_OF_SHIP );					//17. TYP STATKU
// 	strcat(str, ",");
// 	strcat(str, ownship.DIM_A );						//18. DIMA
// 	strcat(str, ",");
// 	strcat(str, ownship.DIM_B );						//19. DIMB
// 	strcat(str, ",");
// 	strcat(str, ownship.DIM_C );						//20. DIMC
// 	strcat(str, ",");
// 	strcat(str, ownship.DIM_D );						//21. DIMD
// 	strcat(str, ",1,");									//22. PRZECINEK + TYP URZ?DZENIA
// 	wartoscDoWyswUDP = ownship.ETA_month;
// 	itoa(wartoscDoWyswUDP, str1, 10);
// 	strcat(str, str1 );									//23. ETA MONTH
// 	strcat(str, ",");
// 	wartoscDoWyswUDP = ownship.ETA_day;
// 	itoa(wartoscDoWyswUDP, str1, 10);
// 	strcat(str, str1 );									//24. ETA DAY
// 	strcat(str, ",");
// 	wartoscDoWyswUDP = ownship.ETA_hour;
// 	itoa(wartoscDoWyswUDP, str1, 10);
// 	strcat(str, str1 );									//25. ETA HOUR
// 	strcat(str, ",");
// 	wartoscDoWyswUDP = ownship.ETA_minute;
// 	itoa(wartoscDoWyswUDP, str1, 10);
// 	strcat(str, str1 );									//26. ETA MINUTE
// 	strcat(str, ",");
// 	strcat(str, ownship.DRAUGHT);						//27. DRAUGHT
// 	strcat(str, ",");
// 	strcat(str, ownship.DESTINATION);					//28. DESTINATION	
// 	strcat(str, ",");
// 	//wy?lij ramk? UDP na adres ip znajduj?cy si? w tablicy farip[] na port 24478 (odczytywane przez plik filetoNAVDEC, aby oblicza? poprawne CPA i TCPA) 
// 	send_udp(buf, str, strlen(str), 8095, farip[0], 24478);
// 	//wy?lij ramk? UDP na adres ip znajduj?cy si? w tablicy farip[] na port 10110 (odczytywane przez program NAVDEC)
// 	send_udp(buf, str, strlen(str), 8095, farip[0], 10110);
// }