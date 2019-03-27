#ifndef INTERFACE_H
#define INTERFACE_H



class Interface
{
	char interfaceMode;
	unsigned int interfaceMAINCourse;
	int interfaceMAINSpeed;
	int interfaceManipCourse;
	int interfaceManipSpeed;
	char interfaceSteerWheelPos;
	char interfaceRose[359];
	public:
	Interface(const unsigned int &course, const int &speed, const int &rzadanyCourse, const int &rzadanaSpeed);
	~Interface();
	
	void getDataToDisplay(const unsigned int &course, const int &speed, const int &rzadanyCourse, const int &rzadanaSpeed);
	void pushDataToConsole(long data);
};

#endif