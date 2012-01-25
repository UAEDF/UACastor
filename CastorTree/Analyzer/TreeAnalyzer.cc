
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
#include <cmath>
#include <algorithm>
#include <ctime>
#include<sys/stat.h>
#include<sys/types.h>

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
#include "../src/MyBeamSpot.h"
#include "../src/MyGenPart.h"
#include "../src/MyCaloTower.h"
#include "../src/MyGenJet.h"
#include "../src/MyTrackJet.h"

TreeAnalyzer::TreeAnalyzer() { }

TreeAnalyzer::~TreeAnalyzer() { }


void TreeAnalyzer::Loop(TString inputdir, TObjArray* filelist, bool isData, double cmenergy) {
	
	
	using namespace std;
	int it = 0;
	int totalevents = 0;
	
	/////////////////////////////////////
	// Define all histograms
	/////////////////////////////////////
	
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
	TH1D *heflow_averagePUperRun[Nruns];
	TH1D *heflow_perRun[Nruns];
	TH1D *heflow_AllV_perRun[Nruns];
	double LumiBins[nLumiBins];
	double LumiBins2[nLumiBins];
	
	int Nmod = 5;
	double CASTORcut = 0;
	
	double MeanhadronMBflow = 0.;
	double MeandetectorMBflow = 0.;
	
	if (cmenergy == 900) {
		// ranges for 900 GeV - use this
		// data
		if (isData) {
			CASTORcut = 1.46; // GeV
		} else {
			CASTORcut = 1.46; // GeV
		}
		min = 0.015*-2000;
		max = 0.015*60000;
		channelmin = 0.015*-200;
		channelmax = 0.015*40000;
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
		LumiBins2[0] = 0.00000;
		LumiBins2[1] = 0.00005;
		LumiBins2[2] = 0.00010;
		LumiBins2[3] = 0.00015;
		LumiBins2[4] = 0.00020;
		LumiBins2[5] = 0.00025;
		LumiBins2[6] = 0.00030;
		LumiBins2[7] = 0.00035;
		LumiBins2[8] = 0.00040;
		LumiBins2[9] = 0.00045;
		runs[0] = 134721;
		runs[1] = 134725;
		heflow_averagePUperRun[0] = new TH1D("heflow_averagePUperRun_134721","Average number of vertices 134721",10,0,10);
		heflow_averagePUperRun[1] = new TH1D("heflow_averagePUperRun_134725","Average number of vertices 134725",10,0,10);
		heflow_perRun[0] = new TH1D("heflow_perRun_134721","Energy flow for run 134721",nBins,min,max);
		heflow_perRun[1] = new TH1D("heflow_perRun_134725","Energy flow for run 134725",nBins,min,max);
		heflow_AllV_perRun[0] = new TH1D("heflow_AllV_perRun_134721","Energy flow (1 or more Vtx) for run 134721",nBins,min,max);
		heflow_AllV_perRun[1] = new TH1D("heflow_AllV_perRun_134725","Energy flow (1 or more Vtx) for run 134725",nBins,min,max);
	} else if (cmenergy == 2760) {
        // ranges for 2760 GeV - use this
        // data
		if (isData) {
			CASTORcut = 1.46; // GeV
		} else {
			CASTORcut = 1.46; // GeV
		}
        min = 0.015*-2000;
        max = 0.015*120000; // was 100000
        channelmin = 0.015*-200;
        channelmax = 0.015*60000;
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
		for (int ibin=0;ibin<nLumiBins;ibin++) {
			LumiBins2[ibin] = 0.002+ibin*0.0002;
		}
		runs[0] = 161366;
		runs[1] = 161396;
		runs[2] = 161404;
		runs[3] = 161439;
		runs[4] = 161445;
		runs[5] = 161450;
		runs[6] = 161454;
		runs[7] = 161473;
		runs[8] = 161474;
		heflow_averagePUperRun[0] = new TH1D("heflow_averagePUperRun_161366","Average number of vertices 161366",10,0,10);
		heflow_averagePUperRun[1] = new TH1D("heflow_averagePUperRun_161396","Average number of vertices 161396",10,0,10);
		heflow_averagePUperRun[2] = new TH1D("heflow_averagePUperRun_161404","Average number of vertices 161404",10,0,10);
		heflow_averagePUperRun[3] = new TH1D("heflow_averagePUperRun_161439","Average number of vertices 161439",10,0,10);
		heflow_averagePUperRun[4] = new TH1D("heflow_averagePUperRun_161445","Average number of vertices 161445",10,0,10);
		heflow_averagePUperRun[5] = new TH1D("heflow_averagePUperRun_161450","Average number of vertices 161450",10,0,10);
		heflow_averagePUperRun[6] = new TH1D("heflow_averagePUperRun_161454","Average number of vertices 161454",10,0,10);
		heflow_averagePUperRun[7] = new TH1D("heflow_averagePUperRun_161473","Average number of vertices 161473",10,0,10);
		heflow_averagePUperRun[8] = new TH1D("heflow_averagePUperRun_161474","Average number of vertices 161474",10,0,10);
		heflow_perRun[0] = new TH1D("heflow_perRun_161366","Energy flow for run 161366",nBins,min,max);
		heflow_perRun[1] = new TH1D("heflow_perRun_161396","Energy flow for run 161396",nBins,min,max);
		heflow_perRun[2] = new TH1D("heflow_perRun_161404","Energy flow for run 161404",nBins,min,max);
		heflow_perRun[3] = new TH1D("heflow_perRun_161439","Energy flow for run 161439",nBins,min,max);
		heflow_perRun[4] = new TH1D("heflow_perRun_161445","Energy flow for run 161445",nBins,min,max);
		heflow_perRun[5] = new TH1D("heflow_perRun_161450","Energy flow for run 161450",nBins,min,max);
		heflow_perRun[6] = new TH1D("heflow_perRun_161454","Energy flow for run 161454",nBins,min,max);
		heflow_perRun[7] = new TH1D("heflow_perRun_161473","Energy flow for run 161473",nBins,min,max);
		heflow_perRun[8] = new TH1D("heflow_perRun_161474","Energy flow for run 161474",nBins,min,max);
		heflow_AllV_perRun[0] = new TH1D("heflow_AllV_perRun_161366","Energy flow (1 or more Vtx) for run 161366",nBins,min,max);
		heflow_AllV_perRun[1] = new TH1D("heflow_AllV_perRun_161396","Energy flow (1 or more Vtx) for run 161396",nBins,min,max);
		heflow_AllV_perRun[2] = new TH1D("heflow_AllV_perRun_161404","Energy flow (1 or more Vtx) for run 161404",nBins,min,max);
		heflow_AllV_perRun[3] = new TH1D("heflow_AllV_perRun_161439","Energy flow (1 or more Vtx) for run 161439",nBins,min,max);
		heflow_AllV_perRun[4] = new TH1D("heflow_AllV_perRun_161445","Energy flow (1 or more Vtx) for run 161445",nBins,min,max);
		heflow_AllV_perRun[5] = new TH1D("heflow_AllV_perRun_161450","Energy flow (1 or more Vtx) for run 161450",nBins,min,max);
		heflow_AllV_perRun[6] = new TH1D("heflow_AllV_perRun_161454","Energy flow (1 or more Vtx) for run 161454",nBins,min,max);
		heflow_AllV_perRun[7] = new TH1D("heflow_AllV_perRun_161473","Energy flow (1 or more Vtx) for run 161473",nBins,min,max);
		heflow_AllV_perRun[8] = new TH1D("heflow_AllV_perRun_161474","Energy flow (1 or more Vtx) for run 161474",nBins,min,max);
		
	} else if (cmenergy == 7000) {
        // ranges for 7 TeV - use this
        // data
		MeanhadronMBflow = 526.;
		MeandetectorMBflow = 269.;
		
		if (isData) {
			CASTORcut = 1.46; // GeV
		} else {
			CASTORcut = 1.46; // GeV
		}
        min = -30; //0.015*-2000; // to get whole spectrum: -2000
        max = 3750; //0.015*250000; // to get whole spectrum: 250000
        channelmin = 0.015*-200;
        channelmax = 0.015*120000;
		nBins = 252; // was 252
		ptcut = 20;
		lumimax = 0.1;
		lumiBXmax = 0.005;
		for (int ibin=0;ibin<nLumiBins;ibin++) {
			LumiBins[ibin] = 0.000+ibin*0.0005;
			LumiBins2[ibin] = 0.0025+ibin*0.00015;
		}
		runs[0] = 135059;
		runs[1] = 135521;
		runs[2] = 135523;
		runs[3] = 135525;
		runs[4] = 135528;
		runs[5] = 135535;
		runs[6] = 135573;
		runs[7] = 135575;
		heflow_averagePUperRun[0] = new TH1D("heflow_averagePUperRun_135059","Average number of vertices 135059",10,0,10);
		heflow_averagePUperRun[1] = new TH1D("heflow_averagePUperRun_135521","Average number of vertices 135521",10,0,10);
		heflow_averagePUperRun[2] = new TH1D("heflow_averagePUperRun_135523","Average number of vertices 135523",10,0,10);
		heflow_averagePUperRun[3] = new TH1D("heflow_averagePUperRun_135525","Average number of vertices 135525",10,0,10);
		heflow_averagePUperRun[4] = new TH1D("heflow_averagePUperRun_135528","Average number of vertices 135528",10,0,10);
		heflow_averagePUperRun[5] = new TH1D("heflow_averagePUperRun_135535","Average number of vertices 135535",10,0,10);
		heflow_averagePUperRun[6] = new TH1D("heflow_averagePUperRun_135573","Average number of vertices 135573",10,0,10);
		heflow_averagePUperRun[7] = new TH1D("heflow_averagePUperRun_135575","Average number of vertices 135575",10,0,10);
		heflow_perRun[0] = new TH1D("heflow_perRun_135059","Energy flow for run 135059",nBins,min,max);
		heflow_perRun[1] = new TH1D("heflow_perRun_135521","Energy flow for run 135521",nBins,min,max);
		heflow_perRun[2] = new TH1D("heflow_perRun_135523","Energy flow for run 135523",nBins,min,max);
		heflow_perRun[3] = new TH1D("heflow_perRun_135525","Energy flow for run 135525",nBins,min,max);
		heflow_perRun[4] = new TH1D("heflow_perRun_135528","Energy flow for run 135528",nBins,min,max);
		heflow_perRun[5] = new TH1D("heflow_perRun_135535","Energy flow for run 135535",nBins,min,max);
		heflow_perRun[6] = new TH1D("heflow_perRun_135573","Energy flow for run 135573",nBins,min,max);
		heflow_perRun[7] = new TH1D("heflow_perRun_135575","Energy flow for run 135575",nBins,min,max);
		heflow_AllV_perRun[0] = new TH1D("heflow_AllV_perRun_135059","Energy flow (1 or more Vtx) for run 135059",nBins,min,max);
		heflow_AllV_perRun[1] = new TH1D("heflow_AllV_perRun_135521","Energy flow (1 or more Vtx) for run 135521",nBins,min,max);
		heflow_AllV_perRun[2] = new TH1D("heflow_AllV_perRun_135523","Energy flow (1 or more Vtx) for run 135523",nBins,min,max);
		heflow_AllV_perRun[3] = new TH1D("heflow_AllV_perRun_135525","Energy flow (1 or more Vtx) for run 135525",nBins,min,max);
		heflow_AllV_perRun[4] = new TH1D("heflow_AllV_perRun_135528","Energy flow (1 or more Vtx) for run 135528",nBins,min,max);
		heflow_AllV_perRun[5] = new TH1D("heflow_AllV_perRun_135535","Energy flow (1 or more Vtx) for run 135535",nBins,min,max);
		heflow_AllV_perRun[6] = new TH1D("heflow_AllV_perRun_135573","Energy flow (1 or more Vtx) for run 135573",nBins,min,max);
		heflow_AllV_perRun[7] = new TH1D("heflow_AllV_perRun_135575","Energy flow (1 or more Vtx) for run 135575",nBins,min,max);
	}
	
	for (unsigned int iRun=0;iRun<Nruns;iRun++) {
		heflow_averagePUperRun[iRun]->Sumw2();
		heflow_perRun[iRun]->Sumw2();
		heflow_AllV_perRun[iRun]->Sumw2();
	}
	
	// default energy flow histos - using 5 modules
	TH1D *heflow_DijetRatio = new TH1D("heflow_DijetRatio","Dijet Ratio",1,0,1);
	TH1D *heflow_LeadingjetRatio = new TH1D("heflow_LeadingjetRatio","Leadingjet Ratio",1,0,1);
	TH1D *heflow;
	TH1D *heflow_toward;
	TH1D *heflow_away;
	TH1D *heflow_transverse;
	TH1D *heflow_dijet;
	TH1D *heflow_leadingjet;
	TH1D *heflow_toward_leadingjet;
	TH1D *heflow_away_leadingjet;
	TH1D *heflow_transverse_leadingjet;

	heflow = new TH1D("heflow","Total CASTOR energy flow",nBins,min,max); // for data -2000,60000
	heflow_toward = new TH1D("heflow_toward","CASTOR energy flow - toward region",nBins,min,max);
	heflow_away = new TH1D("heflow_away","CASTOR energy flow - away region",nBins,min,max);
	heflow_transverse = new TH1D("heflow_transverse","CASTOR energy flow - transverse region",nBins,min,max);
	heflow_dijet = new TH1D("heflow_dijet","total rechit GeV distribution for dijet events",nBins,min,max); // for mc -40,600
	heflow_leadingjet = new TH1D("heflow_leadingjet","Total CASTOR energy flow for leadingjet events",nBins,min,max); // for mc -40,600
	heflow_toward_leadingjet = new TH1D("heflow_toward_leadingjet","CASTOR energy flow - toward region for leadingjet events",nBins,min,max);
	heflow_away_leadingjet = new TH1D("heflow_away_leadingjet","CASTOR energy flow - away region for leadingjet events",nBins,min,max);
	heflow_transverse_leadingjet = new TH1D("heflow_transverse_leadingjet","CASTOR energy flow - transverse region for leadingjet events",nBins,min,max);
	
	// energy flow histos using 6 modules
	TH1D *heflow_leadingjetRatio_6m = new TH1D("heflow_leadingjetRatio_6m","leadingjet Ratio using 6 modules",1,0,1);
	TH1D *heflow_6m = new TH1D("heflow_6m","total rechit GeV distribution (6 modules)",nBins,min,max);
	TH1D *heflow_leadingjet_6m = new TH1D("heflow_leadingjet_6m","total rechit GeV distribution for leadingjet events (6 modules)",nBins,min,max);
	
	// energy flow histos using all modules
	TH1D *heflow_leadingjetRatio_14m = new TH1D("heflow_leadingjetRatio_14m","leadingjet Ratio using all modules",1,0,1);
	TH1D *heflow_14m = new TH1D("heflow_14m","total rechit GeV distribution (all modules)",nBins,min,max);                        
	TH1D *heflow_leadingjet_14m = new TH1D("heflow_leadingjet_14m","total rechit GeV distribution for leadingjet events (all modules)",nBins,min,max);
	
	// energy flow histos with no number of vertex conditions
	TH1D *heflow_leadingjetRatio_AllV = new TH1D("heflow_leadingjetRatio_AllV","leadingjet Ratio with no # vertices condition",1,0,1);
	TH1D *heflow_AllV = new TH1D("heflow_AllV","total rechit GeV distribution (all # vertices)",nBins,min,max);
	TH1D *heflow_leadingjet_AllV = new TH1D("heflow_leadingjet_AllV","total rechit GeV distribution for leadingjet events (all # vertices)",nBins,min,max);
	
	TH2D *h2eflow_grid = new TH2D("h2eflow_grid","energy weighted module vs sector distribution",16,1,17,14,1,15);
	TH2D *h2eflow_map = new TH2D("h2eflow_map","used channels map",16,1,17,14,1,15);
	TH1D *heflow_modules = new TH1D("heflow_modules","average energy in used modules",14,1,15);
	TH1D *heflow_sectors = new TH1D("heflow_sectors","average energy in used sectors",16,1,17);
	TH1D *heflow_sectors_leadingjet = new TH1D("heflow_sectors_leadingjet","Distribution of leadingjet sectors",16,1,17);
	TH1D *heflow_usedchannels = new TH1D("heflow_usedchannels","number of used channels to compute eflow",224,1,225);
	TH1D *heflow_channels = new TH1D("heflow_channels","average energy in used channels",80,1,81);
	TH1D *heflow_outoftime = new TH1D("heflow_outoftime","total rechit distribution for out of time rechits",nBins,min,max);
	TH1D *heflow_averagePU = new TH1D("heflow_averagePU","Distribution of # vertices per event",10,0,10);
	
	TH1D *hEventSelection = new TH1D("hEventSelection","Event Selection histogram",7,1,8);
	
	TH1D *heflow_channel[224];
	TH1D *heflow_leadingjet_channel[224];
	char name [100];
	char title [100];
	for (int i=0;i<224;i++) {
		sprintf(name,"heflow_channel_%d",i+1);
		sprintf(title,"Energy distribution for channel %d",i+1);
		heflow_channel[i] = new TH1D(name,title,100,channelmin,channelmax); 
		heflow_channel[i]->Sumw2();
		
		sprintf(name,"heflow_leadingjet_channel_%d",i+1);
		sprintf(title,"Leadingjet Energy distribution for channel %d",i+1);
		heflow_leadingjet_channel[i] = new TH1D(name,title,100,channelmin,channelmax); 
		heflow_leadingjet_channel[i]->Sumw2();
	}
	
	int maxVertices = 4;
	TH1D *heflow_pileup[maxVertices];
	for (int i=0;i<maxVertices;i++) {
		sprintf(name,"heflow_pileup_%d",i+1);
		sprintf(title,"Energy flow distribution for %d vertex events",i+1);
		heflow_pileup[i] = new TH1D(name,title,nBins,min,max); 
		heflow_pileup[i]->Sumw2();
	}
	
	int NptBins = 16;
	double ptbinning[17] = {0,0.3,1,2,3,5,7.5,10,12.5,15,17.5,20,22.5,25,30,40,50};
	
	TH1D *heflow_dijetpt[NptBins];
	TH1D *heflow_leadingjetpt[NptBins];
	TH1D *heflow_toward_leadingjetpt[NptBins];
	TH1D *heflow_away_leadingjetpt[NptBins];
	TH1D *heflow_transverse_leadingjetpt[NptBins];
	
	for (int i=0;i<NptBins;i++) {
		sprintf(name,"heflow_dijetpt_%d",i+1);
		sprintf(title,"Dijet Energy flow distribution with pt cut %d",i+1);
		heflow_dijetpt[i] = new TH1D(name,title,nBins,min,max);
		heflow_dijetpt[i]->Sumw2();
		
		sprintf(name,"heflow_leadingjetpt_%d",i+1);
		sprintf(title,"Leadingjet Energy flow distribution with pt cut %d",i+1);
		heflow_leadingjetpt[i] = new TH1D(name,title,nBins,min,max);
		heflow_leadingjetpt[i]->Sumw2();
		
		sprintf(name,"heflow_toward_leadingjetpt_%d",i+1);
		sprintf(title,"Toward region Leadingjet Energy flow distribution with pt cut %d",i+1);
		heflow_toward_leadingjetpt[i] = new TH1D(name,title,nBins,min,max);
		heflow_toward_leadingjetpt[i]->Sumw2();
		
		sprintf(name,"heflow_away_leadingjetpt_%d",i+1);
		sprintf(title,"away region Leadingjet Energy flow distribution with pt cut %d",i+1);
		heflow_away_leadingjetpt[i] = new TH1D(name,title,nBins,min,max);
		heflow_away_leadingjetpt[i]->Sumw2();
		
		sprintf(name,"heflow_transverse_leadingjetpt_%d",i+1);
		sprintf(title,"transverse region Leadingjet Energy flow distribution with pt cut %d",i+1);
		heflow_transverse_leadingjetpt[i] = new TH1D(name,title,nBins,min,max);
		heflow_transverse_leadingjetpt[i]->Sumw2();
		
	}
	
	
	TH1D *heflow_InstLumi = new TH1D("heflow_InstLumi","Instantanious Lumi distribution",500,0,lumimax);
	TH1D *heflow_InstLumiPerBX = new TH1D("heflow_InstLumiPerBX","Instantanious Lumi per BX distribution",nLumiBins,0,lumiBXmax);
	TH1D *heflow_InstLumi_AllV = new TH1D("heflow_InstLumi_AllV","Instantanious Lumi distribution AllV",500,0,lumimax);
	TH1D *heflow_InstLumiPerBX_AllV = new TH1D("heflow_InstLumiPerBX_AllV","Instantanious Lumi per BX distribution AllV",nLumiBins,0,lumiBXmax);
	
	TH1D *heflow_InstLumiPerBX2 = new TH1D("heflow_InstLumiPerBX2","Instantanious Lumi per BX distribution",nLumiBins,0.0025,0.004);
	heflow_InstLumiPerBX2->Sumw2();
	
	heflow_InstLumi->Sumw2();
	heflow_InstLumiPerBX->Sumw2();
	heflow_InstLumi_AllV->Sumw2();
	heflow_InstLumiPerBX_AllV->Sumw2();
	
	TH1D *heflow_perLumi[nLumiBins];
	TH1D *heflow_perLumi2[nLumiBins];
	TH1D *heflow_perLumi_leadingjet[nLumiBins];
	TH1D *heflow_perLumi_leadingjet2[nLumiBins];
	for (int i=0;i<nLumiBins;i++) {
		sprintf(name,"heflow_perLumi_%d",i+1);
		sprintf(title,"Energy flow distribution within Inst. lumi per BX bin %d",i+1);
		heflow_perLumi[i] = new TH1D(name,title,nBins,min,max);
		heflow_perLumi[i]->Sumw2();
		
		sprintf(name,"heflow_perLumi_leadingjet_%d",i+1);
		sprintf(title,"leadingjet Energy flow distribution within Inst. lumi per BX bin %d",i+1);
		heflow_perLumi_leadingjet[i] = new TH1D(name,title,nBins,min,max);
		heflow_perLumi_leadingjet[i]->Sumw2();
		
		sprintf(name,"heflow_perLumi2_%d",i+1);
		sprintf(title,"Energy flow distribution within Inst. lumi per BX bin %d",i+1);
		heflow_perLumi2[i] = new TH1D(name,title,nBins,min,max);
		heflow_perLumi2[i]->Sumw2();
		
		sprintf(name,"heflow_perLumi_leadingjet2_%d",i+1);
		sprintf(title,"leadingjet Energy flow distribution within Inst. lumi per BX bin %d",i+1);
		heflow_perLumi_leadingjet2[i] = new TH1D(name,title,nBins,min,max);
		heflow_perLumi_leadingjet2[i]->Sumw2();
		
	}
	
	// plot beamspot information
	TH1D *hBeamSpot_x = new TH1D("hBeamSpot_x","BeamSpot x coordinate",100,-1,1);
	TH1D *hBeamSpot_y = new TH1D("hBeamSpot_y","BeamSpot y coordinate",100,-1,1);
	TH1D *hBeamSpot_z = new TH1D("hBeamSpot_z","BeamSpot z coordinate",100,-2,2);
	
	TH1D *hBeamSpot_dxdz = new TH1D("hBeamSpot_dxdz","BeamSpot dxdz angle",100,-0.01,0.01);
	TH1D *hBeamSpot_dydz = new TH1D("hBeamSpot_dydz","BeamSpot dydz angle",100,-0.01,0.01);
	TH1D *hBeamSpot_sigmaZ = new TH1D("hBeamSpot_sigmaZ","BeamSpot sigmaZ angle",100,0,8);
	
	// hadron level histograms
	TH1D *heflow_hadronlevel;
	TH1D *heflow_dijet_hadronlevel;
	TH1D *heflow_leadingjet_hadronlevel;
	TH1D *heflow_LeadingjetRatio_hadronlevel = new TH1D("heflow_LeadingjetRatio_hadronlevel","Leadingjet Ratio Hadron level",1,0,1);

	heflow_hadronlevel = new TH1D("heflow_hadronlevel","Hadron level MB energy flow in CASTOR",nBins,min,max);
	heflow_dijet_hadronlevel = new TH1D("heflow_dijet_hadronlevel","Hadron level dijet energy flow in CASTOR",nBins,min,max);
	heflow_leadingjet_hadronlevel = new TH1D("heflow_leadingjet_hadronlevel","Hadron level leadingjet energy flow in CASTOR",nBins,min,max);
	
	TH1D *hhadron_energy = new TH1D("hhadron_energy","Hadron level energy distribution",nBins,min,max);
	TH1D *hhadron_eta = new TH1D("hhadron_eta","Hadron level eta distribution",100,-15,15);
	TH1D *hhadron_phi = new TH1D("hhadron_phi","Hadron level phi distribution",100,-3.15,3.15);
	
	TH1D *hxi = new TH1D("hxi","log10(Xi) distribution off all the events",55,-10,1);
	TH1D *hxix = new TH1D("hxix","log10(Xix) distribution off all the events",55,-10,1);
	TH1D *hxiy = new TH1D("hxiy","log10(Xiy) distribution off all the events",55,-10,1);
	TH1D *hxidd = new TH1D("hxidd","log10(Xidd) distribution off all the events",125,-20,5);
	TH1D *hxiddln = new TH1D("hxiddln","log10(Xidd) distribution off all the events",150,-20,10);
	TH1D *hxiddlninverse = new TH1D("hxiddlninverse","log10(Xidd) distribution off all the events",300,-10,50);
	TH1D *hetamax = new TH1D("hetamax","Delta(etamax) of all the events",200,0,20);
	TH1D *hxi_withDetectorCuts = new TH1D("hxi_withDetectorCuts","log10(Xi) distribution off all the events that pass on detector level",55,-10,1);
	TH1D *hxix_withDetectorCuts = new TH1D("hxix_withDetectorCuts","log10(Xix) distribution off all the events that pass on detector level",55,-10,1);
	TH1D *hxiy_withDetectorCuts = new TH1D("hxiy_withDetectorCuts","log10(Xiy) distribution off all the events that pass on detector level",55,-10,1);
	TH1D *hxidd_withDetectorCuts = new TH1D("hxidd_withDetectorCuts","log10(Xidd) distribution off all the events that pass on detector level",125,-20,5);
	TH1D *hetamax_withDetectorCuts = new TH1D("hetamax_withDetectorCuts","Delta(etamax) of all the events that pass on detector level",200,0,20);
	
	TH2D *h2xixxiy = new TH2D("h2xixxiy","log10(Xiy) vs log10(Xix) distribution off all the events",55,-10,1,55,-10,1);
	TH2D *h2xixxiy_withDetectorCuts = new TH2D("h2xixxiy_withDetectorCuts","log10(Xiy) vs log10(Xix) distribution off all the events that pass on detector level",55,-10,1,55,-10,1);
	TH2D *h2xixxiy_withXiddCut = new TH2D("h2xixxiy_withXiddCut","log10(Xiy) vs log10(Xix) distribution off all the events with log10(Xidd) > -1.6 Cut",55,-10,1,55,-10,1);
	
	heflow_hadronlevel->Sumw2();
	heflow_dijet_hadronlevel->Sumw2();
	heflow_leadingjet_hadronlevel->Sumw2();
	hhadron_energy->Sumw2();
	hhadron_eta->Sumw2();
	hhadron_phi->Sumw2();
	
	TH1D *heflow_dijetpt_hadronlevel[NptBins];
	TH1D *heflow_leadingjet_chargedgenjets_hadronlevel[NptBins];
	TH2D *h2detvshad_ratiopt[NptBins];
	for (int i=0;i<NptBins;i++) {
		sprintf(name,"heflow_dijetpt_hadronlevel_%d",i+1);
		sprintf(title,"Hadron level Dijet Energy flow distribution with pt cut %d",i+1);
		heflow_dijetpt_hadronlevel[i] = new TH1D(name,title,nBins,min,max);
		heflow_dijetpt_hadronlevel[i]->Sumw2();
		
		sprintf(name,"heflow_leadingjet_chargedgenjets_hadronlevel_%d",i+1);
		sprintf(title,"ChargedGenJets Hadron level Leadingjet Energy flow distribution with pt cut %d",i+1);
		heflow_leadingjet_chargedgenjets_hadronlevel[i] = new TH1D(name,title,nBins,min,max);
		heflow_leadingjet_chargedgenjets_hadronlevel[i]->Sumw2();
		
		sprintf(name,"h2detvshad_ratiopt_%d",i+1);
		sprintf(title,"Detector level leadingjet ratio vs hadron level leadingjet ratio with pt cut %d",i+1);
		h2detvshad_ratiopt[i] = new TH2D(name,title,44,-1,10,44,-1,10);
		h2detvshad_ratiopt[i]->Sumw2();
	}
	
	// hadron level corrections
	TH1D *hRatioDist_hadronlevel = new TH1D("hRatioDist_hadronlevel","hadron level leadingjet ratio distribution",40,0,10);
	TH1D *hRatioDist_detectorlevel = new TH1D("hRatioDist_detectorlevel","detector level leadingjet ratio distribution",40,0,10);
	TH2D *h2detvshad_ratio = new TH2D("h2detvshad_ratio","Detector level leadingjet ratio vs hadron level leadingjet ratio",40,0,10,40,0,10);
	
	hRatioDist_detectorlevel->Sumw2();
	hRatioDist_hadronlevel->Sumw2();
	h2detvshad_ratio->Sumw2();
	
	// calotower histograms
	TH1D *hCaloTower_energy = new TH1D("hCaloTower_energy","Calotower HF energy distribution",100,0,1500);
	TH1D *hCaloTower_eta = new TH1D("hCaloTower_eta","Calotower HF eta distribution",96,-6,6);
	TH1D *hCaloTower_phi = new TH1D("hCaloTower_phi","Calotower HF phi distribution",100,-3.15,3.15);
	TH1D *hCaloTower_zside = new TH1D("hCaloTower_zside","Calotower HF zside distribution",3,-1,2);
	TH1D *hHFPluseflow = new TH1D("hHFPluseflow","HF Plus eflow",5,3.15,4.90);
	TH1D *hHFMinuseflow = new TH1D("hHFMinuseflow","HF Minus eflow",5,-4.90,-3.15);
	
	hCaloTower_energy->Sumw2();
	hCaloTower_eta->Sumw2();
	hCaloTower_phi->Sumw2();
	hCaloTower_zside->Sumw2();
	hHFPluseflow->Sumw2();
	hHFMinuseflow->Sumw2();
	
	
	
	
	// put sumw2's for some histos
	heflow_modules->Sumw2();
	heflow_sectors->Sumw2();
	heflow_sectors_leadingjet->Sumw2();
	heflow_channels->Sumw2();
	heflow_averagePU->Sumw2();
	heflow->Sumw2();
	heflow_toward->Sumw2();
	heflow_away->Sumw2();
	heflow_transverse->Sumw2();
	heflow_dijet->Sumw2();
	heflow_leadingjet->Sumw2();
	heflow_toward_leadingjet->Sumw2();
	heflow_away_leadingjet->Sumw2();
	heflow_transverse_leadingjet->Sumw2();
	heflow_DijetRatio->Sumw2();
	heflow_LeadingjetRatio_hadronlevel->Sumw2();
	heflow_LeadingjetRatio->Sumw2();
	heflow_usedchannels->Sumw2();
	heflow_14m->Sumw2();
	heflow_leadingjet_14m->Sumw2();
	heflow_leadingjetRatio_14m->Sumw2();
	heflow_AllV->Sumw2();
	heflow_leadingjet_AllV->Sumw2();
	heflow_leadingjetRatio_AllV->Sumw2();
	
	TIter       next(filelist); 
	TObjString* fn = 0;
	TString currentfile = "";
	
	bool isMC = false;
	
	double IntegratedLumi = 0;
	
	
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
		MyBeamSpot *BeamSpot = NULL;
		MyDiJet *dijet = NULL;
		MyHLTrig *HLTrig = NULL;
		MyL1Trig *L1Trig = NULL;
		std::vector<MyVertex> *Vertices = NULL;
		std::vector<MyCastorRecHit> *CastorRecHits = NULL;
		//std::vector<MyCastorDigi> *CastorDigis = NULL;
		std::vector<MyJet> *PFJets = NULL;
		std::vector<MyGenPart> *genParts = NULL;
		std::vector<MyCaloTower> *caloTowers = NULL;
		std::vector<MyGenJet> *genJets = NULL;
		std::vector<MyGenJet> *chargedGenJets = NULL;
		std::vector<MyTrackJet> *trackJets = NULL;
		
		TBranch *b_evtid = tree->GetBranch("EvtId");
		TBranch *b_BeamSpot = tree->GetBranch("beamSpot");
		TBranch *b_dijet = tree->GetBranch("pfDiJet");
		TBranch *b_HLTrig = tree->GetBranch("HLTrig");
		TBranch *b_L1Trig = tree->GetBranch("L1Trig");
		TBranch *b_vertices = tree->GetBranch("primaryVertex");
		TBranch *b_castorrechits = tree->GetBranch("castorRecHit");
		//TBranch *b_castordigis = tree->GetBranch("castorDigi");
		TBranch *b_PFJets = tree->GetBranch("pfJet");
		TBranch *b_genParts = NULL;
		if (!isData) b_genParts = tree->GetBranch("GenPart");
		TBranch *b_caloTowers = tree->GetBranch("caloTower");
		TBranch *b_genJets = NULL;
		TBranch *b_chargedGenJets = NULL;
		if (!isData) b_genJets = tree->GetBranch("GenJet");
		if (!isData) b_chargedGenJets = tree->GetBranch("ChargedGenJet");
		TBranch *b_trackJets = tree->GetBranch("trackJet");
		
		b_evtid->SetAddress(&evtid);
		b_BeamSpot->SetAddress(&BeamSpot);
		b_dijet->SetAddress(&dijet);
		b_HLTrig->SetAddress(&HLTrig);
		b_L1Trig->SetAddress(&L1Trig);
		b_vertices->SetAddress(&Vertices);
		b_castorrechits->SetAddress(&CastorRecHits);
		b_PFJets->SetAddress(&PFJets);
		if (!isData) b_genParts->SetAddress(&genParts);
		b_caloTowers->SetAddress(&caloTowers);
		if (!isData) b_genJets->SetAddress(&genJets);
		if (!isData) b_chargedGenJets->SetAddress(&chargedGenJets);
		b_trackJets->SetAddress(&trackJets);
		
		int Nevents = tree->GetEntriesFast();
		std::cout << "events in this file = " << Nevents << std::endl;
		//totalevents += Nevents;
		
		// start event loop
		for (int i=0;i<Nevents;i++) {
			
			bool passedHadronCuts = false;
			bool passedDetectorCuts = false;
			
			double hadron_eflow = -99999;
			double detector_eflow = -99999;
			double hadron_eflow_dijet = -99999;
			double detector_eflow_dijet = -99999;
			double hadron_eflow_leadingjet = -99999;
			double detector_eflow_leadingjet = -99999;
			
			double xix = 10;
			double xiy = 10;
			double xi = 10;
			double xidd = 10e10;
			double etamax = -1;
			
			/////////////////////////////////////////
			// Hadron level code
			/////////////////////////////////////////
			
			if (!isData) {
				b_genParts->GetEntry(i);
				
				// look for particles in HF+ & HF- in BSC range
				bool HadronHFplus = false;
				bool HadronHFminus = false;
				for (unsigned int ipart = 0;ipart<genParts->size();ipart++) {
					MyGenPart particle = (*genParts)[ipart];
					if (particle.status == 1) {
						if (particle.Eta() > 3.23 && particle.Eta() < 4.65 && particle.E() > 4.) HadronHFplus = true; // exclude neutrino's and muons?
						if (particle.Eta() < -3.23 && particle.Eta() > -4.65 && particle.E() > 4.) HadronHFminus = true; // exclude neutrino's and muons?
					}
				}
				
				// CASTOR activity
				bool HadronCASTOR_Activity = false;
				for (unsigned int ipart = 0;ipart<genParts->size();ipart++) {
					MyGenPart particle = (*genParts)[ipart];
					if (particle.status == 1) {
						if (particle.Eta() < -5.2 && particle.Eta() > -6.6 && particle.E() > 0.) HadronCASTOR_Activity = true; // exclude neutrino's and muons?
					} // energy cut ?
				}
				
				// vertex condition
				bool Hadronvertexok = false;
				int Ncharged = 0;
				for (unsigned int ipart = 0;ipart<genParts->size();ipart++) {
					MyGenPart particle = (*genParts)[ipart];
					if (particle.status == 1) {
						if (fabs(particle.Eta()) < 2.5 && particle.Pt() > 0.3 && particle.charge != 0) Ncharged++; // Pt cut ?
					}
				}
				if (Ncharged > 3) Hadronvertexok = true;
				
				// combine selection
				if (HadronHFplus && HadronHFminus && HadronCASTOR_Activity && Hadronvertexok) passedHadronCuts = true;
				
				
				
				
				
				
				// calculate xi of the event
				
				// sort genParticles in eta, from eta_min to eta_max
				std::vector<MyGenPart> myTempParticles;
				std::vector<MyGenPart> myEtaSortedParticles;
				// copy only final stable particles with realistic eta in tempvector
				for (unsigned int ipart=0;ipart<genParts->size();ipart++) {
					if ((*genParts)[ipart].status == 1 && (*genParts)[ipart].Eta() > -1000. && (*genParts)[ipart].Eta() < 1000.) 
						myTempParticles.push_back((*genParts)[ipart]);
				}
				// do actual sorting
				while (myTempParticles.size() != 0) {
					double min_eta = 10000;
					int min_eta_pos = -1;
					for (unsigned int ipart = 0;ipart<myTempParticles.size();ipart++) {
						if (myTempParticles[ipart].Eta() < min_eta) {
							min_eta = myTempParticles[ipart].Eta();
							min_eta_pos = ipart;
						}
					}
					myEtaSortedParticles.push_back(myTempParticles[min_eta_pos]);
					myTempParticles.erase(myTempParticles.begin()+min_eta_pos);
				}
				
				// find deltaymax
				double deltaymax = 0;
				int deltaymax_pos = -1;
				for (unsigned int ipart=0;ipart<myEtaSortedParticles.size()-1;ipart++) {
					double deltay = myEtaSortedParticles[ipart+1].Eta() - myEtaSortedParticles[ipart].Eta();
					if (deltay > deltaymax) {
						deltaymax = deltay;
						deltaymax_pos = ipart;
					}
				}
				etamax = deltaymax;
				
				// calculate Mx2 and My2
				long double XEtot = 0;
				long double XPxtot = 0;
				long double XPytot = 0;
				long double XPztot = 0;
				long double YEtot = 0;
				long double YPxtot = 0;
				long double YPytot = 0;
				long double YPztot = 0;
				
				for (int ipart=0;ipart<=deltaymax_pos;ipart++) {
					XEtot += myEtaSortedParticles[ipart].E();
					XPxtot += myEtaSortedParticles[ipart].Px();
					XPytot += myEtaSortedParticles[ipart].Py();
					XPztot += myEtaSortedParticles[ipart].Pz();
				}
				long double Mx2 = -1.;
				Mx2 = XEtot*XEtot - XPxtot*XPxtot - XPytot*XPytot - XPztot*XPztot;
				
				for (unsigned int ipart=deltaymax_pos+1;ipart<myEtaSortedParticles.size();ipart++) {
					YEtot += myEtaSortedParticles[ipart].E();
					YPxtot += myEtaSortedParticles[ipart].Px();
					YPytot += myEtaSortedParticles[ipart].Py();
					YPztot += myEtaSortedParticles[ipart].Pz();
				}
				long double My2 = YEtot*YEtot - YPxtot*YPxtot - YPytot*YPytot - YPztot*YPztot;
				
				// calculate xix and xiy
				xix = Mx2/(cmenergy*cmenergy);
				xiy = My2/(cmenergy*cmenergy);
				
				// xi of event is max
				xi = std::max(xix,xiy);
				xidd = (Mx2*My2)/(cmenergy*cmenergy*0.938*0.938);
				
				hxi->Fill(log10(xi));
				hxix->Fill(log10(xix));
				hxiy->Fill(log10(xiy));
				hxidd->Fill(log10(xidd));
				hxiddln->Fill(log(xidd));
				hxiddlninverse->Fill(log(1./xidd));
				hetamax->Fill(etamax);
				h2xixxiy->Fill(log10(xix),log10(xiy));
				if (passedHadronCuts) h2xixxiy_withXiddCut->Fill(log10(xix),log10(xiy));
				
				double CASTOReflow = 0;
				for (unsigned int ipart = 0;ipart<genParts->size();ipart++) {
					MyGenPart particle = (*genParts)[ipart];
					if (particle.status == 1) {
						// control plots
						hhadron_energy->Fill(particle.E());
						hhadron_eta->Fill(particle.Eta());
						hhadron_phi->Fill(particle.Phi());
						// fill castor eflow
						if (particle.Eta() < -5.2 && particle.Eta() > -6.6 && particle.E() > 0.) {
							bool cond1 = false;
							bool cond2 = false;
							bool cond3 = false;
							if (particle.pdgId != 12 && particle.pdgId != 14 && particle.pdgId != 16) cond1 = true;
							if (particle.pdgId != -12 && particle.pdgId != -14 && particle.pdgId != -16) cond2 = true;
							if (particle.pdgId != 13 && particle.pdgId != -13) cond3 = true;
							if (cond1 && cond2 && cond3) {
								CASTOReflow += particle.E();
							}
						}
					}
				}

				hadron_eflow = CASTOReflow;
				
				// if event passed xi cut, execute analysis code
				if (passedHadronCuts) {
					
					heflow_hadronlevel->Fill(CASTOReflow);
					
					// do dijet selection 
					b_genJets->GetEntry(i);
					b_chargedGenJets->GetEntry(i);
					
					// check for dijet system
					if (isGenDiJet(*genJets,true,2.5,ptcut)) {
						heflow_dijet_hadronlevel->Fill(CASTOReflow);
						hadron_eflow_dijet = CASTOReflow;
					}
					// check for leading charged genjet
					int posLeadingChargedGenJet = posLeadingGenJet(*chargedGenJets,2.,1.);
					if (posLeadingChargedGenJet != -1) {
						if ((*chargedGenJets)[posLeadingChargedGenJet].Pt() > ptcut) {
							heflow_leadingjet_hadronlevel->Fill(CASTOReflow);
							hadron_eflow_leadingjet = CASTOReflow;
						}
						for (int ipt=0;ipt<NptBins;ipt++) {
							if ((*chargedGenJets)[posLeadingChargedGenJet].Pt() > ptbinning[ipt] && (*chargedGenJets)[posLeadingChargedGenJet].Pt() < ptbinning[ipt+1]) 
								heflow_leadingjet_chargedgenjets_hadronlevel[ipt]->Fill(CASTOReflow);
						}
					}
					
					// pt evolution, do manual dijet selection
					for (int ipt=0;ipt<NptBins;ipt++) {
						if ( isGenDiJet(*genJets,true,2.5,ptbinning[ipt],ptbinning[ipt+1],true)) heflow_dijetpt_hadronlevel[ipt]->Fill(CASTOReflow);
					}
					
				} // end if passedHadronCuts
				
			} // end if not data
			
			/////////////////////////////////////////
			// Do stuff before filters
			/////////////////////////////////////////
			
			b_evtid->GetEntry(i);
			b_HLTrig->GetEntry(i);
			b_L1Trig->GetEntry(i);
			b_vertices->GetEntry(i);
			b_caloTowers->GetEntry(i);
			b_castorrechits->GetEntry(i);
			
			// only process a certain run
			//if (evtid->Run == 135535) continue;
			
			// before any filter, fill first bin in histo which is total number of events
			hEventSelection->Fill(1,1);
			
			/////////////////////////////////////////
			// Filter the results
			/////////////////////////////////////////
			
			if (isData) {
				
				// filter results
				// filter on phys declared bit
				bool physDeclresult = HLTrig->HLTmap["physDeclpath"];
				
				// filter on castor invalid data
				bool castorInvalidDataFilterresult = HLTrig->HLTmap["castorInvalidDataFilterpath"];
				
				// filter out scraping events
				bool noscrapingresult = HLTrig->HLTmap["noscrapingpath"];
				
				bool gooddata = physDeclresult && castorInvalidDataFilterresult && noscrapingresult;
				
				// L1 filter
				
				bool L1_BX = L1Trig->fTechDecisionBefore[0];
				bool L1_Veto = !L1Trig->fTechDecisionBefore[36] && !L1Trig->fTechDecisionBefore[37] && !L1Trig->fTechDecisionBefore[38] && !L1Trig->fTechDecisionBefore[39];
				
				bool L1_BSC = L1Trig->fTechDecisionBefore[40] || L1Trig->fTechDecisionBefore[41]; // default value for 900 GeV or 7000 GeV 
				if (cmenergy == 2760) L1_BSC = L1Trig->fPhysDecisionBefore[126];
				
				bool HLT_BSC = true; // default value for 900 GeV or 7000 GeV (do we need an HLT here?)
				if (cmenergy == 2760) HLT_BSC = HLTrig->HLTmap["HLT_L1BscMinBiasORBptxPlusANDMinus_v1"];
				
				bool TriggerSelection = L1_BX && L1_Veto && L1_BSC && HLT_BSC;
				
				// ask for activity in HF
				bool HF_Activity = true;
				bool HFplus = false;
				bool HFminus = false;
				for (unsigned int itow=0;itow<caloTowers->size();itow++) {
					MyCaloTower mytow = (*caloTowers)[itow];
					if (mytow.hasHF && mytow.Energy() > 4. && mytow.zside == 1 && mytow.Eta() > 3.23 && mytow.Eta() < 4.65) HFplus = true;
					if (mytow.hasHF && mytow.Energy() > 4. && mytow.zside == -1 && mytow.Eta() < -3.23 && mytow.Eta() > -4.65) HFminus = true;
				}
				if (!HFplus || !HFminus) HF_Activity = false; // real HF condition... 
				
				// ask for activity in CASTOR
				bool CASTOR_Activity = false; 
				double towers[16];
				for (int itow=0;itow<16;itow++) towers[itow] = 0;
				for (unsigned int irh=0;irh<CastorRecHits->size();irh++) {
					MyCastorRecHit rechit = (*CastorRecHits)[irh];
					if (rechit.mod <= Nmod) towers[rechit.sec-1] += 0.015*rechit.energy; // this is intercalibrated fC in data
				}
				for (int itow=0;itow<16;itow++) {
					if (towers[itow] > CASTORcut) CASTOR_Activity = true;
				}
				
				// get vertex info
				// do the oneGoodVertexFilter
				bool wehaveGoodVertex = false;
				for (unsigned int iVert=0;iVert<Vertices->size();iVert++) {
					MyVertex vertex = (*Vertices)[iVert];
					if (vertex.isGoodVertex) wehaveGoodVertex = true;
				}
				
				if (physDeclresult) hEventSelection->Fill(2,1);
				if (physDeclresult && castorInvalidDataFilterresult) hEventSelection->Fill(3,1);
				if (gooddata) hEventSelection->Fill(4,1);
				if (gooddata && TriggerSelection) hEventSelection->Fill(5,1);
				if (gooddata && TriggerSelection && HF_Activity && CASTOR_Activity) hEventSelection->Fill(6,1);
				if (gooddata && TriggerSelection && HF_Activity && CASTOR_Activity && wehaveGoodVertex) passedDetectorCuts = true;
				
			} else {
				
				// MC
				
				// ask for activity in HF
				bool HF_Activity = true; 
				bool HFplus = false;
				bool HFminus = false;
				for (unsigned int itow=0;itow<caloTowers->size();itow++) {
					MyCaloTower mytow = (*caloTowers)[itow];
					if (mytow.hasHF && mytow.Energy() > 4. && mytow.zside == 1 && mytow.Eta() > 3.23 && mytow.Eta() < 4.65) HFplus = true;
					if (mytow.hasHF && mytow.Energy() > 4. && mytow.zside == -1 && mytow.Eta() < -3.23 && mytow.Eta() > -4.65) HFminus = true;
				}
				if (!HFplus || !HFminus) HF_Activity = false; // real HF condition... 
				
				// ask for activity in CASTOR
				bool CASTOR_Activity = false;
				double towers[16];
				for (int itow=0;itow<16;itow++) towers[itow] = 0;
				for (unsigned int irh=0;irh<CastorRecHits->size();irh++) {
					MyCastorRecHit rechit = (*CastorRecHits)[irh];
					if (rechit.mod <= Nmod) towers[rechit.sec-1] += 0.015*rechit.fC; // for MC access fC as energy is in GeV
				}
				for (int itow=0;itow<16;itow++) {
					if (towers[itow] > CASTORcut) CASTOR_Activity = true;
				}
				
				// get vertex info
				// do the oneGoodVertexFilter
				bool wehaveGoodVertex = false;
				for (unsigned int iVert=0;iVert<Vertices->size();iVert++) {
					MyVertex vertex = (*Vertices)[iVert];
					if (vertex.isGoodVertex) wehaveGoodVertex = true;
				}
				
				if (HF_Activity && CASTOR_Activity) hEventSelection->Fill(6,1);
				if (HF_Activity && CASTOR_Activity && wehaveGoodVertex) passedDetectorCuts = true;
				
			}
				
			/////////////////////////////////////////
			// Do stuff after filters
			/////////////////////////////////////////
			
			// get all the remaining branch entries
			b_dijet->GetEntry(i);
			b_PFJets->GetEntry(i);
			b_trackJets->GetEntry(i);
			b_BeamSpot->GetEntry(i);
				
			if (passedDetectorCuts) {
				
				// get beamspot info
				hBeamSpot_x->Fill(BeamSpot->x);
				hBeamSpot_y->Fill(BeamSpot->y);
				hBeamSpot_z->Fill(BeamSpot->z);
				hBeamSpot_dxdz->Fill(BeamSpot->dxdz);
				hBeamSpot_dydz->Fill(BeamSpot->dydz);
				hBeamSpot_sigmaZ->Fill(BeamSpot->sigmaZ);
				
				// get average number of vertices per run
				for (unsigned int iRun=0;iRun<Nruns;iRun++) {
					if (evtid->Run == runs[iRun]) heflow_averagePUperRun[iRun]->Fill(Vertices->size());
				}
				heflow_averagePU->Fill(Vertices->size());
				
				// fill the inst lumi distributions
				heflow_InstLumi_AllV->Fill(evtid->IstLumi);
				heflow_InstLumiPerBX_AllV->Fill(evtid->IstLumiPerBX);
				
				// check caloTowers
				for (unsigned int itow=0;itow<caloTowers->size();itow++) {
					MyCaloTower mytow = (*caloTowers)[itow];
					if (mytow.hasHF) {
						hCaloTower_energy->Fill(mytow.Energy());
						hCaloTower_eta->Fill(mytow.Eta());
						hCaloTower_phi->Fill(mytow.Phi());
						hCaloTower_zside->Fill(mytow.zside);
						if (mytow.Energy() > 4.) hHFPluseflow->Fill(std::abs(mytow.Eta()),mytow.Energy());
					}
				}
				
				
				
				/////////////////////////////////////////
				// Start Nvertex == 1 part of the code 
				/////////////////////////////////////////
				
				// only fill the histograms when there's 1 vertex (filter out pile-up)
				if (Vertices->size() == 1) {
					
					hEventSelection->Fill(7,1);
					
					hxi_withDetectorCuts->Fill(log10(xi));
					hxix_withDetectorCuts->Fill(log10(xix));
					hxiy_withDetectorCuts->Fill(log10(xiy));
					hxidd_withDetectorCuts->Fill(log10(xidd));
					hetamax_withDetectorCuts->Fill(etamax);
					h2xixxiy_withDetectorCuts->Fill(log10(xix),log10(xiy));
					
					// get event id stuff
					if( ((i+1) % 1000) == 0) cout << " run " << evtid->Run << " isData = " << evtid->IsData << " lumiblock " << 
						evtid->LumiBlock << " event " << evtid->Evt << endl; 
					if (!evtid->IsData) isMC = true;
					IntegratedLumi += evtid->IstLumi;
					
					// fill the inst lumi distributions
					heflow_InstLumi->Fill(evtid->IstLumi);
					heflow_InstLumiPerBX->Fill(evtid->IstLumiPerBX);
					heflow_InstLumiPerBX2->Fill(evtid->IstLumiPerBX);
					
					// check for leading trackjet
					bool leadingjet = false;
					int leadingsector = -1;
					int posLeadingTrackJetresult = posLeadingTrackJet(*trackJets,2.,1.);
					if (posLeadingTrackJetresult != -1) {
						if ((*trackJets)[posLeadingTrackJetresult].pt_raw > ptcut) {
							leadingjet = true;
							leadingsector = rad2Sector((*trackJets)[posLeadingTrackJetresult].phi_raw);
							heflow_sectors_leadingjet->Fill(leadingsector);
							//std::cout << " leading jet phi = " << (*trackJets)[posLeadingTrackJetresult].phi_raw << " leading jet sector = " << leadingsector << std::endl;
						}
					}
					
					// fill eflow and leadingjet histograms
					double eflow = 0;
					double eflow_toward = 0;
					double eflow_away = 0;
					double eflow_transverse = 0;
					double eflow_m6 = 0;
					double eflow_m14 = 0;
					int usedchannels = 0;
					double outoftime_eflow = 0;
					for (unsigned int j=0;j<CastorRecHits->size();j++) {
						MyCastorRecHit rechit = (*CastorRecHits)[j];
						h2eflow_map->Fill(rechit.sec,rechit.mod,1);
						if (rechit.cha != 5 && rechit.cha != 6) { // for data 15,35,81,5,6
							if (evtid->IsData) { // for data, energy is intercalibrated fC
								heflow_channel[rechit.cha-1]->Fill(0.015*rechit.energy);
								if (leadingjet) heflow_leadingjet_channel[rechit.cha-1]->Fill(0.015*rechit.energy);
								if (rechit.cha <= 80) {
									eflow += 0.015*rechit.energy;
									// calculate toward,away and transverse eflow
									if (rechit.sec == leadingsector || rechit.sec == AddSector(leadingsector,1) || rechit.sec == SubtractSector(leadingsector,1))
										eflow_toward += 0.015*rechit.energy;
									if (rechit.sec == AddSector(leadingsector,7) || rechit.sec == AddSector(leadingsector,8) || rechit.sec == AddSector(leadingsector,9))
										eflow_away += 0.015*rechit.energy;
									if (rechit.sec == AddSector(leadingsector,3) || rechit.sec == AddSector(leadingsector,4) || rechit.sec == AddSector(leadingsector,5)
										|| rechit.sec == SubtractSector(leadingsector,3) || rechit.sec == SubtractSector(leadingsector,4) 
										|| rechit.sec == SubtractSector(leadingsector,5)) eflow_transverse += 0.015*rechit.energy;
								}
								if (rechit.cha <= 96) eflow_m6 += 0.015*rechit.energy;
								eflow_m14 += 0.015*rechit.energy;
								usedchannels++;
								h2eflow_grid->Fill(rechit.sec,rechit.mod,0.015*rechit.energy);
							} else { // for MC take fC
								heflow_channel[rechit.cha-1]->Fill(0.015*rechit.fC);
								if (leadingjet) heflow_leadingjet_channel[rechit.cha-1]->Fill(0.015*rechit.fC);
								if (rechit.cha <= 80) {
									eflow += 0.015*rechit.fC;
									// calculate toward,away and transverse eflow
									if (rechit.sec == leadingsector || rechit.sec == AddSector(leadingsector,1) || rechit.sec == SubtractSector(leadingsector,1))
										eflow_toward += 0.015*rechit.fC;
									if (rechit.sec == AddSector(leadingsector,7) || rechit.sec == AddSector(leadingsector,8) || rechit.sec == AddSector(leadingsector,9))
										eflow_away += 0.015*rechit.fC;
									if (rechit.sec == AddSector(leadingsector,3) || rechit.sec == AddSector(leadingsector,4) || rechit.sec == AddSector(leadingsector,5)
										|| rechit.sec == SubtractSector(leadingsector,3) || rechit.sec == SubtractSector(leadingsector,4) 
										|| rechit.sec == SubtractSector(leadingsector,5)) eflow_transverse += 0.015*rechit.fC;
								}
								if (rechit.cha <= 96) eflow_m6 += 0.015*rechit.fC;
								eflow_m14 += 0.015*rechit.fC;
								usedchannels++;
								h2eflow_grid->Fill(rechit.sec,rechit.mod,0.015*rechit.fC);
							}
						}
						if ((rechit.time < 15 || rechit.time > 35) && rechit.cha < 81 && rechit.cha != 5 && rechit.cha != 6) outoftime_eflow += 0.015*rechit.energy;
					}
					
					// fill all minbias eflow histos
					heflow->Fill(eflow);
					heflow_6m->Fill(eflow_m6);
					heflow_14m->Fill(eflow_m14);
					heflow_AllV->Fill(eflow);
					heflow_usedchannels->Fill(usedchannels);
					heflow_outoftime->Fill(outoftime_eflow);
					heflow_pileup[Vertices->size()-1]->Fill(eflow);
					detector_eflow = eflow;
					
					heflow_toward->Fill(eflow_toward);
					heflow_away->Fill(eflow_away);
					heflow_transverse->Fill(eflow_transverse);
					
					// get default eflow per run
					for (unsigned int iRun=0;iRun<Nruns;iRun++) {
						if (evtid->Run == runs[iRun]) heflow_perRun[iRun]->Fill(eflow);
						if (evtid->Run == runs[iRun]) heflow_AllV_perRun[iRun]->Fill(eflow);
					}
					
					// get eflow per lumi bin
					for (int iLumiBin=0;iLumiBin<nLumiBins-1;iLumiBin++) {
						double currentLumiPerBX = evtid->IstLumiPerBX;
						if (currentLumiPerBX >= LumiBins[iLumiBin] && currentLumiPerBX < LumiBins[iLumiBin+1]) heflow_perLumi[iLumiBin]->Fill(eflow);
						if (currentLumiPerBX >= LumiBins2[iLumiBin] && currentLumiPerBX < LumiBins2[iLumiBin+1]) heflow_perLumi2[iLumiBin]->Fill(eflow);
					}
					
					if (leadingjet) {
						heflow_leadingjet->Fill(eflow);
						detector_eflow_leadingjet = eflow;
						heflow_leadingjet_AllV->Fill(eflow);
						heflow_leadingjet_6m->Fill(eflow_m6);
						heflow_leadingjet_14m->Fill(eflow_m14);
						
						heflow_toward_leadingjet->Fill(eflow_toward);
						heflow_away_leadingjet->Fill(eflow_away);
						heflow_transverse_leadingjet->Fill(eflow_transverse);
						
						// get leadingjet eflow per lumi bin
						for (int iLumiBin=0;iLumiBin<nLumiBins-1;iLumiBin++) {
							double currentLumiPerBX = evtid->IstLumiPerBX;
							if (currentLumiPerBX >= LumiBins[iLumiBin] && currentLumiPerBX < LumiBins[iLumiBin+1]) heflow_perLumi_leadingjet[iLumiBin]->Fill(eflow);
							if (currentLumiPerBX >= LumiBins2[iLumiBin] && currentLumiPerBX < LumiBins2[iLumiBin+1]) heflow_perLumi_leadingjet2[iLumiBin]->Fill(eflow);
						}
						
						h2detvshad_ratio->Fill(hadron_eflow/MeanhadronMBflow,detector_eflow/MeandetectorMBflow);
						
					}
					
					if (posLeadingTrackJetresult != -1) {
						for (int ipt=0;ipt<NptBins;ipt++) {
							if ((*trackJets)[posLeadingTrackJetresult].pt_raw > ptbinning[ipt] && (*trackJets)[posLeadingTrackJetresult].pt_raw < ptbinning[ipt+1]) {
								heflow_leadingjetpt[ipt]->Fill(eflow);
								heflow_toward_leadingjetpt[ipt]->Fill(eflow_toward);
								heflow_away_leadingjetpt[ipt]->Fill(eflow_away);
								heflow_transverse_leadingjetpt[ipt]->Fill(eflow_transverse);
								h2detvshad_ratiopt[ipt]->Fill(hadron_eflow/MeanhadronMBflow,detector_eflow/MeandetectorMBflow);
								if (detector_eflow/MeandetectorMBflow < 0.) std::cout << " detector_eflow/MeandetectorMBflow = " << detector_eflow/MeandetectorMBflow << std::endl;
							}
						}
					}
					
					// fill default dijet distributions
					if (dijet->isDiJet) {
						if ((*PFJets)[dijet->posJet1].pt_cal >= ptcut && (*PFJets)[dijet->posJet2].pt_cal >= ptcut) {
							detector_eflow_dijet = eflow;
							heflow_dijet->Fill(eflow);
						}
					}
					
					// pt evolution, do manual dijet selection
					for (int ipt=0;ipt<NptBins;ipt++) {
						//double thiscut = ipt+1;
						if ( isPFDiJet(*PFJets,true,2.5,ptbinning[ipt],ptbinning[ipt+1],true)) {heflow_dijetpt[ipt]->Fill(eflow);}
					}
					
					
					// end of event, print status
					if( ((i+1) % 1000) == 0) std::cout << i+1 <<"events done in file " << it << std::endl;
					totalevents++;
					
				} // end if statement for 1 vertex
				else if (Vertices->size() > 1) {
					
					////////////////////////////////////////////////
					// eflow code for events with more than 1 vertex
					////////////////////////////////////////////////
					
					// fill eflow and leadingjet histograms
					double pileup_eflow = 0;
					for (unsigned int j=0;j<CastorRecHits->size();j++) {
						MyCastorRecHit rechit = (*CastorRecHits)[j];
						if (rechit.cha < 81 && rechit.cha != 5 && rechit.cha != 6) { // for data 15,35,81,5,6
							if (evtid->IsData) { // for data, energy is intercalibrated fC
								pileup_eflow += 0.015*rechit.energy;
							} else { // for MC take fC
								pileup_eflow += 0.015*rechit.fC;
							}
						}
					}
					if ((int)Vertices->size() <= maxVertices) heflow_pileup[Vertices->size()-1]->Fill(pileup_eflow);
					
					// check for leading trackjet
					int posLeadingTrackJetresult = posLeadingTrackJet(*trackJets,2.,1.);
					if (posLeadingTrackJetresult != -1) {
						if ((*trackJets)[posLeadingTrackJetresult].pt_raw > ptcut) {
							heflow_leadingjet_AllV->Fill(pileup_eflow);
						}
					}
					
					heflow_AllV->Fill(pileup_eflow);
					// get PU eflow per run
					for (unsigned int iRun=0;iRun<Nruns;iRun++) {
						if (evtid->Run == runs[iRun]) heflow_AllV_perRun[iRun]->Fill(pileup_eflow);
					}
					
				} // end if statement for more than 1 vertex
				
			} // end if passed detector cuts
			
			// combined hadron and detector level code
			// with 332.5 GeV = detector level MB energy flow at 7 TeV
			// with 555.8 GeV = hadron level MB energy flow at 7 TeV
			
			if (passedHadronCuts || (passedDetectorCuts && Vertices->size() == 1) ) {
				if (hadron_eflow_leadingjet > 0) hRatioDist_hadronlevel->Fill(hadron_eflow_leadingjet/MeanhadronMBflow);
				if (detector_eflow_leadingjet > 0) hRatioDist_detectorlevel->Fill(detector_eflow_leadingjet/MeandetectorMBflow);
			}
			
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
		checkFlow(heflow_channel[icha]);
		checkFlow(heflow_leadingjet_channel[icha]);
	}
	
	// check distribution of each pileup on under or overflow
	for (int icha=0;icha<maxVertices;icha++) {
		checkFlow(heflow_pileup[icha]);
	}
	
	// check per run distributions for under or overflow
	for (unsigned int iRun=0;iRun<Nruns;iRun++) {
		checkFlow(heflow_averagePUperRun[iRun]);
		checkFlow(heflow_perRun[iRun]);
		checkFlow(heflow_AllV_perRun[iRun]);
	}
	
	// check all lumibins for under or overflow
	for ( int iLumiBin=0;iLumiBin<nLumiBins;iLumiBin++) {
		checkFlow(heflow_perLumi[iLumiBin]);
		checkFlow(heflow_perLumi_leadingjet[iLumiBin]);
		checkFlow(heflow_perLumi2[iLumiBin]);
		checkFlow(heflow_perLumi_leadingjet2[iLumiBin]);
	}
	
	// check all dijet pt histos for under or overflow
	for (int ipt=0;ipt<NptBins;ipt++) {
		checkFlow(heflow_dijetpt[ipt]);
		checkFlow(heflow_leadingjetpt[ipt]);
		checkFlow(heflow_toward_leadingjetpt[ipt]);
		checkFlow(heflow_away_leadingjetpt[ipt]);
		checkFlow(heflow_transverse_leadingjetpt[ipt]);
		checkFlow(heflow_dijetpt_hadronlevel[ipt]);
		checkFlow(heflow_leadingjet_chargedgenjets_hadronlevel[ipt]);
	}
	
	// check eflow for under/overflow
	checkFlow(heflow);
	checkFlow(heflow_toward);
	checkFlow(heflow_away);
	checkFlow(heflow_transverse);
	checkFlow(heflow_dijet);
	checkFlow(heflow_leadingjet);
	checkFlow(heflow_toward_leadingjet);
	checkFlow(heflow_away_leadingjet);
	checkFlow(heflow_transverse_leadingjet);
	checkFlow(heflow_6m); 
	checkFlow(heflow_leadingjet_6m);	
	checkFlow(heflow_14m); 
	checkFlow(heflow_leadingjet_14m); 
	checkFlow(heflow_AllV); 
	checkFlow(heflow_leadingjet_AllV);
	
	checkFlow(heflow_hadronlevel);
	checkFlow(heflow_dijet_hadronlevel);
	checkFlow(heflow_leadingjet_hadronlevel);
	
	// get mean and error's from all channels and put it in one histo
	for (int icha=0;icha<80;icha++) {
		heflow_channels->SetBinContent(icha+1,heflow_channel[icha]->GetMean());
		heflow_channels->SetBinError(icha+1,heflow_channel[icha]->GetMeanError());
	}
	
	// get leadingjet ratio per channel 
	TH1D *hRatiosperChannel = new TH1D("hRatiosperChannel","Leadingjet ratio per channel",80,1,81);
	TH1D *hRatiosPull = new TH1D("hRatiosPull","Distribution of leadingjet ratio per channel",22,0,7);
	for (int icha=0;icha<80;icha++) {
		if (heflow_channel[icha]->GetMean() != 0) hRatiosperChannel->SetBinContent(icha+1,heflow_leadingjet_channel[icha]->GetMean()/heflow_channel[icha]->GetMean());
		if (heflow_channel[icha]->GetMean() != 0) hRatiosperChannel->SetBinError(icha+1,getRatioError(heflow_channel[icha],heflow_leadingjet_channel[icha]));
		if (heflow_channel[icha]->GetMean() != 0) hRatiosPull->Fill(heflow_leadingjet_channel[icha]->GetMean()/heflow_channel[icha]->GetMean());
	}
	
	// make average module profile
	for (int i=0;i<5;i++) {
		double average = 0;
		double error = 0;
		for (int j=0;j<16;j++) {
			average += heflow_channel[j+(i*16)]->GetMean();
			error += heflow_channel[j+(i*16)]->GetMeanError()*heflow_channel[j+(i*16)]->GetMeanError();
		}
		if (i==0) average = average/14;
		if (i > 0) average = average/16;
		error = sqrt(error);
		heflow_modules->SetBinContent(i+1,average);
		heflow_modules->SetBinError(i+1,error);
	}
	
	// make average sector profile
	for (int i=0;i<16;i++) {
		double average = 0;
		double error = 0;
		for (int j=0;j<5;j++) {
			average += heflow_channel[i+(j*16)]->GetMean();
			error += heflow_channel[i+(j*16)]->GetMeanError()*heflow_channel[i+(j*16)]->GetMeanError();
		}
		if (i==4 || i==5) { average = 0; error = 0; } // channels 5 and 6 are not used
		error = sqrt(error);
		heflow_sectors->SetBinContent(i+1,average);
		heflow_sectors->SetBinError(i+1,error);
	}
	
	// do eflow ratio stuff
	double dijetratio = heflow_dijet->GetMean()/heflow->GetMean();
	double dijetratio_error = getRatioError(heflow,heflow_dijet);
	heflow_DijetRatio->SetBinContent(1,dijetratio);
	heflow_DijetRatio->SetBinError(1,dijetratio_error);
	
	double leadingjetratio = heflow_leadingjet->GetMean()/heflow->GetMean();
	double leadingjetratio_error = getRatioError(heflow,heflow_leadingjet);
	heflow_LeadingjetRatio->SetBinContent(1,leadingjetratio);
	heflow_LeadingjetRatio->SetBinError(1,leadingjetratio_error);
	
	double leadingjetratio_hadronlevel = heflow_leadingjet_hadronlevel->GetMean()/heflow_hadronlevel->GetMean();
	double leadingjetratio_error_hadronlevel = getRatioError(heflow_hadronlevel,heflow_leadingjet_hadronlevel);
	heflow_LeadingjetRatio_hadronlevel->SetBinContent(1,leadingjetratio_hadronlevel);
	heflow_LeadingjetRatio_hadronlevel->SetBinError(1,leadingjetratio_error_hadronlevel);
	
	double leadingjetratio_toward = heflow_toward_leadingjet->GetMean()/heflow_toward->GetMean();
	double leadingjetratio_toward_error = getRatioError(heflow_toward,heflow_toward_leadingjet);
	
	double leadingjetratio_away = heflow_away_leadingjet->GetMean()/heflow_away->GetMean();
	double leadingjetratio_away_error = getRatioError(heflow_away,heflow_away_leadingjet);
	
	double leadingjetratio_transverse = heflow_transverse_leadingjet->GetMean()/heflow_transverse->GetMean();
	double leadingjetratio_transverse_error = getRatioError(heflow_transverse,heflow_transverse_leadingjet);
	
	double leadingjetratio_6m = heflow_leadingjet_6m->GetMean()/heflow_6m->GetMean();
	double leadingjetratio_error_6m = getRatioError(heflow_6m,heflow_leadingjet_6m);
	heflow_leadingjetRatio_6m->SetBinContent(1,leadingjetratio_6m);
	heflow_leadingjetRatio_6m->SetBinError(1,leadingjetratio_error_6m);
	
	double leadingjetratio_14m = heflow_leadingjet_14m->GetMean()/heflow_14m->GetMean();
	double leadingjetratio_error_14m = getRatioError(heflow_14m,heflow_leadingjet_14m);
	heflow_leadingjetRatio_14m->SetBinContent(1,leadingjetratio_14m);
	heflow_leadingjetRatio_14m->SetBinError(1,leadingjetratio_error_14m);
	
	double leadingjetratio_AllV = heflow_leadingjet_AllV->GetMean()/heflow_AllV->GetMean();
	double leadingjetratio_error_AllV = getRatioError(heflow_AllV,heflow_leadingjet_AllV);
	heflow_leadingjetRatio_AllV->SetBinContent(1,leadingjetratio_AllV);
	heflow_leadingjetRatio_AllV->SetBinError(1,leadingjetratio_error_AllV);
	
	// now print all the leadingjet ratio's and their errors
	std::cout << "Hadron level MinBias energy flow (" << cmenergy << " GeV) = " << heflow_hadronlevel->GetMean() << " and Leadingjet energy flow (" << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << heflow_leadingjet_hadronlevel->GetMean() << std::endl;
	std::cout << "Detector level MinBias energy flow (" << cmenergy << " GeV) = " << heflow->GetMean() << " and Leadingjet energy flow (" << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << heflow_leadingjet->GetMean() << std::endl;
	std::cout << "Detector level MinBias energy flow (" << cmenergy << " GeV) = " << heflow->GetMean() << " and Dijet energy flow (" << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << heflow_dijet->GetMean() << std::endl;
	std::cout << "Detector level MinBias energy flow (all modules) (" << cmenergy << " GeV) = " << heflow_14m->GetMean() << " and leadingjet energy flow (" << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << heflow_leadingjet_14m->GetMean() << std::endl;
	std::cout << "Detector level MinBias energy flow (no # vertices condition) (" << cmenergy << " GeV) = " << heflow_AllV->GetMean() << " and leadingjet energy flow (" << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << heflow_leadingjet_AllV->GetMean() << std::endl;
	
	std::cout << "Hadron level Leadingjet ratio (default at " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << leadingjetratio_hadronlevel << " +- " << leadingjetratio_error_hadronlevel << std::endl;
	std::cout << "Detector level Leadingjet ratio (default at " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << leadingjetratio << " +- " << leadingjetratio_error << std::endl;
	
	std::cout << "Toward region Detector level Leadingjet ratio (default at " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << leadingjetratio_toward << " +- " << leadingjetratio_toward_error << std::endl;
	std::cout << "Away region Detector level Leadingjet ratio (default at " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << leadingjetratio_away << " +- " << leadingjetratio_away_error << std::endl;
	std::cout << "Transverse region Detector level Leadingjet ratio (default at " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << leadingjetratio_transverse << " +- " << leadingjetratio_transverse_error << std::endl;
	
	std::cout << "Detector level Dijet ratio (default at " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << dijetratio << " +- " << dijetratio_error << std::endl;
	
	std::cout << "Detector level leadingjet ratio (6 modules at " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << leadingjetratio_6m << " +- "	<< leadingjetratio_error_6m << std::endl;
	std::cout << "Detector level leadingjet ratio (all modules at " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << leadingjetratio_14m << " +- "	<< leadingjetratio_error_14m << std::endl;
	std::cout << "Detector level leadingjet ratio (no # vertices condition at " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << leadingjetratio_AllV << " +- "	<< leadingjetratio_error_AllV << std::endl;
	
	std::cout << "Detector level shower containment systematic " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << (leadingjetratio_14m - leadingjetratio)/leadingjetratio << std::endl;
	std::cout << "Detector level vertex condition systematic " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << (leadingjetratio_AllV - leadingjetratio)/leadingjetratio << std::endl;
	std::cout << "Detector level mean PU distribution " << cmenergy << " GeV, ptcut = " << ptcut << " GeV) = " << heflow_averagePU->GetMean() << std::endl;
	
	// make a pile up plot
	TH1D *heflow_vs_pileup = new TH1D("heflow_vs_pileup","Mean eflow vs number of vertices",maxVertices,1,maxVertices+1);
	for (int i=0;i<maxVertices;i++) {
		heflow_vs_pileup->SetBinContent(i+1,heflow_pileup[i]->GetMean());
		heflow_vs_pileup->SetBinError(i+1,heflow_pileup[i]->GetMeanError());
	}
	
	std::cout << "Integrated Luminosity = " << IntegratedLumi << std::endl;
	
	/*
	// edit event selection histo
	for (int iBin=0;iBin<hEventSelection->GetNbinsX();iBin++) {
		std::cout << " event selection bin " << iBin+1 << " = " << hEventSelection->GetBinContent(iBin+1) << std::endl;
		if (iBin != 0) hEventSelection->SetBinContent(iBin+1,hEventSelection->GetBinContent(iBin)-hEventSelection->GetBinContent(iBin+1));
	}
	 */
	
	// make histos with per run info
	TH1D *heflow_vs_runs = new TH1D("heflow_vs_runs","MinBias energy flow vs runs",Nruns,1,Nruns);
	TH1D *heflow_vs_runs_AllV = new TH1D("heflow_vs_runs_AllV","MinBias energy flow AllV vs runs",Nruns,1,Nruns);
	TH1D *haveragePU_vs_runs = new TH1D("haveragePU_vs_runs","Average # vertices vs runs",Nruns,1,Nruns);
	TH2D *h2eflow_vs_averagePU = new TH2D("h2eflow_vs_averagePU","MinBias energy flow vs Average # vertices",100,1.0,1.1,100,20000,25000);
	
	for (unsigned int iRun=0;iRun<Nruns;iRun++) {
		heflow_vs_runs->SetBinContent(iRun+1,heflow_perRun[iRun]->GetMean());
		heflow_vs_runs->SetBinError(iRun+1,heflow_perRun[iRun]->GetMeanError());
		heflow_vs_runs_AllV->SetBinContent(iRun+1,heflow_AllV_perRun[iRun]->GetMean());
		heflow_vs_runs_AllV->SetBinError(iRun+1,heflow_AllV_perRun[iRun]->GetMeanError());
		haveragePU_vs_runs->SetBinContent(iRun+1,heflow_averagePUperRun[iRun]->GetMean());
		haveragePU_vs_runs->SetBinError(iRun+1,heflow_averagePUperRun[iRun]->GetMeanError());
		h2eflow_vs_averagePU->Fill(heflow_averagePUperRun[iRun]->GetMean(),heflow_AllV_perRun[iRun]->GetMean());
	}
	
	// make leadingjet ratio vs pt plot
	TH1D *hLeadingjetRatios_vs_pt = new TH1D("hLeadingjetRatios_vs_pt","Leadingjet ratios vs leadingjet ptcut",NptBins,ptbinning);
	TH1D *hLeadingjetRatios_vs_pt_toward = new TH1D("hLeadingjetRatios_vs_pt_toward","Toward region Leadingjet ratios vs leadingjet ptcut",NptBins,ptbinning);
	TH1D *hLeadingjetRatios_vs_pt_away = new TH1D("hLeadingjetRatios_vs_pt_away","away region Leadingjet ratios vs leadingjet ptcut",NptBins,ptbinning);
	TH1D *hLeadingjetRatios_vs_pt_transverse = new TH1D("hLeadingjetRatios_vs_pt_transverse","transverse region Leadingjet ratios vs leadingjet ptcut",NptBins,ptbinning);
	TH1D *hDijetRatios_vs_pt = new TH1D("hDijetRatios_vs_pt","Dijet ratios vs dijet ptcut",NptBins,ptbinning);
	
	for (int ipt=0;ipt<NptBins;ipt++) {
		hLeadingjetRatios_vs_pt->SetBinContent(ipt+1,heflow_leadingjetpt[ipt]->GetMean()/heflow->GetMean());
		hLeadingjetRatios_vs_pt->SetBinError(ipt+1,getRatioError(heflow,heflow_leadingjetpt[ipt]));
		
		hLeadingjetRatios_vs_pt_toward->SetBinContent(ipt+1,heflow_toward_leadingjetpt[ipt]->GetMean()/heflow_toward->GetMean());
		hLeadingjetRatios_vs_pt_toward->SetBinError(ipt+1,getRatioError(heflow_toward,heflow_toward_leadingjetpt[ipt]));
		
		hLeadingjetRatios_vs_pt_away->SetBinContent(ipt+1,heflow_away_leadingjetpt[ipt]->GetMean()/heflow_away->GetMean());
		hLeadingjetRatios_vs_pt_away->SetBinError(ipt+1,getRatioError(heflow_away,heflow_away_leadingjetpt[ipt]));
		
		hLeadingjetRatios_vs_pt_transverse->SetBinContent(ipt+1,heflow_transverse_leadingjetpt[ipt]->GetMean()/heflow_transverse->GetMean());
		hLeadingjetRatios_vs_pt_transverse->SetBinError(ipt+1,getRatioError(heflow_transverse,heflow_transverse_leadingjetpt[ipt]));
		
		hDijetRatios_vs_pt->SetBinContent(ipt+1,heflow_dijetpt[ipt]->GetMean()/heflow->GetMean());
		hDijetRatios_vs_pt->SetBinError(ipt+1,getRatioError(heflow,heflow_dijetpt[ipt]));
	}
	
	// do lumi correction
	TH1D *heflow_vs_Lumi = new TH1D("heflow_vs_Lumi","MB energy flow in CASTOR vs Inst. Lumi per BX",nLumiBins-1,LumiBins[0],LumiBins[nLumiBins-1]);
	TH1D *heflow_vs_Lumi2 = new TH1D("heflow_vs_Lumi2","MB energy flow in CASTOR vs Inst. Lumi per BX",nLumiBins-1,LumiBins2[0],LumiBins2[nLumiBins-1]);
	TH1D *heflow_vs_Lumi_leadingjet = new TH1D("heflow_vs_Lumi_leadingjet","leadingjet energy flow in CASTOR vs Inst. Lumi per BX",nLumiBins-1,LumiBins[0],LumiBins[nLumiBins-1]);
	TH1D *heflow_vs_Lumi_leadingjet2 = new TH1D("heflow_vs_Lumi_leadingjet2","leadingjet energy flow in CASTOR vs Inst. Lumi per BX",nLumiBins-1,LumiBins2[0],LumiBins2[nLumiBins-1]);
	for ( int iLumiBin=0;iLumiBin<nLumiBins;iLumiBin++) {
		heflow_vs_Lumi->SetBinContent(iLumiBin+1,heflow_perLumi[iLumiBin]->GetMean());
		heflow_vs_Lumi->SetBinError(iLumiBin+1,heflow_perLumi[iLumiBin]->GetMeanError());
		
		heflow_vs_Lumi_leadingjet->SetBinContent(iLumiBin+1,heflow_perLumi_leadingjet[iLumiBin]->GetMean());
		heflow_vs_Lumi_leadingjet->SetBinError(iLumiBin+1,heflow_perLumi_leadingjet[iLumiBin]->GetMeanError());
		
		heflow_vs_Lumi2->SetBinContent(iLumiBin+1,heflow_perLumi2[iLumiBin]->GetMean());
		heflow_vs_Lumi2->SetBinError(iLumiBin+1,heflow_perLumi2[iLumiBin]->GetMeanError());
		
		heflow_vs_Lumi_leadingjet2->SetBinContent(iLumiBin+1,heflow_perLumi_leadingjet2[iLumiBin]->GetMean());
		heflow_vs_Lumi_leadingjet2->SetBinError(iLumiBin+1,heflow_perLumi_leadingjet2[iLumiBin]->GetMeanError());
	}
	
	
	// divide by number of entries for HF eflow plots
	for (int ibin=0;ibin<5;ibin++) {
		hHFPluseflow->SetBinContent(ibin+1,hHFPluseflow->GetBinContent(ibin+1)/totalevents);
		hHFPluseflow->SetBinError(ibin+1,hHFPluseflow->GetBinError(ibin+1)/totalevents);
		hHFMinuseflow->SetBinContent(ibin+1,hHFMinuseflow->GetBinContent(ibin+1)/totalevents);
		hHFMinuseflow->SetBinError(ibin+1,hHFMinuseflow->GetBinError(ibin+1)/totalevents);
	}
	
	// make leadingjet ratio vs pt plot on hadron level
	TH1D *hDijetRatios_vs_pt_hadronlevel = new TH1D("hDijetRatios_vs_pt_hadronlevel","Hadron level Dijet ratios vs dijet ptcut",NptBins,ptbinning);
	TH1D *hLeadingJetRatios_vs_pt_chargedgenjets_hadronlevel = new TH1D("hLeadingJetRatios_vs_pt_chargedgenjets_hadronlevel","Hadron level LeadingJet ratios vs leadingjet ptcut - charged genjets",NptBins,ptbinning);
	for (int ipt=0;ipt<NptBins;ipt++) {
		hDijetRatios_vs_pt_hadronlevel->SetBinContent(ipt+1,heflow_dijetpt_hadronlevel[ipt]->GetMean()/heflow_hadronlevel->GetMean());
		hDijetRatios_vs_pt_hadronlevel->SetBinError(ipt+1,getRatioError(heflow_hadronlevel,heflow_dijetpt_hadronlevel[ipt]));
		
		hLeadingJetRatios_vs_pt_chargedgenjets_hadronlevel->SetBinContent(ipt+1,heflow_leadingjet_chargedgenjets_hadronlevel[ipt]->GetMean()/heflow_hadronlevel->GetMean());
		hLeadingJetRatios_vs_pt_chargedgenjets_hadronlevel->SetBinError(ipt+1,getRatioError(heflow_hadronlevel,heflow_leadingjet_chargedgenjets_hadronlevel[ipt]));
	}
	
	
	// xi histograms
	TH1D *hxi_cumulative = new TH1D("hxi_cumulative","Cumulative log10(Xi) distribution off all the events",55,-10,1);
	TH1D *hxix_cumulative = new TH1D("hxix_cumulative","Cumulative log10(Xix) distribution off all the events",55,-10,1);
	TH1D *hxiy_cumulative = new TH1D("hxiy_cumulative","Cumulative log10(Xiy) distribution off all the events",55,-10,1);
	TH1D *hxidd_cumulative = new TH1D("hxidd_cumulative","Cumulative log10(Xidd) distribution off all the events",125,-20,5);
	TH1D *hxi_ratio = new TH1D("hxi_ratio","log10(Xi) selected events/log10(Xi) all events",55,-10,1);
	TH1D *hxidd_ratio = new TH1D("hxidd_ratio","log10(Xidd) selected events/log10(Xidd) all events",125,-20,5);
	TH2D *h2xixxiy_ratio = new TH2D("h2xixxiy_ratio","log10(Xi) selected events/log10(Xi) all events",55,-10,1,55,-10,1);
	for (int ibin=0;ibin<hxi->GetNbinsX();ibin++) {
		hxi_cumulative->SetBinContent(ibin+1,hxi->Integral(ibin+1,hxi->GetNbinsX()));
		hxix_cumulative->SetBinContent(ibin+1,hxix->Integral(ibin+1,hxix->GetNbinsX()));
		hxiy_cumulative->SetBinContent(ibin+1,hxiy->Integral(ibin+1,hxiy->GetNbinsX()));
		if (hxi->GetBinContent(ibin+1) != 0) hxi_ratio->SetBinContent(ibin+1,hxi_withDetectorCuts->GetBinContent(ibin+1)/hxi->GetBinContent(ibin+1));
		for (int jbin=0;jbin<h2xixxiy->GetNbinsY();jbin++) {
			if (h2xixxiy->GetBinContent(ibin+1,jbin+1) != 0) h2xixxiy_ratio->SetBinContent(ibin+1,jbin+1,h2xixxiy_withDetectorCuts->GetBinContent(ibin+1,jbin+1)/h2xixxiy->GetBinContent(ibin+1,jbin+1));
		}
	}
	
	for (int ibin=0;ibin<hxidd->GetNbinsX();ibin++) {
		hxidd_cumulative->SetBinContent(ibin+1,hxidd->Integral(ibin+1,hxidd->GetNbinsX()));
		if (hxidd->GetBinContent(ibin+1) != 0) hxidd_ratio->SetBinContent(ibin+1,hxidd_withDetectorCuts->GetBinContent(ibin+1)/hxidd->GetBinContent(ibin+1));
	}
	
	
	// correction factors
	double correctionfactor = 0;
	if (leadingjetratio != 0) correctionfactor = leadingjetratio_hadronlevel/leadingjetratio;
	std::cout << " CASTOR Correlation factor = " << h2detvshad_ratio->GetCorrelationFactor() << std::endl;
	std::cout << " CASTOR Hadron level mean = " << h2detvshad_ratio->GetMean(1) << " detector level mean = " << h2detvshad_ratio->GetMean(2) << std::endl;
	std::cout << " Final Hadron level correction factor for default leadingjet ratio = " << correctionfactor << std::endl;
	
	TH1D *hCorrectionFactors_vs_pt = new TH1D("hCorrectionFactors_vs_pt","Hadron level correction factor vs pt",NptBins,ptbinning);
	TH1D *hCASTORCorrectionFactors_vs_pt = new TH1D("hCASTORCorrectionFactors_vs_pt","CASTOR Hadron level correction factor vs pt",NptBins,ptbinning);
	for (int ipt=0;ipt<NptBins;ipt++) {
		// final correction factors
		if (hLeadingjetRatios_vs_pt->GetBinContent(ipt+1) != 0) hCorrectionFactors_vs_pt->SetBinContent(ipt+1,
												hLeadingJetRatios_vs_pt_chargedgenjets_hadronlevel->GetBinContent(ipt+1)/hLeadingjetRatios_vs_pt->GetBinContent(ipt+1));
		// CASTOR correction factors
		if (h2detvshad_ratiopt[ipt]->GetMean(2) != 0) hCASTORCorrectionFactors_vs_pt->SetBinContent(ipt+1,
																					h2detvshad_ratiopt[ipt]->GetMean(1)/h2detvshad_ratiopt[ipt]->GetMean(2));
	}
	
	// correct detector level ratio with CASTOR factors to then get the remaining correction factors
	TH1D *hOtherCorrectionFactors_vs_pt = new TH1D("hOtherCorrectionFactors_vs_pt","Pt migration Hadron level correction factor vs pt",NptBins,ptbinning);
	for (int ipt=0;ipt<NptBins;ipt++) {
		if (hLeadingjetRatios_vs_pt->GetBinContent(ipt+1) != 0 && hCASTORCorrectionFactors_vs_pt->GetBinContent(ipt+1) != 0) 
			hOtherCorrectionFactors_vs_pt->SetBinContent(ipt+1,hLeadingJetRatios_vs_pt_chargedgenjets_hadronlevel->GetBinContent(ipt+1)/
														 (hLeadingjetRatios_vs_pt->GetBinContent(ipt+1)*hCASTORCorrectionFactors_vs_pt->GetBinContent(ipt+1)));
	}
	
	// recalculation of the final correction factors using CASTOR and Other factors
	TH1D *hCorrectionFactors_vs_pt2 = new TH1D("hCorrectionFactors_vs_pt2","Hadron level correction factor vs pt - recalculated",NptBins,ptbinning);
	for (int ipt=0;ipt<NptBins;ipt++) {
		hCorrectionFactors_vs_pt2->SetBinContent(ipt+1,hCASTORCorrectionFactors_vs_pt->GetBinContent(ipt+1)*hOtherCorrectionFactors_vs_pt->GetBinContent(ipt+1));
	}
	
	
	
	//////////////////////////////////////////////////
	
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
	
	// eflow histos
	heflow->Write();
	heflow_toward->Write();
	heflow_away->Write();
	heflow_transverse->Write();
	heflow_dijet->Write();
	heflow_DijetRatio->Write();
	heflow_leadingjet->Write();
	heflow_toward_leadingjet->Write();
	heflow_away_leadingjet->Write();
	heflow_transverse_leadingjet->Write();
	heflow_LeadingjetRatio->Write();
	
	for (int ipt=0;ipt<NptBins;ipt++) {
		heflow_leadingjetpt[ipt]->Write();
		heflow_toward_leadingjetpt[ipt]->Write();
		heflow_away_leadingjetpt[ipt]->Write();
		heflow_transverse_leadingjetpt[ipt]->Write();
		heflow_dijetpt[ipt]->Write();
	}
	
	heflow_6m->Write();
	heflow_leadingjet_6m->Write();
	heflow_leadingjetRatio_6m->Write();
	
	heflow_14m->Write();
	heflow_leadingjet_14m->Write();
	heflow_leadingjetRatio_14m->Write();
	
	heflow_AllV->Write();
	heflow_leadingjet_AllV->Write();
	heflow_leadingjetRatio_AllV->Write();	
	
	h2eflow_grid->Write();
	h2eflow_map->Write();
	heflow_usedchannels->Write();
	heflow_sectors->Write();
	heflow_sectors_leadingjet->Write();
	heflow_modules->Write();
	for (int icha=0;icha<224;icha++) {
		heflow_channel[icha]->Write();
		heflow_leadingjet_channel[icha]->Write();
	}
	hRatiosperChannel->Write();
	hRatiosPull->Write();
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
	
	//h2L1Prescales->Write();
	heflow_vs_runs->Write();
	heflow_vs_runs_AllV->Write();
	haveragePU_vs_runs->Write();
	h2eflow_vs_averagePU->Write();
	
	hLeadingjetRatios_vs_pt->Write();
	hLeadingjetRatios_vs_pt_toward->Write();
	hLeadingjetRatios_vs_pt_away->Write();
	hLeadingjetRatios_vs_pt_transverse->Write();
	hDijetRatios_vs_pt->Write();
	
	heflow_InstLumi->Write();
	heflow_InstLumiPerBX->Write();
	heflow_InstLumiPerBX2->Write();
	heflow_InstLumi_AllV->Write();
	heflow_InstLumiPerBX_AllV->Write();
	
	for (int iLumiBin=0; iLumiBin<nLumiBins;iLumiBin++) {
		heflow_perLumi[iLumiBin]->Write();
		heflow_perLumi2[iLumiBin]->Write();
		heflow_perLumi_leadingjet[iLumiBin]->Write();
		heflow_perLumi_leadingjet2[iLumiBin]->Write();
	}
	heflow_vs_Lumi->Write();
	heflow_vs_Lumi2->Write();
	heflow_vs_Lumi_leadingjet->Write();
	heflow_vs_Lumi_leadingjet2->Write();
	
	hBeamSpot_x->Write();
	hBeamSpot_y->Write();
	hBeamSpot_z->Write();
	hBeamSpot_dxdz->Write();
	hBeamSpot_dydz->Write();
	hBeamSpot_sigmaZ->Write();
	
	// hadron level
	heflow_hadronlevel->Write();
	heflow_dijet_hadronlevel->Write();
	heflow_leadingjet_hadronlevel->Write();
	heflow_LeadingjetRatio_hadronlevel->Write();
	hhadron_eta->Write();
	hhadron_phi->Write();
	hhadron_energy->Write();
	
	hxi->Write();
	hxix->Write();
	hxiy->Write();
	hxidd->Write();
	hxiddln->Write();
	hxiddlninverse->Write();
	hetamax->Write();
	hxi_withDetectorCuts->Write();
	hxix_withDetectorCuts->Write();
	hxiy_withDetectorCuts->Write();
	hxidd_withDetectorCuts->Write();
	hetamax_withDetectorCuts->Write();
	h2xixxiy->Write();
	h2xixxiy_withDetectorCuts->Write();
	hxi_cumulative->Write();
	hxix_cumulative->Write();
	hxiy_cumulative->Write();
	hxidd_cumulative->Write();
	hxi_ratio->Write();
	hxidd_ratio->Write();
	h2xixxiy_ratio->Write();
	h2xixxiy_withXiddCut->Write();
		
	hRatioDist_hadronlevel->Write();
	hRatioDist_detectorlevel->Write();
	h2detvshad_ratio->Write();
		
	for (int ipt=0;ipt<NptBins;ipt++) {
		heflow_dijetpt_hadronlevel[ipt]->Write();
		heflow_leadingjet_chargedgenjets_hadronlevel[ipt]->Write();
		h2detvshad_ratiopt[ipt]->Write();
	}
	hDijetRatios_vs_pt_hadronlevel->Write();
	hLeadingJetRatios_vs_pt_chargedgenjets_hadronlevel->Write();
	
	// calotowers
	hCaloTower_energy->Write();
	hCaloTower_eta->Write();
	hCaloTower_phi->Write();
	hCaloTower_zside->Write();
	hHFPluseflow->Write();
	hHFMinuseflow->Write();
	
	hCorrectionFactors_vs_pt->Write();
	hCASTORCorrectionFactors_vs_pt->Write();
	hOtherCorrectionFactors_vs_pt->Write();
	hCorrectionFactors_vs_pt2->Write();
	
	output->Close();
	std::cout << "file " << filename << " created." << std::endl;
	
}

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

bool TreeAnalyzer::isPFDiJet(std::vector<MyJet> JetVector, bool backtoback, double usedetacut, double lowptcut, double highptcut, bool mean) {
	
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
		
		if (!mean) {
			//-- jet 1 selection
			if(jet1.pt_cal > lowptcut && jet1.pt_cal < highptcut && fabs(jet1.eta_cal) < usedetacut && jet1.TightPFJetId == true) accept_jet1 = true;
			
			//-- jet 2 selection
			if(jet2.pt_cal > lowptcut && jet2.pt_cal < highptcut && fabs(jet2.eta_cal) < usedetacut && jet2.TightPFJetId == true) accept_jet2 = true;
			
			//-- final selection (back-to-back)
			
			if(accept_jet1 == true && accept_jet2 == true) {
				if (backtoback) {
					double deltaPhi = fabs(deltaPhi2(jet1.phi_cal, jet2.phi_cal));
					if (fabs(deltaPhi - M_PI) < 1.0) accept = true;
				} else {
					accept = true;
				}
				
			}
		} else {
			// using mean dijet system pt
			//-- jet 1 selection
			if(fabs(jet1.eta_cal) < usedetacut && jet1.TightPFJetId == true) accept_jet1 = true;
			
			//-- jet 2 selection
			if(fabs(jet2.eta_cal) < usedetacut && jet2.TightPFJetId == true) accept_jet2 = true;
			
			//-- final selection (back-to-back)
			
			if(accept_jet1 == true && accept_jet2 == true) {
				double meanpt = (jet1.pt_cal + jet2.pt_cal)/2;
				bool meanOK = false;
				if (meanpt > lowptcut && meanpt < highptcut) meanOK = true;
				if (backtoback && meanOK) {
					double deltaPhi = fabs(deltaPhi2(jet1.phi_cal, jet2.phi_cal));
					if (fabs(deltaPhi - M_PI) < 1.0) accept = true;
				} else if (meanOK) {
					accept = true;
				}
				
			}
		}
		
	} //-- posJet1 >= 0 && posJet2 >= 0
	return accept;
}


bool TreeAnalyzer::isGenDiJet(std::vector<MyGenJet> JetVector, bool backtoback, double usedetacut, double usedptcut) {
	
	using namespace std;
	
	//-- central jet selection
	
	bool accept = false;
	
	short int posJet1 = -1;
	short int posJet2 = -1;
	
	double refPt1 = 0;
	double refPt2 = 0;
	
	//-- find the two highest pt jets (corrected pt)
	
	for(vector<MyGenJet>::const_iterator jet = JetVector.begin(); jet < JetVector.end(); ++jet) {
		
		Double_t pt = jet->Pt();
		
		if(pt > refPt1) {
			refPt2 = refPt1;
			posJet2 = posJet1;      
			refPt1 = pt;
			posJet1 = jet - JetVector.begin();
		}
		
		else if(pt > refPt2) {
			refPt2 = pt;
			posJet2 = jet - JetVector.begin();
		}
		
	} 
	
	//-- apply the tight selection to them
	
	if(posJet1 >= 0 && posJet2 >= 0) {
		
		bool accept_jet1 = false;
		bool accept_jet2 = false;
		
		MyGenJet jet1 = JetVector.at(posJet1);
		MyGenJet jet2 = JetVector.at(posJet2);
		
		//-- jet 1 selection
		if(jet1.Pt() > usedptcut && fabs(jet1.Eta()) < usedetacut) accept_jet1 = true;
		
		//-- jet 2 selection
		if(jet2.Pt() > usedptcut && fabs(jet2.Eta()) < usedetacut) accept_jet2 = true;
		
		//-- final selection (back-to-back)
		
		if(accept_jet1 == true && accept_jet2 == true) {
			if (backtoback) {
				double deltaPhi = fabs(deltaPhi2(jet1.Phi(), jet2.Phi()));
				if (fabs(deltaPhi - M_PI) < 1.0) accept = true;
			} else {
				accept = true;
			}
			
		}
		
	} //-- posJet1 >= 0 && posJet2 >= 0
	return accept;
}

bool TreeAnalyzer::isGenDiJet(std::vector<MyGenJet> JetVector, bool backtoback, double usedetacut, double lowptcut, double highptcut, bool mean) {
	
	using namespace std;
	
	//-- central jet selection
	
	bool accept = false;
	
	short int posJet1 = -1;
	short int posJet2 = -1;
	
	double refPt1 = 0;
	double refPt2 = 0;
	
	//-- find the two highest pt jets (corrected pt)
	
	for(vector<MyGenJet>::const_iterator jet = JetVector.begin(); jet < JetVector.end(); ++jet) {
		
		Double_t pt = jet->Pt();
		
		if(pt > refPt1) {
			refPt2 = refPt1;
			posJet2 = posJet1;      
			refPt1 = pt;
			posJet1 = jet - JetVector.begin();
		}
		
		else if(pt > refPt2) {
			refPt2 = pt;
			posJet2 = jet - JetVector.begin();
		}
		
	} 
	
	//-- apply the tight selection to them
	
	if(posJet1 >= 0 && posJet2 >= 0) {
		
		bool accept_jet1 = false;
		bool accept_jet2 = false;
		
		MyGenJet jet1 = JetVector.at(posJet1);
		MyGenJet jet2 = JetVector.at(posJet2);
		
		if (!mean) {
			//-- jet 1 selection
			if(jet1.Pt() > lowptcut && jet1.Pt() < highptcut && fabs(jet1.Eta()) < usedetacut) accept_jet1 = true;
			
			//-- jet 2 selection
			if(jet2.Pt() > lowptcut && jet2.Pt() < highptcut && fabs(jet2.Eta()) < usedetacut) accept_jet2 = true;
			
			//-- final selection (back-to-back)
			
			if(accept_jet1 == true && accept_jet2 == true) {
				if (backtoback) {
					double deltaPhi = fabs(deltaPhi2(jet1.Phi(), jet2.Phi()));
					if (fabs(deltaPhi - M_PI) < 1.0) accept = true;
				} else {
					accept = true;
				}
				
			}
		} else {
			// using mean dijet system pt
			//-- jet 1 selection
			if(fabs(jet1.Eta()) < usedetacut) accept_jet1 = true;
			
			//-- jet 2 selection
			if(fabs(jet2.Eta()) < usedetacut) accept_jet2 = true;
			
			//-- final selection (back-to-back)
			
			if(accept_jet1 == true && accept_jet2 == true) {
				double meanpt = (jet1.Pt() + jet2.Pt())/2;
				bool meanOK = false;
				if (meanpt > lowptcut && meanpt < highptcut) meanOK = true;
				if (backtoback && meanOK) {
					double deltaPhi = fabs(deltaPhi2(jet1.Phi(), jet2.Phi()));
					if (fabs(deltaPhi - M_PI) < 1.0) accept = true;
				} else if (meanOK) {
					accept = true;
				}
				
			}
		}
		
	} //-- posJet1 >= 0 && posJet2 >= 0
	return accept;
}

bool TreeAnalyzer::isTrackDiJet(std::vector<MyTrackJet> JetVector, bool backtoback, double usedetacut, double lowptcut, double highptcut, bool mean) {
	
	using namespace std;
	
	//-- central jet selection
	
	bool accept = false;
	
	short int posJet1 = -1;
	short int posJet2 = -1;
	
	double refPt1 = 0;
	double refPt2 = 0;
	
	//-- find the two highest pt jets (corrected pt)
	
	for(vector<MyTrackJet>::const_iterator jet = JetVector.begin(); jet < JetVector.end(); ++jet) {
		
		Double_t pt = jet->pt_cal;
		
		if(pt > refPt1) {
			refPt2 = refPt1;
			posJet2 = posJet1;      
			refPt1 = pt;
			posJet1 = jet - JetVector.begin();
		}
		
		else if(pt > refPt2) {
			refPt2 = pt;
			posJet2 = jet - JetVector.begin();
		}
		
	} 
	
	//-- apply the tight selection to them
	
	if(posJet1 >= 0 && posJet2 >= 0) {
		
		bool accept_jet1 = false;
		bool accept_jet2 = false;
		
		MyTrackJet jet1 = JetVector.at(posJet1);
		MyTrackJet jet2 = JetVector.at(posJet2);
		
		if (!mean) {
			//-- jet 1 selection
			if(jet1.pt_cal > lowptcut && jet1.pt_cal < highptcut && fabs(jet1.eta_cal) < usedetacut && jet1.pv) accept_jet1 = true;
			
			//-- jet 2 selection
			if(jet2.pt_cal > lowptcut && jet2.pt_cal < highptcut && fabs(jet2.eta_cal) < usedetacut && jet2.pv) accept_jet2 = true;
			
			//-- final selection (back-to-back)
			
			if(accept_jet1 == true && accept_jet2 == true) {
				if (backtoback) {
					double deltaPhi = fabs(deltaPhi2(jet1.phi_cal, jet2.phi_cal));
					if (fabs(deltaPhi - M_PI) < 1.0) accept = true;
				} else {
					accept = true;
				}
				
			}
		} else {
			// using mean dijet system pt
			//-- jet 1 selection
			if(fabs(jet1.eta_cal) < usedetacut && jet1.pv) accept_jet1 = true;
			
			//-- jet 2 selection
			if(fabs(jet2.eta_cal) < usedetacut && jet2.pv) accept_jet2 = true;
			
			//-- final selection (back-to-back)
			
			if(accept_jet1 == true && accept_jet2 == true) {
				double meanpt = (jet1.pt_cal + jet2.pt_cal)/2;
				bool meanOK = false;
				if (meanpt > lowptcut && meanpt < highptcut) meanOK = true;
				if (backtoback && meanOK) {
					double deltaPhi = fabs(deltaPhi2(jet1.phi_cal, jet2.phi_cal));
					if (fabs(deltaPhi - M_PI) < 1.0) accept = true;
				} else if (meanOK) {
					accept = true;
				}
				
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

void TreeAnalyzer::checkFlow(TH1D *histo) {
	if (histo->GetBinContent(histo->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! histogram " << histo->GetName() << " has overflow" << std::endl;
	if (histo->GetBinContent(0) !=0) std::cout << "!!WARNING!! histogram " << histo->GetName() << " has underflow" << std::endl;
}


int TreeAnalyzer::posLeadingGenJet(std::vector<MyGenJet> JetVector,double etacut,double minptcut) {
	
	// search for leading jets
	int posLeadingChargedGenJet = -1;

	double tempptchargedgenjet = 0;
	for (unsigned int ijet=0;ijet<JetVector.size();ijet++) {
		if (JetVector[ijet].Pt() > minptcut && fabs(JetVector[ijet].Eta()) < etacut) {
			if (JetVector[ijet].Pt() > tempptchargedgenjet) {
				tempptchargedgenjet = JetVector[ijet].Pt();
				posLeadingChargedGenJet = ijet;
			}
		}
	}
	
	return posLeadingChargedGenJet;
}

int TreeAnalyzer::posLeadingTrackJet(std::vector<MyTrackJet> JetVector,double etacut,double minptcut) {
	
	// search for leading jets
	int posLeadingTrackJetresult = -1;
	double temppttrack = 0;
	for (unsigned int ijet=0;ijet<JetVector.size();ijet++) {
		if (JetVector[ijet].pt_raw > minptcut && fabs(JetVector[ijet].eta_raw) < etacut && JetVector[ijet].pv) {
			if (JetVector[ijet].pt_raw > temppttrack) {
				temppttrack = JetVector[ijet].pt_raw;
				posLeadingTrackJetresult = ijet;
			}
		}
	}
	
	return posLeadingTrackJetresult;
}

int TreeAnalyzer::rad2Sector(double radians) {
	// convert radian angle to CASTOR sector number
	int result = -1;
	double sectorwidthinrad = M_PI/8;
	if (radians > 0.) {
		for (int i=0;i<8;i++) {
			if (radians > i*sectorwidthinrad && radians < (i+1)*sectorwidthinrad) result = i+1;
		}
	} else {
		for (int i=8;i<16;i++) {
			if (radians > -1*(16-i)*sectorwidthinrad && radians < -1*(16-i-1)*sectorwidthinrad) result = i+1;
		}
	}
	return result;
	
} 

int TreeAnalyzer::AddSector(int sector,int add) {
	// return the next sector: sector+1
	if (sector+add < 17) {
		return sector+add;
	} else {
		return sector+add-16;
	}
}

int TreeAnalyzer::SubtractSector(int sector,int sub) {
	// return the next sector: sector+1
	if (sector-sub > 0) {
		return sector-sub;
	} else {
		return sector-sub+16;
	}
}

