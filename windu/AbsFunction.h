
#ifndef __AbsFunction__
#define __AbsFunction__

#include <iostream>
#include <string>
#include <stdlib.h>
#include <memory>
#include <cmath>
#include "Chi2Function.h"

using namespace std;

template<typename T>
class Histogram;

template<typename axisVar>
class AbsFunction {
public:
	 AbsFunction(){

	 }
	~AbsFunction(){

	}

	virtual double Eval(axisVar val) = 0;

	Chi2Function<axisVar>* GetChi2(Histogram<axisVar>& datahist){
		vector<double> data;
		vector<double> error;
		vector<axisVar> positions;
		for(auto bin : datahist){
			data.push_back(bin.GetSOW());
			error.push_back(sqrt(bin.GetSOW2()));
			positions.push_back(bin.GetCenter());
		}

		Chi2Function<axisVar>* ret = new Chi2Function<axisVar>("Chi2",this,data,error,positions);
		return ret;
	}

	shared_ptr<Histogram<axisVar>> GetHistogram(int nbins, axisVar min, axisVar max){
		return GetHistogram("_hist",nbins,min,max);
	}

	shared_ptr<Histogram<axisVar>> GetHistogram(string title, int nbins, axisVar min, axisVar max){
		axisVar stepsize = (max-min)/nbins;
		vector<axisVar> edges;	
			for(int i=0;i<nbins;i++){
				edges.push_back(min+i*stepsize);
			}
			edges.push_back(max+stepsize);
			return GetHistogram(title,edges);
	}

	shared_ptr<Histogram<axisVar>> GetHistogram(vector<axisVar>& edges){
		return GetHistogram("_hist",edges);
	}

	shared_ptr<Histogram<axisVar>> GetHistogram(string title, vector<axisVar>& edges){
		Histogram<axisVar> hist(title,edges);
		for(auto &bin : hist){
			bin.SetSOW(Eval(bin.GetCenter()),false);
			bin.SetSOW2(0.);
		}
		shared_ptr<Histogram<axisVar>> ret = make_shared<Histogram<axisVar>>(forward<Histogram<axisVar>>(hist));
		return ret;
	}

	vector<double> GetValues(vector<axisVar> edges){
		vector<double > ret;
		for(auto e : edges){
			ret.push_back(Eval((e+(e+1))/2));
		}
		return ret;
	}	

	virtual vector<double> GetParameters() = 0;
	virtual void SetParameters(vector<double> par) = 0;

protected:
private:


};
#endif

