#define TreeAnalyzer_cxx
#include "TreeAnalyzer.h"
#include <TH2.h>
#include <TH1D.h>
#include <iostream>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
#include <TRandom3.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TGraphErrors.h>
#include <TVirtualPad.h>
#include <TPaveText.h>
#include <TF1.h>

#define M_PI 3.14159265358979323846

Double_t TreeAnalyzer::getRatioError(TH1D * hMB, TH1D * hQCD) {
   
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

Double_t TreeAnalyzer::fCfromADC(Int_t adc){

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

void TreeAnalyzer::plotEflows(int savePlots, int log, int nModules, int cms, double HADscale, double ABSscale)
{

  ////////////////////
  //  set style
  ////////////////////
  gROOT  -> SetStyle("Plain");
  gStyle -> SetMarkerStyle(1);
  gStyle -> SetMarkerSize(1);
  gStyle -> SetTextSize(1);
  //gStyle -> SetOptStat("eMR");//"iourmen");
  gStyle -> SetOptStat("");
  gStyle -> SetLineWidth(1.1);//gStyle->GetLineWidth()*1.5); // 2
  gStyle -> SetHistLineWidth(1.4);//gStyle->GetHistLineWidth()*1.5);// 2
  gStyle -> SetPadLeftMargin(0.15);
  gStyle -> SetPadRightMargin(0.1);
  gStyle -> SetPadBottomMargin(0.15);
  gStyle -> SetPadTopMargin(0.10);
  gStyle -> SetEndErrorSize(5);
  gStyle -> SetCanvasBorderSize(2);
  gStyle -> SetHistFillColor(kGray);
  gStyle -> SetHistMinimumZero(kTRUE);
  gStyle -> SetTitleOffset(1.5,"y");
  gStyle -> SetLegendBorderSize(0);
  gROOT  -> ForceStyle();

std::cout << "==== Parameter settings ====" << std::endl;
// set input parameters and show them
if (savePlots == 1) std::cout << "Your plots will be saved in ./TreeAnalyzer/Eflowplots" << std::endl;
if (savePlots == 0) std::cout << "Your plots will not be saved" << std::endl;
if (log == 1) std::cout << "Your plots will be shown in log scale" << std::endl;
if (log == 0) std::cout << "Your plots will be shown in linear scale" << std::endl;

int maxChannel = nModules*16;
std::cout << "Using " << nModules << " modules for the energy flow" << std::endl;
std::cout << "this means we use the first " << maxChannel << " channels of CASTOR" << std::endl;
std::cout << "Data and MC will be analyzed as having a cms of " << cms << std::endl;
if (HADscale != 0) std::cout << "The MC HAD section in CASTOR will be scaled with a factor " << HADscale << std::endl;
if (HADscale == 0) std::cout << "The MC HAD scale is set to 0, you will end up with crazy results" << std::endl;
if (ABSscale != 0) std::cout << "The MC signal in CASTOR will be scaled with a factor " << ABSscale << std::endl;
if (ABSscale == 0) std::cout << "The MC scale is set to 0, you will end up with crazy results" << std::endl;
std::cout << "==== ================== ====" << std::endl;

double maxRange = 40000;
TString cmsstring = "1";
if (cms == 900) {cmsstring = "900"; maxRange = 40000;}
if (cms == 2360) {cmsstring = "2360"; maxRange = 60000;}
if (cms == 7000) {cmsstring = "7000"; maxRange = 80000;}
Char_t HADscalestring[1];
sprintf(HADscalestring,"%6.4f",HADscale);

// define histograms
// MB
TH1D *h900run124020_eflow = new TH1D("h900run124020_eflow","MB energy flow in CASTOR 900GeV - run 124020;Signal(fC);Events",100,-2000,40000);
TH1D *h900run124022_eflow = new TH1D("h900run124022_eflow","MB energy flow in CASTOR 900GeV - run 124022;Signal(fC);Events",100,-2000,40000);
TH1D *h900run124023_eflow = new TH1D("h900run124023_eflow","MB energy flow in CASTOR 900GeV - run 124023;Signal(fC);Events",100,-2000,40000);
TH1D *h900run124024_eflow = new TH1D("h900run124024_eflow","MB energy flow in CASTOR 900GeV - run 124024;Signal(fC);Events",100,-2000,40000);
TH1D *h900run124027_eflow = new TH1D("h900run124027_eflow","MB energy flow in CASTOR 900GeV - run 124027;Signal(fC);Events",100,-2000,40000);
TH1D *h900run124030_eflow = new TH1D("h900run124030_eflow","MB energy flow in CASTOR 900GeV - run 124030;Signal(fC);Events",100,-2000,40000);

TH1D *h_eflow = new TH1D("h_eflow","MB energy flow in CASTOR " + cmsstring + "GeV;Signal(fC);Events",100,-2000,maxRange);
TH1D *hMC_eflow = new TH1D("hMC_eflow","MB energy flow in CASTOR " + cmsstring + "GeV MC;Signal(fC);Events",100,-2000,maxRange);

// QCD
TH1D *h900run124020_eflowPFDijet = new TH1D("h900run124020_eflowPFDijet","QCD dijet energy flow in CASTOR 900GeV - run 124020;Signal(fC);Events",20,-2000,40000);
TH1D *h900run124022_eflowPFDijet = new TH1D("h900run124022_eflowPFDijet","QCD dijet energy flow in CASTOR 900GeV - run 124022;Signal(fC);Events",20,-2000,40000);
TH1D *h900run124023_eflowPFDijet = new TH1D("h900run124023_eflowPFDijet","QCD dijet energy flow in CASTOR 900GeV - run 124023;Signal(fC);Events",20,-2000,40000);
TH1D *h900run124024_eflowPFDijet = new TH1D("h900run124024_eflowPFDijet","QCD dijet energy flow in CASTOR 900GeV - run 124024;Signal(fC);Events",20,-2000,40000);
TH1D *h900run124027_eflowPFDijet = new TH1D("h900run124027_eflowPFDijet","QCD dijet energy flow in CASTOR 900GeV - run 124027;Signal(fC);Events",20,-2000,40000);
TH1D *h900run124030_eflowPFDijet = new TH1D("h900run124030_eflowPFDijet","QCD dijet energy flow in CASTOR 900GeV - run 124030;Signal(fC);Events",20,-2000,40000);

TH1D *h900run124020_eflowPFInclusive = new TH1D("h900run124020_eflowPFInclusive","QCD Inclusive energy flow in CASTOR 900GeV - run 124020;Signal(fC);Events",20,-2000,40000);
TH1D *h900run124022_eflowPFInclusive = new TH1D("h900run124022_eflowPFInclusive","QCD Inclusive energy flow in CASTOR 900GeV - run 124022;Signal(fC);Events",20,-2000,40000);
TH1D *h900run124023_eflowPFInclusive = new TH1D("h900run124023_eflowPFInclusive","QCD Inclusive energy flow in CASTOR 900GeV - run 124023;Signal(fC);Events",20,-2000,40000);
TH1D *h900run124024_eflowPFInclusive = new TH1D("h900run124024_eflowPFInclusive","QCD Inclusive energy flow in CASTOR 900GeV - run 124024;Signal(fC);Events",20,-2000,40000);
TH1D *h900run124027_eflowPFInclusive = new TH1D("h900run124027_eflowPFInclusive","QCD Inclusive energy flow in CASTOR 900GeV - run 124027;Signal(fC);Events",20,-2000,40000);
TH1D *h900run124030_eflowPFInclusive = new TH1D("h900run124030_eflowPFInclusive","QCD Inclusive energy flow in CASTOR 900GeV - run 124030;Signal(fC);Events",20,-2000,40000);


TH1D *h_eflowPFDijet = new TH1D("h_eflowPFDijet","QCD dijet energy flow in CASTOR " + cmsstring + "GeV;Signal(fC);Events",20,-2000,maxRange);
TH1D *h_eflowPFInclusive = new TH1D("h_eflowPFInclusive","QCD inclusive energy flow in CASTOR " + cmsstring + "GeV;Signal(fC);Events",20,-2000,maxRange);

TH1D *hMC_eflowPFDijet = new TH1D("hMC_eflowPFDijet","QCD dijet energy flow in CASTOR MC " + cmsstring + "GeV;Signal(fC);Events",20,-2000,maxRange);
TH1D *hMC_eflowPFInclusive = new TH1D("hMC_eflowPFInclusive","QCD inclusive energy flow in CASTOR MC " + cmsstring + "GeV;Signal(fC);Events",20,-2000,maxRange);

// channel histograms
double ChannelMean[224];
double ChannelMeanMC[224];
for (int i=0;i<224;i++) {
	ChannelMean[i]=0;
	ChannelMeanMC[i]=0;
}

TH1D *hChannelMeans = new TH1D("hChannelMeans","Mean response in the channels for " + cmsstring + "GeV data;Channel;Signal(<fC>)",224,1,225);
TH1D *hChannelMeansMC = new TH1D("hChannelMeansMC","Mean response in the channels for " + cmsstring + "GeV MC;Channel;Signal(<fC>)",224,1,225);

std::cout << "Histograms are defined" << std::endl;

// set count numbers
      int nEvents_run124020 = 0;
      int nEvents_run124022 = 0;
      int nEvents_run124023 = 0;
      int nEvents_run124024 = 0;
      int nEvents_run124027 = 0;
      int nEvents_run124030 = 0;
      int nMCEvents = 0;
      int nEvents = 0;
      
std::cout << "Start variables are set" << std::endl;
std::cout << "Starting event loop now" << std::endl;

//   In a ROOT session, you can do:
//      Root > .L TreeAnalyzer.C
//      Root > TreeAnalyzer t
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

   Long64_t nbytes = 0, nb = 0;
   int d=1;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if (jentry/(d*1000) > 1) {cout << jentry << endl; d++;};  
      
      double TotalSignal = 0;
      // get total signal
      	for (int i=0;i<maxChannel;i++) {
		//if (channel[i]!= 96) 
		if (channel[i] != 11 && channel[i] != 12 && channel[i] != 13 && channel[i] != 14 && channel[i] != 15 && channel[i] != 16 && channel[i] != 96)
		{
      		if (runNumber != 1) TotalSignal += fCsignal[i];
		if (runNumber == 1) {
			if ( channel[i] > 32) {
				TotalSignal += ABSscale*HADscale*fCsignal[i];
			} else {
				TotalSignal += ABSscale*fCsignal[i];
			}
		}
		}
      	}
      
      // 900 GeV data
      if (cms == 900) {
      		if (runNumber == 124020 || runNumber == 124022 || runNumber == 124023 || 
          	    runNumber == 124024 || runNumber == 124027 || runNumber == 124030) {
      
      			nEvents += 1;
      
      			for (int i=0;i<224;i++) {
			if (channel[i] != 11 && channel[i] != 12 && channel[i] != 13 && channel[i] != 14 && channel[i] != 15 && channel[i] != 16 && channel[i] != 96)
		        //if (channel[i] != 96)
			{
			ChannelMean[i] += fCsignal[i];      		
      			}
			}
      
   
      			h_eflow->Fill(TotalSignal);
      			if (isPFDijet == 1) h_eflowPFDijet->Fill(TotalSignal);
			if (isPFInclusive == 1) h_eflowPFInclusive->Fill(TotalSignal);
      		}
      }	
      
      // 2360 data
      if (cms == 2360) {
      		
     		if (runNumber == 124120) {
      
      			nEvents += 1;
      
      			for (int i=0;i<224;i++) {
			if (channel[i] != 11 && channel[i] != 12 && channel[i] != 13 && channel[i] != 14 && channel[i] != 15 && channel[i] != 16 && channel[i] != 96)
		        //if (channel[i] != 96)
			{
			ChannelMean[i] += fCsignal[i];      		
      			}
			}
      
   
      			h_eflow->Fill(TotalSignal);
      			if (isPFDijet == 1) h_eflowPFDijet->Fill(TotalSignal);
			if (isPFInclusive == 1) h_eflowPFInclusive->Fill(TotalSignal);
      		}
      }	
      
      
      
      // 900 GeV or 2360 MC
      if (runNumber == 1) {
      
        nMCEvents += 1;
      
      	for (int i=0;i<224;i++) {
	         if (channel[i] != 11 && channel[i] != 12 && channel[i] != 13 && channel[i] != 14 && channel[i] != 15 && channel[i] != 16
		 && channel[i] != 96)
		 //if (channel[i] != 96)
		 {
		 if (channel[i] > 32) { 
		 	ChannelMeanMC[i] += ABSscale*HADscale*fCsignal[i];   
		 } else {
		 	ChannelMeanMC[i] += ABSscale*fCsignal[i];
		 }
		 }   		
      	}
      
   
      	hMC_eflow->Fill(TotalSignal);
      	if (isPFDijet == 1) hMC_eflowPFDijet->Fill(TotalSignal);
	if (isPFInclusive == 1) hMC_eflowPFInclusive->Fill(TotalSignal);
      }	
      
      // select 900 GeV runs for data
      if (runNumber == 124020) {
      		nEvents_run124020 += 1;
      		h900run124020_eflow->Fill(TotalSignal);
		if (isPFDijet == 1) h900run124020_eflowPFDijet->Fill(TotalSignal);
		if (isPFInclusive == 1) h900run124020_eflowPFInclusive->Fill(TotalSignal);
      }
      if (runNumber == 124022) {
      		nEvents_run124022 += 1;
      		h900run124022_eflow->Fill(TotalSignal);
		if (isPFDijet == 1) h900run124022_eflowPFDijet->Fill(TotalSignal);
		if (isPFInclusive == 1) h900run124022_eflowPFInclusive->Fill(TotalSignal);
      }
      if (runNumber == 124023) {
      		nEvents_run124023 += 1;
      		h900run124023_eflow->Fill(TotalSignal);
		if (isPFDijet == 1) h900run124023_eflowPFDijet->Fill(TotalSignal);
		if (isPFInclusive == 1) h900run124023_eflowPFInclusive->Fill(TotalSignal);
      }
      if (runNumber == 124024) {
      		nEvents_run124024 += 1;
      		h900run124024_eflow->Fill(TotalSignal);
		if (isPFDijet == 1) h900run124024_eflowPFDijet->Fill(TotalSignal);
		if (isPFInclusive == 1) h900run124024_eflowPFInclusive->Fill(TotalSignal);
      }
      if (runNumber == 124027) {
      		nEvents_run124027 += 1;
      		h900run124027_eflow->Fill(TotalSignal);
		if (isPFDijet == 1) h900run124027_eflowPFDijet->Fill(TotalSignal);
		if (isPFInclusive == 1) h900run124027_eflowPFInclusive->Fill(TotalSignal);
      }
      if (runNumber == 124030) {
      		nEvents_run124030 += 1;
      		h900run124030_eflow->Fill(TotalSignal);
		if (isPFDijet == 1) h900run124030_eflowPFDijet->Fill(TotalSignal);
		if (isPFInclusive == 1) h900run124030_eflowPFInclusive->Fill(TotalSignal);
      }
      
      
      
   } // end event loop
   
   
   if (cms == 900) {
   // print out event numbers
   std::cout << "run 124020 has " << nEvents_run124020 << " events" << std::endl;
   std::cout << "run 124022 has " << nEvents_run124022 << " events" << std::endl;
   std::cout << "run 124023 has " << nEvents_run124023 << " events" << std::endl;
   std::cout << "run 124024 has " << nEvents_run124024 << " events" << std::endl;
   std::cout << "run 124027 has " << nEvents_run124027 << " events" << std::endl;
   std::cout << "run 124030 has " << nEvents_run124030 << " events" << std::endl;
   }
   std::cout << "Total number of events in " + cmsstring + " data = " << nEvents << std::endl;
   
   if (cms == 900) {
   // plot energy flows
   TCanvas *c900MBEflow = new TCanvas("c900MBEflow","MB energy flows in CASTOR for 900 GeV runs");
   c900MBEflow->Divide(3,2);
   TVirtualPad *c900MBEflow_p1 = c900MBEflow->cd(1);
   if (log == 1) c900MBEflow_p1->SetLogy();
   h900run124020_eflow->Draw("e");
   TVirtualPad *c900MBEflow_p2 = c900MBEflow->cd(2);
   if (log == 1) c900MBEflow_p2->SetLogy();
   h900run124022_eflow->Draw("e");
   TVirtualPad *c900MBEflow_p3 = c900MBEflow->cd(3);
   if (log == 1) c900MBEflow_p3->SetLogy();
   h900run124023_eflow->Draw("e");
   TVirtualPad *c900MBEflow_p4 = c900MBEflow->cd(4);
   if (log == 1) c900MBEflow_p4->SetLogy();
   h900run124024_eflow->Draw("e");
   TVirtualPad *c900MBEflow_p5 = c900MBEflow->cd(5);
   if (log == 1) c900MBEflow_p5->SetLogy();
   h900run124027_eflow->Draw("e");
   TVirtualPad *c900MBEflow_p6 = c900MBEflow->cd(6);
   if (log == 1) c900MBEflow_p6->SetLogy();
   h900run124030_eflow->Draw("e");
   if (savePlots == 1) c900MBEflow->SaveAs("./TreeAnalyzer/Eflowplots/MBEflow900GeV.eps");
   
   
   TCanvas *c900PFDijetEflow = new TCanvas("c900PFDijetEflow","PFDijet energy flows in CASTOR for 900 GeV runs");
   c900PFDijetEflow->Divide(3,2);
   TVirtualPad *c900PFDijetEflow_p1 = c900PFDijetEflow->cd(1);
   if (log == 1) c900PFDijetEflow_p1->SetLogy();
   h900run124020_eflowPFDijet->Draw("e");
   TVirtualPad *c900PFDijetEflow_p2 = c900PFDijetEflow->cd(2);
   if (log == 1) c900PFDijetEflow_p2->SetLogy();
   h900run124022_eflowPFDijet->Draw("e");
   TVirtualPad *c900PFDijetEflow_p3 = c900PFDijetEflow->cd(3);
   if (log == 1) c900PFDijetEflow_p3->SetLogy();
   h900run124023_eflowPFDijet->Draw("e");
   TVirtualPad *c900PFDijetEflow_p4 = c900PFDijetEflow->cd(4);
   if (log == 1) c900PFDijetEflow_p4->SetLogy();
   h900run124024_eflowPFDijet->Draw("e");
   TVirtualPad *c900PFDijetEflow_p5 = c900PFDijetEflow->cd(5);
   if (log == 1) c900PFDijetEflow_p5->SetLogy();
   h900run124027_eflowPFDijet->Draw("e");
   TVirtualPad *c900PFDijetEflow_p6 = c900PFDijetEflow->cd(6);
   if (log == 1) c900PFDijetEflow_p6->SetLogy();
   h900run124030_eflowPFDijet->Draw("e");
   if (savePlots == 1) c900PFDijetEflow->SaveAs("./TreeAnalyzer/Eflowplots/PFDijetEflow900GeV.eps");
   
    TCanvas *c900PFInclusiveEflow = new TCanvas("c900PFInclusiveEflow","PFInclusive energy flows in CASTOR for 900 GeV runs");
   c900PFInclusiveEflow->Divide(3,2);
   TVirtualPad *c900PFInclusiveEflow_p1 = c900PFInclusiveEflow->cd(1);
   if (log == 1) c900PFInclusiveEflow_p1->SetLogy();
   h900run124020_eflowPFInclusive->Draw("e");
   TVirtualPad *c900PFInclusiveEflow_p2 = c900PFInclusiveEflow->cd(2);
   if (log == 1) c900PFInclusiveEflow_p2->SetLogy();
   h900run124022_eflowPFInclusive->Draw("e");
   TVirtualPad *c900PFInclusiveEflow_p3 = c900PFInclusiveEflow->cd(3);
   if (log == 1) c900PFInclusiveEflow_p3->SetLogy();
   h900run124023_eflowPFInclusive->Draw("e");
   TVirtualPad *c900PFInclusiveEflow_p4 = c900PFInclusiveEflow->cd(4);
   if (log == 1) c900PFInclusiveEflow_p4->SetLogy();
   h900run124024_eflowPFInclusive->Draw("e");
   TVirtualPad *c900PFInclusiveEflow_p5 = c900PFInclusiveEflow->cd(5);
   if (log == 1) c900PFInclusiveEflow_p5->SetLogy();
   h900run124027_eflowPFInclusive->Draw("e");
   TVirtualPad *c900PFInclusiveEflow_p6 = c900PFInclusiveEflow->cd(6);
   if (log == 1) c900PFInclusiveEflow_p6->SetLogy();
   h900run124030_eflowPFInclusive->Draw("e");
   if (savePlots == 1) c900PFInclusiveEflow->SaveAs("./TreeAnalyzer/Eflowplots/PFInclusiveEflow900GeV.eps");
   
   TCanvas *c900MBEflow_all = new TCanvas("c900MBEflow_all","MB energy flows in CASTOR in all 900GeV runs");
   c900MBEflow_all->Divide(1,1);
   TVirtualPad *c900MBEflow_all_p1 = c900MBEflow_all->cd(1);
   if (log == 1) c900MBEflow_all_p1->SetLogy();
   h900run124020_eflow->SetLineColor(kBlack);
   h900run124020_eflow->Draw("e");
   h900run124022_eflow->Scale(h900run124020_eflow->Integral()/h900run124022_eflow->Integral());
   h900run124022_eflow->SetLineColor(kGreen);
   h900run124022_eflow->Draw("samee");
   h900run124023_eflow->Scale(h900run124020_eflow->Integral()/h900run124023_eflow->Integral());
   h900run124023_eflow->SetLineColor(kBlue);
   h900run124023_eflow->Draw("samee");
   h900run124024_eflow->Scale(h900run124020_eflow->Integral()/h900run124024_eflow->Integral());
   h900run124024_eflow->SetLineColor(kRed);
   h900run124024_eflow->Draw("samee");
   h900run124027_eflow->Scale(h900run124020_eflow->Integral()/h900run124027_eflow->Integral());
   h900run124027_eflow->SetLineColor(kYellow);
   h900run124027_eflow->Draw("samee");
   h900run124030_eflow->Scale(h900run124020_eflow->Integral()/h900run124030_eflow->Integral());
   h900run124030_eflow->SetLineColor(kOrange);
   h900run124030_eflow->Draw("samee");
   if (savePlots == 1) c900MBEflow_all->SaveAs("./TreeAnalyzer/Eflowplots/MBEflow900GeV_allruns.eps");
   }
   
   std::cout << "debug 1" << std::endl;
   
   TCanvas *cEflow_all = new TCanvas("cEflow_all","Energy flows in CASTOR for all "+cmsstring+" GeV runs");
   cEflow_all->Divide(1,1);
   TVirtualPad *cEflow_all_p1 = cEflow_all->cd(1);
   if (log == 1) cEflow_all_p1->SetLogy();
   hMC_eflow->SetTitle("MB energy flow in CASTOR " + cmsstring + "GeV");
   hMC_eflow->Draw("");
   h_eflow->Scale(hMC_eflow->Integral()/h_eflow->Integral());
   h_eflow->Draw("samee");
   /*
   TVirtualPad *cEflow_all_p2 = cEflow_all->cd(2);
   if (log == 1) cEflow_all_p2->SetLogy();
   hMC_eflowPFDijet->SetTitle("QCD dijet energy flow in CASTOR " + cmsstring + "GeV");
   hMC_eflowPFDijet->Draw("");
   h_eflowPFDijet->Scale(hMC_eflowPFDijet->Integral()/h_eflowPFDijet->Integral());
   h_eflowPFDijet->Draw("samee");
   TVirtualPad *cEflow_all_p3 = cEflow_all->cd(3);
   if (log == 1) cEflow_all_p3->SetLogy();
   hMC_eflowPFInclusive->SetTitle("QCD inclusive energy flow in CASTOR " + cmsstring + "GeV");
   hMC_eflowPFInclusive->Draw("");
   h_eflowPFInclusive->Scale(hMC_eflowPFInclusive->Integral()/h_eflowPFInclusive->Integral());
   h_eflowPFInclusive->Draw("samee");
   */
   if (savePlots == 1) cEflow_all->SaveAs("./TreeAnalyzer/Eflowplots/Eflow"+cmsstring+"GeV_HADscale"+HADscalestring+".eps");
   
   std::cout << "debug 2" << std::endl;
   
   // get mean response for each channel
   for (int i=0;i<224;i++) {
		ChannelMean[i] = ChannelMean[i]/nEvents;  
		ChannelMeanMC[i] = ChannelMeanMC[i]/nMCEvents;    		
   }
   
   TCanvas *cChannelMeans = new TCanvas("cChannelMeans","Mean response of the channels for "+cmsstring+" GeV");
   cChannelMeans->Divide(1,1);
   for (int i=0;i<224;i++) {
   	hChannelMeans->SetBinContent(i+1,ChannelMean[i]);
	//hChannelMeans->SetBinError(i+1,getMeanError(ChannelMean[i]));
	hChannelMeansMC->SetBinContent(i+1,ChannelMeanMC[i]);
   }
   if (cms == 900) hChannelMeansMC->GetYaxis()->SetRangeUser(0,250);
   if (cms == 2360) hChannelMeansMC->GetYaxis()->SetRangeUser(0,550);
   hChannelMeansMC->SetTitle("Mean response in the channels for " + cmsstring + "GeV");
   hChannelMeansMC->Draw("");
   hChannelMeans->SetMarkerStyle(7);
   hChannelMeans->Draw("samep");
   if (savePlots == 1) cChannelMeans->SaveAs("./TreeAnalyzer/Eflowplots/channels"+cmsstring+"GeV_HADscale"+HADscalestring+".eps");
   
   std::cout << "debug 3" << std::endl;
}

void TreeAnalyzer::plotChannelDistributions(int savePlots, int nModules, int jetsample, int cms,double HADscale, double ABSscale) {

  ////////////////////
  //  set style
  ////////////////////
  gROOT  -> SetStyle("Plain");
  gStyle -> SetMarkerStyle(1);
  gStyle -> SetMarkerSize(1);
  gStyle -> SetTextSize(1);
  gStyle -> SetOptStat("eMR");//"iourmen");
  //gStyle -> SetOptStat("");
  gStyle -> SetLineWidth(1.1);//gStyle->GetLineWidth()*1.5); // 2
  gStyle -> SetHistLineWidth(1.4);//gStyle->GetHistLineWidth()*1.5);// 2
  gStyle -> SetPadLeftMargin(0.15);
  gStyle -> SetPadRightMargin(0.1);
  gStyle -> SetPadBottomMargin(0.15);
  gStyle -> SetPadTopMargin(0.11);
  gStyle -> SetEndErrorSize(5);
  gStyle -> SetCanvasBorderSize(2);
  gStyle -> SetHistFillColor(kGray);
  gStyle -> SetHistMinimumZero(kTRUE);
  gStyle -> SetTitleOffset(1.5,"y");
  gStyle -> SetLegendBorderSize(0);
  gROOT  -> ForceStyle();

  std::cout << "==== Parameter settings ====" << std::endl;
// set input parameters and show them
if (savePlots == 1) std::cout << "Your plots will be saved in ./TreeAnalyzer/ChannelDistributions" << std::endl;
if (savePlots == 0) std::cout << "Your plots will not be saved" << std::endl;
//if (log == 1) std::cout << "Your plots will be shown in log scale" << std::endl;
//if (log == 0) std::cout << "Your plots will be shown in linear scale" << std::endl;

int maxChannel = nModules*16;
std::cout << "Using " << nModules << " modules for the energy flow" << std::endl;
std::cout << "this means we use the first " << maxChannel << " channels of CASTOR" << std::endl;
if (jetsample == 2) std::cout << "Dijet samples will be used for calculations" << std::endl;
if (jetsample == 1) std::cout << "Inclusive samples will be used for calculations" << std::endl;
std::cout << "Data and MC will be analyzed as having a cms of " << cms << std::endl;
if (HADscale != 0) std::cout << "The MC HAD section in CASTOR will be scaled with a factor " << HADscale << std::endl;
if (HADscale == 0) std::cout << "The MC HAD scale is set to 0, you will end up with crazy results" << std::endl;
if (ABSscale != 0) std::cout << "The MC signal in CASTOR will be scaled with a factor " << ABSscale << std::endl;
if (ABSscale == 0) std::cout << "The MC scale is set to 0, you will end up with crazy results" << std::endl;
std::cout << "==== ================== ====" << std::endl;

// define histograms

TString cmsstring = "1";
if (cms == 900) {cmsstring = "900";}
if (cms == 2360) {cmsstring = "2360";}
if (cms == 7000) {cmsstring = "7000";}
Char_t HADscalestring[1];
sprintf(HADscalestring,"%6.4f",HADscale);

TH1D *hEChannel[maxChannel];
TH1D *hEChannelQCD[maxChannel];
Char_t htitle[maxChannel];
Char_t hname[maxChannel];
Char_t htitleQCD[maxChannel];
Char_t hnameQCD[maxChannel];

TH1D *hEChannelMC[maxChannel];
TH1D *hEChannelQCDMC[maxChannel];
Char_t htitleMC[maxChannel];
Char_t hnameMC[maxChannel];
Char_t htitleQCDMC[maxChannel];
Char_t hnameQCDMC[maxChannel];

for (int i=0;i<maxChannel;i++) {
	sprintf(hname,"hEChannel_%d",i);
	sprintf(htitle,"MB Energy in CASTOR channel %d",i+1);
	sprintf(hnameQCD,"hEChannelQCD_%d",i);
	sprintf(htitleQCD,"QCD Energy in CASTOR channel %d",i+1);
	hEChannel[i] = new TH1D(hname,htitle,105,-2000,50000);
	hEChannelQCD[i] = new TH1D(hnameQCD,htitleQCD,105,-2000,50000);
	
	sprintf(hnameMC,"hEChannelMC_%d",i);
	sprintf(htitleMC,"MC MB Energy in CASTOR channel %d",i+1);
	sprintf(hnameQCDMC,"hEChannelQCDMC_%d",i);
	sprintf(htitleQCDMC,"MC QCD Energy in CASTOR channel %d",i+1);
	hEChannelMC[i] = new TH1D(hnameMC,htitleMC,105,-2000,50000);
	hEChannelQCDMC[i] = new TH1D(hnameQCDMC,htitleQCDMC,105,-2000,50000);
}

double ratios[maxChannel];
double ratios_error[maxChannel];
double ratiosMC[maxChannel];
double ratiosMC_error[maxChannel];
TString jetsamplestring;
if (jetsample == 1) jetsamplestring = "inclusive";
if (jetsample == 2) jetsamplestring = "dijet";
TH1D *hRatios = new TH1D("hRatios","#alpha_{"+jetsamplestring+"} per channel for "+cmsstring+"GeV data;Channel;#alpha_{"+jetsamplestring+"}",maxChannel,1,maxChannel+1);
TH1D *hRatiosMC = new TH1D("hRatiosMC","#alpha_{"+jetsamplestring+"} per channel for "+cmsstring+"GeV MC;Channel;#alpha_{"+jetsamplestring+"}",maxChannel,1,maxChannel+1);
hRatios->Sumw2();
hRatiosMC->Sumw2();



std::cout << "Start variables are set" << std::endl;
std::cout << "Starting event loop now" << std::endl;


   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   int d=1;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if (jentry/(d*1000) > 1) {cout << jentry << endl; d++;};  
      
      double TotalSignal = 0;
      // get total signal
      	for (int i=0;i<maxChannel;i++) {
		//if (channel[i] != 11 && channel[i] != 12 && channel[i] != 13 && channel[i] != 14 && channel[i] != 15 && channel[i] != 16)
		//{
		if (cms == 900) {
		if (runNumber == 124020 || runNumber == 124022 || runNumber == 124023 || 
          	    runNumber == 124024 || runNumber == 124027 || runNumber == 124030) {
		    	hEChannel[i]->Fill(fCsignal[i]);
			if (jetsample == 1 && isPFInclusive == 1) hEChannelQCD[i]->Fill(fCsignal[i]);
			if (jetsample == 2 && isPFDijet == 1) hEChannelQCD[i]->Fill(fCsignal[i]);
		} else {
			if (channel[i] > 32) {
				hEChannelMC[i]->Fill(ABSscale*HADscale*fCsignal[i]);
				if (jetsample == 1 && isPFInclusive == 1) hEChannelQCDMC[i]->Fill(ABSscale*HADscale*fCsignal[i]);
				if (jetsample == 2 && isPFDijet == 1) hEChannelQCDMC[i]->Fill(ABSscale*HADscale*fCsignal[i]);
			} else {
				hEChannelMC[i]->Fill(ABSscale*fCsignal[i]);
				if (jetsample == 1 && isPFInclusive == 1) hEChannelQCDMC[i]->Fill(ABSscale*fCsignal[i]);
				if (jetsample == 2 && isPFDijet == 1) hEChannelQCDMC[i]->Fill(ABSscale*fCsignal[i]);
			}
		}
		}
		if (cms == 2360) {  
      		if (runNumber == 124120) {
      			hEChannel[i]->Fill(fCsignal[i]);
			if (jetsample == 1 && isPFInclusive == 1) hEChannelQCD[i]->Fill(fCsignal[i]);
			if (jetsample == 2 && isPFDijet == 1) hEChannelQCD[i]->Fill(fCsignal[i]);
		} else {
			if (channel[i] > 32) {
				hEChannelMC[i]->Fill(ABSscale*HADscale*fCsignal[i]);
				if (jetsample == 1 && isPFInclusive == 1) hEChannelQCDMC[i]->Fill(ABSscale*HADscale*fCsignal[i]);
				if (jetsample == 2 && isPFDijet == 1) hEChannelQCDMC[i]->Fill(ABSscale*HADscale*fCsignal[i]);
			} else {
				hEChannelMC[i]->Fill(ABSscale*fCsignal[i]);
				if (jetsample == 1 && isPFInclusive == 1) hEChannelQCDMC[i]->Fill(ABSscale*fCsignal[i]);
				if (jetsample == 2 && isPFDijet == 1) hEChannelQCDMC[i]->Fill(ABSscale*fCsignal[i]);
			}
		}
		}
		//}
      	}
      
      
   } // end event loop
   
   
   /*
   // plot all channel distributions in 6 canvases
   TCanvas *cChannelDistributions[6];
   Char_t ctitle[6];
   Char_t cname[6];
   
   for (int i=0;i<6;i++) {
   	sprintf(cname,"cChannelDistributions_%d",i+1);
	sprintf(ctitle,"CASTOR channel distributions in module %d",i+1);
   	cChannelDistributions[i] = new TCanvas(cname,ctitle);
   	cChannelDistributions[i]->Divide(4,4);
   
   }
   
   for (int j=0;j < 6;j++) {
   	for (int i=16*j;i < 16*(j+1);i++) {
   		TVirtualPad *cCD_p1 = cChannelDistributions[j]->cd(i+1 - 16*j);
		cCD_p1->SetLogy();
		hEChannelMC[i]->Draw("");
		hEChannel[i]->Scale(hEChannelMC[i]->Integral()/hEChannel[i]->Integral());
		hEChannel[i]->Draw("samee");
   	}
   }
   
   Char_t filename[6];
   for (int i=0;i<6;i++) {
   	sprintf(filename,"./TreeAnalyzer/ChannelDistributions/ChannelDistributions_MB"+cmsstring+"GeV_module%d.eps",i+1);
   	if (savePlots == 1) cChannelDistributions[i]->SaveAs(filename);
   }
   */
   
   // calculate ratios per channel
   for (int i=0;i<maxChannel;i++) {
   	ratios[i] = hEChannelQCD[i]->GetMean()/hEChannel[i]->GetMean();
	ratios_error[i] = getRatioError(hEChannel[i],hEChannelQCD[i]);
	
	ratiosMC[i] = hEChannelQCDMC[i]->GetMean()/hEChannelMC[i]->GetMean();
	ratiosMC_error[i] = getRatioError(hEChannelMC[i],hEChannelQCDMC[i]);
	
	
   }
   
   for (int i=0;i<maxChannel;i++) {
	hRatios->SetBinContent(i+1,ratios[i]);
	hRatios->SetBinError(i+1,ratios_error[i]);
	hRatiosMC->SetBinContent(i+1,ratiosMC[i]);
	hRatiosMC->SetBinError(i+1,ratiosMC_error[i]);
	
   }
   
   
   // calculate average ratios manually
   double mean_ratio = 0;
   double mean_ratioMC = 0;
   double sum_errors = 0;
   double sum_errorsMC = 0;
   for (int i=0;i<maxChannel;i++) {
   	mean_ratio = mean_ratio + ratios[i]/ratios_error[i];
	mean_ratioMC = mean_ratioMC + ratiosMC[i]/ratiosMC_error[i];
	sum_errors = sum_errors + 1./ratios_error[i];
	sum_errorsMC = sum_errorsMC + 1./ratiosMC_error[i];
   }
   mean_ratio = mean_ratio/sum_errors;
   mean_ratioMC = mean_ratioMC/sum_errorsMC;
   
   std::cout << "Mean ratio = " << mean_ratio << std::endl;
   std::cout << "Mean ratio MC = " << mean_ratioMC << std::endl;
   
   //TString cte = mean_ratio.c_str();
   //TString cteMC = mean_ratioMC.c_str();
   Char_t cte[2];
   sprintf(cte,"%6.4f",mean_ratio);
   TF1 *fFit = new TF1("fFit",cte,0,97);
   
   // plot ratios per channel
   TCanvas *cRatios = new TCanvas("cRatios","QCD/MB ratios for "+cmsstring+"GeV data");
   cRatios->Divide(1,1);
   cRatios->cd(1);
   hRatios->Draw("e");
   fFit->Draw("same");
   //hRatios->Fit("pol0","VMEF","",1,96);
   
   Char_t cteMC[2];
   sprintf(cteMC,"%6.4f",mean_ratioMC);
   TF1 *fFitMC = new TF1("fFitMC",cteMC,0,97);
   
   TCanvas *cRatiosMC = new TCanvas("cRatiosMC","QCD/MB ratios for "+cmsstring+"GeV MC");
   cRatiosMC->Divide(1,1);
   cRatiosMC->cd(1);
   hRatiosMC->Draw("e");
   fFitMC->Draw("same");
   //hRatiosMC->Fit("pol0","VMEF","",1,96);
   
   
   /*
   // get fit results
   TF1 *fit = hRatios->GetFunction("pol0"); 
   Double_t par0 = fit->GetParameter(0);
   Double_t par0_error = fit->GetParError(0);
   Double_t chi2 = fit->GetChisquare();
   Double_t ndf = fit->GetNDF();
   std::cout << "fit parameter = " << par0 << " +- " << par0_error << std::endl;
   std::cout << "chi2/ndf = " << chi2/ndf << std::endl;
   
   TF1 *fitMC = hRatiosMC->GetFunction("pol0"); 
   Double_t par0MC = fitMC->GetParameter(0);
   Double_t par0MC_error = fitMC->GetParError(0);
   Double_t chi2MC = fitMC->GetChisquare();
   Double_t ndfMC = fitMC->GetNDF();
   std::cout << "fit parameter MC = " << par0MC << " +- " << par0MC_error << std::endl;
   std::cout << "chi2/ndf MC = " << chi2MC/ndfMC << std::endl;
   */
   
   
   TH1D *hpull = new TH1D("hpull","Pull distributions of "+cmsstring+" GeV data;(#alpha_{i}-<#alpha>)/#sigma_{#alpha_{i}};Events",12,-6,6);
   TH1D *hpullMC = new TH1D("hpullMC","Pull distributions of "+cmsstring+" GeV MC;(#alpha_{i}-<#alpha>)/#sigma_{#alpha_{i}};Events",12,-6,6);
   
   double pull = 0;
   double pullMC = 0;
   
   for (int i=0;i<maxChannel;i++) {
   	pull = pull + (ratios[i]-mean_ratio)/ratios_error[i];
	pullMC = pullMC + (ratiosMC[i]-mean_ratioMC)/ratiosMC_error[i];
   	hpull->Fill((ratios[i]-mean_ratio)/ratios_error[i]);
	hpullMC->Fill((ratiosMC[i]-mean_ratioMC)/ratiosMC_error[i]);
   }
   
   pull = pull/maxChannel;
   pullMC = pullMC/maxChannel;
   
   std::cout << " pull mean = " << pull << std::endl;
   std::cout << " pull MC mean = " << pullMC << std::endl;
   
   double pullrms = 0;
   double pullMCrms = 0;
   
   for (int i=0;i<maxChannel;i++) {
   	pullrms = pullrms + pow((ratios[i]-mean_ratio)/ratios_error[i] - pull,2);
	pullMCrms = pullMCrms + pow((ratiosMC[i]-mean_ratioMC)/ratiosMC_error[i] - pullMC,2);
   }
   
   pullrms = pullrms/(maxChannel-1);
   pullMCrms = pullMCrms/(maxChannel-1);
   
   pullrms = sqrt(pullrms);
   pullMCrms = sqrt(pullMCrms);
   
   std::cout << " pull rms = " << pullrms << std::endl;
   std::cout << " pull MC rms = " << pullMCrms << std::endl;
   
   TCanvas *cPulls = new TCanvas("cPulls","Pull distributions of "+cmsstring+" GeV ratios");
   cPulls->Divide(2,1);
   cPulls->cd(1);
   hpull->Draw();
   cPulls->cd(2);
   hpullMC->Draw();

}

void TreeAnalyzer::calculateABSscale(int savePlots, int nModules, int cms,double HADscale) {

  ////////////////////
  //  set style
  ////////////////////
  gROOT  -> SetStyle("Plain");
  gStyle -> SetMarkerStyle(1);
  gStyle -> SetMarkerSize(1);
  gStyle -> SetTextSize(1);
  gStyle -> SetOptStat("eMR");//"iourmen");
  //gStyle -> SetOptStat("");
  gStyle -> SetLineWidth(1.1);//gStyle->GetLineWidth()*1.5); // 2
  gStyle -> SetHistLineWidth(1.4);//gStyle->GetHistLineWidth()*1.5);// 2
  gStyle -> SetPadLeftMargin(0.15);
  gStyle -> SetPadRightMargin(0.1);
  gStyle -> SetPadBottomMargin(0.15);
  gStyle -> SetPadTopMargin(0.11);
  gStyle -> SetEndErrorSize(5);
  gStyle -> SetCanvasBorderSize(2);
  gStyle -> SetHistFillColor(kGray);
  gStyle -> SetHistMinimumZero(kTRUE);
  gStyle -> SetTitleOffset(1.5,"y");
  gStyle -> SetLegendBorderSize(0);
  gROOT  -> ForceStyle();

  std::cout << "==== Parameter settings ====" << std::endl;
// set input parameters and show them
if (savePlots == 1) std::cout << "Your plots will be saved in ./TreeAnalyzer/ChannelDistributions" << std::endl;
if (savePlots == 0) std::cout << "Your plots will not be saved" << std::endl;
//if (log == 1) std::cout << "Your plots will be shown in log scale" << std::endl;
//if (log == 0) std::cout << "Your plots will be shown in linear scale" << std::endl;

int maxChannel = nModules*16;
std::cout << "Using " << nModules << " modules for the energy flow" << std::endl;
std::cout << "this means we use the first " << maxChannel << " channels of CASTOR" << std::endl;

std::cout << "Data and MC will be analyzed as having a cms of " << cms << std::endl;
if (HADscale != 0) std::cout << "The MC HAD section in CASTOR will be scaled with a factor " << HADscale << std::endl;
if (HADscale == 0) std::cout << "The MC HAD scale is set to 0, you will end up with crazy results" << std::endl;
std::cout << "==== ================== ====" << std::endl;


double ChannelMean[maxChannel];
double ChannelMeanMC[maxChannel];

for (int i=0;i<maxChannel;i++) {
	ChannelMean[i] = 0;
	ChannelMeanMC[i] = 0;
}

int nEvents = 0;
int nMCEvents = 0;

std::cout << "Start variables are set" << std::endl;
std::cout << "Starting event loop now" << std::endl;


   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   int d=1;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if (jentry/(d*1000) > 1) {cout << jentry << endl; d++;}; 
      
      if (runNumber != 1) nEvents += 1;
      if (runNumber == 1) nMCEvents +=1;
      
      for (int i=0;i<maxChannel;i++) {
      		if (channel[i] != 11 && channel[i] != 12 && channel[i] != 13 && channel[i] != 14 && channel[i] != 15 && channel[i] != 16)
		{
      		if (runNumber != 1) {
      			ChannelMean[i] += fCsignal[i];
		} else {
			if (channel[i] > 32) {
				ChannelMeanMC[i] += HADscale*fCsignal[i];
			} else {
				ChannelMeanMC[i] += fCsignal[i];
			}
		}
		}
      } 
      
   } // end event loop
   
   double ChannelMeanRatio[maxChannel];
   double MeanRatio = 0;
   int usedChannels = 0;
   for (int i=0;i<maxChannel;i++) {
   	ChannelMean[i] = ChannelMean[i]/nEvents;
	ChannelMeanMC[i] = ChannelMeanMC[i]/nMCEvents;
   	ChannelMeanRatio[i] = 0;
   	if ( ChannelMeanMC[i] != 0) ChannelMeanRatio[i] = ChannelMean[i]/ChannelMeanMC[i];
	if ( ChannelMeanRatio[i] != 0) MeanRatio += ChannelMeanRatio[i];
	if (ChannelMeanRatio[i] != 0) usedChannels += 1;
   }
   
    MeanRatio = MeanRatio/usedChannels;
    
    std::cout << "Mean ratio DATA/MC = " << MeanRatio << std::endl; 
    
    TH1D *hChannelMean = new TH1D("hChannelMean","Mean signal in each CASTOR channel",maxChannel,1,maxChannel+1);
    TH1D *hChannelMeanMC = new TH1D("hChannelMeanMC","Mean MC signal in each CASTOR channel",maxChannel,1,maxChannel+1);
    TH1D *hChannelMeanRatio = new TH1D("hChannelMeanRatio","Mean DATA/MC ratio in each CASTOR channel",maxChannel,1,maxChannel+1);
    
    for (int i=0;i<maxChannel;i++) {
    	hChannelMean->SetBinContent(i+1,ChannelMean[i]);
	hChannelMeanMC->SetBinContent(i+1,ChannelMeanMC[i]);
	hChannelMeanRatio->SetBinContent(i+1,ChannelMeanRatio[i]);
    }
    
    TCanvas *cChannelMeans = new TCanvas("cChannelMeans","Channel Means");
    cChannelMeans->cd(1);
    hChannelMeanMC->Draw("hist");
    hChannelMean->SetMarkerStyle(7);
    hChannelMean->Draw("samep");
    
    
    TCanvas *cChannelRatios = new TCanvas("cChannelRatios","Channel Ratios");
    cChannelRatios->cd(1);
    hChannelMeanRatio->GetYaxis()->SetRangeUser(0,1.5);
    hChannelMeanRatio->Draw();
    Char_t mean[20];
    sprintf(mean,"%6.4f",MeanRatio);
    TF1 *fMeanRatio = new TF1("fMeanRatio",mean,1,maxChannel);
    fMeanRatio->Draw("same");

}

