//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jun 25 17:05:52 2010 by ROOT version 5.22/00d
// from TTree SimHits/SimHits
// found on file: SLTree_50GeVelectron_FS+SL.root
//////////////////////////////////////////////////////////

#ifndef SimHits_h
#define SimHits_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class SimHits {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   vector<double>  *simhit_x;
   vector<double>  *simhit_y;
   vector<double>  *simhit_z;
   vector<double>  *simhit_eta;
   vector<double>  *simhit_phi;
   vector<double>  *simhit_energy;
   vector<int>     *simhit_sector;
   vector<int>     *simhit_module;
   Double_t        simhit_etot;

   // List of branches
   TBranch        *b_simhit_x;   //!
   TBranch        *b_simhit_y;   //!
   TBranch        *b_simhit_z;   //!
   TBranch        *b_simhit_eta;   //!
   TBranch        *b_simhit_phi;   //!
   TBranch        *b_simhit_energy;   //!
   TBranch        *b_simhit_sector;   //!
   TBranch        *b_simhit_module;   //!
   TBranch        *b_simhit_etot;   //!

   SimHits(TTree *tree=0);
   virtual ~SimHits();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   double           CalculateRatioError(double ratio,double nominator,double denominator, double error_nominator,double error_denominator);
   virtual void     Loop();
   virtual void     CalculateScaling();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef SimHits_cxx
SimHits::SimHits(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("./goodfiles/SLTree_1-50GeVpion_FullSim_10000_SG_2_ShowerShape.root");
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("./Electrons/SLTree_5-45GeVelectron_FS+SL50ME_10000_etaphirange.root");
      if (!f) {
         //f = new TFile("./goodfiles/SLTree_1-50GeVpion_FullSim_10000_SG_2_ShowerShape.root");
         f = new TFile("./Electrons/SLTree_5-45GeVelectron_FS+SL50ME_10000_etaphirange.root");
      }
      tree = (TTree*)gDirectory->Get("SimHits");

   }
   Init(tree);
}

SimHits::~SimHits()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SimHits::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SimHits::LoadTree(Long64_t entry)
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

void SimHits::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   simhit_x = 0;
   simhit_y = 0;
   simhit_z = 0;
   simhit_eta = 0;
   simhit_phi = 0;
   simhit_energy = 0;
   simhit_sector = 0;
   simhit_module = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("simhit_x", &simhit_x, &b_simhit_x);
   fChain->SetBranchAddress("simhit_y", &simhit_y, &b_simhit_y);
   fChain->SetBranchAddress("simhit_z", &simhit_z, &b_simhit_z);
   fChain->SetBranchAddress("simhit_eta", &simhit_eta, &b_simhit_eta);
   fChain->SetBranchAddress("simhit_phi", &simhit_phi, &b_simhit_phi);
   fChain->SetBranchAddress("simhit_energy", &simhit_energy, &b_simhit_energy);
   fChain->SetBranchAddress("simhit_sector", &simhit_sector, &b_simhit_sector);
   fChain->SetBranchAddress("simhit_module", &simhit_module, &b_simhit_module);
   fChain->SetBranchAddress("simhit_etot", &simhit_etot, &b_simhit_etot);
   Notify();
}

Bool_t SimHits::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SimHits::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t SimHits::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef SimHits_cxx
