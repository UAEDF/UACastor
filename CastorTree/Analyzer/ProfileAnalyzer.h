#ifndef ProfileAnalyzer_h
#define ProfileAnalyzer_h

#include <TString.h>
#include <TRegexp.h>
#include <TObjArray.h>
#include <TH1.h>
#include "../src/MyJet.h"

class ProfileAnalyzer {
  
 public:
  
  ProfileAnalyzer();
  virtual ~ProfileAnalyzer();
  
  void Loop(TString inputdir, TObjArray* filelist, bool isData, double cmenergy);
  void CheckHisto(TH1D* h);
  
 private:
};

#endif
