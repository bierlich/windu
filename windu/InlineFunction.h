#ifndef __InlineFunction__
#define __InlineFunction__

#include <vector>
#include <string>
#include "AbsFunction.h"

using namespace std;

template<typename axisVar>
class InlineFunction  : public AbsFunction<axisVar> {

public:
	InlineFunction() {

	}
	~InlineFunction() {

	}
	InlineFunction(string title, function<double (axisVar&, vector<double> par)>func) : _title(title), _func(func){

	}

	double Eval(axisVar val){
		return func(val,_par);
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
	function<double (axisVar&) > _func;
};


#endif