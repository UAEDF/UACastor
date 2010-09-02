// -*- C++ -*-
//
// Package:    ShowerLibraryChecker
// Class:      ShowerLibraryChecker
// 
/**\class ShowerLibraryChecker ShowerLibraryChecker.cc Analyzers/ShowerLibraryChecker/src/ShowerLibraryChecker.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  local user
//         Created:  Thu Jun 24 11:06:22 CEST 2010
// $Id$
//
//


// system include files
#include <memory>
#include <TROOT.h>
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"



// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "SimDataFormats/CaloHit/interface/PCaloHit.h"
#include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h"
#include "DataFormats/HcalDetId/interface/HcalCastorDetId.h"
//
// class declaration
//

class ShowerLibraryChecker : public edm::EDAnalyzer {
   public:
      explicit ShowerLibraryChecker(const edm::ParameterSet&);
      ~ShowerLibraryChecker();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      TH1D *hModules, *hSectors;
      TH1D *hModuleRatios, *hSectorRatios;
      
      TH1D * hEnergy;
      
      //TFile * file;
      TTree * CastorTree;
      
      //TBranch * simhit_energy, * simhit_module, * simhit_sector;
      
        std::vector<double> simhit_x, simhit_y, simhit_z;
  std::vector<double> simhit_eta, simhit_phi, simhit_energy;
  std::vector<int> simhit_sector, simhit_module;
  //std::vector<double> simhit_time;

  std::vector<double> *psimhit_x, *psimhit_y, *psimhit_z;
  std::vector<double> *psimhit_eta, *psimhit_phi,  *psimhit_energy;
  std::vector<int> *psimhit_sector, *psimhit_module;
  //std::vector<double> *psimhit_time;

  double simhit_etot;
      
      
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
ShowerLibraryChecker::ShowerLibraryChecker(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   
   edm::Service<TFileService> fs;
   
   //file = fs->make<TFile>("SLTree_50GeVelectron.root","RECREATE");
   
   CastorTree = fs->make<TTree>("SimHits","SimHits");   
   
    CastorTree->Branch("simhit_x","std::vector<double>",&psimhit_x);
  CastorTree->Branch("simhit_y","std::vector<double>",&psimhit_y);
  CastorTree->Branch("simhit_z","std::vector<double>",&psimhit_z);

  CastorTree->Branch("simhit_eta","std::vector<double>",&psimhit_eta);
  CastorTree->Branch("simhit_phi","std::vector<double>",&psimhit_phi);
  CastorTree->Branch("simhit_energy","std::vector<double>",&psimhit_energy);

  // CastorTree->Branch("simhit_time","std::vector<double>",&psimhit_time);
  CastorTree->Branch("simhit_sector","std::vector<int>",&psimhit_sector);
  CastorTree->Branch("simhit_module","std::vector<int>",&psimhit_module);

  CastorTree->Branch("simhit_etot",&simhit_etot,"simhit_etot/D");
   
   hModules = fs->make<TH1D>("hModules","module distribution of CASTOR simhits",14,1,15);
   hSectors = fs->make<TH1D>("hSectors","sector distribution of CASTOR simhits",16,1,17);
   
   hEnergy = fs->make<TH1D>("hEnergy","Total energy distribution of CASTOR simhits",100,0,1);
   


}


ShowerLibraryChecker::~ShowerLibraryChecker()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
   
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
ShowerLibraryChecker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   
   
   Handle<PCaloHitContainer> hits;
   iEvent.getByLabel("g4SimHits","CastorFI",hits);

   int nentries = hits->size();   
       psimhit_x=&simhit_x;
  psimhit_x->clear();
  psimhit_x->reserve(nentries);

  psimhit_y=&simhit_y;
  psimhit_y->clear();
  psimhit_y->reserve(nentries);

  psimhit_z=&simhit_z;
  psimhit_z->clear();
  psimhit_z->reserve(nentries);

  psimhit_eta=&simhit_eta;
  psimhit_eta->clear();
  psimhit_eta->reserve(nentries);
  
  psimhit_phi=&simhit_phi;
  psimhit_phi->clear();
  psimhit_phi->reserve(nentries);
  
  psimhit_energy=&simhit_energy;
  psimhit_energy->clear();
  psimhit_energy->reserve(nentries);
  
  //psimhit_time=&simhit_time;
  //psimhit_time->clear();
  //psimhit_time->reserve(nentries);
  
  psimhit_sector=&simhit_sector;
  psimhit_sector->clear();
  psimhit_sector->reserve(nentries);

  psimhit_module=&simhit_module;
  psimhit_module->clear();
  psimhit_module->reserve(nentries);

  simhit_etot = 0;

   
   double totalenergy = 0;
   
   for (size_t i=0;i<hits->size();i++) {
   	PCaloHit hit = (*hits)[i];
	HcalCastorDetId *castorid = new HcalCastorDetId(hit.id());
	int module = castorid->module();
	int sector = castorid->sector();
	
	//std::cout << "hit module = " << module << " sector = " << sector << " energy = " << hit.energy() << std::endl;
	hModules->Fill(module,hit.energy());
	hSectors->Fill(sector,hit.energy());
	totalenergy = totalenergy + hit.energy();
	
	psimhit_energy->push_back(hit.energy());
	psimhit_module->push_back(module);
	psimhit_sector->push_back(sector);
	//psimhit_eta->push_back(hit.id().eta());
	//psimhit_phi->push_back(hit.id().phi());	
   }

   hEnergy->Fill(totalenergy);
   
   simhit_etot = totalenergy;
   
   CastorTree->Fill();


#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
ShowerLibraryChecker::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ShowerLibraryChecker::endJob() {
/*
	for (int i=O;i<14;i++) {
		hModuleRatios->SetBinContent(i+1,h
	}
	*/
}

//define this as a plug-in
DEFINE_FWK_MODULE(ShowerLibraryChecker);
