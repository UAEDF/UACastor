#include "EflowAnalyzer.h"

//-- standard root includes
#include <TROOT.h>
#include <TF1.h>
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
#include <TRandom3.h>

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
#include "../src/MyVertex.h"
#include "../src/MyBeamSpot.h"
#include "../src/MyHLTrig.h"
#include "../src/MyL1Trig.h"
#include "../src/MyJet.h"
#include "../src/MyDiJet.h"
#include "../src/MyTrackJet.h"
#include "../src/MyCaloTower.h"
#include "../src/MyGenPart.h"
#include "../src/MyGenJet.h"

#define verbose 1

#define applyweight 1

EflowAnalyzer::EflowAnalyzer() { }

EflowAnalyzer::~EflowAnalyzer() { }

void EflowAnalyzer::Loop(TString inputdir, TObjArray* filelist, TString type, double cmenergy, bool dosubsample) {

  bool isData = false;
  bool isPythia6Z2 = false;

  if(strcmp(type,"data") == 0) isData = true;
  if(strcmp(type,"PYTHIA6Z2") == 0) isPythia6Z2 = true;

  //-----------------------------//
  //-- noise per sector in GeV --//
  //-----------------------------//
  
  double noise_sector_cut = 0.3644;
  double ptcut = 10;

  cout<<"noise sector cut = "<<noise_sector_cut<<endl;
  cout<<"pt cut = "<<ptcut<<endl;

  using namespace std;

  double fac_data = 0.0150;
  double fac_moca = 0.9375;  //-- 0.015/0.016
  
  int file_nb = 0;
  int nb_evt_tot_now = 0;
  double nb_evt_tot = 0;
  int nb_file_max = -1; 

  double nb_data_sel = 0;
  double nb_moca_reco_sel = 0;
  double nb_moca_gen_detcut_sel = 0;
  double nb_moca_gen_xicut_sel = 0;

  double nb_moca_tree = 0;
  double nb_moca_reco_sel_gen_detcut_sel = 0;
  double nb_moca_reco_sel_gen_xicut_sel = 0;
  double nb_moca_gen_detcut_sel_xicut_sel = 0;

  double E_gen_max = -100;

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

  TH1D *hselection_data = new TH1D("hselection_data","Event Selection Data",10,0.5,10.5); 
  TH1D *hselection_moca_reco = new TH1D("hselection_moca_reco","Event Selection MC reco",5,0.5,5.5);
  TH1D *hselection_moca_gen_detcut = new TH1D("hselection_moca_gen_detcut","Event Selection MC gen (det cut)",4,0.5,4.5);
  TH1D *hselection_moca_gen_xicut = new TH1D("hselection_moca_gen_xicut","Event Selection MC gen (xi cut)",2,0.5,2.5);

  //-- vertex

  TH1D* hVx = MakeHisto("hVx","vertex x","vx [cm]","N evts",20,-5,5);
  TH1D* hVy = MakeHisto("hVy","vertex y","vy [cm]","N evts",20,-5,5);
  TH1D* hVz = MakeHisto("hVz","vertex z","vz [cm]","N evts",100,-50,50);
  TH1D* hVrho = MakeHisto("hVrho","vertex rho","rho [cm]","N evts",20,0,2);
  TH1D* hVndof = MakeHisto("hVndof","vertex ndof","ndof","N evts",20,0,20);

  //-- energy distribution

  TH1D *hMBmodule[5];
  for (int imod = 0; imod < 5;imod++) hMBmodule[imod] = MakeHisto(imod,"hMBmodule","MB energy distibution in module","E [GeV]","N evts",228,-40,1100);
 
  TH1D *hMBmodule_sector_used[5];
  for (int imod = 0; imod < 5;imod++) hMBmodule_sector_used[imod] = MakeHisto(imod,"hMBmodule_sector_used","MB number of sectors used in module","sector","N evts",16,0.5,16.5);
 
  TH1D *hMBsector[16];
  for (int isec = 0; isec < 16;isec++) hMBsector[isec] = MakeHisto(isec,"hMBsector","MB energy distibution in sector","E [GeV]","N evts",264,-40,1280);

  TH1D *hMBsector_module_used[16];
  for (int isec = 0; isec < 16;isec++) hMBsector_module_used[isec] = MakeHisto(isec,"hMBsector_module_used","MB number of modules used in sector","module","N evts",5,0.5,5.5);

  TH1D *hMBchannel[16][5];

  for (int imod = 0; imod < 5;imod++) {
    for (int isec = 0; isec < 16;isec++) {
      hMBchannel[isec][imod] = MakeHisto(isec,imod,"hMBchannel","MB energy distibution in channel","E [GeV]","N evts",755,-5,750);
    }
  }

  TH1D *hMBchannel_mean = MakeHisto("hMBchannel_mean","MB mean energy per channel","channel","E [GeV]",80,0.5,80.5);

  //-- z profile and phi profile

  TH1D *hMBzprofile_mean = MakeHisto("hMBzprofile_mean","MB z profile averaged over all sectors","module","E [GeV]",5,0.5,5.5);
  TH1D *hMBphiprofile_mean = MakeHisto("hMBphiprofile_mean","MB phi profile averaged over all modules","sector","E [GeV]",16,0.5,16.5);

  //-- eflow

  Char_t hlabel[200],hname[50];

  Int_t nbin_eflow, bin_eflow_min, bin_eflow_max;
  Int_t nbin_en, bin_en_min, bin_en_max;

  if(cmenergy == 900) {

    nbin_eflow = 183;
    bin_eflow_min = -15;
    bin_eflow_max = 900;

    nbin_en = 300;
    bin_en_min = 0;
    bin_en_max = 1500;

  } else if (cmenergy == 2760) {

    nbin_eflow = 361;
    bin_eflow_min = -5;
    bin_eflow_max = 1800; 

    nbin_en = 300;
    bin_en_min = 0;
    bin_en_max = 1500;

  } else if (cmenergy == 7000) {

    nbin_eflow = 753;  
    bin_eflow_min = -15;
    bin_eflow_max = 3750;

    nbin_en = 300;
    bin_en_min = 0;
    bin_en_max = 1500;

  }
  
  TH1D *hMBEflow = MakeHisto("hMBEflow","MB energy flow","Eflow [GeV]","N evts",nbin_eflow,bin_eflow_min,bin_eflow_max); 
  TH1D *hAllPtEflow = MakeHisto("hAllPtEflow","energy flow for track jet","Eflow [GeV]","N evts",nbin_eflow,bin_eflow_min,bin_eflow_max);

  int nptbin = 7;
  double ptbinning[8] = {1,2,3,5,7.5,10,15,25};

  TH1D *hPtEflow[nptbin];
  
  for (int ipt = 0; ipt < nptbin; ipt++) {
    sprintf(hlabel,"energy flow for track jet with %6.2f < pt < %6.2f",ptbinning[ipt],ptbinning[ipt+1]);
    sprintf(hname,"hPtEflow_%d",ipt+1);
    hPtEflow[ipt] = MakeHisto(hname,hlabel,"Eflow [GeV]","N evts",nbin_eflow,bin_eflow_min,bin_eflow_max);
  }

  TH1D *hPtEflowRatio = new TH1D("hPtEflowRatio","MB energy flow ratio",nptbin,ptbinning);
  SetAxisName(hPtEflowRatio,"pt track jet","ratio");
  
  TH1D *hMBEflow_gen = MakeHisto("hMBEflow_gen","gen energy flow","Eflow [GeV]","N evts",nbin_eflow,bin_eflow_min,bin_eflow_max);

  //-- trackjet variable

  TH1D *hNTrackJet = MakeHisto("hNTrackJet","N Track Jet","N trackjets","N events",50,0,50);
  TH1D *hTrackJetEta = MakeHisto("hTrackJetEta","Track Jet Eta","eta","N trackjets",50,-2.5,2.5);
  TH1D *hTrackJetPt = MakeHisto("hTrackJetPt","Track Jet Pt","pt","N trackjets",60,0,30);
  TH1D *hTrackJetPhi = MakeHisto("hTrackJetPhi","Track Jet Phi","phi","N trackjets",100,-M_PI,M_PI);

  //-- generated information

  TH1D *hgen_energy = MakeHisto("hgen_energy","generated energy","energy","Nparticules",nbin_en,bin_en_min,bin_en_max);
  TH1D *hgen_eta  = MakeHisto("hgen_eta","generated eta","eta","Nparticules",56,-6.6,-5.2);
  TH1D *hgen_phi = MakeHisto("hgen_phi","generated phi","phi","Nparticules",100,-M_PI,M_PI);
  hgen_phi->SetMinimum(0);

  //-- weight and non-linearity factor

  TH2D *hNLfactor = MakeHisto("hNLfactor","Non linearity factor","E flow [GeV]","non linearity factor",100,0,1500,100,0,1);
  TH2D *hWeightEflow = MakeHisto("hWeightEflow","Weight Eflow","E flow [GeV]","weight",100,0,1500,100,0,10); 
  TH2D *hWeightPtTrackJet = MakeHisto("hWeightPtTrackJet","Weight Pt Track Jet","Pt Track Jet [GeV]","weight",25,0,25,100,0,10);

  //-- run number and lumi section

  int NRun900 = 3;
  Float_t ListRun900[4]={134721,134722,134725,134726};

  TH1D *hRun900 = MakeHisto("hRun900","Run Number 900 GeV (all events)","run","N events",NRun900,ListRun900);
  TH1D *hLS900_134721 = MakeHisto("hLS900_134721","Lumi Section 900 GeV Run 134721 (all events)","LS","N events",800,550,1350);
  TH1D *hLS900_134725 = MakeHisto("hLS900_134725","Lumi Section 900 GeV Run 134725 (all events)","LS","N events",1150,200,1350);
	
  TH1D *hRun900_sel = MakeHisto("hRun900_sel","Run Number 900 GeV (selected events)","run","N events",NRun900,ListRun900);
  TH1D *hLS900_134721_sel = MakeHisto("hLS900_134721_sel","Lumi Section 900 GeV Run 134721 (selected events)","LS","N events",800,550,1350);
  TH1D *hLS900_134725_sel = MakeHisto("hLS900_134725_sel","Lumi Section 900 GeV Run 134725 (selected events)","LS","N events",1150,200,1350);

  TH1D *hRun900_stability = MakeHisto("hRun900_stability","Run Number 900 GeV (stability)","run","fraction",NRun900,ListRun900);
  TH1D *hLS900_134721_stability = MakeHisto("hLS900_134721_stability","Lumi Section 900 GeV Run 134721 (stability)","LS","fraction",800,550,1350);
  TH1D *hLS900_134725_stability = MakeHisto("hLS900_134725_stability","Lumi Section 900 GeV Run 134725 (stability)","LS","fraction",1150,200,1350);

  hRun900->SetNdivisions(7);
  hRun900_sel->SetNdivisions(7);
  hRun900_stability->SetNdivisions(7);

  //-- eflow as function of trackjet eta

  int netabin = 8;
  double etabinning[9] = {-2,-1.5,-1,-0.5,0,0.5,1,1.5,2};

  int nptmin = 6;
  double ptmin[6] = {0.3,1,2.5,5,10,15};

  TH1D *hEta_Eflow[netabin][nptmin];
  TH1D* hEta_Eta[netabin][nptmin];
  TH1D* hEta_Pt[netabin][nptmin];

  for (int ieta = 0; ieta < netabin; ieta++) {
    
    for (int ipt = 0; ipt < nptmin; ipt++) {

      sprintf(hlabel,"energy flow for track jet with %6.2f < eta < %6.2f, pt > %6.2f GeV",etabinning[ieta],etabinning[ieta+1],ptmin[ipt]);
      sprintf(hname,"hEta_Eflow_eta_%d_pt_%d",ieta+1,ipt+1);
      hEta_Eflow[ieta][ipt] = MakeHisto(hname,hlabel,"Eflow [GeV]","N evts",nbin_eflow,bin_eflow_min,bin_eflow_max);

      sprintf(hlabel,"eta for track jet with %6.2f < eta < %6.2f, pt > %6.2f GeV",etabinning[ieta],etabinning[ieta+1],ptmin[ipt]);
      sprintf(hname,"hEta_Eta_eta_%d_pt_%d",ieta+1,ipt+1);
      hEta_Eta[ieta][ipt] = MakeHisto(hname,hlabel,"eta","N trackjets",50,etabinning[ieta],etabinning[ieta+1]);

      sprintf(hlabel,"pt for track jet with %6.2f < eta < %6.2f, pt > %6.2f GeV",etabinning[ieta],etabinning[ieta+1],ptmin[ipt]);
      sprintf(hname,"hEta_Pt_eta_%d_pt_%d",ieta+1,ipt+1);
      hEta_Pt[ieta][ipt] = MakeHisto(hname,hlabel,"pt","N trackjets",60,0,30);
    }
  }
  
  TH1D *hEta_EflowRatio[nptmin];
  TH1D *hEta_Ptmean[nptmin];

  for (int ipt = 0; ipt < nptmin; ipt++) {
    
    sprintf(hlabel,"energy flow ratio for track jet with pt > %6.2f GeV",ptmin[ipt]);
    sprintf(hname,"hEta_EflowRatio_pt_%d",ipt+1);
    hEta_EflowRatio[ipt] = new TH1D(hname,hlabel,netabin,etabinning);
    SetAxisName(hEta_EflowRatio[ipt],"eta track jet","ratio");

    sprintf(hlabel,"mean pt for track jet with pt > %6.2f GeV",ptmin[ipt]);
    sprintf(hname,"hEta_Ptmean_pt_%d",ipt+1);
    hEta_Ptmean[ipt] = new TH1D(hname,hlabel,netabin,etabinning);
    SetAxisName(hEta_Ptmean[ipt],"eta track jet","mean pt");
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
      cout<<"Error in EflowAnalyzer: could not open file "<<temp_itfile->GetString()<<endl;
      continue;
    }
    
    TTree *tree; 
    if(dosubsample) {
      tree = new TTree("CastorTree","");
      file->GetObject("castortree/CastorTree",tree);
    }

    else {
      tree = new TTree("CastorTreeSubSample","");
      file->GetObject("CastorTree",tree);
    }

    Nfile_all++;
    nb_evt_all_files+=tree->GetEntriesFast();
    file->Close();
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
      cout<<"Error in EflowAnalyzer: could not open file "<<itfile->GetString()<<endl; 
      continue; 
    } 
    
    //-- Get tree from file
    
    TTree *tree;
    if(dosubsample) {
      tree = new TTree("CastorTree","");
      file->GetObject("castortree/CastorTree",tree);
    }

    else {
      tree = new TTree("CastorTreeSubSample","");
      file->GetObject("CastorTree",tree);
    }

    //-- define objects
    
    MyEvtId *evtid = NULL;
    MyHLTrig *HLTrig = NULL;
    MyL1Trig *L1Trig = NULL;

    vector<MyVertex> *Vertices = NULL;
    vector<MyBeamSpot> *BeamSpots = NULL;

    vector<MyCastorRecHit> *CastorRecHits = NULL;
    vector<MyCastorTower> *CastorTowers = NULL;
    vector<MyCastorJet> *CastorJets = NULL;

    vector<MyJet> *PFJets = NULL;
    vector<MyJet> *CaloJets = NULL;
    vector<MyTrackJet> *TrackJets = NULL;

    MyDiJet *pfDiJets = NULL;
    MyDiJet *caloDiJets = NULL;

    std::vector<MyCaloTower> *CaloTowers = NULL;

    vector<MyGenPart> *GenParts = NULL;
    vector<MyGenJet> *GenJets = NULL;
    vector<MyGenJet> *ChargedGenJets = NULL;
        
    //-- define branches 

    TBranch *b_evtid = tree->GetBranch("EvtId");
    TBranch *b_HLTrig = tree->GetBranch("HLTrig");
    TBranch *b_L1Trig = tree->GetBranch("L1Trig");

    TBranch *b_Vertices = tree->GetBranch("primaryVertex");
    TBranch *b_BeamSpots = tree->GetBranch("beamSpot");

    TBranch *b_CastorRecHits = tree->GetBranch("castorRecHit");
    TBranch *b_CastorTowers = tree->GetBranch("castorTower");
    TBranch *b_CastorJets = tree->GetBranch("castorJet");

    TBranch *b_PFJets = tree->GetBranch("pfJet");
    TBranch *b_CaloJets = tree->GetBranch("caloJet");
    TBranch *b_TrackJets = tree->GetBranch("trackJet");

    TBranch *b_pfDiJet = tree->GetBranch("pfDiJet");
    TBranch *b_caloDiJet = tree->GetBranch("caloDiJet");

    TBranch *b_CaloTowers = tree->GetBranch("caloTower");

    TBranch *b_GenParts; 
    if(!isData) b_GenParts = tree->GetBranch("GenPart");
    TBranch *b_GenJets;
    if(!isData) b_GenJets = tree->GetBranch("GenJet"); 
    TBranch *b_ChargedGenJets;
    if(!isData) b_ChargedGenJets = tree->GetBranch("ChargedGenJet");

    b_evtid->SetAddress(&evtid);
    b_HLTrig->SetAddress(&HLTrig);
    b_L1Trig->SetAddress(&L1Trig);

    b_Vertices->SetAddress(&Vertices);
    b_BeamSpots->SetAddress(&BeamSpots);

    b_CastorRecHits->SetAddress(&CastorRecHits);
    b_CastorTowers->SetAddress(&CastorTowers);
    b_CastorJets->SetAddress(&CastorJets);

    b_PFJets->SetAddress(&PFJets);
    b_CaloJets->SetAddress(&CaloJets);
    b_TrackJets->SetAddress(&TrackJets);

    b_pfDiJet->SetAddress(&pfDiJets);
    b_caloDiJet->SetAddress(&caloDiJets);

    b_CaloTowers->SetAddress(&CaloTowers);

    if(!isData) b_GenParts->SetAddress(&GenParts);
    if(!isData) b_GenJets->SetAddress(&GenJets);
    if(!isData) b_ChargedGenJets->SetAddress(&ChargedGenJets);

    int Nevents = tree->GetEntriesFast();
    cout <<"number of events in file "<<file_nb<<" = "<<Nevents<<endl<<endl;

    TFile* file_eflow;
    TTree *tree_eflow;
    TString string_energy;
    if(cmenergy == 900) string_energy = "900GeV";
    if(cmenergy == 2760) string_energy = "2760GeV";
    if(cmenergy == 7000) string_energy = "7TeV";
    int energy = cmenergy;
    
    TString filename_eflow = "../Result/EflowSubsample/" + string_energy + "/" + type + "/CastorTree_eflow_subsample_" + TString::Format("%d",energy) + "_" + type + "_" + TString::Format("%d",file_nb) + ".root";
    if(dosubsample) file_eflow = new TFile(filename_eflow,"recreate");
    if(dosubsample) tree_eflow = tree->CloneTree(0);

    //--------------------------//    
    //-- Loop over the events --//
    //--------------------------//
    
    for (int ievt=0;ievt<Nevents;ievt++) {

      b_evtid->GetEntry(ievt);
      b_HLTrig->GetEntry(ievt);
      b_L1Trig->GetEntry(ievt);

      b_Vertices->GetEntry(ievt);
      b_BeamSpots->GetEntry(ievt);

      b_CastorRecHits->GetEntry(ievt);
      b_CastorTowers->GetEntry(ievt);
      b_CastorJets->GetEntry(ievt);

      b_PFJets->GetEntry(ievt);
      b_CaloJets->GetEntry(ievt);
      b_TrackJets->GetEntry(ievt);

      b_pfDiJet->GetEntry(ievt);
      b_caloDiJet->GetEntry(ievt);

      b_CaloTowers->GetEntry(ievt);

      if(!isData) b_GenParts->GetEntry(ievt);
      if(!isData) b_GenJets->GetEntry(ievt);
      if(!isData) b_ChargedGenJets->GetEntry(ievt);

      //-- compute weight to apply to Pythia6 Z2

      double weight_eflow = 1;
      double weight_jetpt = 1;
      double weight = 1;

      if(isPythia6Z2 && applyweight) {
	
	//-- reweighting: compute eflow gen
	
	double eflow_gen = 0;
	
	for (int ipart = 0;ipart<GenParts->size();ipart++) {
	  
	  MyGenPart particle = (*GenParts)[ipart];
	  
	  if (particle.status != 1) continue;
	  
	  if (!(particle.Eta() < -5.2 && particle.Eta() > -6.6 && particle.E() > 0.)) continue;
	  
	  int part_id = abs(particle.pdgId);
	  if (part_id == 12 || part_id == 14 || part_id == 16) continue; //-- do not take into account neutrinos
	  if (part_id == 13) continue; //-- do not take into account muons
	  
	  eflow_gen+=particle.E();
	}
	
	//-- reweighting: look for leading charged gen jet
	
	int posLeadingChargedGenJet = GetPosLeadingGenJet(*ChargedGenJets,2.,1.);
	
	//-- reweighting: compute E flow MC weight

	double nonlinearity = GetNonLinearityFactor(eflow_gen,cmenergy);
	double eflow_gen_scaled = eflow_gen * nonlinearity;
	
	weight_eflow = GetEflowMCWeight(eflow_gen_scaled,cmenergy); 
	
	hNLfactor->Fill(eflow_gen,nonlinearity);
	hWeightEflow->Fill(eflow_gen_scaled,weight_eflow);

	//-- reweighting: compute jet pt MC weight
	
	if (posLeadingChargedGenJet != -1) {
	  double pt_leading = (*ChargedGenJets)[posLeadingChargedGenJet].Pt();
	  
	  if (pt_leading > 1. && pt_leading < 25.) {
	    weight_jetpt = GetTrackJetMCWeight(pt_leading,cmenergy);
	    hWeightPtTrackJet->Fill(pt_leading,weight_jetpt);	      
	  }
	}
	
	//-- reweighting: global weight
	
	weight = weight_eflow*weight_jetpt;
      } 

      nb_evt_tot+=weight;
      nb_evt_tot_now+=1;
      if(isData) hselection_data->Fill(1,weight);
      if(!isData) hselection_moca_reco->Fill(1,weight);
      if(!isData) hselection_moca_gen_detcut->Fill(1,weight);
      if(!isData) hselection_moca_gen_xicut->Fill(1,weight);

      if((ievt+1)%5000 == 0) cout<<endl<<"number of events done in file "<<file_nb<<" = "<<ievt+1<<endl;
      if((ievt+1)%5000 == 0) cout<<"total number of events done = "<<nb_evt_tot<<" ("<<100*nb_evt_tot/nb_evt_all_files<<"%)"<<endl;
      if((ievt+1)%5000 == 0 && isData) cout<<"number of selected events in data = "<<nb_data_sel<<endl<<endl;
      if((ievt+1)%5000 == 0 && !isData) cout<<"number of selected events in mc at reco level = "<<nb_moca_reco_sel<<endl;
      if((ievt+1)%5000 == 0 && !isData) cout<<"number of selected events in mc at generated level (det cut) = "<<nb_moca_gen_detcut_sel<<endl;
      if((ievt+1)%5000 == 0 && !isData) cout<<"number of selected events in mc at generated level (xi cut) = "<<nb_moca_gen_xicut_sel<<endl<<endl;

      //-- run number and lumi section

      if (isData && cmenergy == 900) {
	hRun900->Fill(evtid->Run,weight);
	if(evtid->Run==134721) hLS900_134721->Fill(evtid->LumiBlock,weight);
	if(evtid->Run==134725) hLS900_134725->Fill(evtid->LumiBlock,weight);
      }

      //-- Get vertex information
      
      bool at_least_one_gv = false;
      
      for (unsigned int iVert=0;iVert<Vertices->size();iVert++) {
	MyVertex vertex = (*Vertices)[iVert];
	if(!vertex.fake && vertex.ndof >= 4 && TMath::Abs(vertex.z) <= 15 && vertex.rho <=2) at_least_one_gv = true;
      }
      
      bool exactly_one_gv = false;
      if(Vertices->size() == 1) exactly_one_gv = true;

      //----------------------//   
      //--  Filter on data  --//
      //----------------------//

      bool data_sel = false;
      
      if (isData) {

       	//-- filter on physics declared bit

	bool PhysDecl = HLTrig->HLTmap["physDeclpath"];
	if(evtid->Run==134725) PhysDecl = true;

	//-- filter on castor invalid data

	bool CASTORvalid = HLTrig->HLTmap["castorInvalidDataFilterpath"];

	//-- filter out scraping events

	bool noscraping = HLTrig->HLTmap["noscrapingpath"];

	//-- filter on L1 trigger data
	
	bool L1_BX = L1Trig->fTechDecisionBefore[0];

	bool L1_Veto = !L1Trig->fTechDecisionBefore[36] && !L1Trig->fTechDecisionBefore[37] && !L1Trig->fTechDecisionBefore[38] && !L1Trig->fTechDecisionBefore[39];
	
	bool L1_BSC = L1Trig->fTechDecisionBefore[40] || L1Trig->fTechDecisionBefore[41]; // value for 900 GeV and 7 TeV 
	if (cmenergy == 2760) L1_BSC = L1Trig->fPhysDecisionBefore[126];  // value for 2.76 TeV
	
	bool L1_Selection = L1_BX && L1_Veto && L1_BSC;

	//-- filter on HLT trigger data

        bool HLT_Selection = false;  
	if (cmenergy == 900) HLT_Selection = HLTrig->HLTmap["HLT_L1_BscMinBiasOR_BptxPlusORMinus"];     //-- prescale = 1
        if (cmenergy == 2760) HLT_Selection = HLTrig->HLTmap["HLT_L1BscMinBiasORBptxPlusANDMinus_v1"];  //-- prescale = 1
	if (cmenergy == 7000) HLT_Selection = HLTrig->HLTmap["HLT_L1_BscMinBiasOR_BptxPlusORMinus"];    //-- prescale = 40

	//-- filter on HF Activity 

	bool HF_Activity = false;
	
	bool HFplus = false;
	bool HFminus = false;
	  
	for (int itow=0;itow<CaloTowers->size();itow++) {
	  MyCaloTower mytow = (*CaloTowers)[itow];
	  if (mytow.hasHF && mytow.Energy() > 4. && mytow.zside == 1 && mytow.Eta() > 3.23 && mytow.Eta() < 4.65) HFplus = true;
	  if (mytow.hasHF && mytow.Energy() > 4. && mytow.zside == -1 && mytow.Eta() < -3.23 && mytow.Eta() > -4.65) HFminus = true;
	}
	  
	if(HFplus && HFminus) HF_Activity = true;

	//-- filter on CASTOR activity (5 modules - 4 sigmas)

        bool CASTOR_Activity = false;

        double rechit_energy = 0;

        double sector_energy[16];
        for (int isec = 0; isec < 16;isec++) sector_energy[isec] = 0;
      
        for (unsigned int irec = 0;irec < CastorRecHits->size();irec++) {
        
          MyCastorRecHit rechit = (*CastorRecHits)[irec];
        
          bool used_cha = false;
          if(rechit.cha != 5 && rechit.cha != 6 && rechit.cha <= 80) used_cha = true; //-- for data 15,35,81,5,6
          if(used_cha == false) continue;
	  
          rechit_energy = rechit.energy*fac_data;  //-- for data, energy is intercalibrated fC
          
          if(rechit.cha <= 80) sector_energy[rechit.sec-1]+=rechit_energy; //-- first 5 modules        
        }

        //-- at least 1 sector above 4 times noise threshold 

        for (int isec = 0; isec < 16;isec++) {
          if(sector_energy[isec] > 4.*noise_sector_cut) CASTOR_Activity = true;
        }
		    	      
	if (PhysDecl) hselection_data->Fill(2,weight);	

	if (PhysDecl && CASTORvalid) hselection_data->Fill(3,weight);

	if (PhysDecl && CASTORvalid && noscraping) hselection_data->Fill(4,weight);
	
	if (PhysDecl && CASTORvalid && noscraping && L1_Selection) hselection_data->Fill(5,weight);

	if (PhysDecl && CASTORvalid && noscraping && L1_Selection && HLT_Selection) hselection_data->Fill(6,weight);
	
	if (PhysDecl && CASTORvalid && noscraping && L1_Selection && HLT_Selection && at_least_one_gv) hselection_data->Fill(7,weight);
	
	if (PhysDecl && CASTORvalid && noscraping && L1_Selection && HLT_Selection && at_least_one_gv && exactly_one_gv) hselection_data->Fill(8,weight);
	
	if (PhysDecl && CASTORvalid && noscraping && L1_Selection && HLT_Selection && at_least_one_gv && exactly_one_gv && HF_Activity) hselection_data->Fill(9,weight);
	
	if (PhysDecl && CASTORvalid && noscraping && L1_Selection && HLT_Selection && at_least_one_gv && exactly_one_gv && HF_Activity && CASTOR_Activity) {
	  hselection_data->Fill(10,weight);
	  data_sel = true;
	  nb_data_sel+=weight;
          if(dosubsample) tree_eflow->Fill();
	}		      
		    
      } //-- end loop on data

      //---------------------------//
      //-- Filter on montecarlo  --//
      //---------------------------//      
      
      bool moca_reco_sel = false;
      bool moca_gen_detcut_sel = false;
      bool moca_gen_xicut_sel = false;

      if (!isData) {

	//--------------------------------//
	//-- Filter on mc at reco level --//
	//--------------------------------//

	//-- filter on HF Activity 

        bool HF_Activity = false;
        
        bool HFplus = false;
        bool HFminus = false;
          
        for (int itow=0;itow<CaloTowers->size();itow++) {
          MyCaloTower mytow = (*CaloTowers)[itow];
          if (mytow.hasHF && mytow.Energy() > 4. && mytow.zside == 1 && mytow.Eta() > 3.23 && mytow.Eta() < 4.65) HFplus = true;
          if (mytow.hasHF && mytow.Energy() > 4. && mytow.zside == -1 && mytow.Eta() < -3.23 && mytow.Eta() > -4.65) HFminus = true;
        }
          
        if(HFplus && HFminus) HF_Activity = true;

	//-- filter on CASTOR activity (5 modules - 4 sigmas)
	
        bool CASTOR_Activity = false;
	
        double rechit_energy = 0;
	
        double sector_energy[16];
        for (int isec = 0; isec < 16;isec++) sector_energy[isec] = 0;
	
        for (unsigned int irec = 0;irec < CastorRecHits->size();irec++) {
	  
          MyCastorRecHit rechit = (*CastorRecHits)[irec];
	  
          bool used_cha = false;
          if(rechit.cha != 5 && rechit.cha != 6 && rechit.cha <= 80) used_cha = true; //-- for data 15,35,81,5,6
          if(used_cha == false) continue;
	  
          rechit_energy = rechit.energy*fac_moca;

          if(rechit.cha <= 80) sector_energy[rechit.sec-1]+=rechit_energy; //-- first 5 modules        
        }
	
        //-- at least 1 sector above 4 times noise threshold 
	
        for (int isec = 0; isec < 16; isec++) {
          if(sector_energy[isec] > 4.*noise_sector_cut) CASTOR_Activity = true;
        }

        if (at_least_one_gv) hselection_moca_reco->Fill(2,weight);
	
	if (at_least_one_gv && exactly_one_gv) hselection_moca_reco->Fill(3,weight);

	if (at_least_one_gv && exactly_one_gv && HF_Activity) hselection_moca_reco->Fill(4,weight);
	      
	if (at_least_one_gv && exactly_one_gv && HF_Activity && CASTOR_Activity) {
	  hselection_moca_reco->Fill(5,weight);
	  moca_reco_sel = true;
	  nb_moca_reco_sel+=weight;
	}
	
	//-----------------------------------------------//
	//-- Filter on mc at generated level (det cut) --//
	//-----------------------------------------------//

	//-- filter on vertex

	bool vertex_hadron = false;
	int nbch = 0;

	for (int ipart = 0; ipart < GenParts->size(); ipart++) {

	  MyGenPart particle = (*GenParts)[ipart];

	  if (particle.status != 1) continue;  

	  if (fabs(particle.Eta()) < 2.5 && particle.Pt() > 0.3 && particle.charge != 0) nbch++; //-- pt cut value
	}

	//-- at least 4 tracks
	if (nbch >= 4) vertex_hadron = true;

	//-- filter on HF Activity (in BSC range) and on Castor Activity

	bool HF_Activity_hadron = false;
	
	bool HFplus_hadron = false;
	bool HFminus_hadron = false;

	bool CASTOR_Activity_hadron = false;

	for (unsigned int ipart = 0;ipart<GenParts->size();ipart++) {

	  MyGenPart particle = (*GenParts)[ipart];

	  if (particle.status != 1) continue;
	  
	  int part_id = abs(particle.pdgId);
          if (part_id == 12 || part_id == 14 || part_id == 16) continue; //-- do not take into account neutrinos
          if (part_id == 13) continue; //-- do not take into account muons
	  
	  if (particle.Eta() > 3.23 && particle.Eta() < 4.65 && particle.E() > 4.) HFplus_hadron = true; 
	  if (particle.Eta() < -3.23 && particle.Eta() > -4.65 && particle.E() > 4.) HFminus_hadron = true; 

	  if (particle.Eta() < -5.2 && particle.Eta() > -6.6 && particle.E() > 8.*noise_sector_cut) CASTOR_Activity_hadron = true;
	  
	}
       
	if (HFplus_hadron && HFminus_hadron) HF_Activity_hadron = true;
	

	if (vertex_hadron) hselection_moca_gen_detcut->Fill(2,weight);

	if (vertex_hadron && HF_Activity_hadron) hselection_moca_gen_detcut->Fill(3,weight);

	if (vertex_hadron && HF_Activity_hadron && CASTOR_Activity_hadron) {
	  hselection_moca_gen_detcut->Fill(4,weight);
	  moca_gen_detcut_sel = true;
	  nb_moca_gen_detcut_sel+=weight;
	}

	//----------------------------------------------//
        //-- Filter on mc at generated level (xi cut) --//
	//----------------------------------------------//

	//-- sort generated particles in y (from y_min to y_max)

	std::vector<MyGenPart> TempParticles;
	std::vector<MyGenPart> RapiditySortedParticles;
	
	//-- copy only final stable particles with realistic Rapidity in tempvector

	for (unsigned int ipart = 0; ipart < GenParts->size(); ipart++) {
	  MyGenPart particle = (*GenParts)[ipart];
	  if (particle.status == 1) TempParticles.push_back(particle);
	}

	//-- do actual sorting

	while (TempParticles.size() != 0) {
	
	  double min_y = 10000;
	  int min_y_pos = -1;
	  
	  for (unsigned int ipart = 0; ipart < TempParticles.size();ipart++) {
	    if (TempParticles[ipart].Rapidity() < min_y) {
	      min_y = TempParticles[ipart].Rapidity();
	      min_y_pos = ipart;
	    }
	  }
	  
	  RapiditySortedParticles.push_back(TempParticles[min_y_pos]);
	  TempParticles.erase(TempParticles.begin()+min_y_pos);
	}
	
	//-- find delta_y_max
	
	double delta_y_max = 0;
	int delta_y_max_pos = -1;
	
	for (unsigned int ipart = 0 ; ipart < RapiditySortedParticles.size()-1; ipart++) {
	  double delta_y = RapiditySortedParticles[ipart+1].Rapidity() - RapiditySortedParticles[ipart].Rapidity();
	  if (delta_y > delta_y_max) {
	    delta_y_max = delta_y;
	    delta_y_max_pos = ipart;
	  }
	}

	//-- calculate Mx2 and My2
	
	long double XEtot = 0;
	long double XPxtot = 0;
	long double XPytot = 0;
	long double XPztot = 0;
	
	long double YEtot = 0;
	long double YPxtot = 0;
	long double YPytot = 0;
	long double YPztot = 0;
	
	for (unsigned int ipart = 0; ipart <= delta_y_max_pos; ipart++) {
	  XEtot += RapiditySortedParticles[ipart].E();
	  XPxtot += RapiditySortedParticles[ipart].Px();
	  XPytot += RapiditySortedParticles[ipart].Py();
	  XPztot += RapiditySortedParticles[ipart].Pz();
	}
	
	long double Mx2 = XEtot*XEtot - XPxtot*XPxtot - XPytot*XPytot - XPztot*XPztot;
	
	for (unsigned int ipart = delta_y_max_pos + 1; ipart < RapiditySortedParticles.size(); ipart++) {
	  YEtot += RapiditySortedParticles[ipart].E();
	  YPxtot += RapiditySortedParticles[ipart].Px();
	  YPytot += RapiditySortedParticles[ipart].Py();
	  YPztot += RapiditySortedParticles[ipart].Pz();
	}
	
	long double My2 = YEtot*YEtot - YPxtot*YPxtot - YPytot*YPytot - YPztot*YPztot;
	
	//-- calculate xix and xiy
	
	double xix = Mx2/(cmenergy*cmenergy);
	double xiy = My2/(cmenergy*cmenergy);
	
	//-- xi of event is max
	
	double xi = std::max(xix,xiy);
	double xidd = xix*xiy*cmenergy*cmenergy/(0.938*0.938);

	//-- hadron level selection

	if (cmenergy == 900) {
	  if (xix > 0.1 || xiy > 0.4 || xidd > 0.5) moca_gen_xicut_sel = true;
	} 
     
	else if (cmenergy == 2760) {
	  if (xix > 0.07 || xiy > 0.2 || xidd > 0.5) moca_gen_xicut_sel = true;
	} 

	else if (cmenergy == 7000) {
	  if (xix > 0.04 || xiy > 0.1 || xidd > 0.5) moca_gen_xicut_sel = true;
	}

	if(moca_gen_xicut_sel == true) {
	  hselection_moca_gen_xicut->Fill(2,weight);
	  nb_moca_gen_xicut_sel+=weight;
	}

	//-------------------------------//
	//--    fill moca tree once    --//
	//-------------------------------//

	if(moca_reco_sel == true || moca_gen_detcut_sel == true || moca_gen_xicut_sel == true) nb_moca_tree+=weight;
	if(moca_reco_sel == true && moca_gen_detcut_sel == true) nb_moca_reco_sel_gen_detcut_sel+=weight;
	if(moca_reco_sel == true && moca_gen_xicut_sel == true) nb_moca_reco_sel_gen_xicut_sel+=weight;
	if(moca_gen_detcut_sel == true && moca_gen_xicut_sel == true) nb_moca_gen_detcut_sel_xicut_sel+=weight;

	if(moca_reco_sel == true || moca_gen_detcut_sel == true || moca_gen_xicut_sel == true) {
	  if(dosubsample) tree_eflow->Fill();
	}

      } //-- end loop over moca

      //--------------------------------------------------------//    
      //--                    apply filter                    --//
      //--------------------------------------------------------//
	
      if(isData && !data_sel) continue;
      if(!isData && !moca_reco_sel && !moca_gen_xicut_sel) continue;
		
      //--------------------------------------------------//
      //--          data_sel and moca_reco_sel          --//
      //--------------------------------------------------//

      if ((isData && data_sel) || (!isData && moca_reco_sel)) {

	//-- vertex 

	for (unsigned int iVert=0;iVert<Vertices->size();iVert++) {

	  MyVertex vertex = (*Vertices)[iVert];
	  
	  hVx->Fill(vertex.x,weight);
	  hVy->Fill(vertex.y,weight);
	  hVz->Fill(vertex.z,weight);
	  hVrho->Fill(vertex.rho,weight);
	  hVndof->Fill(vertex.ndof,weight);
	}

	//-- run number and lumi section

	if (isData && cmenergy == 900) {
	  hRun900_sel->Fill(evtid->Run,weight);
	  if(evtid->Run==134721) hLS900_134721_sel->Fill(evtid->LumiBlock,weight);
	  if(evtid->Run==134725) hLS900_134725_sel->Fill(evtid->LumiBlock,weight);
	}
	
	//-- rechit

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

	for (unsigned int irec = 0;irec < CastorRecHits->size();irec++) {
	  
	  MyCastorRecHit rechit = (*CastorRecHits)[irec];

	  bool used_cha = false;
	  if(rechit.cha != 5 && rechit.cha != 6 && rechit.cha <= 80) used_cha = true; //-- for data 15,35,81,5,6
	  if(used_cha == false) continue;

	  rechit_energy = 0;
	  if (isData)  rechit_energy = rechit.energy*fac_data;  //-- for data, energy is intercalibrated fC
	  if (!isData) rechit_energy = rechit.energy*fac_moca;

	  if(rechit_energy < E_cha_reco_min) E_cha_reco_min = rechit_energy;
	  if(rechit_energy > E_cha_reco_max) E_cha_reco_max = rechit_energy;

	  module_energy[rechit.mod-1]+=rechit_energy;
          sector_energy[rechit.sec-1]+=rechit_energy;
          
          module_sector_used[rechit.mod-1]++;
          sector_module_used[rechit.sec-1]++;

	  hMBchannel[rechit.sec-1][rechit.mod-1]->Fill(rechit_energy,weight);

	  eflow+=rechit_energy;
	}

	hMBEflow->Fill(eflow,weight);

	for (int imod = 0; imod < 5;imod++) {
          if(module_energy[imod] < E_mod_reco_min) E_mod_reco_min = module_energy[imod];
          if(module_energy[imod] > E_mod_reco_max) E_mod_reco_max = module_energy[imod];
        }

        for (int isec = 0; isec < 16;isec++) {
          if(sector_energy[isec] < E_sec_reco_min) E_sec_reco_min = sector_energy[isec];
          if(sector_energy[isec] > E_sec_reco_max) E_sec_reco_max = sector_energy[isec];
        }

	for (int imod = 0; imod < 5;imod++) hMBmodule[imod]->Fill(module_energy[imod],weight);
        for (int isec = 0; isec < 16;isec++) hMBsector[isec]->Fill(sector_energy[isec],weight);

        for (int imod = 0; imod < 5;imod++) hMBmodule_sector_used[imod]->Fill(module_sector_used[imod],weight);
        for (int isec = 0; isec < 16;isec++) hMBsector_module_used[isec]->Fill(sector_module_used[isec],weight);

	//-- trackjet

	double trackjet_ptmax = -100;
	double trackjet_etamax = -100;
	int ntrackjet = 0;

	for (unsigned int itjet = 0; itjet < TrackJets->size(); itjet++) {

	  MyTrackJet trackjet = (*TrackJets)[itjet];

	  if(!(fabs(trackjet.eta_raw) < 2 && trackjet.pv)) continue;
	 
	  ntrackjet++;
	  hTrackJetEta->Fill(trackjet.eta_raw,weight);
	  hTrackJetPt->Fill(trackjet.pt_raw,weight);
	  hTrackJetPhi->Fill(trackjet.phi_raw,weight);
	  
	  if(trackjet.pt_raw > trackjet_ptmax) {
	    trackjet_ptmax = trackjet.pt_raw;
	    trackjet_etamax = trackjet.eta_raw;
	  }
	}    

	hNTrackJet->Fill(ntrackjet,weight);
	  
	for (int ipt = 0; ipt < nptbin; ipt++) {
	  if(trackjet_ptmax > ptbinning[ipt] && trackjet_ptmax < ptbinning[ipt+1]) {
	    hPtEflow[ipt]->Fill(eflow,weight);
	  }
	}

	for (int ieta = 0; ieta < netabin; ieta++) {
	  if(trackjet_etamax > etabinning[ieta] && trackjet_etamax < etabinning[ieta+1]) {
	    
	    for (int ipt = 0; ipt < nptmin; ipt++) {
	      if(trackjet_ptmax > ptmin[ipt]) {
		
		hEta_Eflow[ieta][ipt]->Fill(eflow,weight);
		hEta_Eta[ieta][ipt]->Fill(trackjet_etamax,weight);
		hEta_Pt[ieta][ipt]->Fill(trackjet_ptmax,weight);

	      }
	    } //-- end loop over pt

	  }
	} //-- end loop over eta

	if(trackjet_ptmax > ptcut) hAllPtEflow->Fill(eflow,weight);
      }
      
      //-------------------------------------------------//
      //--              moca_gen_xicut_sel             --//
      //-------------------------------------------------//
      
      if (!isData && moca_gen_xicut_sel) {
	
	double eflow_gen = 0;
	
	for (int ipart = 0;ipart<GenParts->size();ipart++) {
	  
	  MyGenPart particle = (*GenParts)[ipart];
	  
	  if (particle.status != 1) continue;
	  
	  if (!(particle.Eta() < -5.2 && particle.Eta() > -6.6 && particle.E() > 0.)) continue;
	  
	  int part_id = abs(particle.pdgId);
	  if (part_id == 12 || part_id == 14 || part_id == 16) continue; //-- do not take into account neutrinos 
	  if (part_id == 13) continue; //-- do not take into account muons
	  
	  if(particle.E() > E_gen_max) E_gen_max = particle.E();
	  hgen_energy->Fill(particle.E(),weight);
          hgen_eta->Fill(particle.Eta(),weight);
          hgen_phi->Fill(particle.Phi(),weight);
	  eflow_gen+=particle.E();
	}
	
	hMBEflow_gen->Fill(eflow_gen,weight);
      }
      
    } //-- end event loop
    
    delete tree;
    file->Close();
    
    //----------------------------//
    //--     save subsample     --//
    //----------------------------//

    if(dosubsample) {
      file_eflow->cd();
      tree_eflow->AutoSave();
      file_eflow->Close();
    }

  } //-- end file loop
  
  //--------------------------//
  //-- normalize histograms --//
  //--------------------------//

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

    if(MB_mean_sector_module_used[isec] != 0) MB_mean_sector[isec]/=MB_mean_sector_module_used[isec];
    if(MB_mean_sector_module_used[isec] != 0) MB_error_sector[isec]/=MB_mean_sector_module_used[isec];

    hMBphiprofile_mean->SetBinContent(isec+1,MB_mean_sector[isec]);
    hMBphiprofile_mean->SetBinError(isec+1,MB_error_sector[isec]);
  }

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

      hMBchannel_mean->SetBinContent(icha+1,MB_mean_channel[isec][imod]);
      hMBchannel_mean->SetBinError(icha+1,MB_error_channel[isec][imod]);
    }
  }

  //------------------------------------------//
  //-- compute energy flow means and errors --//
  //------------------------------------------//

  double EflowMB_mean = hMBEflow->GetMean();
  double EflowMB_error = hMBEflow->GetMeanError();

  double EflowAllPt_mean = hAllPtEflow->GetMean();
  double EflowAllPt_error = hAllPtEflow->GetMeanError();

  double EflowPt_mean[nptbin];
  double EflowPt_error[nptbin];
  for (int ipt = 0; ipt < nptbin; ipt++) EflowPt_mean[ipt] = hPtEflow[ipt]->GetMean();
  for (int ipt = 0; ipt < nptbin; ipt++) EflowPt_error[ipt] = hPtEflow[ipt]->GetMeanError();

  double EflowMB_gen_mean = hMBEflow_gen->GetMean();
  double EflowMB_gen_error = hMBEflow_gen->GetMeanError();

  double EflowRatioAllPt_mean = EflowAllPt_mean/EflowMB_mean;
  double EflowRatioAllPt_error = GetRatioError(EflowAllPt_mean,EflowMB_mean,EflowAllPt_error,EflowMB_error);

  double EflowRatioPt_mean[nptbin];
  double EflowRatioPt_error[nptbin];
  for (int ipt = 0; ipt < nptbin; ipt++) EflowRatioPt_mean[ipt] = EflowPt_mean[ipt]/EflowMB_mean;
  for (int ipt = 0; ipt < nptbin; ipt++) EflowRatioPt_error[ipt] = GetRatioError(EflowPt_mean[ipt],EflowMB_mean,EflowPt_error[ipt],EflowMB_error);

  for (int ipt = 0; ipt < nptbin; ipt++) {
    hPtEflowRatio->SetBinContent(ipt+1,EflowRatioPt_mean[ipt]);
    hPtEflowRatio->SetBinError(ipt+1, EflowRatioPt_error[ipt]);
  }

  double EflowEta_mean[netabin][nptmin];
  double EflowEta_error[netabin][nptmin];

  double Eta_mean[netabin][nptmin];
  double Eta_error[netabin][nptmin];

  double Pt_mean[netabin][nptmin];
  double Pt_error[netabin][nptmin];

  double EflowRatioEta_mean[netabin][nptmin];
  double EflowRatioEta_error[netabin][nptmin];

  for (int ieta = 0; ieta < netabin; ieta++) {
    for (int ipt = 0; ipt < nptmin; ipt++) {

      EflowEta_mean[ieta][ipt] = hEta_Eflow[ieta][ipt]->GetMean();
      EflowEta_error[ieta][ipt] = hEta_Eflow[ieta][ipt]->GetMeanError();

      Eta_mean[ieta][ipt] = hEta_Eta[ieta][ipt]->GetMean();
      Eta_error[ieta][ipt] = hEta_Eta[ieta][ipt]->GetMeanError();
      
      Pt_mean[ieta][ipt] = hEta_Pt[ieta][ipt]->GetMean();
      Pt_error[ieta][ipt] = hEta_Pt[ieta][ipt]->GetMeanError();

      EflowRatioEta_mean[ieta][ipt] = EflowEta_mean[ieta][ipt]/EflowMB_mean;
      EflowRatioEta_error[ieta][ipt] = GetRatioError(EflowEta_mean[ieta][ipt],EflowMB_mean,EflowEta_error[ieta][ipt],EflowMB_error);
      
      hEta_EflowRatio[ipt]->SetBinContent(ieta+1,EflowRatioEta_mean[ieta][ipt]);
      hEta_EflowRatio[ipt]->SetBinError(ieta+1,EflowRatioEta_error[ieta][ipt]);

      hEta_Ptmean[ipt]->SetBinContent(ieta+1,Pt_mean[ieta][ipt]);
      hEta_Ptmean[ipt]->SetBinError(ieta+1,Pt_error[ieta][ipt]);
    }
  }
  
  //----------------------------------//
  //-- run number and lumi section  --//
  //----------------------------------//
  
  if (isData && cmenergy == 900) {
    ComputeHistoRatio(hRun900_sel,hRun900,*hRun900_stability);
    ComputeHistoRatio(hLS900_134721_sel,hLS900_134721,*hLS900_134721_stability);
    ComputeHistoRatio(hLS900_134725_sel,hLS900_134725,*hLS900_134725_stability);
  }
  
  //------------------------------------//
  //-- check for underflow - overflow  -//
  //------------------------------------//
  
  //-- run number and lumi section

  CheckHisto(hRun900);
  CheckHisto(hRun900_sel);
  CheckHisto(hRun900_stability);

  CheckHisto(hLS900_134721);
  CheckHisto(hLS900_134721_sel);
  CheckHisto(hLS900_134721_stability);

  CheckHisto(hLS900_134725);
  CheckHisto(hLS900_134725_sel);
  CheckHisto(hLS900_134725_stability);

  //-- weight and non-linearity factor

  CheckHisto(hNLfactor);
  CheckHisto(hWeightEflow);
  CheckHisto(hWeightPtTrackJet);

  //--  Selection

  if(isData) CheckHisto(hselection_data);
  if(!isData) CheckHisto(hselection_moca_reco);
  if(!isData) CheckHisto(hselection_moca_gen_detcut);
  if(!isData) CheckHisto(hselection_moca_gen_xicut);

  //-- vertex

  CheckHisto(hVx);
  CheckHisto(hVy);
  CheckHisto(hVz);
  CheckHisto(hVrho);
  CheckHisto(hVndof);
  
  //-- energy distribution

  for (int imod = 0; imod < 5; imod++)  CheckHisto(hMBmodule[imod]);
  for (int imod = 0; imod < 5; imod++)  CheckHisto(hMBmodule_sector_used[imod]);
  for (int isec = 0; isec < 16; isec++) CheckHisto(hMBsector[isec]);
  for (int isec = 0; isec < 16; isec++) CheckHisto(hMBsector_module_used[isec]);

  for (int isec = 0; isec < 16;isec++) {
    for (int imod = 0; imod < 5;imod++) {
      CheckHisto(hMBchannel[isec][imod]);
    }
  }

  CheckHisto(hMBchannel_mean);

  //-- z profile and phi profile

  CheckHisto(hMBzprofile_mean);
  CheckHisto(hMBphiprofile_mean);

  //-- eflow

  CheckHisto(hMBEflow);
  CheckHisto(hAllPtEflow);
  for (int ipt = 0; ipt < nptbin; ipt++) CheckHisto(hPtEflow[ipt]);
  CheckHisto(hPtEflowRatio);
  CheckHisto(hMBEflow_gen);

  //-- trackjet variable

  CheckHisto(hNTrackJet);
  CheckHisto(hTrackJetEta);
  CheckHisto(hTrackJetPt);
  CheckHisto(hTrackJetPhi);

  //-- generated information

  CheckHisto(hgen_energy);
  CheckHisto(hgen_eta);
  CheckHisto(hgen_phi);

  //-- eflow as function of eta and pt

  for (int ieta = 0; ieta < netabin; ieta++) {
    for (int ipt = 0; ipt < nptmin; ipt++) {
      CheckHisto(hEta_Eflow[ieta][ipt]);
      CheckHisto(hEta_Eta[ieta][ipt]);
      CheckHisto(hEta_Pt[ieta][ipt]);
    }
  }
  
  for (int ipt = 0; ipt < nptmin; ipt++) CheckHisto(hEta_EflowRatio[ipt]);
  for (int ipt = 0; ipt < nptmin; ipt++) CheckHisto(hEta_Ptmean[ipt]);

  //-------------------------------------//
  //-- write histo to output root file --//
  //-------------------------------------//
  
  cout<<endl<<"total number of events: "<<nb_evt_tot<<" from "<<file_nb<<" file(s)"<<endl;
  cout<<"total number of events (no weight): "<<nb_evt_tot_now<<" (weight / no weight: "<<100*nb_evt_tot/nb_evt_tot_now<<" %)"<<endl;
  if(isData) cout<<nb_data_sel<<" selected events in data"<<endl;

  if(!isData) {
    cout<<nb_moca_reco_sel<<" selected events in mc at reco level"<<endl;
    cout<<nb_moca_gen_detcut_sel<<" selected events in mc at generated level (det cut)"<<endl;
    cout<<nb_moca_gen_xicut_sel<<" selected events in mc at generated level (xi cut)"<<endl;

    cout<<""<<endl;

    cout<<nb_moca_tree<<" mc events copied in the tree"<<endl;
    cout<<nb_moca_reco_sel_gen_detcut_sel<<" selected events in mc at reco level and generated level (det cut)"<<endl;
    cout<<nb_moca_reco_sel_gen_xicut_sel<<" selected events in mc at reco level and generated level (xi cut)"<<endl;
    cout<<nb_moca_gen_detcut_sel_xicut_sel<<" selected events in mc at generated level (det cut and xi cut)"<<endl;
    cout<<""<<endl;
  }

  cout<<endl<<"E channel reco min: "<<E_cha_reco_min<<endl;
  cout<<"E channel reco max: "<<E_cha_reco_max<<endl;
  
  cout<<endl<<"E module reco min: "<<E_mod_reco_min<<endl;
  cout<<"E module reco max: "<<E_mod_reco_max<<endl;
  
  cout<<endl<<"E sector reco min: "<<E_sec_reco_min<<endl;
  cout<<"E sector reco max: "<<E_sec_reco_max<<endl;
  
  if(!isData) cout<<endl<<"E gen max: "<<E_gen_max<<endl<<endl;
  
  Char_t output_filename[200];
  const char* part = filename.Data();
  sprintf(output_filename,"../Result/output_eflow_%s",part);
  TFile* foutput = new TFile(output_filename,"RECREATE");
  foutput->cd();

  //-- run number and lumi section

  hRun900->Write();
  hRun900_sel->Write();
  hRun900_stability->Write();

  hLS900_134721->Write();
  hLS900_134721_sel->Write();
  hLS900_134721_stability->Write();

  hLS900_134725->Write();
  hLS900_134725_sel->Write();
  hLS900_134725_stability->Write();

  //-- weight and non-linearity factor

  hNLfactor->Write();
  hWeightEflow->Write();
  hWeightPtTrackJet->Write();

  //--  Selection
	
  hselection_data->Write();
  hselection_moca_reco->Write();
  hselection_moca_gen_detcut->Write();
  hselection_moca_gen_xicut->Write();

  //-- vertex

  hVx->Write();
  hVy->Write();
  hVz->Write();
  hVrho->Write();
  hVndof->Write();

  //-- energy distribution

  for (int imod = 0; imod < 5; imod++)  hMBmodule[imod]->Write();
  for (int imod = 0; imod < 5; imod++)  hMBmodule_sector_used[imod]->Write();
  for (int isec = 0; isec < 16; isec++) hMBsector[isec]->Write();
  for (int isec = 0; isec < 16; isec++) hMBsector_module_used[isec]->Write();

  for (int imod = 0; imod < 5;imod++) {
    for (int isec = 0; isec < 16;isec++) {
      hMBchannel[isec][imod]->Write();
    }
  }

  hMBchannel_mean->Write();

  //-- z profile and phi profile

  hMBzprofile_mean->Write();
  hMBphiprofile_mean->Write();

  //-- eflow

  hMBEflow->Write();
  hAllPtEflow->Write();
  for (int ipt = 0; ipt < nptbin; ipt++) hPtEflow[ipt]->Write();
  hPtEflowRatio->Write();
  hMBEflow_gen->Write();

  //-- trackjet variable

  hNTrackJet->Write();
  hTrackJetEta->Write();
  hTrackJetPt->Write();
  hTrackJetPhi->Write();

  //-- generated information

  hgen_energy->Write();
  hgen_eta->Write();
  hgen_phi->Write();

  //-- eflow as function of eta and pt
  
  for (int ieta = 0; ieta < netabin; ieta++) {
    for (int ipt = 0; ipt < nptmin; ipt++) {
      hEta_Eflow[ieta][ipt]->Write();
      hEta_Eta[ieta][ipt]->Write();
      hEta_Pt[ieta][ipt]->Write();
    }
  }
  
  for (int ipt = 0; ipt < nptmin; ipt++) hEta_EflowRatio[ipt]->Write();
  for (int ipt = 0; ipt < nptmin; ipt++) hEta_Ptmean[ipt]->Write();

  foutput->Close();
  cout<<"file "<<output_filename<<" created"<<endl;

  //----------------------------//
  //--     some print out     --//
  //----------------------------//

  if(isData) {
    cout<<endl<<"data selection: "<<endl;
    cout<<"number of events before selection: "<<hselection_data->GetBinContent(1)<<endl;
    cout<<"number of events after physics declared bit: "<<hselection_data->GetBinContent(2)<<endl;
    cout<<"number of events after castor invalid data: "<<hselection_data->GetBinContent(3)<<endl;
    cout<<"number of events after scraping events: "<<hselection_data->GetBinContent(4)<<endl;
    cout<<"number of events after L1: "<<hselection_data->GetBinContent(5)<<endl;
    cout<<"number of events after HLT: "<<hselection_data->GetBinContent(6)<<endl;
    cout<<"number of events after at least one good vertex: "<<hselection_data->GetBinContent(7)<<endl;
    cout<<"number of events after exactly one good vertex: "<<hselection_data->GetBinContent(8)<<endl;
    cout<<"number of events after HF Activity: "<<hselection_data->GetBinContent(9)<<endl;
    cout<<"number of events after CASTOR activity: "<<hselection_data->GetBinContent(10)<<endl;
  }


  if(!isData) {
    cout<<endl<<"moca at reco level: "<<endl;
    cout<<"number of events before selection: "<<hselection_moca_reco->GetBinContent(1)<<endl;
    cout<<"number of events after at least one good vertex: "<<hselection_moca_reco->GetBinContent(2)<<endl;
    cout<<"number of events after exactly one good vertex: "<<hselection_moca_reco->GetBinContent(3)<<endl;
    cout<<"number of events after HF Activity: "<<hselection_moca_reco->GetBinContent(4)<<endl;
    cout<<"number of events after CASTOR activity: "<<hselection_moca_reco->GetBinContent(5)<<endl;
    cout<<endl<<"moca at generated level (det cut): "<<endl;
    cout<<"number of events before selection: "<<hselection_moca_gen_detcut->GetBinContent(1)<<endl;
    cout<<"number of events after vertex condition: "<<hselection_moca_gen_detcut->GetBinContent(2)<<endl;
    cout<<"number of events after HF Activity: "<<hselection_moca_gen_detcut->GetBinContent(3)<<endl;
    cout<<"number of events after Castor Activity: "<<hselection_moca_gen_detcut->GetBinContent(4)<<endl;
    cout<<endl<<"moca at generated level (xi cut): "<<endl;
    cout<<"number of events before selection: "<<hselection_moca_gen_xicut->GetBinContent(1)<<endl;
    cout<<"number of events after xi condition: "<<hselection_moca_gen_xicut->GetBinContent(2)<<endl;
  }

  if(isData) cout<<endl<<"data at "<<cmenergy<<" GeV"<<endl;
  if(!isData) cout<<endl<<"moca at "<<cmenergy<<" GeV"<<endl;
  cout<<endl<<"mean E flow MB =  "<<EflowMB_mean<<" +/- "<<EflowMB_error<<" GeV"<<endl;
  if(!isData) cout<<"mean E flow MB gen level = "<<EflowMB_gen_mean<<" +/- "<<EflowMB_gen_error<<" GeV"<<endl;
  cout<<"mean E flow Pt scale > "<<ptcut<<" GeV = "<<EflowAllPt_mean<<" +/- "<<EflowAllPt_error<<" GeV"<<endl<<endl;

  for (int ipt = 0; ipt < nptbin; ipt++) cout<<"mean E flow "<<ptbinning[ipt]<<" < Pt scale < "<<ptbinning[ipt+1]<<" GeV = "<<EflowPt_mean[ipt]<<" +/- "<<EflowPt_error[ipt]<<" GeV"<<endl;
  cout<<endl<<"E flow ratio Pt scale > "<<ptcut<<" GeV = "<<EflowRatioAllPt_mean<<" +/- "<< EflowRatioAllPt_error<<endl<<endl;
  for (int ipt = 0; ipt < nptbin; ipt++) cout<<"E flow ratio "<<ptbinning[ipt]<<" < Pt scale < "<<ptbinning[ipt+1]<<" GeV = "<<EflowRatioPt_mean[ipt]<<" +/- "<<EflowRatioPt_error[ipt]<<" GeV"<<endl; 
  cout<<endl;

  for (int ipt = 0; ipt < nptmin; ipt++) {
    for (int ieta = 0; ieta < netabin; ieta++) 
      cout<<hEta_Eflow[ieta][ipt]->GetTitle()<<": N events = "<<hEta_Eflow[ieta][ipt]->GetEntries()<<endl;
    cout<<endl;      
  }
  
  for (int ipt = 0; ipt < nptmin; ipt++) {
    for (int ieta = 0; ieta < netabin; ieta++) 
      cout<<hEta_Eflow[ieta][ipt]->GetTitle()<<" = "<<EflowEta_mean[ieta][ipt]<<" +/- "<<EflowEta_error[ieta][ipt]<<" GeV"<<endl;
    cout<<endl;
  }

  for (int ipt = 0; ipt < nptmin; ipt++) {
    for (int ieta = 0; ieta < netabin; ieta++)
      cout<<hEta_Eflow[ieta][ipt]->GetTitle()<<" / energy flow MB = "<<EflowRatioEta_mean[ieta][ipt]<<" +/- "<<EflowRatioEta_error[ieta][ipt]<<" GeV"<<endl;
    cout<<endl;
  }

  for (int ipt = 0; ipt < nptmin; ipt++) {
    for (int ieta = 0; ieta < netabin; ieta++)
      cout<<hEta_Eta[ieta][ipt]->GetTitle()<<" = "<<Eta_mean[ieta][ipt]<<" +/- "<<Eta_error[ieta][ipt]<<endl;
    cout<<endl;
  }

  for (int ipt = 0; ipt < nptmin; ipt++) {
    for (int ieta = 0; ieta < netabin; ieta++)
      cout<<hEta_Pt[ieta][ipt]->GetTitle()<<" = "<<Pt_mean[ieta][ipt]<<" +/- "<<Pt_error[ieta][ipt]<<" GeV"<<endl;
    cout<<endl;
  }

}

void EflowAnalyzer::CheckHisto(TH1D* h) {

  Int_t NbinX = h->GetNbinsX();
  
  if(h->GetBinContent(0) != 0) cout<<h->GetTitle()<<" has underflow of "<<h->GetBinContent(0)<<" entries"<<endl;
  if(h->GetBinContent(NbinX+1) != 0) cout<<h->GetTitle()<<" has overflow of "<<h->GetBinContent(NbinX+1)<<" entries"<<endl;
  
  return;
}

void EflowAnalyzer::CheckHisto(TH2D* h) {

  Int_t NbinX = h->GetNbinsX();
  Int_t NbinY = h->GetNbinsY();

  int underflow_x = 0;
  int underflow_y = 0;

  int overflow_x = 0;
  int overflow_y = 0;

  for(int ibiny = 0; ibiny <= NbinY+1; ibiny++) {
    if(h->GetBinContent(0,ibiny) != 0) underflow_x+=h->GetBinContent(0,ibiny);
    if(h->GetBinContent(NbinX+1,ibiny) != 0) overflow_x+=h->GetBinContent(NbinX+1,ibiny);
  }

  for(int ibinx = 0; ibinx <= NbinX+1; ibinx++) {
    if(h->GetBinContent(ibinx,0) != 0)underflow_y+=h->GetBinContent(ibinx,0);
    if(h->GetBinContent(ibinx,NbinY+1) != 0) overflow_y+=h->GetBinContent(ibinx,NbinY+1);
  }

  if(underflow_x != 0) cout<<h->GetTitle()<<" has x underflow of "<<underflow_x<<endl;
  if(overflow_x != 0) cout<<h->GetTitle()<<" has x overflow of "<<overflow_x<<endl;
  
  if(underflow_y != 0) cout<<h->GetTitle()<<" has y underflow of "<<underflow_y<<endl;
  if(overflow_y!= 0) cout<<h->GetTitle()<<" has y overflow of "<<overflow_y<<endl;

  return;
}


void EflowAnalyzer::SetAxisName(TH1D* h, TString xleg, TString yleg) { 
  h->GetXaxis()->SetTitle(xleg);
  h->GetYaxis()->SetTitle(yleg);
}

TH1D* EflowAnalyzer::MakeHisto(TString name, TString title, TString xleg, TString yleg, int nbin, float* listbin) {

  TH1D* h = new TH1D(name,title,nbin,listbin);

  h->GetXaxis()->SetTitle(xleg);
  h->GetYaxis()->SetTitle(yleg);

  h->SetMinimum(0);
  h->Sumw2();

  cout<<"create histo: "<<h->GetName()<<" with title: "<<h->GetTitle()<<endl;

  return h;
}

TH1D* EflowAnalyzer::MakeHisto(TString name, TString title, TString xleg, TString yleg, int nbin, double bmin, double bmax) {


  TH1D* h = new TH1D(name,title,nbin,bmin,bmax);

  h->GetXaxis()->SetTitle(xleg);
  h->GetYaxis()->SetTitle(yleg);

  h->SetMinimum(0);
  h->Sumw2();

  cout<<"create histo: "<<h->GetName()<<" with title: "<<h->GetTitle()<<endl;

  return h;
}

TH2D* EflowAnalyzer::MakeHisto(TString name, TString title, TString xleg, TString yleg, int nbinx, double bxmin, double bxmax, int nbiny, double bymin, double bymax) {


  TH2D* h = new TH2D(name,title,nbinx,bxmin,bxmax,nbiny,bymin,bymax);

  h->GetXaxis()->SetTitle(xleg);
  h->GetYaxis()->SetTitle(yleg);

  h->SetMinimum(0);
  h->Sumw2();

  cout<<"create histo: "<<h->GetName()<<" with title: "<<h->GetTitle()<<endl;

  return h;
}

TH1D* EflowAnalyzer::MakeHisto(int id, TString name, TString title, TString xleg, TString yleg, int nbin, double bmin, double bmax) {

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

TH1D* EflowAnalyzer::MakeHisto(int isec, int imod, TString name, TString title, TString xleg, TString yleg, int nbin, double bmin, double bmax) {

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

double EflowAnalyzer::GetRatioError(double a,double b,double sig_a,double sig_b) {

  double sigmaR = 0;

  if(b == 0) {
    cout<<"you are going to divide by zero"<<endl;
    return(sigmaR);
  }
  
  double R = a/b;
  double sigmaR2 = TMath::Power(R,2)*(TMath::Power(sig_a/a,2)+TMath::Power(sig_b/b,2));
  if(sigmaR2>0) sigmaR = TMath::Sqrt(sigmaR2);

  return(sigmaR);
}

Double_t eflow_ana_fpol4(Double_t *x, Double_t *par) {
  Double_t result = 0;
  result = par[0] * TMath::Power(x[0],4) + par[1] * TMath::Power(x[0],3) + par[2] * TMath::Power(x[0],2) + par[3] * x[0] + par[4]; 
  return result;
}


double EflowAnalyzer::GetEflowMCWeight(double Eflow, double cmenergy) {

  double a,b,c,d,e;
  double min_range,max_range;

  if(cmenergy == 900) {
    min_range = 0;
    max_range = 300;
    a = 3.82731e-10;
    b = -1.27842e-07;
    c = 4.29467e-05;
    d = -0.00824302;
    e = 1.35815;
  }

  if(cmenergy == 2760) {
    min_range = 0;
    max_range = 595;
    a = 5.67915e-11;
    b = -8.38315e-08;
    c = 3.97327e-05; 
    d = -0.00601309; 
    e = 1.17696;
  }

  if(cmenergy == 7000) {
    min_range = 0;
    max_range = 1230;
    a = 5.79263e-12; 
    b = -1.47533e-08; 
    c = 1.46094e-05; 
    d = -0.00383304; 
    e = 1.06463; 
  }

  TF1* f = new TF1("myfit",eflow_ana_fpol4,min_range,max_range,5);
  f->SetParameters(a,b,c,d,e);

  double weight = 1;
  if(Eflow > min_range && Eflow < max_range) weight = f->Eval(Eflow);
  return(weight);
}

double EflowAnalyzer::GetNonLinearityFactor(double energy, double cmenergy) {
    
  TH1F *histo = NULL;

  if (cmenergy == 900) {

    histo = new TH1F("histo","900GeV",200,0,2000);

    histo->SetBinContent(1,0.721448);
    histo->SetBinContent(2,0.722857);
    histo->SetBinContent(3,0.686051);
    histo->SetBinContent(4,0.66101);
    histo->SetBinContent(5,0.620311);
    histo->SetBinContent(6,0.606234);
    histo->SetBinContent(7,0.57267);
    histo->SetBinContent(8,0.552634);
    histo->SetBinContent(9,0.545314);
    histo->SetBinContent(10,0.532987);
    histo->SetBinContent(11,0.518831);
    histo->SetBinContent(12,0.512978);
    histo->SetBinContent(13,0.499531);
    histo->SetBinContent(14,0.49845);
    histo->SetBinContent(15,0.490305);
    histo->SetBinContent(16,0.485078);
    histo->SetBinContent(17,0.481035);
    histo->SetBinContent(18,0.477151);
    histo->SetBinContent(19,0.471002);
    histo->SetBinContent(20,0.467955);
    histo->SetBinContent(21,0.465533);
    histo->SetBinContent(22,0.458666);
    histo->SetBinContent(23,0.458348);
    histo->SetBinContent(24,0.45367);
    histo->SetBinContent(25,0.450259);
    histo->SetBinContent(26,0.449351);
    histo->SetBinContent(27,0.443901);
    histo->SetBinContent(28,0.443626);
    histo->SetBinContent(29,0.443137);
    histo->SetBinContent(30,0.442947);
    histo->SetBinContent(31,0.436041);
    histo->SetBinContent(32,0.431092);
    histo->SetBinContent(33,0.434011);
    histo->SetBinContent(34,0.430981);
    histo->SetBinContent(35,0.432902);
    histo->SetBinContent(36,0.427133);
    histo->SetBinContent(37,0.432103);
    histo->SetBinContent(38,0.427756);
    histo->SetBinContent(39,0.437604);
    histo->SetBinContent(40,0.422457);
    histo->SetBinContent(41,0.427414);
    histo->SetBinContent(42,0.430278);
    histo->SetBinContent(43,0.419786);
    histo->SetBinContent(44,0.425318);
    histo->SetBinContent(45,0.406136);
    histo->SetBinContent(46,0.366032);
    for(int ibin = 47; ibin <=200; ibin++) histo->SetBinContent(ibin,0);
  } 

  else if (cmenergy == 2760) {
  
    histo=new TH1F("histo","2760GeV",200,0,2000);
    
    histo->SetBinContent(1,0.73351);
    histo->SetBinContent(2,0.777681);
    histo->SetBinContent(3,0.729239);
    histo->SetBinContent(4,0.682574);
    histo->SetBinContent(5,0.671889);
    histo->SetBinContent(6,0.650658);
    histo->SetBinContent(7,0.622451);
    histo->SetBinContent(8,0.598462);
    histo->SetBinContent(9,0.608734);
    histo->SetBinContent(10,0.58401);
    histo->SetBinContent(11,0.575963);
    histo->SetBinContent(12,0.57471);
    histo->SetBinContent(13,0.55768);
    histo->SetBinContent(14,0.554455);
    histo->SetBinContent(15,0.550512);
    histo->SetBinContent(16,0.554331);
    histo->SetBinContent(17,0.533822);
    histo->SetBinContent(18,0.543537);
    histo->SetBinContent(19,0.536084);
    histo->SetBinContent(20,0.529561);
    histo->SetBinContent(21,0.525936);
    histo->SetBinContent(22,0.517857);
    histo->SetBinContent(23,0.523743);
    histo->SetBinContent(24,0.517746);
    histo->SetBinContent(25,0.517763);
    histo->SetBinContent(26,0.516648);
    histo->SetBinContent(27,0.516028);
    histo->SetBinContent(28,0.514495);
    histo->SetBinContent(29,0.516482);
    histo->SetBinContent(30,0.514519);
    histo->SetBinContent(31,0.50879);
    histo->SetBinContent(32,0.506572);
    histo->SetBinContent(33,0.504814);
    histo->SetBinContent(34,0.500327);
    histo->SetBinContent(35,0.497214);
    histo->SetBinContent(36,0.497952);
    histo->SetBinContent(37,0.496354);
    histo->SetBinContent(38,0.497642);
    histo->SetBinContent(39,0.495763);
    histo->SetBinContent(40,0.494838);
    histo->SetBinContent(41,0.494929);
    histo->SetBinContent(42,0.5014);
    histo->SetBinContent(43,0.492647);
    histo->SetBinContent(44,0.487552);
    histo->SetBinContent(45,0.48994);
    histo->SetBinContent(46,0.486941);
    histo->SetBinContent(47,0.491751);
    histo->SetBinContent(48,0.494377);
    histo->SetBinContent(49,0.492545);
    histo->SetBinContent(50,0.492089);
    histo->SetBinContent(51,0.483155);
    histo->SetBinContent(52,0.482404);
    histo->SetBinContent(53,0.484746);
    histo->SetBinContent(54,0.485681);
    histo->SetBinContent(55,0.478457);
    histo->SetBinContent(56,0.476022);
    histo->SetBinContent(57,0.484);
    histo->SetBinContent(58,0.478708);
    histo->SetBinContent(59,0.477126);
    histo->SetBinContent(60,0.484166);
    histo->SetBinContent(61,0.476339);
    histo->SetBinContent(62,0.474368);
    histo->SetBinContent(63,0.469675);
    histo->SetBinContent(64,0.476968);
    histo->SetBinContent(65,0.475522);
    histo->SetBinContent(66,0.480029);
    histo->SetBinContent(67,0.474057);
    histo->SetBinContent(68,0.467267);
    histo->SetBinContent(69,0.472917);
    histo->SetBinContent(70,0.468073);
    histo->SetBinContent(71,0.477417);
    histo->SetBinContent(72,0.482591);
    histo->SetBinContent(73,0.467737);
    histo->SetBinContent(74,0.459719);
    histo->SetBinContent(75,0.455728);
    histo->SetBinContent(76,0.466121);
    histo->SetBinContent(77,0.476889);
    histo->SetBinContent(78,0.465791);
    histo->SetBinContent(79,0.459312);
    histo->SetBinContent(80,0.468571);
    histo->SetBinContent(81,0.463172);
    histo->SetBinContent(82,0.465802);
    histo->SetBinContent(83,0.473056);
    histo->SetBinContent(84,0.461653);
    histo->SetBinContent(85,0.462807);
    histo->SetBinContent(86,0.469789);
    histo->SetBinContent(87,0.46867);
    histo->SetBinContent(88,0.454514);
    histo->SetBinContent(89,0.466207);
    histo->SetBinContent(90,0.448409);
    histo->SetBinContent(91,0.450769);
    histo->SetBinContent(92,0.467429);
    histo->SetBinContent(93,0.443791);
    histo->SetBinContent(94,0.424375);
    histo->SetBinContent(95,0.45616);
    histo->SetBinContent(96,0.437481);
    histo->SetBinContent(97,0.463019);
    histo->SetBinContent(98,0.43287);
    histo->SetBinContent(99,0.440571);
    histo->SetBinContent(100,0.445684);
    histo->SetBinContent(101,0.450952);
    histo->SetBinContent(102,0.4445);
    histo->SetBinContent(103,0.435904);
    histo->SetBinContent(104,0.421967);
    histo->SetBinContent(105,0.465373);
    histo->SetBinContent(106,0.432308);
    histo->SetBinContent(107,0.453016);
    histo->SetBinContent(108,0.428667);
    histo->SetBinContent(109,0.420588);
    histo->SetBinContent(110,0.404828);
    histo->SetBinContent(111,0.414783);
    histo->SetBinContent(112,0.457037);
    histo->SetBinContent(113,0.415833);
    histo->SetBinContent(114,0.449388);
    histo->SetBinContent(115,0.441538);
    histo->SetBinContent(116,0.437778);
    histo->SetBinContent(117,0.457143);
    histo->SetBinContent(118,0.412);
    histo->SetBinContent(119,0.427);
    histo->SetBinContent(120,0.468571);
    histo->SetBinContent(121,0.435758);
    histo->SetBinContent(122,0.390526);
    histo->SetBinContent(123,0.413333);
    histo->SetBinContent(124,0.449231);
    histo->SetBinContent(125,0.374545);
    histo->SetBinContent(126,0.429524);
    histo->SetBinContent(127,0.470667);
    histo->SetBinContent(128,0.428571);
    histo->SetBinContent(129,0.476667);
    histo->SetBinContent(130,0.368571);
    histo->SetBinContent(131,0.306667);
    for(int ibin = 132; ibin <=200; ibin++) histo->SetBinContent(ibin,0);
  } 

  else if (cmenergy == 7000) {
    
    histo=new TH1F("histo","7TeV",200,0,2000);
    
    histo->SetBinContent(1,0.721693);
    histo->SetBinContent(2,0.729013);
    histo->SetBinContent(3,0.716971);
    histo->SetBinContent(4,0.708558);
    histo->SetBinContent(5,0.645266);
    histo->SetBinContent(6,0.629091);
    histo->SetBinContent(7,0.61978);
    histo->SetBinContent(8,0.621733);
    histo->SetBinContent(9,0.597365);
    histo->SetBinContent(10,0.586991);
    histo->SetBinContent(11,0.588339);
    histo->SetBinContent(12,0.572764);
    histo->SetBinContent(13,0.56528);
    histo->SetBinContent(14,0.567514);
    histo->SetBinContent(15,0.568848);
    histo->SetBinContent(16,0.555901);
    histo->SetBinContent(17,0.553478);
    histo->SetBinContent(18,0.547795);
    histo->SetBinContent(19,0.542438);
    histo->SetBinContent(20,0.549176);
    histo->SetBinContent(21,0.539875);
    histo->SetBinContent(22,0.537946);
    histo->SetBinContent(23,0.534045);
    histo->SetBinContent(24,0.532919);
    histo->SetBinContent(25,0.530786);
    histo->SetBinContent(26,0.531912);
    histo->SetBinContent(27,0.522301);
    histo->SetBinContent(28,0.52568);
    histo->SetBinContent(29,0.521862);
    histo->SetBinContent(30,0.524238);
    histo->SetBinContent(31,0.517848);
    histo->SetBinContent(32,0.524794);
    histo->SetBinContent(33,0.523392);
    histo->SetBinContent(34,0.514632);
    histo->SetBinContent(35,0.512116);
    histo->SetBinContent(36,0.514327);
    histo->SetBinContent(37,0.518286);
    histo->SetBinContent(38,0.5203);
    histo->SetBinContent(39,0.511287);
    histo->SetBinContent(40,0.511591);
    histo->SetBinContent(41,0.515752);
    histo->SetBinContent(42,0.511422);
    histo->SetBinContent(43,0.508204);
    histo->SetBinContent(44,0.508127);
    histo->SetBinContent(45,0.510974);
    histo->SetBinContent(46,0.500816);
    histo->SetBinContent(47,0.504433);
    histo->SetBinContent(48,0.505448);
    histo->SetBinContent(49,0.511641);
    histo->SetBinContent(50,0.502929);
    histo->SetBinContent(51,0.506477);
    histo->SetBinContent(52,0.503761);
    histo->SetBinContent(53,0.504223);
    histo->SetBinContent(54,0.502274);
    histo->SetBinContent(55,0.503253);
    histo->SetBinContent(56,0.503736);
    histo->SetBinContent(57,0.506377);
    histo->SetBinContent(58,0.502548);
    histo->SetBinContent(59,0.502439);
    histo->SetBinContent(60,0.498274);
    histo->SetBinContent(61,0.505038);
    histo->SetBinContent(62,0.505273);
    histo->SetBinContent(63,0.500345);
    histo->SetBinContent(64,0.501088);
    histo->SetBinContent(65,0.502575);
    histo->SetBinContent(66,0.494825);
    histo->SetBinContent(67,0.497779);
    histo->SetBinContent(68,0.493466);
    histo->SetBinContent(69,0.499111);
    histo->SetBinContent(70,0.492164);
    histo->SetBinContent(71,0.494008);
    histo->SetBinContent(72,0.497438);
    histo->SetBinContent(73,0.500674);
    histo->SetBinContent(74,0.493233);
    histo->SetBinContent(75,0.487744);
    histo->SetBinContent(76,0.497182);
    histo->SetBinContent(77,0.498035);
    histo->SetBinContent(78,0.493752);
    histo->SetBinContent(79,0.493849);
    histo->SetBinContent(80,0.499119);
    histo->SetBinContent(81,0.492812);
    histo->SetBinContent(82,0.492674);
    histo->SetBinContent(83,0.48656);
    histo->SetBinContent(84,0.493127);
    histo->SetBinContent(85,0.493494);
    histo->SetBinContent(86,0.498216);
    histo->SetBinContent(87,0.495571);
    histo->SetBinContent(88,0.491854);
    histo->SetBinContent(89,0.494278);
    histo->SetBinContent(90,0.484692);
    histo->SetBinContent(91,0.492717);
    histo->SetBinContent(92,0.492183);
    histo->SetBinContent(93,0.491312);
    histo->SetBinContent(94,0.487734);
    histo->SetBinContent(95,0.487761);
    histo->SetBinContent(96,0.483242);
    histo->SetBinContent(97,0.491057);
    histo->SetBinContent(98,0.49339);
    histo->SetBinContent(99,0.485842);
    histo->SetBinContent(100,0.485611);
    histo->SetBinContent(101,0.484576);
    histo->SetBinContent(102,0.490227);
    histo->SetBinContent(103,0.488641);
    histo->SetBinContent(104,0.493979);
    histo->SetBinContent(105,0.492614);
    histo->SetBinContent(106,0.480413);
    histo->SetBinContent(107,0.486151);
    histo->SetBinContent(108,0.490988);
    histo->SetBinContent(109,0.486638);
    histo->SetBinContent(110,0.478524);
    histo->SetBinContent(111,0.485759);
    histo->SetBinContent(112,0.473641);
    histo->SetBinContent(113,0.491854);
    histo->SetBinContent(114,0.480921);
    histo->SetBinContent(115,0.483573);
    histo->SetBinContent(116,0.487601);
    histo->SetBinContent(117,0.485269);
    histo->SetBinContent(118,0.477205);
    histo->SetBinContent(119,0.49949);
    histo->SetBinContent(120,0.483636);
    histo->SetBinContent(121,0.478502);
    histo->SetBinContent(122,0.48607);
    histo->SetBinContent(123,0.478773);
    histo->SetBinContent(124,0.484625);
    histo->SetBinContent(125,0.482706);
    histo->SetBinContent(126,0.494494);
    histo->SetBinContent(127,0.478427);
    histo->SetBinContent(128,0.497664);
    histo->SetBinContent(129,0.476652);
    histo->SetBinContent(130,0.489841);
    histo->SetBinContent(131,0.48949);
    histo->SetBinContent(132,0.481368);
    histo->SetBinContent(133,0.491934);
    histo->SetBinContent(134,0.483119);
    histo->SetBinContent(135,0.487789);
    histo->SetBinContent(136,0.477857);
    histo->SetBinContent(137,0.488571);
    histo->SetBinContent(138,0.473613);
    histo->SetBinContent(139,0.480782);
    histo->SetBinContent(140,0.489834);
    histo->SetBinContent(141,0.478261);
    histo->SetBinContent(142,0.485956);
    histo->SetBinContent(143,0.485434);
    histo->SetBinContent(144,0.476667);
    histo->SetBinContent(145,0.489487);
    histo->SetBinContent(146,0.491946);
    histo->SetBinContent(147,0.476934);
    histo->SetBinContent(148,0.480637);
    histo->SetBinContent(149,0.479429);
    histo->SetBinContent(150,0.489565);
    histo->SetBinContent(151,0.506563);
    histo->SetBinContent(152,0.469836);
    histo->SetBinContent(153,0.5);
    histo->SetBinContent(154,0.46885);
    histo->SetBinContent(155,0.471966);
    histo->SetBinContent(156,0.485455);
    histo->SetBinContent(157,0.487097);
    histo->SetBinContent(158,0.481474);
    histo->SetBinContent(159,0.499279);
    histo->SetBinContent(160,0.478367);
    histo->SetBinContent(161,0.480769);
    histo->SetBinContent(162,0.459529);
    histo->SetBinContent(163,0.476522);
    histo->SetBinContent(164,0.478431);
    histo->SetBinContent(165,0.47618);
    histo->SetBinContent(166,0.488571);
    histo->SetBinContent(167,0.481176);
    histo->SetBinContent(168,0.478028);
    histo->SetBinContent(169,0.483243);
    histo->SetBinContent(170,0.507595);
    histo->SetBinContent(171,0.473333);
    histo->SetBinContent(172,0.472258);
    histo->SetBinContent(173,0.457818);
    histo->SetBinContent(174,0.477313);
    histo->SetBinContent(175,0.477778);
    histo->SetBinContent(176,0.479733);
    histo->SetBinContent(177,0.485);
    histo->SetBinContent(178,0.466429);
    histo->SetBinContent(179,0.494545);
    histo->SetBinContent(180,0.463019);
    histo->SetBinContent(181,0.489388);
    histo->SetBinContent(182,0.481667);
    histo->SetBinContent(183,0.491724);
    histo->SetBinContent(184,0.466667);
    histo->SetBinContent(185,0.513659);
    histo->SetBinContent(186,0.511111);
    histo->SetBinContent(187,0.488571);
    histo->SetBinContent(188,0.471);
    histo->SetBinContent(189,0.485714);
    histo->SetBinContent(190,0.512222);
    histo->SetBinContent(191,0.489189);
    histo->SetBinContent(192,0.472);
    histo->SetBinContent(193,0.496471);
    histo->SetBinContent(194,0.436923);
    histo->SetBinContent(195,0.462424);
    histo->SetBinContent(196,0.488333);
    histo->SetBinContent(197,0.448966);
    histo->SetBinContent(198,0.471429);
    histo->SetBinContent(199,0.46381);
    histo->SetBinContent(200,0.487368);
  }

  double result = 1.;
  result = histo->GetBinContent(histo->FindBin(energy));
    
  delete histo;
  return result;
}


double EflowAnalyzer::GetTrackJetMCWeight(double pt, double cmenergy) {

  TH1D *histo = NULL;

  if (cmenergy == 900) {
    
    Double_t xAxis3[9] = {0.3, 1, 2, 3, 5, 7.5, 10, 15, 25};
    
    histo = new TH1D("histo","Data",8, xAxis3);
    histo->SetBinContent(1,1.027584);
    histo->SetBinContent(2,0.9685653);
    histo->SetBinContent(3,0.8513239);
    histo->SetBinContent(4,0.7601489);
    histo->SetBinContent(5,0.727091);
    histo->SetBinContent(6,0.7585068);
    histo->SetBinContent(7,0.8696197);
    histo->SetBinContent(8,0.9043195);
  } 

  else if (cmenergy == 2760) {
  
    Double_t xAxis3[9] = {0.3, 1, 2, 3, 5, 7.5, 10, 15, 25};
    
    histo = new TH1D("histo","Data",8, xAxis3);
    histo->SetBinContent(1,1.004105);
    histo->SetBinContent(2,1.01436);
    histo->SetBinContent(3,0.9700292);
    histo->SetBinContent(4,0.9026651);
    histo->SetBinContent(5,0.8482491);
    histo->SetBinContent(6,0.8326606);
    histo->SetBinContent(7,0.8461179);
    histo->SetBinContent(8,0.8716194);
  } 

  else if (cmenergy == 7000) {
  
    Double_t xAxis3[9] = {0.3, 1, 2, 3, 5, 7.5, 10, 15, 25};
    
    histo = new TH1D("histo","Data",8, xAxis3);
    histo->SetBinContent(1,0.9920999);
    histo->SetBinContent(2,1.029762);
    histo->SetBinContent(3,1.023231);
    histo->SetBinContent(4,0.9646435);
    histo->SetBinContent(5,0.8789452);
    histo->SetBinContent(6,0.8042393);
    histo->SetBinContent(7,0.7761746);
    histo->SetBinContent(8,0.8294886);
  }
 
  double result = 1.;
  result = histo->GetBinContent(histo->FindBin(pt));
    
  delete histo;
  return result;
}

 int EflowAnalyzer::GetPosLeadingGenJet(std::vector<MyGenJet> JetVector, double etacut, double minptcut) {
   
   // search for leading jets
   
   int posLeadingGenJet = -1;
   
   double ptmax = 0;
   
   for (unsigned int ijet=0;ijet<JetVector.size();ijet++) {
     
     if (JetVector[ijet].Pt() > minptcut && fabs(JetVector[ijet].Eta()) < etacut) {
       
       if (JetVector[ijet].Pt() > ptmax) {
	 
	 ptmax = JetVector[ijet].Pt();
	 posLeadingGenJet = ijet;
       }
     }
   }
   
   return posLeadingGenJet;
 }

void EflowAnalyzer::ComputeRatio(double up, double down, double error_up, double error_down, double &ratio, double &error) {
   
   ratio = 0; 
   error = 0;

   if(down != 0) {
     ratio = up/down;
     double error2 = 0;
     if(up != 0) error2 = ratio*ratio*((error_up*error_up)/(up*up) + (error_down*error_down)/(down*down));
     error = TMath::Sqrt(error2);
   }
}
 
 void EflowAnalyzer::ComputeHistoRatio(TH1D* hup, TH1D* hdown, TH1D& hratio) {
   
   for(int ibin = 1; ibin <= hup->GetNbinsX(); ibin++) {
     
     double up = hup->GetBinContent(ibin);
     double down = hdown->GetBinContent(ibin);
     
     double error_up = hup->GetBinError(ibin);
     double error_down = hdown->GetBinError(ibin);
     
     double ratio = 0;
     double error = 0;
     ComputeRatio(up,down,error_up,error_down,ratio,error);
     
     hratio.SetBinContent(ibin,ratio);
     hratio.SetBinError(ibin,error);
   }
   
 }
 
