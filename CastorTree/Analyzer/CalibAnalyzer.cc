
#include "CalibAnalyzer.h"

//-- standard root includes
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

//-- standard c++ includes
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>

//-- private classes includes
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
#include "../src/MyCaloTower.h"
#include "../src/MyGenPart.h"

#define verbose 1

CalibAnalyzer::CalibAnalyzer() { }

CalibAnalyzer::~CalibAnalyzer() { }

void CalibAnalyzer::Loop(TString inputdir, TObjArray* filelist, double cmenergy) {
  
  using namespace std;

  int file_nb = 0;    
  int nb_evt_tot = 0;
  int nb_file_max = 1;

  int nb_data_sel = 0;

  double E_cha_reco_min = 1000000;
  double E_cha_reco_max = -1000000;

  double E_mod_reco_min = 1000000;
  double E_mod_reco_max = -1000000;

  double E_sec_reco_min = 1000000;
  double E_sec_reco_max = -1000000;

  //------------------------//
  //-- Define histograms  --//
  //------------------------//

  //--  Selection   

  TH1D *hselection_data = new TH1D("hselection_data","Event Selection Data",7,0.5,7.5); 

  //-- energy distribution 

  TH1D *hchannel_energy = new TH1D("hchannel_energy","channel energy",500,-100,67000);
  TH1D *hchannel_used = new TH1D("hchannel_used","number of used channels to compute eflow",80,0.5,80.5);

  Char_t hlabel[200],hname[50];

  TH1D *hMBchannel[16][5];
  
  for (int imod = 0; imod < 5;imod++) {
    for (int isec = 0; isec < 16;isec++) 
      hMBchannel[isec][imod] = MakeHisto(isec,imod,"hMBchannel","MB energy distibution in channel","E [fC]","N evts",500,-100,67000);
  }
  
  TH1D *hMBmodule[5];
  for (int imod = 0; imod < 5;imod++) hMBmodule[imod] = MakeHisto(imod,"hMBmodule","MB energy distibution in module","E [fC]","N evts",500,-200,93800);
 
  TH1D *hMBmodule_sector_used[5];
  for (int imod = 0; imod < 5;imod++) hMBmodule_sector_used[imod] = MakeHisto(imod,"hMBmodule_sector_used","MB number of sectors used in module","sector","N evts",16,0.5,16.5);
 
  TH1D *hMBsector[16];
  for (int isec = 0; isec < 16;isec++) hMBsector[isec] = MakeHisto(isec,"hMBsector","MB energy distibution in sector","E [fC]","N evts",500,-200,91800);

  TH1D *hMBsector_module_used[16];
  for (int isec = 0; isec < 16;isec++) hMBsector_module_used[isec] = MakeHisto(isec,"hMBsector_module_used","MB number of modules used in sector","module","N evts",5,0.5,5.5);

  //-- z profile and phi profile 

  TH1D *hMBzprofile[16]; 
  for (int isec = 0; isec < 16;isec++) hMBzprofile[isec] = MakeHisto(isec,"hMBzprofile_sector","MB z profile in sector","module","E [fC]",5,0.5,5.5);

  TH1D *hMBphiprofile[5];
  for (int imod = 0; imod < 5;imod++) hMBphiprofile[imod] = MakeHisto(imod,"hMBphiprofile_module","MB phi profile in module","sector","E [fC]",16,0.5,16.5);

  TH1D *hMBzprofile_mean = MakeHisto("hMBzprofile_mean","MB z profile averaged over all sectors","module","E [fC]",5,0.5,5.5);

  TH1D *hMBphiprofile_mean = MakeHisto("hMBphiprofile_mean","MB phi profile averaged over all modules","sector","E [fC]",16,0.5,16.5);

  //-- eflow

  Int_t nbin_eflow, bin_eflow_min, bin_eflow_max;
  Int_t nbin_en, bin_en_min, bin_en_max;
  double ptcut;

  if(cmenergy == 900) {

    nbin_eflow = 200;
    bin_eflow_min = -2000;
    bin_eflow_max = 60000;

    nbin_en = 400;
    bin_en_min = 0;
    bin_en_max = 100000;

    ptcut = 8;

  } else if (cmenergy == 2760) {

    nbin_eflow = 366;
    bin_eflow_min = -2000;
    bin_eflow_max = 120000; 

    nbin_en = 400;
    bin_en_min = 0;
    bin_en_max = 10000;

    ptcut = 12;

  } else if (cmenergy == 7000) {

    nbin_eflow = 756; 
    bin_eflow_min = -2000;
    bin_eflow_max = 250000;

    nbin_en = 400;
    bin_en_min = 0;
    bin_en_max = 100000;

    ptcut = 20;
  }
  
  TH1D *hMBEflow = MakeHisto("hMBEflow","MB energy flow","Eflow [fC]","N evts",nbin_eflow,bin_eflow_min,bin_eflow_max); 

  //-----------------------------------//
  //-- Loop over the different files --//
  //-----------------------------------//
  
  TIter temp_next(filelist); 
  TObjString* temp_itfile = 0;
  
  int Nfile_all = 0;
  int nb_evt_all_files = 0;
  
  while((temp_itfile = (TObjString*)temp_next())) {
    
    TFile* file = TFile::Open(inputdir+temp_itfile->GetString(),"READ");
    
    if (!file) {
      cout<<"Error in CalibAnalyzer: could not open file "<<temp_itfile->GetString()<<endl;
      continue;
    }
    
    TTree *tree = new TTree("CastorTree","");
    file->GetObject("castortree/CastorTree",tree);
    
    Nfile_all++;
    nb_evt_all_files+=tree->GetEntriesFast();
  }
    
  cout<<endl<<"you are going to loop on "<<Nfile_all<<" files containing "<<nb_evt_all_files<<" events"<<endl<<endl;
  
  TIter next(filelist);
  TObjString* itfile = 0;
  TString filename = "";
  
  while((itfile = (TObjString*)next()) && (file_nb < nb_file_max || nb_file_max == -1)) {
    
    file_nb++;
    
    filename.Clear();
    filename = itfile->GetString();
    
    cout<<endl<<"open file "<<file_nb<<" with name: "<<itfile->GetString()<<endl;
    
    TFile* file = TFile::Open(inputdir+itfile->GetString(),"READ");
    
    if (!file) { 
      cout<<"Error in CalibAnalyzer: could not open file "<<itfile->GetString()<<endl; 
      continue; 
    } 
    
    //-- Get tree from file
    
    TTree *tree = new TTree("CastorTree","");
    file->GetObject("castortree/CastorTree",tree);
    
    //-- define objects and branches
    
    MyEvtId *evtid = NULL;
    MyDiJet *dijet = NULL;
    MyHLTrig *HLTrig = NULL;
    MyL1Trig *L1Trig = NULL;
    vector<MyVertex> *Vertices = NULL;
    vector<MyCastorRecHit> *CastorRecHits = NULL;
    vector<MyJet> *PFJets = NULL;
    std::vector<MyCaloTower> *caloTowers = NULL;

    TBranch *b_evtid = tree->GetBranch("EvtId");
    TBranch *b_dijet = tree->GetBranch("pfDiJet");
    TBranch *b_HLTrig = tree->GetBranch("HLTrig");
    TBranch *b_L1Trig = tree->GetBranch("L1Trig");
    TBranch *b_vertices = tree->GetBranch("primaryVertex");
    TBranch *b_castorrechits = tree->GetBranch("castorRecHit");
    TBranch *b_PFJets = tree->GetBranch("pfJet");
    TBranch *b_caloTowers = tree->GetBranch("caloTower");
    
    b_evtid->SetAddress(&evtid);
    b_dijet->SetAddress(&dijet);
    b_HLTrig->SetAddress(&HLTrig);
    b_L1Trig->SetAddress(&L1Trig);
    b_vertices->SetAddress(&Vertices);
    b_castorrechits->SetAddress(&CastorRecHits);
    b_PFJets->SetAddress(&PFJets);
    b_caloTowers->SetAddress(&caloTowers);

    int Nevents = tree->GetEntriesFast();
    cout <<"number of events in file "<<file_nb<<" = "<<Nevents<<endl<<endl;

    //--------------------------//    
    //-- Loop over the events --//
    //--------------------------//
    
    for (int ievt=0;ievt<Nevents;ievt++) {

      //-- Do stuff before filters

      b_evtid->GetEntry(ievt);
      b_HLTrig->GetEntry(ievt);
      b_L1Trig->GetEntry(ievt);
      b_vertices->GetEntry(ievt);
      b_caloTowers->GetEntry(ievt);

      nb_evt_tot++;
      hselection_data->Fill(1,1);
     
      if((ievt+1)%5000 == 0) cout<<endl<<"number of events done in file "<<file_nb<<" = "<<ievt+1<<endl;
      if((ievt+1)%5000 == 0) cout<<"total number of events done = "<<nb_evt_tot<<" ("<<100*nb_evt_tot/nb_evt_all_files<<"%)"<<endl;
      if((ievt+1)%5000 == 0) cout<<"number of selected events in data = "<<nb_data_sel<<endl<<endl;
      
      //-- Get vertex information
      
      bool at_least_one_good_vertex = false;
      
      for (unsigned int iVert=0;iVert<Vertices->size();iVert++) {
	MyVertex vertex = (*Vertices)[iVert];
	if (vertex.isGoodVertex) at_least_one_good_vertex = true;
      }
   
      //--------------------//   
      //-- Filter on data --//
      //--------------------//

      bool data_sel = false;
      
      //-- filter on physics declared bit
      
      bool physDeclresult = HLTrig->HLTmap["physDeclpath"];
      if (physDeclresult == false) continue;
      hselection_data->Fill(2,1); 
      
      //-- filter on castor invalid data
      
      bool castorInvalidData_result = HLTrig->HLTmap["castorInvalidDataFilterpath"];
      if (castorInvalidData_result == false) continue; 
      hselection_data->Fill(3,1);
      
      //-- filter out scraping events
      
      bool noscrapingresult = HLTrig->HLTmap["noscrapingpath"];
      if (noscrapingresult == false) continue;
      hselection_data->Fill(4,1);
      
      //-- check that L1 triggers are not masked
      
      bool  L1Trigger_in_menu = true;
      if ((cmenergy == 900 || cmenergy == 7000) && (L1Trig->fTechMask[40] || L1Trig->fTechMask[41])) L1Trigger_in_menu = false;
      if (cmenergy == 2760 && L1Trig->fTechMask[126]) L1Trigger_in_menu = false;
      
      if (verbose && L1Trigger_in_menu == false) {
	cout<<"you are going to select using a trigger that is masked!"<<endl;
	if (L1Trig->fTechMask[40]) cout<<"bit TT 40 masked"<<endl;
	if (L1Trig->fTechMask[41]) cout<<"bit TT 41 masked"<<endl;
	if (L1Trig->fTechMask[126]) cout<<"bit PT 126 masked"<<endl;
      }
      
      //-- filter on triggers data
      
      bool L1_BX = L1Trig->fTechDecisionBefore[0];
      bool L1_Veto = !L1Trig->fTechDecisionBefore[36] && !L1Trig->fTechDecisionBefore[37] && !L1Trig->fTechDecisionBefore[38] && !L1Trig->fTechDecisionBefore[39];
      
      bool L1_BSC = L1Trig->fTechDecisionBefore[40] || L1Trig->fTechDecisionBefore[41]; // value for 900 GeV and 7 TeV 
      if (cmenergy == 2760) L1_BSC = L1Trig->fPhysDecisionBefore[126];  // value for 2.76 TeV
      
      bool HF_Activity = true; // default value is true for all energies
      
      if (cmenergy == 2760) {
	
	bool HFplus = false;
	bool HFminus = false;
	
	for (int itow=0;itow<caloTowers->size();itow++) {
	  MyCaloTower mytow = (*caloTowers)[itow];
	  if (mytow.hasHF && mytow.Energy() > 4. && mytow.zside == 1 && mytow.Eta() > 3.23 && mytow.Eta() < 4.65) HFplus = true;
	  if (mytow.hasHF && mytow.Energy() > 4. && mytow.zside == -1 && mytow.Eta() < -3.23 && mytow.Eta() > -4.65) HFminus = true;
	}
	
	if(!(HFplus == true && HFminus == true)) HF_Activity = false; // value can only become false for 2.76 TeV   
      }
      
      bool HLT_BSC = true;  // default value is true for all energies (do we need an HLT at 900 GeV and 7 TeV?)
      if (cmenergy == 2760) HLT_BSC = HLTrig->HLTmap["HLT_L1BscMinBiasORBptxPlusANDMinus_v1"];  // value can only become false for 2.76 TeV
      
      bool TriggerSelection = L1_BX && L1_Veto && L1_BSC && HF_Activity && HLT_BSC;
      
      if (TriggerSelection == false) continue;
      hselection_data->Fill(5,1);
      
      //-- filter on at least one good vertex
      
      if(at_least_one_good_vertex == false) continue;
      hselection_data->Fill(6,1);
      
      data_sel = true;
    
      //-----------------------------------------------------------------------------------------------//    
      //-- at this point, event passed following filters:                                            --//
      //-- physics declared, castor invalid data, no scraping, L1 tech trigger, good vertex for data --// 
      //-----------------------------------------------------------------------------------------------//
      
      if(!data_sel) continue;
		
      //-- Do stuff after filters
					
      //-- get all the remaining branch entries

      b_castorrechits->GetEntry(ievt);
      b_dijet->GetEntry(ievt);
      b_PFJets->GetEntry(ievt);

      //----------------------------------------------------//      
      //-- only one vertex condition (filter out pile-up) --//
      //--               data_sel                         --//
      //----------------------------------------------------//

      //-- filter on exactly one good vertex
	
      if (Vertices->size() != 1) continue;
      hselection_data->Fill(7,1);
      nb_data_sel++;

      double rechit_energy = 0;
      
      double module_energy[5];
      double sector_energy[16];
      for (int imod = 0; imod < 5;imod++) module_energy[imod] = 0;	
      for (int isec = 0; isec < 16;isec++) sector_energy[isec] = 0;
      
      double module_sector_used[5];
      double sector_module_used[16];
      for (int imod = 0; imod < 5;imod++) module_sector_used[imod] = 0;
      for (int isec = 0; isec < 16;isec++) sector_module_used[isec] = 0;
      
      double eflow = 0;
      int usedchannels = 0;
      
      for (unsigned int irec = 0;irec < CastorRecHits->size();irec++) {
	
	MyCastorRecHit rechit = (*CastorRecHits)[irec];
	
	bool used_cha = false;
	if(rechit.cha != 5 && rechit.cha != 6 && rechit.cha <= 80) used_cha = true; //-- for data 15,35,81,5,6
	if(used_cha == false) continue;
	
	rechit_energy = 0;
	rechit_energy = rechit.energy; //-- intercalibrated fC

	if(rechit_energy < E_cha_reco_min) E_cha_reco_min = rechit_energy;
	if(rechit_energy > E_cha_reco_max) E_cha_reco_max = rechit_energy;
	
	module_energy[rechit.mod-1]+=rechit_energy;
	sector_energy[rechit.sec-1]+=rechit_energy;
	
	module_sector_used[rechit.mod-1]++;
	sector_module_used[rechit.sec-1]++;
	
	hchannel_energy->Fill(rechit_energy);	 
	hMBchannel[rechit.sec-1][rechit.mod-1]->Fill(rechit_energy);
	
	eflow+=rechit_energy;
	usedchannels++;
      }
      
      hMBEflow->Fill(eflow);
      hchannel_used->Fill(usedchannels);
      
      for (int imod = 0; imod < 5;imod++) {
	if(module_energy[imod] < E_mod_reco_min) E_mod_reco_min = module_energy[imod];
	if(module_energy[imod] > E_mod_reco_max) E_mod_reco_max = module_energy[imod];
      }
      
      for (int isec = 0; isec < 16;isec++) {
	if(sector_energy[isec] < E_sec_reco_min) E_sec_reco_min = sector_energy[isec];
	if(sector_energy[isec] > E_sec_reco_max) E_sec_reco_max = sector_energy[isec];
      }
      
      for (int imod = 0; imod < 5;imod++) hMBmodule[imod]->Fill(module_energy[imod]);
      for (int isec = 0; isec < 16;isec++) hMBsector[isec]->Fill(sector_energy[isec]);
      
      for (int imod = 0; imod < 5;imod++) hMBmodule_sector_used[imod]->Fill(module_sector_used[imod]);
      for (int isec = 0; isec < 16;isec++) hMBsector_module_used[isec]->Fill(sector_module_used[isec]);
      
    } //-- end event loop
    
    delete tree;
    file->Close();
    
  } //-- end file loop
  
  //--------------------------//
  //-- normalize histograms --//
  //--------------------------//
  
  double MB_mean_channel[16][5];
  double MB_error_channel[16][5];
  
  for (int isec = 0; isec < 16; isec++) {
    for (int imod = 0; imod < 5; imod++) {
      
      MB_mean_channel[isec][imod] = 0;
      MB_error_channel[isec][imod] = 0;
      
      int icha = 16*imod+isec;
      if(icha+1 == 5 || icha+1 == 6) continue;
      
      MB_mean_channel[isec][imod] = hMBchannel[isec][imod]->GetMean();
      MB_error_channel[isec][imod] = hMBchannel[isec][imod]->GetMeanError();    
      
      hMBzprofile[isec]->SetBinContent(imod+1,MB_mean_channel[isec][imod]);
      hMBzprofile[isec]->SetBinError(imod+1,MB_error_channel[isec][imod]);

      hMBphiprofile[imod]->SetBinContent(isec+1,MB_mean_channel[isec][imod]);
      hMBphiprofile[imod]->SetBinError(isec+1,MB_error_channel[isec][imod]);
    
    }
  }
  
  double MB_mean_module[5];
  double MB_error_module[5];
  double MB_mean_module_sector_used[5];

  for (int imod = 0; imod < 5;imod++) {
    MB_mean_module[imod] = hMBmodule[imod]->GetMean();
    MB_error_module[imod] = hMBmodule[imod]->GetMeanError();
    
    MB_mean_module_sector_used[imod] = hMBmodule_sector_used[imod]->GetMean();
    
    MB_mean_module[imod]/=MB_mean_module_sector_used[imod];
    MB_error_module[imod]/=MB_mean_module_sector_used[imod];

    hMBzprofile_mean->SetBinContent(imod+1,MB_mean_module[imod]);
    hMBzprofile_mean->SetBinError(imod+1,MB_error_module[imod]);
  }

  double MB_mean_sector[16];
  double MB_error_sector[16];
  double MB_mean_sector_module_used[16];  

  for (int isec = 0; isec < 16;isec++) {
    MB_mean_sector[isec] = hMBsector[isec]->GetMean();
    MB_error_sector[isec] = hMBsector[isec]->GetMeanError();
    
    MB_mean_sector_module_used[isec] = hMBsector_module_used[isec]->GetMean();

    MB_mean_sector[isec]/=MB_mean_sector_module_used[isec];
    MB_error_sector[isec]/=MB_mean_sector_module_used[isec];

    hMBphiprofile_mean->SetBinContent(isec+1,MB_mean_sector[isec]);
    hMBphiprofile_mean->SetBinError(isec+1,MB_error_sector[isec]);
  }

  //------------------------------------//
  //-- check for underflow - overflow  -//
  //------------------------------------//

  //--  Selection

  CheckHisto(hselection_data);
 
  //-- energy distribution

  CheckHisto(hchannel_energy);
  CheckHisto(hchannel_used);
  
  for (int isec = 0; isec < 16;isec++) {
    for (int imod = 0; imod < 5;imod++) {
      CheckHisto(hMBchannel[isec][imod]);
    }
  }

  for (int imod = 0; imod < 5;imod++) CheckHisto(hMBmodule[imod]);
  for (int imod = 0; imod < 5;imod++) CheckHisto(hMBmodule_sector_used[imod]);
  for (int isec = 0; isec < 16;isec++) CheckHisto(hMBsector[isec]);
  for (int isec = 0; isec < 16;isec++) CheckHisto(hMBsector_module_used[isec]);

  //-- z profile and phi profile

  for (int isec = 0; isec < 16;isec++) CheckHisto(hMBzprofile[isec]);
  for (int imod = 0; imod < 5;imod++) CheckHisto(hMBphiprofile[imod]);

  CheckHisto(hMBzprofile_mean);
  CheckHisto(hMBphiprofile_mean);

  //-- eflow

  CheckHisto(hMBEflow);

  //-------------------------------------//
  //-- write histo to output root file --//
  //-------------------------------------//
  
  cout<<endl<<"total number of events: "<<nb_evt_tot<<" from "<<file_nb<<" file(s)"<<endl;
  cout<<nb_data_sel<<" selected events in data"<<endl;

  cout<<endl<<"E channel reco min: "<<E_cha_reco_min<<endl;
  cout<<"E channel reco max: "<<E_cha_reco_max<<endl;
  
  cout<<endl<<"E module reco min: "<<E_mod_reco_min<<endl;
  cout<<"E module reco max: "<<E_mod_reco_max<<endl;
  
  cout<<endl<<"E sector reco min: "<<E_sec_reco_min<<endl;
  cout<<"E sector reco max: "<<E_sec_reco_max<<endl<<endl;

  Char_t output_filename[200];
  const char* part = filename.Data();
  sprintf(output_filename,"../Result/output_calib_%s",part);
  TFile* foutput = new TFile(output_filename,"RECREATE");
  foutput->cd();

  //--  Selection
	
  hselection_data->Write();

  //-- energy distribution

  hchannel_energy->Write();
  hchannel_used->Write();

  for (int imod = 0; imod < 5;imod++) {
    for (int isec = 0; isec < 16;isec++) {
      hMBchannel[isec][imod]->Write();
    }
  }
  
  for (int imod = 0; imod < 5;imod++) hMBmodule[imod]->Write();
  for (int imod = 0; imod < 5;imod++) hMBmodule_sector_used[imod]->Write();
  for (int isec = 0; isec < 16;isec++) hMBsector[isec]->Write();
  for (int isec = 0; isec < 16;isec++) hMBsector_module_used[isec]->Write();

  //-- z profile and phi profile

  for (int isec = 0; isec < 16;isec++) hMBzprofile[isec]->Write();
  for (int imod = 0; imod < 5;imod++) hMBphiprofile[imod]->Write();

  hMBzprofile_mean->Write();
  hMBphiprofile_mean->Write();

  //-- eflow

  hMBEflow->Write();

  foutput->Close();
  cout<<"file "<<output_filename<<" created"<<endl;

  //-----------------------------------//
  //-- compute some means and sigmas --//
  //-----------------------------------//

  double energy_from_HF = 581;
  double corr_to_had_level = 1.81;

  cout<<endl<<"data at "<<cmenergy<<" GeV"<<endl;
  cout<<"mean E flow MB: "<<hMBEflow->GetMean()<<" fC"<<endl;
  
  double calib_factor_mean = energy_from_HF/(corr_to_had_level*hMBEflow->GetMean()); 
  cout<<"mean calibration factor: "<<calib_factor_mean<<" GeV/fC"<<endl<<endl;

  cout<<"mean E flow MB from module mean = ";
  double E_flow_MB_module_check = 0;
  for (int imod = 0; imod < 5; imod++) {
    E_flow_MB_module_check+=MB_mean_module_sector_used[imod]*MB_mean_module[imod];
    cout<<MB_mean_module_sector_used[imod]<<"*"<<MB_mean_module[imod];
    if(imod < 4) cout<<"+";
    if(imod == 4) cout<<" = "<<E_flow_MB_module_check<<" fC"<<endl<<endl;
  }

  cout<<"mean E flow MB from sector mean = ";
  double E_flow_MB_sector_check = 0;
  for (int isec = 0; isec < 16; isec++) {
    E_flow_MB_sector_check+=MB_mean_sector_module_used[isec]*MB_mean_sector[isec];
    cout<<MB_mean_sector_module_used[isec]<<"*"<<MB_mean_sector[isec];
    if(isec < 15) cout<<"+";
    if(isec == 15) cout<<" = "<<E_flow_MB_sector_check<<" fC"<<endl<<endl;
  }

  for (int imod = 0; imod < 5; imod++) {
    cout<<"module "<<imod<<": "<<MB_mean_module_sector_used[imod]*MB_mean_module[imod]<<" fC"<<endl;
    if(imod == 4) cout<<endl;
  }

  for (int isec = 0; isec < 16; isec++) {
    cout<<"sector "<<isec<<": "<<MB_mean_sector_module_used[isec]*MB_mean_sector[isec]<<" fC"<<endl;
    if(isec == 15) cout<<endl;
  }

  cout<<"contribution channel first module"<<endl<<endl;;
  
  double contribution_channel_first_module[16];
  for (int isec = 0; isec < 16; isec++) contribution_channel_first_module[isec] = 0;

  double contribution_channel_first_module_mean = 0;
  int N_channel_first_module = 0;
  
  for (int isec = 0; isec < 16; isec++) {
    int icha = isec;
    if(icha+1 == 5 || icha+1 == 6) continue;

    contribution_channel_first_module[isec] = (100*MB_mean_channel[isec][0])/( MB_mean_sector[isec]*MB_mean_sector_module_used[isec]);

    contribution_channel_first_module_mean+=contribution_channel_first_module[isec];
    N_channel_first_module++;
  }

  contribution_channel_first_module_mean/=N_channel_first_module;

  for (int isec = 0; isec < 16; isec++)
    cout<<"contribution channel first module in sector "<<isec+1<<": "<<contribution_channel_first_module[isec]<<" %"<<endl;
  
  cout<<endl<<"contribution channel first module mean: "<<contribution_channel_first_module_mean<<" %"<<endl;

  cout<<endl<<"calibration factor"<<endl<<endl;

  double calib_factor_sector[16];
  double f_sector[16];
  for (int isec = 0; isec < 16; isec++) f_sector[isec] = 0.0625;

  for (int isec = 0; isec < 16; isec++) {
    calib_factor_sector[isec] = (energy_from_HF*f_sector[isec])/(corr_to_had_level*MB_mean_sector_module_used[isec]*MB_mean_sector[isec]);
    if(isec == 4 || isec == 5) calib_factor_sector[isec]/=(1+0.01*contribution_channel_first_module_mean);    
    cout<<"calibration factor sector "<<isec+1<<": "<<calib_factor_sector[isec]<<" GeV/fC"<<endl;
  }

  cout<<endl<<"spread of intercalibrated factors"<<endl<<endl;
  
  double MB_sigma2_module[5];
  double MB_sigma_module[5];
  double MB_sigma_mu_ratio[5];
  int N_module[5];

  for (int imod = 0; imod < 5; imod++) {
    MB_sigma2_module[imod] = 0;
    MB_sigma_module[imod] = 0;
    MB_sigma_mu_ratio[imod] = 0;
    N_module[imod] = 0;
  }

  for (int imod = 0; imod < 5; imod++) {

    for(int isec = 0; isec < 16; isec++) {
      if(imod*16+isec+1 == 5 || imod*16+isec+1 == 6) continue;
      MB_sigma2_module[imod]+=TMath::Power(MB_mean_channel[isec][imod] - MB_mean_module[imod],2);
      N_module[imod]++;
    }
    
    MB_sigma2_module[imod]/=N_module[imod];
    MB_sigma_module[imod] = TMath::Sqrt(MB_sigma2_module[imod]);
    MB_sigma_mu_ratio[imod] = 100*MB_sigma_module[imod]/MB_mean_module[imod];
    cout<<"module "<<imod+1<<": MB mean averaged over all sectors: "<<MB_mean_module[imod]<<", sigma : "<<MB_sigma_module[imod]<<", sigma/mean: "<<MB_sigma_mu_ratio[imod]<<" %"<<endl;    
  }

  cout<<endl;
  for (int imod = 0; imod < 5; imod++) cout<<"module "<<imod+1<<": mean number of sectors used: "<<MB_mean_module_sector_used[imod]<<endl;
  cout<<endl;
  for(int isec = 0; isec < 16; isec++) cout<<"sector "<<isec+1<<": mean number of modules used: "<<MB_mean_sector_module_used[isec]<<endl;

}

void CalibAnalyzer::CheckHisto(TH1D* h) {

  Int_t NbinX = h->GetNbinsX();
  
  if(h->GetBinContent(0) != 0) cout<<h->GetTitle()<<" has underflow of "<<h->GetBinContent(0)<<" entries"<<endl;
  if(h->GetBinContent(NbinX+1) != 0) cout<<h->GetTitle()<<" has overflow of "<<h->GetBinContent(NbinX+1)<<" entries"<<endl;
  
  return;
}

TH1D* CalibAnalyzer::MakeHisto(TString name, TString title, TString xleg, TString yleg, int nbin, double bmin, double bmax) {


  TH1D* h = new TH1D(name,title,nbin,bmin,bmax);

  h->GetXaxis()->SetTitle(xleg);
  h->GetYaxis()->SetTitle(yleg);

  h->SetMinimum(0);
  h->Sumw2();

  cout<<"create histo: "<<h->GetName()<<" with title: "<<h->GetTitle()<<endl;

  return h;
}

TH1D* CalibAnalyzer::MakeHisto(int id, TString name, TString title, TString xleg, TString yleg, int nbin, double bmin, double bmax) {

  int num = id+1;

  TString name_num = TString(name) + TString("_");
  name_num+=num;

  TString title_num = TString(title) + TString(" ");
  title_num+=num;

  TH1D* h = new TH1D(name_num,title_num,nbin,bmin,bmax);

  h->GetXaxis()->SetTitle(xleg);
  h->GetYaxis()->SetTitle(yleg);

  h->SetMinimum(0);
  h->Sumw2();

  cout<<"create histo: "<<h->GetName()<<" with title: "<<h->GetTitle()<<endl;
  
  return h;
}

TH1D* CalibAnalyzer::MakeHisto(int isec, int imod, TString name, TString title, TString xleg, TString yleg, int nbin, double bmin, double bmax) {

  int icha = 16*imod + isec + 1;

  TString name_icha = TString(name) + TString("_");
  name_icha+=icha;

  TString title_icha = TString(title) + TString(" ");
  title_icha+=icha;

  TH1D* h = new TH1D(name_icha,title_icha,nbin,bmin,bmax);

  h->GetXaxis()->SetTitle(xleg);
  h->GetYaxis()->SetTitle(yleg);

  h->SetMinimum(0);
  h->Sumw2();

  cout<<"create histo: "<<h->GetName()<<" with title: "<<h->GetTitle()<<endl;

  return h;
}
