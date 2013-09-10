#include <iostream>
#include <string>


#ifndef __AbsHistVec__
#define __AbsHistVec__

using namespace std;

class AbsHistVec {
public:
	AbsHistVec();
	~AbsHistVec();
	virtual size_t size() = 0;
	virtual void clear() = 0;
		
protected:
private:

};
#endif