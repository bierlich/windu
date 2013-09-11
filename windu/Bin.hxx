template<class TX>
ostream& operator<< (ostream& aStream, const Bin<TX> &aBin){
	aStream << "\t\t\t<sum_of_weights=\"" << aBin._w << "\">\n ";
	aStream << "\t\t\t<sum_of_weights_squared=\"" << aBin._w2 << "\">\n ";
	aStream << "\t\t\t<ledge>\n\t\t\t\t" << aBin._v << "\n\t\t\t</ledge>\n";
	aStream << "\t\t\t<width>\n\t\t\t\t" << aBin._width << "\n\t\t\t</width>\n";
	return aStream;
}

template<class TX>
istream& operator>> (istream& aStream, Histogram<TX>& aHist){
	string line;
	while(line.find("<bin>") == string::npos){
		getline(aStream,line);
		if(!aStream.good()) return aStream;
	}	
	while(line.find("<sum_of_weights=") == string::npos){
		getline(aStream,line);
		if(!aStream.good()) return aStream;
	}
	aBin.w = to_double()
	return aStream;
}