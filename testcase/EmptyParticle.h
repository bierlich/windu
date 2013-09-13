#ifndef __EmptyParticle__
#define __EmptyParticle__

#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class EmptyParticle {
 public:
  EmptyParticle();
  ~EmptyParticle();

 protected:
 private:

  friend istream& operator>> (istream& aStream, EmptyParticle& aEmptyParticle);
  friend ostream& operator<< (ostream& aStream, EmptyParticle& aEmptyParticle);

};
#endif

