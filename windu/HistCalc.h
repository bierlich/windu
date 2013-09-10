#ifndef __HistCalc__
#define __HistCalc__

#include "Bin.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

template<typename T>
class Histogram;

template<typename axisVar>
class HistCalc{

public:
typedef Histogram<axisVar> hist;

	 HistCalc(){
	 }

	~HistCalc(){
	}

	HistCalc(hist * hp){
		hPtr = hp;
	}

	hist CDFHist(string opt);
	typename vector<Bin<axisVar> >::iterator FindFirstAbove(double);
	double Integral();
	pair<double,double> Integral(string opt);
	vector<typename vector<Bin<axisVar> >::iterator> Quantiles(vector<double> qin);

protected:

private:
	hist * hPtr;

};
	#include "HistCalc.hxx"

#endif

