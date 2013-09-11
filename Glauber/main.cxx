#include <iostream>
#include "TGlauberMC.h"
#include <string>
#include <sstream>
#include <sstream>
using namespace std;

/*
void runAndSaveNtuple(Int_t n,
                      Text_t *sysA="Au",
                      Text_t *sysB="Au",
                      Double_t signn=42,
                      Double_t mind=0.4,
                      const char *fname="glau_auau_ntuple.root");

//---------------------------------------------------------------------------------
void runAndSaveNucleons(Int_t n,                    
                        Text_t *sysA="Au",           
                        Text_t *sysB="Au",           
                        Double_t signn=42,           
                        Double_t mind=0.4,
                        Bool_t verbose=0,
                        const char *fname="glau_auau_nucleons.root");


*/

int main(int argc=0, char *argv[]=0){
  if(argc<4){
    cout << "Need to initialize with (at least) two nuclei and a proton cross section!" << endl;
    return 0;
  }
  double xsec=atof(argv[3]);
  if(xsec==0){
    xsec = 42.;
  } 
  if(argc>3){// test if this glauber already exists
    ifstream test(argv[4]);
    if(!test) goto rest;
    string line;
    while(line.find("<info>")==string::npos) getline(test,line);
    while(line.find("process")==string::npos) getline(test,line);
    if(line.find("glauber") == string::npos) goto rest;
    while(line.find("nucl1")==string::npos) getline(test,line);
    if(line.find(argv[1])==string::npos) goto rest;
    while(line.find("nucl2")==string::npos) getline(test,line);
    if(line.find(argv[2])==string::npos) goto rest;
    while(line.find("ppxsec")==string::npos) getline(test,line);
    if(line.find(argv[3])==string::npos) goto rest;
    cout << "This Glauber already exists!" << endl;
    test.close();
    return -1;    
  }
  rest:
  TGlauberMC glauber(argv[1],argv[2],xsec);
  stringstream output;
  output << "\n<info>\nprocess = glauber\nnucl1 = " << argv[1] << endl;
  output << "nucl2 = " << argv[2] << "\nppxsec = " << xsec << " variables = b npart ncoll\n</info>\n";
  for(int i=0;i<1000;++i){
    while(!glauber.NextEvent()) {}
    TObjArray* nucleons=glauber.GetNucleons();
    if(!nucleons) continue;
    output << "<event>\n" << glauber.GetB() << " " << glauber.GetNpart() << " " << glauber.GetNcoll() << "\n<particles>\n</particles>\n</event>\n";
  }
  ofstream out;
  if(argc>4){
    out.open(argv[4]);
  }
  else{
    out.open("glauber.tuple");
  }
  out << output.str() << endl;
  out.close();
  return 1;
}
/*
void runAndSaveNtuple(Int_t n,
                      Text_t *sysA,
                      Text_t *sysB,
                      Double_t signn,
                      Double_t mind,
                      const char *fname)
{
   TGlauberMC *mcg=new TGlauberMC(sysA,sysB,signn);
   mcg->SetMinDistance(mind);
   mcg->Run(n);
   TNtuple  *nt=mcg->GetNtuple();
   TFile out(fname,"recreate",fname,9);
   if(nt) nt->Write();
   out.Close();
}

//---------------------------------------------------------------------------------
void runAndSaveNucleons(Int_t n,                    
                        Text_t *sysA,           
                        Text_t *sysB,           
                        Double_t signn,
                        Double_t mind,
                        Bool_t verbose,
                        const char *fname)
{
   TGlauberMC *mcg=new TGlauberMC(sysA,sysB,signn);
   mcg->SetMinDistance(mind);
   TFile *out=0;
   if(fname) 
      out=new TFile(fname,"recreate",fname,9);

   for(Int_t ievent=0;ievent<n;ievent++){

      //get an event with at least one collision
      while(!mcg->NextEvent()) {}

      //access, save and (if wanted) print out nucleons
      TObjArray* nucleons=mcg->GetNucleons();
      if(!nucleons) continue;
      if(out)
         nucleons->Write(Form("nucleonarray%d",ievent),TObject::kSingleKey);

      if(verbose) {
         cout<<endl<<endl<<"EVENT NO: "<<ievent<<endl;
         cout<<"B = "<<mcg->GetB()<<"  Npart = "<<mcg->GetNpart()<<endl<<endl;
         printf("Nucleus\t X\t Y\t Z\tNcoll\n");
         Int_t nNucls=nucleons->GetEntries();
         for(Int_t iNucl=0;iNucl<nNucls;iNucl++) {
            TGlauNucleon *nucl=(TGlauNucleon *)nucleons->At(iNucl);
            Char_t nucleus='A';
            if(nucl->IsInNucleusB()) nucleus='B';
            Double_t x=nucl->GetX();
            Double_t y=nucl->GetY();
            Double_t z=nucl->GetZ();
            Int_t ncoll=nucl->GetNColl();
            printf("   %c\t%2.2f\t%2.2f\t%2.2f\t%3d\n",nucleus,x,y,z,ncoll);
         }
      }
   }
   if(out) delete out;
}
*/