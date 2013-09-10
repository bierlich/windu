
#include "EmptyParticle.h"

EmptyParticle::EmptyParticle(){
}

EmptyParticle::~EmptyParticle(){
}

istream& operator>> (istream& aStream, EmptyParticle& aEmptyParticle){
	return aStream;
}

ostream& operator<< (ostream& aStream, EmptyParticle& aEmptyParticle){
	return aStream;
}


