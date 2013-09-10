template<class TX>
ostream& operator<< (ostream& aStream, const Bin<TX> &aBin){
	aStream << "\t\t\t<sum_of_weights=\"" << aBin._w << "\">\n ";
	aStream << "\t\t\t<sum_of_weights_squared=\"" << aBin._w2 << "\">\n ";
	aStream << "\t\t\t<ledge>\n\t\t\t\t" << aBin._v << "\n\t\t\t</ledge>\n";
	aStream << "\t\t\t<width>\n\t\t\t\t" << aBin._width << "\n\t\t\t</width>\n";
	return aStream;
}