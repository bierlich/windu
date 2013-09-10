#include "Minuit2/FunctionMinimum.h"
#include "Minuit2/MnMigrad.h"
#include "Minuit2/MnSimplex.h"
#include "Minuit2/MnHesse.h"
#include "Minuit2/MnMinos.h"
#include "Minuit2/MnUserParameters.h"
#include "Minuit2/MnPrint.h"
#include "Minuit2/FCNBase.h"

#include <string>

#ifndef __MINUITWRAPPER__
#define __MINUITWRAPPER__

using namespace std;
using namespace ROOT::Minuit2;

//template<typename func>
class MinuitWrapper {

public:
	MinuitWrapper(){
		_npar = 0;

	}

	MinuitWrapper(FCNBase * fPtr) : _fPtr(fPtr){
		_npar = 0;
	}	


	~MinuitWrapper(){

	}

	void AddPar(string name, double startval, double esterr, double min, double max){
		upar.Add(name.c_str(),startval, esterr, min, max);
		++_npar;
	}

	void AddPar(string name, double startval, double esterr){
		upar.Add(name.c_str(),startval, esterr);
		++_npar;
	}

	FunctionMinimum Migrad(){
		MnMigrad migrad(*_fPtr,upar);
		FunctionMinimum min = migrad();
		return min;
	}

	vector<pair<double,double>>  Minos(){
		MnMigrad migrad(*_fPtr,upar);
		FunctionMinimum min = migrad();
		return Minos(min);
	}

	vector<pair<double,double>>  Minos(FunctionMinimum& min){
		MnMinos minos(*_fPtr,min);
		vector<pair<double,double>> ret;
		for(int i=0;i!=_npar;++i){
			ret.push_back(minos(i));
		}
		return ret;
	}

protected:
private:
	FCNBase * _fPtr;
	MnUserParameters upar;
	int _npar;
};

#endif