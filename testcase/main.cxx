#include "Windu.h"

int main() {
	Histogram<double> h("h",4,0,4);
	h.Fill(1);
	h.Fill(2);
	h.Fill(3);

	ofstream out("testfile.xml");

	out << h;

	out.close();

	ifstream in("testfile.xml");

	Histogram<double> g;

	in >> g;

	in.close();

	cout << g << endl;
 
}
