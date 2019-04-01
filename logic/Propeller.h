#ifndef PROPELLER_H
#define PROPELLER_H

class Propeller
{

	int maxRevolution;
	char rotationRating; //time in seconds*100 for change propeller rotation by one, ex: 10 means change rotation by one in 0,1s
	int* currentRevolution;
	int requestedRevolution;
	
	public:
	Propeller(int shipModelMaxRevolution, char revRatting, int* currentPropelerRevolution);
	
	~Propeller();
	
	void propelerChangeRevolution(int _requestedRevolution);
	
	void PropellerInterruptFunction(void);
	
	
};

#endif