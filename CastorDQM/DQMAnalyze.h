#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>
#include <TStyle.h>
#include <TH1.h>
#include <TH2.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TAxis.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TRegexp.h>
#include <TExec.h>
#include <TSystem.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

void SetStyle() {
  gROOT->SetStyle("Plain");

  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadBorderSize(0);
  gStyle->SetOptStat(0);
}

void SetStyle(TLegendEntry* entry) {
  entry->SetTextSize(0.05);
  entry->SetTextFont(42);
}

void SetStyle(TLegend* leg) {
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
}

bool init = false;

void reportSummaryMapPalette(TH2* histo) {

  static Int_t pcol[20];

  if( !init ) {

    init = true;

    float rgb[20][3];

    for( int i=0; i<20; i++) {
     
      if (i < 17) {
        rgb[i][0] = 0.80+0.01*i;
        rgb[i][1] = 0.00+0.03*i;
        rgb[i][2] = 0.00;
      }
      
      else if( i < 19) {
        rgb[i][0] = 0.80+0.01*i;
        rgb[i][1] = 0.00+0.03*i+0.15+0.10*(i-17);
        rgb[i][2] = 0.00;
      }
      
      else if(i == 19) {
        rgb[i][0] = 0.00;
        rgb[i][1] = 0.80;
        rgb[i][2] = 0.00;
      }

      pcol[i] = 901+i;
      TColor* color = gROOT->GetColor(901+i);
      if( ! color ) color = new TColor(901+i,0,0,0,"");
      color->SetRGB(rgb[i][0],rgb[i][1],rgb[i][2]);
    }
  }

  gStyle->SetPalette(20, pcol);
 
  if(histo) {
    histo->SetMinimum(-1.e-15);
    histo->SetMaximum(+1.0);
    histo->SetOption("colz");
  }

}

void preDrawCastorTH2(TPad *pad,TH2F* histo) { 

  Int_t debug = 0;

  assert(histo);
  
  histo->SetStats(kFALSE);
  histo->SetOption("colz");
  histo->GetXaxis()->SetLabelSize(0.03);
  histo->GetYaxis()->SetLabelSize(0.03);
  histo->GetXaxis()->SetTitle("z-module");
  histo->GetYaxis()->SetTitle("#phi-sector");
  
  TString histo_name = histo->GetName(); 
  if(debug) cout<<"name of the histogram: "<<histo_name.Data()<<endl;

  char *label[16] = {"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16"};

  if (histo_name.Index("reportSummaryMap") != kNPOS) {
    
    if(debug) cout<<"reportSummaryMap \n"<<endl;
  
    histo->GetXaxis()->SetNdivisions(15,true);
    histo->GetYaxis()->SetNdivisions(17,true);
    histo->GetXaxis()->SetLabelSize(0.03);
    histo->GetYaxis()->SetLabelSize(0.03);
    
    for(int i = 1; i < 15; i ++) histo->GetXaxis()->SetBinLabel(i,label[i-1]);
    for(int i = 1; i < 17; i ++) histo->GetYaxis()->SetBinLabel(i,label[i-1]);
    
    histo->GetXaxis()->CenterLabels();
    histo->GetYaxis()->CenterLabels();
    
    pad->SetGrid(1,1);
    
    reportSummaryMapPalette(histo);

    histo->SetMinimum(0.0);
    histo->SetMaximum(+1.0);
  }

  if (histo_name.Index("ChannelSummaryMap") != kNPOS) {
    
    if(debug) cout<<"ChannelSummaryMap \n"<<endl;
       
    histo->GetXaxis()->SetNdivisions(15,true);
    histo->GetYaxis()->SetNdivisions(17,true);
    histo->GetXaxis()->SetLabelSize(0.03);
    histo->GetYaxis()->SetLabelSize(0.03);
    
    for(int i = 1; i < 15; i ++) histo->GetXaxis()->SetBinLabel(i,label[i-1]);
    for(int i = 1; i < 17; i ++) histo->GetYaxis()->SetBinLabel(i,label[i-1]);

    histo->GetXaxis()->CenterLabels();
    histo->GetYaxis()->CenterLabels();
    
    pad->SetGrid(1,1);
    
    histo->SetMinimum(-1.0);
    histo->SetMaximum(+1.0);

    Int_t colorError1[4];
    colorError1[0] = 632; // kRed
    colorError1[1] = 800; // kOrange
    colorError1[2] = 432; // kCyan 
    colorError1[3] = 416; // kGreen
    
    gStyle->SetPalette(4,colorError1);
    gStyle->SetPaintTextFormat("+g");
  }
  
  return;  
}

void preDrawInfoTH2(TPad* pad,TH2F* histo) {

  assert(histo);
  
  Int_t nbinx = histo->GetNbinsX();
  Int_t topBin = histo->GetNbinsY();
  Int_t maxRange = nbinx;
  
  for (int i = nbinx; i > 0; --i) {
    if (histo->GetBinContent(i,topBin) != 0) {
      maxRange = TMath::Max(i+1,2);  // leave at least 2 bins
      break;
    }
  }
 
  histo->GetXaxis()->SetRange(1,maxRange);
  histo->GetYaxis()->SetRange(1,topBin);
    
  pad->SetGrid(1,1);
  pad->SetLeftMargin(0.12);
  histo->SetStats(kFALSE);
  
  Int_t pcol[2];
  float rgb[2][2];
  rgb[0][0] = 0.80;
  rgb[0][1] = 0.00;
  rgb[1][0] = 0.00;
  rgb[1][1] = 0.80;
  
  for(int i=0; i<2; i++) {
    pcol[i] = 801+i;
    TColor* color2 = gROOT->GetColor(801+i);
    if(!color2) color2 = new TColor(801+i,0,0,0,"");
    color2->SetRGB(rgb[i][0],rgb[i][1],0.);
  }
  
  gStyle->SetPalette(2,pcol);
  histo->SetMinimum(-1.e-15);
  histo->SetMaximum(1.0);
  histo->SetOption("colz");
  
  return;
}

void GetDecision_reportSummaryMap(TH2F* histo,Int_t& ngreen,Double_t& ratio,Int_t& decision) {
  
  //-- Castor reportSummaryMap
  //-- at least 50% of the bins in this histogram must be GREEN

  Int_t debug = 0;

  Double_t value = 0;
  Double_t ratio_min = 0.50;

  Int_t ntot = 224;

  for(int ibin_x = 1; ibin_x <= 14; ++ibin_x) {
    for(int ibin_y = 1; ibin_y <= 16; ++ibin_y) {
	  
      value = histo->GetBinContent(ibin_x,ibin_y);
      if(value > 0.949) ngreen++; 
      if(debug) cout<<"module: "<<ibin_x<<" sector: "<<ibin_y<<" value: "<<value<<endl;
    }
  }
 
  ratio = 1.0*ngreen/ntot;
  if(ratio > ratio_min) decision = 1; 

  if(debug) cout<<endl;
  if(debug) cout<<"reportSummaryMap ngreen: "<<ngreen<<endl;
  if(debug) cout<<"reportSummaryMap ratio: "<<ratio<<endl;
  if(debug) cout<<"reportSummaryMap decision: "<<decision<<endl;
  if(debug) cout<<endl;
}

void GetDecision_ChannelSummaryMap(TH2F* histo,Int_t& ngreen,Int_t& ncyan,Double_t& ratio,Int_t& decision) {
  
  //-- CASTOR Digi ChannelSummaryMap
  //-- most of the channels (above 50%) must either be GREEN or CYAN

  Int_t debug = 0;

  Double_t value = 0;
  Double_t ratio_min = 0.50;

  Int_t ntot = 224;

  for(int ibin_x = 1; ibin_x <= 14; ++ibin_x) {
    for(int ibin_y = 1; ibin_y <= 16; ++ibin_y) {
	  
      value = histo->GetBinContent(ibin_x,ibin_y);
      if(value > 0 && value < 0.5) ncyan++;
      if(value > 0.5) ngreen++;
      if(debug) cout<<"module: "<<ibin_x<<" sector: "<<ibin_y<<" value: "<<value<<endl;
    }
  }

  ratio = 1.0*(ngreen+ncyan)/ntot;
  if(ratio > ratio_min && ncyan != 224) decision = 1; //-- ncyan == 224: pedestal or not in the DAQ

  if(debug) cout<<endl;
  if(debug) cout<<"ChannelSummaryMap ngreen: "<<ngreen<<endl;
  if(debug) cout<<"ChannelSummaryMap ncyan: "<<ncyan<<endl;
  if(debug) cout<<"ChannelSummaryMap ratio: "<<ratio<<endl;
  if(debug) cout<<"ChannelSummaryMap decision: "<<decision<<endl;
  if(debug) cout<<endl;
}


void GetDecision_AllDigiValues(TH1F* histo,Double_t& mean,Int_t& decision) {
  
  //-- CASTOR All Digi Values
  //-- the mean value of this histogram lies in the interval between 2 and 10 ADC

  Int_t debug = 0;

  Double_t min = 2;
  Double_t max = 10;

  mean = histo->GetMean();
  if(mean > min && mean < max) decision = 1;

  if(debug) cout<<endl;
  if(debug) cout<<"AllDigiValues mean: "<<mean<<endl;
  if(debug) cout<<"AllDigiValues decision: "<<decision<<endl;
  if(debug) cout<<endl;
}

void GetDecision_HVBeamStatus(TH2F* histo,vector<Int_t>& list_LS_min,vector<Int_t>& list_LS_max,Int_t& decision) {

  Int_t debug = 0;

  Int_t nbinx = histo->GetNbinsX();
  Int_t topBin = histo->GetNbinsY();
  Int_t maxRange = nbinx;

  TString label;
  TRegexp regexp_Castor("CASTOR");
  Int_t CastorBin = 0;

  //-- retrieve the bin in y corresponding to Castor (CastorBin)

  for (int i = 1; i < topBin+1; i++) {
    label = histo->GetYaxis()->GetBinLabel(i);
    if(debug) cout<<"bin "<<i<<" has label: "<<label.Data()<<endl;
    if(label.Index(regexp_Castor) != kNPOS) CastorBin = i;
  }

  if(debug) cout<<""<<endl;
  if(debug) cout<<"Castor bin: "<<CastorBin<<endl;
  if(debug) cout<<""<<endl;

  //-- retrieve the "last good LS + one" (maxRange)

  for (int i = nbinx; i > 0; --i) {
    if (histo->GetBinContent(i,topBin) != 0) {
      maxRange = i+1;
      break;
    }
  }

  if(debug) cout<<"last good LS + one: "<<maxRange<<endl;
  if(debug) cout<<""<<endl;

  //-- retrieve the good LS intervals

  Bool_t current_min = false;
  Int_t LS_min  = 0;
  Int_t LS_max = 0;
  
  for(int i = 1; i < maxRange+1; i++) {

    if(debug && i != maxRange) cout<<"LS: "<<i<<" Castor status: "<<histo->GetBinContent(i,CastorBin)<<endl;

    //-- good LS
    if(histo->GetBinContent(i,CastorBin) > 0.5){ 

      decision = 1;

      if (current_min == false) {
	LS_min = i;
	current_min = true; 
      }

      if(current_min == true) LS_max = i;
    }

    //-- bad LS
    if(histo->GetBinContent(i,CastorBin) < 0.5 && current_min == true) { // to avoid to read multiple time when several consecutive bad LS 
      list_LS_min.push_back(LS_min);
      list_LS_max.push_back(LS_max);
      current_min = false;
    }
  }
  
  //-- if no good LS at all
  if(LS_min == 0 && LS_max == 0) {
    list_LS_min.push_back(LS_min);
    list_LS_max.push_back(LS_max);
  }

  if(debug) {
    cout<<""<<endl;
    cout<<"decision: "<<decision<<endl;
    cout<<"selected good LS: ";
    for(int i = 0; i < list_LS_min.size(); i++) {
      cout<<" "<<list_LS_min.at(i)<<" - "<<list_LS_max.at(i);
      if(i != list_LS_min.size() -1) cout<<" , ";
    }
    cout<<""<<endl;
  }

}


