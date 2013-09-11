#ifndef __TGlauNucleon__
#define __TGlauNucleon__

#include <Riostream.h>
#include <TSystem.h>
#include <TMath.h>
#include <TRandom.h>
#include <TNtuple.h>
#include <TNamed.h>
#include <TF1.h>
#include <TFile.h>
#include <TObjArray.h>
#include <TString.h>
#include <TEllipse.h>

class TGlauNucleon : public TNamed
{
   private:
      Double32_t fX;            //Position of nucleon
      Double32_t fY;            //Position of nucleon
      Double32_t fZ;            //Position of nucleon
      Bool_t     fInNucleusA;   //=1 from nucleus A, =0 from nucleus B
      Int_t      fNColl;        //Number of binary collisions

   public:
      TGlauNucleon() : fX(0), fY(0), fZ(0), fInNucleusA(0), fNColl(0) {}
      virtual   ~TGlauNucleon() {}

      void       Collide()            {fNColl++;}
      Int_t      GetNColl()     const {return fNColl;}
      Double_t   GetX()         const {return fX;}
      Double_t   GetY()         const {return fY;}
      Double_t   GetZ()         const {return fZ;}
      Bool_t     IsInNucleusA() const {return fInNucleusA;}
      Bool_t     IsInNucleusB() const {return !fInNucleusA;}
      Bool_t     IsSpectator()  const {return !fNColl;}
      Bool_t     IsWounded()    const {return fNColl;}
      void       Reset()              {fNColl=0;}
      void       SetInNucleusA()      {fInNucleusA=1;}
      void       SetInNucleusB()      {fInNucleusA=0;}
      void       SetXYZ(Double_t x, Double_t y, Double_t z) {fX=x; fY=y; fZ=z;}

#if !defined (__CINT__) || defined (__MAKECINT__)
      ClassDef(TGlauNucleon,1)
#endif

};

#endif