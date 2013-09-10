// Rndm generates random numbers uniformly distributed 
// between 0 and 1, excluding the endpoints, using the 
// Marsaglia-Zaman-Tsang algorithm.
// Sequence input number can be in range 1 - 900000000 

#ifndef __Rndm__
#define __Rndm__

class Rndm {

public:
	Rndm(int sequence){
			// Unpack sequence number.
    int ij = (sequence/30082) % 31329;
    int kl = sequence % 30082;
    int i  = (ij/177) % 177 + 2;
    int j  = ij % 177 + 2;
    int k  = (kl/169) % 178 + 1;
    int l  =  kl % 169;
    // Initialize random number array.
    for (int ii = 0; ii < 97; ++ii) {
      double s = 0.;
      double t = 0.5;
      for (int jj = 0; jj < 48; ++jj) {
        int m = (( (i*j)%179 )*k) % 179;
        i = j;
        j = k;
        k = m;
        l = (53*l+1) % 169;
        if ( (l*m) % 64 >= 32) s += t;
        t *= 0.5;
      }
      u[ii] = s;
    }
    // Initialize other variables.
    double twom24 = 1.;
    for (int i24 = 0; i24 < 24; ++i24) twom24 *= 0.5;
    c   = 362436. * twom24;
    cd  = 7654321. * twom24;
    cm  = 16777213. * twom24;
    i97 = 96;
    j97 = 32;
};
	double flat(){
		double uni;
    do {
      uni = u[i97] - u[j97];
      if (uni < 0.) uni += 1.;
      u[i97] = uni;
      if (--i97 < 0) i97 = 96;
      if (--j97 < 0) j97 = 96;
      c -= cd;
      if (c < 0.) c += cm;
      uni -= c;
      if(uni < 0.) uni += 1.;
    } while (uni <= 0. || uni >= 1.);
    return uni;
};

private:
  int    i97, j97;
  double c, cd, cm, u[97];

};
#endif
