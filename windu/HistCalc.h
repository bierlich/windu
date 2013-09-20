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
	typename vector<Bin<axisVar> >::iterator FindFirstAbove(double) const ;
	double Integral();
	pair<double,double> Integral(string opt);
	pair<axisVar,axisVar> Mean(){
		for(auto &bin : *hPtr){
			
		}
	}
	vector<typename vector<Bin<axisVar> >::iterator> Quantiles(vector<double> qin);
	
	template<typename U>
        vector<double> Serialize(U unit) const {
	  vector<double> ret;
	  for(auto &bin : *hPtr){
	    ret.push_back(bin.GetLedge()/unit);
	    ret.push_back(bin.GetSOW());
	    ret.push_back(bin.GetSOW2());
	  }
	  double ww = ((--(hPtr->end()))->GetWidth())/unit;
	  double last = ret.back() + ww;
	  ret.push_back(last);
	 return ret;
 	}


protected:

private:
	hist * hPtr;

};
	#include "HistCalc.hxx"


 template<typename U>
 	auto Unserialize(vector<double> & vec, U unit, string title = "") -> Histogram<decltype(unit)>{
 		vector<U> ledges;
		int N=vec.size();
 		for(int i=0;i<=N;i+=3){
 			ledges.push_back(vec[i]*unit);
 		}
 		Histogram<U> ret(title,ledges);
 		ret.SetVariableWidth(false);
 		if(ledges.size()>2){
	 		U firstdist = ledges[1] - ledges[0];
	 		U start = ledges[0];
	 		for(auto l : ledges){
	 			if(l-start!=firstdist&&l!=start){
	 				ret.SetVariableWidth(true);
	 				break;
	 			}
	 			start = l;
	 		}
 		}
 		auto tItr = vec.begin();
 		for(auto & bin : ret){
 			bin.SetSOW(*(++tItr));
 			bin.SetSOW2(*(++tItr));
 			++tItr;
 		}
 	return ret;
 	}

#endif
