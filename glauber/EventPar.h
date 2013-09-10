#include <iostream>
#include <string>
#include "AbsEventPar.h"

#ifndef __EventPar__
#define __EventPar__

using namespace std;

class EventPar : public AbsEventPar {
public:
	EventPar();
	~EventPar();
	int GetNParticles();
	double weight, b, xsec;
	int np, nch;
	
protected:
private:


friend istream& operator>> (istream& aStream, EventPar& aEvent); 
friend ostream& operator<< (ostream& aStream, EventPar& aEvent); 

};
#endif