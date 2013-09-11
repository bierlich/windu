#ifndef __AbsFunction__
#define __AbsFunction__

#include "Minuit2/FCNBase.h"

class AbsFunction : public ROOT::Minuit2::FCNBase {
public:
	AbsFunction() {
	}
	
	~AbsFunction() {
	}

	virtual double operator()(const std::vector<double>& par) const = 0;

	virtual double Up() const = 0;

};

#endif