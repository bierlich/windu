template<typename TX>
ostream& operator<< (ostream& aStream, const Bin<TX>& aBin){
	aStream << "\t\t<bin>\n";
	aStream << "\t\t\t<sum_of_weights=\"" << aBin.GetSOW() << "\">\n ";
	aStream << "\t\t\t<sum_of_weights_squared=\"" << aBin.GetSOW2() << "\">\n ";
	aStream << "\t\t\t<ledge=\"" << aBin.GetLedge() << "\">\n";
	aStream << "\t\t\t<width=\"" << aBin.GetWidth() << "\">\n";
	aStream << "\n\t\t</bin>";
	return aStream;
}

template<class TX>
istream& operator>> (istream& aStream, Bin<TX>& aBin){
	string line;
	string buf;
	while(line.find("<bin>") == string::npos){
		getline(aStream,line);
		if(!aStream.good()) return aStream;
	}	

	while(line.find("<sum_of_weights=") == string::npos){
		getline(aStream,line);
		if(!aStream.good()) return aStream;
	}
	buf = line.substr(line.find("=")+2,line.find(">")-line.find("=")-3);
	aBin._w = buf.length() == 0 ? 0. : stod(buf);

	while(line.find("<sum_of_weights_squared=") == string::npos){
		getline(aStream,line);
		if(!aStream.good()) return aStream;
	}
	buf = line.substr(line.find("=")+2,line.find(">")-line.find("=")-3);
	aBin._w2 = buf.length() == 0 ? 0. : stod(buf);

	while(line.find("<ledge=") == string::npos){
		getline(aStream,line);
		if(!aStream.good()) return aStream;
	}
	buf = line.substr(line.find("=")+2,line.find(">")-line.find("=")-3);
	aBin._v = buf.length() == 0 ? 0. : stod(buf);
	
	while(line.find("<width=") == string::npos){
		getline(aStream,line);
		if(!aStream.good()) return aStream;
	}
	buf = line.substr(line.find("=")+2,line.find(">")-line.find("=")-3);
	aBin._width = buf.length() == 0 ? 0. : stod(buf);

	while(line.find("</bin>") == string::npos){
		getline(aStream,line);
		if(!aStream.good()){
			cout << "Problem reading in histogram! Bin is not closed!" << "\n";
			return aStream;
		}
	}
		
	return aStream;
}