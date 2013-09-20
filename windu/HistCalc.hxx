#include "Histogram.h"

template <typename axisVar>
Histogram<axisVar> HistCalc<axisVar>::CDFHist(string opt = ""){
	// Options:
	// n = Sum to 1 (normalize)
	Histogram<axisVar> ret = hPtr->EmptyClone(hPtr->GetTitle() + "_CDF");
	double sow = 0;
	double sow2 = 0;
	auto iter = hPtr->begin();
	for(auto bin = ret.begin();bin!=ret.end();++bin){
		sow+=iter->GetSOW();
		sow2+=iter->GetSOW2();
		bin->SetSOW(sow);
		bin->SetSOW2(sow2);
		++iter;
	}
	if(opt.find("n")!=string::npos){
		double maxval = (--ret.end())->GetSOW();
		ret/=maxval;
	}
	return ret;
}
template <typename axisVar>
typename vector<Bin<axisVar> >::iterator HistCalc<axisVar>::FindFirstAbove(double sow) const{
	typename vector<Bin<axisVar> >::iterator iter = find_if(hPtr->begin(), hPtr->end(), 
		[&](Bin<axisVar> b) {return (sow <= b.GetSOW());});

	return iter;
}

template <typename axisVar>
double HistCalc<axisVar>::Integral(){
	double ret = 0;
	for(auto bin = hPtr->begin();bin!=hPtr->end();++bin){
	ret+=bin->GetSOW();
	}
	return ret;
}

template <typename axisVar>
pair<double,double> HistCalc<axisVar>::Integral(string opt){
	// Options:
	// e = Calculate error
	// u = include underflow bin
	// o = include overflow bin
	if(opt=="") return make_pair(Integral(),0.);
	double ret1 = 0;
	double ret2 = 0;
	if(opt.find("o")!=string::npos){
		ret1+=hPtr->GetOverflow()->GetSOW();
		if(opt.find("e")!=string::npos) ret2+=hPtr->GetOverflow()->GetSOW2();
	}
	if(opt.find("u")!=string::npos){
		ret1+=hPtr->GetUnderflow()->GetSOW();
		if(opt.find("e")!=string::npos) ret2+=hPtr->GetUnderflow()->GetSOW2();
	}
	for(auto bin = hPtr->begin();bin!=hPtr->end();++bin){
	ret1+=bin->GetSOW();
	if(opt.find("e")!=string::npos) ret2+=bin->GetSOW2();
	}
	if(opt.find("e")!=string::npos){
		return make_pair(ret1,ret2);
	}
	return make_pair(ret1,0.);
}

template<typename axisVar>
vector<typename vector<Bin<axisVar> >::iterator> HistCalc<axisVar>::Quantiles(vector<double> qin={0.5}){
	vector<typename vector<Bin<axisVar> >::iterator> ret;
	ret.clear();
	Histogram<axisVar> cdf = CDFHist("n");
	auto nq_iter = qin.begin();
	auto h_iter = hPtr->begin();
	for(auto bin = cdf.begin();bin!=cdf.end();++bin){
		if(nq_iter==qin.end()) break;
		if(bin->GetSOW()>=*nq_iter){
			ret.push_back(h_iter);
			++nq_iter;
		}
		++h_iter;
	}
	return ret;
}

