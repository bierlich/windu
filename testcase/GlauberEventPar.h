#include <iostream>
#include <string>
#include "AbsEventPar.h"

#ifndef __GlauberEventPar__
#define __GlauberEventPar__

using namespace std;

class GlauberEventPar : public AbsEventPar {
public:
	GlauberEventPar();
	~GlauberEventPar();
	int GetNParticles();
	int GetAncestors(double par, string model = "");
	double b;
	int npart, ncoll;

protected:
private:


friend istream& operator>> (istream& aStream, GlauberEventPar& aEvent); 
friend ostream& operator<< (ostream& aStream, GlauberEventPar& aEvent); 

};
#endif
