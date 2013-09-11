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

	Bin(double w, double w2, axisVar v, axisVar width){
		_w = w;
		_w2 = w2;
		_v = v;
		_width = width;
	}

	~Bin(){

	}

	Bin<axisVar> EmptyClone(){
		Bin b(0,0,_v,_width);
		return b;
	}
	void Fill(double w){
		_w+=w;
		_w2+=w*w;
	}

	axisVar GetCenter(){
		return _v+_width/2;
	}

	axisVar GetLedge(){
		return _v;
	}

	axisVar GetRedge(){
		return _v+_width;
	}

	double GetSOW(){
		return _w;
	}

	double GetSOW2(){
		return _w2;
	}

	axisVar GetWidth(){
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

	Bin operator + (Bin other){
		Bin tmp(_w + other.GetSOW(), 
				_w2 + other.GetSOW2(), _v, _width);
		return tmp;
	}

	Bin operator - (Bin other){
		Bin tmp(_w - other.GetSOW() > 0 ? _w - other.GetSOW() : 0,
				_w2 - other.GetSOW2() > 0 ? _w2 - other.GetSOW2() : 0,
				_v, _width);
		return tmp;
	}

	Bin operator / (Bin other){
		if(other.GetSOW()==0){
			cout << "WARNING: Divide by zero!" << endl;
		}
		double osow = other.GetSOW();
		double osow2 = other.GetSOW2();

		double tmpw = osow==0 ? 0 : _w/osow;

		Bin tmp(tmpw, osow==0 ? 0 : (_w2*osow*osow+osow2*_w*_w)/(osow*osow*osow*osow), _v, _width);

		return tmp;
	}

	Bin operator * (Bin other){
		Bin tmp(_w*other.GetSOW(),_w2+other.GetSOW2(), _v,_width);
		return tmp;
	}

	Bin operator + (double other){
		Bin tmp(_w + other, _w2 + other*other, _v, _width);
		return tmp;
	}

	Bin operator - (double other){
		Bin tmp(_w - other > 0 ? _w - other : 0,
				_w2 - other*other > 0 ? _w2 - other*other : 0,
				_v, _width);
		return tmp;
	}

	Bin operator / (double other){
		if(other==0){
			cout << "WARNING: Divide by zero!" << endl;
		}
		double tmpw = other==0 ? 0 : _w/other;
		double tmpw2 = other==0 ? 0 : _w2/other/other;
		Bin tmp(tmpw, tmpw2, _v, _width);

		return tmp;
	}

	Bin operator * (double other){
		Bin tmp(_w*other, _w2*other*other, _v,_width);
		return tmp;
	}

protected:

private:
	double _w, _w2;
	axisVar _v, _width;

template<class TX>
friend ostream& operator<< (ostream& aStream, const Bin<TX>& aBin);
template<class TX>
friend istream& operator>> (istream& aStream, const Bin<TX>& aBin);

struct support_operation {
	template<class T>
	static auto test_write(T * p) -> decltype(std::cout << *p, std::true_type());

	template<class>
	static auto test_write(...) -> std::false_type;

	template<class T>
	static auto test_read(T * p) -> decltype(std::cin >> *p, std::true_type());

	template<class>
	static auto test_read(...) -> std::false_type;
};

template<class T>
struct test_write : decltype(support_operation::test_write<T>(0))
{};

template<class T>
struct test_read : decltype(support_operation::test_read<T>(0))
{};

};
	#include "Bin.hxx"
#endif