#ifndef SRUBA_H
#define SRUBA_H

class Sruba
{

	int maxRevolution;
	char rotationRating; //time in seconds*100 for change propeller rotation by one, ex: 10 means change rotation by one in 0,1s
	int* currentRevolution;
	int requestedRevolution;
	
	public:
	Sruba(int shipModelMaxRevolution, char revRatting, int* currentPropelerRevolution);
	
	~Sruba();
	
	void propelerChangeRevolution(int _requestedRevolution);
	
	void SrubaInterruptFunction(void);
	
	
};

#endif