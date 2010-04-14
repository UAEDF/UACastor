// -*- C++ -*-
//
// Package:    CentralDiPFJetProducer
// Class:      CentralDiPFJetProducer
// 
/**\class CentralDiPFJetProducer CentralDiPFJetProducer.cc ForwardAnalysis/CentralDiPFJetProducer/src/CentralDiPFJetProducer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Alexander Flossdorf,01c/159,1797,
//         Created:  Wed Mar  3 14:13:12 CET 2010
// $Id: CentralDiPFJetFilter.cc,v 1.1 2010/04/13 14:17:33 hvanhaev Exp $
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
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/JetCollection.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "FWCore/Framework/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Framework/interface/TriggerNames.h"
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

class CentralDiPFJetProducer : public edm::EDProducer {
public:
  explicit CentralDiPFJetProducer(const edm::ParameterSet&);
  ~CentralDiPFJetProducer();

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

  bool diJetEvent;
  int result;
  
  edm::Service<TFileService> fs;
  TTree* EventTree;

	int eventNum;
	int lumiBlock;
	int runNumber;
	int bunchCrossing;
	int isDijet;
};

//
// constructors and destructor
//
CentralDiPFJetProducer::CentralDiPFJetProducer(const edm::ParameterSet& iConfig)
{
  PFJetCorrectionService = iConfig.getParameter<std::string>("PFJetCorrector");
  hlTriggerResults_ = iConfig.getParameter<edm::InputTag>("HLTriggerResults");
  pfJets_ = iConfig.getParameter<edm::InputTag>("PFJets");
  vertices_ = iConfig.getParameter<edm::InputTag>("Vertices");
  l1Trigger_ = iConfig.getParameter<edm::InputTag>("L1Trigger");
  
  EventTree = fs->make<TTree>("CentralPFDiJetSelection","CentralPFDiJetSelection");
  produces<bool>("dijet").setBranchAlias("theResult_dijet");
}


CentralDiPFJetProducer::~CentralDiPFJetProducer()
{
}


//
// member functions
//

// ------------ method called on each new Event  ------------
void CentralDiPFJetProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;


  diJetEvent = false;
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
    triggerName.init(*hlTriggers);

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

    const float ptDiCut = 8.0;
    const float etaDiCut = 2.5;

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

      if(correctedJet1.pt() > ptDiCut && fabs(correctedJet1.eta()) < etaDiCut) {
	// loose jet id
	if(jet1.neutralHadronEnergyFraction() < 1.0 &&
	   jet1.neutralEmEnergyFraction() < 1.0 &&
	   jet1.chargedEmEnergyFraction() < 1.0) {
	  
	  // inside tracker acceptance depends on CHF
	  if(fabs(correctedJet1.eta()) < 2.4) {
	    if(jet1.chargedHadronEnergyFraction() > 0.0)
	      acceptJet1 = true;
	  }
	  // outside tracker, jet accepted without CHF
	  else
	    acceptJet1 = true;
	}
      } // end if di-jet cuts jet1     

      if(correctedJet2.pt() > ptDiCut && fabs(correctedJet2.eta()) < etaDiCut) {
	// loose jet id
	if(jet2.neutralHadronEnergyFraction() < 1.0 &&
	   jet2.neutralEmEnergyFraction() < 1.0 &&
	   jet2.chargedEmEnergyFraction() < 1.0) {
	  
	  // inside tracker acceptance depends on CHF
	  if(fabs(jet2.eta()) < 2.4) {
	    if(correctedJet2.chargedHadronEnergyFraction() > 0.0)
	      acceptJet2 = true;
	  }
	  // outside tracker, jet accepted without CHF
	  else
	    acceptJet2 = true;
	}
      } // end if di-jet cuts jet2     

      if(acceptJet1 == true && acceptJet2 == true) {
	double deltaPhi = fabs(reco::deltaPhi(jet1.phi(), jet2.phi()));
	if (fabs(deltaPhi - M_PI) < 1.0)
	  diJetEvent = true;
      }
    } // end if(posJet1 >= 0 && posJet2 >= 0)  

  } // end result != 0


  eventNum      = iEvent.id().event() ;
   runNumber     = iEvent.id().run() ;
   lumiBlock     = iEvent.luminosityBlock() ;
   bunchCrossing = iEvent.bunchCrossing();
   isDijet = 0;
   if (diJetEvent) isDijet = 1;
   
   EventTree->Fill();

  std::auto_ptr<bool> theResult_dijet(new bool);
  *theResult_dijet = diJetEvent;
  iEvent.put(theResult_dijet, "dijet");
}

// ------------ method called once each job just before starting event loop  ------------
void 
CentralDiPFJetProducer::beginJob()
{
EventTree->Branch("eventNum",&eventNum,"eventNum/I");
EventTree->Branch("lumiBlock",&lumiBlock,"lumiBlock/I");
EventTree->Branch("runNumber",&runNumber,"runNumber/I");
EventTree->Branch("bunchCrossing",&bunchCrossing,"bunchCrossing/I");
EventTree->Branch("isDijet",&isDijet,"isDijet/I");
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CentralDiPFJetProducer::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(CentralDiPFJetProducer);
