
#include "HIParticle.h"

HIParticle::HIParticle(){
}

HIParticle::~HIParticle(){
}

istream& operator>> (istream& aStream, HIParticle& aHIParticle){
	double tmpeta, tmpphi, tmppT;
	int tmppid, tmpch, tmpstr;
	aStream >> tmppid >> tmppT >> tmpeta >> tmpphi >> tmpch >> tmpstr;
	aHIParticle.eta = tmpeta;
	aHIParticle.phi = tmpphi;
	aHIParticle.pT = tmppT;
	aHIParticle.pid = tmppid;
	aHIParticle.isch = (tmpch == 1 ? true : false);
	aHIParticle.hasstrangeparents = (tmpstr == 1 ? true : false);

	//cout << tmppid << " " << tmppT << " " << tmpeta << " " << tmpphi << " " << tmpch << endl;
	return aStream;
}

ostream& operator<< (ostream& aStream, HIParticle& aHIParticle){
	aStream << aHIParticle.pid << " " << aHIParticle.pT << " " << aHIParticle.eta << " " << aHIParticle.phi << " " << (aHIParticle.isch ? "1" : "0") << " " << (aHIParticle.hasstrangeparents ? "1" : "0");
	return aStream;
}


