// -*- C++ -*-
//
// Package:    CentralDiCaloJetProducer
// Class:      CentralDiCaloJetProducer
// 
/**\class CentralDiCaloJetProducer CentralDiCaloJetProducer.cc ForwardAnalysis/CentralDiCaloJetProducer/src/CentralDiCaloJetProducer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Alexander Flossdorf,01c/159,1797,
//         Created:  Wed Mar  3 14:13:07 CET 2010
// $Id: CentralDiCaloJetFilter.cc,v 1.2 2010/04/14 22:04:25 roland Exp $
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
#include "DataFormats/JetReco/interface/JetID.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/Common/interface/ValueMap.h"
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

class CentralDiCaloJetProducer : public edm::EDProducer {
public:
  explicit CentralDiCaloJetProducer(const edm::ParameterSet&);
  ~CentralDiCaloJetProducer();

private:
  virtual void beginJob() ;
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
      
  // ----------member data ---------------------------
  std::string CaloJetCorrectionService;

  edm::InputTag hlTriggerResults_;
  edm::TriggerNames triggerNames_;
  edm::InputTag m_l1ParticleMap_;
  edm::InputTag particleMapSource_;
  edm::InputTag caloJets_;
  edm::InputTag jetId_;
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
CentralDiCaloJetProducer::CentralDiCaloJetProducer(const edm::ParameterSet& iConfig)
{
  CaloJetCorrectionService = iConfig.getParameter<std::string>("CaloJetCorrector");
  hlTriggerResults_ = iConfig.getParameter<edm::InputTag>("HLTriggerResults");
  caloJets_ = iConfig.getParameter<edm::InputTag>("CaloJets");
  jetId_ = iConfig.getParameter<edm::InputTag>("CaloJetId");
  vertices_ = iConfig.getParameter<edm::InputTag>("Vertices");
  l1Trigger_ = iConfig.getParameter<edm::InputTag>("L1Trigger");
  
    EventTree = fs->make<TTree>("CentralCaloDiJetSelection","CentralCaloDiJetSelection");
    produces<bool>("dijet").setBranchAlias("theResult_dijet");
}


CentralDiCaloJetProducer::~CentralDiCaloJetProducer()
{
}


//
// member functions
//

// ------------ method called on each new Event  ------------
void CentralDiCaloJetProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
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

  Handle<reco::CaloJetCollection> ak5CaloJets;
  iEvent.getByLabel(caloJets_, ak5CaloJets);

  Handle<reco::JetIDValueMap> theAk5Id;
  iEvent.getByLabel(jetId_, theAk5Id);
  reco::JetIDValueMap ak5Id = *theAk5Id;

  const JetCorrector* caloJetCorrector = JetCorrector::getJetCorrector(CaloJetCorrectionService,iSetup);


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
    
    unsigned short int trigpos = 0;
    const unsigned short int numTriggers = triggerName.size();
    //std::cout << "Number of HLTriggers: " << numTriggers << std::endl;
    for(unsigned short int trig = 0; trig < numTriggers; ++trig) {
          //std::cout << "trigger found at position " << trig << "with name " << triggerName.triggerName(trig) << std::endl;
	  if ( triggerName.triggerName(trig) == "HLT_PhysicsDeclared") {
	  trigpos = trig;
	  //std::cout << "trigger found at position " << trigpos << std::endl;
	  }
    }
    
    if(triggerName.triggerName(trigpos) == "HLT_PhysicsDeclared") {
      bool trigAccept = hlTriggers.product()->accept(trigpos);
      if(trigAccept == true)
	{result = -1;}
      else
	{result = 0;}
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
	    {result = -1;}
	  else
	    {result = 0;}
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

    const float ptDiCut = 10.0;
    const float etaDiCut = 2.5;

    short int posJet1 = -1;
    short int posJet2 = -1;
    double refPt1 = 0;
    double refPt2 = 0;

    for(reco::CaloJetCollection::const_iterator jet = ak5CaloJets->begin(); jet < ak5CaloJets->end(); ++jet) {
      reco::CaloJet correctedJet = *jet; // copy orignial jet
      double scale = caloJetCorrector->correction(jet->p4());  //calculate the correction
      correctedJet.scaleEnergy(scale); // apply correction

      double pt = correctedJet.pt();

      if(pt > refPt1) {
        refPt2 = refPt1;
        posJet2 = posJet1;
        refPt1 = pt ;
        posJet1 = jet - ak5CaloJets->begin();
      }
      else if(pt > refPt2) {
        refPt2 = pt ;
        posJet2 = jet - ak5CaloJets->begin();
      }
    } // end jet for loop


    if(posJet1 >= 0 && posJet2 >= 0) {
      reco::CaloJet jet1 = ak5CaloJets->at(posJet1);
      double scale1 = caloJetCorrector->correction(jet1.p4());  //calculate the correction
      jet1.scaleEnergy(scale1); // apply correction
      reco::CaloJetRef theRef1(ak5CaloJets, posJet1);

      reco::CaloJet jet2 = ak5CaloJets->at(posJet2);
      double scale2 = caloJetCorrector->correction(jet2.p4());  //calculate the correction
      jet2.scaleEnergy(scale2); // apply correction
      reco::CaloJetRef theRef2(ak5CaloJets, posJet2);

      bool acceptJet1 = false;
      bool acceptJet2 = false;

      if(jet1.pt() > ptDiCut && fabs(jet1.eta()) < etaDiCut) {
        // loose jet id
        if(ak5Id[theRef1].fHPD < 0.98 &&
           ak5Id[theRef1].n90Hits > 1) {

          // inside tracker acceptance depends on emf
          if(fabs(jet1.eta()) < 2.6) {
            if(jet1.emEnergyFraction() > 0.01) {
              acceptJet1 = true;
            }
          }
          // outside tracker, jet accepted without emf
          else
            acceptJet1 = true;
        }
      } // end if di-jet cuts jet1


      if(jet2.pt() > ptDiCut && fabs(jet2.eta()) < etaDiCut) {
        // loose jet id
        if(ak5Id[theRef2].fHPD < 0.98 &&
           ak5Id[theRef2].n90Hits > 1) {

          // inside tracker acceptance depends on emf
          if(fabs(jet2.eta()) < 2.6) {
            if(jet2.emEnergyFraction() > 0.01) {
              acceptJet2 = true;
            }
          }
          // outside tracker, jet accepted without emf
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
CentralDiCaloJetProducer::beginJob()
{
EventTree->Branch("eventNum",&eventNum,"eventNum/I");
EventTree->Branch("lumiBlock",&lumiBlock,"lumiBlock/I");
EventTree->Branch("runNumber",&runNumber,"runNumber/I");
EventTree->Branch("bunchCrossing",&bunchCrossing,"bunchCrossing/I");
EventTree->Branch("isDijet",&isDijet,"isDijet/I");
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CentralDiCaloJetProducer::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(CentralDiCaloJetProducer);
