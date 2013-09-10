#include "templ.h"
#include "EmptyParticle.h"
#include "GlauberEventPar.h"
#include "GlauberChi2.h"
#include "MinuitWrapper.h"
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
    EventList<GlauberEvent> * el = new EventList<GlauberEvent>("../Glauber/glauber_pbpb.tuple");
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
	auto quan = nparticles->GetHistCalc()->Quantiles({0.,1.});
	*nparticles/=nparticles->GetHistCalc()->Integral();
	nparticles->SetInfoString("log");

	nparticles->DrawSimple("test.xml");

	GlauberChi2 chi2("chi2",nparticles,"../Glauber/glauber_pbpb.tuple",log_p_neg_bin,sample_cdf,r);
	MinuitWrapper mw(&chi2);
	mw.AddPar("f",.5,0.2,0.1,1.);
	mw.AddPar("k",1.,0.2,0.,5);
	mw.AddPar("mu",25.,0.5,10.,50);

	auto res = mw.Minos();
	for(auto m : res ){
		cout << m.first << " " << m.second << endl;
	}
	/*el->Clear();
	for(auto &ev : *el){
		int nanc = f*ev.GetPar()->npart+(1-f)*ev.GetPar()->ncoll;
		int nfs = 0;
		for(int i=0;i<nanc;++i){
			nfs+=sample_cdf(r,cdf);
		}
		if(nfs>=quan[0]->GetLedge()&&nfs<quan[1]->GetRedge()){
			impact.Fill(ev.GetPar()->b);
		}
	}
	nparticles/=nparticles.GetHistCalc()->Integral();
	nparticles.SetInfoString("log");
	nparticles.DrawSimple("hist.xml");
*/
    delete cdf;
    delete r;
    auto t2 = chrono::high_resolution_clock::now();
	cout  << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " milliseconds\n";	
    
    return 1;
}
