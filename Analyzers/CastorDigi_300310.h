//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar 11 16:42:26 2010 by ROOT version 5.22/00d
// from TTree CastorDigi/CastorDigi
// found on file: TreeMaker_Jan23RawReco_900+2360GeV.root
//////////////////////////////////////////////////////////

#ifndef CastorDigi_h
#define CastorDigi_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TAxis.h"
#include <TH1D.h>
#include <fstream>

class CastorDigi {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   
   Int_t PFDijetList[531][3];
   Int_t CaloDijetList[246][3];
   Int_t PFInclusiveList[2088][3];
   Int_t CaloInclusiveList[459][3];

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
   Double_t        pedestal[224];
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
   TBranch        *b_pedestal;   //!
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

   CastorDigi(TTree *tree=0, TString filename="TreeMaker_Jan23RawReco+MC_900+2360GeV.root");
   virtual ~CastorDigi();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(int range,int useList,double minhistrange900,double histrange900,double minhistrange2360,double
   histrange2360, int usefC, int convertfC, double fCscale);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   Double_t fCfromADC(Int_t adc);
   Double_t getRatioError(TH1D * hMB, TH1D * hQCD);
};

#endif

#ifdef CastorDigi_cxx
CastorDigi::CastorDigi(TTree *tree, TString filename)
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
	
	// copy PF Dijet event list into array
	std::ifstream myfile1("philipp_pfdijets.txt");
	if (myfile1.is_open())
	{
		int i=0;
		while (! myfile1.eof() )
		{
			string line;
			getline (myfile1,line);
			//std::cout << line << endl;
			char * cstr, *p;
			cstr = new char [line.size()+1];
			strcpy (cstr, line.c_str());
			// cstr now contains a c-string copy of str
			p=strtok (cstr,":");
			int j=0;
			while (p!=NULL)
			{
				//std::cout << p << endl;
				PFDijetList[i][j] = atoi(p);
				p=strtok(NULL,":");
				j++;
			}
			delete[] cstr;
			i++;
			
		}
		myfile1.close();
	} else std::cout << "Unable to open file";
	
	// copy Calo Dijet event list into array
	ifstream myfile2 ("philipp_calodijets.txt");
	if (myfile2.is_open())
	{
		int i=0;
		while (! myfile2.eof() )
		{
			string line;
			getline (myfile2,line);
			//std::cout << line << endl;
			char * cstr, *p;
			cstr = new char [line.size()+1];
			strcpy (cstr, line.c_str());
			// cstr now contains a c-string copy of str
			p=strtok (cstr,":");
			int j=0;
			while (p!=NULL)
			{
				//std::cout << p << endl;
				CaloDijetList[i][j] = atoi(p);
				p=strtok(NULL,":");
				j++;
			}
			delete[] cstr;
			i++;
			
		}
		myfile2.close();
	} else std::cout << "Unable to open file";
	
	// copy PF inclusive event list into array
	ifstream myfile3 ("Niki_inclusivePFjets.txt");
	if (myfile3.is_open())
	{
		int i=0;
		while (i<2088 )
		{
			string line;
			getline (myfile3,line);
			//std::cout << line << endl;
			char * cstr, *p;
			cstr = new char [line.size()+1];
			strcpy (cstr, line.c_str());
			// cstr now contains a c-string copy of str
			p=strtok (cstr," ");
			int j=0;
			while (j<6)
			{
				//std::cout << j << p << endl;
				if (j==1) PFInclusiveList[i][0] = atoi(p);
				if (j==3) PFInclusiveList[i][1] = atoi(p);
				if (j==5) PFInclusiveList[i][2] = atoi(p);
				p=strtok(NULL," ");
				j++;
			}
			delete[] cstr;
			i++;
			
		}
		myfile3.close();
	} else std::cout << "Unable to open file";
 	
	// copy Calo inclusive event list into array
	ifstream myfile4 ("Kostas_inclusiveCalojets.txt");
	if (myfile4.is_open())
	{
		int i=0;
		while (i<418 )
		{
			string line;
			getline (myfile4,line);
			//std::cout << line << endl;
			char * cstr, *p;
			cstr = new char [line.size()+1];
			strcpy (cstr, line.c_str());
			// cstr now contains a c-string copy of str
			p=strtok (cstr," ");
			int j=0;
			while (j<4)
			{
				//std::cout << j << p << endl;
				if (j==0) PFInclusiveList[i][0] = atoi(p);
				if (j==1) PFInclusiveList[i][2] = atoi(p);
				if (j==2) PFInclusiveList[i][1] = atoi(p);
				p=strtok(NULL," ");
				j++;
			}
			delete[] cstr;
			i++;
			
		}
		myfile4.close();
	} else std::cout << "Unable to open file";
	
	
	/*
	 for (int k=0;k<531;k++) {
		 std::cout << k+1 << " Run = " << PFDijets[k][0] << " Lumi = " << PFDijets[k][1] << " Event = " << PFDijets[k][2] << endl;
	 }
	 for (int k=0;k<246;k++) {
		 std::cout << k+1 << " Run = " << CaloDijets[k][0] << " Lumi = " << CaloDijets[k][1] << " Event = " << CaloDijets[k][2] << endl;
	 }
	 */
	
	std::cout << "Constructed the EventList, you can use it now" << endl;
}

CastorDigi::~CastorDigi()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t CastorDigi::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t CastorDigi::LoadTree(Long64_t entry)
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

void CastorDigi::Init(TTree *tree)
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
   fChain->SetBranchAddress("pedestal", pedestal, &b_pedestal);
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
   Notify();
}

Bool_t CastorDigi::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void CastorDigi::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t CastorDigi::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}


#endif // #ifdef CastorDigi_cxx
