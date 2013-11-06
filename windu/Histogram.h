#ifndef __Histogram__
#define __Histogram__

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <typeinfo>
#include "Bin.h"
#include <stdexcept>
#include <memory>
#include <iterator>
#include <algorithm>
#include <cxxabi.h>
#include <fstream>
#include <utility>

using namespace std;
template<class T>
class HistCalc;


template <typename axisVar=double>
class Histogram{

public:
	Histogram();
	~Histogram();
	Histogram(Histogram& other, string title);
	//Histogram(Histogram& other) = default;
	Histogram(string title, int nbins, axisVar min, axisVar max);
	Histogram(string title, vector<axisVar> edges);
	void AddOverflow();
	typename vector<Bin<axisVar> >::iterator begin();
	void DrawSimple(string filename="hist.xml",string opt="");
	Histogram<axisVar> EmptyClone(string title);
	typename vector<Bin<axisVar> >::iterator end();
	void Fill(axisVar value, double weight=1.);
	typename vector<Bin<axisVar> >::iterator GetBinItr(axisVar value);
	shared_ptr<Bin<axisVar>> GetOverflow();
	string GetTitle();
	shared_ptr<Bin<axisVar>> GetUnderflow();
	shared_ptr<HistCalc<axisVar>> GetHistCalc();
	string GetInfoString() const;
	string GetTypeName() const;
	void SetInfoString(string info);
	void SetTitle(string newTitle);
	void SetVariableWidth(bool isVariable);
	Histogram<axisVar> operator + (Histogram<axisVar>& other);
	Histogram<axisVar> operator - (Histogram<axisVar>& other);
	Histogram<axisVar> operator * (Histogram<axisVar>& other);
	Histogram<axisVar> operator / (Histogram<axisVar>& other);
	void operator += (Histogram<axisVar>& other);
	void operator -= (Histogram<axisVar>& other);
	void operator *= (Histogram<axisVar>& other);
	void operator /= (Histogram<axisVar>& other);
	Histogram<axisVar> operator + (double other);
	Histogram<axisVar> operator - (double other);
	Histogram<axisVar> operator * (double other);
	Histogram<axisVar> operator / (double other);
	void operator += (double other);
	void operator -= (double other);
	void operator *= (double other);
	void operator /= (double other);

	template<typename unit>
	auto operator * (unit u) -> Histogram<decltype(u*declval<axisVar>())>{
		vector<decltype(u*declval<axisVar>())> ledges;
		for(auto bin : _bins){
			ledges.push_back(bin.GetLedge()*u);
		}
		auto bPtr = --_bins.end();
		ledges.push_back(bPtr->GetLedge()*u+bPtr->GetWidth()*u);

		Histogram<decltype(u*declval<axisVar>())> ret(_title,ledges);
		auto tItr = begin();
		for(auto& bin : ret){
			bin.SetSOW(tItr->GetSOW());
			bin.SetSOW2(tItr->GetSOW2());
			++tItr;
		}
		ret.SetVariableWidth(_variableWidth);
		ret.SetInfoString(_infostring);
		return ret;
	}

	template<typename unit>
	auto operator / (unit u) -> Histogram<decltype(u/declval<axisVar>())>{
		vector<decltype(u/declval<axisVar>())> ledges;
		for(auto bin : _bins){
			ledges.push_back(bin.GetLedge()/u);
		}
		auto bPtr = --_bins.end();
		ledges.push_back(bPtr->GetLedge()/u+bPtr->GetWidth()/u);

		Histogram<decltype(u/declval<axisVar>())> ret(_title,ledges);
		auto tItr = begin();
		for(auto& bin : ret){
			bin.SetSOW(tItr->GetSOW());
			bin.SetSOW2(tItr->GetSOW2());
			++tItr;
		}
		ret.SetVariableWidth(_variableWidth);
		ret.SetInfoString(_infostring);
		return ret;
	}

protected:
private:
	
	bool TestCompatibility(Histogram other);
	string _title;
	string _infostring;
	vector<Bin<axisVar> > _bins;
	Bin<axisVar> _overflow, _underflow;
	bool _variableWidth;
	shared_ptr<HistCalc<axisVar> > hPtr;

template<class TY>
friend istream& operator>> (istream& aStream, Histogram<TY>& aHist);
template<class TX>
friend ostream& operator<< (ostream& aStream, const Histogram<TX>& aHist);

};
	#include "Histogram.hxx"

typedef Histogram<double> Hist;

#endif
