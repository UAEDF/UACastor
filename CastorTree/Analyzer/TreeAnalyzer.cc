
#include "TreeAnalyzer.h"

//STANDARD ROOT INCLUDES
#include <TROOT.h>
#include <TH1.h>
#include <TH2.h>
#include <TProfile.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <TChain.h>
#include <TChainElement.h>
#include <TDirectory.h>
#include <TMath.h>
#include <TBranch.h>

//STANDARD C++ INCLUDES
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>

// own classes includes
#include "../src/MyCastorRecHit.h"
#include "../src/MyCastorDigi.h"
#include "../src/MyCastorTower.h"
#include "../src/MyCastorJet.h"
#include "../src/MyEvtId.h"
#include "../src/MyDiJet.h"
#include "../src/MyVertex.h"
#include "../src/MyHLTrig.h"
#include "../src/MyL1Trig.h"
#include "../src/MyJet.h"

TreeAnalyzer::TreeAnalyzer() { }

TreeAnalyzer::~TreeAnalyzer() { }


void TreeAnalyzer::Loop(TString inputdir, TObjArray* filelist, bool isData, double cmenergy) {
	
	
	using namespace std;
	int it = 0;
	int totalevents = 0;
	
	/////////////////////////////////////
	// Define all histograms
	/////////////////////////////////////
	
	// castor rechit histos
	TH1F *hRecHit_energy = new TH1F("hRecHit_energy","RecHit energy",100,-200,30000);
	TH1F *hRecHit_energy_clean = new TH1F("hRecHit_energy_clean","RecHit energy",100,-200,30000);
	TH1F *hRecHit_time = new TH1F("hRecHit_time","RecHit time",105,-100,50); // for data -5,50
	TH1F *hNRecHits = new TH1F("hNRecHits","Number of Rechits/event",225,0,225);
	TH1F *hRecHit_fC = new TH1F("hRecHit_fC","RecHit fC",100,-10000,900000);
	TH1F *hRecHit_module = new TH1F("hRecHit_module","RecHits: energy weighted modules",14,1,15);
	TH1F *hRecHit_sector = new TH1F("hRecHit_sector","RecHits: energy weighted sectors",16,1,17);
	TH1F *hRecHit_channel = new TH1F("hRecHit_channel","RecHits: energy weighted channels",225,0,225);
	TH1F *hRecHit_totalenergy = new TH1F("hRecHit_totalenergy","total rechit GeV distribution",100,-2000,50000);
	
	TH1F *hRecHit_WeightedTime = new TH1F("hRecHit_WeightedTime","Energy(fC) weighted rechit time",100,-100,50); // for data -5,50 
	TH2F *h2RecHit_EvsT = new TH2F("h2RecHit_EvsT","RecHit energy(fC) vs time",105,-5,50,100,-500,80000);
	
	TH2F *hLS = new TH2F("hLS","LS distribution",303,193,496,224,1,225);
	TH2F *hLSWeighted = new TH2F("hLSWeighted","LS distribution weighted with energy",303,193,496,224,1,225);
	
	// eflow histograms
	
	// ranges for different CMS energies & data-MC
	double min = 0;
	double max = 0;
	double channelmin = 0;
	double channelmax = 0;
	double nBins = 0;
	double ptcut = 8;
	double lumimax = 0;
	double lumiBXmax = 0;
	int nLumiBins = 0;
	
	
	unsigned int Nruns = 0;
	if (cmenergy == 900) {Nruns = 2; nLumiBins = 10;}
	if (cmenergy == 2760) {Nruns = 9; nLumiBins = 10;}
	if (cmenergy == 7000) {Nruns = 8; nLumiBins = 10;}
	unsigned int runs[Nruns];
	TH1F *heflow_averagePUperRun[Nruns];
	TH1F *heflow_perRun[Nruns];
	TH1F *heflow_AllV_perRun[Nruns];
	double LumiBins[nLumiBins];
	
	if (cmenergy == 900) {
		// ranges for 900 GeV - use this
		// data
		min = -2000;
		max = 60000;
		channelmin = -200;
		channelmax = 40000;
		nBins = 124;
		ptcut = 8;
		lumimax = 0.1;
		lumiBXmax = 0.0005;
		LumiBins[0] = 0.00000;
		LumiBins[1] = 0.00005;
		LumiBins[2] = 0.00010;
		LumiBins[3] = 0.00015;
		LumiBins[4] = 0.00020;
		LumiBins[5] = 0.00025;
		LumiBins[6] = 0.00030;
		LumiBins[7] = 0.00035;
		LumiBins[8] = 0.00040;
		LumiBins[9] = 0.00045;
		runs[0] = 134721;
		runs[1] = 134725;
		heflow_averagePUperRun[0] = new TH1F("heflow_averagePUperRun_134721","Average number of vertices 134721",10,0,10);
		heflow_averagePUperRun[1] = new TH1F("heflow_averagePUperRun_134725","Average number of vertices 134725",10,0,10);
		heflow_perRun[0] = new TH1F("heflow_perRun_134721","Energy flow for run 134721",nBins,min,max);
		heflow_perRun[1] = new TH1F("heflow_perRun_134725","Energy flow for run 134725",nBins,min,max);
		heflow_AllV_perRun[0] = new TH1F("heflow_AllV_perRun_134721","Energy flow (1 or more Vtx) for run 134721",nBins,min,max);
		heflow_AllV_perRun[1] = new TH1F("heflow_AllV_perRun_134725","Energy flow (1 or more Vtx) for run 134725",nBins,min,max);
	} else if (cmenergy == 2760) {
        // ranges for 2760 GeV - use this
        // data
        min = -2000;
        max = 120000; // was 100000
        channelmin = -200;
        channelmax = 60000;
        nBins = 244; // was 204
		ptcut = 12;
		lumimax = 10.;
		lumiBXmax = 0.01;
		LumiBins[0] = 0.000;
		LumiBins[1] = 0.001;
		LumiBins[2] = 0.002;
		LumiBins[3] = 0.003;
		LumiBins[4] = 0.004;
		LumiBins[5] = 0.005;
		LumiBins[6] = 0.006;
		LumiBins[7] = 0.007;
		LumiBins[8] = 0.008;
		LumiBins[9] = 0.009;
		runs[0] = 161366;
		runs[1] = 161396;
		runs[2] = 161404;
		runs[3] = 161439;
		runs[4] = 161445;
		runs[5] = 161450;
		runs[6] = 161454;
		runs[7] = 161473;
		runs[8] = 161474;
		heflow_averagePUperRun[0] = new TH1F("heflow_averagePUperRun_161366","Average number of vertices 161366",10,0,10);
		heflow_averagePUperRun[1] = new TH1F("heflow_averagePUperRun_161396","Average number of vertices 161396",10,0,10);
		heflow_averagePUperRun[2] = new TH1F("heflow_averagePUperRun_161404","Average number of vertices 161404",10,0,10);
		heflow_averagePUperRun[3] = new TH1F("heflow_averagePUperRun_161439","Average number of vertices 161439",10,0,10);
		heflow_averagePUperRun[4] = new TH1F("heflow_averagePUperRun_161445","Average number of vertices 161445",10,0,10);
		heflow_averagePUperRun[5] = new TH1F("heflow_averagePUperRun_161450","Average number of vertices 161450",10,0,10);
		heflow_averagePUperRun[6] = new TH1F("heflow_averagePUperRun_161454","Average number of vertices 161454",10,0,10);
		heflow_averagePUperRun[7] = new TH1F("heflow_averagePUperRun_161473","Average number of vertices 161473",10,0,10);
		heflow_averagePUperRun[8] = new TH1F("heflow_averagePUperRun_161474","Average number of vertices 161474",10,0,10);
		heflow_perRun[0] = new TH1F("heflow_perRun_161366","Energy flow for run 161366",nBins,min,max);
		heflow_perRun[1] = new TH1F("heflow_perRun_161396","Energy flow for run 161396",nBins,min,max);
		heflow_perRun[2] = new TH1F("heflow_perRun_161404","Energy flow for run 161404",nBins,min,max);
		heflow_perRun[3] = new TH1F("heflow_perRun_161439","Energy flow for run 161439",nBins,min,max);
		heflow_perRun[4] = new TH1F("heflow_perRun_161445","Energy flow for run 161445",nBins,min,max);
		heflow_perRun[5] = new TH1F("heflow_perRun_161450","Energy flow for run 161450",nBins,min,max);
		heflow_perRun[6] = new TH1F("heflow_perRun_161454","Energy flow for run 161454",nBins,min,max);
		heflow_perRun[7] = new TH1F("heflow_perRun_161473","Energy flow for run 161473",nBins,min,max);
		heflow_perRun[8] = new TH1F("heflow_perRun_161474","Energy flow for run 161474",nBins,min,max);
		heflow_AllV_perRun[0] = new TH1F("heflow_AllV_perRun_161366","Energy flow (1 or more Vtx) for run 161366",nBins,min,max);
		heflow_AllV_perRun[1] = new TH1F("heflow_AllV_perRun_161396","Energy flow (1 or more Vtx) for run 161396",nBins,min,max);
		heflow_AllV_perRun[2] = new TH1F("heflow_AllV_perRun_161404","Energy flow (1 or more Vtx) for run 161404",nBins,min,max);
		heflow_AllV_perRun[3] = new TH1F("heflow_AllV_perRun_161439","Energy flow (1 or more Vtx) for run 161439",nBins,min,max);
		heflow_AllV_perRun[4] = new TH1F("heflow_AllV_perRun_161445","Energy flow (1 or more Vtx) for run 161445",nBins,min,max);
		heflow_AllV_perRun[5] = new TH1F("heflow_AllV_perRun_161450","Energy flow (1 or more Vtx) for run 161450",nBins,min,max);
		heflow_AllV_perRun[6] = new TH1F("heflow_AllV_perRun_161454","Energy flow (1 or more Vtx) for run 161454",nBins,min,max);
		heflow_AllV_perRun[7] = new TH1F("heflow_AllV_perRun_161473","Energy flow (1 or more Vtx) for run 161473",nBins,min,max);
		heflow_AllV_perRun[8] = new TH1F("heflow_AllV_perRun_161474","Energy flow (1 or more Vtx) for run 161474",nBins,min,max);
		
	} else if (cmenergy == 7000) {
        // ranges for 7 TeV - use this
        // data
        min = -2000; // to get whole spectrum: -2000
        max = 250000; // to get whole spectrum: 250000
        channelmin = -200;
        channelmax = 120000;
		nBins = 252;
		ptcut = 20;
		lumimax = 0.1;
		lumiBXmax = 0.005;
		LumiBins[0] = 0.0000;
		LumiBins[1] = 0.0005;
		LumiBins[2] = 0.0010;
		LumiBins[3] = 0.0015;
		LumiBins[4] = 0.0020;
		LumiBins[5] = 0.0025;
		LumiBins[6] = 0.0030;
		LumiBins[7] = 0.0035;
		LumiBins[8] = 0.0040;
		LumiBins[9] = 0.0045;
		runs[0] = 135059;
		runs[1] = 135521;
		runs[2] = 135523;
		runs[3] = 135525;
		runs[4] = 135528;
		runs[5] = 135535;
		runs[6] = 135573;
		runs[7] = 135575;
		heflow_averagePUperRun[0] = new TH1F("heflow_averagePUperRun_135059","Average number of vertices 135059",10,0,10);
		heflow_averagePUperRun[1] = new TH1F("heflow_averagePUperRun_135521","Average number of vertices 135521",10,0,10);
		heflow_averagePUperRun[2] = new TH1F("heflow_averagePUperRun_135523","Average number of vertices 135523",10,0,10);
		heflow_averagePUperRun[3] = new TH1F("heflow_averagePUperRun_135525","Average number of vertices 135525",10,0,10);
		heflow_averagePUperRun[4] = new TH1F("heflow_averagePUperRun_135528","Average number of vertices 135528",10,0,10);
		heflow_averagePUperRun[5] = new TH1F("heflow_averagePUperRun_135535","Average number of vertices 135535",10,0,10);
		heflow_averagePUperRun[6] = new TH1F("heflow_averagePUperRun_135573","Average number of vertices 135573",10,0,10);
		heflow_averagePUperRun[7] = new TH1F("heflow_averagePUperRun_135575","Average number of vertices 135575",10,0,10);
		heflow_perRun[0] = new TH1F("heflow_perRun_135059","Energy flow for run 135059",nBins,min,max);
		heflow_perRun[1] = new TH1F("heflow_perRun_135521","Energy flow for run 135521",nBins,min,max);
		heflow_perRun[2] = new TH1F("heflow_perRun_135523","Energy flow for run 135523",nBins,min,max);
		heflow_perRun[3] = new TH1F("heflow_perRun_135525","Energy flow for run 135525",nBins,min,max);
		heflow_perRun[4] = new TH1F("heflow_perRun_135528","Energy flow for run 135528",nBins,min,max);
		heflow_perRun[5] = new TH1F("heflow_perRun_135535","Energy flow for run 135535",nBins,min,max);
		heflow_perRun[6] = new TH1F("heflow_perRun_135573","Energy flow for run 135573",nBins,min,max);
		heflow_perRun[7] = new TH1F("heflow_perRun_135575","Energy flow for run 135575",nBins,min,max);
		heflow_AllV_perRun[0] = new TH1F("heflow_AllV_perRun_135059","Energy flow (1 or more Vtx) for run 135059",nBins,min,max);
		heflow_AllV_perRun[1] = new TH1F("heflow_AllV_perRun_135521","Energy flow (1 or more Vtx) for run 135521",nBins,min,max);
		heflow_AllV_perRun[2] = new TH1F("heflow_AllV_perRun_135523","Energy flow (1 or more Vtx) for run 135523",nBins,min,max);
		heflow_AllV_perRun[3] = new TH1F("heflow_AllV_perRun_135525","Energy flow (1 or more Vtx) for run 135525",nBins,min,max);
		heflow_AllV_perRun[4] = new TH1F("heflow_AllV_perRun_135528","Energy flow (1 or more Vtx) for run 135528",nBins,min,max);
		heflow_AllV_perRun[5] = new TH1F("heflow_AllV_perRun_135535","Energy flow (1 or more Vtx) for run 135535",nBins,min,max);
		heflow_AllV_perRun[6] = new TH1F("heflow_AllV_perRun_135573","Energy flow (1 or more Vtx) for run 135573",nBins,min,max);
		heflow_AllV_perRun[7] = new TH1F("heflow_AllV_perRun_135575","Energy flow (1 or more Vtx) for run 135575",nBins,min,max);
	}
	
	for (int iRun=0;iRun<Nruns;iRun++) {
		heflow_averagePUperRun[iRun]->Sumw2();
		heflow_perRun[iRun]->Sumw2();
		heflow_AllV_perRun[iRun]->Sumw2();
	}
	
	// default energy flow histos - using 5 modules
	TH1F *heflow_DijetRatio = new TH1F("heflow_DijetRatio","Dijet Ratio",1,0,1);
	TH1F *heflow = new TH1F("heflow","total rechit GeV distribution",nBins,min,max); // for data -2000,60000
	TH1F *heflow_dijet = new TH1F("heflow_dijet","total rechit GeV distribution for dijet events",nBins,min,max); // for mc -40,600
	
	// default energy flow histos - using 5 modules - with different dijet pt cuts
	TH1F *heflow_dijet8 = new TH1F("heflow_dijet8","total rechit GeV distribution for dijet events - ptcut 8GeV",nBins,min,max);
	TH1F *heflow_dijet12 = new TH1F("heflow_dijet12","total rechit GeV distribution for dijet events - ptcut 12GeV",nBins,min,max);
	TH1F *heflow_dijet20 = new TH1F("heflow_dijet20","total rechit GeV distribution for dijet events - ptcut 20GeV",nBins,min,max);
	TH1F *heflow_DijetRatio8 = new TH1F("heflow_DijetRatio8","Dijet Ratio (ptcut 8GeV)",1,0,1);
	TH1F *heflow_DijetRatio12 = new TH1F("heflow_DijetRatio12","Dijet Ratio (ptcut 12GeV)",1,0,1);
	TH1F *heflow_DijetRatio20 = new TH1F("heflow_DijetRatio20","Dijet Ratio (ptcut 20GeV)",1,0,1);
	
	// energy flow histos using 6 modules
	TH1F *heflow_DijetRatio_6m = new TH1F("heflow_DijetRatio_6m","Dijet Ratio using 6 modules",1,0,1);
	TH1F *heflow_6m = new TH1F("heflow_6m","total rechit GeV distribution (6 modules)",nBins,min,max);
	TH1F *heflow_dijet_6m = new TH1F("heflow_dijet_6m","total rechit GeV distribution for dijet events (6 modules)",nBins,min,max);
	
	// energy flow histos using all modules
	TH1F *heflow_DijetRatio_14m = new TH1F("heflow_DijetRatio_14m","Dijet Ratio using all modules",1,0,1);
	TH1F *heflow_14m = new TH1F("heflow_14m","total rechit GeV distribution (all modules)",nBins,min,max);                        
	TH1F *heflow_dijet_14m = new TH1F("heflow_dijet_14m","total rechit GeV distribution for dijet events (all modules)",nBins,min,max);
	
	// energy flow histos with no number of vertex conditions
	TH1F *heflow_DijetRatio_AllV = new TH1F("heflow_DijetRatio_AllV","Dijet Ratio with no # vertices condition",1,0,1);
	TH1F *heflow_AllV = new TH1F("heflow_AllV","total rechit GeV distribution (all # vertices)",nBins,min,max);
	TH1F *heflow_dijet_AllV = new TH1F("heflow_dijet_AllV","total rechit GeV distribution for dijet events (all # vertices)",nBins,min,max);
	
	TH2F *h2eflow_grid = new TH2F("h2eflow_grid","energy weighted module vs sector distribution",16,1,17,14,1,15);
	TH2F *h2eflow_map = new TH2F("h2eflow_map","used channels map",16,1,17,14,1,15);
	TH1F *heflow_modules = new TH1F("heflow_modules","average energy in used modules",14,1,15);
	TH1F *heflow_sectors = new TH1F("heflow_sectors","average energy in used sectors",16,1,17);
	TH1F *heflow_usedchannels = new TH1F("heflow_usedchannels","number of used channels to compute eflow",224,1,225);
	TH1F *heflow_channels = new TH1F("heflow_channels","average energy in used channels",80,1,81);
	TH1F *heflow_outoftime = new TH1F("heflow_outoftime","total rechit distribution for out of time rechits",nBins,min,max);
	TH1F *heflow_averagePU = new TH1F("heflow_averagePU","Distribution of # vertices per event",10,0,10);
	
	TH1F *hEventSelection = new TH1F("hEventSelection","Event Selection histogram",7,1,8);
	
	TH2F *h2L1Prescales = new TH2F("h2L1Prescales","Prescale factors vs L1 trigger bits",64,0,64,200,0,200);
	
	TH1F *PFJetpt = new TH1F("PFJetpt","PFjet pt ",100,0,100);
	TH1F *PFJetpt20 = new TH1F("PFJetpt20","PFjet pt with pt>20GeV",100,0,100);
	TH1F *PFJetptdijet20  = new TH1F("PFJetptdijet20","PFjet pt with pt>20GeV & jetcollection size >=2",100,0,100);
	int Ngood = 0;
	int NgoodCentral = 0;
	TH1F *PFJeteta = new TH1F("PFJeteta","PFjet eta ",100,-5,5);
	TH1F *PFJeteta20 = new TH1F("PFJeteta20","PFjet eta with pt>20GeV",100,-5,5);
	TH1F *PFJetetadijet20  = new TH1F("PFJetetadijet20","PFjet eta with pt>20GeV & jetcollection size >=2",100,-5,5);
	
	TH1F *JetMulti  = new TH1F("JetMulti","PFjet multi",20,0,20);
	TH1F *JetMultiGood  = new TH1F("JetMultiGood","PFjet multi NJet >= 2",20,0,20);
	TH1F *JetMultiGoodCentral  = new TH1F("JetMultiGoodCentral","PFjet multi NJetCentral >= 2",20,0,20);
	int Nnotreallygood = 0;
	
	TH1F *heflow_channel[224];
	char name [50];
	char title [50];
	for (int i=0;i<224;i++) {
		sprintf(name,"heflow_channel_%d",i+1);
		sprintf(title,"Energy distribution for channel %d",i+1);
		heflow_channel[i] = new TH1F(name,title,100,channelmin,channelmax); 
		heflow_channel[i]->Sumw2();
	}
	
	int maxVertices = 4;
	TH1F *heflow_pileup[maxVertices];
	for (int i=0;i<maxVertices;i++) {
		sprintf(name,"heflow_pileup_%d",i+1);
		sprintf(title,"Energy flow distribution for %d vertex events",i+1);
		heflow_pileup[i] = new TH1F(name,title,nBins,min,max); 
		heflow_pileup[i]->Sumw2();
	}
	
	TH1F *heflow_dijetpt[25];
	TH1F *heflow_dijetpt_nobacktoback[25];
	for (int i=0;i<25;i++) {
		sprintf(name,"heflow_dijetpt_%d",i+1);
		sprintf(title,"Dijet Energy flow distribution with pt cut %d",i+1);
		heflow_dijetpt[i] = new TH1F(name,title,nBins,min,max);
		heflow_dijetpt[i]->Sumw2();
		sprintf(name,"heflow_dijetpt_nobacktoback%d",i+1);
		sprintf(title,"Dijet Energy flow distribution with pt cut no backtoback %d",i+1);
		heflow_dijetpt_nobacktoback[i] = new TH1F(name,title,nBins,min,max);
		heflow_dijetpt_nobacktoback[i]->Sumw2();
	}
	
	TH1F *heflow_InstLumi = new TH1F("heflow_InstLumi","Instantanious Lumi distribution",500,0,lumimax);
	TH1F *heflow_InstLumiPerBX = new TH1F("heflow_InstLumiPerBX","Instantanious Lumi per BX distribution",nLumiBins,0,lumiBXmax);
	TH1F *heflow_InstLumi_AllV = new TH1F("heflow_InstLumi_AllV","Instantanious Lumi distribution AllV",500,0,lumimax);
	TH1F *heflow_InstLumiPerBX_AllV = new TH1F("heflow_InstLumiPerBX_AllV","Instantanious Lumi per BX distribution AllV",nLumiBins,0,lumiBXmax);
	
	heflow_InstLumi->Sumw2();
	heflow_InstLumiPerBX->Sumw2();
	heflow_InstLumi_AllV->Sumw2();
	heflow_InstLumiPerBX_AllV->Sumw2();
	
	TH1F *heflow_perLumi[nLumiBins];
	for (int i=0;i<nLumiBins;i++) {
		sprintf(name,"heflow_perLumi_%d",i+1);
		sprintf(title,"Energy flow distribution within Inst. lumi per BX bin %d",i+1);
		heflow_perLumi[i] = new TH1F(name,title,nBins,min,max);
		heflow_perLumi[i]->Sumw2();
	}
	
	TH1F *hL1After = new TH1F("hL1After","Result of L1 after mask filter",2,0,2);
	
	// put sumw2's for some histos
	heflow_modules->Sumw2();
	heflow_sectors->Sumw2();
	heflow_channels->Sumw2();
	heflow_averagePU->Sumw2();
	heflow->Sumw2();
	heflow_dijet->Sumw2();
	heflow_DijetRatio->Sumw2();
	heflow_usedchannels->Sumw2();
	heflow_14m->Sumw2();
	heflow_dijet_14m->Sumw2();
	heflow_DijetRatio_14m->Sumw2();
	heflow_AllV->Sumw2();
	heflow_dijet_AllV->Sumw2();
	heflow_DijetRatio_AllV->Sumw2();
	
	TIter       next(filelist); 
	TObjString* fn = 0;
	TString currentfile = "";
	
	bool isMC = false;
	
	double IntegratedLumi = 0;
	
	int passedL1Phys15 = 0;
	int passedL1Phys15AndMB = 0;
	
	
	// de-calibrate using the errors of the inter-calibration constants
	bool decalibrate = false;
	
	if (decalibrate) {
		// get constants and their errors from file
	}
	
	
	std::cout << "start looping over files" << std::endl;
	
	// start file loop
	while((fn = (TObjString*)next())) { 
		
		currentfile.Clear();
		currentfile = fn->GetString();
		
		std::cout << "opening the file..." << std::endl;
		
		TFile* f = TFile::Open(inputdir+fn->GetString(),"READ");
		if (!f) { std::cout << "Error in TreeAnalyzer: could not open file " << fn->GetString() << std::endl; continue; } 
		// do what ever 
		std::cout << "opened " << fn->GetString() << std::endl;
		
		//////////////////////////////////////////////////
		// Get tree from the files and define all branches
		//////////////////////////////////////////////////
		
		// get tree from file
		TTree *tree = new TTree("CastorTree","");
		f->GetObject("castortree/CastorTree",tree);
		
		TString strangefile = "CastorTree_data_MinBias_Commissioning10-May19ReReco-v1_7TeV_RECOwithCorrector_8_1_RUK.rootdontprint";
		if (strangefile == fn->GetString()) std::cout << "got tree from strange file" << std::endl;
		
		// define objects and branches
		MyEvtId *evtid = NULL;
		MyDiJet *dijet = NULL;
		MyHLTrig *HLTrig = NULL;
		MyL1Trig *L1Trig = NULL;
		std::vector<MyVertex> *Vertices = NULL;
		std::vector<MyCastorRecHit> *CastorRecHits = NULL;
		//std::vector<MyCastorDigi> *CastorDigis = NULL;
		std::vector<MyJet> *PFJets = NULL;
		
		TBranch *b_evtid = tree->GetBranch("EvtId");
		TBranch *b_dijet = tree->GetBranch("pfDiJet");
		TBranch *b_HLTrig = tree->GetBranch("HLTrig");
		TBranch *b_L1Trig = tree->GetBranch("L1Trig");
		TBranch *b_vertices = tree->GetBranch("primaryVertex");
		TBranch *b_castorrechits = tree->GetBranch("castorRecHit");
		//TBranch *b_castordigis = tree->GetBranch("castorDigi");
		TBranch *b_PFJets = tree->GetBranch("pfJet");
		
		b_evtid->SetAddress(&evtid);
		b_dijet->SetAddress(&dijet);
		b_HLTrig->SetAddress(&HLTrig);
		b_L1Trig->SetAddress(&L1Trig);
		b_vertices->SetAddress(&Vertices);
		b_castorrechits->SetAddress(&CastorRecHits);
		//b_castordigis->SetAddress(&CastorDigis);
		b_PFJets->SetAddress(&PFJets);
		
		int Nevents = tree->GetEntriesFast();
		std::cout << "events in this file = " << Nevents << std::endl;
		//totalevents += Nevents;
		
		// start event loop
		for (int i=0;i<Nevents;i++) {
			
			/////////////////////////////////////////
			// Do stuff before filters
			/////////////////////////////////////////
			
			b_evtid->GetEntry(i);
			b_HLTrig->GetEntry(i);
			b_L1Trig->GetEntry(i);
			b_vertices->GetEntry(i);
			
			// only process a certain run
			//if (evtid->Run == 135535) continue;
			
			// before any filter, fill first bin in histo which is total number of events
			hEventSelection->Fill(1,1);
			
			/////////////////////////////////////////
			// Filter the results
			/////////////////////////////////////////
			
			if (isData) {
				// filter results
				if (cmenergy != 2760) { // only put this statement when using the L1 skim of the 2.76 TeV data
					// filter on phys declared bit
					bool physDeclresult = HLTrig->HLTmap["physDeclpath"];
					if ( physDeclresult == false) {hEventSelection->Fill(2,1); continue;}
					
					// filter on castor invalid data
					bool castorInvalidDataFilterresult = HLTrig->HLTmap["castorInvalidDataFilterpath"];
					if ( castorInvalidDataFilterresult == false) {hEventSelection->Fill(3,1); continue;}
					
					// filter out scraping events
					bool noscrapingresult = HLTrig->HLTmap["noscrapingpath"];
					if ( noscrapingresult == false) {hEventSelection->Fill(4,1); continue;}
				}
				
				// L1 filter
				
				/*
				for (int iTrig = 0;iTrig<64;iTrig++) {
					std::cout << " L1 technical trigger bit " << iTrig << " = " << L1Trig->GetTechName(iTrig) << " prescale = " << L1Trig->GetTechPrescale(iTrig) 
					<< " and it is masked? " << L1Trig->GetTechMask(iTrig) << std::endl;
					std::cout << " L1 physical trigger bit " << iTrig << " = " << L1Trig->GetPhysName(iTrig) << " prescale = " << L1Trig->GetPhysPrescale(iTrig) 
					<< " and it is masked? " << L1Trig->GetPhysMask(iTrig) << std::endl;
				}
				*/
				// check that the technical trigger are not masked
				bool L1Triggers_ok = false;
				if ( !L1Trig->fTechMask[0] && !L1Trig->fTechMask[36] && !L1Trig->fTechMask[37] && !L1Trig->fTechMask[38] && !L1Trig->fTechMask[39]
					&& !L1Trig->fTechMask[40] && !L1Trig->fTechMask[41]) L1Triggers_ok = true;
				// check trigger condition
				bool L1Triggers_passed = false;
				if ( L1Trig->fTechDecisionBefore[0] && (L1Trig->fTechDecisionBefore[40] || L1Trig->fTechDecisionBefore[41]) 
					&& !(L1Trig->fTechDecisionBefore[36] || L1Trig->fTechDecisionBefore[37] || L1Trig->fTechDecisionBefore[38] || L1Trig->fTechDecisionBefore[39])) 
					L1Triggers_passed = true;
				
				
				int L1after = 0;
				if ( L1Trig->fTechDecisionAfter[0] && (L1Trig->fTechDecisionAfter[40] || L1Trig->fTechDecisionAfter[41]) 
					&& !(L1Trig->fTechDecisionAfter[36] || L1Trig->fTechDecisionAfter[37] || L1Trig->fTechDecisionAfter[38] || L1Trig->fTechDecisionAfter[39])) L1after = 1;
				
				//if (L1Trig->fTechDecisionBefore[40] || L1Trig->fTechDecisionBefore[41] ) L1Triggers_passed = true;
				// filter on L1 tech triggers
				//if (!L1Triggers_ok) std::cout << "All the triggers are masked" << std::endl;
				if (!L1Triggers_passed) {hEventSelection->Fill(5,1); continue;}
				
				hL1After->Fill(L1after);
				
				/*
				if (L1Trig->fPhysDecisionBefore[15]) {
					passedL1Phys15++;
					if (L1Triggers_passed) passedL1Phys15AndMB++;
				}
				*/
				
				// get vertex info
				// do the oneGoodVertexFilter
				bool wehaveGoodVertex = false;
				for (unsigned int iVert=0;iVert<Vertices->size();iVert++) {
					MyVertex vertex = (*Vertices)[iVert];
					if (vertex.isGoodVertex) wehaveGoodVertex = true;
				}
				if (wehaveGoodVertex == false) {hEventSelection->Fill(6,1); continue;}
			} else {
				// MC
				// L1 filter
				// check trigger condition
				bool L1Triggers_passed = false;
				if ( L1Trig->fTechDecisionBefore[40] || L1Trig->fTechDecisionBefore[41]) L1Triggers_passed = true;
				// filter on L1 tech triggers
				if (!L1Triggers_passed) {hEventSelection->Fill(5,1); continue;}
				
				// get vertex info
				// do the oneGoodVertexFilter
				bool wehaveGoodVertex = false;
				for (unsigned int iVert=0;iVert<Vertices->size();iVert++) {
					MyVertex vertex = (*Vertices)[iVert];
					if (vertex.isGoodVertex) wehaveGoodVertex = true;
				}
				if (wehaveGoodVertex == false) {hEventSelection->Fill(6,1); continue;}				
			}

			
			// at this point, event passed following filters: physDecl, castorInvalidDataFilter, noscraping, L1 tech, oneGoodVertexFilter for data or
			// just the L1 and vertex filter for MC
			
			/////////////////////////////////////////
			// Do stuff after filters
			/////////////////////////////////////////
			
			// get all the remaining branch entries
			b_castorrechits->GetEntry(i);
			b_dijet->GetEntry(i);
			b_PFJets->GetEntry(i);
			
			// show in plot how many events with more than 1 vertex we have - these are also filtered in default eflow (see below)
			if (Vertices->size() > 1) hEventSelection->Fill(7,1);
			
			// get average number of vertices per run
			for (unsigned int iRun=0;iRun<Nruns;iRun++) {
				if (evtid->Run == runs[iRun]) heflow_averagePUperRun[iRun]->Fill(Vertices->size());
			}
			heflow_averagePU->Fill(Vertices->size());
			
			// get prescale factors of the L1 triggers
			h2L1Prescales->Fill(0.,(double)L1Trig->fTechPrescale[0]);
			h2L1Prescales->Fill(40.,(double)L1Trig->fTechPrescale[40]);
			h2L1Prescales->Fill(41.,(double)L1Trig->fTechPrescale[41]); 
			h2L1Prescales->Fill(36.,(double)L1Trig->fTechPrescale[36]);
			h2L1Prescales->Fill(37.,(double)L1Trig->fTechPrescale[37]);
			h2L1Prescales->Fill(38.,(double)L1Trig->fTechPrescale[38]);
			h2L1Prescales->Fill(39.,(double)L1Trig->fTechPrescale[39]);
			
			// fill the inst lumi distributions
			heflow_InstLumi_AllV->Fill(evtid->IstLumi);
			heflow_InstLumiPerBX_AllV->Fill(evtid->IstLumiPerBX);
			
			
			/////////////////////////////////////////
			// Start Nvertex == 1 part of the code 
			/////////////////////////////////////////
			
			// only fill the histograms when there's 1 vertex (filter out pile-up)
			if (Vertices->size() == 1) {
				
				// get event id stuff
				if( ((i+1) % 1000) == 0) cout << " run " << evtid->Run << " isData = " << evtid->IsData << " lumiblock " << evtid->LumiBlock << " event " << evtid->Evt << endl; 
				if (!evtid->IsData) isMC = true;
				IntegratedLumi += evtid->IstLumi;
				
				// fill the inst lumi distributions
				heflow_InstLumi->Fill(evtid->IstLumi);
				heflow_InstLumiPerBX->Fill(evtid->IstLumiPerBX);
				
				// fill castor rechit stuff
				double totalrechitenergy = 0;
				hNRecHits->Fill(CastorRecHits->size());
				for (unsigned int j=0;j<CastorRecHits->size();j++) {
					MyCastorRecHit rechit = (*CastorRecHits)[j];
					hRecHit_energy->Fill(rechit.energy);
					hRecHit_fC->Fill(rechit.fC);
					hRecHit_time->Fill(rechit.time);
					hRecHit_module->Fill(rechit.mod,rechit.energy);
					hRecHit_sector->Fill(rechit.sec,rechit.energy);
					hRecHit_channel->Fill(rechit.cha,rechit.energy);
					totalrechitenergy += rechit.energy;
					if (rechit.time > 15 && rechit.time < 35) hRecHit_energy_clean->Fill(rechit.energy);
					h2RecHit_EvsT->Fill(rechit.time,rechit.fC);
					hRecHit_WeightedTime->Fill(rechit.time,rechit.fC);
					hLS->Fill(evtid->LumiBlock,rechit.cha);
					hLSWeighted->Fill(evtid->LumiBlock,rechit.cha,rechit.energy);
				}
				hRecHit_totalenergy->Fill(totalrechitenergy);
				
				// fill LS histogram with total rechit energy
				//hLS->Fill(evtid->LumiBlock);
				//hLSWeighted->Fill(evtid->LumiBlock,totalrechitenergy);
				
				// fill eflow and dijet histograms
				double eflow = 0;
				double eflow_m6 = 0;
				double eflow_m14 = 0;
				int usedchannels = 0;
				double outoftime_eflow = 0;
				for (unsigned int j=0;j<CastorRecHits->size();j++) {
					MyCastorRecHit rechit = (*CastorRecHits)[j];
					h2eflow_map->Fill(rechit.sec,rechit.mod,1);
					if (rechit.cha != 5 && rechit.cha != 6) { // for data 15,35,81,5,6
						if (evtid->IsData) { // for data, energy is intercalibrated fC
							heflow_channel[rechit.cha-1]->Fill(rechit.energy);
							if (rechit.cha <= 80) eflow += rechit.energy;
							if (rechit.cha <= 96) eflow_m6 += rechit.energy;
							eflow_m14 += rechit.energy;
							usedchannels++;
							h2eflow_grid->Fill(rechit.sec,rechit.mod,rechit.energy);
						} else { // for MC take fC
							heflow_channel[rechit.cha-1]->Fill(rechit.fC);
							if (rechit.cha <= 80) eflow += rechit.fC;
							if (rechit.cha <= 96) eflow_m6 += rechit.fC;
							eflow_m14 += rechit.fC;
							usedchannels++;
							h2eflow_grid->Fill(rechit.sec,rechit.mod,rechit.fC);
						}
					}
					if ((rechit.time < 15 || rechit.time > 35) && rechit.cha < 81 && rechit.cha != 5 && rechit.cha != 6) outoftime_eflow += rechit.energy;
				}
				
				// fill all minbias eflow histos
				heflow->Fill(eflow);
				heflow_6m->Fill(eflow_m6);
				heflow_14m->Fill(eflow_m14);
				heflow_AllV->Fill(eflow);
				heflow_usedchannels->Fill(usedchannels);
				heflow_outoftime->Fill(outoftime_eflow);
				heflow_pileup[Vertices->size()-1]->Fill(eflow);
				
				// get default eflow per run
				for (unsigned int iRun=0;iRun<Nruns;iRun++) {
					if (evtid->Run == runs[iRun]) heflow_perRun[iRun]->Fill(eflow);
					if (evtid->Run == runs[iRun]) heflow_AllV_perRun[iRun]->Fill(eflow);
				}
				
				// get eflow per lumi bin
				for (int iLumiBin=0;iLumiBin<nLumiBins-1;iLumiBin++) {
					double currentLumiPerBX = evtid->IstLumiPerBX;
					if (currentLumiPerBX >= LumiBins[iLumiBin] && currentLumiPerBX < LumiBins[iLumiBin+1]) heflow_perLumi[iLumiBin]->Fill(eflow);
				}
				
				// fill default dijet distributions
				if (dijet->isDiJet) {
					if ((*PFJets)[dijet->posJet1].pt_cal >= ptcut && (*PFJets)[dijet->posJet2].pt_cal >= ptcut) heflow_dijet->Fill(eflow);
					if ((*PFJets)[dijet->posJet1].pt_cal >= ptcut && (*PFJets)[dijet->posJet2].pt_cal >= ptcut) heflow_dijet_AllV->Fill(eflow);
					if ((*PFJets)[dijet->posJet1].pt_cal >= ptcut && (*PFJets)[dijet->posJet2].pt_cal >= ptcut) heflow_dijet_6m->Fill(eflow_m6);
					if ((*PFJets)[dijet->posJet1].pt_cal >= ptcut && (*PFJets)[dijet->posJet2].pt_cal >= ptcut) heflow_dijet_14m->Fill(eflow_m14);
					
					// fill 8GeV ptcut distributions
					if ((*PFJets)[dijet->posJet1].pt_cal >= 8.0 && (*PFJets)[dijet->posJet2].pt_cal >= 8.0) heflow_dijet8->Fill(eflow);
					// fill 12GeV ptcut distributions
					if ((*PFJets)[dijet->posJet1].pt_cal >= 12.0 && (*PFJets)[dijet->posJet2].pt_cal >= 12.0) heflow_dijet12->Fill(eflow);
					// fill 20GeV ptcut distributions
					if ((*PFJets)[dijet->posJet1].pt_cal >= 20.0 && (*PFJets)[dijet->posJet2].pt_cal >= 20.0) heflow_dijet20->Fill(eflow);
				}
				
				// pt evolution, do manual dijet selection
				for (int ipt=0;ipt<25;ipt++) {
					double thiscut = ipt+1;
					if ( isPFDiJet(*PFJets,true,2.5,thiscut)) heflow_dijetpt[ipt]->Fill(eflow);
					if ( isPFDiJet(*PFJets,false,2.5,thiscut)) heflow_dijetpt_nobacktoback[ipt]->Fill(eflow);
				}
				
				
				// PF jet control plots
				int NJet = 0;
				int NCentralJet = 0;
				for (int ijet=0;ijet<PFJets->size();ijet++) {
					PFJetpt->Fill((*PFJets)[ijet].pt_cal);
					if ((*PFJets)[ijet].pt_cal > 20.) PFJetpt20->Fill((*PFJets)[ijet].pt_cal);
					if ((*PFJets)[ijet].pt_cal > 20. && PFJets->size() >= 2) PFJetptdijet20->Fill((*PFJets)[ijet].pt_cal);
					
					if ((*PFJets)[ijet].pt_cal > 20. && fabs((*PFJets)[ijet].eta_cal) < 2.5) NCentralJet++;
					if ((*PFJets)[ijet].pt_cal > 20.) NJet++;
					
					PFJeteta->Fill((*PFJets)[ijet].eta_cal);
					if ((*PFJets)[ijet].pt_cal > 20.) PFJeteta20->Fill((*PFJets)[ijet].eta_cal);
					if ((*PFJets)[ijet].pt_cal > 20. && PFJets->size() >= 2) PFJetetadijet20->Fill((*PFJets)[ijet].eta_cal);
				}
				if (PFJets->size() >= 2) Nnotreallygood++;
				if (NJet >= 2) Ngood++;
				if (NCentralJet >= 2) NgoodCentral++;
				JetMulti->Fill(PFJets->size());
				if (NJet >= 2) JetMultiGood->Fill(PFJets->size());
				if (NCentralJet >= 2)JetMultiGoodCentral->Fill(PFJets->size());
				
				
				// end of event, print status
				if( ((i+1) % 1000) == 0) std::cout << i+1 <<"events done in file " << it << std::endl;
				totalevents++;
				
			} // end if statement for 1 vertex
			else if (Vertices->size() > 1) {
				
				////////////////////////////////////////////////
				// eflow code for events with more than 1 vertex
				////////////////////////////////////////////////
				
				// fill eflow and dijet histograms
				double pileup_eflow = 0;
				for (unsigned int j=0;j<CastorRecHits->size();j++) {
					MyCastorRecHit rechit = (*CastorRecHits)[j];
					if (rechit.cha < 81 && rechit.cha != 5 && rechit.cha != 6) { // for data 15,35,81,5,6
						if (evtid->IsData) { // for data, energy is intercalibrated fC
							pileup_eflow += rechit.energy;
						} else { // for MC take fC
							pileup_eflow += rechit.fC;
						}
					}
				}
				if ((int)Vertices->size() <= maxVertices) heflow_pileup[Vertices->size()-1]->Fill(pileup_eflow);
				if (dijet->isDiJet) { 
					MyJet jet1 = (*PFJets)[dijet->posJet1];
					MyJet jet2 = (*PFJets)[dijet->posJet2];
					if (jet1.pt_cal >= ptcut && jet2.pt_cal >= ptcut) {
						heflow_dijet_AllV->Fill(pileup_eflow);
					}
				}
				heflow_AllV->Fill(pileup_eflow);
				// get PU eflow per run
				for (unsigned int iRun=0;iRun<Nruns;iRun++) {
					if (evtid->Run == runs[iRun]) heflow_AllV_perRun[iRun]->Fill(pileup_eflow);
				}
				
			} // end if statement for more than 1 vertex
			
		} // end event loop
		
		delete tree;
		f->Close();
		it++;
	} // end file loop
	
	
	//////////////////////////////////////////////////
	// energy flow stuff needed after event filling //
	//////////////////////////////////////////////////
	
	std::cout << "starting eflow calculations" << std::endl;
	
	// check distribution of each channel on under or overflow
	for (int icha=0;icha<224;icha++) {
		if (heflow_channel[icha]->GetBinContent(heflow_channel[icha]->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! channel " << icha << " has overflow" << std::endl;
		if (heflow_channel[icha]->GetBinContent(0) !=0) std::cout << "!!WARNING!! channel " << icha << " has underflow" << std::endl;
	}
	
	// check distribution of each pileup on under or overflow
	for (int icha=0;icha<maxVertices;icha++) {
		if (heflow_pileup[icha]->GetBinContent(heflow_pileup[icha]->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! eflow with pileup " << icha << " has overflow" << std::endl;
		if (heflow_pileup[icha]->GetBinContent(0) !=0) std::cout << "!!WARNING!! eflow with pileup " << icha << " has underflow" << std::endl;
	}
	
	// check per run distributions for under or overflow
	for (int iRun=0;iRun<Nruns;iRun++) {
		if (heflow_averagePUperRun[iRun]->GetBinContent(heflow_averagePUperRun[iRun]->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! average vertices for run " << iRun << " has overflow" << std::endl;
		if (heflow_averagePUperRun[iRun]->GetBinContent(0) !=0) std::cout << "!!WARNING!! average vertices for run " << iRun << " has underflow" << std::endl;
		if (heflow_perRun[iRun]->GetBinContent(heflow_perRun[iRun]->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! eflow for run " << iRun << " has overflow" << std::endl;;
		if (heflow_perRun[iRun]->GetBinContent(0) !=0) std::cout << "!!WARNING!! eflow for run " << iRun << " has underflow" << std::endl;
		if (heflow_AllV_perRun[iRun]->GetBinContent(heflow_AllV_perRun[iRun]->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! eflow with 1 or more Vtx for run " << iRun << " has overflow" << std::endl;
		if (heflow_AllV_perRun[iRun]->GetBinContent(0) !=0) std::cout << "!!WARNING!! eflow with 1 or more Vtx  for run " << iRun << " has underflow" << std::endl;
	}
	
	// check all dijet pt histos for under or overflow
	for (int ipt=0;ipt<25;ipt++) {
		if (heflow_dijetpt[ipt]->GetBinContent(heflow_dijetpt[ipt]->GetNbinsX()+1) !=0)std::cout << "!!WARNING!! dijet eflow with with ptcut " << ipt+1 << " has overflow" << std::endl;
		if (heflow_dijetpt[ipt]->GetBinContent(0) !=0) std::cout << "!!WARNING!! dijet eflow with ptcut " << ipt+1 << " has underflow" << std::endl;
	}
	
	// check eflow for under/overflow
	if (heflow->GetBinContent(heflow->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! minbias eflow has overflow" << std::endl;
	if (heflow->GetBinContent(0) !=0) std::cout << "!!WARNING!! minbias eflow has underflow" << std::endl;
	if (heflow_dijet->GetBinContent(heflow_dijet->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! dijet eflow has overflow" << std::endl;
	if (heflow_dijet->GetBinContent(0) !=0) std::cout << "!!WARNING!! dijet eflow has underflow" << std::endl;
	
	if (heflow_dijet8->GetBinContent(heflow_dijet8->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! dijet eflow ptcut 8GeV has overflow" << std::endl;
	if (heflow_dijet8->GetBinContent(0) !=0) std::cout << "!!WARNING!! dijet eflow ptcut 8GeV has underflow" << std::endl;

	if (heflow_dijet12->GetBinContent(heflow_dijet12->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! dijet eflow ptcut 12GeV has overflow" << std::endl;
	if (heflow_dijet12->GetBinContent(0) !=0) std::cout << "!!WARNING!! dijet eflow ptcut 12GeV has underflow" << std::endl;
	
	if (heflow_dijet20->GetBinContent(heflow_dijet20->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! dijet eflow ptcut 20GeV has overflow" << std::endl;
	if (heflow_dijet20->GetBinContent(0) !=0) std::cout << "!!WARNING!! dijet eflow ptcut 20GeV has underflow" << std::endl;
	
	if (heflow_6m->GetBinContent(heflow_6m->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! minbias eflow using 6 modules has overflow" << std::endl;
	if (heflow_6m->GetBinContent(0) !=0) std::cout << "!!WARNING!! minbias eflow using 6 modules has underflow" << std::endl;
	if (heflow_dijet_6m->GetBinContent(heflow_dijet_6m->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! dijet eflow using 6 modules has overflow" << std::endl;
	if (heflow_dijet_6m->GetBinContent(0) !=0) std::cout << "!!WARNING!! dijet eflow using 6 modules has underflow" << std::endl;
	
	if (heflow_14m->GetBinContent(heflow_14m->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! minbias eflow using all modules has overflow" << std::endl;
	if (heflow_14m->GetBinContent(0) !=0) std::cout << "!!WARNING!! minbias eflow using all modules has underflow" << std::endl;
	if (heflow_dijet_14m->GetBinContent(heflow_dijet_14m->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! dijet eflow using all modules has overflow" << std::endl;
	if (heflow_dijet_14m->GetBinContent(0) !=0) std::cout << "!!WARNING!! dijet eflow using all modules has underflow" << std::endl;
	
	if (heflow_AllV->GetBinContent(heflow_AllV->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! minbias eflow with no # vertices condition has overflow" << std::endl;
	if (heflow_AllV->GetBinContent(0) !=0) std::cout << "!!WARNING!! minbias eflow with no # vertices condition has underflow" << std::endl;
	if (heflow_dijet_AllV->GetBinContent(heflow_dijet_AllV->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! dijet eflow with no # vertices condition has overflow" << std::endl;
	if (heflow_dijet_AllV->GetBinContent(0) !=0) std::cout << "!!WARNING!! dijet eflow with no # vertices condition has underflow" << std::endl;
	
	// get mean and error's from all channels and put it in one histo
	for (int icha=0;icha<80;icha++) {
		if (icha<32 && !isMC) { heflow_channels->SetBinContent(icha+1,heflow_channel[icha]->GetMean());} else {heflow_channels->SetBinContent(icha+1,heflow_channel[icha]->GetMean());}
		if (icha<32 && !isMC) { heflow_channels->SetBinError(icha+1,heflow_channel[icha]->GetMeanError());} else {heflow_channels->SetBinError(icha+1,heflow_channel[icha]->GetMeanError());}
	}
	
	//heflow_channels->Scale(1./heflow_channels->Integral());
	
	/*
	 // normalize heflow_channels histo to first bin
	 double bin1 = heflow_channels->GetBinContent(1);
	 double errorbin1 = heflow_channels->GetBinError(1);
	 for (int i=0;i<80;i++) {
	 double tmp = heflow_channels->GetBinContent(i+1);
	 double tmperror = heflow_channels->GetBinError(i+1);
	 heflow_channels->SetBinContent(i+1,tmp/bin1);
	 if (tmp !=0) heflow_channels->SetBinError(i+1,getRatioError(tmp,bin1,tmperror,errorbin1));
	 }
	 */ 
	
	// make average module profile
	for (int i=0;i<5;i++) {
		double average = 0;
		double error = 0;
		for (int j=0;j<16;j++) {
			bool bad = false;
			if (i==0 && j==11) bad = true; // module 1, sector 12
			if (i==2 && j==4) bad = true; // module 3, sector 5
			if (i==3 && j==4) bad = true; // module 4, sector 5
			if (i==4 && j==4) bad = true; // module 5, sector 5
			if (i==4 && j==5) bad = true; // module 5, sector 6
			if (!bad) {
				average += heflow_channel[j+(i*16)]->GetMean();
				error += heflow_channel[j+(i*16)]->GetMeanError()*heflow_channel[j+(i*16)]->GetMeanError();
			}
		}
		
		if (i==0) average = average/13;
		if (i==1) average = average/16;
		if (i==2) average = average/15;
		if (i==3) average = average/15;
		if (i==4) average = average/14;
		
		//if (i==0) average = average/14;
		//if (i > 0) average = average/16;
		error = sqrt(error);
		heflow_modules->SetBinContent(i+1,average);
		heflow_modules->SetBinError(i+1,error);
	}
	
	// normalize to integral
	//heflow_modules->Scale(1./heflow_modules->Integral());
	
	/*
	 // normalize average module profile to first bin
	 double bin2 = heflow_modules->GetBinContent(1);
	 double errorbin2 = heflow_modules->GetBinError(1);
	 for (int i=0;i<5;i++) {
	 double tmp = heflow_modules->GetBinContent(i+1);
	 double tmperror = heflow_modules->GetBinError(i+1);
	 heflow_modules->SetBinContent(i+1,tmp/bin2);
	 if (tmp !=0) heflow_modules->SetBinError(i+1,getRatioError(tmp,bin2,tmperror,errorbin2));
	 }
	 */ 
	
	// make average sector profile
	for (int i=0;i<16;i++) {
		double average = 0;
		double error = 0;
		for (int j=0;j<5;j++) {
			average += heflow_channel[i+(j*16)]->GetMean();
			error += heflow_channel[i+(j*16)]->GetMeanError()*heflow_channel[i+(j*16)]->GetMeanError();
		}
		average = average/5;
		if (i==4 || i==5) { average = 0; error = 0; } // channels 5 and 6 are not used
		error = sqrt(error);
		heflow_sectors->SetBinContent(i+1,average);
		heflow_sectors->SetBinError(i+1,error);
	}
	
	//heflow_sectors->Scale(1./heflow_sectors->Integral());
	
	// do eflow ratio stuff
	double dijetratio = heflow_dijet->GetMean()/heflow->GetMean();
	double dijetratio_error = getRatioError(heflow,heflow_dijet);
	heflow_DijetRatio->SetBinContent(1,dijetratio);
	heflow_DijetRatio->SetBinError(1,dijetratio_error);
	
	double dijetratio8 = heflow_dijet8->GetMean()/heflow->GetMean();
	double dijetratio_error8 = getRatioError(heflow,heflow_dijet8);
	heflow_DijetRatio8->SetBinContent(1,dijetratio8);
	heflow_DijetRatio8->SetBinError(1,dijetratio_error8);
	
	double dijetratio12 = heflow_dijet12->GetMean()/heflow->GetMean();
	double dijetratio_error12 = getRatioError(heflow,heflow_dijet12);
	heflow_DijetRatio12->SetBinContent(1,dijetratio12);
	heflow_DijetRatio12->SetBinError(1,dijetratio_error12);
	
	double dijetratio20 = heflow_dijet20->GetMean()/heflow->GetMean();
	double dijetratio_error20 = getRatioError(heflow,heflow_dijet20);
	heflow_DijetRatio20->SetBinContent(1,dijetratio20);
	heflow_DijetRatio20->SetBinError(1,dijetratio_error20);
	
	double dijetratio_6m = heflow_dijet_6m->GetMean()/heflow_6m->GetMean();
	double dijetratio_error_6m = getRatioError(heflow_6m,heflow_dijet_6m);
	heflow_DijetRatio_6m->SetBinContent(1,dijetratio_6m);
	heflow_DijetRatio_6m->SetBinError(1,dijetratio_error_6m);
	
	double dijetratio_14m = heflow_dijet_14m->GetMean()/heflow_14m->GetMean();
	double dijetratio_error_14m = getRatioError(heflow_14m,heflow_dijet_14m);
	heflow_DijetRatio_14m->SetBinContent(1,dijetratio_14m);
	heflow_DijetRatio_14m->SetBinError(1,dijetratio_error_14m);
	
	double dijetratio_AllV = heflow_dijet_AllV->GetMean()/heflow_AllV->GetMean();
	double dijetratio_error_AllV = getRatioError(heflow_AllV,heflow_dijet_AllV);
	heflow_DijetRatio_AllV->SetBinContent(1,dijetratio_AllV);
	heflow_DijetRatio_AllV->SetBinError(1,dijetratio_error_AllV);
	
	// now print all the dijet ratio's and their errors  
	std::cout << "MinBias energy flow (" << cmenergy << " GeV) = " << heflow->GetMean() << " and Dijet energy flow (" << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << heflow_dijet->GetMean() << std::endl;
	
	std::cout << "Dijet energy flow (" << cmenergy << " GeV, ptcut = 8 GeV) = " << heflow_dijet8->GetMean() << std::endl;
	std::cout << "Dijet energy flow (" << cmenergy << " GeV, ptcut = 12 GeV) = " << heflow_dijet12->GetMean() << std::endl;
	std::cout << "Dijet energy flow (" << cmenergy << " GeV, ptcut = 20 GeV) = " << heflow_dijet20->GetMean() << std::endl;
	
	std::cout << "Dijet ratio (default at " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << dijetratio << " +- " << dijetratio_error << std::endl;
	std::cout << "Dijet ratio ( " << cmenergy << " GeV, ptcut = 8 GeV) = " << dijetratio8 << " +- " << dijetratio_error8 << std::endl;
	std::cout << "Dijet ratio ( " << cmenergy << " GeV, ptcut = 12 GeV) = " << dijetratio12 << " +- " << dijetratio_error12 << std::endl;
	std::cout << "Dijet ratio ( " << cmenergy << " GeV, ptcut = 20 GeV) = " << dijetratio20 << " +- " << dijetratio_error20 << std::endl;
	
	std::cout << "Dijet ratio (6 modules at " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << dijetratio_6m << " +- "	<< dijetratio_error_6m << std::endl;
	std::cout << "Dijet ratio (all modules at " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << dijetratio_14m << " +- "	<< dijetratio_error_14m << std::endl;
	std::cout << "Dijet ratio (no # vertices condition at " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << dijetratio_AllV << " +- "	<< dijetratio_error_AllV << std::endl;
	
	std::cout << "shower containment systematic " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << (dijetratio_14m - dijetratio)/dijetratio << std::endl;
	std::cout << "vertex condition systematic " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << (dijetratio_AllV - dijetratio)/dijetratio << std::endl;
	std::cout << "mean PU distribution " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << heflow_averagePU->GetMean() << std::endl;
	
	// make a pile up plot
	TH1F *heflow_vs_pileup = new TH1F("heflow_vs_pileup","Mean eflow vs number of vertices",maxVertices,1,maxVertices+1);
	for (int i=0;i<maxVertices;i++) {
		heflow_vs_pileup->SetBinContent(i+1,heflow_pileup[i]->GetMean());
		heflow_vs_pileup->SetBinError(i+1,heflow_pileup[i]->GetMeanError());
	}
	
	std::cout << "Integrated Luminosity = " << IntegratedLumi << std::endl;
	
	// edit event selection histo
	for (int iBin=0;iBin<hEventSelection->GetNbinsX();iBin++) {
		std::cout << " event selection bin " << iBin+1 << " = " << hEventSelection->GetBinContent(iBin+1) << std::endl;
		if (iBin != 0) hEventSelection->SetBinContent(iBin+1,hEventSelection->GetBinContent(iBin)-hEventSelection->GetBinContent(iBin+1));
	}
	
	// make histos with per run info
	TH1F *heflow_vs_runs = new TH1F("heflow_vs_runs","MinBias energy flow vs runs",Nruns,1,Nruns);
	TH1F *heflow_vs_runs_AllV = new TH1F("heflow_vs_runs_AllV","MinBias energy flow AllV vs runs",Nruns,1,Nruns);
	TH1F *haveragePU_vs_runs = new TH1F("haveragePU_vs_runs","Average # vertices vs runs",Nruns,1,Nruns);
	TH2F *h2eflow_vs_averagePU = new TH2F("h2eflow_vs_averagePU","MinBias energy flow vs Average # vertices",100,1.0,1.1,100,20000,25000);
	
	for (unsigned int iRun=0;iRun<Nruns;iRun++) {
		heflow_vs_runs->SetBinContent(iRun+1,heflow_perRun[iRun]->GetMean());
		heflow_vs_runs->SetBinError(iRun+1,heflow_perRun[iRun]->GetMeanError());
		heflow_vs_runs_AllV->SetBinContent(iRun+1,heflow_AllV_perRun[iRun]->GetMean());
		heflow_vs_runs_AllV->SetBinError(iRun+1,heflow_AllV_perRun[iRun]->GetMeanError());
		haveragePU_vs_runs->SetBinContent(iRun+1,heflow_averagePUperRun[iRun]->GetMean());
		haveragePU_vs_runs->SetBinError(iRun+1,heflow_averagePUperRun[iRun]->GetMeanError());
		h2eflow_vs_averagePU->Fill(heflow_averagePUperRun[iRun]->GetMean(),heflow_AllV_perRun[iRun]->GetMean());
	}
	
	std::cout << "number of good events with at least 2 jets in eta 2.5 and 20GeV = " << NgoodCentral << std::endl;	
	std::cout << "number of events with at least 2 jets and 20GeV = " << Ngood << std::endl;
	std::cout << "number of events with at least 2 jets = " << Nnotreallygood << std::endl;
	
	// make dijet ratio vs pt plot
	TH1F *hDijetRatios_vs_pt = new TH1F("hDijetRatios_vs_pt","Dijet ratios vs dijet ptcut",25,1,26);
	TH1F *hDijetRatios_vs_pt_nobacktoback = new TH1F("hDijetRatios_vs_pt_nobacktoback","Dijet ratios vs dijet ptcut - no back to back",25,1,26);
	for (int ipt=0;ipt<25;ipt++) {
		hDijetRatios_vs_pt->SetBinContent(ipt+1,heflow_dijetpt[ipt]->GetMean()/heflow->GetMean());
		hDijetRatios_vs_pt->SetBinError(ipt+1,getRatioError(heflow,heflow_dijetpt[ipt]));
		hDijetRatios_vs_pt_nobacktoback->SetBinContent(ipt+1,heflow_dijetpt_nobacktoback[ipt]->GetMean()/heflow->GetMean());
		hDijetRatios_vs_pt_nobacktoback->SetBinError(ipt+1,getRatioError(heflow,heflow_dijetpt_nobacktoback[ipt]));
	}
	
	std::cout << "dijet ratio pt histo at 8 = " << hDijetRatios_vs_pt->GetBinContent(8) << std::endl;
	
	// do lumi correction
	TH1F *heflow_vs_Lumi = new TH1F("heflow_vs_Lumi","MB energy flow in CASTOR vs Inst. Lumi per BX",nLumiBins-1,LumiBins[0],LumiBins[nLumiBins-1]);
	for ( int iLumiBin=0;iLumiBin<nLumiBins;iLumiBin++) {
		heflow_vs_Lumi->SetBinContent(iLumiBin+1,heflow_perLumi[iLumiBin]->GetMean());
		heflow_vs_Lumi->SetBinError(iLumiBin+1,heflow_perLumi[iLumiBin]->GetMeanError());
	}
	
	std::cout << "passedL1Phys15 = " << passedL1Phys15 << std::endl;
	std::cout << "passedL1Phys15AndMB = " << passedL1Phys15AndMB << std::endl;
	
	
	//////////////////////////////////////////////////
	
	TH2F *hLSMeanE = new TH2F("hLSMeanE","Mean energy per channel per LS",303,193,496,224,1,225);
	for (int i=0;i<303;i++) {
		for (int j=0;j<224;j++) {
			if (hLS->GetBinContent(i+1,j+1) != 0) hLSMeanE->SetBinContent(i+1,j+1,hLSWeighted->GetBinContent(i+1,j+1)/hLS->GetBinContent(i+1,j+1));
			if (hLS->GetBinContent(i+1,j+1) != 0)
				hLSMeanE->SetBinError(i+1,j+1,getRatioError(hLSWeighted->GetBinContent(i+1,j+1),hLS->GetBinContent(i+1,j+1),hLSWeighted->GetBinError(i+1,j+1),hLS->GetBinError(i+1,j+1)));
		}
	}
	
	cout << "total number of events = " << totalevents << " from " << it << " file(s)" << endl;
	
	
	// create output root file
	Char_t filename[100];
	const char* part = currentfile.Data();
	sprintf(filename,"output_all_%s",part);
	TFile* output = new TFile(filename,"RECREATE");
	output->cd();
	
	//////////////////////////////////////////
	// Save all your histograms in a root file
	//////////////////////////////////////////
	
	// save rechit histos in file
	hNRecHits->Write();
	hRecHit_energy->Write();
	hRecHit_energy_clean->Write();
	hRecHit_time->Write();
	hRecHit_fC->Write();
	hRecHit_totalenergy->Write();
	hRecHit_module->Write();
	hRecHit_sector->Write();
	hRecHit_channel->Write();
	
	h2RecHit_EvsT->Write();
	hRecHit_WeightedTime->Write();
	
	hLS->Write();
	hLSWeighted->Write();
	hLSMeanE->Write();
	
	// eflow histos
	heflow->Write();
	heflow_dijet->Write();
	heflow_DijetRatio->Write();
	
	heflow_dijet8->Write();
	heflow_dijet12->Write();
	heflow_dijet20->Write();
	heflow_DijetRatio8->Write();
	heflow_DijetRatio12->Write();
	heflow_DijetRatio20->Write();
	
	for (int ipt=0;ipt<25;ipt++) {
		heflow_dijetpt[ipt]->Write();
		heflow_dijetpt_nobacktoback[ipt]->Write();
	}
	
	heflow_6m->Write();
	heflow_dijet_6m->Write();
	heflow_DijetRatio_6m->Write();
	
	heflow_14m->Write();
	heflow_dijet_14m->Write();
	heflow_DijetRatio_14m->Write();
	
	heflow_AllV->Write();
	heflow_dijet_AllV->Write();
	heflow_DijetRatio_AllV->Write();	
	
	h2eflow_grid->Write();
	h2eflow_map->Write();
	heflow_usedchannels->Write();
	heflow_sectors->Write();
	heflow_modules->Write();
	for (int icha=0;icha<224;icha++) {
		heflow_channel[icha]->Write();
	}
	heflow_channels->Write();
	//heflow_norm->Write();
	heflow_outoftime->Write();
	
	for (int icha=0;icha<maxVertices;icha++) {
		heflow_pileup[icha]->Write();
	}
	heflow_vs_pileup->Write();
	heflow_averagePU->Write();
	hEventSelection->Write();
	
	for (unsigned int iRun=0;iRun<Nruns;iRun++) {
		heflow_averagePUperRun[iRun]->Write();
		heflow_perRun[iRun]->Write();
		heflow_AllV_perRun[iRun]->Write();
	}
	
	h2L1Prescales->Write();
	heflow_vs_runs->Write();
	heflow_vs_runs_AllV->Write();
	haveragePU_vs_runs->Write();
	h2eflow_vs_averagePU->Write();
	
	PFJetpt->Write();
	PFJetpt20->Write();
	PFJetptdijet20->Write();
	PFJeteta->Write();
	PFJeteta20->Write();
	PFJetetadijet20->Write();
	JetMulti->Write();
	JetMultiGood->Write();
	JetMultiGoodCentral->Write();
	
	hDijetRatios_vs_pt->Write();
	hDijetRatios_vs_pt_nobacktoback->Write();
	
	heflow_InstLumi->Write();
	heflow_InstLumiPerBX->Write();
	heflow_InstLumi_AllV->Write();
	heflow_InstLumiPerBX_AllV->Write();
	
	for (int iLumiBin; iLumiBin<nLumiBins;iLumiBin++) {
		heflow_perLumi[iLumiBin]->Write();
	}
	heflow_vs_Lumi->Write();
	hL1After->Write();
	
	output->Close();
	std::cout << "file " << filename << " created." << std::endl;
	
}

Double_t TreeAnalyzer::getRatioError(TH1F * hMB, TH1F * hQCD) {
	
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

Double_t TreeAnalyzer::getRatioError(double	a, double b, double errora, double errorb) {
	
	Double_t error = 0;
	Double_t ratio = a/b;
	
	error = ratio*ratio*((errora*errora)/(a*a) + (errorb*errorb)/(b*b));
	error = sqrt(error);
	return error;
	
}

bool TreeAnalyzer::isPFDiJet(std::vector<MyJet> JetVector, bool backtoback, double usedetacut, double usedptcut) {
	
	using namespace std;
	
	//-- central jet selection
	
	bool accept = false;
	
	short int posJet1 = -1;
	short int posJet2 = -1;
	
	double refPt1 = 0;
	double refPt2 = 0;
	
	//-- find the two highest pt jets (corrected pt)
	
	for(vector<MyJet>::const_iterator jet = JetVector.begin(); jet < JetVector.end(); ++jet) {
		
		Double_t ptcal = jet->pt_cal;
		
		if(ptcal > refPt1) {
			refPt2 = refPt1;
			posJet2 = posJet1;      
			refPt1 = ptcal;
			posJet1 = jet - JetVector.begin();
		}
		
		else if(ptcal > refPt2) {
			refPt2 = ptcal;
			posJet2 = jet - JetVector.begin();
		}
		
	} 
	
	//-- apply the tight selection to them
	
	if(posJet1 >= 0 && posJet2 >= 0) {
		
		bool accept_jet1 = false;
		bool accept_jet2 = false;
		
		MyJet jet1 = JetVector.at(posJet1);
		MyJet jet2 = JetVector.at(posJet2);
		
		//-- jet 1 selection
		if(jet1.pt_cal > usedptcut && fabs(jet1.eta_cal) < usedetacut && jet1.TightPFJetId == true) accept_jet1 = true;
		
		//-- jet 2 selection
		if(jet2.pt_cal > usedptcut && fabs(jet2.eta_cal) < usedetacut && jet2.TightPFJetId == true) accept_jet2 = true;
		
		//-- final selection (back-to-back)
		
		if(accept_jet1 == true && accept_jet2 == true) {
			if (backtoback) {
				double deltaPhi = fabs(deltaPhi2(jet1.phi_cal, jet2.phi_cal));
				if (fabs(deltaPhi - M_PI) < 1.0) accept = true;
			} else {
				accept = true;
			}

		}
		
	} //-- posJet1 >= 0 && posJet2 >= 0
	return accept;
}


Double_t TreeAnalyzer::deltaPhi2(double phi1, double phi2) { 
    double result = phi1 - phi2;
    while (result > M_PI) result -= 2*M_PI;
    while (result <= -M_PI) result += 2*M_PI;
    return result;
}
