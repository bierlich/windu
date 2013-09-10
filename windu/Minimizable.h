#ifndef __Minimizable__
#define __Minimizable__

#include "Minuit2/FCNBase.h"

class Minimizable : public ROOT::Minuit2::FCNBase {
public:
	Minimizable() {
	}
	
	~Minimizable() {
	}

	virtual double operator()(const std::vector<double>& par) const = 0;

	virtual double Up() const = 0;

};

#endif