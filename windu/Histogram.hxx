#include "HistCalc.h"

template <typename axisVar>
Histogram<axisVar>::Histogram(){
	hPtr.reset();
}

template <typename axisVar>
Histogram<axisVar>::Histogram(string title, int nbins, axisVar min, axisVar max){
	if(nbins<1) cerr << "Cannot initialize histogram without any bins!" << "\n";
	_title = title;
	_variableWidth = false;
	_bins.clear();
	hPtr.reset();
	axisVar stepsize = (max-min)/nbins;
	for(int i=0;i<nbins;++i){
		Bin <axisVar> tmp(0,0,min+(i*stepsize),stepsize);
		_bins.push_back(tmp);
	}
}

template <typename axisVar>
Histogram<axisVar>::Histogram(string title, vector<axisVar> edges){
	_title = title;
	_variableWidth = true;
	hPtr.reset();
	for(auto v = edges.begin();v!=edges.end()-1;++v){
		Bin<axisVar> tmp(0,0,*v,*(v+1)-*v);
		_bins.push_back(tmp);
	}
}

template <typename axisVar>
Histogram<axisVar>::~Histogram(){
	hPtr.reset();
}

template <typename axisVar>
typename vector<Bin<axisVar> >::iterator Histogram<axisVar>::begin(){
	return _bins.begin();
}

template <typename axisVar>
void Histogram<axisVar>::DrawSimple(string filename, string opt){
	ofstream of;
	if(opt.find("app")!=string::npos){
		of.open(filename,ios::app);
	}
	else{
		of.open(filename);
	}
	of << *this;
	of.close();
}

template <typename axisVar>
Histogram<axisVar> Histogram<axisVar>::EmptyClone(string title){
	vector<axisVar> edges;
	for(Bin<axisVar> b: _bins){
		edges.push_back(b.GetLedge());
	}
	auto lastbin = _bins.end()-1;
	edges.push_back(lastbin->GetRedge());
	Histogram<axisVar> ret(title,edges);
	ret._variableWidth = _variableWidth;
	return ret;
}

template <typename axisVar>
typename vector<Bin<axisVar> >::iterator Histogram<axisVar>::end(){
	return _bins.end();
}

template <typename axisVar>
void Histogram<axisVar>::Fill(axisVar value, double weight){
	typename vector<Bin<axisVar> >::iterator iter = GetBinItr(value);
	if(iter==_bins.end()){
		if(value<_bins.begin()->GetLedge()){
			_underflow.Fill(weight);
		}
		else if(value>=(--iter)->GetRedge()){
			_overflow.Fill(weight);
		}
	}	
	else{
		iter->Fill(weight);
	}
}

template <typename axisVar>
typename vector<Bin<axisVar> >::iterator Histogram<axisVar>::GetBinItr(axisVar value){
	// NEED TO IMPLEMENT A BETTER SEARCH ALGORITHM!
	typename vector<Bin<axisVar> >::iterator iter = find_if(_bins.begin(), _bins.end(), 
		[&](Bin<axisVar> b) {return (value >= b.GetLedge()&&value<b.GetRedge());});

	return iter;
}

template <typename axisVar>
shared_ptr<Bin<axisVar>> Histogram<axisVar>::GetOverflow(){
	shared_ptr<Bin<axisVar>> sp = make_shared<Bin<axisVar>>(_overflow);
	return sp;
}

/*template <typename axisVar>
shared_ptr<Histogram<axisVar>> Histogram<axisVar>::GetSharedPtr(){
	shared_ptr<Histogram<axisVar>> sp = make_shared<Histogram<axisVar>>(*this);
	return sp;
}
*/
template <typename axisVar>
string Histogram<axisVar>::GetTitle(){
	return _title;
}

template <typename axisVar>
shared_ptr<Bin<axisVar>> Histogram<axisVar>::GetUnderflow(){
	shared_ptr<Bin<axisVar>> sp = make_shared<Bin<axisVar>>(_underflow);
	return sp;
}

template <typename axisVar>
shared_ptr<HistCalc<axisVar>> Histogram<axisVar>::GetHistCalc(){
	if(hPtr){
		shared_ptr<HistCalc<axisVar>> ret = hPtr;
		return ret;
	}
	hPtr = shared_ptr<HistCalc<axisVar> > (new HistCalc<axisVar>(this));
	return GetHistCalc();
}

template <typename axisVar>
string Histogram<axisVar>::GetInfoString(){
	return _infostring;
}

template <typename axisVar>
string Histogram<axisVar>::GetTypeName(){
	char *realname;
	int status;
	const type_info & ti = typeid(axisVar);
	realname = abi::__cxa_demangle(ti.name(),0,0,&status);
	string s = realname;
	free(realname);
	return s;
}

template <typename axisVar>
void Histogram<axisVar>::SetInfoString(string info){
	_infostring = info;
}

template <typename axisVar>
void Histogram<axisVar>::SetTitle(string newTitle){
	_title = newTitle;
}

template <typename axisVar>
void Histogram<axisVar>::SetVariableWidth(bool isVariable){
	_variableWidth = isVariable;
}

template <typename axisVar>
bool Histogram<axisVar>::TestCompatibility(Histogram other){
	return true;
}

template <typename axisVar>
Histogram<axisVar> Histogram<axisVar>::operator + (Histogram<axisVar>& other){
		auto tmp = EmptyClone(_title);
		if(!TestCompatibility(other)){
			cerr << "Add: Not Compatible" << "\n";
			return tmp;
		}
		auto itr1 = begin();
		auto itr2 = other.begin();
		for(Bin<axisVar> &b : tmp._bins){
			b = *itr1+*itr2;
			++itr1;
			++itr2;
		}
	return tmp;
}

template <typename axisVar>
Histogram<axisVar> Histogram<axisVar>::operator - (Histogram<axisVar>& other){
		auto tmp = EmptyClone(_title);
		if(!TestCompatibility(other)){
			cerr << "Subtract: Not Compatible" << "\n";
			return tmp;
		}
		auto itr1 = begin();
		auto itr2 = other.begin();
		for(Bin<axisVar> &b : tmp._bins){
			b = *itr1-*itr2;
			++itr1;
			++itr2;
		}
	return tmp;
}

template <typename axisVar>
Histogram<axisVar> Histogram<axisVar>::operator * (Histogram<axisVar>& other){
		auto tmp = EmptyClone(_title);
		if(!TestCompatibility(other)){
			cerr << "Multiply: Not Compatible" << "\n";
			return tmp;
		}
		auto itr1 = begin();
		auto itr2 = other.begin();
		for(Bin<axisVar> &b : tmp._bins){
			b = (*itr1)*(*itr2);
			++itr1;
			++itr2;
		}
	return tmp;
}

template <typename axisVar>
Histogram<axisVar> Histogram<axisVar>::operator / (Histogram<axisVar>& other){
		auto tmp = EmptyClone(_title);
		if(!TestCompatibility(other)){
			cerr << "Divide: Not Compatible" << "\n";
			return tmp;
		}
		auto itr1 = begin();
		auto itr2 = other.begin();
		for(Bin<axisVar> &b : tmp._bins){
			b = (*itr1)/(*itr2);
			++itr1;
			++itr2;
		}
	return tmp;
}

template <typename axisVar>
void Histogram<axisVar>::operator += (Histogram<axisVar>& other){
		if(!TestCompatibility(other)){
			cerr << "Add: Not Compatible" << "\n";
		}
		auto itr = other.begin();
		for(Bin<axisVar> &b : _bins){
			b = b+*itr;
			++itr;
		}
}

template <typename axisVar>
void Histogram<axisVar>::operator -= (Histogram<axisVar>& other){
		if(!TestCompatibility(other)){
			cerr << "Subtract: Not Compatible" << "\n";
		}
		auto itr = other.begin();
		for(Bin<axisVar> &b : _bins){
			b = b-*itr;
			++itr;
		}
}

template <typename axisVar>
void Histogram<axisVar>::operator *= (Histogram<axisVar>& other){
		if(!TestCompatibility(other)){
			cerr << "Multiply: Not Compatible" << "\n";
		}
		auto itr = other.begin();
		for(Bin<axisVar> &b : _bins){
			b = b*(*itr);
			++itr;
		}
}

template <typename axisVar>
void Histogram<axisVar>::operator /= (Histogram<axisVar>& other){
		if(!TestCompatibility(other)){
			cerr << "Divide: Not Compatible" << "\n";
		}
		auto itr = other.begin();
		for(Bin<axisVar> &b : _bins){
			b = b/(*itr);
			++itr;
		}
}

template <typename axisVar>
Histogram<axisVar> Histogram<axisVar>::operator + (double other){
		auto tmp = EmptyClone(_title);
		auto itr = begin();
		for(Bin<axisVar> &b : tmp._bins){
			b = *itr+other;
			++itr;
		}
	return tmp;
}

template <typename axisVar>
Histogram<axisVar> Histogram<axisVar>::operator - (double other){
		auto tmp = EmptyClone(_title);
		auto itr = begin();
		for(Bin<axisVar> &b : tmp._bins){
			b = *itr-other;
			++itr;
		}
	return tmp;
}

template <typename axisVar>
Histogram<axisVar> Histogram<axisVar>::operator * (double other){
		auto tmp = EmptyClone(_title);
		auto itr = begin();
		for(Bin<axisVar> &b : tmp._bins){
			b = *itr*other;
			++itr;
		}
	return tmp;
}

template <typename axisVar>
Histogram<axisVar> Histogram<axisVar>::operator / (double other){
		auto tmp = EmptyClone(_title);
		auto itr = begin();
		for(Bin<axisVar> &b : tmp._bins){
			b = *itr/other;
			++itr;
		}
	return tmp;
}

template <typename axisVar>
void Histogram<axisVar>::operator += (double other){
		for(Bin<axisVar> &b : _bins){
			b = b+other;
		}
}

template <typename axisVar>
void Histogram<axisVar>::operator -= (double other){
		for(Bin<axisVar> &b : _bins){
			b = b-other;
		}
}

template <typename axisVar>
void Histogram<axisVar>::operator *= (double other){
		for(Bin<axisVar> &b : _bins){
			b = b*other;
		}
}

template <typename axisVar>
void Histogram<axisVar>::operator /= (double other){
		for(Bin<axisVar> &b : _bins){
			b = b/other;
		}
}

template<class TX>
ostream& operator<< (ostream& aStream, Histogram<TX>& aHist){
	aStream << "<histogram>\n\t<meta>\n\t\t<title=\"" << aHist._title << "\">" << "\n";
	aStream << "\t\t<type=\"" << aHist.GetTypeName() << "\">" << "\n";
	aStream << "\t\t<nbins=\"" << aHist._bins.size() << "\">" << "\n";
	aStream << "\t\t<variableWidth=\"" << (aHist._variableWidth ? "true" : "false") << "\">" << "\n";
	aStream << "\t\t<info=\"" << aHist.GetInfoString() << "\">" << "\n";
	aStream << "\t</meta>\n\t<bins>" << "\n";
	for(Bin<TX> &b : aHist._bins){
		aStream << b << "\n";
	}
	aStream << "\t</bins>\n</histogram>" << "\n";

	return aStream;
}

template<class TX>
istream& operator>> (istream& aStream, Histogram<TX>& aHist){
	string line;
	string buf;
	int nbins_control;
	
	while(line.find("<histogram>") == string::npos){
		getline(aStream,line);
		if(!aStream.good()) return aStream;
	}	
	while(line.find("<meta>") == string::npos){
		getline(aStream,line);
		if(!aStream.good()) return aStream;
	}	
	
	while(line.find("<title=") == string::npos){
		getline(aStream,line);
		if(!aStream.good()) return aStream;
	}
	buf = line.substr(line.find("=")+2,line.find(">")-line.find("=")-3);
	aHist._title = buf;
	
	while(line.find("<type=") == string::npos){
		getline(aStream,line);
		if(!aStream.good()) return aStream;
	}
	buf = line.substr(line.find("=")+2,line.find(">")-line.find("=")-3);
	if(aHist.GetTypeName()!=buf) cout << "Warning! typename of initialized histogram is \"" << aHist.GetTypeName() <<
		"\" while typename of the histogram read from stream is \"" << buf << "\". Make sure everything is initialized correct!" << "\n";
	
	while(line.find("<nbins=") == string::npos){
		getline(aStream,line);
		if(!aStream.good()) return aStream;
	}
	buf = line.substr(line.find("=")+2,line.find(">")-line.find("=")-3);
	nbins_control = stoi(buf);

	while(line.find("<variableWidth=") == string::npos){
		getline(aStream,line);
		if(!aStream.good()) return aStream;
	}
	buf =line.substr(line.find("=")+2,line.find(">")-line.find("=")-3);
	aHist._variableWidth = (buf=="true" ? true : false);

	while(line.find("<info=") == string::npos){
		getline(aStream,line);
		if(!aStream.good()) return aStream;
	}
	buf = line.substr(line.find("=")+2,line.find(">")-line.find("=")-3);
	aHist._infostring = buf;
	while(line.find("</meta>") == string::npos){
		getline(aStream,line);
		if(!aStream.good()) return aStream;
	}	
	while(line.find("<bins>") == string::npos){
		getline(aStream,line);
		if(!aStream.good()) return aStream;
	}

	Bin<TX> tmpbin;
	while(aStream >> tmpbin){
		aHist._bins.push_back(tmpbin);
	
	}
	
	while(line.find("</bins>") == string::npos){
		getline(aStream,line);
		if(!aStream.good()) return aStream;
	}

	if(nbins_control!=aHist._bins.size()){
		cout << "Warning! Size of the histogram I read is not equal to the size stated in header!" << "\n";
	}

	return aStream;
}