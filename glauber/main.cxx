
#include "Windu.h"




int main(){

	Histogram<double> h("hist",4,0,4);
	h.Fill(1);
	h.Fill(2);
	h.Fill(3);

	ofstream out("testfile");
	out << h;
	out.close();

	Histogram<double> g("histss",4,0,4);
	ifstream in("testfile");
	in >> g;
	cout << g;

}