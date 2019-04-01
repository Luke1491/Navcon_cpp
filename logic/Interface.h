#ifndef INTERFACE_H
#define INTERFACE_H

class Disp_manip_cog;

class Interface
{
	protected:
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
	
// 	Rose * rose;
// 	Main_disp_cog * mainDispCog;
// 	Main_disp_sog * mainDispSog;
 	Disp_manip_cog * dispManipCog;
// 	Disp_manip_sog * dispManipSog;
// 	Cog_led * cogLed;
// 	Sog_led * sogLed;
// 	Steer_wheel * steerWheel;
// 	Button_cap * buttonCap;
// 	Knob_cog * knobCog;
// 	Knob_sog * knobSog;
	
	void getDataToDisplay(const unsigned int &course, const int &speed, const int &rzadanyCourse, const int &rzadanaSpeed);
	void refreshDisplays();
	void pushDataToConsole(long data);//to do
	void reset(void); //to do
};

#endif