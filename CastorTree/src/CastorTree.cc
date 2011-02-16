//-- system include files
#include <memory>
#include <string>
#include <iostream>
   
//-- user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "UACastor/CastorTree/interface/CastorTree.h"

//c int nEvtCut_ALL      = 0 ;
//c int nEvtCut_L1Common = 0 ;
//c int nEvtCut_L1Mult   = 0 ;
//c int nEvtCut_HLTMult  = 0 ;
//c int nEvtCut_HF       = 0 ;
//c int nEvtCut_VTX      = 0 ;
//c int nEvtCut_Ntracks  = 0 ;


CastorTree::CastorTree(const edm::ParameterSet& iConfig) {
  
  //-- do what ever initialization is needed

  rnd = new TRandom3();
  
  //-- Modules to execute 
  StoreGenKine = iConfig.getParameter<bool>("StoreGenKine");
  StoreGenPart = iConfig.getParameter<bool>("StoreGenPart");
  StoreCastorDigi = iConfig.getParameter<bool>("StoreCastorDigi");
  StoreCastorJet = iConfig.getParameter<bool>("StoreCastorJet");

  //-- define Collection
  genPartColl_ = iConfig.getParameter<edm::InputTag>("genPartColl");
  hepMCColl_ = iConfig.getParameter<edm::InputTag>("hepMCColl");

  L1GT_TrigMenuLite_Prov_ = iConfig.getParameter<bool>("L1GT_TrigMenuLite_Prov");
  L1GT_TrigMenuLite_ = iConfig.getParameter<edm::InputTag>("L1GT_TrigMenuLite");
  L1GT_ObjectMap_ = iConfig.getParameter<edm::InputTag>("L1GT_ObjectMap");

  CastorDigiColl_ = iConfig.getParameter<edm::InputTag>("CastorDigiColl");
  CastorRecHitColl_ = iConfig.getParameter<edm::InputTag>("CastorRecHitColl");
  BasicJet_ = iConfig.getParameter<edm::InputTag>("BasicJet");
  CastorJetID_ = iConfig.getParameter<edm::InputTag>("CastorJetID");
 
  PFJetColl_ = iConfig.getParameter<edm::InputTag>("PFJetColl");
  CaloJetColl_ = iConfig.getParameter<edm::InputTag>("CaloJetColl");
  CaloJetId_ = iConfig.getParameter<edm::InputTag>("CaloJetId");

  //-- needed to retrieve JEC
  PFJetJEC_ = iConfig.getParameter<string>("PFJetJEC");
  CaloJetJEC_ = iConfig.getParameter<string>("CaloJetJEC");

  //-- needed to retrieve JEC uncertainty
  PFJetJECunc_ = iConfig.getParameter<string>("PFJetJECunc");
  CaloJetJECunc_ = iConfig.getParameter<string>("CaloJetJECunc");

  //-- central jet selection
  ParaSetTightPFJetID_ = iConfig.getParameter<edm::ParameterSet>("TightPFJetID_Parameters");
  ParaSetLooseCaloJetID_ = iConfig.getParameter<edm::ParameterSet>("LooseCaloJetID_Parameters");
  ParaSetTightCaloJetID_ = iConfig.getParameter<edm::ParameterSet>("TightCaloJetID_Parameters");
  jetPtCut_ = iConfig.getParameter<double>("JetPtCut");
  jetEtaCut_ = iConfig.getParameter<double>("JetEtaCut");

  //-- HLT triggers requested by user
  hlt_bits = iConfig.getParameter<vector<string> >("requested_hlt_bits");

  //-- needed to retrieve HLT triggers
  isValidHLTConfig_ = false;
}


CastorTree::~CastorTree() {
   //-- do anything here that needs to be done at destruction time
   //-- e.g. close files, deallocate resources etc.
}


//-- member functions

//-- method called to for each event
void CastorTree::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
   
  using namespace edm;
  
  //-- General Information
  GetEvtId(iEvent);
  GetL1Trig(iEvent,iSetup);
  GetHLTrig(iEvent,iSetup);
  
  //-- MC Information
  if(StoreGenKine) GetGenKin(iEvent);
  if(StoreGenPart) GetGenPart(iEvent,iSetup);

  //-- Reco Vertex Information
  GetBeamSpot(iEvent);
  GetRecoVertex(iEvent,"offlinePrimaryVertices",primaryVertex);

  //-- Castor Information
  if(StoreCastorDigi) GetCastorDigi(iEvent,iSetup,castorDigi);
  GetCastorRecHit(iEvent,castorRecHit);
  nCastorJet = 0;
  if(StoreCastorJet) GetCastorJet(iEvent,castorJet);
  
  //-- Central Jet Information
  nPFJet = 0;
  GetRecoPFJet(iEvent,iSetup,pfJet);
  GetCentralPFDiJet(pfJet,pfDiJet);

  nCaloJet = 0;
  GetRecoCaloJet(iEvent,iSetup,caloJet);
  GetCentralCaloDiJet(caloJet,caloDiJet);

  /* benoit
     
   // Event Selection (DATA ONLY) 
   bool badEvent = false;
   if ( EvtId.IsData ) { 

     ++nEvtCut_ALL;

     // ... Common Trigger selection: VETO + PhysBit
      if( ! (    !L1Trig.TechTrigWord[36]
              && !L1Trig.TechTrigWord[37]
              && !L1Trig.TechTrigWord[38]
              && !L1Trig.TechTrigWord[39] ) )  badEvent = true; 
//            &&  L1Trig.TechTrigWord[0]  ) )  badEvent = true;

     if ( ! badEvent ) ++nEvtCut_L1Common;

     // L1 Multiplicity
     if ( ! ( L1Trig.PhysTrigWord[124] || L1Trig.PhysTrigWord[63] ) ) badEvent = true;

     if ( ! badEvent ) ++nEvtCut_L1Mult;

     // HLT Multiplicity
     if ( ! (    HLTrig.HLTmap["HLT_L1_BscMinBiasOR_BptxPlusORMinus"] 
              || HLTrig.HLTmap["HLT_PixelTracks_Multiplicity40"]
              || HLTrig.HLTmap["HLT_PixelTracks_Multiplicity70"]
              || HLTrig.HLTmap["HLT_PixelTracks_Multiplicity85"]
	      || HLTrig.HLTmap["HLT_MinBiasPixel_SingleTrack"]    ) ) badEvent = true;
  
     if ( ! badEvent ) ++nEvtCut_HLTMult;

     // Vertex Cut
     bool goodVtx = false ;
     double vtxz_cut = 30.;
     for(vector<MyVertex>::iterator itvtx=primaryVertex.begin();itvtx!=primaryVertex.end();++itvtx){
       if(itvtx->validity && fabs(itvtx->z)<vtxz_cut && itvtx->ntracks>0 ) goodVtx = true;
     }

     if ( ! goodVtx ) badEvent = true;

     if ( ! badEvent ) ++nEvtCut_VTX;

   } // End of Event Selection 

   if ( ! badEvent ) tree->Fill();
   // tree->Fill(); 
   */ // benoit
   tree->Fill();
}

//-- method called once each job just before starting the event loop 
void CastorTree::beginJob() {

  tree = fs->make<TTree>("CastorTree","CastorTree");

  //c add store flag in front of tree branch

  //-- General Information
  tree->Branch("EvtId",&EvtId);
  tree->Branch("L1Trig",&L1Trig);
  tree->Branch("HLTrig",&HLTrig);

  //-- MC Information
  if(StoreGenKine) tree->Branch("GenKin",&GenKin);
  if(StoreGenPart) tree->Branch("GenPart",&GenPart);
  if(StoreGenPart) tree->Branch("simVertex",&simVertex);

  //-- Reco Vertex Information
  tree->Branch("beamSpot",&beamSpot);
  tree->Branch("primaryVertex",&primaryVertex);  

  //-- Castor Information
  tree->Branch("castorDigi",&castorDigi);
  tree->Branch("castorRecHit",&castorRecHit);
  tree->Branch("castorJet",&castorJet);
  tree->Branch("nCastorJet",&nCastorJet,"nCastorJet/I");

  //-- Central Jet Information 
  tree->Branch("pfJet",&pfJet);
  tree->Branch("nPFJet",&nPFJet,"nPFJet/I");

  tree->Branch("caloJet",&caloJet);
  tree->Branch("nCaloJet",&nCaloJet,"nCaloJet/I");

  tree->Branch("pfDiJet",&pfDiJet);
  tree->Branch("caloDiJet",&caloDiJet);
}


//-- method called to for each run
void CastorTree::beginRun(edm::Run const & iRun, edm::EventSetup const& iSetup){
  using namespace std;
  using namespace edm;

  bool changed = true;
  isValidHLTConfig_ = hltConfig.init(iRun,iSetup,"HLT",changed);
}



//-- method called once each job just after ending the event loop
void CastorTree::endJob() {

  //c  cout << " Events Passing cuts: "   << endl;
  //c  cout << " ******************** "   << endl;
  //c  cout << " ALL      = " << nEvtCut_ALL      << endl;
  //c  cout << " L1Common = " << nEvtCut_L1Common << endl;
  //c  cout << " L1Mult   = " << nEvtCut_L1Mult   << endl;
  //c  cout << " HLTMult  = " << nEvtCut_HLTMult  << endl;
  //c  cout << " VTX      = " << nEvtCut_VTX      << endl;

  //c fout->Write() ;
  //c fout->Close() ;

}

//define this as a plug-in
DEFINE_FWK_MODULE(CastorTree);
