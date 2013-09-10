template<typename TX, typename TY>
istream& operator>> (istream& aStream, Event<TX,TY>& aEvent){
	shared_ptr<TY> ptr = make_shared<TY>(TY());
	string line;
	while(line.find("<event>") == string::npos){
           getline(aStream,line);
           if(!aStream.good()){ 
              return aStream;
            }
        }
	aStream >> *ptr;
	aEvent._eventPar = ptr;
	ptr.reset();
	while(line.find("<particles>") == string::npos){
            getline(aStream,line);
            if(!aStream.good()){
            cout << "Error reading particles (1) " << endl;
            return aStream;
            }
        }
    int tmpnp = aEvent._eventPar->GetNParticles();
    for(int i=0;i<tmpnp;++i){
        TX p;
        if(!aStream.good()){
            if(line.find("</particles>")){
                cout << "Particles ended before expected!" << endl;
                aStream.setstate(ios::goodbit);
                break;
                }
                cout << "Error reading particles (2) " << endl;
                return aStream;
               }
        aStream >> p;
        aEvent.AddParticle(p);
        }
    while(line.find("</particles>") == string::npos){
        getline(aStream,line);
        if(!aStream.good()){
            cout << "Error reading particles (3) " << endl;
            return aStream;
            }
        }
    while(line.find("</event>") == string::npos){
        getline(aStream,line);
        if(!aStream.good()){
            cout << "Error reading event " << endl;
            return aStream;
            }
        }
    aEvent._good = true;
	return aStream;
}

template<typename TZ, typename TW>
ostream& operator<< (ostream& aStream, Event<TZ,TW>& aEvent){
    aStream << "<event>\n" << *aEvent._eventPar;
    aStream << "\n\t<particles>\n";
    for(auto p : aEvent._pList){
        aStream << "\t" << p << "\n";
    }
    aStream << "\t</particles>\n</event>";
    return aStream;
}