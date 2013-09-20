
#include "Windu.h"
#include "Units.h"
int main(){
	vector<Length> vec = {0* meter, 1*meter, 2*meter, 5*meter, 6*meter};
	Histogram<Length> h("h",vec);
	h.Fill(1*meter);
	h.Fill(2*meter);
	h.Fill(2*meter);
	h.Fill(3*meter);
	h.Fill(3*meter);
	cout << h/meter << endl;
	cout << "-----------" << endl;
	vector<double> v = h.GetHistCalc()->Serialize(meter);
	Histogram<Length> g;
	g = Unserialize(v,meter);
	cout << g/meter << endl;
	return 1;

}
