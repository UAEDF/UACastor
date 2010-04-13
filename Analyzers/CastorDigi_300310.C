
#define CastorDigi_cxx
 using namespace std;
#include <iostream>
#include "CastorDigi.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
#include <TRandom3.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TGraphErrors.h>

#define M_PI 3.14159265358979323846

Double_t CastorDigi::getRatioError(TH1D * hMB, TH1D * hQCD) {
   
   Double_t error = 0;
   Double_t ratio = hQCD->GetMean()/hMB->GetMean();
   Double_t QCDmeanerror = hQCD->GetMeanError();
   Double_t MBmeanerror = hMB->GetMeanError();
   Double_t QCDmean = hQCD->GetMean();
   Double_t MBmean = hMB->GetMean();
   
   error = ratio*ratio*((QCDmeanerror*QCDmeanerror)/(QCDmean*QCDmean) + (MBmeanerror*MBmeanerror)/(MBmean*MBmean));
   error = sqrt(error);
   return error;

}

Double_t CastorDigi::fCfromADC(Int_t adc){

  static Int_t naxes = 20;

  TAxis InputChargeAxes[naxes];
  InputChargeAxes[0] .Set(15,   -3,     36);
  InputChargeAxes[1] .Set( 7,   36,     73);
  InputChargeAxes[2] .Set( 4,   73,    104);
  InputChargeAxes[3] .Set( 3,  104,    135);
  InputChargeAxes[4] .Set( 3,  135,    174);

  InputChargeAxes[5] .Set(15,  150,    343);
  InputChargeAxes[6] .Set( 7,  343,    525);
  InputChargeAxes[7] .Set( 4,  525,    681);
  InputChargeAxes[8] .Set( 3,  381,    837);
  InputChargeAxes[9] .Set( 3,  837,   1032);

  InputChargeAxes[10].Set(15,   902,  1877);
  InputChargeAxes[11].Set( 7,  1877,  2787);
  InputChargeAxes[12].Set( 4,  2787,  3567);
  InputChargeAxes[13].Set( 3,  3567,  4347);
  InputChargeAxes[14].Set( 3,  4347,  5322);

  InputChargeAxes[15].Set(15,  4672,  9547);
  InputChargeAxes[16].Set( 7,  9547, 14097);
  InputChargeAxes[17].Set( 4, 14097, 17997);
  InputChargeAxes[18].Set( 3, 17997, 21897);
  InputChargeAxes[19].Set( 3, 21897, 26772);




  // .. get fC for given ADC
  Int_t adctmp = -1;
  Int_t wasassigned = 0;
  Double_t result = 0;
  for(Int_t ai = 0; ai < naxes; ai++){
    for(Int_t bi = 1; bi <= InputChargeAxes[ai].GetNbins(); bi++){
      adctmp++;
      //      cout << "bi , adctmp " << bi << " " << adctmp << endl;
      if(adctmp == adc){
        wasassigned = 1;
        result = InputChargeAxes[ai].GetBinCenter(bi);
        break;
      }
    }
  }

  if(!wasassigned) result = -100.;
  return result;
}

void CastorDigi::Loop(int range, int useList, double minhistrange900, double histrange900,double minhistrange2360, double histrange2360, int
usefC, int convertfC, double fCscale)
{


 ////////////////////
  //  set style
  ////////////////////
  gROOT  -> SetStyle("Plain");
  gStyle -> SetMarkerStyle(20);
  gStyle -> SetMarkerSize(1);
  gStyle -> SetTextSize(1);
  //gStyle -> SetOptStat("eMR");//"iourmen");
  gStyle -> SetOptStat("");
  gStyle -> SetLineWidth(1.1);//gStyle->GetLineWidth()*1.5); // 2
  gStyle -> SetHistLineWidth(1.4);//gStyle->GetHistLineWidth()*1.5);// 2
  gStyle -> SetPadLeftMargin(0.25);
  gStyle -> SetPadRightMargin(0.1);
  gStyle -> SetPadBottomMargin(0.25);
  gStyle -> SetPadTopMargin(0.11);
  gStyle -> SetEndErrorSize(5);
  gStyle -> SetCanvasBorderSize(2);
  gStyle -> SetHistFillColor(kGray);
  gStyle -> SetHistMinimumZero(kTRUE);
  gStyle -> SetTitleOffset(2,"y");
  gStyle -> SetLegendBorderSize(0);
  gROOT  -> ForceStyle();


// declare everything...

int n900Events = 0;
int n900CaloInclusive = 0;
int n900CaloDijet = 0;
int n900PFInclusive = 0;
int n900PFDijet = 0;

int n900MCEvents = 0;
int n900MCCaloInclusive = 0;
int n900MCCaloDijet = 0;
int n900MCPFInclusive = 0;
int n900MCPFDijet = 0;

int n2360Events = 0;
int n2360CaloInclusive = 0;
int n2360CaloDijet = 0;
int n2360PFInclusive = 0;
int n2360PFDijet = 0;

int n2360MCEvents = 0;
int n2360MCCaloInclusive = 0;
int n2360MCCaloDijet = 0;
int n2360MCPFInclusive = 0;
int n2360MCPFDijet = 0;

int MCevent = 0;

TString units = "ADC";
if (usefC ==1) units = "fC"; 

// declare eflow histos

TH1D * h2360SignalTot = new TH1D("h2360SignalTot","Total Signal in CASTOR for MB at 2360 GeV;Signal (" + units + ");Events",105,minhistrange2360,histrange2360);
TH1D * h2360SignalTotPFDijet = new TH1D("h2360SignalTotPFDijet","Total Signal in CASTOR for PF Dijets at 2360 GeV;Signal (" + units + ");Events",21,minhistrange2360,histrange2360);
TH1D * h2360SignalTotPFInclusive = new TH1D("h2360SignalTotPFInclusive","Total Signal in CASTOR for PF Inclusive at 2360 GeV;Signal (" + units + ");Events",21,minhistrange2360,histrange2360);
TH1D * h2360SignalTotCaloDijet = new TH1D("h2360SignalTotCaloDijet","Total Signal in CASTOR for Calo Dijets at 2360 GeV;Signal (" + units + ");Events",21,minhistrange2360,histrange2360);
TH1D * h2360SignalTotCaloInclusive = new TH1D("h2360SignalTotCaloInclusive","Total Signal in CASTOR for Calo Inclusive at 2360 GeV;Signal (" + units + ");Events",21,minhistrange2360,histrange2360);

TH1D * h2360MCSignalTot = new TH1D("h2360MCSignalTot","Total Signal in CASTOR for MB at 2360 GeV MC;Signal (" + units + ");Events",105,minhistrange2360,histrange2360);
TH1D * h2360MCSignalTotPFDijet = new TH1D("h2360MCSignalTotPFDijet","Total Signal in CASTOR for PF Dijets at 2360 GeV MC;Signal (" + units + ");Events",21,minhistrange2360,histrange2360);
TH1D * h2360MCSignalTotPFInclusive = new TH1D("h2360MCSignalTotPFInclusive","Total Signal in CASTOR for PF Inclusive at 2360 GeV MC;Signal (" + units + ");Events",21,minhistrange2360,histrange2360);
TH1D * h2360MCSignalTotCaloDijet = new TH1D("h2360MCSignalTotCaloDijet","Total Signal in CASTOR for Calo Dijets at 2360 GeV MC;Signal (" + units + ");Events",21,minhistrange2360,histrange2360);
TH1D * h2360MCSignalTotCaloInclusive = new TH1D("h2360MCSignalTotCaloInclusive","Total Signal in CASTOR for Calo Inclusive at 2360 GeV MC;Signal (" + units + ");Events",21,minhistrange2360,histrange2360);

TH1D * h900SignalTot = new TH1D("h900SignalTot","Total Signal in CASTOR for MB at 900 GeV;Signal (" + units + ");Events",105,minhistrange900,histrange900);
TH1D * h900SignalTotPFDijet = new TH1D("h900SignalTotPFDijet","Total Signal in CASTOR for PF Dijets at 900 GeV;Signal (" + units + ");Events",21,minhistrange900,histrange900);
TH1D * h900SignalTotPFInclusive = new TH1D("h900SignalTotPFInclusive","Total Signal in CASTOR for PF Inclusive at 900 GeV;Signal (" + units + ");Events",21,minhistrange900,histrange900);
TH1D * h900SignalTotCaloDijet = new TH1D("h900SignalTotCaloDijet","Total Signal in CASTOR for Calo Dijets at 900 GeV;Signal (" + units + ");Events",21,minhistrange900,histrange900);
TH1D * h900SignalTotCaloInclusive = new TH1D("h900SignalTotCaloInclusive","Total Signal in CASTOR for Calo Inclusive at 900 GeV;Signal (" + units + ");Events",21,minhistrange900,histrange900);

TH1D * h900MCSignalTot = new TH1D("h900MCSignalTot","Total Signal in CASTOR for MB at 900 GeV MC;Signal (" + units + ");Events",105,minhistrange900,histrange900);
TH1D * h900MCSignalTotPFDijet = new TH1D("h900MCSignalTotPFDijet","Total Signal in CASTOR for PF Dijets at 900 GeV MC;Signal (" + units + ");Events",21,minhistrange900,histrange900);
TH1D * h900MCSignalTotPFInclusive = new TH1D("h900MCSignalTotPFInclusive","Total Signal in CASTOR for PF Inclusive at 900 GeV MC;Signal (" + units + ");Events",21,minhistrange900,histrange900);
TH1D * h900MCSignalTotCaloDijet = new TH1D("h900MCSignalTotCaloDijet","Total Signal in CASTOR for Calo Dijets at 900 GeV MC;Signal (" + units + ");Events",21,minhistrange900,histrange900);
TH1D * h900MCSignalTotCaloInclusive = new TH1D("h900MCSignalTotCaloInclusive","Total Signal in CASTOR for Calo Inclusive at 900 GeV MC;Signal (" + units + ");Events",21,minhistrange900,histrange900);

// declare eflow histos per module-sector
double minMhistrange900 = -100;
double minMhistrange2360 = -100;
double maxMhistrange900 = 1000;
double maxMhistrange2360 = 4000;

double minShistrange900 = -100;
double minShistrange2360 = -100;
double maxShistrange900 = 500;
double maxShistrange2360 = 4000;

if (usefC == 1) {
minMhistrange900 = -500;
minMhistrange2360 = -500;
maxMhistrange900 = 30000;
maxMhistrange2360 = 40000;

minShistrange900 = -500;
minShistrange2360 = -500;
maxShistrange900 = 30000;
maxShistrange2360 = 40000;
}


TH1D * h900SignalM1 = new TH1D("h900SignalM1","Total Signal in module 1 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900SignalM2 = new TH1D("h900SignalM2","Total Signal in module 2 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900SignalM3 = new TH1D("h900SignalM3","Total Signal in module 3 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900SignalM4 = new TH1D("h900SignalM4","Total Signal in module 4 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900SignalM5 = new TH1D("h900SignalM5","Total Signal in module 5 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900SignalM6 = new TH1D("h900SignalM6","Total Signal in module 6 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900SignalM7 = new TH1D("h900SignalM7","Total Signal in module 7 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900SignalM8 = new TH1D("h900SignalM8","Total Signal in module 8 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900SignalM9 = new TH1D("h900SignalM9","Total Signal in module 9 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900SignalM10 = new TH1D("h900SignalM10","Total Signal in module 10 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900SignalM11 = new TH1D("h900SignalM11","Total Signal in module 11 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900SignalM12 = new TH1D("h900SignalM12","Total Signal in module 12 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900SignalM13 = new TH1D("h900SignalM13","Total Signal in module 13 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900SignalM14 = new TH1D("h900SignalM14","Total Signal in module 14 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);

TH1D * h900MCSignalM1 = new TH1D("h900MCSignalM1","Total Signal in module 1 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalM2 = new TH1D("h900MCSignalM2","Total Signal in module 2 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalM3 = new TH1D("h900MCSignalM3","Total Signal in module 3 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalM4 = new TH1D("h900MCSignalM4","Total Signal in module 4 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalM5 = new TH1D("h900MCSignalM5","Total Signal in module 5 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalM6 = new TH1D("h900MCSignalM6","Total Signal in module 6 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalM7 = new TH1D("h900MCSignalM7","Total Signal in module 7 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalM8 = new TH1D("h900MCSignalM8","Total Signal in module 8 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalM9 = new TH1D("h900MCSignalM9","Total Signal in module 9 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalM10 = new TH1D("h900MCSignalM10","Total Signal in module 10 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalM11 = new TH1D("h900MCSignalM11","Total Signal in module 11 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalM12 = new TH1D("h900MCSignalM12","Total Signal in module 12 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalM13 = new TH1D("h900MCSignalM13","Total Signal in module 13 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalM14 = new TH1D("h900MCSignalM14","Total Signal in module 14 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minMhistrange900,maxMhistrange900);

TH1D * h900SignalPFDijetM1 = new TH1D("h900SignalPFDijetM1","Total Signal in module 1 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900SignalPFDijetM2 = new TH1D("h900SignalPFDijetM2","Total Signal in module 2 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900SignalPFDijetM3 = new TH1D("h900SignalPFDijetM3","Total Signal in module 3 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900SignalPFDijetM4 = new TH1D("h900SignalPFDijetM4","Total Signal in module 4 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900SignalPFDijetM5 = new TH1D("h900SignalPFDijetM5","Total Signal in module 5 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900SignalPFDijetM6 = new TH1D("h900SignalPFDijetM6","Total Signal in module 6 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900SignalPFDijetM7 = new TH1D("h900SignalPFDijetM7","Total Signal in module 7 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900SignalPFDijetM8 = new TH1D("h900SignalPFDijetM8","Total Signal in module 8 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900SignalPFDijetM9 = new TH1D("h900SignalPFDijetM9","Total Signal in module 9 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900SignalPFDijetM10 = new TH1D("h900SignalPFDijetM10","Total Signal in module 10 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900SignalPFDijetM11 = new TH1D("h900SignalPFDijetM11","Total Signal in module 11 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900SignalPFDijetM12 = new TH1D("h900SignalPFDijetM12","Total Signal in module 12 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900SignalPFDijetM13 = new TH1D("h900SignalPFDijetM13","Total Signal in module 13 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900SignalPFDijetM14 = new TH1D("h900SignalPFDijetM14","Total Signal in module 14 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);

TH1D * h900MCSignalPFDijetM1 = new TH1D("h900MCSignalPFDijetM1","Total Signal in module 1 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalPFDijetM2 = new TH1D("h900MCSignalPFDijetM2","Total Signal in module 2 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalPFDijetM3 = new TH1D("h900MCSignalPFDijetM3","Total Signal in module 3 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalPFDijetM4 = new TH1D("h900MCSignalPFDijetM4","Total Signal in module 4 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalPFDijetM5 = new TH1D("h900MCSignalPFDijetM5","Total Signal in module 5 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalPFDijetM6 = new TH1D("h900MCSignalPFDijetM6","Total Signal in module 6 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalPFDijetM7 = new TH1D("h900MCSignalPFDijetM7","Total Signal in module 7 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalPFDijetM8 = new TH1D("h900MCSignalPFDijetM8","Total Signal in module 8 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalPFDijetM9 = new TH1D("h900MCSignalPFDijetM9","Total Signal in module 9 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalPFDijetM10 = new TH1D("h900MCSignalPFDijetM10","Total Signal in module 10 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalPFDijetM11 = new TH1D("h900MCSignalPFDijetM11","Total Signal in module 11 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalPFDijetM12 = new TH1D("h900MCSignalPFDijetM12","Total Signal in module 12 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalPFDijetM13 = new TH1D("h900MCSignalPFDijetM13","Total Signal in module 13 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);
TH1D * h900MCSignalPFDijetM14 = new TH1D("h900MCSignalPFDijetM14","Total Signal in module 14 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minMhistrange900,maxMhistrange900);

TH1D * h2360SignalM1 = new TH1D("h2360SignalM1","Total Signal in module 1 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalM2 = new TH1D("h2360SignalM2","Total Signal in module 2 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalM3 = new TH1D("h2360SignalM3","Total Signal in module 3 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalM4 = new TH1D("h2360SignalM4","Total Signal in module 4 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalM5 = new TH1D("h2360SignalM5","Total Signal in module 5 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalM6 = new TH1D("h2360SignalM6","Total Signal in module 6 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalM7 = new TH1D("h2360SignalM7","Total Signal in module 7 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalM8 = new TH1D("h2360SignalM8","Total Signal in module 8 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalM9 = new TH1D("h2360SignalM9","Total Signal in module 9 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalM10 = new TH1D("h2360SignalM10","Total Signal in module 10 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalM11 = new TH1D("h2360SignalM11","Total Signal in module 11 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalM12 = new TH1D("h2360SignalM12","Total Signal in module 12 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalM13 = new TH1D("h2360SignalM13","Total Signal in module 13 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalM14 = new TH1D("h2360SignalM14","Total Signal in module 14 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);

TH1D * h2360MCSignalM1 = new TH1D("h2360MCSignalM1","Total Signal in module 1 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalM2 = new TH1D("h2360MCSignalM2","Total Signal in module 2 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalM3 = new TH1D("h2360MCSignalM3","Total Signal in module 3 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalM4 = new TH1D("h2360MCSignalM4","Total Signal in module 4 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalM5 = new TH1D("h2360MCSignalM5","Total Signal in module 5 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalM6 = new TH1D("h2360MCSignalM6","Total Signal in module 6 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalM7 = new TH1D("h2360MCSignalM7","Total Signal in module 7 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalM8 = new TH1D("h2360MCSignalM8","Total Signal in module 8 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalM9 = new TH1D("h2360MCSignalM9","Total Signal in module 9 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalM10 = new TH1D("h2360MCSignalM10","Total Signal in module 10 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalM11 = new TH1D("h2360MCSignalM11","Total Signal in module 11 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalM12 = new TH1D("h2360MCSignalM12","Total Signal in module 12 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalM13 = new TH1D("h2360MCSignalM13","Total Signal in module 13 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalM14 = new TH1D("h2360MCSignalM14","Total Signal in module 14 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minMhistrange2360,maxMhistrange2360);

TH1D * h2360SignalPFDijetM1 = new TH1D("h2360SignalPFDijetM1","Total Signal in module 1 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalPFDijetM2 = new TH1D("h2360SignalPFDijetM2","Total Signal in module 2 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalPFDijetM3 = new TH1D("h2360SignalPFDijetM3","Total Signal in module 3 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalPFDijetM4 = new TH1D("h2360SignalPFDijetM4","Total Signal in module 4 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalPFDijetM5 = new TH1D("h2360SignalPFDijetM5","Total Signal in module 5 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalPFDijetM6 = new TH1D("h2360SignalPFDijetM6","Total Signal in module 6 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalPFDijetM7 = new TH1D("h2360SignalPFDijetM7","Total Signal in module 7 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalPFDijetM8 = new TH1D("h2360SignalPFDijetM8","Total Signal in module 8 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalPFDijetM9 = new TH1D("h2360SignalPFDijetM9","Total Signal in module 9 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalPFDijetM10 = new TH1D("h2360SignalPFDijetM10","Total Signal in module 10 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalPFDijetM11 = new TH1D("h2360SignalPFDijetM11","Total Signal in module 11 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalPFDijetM12 = new TH1D("h2360SignalPFDijetM12","Total Signal in module 12 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalPFDijetM13 = new TH1D("h2360SignalPFDijetM13","Total Signal in module 13 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360SignalPFDijetM14 = new TH1D("h2360SignalPFDijetM14","Total Signal in module 14 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);

TH1D * h2360MCSignalPFDijetM1 = new TH1D("h2360MCSignalPFDijetM1","Total Signal in module 1 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalPFDijetM2 = new TH1D("h2360MCSignalPFDijetM2","Total Signal in module 2 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalPFDijetM3 = new TH1D("h2360MCSignalPFDijetM3","Total Signal in module 3 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalPFDijetM4 = new TH1D("h2360MCSignalPFDijetM4","Total Signal in module 4 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalPFDijetM5 = new TH1D("h2360MCSignalPFDijetM5","Total Signal in module 5 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalPFDijetM6 = new TH1D("h2360MCSignalPFDijetM6","Total Signal in module 6 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalPFDijetM7 = new TH1D("h2360MCSignalPFDijetM7","Total Signal in module 7 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalPFDijetM8 = new TH1D("h2360MCSignalPFDijetM8","Total Signal in module 8 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalPFDijetM9 = new TH1D("h2360MCSignalPFDijetM9","Total Signal in module 9 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalPFDijetM10 = new TH1D("h2360MCSignalPFDijetM10","Total Signal in module 10 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalPFDijetM11 = new TH1D("h2360MCSignalPFDijetM11","Total Signal in module 11 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalPFDijetM12 = new TH1D("h2360MCSignalPFDijetM12","Total Signal in module 12 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalPFDijetM13 = new TH1D("h2360MCSignalPFDijetM13","Total Signal in module 13 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);
TH1D * h2360MCSignalPFDijetM14 = new TH1D("h2360MCSignalPFDijetM14","Total Signal in module 14 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minMhistrange2360,maxMhistrange2360);

// sector plots

TH1D * h900SignalS1 = new TH1D("h900SignalS1","Total Signal in sector 1 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900SignalS2 = new TH1D("h900SignalS2","Total Signal in sector 2 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900SignalS3 = new TH1D("h900SignalS3","Total Signal in sector 3 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900SignalS4 = new TH1D("h900SignalS4","Total Signal in sector 4 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900SignalS5 = new TH1D("h900SignalS5","Total Signal in sector 5 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900SignalS6 = new TH1D("h900SignalS6","Total Signal in sector 6 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900SignalS7 = new TH1D("h900SignalS7","Total Signal in sector 7 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900SignalS8 = new TH1D("h900SignalS8","Total Signal in sector 8 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900SignalS9 = new TH1D("h900SignalS9","Total Signal in sector 9 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900SignalS10 = new TH1D("h900SignalS10","Total Signal in sector 10 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900SignalS11 = new TH1D("h900SignalS11","Total Signal in sector 11 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900SignalS12 = new TH1D("h900SignalS12","Total Signal in sector 12 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900SignalS13 = new TH1D("h900SignalS13","Total Signal in sector 13 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900SignalS14 = new TH1D("h900SignalS14","Total Signal in sector 14 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900SignalS15 = new TH1D("h900SignalS15","Total Signal in sector 15 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900SignalS16 = new TH1D("h900SignalS16","Total Signal in sector 16 of CASTOR for MB at 900 GeV;Signal("+units+");Events",105,minShistrange900,maxShistrange900);

TH1D * h900MCSignalS1 = new TH1D("h900MCSignalS1","Total Signal in sector 1 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900MCSignalS2 = new TH1D("h900MCSignalS2","Total Signal in sector 2 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900MCSignalS3 = new TH1D("h900MCSignalS3","Total Signal in sector 3 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900MCSignalS4 = new TH1D("h900MCSignalS4","Total Signal in sector 4 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900MCSignalS5 = new TH1D("h900MCSignalS5","Total Signal in sector 5 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900MCSignalS6 = new TH1D("h900MCSignalS6","Total Signal in sector 6 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900MCSignalS7 = new TH1D("h900MCSignalS7","Total Signal in sector 7 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900MCSignalS8 = new TH1D("h900MCSignalS8","Total Signal in sector 8 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900MCSignalS9 = new TH1D("h900MCSignalS9","Total Signal in sector 9 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900MCSignalS10 = new TH1D("h900MCSignalS10","Total Signal in sector 10 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900MCSignalS11 = new TH1D("h900MCSignalS11","Total Signal in sector 11 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900MCSignalS12 = new TH1D("h900MCSignalS12","Total Signal in sector 12 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900MCSignalS13 = new TH1D("h900MCSignalS13","Total Signal in sector 13 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900MCSignalS14 = new TH1D("h900MCSignalS14","Total Signal in sector 14 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900MCSignalS15 = new TH1D("h900MCSignalS15","Total Signal in sector 15 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minShistrange900,maxShistrange900);
TH1D * h900MCSignalS16 = new TH1D("h900MCSignalS16","Total Signal in sector 16 of CASTOR for MB at 900 GeV MC;Signal("+units+");Events",105,minShistrange900,maxShistrange900);

TH1D * h900SignalPFDijetS1 = new TH1D("h900SignalPFDijetS1","Total Signal in sector 1 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900SignalPFDijetS2 = new TH1D("h900SignalPFDijetS2","Total Signal in sector 2 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900SignalPFDijetS3 = new TH1D("h900SignalPFDijetS3","Total Signal in sector 3 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900SignalPFDijetS4 = new TH1D("h900SignalPFDijetS4","Total Signal in sector 4 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900SignalPFDijetS5 = new TH1D("h900SignalPFDijetS5","Total Signal in sector 5 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900SignalPFDijetS6 = new TH1D("h900SignalPFDijetS6","Total Signal in sector 6 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900SignalPFDijetS7 = new TH1D("h900SignalPFDijetS7","Total Signal in sector 7 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900SignalPFDijetS8 = new TH1D("h900SignalPFDijetS8","Total Signal in sector 8 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900SignalPFDijetS9 = new TH1D("h900SignalPFDijetS9","Total Signal in sector 9 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900SignalPFDijetS10 = new TH1D("h900SignalPFDijetS10","Total Signal in sector 10 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900SignalPFDijetS11 = new TH1D("h900SignalPFDijetS11","Total Signal in sector 11 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900SignalPFDijetS12 = new TH1D("h900SignalPFDijetS12","Total Signal in sector 12 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900SignalPFDijetS13 = new TH1D("h900SignalPFDijetS13","Total Signal in sector 13 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900SignalPFDijetS14 = new TH1D("h900SignalPFDijetS14","Total Signal in sector 14 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900SignalPFDijetS15 = new TH1D("h900SignalPFDijetS15","Total Signal in sector 15 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900SignalPFDijetS16 = new TH1D("h900SignalPFDijetS16","Total Signal in sector 16 of CASTOR for central dijets at 900 GeV;Signal("+units+");Events",25,minShistrange900,maxShistrange900);

TH1D * h900MCSignalPFDijetS1 = new TH1D("h900MCSignalPFDijetS1","Total Signal in sector 1 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900MCSignalPFDijetS2 = new TH1D("h900MCSignalPFDijetS2","Total Signal in sector 2 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900MCSignalPFDijetS3 = new TH1D("h900MCSignalPFDijetS3","Total Signal in sector 3 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900MCSignalPFDijetS4 = new TH1D("h900MCSignalPFDijetS4","Total Signal in sector 4 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900MCSignalPFDijetS5 = new TH1D("h900MCSignalPFDijetS5","Total Signal in sector 5 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900MCSignalPFDijetS6 = new TH1D("h900MCSignalPFDijetS6","Total Signal in sector 6 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900MCSignalPFDijetS7 = new TH1D("h900MCSignalPFDijetS7","Total Signal in sector 7 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900MCSignalPFDijetS8 = new TH1D("h900MCSignalPFDijetS8","Total Signal in sector 8 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900MCSignalPFDijetS9 = new TH1D("h900MCSignalPFDijetS9","Total Signal in sector 9 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900MCSignalPFDijetS10 = new TH1D("h900MCSignalPFDijetS10","Total Signal in sector 10 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900MCSignalPFDijetS11 = new TH1D("h900MCSignalPFDijetS11","Total Signal in sector 11 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900MCSignalPFDijetS12 = new TH1D("h900MCSignalPFDijetS12","Total Signal in sector 12 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900MCSignalPFDijetS13 = new TH1D("h900MCSignalPFDijetS13","Total Signal in sector 13 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900MCSignalPFDijetS14 = new TH1D("h900MCSignalPFDijetS14","Total Signal in sector 14 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900MCSignalPFDijetS15 = new TH1D("h900MCSignalPFDijetS15","Total Signal in sector 15 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minShistrange900,maxShistrange900);
TH1D * h900MCSignalPFDijetS16 = new TH1D("h900MCSignalPFDijetS16","Total Signal in sector 16 of CASTOR for central dijets at 900 GeV MC;Signal("+units+");Events",25,minShistrange900,maxShistrange900);

TH1D * h2360SignalS1 = new TH1D("h2360SignalS1","Total Signal in sector 1 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalS2 = new TH1D("h2360SignalS2","Total Signal in sector 2 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalS3 = new TH1D("h2360SignalS3","Total Signal in sector 3 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalS4 = new TH1D("h2360SignalS4","Total Signal in sector 4 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalS5 = new TH1D("h2360SignalS5","Total Signal in sector 5 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalS6 = new TH1D("h2360SignalS6","Total Signal in sector 6 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalS7 = new TH1D("h2360SignalS7","Total Signal in sector 7 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalS8 = new TH1D("h2360SignalS8","Total Signal in sector 8 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalS9 = new TH1D("h2360SignalS9","Total Signal in sector 9 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalS10 = new TH1D("h2360SignalS10","Total Signal in sector 10 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalS11 = new TH1D("h2360SignalS11","Total Signal in sector 11 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalS12 = new TH1D("h2360SignalS12","Total Signal in sector 12 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalS13 = new TH1D("h2360SignalS13","Total Signal in sector 13 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalS14 = new TH1D("h2360SignalS14","Total Signal in sector 14 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalS15 = new TH1D("h2360SignalS15","Total Signal in sector 15 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalS16 = new TH1D("h2360SignalS16","Total Signal in sector 16 of CASTOR for MB at 2360 GeV;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);

TH1D * h2360MCSignalS1 = new TH1D("h2360MCSignalS1","Total Signal in sector 1 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalS2 = new TH1D("h2360MCSignalS2","Total Signal in sector 2 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalS3 = new TH1D("h2360MCSignalS3","Total Signal in sector 3 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalS4 = new TH1D("h2360MCSignalS4","Total Signal in sector 4 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalS5 = new TH1D("h2360MCSignalS5","Total Signal in sector 5 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalS6 = new TH1D("h2360MCSignalS6","Total Signal in sector 6 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalS7 = new TH1D("h2360MCSignalS7","Total Signal in sector 7 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalS8 = new TH1D("h2360MCSignalS8","Total Signal in sector 8 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalS9 = new TH1D("h2360MCSignalS9","Total Signal in sector 9 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalS10 = new TH1D("h2360MCSignalS10","Total Signal in sector 10 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalS11 = new TH1D("h2360MCSignalS11","Total Signal in sector 11 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalS12 = new TH1D("h2360MCSignalS12","Total Signal in sector 12 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalS13 = new TH1D("h2360MCSignalS13","Total Signal in sector 13 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalS14 = new TH1D("h2360MCSignalS14","Total Signal in sector 14 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalS15 = new TH1D("h2360MCSignalS15","Total Signal in sector 15 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalS16 = new TH1D("h2360MCSignalS16","Total Signal in sector 16 of CASTOR for MB at 2360 GeV MC;Signal("+units+");Events",105,minShistrange2360,maxShistrange2360);

TH1D * h2360SignalPFDijetS1 = new TH1D("h2360SignalPFDijetS1","Total Signal in sector 1 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalPFDijetS2 = new TH1D("h2360SignalPFDijetS2","Total Signal in sector 2 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalPFDijetS3 = new TH1D("h2360SignalPFDijetS3","Total Signal in sector 3 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalPFDijetS4 = new TH1D("h2360SignalPFDijetS4","Total Signal in sector 4 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalPFDijetS5 = new TH1D("h2360SignalPFDijetS5","Total Signal in sector 5 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalPFDijetS6 = new TH1D("h2360SignalPFDijetS6","Total Signal in sector 6 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalPFDijetS7 = new TH1D("h2360SignalPFDijetS7","Total Signal in sector 7 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalPFDijetS8 = new TH1D("h2360SignalPFDijetS8","Total Signal in sector 8 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalPFDijetS9 = new TH1D("h2360SignalPFDijetS9","Total Signal in sector 9 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalPFDijetS10 = new TH1D("h2360SignalPFDijetS10","Total Signal in sector 10 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalPFDijetS11 = new TH1D("h2360SignalPFDijetS11","Total Signal in sector 11 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalPFDijetS12 = new TH1D("h2360SignalPFDijetS12","Total Signal in sector 12 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalPFDijetS13 = new TH1D("h2360SignalPFDijetS13","Total Signal in sector 13 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalPFDijetS14 = new TH1D("h2360SignalPFDijetS14","Total Signal in sector 14 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalPFDijetS15 = new TH1D("h2360SignalPFDijetS15","Total Signal in sector 15 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360SignalPFDijetS16 = new TH1D("h2360SignalPFDijetS16","Total Signal in sector 16 of CASTOR for central dijets at 2360 GeV;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);

TH1D * h2360MCSignalPFDijetS1 = new TH1D("h2360MCSignalPFDijetS1","Total Signal in sector 1 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalPFDijetS2 = new TH1D("h2360MCSignalPFDijetS2","Total Signal in sector 2 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalPFDijetS3 = new TH1D("h2360MCSignalPFDijetS3","Total Signal in sector 3 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalPFDijetS4 = new TH1D("h2360MCSignalPFDijetS4","Total Signal in sector 4 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalPFDijetS5 = new TH1D("h2360MCSignalPFDijetS5","Total Signal in sector 5 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalPFDijetS6 = new TH1D("h2360MCSignalPFDijetS6","Total Signal in sector 6 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalPFDijetS7 = new TH1D("h2360MCSignalPFDijetS7","Total Signal in sector 7 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalPFDijetS8 = new TH1D("h2360MCSignalPFDijetS8","Total Signal in sector 8 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalPFDijetS9 = new TH1D("h2360MCSignalPFDijetS9","Total Signal in sector 9 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalPFDijetS10 = new TH1D("h2360MCSignalPFDijetS10","Total Signal in sector 10 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalPFDijetS11 = new TH1D("h2360MCSignalPFDijetS11","Total Signal in sector 11 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalPFDijetS12 = new TH1D("h2360MCSignalPFDijetS12","Total Signal in sector 12 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalPFDijetS13 = new TH1D("h2360MCSignalPFDijetS13","Total Signal in sector 13 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalPFDijetS14 = new TH1D("h2360MCSignalPFDijetS14","Total Signal in sector 14 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalPFDijetS15 = new TH1D("h2360MCSignalPFDijetS15","Total Signal in sector 15 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);
TH1D * h2360MCSignalPFDijetS16 = new TH1D("h2360MCSignalPFDijetS16","Total Signal in sector 16 of CASTOR for central dijets at 2360 GeV MC;Signal("+units+");Events",25,minShistrange2360,maxShistrange2360);


// ratio plots in modules and sectors

TH1D * h900RatiosModules = new TH1D("h900RatiosModules","QCD/MB ratio at 900GeV in CASTOR modules;Modules;Ratio",14,1,15);
TH1D * h900RatiosSectors = new TH1D("h900RatiosSectors","QCD/MB ratio at 900GeV in CASTOR sectors;Sectors;Ratio",16,1,17);
TH1D * h900RatiosModulesMC = new TH1D("h900RatiosModulesMC","MC QCD/MB ratio at 900GeV in CASTOR modules;Modules;Ratio",14,1,15);
TH1D * h900RatiosSectorsMC = new TH1D("h900RatiosSectorsMC","MC QCD/MB ratio at 900GeV in CASTOR sectors;Sectors;Ratio",16,1,17);

TH1D * h2360RatiosModules = new TH1D("h2360RatiosModules","QCD/MB ratio at 900GeV in CASTOR modules;Modules;Ratio",14,1,15);
TH1D * h2360RatiosSectors = new TH1D("h2360RatiosSectors","QCD/MB ratio at 900GeV in CASTOR sectors;Sectors;Ratio",16,1,17);
TH1D * h2360RatiosModulesMC = new TH1D("h2360RatiosModulesMC","MC QCD/MB ratio at 900GeV in CASTOR modules;Modules;Ratio",14,1,15);
TH1D * h2360RatiosSectorsMC = new TH1D("h2360RatiosSectorsMC","MC QCD/MB ratio at 900GeV in CASTOR sectors;Sectors;Ratio",16,1,17);

TH1D * hMeansModules = new TH1D("hMeansModules","MB Mean at 900GeV in CASTOR modules;Modules;Mean",14,1,15);
TH1D * hMeansSectors = new TH1D("hMeansSectors","MB Mean at 900GeV in CASTOR sectors;Sectors;Mean",16,1,17);
TH1D * hMeansModulesMC = new TH1D("hMeansModulesMC","MB Mean at 900GeV in CASTOR modules;Modules;Mean",14,1,15);
TH1D * hMeansSectorsMC = new TH1D("hMeansSectorsMC","MB Mean at 900GeV in CASTOR sectors;Sectors;Mean",16,1,17);

TH1D * hMeansQCDModules = new TH1D("hMeansQCDModules","QCD Mean at 900GeV in CASTOR modules;Modules;Mean",14,1,15);
TH1D * hMeansQCDSectors = new TH1D("hMeansQCDSectors","QCD Mean at 900GeV in CASTOR sectors;Sectors;Mean",16,1,17);
TH1D * hMeansQCDModulesMC = new TH1D("hMeansQCDModulesMC","QCD Mean at 900GeV in CASTOR modules;Modules;Mean",14,1,15);
TH1D * hMeansQCDSectorsMC = new TH1D("hMeansQCDSectorsMC","QCD Mean at 900GeV in CASTOR sectors;Sectors;Mean",16,1,17);

TH1D * hMeans2360Modules = new TH1D("hMeans2360Modules","MB Mean at 2360GeV in CASTOR modules;Modules;Mean",14,1,15);
TH1D * hMeans2360Sectors = new TH1D("hMeans2360Sectors","MB Mean at 2360GeV in CASTOR sectors;Sectors;Mean",16,1,17);
TH1D * hMeans2360ModulesMC = new TH1D("hMeans2360ModulesMC","MB Mean at 2360GeV in CASTOR modules;Modules;Mean",14,1,15);
TH1D * hMeans2360SectorsMC = new TH1D("hMeans2360SectorsMC","MB Mean at 2360GeV in CASTOR sectors;Sectors;Mean",16,1,17);

TH1D * hMeans2360QCDModules = new TH1D("hMeans2360QCDModules","QCD Mean at 2360GeV in CASTOR modules;Modules;Mean",14,1,15);
TH1D * hMeans2360QCDSectors = new TH1D("hMeans2360QCDSectors","QCD Mean at 2360GeV in CASTOR sectors;Sectors;Mean",16,1,17);
TH1D * hMeans2360QCDModulesMC = new TH1D("hMeans2360QCDModulesMC","QCD Mean at 2360GeV in CASTOR modules;Modules;Mean",14,1,15);
TH1D * hMeans2360QCDSectorsMC = new TH1D("hMeans2360QCDSectorsMC","QCD Mean at 2360GeV in CASTOR sectors;Sectors;Mean",16,1,17);



// declare jet histos

TH1D * hPFDijetPt = new TH1D("hPFDijetPt","PF Dijet Pt distribution;Pt (GeV);Events",70,0,70);
TH1D * hPFInclusivePt = new TH1D("hPFInclusivePt","PF Inclusive Pt distribution;Pt (GeV);Events",70,0,70);
TH1D * hPFDijetEta = new TH1D("hPFDijetEta","PF Dijet Eta distribution;#eta;Events",60,-3,3);
TH1D * hPFInclusiveEta = new TH1D("hPFInclusiveEta","PF Inclusive Eta distribution;#eta;Events",60,-3,3);
TH1D * hPFDijetPhi = new TH1D("hPFDijetPhi","PF Dijet Phi distribution;#phi;Events",20,-M_PI,M_PI);
TH1D * hPFInclusivePhi = new TH1D("hPFInclusivePhi","PF Inclusive Phi distribution;#phi;Events",20,-M_PI,M_PI);

// declare channel plot histos

TH1D * h900channels = new TH1D("h900channels","Mean channel signal for 900GeV MC",96,0,97);
TH1D * h2360channels = new TH1D("h2360channels","Mean channel signal for 2360GeV MC",96,0,97);
TH1D * h900decalchannels = new TH1D("h900decalchannels","Mean decalibrated channel signal for 900GeV MC",96,0,97);
TH1D * h2360decalchannels = new TH1D("h2360decalchannels","Mean decalibrated channel signal for 2360GeV MC",96,0,97);

// declare pulse shape histos

TH1D * hDataSlices = new TH1D("hDataSlices","Data pulse shapes in ADC",6,0,6);
TH1D * hMCSlices = new TH1D("hMCSlices","MC pusle shapes in ADC",6,0,6);
TH1D * hDataSlicesfC = new TH1D("hDataSlicesfC","Data pulse shapes in fC",6,0,6);
TH1D * hMCSlicesfC = new TH1D("hMCSlicesfC","MC pusle shapes in fC",6,0,6);
/*
TH1D * hnChannels = new TH1D("hnChannels","channels",6,0,6);
		for (int i=1;i<=6;i++) {
			hnChannels->SetBinContent(i,96);
		}
*/

TH1D *h900EChannel[96];
TH1D *h900EChannelQCD[96];
Char_t htitle[96];
Char_t hname[96];
Char_t htitleQCD[96];
Char_t hnameQCD[96];

TH1D *h900EChannelMC[96];
TH1D *h900EChannelQCDMC[96];
Char_t htitleMC[96];
Char_t hnameMC[96];
Char_t htitleQCDMC[96];
Char_t hnameQCDMC[96];

for (int i=0;i<96;i++) {
	sprintf(hname,"h900EChannel_%d",i);
	sprintf(htitle,"MB Energy in CASTOR channel %d",i);
	sprintf(hnameQCD,"h900EChannelQCD_%d",i);
	sprintf(htitleQCD,"QCD Energy in CASTOR channel %d",i);
	h900EChannel[i] = new TH1D(hname,htitle,105,-500,30000);
	h900EChannelQCD[i] = new TH1D(hnameQCD,htitleQCD,105,-500,30000);
	
	sprintf(hnameMC,"h900EChannelMC_%d",i);
	sprintf(htitleMC,"MC MB Energy in CASTOR channel %d",i);
	sprintf(hnameQCDMC,"h900EChannelQCDMC_%d",i);
	sprintf(htitleQCDMC,"MC QCD Energy in CASTOR channel %d",i);
	h900EChannelMC[i] = new TH1D(hnameMC,htitleMC,105,-500,30000);
	h900EChannelQCDMC[i] = new TH1D(hnameQCDMC,htitleQCDMC,105,-500,30000);
}

TH1D *h2360EChannel[96];
TH1D *h2360EChannelQCD[96];
Char_t htitle2360[96];
Char_t hname2360[96];
Char_t htitle2360QCD[96];
Char_t hname2360QCD[96];

TH1D *h2360EChannelMC[96];
TH1D *h2360EChannelQCDMC[96];
Char_t htitle2360MC[96];
Char_t hname2360MC[96];
Char_t htitle2360QCDMC[96];
Char_t hname2360QCDMC[96];

for (int i=0;i<96;i++) {
	sprintf(hname2360,"h2360EChannel_%d",i);
	sprintf(htitle2360,"MB Energy in CASTOR channel %d",i);
	sprintf(hname2360QCD,"h2360EChannelQCD_%d",i);
	sprintf(htitle2360QCD,"QCD Energy in CASTOR channel %d",i);
	h2360EChannel[i] = new TH1D(hname2360,htitle2360,105,-500,30000);
	h2360EChannelQCD[i] = new TH1D(hname2360QCD,htitle2360QCD,105,-500,30000);
	
	sprintf(hname2360MC,"h2360EChannelMC_%d",i);
	sprintf(htitle2360MC,"MC MB Energy in CASTOR channel %d",i);
	sprintf(hname2360QCDMC,"h2360EChannelQCDMC_%d",i);
	sprintf(htitle2360QCDMC,"MC QCD Energy in CASTOR channel %d",i);
	h2360EChannelMC[i] = new TH1D(hname2360MC,htitle2360MC,105,-500,30000);
	h2360EChannelQCDMC[i] = new TH1D(hname2360QCDMC,htitle2360QCDMC,105,-500,30000);
}


// variables for manual mean calculation of distribution
double sum900 = 0;
double sum900MC = 0;
double sum2360 = 0;
double sum2360MC = 0;
double sum900PFInclusive = 0;
double sum900MCPFInclusive = 0;
double sum2360PFInclusive = 0;
double sum2360MCPFInclusive = 0;
double sum900PFDijet = 0;
double sum900MCPFDijet = 0;
double sum2360PFDijet = 0;
double sum2360MCPFDijet = 0;

/*

for (int k=0;k<531;k++) {
	cout << k+1 << " Run = " << PFDijetList[k][0] << " Lumi = " << PFDijetList[k][1] << " Event = " << PFDijetList[k][2] << endl;
}
for (int k=0;k<246;k++) {
	cout << k+1 << " Run = " << CaloDijetList[k][0] << " Lumi = " << CaloDijetList[k][1] << " Event = " << CaloDijetList[k][2] << endl;
}
*/

cout << "Module range is set to " << range << endl;
cout << "useList is set to " << useList << endl;
cout << "900GeV histograms range is set to " << histrange900 << endl;
cout << "2360GeV histograms range is set to " << histrange2360 << endl;
cout << "usefC is set to " << usefC << endl;
cout << "convertfC is set to " << convertfC << endl;
cout << "Starting event loop now" << endl;

//   In a ROOT session, you can do:
//      Root > .L CastorDigi.C
//      Root > CastorDigi t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   int d=1;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      if (jentry/(d*1000) > 1) {cout << jentry << endl; d++;};  
      
      // change between ADC and fC
      	if (convertfC ==1) {
		//if (runNumber != 1) {
		// convert to fC manually by using Karel's function
		for (int i=0;i<224;i++) {
			// reset 
			fCsignal[i]=0;
			sumfC[i] = 0;
			for (int j=0;j<6;j++) {
				fC[i][j] = 0;
				fC[i][j] = fCfromADC(ADC[i][j]);
				if (j>1) sumfC[i] = sumfC[i] + fC[i][j]; // sum 4 last time slices
			}
			fCsignal[i] = sumfC[i] - 4*2.6*pedestal[i]; // substract pedestal in fC
		}
		/*
		}  else {
		for (int i=0;i<224;i++) {
			// reset 
			fCsignal[i]=0;
			sumfC[i] = 0;
			for (int j=0;j<6;j++) {
				fC[i][j] = 0;
				if (j<3) fC[i][j] = fCfromADC(ADC[i][j]);
				if (j==3) fC[i][j] = 2.6*pedestal[i] + fCfromADC(0.7*(ADC[i][3]-pedestal[i]));
				if (j==4) fC[i][j] = 2.6*pedestal[i] + fCfromADC(0.2*(ADC[i][3]-pedestal[i]));
				if (j==5) fC[i][j] = 2.6*pedestal[i] + fCfromADC(0.1*(ADC[i][3]-pedestal[i]));
				if (j>1) sumfC[i] = sumfC[i] + fC[i][j]; // sum 4 last time slices
			}
			fCsignal[i] = sumfC[i] - 4*2.6*pedestal[i]; // substract pedestal in fC
		}
		}
		*/
		
	} 
      
      // select 900 GeV runs for data
      if (runNumber == 124020 || runNumber == 124022 || runNumber == 124023 || 
      runNumber == 124024 || runNumber == 124027 || runNumber == 124030) {
      
      
      		// fill channel histos from module 1-6
		for (int i=0;i<96;i++) {
			h900EChannel[i]->Fill(fCsignal[i]);
			if (isPFDijet == 1) h900EChannelQCD[i]->Fill(fCsignal[i]);
		}
      
      		// fill time slice histo
		
		for (int i=0;i<96;i++) {
			for (int j=0;j<6;j++) {
				hDataSlices->Fill(j+0.1,ADC[i][j]);
				hDataSlicesfC->Fill(j+0.1,fC[i][j]);
			}
		}
		
		hDataSlices->Scale(1./96.);
		hDataSlicesfC->Scale(1./96.);
      
      		// calculate total numbers
      		n900Events = n900Events +1; 
       
       		// calculate total signals
       		double SignalTot = 0;
		
		double SignalTotM1 = 0;
		double SignalTotM2 = 0;
		double SignalTotM3 = 0;
		double SignalTotM4 = 0;
		double SignalTotM5 = 0;
		double SignalTotM6 = 0;
		double SignalTotM7 = 0;
		double SignalTotM8 = 0;
		double SignalTotM9 = 0;
		double SignalTotM10 = 0;
		double SignalTotM11 = 0;
		double SignalTotM12 = 0;
		double SignalTotM13 = 0;
		double SignalTotM14 = 0;
		
		double SignalTotS1 = 0;
		double SignalTotS2 = 0;
		double SignalTotS3 = 0;
		double SignalTotS4 = 0;
		double SignalTotS5 = 0;
		double SignalTotS6 = 0;
		double SignalTotS7 = 0;
		double SignalTotS8 = 0;
		double SignalTotS9 = 0;
		double SignalTotS10 = 0;
		double SignalTotS11 = 0;
		double SignalTotS12 = 0;
		double SignalTotS13 = 0;
		double SignalTotS14 = 0;
		double SignalTotS15 = 0;
		double SignalTotS16 = 0;
		
		if (range == 15) {	
      			// calculate total fCsignal in CASTOR
			// modules 1-5
      			for (int i=0;i<80;i++) {
      				if (channel[i] != 11 && channel[i] != 12) {
					if (usefC == 0) SignalTot = SignalTot + signal[i];
					if (usefC == 1) SignalTot = SignalTot + fCsignal[i];
					if (module[i] == 1) {
						if (usefC == 0) SignalTotM1 = SignalTotM1 + signal[i];
						if (usefC == 1) SignalTotM1 = SignalTotM1 + fCsignal[i];
					}
					if (module[i] == 2) {
						if (usefC == 0) SignalTotM2 = SignalTotM2 + signal[i];
						if (usefC == 1) SignalTotM2 = SignalTotM2 + fCsignal[i];
					}
					if (module[i] == 3) {
						if (usefC == 0) SignalTotM3 = SignalTotM3 + signal[i];
						if (usefC == 1) SignalTotM3 = SignalTotM3 + fCsignal[i];
					}
					if (module[i] == 4) {
						if (usefC == 0) SignalTotM4 = SignalTotM4 + signal[i];
						if (usefC == 1) SignalTotM4 = SignalTotM4 + fCsignal[i];
					}
					if (module[i] == 5) {
						if (usefC == 0) SignalTotM5 = SignalTotM5 + signal[i];
						if (usefC == 1) SignalTotM5 = SignalTotM5 + fCsignal[i];
					}
					if (module[i] == 6) {
						if (usefC == 0) SignalTotM6 = SignalTotM6 + signal[i];
						if (usefC == 1) SignalTotM6 = SignalTotM6 + fCsignal[i];
					}
					if (module[i] == 7) {
						if (usefC == 0) SignalTotM7 = SignalTotM7 + signal[i];
						if (usefC == 1) SignalTotM7 = SignalTotM7 + fCsignal[i];
					}
					if (module[i] == 8) {
						if (usefC == 0) SignalTotM8 = SignalTotM8 + signal[i];
						if (usefC == 1) SignalTotM8 = SignalTotM8 + fCsignal[i];
					}
					if (module[i] == 9) {
						if (usefC == 0) SignalTotM9 = SignalTotM9 + signal[i];
						if (usefC == 1) SignalTotM9 = SignalTotM9 + fCsignal[i];
					}
					if (module[i] == 10) {
						if (usefC == 0) SignalTotM10 = SignalTotM10 + signal[i];
						if (usefC == 1) SignalTotM10 = SignalTotM10 + fCsignal[i];
					}
					if (module[i] == 11) {
						if (usefC == 0) SignalTotM11 = SignalTotM11 + signal[i];
						if (usefC == 1) SignalTotM11 = SignalTotM11 + fCsignal[i];
					}
					if (module[i] == 12) {
						if (usefC == 0) SignalTotM12 = SignalTotM12 + signal[i];
						if (usefC == 1) SignalTotM12 = SignalTotM12 + fCsignal[i];
					}
					if (module[i] == 13) {
						if (usefC == 0) SignalTotM13 = SignalTotM13 + signal[i];
						if (usefC == 1) SignalTotM13 = SignalTotM13 + fCsignal[i];
					}
					if (module[i] == 14) {
						if (usefC == 0) SignalTotM14 = SignalTotM14 + signal[i];
						if (usefC == 1) SignalTotM14 = SignalTotM14 + fCsignal[i];
					}
					// sectors
					if (sector[i] == 1) {
						if (usefC == 0) SignalTotS1 = SignalTotS1 + signal[i];
						if (usefC == 1) SignalTotS1 = SignalTotS1 + fCsignal[i];
					}
					if (sector[i] == 2) {
						if (usefC == 0) SignalTotS2 = SignalTotS2 + signal[i];
						if (usefC == 1) SignalTotS2 = SignalTotS2 + fCsignal[i];
					}
					if (sector[i] == 3) {
						if (usefC == 0) SignalTotS3 = SignalTotS3 + signal[i];
						if (usefC == 1) SignalTotS3 = SignalTotS3 + fCsignal[i];
					}
					if (sector[i] == 4) {
						if (usefC == 0) SignalTotS4 = SignalTotS4 + signal[i];
						if (usefC == 1) SignalTotS4 = SignalTotS4 + fCsignal[i];
					}
					if (sector[i] == 5) {
						if (usefC == 0) SignalTotS5 = SignalTotS5 + signal[i];
						if (usefC == 1) SignalTotS5 = SignalTotS5 + fCsignal[i];
					}
					if (sector[i] == 6) {
						if (usefC == 0) SignalTotS6 = SignalTotS6 + signal[i];
						if (usefC == 1) SignalTotS6 = SignalTotS6 + fCsignal[i];
					}
					if (sector[i] == 7) {
						if (usefC == 0) SignalTotS7 = SignalTotS7 + signal[i];
						if (usefC == 1) SignalTotS7 = SignalTotS7 + fCsignal[i];
					}
					if (sector[i] == 8) {
						if (usefC == 0) SignalTotS8 = SignalTotS8 + signal[i];
						if (usefC == 1) SignalTotS8 = SignalTotS8 + fCsignal[i];
					}
					if (sector[i] == 9) {
						if (usefC == 0) SignalTotS9 = SignalTotS9 + signal[i];
						if (usefC == 1) SignalTotS9 = SignalTotS9 + fCsignal[i];
					}
					if (sector[i] == 10) {
						if (usefC == 0) SignalTotS10 = SignalTotS10 + signal[i];
						if (usefC == 1) SignalTotS10 = SignalTotS10 + fCsignal[i];
					}
					if (sector[i] == 11) {
						if (usefC == 0) SignalTotS11 = SignalTotS11 + signal[i];
						if (usefC == 1) SignalTotS11 = SignalTotS11 + fCsignal[i];
					}
					if (sector[i] == 12) {
						if (usefC == 0) SignalTotS12 = SignalTotS12 + signal[i];
						if (usefC == 1) SignalTotS12 = SignalTotS12 + fCsignal[i];
					}
					if (sector[i] == 13) {
						if (usefC == 0) SignalTotS13 = SignalTotS13 + signal[i];
						if (usefC == 1) SignalTotS13 = SignalTotS13 + fCsignal[i];
					}
					if (sector[i] == 14) {
						if (usefC == 0) SignalTotS14 = SignalTotS14 + signal[i];
						if (usefC == 1) SignalTotS14 = SignalTotS14 + fCsignal[i];
					}
					if (sector[i] == 15) {
						if (usefC == 0) SignalTotS15 = SignalTotS15 + signal[i];
						if (usefC == 1) SignalTotS15 = SignalTotS15 + fCsignal[i];
					}
					if (sector[i] == 16) {
						if (usefC == 0) SignalTotS16 = SignalTotS16 + signal[i];
						if (usefC == 1) SignalTotS16 = SignalTotS16 + fCsignal[i];
					}
				}
      			}
		}
      		if (range == 16) {	
      			// calculate total fCsignal in CASTOR
			// modules 1-6
      			for (int i=0;i<96;i++) {
				bool channel1 = false;
				if (module[i] == 6 && sector[i] == 16) channel1 = true;
      				if (channel[i] != 11 && channel[i] != 12 && !channel1) {
					if (usefC == 0) SignalTot = SignalTot + signal[i];
					if (usefC == 1) SignalTot = SignalTot + fCsignal[i];
					if (module[i] == 1) {
						if (usefC == 0) SignalTotM1 = SignalTotM1 + signal[i];
						if (usefC == 1) SignalTotM1 = SignalTotM1 + fCsignal[i];
					}
					if (module[i] == 2) {
						if (usefC == 0) SignalTotM2 = SignalTotM2 + signal[i];
						if (usefC == 1) SignalTotM2 = SignalTotM2 + fCsignal[i];
					}
					if (module[i] == 3) {
						if (usefC == 0) SignalTotM3 = SignalTotM3 + signal[i];
						if (usefC == 1) SignalTotM3 = SignalTotM3 + fCsignal[i];
					}
					if (module[i] == 4) {
						if (usefC == 0) SignalTotM4 = SignalTotM4 + signal[i];
						if (usefC == 1) SignalTotM4 = SignalTotM4 + fCsignal[i];
					}
					if (module[i] == 5) {
						if (usefC == 0) SignalTotM5 = SignalTotM5 + signal[i];
						if (usefC == 1) SignalTotM5 = SignalTotM5 + fCsignal[i];
					}
					if (module[i] == 6) {
						if (usefC == 0) SignalTotM6 = SignalTotM6 + signal[i];
						if (usefC == 1) SignalTotM6 = SignalTotM6 + fCsignal[i];
					}
					if (module[i] == 7) {
						if (usefC == 0) SignalTotM7 = SignalTotM7 + signal[i];
						if (usefC == 1) SignalTotM7 = SignalTotM7 + fCsignal[i];
					}
					if (module[i] == 8) {
						if (usefC == 0) SignalTotM8 = SignalTotM8 + signal[i];
						if (usefC == 1) SignalTotM8 = SignalTotM8 + fCsignal[i];
					}
					if (module[i] == 9) {
						if (usefC == 0) SignalTotM9 = SignalTotM9 + signal[i];
						if (usefC == 1) SignalTotM9 = SignalTotM9 + fCsignal[i];
					}
					if (module[i] == 10) {
						if (usefC == 0) SignalTotM10 = SignalTotM10 + signal[i];
						if (usefC == 1) SignalTotM10 = SignalTotM10 + fCsignal[i];
					}
					if (module[i] == 11) {
						if (usefC == 0) SignalTotM11 = SignalTotM11 + signal[i];
						if (usefC == 1) SignalTotM11 = SignalTotM11 + fCsignal[i];
					}
					if (module[i] == 12) {
						if (usefC == 0) SignalTotM12 = SignalTotM12 + signal[i];
						if (usefC == 1) SignalTotM12 = SignalTotM12 + fCsignal[i];
					}
					if (module[i] == 13) {
						if (usefC == 0) SignalTotM13 = SignalTotM13 + signal[i];
						if (usefC == 1) SignalTotM13 = SignalTotM13 + fCsignal[i];
					}
					if (module[i] == 14) {
						if (usefC == 0) SignalTotM14 = SignalTotM14 + signal[i];
						if (usefC == 1) SignalTotM14 = SignalTotM14 + fCsignal[i];
					}
					// sectors
					if (sector[i] == 1) {
						if (usefC == 0) SignalTotS1 = SignalTotS1 + signal[i];
						if (usefC == 1) SignalTotS1 = SignalTotS1 + fCsignal[i];
					}
					if (sector[i] == 2) {
						if (usefC == 0) SignalTotS2 = SignalTotS2 + signal[i];
						if (usefC == 1) SignalTotS2 = SignalTotS2 + fCsignal[i];
					}
					if (sector[i] == 3) {
						if (usefC == 0) SignalTotS3 = SignalTotS3 + signal[i];
						if (usefC == 1) SignalTotS3 = SignalTotS3 + fCsignal[i];
					}
					if (sector[i] == 4) {
						if (usefC == 0) SignalTotS4 = SignalTotS4 + signal[i];
						if (usefC == 1) SignalTotS4 = SignalTotS4 + fCsignal[i];
					}
					if (sector[i] == 5) {
						if (usefC == 0) SignalTotS5 = SignalTotS5 + signal[i];
						if (usefC == 1) SignalTotS5 = SignalTotS5 + fCsignal[i];
					}
					if (sector[i] == 6) {
						if (usefC == 0) SignalTotS6 = SignalTotS6 + signal[i];
						if (usefC == 1) SignalTotS6 = SignalTotS6 + fCsignal[i];
					}
					if (sector[i] == 7) {
						if (usefC == 0) SignalTotS7 = SignalTotS7 + signal[i];
						if (usefC == 1) SignalTotS7 = SignalTotS7 + fCsignal[i];
					}
					if (sector[i] == 8) {
						if (usefC == 0) SignalTotS8 = SignalTotS8 + signal[i];
						if (usefC == 1) SignalTotS8 = SignalTotS8 + fCsignal[i];
					}
					if (sector[i] == 9) {
						if (usefC == 0) SignalTotS9 = SignalTotS9 + signal[i];
						if (usefC == 1) SignalTotS9 = SignalTotS9 + fCsignal[i];
					}
					if (sector[i] == 10) {
						if (usefC == 0) SignalTotS10 = SignalTotS10 + signal[i];
						if (usefC == 1) SignalTotS10 = SignalTotS10 + fCsignal[i];
					}
					if (sector[i] == 11) {
						if (usefC == 0) SignalTotS11 = SignalTotS11 + signal[i];
						if (usefC == 1) SignalTotS11 = SignalTotS11 + fCsignal[i];
					}
					if (sector[i] == 12) {
						if (usefC == 0) SignalTotS12 = SignalTotS12 + signal[i];
						if (usefC == 1) SignalTotS12 = SignalTotS12 + fCsignal[i];
					}
					if (sector[i] == 13) {
						if (usefC == 0) SignalTotS13 = SignalTotS13 + signal[i];
						if (usefC == 1) SignalTotS13 = SignalTotS13 + fCsignal[i];
					}
					if (sector[i] == 14) {
						if (usefC == 0) SignalTotS14 = SignalTotS14 + signal[i];
						if (usefC == 1) SignalTotS14 = SignalTotS14 + fCsignal[i];
					}
					if (sector[i] == 15) {
						if (usefC == 0) SignalTotS15 = SignalTotS15 + signal[i];
						if (usefC == 1) SignalTotS15 = SignalTotS15 + fCsignal[i];
					}
					if (sector[i] == 16) {
						if (usefC == 0) SignalTotS16 = SignalTotS16 + signal[i];
						if (usefC == 1) SignalTotS16 = SignalTotS16 + fCsignal[i];
					}
				}
      			}
		}
		if (range == 27) {
			// calculate total fCsignal in CASTOR
			// modules 2-7
      			for (int i=16;i<112;i++) {
				bool channel1 = false;
				if (module[i] == 6 && sector[i] == 16) channel1 = true;
      				if (channel[i] != 11 && channel[i] != 12 && !channel1) {
					if (usefC == 0) SignalTot = SignalTot + signal[i];
					if (usefC == 1) SignalTot = SignalTot + fCsignal[i];
					if (module[i] == 1) {
						if (usefC == 0) SignalTotM1 = SignalTotM1 + signal[i];
						if (usefC == 1) SignalTotM1 = SignalTotM1 + fCsignal[i];
					}
					if (module[i] == 2) {
						if (usefC == 0) SignalTotM2 = SignalTotM2 + signal[i];
						if (usefC == 1) SignalTotM2 = SignalTotM2 + fCsignal[i];
					}
					if (module[i] == 3) {
						if (usefC == 0) SignalTotM3 = SignalTotM3 + signal[i];
						if (usefC == 1) SignalTotM3 = SignalTotM3 + fCsignal[i];
					}
					if (module[i] == 4) {
						if (usefC == 0) SignalTotM4 = SignalTotM4 + signal[i];
						if (usefC == 1) SignalTotM4 = SignalTotM4 + fCsignal[i];
					}
					if (module[i] == 5) {
						if (usefC == 0) SignalTotM5 = SignalTotM5 + signal[i];
						if (usefC == 1) SignalTotM5 = SignalTotM5 + fCsignal[i];
					}
					if (module[i] == 6) {
						if (usefC == 0) SignalTotM6 = SignalTotM6 + signal[i];
						if (usefC == 1) SignalTotM6 = SignalTotM6 + fCsignal[i];
					}
					if (module[i] == 7) {
						if (usefC == 0) SignalTotM7 = SignalTotM7 + signal[i];
						if (usefC == 1) SignalTotM7 = SignalTotM7 + fCsignal[i];
					}
					if (module[i] == 8) {
						if (usefC == 0) SignalTotM8 = SignalTotM8 + signal[i];
						if (usefC == 1) SignalTotM8 = SignalTotM8 + fCsignal[i];
					}
					if (module[i] == 9) {
						if (usefC == 0) SignalTotM9 = SignalTotM9 + signal[i];
						if (usefC == 1) SignalTotM9 = SignalTotM9 + fCsignal[i];
					}
					if (module[i] == 10) {
						if (usefC == 0) SignalTotM10 = SignalTotM10 + signal[i];
						if (usefC == 1) SignalTotM10 = SignalTotM10 + fCsignal[i];
					}
					if (module[i] == 11) {
						if (usefC == 0) SignalTotM11 = SignalTotM11 + signal[i];
						if (usefC == 1) SignalTotM11 = SignalTotM11 + fCsignal[i];
					}
					if (module[i] == 12) {
						if (usefC == 0) SignalTotM12 = SignalTotM12 + signal[i];
						if (usefC == 1) SignalTotM12 = SignalTotM12 + fCsignal[i];
					}
					if (module[i] == 13) {
						if (usefC == 0) SignalTotM13 = SignalTotM13 + signal[i];
						if (usefC == 1) SignalTotM13 = SignalTotM13 + fCsignal[i];
					}
					if (module[i] == 14) {
						if (usefC == 0) SignalTotM14 = SignalTotM14 + signal[i];
						if (usefC == 1) SignalTotM14 = SignalTotM14 + fCsignal[i];
					}
					// sectors
					if (sector[i] == 1) {
						if (usefC == 0) SignalTotS1 = SignalTotS1 + signal[i];
						if (usefC == 1) SignalTotS1 = SignalTotS1 + fCsignal[i];
					}
					if (sector[i] == 2) {
						if (usefC == 0) SignalTotS2 = SignalTotS2 + signal[i];
						if (usefC == 1) SignalTotS2 = SignalTotS2 + fCsignal[i];
					}
					if (sector[i] == 3) {
						if (usefC == 0) SignalTotS3 = SignalTotS3 + signal[i];
						if (usefC == 1) SignalTotS3 = SignalTotS3 + fCsignal[i];
					}
					if (sector[i] == 4) {
						if (usefC == 0) SignalTotS4 = SignalTotS4 + signal[i];
						if (usefC == 1) SignalTotS4 = SignalTotS4 + fCsignal[i];
					}
					if (sector[i] == 5) {
						if (usefC == 0) SignalTotS5 = SignalTotS5 + signal[i];
						if (usefC == 1) SignalTotS5 = SignalTotS5 + fCsignal[i];
					}
					if (sector[i] == 6) {
						if (usefC == 0) SignalTotS6 = SignalTotS6 + signal[i];
						if (usefC == 1) SignalTotS6 = SignalTotS6 + fCsignal[i];
					}
					if (sector[i] == 7) {
						if (usefC == 0) SignalTotS7 = SignalTotS7 + signal[i];
						if (usefC == 1) SignalTotS7 = SignalTotS7 + fCsignal[i];
					}
					if (sector[i] == 8) {
						if (usefC == 0) SignalTotS8 = SignalTotS8 + signal[i];
						if (usefC == 1) SignalTotS8 = SignalTotS8 + fCsignal[i];
					}
					if (sector[i] == 9) {
						if (usefC == 0) SignalTotS9 = SignalTotS9 + signal[i];
						if (usefC == 1) SignalTotS9 = SignalTotS9 + fCsignal[i];
					}
					if (sector[i] == 10) {
						if (usefC == 0) SignalTotS10 = SignalTotS10 + signal[i];
						if (usefC == 1) SignalTotS10 = SignalTotS10 + fCsignal[i];
					}
					if (sector[i] == 11) {
						if (usefC == 0) SignalTotS11 = SignalTotS11 + signal[i];
						if (usefC == 1) SignalTotS11 = SignalTotS11 + fCsignal[i];
					}
					if (sector[i] == 12) {
						if (usefC == 0) SignalTotS12 = SignalTotS12 + signal[i];
						if (usefC == 1) SignalTotS12 = SignalTotS12 + fCsignal[i];
					}
					if (sector[i] == 13) {
						if (usefC == 0) SignalTotS13 = SignalTotS13 + signal[i];
						if (usefC == 1) SignalTotS13 = SignalTotS13 + fCsignal[i];
					}
					if (sector[i] == 14) {
						if (usefC == 0) SignalTotS14 = SignalTotS14 + signal[i];
						if (usefC == 1) SignalTotS14 = SignalTotS14 + fCsignal[i];
					}
					if (sector[i] == 15) {
						if (usefC == 0) SignalTotS15 = SignalTotS15 + signal[i];
						if (usefC == 1) SignalTotS15 = SignalTotS15 + fCsignal[i];
					}
					if (sector[i] == 16) {
						if (usefC == 0) SignalTotS16 = SignalTotS16 + signal[i];
						if (usefC == 1) SignalTotS16 = SignalTotS16 + fCsignal[i];
					}
				}
      			}
		}
		if (range == 19) {
			// calculate total fCsignal in CASTOR
			// modules 1-9
      			for (int i=0;i<144;i++) {
				bool channel1 = false;
				bool channel2 = false;
				bool channel3 = false;
				if (module[i] == 6 && sector[i] == 16) channel1 = true;
				if (module[i] == 8 && sector[i] == 3) channel2 = true;
				if (module[i] == 8 && sector[i] == 8) channel3 = true;
				if (channel[i] != 11 && channel[i] != 12 && !channel1 && !channel2 && !channel3) {
					if (usefC == 0) SignalTot = SignalTot + signal[i];
					if (usefC == 1) SignalTot = SignalTot + fCsignal[i];
					if (module[i] == 1) {
						if (usefC == 0) SignalTotM1 = SignalTotM1 + signal[i];
						if (usefC == 1) SignalTotM1 = SignalTotM1 + fCsignal[i];
					}
					if (module[i] == 2) {
						if (usefC == 0) SignalTotM2 = SignalTotM2 + signal[i];
						if (usefC == 1) SignalTotM2 = SignalTotM2 + fCsignal[i];
					}
					if (module[i] == 3) {
						if (usefC == 0) SignalTotM3 = SignalTotM3 + signal[i];
						if (usefC == 1) SignalTotM3 = SignalTotM3 + fCsignal[i];
					}
					if (module[i] == 4) {
						if (usefC == 0) SignalTotM4 = SignalTotM4 + signal[i];
						if (usefC == 1) SignalTotM4 = SignalTotM4 + fCsignal[i];
					}
					if (module[i] == 5) {
						if (usefC == 0) SignalTotM5 = SignalTotM5 + signal[i];
						if (usefC == 1) SignalTotM5 = SignalTotM5 + fCsignal[i];
					}
					if (module[i] == 6) {
						if (usefC == 0) SignalTotM6 = SignalTotM6 + signal[i];
						if (usefC == 1) SignalTotM6 = SignalTotM6 + fCsignal[i];
					}
					if (module[i] == 7) {
						if (usefC == 0) SignalTotM7 = SignalTotM7 + signal[i];
						if (usefC == 1) SignalTotM7 = SignalTotM7 + fCsignal[i];
					}
					if (module[i] == 8) {
						if (usefC == 0) SignalTotM8 = SignalTotM8 + signal[i];
						if (usefC == 1) SignalTotM8 = SignalTotM8 + fCsignal[i];
					}
					if (module[i] == 9) {
						if (usefC == 0) SignalTotM9 = SignalTotM9 + signal[i];
						if (usefC == 1) SignalTotM9 = SignalTotM9 + fCsignal[i];
					}
					if (module[i] == 10) {
						if (usefC == 0) SignalTotM10 = SignalTotM10 + signal[i];
						if (usefC == 1) SignalTotM10 = SignalTotM10 + fCsignal[i];
					}
					if (module[i] == 11) {
						if (usefC == 0) SignalTotM11 = SignalTotM11 + signal[i];
						if (usefC == 1) SignalTotM11 = SignalTotM11 + fCsignal[i];
					}
					if (module[i] == 12) {
						if (usefC == 0) SignalTotM12 = SignalTotM12 + signal[i];
						if (usefC == 1) SignalTotM12 = SignalTotM12 + fCsignal[i];
					}
					if (module[i] == 13) {
						if (usefC == 0) SignalTotM13 = SignalTotM13 + signal[i];
						if (usefC == 1) SignalTotM13 = SignalTotM13 + fCsignal[i];
					}
					if (module[i] == 14) {
						if (usefC == 0) SignalTotM14 = SignalTotM14 + signal[i];
						if (usefC == 1) SignalTotM14 = SignalTotM14 + fCsignal[i];
					}
					// sectors
					if (sector[i] == 1) {
						if (usefC == 0) SignalTotS1 = SignalTotS1 + signal[i];
						if (usefC == 1) SignalTotS1 = SignalTotS1 + fCsignal[i];
					}
					if (sector[i] == 2) {
						if (usefC == 0) SignalTotS2 = SignalTotS2 + signal[i];
						if (usefC == 1) SignalTotS2 = SignalTotS2 + fCsignal[i];
					}
					if (sector[i] == 3) {
						if (usefC == 0) SignalTotS3 = SignalTotS3 + signal[i];
						if (usefC == 1) SignalTotS3 = SignalTotS3 + fCsignal[i];
					}
					if (sector[i] == 4) {
						if (usefC == 0) SignalTotS4 = SignalTotS4 + signal[i];
						if (usefC == 1) SignalTotS4 = SignalTotS4 + fCsignal[i];
					}
					if (sector[i] == 5) {
						if (usefC == 0) SignalTotS5 = SignalTotS5 + signal[i];
						if (usefC == 1) SignalTotS5 = SignalTotS5 + fCsignal[i];
					}
					if (sector[i] == 6) {
						if (usefC == 0) SignalTotS6 = SignalTotS6 + signal[i];
						if (usefC == 1) SignalTotS6 = SignalTotS6 + fCsignal[i];
					}
					if (sector[i] == 7) {
						if (usefC == 0) SignalTotS7 = SignalTotS7 + signal[i];
						if (usefC == 1) SignalTotS7 = SignalTotS7 + fCsignal[i];
					}
					if (sector[i] == 8) {
						if (usefC == 0) SignalTotS8 = SignalTotS8 + signal[i];
						if (usefC == 1) SignalTotS8 = SignalTotS8 + fCsignal[i];
					}
					if (sector[i] == 9) {
						if (usefC == 0) SignalTotS9 = SignalTotS9 + signal[i];
						if (usefC == 1) SignalTotS9 = SignalTotS9 + fCsignal[i];
					}
					if (sector[i] == 10) {
						if (usefC == 0) SignalTotS10 = SignalTotS10 + signal[i];
						if (usefC == 1) SignalTotS10 = SignalTotS10 + fCsignal[i];
					}
					if (sector[i] == 11) {
						if (usefC == 0) SignalTotS11 = SignalTotS11 + signal[i];
						if (usefC == 1) SignalTotS11 = SignalTotS11 + fCsignal[i];
					}
					if (sector[i] == 12) {
						if (usefC == 0) SignalTotS12 = SignalTotS12 + signal[i];
						if (usefC == 1) SignalTotS12 = SignalTotS12 + fCsignal[i];
					}
					if (sector[i] == 13) {
						if (usefC == 0) SignalTotS13 = SignalTotS13 + signal[i];
						if (usefC == 1) SignalTotS13 = SignalTotS13 + fCsignal[i];
					}
					if (sector[i] == 14) {
						if (usefC == 0) SignalTotS14 = SignalTotS14 + signal[i];
						if (usefC == 1) SignalTotS14 = SignalTotS14 + fCsignal[i];
					}
					if (sector[i] == 15) {
						if (usefC == 0) SignalTotS15 = SignalTotS15 + signal[i];
						if (usefC == 1) SignalTotS15 = SignalTotS15 + fCsignal[i];
					}
					if (sector[i] == 16) {
						if (usefC == 0) SignalTotS16 = SignalTotS16 + signal[i];
						if (usefC == 1) SignalTotS16 = SignalTotS16 + fCsignal[i];
					}
				}	
      			}
		}
      
      		// fill total signal histograms
      		h900SignalTot->Fill(SignalTot);
				h900SignalM1->Fill(SignalTotM1);
				h900SignalM2->Fill(SignalTotM2);
				h900SignalM3->Fill(SignalTotM3);
				h900SignalM4->Fill(SignalTotM4);
				h900SignalM5->Fill(SignalTotM5);
				h900SignalM6->Fill(SignalTotM6);
				h900SignalM7->Fill(SignalTotM7);
				h900SignalM8->Fill(SignalTotM8);
				h900SignalM9->Fill(SignalTotM9);
				h900SignalM10->Fill(SignalTotM10);
				h900SignalM11->Fill(SignalTotM11);
				h900SignalM12->Fill(SignalTotM12);
				h900SignalM13->Fill(SignalTotM13);
				h900SignalM14->Fill(SignalTotM14);
				h900SignalS1->Fill(SignalTotS1);
				h900SignalS2->Fill(SignalTotS2);
				h900SignalS3->Fill(SignalTotS3);
				h900SignalS4->Fill(SignalTotS4);
				h900SignalS5->Fill(SignalTotS5);
				h900SignalS6->Fill(SignalTotS6);
				h900SignalS7->Fill(SignalTotS7);
				h900SignalS8->Fill(SignalTotS8);
				h900SignalS9->Fill(SignalTotS9);
				h900SignalS10->Fill(SignalTotS10);
				h900SignalS11->Fill(SignalTotS11);
				h900SignalS12->Fill(SignalTotS12);
				h900SignalS13->Fill(SignalTotS13);
				h900SignalS14->Fill(SignalTotS14);
				h900SignalS15->Fill(SignalTotS15);
				h900SignalS16->Fill(SignalTotS16);
		
		if (useList == 0) {    
      			if (isCaloInclusive == 1) n900CaloInclusive += 1;
      			if (isCaloDijet == 1) n900CaloDijet += 1;
      			if (isPFInclusive == 1) n900PFInclusive += 1;
      			if (isPFDijet == 1) n900PFDijet += 1;
			if (isPFDijet == 1) {
				h900SignalTotPFDijet->Fill(SignalTot);
				h900SignalPFDijetM1->Fill(SignalTotM1);
				h900SignalPFDijetM2->Fill(SignalTotM2);
				h900SignalPFDijetM3->Fill(SignalTotM3);
				h900SignalPFDijetM4->Fill(SignalTotM4);
				h900SignalPFDijetM5->Fill(SignalTotM5);
				h900SignalPFDijetM6->Fill(SignalTotM6);
				h900SignalPFDijetM7->Fill(SignalTotM7);
				h900SignalPFDijetM8->Fill(SignalTotM8);
				h900SignalPFDijetM9->Fill(SignalTotM9);
				h900SignalPFDijetM10->Fill(SignalTotM10);
				h900SignalPFDijetM11->Fill(SignalTotM11);
				h900SignalPFDijetM12->Fill(SignalTotM12);
				h900SignalPFDijetM13->Fill(SignalTotM13);
				h900SignalPFDijetM14->Fill(SignalTotM14);
				h900SignalPFDijetS1->Fill(SignalTotS1);
				h900SignalPFDijetS2->Fill(SignalTotS2);
				h900SignalPFDijetS3->Fill(SignalTotS3);
				h900SignalPFDijetS4->Fill(SignalTotS4);
				h900SignalPFDijetS5->Fill(SignalTotS5);
				h900SignalPFDijetS6->Fill(SignalTotS6);
				h900SignalPFDijetS7->Fill(SignalTotS7);
				h900SignalPFDijetS8->Fill(SignalTotS8);
				h900SignalPFDijetS9->Fill(SignalTotS9);
				h900SignalPFDijetS10->Fill(SignalTotS10);
				h900SignalPFDijetS11->Fill(SignalTotS11);
				h900SignalPFDijetS12->Fill(SignalTotS12);
				h900SignalPFDijetS13->Fill(SignalTotS13);
				h900SignalPFDijetS14->Fill(SignalTotS14);
				h900SignalPFDijetS15->Fill(SignalTotS15);
				h900SignalPFDijetS16->Fill(SignalTotS16);
			}	
      			if (isPFInclusive == 1) h900SignalTotPFInclusive->Fill(SignalTot);
      			if (isCaloDijet == 1) h900SignalTotCaloDijet->Fill(SignalTot);
      			if (isCaloInclusive == 1) h900SignalTotCaloInclusive->Fill(SignalTot);
		}	 
		 
		if (useList == 1) {  
		  	for (int i=0;i<2088;i++) {
			  	if (PFInclusiveList[i][0] == runNumber && PFInclusiveList[i][1] == lumiBlock && PFInclusiveList[i][2] == eventNum) 
				{n900PFInclusive += 1;h900SignalTotPFInclusive->Fill(SignalTot);}
		  	}
			for (int i=0;i<531;i++) {
			  	if (PFDijetList[i][0] == runNumber && PFDijetList[i][1] == lumiBlock && PFDijetList[i][2] == eventNum)
				{n900PFDijet += 1;h900SignalTotPFDijet->Fill(SignalTot);}
		  	}
			for (int i=0;i<459;i++) {
			  	if (CaloInclusiveList[i][0] == runNumber && CaloInclusiveList[i][1] == lumiBlock && CaloInclusiveList[i][2] ==eventNum) 
				{n900CaloInclusive += 1;h900SignalTotCaloInclusive->Fill(SignalTot);}
		  	}
			for (int i=0;i<246;i++) {
			  	if (CaloDijetList[i][0] == runNumber && CaloDijetList[i][1] == lumiBlock && CaloDijetList[i][2] == eventNum)
				{n900CaloDijet += 1;h900SignalTotCaloDijet->Fill(SignalTot);}
		  	}
		}
		
		sum900 = sum900 + SignalTot;
		if (isPFInclusive == 1) sum900PFInclusive = sum900PFInclusive + SignalTot;
		if (isPFDijet == 1) sum900PFDijet = sum900PFDijet + SignalTot;
      }
      
      // select 2360 GeV run for data
      if (runNumber == 124120 ) {
      
      		// fill channel histos from module 1-6
		for (int i=0;i<96;i++) {
			h2360EChannel[i]->Fill(fCsignal[i]);
			if (isPFDijet == 1) h2360EChannelQCD[i]->Fill(fCsignal[i]);
		}
      
      		// calculate total numbers
      		n2360Events = n2360Events +1; 
		
      		// calculate total signals
       		double SignalTot = 0;
		
		double SignalTotM1 = 0;
		double SignalTotM2 = 0;
		double SignalTotM3 = 0;
		double SignalTotM4 = 0;
		double SignalTotM5 = 0;
		double SignalTotM6 = 0;
		double SignalTotM7 = 0;
		double SignalTotM8 = 0;
		double SignalTotM9 = 0;
		double SignalTotM10 = 0;
		double SignalTotM11 = 0;
		double SignalTotM12 = 0;
		double SignalTotM13 = 0;
		double SignalTotM14 = 0;
		
		double SignalTotS1 = 0;
		double SignalTotS2 = 0;
		double SignalTotS3 = 0;
		double SignalTotS4 = 0;
		double SignalTotS5 = 0;
		double SignalTotS6 = 0;
		double SignalTotS7 = 0;
		double SignalTotS8 = 0;
		double SignalTotS9 = 0;
		double SignalTotS10 = 0;
		double SignalTotS11 = 0;
		double SignalTotS12 = 0;
		double SignalTotS13 = 0;
		double SignalTotS14 = 0;
		double SignalTotS15 = 0;
		double SignalTotS16 = 0;
		
		if (range == 15) {	
      			// calculate total fCsignal in CASTOR
			// modules 1-5
      			for (int i=0;i<80;i++) {
      				if (channel[i] != 11 && channel[i] != 12) {
					if (usefC == 0) SignalTot = SignalTot + signal[i];
					if (usefC == 1) SignalTot = SignalTot + fCsignal[i];
					if (module[i] == 1) {
						if (usefC == 0) SignalTotM1 = SignalTotM1 + signal[i];
						if (usefC == 1) SignalTotM1 = SignalTotM1 + fCsignal[i];
					}
					if (module[i] == 2) {
						if (usefC == 0) SignalTotM2 = SignalTotM2 + signal[i];
						if (usefC == 1) SignalTotM2 = SignalTotM2 + fCsignal[i];
					}
					if (module[i] == 3) {
						if (usefC == 0) SignalTotM3 = SignalTotM3 + signal[i];
						if (usefC == 1) SignalTotM3 = SignalTotM3 + fCsignal[i];
					}
					if (module[i] == 4) {
						if (usefC == 0) SignalTotM4 = SignalTotM4 + signal[i];
						if (usefC == 1) SignalTotM4 = SignalTotM4 + fCsignal[i];
					}
					if (module[i] == 5) {
						if (usefC == 0) SignalTotM5 = SignalTotM5 + signal[i];
						if (usefC == 1) SignalTotM5 = SignalTotM5 + fCsignal[i];
					}
					if (module[i] == 6) {
						if (usefC == 0) SignalTotM6 = SignalTotM6 + signal[i];
						if (usefC == 1) SignalTotM6 = SignalTotM6 + fCsignal[i];
					}
					if (module[i] == 7) {
						if (usefC == 0) SignalTotM7 = SignalTotM7 + signal[i];
						if (usefC == 1) SignalTotM7 = SignalTotM7 + fCsignal[i];
					}
					if (module[i] == 8) {
						if (usefC == 0) SignalTotM8 = SignalTotM8 + signal[i];
						if (usefC == 1) SignalTotM8 = SignalTotM8 + fCsignal[i];
					}
					if (module[i] == 9) {
						if (usefC == 0) SignalTotM9 = SignalTotM9 + signal[i];
						if (usefC == 1) SignalTotM9 = SignalTotM9 + fCsignal[i];
					}
					if (module[i] == 10) {
						if (usefC == 0) SignalTotM10 = SignalTotM10 + signal[i];
						if (usefC == 1) SignalTotM10 = SignalTotM10 + fCsignal[i];
					}
					if (module[i] == 11) {
						if (usefC == 0) SignalTotM11 = SignalTotM11 + signal[i];
						if (usefC == 1) SignalTotM11 = SignalTotM11 + fCsignal[i];
					}
					if (module[i] == 12) {
						if (usefC == 0) SignalTotM12 = SignalTotM12 + signal[i];
						if (usefC == 1) SignalTotM12 = SignalTotM12 + fCsignal[i];
					}
					if (module[i] == 13) {
						if (usefC == 0) SignalTotM13 = SignalTotM13 + signal[i];
						if (usefC == 1) SignalTotM13 = SignalTotM13 + fCsignal[i];
					}
					if (module[i] == 14) {
						if (usefC == 0) SignalTotM14 = SignalTotM14 + signal[i];
						if (usefC == 1) SignalTotM14 = SignalTotM14 + fCsignal[i];
					}
					// sectors
					if (sector[i] == 1) {
						if (usefC == 0) SignalTotS1 = SignalTotS1 + signal[i];
						if (usefC == 1) SignalTotS1 = SignalTotS1 + fCsignal[i];
					}
					if (sector[i] == 2) {
						if (usefC == 0) SignalTotS2 = SignalTotS2 + signal[i];
						if (usefC == 1) SignalTotS2 = SignalTotS2 + fCsignal[i];
					}
					if (sector[i] == 3) {
						if (usefC == 0) SignalTotS3 = SignalTotS3 + signal[i];
						if (usefC == 1) SignalTotS3 = SignalTotS3 + fCsignal[i];
					}
					if (sector[i] == 4) {
						if (usefC == 0) SignalTotS4 = SignalTotS4 + signal[i];
						if (usefC == 1) SignalTotS4 = SignalTotS4 + fCsignal[i];
					}
					if (sector[i] == 5) {
						if (usefC == 0) SignalTotS5 = SignalTotS5 + signal[i];
						if (usefC == 1) SignalTotS5 = SignalTotS5 + fCsignal[i];
					}
					if (sector[i] == 6) {
						if (usefC == 0) SignalTotS6 = SignalTotS6 + signal[i];
						if (usefC == 1) SignalTotS6 = SignalTotS6 + fCsignal[i];
					}
					if (sector[i] == 7) {
						if (usefC == 0) SignalTotS7 = SignalTotS7 + signal[i];
						if (usefC == 1) SignalTotS7 = SignalTotS7 + fCsignal[i];
					}
					if (sector[i] == 8) {
						if (usefC == 0) SignalTotS8 = SignalTotS8 + signal[i];
						if (usefC == 1) SignalTotS8 = SignalTotS8 + fCsignal[i];
					}
					if (sector[i] == 9) {
						if (usefC == 0) SignalTotS9 = SignalTotS9 + signal[i];
						if (usefC == 1) SignalTotS9 = SignalTotS9 + fCsignal[i];
					}
					if (sector[i] == 10) {
						if (usefC == 0) SignalTotS10 = SignalTotS10 + signal[i];
						if (usefC == 1) SignalTotS10 = SignalTotS10 + fCsignal[i];
					}
					if (sector[i] == 11) {
						if (usefC == 0) SignalTotS11 = SignalTotS11 + signal[i];
						if (usefC == 1) SignalTotS11 = SignalTotS11 + fCsignal[i];
					}
					if (sector[i] == 12) {
						if (usefC == 0) SignalTotS12 = SignalTotS12 + signal[i];
						if (usefC == 1) SignalTotS12 = SignalTotS12 + fCsignal[i];
					}
					if (sector[i] == 13) {
						if (usefC == 0) SignalTotS13 = SignalTotS13 + signal[i];
						if (usefC == 1) SignalTotS13 = SignalTotS13 + fCsignal[i];
					}
					if (sector[i] == 14) {
						if (usefC == 0) SignalTotS14 = SignalTotS14 + signal[i];
						if (usefC == 1) SignalTotS14 = SignalTotS14 + fCsignal[i];
					}
					if (sector[i] == 15) {
						if (usefC == 0) SignalTotS15 = SignalTotS15 + signal[i];
						if (usefC == 1) SignalTotS15 = SignalTotS15 + fCsignal[i];
					}
					if (sector[i] == 16) {
						if (usefC == 0) SignalTotS16 = SignalTotS16 + signal[i];
						if (usefC == 1) SignalTotS16 = SignalTotS16 + fCsignal[i];
					}
				}
      			}
		}
      		if (range == 16) {	
      			// calculate total fCsignal in CASTOR
			// modules 1-6
      			for (int i=0;i<96;i++) {
				bool channel1 = false;
				if (module[i] == 6 && sector[i] == 16) channel1 = true;
      				if (channel[i] != 11 && channel[i] != 12 && !channel1) {
					if (usefC == 0) SignalTot = SignalTot + signal[i];
					if (usefC == 1) SignalTot = SignalTot + fCsignal[i];
					if (module[i] == 1) {
						if (usefC == 0) SignalTotM1 = SignalTotM1 + signal[i];
						if (usefC == 1) SignalTotM1 = SignalTotM1 + fCsignal[i];
					}
					if (module[i] == 2) {
						if (usefC == 0) SignalTotM2 = SignalTotM2 + signal[i];
						if (usefC == 1) SignalTotM2 = SignalTotM2 + fCsignal[i];
					}
					if (module[i] == 3) {
						if (usefC == 0) SignalTotM3 = SignalTotM3 + signal[i];
						if (usefC == 1) SignalTotM3 = SignalTotM3 + fCsignal[i];
					}
					if (module[i] == 4) {
						if (usefC == 0) SignalTotM4 = SignalTotM4 + signal[i];
						if (usefC == 1) SignalTotM4 = SignalTotM4 + fCsignal[i];
					}
					if (module[i] == 5) {
						if (usefC == 0) SignalTotM5 = SignalTotM5 + signal[i];
						if (usefC == 1) SignalTotM5 = SignalTotM5 + fCsignal[i];
					}
					if (module[i] == 6) {
						if (usefC == 0) SignalTotM6 = SignalTotM6 + signal[i];
						if (usefC == 1) SignalTotM6 = SignalTotM6 + fCsignal[i];
					}
					if (module[i] == 7) {
						if (usefC == 0) SignalTotM7 = SignalTotM7 + signal[i];
						if (usefC == 1) SignalTotM7 = SignalTotM7 + fCsignal[i];
					}
					if (module[i] == 8) {
						if (usefC == 0) SignalTotM8 = SignalTotM8 + signal[i];
						if (usefC == 1) SignalTotM8 = SignalTotM8 + fCsignal[i];
					}
					if (module[i] == 9) {
						if (usefC == 0) SignalTotM9 = SignalTotM9 + signal[i];
						if (usefC == 1) SignalTotM9 = SignalTotM9 + fCsignal[i];
					}
					if (module[i] == 10) {
						if (usefC == 0) SignalTotM10 = SignalTotM10 + signal[i];
						if (usefC == 1) SignalTotM10 = SignalTotM10 + fCsignal[i];
					}
					if (module[i] == 11) {
						if (usefC == 0) SignalTotM11 = SignalTotM11 + signal[i];
						if (usefC == 1) SignalTotM11 = SignalTotM11 + fCsignal[i];
					}
					if (module[i] == 12) {
						if (usefC == 0) SignalTotM12 = SignalTotM12 + signal[i];
						if (usefC == 1) SignalTotM12 = SignalTotM12 + fCsignal[i];
					}
					if (module[i] == 13) {
						if (usefC == 0) SignalTotM13 = SignalTotM13 + signal[i];
						if (usefC == 1) SignalTotM13 = SignalTotM13 + fCsignal[i];
					}
					if (module[i] == 14) {
						if (usefC == 0) SignalTotM14 = SignalTotM14 + signal[i];
						if (usefC == 1) SignalTotM14 = SignalTotM14 + fCsignal[i];
					}
					// sectors
					if (sector[i] == 1) {
						if (usefC == 0) SignalTotS1 = SignalTotS1 + signal[i];
						if (usefC == 1) SignalTotS1 = SignalTotS1 + fCsignal[i];
					}
					if (sector[i] == 2) {
						if (usefC == 0) SignalTotS2 = SignalTotS2 + signal[i];
						if (usefC == 1) SignalTotS2 = SignalTotS2 + fCsignal[i];
					}
					if (sector[i] == 3) {
						if (usefC == 0) SignalTotS3 = SignalTotS3 + signal[i];
						if (usefC == 1) SignalTotS3 = SignalTotS3 + fCsignal[i];
					}
					if (sector[i] == 4) {
						if (usefC == 0) SignalTotS4 = SignalTotS4 + signal[i];
						if (usefC == 1) SignalTotS4 = SignalTotS4 + fCsignal[i];
					}
					if (sector[i] == 5) {
						if (usefC == 0) SignalTotS5 = SignalTotS5 + signal[i];
						if (usefC == 1) SignalTotS5 = SignalTotS5 + fCsignal[i];
					}
					if (sector[i] == 6) {
						if (usefC == 0) SignalTotS6 = SignalTotS6 + signal[i];
						if (usefC == 1) SignalTotS6 = SignalTotS6 + fCsignal[i];
					}
					if (sector[i] == 7) {
						if (usefC == 0) SignalTotS7 = SignalTotS7 + signal[i];
						if (usefC == 1) SignalTotS7 = SignalTotS7 + fCsignal[i];
					}
					if (sector[i] == 8) {
						if (usefC == 0) SignalTotS8 = SignalTotS8 + signal[i];
						if (usefC == 1) SignalTotS8 = SignalTotS8 + fCsignal[i];
					}
					if (sector[i] == 9) {
						if (usefC == 0) SignalTotS9 = SignalTotS9 + signal[i];
						if (usefC == 1) SignalTotS9 = SignalTotS9 + fCsignal[i];
					}
					if (sector[i] == 10) {
						if (usefC == 0) SignalTotS10 = SignalTotS10 + signal[i];
						if (usefC == 1) SignalTotS10 = SignalTotS10 + fCsignal[i];
					}
					if (sector[i] == 11) {
						if (usefC == 0) SignalTotS11 = SignalTotS11 + signal[i];
						if (usefC == 1) SignalTotS11 = SignalTotS11 + fCsignal[i];
					}
					if (sector[i] == 12) {
						if (usefC == 0) SignalTotS12 = SignalTotS12 + signal[i];
						if (usefC == 1) SignalTotS12 = SignalTotS12 + fCsignal[i];
					}
					if (sector[i] == 13) {
						if (usefC == 0) SignalTotS13 = SignalTotS13 + signal[i];
						if (usefC == 1) SignalTotS13 = SignalTotS13 + fCsignal[i];
					}
					if (sector[i] == 14) {
						if (usefC == 0) SignalTotS14 = SignalTotS14 + signal[i];
						if (usefC == 1) SignalTotS14 = SignalTotS14 + fCsignal[i];
					}
					if (sector[i] == 15) {
						if (usefC == 0) SignalTotS15 = SignalTotS15 + signal[i];
						if (usefC == 1) SignalTotS15 = SignalTotS15 + fCsignal[i];
					}
					if (sector[i] == 16) {
						if (usefC == 0) SignalTotS16 = SignalTotS16 + signal[i];
						if (usefC == 1) SignalTotS16 = SignalTotS16 + fCsignal[i];
					}
				}
      			}
		}
		if (range == 27) {
			// calculate total fCsignal in CASTOR
			// modules 2-7
      			for (int i=16;i<112;i++) {
				bool channel1 = false;
				if (module[i] == 6 && sector[i] == 16) channel1 = true;
      				if (channel[i] != 11 && channel[i] != 12 && !channel1) {
					if (usefC == 0) SignalTot = SignalTot + signal[i];
					if (usefC == 1) SignalTot = SignalTot + fCsignal[i];
					if (module[i] == 1) {
						if (usefC == 0) SignalTotM1 = SignalTotM1 + signal[i];
						if (usefC == 1) SignalTotM1 = SignalTotM1 + fCsignal[i];
					}
					if (module[i] == 2) {
						if (usefC == 0) SignalTotM2 = SignalTotM2 + signal[i];
						if (usefC == 1) SignalTotM2 = SignalTotM2 + fCsignal[i];
					}
					if (module[i] == 3) {
						if (usefC == 0) SignalTotM3 = SignalTotM3 + signal[i];
						if (usefC == 1) SignalTotM3 = SignalTotM3 + fCsignal[i];
					}
					if (module[i] == 4) {
						if (usefC == 0) SignalTotM4 = SignalTotM4 + signal[i];
						if (usefC == 1) SignalTotM4 = SignalTotM4 + fCsignal[i];
					}
					if (module[i] == 5) {
						if (usefC == 0) SignalTotM5 = SignalTotM5 + signal[i];
						if (usefC == 1) SignalTotM5 = SignalTotM5 + fCsignal[i];
					}
					if (module[i] == 6) {
						if (usefC == 0) SignalTotM6 = SignalTotM6 + signal[i];
						if (usefC == 1) SignalTotM6 = SignalTotM6 + fCsignal[i];
					}
					if (module[i] == 7) {
						if (usefC == 0) SignalTotM7 = SignalTotM7 + signal[i];
						if (usefC == 1) SignalTotM7 = SignalTotM7 + fCsignal[i];
					}
					if (module[i] == 8) {
						if (usefC == 0) SignalTotM8 = SignalTotM8 + signal[i];
						if (usefC == 1) SignalTotM8 = SignalTotM8 + fCsignal[i];
					}
					if (module[i] == 9) {
						if (usefC == 0) SignalTotM9 = SignalTotM9 + signal[i];
						if (usefC == 1) SignalTotM9 = SignalTotM9 + fCsignal[i];
					}
					if (module[i] == 10) {
						if (usefC == 0) SignalTotM10 = SignalTotM10 + signal[i];
						if (usefC == 1) SignalTotM10 = SignalTotM10 + fCsignal[i];
					}
					if (module[i] == 11) {
						if (usefC == 0) SignalTotM11 = SignalTotM11 + signal[i];
						if (usefC == 1) SignalTotM11 = SignalTotM11 + fCsignal[i];
					}
					if (module[i] == 12) {
						if (usefC == 0) SignalTotM12 = SignalTotM12 + signal[i];
						if (usefC == 1) SignalTotM12 = SignalTotM12 + fCsignal[i];
					}
					if (module[i] == 13) {
						if (usefC == 0) SignalTotM13 = SignalTotM13 + signal[i];
						if (usefC == 1) SignalTotM13 = SignalTotM13 + fCsignal[i];
					}
					if (module[i] == 14) {
						if (usefC == 0) SignalTotM14 = SignalTotM14 + signal[i];
						if (usefC == 1) SignalTotM14 = SignalTotM14 + fCsignal[i];
					}
					// sectors
					if (sector[i] == 1) {
						if (usefC == 0) SignalTotS1 = SignalTotS1 + signal[i];
						if (usefC == 1) SignalTotS1 = SignalTotS1 + fCsignal[i];
					}
					if (sector[i] == 2) {
						if (usefC == 0) SignalTotS2 = SignalTotS2 + signal[i];
						if (usefC == 1) SignalTotS2 = SignalTotS2 + fCsignal[i];
					}
					if (sector[i] == 3) {
						if (usefC == 0) SignalTotS3 = SignalTotS3 + signal[i];
						if (usefC == 1) SignalTotS3 = SignalTotS3 + fCsignal[i];
					}
					if (sector[i] == 4) {
						if (usefC == 0) SignalTotS4 = SignalTotS4 + signal[i];
						if (usefC == 1) SignalTotS4 = SignalTotS4 + fCsignal[i];
					}
					if (sector[i] == 5) {
						if (usefC == 0) SignalTotS5 = SignalTotS5 + signal[i];
						if (usefC == 1) SignalTotS5 = SignalTotS5 + fCsignal[i];
					}
					if (sector[i] == 6) {
						if (usefC == 0) SignalTotS6 = SignalTotS6 + signal[i];
						if (usefC == 1) SignalTotS6 = SignalTotS6 + fCsignal[i];
					}
					if (sector[i] == 7) {
						if (usefC == 0) SignalTotS7 = SignalTotS7 + signal[i];
						if (usefC == 1) SignalTotS7 = SignalTotS7 + fCsignal[i];
					}
					if (sector[i] == 8) {
						if (usefC == 0) SignalTotS8 = SignalTotS8 + signal[i];
						if (usefC == 1) SignalTotS8 = SignalTotS8 + fCsignal[i];
					}
					if (sector[i] == 9) {
						if (usefC == 0) SignalTotS9 = SignalTotS9 + signal[i];
						if (usefC == 1) SignalTotS9 = SignalTotS9 + fCsignal[i];
					}
					if (sector[i] == 10) {
						if (usefC == 0) SignalTotS10 = SignalTotS10 + signal[i];
						if (usefC == 1) SignalTotS10 = SignalTotS10 + fCsignal[i];
					}
					if (sector[i] == 11) {
						if (usefC == 0) SignalTotS11 = SignalTotS11 + signal[i];
						if (usefC == 1) SignalTotS11 = SignalTotS11 + fCsignal[i];
					}
					if (sector[i] == 12) {
						if (usefC == 0) SignalTotS12 = SignalTotS12 + signal[i];
						if (usefC == 1) SignalTotS12 = SignalTotS12 + fCsignal[i];
					}
					if (sector[i] == 13) {
						if (usefC == 0) SignalTotS13 = SignalTotS13 + signal[i];
						if (usefC == 1) SignalTotS13 = SignalTotS13 + fCsignal[i];
					}
					if (sector[i] == 14) {
						if (usefC == 0) SignalTotS14 = SignalTotS14 + signal[i];
						if (usefC == 1) SignalTotS14 = SignalTotS14 + fCsignal[i];
					}
					if (sector[i] == 15) {
						if (usefC == 0) SignalTotS15 = SignalTotS15 + signal[i];
						if (usefC == 1) SignalTotS15 = SignalTotS15 + fCsignal[i];
					}
					if (sector[i] == 16) {
						if (usefC == 0) SignalTotS16 = SignalTotS16 + signal[i];
						if (usefC == 1) SignalTotS16 = SignalTotS16 + fCsignal[i];
					}
				}
      			}
		}
		if (range == 19) {
			// calculate total fCsignal in CASTOR
			// modules 1-9
      			for (int i=0;i<144;i++) {
				bool channel1 = false;
				bool channel2 = false;
				bool channel3 = false;
				if (module[i] == 6 && sector[i] == 16) channel1 = true;
				if (module[i] == 8 && sector[i] == 3) channel2 = true;
				if (module[i] == 8 && sector[i] == 8) channel3 = true;
				if (channel[i] != 11 && channel[i] != 12 && !channel1 && !channel2 && !channel3) {
					if (usefC == 0) SignalTot = SignalTot + signal[i];
					if (usefC == 1) SignalTot = SignalTot + fCsignal[i];
					if (module[i] == 1) {
						if (usefC == 0) SignalTotM1 = SignalTotM1 + signal[i];
						if (usefC == 1) SignalTotM1 = SignalTotM1 + fCsignal[i];
					}
					if (module[i] == 2) {
						if (usefC == 0) SignalTotM2 = SignalTotM2 + signal[i];
						if (usefC == 1) SignalTotM2 = SignalTotM2 + fCsignal[i];
					}
					if (module[i] == 3) {
						if (usefC == 0) SignalTotM3 = SignalTotM3 + signal[i];
						if (usefC == 1) SignalTotM3 = SignalTotM3 + fCsignal[i];
					}
					if (module[i] == 4) {
						if (usefC == 0) SignalTotM4 = SignalTotM4 + signal[i];
						if (usefC == 1) SignalTotM4 = SignalTotM4 + fCsignal[i];
					}
					if (module[i] == 5) {
						if (usefC == 0) SignalTotM5 = SignalTotM5 + signal[i];
						if (usefC == 1) SignalTotM5 = SignalTotM5 + fCsignal[i];
					}
					if (module[i] == 6) {
						if (usefC == 0) SignalTotM6 = SignalTotM6 + signal[i];
						if (usefC == 1) SignalTotM6 = SignalTotM6 + fCsignal[i];
					}
					if (module[i] == 7) {
						if (usefC == 0) SignalTotM7 = SignalTotM7 + signal[i];
						if (usefC == 1) SignalTotM7 = SignalTotM7 + fCsignal[i];
					}
					if (module[i] == 8) {
						if (usefC == 0) SignalTotM8 = SignalTotM8 + signal[i];
						if (usefC == 1) SignalTotM8 = SignalTotM8 + fCsignal[i];
					}
					if (module[i] == 9) {
						if (usefC == 0) SignalTotM9 = SignalTotM9 + signal[i];
						if (usefC == 1) SignalTotM9 = SignalTotM9 + fCsignal[i];
					}
					if (module[i] == 10) {
						if (usefC == 0) SignalTotM10 = SignalTotM10 + signal[i];
						if (usefC == 1) SignalTotM10 = SignalTotM10 + fCsignal[i];
					}
					if (module[i] == 11) {
						if (usefC == 0) SignalTotM11 = SignalTotM11 + signal[i];
						if (usefC == 1) SignalTotM11 = SignalTotM11 + fCsignal[i];
					}
					if (module[i] == 12) {
						if (usefC == 0) SignalTotM12 = SignalTotM12 + signal[i];
						if (usefC == 1) SignalTotM12 = SignalTotM12 + fCsignal[i];
					}
					if (module[i] == 13) {
						if (usefC == 0) SignalTotM13 = SignalTotM13 + signal[i];
						if (usefC == 1) SignalTotM13 = SignalTotM13 + fCsignal[i];
					}
					if (module[i] == 14) {
						if (usefC == 0) SignalTotM14 = SignalTotM14 + signal[i];
						if (usefC == 1) SignalTotM14 = SignalTotM14 + fCsignal[i];
					}
					// sectors
					if (sector[i] == 1) {
						if (usefC == 0) SignalTotS1 = SignalTotS1 + signal[i];
						if (usefC == 1) SignalTotS1 = SignalTotS1 + fCsignal[i];
					}
					if (sector[i] == 2) {
						if (usefC == 0) SignalTotS2 = SignalTotS2 + signal[i];
						if (usefC == 1) SignalTotS2 = SignalTotS2 + fCsignal[i];
					}
					if (sector[i] == 3) {
						if (usefC == 0) SignalTotS3 = SignalTotS3 + signal[i];
						if (usefC == 1) SignalTotS3 = SignalTotS3 + fCsignal[i];
					}
					if (sector[i] == 4) {
						if (usefC == 0) SignalTotS4 = SignalTotS4 + signal[i];
						if (usefC == 1) SignalTotS4 = SignalTotS4 + fCsignal[i];
					}
					if (sector[i] == 5) {
						if (usefC == 0) SignalTotS5 = SignalTotS5 + signal[i];
						if (usefC == 1) SignalTotS5 = SignalTotS5 + fCsignal[i];
					}
					if (sector[i] == 6) {
						if (usefC == 0) SignalTotS6 = SignalTotS6 + signal[i];
						if (usefC == 1) SignalTotS6 = SignalTotS6 + fCsignal[i];
					}
					if (sector[i] == 7) {
						if (usefC == 0) SignalTotS7 = SignalTotS7 + signal[i];
						if (usefC == 1) SignalTotS7 = SignalTotS7 + fCsignal[i];
					}
					if (sector[i] == 8) {
						if (usefC == 0) SignalTotS8 = SignalTotS8 + signal[i];
						if (usefC == 1) SignalTotS8 = SignalTotS8 + fCsignal[i];
					}
					if (sector[i] == 9) {
						if (usefC == 0) SignalTotS9 = SignalTotS9 + signal[i];
						if (usefC == 1) SignalTotS9 = SignalTotS9 + fCsignal[i];
					}
					if (sector[i] == 10) {
						if (usefC == 0) SignalTotS10 = SignalTotS10 + signal[i];
						if (usefC == 1) SignalTotS10 = SignalTotS10 + fCsignal[i];
					}
					if (sector[i] == 11) {
						if (usefC == 0) SignalTotS11 = SignalTotS11 + signal[i];
						if (usefC == 1) SignalTotS11 = SignalTotS11 + fCsignal[i];
					}
					if (sector[i] == 12) {
						if (usefC == 0) SignalTotS12 = SignalTotS12 + signal[i];
						if (usefC == 1) SignalTotS12 = SignalTotS12 + fCsignal[i];
					}
					if (sector[i] == 13) {
						if (usefC == 0) SignalTotS13 = SignalTotS13 + signal[i];
						if (usefC == 1) SignalTotS13 = SignalTotS13 + fCsignal[i];
					}
					if (sector[i] == 14) {
						if (usefC == 0) SignalTotS14 = SignalTotS14 + signal[i];
						if (usefC == 1) SignalTotS14 = SignalTotS14 + fCsignal[i];
					}
					if (sector[i] == 15) {
						if (usefC == 0) SignalTotS15 = SignalTotS15 + signal[i];
						if (usefC == 1) SignalTotS15 = SignalTotS15 + fCsignal[i];
					}
					if (sector[i] == 16) {
						if (usefC == 0) SignalTotS16 = SignalTotS16 + signal[i];
						if (usefC == 1) SignalTotS16 = SignalTotS16 + fCsignal[i];
					}
				}	
      			}
		}
      
      		// fill total signal histograms
      		h2360SignalTot->Fill(SignalTot);
				h2360SignalM1->Fill(SignalTotM1);
				h2360SignalM2->Fill(SignalTotM2);
				h2360SignalM3->Fill(SignalTotM3);
				h2360SignalM4->Fill(SignalTotM4);
				h2360SignalM5->Fill(SignalTotM5);
				h2360SignalM6->Fill(SignalTotM6);
				h2360SignalM7->Fill(SignalTotM7);
				h2360SignalM8->Fill(SignalTotM8);
				h2360SignalM9->Fill(SignalTotM9);
				h2360SignalM10->Fill(SignalTotM10);
				h2360SignalM11->Fill(SignalTotM11);
				h2360SignalM12->Fill(SignalTotM12);
				h2360SignalM13->Fill(SignalTotM13);
				h2360SignalM14->Fill(SignalTotM14);
				h2360SignalS1->Fill(SignalTotS1);
				h2360SignalS2->Fill(SignalTotS2);
				h2360SignalS3->Fill(SignalTotS3);
				h2360SignalS4->Fill(SignalTotS4);
				h2360SignalS5->Fill(SignalTotS5);
				h2360SignalS6->Fill(SignalTotS6);
				h2360SignalS7->Fill(SignalTotS7);
				h2360SignalS8->Fill(SignalTotS8);
				h2360SignalS9->Fill(SignalTotS9);
				h2360SignalS10->Fill(SignalTotS10);
				h2360SignalS11->Fill(SignalTotS11);
				h2360SignalS12->Fill(SignalTotS12);
				h2360SignalS13->Fill(SignalTotS13);
				h2360SignalS14->Fill(SignalTotS14);
				h2360SignalS15->Fill(SignalTotS15);
				h2360SignalS16->Fill(SignalTotS16);
		
		if (useList == 0) {    
      			if (isCaloInclusive == 1) n2360CaloInclusive += 1;
      			if (isCaloDijet == 1) n2360CaloDijet += 1;
      			if (isPFInclusive == 1) n2360PFInclusive += 1;
      			if (isPFDijet == 1) n2360PFDijet += 1;
			if (isPFDijet == 1) {
				h2360SignalTotPFDijet->Fill(SignalTot);
				h2360SignalPFDijetM1->Fill(SignalTotM1);
				h2360SignalPFDijetM2->Fill(SignalTotM2);
				h2360SignalPFDijetM3->Fill(SignalTotM3);
				h2360SignalPFDijetM4->Fill(SignalTotM4);
				h2360SignalPFDijetM5->Fill(SignalTotM5);
				h2360SignalPFDijetM6->Fill(SignalTotM6);
				h2360SignalPFDijetM7->Fill(SignalTotM7);
				h2360SignalPFDijetM8->Fill(SignalTotM8);
				h2360SignalPFDijetM9->Fill(SignalTotM9);
				h2360SignalPFDijetM10->Fill(SignalTotM10);
				h2360SignalPFDijetM11->Fill(SignalTotM11);
				h2360SignalPFDijetM12->Fill(SignalTotM12);
				h2360SignalPFDijetM13->Fill(SignalTotM13);
				h2360SignalPFDijetM14->Fill(SignalTotM14);
				h2360SignalPFDijetS1->Fill(SignalTotS1);
				h2360SignalPFDijetS2->Fill(SignalTotS2);
				h2360SignalPFDijetS3->Fill(SignalTotS3);
				h2360SignalPFDijetS4->Fill(SignalTotS4);
				h2360SignalPFDijetS5->Fill(SignalTotS5);
				h2360SignalPFDijetS6->Fill(SignalTotS6);
				h2360SignalPFDijetS7->Fill(SignalTotS7);
				h2360SignalPFDijetS8->Fill(SignalTotS8);
				h2360SignalPFDijetS9->Fill(SignalTotS9);
				h2360SignalPFDijetS10->Fill(SignalTotS10);
				h2360SignalPFDijetS11->Fill(SignalTotS11);
				h2360SignalPFDijetS12->Fill(SignalTotS12);
				h2360SignalPFDijetS13->Fill(SignalTotS13);
				h2360SignalPFDijetS14->Fill(SignalTotS14);
				h2360SignalPFDijetS15->Fill(SignalTotS15);
				h2360SignalPFDijetS16->Fill(SignalTotS16);
			}
      			if (isPFInclusive == 1) h2360SignalTotPFInclusive->Fill(SignalTot);
      			if (isCaloDijet == 1) h2360SignalTotCaloDijet->Fill(SignalTot);
      			if (isCaloInclusive == 1) h2360SignalTotCaloInclusive->Fill(SignalTot);
		}	 
		 
		if (useList == 1) {  
		  	for (int i=0;i<2088;i++) {
			  	if (PFInclusiveList[i][0] == runNumber && PFInclusiveList[i][1] == lumiBlock && PFInclusiveList[i][2] == eventNum) 
				{n2360PFInclusive += 1;h2360SignalTotPFInclusive->Fill(SignalTot);}
		  	}
			for (int i=0;i<531;i++) {
			  	if (PFDijetList[i][0] == runNumber && PFDijetList[i][1] == lumiBlock && PFDijetList[i][2] == eventNum)
				{n2360PFDijet += 1;h2360SignalTotPFDijet->Fill(SignalTot);}
		  	}
			for (int i=0;i<459;i++) {
			  	if (CaloInclusiveList[i][0] == runNumber && CaloInclusiveList[i][1] == lumiBlock && CaloInclusiveList[i][2] ==eventNum) 
				{n2360CaloInclusive += 1;h2360SignalTotCaloInclusive->Fill(SignalTot);}
		  	}
			for (int i=0;i<246;i++) {
			  	if (CaloDijetList[i][0] == runNumber && CaloDijetList[i][1] == lumiBlock && CaloDijetList[i][2] == eventNum)
				{n2360CaloDijet += 1;h2360SignalTotCaloDijet->Fill(SignalTot);}
		  	}
		}
		
		sum2360 = sum2360 + SignalTot;
		if (isPFInclusive == 1) sum2360PFInclusive = sum2360PFInclusive + SignalTot;
		if (isPFDijet == 1) sum2360PFDijet = sum2360PFDijet + SignalTot;
      }
      
      // select run for MC
      if (runNumber == 1 ) {
		
		if (MCevent < 89746) {
		
		// fill channel histos from module 1-6
		for (int i=0;i<96;i++) {
			h900EChannelMC[i]->Fill(fCscale*fCsignal[i]);
			if (isPFDijet == 1) h900EChannelQCDMC[i]->Fill(fCscale*fCsignal[i]);
		}
      
		
		for (int i=0;i<96;i++) {
			for (int j=0;j<6;j++) {
				hMCSlices->Fill(j+0.1,ADC[i][j]);
				hMCSlicesfC->Fill(j+0.1,fC[i][j]);
			}
		}
		
		hMCSlices->Scale(1./96.);
		hMCSlicesfC->Scale(1./96.);
		
		// put fCsignal in histogram for MC
		for (int i=0;i<96;i++) {
			h900channels->Fill(i+0.1,signal[i]);
			
		}	
      
      		// calculate total numbers
      		n900MCEvents = n900MCEvents +1; 
		
		
      		// calculate total signals
       		double SignalTot = 0;
		
		double SignalTotM1 = 0;
		double SignalTotM2 = 0;
		double SignalTotM3 = 0;
		double SignalTotM4 = 0;
		double SignalTotM5 = 0;
		double SignalTotM6 = 0;
		double SignalTotM7 = 0;
		double SignalTotM8 = 0;
		double SignalTotM9 = 0;
		double SignalTotM10 = 0;
		double SignalTotM11 = 0;
		double SignalTotM12 = 0;
		double SignalTotM13 = 0;
		double SignalTotM14 = 0;
		
		double SignalTotS1 = 0;
		double SignalTotS2 = 0;
		double SignalTotS3 = 0;
		double SignalTotS4 = 0;
		double SignalTotS5 = 0;
		double SignalTotS6 = 0;
		double SignalTotS7 = 0;
		double SignalTotS8 = 0;
		double SignalTotS9 = 0;
		double SignalTotS10 = 0;
		double SignalTotS11 = 0;
		double SignalTotS12 = 0;
		double SignalTotS13 = 0;
		double SignalTotS14 = 0;
		double SignalTotS15 = 0;
		double SignalTotS16 = 0;
		
		if (range == 15) {	
      			// calculate total fCscale*fCsignal in CASTOR
			// modules 1-5
      			for (int i=0;i<80;i++) {
      				if (channel[i] != 11 && channel[i] != 12) {
					if (usefC == 0) SignalTot = SignalTot + signal[i];
					if (usefC == 1) SignalTot = SignalTot + fCscale*fCsignal[i];
					if (module[i] == 1) {
						if (usefC == 0) SignalTotM1 = SignalTotM1 + signal[i];
						if (usefC == 1) SignalTotM1 = SignalTotM1 + fCscale*fCsignal[i];
					}
					if (module[i] == 2) {
						if (usefC == 0) SignalTotM2 = SignalTotM2 + signal[i];
						if (usefC == 1) SignalTotM2 = SignalTotM2 + fCscale*fCsignal[i];
					}
					if (module[i] == 3) {
						if (usefC == 0) SignalTotM3 = SignalTotM3 + signal[i];
						if (usefC == 1) SignalTotM3 = SignalTotM3 + fCscale*fCsignal[i];
					}
					if (module[i] == 4) {
						if (usefC == 0) SignalTotM4 = SignalTotM4 + signal[i];
						if (usefC == 1) SignalTotM4 = SignalTotM4 + fCscale*fCsignal[i];
					}
					if (module[i] == 5) {
						if (usefC == 0) SignalTotM5 = SignalTotM5 + signal[i];
						if (usefC == 1) SignalTotM5 = SignalTotM5 + fCscale*fCsignal[i];
					}
					if (module[i] == 6) {
						if (usefC == 0) SignalTotM6 = SignalTotM6 + signal[i];
						if (usefC == 1) SignalTotM6 = SignalTotM6 + fCscale*fCsignal[i];
					}
					if (module[i] == 7) {
						if (usefC == 0) SignalTotM7 = SignalTotM7 + signal[i];
						if (usefC == 1) SignalTotM7 = SignalTotM7 + fCscale*fCsignal[i];
					}
					if (module[i] == 8) {
						if (usefC == 0) SignalTotM8 = SignalTotM8 + signal[i];
						if (usefC == 1) SignalTotM8 = SignalTotM8 + fCscale*fCsignal[i];
					}
					if (module[i] == 9) {
						if (usefC == 0) SignalTotM9 = SignalTotM9 + signal[i];
						if (usefC == 1) SignalTotM9 = SignalTotM9 + fCscale*fCsignal[i];
					}
					if (module[i] == 10) {
						if (usefC == 0) SignalTotM10 = SignalTotM10 + signal[i];
						if (usefC == 1) SignalTotM10 = SignalTotM10 + fCscale*fCsignal[i];
					}
					if (module[i] == 11) {
						if (usefC == 0) SignalTotM11 = SignalTotM11 + signal[i];
						if (usefC == 1) SignalTotM11 = SignalTotM11 + fCscale*fCsignal[i];
					}
					if (module[i] == 12) {
						if (usefC == 0) SignalTotM12 = SignalTotM12 + signal[i];
						if (usefC == 1) SignalTotM12 = SignalTotM12 + fCscale*fCsignal[i];
					}
					if (module[i] == 13) {
						if (usefC == 0) SignalTotM13 = SignalTotM13 + signal[i];
						if (usefC == 1) SignalTotM13 = SignalTotM13 + fCscale*fCsignal[i];
					}
					if (module[i] == 14) {
						if (usefC == 0) SignalTotM14 = SignalTotM14 + signal[i];
						if (usefC == 1) SignalTotM14 = SignalTotM14 + fCscale*fCsignal[i];
					}
					// sectors
					if (sector[i] == 1) {
						if (usefC == 0) SignalTotS1 = SignalTotS1 + signal[i];
						if (usefC == 1) SignalTotS1 = SignalTotS1 + fCscale*fCsignal[i];
					}
					if (sector[i] == 2) {
						if (usefC == 0) SignalTotS2 = SignalTotS2 + signal[i];
						if (usefC == 1) SignalTotS2 = SignalTotS2 + fCscale*fCsignal[i];
					}
					if (sector[i] == 3) {
						if (usefC == 0) SignalTotS3 = SignalTotS3 + signal[i];
						if (usefC == 1) SignalTotS3 = SignalTotS3 + fCscale*fCsignal[i];
					}
					if (sector[i] == 4) {
						if (usefC == 0) SignalTotS4 = SignalTotS4 + signal[i];
						if (usefC == 1) SignalTotS4 = SignalTotS4 + fCscale*fCsignal[i];
					}
					if (sector[i] == 5) {
						if (usefC == 0) SignalTotS5 = SignalTotS5 + signal[i];
						if (usefC == 1) SignalTotS5 = SignalTotS5 + fCscale*fCsignal[i];
					}
					if (sector[i] == 6) {
						if (usefC == 0) SignalTotS6 = SignalTotS6 + signal[i];
						if (usefC == 1) SignalTotS6 = SignalTotS6 + fCscale*fCsignal[i];
					}
					if (sector[i] == 7) {
						if (usefC == 0) SignalTotS7 = SignalTotS7 + signal[i];
						if (usefC == 1) SignalTotS7 = SignalTotS7 + fCscale*fCsignal[i];
					}
					if (sector[i] == 8) {
						if (usefC == 0) SignalTotS8 = SignalTotS8 + signal[i];
						if (usefC == 1) SignalTotS8 = SignalTotS8 + fCscale*fCsignal[i];
					}
					if (sector[i] == 9) {
						if (usefC == 0) SignalTotS9 = SignalTotS9 + signal[i];
						if (usefC == 1) SignalTotS9 = SignalTotS9 + fCscale*fCsignal[i];
					}
					if (sector[i] == 10) {
						if (usefC == 0) SignalTotS10 = SignalTotS10 + signal[i];
						if (usefC == 1) SignalTotS10 = SignalTotS10 + fCscale*fCsignal[i];
					}
					if (sector[i] == 11) {
						if (usefC == 0) SignalTotS11 = SignalTotS11 + signal[i];
						if (usefC == 1) SignalTotS11 = SignalTotS11 + fCscale*fCsignal[i];
					}
					if (sector[i] == 12) {
						if (usefC == 0) SignalTotS12 = SignalTotS12 + signal[i];
						if (usefC == 1) SignalTotS12 = SignalTotS12 + fCscale*fCsignal[i];
					}
					if (sector[i] == 13) {
						if (usefC == 0) SignalTotS13 = SignalTotS13 + signal[i];
						if (usefC == 1) SignalTotS13 = SignalTotS13 + fCscale*fCsignal[i];
					}
					if (sector[i] == 14) {
						if (usefC == 0) SignalTotS14 = SignalTotS14 + signal[i];
						if (usefC == 1) SignalTotS14 = SignalTotS14 + fCscale*fCsignal[i];
					}
					if (sector[i] == 15) {
						if (usefC == 0) SignalTotS15 = SignalTotS15 + signal[i];
						if (usefC == 1) SignalTotS15 = SignalTotS15 + fCscale*fCsignal[i];
					}
					if (sector[i] == 16) {
						if (usefC == 0) SignalTotS16 = SignalTotS16 + signal[i];
						if (usefC == 1) SignalTotS16 = SignalTotS16 + fCscale*fCsignal[i];
					}
				}
      			}
		}
      		if (range == 16) {	
      			// calculate total fCscale*fCsignal in CASTOR
			// modules 1-6
      			for (int i=0;i<96;i++) {
				bool channel1 = false;
				if (module[i] == 6 && sector[i] == 16) channel1 = true;
      				if (channel[i] != 11 && channel[i] != 12 && !channel1) {
					if (usefC == 0) SignalTot = SignalTot + signal[i];
					if (usefC == 1) SignalTot = SignalTot + fCscale*fCsignal[i];
					if (module[i] == 1) {
						if (usefC == 0) SignalTotM1 = SignalTotM1 + signal[i];
						if (usefC == 1) SignalTotM1 = SignalTotM1 + fCscale*fCsignal[i];
					}
					if (module[i] == 2) {
						if (usefC == 0) SignalTotM2 = SignalTotM2 + signal[i];
						if (usefC == 1) SignalTotM2 = SignalTotM2 + fCscale*fCsignal[i];
					}
					if (module[i] == 3) {
						if (usefC == 0) SignalTotM3 = SignalTotM3 + signal[i];
						if (usefC == 1) SignalTotM3 = SignalTotM3 + fCscale*fCsignal[i];
					}
					if (module[i] == 4) {
						if (usefC == 0) SignalTotM4 = SignalTotM4 + signal[i];
						if (usefC == 1) SignalTotM4 = SignalTotM4 + fCscale*fCsignal[i];
					}
					if (module[i] == 5) {
						if (usefC == 0) SignalTotM5 = SignalTotM5 + signal[i];
						if (usefC == 1) SignalTotM5 = SignalTotM5 + fCscale*fCsignal[i];
					}
					if (module[i] == 6) {
						if (usefC == 0) SignalTotM6 = SignalTotM6 + signal[i];
						if (usefC == 1) SignalTotM6 = SignalTotM6 + fCscale*fCsignal[i];
					}
					if (module[i] == 7) {
						if (usefC == 0) SignalTotM7 = SignalTotM7 + signal[i];
						if (usefC == 1) SignalTotM7 = SignalTotM7 + fCscale*fCsignal[i];
					}
					if (module[i] == 8) {
						if (usefC == 0) SignalTotM8 = SignalTotM8 + signal[i];
						if (usefC == 1) SignalTotM8 = SignalTotM8 + fCscale*fCsignal[i];
					}
					if (module[i] == 9) {
						if (usefC == 0) SignalTotM9 = SignalTotM9 + signal[i];
						if (usefC == 1) SignalTotM9 = SignalTotM9 + fCscale*fCsignal[i];
					}
					if (module[i] == 10) {
						if (usefC == 0) SignalTotM10 = SignalTotM10 + signal[i];
						if (usefC == 1) SignalTotM10 = SignalTotM10 + fCscale*fCsignal[i];
					}
					if (module[i] == 11) {
						if (usefC == 0) SignalTotM11 = SignalTotM11 + signal[i];
						if (usefC == 1) SignalTotM11 = SignalTotM11 + fCscale*fCsignal[i];
					}
					if (module[i] == 12) {
						if (usefC == 0) SignalTotM12 = SignalTotM12 + signal[i];
						if (usefC == 1) SignalTotM12 = SignalTotM12 + fCscale*fCsignal[i];
					}
					if (module[i] == 13) {
						if (usefC == 0) SignalTotM13 = SignalTotM13 + signal[i];
						if (usefC == 1) SignalTotM13 = SignalTotM13 + fCscale*fCsignal[i];
					}
					if (module[i] == 14) {
						if (usefC == 0) SignalTotM14 = SignalTotM14 + signal[i];
						if (usefC == 1) SignalTotM14 = SignalTotM14 + fCscale*fCsignal[i];
					}
					// sectors
					if (sector[i] == 1) {
						if (usefC == 0) SignalTotS1 = SignalTotS1 + signal[i];
						if (usefC == 1) SignalTotS1 = SignalTotS1 + fCscale*fCsignal[i];
					}
					if (sector[i] == 2) {
						if (usefC == 0) SignalTotS2 = SignalTotS2 + signal[i];
						if (usefC == 1) SignalTotS2 = SignalTotS2 + fCscale*fCsignal[i];
					}
					if (sector[i] == 3) {
						if (usefC == 0) SignalTotS3 = SignalTotS3 + signal[i];
						if (usefC == 1) SignalTotS3 = SignalTotS3 + fCscale*fCsignal[i];
					}
					if (sector[i] == 4) {
						if (usefC == 0) SignalTotS4 = SignalTotS4 + signal[i];
						if (usefC == 1) SignalTotS4 = SignalTotS4 + fCscale*fCsignal[i];
					}
					if (sector[i] == 5) {
						if (usefC == 0) SignalTotS5 = SignalTotS5 + signal[i];
						if (usefC == 1) SignalTotS5 = SignalTotS5 + fCscale*fCsignal[i];
					}
					if (sector[i] == 6) {
						if (usefC == 0) SignalTotS6 = SignalTotS6 + signal[i];
						if (usefC == 1) SignalTotS6 = SignalTotS6 + fCscale*fCsignal[i];
					}
					if (sector[i] == 7) {
						if (usefC == 0) SignalTotS7 = SignalTotS7 + signal[i];
						if (usefC == 1) SignalTotS7 = SignalTotS7 + fCscale*fCsignal[i];
					}
					if (sector[i] == 8) {
						if (usefC == 0) SignalTotS8 = SignalTotS8 + signal[i];
						if (usefC == 1) SignalTotS8 = SignalTotS8 + fCscale*fCsignal[i];
					}
					if (sector[i] == 9) {
						if (usefC == 0) SignalTotS9 = SignalTotS9 + signal[i];
						if (usefC == 1) SignalTotS9 = SignalTotS9 + fCscale*fCsignal[i];
					}
					if (sector[i] == 10) {
						if (usefC == 0) SignalTotS10 = SignalTotS10 + signal[i];
						if (usefC == 1) SignalTotS10 = SignalTotS10 + fCscale*fCsignal[i];
					}
					if (sector[i] == 11) {
						if (usefC == 0) SignalTotS11 = SignalTotS11 + signal[i];
						if (usefC == 1) SignalTotS11 = SignalTotS11 + fCscale*fCsignal[i];
					}
					if (sector[i] == 12) {
						if (usefC == 0) SignalTotS12 = SignalTotS12 + signal[i];
						if (usefC == 1) SignalTotS12 = SignalTotS12 + fCscale*fCsignal[i];
					}
					if (sector[i] == 13) {
						if (usefC == 0) SignalTotS13 = SignalTotS13 + signal[i];
						if (usefC == 1) SignalTotS13 = SignalTotS13 + fCscale*fCsignal[i];
					}
					if (sector[i] == 14) {
						if (usefC == 0) SignalTotS14 = SignalTotS14 + signal[i];
						if (usefC == 1) SignalTotS14 = SignalTotS14 + fCscale*fCsignal[i];
					}
					if (sector[i] == 15) {
						if (usefC == 0) SignalTotS15 = SignalTotS15 + signal[i];
						if (usefC == 1) SignalTotS15 = SignalTotS15 + fCscale*fCsignal[i];
					}
					if (sector[i] == 16) {
						if (usefC == 0) SignalTotS16 = SignalTotS16 + signal[i];
						if (usefC == 1) SignalTotS16 = SignalTotS16 + fCscale*fCsignal[i];
					}
				}
      			}
		}
		if (range == 27) {
			// calculate total fCscale*fCsignal in CASTOR
			// modules 2-7
      			for (int i=16;i<112;i++) {
				bool channel1 = false;
				if (module[i] == 6 && sector[i] == 16) channel1 = true;
      				if (channel[i] != 11 && channel[i] != 12 && !channel1) {
					if (usefC == 0) SignalTot = SignalTot + signal[i];
					if (usefC == 1) SignalTot = SignalTot + fCscale*fCsignal[i];
					if (module[i] == 1) {
						if (usefC == 0) SignalTotM1 = SignalTotM1 + signal[i];
						if (usefC == 1) SignalTotM1 = SignalTotM1 + fCscale*fCsignal[i];
					}
					if (module[i] == 2) {
						if (usefC == 0) SignalTotM2 = SignalTotM2 + signal[i];
						if (usefC == 1) SignalTotM2 = SignalTotM2 + fCscale*fCsignal[i];
					}
					if (module[i] == 3) {
						if (usefC == 0) SignalTotM3 = SignalTotM3 + signal[i];
						if (usefC == 1) SignalTotM3 = SignalTotM3 + fCscale*fCsignal[i];
					}
					if (module[i] == 4) {
						if (usefC == 0) SignalTotM4 = SignalTotM4 + signal[i];
						if (usefC == 1) SignalTotM4 = SignalTotM4 + fCscale*fCsignal[i];
					}
					if (module[i] == 5) {
						if (usefC == 0) SignalTotM5 = SignalTotM5 + signal[i];
						if (usefC == 1) SignalTotM5 = SignalTotM5 + fCscale*fCsignal[i];
					}
					if (module[i] == 6) {
						if (usefC == 0) SignalTotM6 = SignalTotM6 + signal[i];
						if (usefC == 1) SignalTotM6 = SignalTotM6 + fCscale*fCsignal[i];
					}
					if (module[i] == 7) {
						if (usefC == 0) SignalTotM7 = SignalTotM7 + signal[i];
						if (usefC == 1) SignalTotM7 = SignalTotM7 + fCscale*fCsignal[i];
					}
					if (module[i] == 8) {
						if (usefC == 0) SignalTotM8 = SignalTotM8 + signal[i];
						if (usefC == 1) SignalTotM8 = SignalTotM8 + fCscale*fCsignal[i];
					}
					if (module[i] == 9) {
						if (usefC == 0) SignalTotM9 = SignalTotM9 + signal[i];
						if (usefC == 1) SignalTotM9 = SignalTotM9 + fCscale*fCsignal[i];
					}
					if (module[i] == 10) {
						if (usefC == 0) SignalTotM10 = SignalTotM10 + signal[i];
						if (usefC == 1) SignalTotM10 = SignalTotM10 + fCscale*fCsignal[i];
					}
					if (module[i] == 11) {
						if (usefC == 0) SignalTotM11 = SignalTotM11 + signal[i];
						if (usefC == 1) SignalTotM11 = SignalTotM11 + fCscale*fCsignal[i];
					}
					if (module[i] == 12) {
						if (usefC == 0) SignalTotM12 = SignalTotM12 + signal[i];
						if (usefC == 1) SignalTotM12 = SignalTotM12 + fCscale*fCsignal[i];
					}
					if (module[i] == 13) {
						if (usefC == 0) SignalTotM13 = SignalTotM13 + signal[i];
						if (usefC == 1) SignalTotM13 = SignalTotM13 + fCscale*fCsignal[i];
					}
					if (module[i] == 14) {
						if (usefC == 0) SignalTotM14 = SignalTotM14 + signal[i];
						if (usefC == 1) SignalTotM14 = SignalTotM14 + fCscale*fCsignal[i];
					}
					// sectors
					if (sector[i] == 1) {
						if (usefC == 0) SignalTotS1 = SignalTotS1 + signal[i];
						if (usefC == 1) SignalTotS1 = SignalTotS1 + fCscale*fCsignal[i];
					}
					if (sector[i] == 2) {
						if (usefC == 0) SignalTotS2 = SignalTotS2 + signal[i];
						if (usefC == 1) SignalTotS2 = SignalTotS2 + fCscale*fCsignal[i];
					}
					if (sector[i] == 3) {
						if (usefC == 0) SignalTotS3 = SignalTotS3 + signal[i];
						if (usefC == 1) SignalTotS3 = SignalTotS3 + fCscale*fCsignal[i];
					}
					if (sector[i] == 4) {
						if (usefC == 0) SignalTotS4 = SignalTotS4 + signal[i];
						if (usefC == 1) SignalTotS4 = SignalTotS4 + fCscale*fCsignal[i];
					}
					if (sector[i] == 5) {
						if (usefC == 0) SignalTotS5 = SignalTotS5 + signal[i];
						if (usefC == 1) SignalTotS5 = SignalTotS5 + fCscale*fCsignal[i];
					}
					if (sector[i] == 6) {
						if (usefC == 0) SignalTotS6 = SignalTotS6 + signal[i];
						if (usefC == 1) SignalTotS6 = SignalTotS6 + fCscale*fCsignal[i];
					}
					if (sector[i] == 7) {
						if (usefC == 0) SignalTotS7 = SignalTotS7 + signal[i];
						if (usefC == 1) SignalTotS7 = SignalTotS7 + fCscale*fCsignal[i];
					}
					if (sector[i] == 8) {
						if (usefC == 0) SignalTotS8 = SignalTotS8 + signal[i];
						if (usefC == 1) SignalTotS8 = SignalTotS8 + fCscale*fCsignal[i];
					}
					if (sector[i] == 9) {
						if (usefC == 0) SignalTotS9 = SignalTotS9 + signal[i];
						if (usefC == 1) SignalTotS9 = SignalTotS9 + fCscale*fCsignal[i];
					}
					if (sector[i] == 10) {
						if (usefC == 0) SignalTotS10 = SignalTotS10 + signal[i];
						if (usefC == 1) SignalTotS10 = SignalTotS10 + fCscale*fCsignal[i];
					}
					if (sector[i] == 11) {
						if (usefC == 0) SignalTotS11 = SignalTotS11 + signal[i];
						if (usefC == 1) SignalTotS11 = SignalTotS11 + fCscale*fCsignal[i];
					}
					if (sector[i] == 12) {
						if (usefC == 0) SignalTotS12 = SignalTotS12 + signal[i];
						if (usefC == 1) SignalTotS12 = SignalTotS12 + fCscale*fCsignal[i];
					}
					if (sector[i] == 13) {
						if (usefC == 0) SignalTotS13 = SignalTotS13 + signal[i];
						if (usefC == 1) SignalTotS13 = SignalTotS13 + fCscale*fCsignal[i];
					}
					if (sector[i] == 14) {
						if (usefC == 0) SignalTotS14 = SignalTotS14 + signal[i];
						if (usefC == 1) SignalTotS14 = SignalTotS14 + fCscale*fCsignal[i];
					}
					if (sector[i] == 15) {
						if (usefC == 0) SignalTotS15 = SignalTotS15 + signal[i];
						if (usefC == 1) SignalTotS15 = SignalTotS15 + fCscale*fCsignal[i];
					}
					if (sector[i] == 16) {
						if (usefC == 0) SignalTotS16 = SignalTotS16 + signal[i];
						if (usefC == 1) SignalTotS16 = SignalTotS16 + fCscale*fCsignal[i];
					}
				}
      			}
		}
		if (range == 19) {
			// calculate total fCscale*fCsignal in CASTOR
			// modules 1-9
      			for (int i=0;i<144;i++) {
				bool channel1 = false;
				bool channel2 = false;
				bool channel3 = false;
				if (module[i] == 6 && sector[i] == 16) channel1 = true;
				if (module[i] == 8 && sector[i] == 3) channel2 = true;
				if (module[i] == 8 && sector[i] == 8) channel3 = true;
				if (channel[i] != 11 && channel[i] != 12 && !channel1 && !channel2 && !channel3) {
					if (usefC == 0) SignalTot = SignalTot + signal[i];
					if (usefC == 1) SignalTot = SignalTot + fCscale*fCsignal[i];
					if (module[i] == 1) {
						if (usefC == 0) SignalTotM1 = SignalTotM1 + signal[i];
						if (usefC == 1) SignalTotM1 = SignalTotM1 + fCscale*fCsignal[i];
					}
					if (module[i] == 2) {
						if (usefC == 0) SignalTotM2 = SignalTotM2 + signal[i];
						if (usefC == 1) SignalTotM2 = SignalTotM2 + fCscale*fCsignal[i];
					}
					if (module[i] == 3) {
						if (usefC == 0) SignalTotM3 = SignalTotM3 + signal[i];
						if (usefC == 1) SignalTotM3 = SignalTotM3 + fCscale*fCsignal[i];
					}
					if (module[i] == 4) {
						if (usefC == 0) SignalTotM4 = SignalTotM4 + signal[i];
						if (usefC == 1) SignalTotM4 = SignalTotM4 + fCscale*fCsignal[i];
					}
					if (module[i] == 5) {
						if (usefC == 0) SignalTotM5 = SignalTotM5 + signal[i];
						if (usefC == 1) SignalTotM5 = SignalTotM5 + fCscale*fCsignal[i];
					}
					if (module[i] == 6) {
						if (usefC == 0) SignalTotM6 = SignalTotM6 + signal[i];
						if (usefC == 1) SignalTotM6 = SignalTotM6 + fCscale*fCsignal[i];
					}
					if (module[i] == 7) {
						if (usefC == 0) SignalTotM7 = SignalTotM7 + signal[i];
						if (usefC == 1) SignalTotM7 = SignalTotM7 + fCscale*fCsignal[i];
					}
					if (module[i] == 8) {
						if (usefC == 0) SignalTotM8 = SignalTotM8 + signal[i];
						if (usefC == 1) SignalTotM8 = SignalTotM8 + fCscale*fCsignal[i];
					}
					if (module[i] == 9) {
						if (usefC == 0) SignalTotM9 = SignalTotM9 + signal[i];
						if (usefC == 1) SignalTotM9 = SignalTotM9 + fCscale*fCsignal[i];
					}
					if (module[i] == 10) {
						if (usefC == 0) SignalTotM10 = SignalTotM10 + signal[i];
						if (usefC == 1) SignalTotM10 = SignalTotM10 + fCscale*fCsignal[i];
					}
					if (module[i] == 11) {
						if (usefC == 0) SignalTotM11 = SignalTotM11 + signal[i];
						if (usefC == 1) SignalTotM11 = SignalTotM11 + fCscale*fCsignal[i];
					}
					if (module[i] == 12) {
						if (usefC == 0) SignalTotM12 = SignalTotM12 + signal[i];
						if (usefC == 1) SignalTotM12 = SignalTotM12 + fCscale*fCsignal[i];
					}
					if (module[i] == 13) {
						if (usefC == 0) SignalTotM13 = SignalTotM13 + signal[i];
						if (usefC == 1) SignalTotM13 = SignalTotM13 + fCscale*fCsignal[i];
					}
					if (module[i] == 14) {
						if (usefC == 0) SignalTotM14 = SignalTotM14 + signal[i];
						if (usefC == 1) SignalTotM14 = SignalTotM14 + fCscale*fCsignal[i];
					}
					// sectors
					if (sector[i] == 1) {
						if (usefC == 0) SignalTotS1 = SignalTotS1 + signal[i];
						if (usefC == 1) SignalTotS1 = SignalTotS1 + fCscale*fCsignal[i];
					}
					if (sector[i] == 2) {
						if (usefC == 0) SignalTotS2 = SignalTotS2 + signal[i];
						if (usefC == 1) SignalTotS2 = SignalTotS2 + fCscale*fCsignal[i];
					}
					if (sector[i] == 3) {
						if (usefC == 0) SignalTotS3 = SignalTotS3 + signal[i];
						if (usefC == 1) SignalTotS3 = SignalTotS3 + fCscale*fCsignal[i];
					}
					if (sector[i] == 4) {
						if (usefC == 0) SignalTotS4 = SignalTotS4 + signal[i];
						if (usefC == 1) SignalTotS4 = SignalTotS4 + fCscale*fCsignal[i];
					}
					if (sector[i] == 5) {
						if (usefC == 0) SignalTotS5 = SignalTotS5 + signal[i];
						if (usefC == 1) SignalTotS5 = SignalTotS5 + fCscale*fCsignal[i];
					}
					if (sector[i] == 6) {
						if (usefC == 0) SignalTotS6 = SignalTotS6 + signal[i];
						if (usefC == 1) SignalTotS6 = SignalTotS6 + fCscale*fCsignal[i];
					}
					if (sector[i] == 7) {
						if (usefC == 0) SignalTotS7 = SignalTotS7 + signal[i];
						if (usefC == 1) SignalTotS7 = SignalTotS7 + fCscale*fCsignal[i];
					}
					if (sector[i] == 8) {
						if (usefC == 0) SignalTotS8 = SignalTotS8 + signal[i];
						if (usefC == 1) SignalTotS8 = SignalTotS8 + fCscale*fCsignal[i];
					}
					if (sector[i] == 9) {
						if (usefC == 0) SignalTotS9 = SignalTotS9 + signal[i];
						if (usefC == 1) SignalTotS9 = SignalTotS9 + fCscale*fCsignal[i];
					}
					if (sector[i] == 10) {
						if (usefC == 0) SignalTotS10 = SignalTotS10 + signal[i];
						if (usefC == 1) SignalTotS10 = SignalTotS10 + fCscale*fCsignal[i];
					}
					if (sector[i] == 11) {
						if (usefC == 0) SignalTotS11 = SignalTotS11 + signal[i];
						if (usefC == 1) SignalTotS11 = SignalTotS11 + fCscale*fCsignal[i];
					}
					if (sector[i] == 12) {
						if (usefC == 0) SignalTotS12 = SignalTotS12 + signal[i];
						if (usefC == 1) SignalTotS12 = SignalTotS12 + fCscale*fCsignal[i];
					}
					if (sector[i] == 13) {
						if (usefC == 0) SignalTotS13 = SignalTotS13 + signal[i];
						if (usefC == 1) SignalTotS13 = SignalTotS13 + fCscale*fCsignal[i];
					}
					if (sector[i] == 14) {
						if (usefC == 0) SignalTotS14 = SignalTotS14 + signal[i];
						if (usefC == 1) SignalTotS14 = SignalTotS14 + fCscale*fCsignal[i];
					}
					if (sector[i] == 15) {
						if (usefC == 0) SignalTotS15 = SignalTotS15 + signal[i];
						if (usefC == 1) SignalTotS15 = SignalTotS15 + fCscale*fCsignal[i];
					}
					if (sector[i] == 16) {
						if (usefC == 0) SignalTotS16 = SignalTotS16 + signal[i];
						if (usefC == 1) SignalTotS16 = SignalTotS16 + fCscale*fCsignal[i];
					}
				}	
      			}
		}
      
      		// fill total signal histograms
      		h900MCSignalTot->Fill(SignalTot);
				h900MCSignalM1->Fill(SignalTotM1);
				h900MCSignalM2->Fill(SignalTotM2);
				h900MCSignalM3->Fill(SignalTotM3);
				h900MCSignalM4->Fill(SignalTotM4);
				h900MCSignalM5->Fill(SignalTotM5);
				h900MCSignalM6->Fill(SignalTotM6);
				h900MCSignalM7->Fill(SignalTotM7);
				h900MCSignalM8->Fill(SignalTotM8);
				h900MCSignalM9->Fill(SignalTotM9);
				h900MCSignalM10->Fill(SignalTotM10);
				h900MCSignalM11->Fill(SignalTotM11);
				h900MCSignalM12->Fill(SignalTotM12);
				h900MCSignalM13->Fill(SignalTotM13);
				h900MCSignalM14->Fill(SignalTotM14);
				h900MCSignalS1->Fill(SignalTotS1);
				h900MCSignalS2->Fill(SignalTotS2);
				h900MCSignalS3->Fill(SignalTotS3);
				h900MCSignalS4->Fill(SignalTotS4);
				h900MCSignalS5->Fill(SignalTotS5);
				h900MCSignalS6->Fill(SignalTotS6);
				h900MCSignalS7->Fill(SignalTotS7);
				h900MCSignalS8->Fill(SignalTotS8);
				h900MCSignalS9->Fill(SignalTotS9);
				h900MCSignalS10->Fill(SignalTotS10);
				h900MCSignalS11->Fill(SignalTotS11);
				h900MCSignalS12->Fill(SignalTotS12);
				h900MCSignalS13->Fill(SignalTotS13);
				h900MCSignalS14->Fill(SignalTotS14);
				h900MCSignalS15->Fill(SignalTotS15);
				h900MCSignalS16->Fill(SignalTotS16);
		
		if (useList == 0) {    
      			if (isCaloInclusive == 1) n900MCCaloInclusive += 1;
      			if (isCaloDijet == 1) n900MCCaloDijet += 1;
      			if (isPFInclusive == 1) n900MCPFInclusive += 1;
      			if (isPFDijet == 1) n900MCPFDijet += 1;
			if (isPFDijet == 1) {
				h900MCSignalTotPFDijet->Fill(SignalTot);
				h900MCSignalPFDijetM1->Fill(SignalTotM1);
				h900MCSignalPFDijetM2->Fill(SignalTotM2);
				h900MCSignalPFDijetM3->Fill(SignalTotM3);
				h900MCSignalPFDijetM4->Fill(SignalTotM4);
				h900MCSignalPFDijetM5->Fill(SignalTotM5);
				h900MCSignalPFDijetM6->Fill(SignalTotM6);
				h900MCSignalPFDijetM7->Fill(SignalTotM7);
				h900MCSignalPFDijetM8->Fill(SignalTotM8);
				h900MCSignalPFDijetM9->Fill(SignalTotM9);
				h900MCSignalPFDijetM10->Fill(SignalTotM10);
				h900MCSignalPFDijetM11->Fill(SignalTotM11);
				h900MCSignalPFDijetM12->Fill(SignalTotM12);
				h900MCSignalPFDijetM13->Fill(SignalTotM13);
				h900MCSignalPFDijetM14->Fill(SignalTotM14);
				h900MCSignalPFDijetS1->Fill(SignalTotS1);
				h900MCSignalPFDijetS2->Fill(SignalTotS2);
				h900MCSignalPFDijetS3->Fill(SignalTotS3);
				h900MCSignalPFDijetS4->Fill(SignalTotS4);
				h900MCSignalPFDijetS5->Fill(SignalTotS5);
				h900MCSignalPFDijetS6->Fill(SignalTotS6);
				h900MCSignalPFDijetS7->Fill(SignalTotS7);
				h900MCSignalPFDijetS8->Fill(SignalTotS8);
				h900MCSignalPFDijetS9->Fill(SignalTotS9);
				h900MCSignalPFDijetS10->Fill(SignalTotS10);
				h900MCSignalPFDijetS11->Fill(SignalTotS11);
				h900MCSignalPFDijetS12->Fill(SignalTotS12);
				h900MCSignalPFDijetS13->Fill(SignalTotS13);
				h900MCSignalPFDijetS14->Fill(SignalTotS14);
				h900MCSignalPFDijetS15->Fill(SignalTotS15);
				h900MCSignalPFDijetS16->Fill(SignalTotS16);
			}
      			if (isPFInclusive == 1) h900MCSignalTotPFInclusive->Fill(SignalTot);
      			if (isCaloDijet == 1) h900MCSignalTotCaloDijet->Fill(SignalTot);
      			if (isCaloInclusive == 1) h900MCSignalTotCaloInclusive->Fill(SignalTot);
		}	 
		 
		if (useList == 1) {  
		  	// this is MC
		}
		
		sum900MC = sum900MC + SignalTot;
		if (isPFInclusive == 1) sum900MCPFInclusive = sum900MCPFInclusive + SignalTot;
		if (isPFDijet == 1) sum900MCPFDijet = sum900MCPFDijet + SignalTot;
		
		} else {
		// 2360 GeV
		
		// fill channel histos from module 1-6
		for (int i=0;i<96;i++) {
			h2360EChannelMC[i]->Fill(fCsignal[i]);
			if (isPFDijet == 1) h2360EChannelQCDMC[i]->Fill(fCsignal[i]);
		}
		
		// put fCsignal in histogram for MC
		for (int i=0;i<96;i++) {
			h2360channels->Fill(i+0.1,signal[i]);
			
		}
		
		// calculate total numbers
      		n2360MCEvents = n2360MCEvents +1; 
		
		// calculate total signals
       		double SignalTot = 0;
		
		double SignalTotM1 = 0;
		double SignalTotM2 = 0;
		double SignalTotM3 = 0;
		double SignalTotM4 = 0;
		double SignalTotM5 = 0;
		double SignalTotM6 = 0;
		double SignalTotM7 = 0;
		double SignalTotM8 = 0;
		double SignalTotM9 = 0;
		double SignalTotM10 = 0;
		double SignalTotM11 = 0;
		double SignalTotM12 = 0;
		double SignalTotM13 = 0;
		double SignalTotM14 = 0;
		
		double SignalTotS1 = 0;
		double SignalTotS2 = 0;
		double SignalTotS3 = 0;
		double SignalTotS4 = 0;
		double SignalTotS5 = 0;
		double SignalTotS6 = 0;
		double SignalTotS7 = 0;
		double SignalTotS8 = 0;
		double SignalTotS9 = 0;
		double SignalTotS10 = 0;
		double SignalTotS11 = 0;
		double SignalTotS12 = 0;
		double SignalTotS13 = 0;
		double SignalTotS14 = 0;
		double SignalTotS15 = 0;
		double SignalTotS16 = 0;
		
		if (range == 15) {	
      			// calculate total fCscale*fCsignal in CASTOR
			// modules 1-5
      			for (int i=0;i<80;i++) {
      				if (channel[i] != 11 && channel[i] != 12) {
					if (usefC == 0) SignalTot = SignalTot + signal[i];
					if (usefC == 1) SignalTot = SignalTot + fCscale*fCsignal[i];
					if (module[i] == 1) {
						if (usefC == 0) SignalTotM1 = SignalTotM1 + signal[i];
						if (usefC == 1) SignalTotM1 = SignalTotM1 + fCscale*fCsignal[i];
					}
					if (module[i] == 2) {
						if (usefC == 0) SignalTotM2 = SignalTotM2 + signal[i];
						if (usefC == 1) SignalTotM2 = SignalTotM2 + fCscale*fCsignal[i];
					}
					if (module[i] == 3) {
						if (usefC == 0) SignalTotM3 = SignalTotM3 + signal[i];
						if (usefC == 1) SignalTotM3 = SignalTotM3 + fCscale*fCsignal[i];
					}
					if (module[i] == 4) {
						if (usefC == 0) SignalTotM4 = SignalTotM4 + signal[i];
						if (usefC == 1) SignalTotM4 = SignalTotM4 + fCscale*fCsignal[i];
					}
					if (module[i] == 5) {
						if (usefC == 0) SignalTotM5 = SignalTotM5 + signal[i];
						if (usefC == 1) SignalTotM5 = SignalTotM5 + fCscale*fCsignal[i];
					}
					if (module[i] == 6) {
						if (usefC == 0) SignalTotM6 = SignalTotM6 + signal[i];
						if (usefC == 1) SignalTotM6 = SignalTotM6 + fCscale*fCsignal[i];
					}
					if (module[i] == 7) {
						if (usefC == 0) SignalTotM7 = SignalTotM7 + signal[i];
						if (usefC == 1) SignalTotM7 = SignalTotM7 + fCscale*fCsignal[i];
					}
					if (module[i] == 8) {
						if (usefC == 0) SignalTotM8 = SignalTotM8 + signal[i];
						if (usefC == 1) SignalTotM8 = SignalTotM8 + fCscale*fCsignal[i];
					}
					if (module[i] == 9) {
						if (usefC == 0) SignalTotM9 = SignalTotM9 + signal[i];
						if (usefC == 1) SignalTotM9 = SignalTotM9 + fCscale*fCsignal[i];
					}
					if (module[i] == 10) {
						if (usefC == 0) SignalTotM10 = SignalTotM10 + signal[i];
						if (usefC == 1) SignalTotM10 = SignalTotM10 + fCscale*fCsignal[i];
					}
					if (module[i] == 11) {
						if (usefC == 0) SignalTotM11 = SignalTotM11 + signal[i];
						if (usefC == 1) SignalTotM11 = SignalTotM11 + fCscale*fCsignal[i];
					}
					if (module[i] == 12) {
						if (usefC == 0) SignalTotM12 = SignalTotM12 + signal[i];
						if (usefC == 1) SignalTotM12 = SignalTotM12 + fCscale*fCsignal[i];
					}
					if (module[i] == 13) {
						if (usefC == 0) SignalTotM13 = SignalTotM13 + signal[i];
						if (usefC == 1) SignalTotM13 = SignalTotM13 + fCscale*fCsignal[i];
					}
					if (module[i] == 14) {
						if (usefC == 0) SignalTotM14 = SignalTotM14 + signal[i];
						if (usefC == 1) SignalTotM14 = SignalTotM14 + fCscale*fCsignal[i];
					}
					// sectors
					if (sector[i] == 1) {
						if (usefC == 0) SignalTotS1 = SignalTotS1 + signal[i];
						if (usefC == 1) SignalTotS1 = SignalTotS1 + fCscale*fCsignal[i];
					}
					if (sector[i] == 2) {
						if (usefC == 0) SignalTotS2 = SignalTotS2 + signal[i];
						if (usefC == 1) SignalTotS2 = SignalTotS2 + fCscale*fCsignal[i];
					}
					if (sector[i] == 3) {
						if (usefC == 0) SignalTotS3 = SignalTotS3 + signal[i];
						if (usefC == 1) SignalTotS3 = SignalTotS3 + fCscale*fCsignal[i];
					}
					if (sector[i] == 4) {
						if (usefC == 0) SignalTotS4 = SignalTotS4 + signal[i];
						if (usefC == 1) SignalTotS4 = SignalTotS4 + fCscale*fCsignal[i];
					}
					if (sector[i] == 5) {
						if (usefC == 0) SignalTotS5 = SignalTotS5 + signal[i];
						if (usefC == 1) SignalTotS5 = SignalTotS5 + fCscale*fCsignal[i];
					}
					if (sector[i] == 6) {
						if (usefC == 0) SignalTotS6 = SignalTotS6 + signal[i];
						if (usefC == 1) SignalTotS6 = SignalTotS6 + fCscale*fCsignal[i];
					}
					if (sector[i] == 7) {
						if (usefC == 0) SignalTotS7 = SignalTotS7 + signal[i];
						if (usefC == 1) SignalTotS7 = SignalTotS7 + fCscale*fCsignal[i];
					}
					if (sector[i] == 8) {
						if (usefC == 0) SignalTotS8 = SignalTotS8 + signal[i];
						if (usefC == 1) SignalTotS8 = SignalTotS8 + fCscale*fCsignal[i];
					}
					if (sector[i] == 9) {
						if (usefC == 0) SignalTotS9 = SignalTotS9 + signal[i];
						if (usefC == 1) SignalTotS9 = SignalTotS9 + fCscale*fCsignal[i];
					}
					if (sector[i] == 10) {
						if (usefC == 0) SignalTotS10 = SignalTotS10 + signal[i];
						if (usefC == 1) SignalTotS10 = SignalTotS10 + fCscale*fCsignal[i];
					}
					if (sector[i] == 11) {
						if (usefC == 0) SignalTotS11 = SignalTotS11 + signal[i];
						if (usefC == 1) SignalTotS11 = SignalTotS11 + fCscale*fCsignal[i];
					}
					if (sector[i] == 12) {
						if (usefC == 0) SignalTotS12 = SignalTotS12 + signal[i];
						if (usefC == 1) SignalTotS12 = SignalTotS12 + fCscale*fCsignal[i];
					}
					if (sector[i] == 13) {
						if (usefC == 0) SignalTotS13 = SignalTotS13 + signal[i];
						if (usefC == 1) SignalTotS13 = SignalTotS13 + fCscale*fCsignal[i];
					}
					if (sector[i] == 14) {
						if (usefC == 0) SignalTotS14 = SignalTotS14 + signal[i];
						if (usefC == 1) SignalTotS14 = SignalTotS14 + fCscale*fCsignal[i];
					}
					if (sector[i] == 15) {
						if (usefC == 0) SignalTotS15 = SignalTotS15 + signal[i];
						if (usefC == 1) SignalTotS15 = SignalTotS15 + fCscale*fCsignal[i];
					}
					if (sector[i] == 16) {
						if (usefC == 0) SignalTotS16 = SignalTotS16 + signal[i];
						if (usefC == 1) SignalTotS16 = SignalTotS16 + fCscale*fCsignal[i];
					}
				}
      			}
		}
      		if (range == 16) {	
      			// calculate total fCscale*fCsignal in CASTOR
			// modules 1-6
      			for (int i=0;i<96;i++) {
				bool channel1 = false;
				if (module[i] == 6 && sector[i] == 16) channel1 = true;
      				if (channel[i] != 11 && channel[i] != 12 && !channel1) {
					if (usefC == 0) SignalTot = SignalTot + signal[i];
					if (usefC == 1) SignalTot = SignalTot + fCscale*fCsignal[i];
					if (module[i] == 1) {
						if (usefC == 0) SignalTotM1 = SignalTotM1 + signal[i];
						if (usefC == 1) SignalTotM1 = SignalTotM1 + fCscale*fCsignal[i];
					}
					if (module[i] == 2) {
						if (usefC == 0) SignalTotM2 = SignalTotM2 + signal[i];
						if (usefC == 1) SignalTotM2 = SignalTotM2 + fCscale*fCsignal[i];
					}
					if (module[i] == 3) {
						if (usefC == 0) SignalTotM3 = SignalTotM3 + signal[i];
						if (usefC == 1) SignalTotM3 = SignalTotM3 + fCscale*fCsignal[i];
					}
					if (module[i] == 4) {
						if (usefC == 0) SignalTotM4 = SignalTotM4 + signal[i];
						if (usefC == 1) SignalTotM4 = SignalTotM4 + fCscale*fCsignal[i];
					}
					if (module[i] == 5) {
						if (usefC == 0) SignalTotM5 = SignalTotM5 + signal[i];
						if (usefC == 1) SignalTotM5 = SignalTotM5 + fCscale*fCsignal[i];
					}
					if (module[i] == 6) {
						if (usefC == 0) SignalTotM6 = SignalTotM6 + signal[i];
						if (usefC == 1) SignalTotM6 = SignalTotM6 + fCscale*fCsignal[i];
					}
					if (module[i] == 7) {
						if (usefC == 0) SignalTotM7 = SignalTotM7 + signal[i];
						if (usefC == 1) SignalTotM7 = SignalTotM7 + fCscale*fCsignal[i];
					}
					if (module[i] == 8) {
						if (usefC == 0) SignalTotM8 = SignalTotM8 + signal[i];
						if (usefC == 1) SignalTotM8 = SignalTotM8 + fCscale*fCsignal[i];
					}
					if (module[i] == 9) {
						if (usefC == 0) SignalTotM9 = SignalTotM9 + signal[i];
						if (usefC == 1) SignalTotM9 = SignalTotM9 + fCscale*fCsignal[i];
					}
					if (module[i] == 10) {
						if (usefC == 0) SignalTotM10 = SignalTotM10 + signal[i];
						if (usefC == 1) SignalTotM10 = SignalTotM10 + fCscale*fCsignal[i];
					}
					if (module[i] == 11) {
						if (usefC == 0) SignalTotM11 = SignalTotM11 + signal[i];
						if (usefC == 1) SignalTotM11 = SignalTotM11 + fCscale*fCsignal[i];
					}
					if (module[i] == 12) {
						if (usefC == 0) SignalTotM12 = SignalTotM12 + signal[i];
						if (usefC == 1) SignalTotM12 = SignalTotM12 + fCscale*fCsignal[i];
					}
					if (module[i] == 13) {
						if (usefC == 0) SignalTotM13 = SignalTotM13 + signal[i];
						if (usefC == 1) SignalTotM13 = SignalTotM13 + fCscale*fCsignal[i];
					}
					if (module[i] == 14) {
						if (usefC == 0) SignalTotM14 = SignalTotM14 + signal[i];
						if (usefC == 1) SignalTotM14 = SignalTotM14 + fCscale*fCsignal[i];
					}
					// sectors
					if (sector[i] == 1) {
						if (usefC == 0) SignalTotS1 = SignalTotS1 + signal[i];
						if (usefC == 1) SignalTotS1 = SignalTotS1 + fCscale*fCsignal[i];
					}
					if (sector[i] == 2) {
						if (usefC == 0) SignalTotS2 = SignalTotS2 + signal[i];
						if (usefC == 1) SignalTotS2 = SignalTotS2 + fCscale*fCsignal[i];
					}
					if (sector[i] == 3) {
						if (usefC == 0) SignalTotS3 = SignalTotS3 + signal[i];
						if (usefC == 1) SignalTotS3 = SignalTotS3 + fCscale*fCsignal[i];
					}
					if (sector[i] == 4) {
						if (usefC == 0) SignalTotS4 = SignalTotS4 + signal[i];
						if (usefC == 1) SignalTotS4 = SignalTotS4 + fCscale*fCsignal[i];
					}
					if (sector[i] == 5) {
						if (usefC == 0) SignalTotS5 = SignalTotS5 + signal[i];
						if (usefC == 1) SignalTotS5 = SignalTotS5 + fCscale*fCsignal[i];
					}
					if (sector[i] == 6) {
						if (usefC == 0) SignalTotS6 = SignalTotS6 + signal[i];
						if (usefC == 1) SignalTotS6 = SignalTotS6 + fCscale*fCsignal[i];
					}
					if (sector[i] == 7) {
						if (usefC == 0) SignalTotS7 = SignalTotS7 + signal[i];
						if (usefC == 1) SignalTotS7 = SignalTotS7 + fCscale*fCsignal[i];
					}
					if (sector[i] == 8) {
						if (usefC == 0) SignalTotS8 = SignalTotS8 + signal[i];
						if (usefC == 1) SignalTotS8 = SignalTotS8 + fCscale*fCsignal[i];
					}
					if (sector[i] == 9) {
						if (usefC == 0) SignalTotS9 = SignalTotS9 + signal[i];
						if (usefC == 1) SignalTotS9 = SignalTotS9 + fCscale*fCsignal[i];
					}
					if (sector[i] == 10) {
						if (usefC == 0) SignalTotS10 = SignalTotS10 + signal[i];
						if (usefC == 1) SignalTotS10 = SignalTotS10 + fCscale*fCsignal[i];
					}
					if (sector[i] == 11) {
						if (usefC == 0) SignalTotS11 = SignalTotS11 + signal[i];
						if (usefC == 1) SignalTotS11 = SignalTotS11 + fCscale*fCsignal[i];
					}
					if (sector[i] == 12) {
						if (usefC == 0) SignalTotS12 = SignalTotS12 + signal[i];
						if (usefC == 1) SignalTotS12 = SignalTotS12 + fCscale*fCsignal[i];
					}
					if (sector[i] == 13) {
						if (usefC == 0) SignalTotS13 = SignalTotS13 + signal[i];
						if (usefC == 1) SignalTotS13 = SignalTotS13 + fCscale*fCsignal[i];
					}
					if (sector[i] == 14) {
						if (usefC == 0) SignalTotS14 = SignalTotS14 + signal[i];
						if (usefC == 1) SignalTotS14 = SignalTotS14 + fCscale*fCsignal[i];
					}
					if (sector[i] == 15) {
						if (usefC == 0) SignalTotS15 = SignalTotS15 + signal[i];
						if (usefC == 1) SignalTotS15 = SignalTotS15 + fCscale*fCsignal[i];
					}
					if (sector[i] == 16) {
						if (usefC == 0) SignalTotS16 = SignalTotS16 + signal[i];
						if (usefC == 1) SignalTotS16 = SignalTotS16 + fCscale*fCsignal[i];
					}
				}
      			}
		}
		if (range == 27) {
			// calculate total fCscale*fCsignal in CASTOR
			// modules 2-7
      			for (int i=16;i<112;i++) {
				bool channel1 = false;
				if (module[i] == 6 && sector[i] == 16) channel1 = true;
      				if (channel[i] != 11 && channel[i] != 12 && !channel1) {
					if (usefC == 0) SignalTot = SignalTot + signal[i];
					if (usefC == 1) SignalTot = SignalTot + fCscale*fCsignal[i];
					if (module[i] == 1) {
						if (usefC == 0) SignalTotM1 = SignalTotM1 + signal[i];
						if (usefC == 1) SignalTotM1 = SignalTotM1 + fCscale*fCsignal[i];
					}
					if (module[i] == 2) {
						if (usefC == 0) SignalTotM2 = SignalTotM2 + signal[i];
						if (usefC == 1) SignalTotM2 = SignalTotM2 + fCscale*fCsignal[i];
					}
					if (module[i] == 3) {
						if (usefC == 0) SignalTotM3 = SignalTotM3 + signal[i];
						if (usefC == 1) SignalTotM3 = SignalTotM3 + fCscale*fCsignal[i];
					}
					if (module[i] == 4) {
						if (usefC == 0) SignalTotM4 = SignalTotM4 + signal[i];
						if (usefC == 1) SignalTotM4 = SignalTotM4 + fCscale*fCsignal[i];
					}
					if (module[i] == 5) {
						if (usefC == 0) SignalTotM5 = SignalTotM5 + signal[i];
						if (usefC == 1) SignalTotM5 = SignalTotM5 + fCscale*fCsignal[i];
					}
					if (module[i] == 6) {
						if (usefC == 0) SignalTotM6 = SignalTotM6 + signal[i];
						if (usefC == 1) SignalTotM6 = SignalTotM6 + fCscale*fCsignal[i];
					}
					if (module[i] == 7) {
						if (usefC == 0) SignalTotM7 = SignalTotM7 + signal[i];
						if (usefC == 1) SignalTotM7 = SignalTotM7 + fCscale*fCsignal[i];
					}
					if (module[i] == 8) {
						if (usefC == 0) SignalTotM8 = SignalTotM8 + signal[i];
						if (usefC == 1) SignalTotM8 = SignalTotM8 + fCscale*fCsignal[i];
					}
					if (module[i] == 9) {
						if (usefC == 0) SignalTotM9 = SignalTotM9 + signal[i];
						if (usefC == 1) SignalTotM9 = SignalTotM9 + fCscale*fCsignal[i];
					}
					if (module[i] == 10) {
						if (usefC == 0) SignalTotM10 = SignalTotM10 + signal[i];
						if (usefC == 1) SignalTotM10 = SignalTotM10 + fCscale*fCsignal[i];
					}
					if (module[i] == 11) {
						if (usefC == 0) SignalTotM11 = SignalTotM11 + signal[i];
						if (usefC == 1) SignalTotM11 = SignalTotM11 + fCscale*fCsignal[i];
					}
					if (module[i] == 12) {
						if (usefC == 0) SignalTotM12 = SignalTotM12 + signal[i];
						if (usefC == 1) SignalTotM12 = SignalTotM12 + fCscale*fCsignal[i];
					}
					if (module[i] == 13) {
						if (usefC == 0) SignalTotM13 = SignalTotM13 + signal[i];
						if (usefC == 1) SignalTotM13 = SignalTotM13 + fCscale*fCsignal[i];
					}
					if (module[i] == 14) {
						if (usefC == 0) SignalTotM14 = SignalTotM14 + signal[i];
						if (usefC == 1) SignalTotM14 = SignalTotM14 + fCscale*fCsignal[i];
					}
					// sectors
					if (sector[i] == 1) {
						if (usefC == 0) SignalTotS1 = SignalTotS1 + signal[i];
						if (usefC == 1) SignalTotS1 = SignalTotS1 + fCscale*fCsignal[i];
					}
					if (sector[i] == 2) {
						if (usefC == 0) SignalTotS2 = SignalTotS2 + signal[i];
						if (usefC == 1) SignalTotS2 = SignalTotS2 + fCscale*fCsignal[i];
					}
					if (sector[i] == 3) {
						if (usefC == 0) SignalTotS3 = SignalTotS3 + signal[i];
						if (usefC == 1) SignalTotS3 = SignalTotS3 + fCscale*fCsignal[i];
					}
					if (sector[i] == 4) {
						if (usefC == 0) SignalTotS4 = SignalTotS4 + signal[i];
						if (usefC == 1) SignalTotS4 = SignalTotS4 + fCscale*fCsignal[i];
					}
					if (sector[i] == 5) {
						if (usefC == 0) SignalTotS5 = SignalTotS5 + signal[i];
						if (usefC == 1) SignalTotS5 = SignalTotS5 + fCscale*fCsignal[i];
					}
					if (sector[i] == 6) {
						if (usefC == 0) SignalTotS6 = SignalTotS6 + signal[i];
						if (usefC == 1) SignalTotS6 = SignalTotS6 + fCscale*fCsignal[i];
					}
					if (sector[i] == 7) {
						if (usefC == 0) SignalTotS7 = SignalTotS7 + signal[i];
						if (usefC == 1) SignalTotS7 = SignalTotS7 + fCscale*fCsignal[i];
					}
					if (sector[i] == 8) {
						if (usefC == 0) SignalTotS8 = SignalTotS8 + signal[i];
						if (usefC == 1) SignalTotS8 = SignalTotS8 + fCscale*fCsignal[i];
					}
					if (sector[i] == 9) {
						if (usefC == 0) SignalTotS9 = SignalTotS9 + signal[i];
						if (usefC == 1) SignalTotS9 = SignalTotS9 + fCscale*fCsignal[i];
					}
					if (sector[i] == 10) {
						if (usefC == 0) SignalTotS10 = SignalTotS10 + signal[i];
						if (usefC == 1) SignalTotS10 = SignalTotS10 + fCscale*fCsignal[i];
					}
					if (sector[i] == 11) {
						if (usefC == 0) SignalTotS11 = SignalTotS11 + signal[i];
						if (usefC == 1) SignalTotS11 = SignalTotS11 + fCscale*fCsignal[i];
					}
					if (sector[i] == 12) {
						if (usefC == 0) SignalTotS12 = SignalTotS12 + signal[i];
						if (usefC == 1) SignalTotS12 = SignalTotS12 + fCscale*fCsignal[i];
					}
					if (sector[i] == 13) {
						if (usefC == 0) SignalTotS13 = SignalTotS13 + signal[i];
						if (usefC == 1) SignalTotS13 = SignalTotS13 + fCscale*fCsignal[i];
					}
					if (sector[i] == 14) {
						if (usefC == 0) SignalTotS14 = SignalTotS14 + signal[i];
						if (usefC == 1) SignalTotS14 = SignalTotS14 + fCscale*fCsignal[i];
					}
					if (sector[i] == 15) {
						if (usefC == 0) SignalTotS15 = SignalTotS15 + signal[i];
						if (usefC == 1) SignalTotS15 = SignalTotS15 + fCscale*fCsignal[i];
					}
					if (sector[i] == 16) {
						if (usefC == 0) SignalTotS16 = SignalTotS16 + signal[i];
						if (usefC == 1) SignalTotS16 = SignalTotS16 + fCscale*fCsignal[i];
					}
				}
      			}
		}
		if (range == 19) {
			// calculate total fCscale*fCsignal in CASTOR
			// modules 1-9
      			for (int i=0;i<144;i++) {
				bool channel1 = false;
				bool channel2 = false;
				bool channel3 = false;
				if (module[i] == 6 && sector[i] == 16) channel1 = true;
				if (module[i] == 8 && sector[i] == 3) channel2 = true;
				if (module[i] == 8 && sector[i] == 8) channel3 = true;
				if (channel[i] != 11 && channel[i] != 12 && !channel1 && !channel2 && !channel3) {
					if (usefC == 0) SignalTot = SignalTot + signal[i];
					if (usefC == 1) SignalTot = SignalTot + fCscale*fCsignal[i];
					if (module[i] == 1) {
						if (usefC == 0) SignalTotM1 = SignalTotM1 + signal[i];
						if (usefC == 1) SignalTotM1 = SignalTotM1 + fCscale*fCsignal[i];
					}
					if (module[i] == 2) {
						if (usefC == 0) SignalTotM2 = SignalTotM2 + signal[i];
						if (usefC == 1) SignalTotM2 = SignalTotM2 + fCscale*fCsignal[i];
					}
					if (module[i] == 3) {
						if (usefC == 0) SignalTotM3 = SignalTotM3 + signal[i];
						if (usefC == 1) SignalTotM3 = SignalTotM3 + fCscale*fCsignal[i];
					}
					if (module[i] == 4) {
						if (usefC == 0) SignalTotM4 = SignalTotM4 + signal[i];
						if (usefC == 1) SignalTotM4 = SignalTotM4 + fCscale*fCsignal[i];
					}
					if (module[i] == 5) {
						if (usefC == 0) SignalTotM5 = SignalTotM5 + signal[i];
						if (usefC == 1) SignalTotM5 = SignalTotM5 + fCscale*fCsignal[i];
					}
					if (module[i] == 6) {
						if (usefC == 0) SignalTotM6 = SignalTotM6 + signal[i];
						if (usefC == 1) SignalTotM6 = SignalTotM6 + fCscale*fCsignal[i];
					}
					if (module[i] == 7) {
						if (usefC == 0) SignalTotM7 = SignalTotM7 + signal[i];
						if (usefC == 1) SignalTotM7 = SignalTotM7 + fCscale*fCsignal[i];
					}
					if (module[i] == 8) {
						if (usefC == 0) SignalTotM8 = SignalTotM8 + signal[i];
						if (usefC == 1) SignalTotM8 = SignalTotM8 + fCscale*fCsignal[i];
					}
					if (module[i] == 9) {
						if (usefC == 0) SignalTotM9 = SignalTotM9 + signal[i];
						if (usefC == 1) SignalTotM9 = SignalTotM9 + fCscale*fCsignal[i];
					}
					if (module[i] == 10) {
						if (usefC == 0) SignalTotM10 = SignalTotM10 + signal[i];
						if (usefC == 1) SignalTotM10 = SignalTotM10 + fCscale*fCsignal[i];
					}
					if (module[i] == 11) {
						if (usefC == 0) SignalTotM11 = SignalTotM11 + signal[i];
						if (usefC == 1) SignalTotM11 = SignalTotM11 + fCscale*fCsignal[i];
					}
					if (module[i] == 12) {
						if (usefC == 0) SignalTotM12 = SignalTotM12 + signal[i];
						if (usefC == 1) SignalTotM12 = SignalTotM12 + fCscale*fCsignal[i];
					}
					if (module[i] == 13) {
						if (usefC == 0) SignalTotM13 = SignalTotM13 + signal[i];
						if (usefC == 1) SignalTotM13 = SignalTotM13 + fCscale*fCsignal[i];
					}
					if (module[i] == 14) {
						if (usefC == 0) SignalTotM14 = SignalTotM14 + signal[i];
						if (usefC == 1) SignalTotM14 = SignalTotM14 + fCscale*fCsignal[i];
					}
					// sectors
					if (sector[i] == 1) {
						if (usefC == 0) SignalTotS1 = SignalTotS1 + signal[i];
						if (usefC == 1) SignalTotS1 = SignalTotS1 + fCscale*fCsignal[i];
					}
					if (sector[i] == 2) {
						if (usefC == 0) SignalTotS2 = SignalTotS2 + signal[i];
						if (usefC == 1) SignalTotS2 = SignalTotS2 + fCscale*fCsignal[i];
					}
					if (sector[i] == 3) {
						if (usefC == 0) SignalTotS3 = SignalTotS3 + signal[i];
						if (usefC == 1) SignalTotS3 = SignalTotS3 + fCscale*fCsignal[i];
					}
					if (sector[i] == 4) {
						if (usefC == 0) SignalTotS4 = SignalTotS4 + signal[i];
						if (usefC == 1) SignalTotS4 = SignalTotS4 + fCscale*fCsignal[i];
					}
					if (sector[i] == 5) {
						if (usefC == 0) SignalTotS5 = SignalTotS5 + signal[i];
						if (usefC == 1) SignalTotS5 = SignalTotS5 + fCscale*fCsignal[i];
					}
					if (sector[i] == 6) {
						if (usefC == 0) SignalTotS6 = SignalTotS6 + signal[i];
						if (usefC == 1) SignalTotS6 = SignalTotS6 + fCscale*fCsignal[i];
					}
					if (sector[i] == 7) {
						if (usefC == 0) SignalTotS7 = SignalTotS7 + signal[i];
						if (usefC == 1) SignalTotS7 = SignalTotS7 + fCscale*fCsignal[i];
					}
					if (sector[i] == 8) {
						if (usefC == 0) SignalTotS8 = SignalTotS8 + signal[i];
						if (usefC == 1) SignalTotS8 = SignalTotS8 + fCscale*fCsignal[i];
					}
					if (sector[i] == 9) {
						if (usefC == 0) SignalTotS9 = SignalTotS9 + signal[i];
						if (usefC == 1) SignalTotS9 = SignalTotS9 + fCscale*fCsignal[i];
					}
					if (sector[i] == 10) {
						if (usefC == 0) SignalTotS10 = SignalTotS10 + signal[i];
						if (usefC == 1) SignalTotS10 = SignalTotS10 + fCscale*fCsignal[i];
					}
					if (sector[i] == 11) {
						if (usefC == 0) SignalTotS11 = SignalTotS11 + signal[i];
						if (usefC == 1) SignalTotS11 = SignalTotS11 + fCscale*fCsignal[i];
					}
					if (sector[i] == 12) {
						if (usefC == 0) SignalTotS12 = SignalTotS12 + signal[i];
						if (usefC == 1) SignalTotS12 = SignalTotS12 + fCscale*fCsignal[i];
					}
					if (sector[i] == 13) {
						if (usefC == 0) SignalTotS13 = SignalTotS13 + signal[i];
						if (usefC == 1) SignalTotS13 = SignalTotS13 + fCscale*fCsignal[i];
					}
					if (sector[i] == 14) {
						if (usefC == 0) SignalTotS14 = SignalTotS14 + signal[i];
						if (usefC == 1) SignalTotS14 = SignalTotS14 + fCscale*fCsignal[i];
					}
					if (sector[i] == 15) {
						if (usefC == 0) SignalTotS15 = SignalTotS15 + signal[i];
						if (usefC == 1) SignalTotS15 = SignalTotS15 + fCscale*fCsignal[i];
					}
					if (sector[i] == 16) {
						if (usefC == 0) SignalTotS16 = SignalTotS16 + signal[i];
						if (usefC == 1) SignalTotS16 = SignalTotS16 + fCscale*fCsignal[i];
					}
				}	
      			}
		}
      
      		// fill total signal histograms
      		h2360MCSignalTot->Fill(SignalTot);
				h2360MCSignalM1->Fill(SignalTotM1);
				h2360MCSignalM2->Fill(SignalTotM2);
				h2360MCSignalM3->Fill(SignalTotM3);
				h2360MCSignalM4->Fill(SignalTotM4);
				h2360MCSignalM5->Fill(SignalTotM5);
				h2360MCSignalM6->Fill(SignalTotM6);
				h2360MCSignalM7->Fill(SignalTotM7);
				h2360MCSignalM8->Fill(SignalTotM8);
				h2360MCSignalM9->Fill(SignalTotM9);
				h2360MCSignalM10->Fill(SignalTotM10);
				h2360MCSignalM11->Fill(SignalTotM11);
				h2360MCSignalM12->Fill(SignalTotM12);
				h2360MCSignalM13->Fill(SignalTotM13);
				h2360MCSignalM14->Fill(SignalTotM14);
				h2360MCSignalS1->Fill(SignalTotS1);
				h2360MCSignalS2->Fill(SignalTotS2);
				h2360MCSignalS3->Fill(SignalTotS3);
				h2360MCSignalS4->Fill(SignalTotS4);
				h2360MCSignalS5->Fill(SignalTotS5);
				h2360MCSignalS6->Fill(SignalTotS6);
				h2360MCSignalS7->Fill(SignalTotS7);
				h2360MCSignalS8->Fill(SignalTotS8);
				h2360MCSignalS9->Fill(SignalTotS9);
				h2360MCSignalS10->Fill(SignalTotS10);
				h2360MCSignalS11->Fill(SignalTotS11);
				h2360MCSignalS12->Fill(SignalTotS12);
				h2360MCSignalS13->Fill(SignalTotS13);
				h2360MCSignalS14->Fill(SignalTotS14);
				h2360MCSignalS15->Fill(SignalTotS15);
				h2360MCSignalS16->Fill(SignalTotS16);
		
		if (useList == 0) {    
      			if (isCaloInclusive == 1) n2360MCCaloInclusive += 1;
      			if (isCaloDijet == 1) n2360MCCaloDijet += 1;
      			if (isPFInclusive == 1) n2360MCPFInclusive += 1;
      			if (isPFDijet == 1) n2360MCPFDijet += 1;
			if (isPFDijet == 1) {
				h2360MCSignalTotPFDijet->Fill(SignalTot);
				h2360MCSignalPFDijetM1->Fill(SignalTotM1);
				h2360MCSignalPFDijetM2->Fill(SignalTotM2);
				h2360MCSignalPFDijetM3->Fill(SignalTotM3);
				h2360MCSignalPFDijetM4->Fill(SignalTotM4);
				h2360MCSignalPFDijetM5->Fill(SignalTotM5);
				h2360MCSignalPFDijetM6->Fill(SignalTotM6);
				h2360MCSignalPFDijetM7->Fill(SignalTotM7);
				h2360MCSignalPFDijetM8->Fill(SignalTotM8);
				h2360MCSignalPFDijetM9->Fill(SignalTotM9);
				h2360MCSignalPFDijetM10->Fill(SignalTotM10);
				h2360MCSignalPFDijetM11->Fill(SignalTotM11);
				h2360MCSignalPFDijetM12->Fill(SignalTotM12);
				h2360MCSignalPFDijetM13->Fill(SignalTotM13);
				h2360MCSignalPFDijetM14->Fill(SignalTotM14);
				h2360MCSignalPFDijetS1->Fill(SignalTotS1);
				h2360MCSignalPFDijetS2->Fill(SignalTotS2);
				h2360MCSignalPFDijetS3->Fill(SignalTotS3);
				h2360MCSignalPFDijetS4->Fill(SignalTotS4);
				h2360MCSignalPFDijetS5->Fill(SignalTotS5);
				h2360MCSignalPFDijetS6->Fill(SignalTotS6);
				h2360MCSignalPFDijetS7->Fill(SignalTotS7);
				h2360MCSignalPFDijetS8->Fill(SignalTotS8);
				h2360MCSignalPFDijetS9->Fill(SignalTotS9);
				h2360MCSignalPFDijetS10->Fill(SignalTotS10);
				h2360MCSignalPFDijetS11->Fill(SignalTotS11);
				h2360MCSignalPFDijetS12->Fill(SignalTotS12);
				h2360MCSignalPFDijetS13->Fill(SignalTotS13);
				h2360MCSignalPFDijetS14->Fill(SignalTotS14);
				h2360MCSignalPFDijetS15->Fill(SignalTotS15);
				h2360MCSignalPFDijetS16->Fill(SignalTotS16);
			}
      			if (isPFInclusive == 1) h2360MCSignalTotPFInclusive->Fill(SignalTot);
      			if (isCaloDijet == 1) h2360MCSignalTotCaloDijet->Fill(SignalTot);
      			if (isCaloInclusive == 1) h2360MCSignalTotCaloInclusive->Fill(SignalTot);
		}	 
		 
		if (useList == 1) {  
		  	// this is MC
		}
		
		sum2360MC = sum2360MC + SignalTot;
		if (isPFInclusive == 1) sum2360MCPFInclusive = sum2360MCPFInclusive + SignalTot;
		if (isPFDijet == 1) sum2360MCPFDijet = sum2360MCPFDijet + SignalTot;
		
		}
		
		MCevent = MCevent +1;
      }
   }
   
   
   ///////////////////////////
   // Cout some count numbers
   ///////////////////////////
   
   std::cout << "" << std::endl;
   std::cout << "Number of events/jets: " << std::endl;
   std::cout << "900 GeV results: " << std::endl;
   std::cout << "n900Events = " << n900Events << std::endl;
   std::cout << "n900CaloInclusive = " << n900CaloInclusive << std::endl;
   std::cout << "n900CaloDijet = " << n900CaloDijet << std::endl;
   std::cout << "n900PFInclusive = " << n900PFInclusive << std::endl;
   std::cout << "n900PFDijet = " << n900PFDijet << std::endl;
   std::cout << "" << std::endl;
   std::cout << "2360 GeV results: " << std::endl;
   std::cout << "n2360Events = " << n2360Events << std::endl;
   std::cout << "n2360CaloInclusive = " << n2360CaloInclusive << std::endl;
   std::cout << "n2360CaloDijet = " << n2360CaloDijet << std::endl;
   std::cout << "n2360PFInclusive = " << n2360PFInclusive << std::endl;
   std::cout << "n2360PFDijet = " << n2360PFDijet << std::endl;
   std::cout << "" << std::endl;
   std::cout << "900MC GeV results: " << std::endl;
   std::cout << "n900MCEvents = " << n900MCEvents << std::endl;
   std::cout << "n900MCCaloInclusive = " << n900MCCaloInclusive << std::endl;
   std::cout << "n900MCCaloDijet = " << n900MCCaloDijet << std::endl;
   std::cout << "n900MCPFInclusive = " << n900MCPFInclusive << std::endl;
   std::cout << "n900MCPFDijet = " << n900MCPFDijet << std::endl;
   std::cout << "" << std::endl;
   std::cout << "2360MC GeV results: " << std::endl;
   std::cout << "n2360MCEvents = " << n2360MCEvents << std::endl;
   std::cout << "n2360MCCaloInclusive = " << n2360MCCaloInclusive << std::endl;
   std::cout << "n2360MCCaloDijet = " << n2360MCCaloDijet << std::endl;
   std::cout << "n2360MCPFInclusive = " << n2360MCPFInclusive << std::endl;
   std::cout << "n2360MCPFDijet = " << n2360MCPFDijet << std::endl;
   
   
   // check ratio calculation by using manual means

	std::cout << "" << std::endl;
	std::cout << "Calculate PF ratio's with summed means:" << std::endl;
	std::cout << "" << std::endl;
   std::cout << "Mean 900GeV data = " << sum900/n900Events << std::endl;
   std::cout << "Mean 900GeV MC = " << sum900MC/n900MCEvents << std::endl;
   
   std::cout << "Mean 2360GeV data = " << sum2360/n2360Events << std::endl;
   std::cout << "Mean 2360GeV MC = " << sum2360MC/n2360MCEvents << std::endl;
   std::cout << "" << std::endl;
   double sumRatio900PFInclusive = (sum900PFInclusive/n900PFInclusive)/(sum900/n900Events);
   std::cout << "sumRatio900PFInclusive = " << sumRatio900PFInclusive << std::endl; 
   double sumRatio900MCPFInclusive = (sum900MCPFInclusive/n900MCPFInclusive)/(sum900MC/n900MCEvents);
   std::cout << "sumRatio900MCPFInclusive = " << sumRatio900MCPFInclusive << std::endl; 
   double sumRatio2360PFInclusive = (sum2360PFInclusive/n2360PFInclusive)/(sum2360/n2360Events);
   std::cout << "sumRatio2360PFInclusive = " << sumRatio2360PFInclusive << std::endl; 
   double sumRatio2360MCPFInclusive = (sum2360MCPFInclusive/n2360MCPFInclusive)/(sum2360MC/n2360MCEvents);
   std::cout << "sumRatio2360MCPFInclusive = " << sumRatio2360MCPFInclusive << std::endl; 
   std::cout << "" << std::endl;
	double sumRatio900PFDijet = (sum900PFDijet/n900PFDijet)/(sum900/n900Events);
	std::cout << "sumRatio900PFDijet = " << sumRatio900PFDijet << std::endl; 
	double sumRatio900MCPFDijet = (sum900MCPFDijet/n900MCPFDijet)/(sum900MC/n900MCEvents);
	std::cout << "sumRatio900MCPFDijet = " << sumRatio900MCPFDijet << std::endl; 
	double sumRatio2360PFDijet = (sum2360PFDijet/n2360PFDijet)/(sum2360/n2360Events);
	std::cout << "sumRatio2360PFDijet = " << sumRatio2360PFDijet << std::endl; 
	double sumRatio2360MCPFDijet = (sum2360MCPFDijet/n2360MCPFDijet)/(sum2360MC/n2360MCEvents);
	std::cout << "sumRatio2360MCPFDijet = " << sumRatio2360MCPFDijet << std::endl; 
   
   
   //////////////////////
   // Plot CASTOR stuff
   //////////////////////
   
   /*
   
   // show decalibration of channels
   TCanvas *cdecal = new TCanvas("cdecal","Mean signal distributions in CASTOR");
   cdecal->Divide(2,1);
   cdecal->cd(1);
   
   
   h900decalchannels->Scale(1./n900MCEvents);
   h900decalchannels->Draw("");
   h900channels->Scale(1./n900MCEvents);
   h900channels->Draw("same");
   
   cdecal->cd(2);
   h2360decalchannels->Scale(1./n2360MCEvents);
   h2360decalchannels->Draw("");
   h2360channels->Scale(1./n2360MCEvents);
   h2360channels->Draw("same");
   
   // draw pulse shapes
   TCanvas *cpulses = new TCanvas("cpulses","pulses");
   cpulses->Divide(2,1);
   cpulses->cd(1);
   hMCSlices->Scale(1./n900MCEvents);
   hMCSlices->Draw("");
   hDataSlices->Scale(1./n900Events);
   hDataSlices->Draw("same");
   
   cpulses->cd(2);
   hMCSlicesfC->Scale(1./n900MCEvents);
   hMCSlicesfC->Draw("");
   hDataSlicesfC->Scale(1./n900Events);
   hDataSlicesfC->Draw("same");
   */
   
   TCanvas *c1_900 = new TCanvas("c1_900","Total Signal distributions in CASTOR");
   c1_900->Divide(3,2);
   c1_900->cd(1);
   
   h900MCSignalTot->SetFillColor(8);
   h900MCSignalTot->SetFillStyle(1001);
   h900MCSignalTot->SetMarkerStyle(0);
   h900MCSignalTot->Scale(h900SignalTot->Integral()/h900MCSignalTot->Integral());
   h900MCSignalTot->Draw("hist");
   h900SignalTot->SetFillColor(0);
   h900SignalTot->SetFillStyle(0);
   h900SignalTot->SetMarkerStyle(1);
   h900SignalTot->Draw("samee");
   c1_900->cd(2);
   h900MCSignalTotPFDijet->SetFillColor(8);
   h900MCSignalTotPFDijet->SetFillStyle(1001);
   h900MCSignalTotPFDijet->SetMarkerStyle(0);
   h900MCSignalTotPFDijet->Scale(h900SignalTotPFDijet->Integral()/h900MCSignalTotPFDijet->Integral());
   h900MCSignalTotPFDijet->Draw("hist");
   h900SignalTotPFDijet->SetFillColor(0);
   h900SignalTotPFDijet->SetFillStyle(0);
   h900SignalTotPFDijet->SetMarkerStyle(1);
   h900SignalTotPFDijet->Draw("samee");
   c1_900->cd(3);
   h900MCSignalTotPFInclusive->SetFillColor(8);
   h900MCSignalTotPFInclusive->SetFillStyle(1001);
   h900MCSignalTotPFInclusive->SetMarkerStyle(0);
   h900MCSignalTotPFInclusive->Scale(h900SignalTotPFInclusive->Integral()/h900MCSignalTotPFInclusive->Integral());
   h900MCSignalTotPFInclusive->Draw("hist");
   h900SignalTotPFInclusive->SetFillColor(0);
   h900SignalTotPFInclusive->SetFillStyle(0);
   h900SignalTotPFInclusive->SetMarkerStyle(1);
   h900SignalTotPFInclusive->Draw("samee");
   c1_900->cd(4);
   h900MCSignalTotCaloDijet->SetFillColor(8);
   h900MCSignalTotCaloDijet->SetFillStyle(1001);
   h900MCSignalTotCaloDijet->SetMarkerStyle(0);
   h900MCSignalTotCaloDijet->Scale(h900SignalTotCaloDijet->Integral()/h900MCSignalTotCaloDijet->Integral());
   h900MCSignalTotCaloDijet->Draw("hist");
   h900SignalTotCaloDijet->SetFillColor(0);
   h900SignalTotCaloDijet->SetFillStyle(0);
   h900SignalTotCaloDijet->SetMarkerStyle(1);
   h900SignalTotCaloDijet->Draw("samee");
   c1_900->cd(5);
   h900MCSignalTotCaloInclusive->SetFillColor(8);
   h900MCSignalTotCaloInclusive->SetFillStyle(1001);
   h900MCSignalTotCaloInclusive->SetMarkerStyle(0);
   h900MCSignalTotCaloInclusive->Scale(h900SignalTotCaloInclusive->Integral()/h900MCSignalTotCaloInclusive->Integral());
   h900MCSignalTotCaloInclusive->Draw("hist");
   h900SignalTotCaloInclusive->SetFillColor(0);
   h900SignalTotCaloInclusive->SetFillStyle(0);
   h900SignalTotCaloInclusive->SetMarkerStyle(1);
   h900SignalTotCaloInclusive->Draw("samee");
   

   
   TCanvas *c1_2360 = new TCanvas("c1_2360","Total Signal distributions in CASTOR");
   c1_2360->Divide(3,2);
   c1_2360->cd(1);
   h2360MCSignalTot->SetFillColor(8);
   h2360MCSignalTot->SetFillStyle(1001);
   h2360MCSignalTot->SetMarkerStyle(0);
   h2360MCSignalTot->Scale(h2360SignalTot->Integral()/h2360MCSignalTot->Integral());
   h2360MCSignalTot->Draw("hist");
   h2360SignalTot->SetFillColor(0);
   h2360SignalTot->SetFillStyle(0);
   h2360SignalTot->SetMarkerStyle(1);
   h2360SignalTot->Draw("samee");
   //h2360SignalTot->Draw("e");
   
   c1_2360->cd(2);
   h2360MCSignalTotPFDijet->SetFillColor(8);
   h2360MCSignalTotPFDijet->SetFillStyle(1001);
   h2360MCSignalTotPFDijet->SetMarkerStyle(0);
   h2360MCSignalTotPFDijet->Scale(h2360SignalTotPFDijet->Integral()/h2360MCSignalTotPFDijet->Integral());
   h2360MCSignalTotPFDijet->Draw("hist");
   h2360SignalTotPFDijet->SetFillColor(0);
   h2360SignalTotPFDijet->SetFillStyle(0);
   h2360SignalTotPFDijet->SetMarkerStyle(1);
   h2360SignalTotPFDijet->Draw("samee");
   
   c1_2360->cd(3);
   h2360MCSignalTotPFInclusive->SetFillColor(8);
   h2360MCSignalTotPFInclusive->SetFillStyle(1001);
   h2360MCSignalTotPFInclusive->SetMarkerStyle(0);
   h2360MCSignalTotPFInclusive->Scale(h2360SignalTotPFInclusive->Integral()/h2360MCSignalTotPFInclusive->Integral());
   h2360MCSignalTotPFInclusive->Draw("hist");
   h2360SignalTotPFInclusive->SetFillColor(0);
   h2360SignalTotPFInclusive->SetFillStyle(0);
   h2360SignalTotPFInclusive->SetMarkerStyle(1);
   h2360SignalTotPFInclusive->Draw("samee");
   c1_2360->cd(4);
   h2360MCSignalTotCaloDijet->SetFillColor(8);
   h2360MCSignalTotCaloDijet->SetFillStyle(1001);
   h2360MCSignalTotCaloDijet->SetMarkerStyle(0);
   h2360MCSignalTotCaloDijet->Scale(h2360SignalTotCaloDijet->Integral()/h2360MCSignalTotCaloDijet->Integral());
   h2360MCSignalTotCaloDijet->Draw("hist");
   h2360SignalTotCaloDijet->SetFillColor(0);
   h2360SignalTotCaloDijet->SetFillStyle(0);
   h2360SignalTotCaloDijet->SetMarkerStyle(1);
   h2360SignalTotCaloDijet->Draw("samee");
   c1_2360->cd(5);
   h2360MCSignalTotCaloInclusive->SetFillColor(8);
   h2360MCSignalTotCaloInclusive->SetFillStyle(1001);
   h2360MCSignalTotCaloInclusive->SetMarkerStyle(0);
   h2360MCSignalTotCaloInclusive->Scale(h2360SignalTotCaloInclusive->Integral()/h2360MCSignalTotCaloInclusive->Integral());
   h2360MCSignalTotCaloInclusive->Draw("hist");
   h2360SignalTotCaloInclusive->SetFillColor(0);
   h2360SignalTotCaloInclusive->SetFillStyle(0);
   h2360SignalTotCaloInclusive->SetMarkerStyle(1);
   h2360SignalTotCaloInclusive->Draw("samee");
   
   
   
   // plot distributions for paper
   
   
   TCanvas *c1_900paper = new TCanvas("c1_900paper","Total Signal distributions in CASTOR");
   c1_900paper->Divide(2,1);
   c1_900paper->cd(1);
   h900MCSignalTot->SetFillColor(8);
   h900MCSignalTot->SetFillStyle(1001);
   h900MCSignalTot->SetMarkerStyle(0);
   h900MCSignalTot->Scale(h900SignalTot->Integral()/h900MCSignalTot->Integral());
   h900MCSignalTot->SetTitle("Total Signal in CASTOR for MB events at 900 GeV");
   h900MCSignalTot->Draw("hist");
   h900SignalTot->SetFillColor(0);
   h900SignalTot->SetFillStyle(0);
   h900SignalTot->SetMarkerStyle(1);
   h900SignalTot->Draw("samee");
   //h900SignalTot->Draw("e");
   
   TLegend *leg900MC = new TLegend(0.5067801,0.6687445,0.8864645,0.8791789,NULL,"brNDC");
   leg900MC->SetBorderSize(0);
   leg900MC->SetTextFont(62);
   leg900MC->SetLineColor(1);
   leg900MC->SetLineStyle(1);
   leg900MC->SetLineWidth(1);
   leg900MC->SetFillColor(0);
   leg900MC->SetFillStyle(1001);
   TLegendEntry *entry=leg900MC->AddEntry("h900MCSignalTot","Monte Carlo","lpf");
   entry->SetFillColor(8);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerSize(1);
   TLegendEntry *entry2=leg900MC->AddEntry("h900SignalTot","Data","lp");
   entry2->SetLineColor(1);
   entry2->SetLineStyle(1);
   entry2->SetLineWidth(1);
   entry2->SetMarkerColor(1);
   entry2->SetMarkerStyle(1);
   entry2->SetMarkerSize(1);
   leg900MC->Draw();

   
   c1_900paper->cd(2);
   h900MCSignalTotPFDijet->SetFillColor(8);
   h900MCSignalTotPFDijet->SetFillStyle(1001);
   h900MCSignalTotPFDijet->SetMarkerStyle(0);
   h900MCSignalTotPFDijet->Scale(h900SignalTotPFDijet->Integral()/h900MCSignalTotPFDijet->Integral());
   h900MCSignalTotPFDijet->SetTitle("Total Signal in CASTOR for central dijet events at 900 GeV");
   h900MCSignalTotPFDijet->Draw("hist");
   h900SignalTotPFDijet->SetFillColor(0);
   h900SignalTotPFDijet->SetFillStyle(0);
   h900SignalTotPFDijet->SetMarkerStyle(1);
   h900SignalTotPFDijet->Draw("samee");
   
   TLegend *leg900MCDijet = new TLegend(0.5067801,0.6687445,0.8864645,0.8791789,NULL,"brNDC");
   leg900MCDijet->SetBorderSize(0);
   leg900MCDijet->SetTextFont(62);
   leg900MCDijet->SetLineColor(1);
   leg900MCDijet->SetLineStyle(1);
   leg900MCDijet->SetLineWidth(1);
   leg900MCDijet->SetFillColor(0);
   leg900MCDijet->SetFillStyle(1001);
   TLegendEntry *entry3=leg900MCDijet->AddEntry("h900MCSignalTotPFDijet","Monte Carlo","lpf");
   entry3->SetFillColor(8);
   entry3->SetFillStyle(1001);
   entry3->SetLineColor(1);
   entry3->SetLineStyle(1);
   entry3->SetLineWidth(1);
   entry3->SetMarkerColor(1);
   entry3->SetMarkerSize(1);
   TLegendEntry *entry4=leg900MCDijet->AddEntry("h900SignalTotPFDijet","Data","lp");
   entry4->SetLineColor(1);
   entry4->SetLineStyle(1);
   entry4->SetLineWidth(1);
   entry4->SetMarkerColor(1);
   entry4->SetMarkerStyle(1);
   entry4->SetMarkerSize(1);
   leg900MCDijet->Draw();
   
   
   TCanvas *c1_2360paper = new TCanvas("c1_2360paper","Total Signal distributions in CASTOR");
   c1_2360paper->Divide(2,1);
   c1_2360paper->cd(1);
   h2360MCSignalTot->SetFillColor(8);
   h2360MCSignalTot->SetFillStyle(1001);
   h2360MCSignalTot->SetMarkerStyle(0);
   h2360MCSignalTot->Scale(h2360SignalTot->Integral()/h2360MCSignalTot->Integral());
   h2360MCSignalTot->SetTitle("Total Signal in CASTOR for MB events at 2360 GeV");
   h2360MCSignalTot->Draw("hist");
   h2360SignalTot->SetFillColor(0);
   h2360SignalTot->SetFillStyle(0);
   h2360SignalTot->SetMarkerStyle(1);
   h2360SignalTot->Draw("samee");
   //h2360SignalTot->Draw("e");
   
   TLegend *leg2360MC = new TLegend(0.5067801,0.6687445,0.8864645,0.8791789,NULL,"brNDC");
   leg2360MC->SetBorderSize(0);
   leg2360MC->SetTextFont(62);
   leg2360MC->SetLineColor(1);
   leg2360MC->SetLineStyle(1);
   leg2360MC->SetLineWidth(1);
   leg2360MC->SetFillColor(0);
   leg2360MC->SetFillStyle(1001);
   TLegendEntry *entry5=leg2360MC->AddEntry("h2360MCSignalTot","Monte Carlo","lpf");
   entry5->SetFillColor(8);
   entry5->SetFillStyle(1001);
   entry5->SetLineColor(1);
   entry5->SetLineStyle(1);
   entry5->SetLineWidth(1);
   entry5->SetMarkerColor(1);
   entry5->SetMarkerSize(1);
   TLegendEntry *entry6=leg2360MC->AddEntry("h2360SignalTot","Data","lp");
   entry6->SetLineColor(1);
   entry6->SetLineStyle(1);
   entry6->SetLineWidth(1);
   entry6->SetMarkerColor(1);
   entry6->SetMarkerStyle(1);
   entry6->SetMarkerSize(1);
   leg2360MC->Draw();

   
   c1_2360paper->cd(2);
   h2360MCSignalTotPFDijet->SetFillColor(8);
   h2360MCSignalTotPFDijet->SetFillStyle(1001);
   h2360MCSignalTotPFDijet->SetMarkerStyle(0);
   h2360MCSignalTotPFDijet->Scale(h2360SignalTotPFDijet->Integral()/h2360MCSignalTotPFDijet->Integral());
   h2360MCSignalTotPFDijet->SetTitle("Total Signal in CASTOR for central dijet events at 2360 GeV");
   h2360MCSignalTotPFDijet->Draw("hist");
   h2360SignalTotPFDijet->SetFillColor(0);
   h2360SignalTotPFDijet->SetFillStyle(0);
   h2360SignalTotPFDijet->SetMarkerStyle(1);
   h2360SignalTotPFDijet->Draw("samee");
   
   TLegend *leg2360MCDijet = new TLegend(0.5067801,0.6687445,0.8864645,0.8791789,NULL,"brNDC");
   leg2360MCDijet->SetBorderSize(0);
   leg2360MCDijet->SetTextFont(62);
   leg2360MCDijet->SetLineColor(1);
   leg2360MCDijet->SetLineStyle(1);
   leg2360MCDijet->SetLineWidth(1);
   leg2360MCDijet->SetFillColor(0);
   leg2360MCDijet->SetFillStyle(1001);
   TLegendEntry *entry7=leg2360MCDijet->AddEntry("h2360MCSignalTotPFDijet","Monte Carlo","lpf");
   entry7->SetFillColor(8);
   entry7->SetFillStyle(1001);
   entry7->SetLineColor(1);
   entry7->SetLineStyle(1);
   entry7->SetLineWidth(1);
   entry7->SetMarkerColor(1);
   entry7->SetMarkerSize(1);
   TLegendEntry *entry8=leg2360MCDijet->AddEntry("h2360SignalTotPFDijet","Data","lp");
   entry8->SetLineColor(1);
   entry8->SetLineStyle(1);
   entry8->SetLineWidth(1);
   entry8->SetMarkerColor(1);
   entry8->SetMarkerStyle(1);
   entry8->SetMarkerSize(1);
   leg2360MCDijet->Draw();
   
   
   
   ///////////////////////////////
   // Plot module and sector stuff
   ///////////////////////////////
   
   TCanvas *ceflow900GeV_modules = new TCanvas("ceflow900GeV_modules","Signal distributions in CASTOR");
   ceflow900GeV_modules->Divide(3,2);
   ceflow900GeV_modules->cd(1);
   h900MCSignalM1->SetFillColor(8);
   h900MCSignalM1->SetFillStyle(1001);
   h900MCSignalM1->SetMarkerStyle(0);
   h900MCSignalM1->Scale(h900SignalM1->Integral()/h900MCSignalM1->Integral());
   h900MCSignalM1->SetTitle("Signal module 1 in CASTOR for MB events at 900 GeV");
   h900MCSignalM1->Draw("hist");
   h900SignalM1->SetFillColor(0);
   h900SignalM1->SetFillStyle(0);
   h900SignalM1->SetMarkerStyle(1);
   h900SignalM1->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_modules->cd(2);
   h900MCSignalM2->SetFillColor(8);
   h900MCSignalM2->SetFillStyle(1001);
   h900MCSignalM2->SetMarkerStyle(0);
   h900MCSignalM2->Scale(h900SignalM2->Integral()/h900MCSignalM2->Integral());
   h900MCSignalM2->SetTitle("Signal module 2 in CASTOR for MB events at 900 GeV");
   h900MCSignalM2->Draw("hist");
   h900SignalM2->SetFillColor(0);
   h900SignalM2->SetFillStyle(0);
   h900SignalM2->SetMarkerStyle(1);
   h900SignalM2->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_modules->cd(3);
   h900MCSignalM3->SetFillColor(8);
   h900MCSignalM3->SetFillStyle(1001);
   h900MCSignalM3->SetMarkerStyle(0);
   h900MCSignalM3->Scale(h900SignalM3->Integral()/h900MCSignalM3->Integral());
   h900MCSignalM3->SetTitle("Signal module 3 in CASTOR for MB events at 900 GeV");
   h900MCSignalM3->Draw("hist");
   h900SignalM3->SetFillColor(0);
   h900SignalM3->SetFillStyle(0);
   h900SignalM3->SetMarkerStyle(1);
   h900SignalM3->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_modules->cd(4);
   h900MCSignalM4->SetFillColor(8);
   h900MCSignalM4->SetFillStyle(1001);
   h900MCSignalM4->SetMarkerStyle(0);
   h900MCSignalM4->Scale(h900SignalM4->Integral()/h900MCSignalM4->Integral());
   h900MCSignalM4->SetTitle("Signal module 4 in CASTOR for MB events at 900 GeV");
   h900MCSignalM4->Draw("hist");
   h900SignalM4->SetFillColor(0);
   h900SignalM4->SetFillStyle(0);
   h900SignalM4->SetMarkerStyle(1);
   h900SignalM4->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_modules->cd(5);
   h900MCSignalM5->SetFillColor(8);
   h900MCSignalM5->SetFillStyle(1001);
   h900MCSignalM5->SetMarkerStyle(0);
   h900MCSignalM5->Scale(h900SignalM5->Integral()/h900MCSignalM5->Integral());
   h900MCSignalM5->SetTitle("Signal module 5 in CASTOR for MB events at 900 GeV");
   h900MCSignalM5->Draw("hist");
   h900SignalM5->SetFillColor(0);
   h900SignalM5->SetFillStyle(0);
   h900SignalM5->SetMarkerStyle(1);
   h900SignalM5->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_modules->cd(6);
   h900MCSignalM6->SetFillColor(8);
   h900MCSignalM6->SetFillStyle(1001);
   h900MCSignalM6->SetMarkerStyle(0);
   h900MCSignalM6->Scale(h900SignalM6->Integral()/h900MCSignalM6->Integral());
   h900MCSignalM6->SetTitle("Signal module 6 in CASTOR for MB events at 900 GeV");
   h900MCSignalM6->Draw("hist");
   h900SignalM6->SetFillColor(0);
   h900SignalM6->SetFillStyle(0);
   h900SignalM6->SetMarkerStyle(1);
   h900SignalM6->Draw("samee");
   leg900MCDijet->Draw();
   /*
   ceflow900GeV_modules->cd(7);
   h900MCSignalM7->SetFillColor(8);
   h900MCSignalM7->SetFillStyle(1001);
   h900MCSignalM7->SetMarkerStyle(0);
   h900MCSignalM7->Scale(h900SignalM7->Integral()/h900MCSignalM7->Integral());
   h900MCSignalM7->SetTitle("Signal module 7 in CASTOR for MB events at 900 GeV");
   h900MCSignalM7->Draw("hist");
   h900SignalM7->SetFillColor(0);
   h900SignalM7->SetFillStyle(0);
   h900SignalM7->SetMarkerStyle(1);
   h900SignalM7->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_modules->cd(8);
   h900MCSignalM8->SetFillColor(8);
   h900MCSignalM8->SetFillStyle(1001);
   h900MCSignalM8->SetMarkerStyle(0);
   h900MCSignalM8->Scale(h900SignalM8->Integral()/h900MCSignalM8->Integral());
   h900MCSignalM8->SetTitle("Signal module 8 in CASTOR for MB events at 900 GeV");
   h900MCSignalM8->Draw("hist");
   h900SignalM8->SetFillColor(0);
   h900SignalM8->SetFillStyle(0);
   h900SignalM8->SetMarkerStyle(1);
   h900SignalM8->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_modules->cd(9);
   h900MCSignalM9->SetFillColor(8);
   h900MCSignalM9->SetFillStyle(1001);
   h900MCSignalM9->SetMarkerStyle(0);
   h900MCSignalM9->Scale(h900SignalM9->Integral()/h900MCSignalM9->Integral());
   h900MCSignalM9->SetTitle("Signal module 9 in CASTOR for MB events at 900 GeV");
   h900MCSignalM9->Draw("hist");
   h900SignalM9->SetFillColor(0);
   h900SignalM9->SetFillStyle(0);
   h900SignalM9->SetMarkerStyle(1);
   h900SignalM9->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_modules->cd(10);
   h900MCSignalM10->SetFillColor(8);
   h900MCSignalM10->SetFillStyle(1001);
   h900MCSignalM10->SetMarkerStyle(0);
   h900MCSignalM10->Scale(h900SignalM10->Integral()/h900MCSignalM10->Integral());
   h900MCSignalM10->SetTitle("Signal module 10 in CASTOR for MB events at 900 GeV");
   h900MCSignalM10->Draw("hist");
   h900SignalM10->SetFillColor(0);
   h900SignalM10->SetFillStyle(0);
   h900SignalM10->SetMarkerStyle(1);
   h900SignalM10->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_modules->cd(11);
   h900MCSignalM11->SetFillColor(8);
   h900MCSignalM11->SetFillStyle(1001);
   h900MCSignalM11->SetMarkerStyle(0);
   h900MCSignalM11->Scale(h900SignalM11->Integral()/h900MCSignalM11->Integral());
   h900MCSignalM11->SetTitle("Signal module 11 in CASTOR for MB events at 900 GeV");
   h900MCSignalM11->Draw("hist");
   h900SignalM11->SetFillColor(0);
   h900SignalM11->SetFillStyle(0);
   h900SignalM11->SetMarkerStyle(1);
   h900SignalM11->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_modules->cd(12);
   h900MCSignalM12->SetFillColor(8);
   h900MCSignalM12->SetFillStyle(1001);
   h900MCSignalM12->SetMarkerStyle(0);
   h900MCSignalM12->Scale(h900SignalM12->Integral()/h900MCSignalM12->Integral());
   h900MCSignalM12->SetTitle("Signal module 12 in CASTOR for MB events at 900 GeV");
   h900MCSignalM12->Draw("hist");
   h900SignalM12->SetFillColor(0);
   h900SignalM12->SetFillStyle(0);
   h900SignalM12->SetMarkerStyle(1);
   h900SignalM12->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_modules->cd(13);
   h900MCSignalM13->SetFillColor(8);
   h900MCSignalM13->SetFillStyle(1001);
   h900MCSignalM13->SetMarkerStyle(0);
   h900MCSignalM13->Scale(h900SignalM13->Integral()/h900MCSignalM13->Integral());
   h900MCSignalM13->SetTitle("Signal module 13 in CASTOR for MB events at 900 GeV");
   h900MCSignalM13->Draw("hist");
   h900SignalM13->SetFillColor(0);
   h900SignalM13->SetFillStyle(0);
   h900SignalM13->SetMarkerStyle(1);
   h900SignalM13->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_modules->cd(14);
   h900MCSignalM14->SetFillColor(8);
   h900MCSignalM14->SetFillStyle(1001);
   h900MCSignalM14->SetMarkerStyle(0);
   h900MCSignalM14->Scale(h900SignalM14->Integral()/h900MCSignalM14->Integral());
   h900MCSignalM14->SetTitle("Signal module 14 in CASTOR for MB events at 900 GeV");
   h900MCSignalM14->Draw("hist");
   h900SignalM14->SetFillColor(0);
   h900SignalM14->SetFillStyle(0);
   h900SignalM14->SetMarkerStyle(1);
   h900SignalM14->Draw("samee");
   leg900MCDijet->Draw();
   */
   
   TCanvas *cPFDijet900GeV_modules = new TCanvas("cPFDijet900GeV_modules","Signal distributions in CASTOR");
   cPFDijet900GeV_modules->Divide(3,2);
   cPFDijet900GeV_modules->cd(1);
   h900MCSignalPFDijetM1->SetFillColor(8);
   h900MCSignalPFDijetM1->SetFillStyle(1001);
   h900MCSignalPFDijetM1->SetMarkerStyle(0);
   h900MCSignalPFDijetM1->Scale(h900SignalPFDijetM1->Integral()/h900MCSignalPFDijetM1->Integral());
   h900MCSignalPFDijetM1->SetTitle("Signal module 1 in CASTOR for central dijets events at 900 GeV");
   h900MCSignalPFDijetM1->Draw("hist");
   h900SignalPFDijetM1->SetFillColor(0);
   h900SignalPFDijetM1->SetFillStyle(0);
   h900SignalPFDijetM1->SetMarkerStyle(1);
   h900SignalPFDijetM1->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_modules->cd(2);
   h900MCSignalPFDijetM2->SetFillColor(8);
   h900MCSignalPFDijetM2->SetFillStyle(1001);
   h900MCSignalPFDijetM2->SetMarkerStyle(0);
   h900MCSignalPFDijetM2->Scale(h900SignalPFDijetM2->Integral()/h900MCSignalPFDijetM2->Integral());
   h900MCSignalPFDijetM2->SetTitle("Signal module 2 in CASTOR for central dijets events at 900 GeV");
   h900MCSignalPFDijetM2->Draw("hist");
   h900SignalPFDijetM2->SetFillColor(0);
   h900SignalPFDijetM2->SetFillStyle(0);
   h900SignalPFDijetM2->SetMarkerStyle(1);
   h900SignalPFDijetM2->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_modules->cd(3);
   h900MCSignalPFDijetM3->SetFillColor(8);
   h900MCSignalPFDijetM3->SetFillStyle(1001);
   h900MCSignalPFDijetM3->SetMarkerStyle(0);
   h900MCSignalPFDijetM3->Scale(h900SignalPFDijetM3->Integral()/h900MCSignalPFDijetM3->Integral());
   h900MCSignalPFDijetM3->SetTitle("Signal module 3 in CASTOR for central dijets events at 900 GeV");
   h900MCSignalPFDijetM3->Draw("hist");
   h900SignalPFDijetM3->SetFillColor(0);
   h900SignalPFDijetM3->SetFillStyle(0);
   h900SignalPFDijetM3->SetMarkerStyle(1);
   h900SignalPFDijetM3->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_modules->cd(4);
   h900MCSignalPFDijetM4->SetFillColor(8);
   h900MCSignalPFDijetM4->SetFillStyle(1001);
   h900MCSignalPFDijetM4->SetMarkerStyle(0);
   h900MCSignalPFDijetM4->Scale(h900SignalPFDijetM4->Integral()/h900MCSignalPFDijetM4->Integral());
   h900MCSignalPFDijetM4->SetTitle("Signal module 4 in CASTOR for central dijets events at 900 GeV");
   h900MCSignalPFDijetM4->Draw("hist");
   h900SignalPFDijetM4->SetFillColor(0);
   h900SignalPFDijetM4->SetFillStyle(0);
   h900SignalPFDijetM4->SetMarkerStyle(1);
   h900SignalPFDijetM4->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_modules->cd(5);
   h900MCSignalPFDijetM5->SetFillColor(8);
   h900MCSignalPFDijetM5->SetFillStyle(1001);
   h900MCSignalPFDijetM5->SetMarkerStyle(0);
   h900MCSignalPFDijetM5->Scale(h900SignalPFDijetM5->Integral()/h900MCSignalPFDijetM5->Integral());
   h900MCSignalPFDijetM5->SetTitle("Signal module 5 in CASTOR for central dijets events at 900 GeV");
   h900MCSignalPFDijetM5->Draw("hist");
   h900SignalPFDijetM5->SetFillColor(0);
   h900SignalPFDijetM5->SetFillStyle(0);
   h900SignalPFDijetM5->SetMarkerStyle(1);
   h900SignalPFDijetM5->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_modules->cd(6);
   h900MCSignalPFDijetM6->SetFillColor(8);
   h900MCSignalPFDijetM6->SetFillStyle(1001);
   h900MCSignalPFDijetM6->SetMarkerStyle(0);
   h900MCSignalPFDijetM6->Scale(h900SignalPFDijetM6->Integral()/h900MCSignalPFDijetM6->Integral());
   h900MCSignalPFDijetM6->SetTitle("Signal module 6 in CASTOR for central dijets events at 900 GeV");
   h900MCSignalPFDijetM6->Draw("hist");
   h900SignalPFDijetM6->SetFillColor(0);
   h900SignalPFDijetM6->SetFillStyle(0);
   h900SignalPFDijetM6->SetMarkerStyle(1);
   h900SignalPFDijetM6->Draw("samee");
   leg900MCDijet->Draw();
   
   // sectors
   
  TCanvas *ceflow900GeV_sectors = new TCanvas("ceflow900GeV_sectors","Signal distributions in CASTOR");
   ceflow900GeV_sectors->Divide(4,4);
   ceflow900GeV_sectors->cd(1);
   //ceflow900GeV_sectors_1->SetLogY();
   h900MCSignalS1->SetFillColor(8);
   h900MCSignalS1->SetFillStyle(1001);
   h900MCSignalS1->SetMarkerStyle(0);
   h900MCSignalS1->Scale(h900SignalS1->Integral()/h900MCSignalS1->Integral());
   h900MCSignalS1->SetTitle("Signal sector 1 in CASTOR for MB events at 900 GeV");
   h900MCSignalS1->Draw("hist");
   h900SignalS1->SetFillColor(0);
   h900SignalS1->SetFillStyle(0);
   h900SignalS1->SetMarkerStyle(1);
   h900SignalS1->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_sectors->cd(2);
   h900MCSignalS2->SetFillColor(8);
   h900MCSignalS2->SetFillStyle(1001);
   h900MCSignalS2->SetMarkerStyle(0);
   h900MCSignalS2->Scale(h900SignalS2->Integral()/h900MCSignalS2->Integral());
   h900MCSignalS2->SetTitle("Signal sector 2 in CASTOR for MB events at 900 GeV");
   h900MCSignalS2->Draw("hist");
   h900SignalS2->SetFillColor(0);
   h900SignalS2->SetFillStyle(0);
   h900SignalS2->SetMarkerStyle(1);
   h900SignalS2->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_sectors->cd(3);
   h900MCSignalS3->SetFillColor(8);
   h900MCSignalS3->SetFillStyle(1001);
   h900MCSignalS3->SetMarkerStyle(0);
   h900MCSignalS3->Scale(h900SignalS3->Integral()/h900MCSignalS3->Integral());
   h900MCSignalS3->SetTitle("Signal sector 3 in CASTOR for MB events at 900 GeV");
   h900MCSignalS3->Draw("hist");
   h900SignalS3->SetFillColor(0);
   h900SignalS3->SetFillStyle(0);
   h900SignalS3->SetMarkerStyle(1);
   h900SignalS3->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_sectors->cd(4);
   h900MCSignalS4->SetFillColor(8);
   h900MCSignalS4->SetFillStyle(1001);
   h900MCSignalS4->SetMarkerStyle(0);
   h900MCSignalS4->Scale(h900SignalS4->Integral()/h900MCSignalS4->Integral());
   h900MCSignalS4->SetTitle("Signal sector 4 in CASTOR for MB events at 900 GeV");
   h900MCSignalS4->Draw("hist");
   h900SignalS4->SetFillColor(0);
   h900SignalS4->SetFillStyle(0);
   h900SignalS4->SetMarkerStyle(1);
   h900SignalS4->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_sectors->cd(5);
   h900MCSignalS5->SetFillColor(8);
   h900MCSignalS5->SetFillStyle(1001);
   h900MCSignalS5->SetMarkerStyle(0);
   h900MCSignalS5->Scale(h900SignalS5->Integral()/h900MCSignalS5->Integral());
   h900MCSignalS5->SetTitle("Signal sector 5 in CASTOR for MB events at 900 GeV");
   h900MCSignalS5->Draw("hist");
   h900SignalS5->SetFillColor(0);
   h900SignalS5->SetFillStyle(0);
   h900SignalS5->SetMarkerStyle(1);
   h900SignalS5->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_sectors->cd(6);
   h900MCSignalS6->SetFillColor(8);
   h900MCSignalS6->SetFillStyle(1001);
   h900MCSignalS6->SetMarkerStyle(0);
   h900MCSignalS6->Scale(h900SignalS6->Integral()/h900MCSignalS6->Integral());
   h900MCSignalS6->SetTitle("Signal sector 6 in CASTOR for MB events at 900 GeV");
   h900MCSignalS6->Draw("hist");
   h900SignalS6->SetFillColor(0);
   h900SignalS6->SetFillStyle(0);
   h900SignalS6->SetMarkerStyle(1);
   h900SignalS6->Draw("samee");
   leg900MCDijet->Draw();
   
   ceflow900GeV_sectors->cd(7);
   h900MCSignalS7->SetFillColor(8);
   h900MCSignalS7->SetFillStyle(1001);
   h900MCSignalS7->SetMarkerStyle(0);
   h900MCSignalS7->Scale(h900SignalS7->Integral()/h900MCSignalS7->Integral());
   h900MCSignalS7->SetTitle("Signal sector 7 in CASTOR for MB events at 900 GeV");
   h900MCSignalS7->Draw("hist");
   h900SignalS7->SetFillColor(0);
   h900SignalS7->SetFillStyle(0);
   h900SignalS7->SetMarkerStyle(1);
   h900SignalS7->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_sectors->cd(8);
   h900MCSignalS8->SetFillColor(8);
   h900MCSignalS8->SetFillStyle(1001);
   h900MCSignalS8->SetMarkerStyle(0);
   h900MCSignalS8->Scale(h900SignalS8->Integral()/h900MCSignalS8->Integral());
   h900MCSignalS8->SetTitle("Signal sector 8 in CASTOR for MB events at 900 GeV");
   h900MCSignalS8->Draw("hist");
   h900SignalS8->SetFillColor(0);
   h900SignalS8->SetFillStyle(0);
   h900SignalS8->SetMarkerStyle(1);
   h900SignalS8->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_sectors->cd(9);
   h900MCSignalS9->SetFillColor(8);
   h900MCSignalS9->SetFillStyle(1001);
   h900MCSignalS9->SetMarkerStyle(0);
   h900MCSignalS9->Scale(h900SignalS9->Integral()/h900MCSignalS9->Integral());
   h900MCSignalS9->SetTitle("Signal sector 9 in CASTOR for MB events at 900 GeV");
   h900MCSignalS9->Draw("hist");
   h900SignalS9->SetFillColor(0);
   h900SignalS9->SetFillStyle(0);
   h900SignalS9->SetMarkerStyle(1);
   h900SignalS9->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_sectors->cd(10);
   h900MCSignalS10->SetFillColor(8);
   h900MCSignalS10->SetFillStyle(1001);
   h900MCSignalS10->SetMarkerStyle(0);
   h900MCSignalS10->Scale(h900SignalS10->Integral()/h900MCSignalS10->Integral());
   h900MCSignalS10->SetTitle("Signal sector 10 in CASTOR for MB events at 900 GeV");
   h900MCSignalS10->Draw("hist");
   h900SignalS10->SetFillColor(0);
   h900SignalS10->SetFillStyle(0);
   h900SignalS10->SetMarkerStyle(1);
   h900SignalS10->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_sectors->cd(11);
   h900MCSignalS11->SetFillColor(8);
   h900MCSignalS11->SetFillStyle(1001);
   h900MCSignalS11->SetMarkerStyle(0);
   h900MCSignalS11->Scale(h900SignalS11->Integral()/h900MCSignalS11->Integral());
   h900MCSignalS11->SetTitle("Signal sector 11 in CASTOR for MB events at 900 GeV");
   h900MCSignalS11->Draw("hist");
   h900SignalS11->SetFillColor(0);
   h900SignalS11->SetFillStyle(0);
   h900SignalS11->SetMarkerStyle(1);
   h900SignalS11->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_sectors->cd(12);
   h900MCSignalS12->SetFillColor(8);
   h900MCSignalS12->SetFillStyle(1001);
   h900MCSignalS12->SetMarkerStyle(0);
   h900MCSignalS12->Scale(h900SignalS12->Integral()/h900MCSignalS12->Integral());
   h900MCSignalS12->SetTitle("Signal sector 12 in CASTOR for MB events at 900 GeV");
   h900MCSignalS12->Draw("hist");
   h900SignalS12->SetFillColor(0);
   h900SignalS12->SetFillStyle(0);
   h900SignalS12->SetMarkerStyle(1);
   h900SignalS12->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_sectors->cd(13);
   h900MCSignalS13->SetFillColor(8);
   h900MCSignalS13->SetFillStyle(1001);
   h900MCSignalS13->SetMarkerStyle(0);
   h900MCSignalS13->Scale(h900SignalS13->Integral()/h900MCSignalS13->Integral());
   h900MCSignalS13->SetTitle("Signal sector 13 in CASTOR for MB events at 900 GeV");
   h900MCSignalS13->Draw("hist");
   h900SignalS13->SetFillColor(0);
   h900SignalS13->SetFillStyle(0);
   h900SignalS13->SetMarkerStyle(1);
   h900SignalS13->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_sectors->cd(14);
   h900MCSignalS14->SetFillColor(8);
   h900MCSignalS14->SetFillStyle(1001);
   h900MCSignalS14->SetMarkerStyle(0);
   h900MCSignalS14->Scale(h900SignalS14->Integral()/h900MCSignalS14->Integral());
   h900MCSignalS14->SetTitle("Signal sector 14 in CASTOR for MB events at 900 GeV");
   h900MCSignalS14->Draw("hist");
   h900SignalS14->SetFillColor(0);
   h900SignalS14->SetFillStyle(0);
   h900SignalS14->SetMarkerStyle(1);
   h900SignalS14->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_sectors->cd(15);
   h900MCSignalS15->SetFillColor(8);
   h900MCSignalS15->SetFillStyle(1001);
   h900MCSignalS15->SetMarkerStyle(0);
   h900MCSignalS15->Scale(h900SignalS15->Integral()/h900MCSignalS15->Integral());
   h900MCSignalS15->SetTitle("Signal sector 15 in CASTOR for MB events at 900 GeV");
   h900MCSignalS15->Draw("hist");
   h900SignalS15->SetFillColor(0);
   h900SignalS15->SetFillStyle(0);
   h900SignalS15->SetMarkerStyle(1);
   h900SignalS15->Draw("samee");
   leg900MCDijet->Draw();
   ceflow900GeV_sectors->cd(16);
   h900MCSignalS16->SetFillColor(8);
   h900MCSignalS16->SetFillStyle(1001);
   h900MCSignalS16->SetMarkerStyle(0);
   h900MCSignalS16->Scale(h900SignalS16->Integral()/h900MCSignalS16->Integral());
   h900MCSignalS16->SetTitle("Signal sector 16 in CASTOR for MB events at 900 GeV");
   h900MCSignalS16->Draw("hist");
   h900SignalS16->SetFillColor(0);
   h900SignalS16->SetFillStyle(0);
   h900SignalS16->SetMarkerStyle(1);
   h900SignalS16->Draw("samee");
   leg900MCDijet->Draw();
   
   
   TCanvas *cPFDijet900GeV_sectors = new TCanvas("cPFDijet900GeV_sectors","Signal distributions in CASTOR");
   cPFDijet900GeV_sectors->Divide(4,4);
   cPFDijet900GeV_sectors->cd(1);
   h900MCSignalPFDijetS1->SetFillColor(8);
   h900MCSignalPFDijetS1->SetFillStyle(1001);
   h900MCSignalPFDijetS1->SetMarkerStyle(0);
   h900MCSignalPFDijetS1->Scale(h900SignalPFDijetS1->Integral()/h900MCSignalPFDijetS1->Integral());
   h900MCSignalPFDijetS1->SetTitle("Signal sector 1 in CASTOR for central dijets events at 900 GeV");
   h900MCSignalPFDijetS1->Draw("hist");
   h900SignalPFDijetS1->SetFillColor(0);
   h900SignalPFDijetS1->SetFillStyle(0);
   h900SignalPFDijetS1->SetMarkerStyle(1);
   h900SignalPFDijetS1->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_sectors->cd(2);
   h900MCSignalPFDijetS2->SetFillColor(8);
   h900MCSignalPFDijetS2->SetFillStyle(1001);
   h900MCSignalPFDijetS2->SetMarkerStyle(0);
   h900MCSignalPFDijetS2->Scale(h900SignalPFDijetS2->Integral()/h900MCSignalPFDijetS2->Integral());
   h900MCSignalPFDijetS2->SetTitle("Signal sector 2 in CASTOR for central dijets events at 900 GeV");
   h900MCSignalPFDijetS2->Draw("hist");
   h900SignalPFDijetS2->SetFillColor(0);
   h900SignalPFDijetS2->SetFillStyle(0);
   h900SignalPFDijetS2->SetMarkerStyle(1);
   h900SignalPFDijetS2->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_sectors->cd(3);
   h900MCSignalPFDijetS3->SetFillColor(8);
   h900MCSignalPFDijetS3->SetFillStyle(1001);
   h900MCSignalPFDijetS3->SetMarkerStyle(0);
   h900MCSignalPFDijetS3->Scale(h900SignalPFDijetS3->Integral()/h900MCSignalPFDijetS3->Integral());
   h900MCSignalPFDijetS3->SetTitle("Signal sector 3 in CASTOR for central dijets events at 900 GeV");
   h900MCSignalPFDijetS3->Draw("hist");
   h900SignalPFDijetS3->SetFillColor(0);
   h900SignalPFDijetS3->SetFillStyle(0);
   h900SignalPFDijetS3->SetMarkerStyle(1);
   h900SignalPFDijetS3->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_sectors->cd(4);
   h900MCSignalPFDijetS4->SetFillColor(8);
   h900MCSignalPFDijetS4->SetFillStyle(1001);
   h900MCSignalPFDijetS4->SetMarkerStyle(0);
   h900MCSignalPFDijetS4->Scale(h900SignalPFDijetS4->Integral()/h900MCSignalPFDijetS4->Integral());
   h900MCSignalPFDijetS4->SetTitle("Signal sector 4 in CASTOR for central dijets events at 900 GeV");
   h900MCSignalPFDijetS4->Draw("hist");
   h900SignalPFDijetS4->SetFillColor(0);
   h900SignalPFDijetS4->SetFillStyle(0);
   h900SignalPFDijetS4->SetMarkerStyle(1);
   h900SignalPFDijetS4->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_sectors->cd(5);
   h900MCSignalPFDijetS5->SetFillColor(8);
   h900MCSignalPFDijetS5->SetFillStyle(1001);
   h900MCSignalPFDijetS5->SetMarkerStyle(0);
   h900MCSignalPFDijetS5->Scale(h900SignalPFDijetS5->Integral()/h900MCSignalPFDijetS5->Integral());
   h900MCSignalPFDijetS5->SetTitle("Signal sector 5 in CASTOR for central dijets events at 900 GeV");
   h900MCSignalPFDijetS5->Draw("hist");
   h900SignalPFDijetS5->SetFillColor(0);
   h900SignalPFDijetS5->SetFillStyle(0);
   h900SignalPFDijetS5->SetMarkerStyle(1);
   h900SignalPFDijetS5->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_sectors->cd(6);
   h900MCSignalPFDijetS6->SetFillColor(8);
   h900MCSignalPFDijetS6->SetFillStyle(1001);
   h900MCSignalPFDijetS6->SetMarkerStyle(0);
   h900MCSignalPFDijetS6->Scale(h900SignalPFDijetS6->Integral()/h900MCSignalPFDijetS6->Integral());
   h900MCSignalPFDijetS6->SetTitle("Signal sector 6 in CASTOR for central dijets events at 900 GeV");
   h900MCSignalPFDijetS6->Draw("hist");
   h900SignalPFDijetS6->SetFillColor(0);
   h900SignalPFDijetS6->SetFillStyle(0);
   h900SignalPFDijetS6->SetMarkerStyle(1);
   h900SignalPFDijetS6->Draw("samee");
   leg900MCDijet->Draw();
   
   cPFDijet900GeV_sectors->cd(7);
   h900MCSignalPFDijetS7->SetFillColor(8);
   h900MCSignalPFDijetS7->SetFillStyle(1001);
   h900MCSignalPFDijetS7->SetMarkerStyle(0);
   h900MCSignalPFDijetS7->Scale(h900SignalPFDijetS7->Integral()/h900MCSignalPFDijetS7->Integral());
   h900MCSignalPFDijetS7->SetTitle("Signal sector 7 in CASTOR for MB events at 900 GeV");
   h900MCSignalPFDijetS7->Draw("hist");
   h900SignalPFDijetS7->SetFillColor(0);
   h900SignalPFDijetS7->SetFillStyle(0);
   h900SignalPFDijetS7->SetMarkerStyle(1);
   h900SignalPFDijetS7->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_sectors->cd(8);
   h900MCSignalPFDijetS8->SetFillColor(8);
   h900MCSignalPFDijetS8->SetFillStyle(1001);
   h900MCSignalPFDijetS8->SetMarkerStyle(0);
   h900MCSignalPFDijetS8->Scale(h900SignalPFDijetS8->Integral()/h900MCSignalPFDijetS8->Integral());
   h900MCSignalPFDijetS8->SetTitle("Signal sector 8 in CASTOR for MB events at 900 GeV");
   h900MCSignalPFDijetS8->Draw("hist");
   h900SignalPFDijetS8->SetFillColor(0);
   h900SignalPFDijetS8->SetFillStyle(0);
   h900SignalPFDijetS8->SetMarkerStyle(1);
   h900SignalPFDijetS8->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_sectors->cd(9);
   h900MCSignalPFDijetS9->SetFillColor(8);
   h900MCSignalPFDijetS9->SetFillStyle(1001);
   h900MCSignalPFDijetS9->SetMarkerStyle(0);
   h900MCSignalPFDijetS9->Scale(h900SignalPFDijetS9->Integral()/h900MCSignalPFDijetS9->Integral());
   h900MCSignalPFDijetS9->SetTitle("Signal sector 9 in CASTOR for MB events at 900 GeV");
   h900MCSignalPFDijetS9->Draw("hist");
   h900SignalPFDijetS9->SetFillColor(0);
   h900SignalPFDijetS9->SetFillStyle(0);
   h900SignalPFDijetS9->SetMarkerStyle(1);
   h900SignalPFDijetS9->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_sectors->cd(10);
   h900MCSignalPFDijetS10->SetFillColor(8);
   h900MCSignalPFDijetS10->SetFillStyle(1001);
   h900MCSignalPFDijetS10->SetMarkerStyle(0);
   h900MCSignalPFDijetS10->Scale(h900SignalPFDijetS10->Integral()/h900MCSignalPFDijetS10->Integral());
   h900MCSignalPFDijetS10->SetTitle("Signal sector 10 in CASTOR for MB events at 900 GeV");
   h900MCSignalPFDijetS10->Draw("hist");
   h900SignalPFDijetS10->SetFillColor(0);
   h900SignalPFDijetS10->SetFillStyle(0);
   h900SignalPFDijetS10->SetMarkerStyle(1);
   h900SignalPFDijetS10->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_sectors->cd(11);
   h900MCSignalPFDijetS11->SetFillColor(8);
   h900MCSignalPFDijetS11->SetFillStyle(1001);
   h900MCSignalPFDijetS11->SetMarkerStyle(0);
   h900MCSignalPFDijetS11->Scale(h900SignalPFDijetS11->Integral()/h900MCSignalPFDijetS11->Integral());
   h900MCSignalPFDijetS11->SetTitle("Signal sector 11 in CASTOR for MB events at 900 GeV");
   h900MCSignalPFDijetS11->Draw("hist");
   h900SignalPFDijetS11->SetFillColor(0);
   h900SignalPFDijetS11->SetFillStyle(0);
   h900SignalPFDijetS11->SetMarkerStyle(1);
   h900SignalPFDijetS11->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_sectors->cd(12);
   h900MCSignalPFDijetS12->SetFillColor(8);
   h900MCSignalPFDijetS12->SetFillStyle(1001);
   h900MCSignalPFDijetS12->SetMarkerStyle(0);
   h900MCSignalPFDijetS12->Scale(h900SignalPFDijetS12->Integral()/h900MCSignalPFDijetS12->Integral());
   h900MCSignalPFDijetS12->SetTitle("Signal sector 12 in CASTOR for MB events at 900 GeV");
   h900MCSignalPFDijetS12->Draw("hist");
   h900SignalPFDijetS12->SetFillColor(0);
   h900SignalPFDijetS12->SetFillStyle(0);
   h900SignalPFDijetS12->SetMarkerStyle(1);
   h900SignalPFDijetS12->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_sectors->cd(13);
   h900MCSignalPFDijetS13->SetFillColor(8);
   h900MCSignalPFDijetS13->SetFillStyle(1001);
   h900MCSignalPFDijetS13->SetMarkerStyle(0);
   h900MCSignalPFDijetS13->Scale(h900SignalPFDijetS13->Integral()/h900MCSignalPFDijetS13->Integral());
   h900MCSignalPFDijetS13->SetTitle("Signal sector 13 in CASTOR for MB events at 900 GeV");
   h900MCSignalPFDijetS13->Draw("hist");
   h900SignalPFDijetS13->SetFillColor(0);
   h900SignalPFDijetS13->SetFillStyle(0);
   h900SignalPFDijetS13->SetMarkerStyle(1);
   h900SignalPFDijetS13->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_sectors->cd(14);
   h900MCSignalPFDijetS14->SetFillColor(8);
   h900MCSignalPFDijetS14->SetFillStyle(1001);
   h900MCSignalPFDijetS14->SetMarkerStyle(0);
   h900MCSignalPFDijetS14->Scale(h900SignalPFDijetS14->Integral()/h900MCSignalPFDijetS14->Integral());
   h900MCSignalPFDijetS14->SetTitle("Signal sector 14 in CASTOR for MB events at 900 GeV");
   h900MCSignalPFDijetS14->Draw("hist");
   h900SignalPFDijetS14->SetFillColor(0);
   h900SignalPFDijetS14->SetFillStyle(0);
   h900SignalPFDijetS14->SetMarkerStyle(1);
   h900SignalPFDijetS14->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_sectors->cd(15);
   h900MCSignalPFDijetS15->SetFillColor(8);
   h900MCSignalPFDijetS15->SetFillStyle(1001);
   h900MCSignalPFDijetS15->SetMarkerStyle(0);
   h900MCSignalPFDijetS15->Scale(h900SignalPFDijetS15->Integral()/h900MCSignalPFDijetS15->Integral());
   h900MCSignalPFDijetS15->SetTitle("Signal sector 15 in CASTOR for MB events at 900 GeV");
   h900MCSignalPFDijetS15->Draw("hist");
   h900SignalPFDijetS15->SetFillColor(0);
   h900SignalPFDijetS15->SetFillStyle(0);
   h900SignalPFDijetS15->SetMarkerStyle(1);
   h900SignalPFDijetS15->Draw("samee");
   leg900MCDijet->Draw();
   cPFDijet900GeV_sectors->cd(16);
   h900MCSignalPFDijetS16->SetFillColor(8);
   h900MCSignalPFDijetS16->SetFillStyle(1001);
   h900MCSignalPFDijetS16->SetMarkerStyle(0);
   h900MCSignalPFDijetS16->Scale(h900SignalPFDijetS16->Integral()/h900MCSignalPFDijetS16->Integral());
   h900MCSignalPFDijetS16->SetTitle("Signal sector 16 in CASTOR for MB events at 900 GeV");
   h900MCSignalPFDijetS16->Draw("hist");
   h900SignalPFDijetS16->SetFillColor(0);
   h900SignalPFDijetS16->SetFillStyle(0);
   h900SignalPFDijetS16->SetMarkerStyle(1);
   h900SignalPFDijetS16->Draw("samee");
   leg900MCDijet->Draw();
   
   ////////////////////////////////////////////
   // plot module and sector stuff for 2360GeV
   ////////////////////////////////////////////
   
      TCanvas *ceflow2360GeV_modules = new TCanvas("ceflow2360GeV_modules","Signal distributions in CASTOR");
   ceflow2360GeV_modules->Divide(3,2);
   ceflow2360GeV_modules->cd(1);
   h2360MCSignalM1->SetFillColor(8);
   h2360MCSignalM1->SetFillStyle(1001);
   h2360MCSignalM1->SetMarkerStyle(0);
   h2360MCSignalM1->Scale(h2360SignalM1->Integral()/h2360MCSignalM1->Integral());
   h2360MCSignalM1->SetTitle("Signal module 1 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalM1->Draw("hist");
   h2360SignalM1->SetFillColor(0);
   h2360SignalM1->SetFillStyle(0);
   h2360SignalM1->SetMarkerStyle(1);
   h2360SignalM1->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_modules->cd(2);
   h2360MCSignalM2->SetFillColor(8);
   h2360MCSignalM2->SetFillStyle(1001);
   h2360MCSignalM2->SetMarkerStyle(0);
   h2360MCSignalM2->Scale(h2360SignalM2->Integral()/h2360MCSignalM2->Integral());
   h2360MCSignalM2->SetTitle("Signal module 2 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalM2->Draw("hist");
   h2360SignalM2->SetFillColor(0);
   h2360SignalM2->SetFillStyle(0);
   h2360SignalM2->SetMarkerStyle(1);
   h2360SignalM2->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_modules->cd(3);
   h2360MCSignalM3->SetFillColor(8);
   h2360MCSignalM3->SetFillStyle(1001);
   h2360MCSignalM3->SetMarkerStyle(0);
   h2360MCSignalM3->Scale(h2360SignalM3->Integral()/h2360MCSignalM3->Integral());
   h2360MCSignalM3->SetTitle("Signal module 3 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalM3->Draw("hist");
   h2360SignalM3->SetFillColor(0);
   h2360SignalM3->SetFillStyle(0);
   h2360SignalM3->SetMarkerStyle(1);
   h2360SignalM3->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_modules->cd(4);
   h2360MCSignalM4->SetFillColor(8);
   h2360MCSignalM4->SetFillStyle(1001);
   h2360MCSignalM4->SetMarkerStyle(0);
   h2360MCSignalM4->Scale(h2360SignalM4->Integral()/h2360MCSignalM4->Integral());
   h2360MCSignalM4->SetTitle("Signal module 4 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalM4->Draw("hist");
   h2360SignalM4->SetFillColor(0);
   h2360SignalM4->SetFillStyle(0);
   h2360SignalM4->SetMarkerStyle(1);
   h2360SignalM4->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_modules->cd(5);
   h2360MCSignalM5->SetFillColor(8);
   h2360MCSignalM5->SetFillStyle(1001);
   h2360MCSignalM5->SetMarkerStyle(0);
   h2360MCSignalM5->Scale(h2360SignalM5->Integral()/h2360MCSignalM5->Integral());
   h2360MCSignalM5->SetTitle("Signal module 5 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalM5->Draw("hist");
   h2360SignalM5->SetFillColor(0);
   h2360SignalM5->SetFillStyle(0);
   h2360SignalM5->SetMarkerStyle(1);
   h2360SignalM5->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_modules->cd(6);
   h2360MCSignalM6->SetFillColor(8);
   h2360MCSignalM6->SetFillStyle(1001);
   h2360MCSignalM6->SetMarkerStyle(0);
   h2360MCSignalM6->Scale(h2360SignalM6->Integral()/h2360MCSignalM6->Integral());
   h2360MCSignalM6->SetTitle("Signal module 6 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalM6->Draw("hist");
   h2360SignalM6->SetFillColor(0);
   h2360SignalM6->SetFillStyle(0);
   h2360SignalM6->SetMarkerStyle(1);
   h2360SignalM6->Draw("samee");
   leg2360MCDijet->Draw();
   /*
   ceflow2360GeV_modules->cd(7);
   h2360MCSignalM7->SetFillColor(8);
   h2360MCSignalM7->SetFillStyle(1001);
   h2360MCSignalM7->SetMarkerStyle(0);
   h2360MCSignalM7->Scale(h2360SignalM7->Integral()/h2360MCSignalM7->Integral());
   h2360MCSignalM7->SetTitle("Signal module 7 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalM7->Draw("hist");
   h2360SignalM7->SetFillColor(0);
   h2360SignalM7->SetFillStyle(0);
   h2360SignalM7->SetMarkerStyle(1);
   h2360SignalM7->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_modules->cd(8);
   h2360MCSignalM8->SetFillColor(8);
   h2360MCSignalM8->SetFillStyle(1001);
   h2360MCSignalM8->SetMarkerStyle(0);
   h2360MCSignalM8->Scale(h2360SignalM8->Integral()/h2360MCSignalM8->Integral());
   h2360MCSignalM8->SetTitle("Signal module 8 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalM8->Draw("hist");
   h2360SignalM8->SetFillColor(0);
   h2360SignalM8->SetFillStyle(0);
   h2360SignalM8->SetMarkerStyle(1);
   h2360SignalM8->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_modules->cd(9);
   h2360MCSignalM9->SetFillColor(8);
   h2360MCSignalM9->SetFillStyle(1001);
   h2360MCSignalM9->SetMarkerStyle(0);
   h2360MCSignalM9->Scale(h2360SignalM9->Integral()/h2360MCSignalM9->Integral());
   h2360MCSignalM9->SetTitle("Signal module 9 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalM9->Draw("hist");
   h2360SignalM9->SetFillColor(0);
   h2360SignalM9->SetFillStyle(0);
   h2360SignalM9->SetMarkerStyle(1);
   h2360SignalM9->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_modules->cd(10);
   h2360MCSignalM10->SetFillColor(8);
   h2360MCSignalM10->SetFillStyle(1001);
   h2360MCSignalM10->SetMarkerStyle(0);
   h2360MCSignalM10->Scale(h2360SignalM10->Integral()/h2360MCSignalM10->Integral());
   h2360MCSignalM10->SetTitle("Signal module 10 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalM10->Draw("hist");
   h2360SignalM10->SetFillColor(0);
   h2360SignalM10->SetFillStyle(0);
   h2360SignalM10->SetMarkerStyle(1);
   h2360SignalM10->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_modules->cd(11);
   h2360MCSignalM11->SetFillColor(8);
   h2360MCSignalM11->SetFillStyle(1001);
   h2360MCSignalM11->SetMarkerStyle(0);
   h2360MCSignalM11->Scale(h2360SignalM11->Integral()/h2360MCSignalM11->Integral());
   h2360MCSignalM11->SetTitle("Signal module 11 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalM11->Draw("hist");
   h2360SignalM11->SetFillColor(0);
   h2360SignalM11->SetFillStyle(0);
   h2360SignalM11->SetMarkerStyle(1);
   h2360SignalM11->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_modules->cd(12);
   h2360MCSignalM12->SetFillColor(8);
   h2360MCSignalM12->SetFillStyle(1001);
   h2360MCSignalM12->SetMarkerStyle(0);
   h2360MCSignalM12->Scale(h2360SignalM12->Integral()/h2360MCSignalM12->Integral());
   h2360MCSignalM12->SetTitle("Signal module 12 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalM12->Draw("hist");
   h2360SignalM12->SetFillColor(0);
   h2360SignalM12->SetFillStyle(0);
   h2360SignalM12->SetMarkerStyle(1);
   h2360SignalM12->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_modules->cd(13);
   h2360MCSignalM13->SetFillColor(8);
   h2360MCSignalM13->SetFillStyle(1001);
   h2360MCSignalM13->SetMarkerStyle(0);
   h2360MCSignalM13->Scale(h2360SignalM13->Integral()/h2360MCSignalM13->Integral());
   h2360MCSignalM13->SetTitle("Signal module 13 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalM13->Draw("hist");
   h2360SignalM13->SetFillColor(0);
   h2360SignalM13->SetFillStyle(0);
   h2360SignalM13->SetMarkerStyle(1);
   h2360SignalM13->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_modules->cd(14);
   h2360MCSignalM14->SetFillColor(8);
   h2360MCSignalM14->SetFillStyle(1001);
   h2360MCSignalM14->SetMarkerStyle(0);
   h2360MCSignalM14->Scale(h2360SignalM14->Integral()/h2360MCSignalM14->Integral());
   h2360MCSignalM14->SetTitle("Signal module 14 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalM14->Draw("hist");
   h2360SignalM14->SetFillColor(0);
   h2360SignalM14->SetFillStyle(0);
   h2360SignalM14->SetMarkerStyle(1);
   h2360SignalM14->Draw("samee");
   leg2360MCDijet->Draw();
   */
   
   TCanvas *cPFDijet2360GeV_modules = new TCanvas("cPFDijet2360GeV_modules","Signal distributions in CASTOR");
   cPFDijet2360GeV_modules->Divide(3,2);
   cPFDijet2360GeV_modules->cd(1);
   h2360MCSignalPFDijetM1->SetFillColor(8);
   h2360MCSignalPFDijetM1->SetFillStyle(1001);
   h2360MCSignalPFDijetM1->SetMarkerStyle(0);
   h2360MCSignalPFDijetM1->Scale(h2360SignalPFDijetM1->Integral()/h2360MCSignalPFDijetM1->Integral());
   h2360MCSignalPFDijetM1->SetTitle("Signal module 1 in CASTOR for central dijets events at 2360 GeV");
   h2360MCSignalPFDijetM1->Draw("hist");
   h2360SignalPFDijetM1->SetFillColor(0);
   h2360SignalPFDijetM1->SetFillStyle(0);
   h2360SignalPFDijetM1->SetMarkerStyle(1);
   h2360SignalPFDijetM1->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_modules->cd(2);
   h2360MCSignalPFDijetM2->SetFillColor(8);
   h2360MCSignalPFDijetM2->SetFillStyle(1001);
   h2360MCSignalPFDijetM2->SetMarkerStyle(0);
   h2360MCSignalPFDijetM2->Scale(h2360SignalPFDijetM2->Integral()/h2360MCSignalPFDijetM2->Integral());
   h2360MCSignalPFDijetM2->SetTitle("Signal module 2 in CASTOR for central dijets events at 2360 GeV");
   h2360MCSignalPFDijetM2->Draw("hist");
   h2360SignalPFDijetM2->SetFillColor(0);
   h2360SignalPFDijetM2->SetFillStyle(0);
   h2360SignalPFDijetM2->SetMarkerStyle(1);
   h2360SignalPFDijetM2->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_modules->cd(3);
   h2360MCSignalPFDijetM3->SetFillColor(8);
   h2360MCSignalPFDijetM3->SetFillStyle(1001);
   h2360MCSignalPFDijetM3->SetMarkerStyle(0);
   h2360MCSignalPFDijetM3->Scale(h2360SignalPFDijetM3->Integral()/h2360MCSignalPFDijetM3->Integral());
   h2360MCSignalPFDijetM3->SetTitle("Signal module 3 in CASTOR for central dijets events at 2360 GeV");
   h2360MCSignalPFDijetM3->Draw("hist");
   h2360SignalPFDijetM3->SetFillColor(0);
   h2360SignalPFDijetM3->SetFillStyle(0);
   h2360SignalPFDijetM3->SetMarkerStyle(1);
   h2360SignalPFDijetM3->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_modules->cd(4);
   h2360MCSignalPFDijetM4->SetFillColor(8);
   h2360MCSignalPFDijetM4->SetFillStyle(1001);
   h2360MCSignalPFDijetM4->SetMarkerStyle(0);
   h2360MCSignalPFDijetM4->Scale(h2360SignalPFDijetM4->Integral()/h2360MCSignalPFDijetM4->Integral());
   h2360MCSignalPFDijetM4->SetTitle("Signal module 4 in CASTOR for central dijets events at 2360 GeV");
   h2360MCSignalPFDijetM4->Draw("hist");
   h2360SignalPFDijetM4->SetFillColor(0);
   h2360SignalPFDijetM4->SetFillStyle(0);
   h2360SignalPFDijetM4->SetMarkerStyle(1);
   h2360SignalPFDijetM4->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_modules->cd(5);
   h2360MCSignalPFDijetM5->SetFillColor(8);
   h2360MCSignalPFDijetM5->SetFillStyle(1001);
   h2360MCSignalPFDijetM5->SetMarkerStyle(0);
   h2360MCSignalPFDijetM5->Scale(h2360SignalPFDijetM5->Integral()/h2360MCSignalPFDijetM5->Integral());
   h2360MCSignalPFDijetM5->SetTitle("Signal module 5 in CASTOR for central dijets events at 2360 GeV");
   h2360MCSignalPFDijetM5->Draw("hist");
   h2360SignalPFDijetM5->SetFillColor(0);
   h2360SignalPFDijetM5->SetFillStyle(0);
   h2360SignalPFDijetM5->SetMarkerStyle(1);
   h2360SignalPFDijetM5->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_modules->cd(6);
   h2360MCSignalPFDijetM6->SetFillColor(8);
   h2360MCSignalPFDijetM6->SetFillStyle(1001);
   h2360MCSignalPFDijetM6->SetMarkerStyle(0);
   h2360MCSignalPFDijetM6->Scale(h2360SignalPFDijetM6->Integral()/h2360MCSignalPFDijetM6->Integral());
   h2360MCSignalPFDijetM6->SetTitle("Signal module 6 in CASTOR for central dijets events at 2360 GeV");
   h2360MCSignalPFDijetM6->Draw("hist");
   h2360SignalPFDijetM6->SetFillColor(0);
   h2360SignalPFDijetM6->SetFillStyle(0);
   h2360SignalPFDijetM6->SetMarkerStyle(1);
   h2360SignalPFDijetM6->Draw("samee");
   leg2360MCDijet->Draw();
   
   // sectors
   
  TCanvas *ceflow2360GeV_sectors = new TCanvas("ceflow2360GeV_sectors","Signal distributions in CASTOR");
   ceflow2360GeV_sectors->Divide(4,4);
   ceflow2360GeV_sectors->cd(1);
   //ceflow2360GeV_sectors_1->SetLogY();
   h2360MCSignalS1->SetFillColor(8);
   h2360MCSignalS1->SetFillStyle(1001);
   h2360MCSignalS1->SetMarkerStyle(0);
   h2360MCSignalS1->Scale(h2360SignalS1->Integral()/h2360MCSignalS1->Integral());
   h2360MCSignalS1->SetTitle("Signal sector 1 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalS1->Draw("hist");
   h2360SignalS1->SetFillColor(0);
   h2360SignalS1->SetFillStyle(0);
   h2360SignalS1->SetMarkerStyle(1);
   h2360SignalS1->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_sectors->cd(2);
   h2360MCSignalS2->SetFillColor(8);
   h2360MCSignalS2->SetFillStyle(1001);
   h2360MCSignalS2->SetMarkerStyle(0);
   h2360MCSignalS2->Scale(h2360SignalS2->Integral()/h2360MCSignalS2->Integral());
   h2360MCSignalS2->SetTitle("Signal sector 2 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalS2->Draw("hist");
   h2360SignalS2->SetFillColor(0);
   h2360SignalS2->SetFillStyle(0);
   h2360SignalS2->SetMarkerStyle(1);
   h2360SignalS2->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_sectors->cd(3);
   h2360MCSignalS3->SetFillColor(8);
   h2360MCSignalS3->SetFillStyle(1001);
   h2360MCSignalS3->SetMarkerStyle(0);
   h2360MCSignalS3->Scale(h2360SignalS3->Integral()/h2360MCSignalS3->Integral());
   h2360MCSignalS3->SetTitle("Signal sector 3 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalS3->Draw("hist");
   h2360SignalS3->SetFillColor(0);
   h2360SignalS3->SetFillStyle(0);
   h2360SignalS3->SetMarkerStyle(1);
   h2360SignalS3->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_sectors->cd(4);
   h2360MCSignalS4->SetFillColor(8);
   h2360MCSignalS4->SetFillStyle(1001);
   h2360MCSignalS4->SetMarkerStyle(0);
   h2360MCSignalS4->Scale(h2360SignalS4->Integral()/h2360MCSignalS4->Integral());
   h2360MCSignalS4->SetTitle("Signal sector 4 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalS4->Draw("hist");
   h2360SignalS4->SetFillColor(0);
   h2360SignalS4->SetFillStyle(0);
   h2360SignalS4->SetMarkerStyle(1);
   h2360SignalS4->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_sectors->cd(5);
   h2360MCSignalS5->SetFillColor(8);
   h2360MCSignalS5->SetFillStyle(1001);
   h2360MCSignalS5->SetMarkerStyle(0);
   h2360MCSignalS5->Scale(h2360SignalS5->Integral()/h2360MCSignalS5->Integral());
   h2360MCSignalS5->SetTitle("Signal sector 5 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalS5->Draw("hist");
   h2360SignalS5->SetFillColor(0);
   h2360SignalS5->SetFillStyle(0);
   h2360SignalS5->SetMarkerStyle(1);
   h2360SignalS5->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_sectors->cd(6);
   h2360MCSignalS6->SetFillColor(8);
   h2360MCSignalS6->SetFillStyle(1001);
   h2360MCSignalS6->SetMarkerStyle(0);
   h2360MCSignalS6->Scale(h2360SignalS6->Integral()/h2360MCSignalS6->Integral());
   h2360MCSignalS6->SetTitle("Signal sector 6 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalS6->Draw("hist");
   h2360SignalS6->SetFillColor(0);
   h2360SignalS6->SetFillStyle(0);
   h2360SignalS6->SetMarkerStyle(1);
   h2360SignalS6->Draw("samee");
   leg2360MCDijet->Draw();
   
   ceflow2360GeV_sectors->cd(7);
   h2360MCSignalS7->SetFillColor(8);
   h2360MCSignalS7->SetFillStyle(1001);
   h2360MCSignalS7->SetMarkerStyle(0);
   h2360MCSignalS7->Scale(h2360SignalS7->Integral()/h2360MCSignalS7->Integral());
   h2360MCSignalS7->SetTitle("Signal sector 7 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalS7->Draw("hist");
   h2360SignalS7->SetFillColor(0);
   h2360SignalS7->SetFillStyle(0);
   h2360SignalS7->SetMarkerStyle(1);
   h2360SignalS7->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_sectors->cd(8);
   h2360MCSignalS8->SetFillColor(8);
   h2360MCSignalS8->SetFillStyle(1001);
   h2360MCSignalS8->SetMarkerStyle(0);
   h2360MCSignalS8->Scale(h2360SignalS8->Integral()/h2360MCSignalS8->Integral());
   h2360MCSignalS8->SetTitle("Signal sector 8 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalS8->Draw("hist");
   h2360SignalS8->SetFillColor(0);
   h2360SignalS8->SetFillStyle(0);
   h2360SignalS8->SetMarkerStyle(1);
   h2360SignalS8->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_sectors->cd(9);
   h2360MCSignalS9->SetFillColor(8);
   h2360MCSignalS9->SetFillStyle(1001);
   h2360MCSignalS9->SetMarkerStyle(0);
   h2360MCSignalS9->Scale(h2360SignalS9->Integral()/h2360MCSignalS9->Integral());
   h2360MCSignalS9->SetTitle("Signal sector 9 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalS9->Draw("hist");
   h2360SignalS9->SetFillColor(0);
   h2360SignalS9->SetFillStyle(0);
   h2360SignalS9->SetMarkerStyle(1);
   h2360SignalS9->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_sectors->cd(10);
   h2360MCSignalS10->SetFillColor(8);
   h2360MCSignalS10->SetFillStyle(1001);
   h2360MCSignalS10->SetMarkerStyle(0);
   h2360MCSignalS10->Scale(h2360SignalS10->Integral()/h2360MCSignalS10->Integral());
   h2360MCSignalS10->SetTitle("Signal sector 10 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalS10->Draw("hist");
   h2360SignalS10->SetFillColor(0);
   h2360SignalS10->SetFillStyle(0);
   h2360SignalS10->SetMarkerStyle(1);
   h2360SignalS10->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_sectors->cd(11);
   h2360MCSignalS11->SetFillColor(8);
   h2360MCSignalS11->SetFillStyle(1001);
   h2360MCSignalS11->SetMarkerStyle(0);
   h2360MCSignalS11->Scale(h2360SignalS11->Integral()/h2360MCSignalS11->Integral());
   h2360MCSignalS11->SetTitle("Signal sector 11 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalS11->Draw("hist");
   h2360SignalS11->SetFillColor(0);
   h2360SignalS11->SetFillStyle(0);
   h2360SignalS11->SetMarkerStyle(1);
   h2360SignalS11->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_sectors->cd(12);
   h2360MCSignalS12->SetFillColor(8);
   h2360MCSignalS12->SetFillStyle(1001);
   h2360MCSignalS12->SetMarkerStyle(0);
   h2360MCSignalS12->Scale(h2360SignalS12->Integral()/h2360MCSignalS12->Integral());
   h2360MCSignalS12->SetTitle("Signal sector 12 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalS12->Draw("hist");
   h2360SignalS12->SetFillColor(0);
   h2360SignalS12->SetFillStyle(0);
   h2360SignalS12->SetMarkerStyle(1);
   h2360SignalS12->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_sectors->cd(13);
   h2360MCSignalS13->SetFillColor(8);
   h2360MCSignalS13->SetFillStyle(1001);
   h2360MCSignalS13->SetMarkerStyle(0);
   h2360MCSignalS13->Scale(h2360SignalS13->Integral()/h2360MCSignalS13->Integral());
   h2360MCSignalS13->SetTitle("Signal sector 13 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalS13->Draw("hist");
   h2360SignalS13->SetFillColor(0);
   h2360SignalS13->SetFillStyle(0);
   h2360SignalS13->SetMarkerStyle(1);
   h2360SignalS13->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_sectors->cd(14);
   h2360MCSignalS14->SetFillColor(8);
   h2360MCSignalS14->SetFillStyle(1001);
   h2360MCSignalS14->SetMarkerStyle(0);
   h2360MCSignalS14->Scale(h2360SignalS14->Integral()/h2360MCSignalS14->Integral());
   h2360MCSignalS14->SetTitle("Signal sector 14 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalS14->Draw("hist");
   h2360SignalS14->SetFillColor(0);
   h2360SignalS14->SetFillStyle(0);
   h2360SignalS14->SetMarkerStyle(1);
   h2360SignalS14->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_sectors->cd(15);
   h2360MCSignalS15->SetFillColor(8);
   h2360MCSignalS15->SetFillStyle(1001);
   h2360MCSignalS15->SetMarkerStyle(0);
   h2360MCSignalS15->Scale(h2360SignalS15->Integral()/h2360MCSignalS15->Integral());
   h2360MCSignalS15->SetTitle("Signal sector 15 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalS15->Draw("hist");
   h2360SignalS15->SetFillColor(0);
   h2360SignalS15->SetFillStyle(0);
   h2360SignalS15->SetMarkerStyle(1);
   h2360SignalS15->Draw("samee");
   leg2360MCDijet->Draw();
   ceflow2360GeV_sectors->cd(16);
   h2360MCSignalS16->SetFillColor(8);
   h2360MCSignalS16->SetFillStyle(1001);
   h2360MCSignalS16->SetMarkerStyle(0);
   h2360MCSignalS16->Scale(h2360SignalS16->Integral()/h2360MCSignalS16->Integral());
   h2360MCSignalS16->SetTitle("Signal sector 16 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalS16->Draw("hist");
   h2360SignalS16->SetFillColor(0);
   h2360SignalS16->SetFillStyle(0);
   h2360SignalS16->SetMarkerStyle(1);
   h2360SignalS16->Draw("samee");
   leg2360MCDijet->Draw();
   
   
   TCanvas *cPFDijet2360GeV_sectors = new TCanvas("cPFDijet2360GeV_sectors","Signal distributions in CASTOR");
   cPFDijet2360GeV_sectors->Divide(4,4);
   cPFDijet2360GeV_sectors->cd(1);
   h2360MCSignalPFDijetS1->SetFillColor(8);
   h2360MCSignalPFDijetS1->SetFillStyle(1001);
   h2360MCSignalPFDijetS1->SetMarkerStyle(0);
   h2360MCSignalPFDijetS1->Scale(h2360SignalPFDijetS1->Integral()/h2360MCSignalPFDijetS1->Integral());
   h2360MCSignalPFDijetS1->SetTitle("Signal sector 1 in CASTOR for central dijets events at 2360 GeV");
   h2360MCSignalPFDijetS1->Draw("hist");
   h2360SignalPFDijetS1->SetFillColor(0);
   h2360SignalPFDijetS1->SetFillStyle(0);
   h2360SignalPFDijetS1->SetMarkerStyle(1);
   h2360SignalPFDijetS1->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_sectors->cd(2);
   h2360MCSignalPFDijetS2->SetFillColor(8);
   h2360MCSignalPFDijetS2->SetFillStyle(1001);
   h2360MCSignalPFDijetS2->SetMarkerStyle(0);
   h2360MCSignalPFDijetS2->Scale(h2360SignalPFDijetS2->Integral()/h2360MCSignalPFDijetS2->Integral());
   h2360MCSignalPFDijetS2->SetTitle("Signal sector 2 in CASTOR for central dijets events at 2360 GeV");
   h2360MCSignalPFDijetS2->Draw("hist");
   h2360SignalPFDijetS2->SetFillColor(0);
   h2360SignalPFDijetS2->SetFillStyle(0);
   h2360SignalPFDijetS2->SetMarkerStyle(1);
   h2360SignalPFDijetS2->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_sectors->cd(3);
   h2360MCSignalPFDijetS3->SetFillColor(8);
   h2360MCSignalPFDijetS3->SetFillStyle(1001);
   h2360MCSignalPFDijetS3->SetMarkerStyle(0);
   h2360MCSignalPFDijetS3->Scale(h2360SignalPFDijetS3->Integral()/h2360MCSignalPFDijetS3->Integral());
   h2360MCSignalPFDijetS3->SetTitle("Signal sector 3 in CASTOR for central dijets events at 2360 GeV");
   h2360MCSignalPFDijetS3->Draw("hist");
   h2360SignalPFDijetS3->SetFillColor(0);
   h2360SignalPFDijetS3->SetFillStyle(0);
   h2360SignalPFDijetS3->SetMarkerStyle(1);
   h2360SignalPFDijetS3->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_sectors->cd(4);
   h2360MCSignalPFDijetS4->SetFillColor(8);
   h2360MCSignalPFDijetS4->SetFillStyle(1001);
   h2360MCSignalPFDijetS4->SetMarkerStyle(0);
   h2360MCSignalPFDijetS4->Scale(h2360SignalPFDijetS4->Integral()/h2360MCSignalPFDijetS4->Integral());
   h2360MCSignalPFDijetS4->SetTitle("Signal sector 4 in CASTOR for central dijets events at 2360 GeV");
   h2360MCSignalPFDijetS4->Draw("hist");
   h2360SignalPFDijetS4->SetFillColor(0);
   h2360SignalPFDijetS4->SetFillStyle(0);
   h2360SignalPFDijetS4->SetMarkerStyle(1);
   h2360SignalPFDijetS4->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_sectors->cd(5);
   h2360MCSignalPFDijetS5->SetFillColor(8);
   h2360MCSignalPFDijetS5->SetFillStyle(1001);
   h2360MCSignalPFDijetS5->SetMarkerStyle(0);
   h2360MCSignalPFDijetS5->Scale(h2360SignalPFDijetS5->Integral()/h2360MCSignalPFDijetS5->Integral());
   h2360MCSignalPFDijetS5->SetTitle("Signal sector 5 in CASTOR for central dijets events at 2360 GeV");
   h2360MCSignalPFDijetS5->Draw("hist");
   h2360SignalPFDijetS5->SetFillColor(0);
   h2360SignalPFDijetS5->SetFillStyle(0);
   h2360SignalPFDijetS5->SetMarkerStyle(1);
   h2360SignalPFDijetS5->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_sectors->cd(6);
   h2360MCSignalPFDijetS6->SetFillColor(8);
   h2360MCSignalPFDijetS6->SetFillStyle(1001);
   h2360MCSignalPFDijetS6->SetMarkerStyle(0);
   h2360MCSignalPFDijetS6->Scale(h2360SignalPFDijetS6->Integral()/h2360MCSignalPFDijetS6->Integral());
   h2360MCSignalPFDijetS6->SetTitle("Signal sector 6 in CASTOR for central dijets events at 2360 GeV");
   h2360MCSignalPFDijetS6->Draw("hist");
   h2360SignalPFDijetS6->SetFillColor(0);
   h2360SignalPFDijetS6->SetFillStyle(0);
   h2360SignalPFDijetS6->SetMarkerStyle(1);
   h2360SignalPFDijetS6->Draw("samee");
   leg2360MCDijet->Draw();
   
   cPFDijet2360GeV_sectors->cd(7);
   h2360MCSignalPFDijetS7->SetFillColor(8);
   h2360MCSignalPFDijetS7->SetFillStyle(1001);
   h2360MCSignalPFDijetS7->SetMarkerStyle(0);
   h2360MCSignalPFDijetS7->Scale(h2360SignalPFDijetS7->Integral()/h2360MCSignalPFDijetS7->Integral());
   h2360MCSignalPFDijetS7->SetTitle("Signal sector 7 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalPFDijetS7->Draw("hist");
   h2360SignalPFDijetS7->SetFillColor(0);
   h2360SignalPFDijetS7->SetFillStyle(0);
   h2360SignalPFDijetS7->SetMarkerStyle(1);
   h2360SignalPFDijetS7->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_sectors->cd(8);
   h2360MCSignalPFDijetS8->SetFillColor(8);
   h2360MCSignalPFDijetS8->SetFillStyle(1001);
   h2360MCSignalPFDijetS8->SetMarkerStyle(0);
   h2360MCSignalPFDijetS8->Scale(h2360SignalPFDijetS8->Integral()/h2360MCSignalPFDijetS8->Integral());
   h2360MCSignalPFDijetS8->SetTitle("Signal sector 8 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalPFDijetS8->Draw("hist");
   h2360SignalPFDijetS8->SetFillColor(0);
   h2360SignalPFDijetS8->SetFillStyle(0);
   h2360SignalPFDijetS8->SetMarkerStyle(1);
   h2360SignalPFDijetS8->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_sectors->cd(9);
   h2360MCSignalPFDijetS9->SetFillColor(8);
   h2360MCSignalPFDijetS9->SetFillStyle(1001);
   h2360MCSignalPFDijetS9->SetMarkerStyle(0);
   h2360MCSignalPFDijetS9->Scale(h2360SignalPFDijetS9->Integral()/h2360MCSignalPFDijetS9->Integral());
   h2360MCSignalPFDijetS9->SetTitle("Signal sector 9 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalPFDijetS9->Draw("hist");
   h2360SignalPFDijetS9->SetFillColor(0);
   h2360SignalPFDijetS9->SetFillStyle(0);
   h2360SignalPFDijetS9->SetMarkerStyle(1);
   h2360SignalPFDijetS9->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_sectors->cd(10);
   h2360MCSignalPFDijetS10->SetFillColor(8);
   h2360MCSignalPFDijetS10->SetFillStyle(1001);
   h2360MCSignalPFDijetS10->SetMarkerStyle(0);
   h2360MCSignalPFDijetS10->Scale(h2360SignalPFDijetS10->Integral()/h2360MCSignalPFDijetS10->Integral());
   h2360MCSignalPFDijetS10->SetTitle("Signal sector 10 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalPFDijetS10->Draw("hist");
   h2360SignalPFDijetS10->SetFillColor(0);
   h2360SignalPFDijetS10->SetFillStyle(0);
   h2360SignalPFDijetS10->SetMarkerStyle(1);
   h2360SignalPFDijetS10->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_sectors->cd(11);
   h2360MCSignalPFDijetS11->SetFillColor(8);
   h2360MCSignalPFDijetS11->SetFillStyle(1001);
   h2360MCSignalPFDijetS11->SetMarkerStyle(0);
   h2360MCSignalPFDijetS11->Scale(h2360SignalPFDijetS11->Integral()/h2360MCSignalPFDijetS11->Integral());
   h2360MCSignalPFDijetS11->SetTitle("Signal sector 11 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalPFDijetS11->Draw("hist");
   h2360SignalPFDijetS11->SetFillColor(0);
   h2360SignalPFDijetS11->SetFillStyle(0);
   h2360SignalPFDijetS11->SetMarkerStyle(1);
   h2360SignalPFDijetS11->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_sectors->cd(12);
   h2360MCSignalPFDijetS12->SetFillColor(8);
   h2360MCSignalPFDijetS12->SetFillStyle(1001);
   h2360MCSignalPFDijetS12->SetMarkerStyle(0);
   h2360MCSignalPFDijetS12->Scale(h2360SignalPFDijetS12->Integral()/h2360MCSignalPFDijetS12->Integral());
   h2360MCSignalPFDijetS12->SetTitle("Signal sector 12 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalPFDijetS12->Draw("hist");
   h2360SignalPFDijetS12->SetFillColor(0);
   h2360SignalPFDijetS12->SetFillStyle(0);
   h2360SignalPFDijetS12->SetMarkerStyle(1);
   h2360SignalPFDijetS12->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_sectors->cd(13);
   h2360MCSignalPFDijetS13->SetFillColor(8);
   h2360MCSignalPFDijetS13->SetFillStyle(1001);
   h2360MCSignalPFDijetS13->SetMarkerStyle(0);
   h2360MCSignalPFDijetS13->Scale(h2360SignalPFDijetS13->Integral()/h2360MCSignalPFDijetS13->Integral());
   h2360MCSignalPFDijetS13->SetTitle("Signal sector 13 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalPFDijetS13->Draw("hist");
   h2360SignalPFDijetS13->SetFillColor(0);
   h2360SignalPFDijetS13->SetFillStyle(0);
   h2360SignalPFDijetS13->SetMarkerStyle(1);
   h2360SignalPFDijetS13->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_sectors->cd(14);
   h2360MCSignalPFDijetS14->SetFillColor(8);
   h2360MCSignalPFDijetS14->SetFillStyle(1001);
   h2360MCSignalPFDijetS14->SetMarkerStyle(0);
   h2360MCSignalPFDijetS14->Scale(h2360SignalPFDijetS14->Integral()/h2360MCSignalPFDijetS14->Integral());
   h2360MCSignalPFDijetS14->SetTitle("Signal sector 14 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalPFDijetS14->Draw("hist");
   h2360SignalPFDijetS14->SetFillColor(0);
   h2360SignalPFDijetS14->SetFillStyle(0);
   h2360SignalPFDijetS14->SetMarkerStyle(1);
   h2360SignalPFDijetS14->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_sectors->cd(15);
   h2360MCSignalPFDijetS15->SetFillColor(8);
   h2360MCSignalPFDijetS15->SetFillStyle(1001);
   h2360MCSignalPFDijetS15->SetMarkerStyle(0);
   h2360MCSignalPFDijetS15->Scale(h2360SignalPFDijetS15->Integral()/h2360MCSignalPFDijetS15->Integral());
   h2360MCSignalPFDijetS15->SetTitle("Signal sector 15 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalPFDijetS15->Draw("hist");
   h2360SignalPFDijetS15->SetFillColor(0);
   h2360SignalPFDijetS15->SetFillStyle(0);
   h2360SignalPFDijetS15->SetMarkerStyle(1);
   h2360SignalPFDijetS15->Draw("samee");
   leg2360MCDijet->Draw();
   cPFDijet2360GeV_sectors->cd(16);
   h2360MCSignalPFDijetS16->SetFillColor(8);
   h2360MCSignalPFDijetS16->SetFillStyle(1001);
   h2360MCSignalPFDijetS16->SetMarkerStyle(0);
   h2360MCSignalPFDijetS16->Scale(h2360SignalPFDijetS16->Integral()/h2360MCSignalPFDijetS16->Integral());
   h2360MCSignalPFDijetS16->SetTitle("Signal sector 16 in CASTOR for MB events at 2360 GeV");
   h2360MCSignalPFDijetS16->Draw("hist");
   h2360SignalPFDijetS16->SetFillColor(0);
   h2360SignalPFDijetS16->SetFillStyle(0);
   h2360SignalPFDijetS16->SetMarkerStyle(1);
   h2360SignalPFDijetS16->Draw("samee");
   leg2360MCDijet->Draw();
   
   //////////////////////////////////////////////
   // plot ratios as a function of module -sector
   //////////////////////////////////////////////
   
   if (h900SignalM1->GetMean() != 0) h900RatiosModules->SetBinContent(1,h900SignalPFDijetM1->GetMean()/h900SignalM1->GetMean());
   if (h900SignalM2->GetMean() != 0) h900RatiosModules->SetBinContent(2,h900SignalPFDijetM2->GetMean()/h900SignalM2->GetMean());
   if (h900SignalM3->GetMean() != 0) h900RatiosModules->SetBinContent(3,h900SignalPFDijetM3->GetMean()/h900SignalM3->GetMean());
   if (h900SignalM4->GetMean() != 0) h900RatiosModules->SetBinContent(4,h900SignalPFDijetM4->GetMean()/h900SignalM4->GetMean());
   if (h900SignalM5->GetMean() != 0) h900RatiosModules->SetBinContent(5,h900SignalPFDijetM5->GetMean()/h900SignalM5->GetMean());
   if (h900SignalM6->GetMean() != 0) h900RatiosModules->SetBinContent(6,h900SignalPFDijetM6->GetMean()/h900SignalM6->GetMean());
   if (h900SignalM7->GetMean() != 0) h900RatiosModules->SetBinContent(7,h900SignalPFDijetM7->GetMean()/h900SignalM7->GetMean());
   if (h900SignalM8->GetMean() != 0) h900RatiosModules->SetBinContent(8,h900SignalPFDijetM8->GetMean()/h900SignalM8->GetMean());
   if (h900SignalM9->GetMean() != 0) h900RatiosModules->SetBinContent(9,h900SignalPFDijetM9->GetMean()/h900SignalM9->GetMean());
   if (h900SignalM10->GetMean() != 0) h900RatiosModules->SetBinContent(10,h900SignalPFDijetM10->GetMean()/h900SignalM10->GetMean());
   if (h900SignalM11->GetMean() != 0) h900RatiosModules->SetBinContent(11,h900SignalPFDijetM11->GetMean()/h900SignalM11->GetMean());
   if (h900SignalM12->GetMean() != 0) h900RatiosModules->SetBinContent(12,h900SignalPFDijetM12->GetMean()/h900SignalM12->GetMean());
   if (h900SignalM13->GetMean() != 0) h900RatiosModules->SetBinContent(13,h900SignalPFDijetM13->GetMean()/h900SignalM13->GetMean());
   if (h900SignalM14->GetMean() != 0) h900RatiosModules->SetBinContent(14,h900SignalPFDijetM14->GetMean()/h900SignalM14->GetMean());
   
   if (h900MCSignalM1->GetMean() != 0) h900RatiosModulesMC->SetBinContent(1,h900MCSignalPFDijetM1->GetMean()/h900MCSignalM1->GetMean());
   if (h900MCSignalM2->GetMean() != 0) h900RatiosModulesMC->SetBinContent(2,h900MCSignalPFDijetM2->GetMean()/h900MCSignalM2->GetMean());
   if (h900MCSignalM3->GetMean() != 0) h900RatiosModulesMC->SetBinContent(3,h900MCSignalPFDijetM3->GetMean()/h900MCSignalM3->GetMean());
   if (h900MCSignalM4->GetMean() != 0) h900RatiosModulesMC->SetBinContent(4,h900MCSignalPFDijetM4->GetMean()/h900MCSignalM4->GetMean());
   if (h900MCSignalM5->GetMean() != 0) h900RatiosModulesMC->SetBinContent(5,h900MCSignalPFDijetM5->GetMean()/h900MCSignalM5->GetMean());
   if (h900MCSignalM6->GetMean() != 0) h900RatiosModulesMC->SetBinContent(6,h900MCSignalPFDijetM6->GetMean()/h900MCSignalM6->GetMean());
   if (h900MCSignalM7->GetMean() != 0) h900RatiosModulesMC->SetBinContent(7,h900MCSignalPFDijetM7->GetMean()/h900MCSignalM7->GetMean());
   if (h900MCSignalM8->GetMean() != 0) h900RatiosModulesMC->SetBinContent(8,h900MCSignalPFDijetM8->GetMean()/h900MCSignalM8->GetMean());
   if (h900MCSignalM9->GetMean() != 0) h900RatiosModulesMC->SetBinContent(9,h900MCSignalPFDijetM9->GetMean()/h900MCSignalM9->GetMean());
   if (h900MCSignalM10->GetMean() != 0) h900RatiosModulesMC->SetBinContent(10,h900MCSignalPFDijetM10->GetMean()/h900MCSignalM10->GetMean());
   if (h900MCSignalM11->GetMean() != 0) h900RatiosModulesMC->SetBinContent(11,h900MCSignalPFDijetM11->GetMean()/h900MCSignalM11->GetMean());
   if (h900MCSignalM12->GetMean() != 0) h900RatiosModulesMC->SetBinContent(12,h900MCSignalPFDijetM12->GetMean()/h900MCSignalM12->GetMean());
   if (h900MCSignalM13->GetMean() != 0) h900RatiosModulesMC->SetBinContent(13,h900MCSignalPFDijetM13->GetMean()/h900MCSignalM13->GetMean());
   if (h900MCSignalM14->GetMean() != 0) h900RatiosModulesMC->SetBinContent(14,h900MCSignalPFDijetM14->GetMean()/h900MCSignalM14->GetMean());
   
   if (h900SignalM1->GetMean() != 0) h900RatiosModules->SetBinError(1,getRatioError(h900SignalM1,h900SignalPFDijetM1));
   if (h900SignalM2->GetMean() != 0) h900RatiosModules->SetBinError(2,getRatioError(h900SignalM2,h900SignalPFDijetM2));
   if (h900SignalM3->GetMean() != 0) h900RatiosModules->SetBinError(3,getRatioError(h900SignalM3,h900SignalPFDijetM3));
   if (h900SignalM4->GetMean() != 0) h900RatiosModules->SetBinError(4,getRatioError(h900SignalM4,h900SignalPFDijetM4));
   if (h900SignalM5->GetMean() != 0) h900RatiosModules->SetBinError(5,getRatioError(h900SignalM5,h900SignalPFDijetM5));
   if (h900SignalM6->GetMean() != 0) h900RatiosModules->SetBinError(6,getRatioError(h900SignalM6,h900SignalPFDijetM6));
   if (h900SignalM7->GetMean() != 0) h900RatiosModules->SetBinError(7,getRatioError(h900SignalM7,h900SignalPFDijetM7));
   if (h900SignalM8->GetMean() != 0) h900RatiosModules->SetBinError(8,getRatioError(h900SignalM8,h900SignalPFDijetM8));
   if (h900SignalM9->GetMean() != 0) h900RatiosModules->SetBinError(9,getRatioError(h900SignalM9,h900SignalPFDijetM9));
   if (h900SignalM10->GetMean() != 0) h900RatiosModules->SetBinError(10,getRatioError(h900SignalM10,h900SignalPFDijetM10));
   if (h900SignalM11->GetMean() != 0) h900RatiosModules->SetBinError(11,getRatioError(h900SignalM11,h900SignalPFDijetM11));
   if (h900SignalM12->GetMean() != 0) h900RatiosModules->SetBinError(12,getRatioError(h900SignalM12,h900SignalPFDijetM12));
   if (h900SignalM13->GetMean() != 0) h900RatiosModules->SetBinError(13,getRatioError(h900SignalM13,h900SignalPFDijetM13));
   if (h900SignalM14->GetMean() != 0) h900RatiosModules->SetBinError(14,getRatioError(h900SignalM14,h900SignalPFDijetM14));
   
   if (h900MCSignalM1->GetMean() != 0) h900RatiosModulesMC->SetBinError(1,getRatioError(h900MCSignalM1,h900MCSignalPFDijetM1));
   if (h900MCSignalM2->GetMean() != 0) h900RatiosModulesMC->SetBinError(2,getRatioError(h900MCSignalM2,h900MCSignalPFDijetM2));
   if (h900MCSignalM3->GetMean() != 0) h900RatiosModulesMC->SetBinError(3,getRatioError(h900MCSignalM3,h900MCSignalPFDijetM3));
   if (h900MCSignalM4->GetMean() != 0) h900RatiosModulesMC->SetBinError(4,getRatioError(h900MCSignalM4,h900MCSignalPFDijetM4));
   if (h900MCSignalM5->GetMean() != 0) h900RatiosModulesMC->SetBinError(5,getRatioError(h900MCSignalM5,h900MCSignalPFDijetM5));
   if (h900MCSignalM6->GetMean() != 0) h900RatiosModulesMC->SetBinError(6,getRatioError(h900MCSignalM6,h900MCSignalPFDijetM6));
   if (h900MCSignalM7->GetMean() != 0) h900RatiosModulesMC->SetBinError(7,getRatioError(h900MCSignalM7,h900MCSignalPFDijetM7));
   if (h900MCSignalM8->GetMean() != 0) h900RatiosModulesMC->SetBinError(8,getRatioError(h900MCSignalM8,h900MCSignalPFDijetM8));
   if (h900MCSignalM9->GetMean() != 0) h900RatiosModulesMC->SetBinError(9,getRatioError(h900MCSignalM9,h900MCSignalPFDijetM9));
   if (h900MCSignalM10->GetMean() != 0) h900RatiosModulesMC->SetBinError(10,getRatioError(h900MCSignalM10,h900MCSignalPFDijetM10));
   if (h900MCSignalM11->GetMean() != 0) h900RatiosModulesMC->SetBinError(11,getRatioError(h900MCSignalM11,h900MCSignalPFDijetM11));
   if (h900MCSignalM12->GetMean() != 0) h900RatiosModulesMC->SetBinError(12,getRatioError(h900MCSignalM12,h900MCSignalPFDijetM12));
   if (h900MCSignalM13->GetMean() != 0) h900RatiosModulesMC->SetBinError(13,getRatioError(h900MCSignalM13,h900MCSignalPFDijetM13));
   if (h900MCSignalM14->GetMean() != 0) h900RatiosModulesMC->SetBinError(14,getRatioError(h900MCSignalM14,h900MCSignalPFDijetM14)); 
   
   TCanvas * c900RatiosModules = new TCanvas("c900RatiosModules","QCD/MB ratios per module 900GeV");
   c900RatiosModules->Divide(1,1);
   c900RatiosModules->cd(1);
   h900RatiosModulesMC->SetFillColor(8);
   h900RatiosModulesMC->SetFillStyle(1001);
   h900RatiosModulesMC->SetMarkerStyle(0);
   h900RatiosModulesMC->Draw("histe");
   h900RatiosModules->SetFillColor(0);
   h900RatiosModules->SetFillStyle(0);
   h900RatiosModules->SetMarkerStyle(1);
   h900RatiosModules->Draw("samee");
   
   if (h900SignalS1->GetMean() != 0) h900RatiosSectors->SetBinContent(1,h900SignalPFDijetS1->GetMean()/h900SignalS1->GetMean());
   if (h900SignalS2->GetMean() != 0) h900RatiosSectors->SetBinContent(2,h900SignalPFDijetS2->GetMean()/h900SignalS2->GetMean());
   if (h900SignalS3->GetMean() != 0) h900RatiosSectors->SetBinContent(3,h900SignalPFDijetS3->GetMean()/h900SignalS3->GetMean());
   if (h900SignalS4->GetMean() != 0) h900RatiosSectors->SetBinContent(4,h900SignalPFDijetS4->GetMean()/h900SignalS4->GetMean());
   if (h900SignalS5->GetMean() != 0) h900RatiosSectors->SetBinContent(5,h900SignalPFDijetS5->GetMean()/h900SignalS5->GetMean());
   if (h900SignalS6->GetMean() != 0) h900RatiosSectors->SetBinContent(6,h900SignalPFDijetS6->GetMean()/h900SignalS6->GetMean());
   if (h900SignalS7->GetMean() != 0) h900RatiosSectors->SetBinContent(7,h900SignalPFDijetS7->GetMean()/h900SignalS7->GetMean());
   if (h900SignalS8->GetMean() != 0) h900RatiosSectors->SetBinContent(8,h900SignalPFDijetS8->GetMean()/h900SignalS8->GetMean());
   if (h900SignalS9->GetMean() != 0) h900RatiosSectors->SetBinContent(9,h900SignalPFDijetS9->GetMean()/h900SignalS9->GetMean());
   if (h900SignalS10->GetMean() != 0) h900RatiosSectors->SetBinContent(10,h900SignalPFDijetS10->GetMean()/h900SignalS10->GetMean());
   if (h900SignalS11->GetMean() != 0) h900RatiosSectors->SetBinContent(11,h900SignalPFDijetS11->GetMean()/h900SignalS11->GetMean());
   if (h900SignalS12->GetMean() != 0) h900RatiosSectors->SetBinContent(12,h900SignalPFDijetS12->GetMean()/h900SignalS12->GetMean());
   if (h900SignalS13->GetMean() != 0) h900RatiosSectors->SetBinContent(13,h900SignalPFDijetS13->GetMean()/h900SignalS13->GetMean());
   if (h900SignalS14->GetMean() != 0) h900RatiosSectors->SetBinContent(14,h900SignalPFDijetS14->GetMean()/h900SignalS14->GetMean());
   if (h900SignalS15->GetMean() != 0) h900RatiosSectors->SetBinContent(15,h900SignalPFDijetS15->GetMean()/h900SignalS15->GetMean());
   if (h900SignalS16->GetMean() != 0) h900RatiosSectors->SetBinContent(16,h900SignalPFDijetS16->GetMean()/h900SignalS16->GetMean());
   
   if (h900MCSignalS1->GetMean() != 0) h900RatiosSectorsMC->SetBinContent(1,h900MCSignalPFDijetS1->GetMean()/h900MCSignalS1->GetMean());
   if (h900MCSignalS2->GetMean() != 0) h900RatiosSectorsMC->SetBinContent(2,h900MCSignalPFDijetS2->GetMean()/h900MCSignalS2->GetMean());
   if (h900MCSignalS3->GetMean() != 0) h900RatiosSectorsMC->SetBinContent(3,h900MCSignalPFDijetS3->GetMean()/h900MCSignalS3->GetMean());
   if (h900MCSignalS4->GetMean() != 0) h900RatiosSectorsMC->SetBinContent(4,h900MCSignalPFDijetS4->GetMean()/h900MCSignalS4->GetMean());
   if (h900MCSignalS5->GetMean() != 0) h900RatiosSectorsMC->SetBinContent(5,h900MCSignalPFDijetS5->GetMean()/h900MCSignalS5->GetMean());
   if (h900MCSignalS6->GetMean() != 0) h900RatiosSectorsMC->SetBinContent(6,h900MCSignalPFDijetS6->GetMean()/h900MCSignalS6->GetMean());
   if (h900MCSignalS7->GetMean() != 0) h900RatiosSectorsMC->SetBinContent(7,h900MCSignalPFDijetS7->GetMean()/h900MCSignalS7->GetMean());
   if (h900MCSignalS8->GetMean() != 0) h900RatiosSectorsMC->SetBinContent(8,h900MCSignalPFDijetS8->GetMean()/h900MCSignalS8->GetMean());
   if (h900MCSignalS9->GetMean() != 0) h900RatiosSectorsMC->SetBinContent(9,h900MCSignalPFDijetS9->GetMean()/h900MCSignalS9->GetMean());
   if (h900MCSignalS10->GetMean() != 0) h900RatiosSectorsMC->SetBinContent(10,h900MCSignalPFDijetS10->GetMean()/h900MCSignalS10->GetMean());
   if (h900MCSignalS11->GetMean() != 0) h900RatiosSectorsMC->SetBinContent(11,h900MCSignalPFDijetS11->GetMean()/h900MCSignalS11->GetMean());
   if (h900MCSignalS12->GetMean() != 0) h900RatiosSectorsMC->SetBinContent(12,h900MCSignalPFDijetS12->GetMean()/h900MCSignalS12->GetMean());
   if (h900MCSignalS13->GetMean() != 0) h900RatiosSectorsMC->SetBinContent(13,h900MCSignalPFDijetS13->GetMean()/h900MCSignalS13->GetMean());
   if (h900MCSignalS14->GetMean() != 0) h900RatiosSectorsMC->SetBinContent(14,h900MCSignalPFDijetS14->GetMean()/h900MCSignalS14->GetMean());
   if (h900MCSignalS15->GetMean() != 0) h900RatiosSectorsMC->SetBinContent(15,h900MCSignalPFDijetS15->GetMean()/h900MCSignalS15->GetMean());
   if (h900MCSignalS16->GetMean() != 0) h900RatiosSectorsMC->SetBinContent(16,h900MCSignalPFDijetS16->GetMean()/h900MCSignalS16->GetMean());
   
   if (h900SignalS1->GetMean() != 0) h900RatiosSectors->SetBinError(1,getRatioError(h900SignalS1,h900SignalPFDijetS1));
   if (h900SignalS2->GetMean() != 0) h900RatiosSectors->SetBinError(2,getRatioError(h900SignalS2,h900SignalPFDijetS2));
   if (h900SignalS3->GetMean() != 0) h900RatiosSectors->SetBinError(3,getRatioError(h900SignalS3,h900SignalPFDijetS3));
   if (h900SignalS4->GetMean() != 0) h900RatiosSectors->SetBinError(4,getRatioError(h900SignalS4,h900SignalPFDijetS4));
   if (h900SignalS5->GetMean() != 0) h900RatiosSectors->SetBinError(5,getRatioError(h900SignalS5,h900SignalPFDijetS5));
   if (h900SignalS6->GetMean() != 0) h900RatiosSectors->SetBinError(6,getRatioError(h900SignalS6,h900SignalPFDijetS6));
   if (h900SignalS7->GetMean() != 0) h900RatiosSectors->SetBinError(7,getRatioError(h900SignalS7,h900SignalPFDijetS7));
   if (h900SignalS8->GetMean() != 0) h900RatiosSectors->SetBinError(8,getRatioError(h900SignalS8,h900SignalPFDijetS8));
   if (h900SignalS9->GetMean() != 0) h900RatiosSectors->SetBinError(9,getRatioError(h900SignalS9,h900SignalPFDijetS9));
   if (h900SignalS10->GetMean() != 0) h900RatiosSectors->SetBinError(10,getRatioError(h900SignalS10,h900SignalPFDijetS10));
   if (h900SignalS11->GetMean() != 0) h900RatiosSectors->SetBinError(11,getRatioError(h900SignalS11,h900SignalPFDijetS11));
   if (h900SignalS12->GetMean() != 0) h900RatiosSectors->SetBinError(12,getRatioError(h900SignalS12,h900SignalPFDijetS12));
   if (h900SignalS13->GetMean() != 0) h900RatiosSectors->SetBinError(13,getRatioError(h900SignalS13,h900SignalPFDijetS13));
   if (h900SignalS14->GetMean() != 0) h900RatiosSectors->SetBinError(14,getRatioError(h900SignalS14,h900SignalPFDijetS14));
   if (h900SignalS15->GetMean() != 0) h900RatiosSectors->SetBinError(15,getRatioError(h900SignalS15,h900SignalPFDijetS15));
   if (h900SignalS16->GetMean() != 0) h900RatiosSectors->SetBinError(16,getRatioError(h900SignalS16,h900SignalPFDijetS16));
   
   if (h900MCSignalS1->GetMean() != 0) h900RatiosSectorsMC->SetBinError(1,getRatioError(h900MCSignalS1,h900MCSignalPFDijetS1));
   if (h900MCSignalS2->GetMean() != 0) h900RatiosSectorsMC->SetBinError(2,getRatioError(h900MCSignalS2,h900MCSignalPFDijetS2));
   if (h900MCSignalS3->GetMean() != 0) h900RatiosSectorsMC->SetBinError(3,getRatioError(h900MCSignalS3,h900MCSignalPFDijetS3));
   if (h900MCSignalS4->GetMean() != 0) h900RatiosSectorsMC->SetBinError(4,getRatioError(h900MCSignalS4,h900MCSignalPFDijetS4));
   if (h900MCSignalS5->GetMean() != 0) h900RatiosSectorsMC->SetBinError(5,getRatioError(h900MCSignalS5,h900MCSignalPFDijetS5));
   if (h900MCSignalS6->GetMean() != 0) h900RatiosSectorsMC->SetBinError(6,getRatioError(h900MCSignalS6,h900MCSignalPFDijetS6));
   if (h900MCSignalS7->GetMean() != 0) h900RatiosSectorsMC->SetBinError(7,getRatioError(h900MCSignalS7,h900MCSignalPFDijetS7));
   if (h900MCSignalS8->GetMean() != 0) h900RatiosSectorsMC->SetBinError(8,getRatioError(h900MCSignalS8,h900MCSignalPFDijetS8));
   if (h900MCSignalS9->GetMean() != 0) h900RatiosSectorsMC->SetBinError(9,getRatioError(h900MCSignalS9,h900MCSignalPFDijetS9));
   if (h900MCSignalS10->GetMean() != 0) h900RatiosSectorsMC->SetBinError(10,getRatioError(h900MCSignalS10,h900MCSignalPFDijetS10));
   if (h900MCSignalS11->GetMean() != 0) h900RatiosSectorsMC->SetBinError(11,getRatioError(h900MCSignalS11,h900MCSignalPFDijetS11));
   if (h900MCSignalS12->GetMean() != 0) h900RatiosSectorsMC->SetBinError(12,getRatioError(h900MCSignalS12,h900MCSignalPFDijetS12));
   if (h900MCSignalS13->GetMean() != 0) h900RatiosSectorsMC->SetBinError(13,getRatioError(h900MCSignalS13,h900MCSignalPFDijetS13));
   if (h900MCSignalS14->GetMean() != 0) h900RatiosSectorsMC->SetBinError(14,getRatioError(h900MCSignalS14,h900MCSignalPFDijetS14)); 
   if (h900MCSignalS15->GetMean() != 0) h900RatiosSectorsMC->SetBinError(15,getRatioError(h900MCSignalS15,h900MCSignalPFDijetS15));
   if (h900MCSignalS16->GetMean() != 0) h900RatiosSectorsMC->SetBinError(16,getRatioError(h900MCSignalS16,h900MCSignalPFDijetS16)); 
  
   
   
   TCanvas * c900RatiosSectors = new TCanvas("c900RatiosSectors","QCD/MB ratios per sector 900GeV");
   c900RatiosSectors->Divide(1,1);
   c900RatiosSectors->cd(1);
   h900RatiosSectorsMC->SetFillColor(8);
   h900RatiosSectorsMC->SetFillStyle(1001);
   h900RatiosSectorsMC->SetMarkerStyle(0);
   h900RatiosSectorsMC->Draw("histe");
   h900RatiosSectors->SetFillColor(0);
   h900RatiosSectors->SetFillStyle(0);
   h900RatiosSectors->SetMarkerStyle(1);
   h900RatiosSectors->Draw("samee");
   
   // 2360 GeV
   
      if (h2360SignalM1->GetMean() != 0) h2360RatiosModules->SetBinContent(1,h2360SignalPFDijetM1->GetMean()/h2360SignalM1->GetMean());
   if (h2360SignalM2->GetMean() != 0) h2360RatiosModules->SetBinContent(2,h2360SignalPFDijetM2->GetMean()/h2360SignalM2->GetMean());
   if (h2360SignalM3->GetMean() != 0) h2360RatiosModules->SetBinContent(3,h2360SignalPFDijetM3->GetMean()/h2360SignalM3->GetMean());
   if (h2360SignalM4->GetMean() != 0) h2360RatiosModules->SetBinContent(4,h2360SignalPFDijetM4->GetMean()/h2360SignalM4->GetMean());
   if (h2360SignalM5->GetMean() != 0) h2360RatiosModules->SetBinContent(5,h2360SignalPFDijetM5->GetMean()/h2360SignalM5->GetMean());
   if (h2360SignalM6->GetMean() != 0) h2360RatiosModules->SetBinContent(6,h2360SignalPFDijetM6->GetMean()/h2360SignalM6->GetMean());
   if (h2360SignalM7->GetMean() != 0) h2360RatiosModules->SetBinContent(7,h2360SignalPFDijetM7->GetMean()/h2360SignalM7->GetMean());
   if (h2360SignalM8->GetMean() != 0) h2360RatiosModules->SetBinContent(8,h2360SignalPFDijetM8->GetMean()/h2360SignalM8->GetMean());
   if (h2360SignalM9->GetMean() != 0) h2360RatiosModules->SetBinContent(9,h2360SignalPFDijetM9->GetMean()/h2360SignalM9->GetMean());
   if (h2360SignalM10->GetMean() != 0) h2360RatiosModules->SetBinContent(10,h2360SignalPFDijetM10->GetMean()/h2360SignalM10->GetMean());
   if (h2360SignalM11->GetMean() != 0) h2360RatiosModules->SetBinContent(11,h2360SignalPFDijetM11->GetMean()/h2360SignalM11->GetMean());
   if (h2360SignalM12->GetMean() != 0) h2360RatiosModules->SetBinContent(12,h2360SignalPFDijetM12->GetMean()/h2360SignalM12->GetMean());
   if (h2360SignalM13->GetMean() != 0) h2360RatiosModules->SetBinContent(13,h2360SignalPFDijetM13->GetMean()/h2360SignalM13->GetMean());
   if (h2360SignalM14->GetMean() != 0) h2360RatiosModules->SetBinContent(14,h2360SignalPFDijetM14->GetMean()/h2360SignalM14->GetMean());
   
   if (h2360MCSignalM1->GetMean() != 0) h2360RatiosModulesMC->SetBinContent(1,h2360MCSignalPFDijetM1->GetMean()/h2360MCSignalM1->GetMean());
   if (h2360MCSignalM2->GetMean() != 0) h2360RatiosModulesMC->SetBinContent(2,h2360MCSignalPFDijetM2->GetMean()/h2360MCSignalM2->GetMean());
   if (h2360MCSignalM3->GetMean() != 0) h2360RatiosModulesMC->SetBinContent(3,h2360MCSignalPFDijetM3->GetMean()/h2360MCSignalM3->GetMean());
   if (h2360MCSignalM4->GetMean() != 0) h2360RatiosModulesMC->SetBinContent(4,h2360MCSignalPFDijetM4->GetMean()/h2360MCSignalM4->GetMean());
   if (h2360MCSignalM5->GetMean() != 0) h2360RatiosModulesMC->SetBinContent(5,h2360MCSignalPFDijetM5->GetMean()/h2360MCSignalM5->GetMean());
   if (h2360MCSignalM6->GetMean() != 0) h2360RatiosModulesMC->SetBinContent(6,h2360MCSignalPFDijetM6->GetMean()/h2360MCSignalM6->GetMean());
   if (h2360MCSignalM7->GetMean() != 0) h2360RatiosModulesMC->SetBinContent(7,h2360MCSignalPFDijetM7->GetMean()/h2360MCSignalM7->GetMean());
   if (h2360MCSignalM8->GetMean() != 0) h2360RatiosModulesMC->SetBinContent(8,h2360MCSignalPFDijetM8->GetMean()/h2360MCSignalM8->GetMean());
   if (h2360MCSignalM9->GetMean() != 0) h2360RatiosModulesMC->SetBinContent(9,h2360MCSignalPFDijetM9->GetMean()/h2360MCSignalM9->GetMean());
   if (h2360MCSignalM10->GetMean() != 0) h2360RatiosModulesMC->SetBinContent(10,h2360MCSignalPFDijetM10->GetMean()/h2360MCSignalM10->GetMean());
   if (h2360MCSignalM11->GetMean() != 0) h2360RatiosModulesMC->SetBinContent(11,h2360MCSignalPFDijetM11->GetMean()/h2360MCSignalM11->GetMean());
   if (h2360MCSignalM12->GetMean() != 0) h2360RatiosModulesMC->SetBinContent(12,h2360MCSignalPFDijetM12->GetMean()/h2360MCSignalM12->GetMean());
   if (h2360MCSignalM13->GetMean() != 0) h2360RatiosModulesMC->SetBinContent(13,h2360MCSignalPFDijetM13->GetMean()/h2360MCSignalM13->GetMean());
   if (h2360MCSignalM14->GetMean() != 0) h2360RatiosModulesMC->SetBinContent(14,h2360MCSignalPFDijetM14->GetMean()/h2360MCSignalM14->GetMean());
   
   if (h2360SignalM1->GetMean() != 0) h2360RatiosModules->SetBinError(1,getRatioError(h2360SignalM1,h2360SignalPFDijetM1));
   if (h2360SignalM2->GetMean() != 0) h2360RatiosModules->SetBinError(2,getRatioError(h2360SignalM2,h2360SignalPFDijetM2));
   if (h2360SignalM3->GetMean() != 0) h2360RatiosModules->SetBinError(3,getRatioError(h2360SignalM3,h2360SignalPFDijetM3));
   if (h2360SignalM4->GetMean() != 0) h2360RatiosModules->SetBinError(4,getRatioError(h2360SignalM4,h2360SignalPFDijetM4));
   if (h2360SignalM5->GetMean() != 0) h2360RatiosModules->SetBinError(5,getRatioError(h2360SignalM5,h2360SignalPFDijetM5));
   if (h2360SignalM6->GetMean() != 0) h2360RatiosModules->SetBinError(6,getRatioError(h2360SignalM6,h2360SignalPFDijetM6));
   if (h2360SignalM7->GetMean() != 0) h2360RatiosModules->SetBinError(7,getRatioError(h2360SignalM7,h2360SignalPFDijetM7));
   if (h2360SignalM8->GetMean() != 0) h2360RatiosModules->SetBinError(8,getRatioError(h2360SignalM8,h2360SignalPFDijetM8));
   if (h2360SignalM9->GetMean() != 0) h2360RatiosModules->SetBinError(9,getRatioError(h2360SignalM9,h2360SignalPFDijetM9));
   if (h2360SignalM10->GetMean() != 0) h2360RatiosModules->SetBinError(10,getRatioError(h2360SignalM10,h2360SignalPFDijetM10));
   if (h2360SignalM11->GetMean() != 0) h2360RatiosModules->SetBinError(11,getRatioError(h2360SignalM11,h2360SignalPFDijetM11));
   if (h2360SignalM12->GetMean() != 0) h2360RatiosModules->SetBinError(12,getRatioError(h2360SignalM12,h2360SignalPFDijetM12));
   if (h2360SignalM13->GetMean() != 0) h2360RatiosModules->SetBinError(13,getRatioError(h2360SignalM13,h2360SignalPFDijetM13));
   if (h2360SignalM14->GetMean() != 0) h2360RatiosModules->SetBinError(14,getRatioError(h2360SignalM14,h2360SignalPFDijetM14));
   
   if (h2360MCSignalM1->GetMean() != 0) h2360RatiosModulesMC->SetBinError(1,getRatioError(h2360MCSignalM1,h2360MCSignalPFDijetM1));
   if (h2360MCSignalM2->GetMean() != 0) h2360RatiosModulesMC->SetBinError(2,getRatioError(h2360MCSignalM2,h2360MCSignalPFDijetM2));
   if (h2360MCSignalM3->GetMean() != 0) h2360RatiosModulesMC->SetBinError(3,getRatioError(h2360MCSignalM3,h2360MCSignalPFDijetM3));
   if (h2360MCSignalM4->GetMean() != 0) h2360RatiosModulesMC->SetBinError(4,getRatioError(h2360MCSignalM4,h2360MCSignalPFDijetM4));
   if (h2360MCSignalM5->GetMean() != 0) h2360RatiosModulesMC->SetBinError(5,getRatioError(h2360MCSignalM5,h2360MCSignalPFDijetM5));
   if (h2360MCSignalM6->GetMean() != 0) h2360RatiosModulesMC->SetBinError(6,getRatioError(h2360MCSignalM6,h2360MCSignalPFDijetM6));
   if (h2360MCSignalM7->GetMean() != 0) h2360RatiosModulesMC->SetBinError(7,getRatioError(h2360MCSignalM7,h2360MCSignalPFDijetM7));
   if (h2360MCSignalM8->GetMean() != 0) h2360RatiosModulesMC->SetBinError(8,getRatioError(h2360MCSignalM8,h2360MCSignalPFDijetM8));
   if (h2360MCSignalM9->GetMean() != 0) h2360RatiosModulesMC->SetBinError(9,getRatioError(h2360MCSignalM9,h2360MCSignalPFDijetM9));
   if (h2360MCSignalM10->GetMean() != 0) h2360RatiosModulesMC->SetBinError(10,getRatioError(h2360MCSignalM10,h2360MCSignalPFDijetM10));
   if (h2360MCSignalM11->GetMean() != 0) h2360RatiosModulesMC->SetBinError(11,getRatioError(h2360MCSignalM11,h2360MCSignalPFDijetM11));
   if (h2360MCSignalM12->GetMean() != 0) h2360RatiosModulesMC->SetBinError(12,getRatioError(h2360MCSignalM12,h2360MCSignalPFDijetM12));
   if (h2360MCSignalM13->GetMean() != 0) h2360RatiosModulesMC->SetBinError(13,getRatioError(h2360MCSignalM13,h2360MCSignalPFDijetM13));
   if (h2360MCSignalM14->GetMean() != 0) h2360RatiosModulesMC->SetBinError(14,getRatioError(h2360MCSignalM14,h2360MCSignalPFDijetM14)); 
   
   TCanvas * c2360RatiosModules = new TCanvas("c2360RatiosModules","QCD/MB ratios per module 2360GeV");
   c2360RatiosModules->Divide(1,1);
   c2360RatiosModules->cd(1);
   h2360RatiosModulesMC->SetFillColor(8);
   h2360RatiosModulesMC->SetFillStyle(1001);
   h2360RatiosModulesMC->SetMarkerStyle(0);
   h2360RatiosModulesMC->Draw("histe");
   h2360RatiosModules->SetFillColor(0);
   h2360RatiosModules->SetFillStyle(0);
   h2360RatiosModules->SetMarkerStyle(1);
   h2360RatiosModules->Draw("samee");
   
   if (h2360SignalS1->GetMean() != 0) h2360RatiosSectors->SetBinContent(1,h2360SignalPFDijetS1->GetMean()/h2360SignalS1->GetMean());
   if (h2360SignalS2->GetMean() != 0) h2360RatiosSectors->SetBinContent(2,h2360SignalPFDijetS2->GetMean()/h2360SignalS2->GetMean());
   if (h2360SignalS3->GetMean() != 0) h2360RatiosSectors->SetBinContent(3,h2360SignalPFDijetS3->GetMean()/h2360SignalS3->GetMean());
   if (h2360SignalS4->GetMean() != 0) h2360RatiosSectors->SetBinContent(4,h2360SignalPFDijetS4->GetMean()/h2360SignalS4->GetMean());
   if (h2360SignalS5->GetMean() != 0) h2360RatiosSectors->SetBinContent(5,h2360SignalPFDijetS5->GetMean()/h2360SignalS5->GetMean());
   if (h2360SignalS6->GetMean() != 0) h2360RatiosSectors->SetBinContent(6,h2360SignalPFDijetS6->GetMean()/h2360SignalS6->GetMean());
   if (h2360SignalS7->GetMean() != 0) h2360RatiosSectors->SetBinContent(7,h2360SignalPFDijetS7->GetMean()/h2360SignalS7->GetMean());
   if (h2360SignalS8->GetMean() != 0) h2360RatiosSectors->SetBinContent(8,h2360SignalPFDijetS8->GetMean()/h2360SignalS8->GetMean());
   if (h2360SignalS9->GetMean() != 0) h2360RatiosSectors->SetBinContent(9,h2360SignalPFDijetS9->GetMean()/h2360SignalS9->GetMean());
   if (h2360SignalS10->GetMean() != 0) h2360RatiosSectors->SetBinContent(10,h2360SignalPFDijetS10->GetMean()/h2360SignalS10->GetMean());
   if (h2360SignalS11->GetMean() != 0) h2360RatiosSectors->SetBinContent(11,h2360SignalPFDijetS11->GetMean()/h2360SignalS11->GetMean());
   if (h2360SignalS12->GetMean() != 0) h2360RatiosSectors->SetBinContent(12,h2360SignalPFDijetS12->GetMean()/h2360SignalS12->GetMean());
   if (h2360SignalS13->GetMean() != 0) h2360RatiosSectors->SetBinContent(13,h2360SignalPFDijetS13->GetMean()/h2360SignalS13->GetMean());
   if (h2360SignalS14->GetMean() != 0) h2360RatiosSectors->SetBinContent(14,h2360SignalPFDijetS14->GetMean()/h2360SignalS14->GetMean());
   if (h2360SignalS15->GetMean() != 0) h2360RatiosSectors->SetBinContent(15,h2360SignalPFDijetS15->GetMean()/h2360SignalS15->GetMean());
   if (h2360SignalS16->GetMean() != 0) h2360RatiosSectors->SetBinContent(16,h2360SignalPFDijetS16->GetMean()/h2360SignalS16->GetMean());
   
   if (h2360MCSignalS1->GetMean() != 0) h2360RatiosSectorsMC->SetBinContent(1,h2360MCSignalPFDijetS1->GetMean()/h2360MCSignalS1->GetMean());
   if (h2360MCSignalS2->GetMean() != 0) h2360RatiosSectorsMC->SetBinContent(2,h2360MCSignalPFDijetS2->GetMean()/h2360MCSignalS2->GetMean());
   if (h2360MCSignalS3->GetMean() != 0) h2360RatiosSectorsMC->SetBinContent(3,h2360MCSignalPFDijetS3->GetMean()/h2360MCSignalS3->GetMean());
   if (h2360MCSignalS4->GetMean() != 0) h2360RatiosSectorsMC->SetBinContent(4,h2360MCSignalPFDijetS4->GetMean()/h2360MCSignalS4->GetMean());
   if (h2360MCSignalS5->GetMean() != 0) h2360RatiosSectorsMC->SetBinContent(5,h2360MCSignalPFDijetS5->GetMean()/h2360MCSignalS5->GetMean());
   if (h2360MCSignalS6->GetMean() != 0) h2360RatiosSectorsMC->SetBinContent(6,h2360MCSignalPFDijetS6->GetMean()/h2360MCSignalS6->GetMean());
   if (h2360MCSignalS7->GetMean() != 0) h2360RatiosSectorsMC->SetBinContent(7,h2360MCSignalPFDijetS7->GetMean()/h2360MCSignalS7->GetMean());
   if (h2360MCSignalS8->GetMean() != 0) h2360RatiosSectorsMC->SetBinContent(8,h2360MCSignalPFDijetS8->GetMean()/h2360MCSignalS8->GetMean());
   if (h2360MCSignalS9->GetMean() != 0) h2360RatiosSectorsMC->SetBinContent(9,h2360MCSignalPFDijetS9->GetMean()/h2360MCSignalS9->GetMean());
   if (h2360MCSignalS10->GetMean() != 0) h2360RatiosSectorsMC->SetBinContent(10,h2360MCSignalPFDijetS10->GetMean()/h2360MCSignalS10->GetMean());
   if (h2360MCSignalS11->GetMean() != 0) h2360RatiosSectorsMC->SetBinContent(11,h2360MCSignalPFDijetS11->GetMean()/h2360MCSignalS11->GetMean());
   if (h2360MCSignalS12->GetMean() != 0) h2360RatiosSectorsMC->SetBinContent(12,h2360MCSignalPFDijetS12->GetMean()/h2360MCSignalS12->GetMean());
   if (h2360MCSignalS13->GetMean() != 0) h2360RatiosSectorsMC->SetBinContent(13,h2360MCSignalPFDijetS13->GetMean()/h2360MCSignalS13->GetMean());
   if (h2360MCSignalS14->GetMean() != 0) h2360RatiosSectorsMC->SetBinContent(14,h2360MCSignalPFDijetS14->GetMean()/h2360MCSignalS14->GetMean());
   if (h2360MCSignalS15->GetMean() != 0) h2360RatiosSectorsMC->SetBinContent(15,h2360MCSignalPFDijetS15->GetMean()/h2360MCSignalS15->GetMean());
   if (h2360MCSignalS16->GetMean() != 0) h2360RatiosSectorsMC->SetBinContent(16,h2360MCSignalPFDijetS16->GetMean()/h2360MCSignalS16->GetMean());
   
   if (h2360SignalS1->GetMean() != 0) h2360RatiosSectors->SetBinError(1,getRatioError(h2360SignalS1,h2360SignalPFDijetS1));
   if (h2360SignalS2->GetMean() != 0) h2360RatiosSectors->SetBinError(2,getRatioError(h2360SignalS2,h2360SignalPFDijetS2));
   if (h2360SignalS3->GetMean() != 0) h2360RatiosSectors->SetBinError(3,getRatioError(h2360SignalS3,h2360SignalPFDijetS3));
   if (h2360SignalS4->GetMean() != 0) h2360RatiosSectors->SetBinError(4,getRatioError(h2360SignalS4,h2360SignalPFDijetS4));
   if (h2360SignalS5->GetMean() != 0) h2360RatiosSectors->SetBinError(5,getRatioError(h2360SignalS5,h2360SignalPFDijetS5));
   if (h2360SignalS6->GetMean() != 0) h2360RatiosSectors->SetBinError(6,getRatioError(h2360SignalS6,h2360SignalPFDijetS6));
   if (h2360SignalS7->GetMean() != 0) h2360RatiosSectors->SetBinError(7,getRatioError(h2360SignalS7,h2360SignalPFDijetS7));
   if (h2360SignalS8->GetMean() != 0) h2360RatiosSectors->SetBinError(8,getRatioError(h2360SignalS8,h2360SignalPFDijetS8));
   if (h2360SignalS9->GetMean() != 0) h2360RatiosSectors->SetBinError(9,getRatioError(h2360SignalS9,h2360SignalPFDijetS9));
   if (h2360SignalS10->GetMean() != 0) h2360RatiosSectors->SetBinError(10,getRatioError(h2360SignalS10,h2360SignalPFDijetS10));
   if (h2360SignalS11->GetMean() != 0) h2360RatiosSectors->SetBinError(11,getRatioError(h2360SignalS11,h2360SignalPFDijetS11));
   if (h2360SignalS12->GetMean() != 0) h2360RatiosSectors->SetBinError(12,getRatioError(h2360SignalS12,h2360SignalPFDijetS12));
   if (h2360SignalS13->GetMean() != 0) h2360RatiosSectors->SetBinError(13,getRatioError(h2360SignalS13,h2360SignalPFDijetS13));
   if (h2360SignalS14->GetMean() != 0) h2360RatiosSectors->SetBinError(14,getRatioError(h2360SignalS14,h2360SignalPFDijetS14));
   if (h2360SignalS15->GetMean() != 0) h2360RatiosSectors->SetBinError(15,getRatioError(h2360SignalS15,h2360SignalPFDijetS15));
   if (h2360SignalS16->GetMean() != 0) h2360RatiosSectors->SetBinError(16,getRatioError(h2360SignalS16,h2360SignalPFDijetS16));
   
   if (h2360MCSignalS1->GetMean() != 0) h2360RatiosSectorsMC->SetBinError(1,getRatioError(h2360MCSignalS1,h2360MCSignalPFDijetS1));
   if (h2360MCSignalS2->GetMean() != 0) h2360RatiosSectorsMC->SetBinError(2,getRatioError(h2360MCSignalS2,h2360MCSignalPFDijetS2));
   if (h2360MCSignalS3->GetMean() != 0) h2360RatiosSectorsMC->SetBinError(3,getRatioError(h2360MCSignalS3,h2360MCSignalPFDijetS3));
   if (h2360MCSignalS4->GetMean() != 0) h2360RatiosSectorsMC->SetBinError(4,getRatioError(h2360MCSignalS4,h2360MCSignalPFDijetS4));
   if (h2360MCSignalS5->GetMean() != 0) h2360RatiosSectorsMC->SetBinError(5,getRatioError(h2360MCSignalS5,h2360MCSignalPFDijetS5));
   if (h2360MCSignalS6->GetMean() != 0) h2360RatiosSectorsMC->SetBinError(6,getRatioError(h2360MCSignalS6,h2360MCSignalPFDijetS6));
   if (h2360MCSignalS7->GetMean() != 0) h2360RatiosSectorsMC->SetBinError(7,getRatioError(h2360MCSignalS7,h2360MCSignalPFDijetS7));
   if (h2360MCSignalS8->GetMean() != 0) h2360RatiosSectorsMC->SetBinError(8,getRatioError(h2360MCSignalS8,h2360MCSignalPFDijetS8));
   if (h2360MCSignalS9->GetMean() != 0) h2360RatiosSectorsMC->SetBinError(9,getRatioError(h2360MCSignalS9,h2360MCSignalPFDijetS9));
   if (h2360MCSignalS10->GetMean() != 0) h2360RatiosSectorsMC->SetBinError(10,getRatioError(h2360MCSignalS10,h2360MCSignalPFDijetS10));
   if (h2360MCSignalS11->GetMean() != 0) h2360RatiosSectorsMC->SetBinError(11,getRatioError(h2360MCSignalS11,h2360MCSignalPFDijetS11));
   if (h2360MCSignalS12->GetMean() != 0) h2360RatiosSectorsMC->SetBinError(12,getRatioError(h2360MCSignalS12,h2360MCSignalPFDijetS12));
   if (h2360MCSignalS13->GetMean() != 0) h2360RatiosSectorsMC->SetBinError(13,getRatioError(h2360MCSignalS13,h2360MCSignalPFDijetS13));
   if (h2360MCSignalS14->GetMean() != 0) h2360RatiosSectorsMC->SetBinError(14,getRatioError(h2360MCSignalS14,h2360MCSignalPFDijetS14)); 
   if (h2360MCSignalS15->GetMean() != 0) h2360RatiosSectorsMC->SetBinError(15,getRatioError(h2360MCSignalS15,h2360MCSignalPFDijetS15));
   if (h2360MCSignalS16->GetMean() != 0) h2360RatiosSectorsMC->SetBinError(16,getRatioError(h2360MCSignalS16,h2360MCSignalPFDijetS16)); 
  
   
   
   TCanvas * c2360RatiosSectors = new TCanvas("c2360RatiosSectors","QCD/MB ratios per sector 2360GeV");
   c2360RatiosSectors->Divide(1,1);
   c2360RatiosSectors->cd(1);
   h2360RatiosSectorsMC->SetFillColor(8);
   h2360RatiosSectorsMC->SetFillStyle(1001);
   h2360RatiosSectorsMC->SetMarkerStyle(0);
   h2360RatiosSectorsMC->Draw("histe");
   h2360RatiosSectors->SetFillColor(0);
   h2360RatiosSectors->SetFillStyle(0);
   h2360RatiosSectors->SetMarkerStyle(1);
   h2360RatiosSectors->Draw("samee");

   
   /////////////////////////////////////////////////
   // plot means for MB and QCD vs module and sector
   /////////////////////////////////////////////////
   
    if (h900SignalM1->GetMean() != 0) hMeansModules->SetBinContent(1,h900SignalM1->GetMean());
   if (h900SignalM2->GetMean() != 0) hMeansModules->SetBinContent(2,h900SignalM2->GetMean());
   if (h900SignalM3->GetMean() != 0) hMeansModules->SetBinContent(3,h900SignalM3->GetMean());
   if (h900SignalM4->GetMean() != 0) hMeansModules->SetBinContent(4,h900SignalM4->GetMean());
   if (h900SignalM5->GetMean() != 0) hMeansModules->SetBinContent(5,h900SignalM5->GetMean());
   if (h900SignalM6->GetMean() != 0) hMeansModules->SetBinContent(6,h900SignalM6->GetMean());
   if (h900SignalM7->GetMean() != 0) hMeansModules->SetBinContent(7,h900SignalM7->GetMean());
   if (h900SignalM8->GetMean() != 0) hMeansModules->SetBinContent(8,h900SignalM8->GetMean());
   if (h900SignalM9->GetMean() != 0) hMeansModules->SetBinContent(9,h900SignalM9->GetMean());
   if (h900SignalM10->GetMean() != 0) hMeansModules->SetBinContent(10,h900SignalM10->GetMean());
   if (h900SignalM11->GetMean() != 0) hMeansModules->SetBinContent(11,h900SignalM11->GetMean());
   if (h900SignalM12->GetMean() != 0) hMeansModules->SetBinContent(12,h900SignalM12->GetMean());
   if (h900SignalM13->GetMean() != 0) hMeansModules->SetBinContent(13,h900SignalM13->GetMean());
   if (h900SignalM14->GetMean() != 0) hMeansModules->SetBinContent(14,h900SignalM14->GetMean());
   
   if (h900MCSignalM1->GetMean() != 0) hMeansModulesMC->SetBinContent(1,h900MCSignalM1->GetMean());
   if (h900MCSignalM2->GetMean() != 0) hMeansModulesMC->SetBinContent(2,h900MCSignalM2->GetMean());
   if (h900MCSignalM3->GetMean() != 0) hMeansModulesMC->SetBinContent(3,h900MCSignalM3->GetMean());
   if (h900MCSignalM4->GetMean() != 0) hMeansModulesMC->SetBinContent(4,h900MCSignalM4->GetMean());
   if (h900MCSignalM5->GetMean() != 0) hMeansModulesMC->SetBinContent(5,h900MCSignalM5->GetMean());
   if (h900MCSignalM6->GetMean() != 0) hMeansModulesMC->SetBinContent(6,h900MCSignalM6->GetMean());
   if (h900MCSignalM7->GetMean() != 0) hMeansModulesMC->SetBinContent(7,h900MCSignalM7->GetMean());
   if (h900MCSignalM8->GetMean() != 0) hMeansModulesMC->SetBinContent(8,h900MCSignalM8->GetMean());
   if (h900MCSignalM9->GetMean() != 0) hMeansModulesMC->SetBinContent(9,h900MCSignalM9->GetMean());
   if (h900MCSignalM10->GetMean() != 0) hMeansModulesMC->SetBinContent(10,h900MCSignalM10->GetMean());
   if (h900MCSignalM11->GetMean() != 0) hMeansModulesMC->SetBinContent(11,h900MCSignalM11->GetMean());
   if (h900MCSignalM12->GetMean() != 0) hMeansModulesMC->SetBinContent(12,h900MCSignalM12->GetMean());
   if (h900MCSignalM13->GetMean() != 0) hMeansModulesMC->SetBinContent(13,h900MCSignalM13->GetMean());
   if (h900MCSignalM14->GetMean() != 0) hMeansModulesMC->SetBinContent(14,h900MCSignalM14->GetMean());
   
     if (h900SignalM1->GetMeanError() != 0) hMeansModules->SetBinError(1,h900SignalM1->GetMeanError());
   if (h900SignalM2->GetMeanError() != 0) hMeansModules->SetBinError(2,h900SignalM2->GetMeanError());
   if (h900SignalM3->GetMeanError() != 0) hMeansModules->SetBinError(3,h900SignalM3->GetMeanError());
   if (h900SignalM4->GetMeanError() != 0) hMeansModules->SetBinError(4,h900SignalM4->GetMeanError());
   if (h900SignalM5->GetMeanError() != 0) hMeansModules->SetBinError(5,h900SignalM5->GetMeanError());
   if (h900SignalM6->GetMeanError() != 0) hMeansModules->SetBinError(6,h900SignalM6->GetMeanError());
   if (h900SignalM7->GetMeanError() != 0) hMeansModules->SetBinError(7,h900SignalM7->GetMeanError());
   if (h900SignalM8->GetMeanError() != 0) hMeansModules->SetBinError(8,h900SignalM8->GetMeanError());
   if (h900SignalM9->GetMeanError() != 0) hMeansModules->SetBinError(9,h900SignalM9->GetMeanError());
   if (h900SignalM10->GetMeanError() != 0) hMeansModules->SetBinError(10,h900SignalM10->GetMeanError());
   if (h900SignalM11->GetMeanError() != 0) hMeansModules->SetBinError(11,h900SignalM11->GetMeanError());
   if (h900SignalM12->GetMeanError() != 0) hMeansModules->SetBinError(12,h900SignalM12->GetMeanError());
   if (h900SignalM13->GetMeanError() != 0) hMeansModules->SetBinError(13,h900SignalM13->GetMeanError());
   if (h900SignalM14->GetMeanError() != 0) hMeansModules->SetBinError(14,h900SignalM14->GetMeanError());
   
   if (h900MCSignalM1->GetMeanError() != 0) hMeansModulesMC->SetBinError(1,h900MCSignalM1->GetMeanError());
   if (h900MCSignalM2->GetMeanError() != 0) hMeansModulesMC->SetBinError(2,h900MCSignalM2->GetMeanError());
   if (h900MCSignalM3->GetMeanError() != 0) hMeansModulesMC->SetBinError(3,h900MCSignalM3->GetMeanError());
   if (h900MCSignalM4->GetMeanError() != 0) hMeansModulesMC->SetBinError(4,h900MCSignalM4->GetMeanError());
   if (h900MCSignalM5->GetMeanError() != 0) hMeansModulesMC->SetBinError(5,h900MCSignalM5->GetMeanError());
   if (h900MCSignalM6->GetMeanError() != 0) hMeansModulesMC->SetBinError(6,h900MCSignalM6->GetMeanError());
   if (h900MCSignalM7->GetMeanError() != 0) hMeansModulesMC->SetBinError(7,h900MCSignalM7->GetMeanError());
   if (h900MCSignalM8->GetMeanError() != 0) hMeansModulesMC->SetBinError(8,h900MCSignalM8->GetMeanError());
   if (h900MCSignalM9->GetMeanError() != 0) hMeansModulesMC->SetBinError(9,h900MCSignalM9->GetMeanError());
   if (h900MCSignalM10->GetMeanError() != 0) hMeansModulesMC->SetBinError(10,h900MCSignalM10->GetMeanError());
   if (h900MCSignalM11->GetMeanError() != 0) hMeansModulesMC->SetBinError(11,h900MCSignalM11->GetMeanError());
   if (h900MCSignalM12->GetMeanError() != 0) hMeansModulesMC->SetBinError(12,h900MCSignalM12->GetMeanError());
   if (h900MCSignalM13->GetMeanError() != 0) hMeansModulesMC->SetBinError(13,h900MCSignalM13->GetMeanError());
   if (h900MCSignalM14->GetMeanError() != 0) hMeansModulesMC->SetBinError(14,h900MCSignalM14->GetMeanError());
   
     
    if (h900SignalPFDijetM1->GetMean() != 0) hMeansQCDModules->SetBinContent(1,h900SignalPFDijetM1->GetMean());
   if (h900SignalPFDijetM2->GetMean() != 0) hMeansQCDModules->SetBinContent(2,h900SignalPFDijetM2->GetMean());
   if (h900SignalPFDijetM3->GetMean() != 0) hMeansQCDModules->SetBinContent(3,h900SignalPFDijetM3->GetMean());
   if (h900SignalPFDijetM4->GetMean() != 0) hMeansQCDModules->SetBinContent(4,h900SignalPFDijetM4->GetMean());
   if (h900SignalPFDijetM5->GetMean() != 0) hMeansQCDModules->SetBinContent(5,h900SignalPFDijetM5->GetMean());
   if (h900SignalPFDijetM6->GetMean() != 0) hMeansQCDModules->SetBinContent(6,h900SignalPFDijetM6->GetMean());
   if (h900SignalPFDijetM7->GetMean() != 0) hMeansQCDModules->SetBinContent(7,h900SignalPFDijetM7->GetMean());
   if (h900SignalPFDijetM8->GetMean() != 0) hMeansQCDModules->SetBinContent(8,h900SignalPFDijetM8->GetMean());
   if (h900SignalPFDijetM9->GetMean() != 0) hMeansQCDModules->SetBinContent(9,h900SignalPFDijetM9->GetMean());
   if (h900SignalPFDijetM10->GetMean() != 0) hMeansQCDModules->SetBinContent(10,h900SignalPFDijetM10->GetMean());
   if (h900SignalPFDijetM11->GetMean() != 0) hMeansQCDModules->SetBinContent(11,h900SignalPFDijetM11->GetMean());
   if (h900SignalPFDijetM12->GetMean() != 0) hMeansQCDModules->SetBinContent(12,h900SignalPFDijetM12->GetMean());
   if (h900SignalPFDijetM13->GetMean() != 0) hMeansQCDModules->SetBinContent(13,h900SignalPFDijetM13->GetMean());
   if (h900SignalPFDijetM14->GetMean() != 0) hMeansQCDModules->SetBinContent(14,h900SignalPFDijetM14->GetMean());
   
   if (h900MCSignalPFDijetM1->GetMean() != 0) hMeansQCDModulesMC->SetBinContent(1,h900MCSignalPFDijetM1->GetMean());
   if (h900MCSignalPFDijetM2->GetMean() != 0) hMeansQCDModulesMC->SetBinContent(2,h900MCSignalPFDijetM2->GetMean());
   if (h900MCSignalPFDijetM3->GetMean() != 0) hMeansQCDModulesMC->SetBinContent(3,h900MCSignalPFDijetM3->GetMean());
   if (h900MCSignalPFDijetM4->GetMean() != 0) hMeansQCDModulesMC->SetBinContent(4,h900MCSignalPFDijetM4->GetMean());
   if (h900MCSignalPFDijetM5->GetMean() != 0) hMeansQCDModulesMC->SetBinContent(5,h900MCSignalPFDijetM5->GetMean());
   if (h900MCSignalPFDijetM6->GetMean() != 0) hMeansQCDModulesMC->SetBinContent(6,h900MCSignalPFDijetM6->GetMean());
   if (h900MCSignalPFDijetM7->GetMean() != 0) hMeansQCDModulesMC->SetBinContent(7,h900MCSignalPFDijetM7->GetMean());
   if (h900MCSignalPFDijetM8->GetMean() != 0) hMeansQCDModulesMC->SetBinContent(8,h900MCSignalPFDijetM8->GetMean());
   if (h900MCSignalPFDijetM9->GetMean() != 0) hMeansQCDModulesMC->SetBinContent(9,h900MCSignalPFDijetM9->GetMean());
   if (h900MCSignalPFDijetM10->GetMean() != 0) hMeansQCDModulesMC->SetBinContent(10,h900MCSignalPFDijetM10->GetMean());
   if (h900MCSignalPFDijetM11->GetMean() != 0) hMeansQCDModulesMC->SetBinContent(11,h900MCSignalPFDijetM11->GetMean());
   if (h900MCSignalPFDijetM12->GetMean() != 0) hMeansQCDModulesMC->SetBinContent(12,h900MCSignalPFDijetM12->GetMean());
   if (h900MCSignalPFDijetM13->GetMean() != 0) hMeansQCDModulesMC->SetBinContent(13,h900MCSignalPFDijetM13->GetMean());
   if (h900MCSignalPFDijetM14->GetMean() != 0) hMeansQCDModulesMC->SetBinContent(14,h900MCSignalPFDijetM14->GetMean());
   
     if (h900SignalPFDijetM1->GetMeanError() != 0) hMeansQCDModules->SetBinError(1,h900SignalPFDijetM1->GetMeanError());
   if (h900SignalPFDijetM2->GetMeanError() != 0) hMeansQCDModules->SetBinError(2,h900SignalPFDijetM2->GetMeanError());
   if (h900SignalPFDijetM3->GetMeanError() != 0) hMeansQCDModules->SetBinError(3,h900SignalPFDijetM3->GetMeanError());
   if (h900SignalPFDijetM4->GetMeanError() != 0) hMeansQCDModules->SetBinError(4,h900SignalPFDijetM4->GetMeanError());
   if (h900SignalPFDijetM5->GetMeanError() != 0) hMeansQCDModules->SetBinError(5,h900SignalPFDijetM5->GetMeanError());
   if (h900SignalPFDijetM6->GetMeanError() != 0) hMeansQCDModules->SetBinError(6,h900SignalPFDijetM6->GetMeanError());
   if (h900SignalPFDijetM7->GetMeanError() != 0) hMeansQCDModules->SetBinError(7,h900SignalPFDijetM7->GetMeanError());
   if (h900SignalPFDijetM8->GetMeanError() != 0) hMeansQCDModules->SetBinError(8,h900SignalPFDijetM8->GetMeanError());
   if (h900SignalPFDijetM9->GetMeanError() != 0) hMeansQCDModules->SetBinError(9,h900SignalPFDijetM9->GetMeanError());
   if (h900SignalPFDijetM10->GetMeanError() != 0) hMeansQCDModules->SetBinError(10,h900SignalPFDijetM10->GetMeanError());
   if (h900SignalPFDijetM11->GetMeanError() != 0) hMeansQCDModules->SetBinError(11,h900SignalPFDijetM11->GetMeanError());
   if (h900SignalPFDijetM12->GetMeanError() != 0) hMeansQCDModules->SetBinError(12,h900SignalPFDijetM12->GetMeanError());
   if (h900SignalPFDijetM13->GetMeanError() != 0) hMeansQCDModules->SetBinError(13,h900SignalPFDijetM13->GetMeanError());
   if (h900SignalPFDijetM14->GetMeanError() != 0) hMeansQCDModules->SetBinError(14,h900SignalPFDijetM14->GetMeanError());
   
   if (h900MCSignalPFDijetM1->GetMeanError() != 0) hMeansQCDModulesMC->SetBinError(1,h900MCSignalPFDijetM1->GetMeanError());
   if (h900MCSignalPFDijetM2->GetMeanError() != 0) hMeansQCDModulesMC->SetBinError(2,h900MCSignalPFDijetM2->GetMeanError());
   if (h900MCSignalPFDijetM3->GetMeanError() != 0) hMeansQCDModulesMC->SetBinError(3,h900MCSignalPFDijetM3->GetMeanError());
   if (h900MCSignalPFDijetM4->GetMeanError() != 0) hMeansQCDModulesMC->SetBinError(4,h900MCSignalPFDijetM4->GetMeanError());
   if (h900MCSignalPFDijetM5->GetMeanError() != 0) hMeansQCDModulesMC->SetBinError(5,h900MCSignalPFDijetM5->GetMeanError());
   if (h900MCSignalPFDijetM6->GetMeanError() != 0) hMeansQCDModulesMC->SetBinError(6,h900MCSignalPFDijetM6->GetMeanError());
   if (h900MCSignalPFDijetM7->GetMeanError() != 0) hMeansQCDModulesMC->SetBinError(7,h900MCSignalPFDijetM7->GetMeanError());
   if (h900MCSignalPFDijetM8->GetMeanError() != 0) hMeansQCDModulesMC->SetBinError(8,h900MCSignalPFDijetM8->GetMeanError());
   if (h900MCSignalPFDijetM9->GetMeanError() != 0) hMeansQCDModulesMC->SetBinError(9,h900MCSignalPFDijetM9->GetMeanError());
   if (h900MCSignalPFDijetM10->GetMeanError() != 0) hMeansQCDModulesMC->SetBinError(10,h900MCSignalPFDijetM10->GetMeanError());
   if (h900MCSignalPFDijetM11->GetMeanError() != 0) hMeansQCDModulesMC->SetBinError(11,h900MCSignalPFDijetM11->GetMeanError());
   if (h900MCSignalPFDijetM12->GetMeanError() != 0) hMeansQCDModulesMC->SetBinError(12,h900MCSignalPFDijetM12->GetMeanError());
   if (h900MCSignalPFDijetM13->GetMeanError() != 0) hMeansQCDModulesMC->SetBinError(13,h900MCSignalPFDijetM13->GetMeanError());
   if (h900MCSignalPFDijetM14->GetMeanError() != 0) hMeansQCDModulesMC->SetBinError(14,h900MCSignalPFDijetM14->GetMeanError());
 
   TCanvas *cMeansModules = new TCanvas("cMeansModules","MB and QCD means in CASTOR modules for 900 GeV");
   cMeansModules->Divide(2,1);
   cMeansModules->cd(1);
   hMeansModules->GetYaxis()->SetTitle("Means 900GeV data");
   hMeansModules->SetMarkerColor(kBlue);
   hMeansModules->Draw("");
   hMeansQCDModules->Draw("same");
   cMeansModules->cd(2);
   hMeansModulesMC->GetYaxis()->SetTitle("Means 900GeV MC");
   hMeansModulesMC->SetMarkerColor(kBlue);
   hMeansModulesMC->Draw("");
   hMeansQCDModulesMC->Draw("same");
   
   if (h900SignalS1->GetMean() != 0) hMeansSectors->SetBinContent(1,h900SignalS1->GetMean());
   if (h900SignalS2->GetMean() != 0) hMeansSectors->SetBinContent(2,h900SignalS2->GetMean());
   if (h900SignalS3->GetMean() != 0) hMeansSectors->SetBinContent(3,h900SignalS3->GetMean());
   if (h900SignalS4->GetMean() != 0) hMeansSectors->SetBinContent(4,h900SignalS4->GetMean());
   if (h900SignalS5->GetMean() != 0) hMeansSectors->SetBinContent(5,h900SignalS5->GetMean());
   if (h900SignalS6->GetMean() != 0) hMeansSectors->SetBinContent(6,h900SignalS6->GetMean());
   if (h900SignalS7->GetMean() != 0) hMeansSectors->SetBinContent(7,h900SignalS7->GetMean());
   if (h900SignalS8->GetMean() != 0) hMeansSectors->SetBinContent(8,h900SignalS8->GetMean());
   if (h900SignalS9->GetMean() != 0) hMeansSectors->SetBinContent(9,h900SignalS9->GetMean());
   if (h900SignalS10->GetMean() != 0) hMeansSectors->SetBinContent(10,h900SignalS10->GetMean());
   if (h900SignalS11->GetMean() != 0) hMeansSectors->SetBinContent(11,h900SignalS11->GetMean());
   if (h900SignalS12->GetMean() != 0) hMeansSectors->SetBinContent(12,h900SignalS12->GetMean());
   if (h900SignalS13->GetMean() != 0) hMeansSectors->SetBinContent(13,h900SignalS13->GetMean());
   if (h900SignalS14->GetMean() != 0) hMeansSectors->SetBinContent(14,h900SignalS14->GetMean());
   if (h900SignalS15->GetMean() != 0) hMeansSectors->SetBinContent(15,h900SignalS15->GetMean());
   if (h900SignalS16->GetMean() != 0) hMeansSectors->SetBinContent(16,h900SignalS16->GetMean());
   
   if (h900MCSignalS1->GetMean() != 0) hMeansSectorsMC->SetBinContent(1,h900MCSignalS1->GetMean());
   if (h900MCSignalS2->GetMean() != 0) hMeansSectorsMC->SetBinContent(2,h900MCSignalS2->GetMean());
   if (h900MCSignalS3->GetMean() != 0) hMeansSectorsMC->SetBinContent(3,h900MCSignalS3->GetMean());
   if (h900MCSignalS4->GetMean() != 0) hMeansSectorsMC->SetBinContent(4,h900MCSignalS4->GetMean());
   if (h900MCSignalS5->GetMean() != 0) hMeansSectorsMC->SetBinContent(5,h900MCSignalS5->GetMean());
   if (h900MCSignalS6->GetMean() != 0) hMeansSectorsMC->SetBinContent(6,h900MCSignalS6->GetMean());
   if (h900MCSignalS7->GetMean() != 0) hMeansSectorsMC->SetBinContent(7,h900MCSignalS7->GetMean());
   if (h900MCSignalS8->GetMean() != 0) hMeansSectorsMC->SetBinContent(8,h900MCSignalS8->GetMean());
   if (h900MCSignalS9->GetMean() != 0) hMeansSectorsMC->SetBinContent(9,h900MCSignalS9->GetMean());
   if (h900MCSignalS10->GetMean() != 0) hMeansSectorsMC->SetBinContent(10,h900MCSignalS10->GetMean());
   if (h900MCSignalS11->GetMean() != 0) hMeansSectorsMC->SetBinContent(11,h900MCSignalS11->GetMean());
   if (h900MCSignalS12->GetMean() != 0) hMeansSectorsMC->SetBinContent(12,h900MCSignalS12->GetMean());
   if (h900MCSignalS13->GetMean() != 0) hMeansSectorsMC->SetBinContent(13,h900MCSignalS13->GetMean());
   if (h900MCSignalS14->GetMean() != 0) hMeansSectorsMC->SetBinContent(14,h900MCSignalS14->GetMean());
   if (h900MCSignalS15->GetMean() != 0) hMeansSectorsMC->SetBinContent(15,h900MCSignalS15->GetMean());
   if (h900MCSignalS16->GetMean() != 0) hMeansSectorsMC->SetBinContent(16,h900MCSignalS16->GetMean());
   
     if (h900SignalS1->GetMeanError() != 0) hMeansSectors->SetBinError(1,h900SignalS1->GetMeanError());
   if (h900SignalS2->GetMeanError() != 0) hMeansSectors->SetBinError(2,h900SignalS2->GetMeanError());
   if (h900SignalS3->GetMeanError() != 0) hMeansSectors->SetBinError(3,h900SignalS3->GetMeanError());
   if (h900SignalS4->GetMeanError() != 0) hMeansSectors->SetBinError(4,h900SignalS4->GetMeanError());
   if (h900SignalS5->GetMeanError() != 0) hMeansSectors->SetBinError(5,h900SignalS5->GetMeanError());
   if (h900SignalS6->GetMeanError() != 0) hMeansSectors->SetBinError(6,h900SignalS6->GetMeanError());
   if (h900SignalS7->GetMeanError() != 0) hMeansSectors->SetBinError(7,h900SignalS7->GetMeanError());
   if (h900SignalS8->GetMeanError() != 0) hMeansSectors->SetBinError(8,h900SignalS8->GetMeanError());
   if (h900SignalS9->GetMeanError() != 0) hMeansSectors->SetBinError(9,h900SignalS9->GetMeanError());
   if (h900SignalS10->GetMeanError() != 0) hMeansSectors->SetBinError(10,h900SignalS10->GetMeanError());
   if (h900SignalS11->GetMeanError() != 0) hMeansSectors->SetBinError(11,h900SignalS11->GetMeanError());
   if (h900SignalS12->GetMeanError() != 0) hMeansSectors->SetBinError(12,h900SignalS12->GetMeanError());
   if (h900SignalS13->GetMeanError() != 0) hMeansSectors->SetBinError(13,h900SignalS13->GetMeanError());
   if (h900SignalS14->GetMeanError() != 0) hMeansSectors->SetBinError(14,h900SignalS14->GetMeanError());
   if (h900SignalS15->GetMeanError() != 0) hMeansSectors->SetBinError(15,h900SignalS15->GetMeanError());
   if (h900SignalS16->GetMeanError() != 0) hMeansSectors->SetBinError(16,h900SignalS16->GetMeanError());
   
   if (h900MCSignalS1->GetMeanError() != 0) hMeansSectorsMC->SetBinError(1,h900MCSignalS1->GetMeanError());
   if (h900MCSignalS2->GetMeanError() != 0) hMeansSectorsMC->SetBinError(2,h900MCSignalS2->GetMeanError());
   if (h900MCSignalS3->GetMeanError() != 0) hMeansSectorsMC->SetBinError(3,h900MCSignalS3->GetMeanError());
   if (h900MCSignalS4->GetMeanError() != 0) hMeansSectorsMC->SetBinError(4,h900MCSignalS4->GetMeanError());
   if (h900MCSignalS5->GetMeanError() != 0) hMeansSectorsMC->SetBinError(5,h900MCSignalS5->GetMeanError());
   if (h900MCSignalS6->GetMeanError() != 0) hMeansSectorsMC->SetBinError(6,h900MCSignalS6->GetMeanError());
   if (h900MCSignalS7->GetMeanError() != 0) hMeansSectorsMC->SetBinError(7,h900MCSignalS7->GetMeanError());
   if (h900MCSignalS8->GetMeanError() != 0) hMeansSectorsMC->SetBinError(8,h900MCSignalS8->GetMeanError());
   if (h900MCSignalS9->GetMeanError() != 0) hMeansSectorsMC->SetBinError(9,h900MCSignalS9->GetMeanError());
   if (h900MCSignalS10->GetMeanError() != 0) hMeansSectorsMC->SetBinError(10,h900MCSignalS10->GetMeanError());
   if (h900MCSignalS11->GetMeanError() != 0) hMeansSectorsMC->SetBinError(11,h900MCSignalS11->GetMeanError());
   if (h900MCSignalS12->GetMeanError() != 0) hMeansSectorsMC->SetBinError(12,h900MCSignalS12->GetMeanError());
   if (h900MCSignalS13->GetMeanError() != 0) hMeansSectorsMC->SetBinError(13,h900MCSignalS13->GetMeanError());
   if (h900MCSignalS14->GetMeanError() != 0) hMeansSectorsMC->SetBinError(14,h900MCSignalS14->GetMeanError());
   if (h900MCSignalS15->GetMeanError() != 0) hMeansSectorsMC->SetBinError(15,h900MCSignalS15->GetMeanError());
   if (h900MCSignalS16->GetMeanError() != 0) hMeansSectorsMC->SetBinError(16,h900MCSignalS16->GetMeanError());
   
     
    if (h900SignalPFDijetS1->GetMean() != 0) hMeansQCDSectors->SetBinContent(1,h900SignalPFDijetS1->GetMean());
   if (h900SignalPFDijetS2->GetMean() != 0) hMeansQCDSectors->SetBinContent(2,h900SignalPFDijetS2->GetMean());
   if (h900SignalPFDijetS3->GetMean() != 0) hMeansQCDSectors->SetBinContent(3,h900SignalPFDijetS3->GetMean());
   if (h900SignalPFDijetS4->GetMean() != 0) hMeansQCDSectors->SetBinContent(4,h900SignalPFDijetS4->GetMean());
   if (h900SignalPFDijetS5->GetMean() != 0) hMeansQCDSectors->SetBinContent(5,h900SignalPFDijetS5->GetMean());
   if (h900SignalPFDijetS6->GetMean() != 0) hMeansQCDSectors->SetBinContent(6,h900SignalPFDijetS6->GetMean());
   if (h900SignalPFDijetS7->GetMean() != 0) hMeansQCDSectors->SetBinContent(7,h900SignalPFDijetS7->GetMean());
   if (h900SignalPFDijetS8->GetMean() != 0) hMeansQCDSectors->SetBinContent(8,h900SignalPFDijetS8->GetMean());
   if (h900SignalPFDijetS9->GetMean() != 0) hMeansQCDSectors->SetBinContent(9,h900SignalPFDijetS9->GetMean());
   if (h900SignalPFDijetS10->GetMean() != 0) hMeansQCDSectors->SetBinContent(10,h900SignalPFDijetS10->GetMean());
   if (h900SignalPFDijetS11->GetMean() != 0) hMeansQCDSectors->SetBinContent(11,h900SignalPFDijetS11->GetMean());
   if (h900SignalPFDijetS12->GetMean() != 0) hMeansQCDSectors->SetBinContent(12,h900SignalPFDijetS12->GetMean());
   if (h900SignalPFDijetS13->GetMean() != 0) hMeansQCDSectors->SetBinContent(13,h900SignalPFDijetS13->GetMean());
   if (h900SignalPFDijetS14->GetMean() != 0) hMeansQCDSectors->SetBinContent(14,h900SignalPFDijetS14->GetMean());
   if (h900SignalPFDijetS15->GetMean() != 0) hMeansQCDSectors->SetBinContent(15,h900SignalPFDijetS15->GetMean());
   if (h900SignalPFDijetS16->GetMean() != 0) hMeansQCDSectors->SetBinContent(16,h900SignalPFDijetS16->GetMean());
   
   if (h900MCSignalPFDijetS1->GetMean() != 0) hMeansQCDSectorsMC->SetBinContent(1,h900MCSignalPFDijetS1->GetMean());
   if (h900MCSignalPFDijetS2->GetMean() != 0) hMeansQCDSectorsMC->SetBinContent(2,h900MCSignalPFDijetS2->GetMean());
   if (h900MCSignalPFDijetS3->GetMean() != 0) hMeansQCDSectorsMC->SetBinContent(3,h900MCSignalPFDijetS3->GetMean());
   if (h900MCSignalPFDijetS4->GetMean() != 0) hMeansQCDSectorsMC->SetBinContent(4,h900MCSignalPFDijetS4->GetMean());
   if (h900MCSignalPFDijetS5->GetMean() != 0) hMeansQCDSectorsMC->SetBinContent(5,h900MCSignalPFDijetS5->GetMean());
   if (h900MCSignalPFDijetS6->GetMean() != 0) hMeansQCDSectorsMC->SetBinContent(6,h900MCSignalPFDijetS6->GetMean());
   if (h900MCSignalPFDijetS7->GetMean() != 0) hMeansQCDSectorsMC->SetBinContent(7,h900MCSignalPFDijetS7->GetMean());
   if (h900MCSignalPFDijetS8->GetMean() != 0) hMeansQCDSectorsMC->SetBinContent(8,h900MCSignalPFDijetS8->GetMean());
   if (h900MCSignalPFDijetS9->GetMean() != 0) hMeansQCDSectorsMC->SetBinContent(9,h900MCSignalPFDijetS9->GetMean());
   if (h900MCSignalPFDijetS10->GetMean() != 0) hMeansQCDSectorsMC->SetBinContent(10,h900MCSignalPFDijetS10->GetMean());
   if (h900MCSignalPFDijetS11->GetMean() != 0) hMeansQCDSectorsMC->SetBinContent(11,h900MCSignalPFDijetS11->GetMean());
   if (h900MCSignalPFDijetS12->GetMean() != 0) hMeansQCDSectorsMC->SetBinContent(12,h900MCSignalPFDijetS12->GetMean());
   if (h900MCSignalPFDijetS13->GetMean() != 0) hMeansQCDSectorsMC->SetBinContent(13,h900MCSignalPFDijetS13->GetMean());
   if (h900MCSignalPFDijetS14->GetMean() != 0) hMeansQCDSectorsMC->SetBinContent(14,h900MCSignalPFDijetS14->GetMean());
   if (h900MCSignalPFDijetS15->GetMean() != 0) hMeansQCDSectorsMC->SetBinContent(15,h900MCSignalPFDijetS15->GetMean());
   if (h900MCSignalPFDijetS16->GetMean() != 0) hMeansQCDSectorsMC->SetBinContent(16,h900MCSignalPFDijetS16->GetMean());
   
     if (h900SignalPFDijetS1->GetMeanError() != 0) hMeansQCDSectors->SetBinError(1,h900SignalPFDijetS1->GetMeanError());
   if (h900SignalPFDijetS2->GetMeanError() != 0) hMeansQCDSectors->SetBinError(2,h900SignalPFDijetS2->GetMeanError());
   if (h900SignalPFDijetS3->GetMeanError() != 0) hMeansQCDSectors->SetBinError(3,h900SignalPFDijetS3->GetMeanError());
   if (h900SignalPFDijetS4->GetMeanError() != 0) hMeansQCDSectors->SetBinError(4,h900SignalPFDijetS4->GetMeanError());
   if (h900SignalPFDijetS5->GetMeanError() != 0) hMeansQCDSectors->SetBinError(5,h900SignalPFDijetS5->GetMeanError());
   if (h900SignalPFDijetS6->GetMeanError() != 0) hMeansQCDSectors->SetBinError(6,h900SignalPFDijetS6->GetMeanError());
   if (h900SignalPFDijetS7->GetMeanError() != 0) hMeansQCDSectors->SetBinError(7,h900SignalPFDijetS7->GetMeanError());
   if (h900SignalPFDijetS8->GetMeanError() != 0) hMeansQCDSectors->SetBinError(8,h900SignalPFDijetS8->GetMeanError());
   if (h900SignalPFDijetS9->GetMeanError() != 0) hMeansQCDSectors->SetBinError(9,h900SignalPFDijetS9->GetMeanError());
   if (h900SignalPFDijetS10->GetMeanError() != 0) hMeansQCDSectors->SetBinError(10,h900SignalPFDijetS10->GetMeanError());
   if (h900SignalPFDijetS11->GetMeanError() != 0) hMeansQCDSectors->SetBinError(11,h900SignalPFDijetS11->GetMeanError());
   if (h900SignalPFDijetS12->GetMeanError() != 0) hMeansQCDSectors->SetBinError(12,h900SignalPFDijetS12->GetMeanError());
   if (h900SignalPFDijetS13->GetMeanError() != 0) hMeansQCDSectors->SetBinError(13,h900SignalPFDijetS13->GetMeanError());
   if (h900SignalPFDijetS14->GetMeanError() != 0) hMeansQCDSectors->SetBinError(14,h900SignalPFDijetS14->GetMeanError());
   if (h900SignalPFDijetS15->GetMeanError() != 0) hMeansQCDSectors->SetBinError(15,h900SignalPFDijetS15->GetMeanError());
   if (h900SignalPFDijetS16->GetMeanError() != 0) hMeansQCDSectors->SetBinError(16,h900SignalPFDijetS16->GetMeanError());
   
   if (h900MCSignalPFDijetS1->GetMeanError() != 0) hMeansQCDSectorsMC->SetBinError(1,h900MCSignalPFDijetS1->GetMeanError());
   if (h900MCSignalPFDijetS2->GetMeanError() != 0) hMeansQCDSectorsMC->SetBinError(2,h900MCSignalPFDijetS2->GetMeanError());
   if (h900MCSignalPFDijetS3->GetMeanError() != 0) hMeansQCDSectorsMC->SetBinError(3,h900MCSignalPFDijetS3->GetMeanError());
   if (h900MCSignalPFDijetS4->GetMeanError() != 0) hMeansQCDSectorsMC->SetBinError(4,h900MCSignalPFDijetS4->GetMeanError());
   if (h900MCSignalPFDijetS5->GetMeanError() != 0) hMeansQCDSectorsMC->SetBinError(5,h900MCSignalPFDijetS5->GetMeanError());
   if (h900MCSignalPFDijetS6->GetMeanError() != 0) hMeansQCDSectorsMC->SetBinError(6,h900MCSignalPFDijetS6->GetMeanError());
   if (h900MCSignalPFDijetS7->GetMeanError() != 0) hMeansQCDSectorsMC->SetBinError(7,h900MCSignalPFDijetS7->GetMeanError());
   if (h900MCSignalPFDijetS8->GetMeanError() != 0) hMeansQCDSectorsMC->SetBinError(8,h900MCSignalPFDijetS8->GetMeanError());
   if (h900MCSignalPFDijetS9->GetMeanError() != 0) hMeansQCDSectorsMC->SetBinError(9,h900MCSignalPFDijetS9->GetMeanError());
   if (h900MCSignalPFDijetS10->GetMeanError() != 0) hMeansQCDSectorsMC->SetBinError(10,h900MCSignalPFDijetS10->GetMeanError());
   if (h900MCSignalPFDijetS11->GetMeanError() != 0) hMeansQCDSectorsMC->SetBinError(11,h900MCSignalPFDijetS11->GetMeanError());
   if (h900MCSignalPFDijetS12->GetMeanError() != 0) hMeansQCDSectorsMC->SetBinError(12,h900MCSignalPFDijetS12->GetMeanError());
   if (h900MCSignalPFDijetS13->GetMeanError() != 0) hMeansQCDSectorsMC->SetBinError(13,h900MCSignalPFDijetS13->GetMeanError());
   if (h900MCSignalPFDijetS14->GetMeanError() != 0) hMeansQCDSectorsMC->SetBinError(14,h900MCSignalPFDijetS14->GetMeanError());
   if (h900MCSignalPFDijetS15->GetMeanError() != 0) hMeansQCDSectorsMC->SetBinError(15,h900MCSignalPFDijetS15->GetMeanError());
   if (h900MCSignalPFDijetS16->GetMeanError() != 0) hMeansQCDSectorsMC->SetBinError(16,h900MCSignalPFDijetS16->GetMeanError());
   
   TCanvas *cMeansSectors = new TCanvas("cMeansSectors","MB and QCD means in CASTOR Sectors for 900 GeV");
   cMeansSectors->Divide(2,1);
   cMeansSectors->cd(1);
   hMeansSectors->SetMarkerColor(kBlue);
   hMeansSectors->GetYaxis()->SetTitle("Means 900GeV data");
   hMeansSectors->Draw("");
   hMeansQCDSectors->Draw("same");
   cMeansSectors->cd(2);
   hMeansSectorsMC->GetYaxis()->SetTitle("Means 900GeV MC");
   hMeansSectorsMC->SetMarkerColor(kBlue);
   hMeansSectorsMC->Draw("");
   hMeansQCDSectorsMC->Draw("same");
   
      /////////////////////////////////////////////////
   // plot Means2360 for MB and QCD vs module and sector
   /////////////////////////////////////////////////
   
    if (h2360SignalM1->GetMean() != 0) hMeans2360Modules->SetBinContent(1,h2360SignalM1->GetMean());
   if (h2360SignalM2->GetMean() != 0) hMeans2360Modules->SetBinContent(2,h2360SignalM2->GetMean());
   if (h2360SignalM3->GetMean() != 0) hMeans2360Modules->SetBinContent(3,h2360SignalM3->GetMean());
   if (h2360SignalM4->GetMean() != 0) hMeans2360Modules->SetBinContent(4,h2360SignalM4->GetMean());
   if (h2360SignalM5->GetMean() != 0) hMeans2360Modules->SetBinContent(5,h2360SignalM5->GetMean());
   if (h2360SignalM6->GetMean() != 0) hMeans2360Modules->SetBinContent(6,h2360SignalM6->GetMean());
   if (h2360SignalM7->GetMean() != 0) hMeans2360Modules->SetBinContent(7,h2360SignalM7->GetMean());
   if (h2360SignalM8->GetMean() != 0) hMeans2360Modules->SetBinContent(8,h2360SignalM8->GetMean());
   if (h2360SignalM9->GetMean() != 0) hMeans2360Modules->SetBinContent(9,h2360SignalM9->GetMean());
   if (h2360SignalM10->GetMean() != 0) hMeans2360Modules->SetBinContent(10,h2360SignalM10->GetMean());
   if (h2360SignalM11->GetMean() != 0) hMeans2360Modules->SetBinContent(11,h2360SignalM11->GetMean());
   if (h2360SignalM12->GetMean() != 0) hMeans2360Modules->SetBinContent(12,h2360SignalM12->GetMean());
   if (h2360SignalM13->GetMean() != 0) hMeans2360Modules->SetBinContent(13,h2360SignalM13->GetMean());
   if (h2360SignalM14->GetMean() != 0) hMeans2360Modules->SetBinContent(14,h2360SignalM14->GetMean());
   
   if (h2360MCSignalM1->GetMean() != 0) hMeans2360ModulesMC->SetBinContent(1,h2360MCSignalM1->GetMean());
   if (h2360MCSignalM2->GetMean() != 0) hMeans2360ModulesMC->SetBinContent(2,h2360MCSignalM2->GetMean());
   if (h2360MCSignalM3->GetMean() != 0) hMeans2360ModulesMC->SetBinContent(3,h2360MCSignalM3->GetMean());
   if (h2360MCSignalM4->GetMean() != 0) hMeans2360ModulesMC->SetBinContent(4,h2360MCSignalM4->GetMean());
   if (h2360MCSignalM5->GetMean() != 0) hMeans2360ModulesMC->SetBinContent(5,h2360MCSignalM5->GetMean());
   if (h2360MCSignalM6->GetMean() != 0) hMeans2360ModulesMC->SetBinContent(6,h2360MCSignalM6->GetMean());
   if (h2360MCSignalM7->GetMean() != 0) hMeans2360ModulesMC->SetBinContent(7,h2360MCSignalM7->GetMean());
   if (h2360MCSignalM8->GetMean() != 0) hMeans2360ModulesMC->SetBinContent(8,h2360MCSignalM8->GetMean());
   if (h2360MCSignalM9->GetMean() != 0) hMeans2360ModulesMC->SetBinContent(9,h2360MCSignalM9->GetMean());
   if (h2360MCSignalM10->GetMean() != 0) hMeans2360ModulesMC->SetBinContent(10,h2360MCSignalM10->GetMean());
   if (h2360MCSignalM11->GetMean() != 0) hMeans2360ModulesMC->SetBinContent(11,h2360MCSignalM11->GetMean());
   if (h2360MCSignalM12->GetMean() != 0) hMeans2360ModulesMC->SetBinContent(12,h2360MCSignalM12->GetMean());
   if (h2360MCSignalM13->GetMean() != 0) hMeans2360ModulesMC->SetBinContent(13,h2360MCSignalM13->GetMean());
   if (h2360MCSignalM14->GetMean() != 0) hMeans2360ModulesMC->SetBinContent(14,h2360MCSignalM14->GetMean());
   
     if (h2360SignalM1->GetMeanError() != 0) hMeans2360Modules->SetBinError(1,h2360SignalM1->GetMeanError());
   if (h2360SignalM2->GetMeanError() != 0) hMeans2360Modules->SetBinError(2,h2360SignalM2->GetMeanError());
   if (h2360SignalM3->GetMeanError() != 0) hMeans2360Modules->SetBinError(3,h2360SignalM3->GetMeanError());
   if (h2360SignalM4->GetMeanError() != 0) hMeans2360Modules->SetBinError(4,h2360SignalM4->GetMeanError());
   if (h2360SignalM5->GetMeanError() != 0) hMeans2360Modules->SetBinError(5,h2360SignalM5->GetMeanError());
   if (h2360SignalM6->GetMeanError() != 0) hMeans2360Modules->SetBinError(6,h2360SignalM6->GetMeanError());
   if (h2360SignalM7->GetMeanError() != 0) hMeans2360Modules->SetBinError(7,h2360SignalM7->GetMeanError());
   if (h2360SignalM8->GetMeanError() != 0) hMeans2360Modules->SetBinError(8,h2360SignalM8->GetMeanError());
   if (h2360SignalM9->GetMeanError() != 0) hMeans2360Modules->SetBinError(9,h2360SignalM9->GetMeanError());
   if (h2360SignalM10->GetMeanError() != 0) hMeans2360Modules->SetBinError(10,h2360SignalM10->GetMeanError());
   if (h2360SignalM11->GetMeanError() != 0) hMeans2360Modules->SetBinError(11,h2360SignalM11->GetMeanError());
   if (h2360SignalM12->GetMeanError() != 0) hMeans2360Modules->SetBinError(12,h2360SignalM12->GetMeanError());
   if (h2360SignalM13->GetMeanError() != 0) hMeans2360Modules->SetBinError(13,h2360SignalM13->GetMeanError());
   if (h2360SignalM14->GetMeanError() != 0) hMeans2360Modules->SetBinError(14,h2360SignalM14->GetMeanError());
   
   if (h2360MCSignalM1->GetMeanError() != 0) hMeans2360ModulesMC->SetBinError(1,h2360MCSignalM1->GetMeanError());
   if (h2360MCSignalM2->GetMeanError() != 0) hMeans2360ModulesMC->SetBinError(2,h2360MCSignalM2->GetMeanError());
   if (h2360MCSignalM3->GetMeanError() != 0) hMeans2360ModulesMC->SetBinError(3,h2360MCSignalM3->GetMeanError());
   if (h2360MCSignalM4->GetMeanError() != 0) hMeans2360ModulesMC->SetBinError(4,h2360MCSignalM4->GetMeanError());
   if (h2360MCSignalM5->GetMeanError() != 0) hMeans2360ModulesMC->SetBinError(5,h2360MCSignalM5->GetMeanError());
   if (h2360MCSignalM6->GetMeanError() != 0) hMeans2360ModulesMC->SetBinError(6,h2360MCSignalM6->GetMeanError());
   if (h2360MCSignalM7->GetMeanError() != 0) hMeans2360ModulesMC->SetBinError(7,h2360MCSignalM7->GetMeanError());
   if (h2360MCSignalM8->GetMeanError() != 0) hMeans2360ModulesMC->SetBinError(8,h2360MCSignalM8->GetMeanError());
   if (h2360MCSignalM9->GetMeanError() != 0) hMeans2360ModulesMC->SetBinError(9,h2360MCSignalM9->GetMeanError());
   if (h2360MCSignalM10->GetMeanError() != 0) hMeans2360ModulesMC->SetBinError(10,h2360MCSignalM10->GetMeanError());
   if (h2360MCSignalM11->GetMeanError() != 0) hMeans2360ModulesMC->SetBinError(11,h2360MCSignalM11->GetMeanError());
   if (h2360MCSignalM12->GetMeanError() != 0) hMeans2360ModulesMC->SetBinError(12,h2360MCSignalM12->GetMeanError());
   if (h2360MCSignalM13->GetMeanError() != 0) hMeans2360ModulesMC->SetBinError(13,h2360MCSignalM13->GetMeanError());
   if (h2360MCSignalM14->GetMeanError() != 0) hMeans2360ModulesMC->SetBinError(14,h2360MCSignalM14->GetMeanError());
   
     
    if (h2360SignalPFDijetM1->GetMean() != 0) hMeans2360QCDModules->SetBinContent(1,h2360SignalPFDijetM1->GetMean());
   if (h2360SignalPFDijetM2->GetMean() != 0) hMeans2360QCDModules->SetBinContent(2,h2360SignalPFDijetM2->GetMean());
   if (h2360SignalPFDijetM3->GetMean() != 0) hMeans2360QCDModules->SetBinContent(3,h2360SignalPFDijetM3->GetMean());
   if (h2360SignalPFDijetM4->GetMean() != 0) hMeans2360QCDModules->SetBinContent(4,h2360SignalPFDijetM4->GetMean());
   if (h2360SignalPFDijetM5->GetMean() != 0) hMeans2360QCDModules->SetBinContent(5,h2360SignalPFDijetM5->GetMean());
   if (h2360SignalPFDijetM6->GetMean() != 0) hMeans2360QCDModules->SetBinContent(6,h2360SignalPFDijetM6->GetMean());
   if (h2360SignalPFDijetM7->GetMean() != 0) hMeans2360QCDModules->SetBinContent(7,h2360SignalPFDijetM7->GetMean());
   if (h2360SignalPFDijetM8->GetMean() != 0) hMeans2360QCDModules->SetBinContent(8,h2360SignalPFDijetM8->GetMean());
   if (h2360SignalPFDijetM9->GetMean() != 0) hMeans2360QCDModules->SetBinContent(9,h2360SignalPFDijetM9->GetMean());
   if (h2360SignalPFDijetM10->GetMean() != 0) hMeans2360QCDModules->SetBinContent(10,h2360SignalPFDijetM10->GetMean());
   if (h2360SignalPFDijetM11->GetMean() != 0) hMeans2360QCDModules->SetBinContent(11,h2360SignalPFDijetM11->GetMean());
   if (h2360SignalPFDijetM12->GetMean() != 0) hMeans2360QCDModules->SetBinContent(12,h2360SignalPFDijetM12->GetMean());
   if (h2360SignalPFDijetM13->GetMean() != 0) hMeans2360QCDModules->SetBinContent(13,h2360SignalPFDijetM13->GetMean());
   if (h2360SignalPFDijetM14->GetMean() != 0) hMeans2360QCDModules->SetBinContent(14,h2360SignalPFDijetM14->GetMean());
   
   if (h2360MCSignalPFDijetM1->GetMean() != 0) hMeans2360QCDModulesMC->SetBinContent(1,h2360MCSignalPFDijetM1->GetMean());
   if (h2360MCSignalPFDijetM2->GetMean() != 0) hMeans2360QCDModulesMC->SetBinContent(2,h2360MCSignalPFDijetM2->GetMean());
   if (h2360MCSignalPFDijetM3->GetMean() != 0) hMeans2360QCDModulesMC->SetBinContent(3,h2360MCSignalPFDijetM3->GetMean());
   if (h2360MCSignalPFDijetM4->GetMean() != 0) hMeans2360QCDModulesMC->SetBinContent(4,h2360MCSignalPFDijetM4->GetMean());
   if (h2360MCSignalPFDijetM5->GetMean() != 0) hMeans2360QCDModulesMC->SetBinContent(5,h2360MCSignalPFDijetM5->GetMean());
   if (h2360MCSignalPFDijetM6->GetMean() != 0) hMeans2360QCDModulesMC->SetBinContent(6,h2360MCSignalPFDijetM6->GetMean());
   if (h2360MCSignalPFDijetM7->GetMean() != 0) hMeans2360QCDModulesMC->SetBinContent(7,h2360MCSignalPFDijetM7->GetMean());
   if (h2360MCSignalPFDijetM8->GetMean() != 0) hMeans2360QCDModulesMC->SetBinContent(8,h2360MCSignalPFDijetM8->GetMean());
   if (h2360MCSignalPFDijetM9->GetMean() != 0) hMeans2360QCDModulesMC->SetBinContent(9,h2360MCSignalPFDijetM9->GetMean());
   if (h2360MCSignalPFDijetM10->GetMean() != 0) hMeans2360QCDModulesMC->SetBinContent(10,h2360MCSignalPFDijetM10->GetMean());
   if (h2360MCSignalPFDijetM11->GetMean() != 0) hMeans2360QCDModulesMC->SetBinContent(11,h2360MCSignalPFDijetM11->GetMean());
   if (h2360MCSignalPFDijetM12->GetMean() != 0) hMeans2360QCDModulesMC->SetBinContent(12,h2360MCSignalPFDijetM12->GetMean());
   if (h2360MCSignalPFDijetM13->GetMean() != 0) hMeans2360QCDModulesMC->SetBinContent(13,h2360MCSignalPFDijetM13->GetMean());
   if (h2360MCSignalPFDijetM14->GetMean() != 0) hMeans2360QCDModulesMC->SetBinContent(14,h2360MCSignalPFDijetM14->GetMean());
   
     if (h2360SignalPFDijetM1->GetMeanError() != 0) hMeans2360QCDModules->SetBinError(1,h2360SignalPFDijetM1->GetMeanError());
   if (h2360SignalPFDijetM2->GetMeanError() != 0) hMeans2360QCDModules->SetBinError(2,h2360SignalPFDijetM2->GetMeanError());
   if (h2360SignalPFDijetM3->GetMeanError() != 0) hMeans2360QCDModules->SetBinError(3,h2360SignalPFDijetM3->GetMeanError());
   if (h2360SignalPFDijetM4->GetMeanError() != 0) hMeans2360QCDModules->SetBinError(4,h2360SignalPFDijetM4->GetMeanError());
   if (h2360SignalPFDijetM5->GetMeanError() != 0) hMeans2360QCDModules->SetBinError(5,h2360SignalPFDijetM5->GetMeanError());
   if (h2360SignalPFDijetM6->GetMeanError() != 0) hMeans2360QCDModules->SetBinError(6,h2360SignalPFDijetM6->GetMeanError());
   if (h2360SignalPFDijetM7->GetMeanError() != 0) hMeans2360QCDModules->SetBinError(7,h2360SignalPFDijetM7->GetMeanError());
   if (h2360SignalPFDijetM8->GetMeanError() != 0) hMeans2360QCDModules->SetBinError(8,h2360SignalPFDijetM8->GetMeanError());
   if (h2360SignalPFDijetM9->GetMeanError() != 0) hMeans2360QCDModules->SetBinError(9,h2360SignalPFDijetM9->GetMeanError());
   if (h2360SignalPFDijetM10->GetMeanError() != 0) hMeans2360QCDModules->SetBinError(10,h2360SignalPFDijetM10->GetMeanError());
   if (h2360SignalPFDijetM11->GetMeanError() != 0) hMeans2360QCDModules->SetBinError(11,h2360SignalPFDijetM11->GetMeanError());
   if (h2360SignalPFDijetM12->GetMeanError() != 0) hMeans2360QCDModules->SetBinError(12,h2360SignalPFDijetM12->GetMeanError());
   if (h2360SignalPFDijetM13->GetMeanError() != 0) hMeans2360QCDModules->SetBinError(13,h2360SignalPFDijetM13->GetMeanError());
   if (h2360SignalPFDijetM14->GetMeanError() != 0) hMeans2360QCDModules->SetBinError(14,h2360SignalPFDijetM14->GetMeanError());
   
   if (h2360MCSignalPFDijetM1->GetMeanError() != 0) hMeans2360QCDModulesMC->SetBinError(1,h2360MCSignalPFDijetM1->GetMeanError());
   if (h2360MCSignalPFDijetM2->GetMeanError() != 0) hMeans2360QCDModulesMC->SetBinError(2,h2360MCSignalPFDijetM2->GetMeanError());
   if (h2360MCSignalPFDijetM3->GetMeanError() != 0) hMeans2360QCDModulesMC->SetBinError(3,h2360MCSignalPFDijetM3->GetMeanError());
   if (h2360MCSignalPFDijetM4->GetMeanError() != 0) hMeans2360QCDModulesMC->SetBinError(4,h2360MCSignalPFDijetM4->GetMeanError());
   if (h2360MCSignalPFDijetM5->GetMeanError() != 0) hMeans2360QCDModulesMC->SetBinError(5,h2360MCSignalPFDijetM5->GetMeanError());
   if (h2360MCSignalPFDijetM6->GetMeanError() != 0) hMeans2360QCDModulesMC->SetBinError(6,h2360MCSignalPFDijetM6->GetMeanError());
   if (h2360MCSignalPFDijetM7->GetMeanError() != 0) hMeans2360QCDModulesMC->SetBinError(7,h2360MCSignalPFDijetM7->GetMeanError());
   if (h2360MCSignalPFDijetM8->GetMeanError() != 0) hMeans2360QCDModulesMC->SetBinError(8,h2360MCSignalPFDijetM8->GetMeanError());
   if (h2360MCSignalPFDijetM9->GetMeanError() != 0) hMeans2360QCDModulesMC->SetBinError(9,h2360MCSignalPFDijetM9->GetMeanError());
   if (h2360MCSignalPFDijetM10->GetMeanError() != 0) hMeans2360QCDModulesMC->SetBinError(10,h2360MCSignalPFDijetM10->GetMeanError());
   if (h2360MCSignalPFDijetM11->GetMeanError() != 0) hMeans2360QCDModulesMC->SetBinError(11,h2360MCSignalPFDijetM11->GetMeanError());
   if (h2360MCSignalPFDijetM12->GetMeanError() != 0) hMeans2360QCDModulesMC->SetBinError(12,h2360MCSignalPFDijetM12->GetMeanError());
   if (h2360MCSignalPFDijetM13->GetMeanError() != 0) hMeans2360QCDModulesMC->SetBinError(13,h2360MCSignalPFDijetM13->GetMeanError());
   if (h2360MCSignalPFDijetM14->GetMeanError() != 0) hMeans2360QCDModulesMC->SetBinError(14,h2360MCSignalPFDijetM14->GetMeanError());
 
   TCanvas *cMeans2360Modules = new TCanvas("cMeans2360Modules","MB and QCD Means2360 in CASTOR modules for 2360 GeV");
   cMeans2360Modules->Divide(2,1);
   cMeans2360Modules->cd(1);
   hMeans2360Modules->GetYaxis()->SetTitle("Means2360 2360GeV data");
   hMeans2360Modules->SetMarkerColor(kBlue);
   hMeans2360Modules->Draw("");
   hMeans2360QCDModules->Draw("same");
   cMeans2360Modules->cd(2);
   hMeans2360ModulesMC->GetYaxis()->SetTitle("Means2360 2360GeV MC");
   hMeans2360ModulesMC->SetMarkerColor(kBlue);
   hMeans2360ModulesMC->Draw("");
   hMeans2360QCDModulesMC->Draw("same");
   
   if (h2360SignalS1->GetMean() != 0) hMeans2360Sectors->SetBinContent(1,h2360SignalS1->GetMean());
   if (h2360SignalS2->GetMean() != 0) hMeans2360Sectors->SetBinContent(2,h2360SignalS2->GetMean());
   if (h2360SignalS3->GetMean() != 0) hMeans2360Sectors->SetBinContent(3,h2360SignalS3->GetMean());
   if (h2360SignalS4->GetMean() != 0) hMeans2360Sectors->SetBinContent(4,h2360SignalS4->GetMean());
   if (h2360SignalS5->GetMean() != 0) hMeans2360Sectors->SetBinContent(5,h2360SignalS5->GetMean());
   if (h2360SignalS6->GetMean() != 0) hMeans2360Sectors->SetBinContent(6,h2360SignalS6->GetMean());
   if (h2360SignalS7->GetMean() != 0) hMeans2360Sectors->SetBinContent(7,h2360SignalS7->GetMean());
   if (h2360SignalS8->GetMean() != 0) hMeans2360Sectors->SetBinContent(8,h2360SignalS8->GetMean());
   if (h2360SignalS9->GetMean() != 0) hMeans2360Sectors->SetBinContent(9,h2360SignalS9->GetMean());
   if (h2360SignalS10->GetMean() != 0) hMeans2360Sectors->SetBinContent(10,h2360SignalS10->GetMean());
   if (h2360SignalS11->GetMean() != 0) hMeans2360Sectors->SetBinContent(11,h2360SignalS11->GetMean());
   if (h2360SignalS12->GetMean() != 0) hMeans2360Sectors->SetBinContent(12,h2360SignalS12->GetMean());
   if (h2360SignalS13->GetMean() != 0) hMeans2360Sectors->SetBinContent(13,h2360SignalS13->GetMean());
   if (h2360SignalS14->GetMean() != 0) hMeans2360Sectors->SetBinContent(14,h2360SignalS14->GetMean());
   if (h2360SignalS15->GetMean() != 0) hMeans2360Sectors->SetBinContent(15,h2360SignalS15->GetMean());
   if (h2360SignalS16->GetMean() != 0) hMeans2360Sectors->SetBinContent(16,h2360SignalS16->GetMean());
   
   if (h2360MCSignalS1->GetMean() != 0) hMeans2360SectorsMC->SetBinContent(1,h2360MCSignalS1->GetMean());
   if (h2360MCSignalS2->GetMean() != 0) hMeans2360SectorsMC->SetBinContent(2,h2360MCSignalS2->GetMean());
   if (h2360MCSignalS3->GetMean() != 0) hMeans2360SectorsMC->SetBinContent(3,h2360MCSignalS3->GetMean());
   if (h2360MCSignalS4->GetMean() != 0) hMeans2360SectorsMC->SetBinContent(4,h2360MCSignalS4->GetMean());
   if (h2360MCSignalS5->GetMean() != 0) hMeans2360SectorsMC->SetBinContent(5,h2360MCSignalS5->GetMean());
   if (h2360MCSignalS6->GetMean() != 0) hMeans2360SectorsMC->SetBinContent(6,h2360MCSignalS6->GetMean());
   if (h2360MCSignalS7->GetMean() != 0) hMeans2360SectorsMC->SetBinContent(7,h2360MCSignalS7->GetMean());
   if (h2360MCSignalS8->GetMean() != 0) hMeans2360SectorsMC->SetBinContent(8,h2360MCSignalS8->GetMean());
   if (h2360MCSignalS9->GetMean() != 0) hMeans2360SectorsMC->SetBinContent(9,h2360MCSignalS9->GetMean());
   if (h2360MCSignalS10->GetMean() != 0) hMeans2360SectorsMC->SetBinContent(10,h2360MCSignalS10->GetMean());
   if (h2360MCSignalS11->GetMean() != 0) hMeans2360SectorsMC->SetBinContent(11,h2360MCSignalS11->GetMean());
   if (h2360MCSignalS12->GetMean() != 0) hMeans2360SectorsMC->SetBinContent(12,h2360MCSignalS12->GetMean());
   if (h2360MCSignalS13->GetMean() != 0) hMeans2360SectorsMC->SetBinContent(13,h2360MCSignalS13->GetMean());
   if (h2360MCSignalS14->GetMean() != 0) hMeans2360SectorsMC->SetBinContent(14,h2360MCSignalS14->GetMean());
   if (h2360MCSignalS15->GetMean() != 0) hMeans2360SectorsMC->SetBinContent(15,h2360MCSignalS15->GetMean());
   if (h2360MCSignalS16->GetMean() != 0) hMeans2360SectorsMC->SetBinContent(16,h2360MCSignalS16->GetMean());
   
     if (h2360SignalS1->GetMeanError() != 0) hMeans2360Sectors->SetBinError(1,h2360SignalS1->GetMeanError());
   if (h2360SignalS2->GetMeanError() != 0) hMeans2360Sectors->SetBinError(2,h2360SignalS2->GetMeanError());
   if (h2360SignalS3->GetMeanError() != 0) hMeans2360Sectors->SetBinError(3,h2360SignalS3->GetMeanError());
   if (h2360SignalS4->GetMeanError() != 0) hMeans2360Sectors->SetBinError(4,h2360SignalS4->GetMeanError());
   if (h2360SignalS5->GetMeanError() != 0) hMeans2360Sectors->SetBinError(5,h2360SignalS5->GetMeanError());
   if (h2360SignalS6->GetMeanError() != 0) hMeans2360Sectors->SetBinError(6,h2360SignalS6->GetMeanError());
   if (h2360SignalS7->GetMeanError() != 0) hMeans2360Sectors->SetBinError(7,h2360SignalS7->GetMeanError());
   if (h2360SignalS8->GetMeanError() != 0) hMeans2360Sectors->SetBinError(8,h2360SignalS8->GetMeanError());
   if (h2360SignalS9->GetMeanError() != 0) hMeans2360Sectors->SetBinError(9,h2360SignalS9->GetMeanError());
   if (h2360SignalS10->GetMeanError() != 0) hMeans2360Sectors->SetBinError(10,h2360SignalS10->GetMeanError());
   if (h2360SignalS11->GetMeanError() != 0) hMeans2360Sectors->SetBinError(11,h2360SignalS11->GetMeanError());
   if (h2360SignalS12->GetMeanError() != 0) hMeans2360Sectors->SetBinError(12,h2360SignalS12->GetMeanError());
   if (h2360SignalS13->GetMeanError() != 0) hMeans2360Sectors->SetBinError(13,h2360SignalS13->GetMeanError());
   if (h2360SignalS14->GetMeanError() != 0) hMeans2360Sectors->SetBinError(14,h2360SignalS14->GetMeanError());
   if (h2360SignalS15->GetMeanError() != 0) hMeans2360Sectors->SetBinError(15,h2360SignalS15->GetMeanError());
   if (h2360SignalS16->GetMeanError() != 0) hMeans2360Sectors->SetBinError(16,h2360SignalS16->GetMeanError());
   
   if (h2360MCSignalS1->GetMeanError() != 0) hMeans2360SectorsMC->SetBinError(1,h2360MCSignalS1->GetMeanError());
   if (h2360MCSignalS2->GetMeanError() != 0) hMeans2360SectorsMC->SetBinError(2,h2360MCSignalS2->GetMeanError());
   if (h2360MCSignalS3->GetMeanError() != 0) hMeans2360SectorsMC->SetBinError(3,h2360MCSignalS3->GetMeanError());
   if (h2360MCSignalS4->GetMeanError() != 0) hMeans2360SectorsMC->SetBinError(4,h2360MCSignalS4->GetMeanError());
   if (h2360MCSignalS5->GetMeanError() != 0) hMeans2360SectorsMC->SetBinError(5,h2360MCSignalS5->GetMeanError());
   if (h2360MCSignalS6->GetMeanError() != 0) hMeans2360SectorsMC->SetBinError(6,h2360MCSignalS6->GetMeanError());
   if (h2360MCSignalS7->GetMeanError() != 0) hMeans2360SectorsMC->SetBinError(7,h2360MCSignalS7->GetMeanError());
   if (h2360MCSignalS8->GetMeanError() != 0) hMeans2360SectorsMC->SetBinError(8,h2360MCSignalS8->GetMeanError());
   if (h2360MCSignalS9->GetMeanError() != 0) hMeans2360SectorsMC->SetBinError(9,h2360MCSignalS9->GetMeanError());
   if (h2360MCSignalS10->GetMeanError() != 0) hMeans2360SectorsMC->SetBinError(10,h2360MCSignalS10->GetMeanError());
   if (h2360MCSignalS11->GetMeanError() != 0) hMeans2360SectorsMC->SetBinError(11,h2360MCSignalS11->GetMeanError());
   if (h2360MCSignalS12->GetMeanError() != 0) hMeans2360SectorsMC->SetBinError(12,h2360MCSignalS12->GetMeanError());
   if (h2360MCSignalS13->GetMeanError() != 0) hMeans2360SectorsMC->SetBinError(13,h2360MCSignalS13->GetMeanError());
   if (h2360MCSignalS14->GetMeanError() != 0) hMeans2360SectorsMC->SetBinError(14,h2360MCSignalS14->GetMeanError());
   if (h2360MCSignalS15->GetMeanError() != 0) hMeans2360SectorsMC->SetBinError(15,h2360MCSignalS15->GetMeanError());
   if (h2360MCSignalS16->GetMeanError() != 0) hMeans2360SectorsMC->SetBinError(16,h2360MCSignalS16->GetMeanError());
   
     
    if (h2360SignalPFDijetS1->GetMean() != 0) hMeans2360QCDSectors->SetBinContent(1,h2360SignalPFDijetS1->GetMean());
   if (h2360SignalPFDijetS2->GetMean() != 0) hMeans2360QCDSectors->SetBinContent(2,h2360SignalPFDijetS2->GetMean());
   if (h2360SignalPFDijetS3->GetMean() != 0) hMeans2360QCDSectors->SetBinContent(3,h2360SignalPFDijetS3->GetMean());
   if (h2360SignalPFDijetS4->GetMean() != 0) hMeans2360QCDSectors->SetBinContent(4,h2360SignalPFDijetS4->GetMean());
   if (h2360SignalPFDijetS5->GetMean() != 0) hMeans2360QCDSectors->SetBinContent(5,h2360SignalPFDijetS5->GetMean());
   if (h2360SignalPFDijetS6->GetMean() != 0) hMeans2360QCDSectors->SetBinContent(6,h2360SignalPFDijetS6->GetMean());
   if (h2360SignalPFDijetS7->GetMean() != 0) hMeans2360QCDSectors->SetBinContent(7,h2360SignalPFDijetS7->GetMean());
   if (h2360SignalPFDijetS8->GetMean() != 0) hMeans2360QCDSectors->SetBinContent(8,h2360SignalPFDijetS8->GetMean());
   if (h2360SignalPFDijetS9->GetMean() != 0) hMeans2360QCDSectors->SetBinContent(9,h2360SignalPFDijetS9->GetMean());
   if (h2360SignalPFDijetS10->GetMean() != 0) hMeans2360QCDSectors->SetBinContent(10,h2360SignalPFDijetS10->GetMean());
   if (h2360SignalPFDijetS11->GetMean() != 0) hMeans2360QCDSectors->SetBinContent(11,h2360SignalPFDijetS11->GetMean());
   if (h2360SignalPFDijetS12->GetMean() != 0) hMeans2360QCDSectors->SetBinContent(12,h2360SignalPFDijetS12->GetMean());
   if (h2360SignalPFDijetS13->GetMean() != 0) hMeans2360QCDSectors->SetBinContent(13,h2360SignalPFDijetS13->GetMean());
   if (h2360SignalPFDijetS14->GetMean() != 0) hMeans2360QCDSectors->SetBinContent(14,h2360SignalPFDijetS14->GetMean());
   if (h2360SignalPFDijetS15->GetMean() != 0) hMeans2360QCDSectors->SetBinContent(15,h2360SignalPFDijetS15->GetMean());
   if (h2360SignalPFDijetS16->GetMean() != 0) hMeans2360QCDSectors->SetBinContent(16,h2360SignalPFDijetS16->GetMean());
   
   if (h2360MCSignalPFDijetS1->GetMean() != 0) hMeans2360QCDSectorsMC->SetBinContent(1,h2360MCSignalPFDijetS1->GetMean());
   if (h2360MCSignalPFDijetS2->GetMean() != 0) hMeans2360QCDSectorsMC->SetBinContent(2,h2360MCSignalPFDijetS2->GetMean());
   if (h2360MCSignalPFDijetS3->GetMean() != 0) hMeans2360QCDSectorsMC->SetBinContent(3,h2360MCSignalPFDijetS3->GetMean());
   if (h2360MCSignalPFDijetS4->GetMean() != 0) hMeans2360QCDSectorsMC->SetBinContent(4,h2360MCSignalPFDijetS4->GetMean());
   if (h2360MCSignalPFDijetS5->GetMean() != 0) hMeans2360QCDSectorsMC->SetBinContent(5,h2360MCSignalPFDijetS5->GetMean());
   if (h2360MCSignalPFDijetS6->GetMean() != 0) hMeans2360QCDSectorsMC->SetBinContent(6,h2360MCSignalPFDijetS6->GetMean());
   if (h2360MCSignalPFDijetS7->GetMean() != 0) hMeans2360QCDSectorsMC->SetBinContent(7,h2360MCSignalPFDijetS7->GetMean());
   if (h2360MCSignalPFDijetS8->GetMean() != 0) hMeans2360QCDSectorsMC->SetBinContent(8,h2360MCSignalPFDijetS8->GetMean());
   if (h2360MCSignalPFDijetS9->GetMean() != 0) hMeans2360QCDSectorsMC->SetBinContent(9,h2360MCSignalPFDijetS9->GetMean());
   if (h2360MCSignalPFDijetS10->GetMean() != 0) hMeans2360QCDSectorsMC->SetBinContent(10,h2360MCSignalPFDijetS10->GetMean());
   if (h2360MCSignalPFDijetS11->GetMean() != 0) hMeans2360QCDSectorsMC->SetBinContent(11,h2360MCSignalPFDijetS11->GetMean());
   if (h2360MCSignalPFDijetS12->GetMean() != 0) hMeans2360QCDSectorsMC->SetBinContent(12,h2360MCSignalPFDijetS12->GetMean());
   if (h2360MCSignalPFDijetS13->GetMean() != 0) hMeans2360QCDSectorsMC->SetBinContent(13,h2360MCSignalPFDijetS13->GetMean());
   if (h2360MCSignalPFDijetS14->GetMean() != 0) hMeans2360QCDSectorsMC->SetBinContent(14,h2360MCSignalPFDijetS14->GetMean());
   if (h2360MCSignalPFDijetS15->GetMean() != 0) hMeans2360QCDSectorsMC->SetBinContent(15,h2360MCSignalPFDijetS15->GetMean());
   if (h2360MCSignalPFDijetS16->GetMean() != 0) hMeans2360QCDSectorsMC->SetBinContent(16,h2360MCSignalPFDijetS16->GetMean());
   
     if (h2360SignalPFDijetS1->GetMeanError() != 0) hMeans2360QCDSectors->SetBinError(1,h2360SignalPFDijetS1->GetMeanError());
   if (h2360SignalPFDijetS2->GetMeanError() != 0) hMeans2360QCDSectors->SetBinError(2,h2360SignalPFDijetS2->GetMeanError());
   if (h2360SignalPFDijetS3->GetMeanError() != 0) hMeans2360QCDSectors->SetBinError(3,h2360SignalPFDijetS3->GetMeanError());
   if (h2360SignalPFDijetS4->GetMeanError() != 0) hMeans2360QCDSectors->SetBinError(4,h2360SignalPFDijetS4->GetMeanError());
   if (h2360SignalPFDijetS5->GetMeanError() != 0) hMeans2360QCDSectors->SetBinError(5,h2360SignalPFDijetS5->GetMeanError());
   if (h2360SignalPFDijetS6->GetMeanError() != 0) hMeans2360QCDSectors->SetBinError(6,h2360SignalPFDijetS6->GetMeanError());
   if (h2360SignalPFDijetS7->GetMeanError() != 0) hMeans2360QCDSectors->SetBinError(7,h2360SignalPFDijetS7->GetMeanError());
   if (h2360SignalPFDijetS8->GetMeanError() != 0) hMeans2360QCDSectors->SetBinError(8,h2360SignalPFDijetS8->GetMeanError());
   if (h2360SignalPFDijetS9->GetMeanError() != 0) hMeans2360QCDSectors->SetBinError(9,h2360SignalPFDijetS9->GetMeanError());
   if (h2360SignalPFDijetS10->GetMeanError() != 0) hMeans2360QCDSectors->SetBinError(10,h2360SignalPFDijetS10->GetMeanError());
   if (h2360SignalPFDijetS11->GetMeanError() != 0) hMeans2360QCDSectors->SetBinError(11,h2360SignalPFDijetS11->GetMeanError());
   if (h2360SignalPFDijetS12->GetMeanError() != 0) hMeans2360QCDSectors->SetBinError(12,h2360SignalPFDijetS12->GetMeanError());
   if (h2360SignalPFDijetS13->GetMeanError() != 0) hMeans2360QCDSectors->SetBinError(13,h2360SignalPFDijetS13->GetMeanError());
   if (h2360SignalPFDijetS14->GetMeanError() != 0) hMeans2360QCDSectors->SetBinError(14,h2360SignalPFDijetS14->GetMeanError());
   if (h2360SignalPFDijetS15->GetMeanError() != 0) hMeans2360QCDSectors->SetBinError(15,h2360SignalPFDijetS15->GetMeanError());
   if (h2360SignalPFDijetS16->GetMeanError() != 0) hMeans2360QCDSectors->SetBinError(16,h2360SignalPFDijetS16->GetMeanError());
   
   if (h2360MCSignalPFDijetS1->GetMeanError() != 0) hMeans2360QCDSectorsMC->SetBinError(1,h2360MCSignalPFDijetS1->GetMeanError());
   if (h2360MCSignalPFDijetS2->GetMeanError() != 0) hMeans2360QCDSectorsMC->SetBinError(2,h2360MCSignalPFDijetS2->GetMeanError());
   if (h2360MCSignalPFDijetS3->GetMeanError() != 0) hMeans2360QCDSectorsMC->SetBinError(3,h2360MCSignalPFDijetS3->GetMeanError());
   if (h2360MCSignalPFDijetS4->GetMeanError() != 0) hMeans2360QCDSectorsMC->SetBinError(4,h2360MCSignalPFDijetS4->GetMeanError());
   if (h2360MCSignalPFDijetS5->GetMeanError() != 0) hMeans2360QCDSectorsMC->SetBinError(5,h2360MCSignalPFDijetS5->GetMeanError());
   if (h2360MCSignalPFDijetS6->GetMeanError() != 0) hMeans2360QCDSectorsMC->SetBinError(6,h2360MCSignalPFDijetS6->GetMeanError());
   if (h2360MCSignalPFDijetS7->GetMeanError() != 0) hMeans2360QCDSectorsMC->SetBinError(7,h2360MCSignalPFDijetS7->GetMeanError());
   if (h2360MCSignalPFDijetS8->GetMeanError() != 0) hMeans2360QCDSectorsMC->SetBinError(8,h2360MCSignalPFDijetS8->GetMeanError());
   if (h2360MCSignalPFDijetS9->GetMeanError() != 0) hMeans2360QCDSectorsMC->SetBinError(9,h2360MCSignalPFDijetS9->GetMeanError());
   if (h2360MCSignalPFDijetS10->GetMeanError() != 0) hMeans2360QCDSectorsMC->SetBinError(10,h2360MCSignalPFDijetS10->GetMeanError());
   if (h2360MCSignalPFDijetS11->GetMeanError() != 0) hMeans2360QCDSectorsMC->SetBinError(11,h2360MCSignalPFDijetS11->GetMeanError());
   if (h2360MCSignalPFDijetS12->GetMeanError() != 0) hMeans2360QCDSectorsMC->SetBinError(12,h2360MCSignalPFDijetS12->GetMeanError());
   if (h2360MCSignalPFDijetS13->GetMeanError() != 0) hMeans2360QCDSectorsMC->SetBinError(13,h2360MCSignalPFDijetS13->GetMeanError());
   if (h2360MCSignalPFDijetS14->GetMeanError() != 0) hMeans2360QCDSectorsMC->SetBinError(14,h2360MCSignalPFDijetS14->GetMeanError());
   if (h2360MCSignalPFDijetS15->GetMeanError() != 0) hMeans2360QCDSectorsMC->SetBinError(15,h2360MCSignalPFDijetS15->GetMeanError());
   if (h2360MCSignalPFDijetS16->GetMeanError() != 0) hMeans2360QCDSectorsMC->SetBinError(16,h2360MCSignalPFDijetS16->GetMeanError());
   
   TCanvas *cMeans2360Sectors = new TCanvas("cMeans2360Sectors","MB and QCD Means2360 in CASTOR Sectors for 2360 GeV");
   cMeans2360Sectors->Divide(2,1);
   cMeans2360Sectors->cd(1);
   hMeans2360Sectors->SetMarkerColor(kBlue);
   hMeans2360Sectors->GetYaxis()->SetTitle("Means2360 2360GeV data");
   hMeans2360Sectors->Draw("");
   hMeans2360QCDSectors->Draw("same");
   cMeans2360Sectors->cd(2);
   hMeans2360SectorsMC->GetYaxis()->SetTitle("Means2360 2360GeV MC");
   hMeans2360SectorsMC->SetMarkerColor(kBlue);
   hMeans2360SectorsMC->Draw("");
   hMeans2360QCDSectorsMC->Draw("same");
   
   ////////////////////////
   // Ratio per channel
   ////////////////////////
   
   
   TH1D *h900Module1 = new TH1D("h900Module1","Ratios in module 1",16,1,17);
   TH1D *h900Module2 = new TH1D("h900Module2","Ratios in module 2",16,1,17);
   TH1D *h900Module3 = new TH1D("h900Module3","Ratios in module 3",16,1,17);
   TH1D *h900Module4 = new TH1D("h900Module4","Ratios in module 4",16,1,17);
   TH1D *h900Module5 = new TH1D("h900Module5","Ratios in module 5",16,1,17);
   TH1D *h900Module6 = new TH1D("h900Module6","Ratios in module 6",16,1,17);
   
   for (int i=0;i<16;i++) {
   	h900Module1->SetBinContent(i+1,h900EChannelQCD[i]->GetMean()/h900EChannel[i]->GetMean());
	h900Module1->SetBinError(i+1,getRatioError(h900EChannel[i],h900EChannelQCD[i]));
   }
   for (int i=16;i<32;i++) {
   	h900Module2->SetBinContent(i+1-16,h900EChannelQCD[i]->GetMean()/h900EChannel[i]->GetMean());
	h900Module2->SetBinError(i+1-16,getRatioError(h900EChannel[i],h900EChannelQCD[i]));
   }
   for (int i=32;i<48;i++) {
   	h900Module3->SetBinContent(i+1-32,h900EChannelQCD[i]->GetMean()/h900EChannel[i]->GetMean());
	h900Module3->SetBinError(i+1-32,getRatioError(h900EChannel[i],h900EChannelQCD[i]));
   }
   for (int i=48;i<64;i++) {
   	h900Module4->SetBinContent(i+1-48,h900EChannelQCD[i]->GetMean()/h900EChannel[i]->GetMean());
	h900Module4->SetBinError(i+1-48,getRatioError(h900EChannel[i],h900EChannelQCD[i]));
   }
   for (int i=64;i<80;i++) {
   	h900Module5->SetBinContent(i+1-64,h900EChannelQCD[i]->GetMean()/h900EChannel[i]->GetMean());
	h900Module5->SetBinError(i+1-64,getRatioError(h900EChannel[i],h900EChannelQCD[i]));
   }
   for (int i=80;i<96;i++) {
   	h900Module6->SetBinContent(i+1-80,h900EChannelQCD[i]->GetMean()/h900EChannel[i]->GetMean());
	h900Module6->SetBinError(i+1-80,getRatioError(h900EChannel[i],h900EChannelQCD[i]));
   }
   
   TH1D *h900ModuleMC1 = new TH1D("h900ModuleMC1","Ratios in module 1;Sector;Ratio",16,1,17);
   TH1D *h900ModuleMC2 = new TH1D("h900ModuleMC2","Ratios in module 2;Sector;Ratio",16,1,17);
   TH1D *h900ModuleMC3 = new TH1D("h900ModuleMC3","Ratios in module 3;Sector;Ratio",16,1,17);
   TH1D *h900ModuleMC4 = new TH1D("h900ModuleMC4","Ratios in module 4;Sector;Ratio",16,1,17);
   TH1D *h900ModuleMC5 = new TH1D("h900ModuleMC5","Ratios in module 5;Sector;Ratio",16,1,17);
   TH1D *h900ModuleMC6 = new TH1D("h900ModuleMC6","Ratios in module 6;Sector;Ratio",16,1,17);
   
   for (int i=0;i<16;i++) {
   	h900ModuleMC1->SetBinContent(i+1,h900EChannelQCDMC[i]->GetMean()/h900EChannelMC[i]->GetMean());
	h900ModuleMC1->SetBinError(i+1,getRatioError(h900EChannelMC[i],h900EChannelQCDMC[i]));
   }
   for (int i=16;i<32;i++) {
   	h900ModuleMC2->SetBinContent(i+1-16,h900EChannelQCDMC[i]->GetMean()/h900EChannelMC[i]->GetMean());
	h900ModuleMC2->SetBinError(i+1-16,getRatioError(h900EChannelMC[i],h900EChannelQCDMC[i]));
   }
   for (int i=32;i<48;i++) {
   	h900ModuleMC3->SetBinContent(i+1-32,h900EChannelQCDMC[i]->GetMean()/h900EChannelMC[i]->GetMean());
	h900ModuleMC3->SetBinError(i+1-32,getRatioError(h900EChannelMC[i],h900EChannelQCDMC[i]));
   }
   for (int i=48;i<64;i++) {
   	h900ModuleMC4->SetBinContent(i+1-48,h900EChannelQCDMC[i]->GetMean()/h900EChannelMC[i]->GetMean());
	h900ModuleMC4->SetBinError(i+1-48,getRatioError(h900EChannelMC[i],h900EChannelQCDMC[i]));
   }
   for (int i=64;i<80;i++) {
   	h900ModuleMC5->SetBinContent(i+1-64,h900EChannelQCDMC[i]->GetMean()/h900EChannelMC[i]->GetMean());
	h900ModuleMC5->SetBinError(i+1-64,getRatioError(h900EChannelMC[i],h900EChannelQCDMC[i]));
   }
   for (int i=80;i<96;i++) {
   	h900ModuleMC6->SetBinContent(i+1-80,h900EChannelQCDMC[i]->GetMean()/h900EChannelMC[i]->GetMean());
	h900ModuleMC6->SetBinError(i+1-80,getRatioError(h900EChannelMC[i],h900EChannelQCDMC[i]));
   }
   
   TCanvas *cChannelRatio = new TCanvas("cChannelRatio","Ratio per channel");
   cChannelRatio->Divide(3,2);
   cChannelRatio->cd(1);
   h900ModuleMC1->GetYaxis()->SetRangeUser(0,4);
   h900ModuleMC1->SetMarkerColor(kGreen);
   h900Module1->Draw("");
   h900ModuleMC1->Draw("same");
   cChannelRatio->cd(2);
   h900ModuleMC2->GetYaxis()->SetRangeUser(0,4);
   h900ModuleMC2->SetMarkerColor(kGreen);
   h900Module2->Draw("");
   h900ModuleMC2->Draw("same");
   cChannelRatio->cd(3);
   h900ModuleMC3->GetYaxis()->SetRangeUser(0,4);
   h900ModuleMC3->SetMarkerColor(kGreen);
   h900Module3->Draw("");
   h900ModuleMC3->Draw("same");
   cChannelRatio->cd(4);
   h900ModuleMC4->GetYaxis()->SetRangeUser(0,4);
   h900ModuleMC4->SetMarkerColor(kGreen);
   h900Module4->Draw("");
   h900ModuleMC4->Draw("same");
   cChannelRatio->cd(5);
   h900ModuleMC5->GetYaxis()->SetRangeUser(0,4);
   h900ModuleMC5->SetMarkerColor(kGreen);
   h900Module5->Draw("");
   h900ModuleMC5->Draw("same");
   cChannelRatio->cd(6);
   h900ModuleMC6->GetYaxis()->SetRangeUser(0,4);
   h900ModuleMC6->SetMarkerColor(kGreen);
   h900Module6->Draw("");
   h900ModuleMC6->Draw("same");
   
    TH1D *h2360Module1 = new TH1D("h2360Module1","Ratios in module 1;Sector;Ratio",16,1,17);
   TH1D *h2360Module2 = new TH1D("h2360Module2","Ratios in module 2;Sector;Ratio",16,1,17);
   TH1D *h2360Module3 = new TH1D("h2360Module3","Ratios in module 3;Sector;Ratio",16,1,17);
   TH1D *h2360Module4 = new TH1D("h2360Module4","Ratios in module 4;Sector;Ratio",16,1,17);
   TH1D *h2360Module5 = new TH1D("h2360Module5","Ratios in module 5;Sector;Ratio",16,1,17);
   TH1D *h2360Module6 = new TH1D("h2360Module6","Ratios in module 6;Sector;Ratio",16,1,17);
   
   for (int i=0;i<16;i++) {
   	h2360Module1->SetBinContent(i+1,h2360EChannelQCD[i]->GetMean()/h2360EChannel[i]->GetMean());
	h2360Module1->SetBinError(i+1,getRatioError(h2360EChannel[i],h2360EChannelQCD[i]));
   }
   for (int i=16;i<32;i++) {
   	h2360Module2->SetBinContent(i+1-16,h2360EChannelQCD[i]->GetMean()/h2360EChannel[i]->GetMean());
	h2360Module2->SetBinError(i+1-16,getRatioError(h2360EChannel[i],h2360EChannelQCD[i]));
   }
   for (int i=32;i<48;i++) {
   	h2360Module3->SetBinContent(i+1-32,h2360EChannelQCD[i]->GetMean()/h2360EChannel[i]->GetMean());
	h2360Module3->SetBinError(i+1-32,getRatioError(h2360EChannel[i],h2360EChannelQCD[i]));
   }
   for (int i=48;i<64;i++) {
   	h2360Module4->SetBinContent(i+1-48,h2360EChannelQCD[i]->GetMean()/h2360EChannel[i]->GetMean());
	h2360Module4->SetBinError(i+1-48,getRatioError(h2360EChannel[i],h2360EChannelQCD[i]));
   }
   for (int i=64;i<80;i++) {
   	h2360Module5->SetBinContent(i+1-64,h2360EChannelQCD[i]->GetMean()/h2360EChannel[i]->GetMean());
	h2360Module5->SetBinError(i+1-64,getRatioError(h2360EChannel[i],h2360EChannelQCD[i]));
   }
   for (int i=80;i<96;i++) {
   	h2360Module6->SetBinContent(i+1-80,h2360EChannelQCD[i]->GetMean()/h2360EChannel[i]->GetMean());
	h2360Module6->SetBinError(i+1-80,getRatioError(h2360EChannel[i],h2360EChannelQCD[i]));
   }
   
   TH1D *h2360ModuleMC1 = new TH1D("h2360ModuleMC1","Ratios in module 1;Sector;Ratio",16,1,17);
   TH1D *h2360ModuleMC2 = new TH1D("h2360ModuleMC2","Ratios in module 2;Sector;Ratio",16,1,17);
   TH1D *h2360ModuleMC3 = new TH1D("h2360ModuleMC3","Ratios in module 3;Sector;Ratio",16,1,17);
   TH1D *h2360ModuleMC4 = new TH1D("h2360ModuleMC4","Ratios in module 4;Sector;Ratio",16,1,17);
   TH1D *h2360ModuleMC5 = new TH1D("h2360ModuleMC5","Ratios in module 5;Sector;Ratio",16,1,17);
   TH1D *h2360ModuleMC6 = new TH1D("h2360ModuleMC6","Ratios in module 6;Sector;Ratio",16,1,17);
   
   for (int i=0;i<16;i++) {
   	h2360ModuleMC1->SetBinContent(i+1,h2360EChannelQCDMC[i]->GetMean()/h2360EChannelMC[i]->GetMean());
	h2360ModuleMC1->SetBinError(i+1,getRatioError(h2360EChannelMC[i],h2360EChannelQCDMC[i]));
   }
   for (int i=16;i<32;i++) {
   	h2360ModuleMC2->SetBinContent(i+1-16,h2360EChannelQCDMC[i]->GetMean()/h2360EChannelMC[i]->GetMean());
	h2360ModuleMC2->SetBinError(i+1-16,getRatioError(h2360EChannelMC[i],h2360EChannelQCDMC[i]));
   }
   for (int i=32;i<48;i++) {
   	h2360ModuleMC3->SetBinContent(i+1-32,h2360EChannelQCDMC[i]->GetMean()/h2360EChannelMC[i]->GetMean());
	h2360ModuleMC3->SetBinError(i+1-32,getRatioError(h2360EChannelMC[i],h2360EChannelQCDMC[i]));
   }
   for (int i=48;i<64;i++) {
   	h2360ModuleMC4->SetBinContent(i+1-48,h2360EChannelQCDMC[i]->GetMean()/h2360EChannelMC[i]->GetMean());
	h2360ModuleMC4->SetBinError(i+1-48,getRatioError(h2360EChannelMC[i],h2360EChannelQCDMC[i]));
   }
   for (int i=64;i<80;i++) {
   	h2360ModuleMC5->SetBinContent(i+1-64,h2360EChannelQCDMC[i]->GetMean()/h2360EChannelMC[i]->GetMean());
	h2360ModuleMC5->SetBinError(i+1-64,getRatioError(h2360EChannelMC[i],h2360EChannelQCDMC[i]));
   }
   for (int i=80;i<96;i++) {
   	h2360ModuleMC6->SetBinContent(i+1-80,h2360EChannelQCDMC[i]->GetMean()/h2360EChannelMC[i]->GetMean());
	h2360ModuleMC6->SetBinError(i+1-80,getRatioError(h2360EChannelMC[i],h2360EChannelQCDMC[i]));
   }
   
   TCanvas *cChannelRatio2360 = new TCanvas("cChannelRatio2360","Ratio per channel");
   cChannelRatio2360->Divide(3,2);
   cChannelRatio2360->cd(1);
   h2360ModuleMC1->GetYaxis()->SetRangeUser(0,4);
   h2360ModuleMC1->SetMarkerColor(kGreen);
   h2360Module1->Draw("");
   h2360ModuleMC1->Draw("same");
   cChannelRatio2360->cd(2);
   h2360ModuleMC2->GetYaxis()->SetRangeUser(0,4);
   h2360ModuleMC2->SetMarkerColor(kGreen);
   h2360Module2->Draw("");
   h2360ModuleMC2->Draw("same");
   cChannelRatio2360->cd(3);
   h2360ModuleMC3->GetYaxis()->SetRangeUser(0,4);
   h2360ModuleMC3->SetMarkerColor(kGreen);
   h2360Module3->Draw("");
   h2360ModuleMC3->Draw("same");
   cChannelRatio2360->cd(4);
   h2360ModuleMC4->GetYaxis()->SetRangeUser(0,4);
   h2360ModuleMC4->SetMarkerColor(kGreen);
   h2360Module4->Draw("");
   h2360ModuleMC4->Draw("same");
   cChannelRatio2360->cd(5);
   h2360ModuleMC5->GetYaxis()->SetRangeUser(0,4);
   h2360ModuleMC5->SetMarkerColor(kGreen);
   h2360Module5->Draw("");
   h2360ModuleMC5->Draw("same");
   cChannelRatio2360->cd(6);
   h2360ModuleMC6->GetYaxis()->SetRangeUser(0,4);
   h2360ModuleMC6->SetMarkerColor(kGreen);
   h2360Module6->Draw("");
   h2360ModuleMC6->Draw("same");
   
   
   ///////////////////////
   // Plot Jet stuff
   ///////////////////////
   /*
   TCanvas *cJets = new TCanvas("cJets","Central Jet distributions");
   cJets->Divide(3,2);
   cJets->cd(1);
   hPFDijetPt->Draw();
   cJets->cd(2);
   hPFDijetEta->Draw();
   cJets->cd(3);
   hPFDijetPhi->Draw();
   cJets->cd(4);
   hPFInclusivePt->Draw();
   cJets->cd(5);
   hPFInclusiveEta->Draw();
   cJets->cd(6);
   hPFInclusivePhi->Draw();
   */
   
   
   //////////////////////
   // Calculate ratios
   //////////////////////

  std::cout << "" << std::endl;
  std::cout << "Caluclate ratios from histograms:" << std::endl;
   
   double Mean900MB = h900SignalTot->GetMean();
   double Mean900MB_error = h900SignalTot->GetMeanError();
   std::cout << "900 GeV Data mean = " << Mean900MB << "+-" << Mean900MB_error << std::endl;
   
   double Mean900PFDijet = h900SignalTotPFDijet->GetMean();
   double Mean900PFInclusive = h900SignalTotPFInclusive->GetMean();
   
   double Mean900CaloDijet = h900SignalTotCaloDijet->GetMean();
   double Mean900CaloInclusive = h900SignalTotCaloInclusive->GetMean();
   
   double Mean900PFDijet_error = h900SignalTotPFDijet->GetMeanError();
   double Mean900PFInclusive_error = h900SignalTotPFInclusive->GetMeanError();
   
   double Mean900CaloDijet_error = h900SignalTotCaloDijet->GetMeanError();
   double Mean900CaloInclusive_error = h900SignalTotCaloInclusive->GetMeanError();
   
   double Ratio900PFDijet = Mean900PFDijet/Mean900MB;
   double Ratio900PFInclusive = Mean900PFInclusive/Mean900MB;
   
   double Ratio900CaloDijet = Mean900CaloDijet/Mean900MB;
   double Ratio900CaloInclusive = Mean900CaloInclusive/Mean900MB;
   
   double Ratio900PFDijet_error = Ratio900PFDijet*Ratio900PFDijet*((Mean900PFDijet_error*Mean900PFDijet_error)/(Mean900PFDijet*Mean900PFDijet) +
   (Mean900MB_error*Mean900MB_error)/(Mean900MB*Mean900MB));
   Ratio900PFDijet_error = sqrt(Ratio900PFDijet_error);
   
   double Ratio900PFInclusive_error = Ratio900PFInclusive*Ratio900PFInclusive*((Mean900PFInclusive_error*Mean900PFInclusive_error)/(Mean900PFInclusive*Mean900PFInclusive) +
   (Mean900MB_error*Mean900MB_error)/(Mean900MB*Mean900MB));
   Ratio900PFInclusive_error = sqrt(Ratio900PFInclusive_error);
   
   double Ratio900CaloDijet_error = Ratio900CaloDijet*Ratio900CaloDijet*((Mean900CaloDijet_error*Mean900CaloDijet_error)/(Mean900CaloDijet*Mean900CaloDijet) +
   (Mean900MB_error*Mean900MB_error)/(Mean900MB*Mean900MB));
   Ratio900CaloDijet_error = sqrt(Ratio900CaloDijet_error);
   
   double Ratio900CaloInclusive_error = Ratio900CaloInclusive*Ratio900CaloInclusive*((Mean900CaloInclusive_error*Mean900CaloInclusive_error)/(Mean900CaloInclusive*Mean900CaloInclusive) +
   (Mean900MB_error*Mean900MB_error)/(Mean900MB*Mean900MB));
   Ratio900CaloInclusive_error = sqrt(Ratio900CaloInclusive_error);

   std::cout << "Ratio900 PF Dijet/MB = " << Ratio900PFDijet << " +- " << Ratio900PFDijet_error << std::endl;
   std::cout << "Ratio900 PF Inclusive/MB = " << Ratio900PFInclusive << " +- " << Ratio900PFInclusive_error << std::endl;
   std::cout << "Ratio900 Calo Dijet/MB = " << Ratio900CaloDijet << " +- " << Ratio900CaloDijet_error << std::endl;
   std::cout << "Ratio900 Calo Inclusive/MB = " << Ratio900CaloInclusive << " +- " << Ratio900CaloInclusive_error << std::endl;
   std::cout << "" << std::endl;
   
   double Mean2360MB = h2360SignalTot->GetMean();
   double Mean2360MB_error = h2360SignalTot->GetMeanError();
   std::cout << "2360 GeV Data mean = " << Mean2360MB << "+-" << Mean2360MB_error << std::endl;
   
   double Mean2360PFDijet = h2360SignalTotPFDijet->GetMean();
   double Mean2360PFInclusive = h2360SignalTotPFInclusive->GetMean();
   
   double Mean2360CaloDijet = h2360SignalTotCaloDijet->GetMean();
   double Mean2360CaloInclusive = h2360SignalTotCaloInclusive->GetMean();
   
   double Mean2360PFDijet_error = h2360SignalTotPFDijet->GetMeanError();
   double Mean2360PFInclusive_error = h2360SignalTotPFInclusive->GetMeanError();
   
   double Mean2360CaloDijet_error = h2360SignalTotCaloDijet->GetMeanError();
   double Mean2360CaloInclusive_error = h2360SignalTotCaloInclusive->GetMeanError();
   
   double Ratio2360PFDijet = Mean2360PFDijet/Mean2360MB;
   double Ratio2360PFInclusive = Mean2360PFInclusive/Mean2360MB;
   
   double Ratio2360CaloDijet = Mean2360CaloDijet/Mean2360MB;
   double Ratio2360CaloInclusive = Mean2360CaloInclusive/Mean2360MB;
   
   double Ratio2360PFDijet_error = Ratio2360PFDijet*Ratio2360PFDijet*((Mean2360PFDijet_error*Mean2360PFDijet_error)/(Mean2360PFDijet*Mean2360PFDijet) +
   (Mean2360MB_error*Mean2360MB_error)/(Mean2360MB*Mean2360MB));
   Ratio2360PFDijet_error = sqrt(Ratio2360PFDijet_error);
   
   double Ratio2360PFInclusive_error = Ratio2360PFInclusive*Ratio2360PFInclusive*((Mean2360PFInclusive_error*Mean2360PFInclusive_error)/(Mean2360PFInclusive*Mean2360PFInclusive) +
   (Mean2360MB_error*Mean2360MB_error)/(Mean2360MB*Mean2360MB));
   Ratio2360PFInclusive_error = sqrt(Ratio2360PFInclusive_error);
   
   double Ratio2360CaloDijet_error = Ratio2360CaloDijet*Ratio2360CaloDijet*((Mean2360CaloDijet_error*Mean2360CaloDijet_error)/(Mean2360CaloDijet*Mean2360CaloDijet) +
   (Mean2360MB_error*Mean2360MB_error)/(Mean2360MB*Mean2360MB));
   Ratio2360CaloDijet_error = sqrt(Ratio2360CaloDijet_error);
   
   double Ratio2360CaloInclusive_error = Ratio2360CaloInclusive*Ratio2360CaloInclusive*((Mean2360CaloInclusive_error*Mean2360CaloInclusive_error)/(Mean2360CaloInclusive*Mean2360CaloInclusive) +
   (Mean2360MB_error*Mean2360MB_error)/(Mean2360MB*Mean2360MB));
   Ratio2360CaloInclusive_error = sqrt(Ratio2360CaloInclusive_error);
   
   std::cout << "Ratio2360 PF Dijet/MB = " << Ratio2360PFDijet << " +- " << Ratio2360PFDijet_error << std::endl;
   std::cout << "Ratio2360 PF Inclusive/MB = " << Ratio2360PFInclusive << " +- " << Ratio2360PFInclusive_error << std::endl;
   std::cout << "Ratio2360 Calo Dijet/MB = " << Ratio2360CaloDijet << " +- " << Ratio2360CaloDijet_error << std::endl;
   std::cout << "Ratio2360 Calo Inclusive/MB = " << Ratio2360CaloInclusive << " +- " << Ratio2360CaloInclusive_error << std::endl;
   std::cout << "" << std::endl;
   
   // MC ratios
   
   
   double Mean900MCMB = h900MCSignalTot->GetMean();
   double Mean900MCMB_error = h900MCSignalTot->GetMeanError();
   std::cout << "900 GeV MC mean = " << Mean900MCMB << "+-" << Mean900MCMB_error << std::endl;
   
   double Mean900MCPFDijet = h900MCSignalTotPFDijet->GetMean();
   double Mean900MCPFInclusive = h900MCSignalTotPFInclusive->GetMean();
   
   double Mean900MCCaloDijet = h900MCSignalTotCaloDijet->GetMean();
   double Mean900MCCaloInclusive = h900MCSignalTotCaloInclusive->GetMean();
   
   double Mean900MCPFDijet_error = h900MCSignalTotPFDijet->GetMeanError();
   double Mean900MCPFInclusive_error = h900MCSignalTotPFInclusive->GetMeanError();
   
   double Mean900MCCaloDijet_error = h900MCSignalTotCaloDijet->GetMeanError();
   double Mean900MCCaloInclusive_error = h900MCSignalTotCaloInclusive->GetMeanError();
   
   double Ratio900MCPFDijet = Mean900MCPFDijet/Mean900MCMB;
   double Ratio900MCPFInclusive = Mean900MCPFInclusive/Mean900MCMB;
   
   double Ratio900MCCaloDijet = Mean900MCCaloDijet/Mean900MCMB;
   double Ratio900MCCaloInclusive = Mean900MCCaloInclusive/Mean900MCMB;
   
   double Ratio900MCPFDijet_error = Ratio900MCPFDijet*Ratio900MCPFDijet*((Mean900MCPFDijet_error*Mean900MCPFDijet_error)/(Mean900MCPFDijet*Mean900MCPFDijet) +
   (Mean900MCMB_error*Mean900MCMB_error)/(Mean900MCMB*Mean900MCMB));
   Ratio900MCPFDijet_error = sqrt(Ratio900MCPFDijet_error);
   
   double Ratio900MCPFInclusive_error = Ratio900MCPFInclusive*Ratio900MCPFInclusive*((Mean900MCPFInclusive_error*Mean900MCPFInclusive_error)/(Mean900MCPFInclusive*Mean900MCPFInclusive) +
   (Mean900MCMB_error*Mean900MCMB_error)/(Mean900MCMB*Mean900MCMB));
   Ratio900MCPFInclusive_error = sqrt(Ratio900MCPFInclusive_error);
   
   double Ratio900MCCaloDijet_error = Ratio900MCCaloDijet*Ratio900MCCaloDijet*((Mean900MCCaloDijet_error*Mean900MCCaloDijet_error)/(Mean900MCCaloDijet*Mean900MCCaloDijet) +
   (Mean900MCMB_error*Mean900MCMB_error)/(Mean900MCMB*Mean900MCMB));
   Ratio900MCCaloDijet_error = sqrt(Ratio900MCCaloDijet_error);
   
   double Ratio900MCCaloInclusive_error = Ratio900MCCaloInclusive*Ratio900MCCaloInclusive*((Mean900MCCaloInclusive_error*Mean900MCCaloInclusive_error)/(Mean900MCCaloInclusive*Mean900MCCaloInclusive) +
   (Mean900MCMB_error*Mean900MCMB_error)/(Mean900MCMB*Mean900MCMB));
   Ratio900MCCaloInclusive_error = sqrt(Ratio900MCCaloInclusive_error);
   
   std::cout << "Ratio900MC PF Dijet/MB = " << Ratio900MCPFDijet << " +- " << Ratio900MCPFDijet_error << std::endl;
   std::cout << "Ratio900MC PF Inclusive/MB = " << Ratio900MCPFInclusive << " +- " << Ratio900MCPFInclusive_error << std::endl;
   std::cout << "Ratio900MC Calo Dijet/MB = " << Ratio900MCCaloDijet << " +- " << Ratio900MCCaloDijet_error << std::endl;
   std::cout << "Ratio900MC Calo Inclusive/MB = " << Ratio900MCCaloInclusive << " +- " << Ratio900MCCaloInclusive_error << std::endl;
   std::cout << "" << std::endl;
   
   double Mean2360MCMB = h2360MCSignalTot->GetMean();
   double Mean2360MCMB_error = h2360MCSignalTot->GetMeanError();
   std::cout << "2360 GeV MC mean = " << Mean2360MCMB << "+-" << Mean2360MCMB_error << std::endl;
   
   double Mean2360MCPFDijet = h2360MCSignalTotPFDijet->GetMean();
   double Mean2360MCPFInclusive = h2360MCSignalTotPFInclusive->GetMean();
   
   double Mean2360MCCaloDijet = h2360MCSignalTotCaloDijet->GetMean();
   double Mean2360MCCaloInclusive = h2360MCSignalTotCaloInclusive->GetMean();
   
   double Mean2360MCPFDijet_error = h2360MCSignalTotPFDijet->GetMeanError();
   double Mean2360MCPFInclusive_error = h2360MCSignalTotPFInclusive->GetMeanError();
   
   double Mean2360MCCaloDijet_error = h2360MCSignalTotCaloDijet->GetMeanError();
   double Mean2360MCCaloInclusive_error = h2360MCSignalTotCaloInclusive->GetMeanError();
   
   double Ratio2360MCPFDijet = Mean2360MCPFDijet/Mean2360MCMB;
   double Ratio2360MCPFInclusive = Mean2360MCPFInclusive/Mean2360MCMB;
   
   double Ratio2360MCCaloDijet = Mean2360MCCaloDijet/Mean2360MCMB;
   double Ratio2360MCCaloInclusive = Mean2360MCCaloInclusive/Mean2360MCMB;
   
   double Ratio2360MCPFDijet_error = Ratio2360MCPFDijet*Ratio2360MCPFDijet*((Mean2360MCPFDijet_error*Mean2360MCPFDijet_error)/(Mean2360MCPFDijet*Mean2360MCPFDijet) +
   (Mean2360MCMB_error*Mean2360MCMB_error)/(Mean2360MCMB*Mean2360MCMB));
   Ratio2360MCPFDijet_error = sqrt(Ratio2360MCPFDijet_error);
   
   double Ratio2360MCPFInclusive_error = Ratio2360MCPFInclusive*Ratio2360MCPFInclusive*((Mean2360MCPFInclusive_error*Mean2360MCPFInclusive_error)/(Mean2360MCPFInclusive*Mean2360MCPFInclusive) +
   (Mean2360MCMB_error*Mean2360MCMB_error)/(Mean2360MCMB*Mean2360MCMB));
   Ratio2360MCPFInclusive_error = sqrt(Ratio2360MCPFInclusive_error);
   
   double Ratio2360MCCaloDijet_error = Ratio2360MCCaloDijet*Ratio2360MCCaloDijet*((Mean2360MCCaloDijet_error*Mean2360MCCaloDijet_error)/(Mean2360MCCaloDijet*Mean2360MCCaloDijet) +
   (Mean2360MCMB_error*Mean2360MCMB_error)/(Mean2360MCMB*Mean2360MCMB));
   Ratio2360MCCaloDijet_error = sqrt(Ratio2360MCCaloDijet_error);
   
   double Ratio2360MCCaloInclusive_error = Ratio2360MCCaloInclusive*Ratio2360MCCaloInclusive*((Mean2360MCCaloInclusive_error*Mean2360MCCaloInclusive_error)/(Mean2360MCCaloInclusive*Mean2360MCCaloInclusive) +
   (Mean2360MCMB_error*Mean2360MCMB_error)/(Mean2360MCMB*Mean2360MCMB));
   Ratio2360MCCaloInclusive_error = sqrt(Ratio2360MCCaloInclusive_error);
   
   std::cout << "Ratio2360MC PF Dijet/MB = " << Ratio2360MCPFDijet << " +- " << Ratio2360MCPFDijet_error << std::endl;
   std::cout << "Ratio2360MC PF Inclusive/MB = " << Ratio2360MCPFInclusive << " +- " << Ratio2360MCPFInclusive_error << std::endl;
   std::cout << "Ratio2360MC Calo Dijet/MB = " << Ratio2360MCCaloDijet << " +- " << Ratio2360MCCaloDijet_error << std::endl;
   std::cout << "Ratio2360MC Calo Inclusive/MB = " << Ratio2360MCCaloInclusive << " +- " << Ratio2360MCCaloInclusive_error << std::endl;
   std::cout << "" << std::endl;
   
   /////////////////////
   // plot paper plots
   /////////////////////
   
   double cms[2] = {900,2360};
   double cms_error[2] = {0,0};
   double yRatioPFDijet[2] = {Ratio900PFDijet, Ratio2360PFDijet};
   double yRatioPFInclusive[2] = {Ratio900PFInclusive, Ratio2360PFInclusive};
   double yRatioPFDijet_error[2] = {Ratio900PFDijet_error, Ratio2360PFDijet_error};
   double yRatioPFInclusive_error[2] = {Ratio900PFInclusive_error, Ratio2360PFInclusive_error};
   
   double yRatioCaloDijet[2] = {Ratio900CaloDijet, Ratio2360CaloDijet};
   double yRatioCaloInclusive[2] = {Ratio900CaloInclusive, Ratio2360CaloInclusive};
   double yRatioCaloDijet_error[2] = {Ratio900CaloDijet_error, Ratio2360CaloDijet_error};
   double yRatioCaloInclusive_error[2] = {Ratio900CaloInclusive_error, Ratio2360CaloInclusive_error};
   
   
   TGraphErrors *gRatiosPFDijetPaper = new TGraphErrors(2,cms,yRatioPFDijet,cms_error,yRatioPFDijet_error);
   TGraphErrors *gRatiosPFInclusivePaper = new TGraphErrors(2,cms,yRatioPFInclusive,cms_error,yRatioPFInclusive_error);
   gRatiosPFDijetPaper->SetTitle("Dijet Ratios");
   gRatiosPFInclusivePaper->SetTitle("Inclusive jet Ratios");
   gRatiosPFDijetPaper->SetName("gRatiosPFDijetPaper");
   gRatiosPFInclusivePaper->SetName("gRatiosPFInclusivePaper");
   
   TGraphErrors *gRatiosCaloDijetPaper = new TGraphErrors(2,cms,yRatioCaloDijet,cms_error,yRatioCaloDijet_error);
   TGraphErrors *gRatiosCaloInclusivePaper = new TGraphErrors(2,cms,yRatioCaloInclusive,cms_error,yRatioCaloInclusive_error);
   gRatiosCaloDijetPaper->SetTitle("Dijet Ratios");
   gRatiosCaloInclusivePaper->SetTitle("Inclusive jet Ratios");
   gRatiosCaloDijetPaper->SetName("gRatiosCaloDijetPaper");
   gRatiosCaloInclusivePaper->SetName("gRatiosCaloInclusivePaper");
   
   TH1D *hRatiosPFDijetMCPaper = new TH1D("hRatiosPFDijetMCPaper","PF Dijet MC ratio;Center of Mass energies (GeV);Ratio",2,170,3090);
   TH1D *hRatiosPFInclusiveMCPaper = new TH1D("hRatiosPFInclusiveMCPaper","PF Inclusive MC ratio;Center of Mass energies (GeV);Ratio",2,170,3090);
   hRatiosPFDijetMCPaper->SetBinContent(1,Ratio900MCPFDijet);
   hRatiosPFDijetMCPaper->SetBinError(1,Ratio900MCPFDijet_error);
   hRatiosPFDijetMCPaper->SetBinContent(2,Ratio2360MCPFDijet);
   hRatiosPFDijetMCPaper->SetBinError(2,Ratio2360MCPFDijet_error);
   hRatiosPFInclusiveMCPaper->SetBinContent(1,Ratio900MCPFInclusive);
   hRatiosPFInclusiveMCPaper->SetBinError(1,Ratio900MCPFInclusive_error);
   hRatiosPFInclusiveMCPaper->SetBinContent(2,Ratio2360MCPFInclusive);
   hRatiosPFInclusiveMCPaper->SetBinError(2,Ratio2360MCPFInclusive_error);
   hRatiosPFDijetMCPaper->SetStats(0);
   hRatiosPFInclusiveMCPaper->SetStats(0);
   
   TH1D *hRatiosCaloDijetMCPaper = new TH1D("hRatiosCaloDijetMCPaper","Calo Dijet MC ratio;Center of Mass energies (GeV);Ratio",2,170,3090);
   TH1D *hRatiosCaloInclusiveMCPaper = new TH1D("hRatiosCaloInclusiveMCPaper","Calo Inclusive MC ratio;Center of Mass energies (GeV);Ratio",2,170,3090);
   hRatiosCaloDijetMCPaper->SetBinContent(1,Ratio900MCCaloDijet);
   hRatiosCaloDijetMCPaper->SetBinError(1,Ratio900MCCaloDijet_error);
   hRatiosCaloDijetMCPaper->SetBinContent(2,Ratio2360MCCaloDijet);
   hRatiosCaloDijetMCPaper->SetBinError(2,Ratio2360MCCaloDijet_error);
   hRatiosCaloInclusiveMCPaper->SetBinContent(1,Ratio900MCCaloInclusive);
   hRatiosCaloInclusiveMCPaper->SetBinError(1,Ratio900MCCaloInclusive_error);
   hRatiosCaloInclusiveMCPaper->SetBinContent(2,Ratio2360MCCaloInclusive);
   hRatiosCaloInclusiveMCPaper->SetBinError(2,Ratio2360MCCaloInclusive_error);
   hRatiosCaloDijetMCPaper->SetStats(0);
   hRatiosCaloInclusiveMCPaper->SetStats(0);
   
   TCanvas *cPFRatios = new TCanvas("cPFRatios","Forward Energy Flow Ratios in CASTOR");
   cPFRatios->Divide(1,1);
   cPFRatios->cd(1);
   // plot MC
   hRatiosPFInclusiveMCPaper->SetFillStyle(1001);
   hRatiosPFDijetMCPaper->SetFillStyle(3004);
   hRatiosPFInclusiveMCPaper->SetFillColor(kGray);
   hRatiosPFDijetMCPaper->SetFillColor(1);
   hRatiosPFInclusiveMCPaper->SetMarkerStyle(0);
   hRatiosPFDijetMCPaper->SetMarkerStyle(0);
   hRatiosPFInclusiveMCPaper->GetYaxis()->SetRangeUser(0.6,1.3);
   hRatiosPFInclusiveMCPaper->SetTitle("Forward Energy Flow Ratios in CASTOR - PF jets");
   hRatiosPFInclusiveMCPaper->Draw("hist");
   hRatiosPFDijetMCPaper->Draw("samehist");
   // plot data
   gRatiosPFInclusivePaper->Draw("sameP");
   gRatiosPFDijetPaper->Draw("sameP");
   gRatiosPFInclusivePaper->SetMarkerStyle(21);
   gRatiosPFDijetPaper->SetMarkerStyle(23);
   
   TCanvas *cCaloRatios = new TCanvas("cCaloRatios","Forward Energy Flow Ratios in CASTOR");
   cCaloRatios->Divide(1,1);
   cCaloRatios->cd(1);
   // plot MC
   hRatiosCaloInclusiveMCPaper->SetFillStyle(1001);
   hRatiosCaloDijetMCPaper->SetFillStyle(3004);
   hRatiosCaloInclusiveMCPaper->SetFillColor(kGray);
   hRatiosCaloDijetMCPaper->SetFillColor(1);
   hRatiosCaloInclusiveMCPaper->SetMarkerStyle(0);
   hRatiosCaloDijetMCPaper->SetMarkerStyle(0);
   hRatiosCaloInclusiveMCPaper->GetYaxis()->SetRangeUser(0.6,1.4);
   hRatiosCaloInclusiveMCPaper->SetTitle("Forward Energy Flow Ratios in CASTOR - Calo jets");
   hRatiosCaloInclusiveMCPaper->Draw("hist");
   hRatiosCaloDijetMCPaper->Draw("samehist");
   // plot data
   gRatiosCaloInclusivePaper->Draw("sameP");
   gRatiosCaloDijetPaper->Draw("sameP");
   gRatiosCaloInclusivePaper->SetMarkerStyle(21);
   gRatiosCaloDijetPaper->SetMarkerStyle(23);
   
   // save all the canvasses
   
   c1_900paper->SaveAs("./plots_16_fC_newMC/eflow900GeV.eps");
   c1_2360paper->SaveAs("./plots_16_fC_newMC/eflow2360GeV.eps");
   
   ceflow900GeV_modules->SaveAs("./plots_16_fC_newMC/eflow900GeV_modules.eps");
   cPFDijet900GeV_modules->SaveAs("./plots_16_fC_newMC/PFDijet900GeV_modules.eps");
   ceflow2360GeV_modules->SaveAs("./plots_16_fC_newMC/eflow2360GeV_modules.eps");
   cPFDijet2360GeV_modules->SaveAs("./plots_16_fC_newMC/PFDijet2360GeV_modules.eps");
   ceflow900GeV_sectors->SaveAs("./plots_16_fC_newMC/eflow900GeV_sectors.eps");
   cPFDijet900GeV_sectors->SaveAs("./plots_16_fC_newMC/PFDijet900GeV_sectors.eps");
   ceflow2360GeV_sectors->SaveAs("./plots_16_fC_newMC/eflow2360GeV_sectors.eps");
   cPFDijet2360GeV_sectors->SaveAs("./plots_16_fC_newMC/PFDijet2360GeV_sectors.eps");
   
   c900RatiosModules->SaveAs("./plots_16_fC_newMC/Ratios_vs_modules_900GeV.eps");
   c900RatiosSectors->SaveAs("./plots_16_fC_newMC/Ratios_vs_sectors_900GeV.eps");
   c2360RatiosModules->SaveAs("./plots_16_fC_newMC/Ratios_vs_modules_2360GeV.eps");
   c2360RatiosSectors->SaveAs("./plots_16_fC_newMC/Ratios_vs_sectors_2360GeV.eps");
   
   cMeansModules->SaveAs("./plots_16_fC_newMC/MeanSignal_vs_modules_900GeV.eps");
   cMeansSectors->SaveAs("./plots_16_fC_newMC/MeanSignal_vs_sectors_900GeV.eps");
   cMeans2360Modules->SaveAs("./plots_16_fC_newMC/MeanSignal_vs_modules_2360GeV.eps");
   cMeans2360Sectors->SaveAs("./plots_16_fC_newMC/MeanSignal_vs_sectors_2360GeV.eps");
   
   cChannelRatio->SaveAs("./plots_16_fC_newMC/96Ratios900GeV.eps");
   cChannelRatio2360->SaveAs("./plots_16_fC_newMC/96Ratios2360GeV.eps");
   
   cPFRatios->SaveAs("./plots_16_fC_newMC/PFRatios.eps");
   cCaloRatios->SaveAs("./plots_16_fC_newMC/CaloRatios.eps");
   
   
   
}
