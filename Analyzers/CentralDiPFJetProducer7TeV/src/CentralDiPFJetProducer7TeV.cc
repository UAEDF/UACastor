// -*- C++ -*-
//
// Package:    CentralDiPFJetProducer7TeV
// Class:      CentralDiPFJetProducer7TeV
// 
/**\class CentralDiPFJetProducer7TeV CentralDiPFJetProducer7TeV.cc ForwardAnalysis/CentralDiPFJetProducer7TeV/src/CentralDiPFJetProducer7TeV.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Alexander Flossdorf,01c/271,1797,
//         Created:  Tue Apr 27 17:43:18 CEST 2010
// $Id: CentralDiPFJetProducer7TeV.cc,v 1.1 2010/06/30 13:00:10 roland Exp $
//
//

// system include files
#include <memory>
#include "TFile.h"
#include "TTree.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/JetCollection.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"

#include "DataFormats/Math/interface/deltaPhi.h"

//
// class declaration
//

class CentralDiPFJetProducer7TeV : public edm::EDProducer {

public:

  explicit CentralDiPFJetProducer7TeV(const edm::ParameterSet&);
  ~CentralDiPFJetProducer7TeV();

private:

  virtual void beginJob() ;
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
      
  // ----------member data ---------------------------

  std::string PFJetCorrectionService;
  edm::InputTag pfJets_;

  double nhfCutUp;
  double nefCutUp;
  double chfCutLow;
  double cefCutUp;
  uint32_t numConstituentsCutLow;
  int chargedMultiplicityCutLow;

  double jetPtCut;
  double jetEtaCut;

  bool accept;
  bool DoTree_;

  edm::Service<TFileService> fs;
  TTree* EventTree;

  int event;
  int run;
  int lumiblock;
  int bunchcrossing;
  int isDijet;
  double Pt1jet;
  double Pt2jet;
};


//
// constructors and destructor
//

CentralDiPFJetProducer7TeV::CentralDiPFJetProducer7TeV(const edm::ParameterSet& iConfig)
{
  PFJetCorrectionService = iConfig.getParameter<std::string>("PFJetCorrector");
  pfJets_ = iConfig.getParameter<edm::InputTag>("PFJets");

  nhfCutUp = iConfig.getParameter<double>("NHFCutUp");
  nefCutUp = iConfig.getParameter<double>("NEFCutUp");
  chfCutLow = iConfig.getParameter<double>("CHFCutLow");
  cefCutUp = iConfig.getParameter<double>("CEFCutUp");
  numConstituentsCutLow = iConfig.getParameter<int>("NumConstituentsCutLow");
  chargedMultiplicityCutLow = iConfig.getParameter<int>("ChargedMultiplicityCutLow");

  jetPtCut = iConfig.getParameter<double>("JetPtCut");
  jetEtaCut = iConfig.getParameter<double>("JetEtaCut");

  DoTree_ = iConfig.getUntrackedParameter<bool>("DoTree");

  if(DoTree_) EventTree = fs->make<TTree>("CentralPFDiJetSelection","CentralPFDiJetSelection");
  produces<bool>("dijet").setBranchAlias("DiJetEvent");
}


CentralDiPFJetProducer7TeV::~CentralDiPFJetProducer7TeV()
{
}


//
// member functions
//

// ------------ method called on each new Event  ------------
void CentralDiPFJetProducer7TeV::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;

  accept = false;
  Pt1jet = -999;
  Pt2jet = -999;

  
  Handle<reco::PFJetCollection> ak5PFJets;
  iEvent.getByLabel(pfJets_,ak5PFJets);
  
  const JetCorrector* pfJetCorrector = JetCorrector::getJetCorrector(PFJetCorrectionService,iSetup);
  
  if(ak5PFJets->size() >= 2) {

    short int posJet1 = -1;
    short int posJet2 = -1;
    double refPt1 = 0;
    double refPt2 = 0;
    
    for(reco::PFJetCollection::const_iterator jet = ak5PFJets->begin(); jet < ak5PFJets->end(); ++jet) {
      reco::PFJet correctedJet = *jet; // copy orignial jet
      double scale = pfJetCorrector->correction(jet->p4());  //calculate the correction
      correctedJet.scaleEnergy(scale); // apply correction
      
      double pt = correctedJet.pt();
      
      if(pt > refPt1) {
	refPt2 = refPt1;
	posJet2 = posJet1;
	refPt1 = pt ;
	posJet1 = jet - ak5PFJets->begin();
      }
      else if(pt > refPt2) {
	refPt2 = pt ;
	posJet2 = jet - ak5PFJets->begin();
      }
    } // end jet for loop
    
    if(posJet1 >= 0 && posJet2 >= 0) {  
      reco::PFJet jet1 = ak5PFJets->at(posJet1);
      reco::PFJet correctedJet1 = ak5PFJets->at(posJet1);
      double scale1 = pfJetCorrector->correction(jet1.p4());  //calculate the correction
      correctedJet1.scaleEnergy(scale1); // apply correction
      
      reco::PFJet jet2 = ak5PFJets->at(posJet2);
      reco::PFJet correctedJet2 = ak5PFJets->at(posJet2);
      double scale2 = pfJetCorrector->correction(jet2.p4());  //calculate the correction
      correctedJet2.scaleEnergy(scale2); // apply correction
      
      bool acceptJet1 = false;
      bool acceptJet2 = false;
      
      if(correctedJet1.pt() > jetPtCut && fabs(correctedJet1.eta()) < jetEtaCut) {
	if(jet1.neutralHadronEnergyFraction() < nhfCutUp &&
	   jet1.neutralEmEnergyFraction() < nefCutUp &&
	   jet1.getPFConstituents().size() > numConstituentsCutLow) {
	  
	  // inside tracker acceptance depends on CHF, CEF and Charged Multiplicity
	  if(fabs(correctedJet1.eta()) < 2.4) {
	    if(jet1.chargedEmEnergyFraction() < cefCutUp &&
	       jet1.chargedHadronEnergyFraction() > chfCutLow &&
	       jet1.chargedMultiplicity() > chargedMultiplicityCutLow)
	      acceptJet1 = true;
	  }
	  // outside tracker, jet accepted without CHF, CEF and Charged Multiplicity
	  else
	    acceptJet1 = true;
	}
      } // end if statement jet 1
      
      if(correctedJet2.pt() > jetPtCut && fabs(correctedJet2.eta()) < jetEtaCut) {
	if(jet2.neutralHadronEnergyFraction() < nhfCutUp &&
	   jet2.neutralEmEnergyFraction() < nefCutUp &&
	   jet2.getPFConstituents().size() > numConstituentsCutLow) {
	  
	  // inside tracker acceptance depends on CHF, CEF and Charged Multiplicity
	  if(fabs(correctedJet2.eta()) < 2.4) {
	    if(jet2.chargedEmEnergyFraction() < cefCutUp &&
	       jet2.chargedHadronEnergyFraction() > chfCutLow &&
	       jet2.chargedMultiplicity() > chargedMultiplicityCutLow)
	      acceptJet2 = true;
	  }
	  // outside tracker, jet accepted without CHF, CEF and Charged Multiplicity
	  else
	    acceptJet2 = true;
	}
      } // end if statement jet 2
      
      if(acceptJet1 == true && acceptJet2 == true) {
	double deltaPhi = fabs(reco::deltaPhi(jet1.phi(), jet2.phi()));
	if (fabs(deltaPhi - M_PI) < 1.0) {
	  accept = true;
	  Pt1jet = correctedJet1.pt();
	  Pt2jet = correctedJet2.pt();
	}
      }
    } // end if(posJet1 >= 0 && posJet2 >= 0)  
  } // end if(ak5PFJets->size() >= 2)

  event = iEvent.id().event() ;
  run = iEvent.id().run() ;
  lumiblock = iEvent.luminosityBlock() ;
  bunchcrossing = iEvent.bunchCrossing();

  isDijet = 0;
  if(accept) isDijet = 1;

  if(DoTree_) EventTree->Fill();

  std::auto_ptr<bool> DiJetEvent(new bool);
  *DiJetEvent = accept;
  iEvent.put(DiJetEvent,"dijet");
}

// ------------ method called once each job just before starting event loop  ------------
void 
CentralDiPFJetProducer7TeV::beginJob()
{
  if(DoTree_) EventTree->Branch("event",&event,"event/I");
  if(DoTree_) EventTree->Branch("run",&run,"run/I");
  if(DoTree_) EventTree->Branch("lumiblock",&lumiblock,"lumiblock/I");
  if(DoTree_) EventTree->Branch("bunchcrossing",&bunchcrossing,"bunchcrossing/I");
  if(DoTree_) EventTree->Branch("isDijet",&isDijet,"isDijet/I");
  if(DoTree_) EventTree->Branch("Pt1jet",&Pt1jet,"Pt1jet/D");
  if(DoTree_) EventTree->Branch("Pt2jet",&Pt2jet,"Pt2jet/D");
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CentralDiPFJetProducer7TeV::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(CentralDiPFJetProducer7TeV);

