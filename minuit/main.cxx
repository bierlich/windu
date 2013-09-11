#include <iostream>
#include "GausFunc.h"
#include "../panf/templ.h"
#include "../panf/objs.h"

using namespace std;
int main(){

	TestFunction tf ("tf");
	MinuitWrapper mw(&tf);
	mw.AddPar("x",1.,0.1);
	mw.AddPar("y",1.,0.1);
	mw.AddPar("z",1.,0.1);
	mw.AddPar("w",1.,0.1);

	cout << mw.Migrad() << endl;
	return 1;

}