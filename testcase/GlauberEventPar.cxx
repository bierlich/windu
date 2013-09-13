#include "GlauberEventPar.h"

GlauberEventPar::GlauberEventPar(){
}

GlauberEventPar::~GlauberEventPar(){
}

int GlauberEventPar::GetNParticles(){
  return 0;
}

int GlauberEventPar::GetAncestors(double par, string model){
  return par*npart+(1-par)*ncoll;
}


istream& operator>> (istream& aStream, GlauberEventPar& aEvent){
  double tmpb;
  int tmpnpart, tmpncoll;
  aStream >> tmpb >> tmpnpart >> tmpncoll;
  aEvent.npart = tmpnpart;
  aEvent.ncoll = tmpncoll;
  aEvent.b = tmpb;

  return aStream;
}

ostream& operator<< (ostream& aStream, GlauberEventPar& aEvent){
  aStream << aEvent.b << " " << aEvent.npart << " " << aEvent.ncoll;
  return aStream;
}

