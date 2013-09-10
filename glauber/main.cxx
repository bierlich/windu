#include "templ.h"
#include "EmptyParticle.h"
#include "GlauberEventPar.h"
#include "GlauberChi2.h"
#include "Rndm.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <gsl/gsl_sf_gamma.h>

using namespace std;


double log_p_neg_bin(int n, double k, double mu){
	double term1 = gsl_sf_lngamma(n+k)-gsl_sf_lngamma(n+1)-gsl_sf_lngamma(k);
	double term2 = n*log(mu/k)-(n+k)*log(mu/k+1);
	return term1+term2;
}

int sample_cdf(Rndm * r, Hist * cdf){
	double ran = r->flat();
	auto bPtr = cdf->GetHistCalc()->FindFirstAbove(ran);
	return bPtr->GetCenter();
}

int main(){
    auto t1 = chrono::high_resolution_clock::now();
    EventList<GlauberEvent> * el = new EventList<GlauberEvent>("/scratch/galette/bierlich/mc/Glauber/glauber_pbpb.tuple");
    // parameter initialisation
    double f = 0.806;
    double mu = 29.003;
    double k = 1.202;
    Rndm * r = new Rndm(31415);
	Histogram<int> * nparticles = new Histogram<int>("nparticles",100,0,25000);
	Hist impact("impact",100,5,15);
	Hist * cdf = new Hist("cdf",200,0,200);
	double cumsum = 0;
	for(auto &bin : *cdf){
		cumsum+=exp(log_p_neg_bin(bin.GetCenter(),k,mu));
		bin.SetSOW(cumsum);
	}

	for(auto &ev : *el){
		int nanc = f*ev.GetPar()->npart+(1-f)*ev.GetPar()->ncoll;
		int nfs = 0;
		for(int i=0;i<nanc;++i){
		nfs+=sample_cdf(r,cdf);
			}
		nparticles->Fill(nfs);
	}
	delete el;

    auto t2 = chrono::high_resolution_clock::now();
	cout  << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " milliseconds\n";	
    
    return 1;
}
