////////////////////////////////////////////////////////// 
// This class has been automatically generated on // Tue Mar 30 14:38:57 2010 by ROOT version 5.22/00d 
// from TTree TreeAnalyzer/TreeAnalyzer 
// found on file: TreeMaker_Jan23RawReco_AllCastorRuns900GeV.root 
//////////////////////////////////////////////////////////

#ifndef TreeAnalyzer_h
#define TreeAnalyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TAxis.h"
#include <TH1D.h>
#include <fstream>
#include <TString.h>


class TreeAnalyzer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        ADC[224][6];
   Double_t        sumADC[224];
   Double_t        fC[224][6];
   Double_t        sumfC[224];
   Int_t           module[224];
   Int_t           sector[224];
   Int_t           channel[224];
   Double_t        signal[224];
   Double_t        fCsignal[224];
   Double_t        pedestalADC[224];
   Double_t        pedestalfC[224];
   Int_t           eventNum;
   Int_t           lumiBlock;
   Int_t           runNumber;
   Int_t           bunchCrossing;
   Int_t           PhysicsDeclared;
   Int_t           L1bit0;
   Int_t           L1bit36;
   Int_t           L1bit37;
   Int_t           L1bit38;
   Int_t           L1bit39;
   Int_t           L1bit40;
   Int_t           L1bit41;
   Int_t           nCaloJets;
   Int_t           nPFJets;
   Int_t           isCaloInclusive;
   Int_t           isPFInclusive;
   Int_t           isCaloDijet;
   Int_t           isPFDijet;
   Double_t        CaloJetEnergy[4];
   Double_t        CaloJetPt[4];
   Double_t        CaloJetEta[4];
   Double_t        CaloJetPhi[4];
   Double_t        PFJetEnergy[4];
   Double_t        PFJetPt[4];
   Double_t        PFJetEta[4];
   Double_t        PFJetPhi[4];
   Int_t           ProcessId;
   Double_t        PtHat;
   Int_t           nPV;
   Int_t           nTrackPV;
   Double_t        PV[3];
   Double_t        PVerr[3];
   Double_t        BS[3];
   Double_t        PVsim[3];

   // List of branches
   TBranch        *b_ADC;   //!
   TBranch        *b_sumADC;   //!
   TBranch        *b_fC;   //!
   TBranch        *b_sumfC;   //!
   TBranch        *b_module;   //!
   TBranch        *b_sector;   //!
   TBranch        *b_channel;   //!
   TBranch        *b_signal;   //!
   TBranch        *b_fCsignal;   //!
   TBranch        *b_pedestalADC;   //!
   TBranch        *b_pedestalfC;   //
   TBranch        *b_eventNum;   //!
   TBranch        *b_lumiBlock;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_bunchCrossing;   //!
   TBranch        *b_PhysicsDeclared;   //!
   TBranch        *b_L1bit0;   //!
   TBranch        *b_L1bit36;   //!
   TBranch        *b_L1bit37;   //!
   TBranch        *b_L1bit38;   //!
   TBranch        *b_L1bit39;   //!
   TBranch        *b_L1bit40;   //!
   TBranch        *b_L1bit41;   //!
   TBranch        *b_nCaloJets;   //!
   TBranch        *b_nPFJets;   //!
   TBranch        *b_isCaloInclusive;   //!
   TBranch        *b_isPFInclusive;   //!
   TBranch        *b_isCaloDijet;   //!
   TBranch        *b_isPFDijet;   //!
   TBranch        *b_CaloJetEnergy;   //!
   TBranch        *b_CaloJetPt;   //!
   TBranch        *b_CaloJetEta;   //!
   TBranch        *b_CaloJetPhi;   //!
   TBranch        *b_PFJetEnergy;   //!
   TBranch        *b_PFJetPt;   //!
   TBranch        *b_PFJetEta;   //!
   TBranch        *b_PFJetPhi;   //!
   TBranch        *b_ProcessId;   //!
   TBranch        *b_PtHat;   //!
   TBranch        *b_nPV;   //!
   TBranch        *b_nTrackPV;   //!
   TBranch        *b_PV;   //!
   TBranch        *b_PVerr;   //!
   TBranch        *b_BS;   //!
   TBranch        *b_PVsim;   //!


   TreeAnalyzer();
   virtual void GetTreeFile(TTree *tree=0, TString filename="Dummyfile.root");
   virtual ~TreeAnalyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     plotEflows(int savePlots, int log, int nModules, int cms, double HADscale,double ABSscale);
   virtual void	    plotChannelDistributions(int savePlots, int nModules,int jetsample, int cms,double HADscale,double ABSscale);
   virtual void     calculateABSscale(int savePlots, int nModules, int cms,double HADscale);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   Double_t fCfromADC(Int_t adc);  
   Double_t getRatioError(TH1D * hMB, TH1D * hQCD);
};

#endif

#ifdef TreeAnalyzer_cxx
TreeAnalyzer::TreeAnalyzer()
{
	//GetTreeFile(0,"TreeMaker_Jan23RawReco+MC_900GeV_test.root");
	fChain = 0;
}

void TreeAnalyzer::GetTreeFile(TTree *tree, TString filename)
{
	// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename.Data());
      if (!f) {
         f = new TFile(filename.Data());
      }
      tree = (TTree*)gDirectory->Get("CastorDigi");

   }
   Init(tree);


}

TreeAnalyzer::~TreeAnalyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TreeAnalyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TreeAnalyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TreeAnalyzer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("ADC", ADC, &b_ADC);
   fChain->SetBranchAddress("sumADC", sumADC, &b_sumADC);
   fChain->SetBranchAddress("fC", fC, &b_fC);
   fChain->SetBranchAddress("sumfC", sumfC, &b_sumfC);
   fChain->SetBranchAddress("module", module, &b_module);
   fChain->SetBranchAddress("sector", sector, &b_sector);
   fChain->SetBranchAddress("channel", channel, &b_channel);
   fChain->SetBranchAddress("signal", signal, &b_signal);
   fChain->SetBranchAddress("fCsignal", fCsignal, &b_fCsignal);
   fChain->SetBranchAddress("pedestalADC", pedestalADC, &b_pedestalADC);
   fChain->SetBranchAddress("pedestalfC", pedestalfC, &b_pedestalfC);
   fChain->SetBranchAddress("eventNum", &eventNum, &b_eventNum);
   fChain->SetBranchAddress("lumiBlock", &lumiBlock, &b_lumiBlock);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("bunchCrossing", &bunchCrossing, &b_bunchCrossing);
   fChain->SetBranchAddress("PhysicsDeclared", &PhysicsDeclared, &b_PhysicsDeclared);
   fChain->SetBranchAddress("L1bit0", &L1bit0, &b_L1bit0);
   fChain->SetBranchAddress("L1bit36", &L1bit36, &b_L1bit36);
   fChain->SetBranchAddress("L1bit37", &L1bit37, &b_L1bit37);
   fChain->SetBranchAddress("L1bit38", &L1bit38, &b_L1bit38);
   fChain->SetBranchAddress("L1bit39", &L1bit39, &b_L1bit39);
   fChain->SetBranchAddress("L1bit40", &L1bit40, &b_L1bit40);
   fChain->SetBranchAddress("L1bit41", &L1bit41, &b_L1bit41);
   fChain->SetBranchAddress("nCaloJets", &nCaloJets, &b_nCaloJets);
   fChain->SetBranchAddress("nPFJets", &nPFJets, &b_nPFJets);
   fChain->SetBranchAddress("isCaloInclusive", &isCaloInclusive, &b_isCaloInclusive);
   fChain->SetBranchAddress("isPFInclusive", &isPFInclusive, &b_isPFInclusive);
   fChain->SetBranchAddress("isCaloDijet", &isCaloDijet, &b_isCaloDijet);
   fChain->SetBranchAddress("isPFDijet", &isPFDijet, &b_isPFDijet);
   fChain->SetBranchAddress("CaloJetEnergy", CaloJetEnergy, &b_CaloJetEnergy);
   fChain->SetBranchAddress("CaloJetPt", CaloJetPt, &b_CaloJetPt);
   fChain->SetBranchAddress("CaloJetEta", CaloJetEta, &b_CaloJetEta);
   fChain->SetBranchAddress("CaloJetPhi", CaloJetPhi, &b_CaloJetPhi);
   fChain->SetBranchAddress("PFJetEnergy", PFJetEnergy, &b_PFJetEnergy);
   fChain->SetBranchAddress("PFJetPt", PFJetPt, &b_PFJetPt);
   fChain->SetBranchAddress("PFJetEta", PFJetEta, &b_PFJetEta);
   fChain->SetBranchAddress("PFJetPhi", PFJetPhi, &b_PFJetPhi);
   fChain->SetBranchAddress("ProcessId", &ProcessId, &b_ProcessId);
   fChain->SetBranchAddress("PtHat", &PtHat, &b_PtHat);
   fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
   fChain->SetBranchAddress("nTrackPV", &nTrackPV, &b_nTrackPV);
   fChain->SetBranchAddress("PV", PV, &b_PV);
   fChain->SetBranchAddress("PVerr", PVerr, &b_PVerr);
   fChain->SetBranchAddress("BS", BS, &b_BS);
   fChain->SetBranchAddress("PVsim", PVsim, &b_PVsim);
   Notify();
}

Bool_t TreeAnalyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TreeAnalyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TreeAnalyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TreeAnalyzer_cxx
