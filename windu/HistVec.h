#ifndef __HistVec__
#define __HistVec__

#include "../common/AbsHistVec.h"
#include <istream>
#include <string>
#include <stdlib.h>
#include <memory>

using namespace std;

template<typename T>
class Histogram;

template<typename axisVar=double>
class HistVec : public AbsHistVec {
public:
	typedef vector<shared_ptr<Histogram<axisVar>>> hPtrVec;

	HistVec(){

	}
	~HistVec(){

	}

	void clear(){
		hVec.clear();
	}

	size_t size(){
		return hVec.size();
	}

	typename hPtrVec::iterator begin(){
		return hVec.begin();
	}

	typename hPtrVec::iterator end(){
		return hVec.end();
	}

	void push_back(Histogram<axisVar> hist){
		hVec.push_back(make_shared<Histogram<axisVar>>(hist));
	}
	void push_back(shared_ptr<Histogram<axisVar>> histP){
		hVec.push_back(histP);
	}

	void push_back_clone(Histogram<axisVar> hMaster, string title=""){
		push_back(make_shared<Histogram<axisVar>>(hMaster.EmptyClone(title)));
	}

	shared_ptr<Histogram<axisVar>> operator[](int i){
		return hVec[i];
	} 	

protected:

private:
	hPtrVec hVec;

};

#endif

