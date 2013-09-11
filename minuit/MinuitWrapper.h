#include "Minuit2/FunctionMinimum.h"
#include "Minuit2/MnMigrad.h"
#include "Minuit2/MnHesse.h"
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

	}

	MinuitWrapper(FCNBase * fPtr) : _fPtr(fPtr){
	}	

	~MinuitWrapper(){

	}

	void AddPar(string name, double x1, double x2){
		upar.Add(name.c_str(),x1,x2);
	}

	FunctionMinimum Migrad(){
		MnMigrad migrad(*_fPtr,upar);
		cout << "2" << endl;
		FunctionMinimum min = migrad();
		cout << "3" << endl;
		return min;
	}

protected:
private:
	FCNBase * _fPtr;
	MnUserParameters upar;
};

#endif