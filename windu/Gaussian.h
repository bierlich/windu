#ifndef __Gaussian__
#define __Gaussian__

#include "AbsFunction.h"

template<typename axisVar>

class Gaussian : public AbsFunction<axisVar> {
public: 
	Gaussian(string title){
		// Implements a Gaussian function of the form:
		// f (x) = a*exp(-(x - b)**2/(2*c**2))
		// Parameters are: par = {a,b,c} = (default) {1/sqrt(2pi), 0,  1}
		_par = {1/sqrt(2*M_PI),0,1};
		_title = title;
	}
	double Eval(axisVar val){
		return _par[0]*exp(-(val - _par[1])*(val - _par[1])/(2*_par[2]*_par[2]));
	}

	vector<double> GetParameters(){
		return _par;
	}
	void SetParameters(vector<double> par){
		_par = par;
	}
protected:
private:
	vector<double> _par;
	string _title;
	
};
#endif