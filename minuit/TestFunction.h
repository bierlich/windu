#ifndef __TestFunction__
#define __TestFunction__

#include <vector>
#include <string>
#include "AbsFunction.h"

using namespace std;
class TestFunction  : public AbsFunction {

public:
	TestFunction() {

	}
	~TestFunction() {

	}
	TestFunction(string title) : _title(title){
		_title = title;
	}

	double operator()(const vector<double>& par) const{
	double x = par[0];
    double y = par[1];
    double z = par[2];
    double w = par[3];

	return ((1./70.)*(21*x*x + 20*y*y + 19*z*z - 14*x*z - 20*y*z) + w*w);
}

	double Up() const {return 1.;}

protected:
private:
	vector<double> _par;
	string _title;

};


#endif