#ifndef __GlauberChi2__
#define __GlauberChi2__

#include <vector>
#include <string>
#include <functional>
#include "Rndm.h"
#include "EmptyParticle.h"
#include "GlauberEventPar.h"
#include "templ.h"
#include "Minuit2/FCNBase.h"
#include "Minimizable.h"

using namespace std;
typedef Event<EmptyParticle,GlauberEventPar> GlauberEvent;

class GlauberChi2 : public Minimizable {

public:
	GlauberChi2(string title, Histogram<int> * data, string glauber, function<double (int, double, double)> log_p_neg_bin, 
				function<int (Rndm *, Hist *)> sample_cdf, Rndm * r){
		_title = title;
		_data = data;
		_r = r;
		_glauber = glauber;
		_log_p_neg_bin = log_p_neg_bin;
		_sample_cdf = sample_cdf;
	}

	double operator()(const std::vector<double>& par) const{
		double f = par[0];
		double k = par[1];
		double mu = par[2];
		Hist * cdf = new Hist("cdf",200,0,200);
		Histogram<int> prediction = _data->EmptyClone("predict");
		double cumsum = 0;
		for(auto &bin : *cdf){
			cumsum+=exp(_log_p_neg_bin(bin.GetCenter(),k,mu));
			bin.SetSOW(cumsum);
		}
		*cdf/=(cdf->end() - cdf->begin())/((--cdf->end())->GetRedge() - cdf->begin()->GetLedge());
		cdf->DrawSimple("test.xml");
		double total_sow = 0;
		EventList<GlauberEvent> * _el = new EventList<GlauberEvent>(_glauber);

		for(auto &ev : *_el){
			int nanc = f*ev.GetPar()->npart+(1-f)*ev.GetPar()->ncoll;
			int nfs = 0;
			total_sow += 1;
			for(int i=0;i<nanc;++i){
				nfs+=_sample_cdf(_r,cdf);
			}
			prediction.Fill(nfs);
			if (total_sow>1000) break;
		}
		prediction/=prediction.GetHistCalc()->Integral();
		double chi2 = 0;
		double deg_of_freedom = total_sow - 4;

		auto numhist = prediction - *_data;
		auto dataItr = _data->begin();
		auto predItr = prediction.begin();
		for(auto num : numhist){
			double nn = num.GetSOW();
			double err = dataItr->GetSOW2();// + predItr->GetSOW2();
			chi2+=err == 0 ? 0 : nn*nn/err;
			++dataItr;
			++predItr;
		}

		delete cdf;
		/*_predict->SetParameters(par);

		vector<double> pred = _predict->GetValues(_positions);

		int deg_of_freedom = _data.size() - par.size() - 1;

		double chi2 = 0;

		auto predItr = pred.begin();
		auto errItr = _error.begin();
		for(auto dataItr : _data){
			double num = (*predItr - dataItr);
			chi2+=num*num/(*errItr)/(*errItr);
			++predItr;
			++errItr;
		}
		*/
		chi2/=deg_of_freedom;
		
		cout << "chi2 " << chi2 << endl; 
		return chi2;
	}

	double Up() const {
		return 1;
	}
protected:
private:
	string _title;
	Histogram<int> * _data;
	Rndm * _r; 
	string _glauber;
	function<double (int, double, double)> _log_p_neg_bin;
	function<int (Rndm *, Hist *)> _sample_cdf;	

};


#endif
