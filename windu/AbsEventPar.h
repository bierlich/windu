#include <iostream>
#include <string>


#ifndef __AbsEventPar__
#define __AbsEventPar__

using namespace std;

class AbsEventPar {
public:
	AbsEventPar();
	~AbsEventPar();
	virtual int GetNParticles() = 0;
	
protected:
private:

};
#endif