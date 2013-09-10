// Dear emacs, this is -*- C++ -*-
// $Id$
// EDIT ONLY DictDef.h, NEVER LinkDef.h AS IT IS OVERWRITTEN WHEN CODE COMPILIES!
#ifdef __CINT__

#include <TROOT.h>

gROOT->ProcessLine("#include <vector>");
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#include "../common/autopragma.tmp"
#pragma link C++ class std::vector<Particle>+;
#endif // __CINT__




// Add the declarations of your cycles, and any other classes for which you
// want to generate a dictionary, here. The usual format is:
//
// #pragma link C++ class MySuperClass+;

//#pragma link C++ class EfficiencyController+;

//#pragma link C++ class std::vector<std::vector<int> >+;
//#pragma link C++ class std::vector<float>+;
//#pragma link C++ class std::vector<std::vector<float> >+;
//#pragma link C++ class std::vector<std::vector<unsigned int> >+;
