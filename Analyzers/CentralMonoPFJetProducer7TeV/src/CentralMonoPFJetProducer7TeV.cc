// -*- C++ -*-
//
// Package:    CentralMonoPFJetProducer7TeV
// Class:      CentralMonoPFJetProducer7TeV
// 
/**\class CentralMonoPFJetProducer7TeV CentralMonoPFJetProducer7TeV.cc ForwardAnalysis/CentralMonoPFJetProducer7TeV/src/CentralMonoPFJetProducer7TeV.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Alexander Flossdorf,01c/271,1797,
//         Created:  Mon Apr 26 15:10:38 CEST 2010
// $Id: CentralMonoPFJetProducer7TeV.cc,v 1.1 2010/04/27 15:04:49 floss Exp $
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

class CentralMonoPFJetProducer7TeV : public edm::EDProducer {

public:

  explicit CentralMonoPFJetProducer7TeV(const edm::ParameterSet&);
  ~CentralMonoPFJetProducer7TeV();

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

  edm::Service<TFileService> fs;
  TTree* EventTree;

  int eventNum;
  int runNumber;
  int lumiBlock;
  int bunchCrossing;
  int isInclusive;
  double Ptjet;
};


//
// constructors and destructor
//

CentralMonoPFJetProducer7TeV::CentralMonoPFJetProducer7TeV(const edm::ParameterSet& iConfig)
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

  EventTree = fs->make<TTree>("CentralPFMonoJetSelection","CentralPFMonoJetSelection");
  produces<bool>("inclusive").setBranchAlias("InclusiveEvent");
}


CentralMonoPFJetProducer7TeV::~CentralMonoPFJetProducer7TeV()
{
}


//
// member functions
//

// ------------ method called on each new Event  ------------
void CentralMonoPFJetProducer7TeV::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;

  accept = false;
  Ptjet = -999;

  Handle<reco::PFJetCollection> ak5PFJets;
  iEvent.getByLabel(pfJets_,ak5PFJets);

  const JetCorrector* pfJetCorrector = JetCorrector::getJetCorrector(PFJetCorrectionService,iSetup);

  for(reco::PFJetCollection::const_iterator jet = ak5PFJets->begin(); jet < ak5PFJets->end(); ++jet) {
    reco::PFJet correctedJet = *jet; // copy orignial jet
    double scale = pfJetCorrector->correction(jet->p4());  //calculate the correction
    correctedJet.scaleEnergy(scale); // apply correction

    if(correctedJet.pt() > jetPtCut && fabs(correctedJet.eta()) < jetEtaCut) {
      if(jet->neutralHadronEnergyFraction() < nhfCutUp &&
	 jet->neutralEmEnergyFraction() < nefCutUp &&
	 jet->getPFConstituents().size() > numConstituentsCutLow) {
	  
	// inside tracker acceptance depends on CHF, CEF and Charged Multiplicity
	if(fabs(correctedJet.eta()) < 2.4) {
	  if(jet->chargedEmEnergyFraction() < cefCutUp &&
	     jet->chargedHadronEnergyFraction() > chfCutLow &&
	     jet->chargedMultiplicity() > chargedMultiplicityCutLow)
	    accept = true;	  
	}
	// outside tracker, jet accepted without CHF, CEF and Charged Multiplicity
	else
	  accept = true;
      }
    } // end if statement jet pt and jet eta

    if (accept == true) {
      Ptjet = correctedJet.pt();
      break; // leave for loop if event is already accepted
    }

  } // end for loop
    
  eventNum      = iEvent.id().event() ;
  runNumber     = iEvent.id().run() ;
  lumiBlock     = iEvent.luminosityBlock() ;
  bunchCrossing = iEvent.bunchCrossing();
  isInclusive = 0;
  if(accept) isInclusive = 1;

  EventTree->Fill();

  std::auto_ptr<bool> InclusiveEvent(new bool);
  *InclusiveEvent = accept;
  iEvent.put(InclusiveEvent,"inclusive");
}

// ------------ method called once each job just before starting event loop  ------------
void 
CentralMonoPFJetProducer7TeV::beginJob()
{
  EventTree->Branch("eventNum",&eventNum,"eventNum/I");
  EventTree->Branch("runNumber",&runNumber,"runNumber/I");
  EventTree->Branch("lumiBlock",&lumiBlock,"lumiBlock/I");
  EventTree->Branch("bunchCrossing",&bunchCrossing,"bunchCrossing/I");
  EventTree->Branch("isInclusive",&isInclusive,"isInclusive/I");
  EventTree->Branch("Ptjet",&Ptjet,"Ptjet/D");
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CentralMonoPFJetProducer7TeV::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(CentralMonoPFJetProducer7TeV);
