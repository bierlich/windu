#include "EventPar.h"

EventPar::EventPar(){
}

EventPar::~EventPar(){
}

int EventPar::GetNParticles(){
	return np;
}

istream& operator>> (istream& aStream, EventPar& aEvent){
        double tmpweight, tmpb, tmpxsec;
        int tmpnc, tmpnp;
        aStream >> tmpweight >> tmpnp >> tmpnc >> tmpb >> tmpxsec;
        aEvent.weight = tmpweight;
        aEvent.np = tmpnp;
        aEvent.b = tmpb;
        aEvent.nch = tmpnc;
        aEvent.xsec  = tmpxsec;

        return aStream;
}

ostream& operator<< (ostream& aStream, EventPar& aEvent){
        aStream << aEvent.weight << " " << aEvent.np << " " << aEvent.nch << " " << aEvent.b << " " << aEvent.xsec;
        return aStream;
}
