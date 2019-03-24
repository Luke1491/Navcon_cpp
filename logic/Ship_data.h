#ifndef SHIP_DATA_H
#define SHIP_DATA_H

struct Ship_data				    //ship constants data
{
	char mmsi[10];					//9 digits in ""
	char navStatus;					//0d 0 do 15
	char pas;
	char typKomunikatu;
	long imoNumber;					//7 digits
	char callSign[8];
	char shipName[21];
	char typeOfShip;				// 1 do 99
	int dimA;						//length overall
	int dimB;						//width overall
	int dimC;						//height overall
};

#endif