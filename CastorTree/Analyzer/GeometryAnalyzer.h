#ifndef GeometryAnalyzer_h
#define GeometryAnalyzer_h

#include <TString.h>
#include <TRegexp.h>
#include <TObjArray.h>
#include <TH1.h>
#include <TH2.h>
#include "../src/MyJet.h"
#include "../src/MyGenJet.h"

class GeometryAnalyzer {
  
 public:
  
  GeometryAnalyzer();
  virtual ~GeometryAnalyzer();
  
  void Loop(TString inputdir, TObjArray* filelist, TString type, double cmenergy);
  void CheckHisto(TH1D* h);
  void CheckHisto(TH2D* h);
  void SetAxisName(TH1D* h,TString xleg, TString yleg);
 
  TH1D* MakeHisto(TString name, TString title, TString xleg, TString yleg, int nbin, double bmin, double bmax);
  TH1D* MakeHisto(TString name, TString title, TString xleg, TString yleg, int nbin, float* listbin); 
  TH2D* MakeHisto(TString name, TString title, TString xleg, TString yleg, int nbinx, double bxmin, double bxmax, int nbiny, double bymin, double bymax);
 
  TH1D* MakeHisto(int id, TString name, TString title, TString xleg, TString yleg, int nbin, double bmin, double bmax);
  TH1D* MakeHisto(int isec, int imod, TString name, TString title, TString xleg, TString yleg, int nbin, double bmin, double bmax);
 
  double GetRatioError(double a,double b,double sig_a,double sig_b);

  double GetEflowMCWeight(double Eflow, double cmenergy);  
  double GetTrackJetMCWeight(double pt, double cmenergy);

  double GetNonLinearityFactor(double energy, double cmenergy);

  int GetPosLeadingGenJet(std::vector<MyGenJet> JetVector, double etacut, double minptcut);

  void ComputeRatio(double up, double down, double error_up, double error_down, double &ratio, double &error);
  void ComputeHistoRatio(TH1D* hup,TH1D* hdown, TH1D& hratio);

  int GetPhiMapping(int sector);
  int GetPhiMappingLeft(int sector);
  int GetPhiMappingRight(int sector);

  int GetPhiMappingWithout56(int sector);
  int GetPhiMappingLeftWithout56(int sector);

 private:
};

#endif
