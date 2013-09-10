#ifndef __HIParticle__
#define __HIParticle__

#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class HIParticle {
public:
	 HIParticle();
	~HIParticle();
	double phi;
	double eta;
	double pT;
	double weight;
	int pid;
	bool isch, hasstrangeparents;

protected:
private:

friend istream& operator>> (istream& aStream, HIParticle& aHIParticle);
friend ostream& operator<< (ostream& aStream, HIParticle& aHIParticle);

};
#endif

