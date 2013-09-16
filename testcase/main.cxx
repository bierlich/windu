
#include "Windu.h"
#include "Units.h"
#include <sstream>
#include <string>



int main(){

	Histogram<Length> h("h",3,0*meter,3*meter);
	h.Fill(1*meter);
	h.Fill(2*meter);
	stringstream ss;

	auto l = h/meter;
	ss << l << endl;
	string s;
	ss >> s;
	cout << s << endl;
	return 1;

}