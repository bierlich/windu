// Rndm generates random numbers uniformly distributed 
// between 0 and 1, excluding the endpoints, using the 
// Marsaglia-Zaman-Tsang algorithm.
// Sequence input number can be in range 1 - 900000000 
#ifndef __RNDM__
#define __RNDM__

class Rndm {

public:
	Rndm(int sequence);
	double flat();

private:
  int    i97, j97;
  double c, cd, cm, u[97];

};

#endif