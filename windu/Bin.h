#ifndef __Bin__
#define __Bin__

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <typeinfo>
#include <tuple>
#include <stdexcept>

using namespace std;


template <class axisVar>
class Bin{
public:
	Bin(){
		_w = 0;
		_w2 = 0;
	}

	Bin(double w, double w2, axisVar v, axisVar width): _w(w), _w2(w2), _v(v), _width(width) {
	}

	~Bin(){

	}

	Bin<axisVar> EmptyClone(){
		Bin<axisVar> b(0,0,_v,_width);
		return b;
	}
	void Fill(double w){
		_w+=w;
		_w2+=w*w;
	}

	axisVar GetCenter() const {
		return _v+_width/2;
	}

	axisVar GetLedge() const {
		return _v;
	}

	axisVar GetRedge() const {
		return _v+_width;
	}

	double GetSOW() const {
		return _w;
	}

	double GetSOW2() const {
		return _w2;
	}

	axisVar GetWidth() const {
		return _width;
	}

	void SetSOW(double w, bool _protectNegative = true){
		if(w<0&&_protectNegative) cout << "Bin: Warning: Negative Bin Value Set!" << endl;
		_w = w;
	}

	void SetSOW2(double w2, bool _protectNegative = true){
		if(w2<0&&_protectNegative) cout << "Bin: Warning: Negative Bin Value2 Set!" << endl;
		_w2 = w2;
	}

	Bin<axisVar> operator + (Bin other){
		Bin<axisVar> tmp(_w + other.GetSOW(), 
				_w2 + other.GetSOW2(), _v, _width);
		return tmp;
	}

	Bin<axisVar> operator - (Bin other){
		Bin<axisVar> tmp(_w - other.GetSOW() > 0 ? _w - other.GetSOW() : 0,
				_w2 - other.GetSOW2() > 0 ? _w2 - other.GetSOW2() : 0,
				_v, _width);
		return tmp;
	}

	Bin<axisVar> operator / (Bin other){
		if(other.GetSOW()==0){
			cout << "WARNING: Divide by zero!" << endl;
		}
		double osow = other.GetSOW();
		double osow2 = other.GetSOW2();

		double tmpw = osow==0 ? 0 : _w/osow;

		Bin tmp(tmpw, osow==0 ? 0 : (_w2*osow*osow+osow2*_w*_w)/(osow*osow*osow*osow), _v, _width);

		return tmp;
	}

	Bin<axisVar> operator * (Bin other){
		Bin<axisVar> tmp(_w*other.GetSOW(),_w2+other.GetSOW2(), _v,_width);
		return tmp;
	}

	Bin<axisVar> operator + (double other){
		Bin<axisVar> tmp(_w + other, _w2 + other*other, _v, _width);
		return tmp;
	}

	Bin<axisVar> operator - (double other){
		Bin<axisVar> tmp(_w - other > 0 ? _w - other : 0,
				_w2 - other*other > 0 ? _w2 - other*other : 0,
				_v, _width);
		return tmp;
	}

	Bin<axisVar> operator / (double other){
		if(other==0){
			cout << "WARNING: Divide by zero!" << endl;
		}
		double tmpw = other==0 ? 0 : _w/other;
		double tmpw2 = other==0 ? 0 : _w2/other/other;
		Bin<axisVar> tmp(tmpw, tmpw2, _v, _width);

		return tmp;
	}

	Bin<axisVar> operator * (double other){
		Bin<axisVar> tmp(_w*other, _w2*other*other, _v,_width);
		return tmp;
	}


protected:

private:
	double _w, _w2;
	axisVar _v, _width;


//template<class TX>
//friend ostream& operator<< (ostream& aStream, const Bin<TX>& aBin);
template<class TX>
friend istream& operator>> (istream& aStream, Bin<TX>& aBin);

};
	#include "Bin.hxx"
#endif