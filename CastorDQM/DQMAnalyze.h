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

void GetDecision_HVBeamStatus(TH2F* histo,vector<Int_t>& list_LS_min,vector<Int_t>& list_LS_max,Int_t run,Int_t& decision) {

  Int_t END = 10000;

  Int_t debug = 0;
  Int_t debug_summary = 0;

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

  //-- retrieve good LS blocks

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
    if(histo->GetBinContent(i,CastorBin) < 0.5 && current_min == true) { 
      // to avoid to read multiple time when several consecutive bad LS 
      list_LS_min.push_back(LS_min);
      list_LS_max.push_back(LS_max);
      current_min = false;
    }
  } //--  end loop retrieve good LS blocks
  
  //-- if no good LS at all
  if(LS_min == 0 && LS_max == 0) {
    list_LS_min.push_back(LS_min);
    list_LS_max.push_back(LS_max);
  }

  //-- if maxRange = nbinx + 1 
  if(maxRange == nbinx+1) {
    list_LS_min.push_back(LS_min);
    list_LS_max.push_back(LS_max);
  }

  //-- special treatment for the runs taken before 20.06.2010 
  //-- Castor DCS bit was not sent to central DCS before 20.06.2010. (Ekaterina)
  //-- HV selection can not be taken from DQM plots before 20.06.2010 

  //-- Commissioning10 

  //-- these runs have to be rejected because of wrong timing
  if(run >= 132440 && run <= 132606) {
    decision = 0;
    LS_min = 0;
    LS_max = 0;
  }

  //-- HV status of these runs should stay BAD (was not able to check HV status)
  if(run >= 132646 && run <= 133928) {
    decision = 0;
    LS_min = 0;
    LS_max = 0;
  }

  //-- was able to check these runs
  if( run == 134721) {
    decision = 1;
    LS_min = 589;
    LS_max = END;
  }

  if(run == 134725) {
    decision = 1; 
    LS_min = 1;
    LS_max = 1305;
  }

  if(run == 135059) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 135149) {
    decision = 1;
    LS_min = 669;
    LS_max = END;
  }

  if(run == 135175) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 135445) {
    decision = 1;
    LS_min = 353;
    LS_max = END;
  }

  if(run == 135521) {
    decision = 1;
    LS_min = 95;
    LS_max = END;
  }

  if(run == 135523) {
    decision = 1;
    LS_min = 116;
    LS_max = END;
  }

  if(run == 135525) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 135528) {
    decision = 1;
    LS_min = 1; 
    LS_max = END;
  }

  if(run == 135534) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 135535) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 135537) {
    decision = 1;
    LS_min = 1; 
    LS_max = END;
  }

  if(run == 135538) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 135573) {
    decision = 1; 
    LS_min = 1;
    LS_max = END;
  }

  if(run == 135575) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 135735) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  //-- Run2010A

  //-- was able to check these runs
  if(run == 136033) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 136035) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 136066) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 136080) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 136082) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 136087) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 136088) {
    decision = 1;
    LS_min = 1;
    LS_max = 263; //-- wrong HV AFTER 263
  }

  if(run == 136097) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 136098) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 136100) {
    decision = 1;
    LS_min = 314;
    LS_max = END;
  }

  if(run == 136119) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 136290) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 136294) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 136297) {
    decision = 1;
    LS_min = 1;
    LS_max = END;
  }

  if(run == 137027) {
    decision = 0; //-- too many channels are off
    LS_min = 0;
    LS_max = 0;
  }

  if(run == 137028) {
    decision = 0; //-- too many channels are off
    LS_min = 0;
    LS_max = 0;
  }

  if(run == 138560) {
    decision = 0; //-- too many channels are off
    LS_min = 0;
    LS_max = 0;
  }

  if(run == 138562) {
    decision = 0; //-- far side HV off
    LS_min = 0;
    LS_max = 0;
  }

  if(run == 138563) {
    decision = 0; //-- far side HV off
    LS_min = 0;
    LS_max = 0;
  }

  if(run == 138564) {
    decision = 0; //-- far side HV off
    LS_min = 0;
    LS_max = 0;
  }

  if(run == 138565) {
    decision = 0; //-- far side HV off
    LS_min = 0;
    LS_max = 0;
  }

  if(run == 138570) { 
    decision = 0;  //-- far side HV off
    LS_min = 0;
    LS_max = 0;
  }

  if(run == 138571) { 
    decision = 0; //-- far side HV off
    LS_min = 0;
    LS_max = 0; 
  }

  if(run == 138572) { 
    decision = 0; //-- far side HV off
    LS_min = 0;
    LS_max = 0; 
  }

  //-- conflict between HV DQM Plot and online HV interface

  if(run == 141874) {
    decision = 0; //-- near side, far side: all HV off (or page 216: HV status GOOD??)
    LS_min = 0;
    LS_max = 0;
  }

  if(run == 141876) {
    decision = 0; //-- near side, far side: all HV off (or page 166: HV status GOOD??)
    LS_min = 0;
    LS_max = 0;
  }

  //-- special treatment for the runs taken before 20.06.2010 + far side HV off

  if(run >= 132440 && run <=  138572) {
    list_LS_min.clear();
    list_LS_max.clear();

    list_LS_min.push_back(LS_min);
    list_LS_max.push_back(LS_max);
  }

  if(debug_summary) {
    cout<<""<<endl;
    cout<<"run: "<<run<<endl;
    cout<<"decision: "<<decision<<endl;
    cout<<list_LS_min.size()<<" blocks of good LS: ";
    for(int i = 0; i < list_LS_min.size(); i++) {
      cout<<" "<<list_LS_min.at(i)<<" - "<<list_LS_max.at(i);
      if(i != list_LS_min.size() -1) cout<<" , ";
    }
    cout<<""<<endl;
  }

}


