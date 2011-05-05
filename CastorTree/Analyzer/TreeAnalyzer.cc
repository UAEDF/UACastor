
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

// own classes includes
#include "../src/MyCastorRecHit.h"
#include "../src/MyCastorDigi.h"
#include "../src/MyCastorTower.h"
#include "../src/MyCastorJet.h"
#include "../src/MyEvtId.h"
#include "../src/MyDiJet.h"
#include "../src/MyVertex.h"

TreeAnalyzer::TreeAnalyzer() { }

TreeAnalyzer::~TreeAnalyzer() { }

void TreeAnalyzer::Loop(TString inputdir, TObjArray* filelist) {

	using namespace std;
	int it = 0;
	int totalevents = 0;
	
	/////////////////////////////////////
	// Define all histograms
	/////////////////////////////////////
	
	// castor digi histos
	TH1F *hDigi_TS = new TH1F("hDigi_TS","fC vs TS",10,1,11);
	TH1F *hDigi_fC = new TH1F("hDigi_fC","fC distribution",100,-500,80000);
	TH1F *hDigi_totalfC = new TH1F("hDigi_totalfC","total fC distribution",100,-5000,1200000);
	TH1F *hDigi_module = new TH1F("hDigi_module","energy weighted modules",14,1,15);
	TH1F *hDigi_sector = new TH1F("hDigi_sector","energy weighted sectors",16,1,17);
	TH1F *hNDigis = new TH1F("hNDigis","Number of digis/event",225,0,225);
	
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
		
	// castor tower histos
	TH1F *hTower_energy = new TH1F("hTower_energy","Tower energy",100,0,3500);
	TH1F *hTower_pt = new TH1F("hTower_pt","Tower pt",100,0,25);
	TH1F *hTower_eta = new TH1F("hTower_eta","Tower eta",14,-6.6,-5.2);
	TH1F *hTower_phi = new TH1F("hTower_phi","Tower phi",100,-1*TMath::Pi(),TMath::Pi());
	TH1F *hTower_fem = new TH1F("hTower_fem","Tower fem",100,-1,2.5);
	TH1F *hTower_depth = new TH1F("hTower_depth","Tower depth",100,-17000,-13000);
	TH1F *hTower_fhot = new TH1F("hTower_fhot","Tower fhot",100,0,2.5);
	TH1F *hTower_ncell = new TH1F("hTower_ncell","Tower ncell",15,0,15);
	TH1F *hNTowers = new TH1F("hNTowers","number of towers/event",17,0,17);
		
	// castor jet histos
	TH1F *hJet_energy = new TH1F("hJet_energy","Jet energy",100,0,7000);
	TH1F *hJet_pt = new TH1F("hJet_pt","Jet pt",100,0,40);
	TH1F *hJet_eta = new TH1F("hJet_eta","Jet eta",14,-6.6,-5.2);
	TH1F *hJet_phi = new TH1F("hJet_phi","Jet phi",100,-1*TMath::Pi(),TMath::Pi());
	TH1F *hJet_fem = new TH1F("hJet_fem","Jet fem",100,-1,2.5);
	TH1F *hJet_depth = new TH1F("hJet_depth","Jet depth",100,-17000,-13000);
	TH1F *hJet_fhot = new TH1F("hJet_fhot","Jet fhot",100,0,2.5);
	TH1F *hJet_ntower = new TH1F("hJet_ntower","Jet ntower",15,0,15);
	TH1F *hNJets = new TH1F("hNJets","number of jets/event",17,0,17);
	TH1F *hJet_width = new TH1F("hJet_width","Jet width",100,0,1);
	TH1F *hJet_sigmaz = new TH1F("hJet_sigmaz","Jet sigmaz",100,0,700);
	
	// eflow histograms
	double min = -2000; // -2000 for data and MC
	double max = 60000; // 60000 for data and MC
	double channelmin = -200; // -200 for data and MC
	double channelmax = 30000; // 30000 for data and MC
	
	TH1F *heflow_DijetRatio = new TH1F("heflow_DijetRatio","Dijet Ratio",1,0,1);
	TH1F *heflow = new TH1F("heflow","total rechit GeV distribution",100,min,max); // for data -2000,60000
	TH1F *heflow_dijet = new TH1F("heflow_dijet","total rechit GeV distribution for dijet events",100,min,max); // for mc -40,600
	TH2F *h2eflow_grid = new TH2F("h2eflow_grid","energy weighted module vs sector distribution",16,1,17,14,1,15);
	TH2F *h2eflow_map = new TH2F("h2eflow_map","used channels map",16,1,17,14,1,15);
	TH1F *heflow_modules = new TH1F("heflow_modules","average energy in used modules",14,1,15);
	TH1F *heflow_sectors = new TH1F("heflow_sectors","average energy in used sectors",16,1,17);
	TH1F *heflow_usedchannels = new TH1F("heflow_usedchannels","number of used channels to compute eflow",224,1,225);
	TH1F *heflow_channels = new TH1F("heflow_channels","average energy in used channels",80,1,81);
	TH1F *heflow_outoftime = new TH1F("heflow_outoftime","total rechit distribution for out of time rechits",100,min,max);
	
	TH1F *heflow_channel[80];
	char name [50];
	char title [50];
	for (int i=0;i<80;i++) {
		sprintf(name,"heflow_channel_%d",i+1);
		sprintf(title,"Energy distribution for channel %d",i+1);
		heflow_channel[i] = new TH1F(name,title,100,channelmin,channelmax); // for data -200,30000, for mc -4,400
		heflow_channel[i]->Sumw2();
	}
	
	int maxVertices = 5;
	TH1F *heflow_pileup[maxVertices];
	for (int i=0;i<maxVertices;i++) {
		sprintf(name,"heflow_pileup_%d",i+1);
		sprintf(title,"Energy flow distribution for %d vertex events",i+1);
		heflow_pileup[i] = new TH1F(name,title,100,min,max); // for data -2000,60000, for mc -4,400
		heflow_pileup[i]->Sumw2();
	}
	
	// put sumw2's for some histos
	heflow_modules->Sumw2();
	heflow_sectors->Sumw2();
	heflow->Sumw2();
	heflow_dijet->Sumw2();
	heflow_DijetRatio->Sumw2();
	heflow_channels->Sumw2();
	heflow_usedchannels->Sumw2();
	
	TIter       next(filelist); 
	TObjString* fn = 0;
	TString currentfile = "";
	
	bool isMC = false;
	
	// start file loop
	while((fn = (TObjString*)next())) { 
		
		currentfile.Clear();
		currentfile = fn->GetString();
		
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
		
		// define objects and branches
		MyEvtId *evtid = NULL;
		MyDiJet *dijet = NULL;
		std::vector<MyVertex> *Vertices = NULL;
		std::vector<MyCastorRecHit> *CastorRecHits = NULL;
		std::vector<MyCastorDigi> *CastorDigis = NULL;
		std::vector<MyCastorTower> *CastorTowers = NULL;
		std::vector<MyCastorJet> *CastorJets = NULL;
		
		TBranch *b_evtid = tree->GetBranch("EvtId");
		TBranch *b_dijet = tree->GetBranch("pfDiJet");
		TBranch *b_vertices = tree->GetBranch("primaryVertex");
		TBranch *b_castorjets = tree->GetBranch("castorJet");
		TBranch *b_castorrechits = tree->GetBranch("castorRecHit");
		TBranch *b_castordigis = tree->GetBranch("castorDigi");
		TBranch *b_castortowers = tree->GetBranch("castorTower");
	
		b_evtid->SetAddress(&evtid);
		b_dijet->SetAddress(&dijet);
		b_vertices->SetAddress(&Vertices);
		b_castorjets->SetAddress(&CastorJets);
		b_castorrechits->SetAddress(&CastorRecHits);
		b_castordigis->SetAddress(&CastorDigis);
		b_castortowers->SetAddress(&CastorTowers);
			
		int Nevents = tree->GetEntriesFast();
		std::cout << "events in this file = " << Nevents << std::endl;
		//totalevents += Nevents;
		
		// start event loop
		for (int i=0;i<Nevents;i++) {
			
			/////////////////////////////////////////
			// Fill the histograms in the event loop
			/////////////////////////////////////////
			
			// only fill the histograms when there's 1 vertex (filter out pile-up)
			b_vertices->GetEntry(i);
			//std::cout << " number of primary vertices = " << Vertices->size() << std::endl;
			if (Vertices->size() == 1) {
			
				b_evtid->GetEntry(i);
				// get event id stuff
				if( ((i+1) % 1000) == 0) cout << " run " << evtid->Run << " isData = " << evtid->IsData << " lumiblock " << evtid->LumiBlock << " event " << evtid->Evt << endl; 
				if (!evtid->IsData) isMC = true;
				
				// fill castor digi stuff
				b_castordigis->GetEntry(i);
				double totalfC = 0;
				hNDigis->Fill(CastorDigis->size());
				for (unsigned int j=0;j<CastorDigis->size();j++) {
					MyCastorDigi digi = (*CastorDigis)[j];
					vector<double> fCs = digi.fC;
					vector<double> adcs = digi.adc;
					for (unsigned int k=0;k<fCs.size();k++) {
						hDigi_TS->Fill(k+1,fCs[k]);
					}
					// take pedestal from first 4 TS, then signal from TS 5+6
					double pedestal = (fCs[0]+fCs[1]+fCs[2]+fCs[3])/4;
					double signal = (fCs[4]-pedestal) + (fCs[5]-pedestal);
					hDigi_fC->Fill(signal);
					hDigi_module->Fill(digi.mod,signal);
					hDigi_sector->Fill(digi.sec,signal);
					totalfC += signal;
				}
				hDigi_totalfC->Fill(totalfC);
				
				// fill castor rechit stuff
				b_castorrechits->GetEntry(i);
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
				}
				hRecHit_totalenergy->Fill(totalrechitenergy);
				
				// fill eflow and dijet histograms
				double eflow = 0;
				int usedchannels = 0;
				double outoftime_eflow = 0;
				for (unsigned int j=0;j<CastorRecHits->size();j++) {
					MyCastorRecHit rechit = (*CastorRecHits)[j];
					h2eflow_map->Fill(rechit.sec,rechit.mod,1);
					if (rechit.cha < 81 && rechit.cha != 5 && rechit.cha != 6) { // for data 15,35,81,5,6
						if (evtid->IsData) { // for data, energy is intercalibrated fC
							heflow_channel[rechit.cha-1]->Fill(rechit.energy);
							eflow += rechit.energy;
							usedchannels++;
							h2eflow_grid->Fill(rechit.sec,rechit.mod,rechit.energy);
						} else { // for MC take fC
							heflow_channel[rechit.cha-1]->Fill(rechit.fC);
							eflow += rechit.fC;
							usedchannels++;
							h2eflow_grid->Fill(rechit.sec,rechit.mod,rechit.fC);
						}
					}
					if ((rechit.time < 15 || rechit.time > 35) && rechit.cha < 81 && rechit.cha != 5 && rechit.cha != 6) outoftime_eflow += rechit.energy;
				}
				heflow->Fill(eflow);
				heflow_usedchannels->Fill(usedchannels);
				heflow_outoftime->Fill(outoftime_eflow);
				heflow_pileup[Vertices->size()-1]->Fill(eflow);
				
				b_dijet->GetEntry(i);
				if (dijet->isDiJet) heflow_dijet->Fill(eflow);

				// do some more rechit stuff
				//if (CastorRecHits->size() < 224) std::cout << "this event has only " << CastorRecHits->size() << " rechits " << " run " << evtid->Run << " isData = " << evtid->IsData << " lumiblock " << evtid->LumiBlock << " event " << evtid->Evt << std::endl;
				//if (evtid->LumiBlock == 64) std:: cout << " lumiblock 64, event = " << evtid->Evt << std::endl;
				
				
				// fill castor tower stuff
				b_castortowers->GetEntry(i);
				hNTowers->Fill(CastorTowers->size());
				for (unsigned int j=0;j<CastorTowers->size();j++) {
					MyCastorTower tower = (*CastorTowers)[j];
					hTower_energy->Fill(tower.energy);
					hTower_pt->Fill(tower.pt);
					hTower_eta->Fill(tower.eta);
					hTower_phi->Fill(tower.phi);
					hTower_fem->Fill(tower.fem);
					hTower_depth->Fill(tower.depth);
					hTower_fhot->Fill(tower.fhot);
					hTower_ncell->Fill(tower.ncell);
				}
				
				// fill castor jet stuff
				b_castorjets->GetEntry(i);
				hNJets->Fill(CastorJets->size());
				for (unsigned int j=0;j<CastorJets->size();j++) {
					MyCastorJet jet = (*CastorJets)[j];
					hJet_energy->Fill(jet.energy);
					hJet_pt->Fill(jet.pt);
					hJet_eta->Fill(jet.eta);
					hJet_phi->Fill(jet.phi);
					hJet_fem->Fill(jet.fem);
					hJet_width->Fill(jet.width);
					hJet_depth->Fill(jet.depth);
					hJet_fhot->Fill(jet.fhot);
					hJet_sigmaz->Fill(jet.sigmaz);
					hJet_ntower->Fill(jet.ntower);
				}
				
				// end of event, print status
				if( ((i+1) % 1000) == 0) std::cout << i+1 <<"events done in file " << it << std::endl;
				totalevents++;
				
			} // end if statement for 1 vertex
			else if (Vertices->size() > 1) {
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
			} // end if statement for more than 1 vertex
			
		} // end event loop
		
		f->Close();
		it++;
	} // end file loop
	
	
	//////////////////////////////////////////////////
	// energy flow stuff needed after event filling //
	//////////////////////////////////////////////////
	
	std::cout << "starting eflow calculations" << std::endl;
	
	// check distribution of each channel on under or overflow
	for (int icha=0;icha<80;icha++) {
		if (heflow_channel[icha]->GetBinContent(heflow_channel[icha]->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! channel " << icha << " has overflow" << std::endl;
		if (heflow_channel[icha]->GetBinContent(0) !=0) std::cout << "!!WARNING!! channel " << icha << " has underflow" << std::endl;
	}
	
	// check distribution of each pileup on under or overflow
	for (int icha=0;icha<maxVertices;icha++) {
		if (heflow_pileup[icha]->GetBinContent(heflow_pileup[icha]->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! eflow with pileup " << icha << " has overflow" << std::endl;
		if (heflow_pileup[icha]->GetBinContent(0) !=0) std::cout << "!!WARNING!! eflow with pileup " << icha << " has underflow" << std::endl;
	}
	
	// check eflow for under/overflow
	if (heflow->GetBinContent(heflow->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! minbias eflow has overflow" << std::endl;
	if (heflow->GetBinContent(0) !=0) std::cout << "!!WARNING!! minbias eflow has underflow" << std::endl;
	if (heflow_dijet->GetBinContent(heflow_dijet->GetNbinsX()+1) !=0) std::cout << "!!WARNING!! dijet eflow has overflow" << std::endl;
	if (heflow_dijet->GetBinContent(0) !=0) std::cout << "!!WARNING!! dijet eflow has underflow" << std::endl;
	
	// get mean and error's from all channels and put it in one histo
	for (int icha=0;icha<80;icha++) {
		if (icha<32 && isMC) { heflow_channels->SetBinContent(icha+1,2*heflow_channel[icha]->GetMean());} else {heflow_channels->SetBinContent(icha+1,heflow_channel[icha]->GetMean());}
		if (icha<32 && isMC) { heflow_channels->SetBinError(icha+1,2*heflow_channel[icha]->GetMeanError());} else {heflow_channels->SetBinError(icha+1,heflow_channel[icha]->GetMeanError());}
	}
	
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
			if (i<2 && isMC) {average += heflow_channel[j+(i*16)]->GetMean()*2;} else {average += heflow_channel[j+(i*16)]->GetMean();}
			if (i<2 && isMC) {error += 2*heflow_channel[j+(i*16)]->GetMeanError()*heflow_channel[j+(i*16)]->GetMeanError();} else {
				error += heflow_channel[j+(i*16)]->GetMeanError()*heflow_channel[j+(i*16)]->GetMeanError();
			}
		}
		average = average/16;
		error = sqrt(error);
		heflow_modules->SetBinContent(i+1,average);
		heflow_modules->SetBinError(i+1,error);
	}
	
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
			if (j<2 && isMC) {average += heflow_channel[i+(j*16)]->GetMean()*2;} else {average += heflow_channel[i+(j*16)]->GetMean();}
			if (j<2 && isMC) {error += 2*heflow_channel[i+(j*16)]->GetMeanError()*heflow_channel[i+(j*16)]->GetMeanError();} else {
				error += heflow_channel[i+(j*16)]->GetMeanError()*heflow_channel[i+(j*16)]->GetMeanError();
			}
		}
		average = average/5;
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
	
	
	// make a pile up plot
	TH1F *heflow_vs_pileup = new TH1F("heflow_vs_pileup","Mean eflow vs number of vertices",maxVertices,0,maxVertices);
	for (int i=0;i<maxVertices;i++) {
		heflow_vs_pileup->SetBinContent(i+1,heflow_pileup[i]->GetMean());
		heflow_vs_pileup->SetBinError(i+1,heflow_pileup[i]->GetMeanError());
	}
	
	//////////////////////////////////////////////////
	
	/*
	heflow->Sumw2();
	heflow->Scale(1./heflow->Integral());
	
	TH1F *heflow_norm = new TH1F("heflow_norm","Normalized eflow disitribution",104,-0.04,1.01);
	for (int i=0;i<heflow->GetNbinsX();i++) {
		heflow_norm->SetBinContent(i+1,heflow->GetBinContent(i+1));
		heflow_norm->SetBinError(i+1,heflow->GetBinError(i+1));
	}
	*/
	
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
	
	// save digi histos in file
	hDigi_TS->Write();
	hDigi_fC->Write();
	hDigi_totalfC->Write();
	hDigi_module->Write();
	hDigi_sector->Write();
	hNDigis->Write();
	
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
		
	// save tower histos in file
	hNTowers->Write();
	hTower_energy->Write();
	hTower_pt->Write();
	hTower_eta->Write();
	hTower_phi->Write();
	hTower_depth->Write();
	hTower_fhot->Write();
	hTower_fem->Write();
	hTower_ncell->Write();
		
	// save jet histos in file
	hNJets->Write();
	hJet_energy->Write();
	hJet_pt->Write();
	hJet_eta->Write();
	hJet_phi->Write();
	hJet_depth->Write();
	hJet_fhot->Write();
	hJet_fem->Write();
	hJet_ntower->Write();
	hJet_width->Write();
	hJet_sigmaz->Write();
	
	// eflow histos
	heflow->Write();
	heflow_dijet->Write();
	heflow_DijetRatio->Write();
	h2eflow_grid->Write();
	h2eflow_map->Write();
	heflow_usedchannels->Write();
	heflow_sectors->Write();
	heflow_modules->Write();
	for (int icha=0;icha<80;icha++) {
		heflow_channel[icha]->Write();
	}
	heflow_channels->Write();
	//heflow_norm->Write();
	heflow_outoftime->Write();
	
	for (int icha=0;icha<maxVertices;icha++) {
		heflow_pileup[icha]->Write();
	}
	heflow_vs_pileup->Write();
	
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
