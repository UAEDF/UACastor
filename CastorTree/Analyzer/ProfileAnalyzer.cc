
#include "ProfileAnalyzer.h"

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
#include "../src/MyGenPart.h"

#define verbose 1

ProfileAnalyzer::ProfileAnalyzer() { }

ProfileAnalyzer::~ProfileAnalyzer() { }

void ProfileAnalyzer::Loop(TString inputdir, TObjArray* filelist, bool isData, double cmenergy) {
  
  using namespace std;

  double fac_data = 0.015;
  double fac_moca = 0.9375;  //-- 0.015/0.016
  
  int file_nb = 0;    
  int nb_evt_tot = 0;
  int nb_file_max = 5;

  int nb_data_sel = 0;
  int nb_moca_reco_sel = 0;
  int nb_moca_gen_sel = 0;
  int nb_moca_gen_non_zero_eflow = 0;

  double E_gen_max = -100;
  double E_gen_elm_max = -100;
  double E_gen_had_max = -100;

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
  TH1D *hselection_moca_reco = new TH1D("hselection_moca_reco","Event Selection MC reco",4,0.5,4.5);
  TH1D *hselection_moca_gen = new TH1D("hselection_moca_gen","Event Selection MC gen",3,0.5,3.5);

  //-- timing distribution
  
  TH1D *hchannel_time = new TH1D("hchannel_time","channel time",105,-5,100);
  
  //-- energy distribution 

  TH1D *hchannel_energy = new TH1D("hchannel_energy","channel energy",755,-5,750);
  TH1D *hchannel_oot_energy = new TH1D("hchannel_oot_energy","channel out-of-time energy",505,-5,500);
  TH1D *hchannel_used = new TH1D("hchannel_used","number of used channels to compute eflow",80,0.5,80.5);

  Char_t hlabel[200],hname[50];

  TH1D *hMBchannel[16][5];
  TH1D *hDJchannel[16][5];
  
  for (int imod = 0; imod < 5;imod++) {
    for (int isec = 0; isec < 16;isec++) {
      hMBchannel[isec][imod] = MakeHisto(isec,imod,"hMBchannel","MB energy distibution in channel","E [GeV]","N evts",755,-5,750);
      hDJchannel[isec][imod] = MakeHisto(isec,imod,"hDJchannel","DJ energy distibution in channel","E [GeV]","N evts",755,-5,750);
    }
  }
  
  TH1D *hMBmodule[5];
  TH1D *hDJmodule[5];
  for (int imod = 0; imod < 5;imod++) hMBmodule[imod] = MakeHisto(imod,"hMBmodule","MB energy distibution in module","E [GeV]","N evts",228,-40,1100);
  for (int imod = 0; imod < 5;imod++) hDJmodule[imod] = MakeHisto(imod,"hDJmodule","DJ energy distibution in module","E [GeV]","N evts",228,-40,1100);
 
  TH1D *hMBmodule_sector_used[5];
  TH1D *hDJmodule_sector_used[5];
  for (int imod = 0; imod < 5;imod++) hMBmodule_sector_used[imod] = MakeHisto(imod,"hMBmodule_sector_used","MB number of sectors used in module","sector","N evts",16,0.5,16.5);
  for (int imod = 0; imod < 5;imod++) hDJmodule_sector_used[imod] = MakeHisto(imod,"hDJmodule_sector_used","DJ number of sectors used in module","sector","N evts",16,0.5,16.5);
 
  TH1D *hMBsector[16];
  TH1D *hDJsector[16];
  for (int isec = 0; isec < 16;isec++) hMBsector[isec] = MakeHisto(isec,"hMBsector","MB energy distibution in sector","E [GeV]","N evts",264,-40,1280);
  for (int isec = 0; isec < 16;isec++) hDJsector[isec] = MakeHisto(isec,"hDJsector","DJ energy distibution in sector","E [GeV]","N evts",264,-40,1280);

  TH1D *hMBsector_module_used[16];
  TH1D *hDJsector_module_used[16];
  for (int isec = 0; isec < 16;isec++) hMBsector_module_used[isec] = MakeHisto(isec,"hMBsector_module_used","MB number of modules used in sector","module","N evts",5,0.5,5.5);
  for (int isec = 0; isec < 16;isec++) hDJsector_module_used[isec] = MakeHisto(isec,"hDJsector_module_used","DJ number of modules used in sector","module","N evts",5,0.5,5.5);

  //-- z profile and phi profile 

  TH1D *hMBzprofile[16]; 
  TH1D *hDJzprofile[16];
  for (int isec = 0; isec < 16;isec++) hMBzprofile[isec] = MakeHisto(isec,"hMBzprofile_sector","MB z profile in sector","module","E [GeV]",5,0.5,5.5);
  for (int isec = 0; isec < 16;isec++) hDJzprofile[isec] = MakeHisto(isec,"hDJzprofile_sector","DJ z profile in sector","module","E [GeV]",5,0.5,5.5);

  TH1D *hMBphiprofile[5];
  TH1D *hDJphiprofile[5];
  for (int imod = 0; imod < 5;imod++) hMBphiprofile[imod] = MakeHisto(imod,"hMBphiprofile_module","MB phi profile in module","sector","E [GeV]",16,0.5,16.5);
  for (int imod = 0; imod < 5;imod++) hDJphiprofile[imod] = MakeHisto(imod,"hDJphiprofile_module","DJ phi profile in module","sector","E [GeV]",16,0.5,16.5);

  TH1D *hMBzprofile_mean = MakeHisto("hMBzprofile_mean","MB z profile averaged over all sectors","module","E [GeV]",5,0.5,5.5);
  TH1D *hDJzprofile_mean = MakeHisto("hDJzprofile_mean","DJ z profile averaged over all sectors","module","E [GeV]",5,0.5,5.5);

  TH1D *hMBphiprofile_mean = MakeHisto("hMBphiprofile_mean","MB phi profile averaged over all modules","sector","E [GeV]",16,0.5,16.5);
  TH1D *hDJphiprofile_mean = MakeHisto("hDJphiprofile_mean","DJ phi profile averaged over all modules","sector","E [GeV]",16,0.5,16.5);

  //-- eflow

  Int_t nbin_eflow, bin_eflow_min, bin_eflow_max;
  Int_t nbin_en, bin_en_min, bin_en_max;
  double ptcut;

  if(cmenergy == 900) {

    nbin_eflow = 186;
    bin_eflow_min = -30;
    bin_eflow_max = 900;

    nbin_en = 300;
    bin_en_min = 0;
    bin_en_max = 1500;

    ptcut = 8;

  } else if (cmenergy == 2760) {

    nbin_eflow = 366;
    bin_eflow_min = -30;
    bin_eflow_max = 1800; 

    nbin_en = 300;
    bin_en_min = 0;
    bin_en_max = 1500;

    ptcut = 12;

  } else if (cmenergy == 7000) {

    nbin_eflow = 756; 
    bin_eflow_min = -30;
    bin_eflow_max = 3750;

    nbin_en = 300;
    bin_en_min = 0;
    bin_en_max = 1500;

    ptcut = 20;
  }
  
  
  TH1D *hMBEflow = MakeHisto("hMBEflow","MB energy flow","Eflow [GeV]","N evts",nbin_eflow,bin_eflow_min,bin_eflow_max); 
  TH1D *hDJEflow = MakeHisto("hDJEflow","DJ energy flow","Eflow [GeV]","N evts",nbin_eflow,bin_eflow_min,bin_eflow_max);
  TH1D *hEflow_gen = MakeHisto("hEflow_gen","gen energy flow","Eflow [GeV]","N evts",nbin_eflow,bin_eflow_min,bin_eflow_max);

  //-- generated information

  TH1D *hgen_energy = new TH1D("hgen_energy","generated energy",nbin_en,bin_en_min,bin_en_max);
  TH1D *hgen_eta  = new TH1D("hgen_eta","generated eta",56,-6.6,-5.2);
  TH1D *hgen_phi = new TH1D("hgen_phi","generated phi",100,-M_PI,M_PI);
  hgen_phi->SetMinimum(0);

  TH1D *hgen_elm_energy = new TH1D("hgen_elm_energy","generated elm energy",nbin_en,bin_en_min,bin_en_max);
  TH1D *hgen_elm_eta = new TH1D("hgen_elm_eta","generated elm eta",56,-6.6,-5.2);
  TH1D *hgen_elm_phi = new TH1D("hgen_elm_phi","generated elm phi",100,-M_PI,M_PI);
  hgen_elm_phi->SetMinimum(0);
  TH1D *hEflow_gen_elm = new TH1D("hEflow_gen_elm","energy flow gen elm",nbin_eflow,bin_eflow_min,bin_eflow_max);
  TH1D *hEflow_gen_elm_fraction = new TH1D("hEflow_gen_elm_fraction","generated elm energy fraction",102,-0.01,1.01);
  hEflow_gen_elm_fraction->Sumw2();

  TH1D *hgen_had_energy = new TH1D("hgen_had_energy","generated had energy",nbin_en,bin_en_min,bin_en_max);
  TH1D *hgen_had_eta = new TH1D("hgen_had_eta","generated had eta",56,-6.6,-5.2);
  TH1D *hgen_had_phi = new TH1D("hgen_had_phi","generated had phi",100,-M_PI,M_PI);
  hgen_had_phi->SetMinimum(0);
  TH1D *hEflow_gen_had = new TH1D("hEflow_gen_had","energy flow gen had",nbin_eflow,bin_eflow_min,bin_eflow_max);
  TH1D *hEflow_gen_had_fraction = new TH1D("hEflow_gen_had_fraction","generated had energy fraction",102,-0.01,1.01);
  hEflow_gen_had_fraction->Sumw2();

  //-- trigger information

  TH1D *hTriggerBefore[7]; //-- [0] 0 - [1] 36 - [2] 37 - [3] 38 - [4] 39 - [5] 40 - [6] 41
  TH1D *hTriggerAfter[7];  //-- [0] 0 - [1] 36 - [2] 37 - [3] 38 - [4] 39 - [5] 40 - [6] 41
  TH1D *hTriggerMask[7];   //-- [0] 0 - [1] 36 - [2] 37 - [3] 38 - [4] 39 - [5] 40 - [6] 41

  hTriggerBefore[0] = new TH1D("decision before trigger 0","hdecision_before_trigger_0",2,-0.5,1.5);
  hTriggerAfter[0] = new TH1D("decision after trigger 0","hdecision_after_trigger_0",2,-0.5,1.5);
  hTriggerMask[0] = new TH1D("decision mask trigger 0","hdecision_mask_trigger_0",2,-0.5,1.5);

  for (int itrig = 1; itrig < 7;itrig++) {

    sprintf(hlabel,"decision before trigger %d",35+itrig);  
    sprintf(hname,"hdecision_before_trigger_%d",35+itrig);
    hTriggerBefore[itrig] = new TH1D(hname,hlabel,2,-0.5,1.5);

    sprintf(hlabel,"decision after trigger %d",35+itrig);
    sprintf(hname,"hdecision_after_trigger_%d",35+itrig);
    hTriggerAfter[itrig] = new TH1D(hname,hlabel,2,-0.5,1.5);

    sprintf(hlabel,"decision mask trigger %d",35+itrig);
    sprintf(hname,"hdecision_mask_trigger_%d",35+itrig);
    hTriggerMask[itrig] = new TH1D(hname,hlabel,2,-0.5,1.5);
  }

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
      cout<<"Error in ProfileAnalyzer: could not open file "<<temp_itfile->GetString()<<endl;
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
      cout<<"Error in ProfileAnalyzer: could not open file "<<itfile->GetString()<<endl; 
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
    // vector<MyCastorDigi> *CastorDigis = NULL;
    vector<MyJet> *PFJets = NULL;
    vector<MyGenPart> *genParts = NULL;
    
    TBranch *b_evtid = tree->GetBranch("EvtId");
    TBranch *b_dijet = tree->GetBranch("pfDiJet");
    TBranch *b_HLTrig = tree->GetBranch("HLTrig");
    TBranch *b_L1Trig = tree->GetBranch("L1Trig");
    TBranch *b_vertices = tree->GetBranch("primaryVertex");
    TBranch *b_castorrechits = tree->GetBranch("castorRecHit");
    // TBranch *b_castordigis = tree->GetBranch("castorDigi");
    TBranch *b_PFJets = tree->GetBranch("pfJet");
    TBranch *b_genParts; 
    if(!isData) b_genParts = tree->GetBranch("GenPart");
    
    b_evtid->SetAddress(&evtid);
    b_dijet->SetAddress(&dijet);
    b_HLTrig->SetAddress(&HLTrig);
    b_L1Trig->SetAddress(&L1Trig);
    b_vertices->SetAddress(&Vertices);
    b_castorrechits->SetAddress(&CastorRecHits);
    // b_castordigis->SetAddress(&CastorDigis);
    b_PFJets->SetAddress(&PFJets);
    if(!isData) b_genParts->SetAddress(&genParts);

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
      if (!evtid->IsData) b_genParts->GetEntry(ievt);

      nb_evt_tot++;
      if(evtid->IsData) hselection_data->Fill(1,1);
      if(!evtid->IsData) hselection_moca_reco->Fill(1,1);
      if(!evtid->IsData) hselection_moca_gen->Fill(1,1);

      if((ievt+1)%5000 == 0) cout<<endl<<"number of events done in file "<<file_nb<<" = "<<ievt+1<<endl;
      if((ievt+1)%5000 == 0) cout<<"total number of events done = "<<nb_evt_tot<<" ("<<100*nb_evt_tot/nb_evt_all_files<<"%)"<<endl;
      if((ievt+1)%5000 == 0 && evtid->IsData) cout<<"number of selected events in data = "<<nb_data_sel<<endl<<endl;
      if((ievt+1)%5000 == 0 && !evtid->IsData) cout<<"number of selected events in mc at reco level = "<<nb_moca_reco_sel<<endl;
      if((ievt+1)%5000 == 0 && !evtid->IsData) cout<<"number of selected events in mc at generated level = "<<nb_moca_gen_sel<<endl<<endl;
      // if((ievt+1)%5000 == 0) cout<<"Run: "<<evtid->Run<<" IsData: "<<evtid->IsData<<" lumiblock: "<<evtid->LumiBlock<<" event: "<<evtid->Evt<<endl;
      
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
      
      if (evtid->IsData) {
	
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

	hTriggerBefore[0]->Fill(L1Trig->fTechDecisionBefore[0]);
	hTriggerAfter[0]->Fill(L1Trig->fTechDecisionAfter[0]);
	hTriggerMask[0]->Fill(L1Trig->fTechMask[0]);
       
	for (int itrig = 1; itrig < 7;itrig++) {
	  hTriggerBefore[itrig]->Fill(L1Trig->fTechDecisionBefore[35+itrig]);
	  hTriggerAfter[itrig]->Fill(L1Trig->fTechDecisionAfter[35+itrig]);
	  hTriggerMask[itrig]->Fill(L1Trig->fTechMask[35+itrig]);
	}

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
	
	bool L1_BSC = L1Trig->fTechDecisionBefore[40] || L1Trig->fTechDecisionBefore[41]; // default value for 900 GeV or 7000 GeV 
	if (cmenergy == 2760) L1_BSC = L1Trig->fPhysDecisionBefore[126];

	bool HF_Activity = true; // default value for 900 GeV or 7000 GeV
	if (cmenergy == 2760) HF_Activity = true; // to be updated with real HF condition... 

	bool HLT_BSC = true; // default value for 900 GeV or 7000 GeV (do we need an HLT here?)
	if (cmenergy == 2760) HLT_BSC = HLTrig->HLTmap["HLT_L1BscMinBiasORBptxPlusANDMinus_v1"];

	bool TriggerSelection = L1_BX && L1_Veto && L1_BSC && HF_Activity && HLT_BSC;
	
	if (TriggerSelection == false) continue;
	hselection_data->Fill(5,1);
	
	//-- filter on at least one good vertex
	
	if(at_least_one_good_vertex == false) continue;
	hselection_data->Fill(6,1);

	data_sel = true;
	nb_data_sel++;
      } 

      //--------------------------------//
      //-- Filter on mc at reco level --//
      //--------------------------------//      
      
      bool moca_reco_sel = false;
      
      if (!evtid->IsData) {
	
	//-- filter on triggers moca
	
	bool L1_BSC = L1Trig->fTechDecisionAfter[40] || L1Trig->fTechDecisionAfter[41]; // default value for 900 GeV or 7000 GeV
        if (cmenergy == 2760) L1_BSC = L1Trig->fTechDecisionBefore[34];
	
	bool HF_Activity = true; // default value for 900 GeV or 7000 GeV
	if (cmenergy == 2760) HF_Activity = true; // to be updated with real HF condition...

	bool TriggerSelection = L1_BSC && HF_Activity;

	if (TriggerSelection == false) continue;
	hselection_moca_reco->Fill(2,1);
	
	//-- filter on at least one good vertex

	if(at_least_one_good_vertex == false) continue;
	hselection_moca_reco->Fill(3,1);	

	moca_reco_sel = true;
      	nb_moca_reco_sel++;
      }
      
      //-------------------------------------//
      //-- Filter on mc at generated level --//
      //-------------------------------------//

      bool moca_gen_sel = false;

      if (!evtid->IsData) {
	    
	bool BSCplus = false;
	bool BSCminus = false;

	bool vertex_ok = false;
	int Ncharged = 0;

	for (int ipart = 0;ipart<genParts->size();ipart++) {
	  
	  MyGenPart particle = (*genParts)[ipart];
	  
	  //--  look for particles in BSC+ & BSC- range
	  
	  if (particle.status != 1) continue;
	  if (particle.Eta() > 3.23 && particle.Eta() < 4.65 && particle.E() > 0. && particle.charge != 0) BSCplus = true;
	  if (particle.Eta() < -3.23 && particle.Eta() > -4.65 && particle.E() > 0. && particle.charge != 0) BSCminus = true;
	  
	  //-- vertex condition
	  
	  if (particle.Eta() > -2.5 && particle.Eta() < 2.5 && particle.E() > 0. && particle.charge != 0) Ncharged++;
	}

	if (Ncharged >= 3) vertex_ok = true;

	//-- filter on BSC AND condition       
	if (!(BSCplus && BSCminus)) continue;
	hselection_moca_gen->Fill(2,1);

	//-- filter on vertex condition
	if(vertex_ok == false) continue; 
	hselection_moca_gen->Fill(3,1);

	moca_gen_sel = true;
	nb_moca_gen_sel++;
      }

      //-----------------------------------------------------------------------------------------------//    
      //-- at this point, event passed following filters:                                            --//
      //-- physics declared, castor invalid data, no scraping, L1 tech trigger, good vertex for data --// 
      //-- L1 tech trigger, good vertex for moca reco level                                          --//
      //-- L1 trigger like condition, vertex like condition for moca generated level                 --//
      //-----------------------------------------------------------------------------------------------//
	
      if(evtid->IsData && !data_sel) continue;
      if(!evtid->IsData && !moca_reco_sel && !moca_gen_sel) continue;
		
      //-- Do stuff after filters
					
      //-- get all the remaining branch entries

      b_castorrechits->GetEntry(ievt);
      b_dijet->GetEntry(ievt);
      b_PFJets->GetEntry(ievt);

      //----------------------------------------------------//      
      //-- only one vertex condition (filter out pile-up) --//
      //--           data_sel & moca_reco_sel             --//
      //----------------------------------------------------//

      if ((evtid->IsData && data_sel) || (!evtid->IsData && moca_reco_sel)) {
	
	//-- filter on exactly one good vertex
	
	if (Vertices->size() != 1) continue;
	if(evtid->IsData) hselection_data->Fill(7,1);
	if(!evtid->IsData) hselection_moca_reco->Fill(4,1); 
	
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
	  if (evtid->IsData)  rechit_energy = rechit.energy*fac_data;  //-- for data, energy is intercalibrated fC
	  if (!evtid->IsData) rechit_energy = rechit.energy*fac_moca;

	  if(rechit_energy < E_cha_reco_min) E_cha_reco_min = rechit_energy;
	  if(rechit_energy > E_cha_reco_max) E_cha_reco_max = rechit_energy;

	  hchannel_time->Fill(rechit.time);
	  if(rechit.time < 15 || rechit.time > 30) hchannel_oot_energy->Fill(rechit_energy);
          //-- if(rechit.time < 15 || rechit.time > 30) continue;

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


	if (dijet->isDiJet) 
	  if ((*PFJets)[dijet->posJet1].pt_cal >= ptcut && (*PFJets)[dijet->posJet2].pt_cal >= ptcut) hDJEflow->Fill(eflow);
								 
      }
      
      //-------------------------------------------//
      //--              moca_gen_sel             --//
      //-------------------------------------------//
      
      if (!evtid->IsData && moca_gen_sel) {
	
	double eflow_gen = 0;
	double eflow_gen_elm = 0;
	double eflow_gen_had = 0;
	
	for (int ipart = 0;ipart<genParts->size();ipart++) {
	  
	  MyGenPart particle = (*genParts)[ipart];
	  
	  if (particle.status != 1) continue;
	  
	  if (!(particle.Eta() < -5.2 && particle.Eta() > -6.6 && particle.E() > 0.)) continue;
	  
	  int part_id = abs(particle.pdgId);
	  if (part_id == 12 || part_id == 14 || part_id == 16) continue; //-- do not take into account neutrinos 
	  if (part_id == 13) continue; //-- do not take into account muons
	  
	  if(particle.E() > E_gen_max) E_gen_max = particle.E();
	  hgen_energy->Fill(particle.E());
          hgen_eta->Fill(particle.Eta());
          hgen_phi->Fill(particle.Phi());
	  eflow_gen+=particle.E();
	  
	  if(part_id == 11 || part_id == 22) {
	    if(particle.E() > E_gen_elm_max) E_gen_elm_max = particle.E();
	    hgen_elm_energy->Fill(particle.E());
	    hgen_elm_eta->Fill(particle.Eta());
	    hgen_elm_phi->Fill(particle.Phi());
	    eflow_gen_elm+=particle.E();
	  } else {
	    if(particle.E() > E_gen_had_max) E_gen_had_max = particle.E();
            hgen_had_energy->Fill(particle.E());
            hgen_had_eta->Fill(particle.Eta());
            hgen_had_phi->Fill(particle.Phi());
            eflow_gen_had+=particle.E();
          }
	}
	
	hEflow_gen->Fill(eflow_gen);
	hEflow_gen_elm->Fill(eflow_gen_elm);
	hEflow_gen_had->Fill(eflow_gen_had);
	
	if(eflow_gen != 0) nb_moca_gen_non_zero_eflow++;
	if(eflow_gen != 0) hEflow_gen_elm_fraction->Fill(eflow_gen_elm/eflow_gen);
	if(eflow_gen != 0) hEflow_gen_had_fraction->Fill(eflow_gen_had/eflow_gen);
      }
      
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

  if(isData) CheckHisto(hselection_data);
  if(!isData) CheckHisto(hselection_moca_reco);
  if(!isData) CheckHisto(hselection_moca_gen);

  //-- timing distribution

  CheckHisto(hchannel_time);

  //-- energy distribution

  CheckHisto(hchannel_energy);
  CheckHisto(hchannel_oot_energy);
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
  CheckHisto(hDJEflow);
  CheckHisto(hEflow_gen);

  //-- generated information

  CheckHisto(hgen_energy);
  CheckHisto(hgen_eta);
  CheckHisto(hgen_phi);

  CheckHisto(hgen_elm_energy);
  CheckHisto(hgen_elm_eta);
  CheckHisto(hgen_elm_phi);
  CheckHisto(hEflow_gen_elm);
  CheckHisto(hEflow_gen_elm_fraction);

  CheckHisto(hgen_had_energy);
  CheckHisto(hgen_had_eta);
  CheckHisto(hgen_had_phi);
  CheckHisto(hEflow_gen_had);
  CheckHisto(hEflow_gen_had_fraction);
  
  //--  trigger information
  
  for (int itrig = 1; itrig < 7;itrig++) {
    CheckHisto(hTriggerBefore[itrig]);
    CheckHisto(hTriggerAfter[itrig]);
    CheckHisto(hTriggerMask[itrig]);
  }
  
  //-------------------------------------//
  //-- write histo to output root file --//
  //-------------------------------------//
  
  cout<<endl<<"total number of events: "<<nb_evt_tot<<" from "<<file_nb<<" file(s)"<<endl;
  cout<<nb_data_sel<<" selected events in data"<<endl;
  cout<<nb_moca_reco_sel<<" selected events in mc at reco level"<<endl;
  cout<<nb_moca_gen_sel<<" selected events in mc at generated level"<<endl<<endl;

  if(!isData) {

    cout<<endl<<"E channel reco min: "<<E_cha_reco_min<<endl;
    cout<<"E channel reco max: "<<E_cha_reco_max<<endl;

    cout<<endl<<"E module reco min: "<<E_mod_reco_min<<endl;
    cout<<"E module reco max: "<<E_mod_reco_max<<endl;

    cout<<endl<<"E sector reco min: "<<E_sec_reco_min<<endl;
    cout<<"E sector reco max: "<<E_sec_reco_max<<endl;

    cout<<endl<<"E gen max: "<<E_gen_max<<endl;
    cout<<"E gen elm max: "<<E_gen_elm_max<<endl;
    cout<<"E gen had max: "<<E_gen_had_max<<endl<<endl;
  }

  if(isData) {
    cout<<endl<<"E channel reco min: "<<E_cha_reco_min<<endl;
    cout<<"E channel reco max: "<<E_cha_reco_max<<endl;

    cout<<endl<<"E module reco min: "<<E_mod_reco_min<<endl;
    cout<<"E module reco max: "<<E_mod_reco_max<<endl;

    cout<<endl<<"E sector reco min: "<<E_sec_reco_min<<endl;
    cout<<"E sector reco max: "<<E_sec_reco_max<<endl<<endl;
  }

  Char_t output_filename[200];
  const char* part = filename.Data();
  sprintf(output_filename,"../Result/output_profile_%s",part);
  TFile* foutput = new TFile(output_filename,"RECREATE");
  foutput->cd();

  //--  Selection
	
  hselection_data->Write();
  hselection_moca_reco->Write();
  hselection_moca_gen->Write();

  //-- timing distribution

  hchannel_time->Write();

  //-- energy distribution

  hchannel_energy->Write();
  hchannel_oot_energy->Write();
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
  hDJEflow->Write();
  hEflow_gen->Write();

  //-- generated information

  hgen_energy->Write();
  hgen_eta->Write();
  hgen_phi->Write();

  hgen_elm_energy->Write();
  hgen_elm_eta->Write();
  hgen_elm_phi->Write();
  hEflow_gen_elm->Write();
  hEflow_gen_elm_fraction->Write();

  hgen_had_energy->Write();
  hgen_had_eta->Write();
  hgen_had_phi->Write();
  hEflow_gen_had->Write();
  hEflow_gen_had_fraction->Write();

  //--  trigger information

  for (int itrig = 0; itrig < 7;itrig++) {
    hTriggerBefore[itrig]->Write();
    hTriggerAfter[itrig]->Write();
    hTriggerMask[itrig]->Write();
  }
	
  foutput->Close();
  cout<<"file "<<output_filename<<" created"<<endl;

  //-----------------------------------//
  //-- compute some means and sigmas --//
  //-----------------------------------//

  if(isData) {
    cout<<endl<<"data at "<<cmenergy<<" GeV"<<endl;
    cout<<"mean E flow MB: "<<hMBEflow->GetMean()<<" GeV"<<endl;
    cout<<"mean E flow dijet: "<<hDJEflow->GetMean()<<" GeV"<<endl<<endl;
  }

  if(!isData) {
    cout<<endl<<"moca at "<<cmenergy<<" GeV"<<endl;
    cout<<"mean E flow MB: "<<hMBEflow->GetMean()<<" GeV"<<endl;
    cout<<"mean E flow dijet: "<<hDJEflow->GetMean()<<" GeV"<<endl;
    cout<<"mean E flow generated: "<<hEflow_gen->GetMean()<<" GeV"<<endl<<endl;
  }

  cout<<"mean E flow MB from module mean = ";
  double E_flow_MB_module_check = 0;
  for (int imod = 0; imod < 5; imod++) {
    E_flow_MB_module_check+=MB_mean_module_sector_used[imod]*MB_mean_module[imod];
    cout<<MB_mean_module_sector_used[imod]<<"*"<<MB_mean_module[imod];
    if(imod < 4) cout<<"+";
    if(imod == 4) cout<<endl<<"mean E flow MB from module mean = "<<E_flow_MB_module_check<<endl<<endl;
  }

  cout<<"mean E flow MB from sector mean = ";
  double E_flow_MB_sector_check = 0;
  for (int isec = 0; isec < 16; isec++) {
    E_flow_MB_sector_check+=MB_mean_sector_module_used[isec]*MB_mean_sector[isec];
    cout<<MB_mean_sector_module_used[isec]<<"*"<<MB_mean_sector[isec];
    if(isec < 15) cout<<"+";
    if(isec == 15) cout<<endl<<"mean E flow MB from sector mean = "<<E_flow_MB_sector_check<<endl<<endl;
  }

  cout<<endl<<"spread of intercalibrated factors"<<endl;
  
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

void ProfileAnalyzer::CheckHisto(TH1D* h) {

  Int_t NbinX = h->GetNbinsX();
  
  if(h->GetBinContent(0) != 0) cout<<h->GetTitle()<<" has underflow of "<<h->GetBinContent(0)<<" entries"<<endl;
  if(h->GetBinContent(NbinX+1) != 0) cout<<h->GetTitle()<<" has overflow of "<<h->GetBinContent(NbinX+1)<<" entries"<<endl;
  
  return;
}

TH1D* ProfileAnalyzer::MakeHisto(TString name, TString title, TString xleg, TString yleg, int nbin, double bmin, double bmax) {


  TH1D* h = new TH1D(name,title,nbin,bmin,bmax);

  h->GetXaxis()->SetTitle(xleg);
  h->GetYaxis()->SetTitle(yleg);

  h->SetMinimum(0);
  h->Sumw2();

  cout<<"create histo: "<<h->GetName()<<" with title: "<<h->GetTitle()<<endl;

  return h;
}

TH1D* ProfileAnalyzer::MakeHisto(int id, TString name, TString title, TString xleg, TString yleg, int nbin, double bmin, double bmax) {

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

TH1D* ProfileAnalyzer::MakeHisto(int isec, int imod, TString name, TString title, TString xleg, TString yleg, int nbin, double bmin, double bmax) {

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
