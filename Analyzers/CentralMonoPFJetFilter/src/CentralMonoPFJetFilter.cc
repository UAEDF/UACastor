// -*- C++ -*-
//
// Package:    CentralMonoPFJetProducer
// Class:      CentralMonoPFJetProducer
// 
/**\class CentralMonoPFJetProducer CentralMonoPFJetProducer.cc ForwardAnalysis/CentralMonoPFJetProducer/src/CentralMonoPFJetProducer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Alexander Flossdorf,01c/159,1797,
//         Created:  Wed Mar  3 14:13:17 CET 2010
// $Id: CentralMonoPFJetFilter.cc,v 1.2 2010/04/14 22:04:25 roland Exp $
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

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "L1Trigger/L1ExtraFromDigis/interface/L1ExtraParticleMapProd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"

#include "DataFormats/Math/interface/deltaPhi.h"

#include "FWCore/ServiceRegistry/interface/Service.h"


//
// class declaration
//

class CentralMonoPFJetProducer : public edm::EDProducer {
public:
  explicit CentralMonoPFJetProducer(const edm::ParameterSet&);
  ~CentralMonoPFJetProducer();

private:
  virtual void beginJob() ;
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
      
  // ----------member data ---------------------------
  std::string PFJetCorrectionService;

  edm::InputTag hlTriggerResults_;
  edm::TriggerNames triggerNames_;
  edm::InputTag m_l1ParticleMap_;
  edm::InputTag particleMapSource_;
  edm::InputTag pfJets_;
  edm::InputTag vertices_;
  edm::InputTag l1Trigger_;

  bool monoJetEvent;
  int result;
  
   edm::Service<TFileService> fs;
  TTree* EventTree;

	int eventNum;
	int lumiBlock;
	int runNumber;
	int bunchCrossing;
	int isInclusive;
};


//
// constructors and destructor
//
CentralMonoPFJetProducer::CentralMonoPFJetProducer(const edm::ParameterSet& iConfig)
{
  PFJetCorrectionService = iConfig.getParameter<std::string>("PFJetCorrector");
  hlTriggerResults_ = iConfig.getParameter<edm::InputTag>("HLTriggerResults");
  pfJets_ = iConfig.getParameter<edm::InputTag>("PFJets");
  vertices_ = iConfig.getParameter<edm::InputTag>("Vertices");
  l1Trigger_ = iConfig.getParameter<edm::InputTag>("L1Trigger");
  
  EventTree = fs->make<TTree>("CentralPFMonoJetSelection","CentralPFMonoJetSelection");
  produces<bool>("inclusive").setBranchAlias("theResult_inclusive");
}


CentralMonoPFJetProducer::~CentralMonoPFJetProducer()
{
}


//
// member functions
//

// ------------ method called on each new Event  ------------
void CentralMonoPFJetProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;


  monoJetEvent = false;
  result = -2;

  // ##############################
  // Handles
  // ##############################

  edm::Handle<TriggerResults> hlTriggers;
  iEvent.getByLabel(hlTriggerResults_, hlTriggers);

  edm::Handle<L1GlobalTriggerReadoutRecord> L1GTRR;
  edm::Handle<L1GlobalTriggerObjectMapRecord> L1GTOMRec;
  iEvent.getByLabel(l1Trigger_, L1GTRR);

  Handle<reco::VertexCollection> vertices;
  iEvent.getByLabel(vertices_, vertices);

  Handle<reco::PFJetCollection> ak5PFJets;
  iEvent.getByLabel(pfJets_, ak5PFJets);


  const JetCorrector* pfJetCorrector = JetCorrector::getJetCorrector(PFJetCorrectionService,iSetup);


  // ##############################
  // Triggers
  // ##############################

 if (iEvent.id().run() == 1) {
  	// MC: do nothing with HLT_PhysicsDeclared
	//-- cout << "this is MC, doing nothing with HLT_PhysicsDeclared in jet selector" << endl;
  } else {
  
  // HLT
  if(hlTriggers.failedToGet()) {
    LogError("HLTriggerError") << "Failed to get trigger results";
    exit(1);
  }
  else {
    TriggerNames triggerName;
    //-- triggerName.init(*hlTriggers);

    if(triggerName.triggerName(116) == "HLT_PhysicsDeclared") {
      bool trigAccept = hlTriggers.product()->accept(116);
      if(trigAccept == true)
        result = -1;
      else
        result = 0;
    }
    else {
      LogError("HLTriggerError") << "Wrong assignment of trigger postion to HLT_PhyscisDeclared";
      const unsigned short int numTriggers = triggerName.size();
      LogDebug("HLTriggerDebug") << "Number of HLTriggers: " << numTriggers;
      for(unsigned short int trig = 0; trig < numTriggers; ++trig) {
        if(triggerName.triggerName(trig) == "HLT_PhysicsDeclared") {
          LogInfo("HLTriggerInfo") << "HLT_PhysicsDeclared trigger found at position " << trig;
          bool trigAccept = hlTriggers.product()->accept(trig);
          if(trigAccept == true)
            result = -1;
          else
            result = 0;
        }
      } // end for
    } // end else
    if(result == -2)
      LogError("HLTriggerError") << "No HLT_PhysicsDeclared trigger found. Something went terribly wrong.";
  } // end trigger.failedToGet()
  }


  // L1
  if(result != 0) {
    int L1TechnicalTriggers[64];

    iEvent.getByLabel(InputTag("hltL1GtObjectMap::HLT"), L1GTOMRec);
    if (L1GTRR.isValid()) {
      DecisionWord gtDecisionWord = L1GTRR->decisionWord();
      const TechnicalTriggerWord&  technicalTriggerWordBeforeMask = L1GTRR->technicalTriggerWord();
      const unsigned int numberTechnicalTriggerBits(technicalTriggerWordBeforeMask.size());
      for (unsigned int iBit = 0; iBit < numberTechnicalTriggerBits; ++iBit) {
        int techTrigger = (int) technicalTriggerWordBeforeMask.at(iBit);
        L1TechnicalTriggers[iBit] = techTrigger;
      }
    }
    else {
      LogError("L1Debug") << "Trigger L1 is not valid: " << L1GTRR.isValid();
      exit(1);
    }

   if (iEvent.id().run() == 1) {
    	if (L1TechnicalTriggers[40] == 1 || L1TechnicalTriggers[41] == 1 )
      	{;}
    	else {
      	result = 0;
	}
    
    } else {
    	if (L1TechnicalTriggers[0] == 1 &&
        	L1TechnicalTriggers[36] == 0 &&
        	L1TechnicalTriggers[37] == 0 &&
        	L1TechnicalTriggers[38] == 0 &&
        	L1TechnicalTriggers[39] == 0 &&
        	(L1TechnicalTriggers[40] == 1 || L1TechnicalTriggers[41] == 1) )
      	{;}
    	else {
      		result = 0;
      	}
    }
  } // end result != 0


  // ##############################
  // Primary vertex
  // ##############################
  if(result != 0) {
    if(vertices->size() > 0) {
      reco::Vertex primaryVertex = vertices->front();
      double primVertZ = primaryVertex.z();
      double ndof = primaryVertex.ndof();

      if(primaryVertex.isFake() == false &&
         fabs(primVertZ) < 15 &&
         ndof >= 5)
        ; // pass vertex selection
      else
        result = 0;
    }
  } // end result != 0



  // ##############################
  // Jets incl. jet id
  // ##############################

  if(result != 0) {

    const float ptMonoCut = 10.0;
    const float etaMonoCut = 2.5;

    for(reco::PFJetCollection::const_iterator jet = ak5PFJets->begin(); jet < ak5PFJets->end(); ++jet) {
      reco::PFJet correctedJet = *jet; // copy orignial jet
      double scale = pfJetCorrector->correction(jet->p4());  //calculate the correction
      correctedJet.scaleEnergy(scale); // apply correction

      if(correctedJet.pt() > ptMonoCut && fabs(correctedJet.eta()) < etaMonoCut) {
	// tight jet id
	if(jet->neutralHadronEnergyFraction() < 0.9 &&
	   jet->neutralEmEnergyFraction() < 0.9 &&
	   jet->chargedEmEnergyFraction() < 1.0) {
	  
	  // inside tracker acceptance depends on CHF
	  if(fabs(correctedJet.eta()) < 2.4) {
	    if(jet->chargedHadronEnergyFraction() > 0.0)
	      monoJetEvent = true;
	  }
	  // outside tracker, jet accepted without CHF
	  else
	    monoJetEvent = true;
	}
      }

    } // end jet for loop
    
  } // end result != 0

  eventNum      = iEvent.id().event() ;
   runNumber     = iEvent.id().run() ;
   lumiBlock     = iEvent.luminosityBlock() ;
   bunchCrossing = iEvent.bunchCrossing();
   isInclusive = 0;
   if (monoJetEvent) isInclusive = 1;
   
   EventTree->Fill();

   std::auto_ptr<bool> theResult_inclusive(new bool);
  *theResult_inclusive = monoJetEvent;
  iEvent.put(theResult_inclusive, "inclusive");
}

// ------------ method called once each job just before starting event loop  ------------
void 
CentralMonoPFJetProducer::beginJob()
{
EventTree->Branch("eventNum",&eventNum,"eventNum/I");
EventTree->Branch("lumiBlock",&lumiBlock,"lumiBlock/I");
EventTree->Branch("runNumber",&runNumber,"runNumber/I");
EventTree->Branch("bunchCrossing",&bunchCrossing,"bunchCrossing/I");
EventTree->Branch("isInclusive",&isInclusive,"isInclusive/I");
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CentralMonoPFJetProducer::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(CentralMonoPFJetProducer);
