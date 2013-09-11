#include "TGlauberMC.h"

TGlauberMC::TGlauberMC(Text_t* NA, Text_t* NB, Double_t xsect) :
   fANucleus(NA),fBNucleus(NB),
   fXSect(0),fNucleonsA(0),fNucleonsB(0),fnt(0),
   fMeanX2(0),fMeanY2(0),fMeanXY(0),fMeanXParts(0),
   fMeanYParts(0),fMeanXSystem(0),fMeanYSystem(0),  
   fMeanX_A(0),fMeanY_A(0),fMeanX_B(0),fMeanY_B(0),fB_MC(0),
   fEvents(0),fTotalEvents(0),fBMin(0),fBMax(0),fMaxNpartFound(0),
   fNpart(0),fNcoll(0),fSx2(0),fSy2(0),fSxy(0)
{
   fBMin = 0;
   fBMax = 20;
   fXSect = xsect;
   
   TString name(Form("Glauber_%s_%s",fANucleus.GetName(),fBNucleus.GetName()));
   TString title(Form("Glauber %s+%s Version",fANucleus.GetName(),fBNucleus.GetName()));
   SetName(name);
   SetTitle(title);
}

Bool_t TGlauberMC::CalcEvent(Double_t bgen)
{
   // prepare event
   fANucleus.ThrowNucleons(-bgen/2.);
   fNucleonsA = fANucleus.GetNucleons();
   fAN = fANucleus.GetN();
   for (Int_t i = 0; i<fAN; i++) {
      TGlauNucleon *nucleonA=(TGlauNucleon*)(fNucleonsA->At(i));
      nucleonA->SetInNucleusA();
   }
   fBNucleus.ThrowNucleons(bgen/2.);
   fNucleonsB = fBNucleus.GetNucleons();
   fBN = fBNucleus.GetN();
   for (Int_t i = 0; i<fBN; i++) {
      TGlauNucleon *nucleonB=(TGlauNucleon*)(fNucleonsB->At(i));
      nucleonB->SetInNucleusB();
   }

   // "ball" diameter = distance at which two balls interact
   Double_t d2 = (Double_t)fXSect/(TMath::Pi()*10); // in fm^2

   // for each of the A nucleons in nucleus B
   for (Int_t i = 0; i<fBN; i++) {
      TGlauNucleon *nucleonB=(TGlauNucleon*)(fNucleonsB->At(i));
      for (Int_t j = 0 ; j < fAN ;j++) {
	 TGlauNucleon *nucleonA=(TGlauNucleon*)(fNucleonsA->At(j));
         Double_t dx = nucleonB->GetX()-nucleonA->GetX();
         Double_t dy = nucleonB->GetY()-nucleonA->GetY();
         Double_t dij = dx*dx+dy*dy;
         if (dij < d2) {
            nucleonB->Collide();
            nucleonA->Collide();
         }
      }
  }
   
  return CalcResults(bgen);
}

Bool_t TGlauberMC::CalcResults(Double_t bgen)
{
   // calc results for the given event
   fNpart=0;
   fNcoll=0;
   fMeanX2=0;
   fMeanY2=0;
   fMeanXY=0;
   fMeanXParts=0;
   fMeanYParts=0;
   fMeanXSystem=0;
   fMeanYSystem=0;
   fMeanX_A=0;
   fMeanY_A=0;
   fMeanX_B=0;
   fMeanY_B=0;
  
   for (Int_t i = 0; i<fAN; i++) {
      TGlauNucleon *nucleonA=(TGlauNucleon*)(fNucleonsA->At(i));
      Double_t xA=nucleonA->GetX();
      Double_t yA=nucleonA->GetY();
      fMeanXSystem  += xA;
      fMeanYSystem  += yA;
      fMeanX_A  += xA;
      fMeanY_A  += yA;

      if(nucleonA->IsWounded()) {
         fNpart++;
         fMeanXParts  += xA;
         fMeanYParts  += yA;
         fMeanX2 += xA * xA;
         fMeanY2 += yA * yA;
         fMeanXY += xA * yA;
      }
   }

   for (Int_t i = 0; i<fBN; i++) {
      TGlauNucleon *nucleonB=(TGlauNucleon*)(fNucleonsB->At(i));
      Double_t xB=nucleonB->GetX();
      Double_t yB=nucleonB->GetY();
      fMeanXSystem  += xB;
      fMeanYSystem  += yB;
      fMeanX_B  += xB;
      fMeanY_B  += yB;

      if(nucleonB->IsWounded()) {
         fNpart++;
         fMeanXParts  += xB;
         fMeanYParts  += yB;
         fMeanX2 += xB * xB;
         fMeanY2 += yB * yB;
         fMeanXY += xB * yB;
	 fNcoll += nucleonB->GetNColl();
      }
   }

   if (fNpart>0) {
      fMeanXParts /= fNpart;
      fMeanYParts /= fNpart;
      fMeanX2 /= fNpart;
      fMeanY2 /= fNpart;
      fMeanXY /= fNpart;
   } else {
      fMeanXParts = 0;
      fMeanYParts = 0;
      fMeanX2 = 0;
      fMeanY2 = 0;
      fMeanXY = 0;
   }
   
   if(fAN+fBN>0) {
      fMeanXSystem /= (fAN + fBN);
      fMeanYSystem /= (fAN + fBN);
   } else {
      fMeanXSystem = 0;
      fMeanYSystem = 0;
   }
   if(fAN>0) {
      fMeanX_A /= fAN;
      fMeanY_A /= fAN;
   } else {
      fMeanX_A = 0;
      fMeanY_A = 0;
   }

   if(fBN>0) {
      fMeanX_B /= fBN;
      fMeanY_B /= fBN;
   } else {
      fMeanX_B = 0;
      fMeanY_B = 0;
   }

   fSx2=fMeanX2-(fMeanXParts*fMeanXParts);
   fSy2=fMeanY2-(fMeanYParts*fMeanYParts);
   fSxy=fMeanXY-fMeanXParts*fMeanYParts;

   fB_MC = bgen;

   fTotalEvents++;
   if (fNpart>0) fEvents++;

   if (fNpart==0) return kFALSE;
   if (fNpart > fMaxNpartFound) fMaxNpartFound = fNpart;

   return kTRUE;
}

void TGlauberMC::Draw(Option_t* /*option*/)
{
   fANucleus.Draw(fXSect, 2);
   fBNucleus.Draw(fXSect, 4);

   TEllipse e;
   e.SetFillColor(0);
   e.SetLineColor(1);
   e.SetLineStyle(2);
   e.SetLineWidth(1);
   e.DrawEllipse(GetB()/2,0,fBNucleus.GetR(),fBNucleus.GetR(),0,360,0);
   e.DrawEllipse(-GetB()/2,0,fANucleus.GetR(),fANucleus.GetR(),0,360,0);
}

Double_t TGlauberMC::GetTotXSect() const
{
   return (1.*fEvents/fTotalEvents)*TMath::Pi()*fBMax*fBMax/100;
}

Double_t TGlauberMC::GetTotXSectErr() const
{
   return GetTotXSect()/TMath::Sqrt((Double_t)fEvents) * 
      TMath::Sqrt(Double_t(1.-fEvents/fTotalEvents));
}

TObjArray *TGlauberMC::GetNucleons() 
{
   if(!fNucleonsA || !fNucleonsB) return 0;
   fNucleonsA->SetOwner(0);
   fNucleonsB->SetOwner(0);
   TObjArray *allnucleons=new TObjArray(fAN+fBN);
   allnucleons->SetOwner();
   for (Int_t i = 0; i<fAN; i++) {
      allnucleons->Add(fNucleonsA->At(i));
   }
   for (Int_t i = 0; i<fBN; i++) {
      allnucleons->Add(fNucleonsB->At(i));
   }
   return allnucleons;
}

Bool_t TGlauberMC::NextEvent(Double_t bgen)
{
   if(bgen<0) 
      bgen = TMath::Sqrt((fBMax*fBMax-fBMin*fBMin)*gRandom->Rndm()+fBMin*fBMin);

   return CalcEvent(bgen);
}

void TGlauberMC::Run(Int_t nevents)
{
   TString name(Form("nt_%s_%s",fANucleus.GetName(),fBNucleus.GetName()));
   TString title(Form("%s + %s (x-sect = %d mb)",fANucleus.GetName(),fBNucleus.GetName(),(Int_t) fXSect));
   if (fnt == 0) {
      fnt = new TNtuple(name,title,
                        "Npart:Ncoll:B:MeanX:MeanY:MeanX2:MeanY2:MeanXY:VarX:VarY:VarXY:MeanXSystem:MeanYSystem:MeanXA:MeanYA:MeanXB:MeanYB");
      fnt->SetDirectory(0);
   }

   for (int i = 0;i<nevents;i++) {

      while(!NextEvent()) {}

      Float_t v[17];
      v[0]  = GetNpart();
      v[1]  = GetNcoll();
      v[2]  = fB_MC;
      v[3]  = fMeanXParts;
      v[4]  = fMeanYParts;
      v[5]  = fMeanX2;
      v[6]  = fMeanY2;
      v[7]  = fMeanXY;
      v[8]  = fSx2;
      v[9]  = fSy2;
      v[10] = fSxy;
      v[11] = fMeanXSystem;
      v[12] = fMeanYSystem;
      v[13] = fMeanX_A;
      v[14] = fMeanY_A;
      v[16] = fMeanX_B;
      v[17] = fMeanY_B;

      fnt->Fill(v);

      if (!(i%50)) cout << "Event # " << i << " x-sect = " << GetTotXSect() << " +- " << GetTotXSectErr() << " b        \r" << flush;  
   }
   cout << endl << "Done!" << endl;
}

#if !defined (__CINT__) || defined (__MAKECINT__)
ClassImp(TGlauberMC)
#endif