#ifndef __CastorTree_H__
#define __CastorTree_H__

//-- class          : CastorTree
//-- Description    : Castor Analysis

//-- system include files
#include <string>
#include <vector>

using namespace std;

//-- ROOT
#include "TFile.h"
#include "TTree.h"
#include <TRandom3.h>

//-- CMSSW Include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

//-- Trigger
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "./MyPart.h"

//-- EvtId and trigger
#include "./MyEvtId.h"
#include "./MyL1Trig.h"
#include "./MyHLTrig.h"

//-- Gen Objects
#include "./MyGenKin.h"
#include "./MyGenPart.h"
#include "./MyGenJet.h"

//-- vertex
#include "./MyBeamSpot.h"
#include "./MyVertex.h"
#include "./MySimVertex.h"

//-- Jets
#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "./MyJet.h"
#include "./MyTrackJet.h"
#include "./MyDiJet.h"

//-- Castor 
#include "./MyCastorDigi.h"
#include "./MyCastorRecHit.h"
#include "./MyCastorTower.h"
#include "./MyCastorJet.h"

//-- Calotower
#include "./MyCaloTower.h"

//-- some constants

//-- class declaration

class CastorTree : public edm::EDAnalyzer {
  
 public:
  
  explicit CastorTree(const edm::ParameterSet&);
  ~CastorTree();
  
 private:
  
  virtual void beginJob() ;
  virtual void beginRun(edm::Run const &,edm::EventSetup const&) ;
  virtual void analyze(const edm::Event&,const edm::EventSetup&);
  virtual void endJob() ;
  
  //-- functions

  virtual void GetEvtId(const edm::Event&);
  virtual void GetL1Trig(const edm::Event&, const edm::EventSetup&);
  virtual void GetHLTrig(const edm::Event&, const edm::EventSetup&);
  bool hasFired(const std::string& triggerName, const edm::TriggerNames& triggerNames, const edm::TriggerResults& triggerResults) const;
  
  virtual void GetGenKin(const edm::Event&);
  virtual void GetGenPart(const edm::Event&, const edm::EventSetup&);      
  virtual void FillGenPart(const reco::GenParticle&, MyGenPart&);
  virtual void GetGenJet(const edm::Event&, const edm::InputTag&, vector<MyGenJet>&);
  
  virtual void GetRecoVertex(const edm::Event&, const char[60], vector<MyVertex>&); 
  virtual void GetBeamSpot(const edm::Event&);
  
  virtual void GetCastorDigi(const edm::Event&, const edm::EventSetup&, vector<MyCastorDigi>&);
  virtual void GetCastorRecHit(const edm::Event&, vector<MyCastorRecHit>&);
  virtual void GetCastorTower(const edm::Event&, vector<MyCastorTower>&);
  virtual void GetCastorJet(const edm::Event&, vector<MyCastorJet>&);

  virtual void GetRecoPFJet(const edm::Event&, const edm::EventSetup&, vector<MyJet>&);
  Bool_t GetTightPFJetId(const MyJet&);
  void GetCentralPFDiJet(const vector<MyJet>&, MyDiJet&);
  
  virtual void GetRecoCaloJet(const edm::Event&, const edm::EventSetup&, vector<MyJet>&);
  Bool_t GetLooseCaloJetId(const MyJet&);
  Bool_t GetTightCaloJetId(const MyJet&);
  void GetCentralCaloDiJet(const vector<MyJet>&, MyDiJet&);

  virtual void GetRecoTrackJet(const edm::Event&, const edm::EventSetup&, vector<MyTrackJet>&);

  void GetCaloTower(const edm::Event&, vector<MyCaloTower>&);

  void CheckPtSorting(vector<MyJet>&);
  void CheckPtSorting(vector<MyTrackJet>&);

  //-- Modules to execute

  bool StoreGenKine;
  bool StoreGenPart;
  bool StoreGenJet;
  bool StoreCastorDigi;
  bool StoreCastorJet;

  //-- Collection to retrieve

  edm::InputTag hepMCColl_;
  edm::InputTag genPartColl_;

  bool L1GT_TrigMenuLite_Prov_;
  edm::InputTag L1GT_TrigMenuLite_;
  edm::InputTag L1GT_ObjectMap_;

  edm::InputTag CastorDigiColl_;
  edm::InputTag CastorRecHitColl_;
  edm::InputTag CastorTower_;
  edm::InputTag BasicJet_;
  edm::InputTag CastorJetID_;

  edm::InputTag PFJetColl_;
  edm::InputTag CaloJetColl_;
  edm::InputTag CaloJetId_;
  edm::InputTag GenJetColl_;
  
  edm::InputTag TrackJetColl_;
  edm::InputTag ChargedGenJetColl_;

  //-- needed to retrieve JEC
  std::string PFJetJEC_;
  std::string CaloJetJEC_;
  std::string TrackJetJEC_;

  //-- needed to retrieve JEC uncertainty
  std::string PFJetJECunc_;
  std::string CaloJetJECunc_;
  std::string TrackJetJECunc_;

  //-- central jet selection
  edm::ParameterSet ParaSetTightPFJetID_;
  edm::ParameterSet ParaSetLooseCaloJetID_;
  edm::ParameterSet ParaSetTightCaloJetID_;
  double jetPtCut_; 
  double jetEtaCut_; 

  edm::InputTag CaloTower_;

  //-- HLT triggers requested by user
  vector<string> hlt_bits;
  vector<string> filter_bits;

  //-- needed to retrieve HLT triggers
  HLTConfigProvider hltConfig;
  bool isValidHLTConfig_;

  //-- collection to read Filter results
  edm::InputTag FilterResults_;

  //-- Tree & File

  edm::Service<TFileService> fs;
  TTree* tree;

  //-- General Information
  MyEvtId  EvtId;
  MyL1Trig L1Trig; 
  MyHLTrig HLTrig;

  //-- MC Information
  MyGenKin GenKin;
  vector<MyGenPart> GenPart;
  MySimVertex simVertex;
  vector<MyGenJet> GenJet;
  vector<MyGenJet> ChargedGenJet;

  //-- Reco Vertex Information
  MyBeamSpot beamSpot;
  vector<MyVertex> primaryVertex;     
 
  //-- Castor Information
  vector<MyCastorDigi> castorDigi;
  vector<MyCastorRecHit> castorRecHit;
  vector<MyCastorTower> castorTower;
  vector<MyCastorJet> castorJet;

  //-- Central Jet Information
  vector<MyJet> pfJet;
  vector<MyJet> caloJet;
  vector<MyTrackJet> trackJet;
  MyDiJet pfDiJet;
  MyDiJet caloDiJet;


  //-- CaloTower Information
  vector<MyCaloTower> caloTower;
 
};

#endif

