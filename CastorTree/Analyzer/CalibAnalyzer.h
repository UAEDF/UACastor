#ifndef CalibAnalyzer_h
#define CalibAnalyzer_h

#include <TString.h>
#include <TRegexp.h>
#include <TObjArray.h>
#include <TH1.h>
#include "../src/MyJet.h"

class CalibAnalyzer {
  
 public:
  
  CalibAnalyzer();
  virtual ~CalibAnalyzer();
  
  void Loop(TString inputdir, TObjArray* filelist, double cmenergy);
  void CheckHisto(TH1D* h);
  TH1D* MakeHisto(TString name, TString title, TString xleg, TString yleg, int nbin, double bmin, double bmax);
  TH1D* MakeHisto(int id, TString name, TString title, TString xleg, TString yleg, int nbin, double bmin, double bmax);
  TH1D* MakeHisto(int isec, int imod, TString name, TString title, TString xleg, TString yleg, int nbin, double bmin, double bmax);
 private:
};

#endif
