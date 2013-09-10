#ifndef __Chi2Function__
#define __Chi2Function__

#include <vector>
#include <string>
#include "Minuit2/FCNBase.h"
#include "Minimizable.h"

template<typename T>
class AbsFunction;

using namespace std;
template<typename axisVar>
class Chi2Function : public Minimizable {

public:
	Chi2Function(string title, AbsFunction<axisVar>* predict, 
				  vector<double> data, vector<double> error, vector<axisVar> positions){
		_title = title;
		_predict = predict;
		_positions = positions;
		_data = data;
		_error = error;
	}

	double operator()(const std::vector<double>& par) const{

		_predict->SetParameters(par);

		vector<double> pred = _predict->GetValues(_positions);

		int deg_of_freedom = _data.size() - par.size() - 1;

		double chi2 = 0;

		auto predItr = pred.begin();
		auto errItr = _error.begin();
		for(auto dataItr : _data){
			double num = (*predItr - dataItr);
			chi2+=num*num/(*errItr)/(*errItr);
			++predItr;
			++errItr;
		}

		chi2/=deg_of_freedom;
		return chi2;
	}

	double Up() const {
		return 1;
	}
protected:
private:
	AbsFunction<axisVar> *  _predict;
	vector<double> _data, _error;
	vector<axisVar> _positions;
	string _title;

};


#endif