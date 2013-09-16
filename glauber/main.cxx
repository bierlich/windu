
#include "Windu.h"
#include "Units.h"



int main(){

	Histogram<Length> h("hist",4,0*metre,4*metre);
	h.Fill(1*metre);
	h.Fill(2*metre);
	h.Fill(3*metre);


}