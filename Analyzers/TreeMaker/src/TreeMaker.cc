// -*- C++ -*-
//
// Package:    TreeMaker
// Class:      TreeMaker
// 
/**\class TreeMaker TreeMaker.cc Analyzers/TreeMaker/src/TreeMaker.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  local user
//         Created:  Wed Mar  3 10:32:26 CET 2010
// $Id: TreeMaker.cc,v 1.2 2010/04/13 15:33:53 roland Exp $
//
//

// system include files
#include <memory>
#include <algorithm>
#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/HcalRecHit/interface/CastorRecHit.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/HcalDetId/interface/HcalCastorDetId.h"


#include "SimDataFormats/CaloHit/interface/PCaloHit.h"
#include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimG4CMS/Calo/interface/CaloHit.h"

#include "DataFormats/HcalRecHit/interface/CastorRecHit.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/HcalDetId/interface/HcalCastorDetId.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HcalDigi/interface/CastorDataFrame.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"

#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "Geometry/Records/interface/CastorGeometryRecord.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"

// vertex includes
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

// #include "SimDataFormats/Vertex/interface/SimVertex.h"
// #include "SimDataFormats/Vertex/interface/SimVertexContainer.h"

// trigger includes
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "L1Trigger/L1ExtraFromDigis/interface/L1ExtraParticleMapProd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"

// jet includes
#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/JetID.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"

#include "HLTriggerOffline/SUSYBSM/interface/PtSorter.h"

#include "CalibFormats/CastorObjects/interface/CastorDbService.h"
#include "CalibFormats/CastorObjects/interface/CastorDbRecord.h"
#include "CalibFormats/CastorObjects/interface/CastorCalibrations.h"
#include "CondFormats/CastorObjects/interface/CastorQIECoder.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TProfile.h"
#include "TLorentzVector.h"
#include "TNtuple.h"
#include <TRandom3.h>

#define debug 0
#define DebugGenKin 0
#define DebugPedestal 0
#define DebugVertex 0

using namespace edm;
using namespace std;
using namespace reco;

//
// class declaration
//

class TreeMaker : public edm::EDAnalyzer {
public:
  explicit TreeMaker(const edm::ParameterSet&);
  ~TreeMaker();
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  // ----------member data ---------------------------
  
  std::string fOutputFileName;
  std::string CaloJetCorrectionService;
  std::string PFJetCorrectionService;
  edm::InputTag hlTriggerResults_;
  edm::TriggerNames triggerNames_;
  edm::InputTag m_l1ParticleMap_;
  edm::InputTag particleMapSource_;
  edm::InputTag caloJets_;
  edm::InputTag pfJets_;
  edm::InputTag l1Trigger_;
  edm::InputTag castordigis_;
  edm::InputTag hepMCColl_;
  edm::InputTag PrimaryVertexColl_;
  edm::InputTag BeamSpot_;
  edm::InputTag GenPartColl_;

  Bool_t ReadPedestal;
  TTree* EventTree;
  TFile* fOutputFile;
  
  Int_t eventNum;
  Int_t lumiBlock;
  Int_t runNumber;
  Int_t bunchCrossing;
  
  Int_t PhysicsDeclared;
  Int_t L1bit0;
  Int_t L1bit36;
  Int_t L1bit37;
  Int_t L1bit38;
  Int_t L1bit39;
  Int_t L1bit40;
  Int_t L1bit41;
  
  Int_t isCaloInclusive;
  Int_t isCaloDijet;
  Int_t nCaloJets;
  
  Int_t isPFInclusive;
  Int_t isPFDijet;
  Int_t nPFJets;
  
  Double_t sumADC[224];     
  Double_t ADC[224][6];
  
  Double_t sumfC[224];     
  Double_t fC[224][6];
  
  Int_t module[224];
  Int_t channel[224];
  Int_t sector[224]; 
  
  Double_t signal[224];
  Double_t fCsignal[224];
  
  Double_t pedestalADC[224];
  Double_t pedestalfC[224];

  Double_t CaloJetEnergy[4];
  Double_t CaloJetPt[4];
  Double_t CaloJetEta[4];
  Double_t CaloJetPhi[4]; 
  
  Double_t PFJetEnergy[4];
  Double_t PFJetPt[4];
  Double_t PFJetEta[4];
  Double_t PFJetPhi[4];
  
  Int_t ProcessId;
  Double_t PtHat;

  Int_t nPV;
  Int_t nTrackPV;
  Double_t PV[3];
  Double_t PVerr[3];
  Double_t BS[3];
  Double_t PVsim[3];
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

TreeMaker::TreeMaker(const edm::ParameterSet& iConfig):
  fOutputFileName(iConfig.getParameter<std::string>("OutputFileName")),
  CaloJetCorrectionService(iConfig.getParameter<std::string>("CaloJetCorrector")),
  PFJetCorrectionService(iConfig.getParameter<std::string>("PFJetCorrector")),
  hlTriggerResults_(iConfig.getParameter<edm::InputTag>("HLTriggerResults")),
  caloJets_(iConfig.getParameter<edm::InputTag>("CaloJets")),
  pfJets_(iConfig.getParameter<edm::InputTag>("PFJets")),
  l1Trigger_(iConfig.getParameter<edm::InputTag>("L1Trigger")),
  castordigis_(iConfig.getParameter<edm::InputTag>("CastorDigis")),
  hepMCColl_(iConfig.getParameter<edm::InputTag>("HepMCColl")),
  PrimaryVertexColl_(iConfig.getParameter<edm::InputTag>("PrimaryVertexColl")),
  BeamSpot_(iConfig.getParameter<edm::InputTag>("BeamSpot")),
  GenPartColl_(iConfig.getParameter<edm::InputTag>("GenPartColl"))
{
  //now do what ever initialization is needed
  ReadPedestal = kTRUE;
}


TreeMaker::~TreeMaker()
{
  
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
}


//
// member functions
//

// ------------ method called to for each event  ------------
void TreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   if(debug) cout<< " Run = " << iEvent.id().run() << " Event = " << iEvent.id().event();
   if(debug) cout<<""<<endl;
   eventNum      = iEvent.id().event() ;
   runNumber     = iEvent.id().run() ;
   lumiBlock     = iEvent.luminosityBlock() ;
   bunchCrossing = iEvent.bunchCrossing();

   //---------------------//
   //--- read pedestal ---//
   //---------------------//
  
   if(ReadPedestal == kTRUE) {
    
     ReadPedestal = kFALSE; //-- initialize the pedestal only once
     Char_t MainDir[100] = "pedestal_settings";
   
     Char_t Pedestal_ADC_FileName[200];

     if (runNumber == 124009) sprintf(Pedestal_ADC_FileName,"%s/pedestal_ADC_data_124009.steer",MainDir);
     else if (runNumber == 124020) sprintf(Pedestal_ADC_FileName,"%s/pedestal_ADC_data_124020.steer",MainDir);
     else if (runNumber == 124022) sprintf(Pedestal_ADC_FileName,"%s/pedestal_ADC_data_124022.steer",MainDir);
     else if (runNumber == 124023) sprintf(Pedestal_ADC_FileName,"%s/pedestal_ADC_data_124023.steer",MainDir);
     else if (runNumber == 124024) sprintf(Pedestal_ADC_FileName,"%s/pedestal_ADC_data_124024.steer",MainDir);
     else if (runNumber == 124027) sprintf(Pedestal_ADC_FileName,"%s/pedestal_ADC_data_124027.steer",MainDir);
     else if (runNumber == 124030) sprintf(Pedestal_ADC_FileName,"%s/pedestal_ADC_data_124030.steer",MainDir);
     else if (runNumber == 124120) sprintf(Pedestal_ADC_FileName,"%s/pedestal_ADC_data_124120.steer",MainDir);
     else sprintf(Pedestal_ADC_FileName,"%s/pedestal_ADC_data_all.steer",MainDir); //-- use data all for mc sample
     //-- from run 124020 - 124022 - 124023 - 124024 - 124027 - 124030

     ifstream pedestal_ADC_fin;
     pedestal_ADC_fin.open(Pedestal_ADC_FileName,ios::in);

     if(DebugPedestal) {
       cout<<"reading pedestal in ADC from file: "<<Pedestal_ADC_FileName<<endl;
       if (pedestal_ADC_fin.is_open()) cout<<"file open"<<endl;
       if (!pedestal_ADC_fin.is_open()) cout<<"could not open file!"<<endl;
       getchar();
     }

     for (Int_t k=0;k<224;k++) {
       pedestal_ADC_fin >> pedestalADC[k];
       if(DebugPedestal) cout<<"channel: "<<k+1<<" ,pedestal: "<<pedestalADC[k]<<endl;
     }

     if(DebugPedestal) getchar();
     pedestal_ADC_fin.close();
     
     Char_t Pedestal_fC_FileName[200];

     if (runNumber == 124009) sprintf(Pedestal_fC_FileName,"%s/pedestal_fC_data_124009.steer",MainDir);
     else if (runNumber == 124020) sprintf(Pedestal_fC_FileName,"%s/pedestal_fC_data_124020.steer",MainDir);
     else if (runNumber == 124022) sprintf(Pedestal_fC_FileName,"%s/pedestal_fC_data_124022.steer",MainDir);
     else if (runNumber == 124023) sprintf(Pedestal_fC_FileName,"%s/pedestal_fC_data_124023.steer",MainDir);
     else if (runNumber == 124024) sprintf(Pedestal_fC_FileName,"%s/pedestal_fC_data_124024.steer",MainDir);
     else if (runNumber == 124027) sprintf(Pedestal_fC_FileName,"%s/pedestal_fC_data_124027.steer",MainDir);
     else if (runNumber == 124030) sprintf(Pedestal_fC_FileName,"%s/pedestal_fC_data_124030.steer",MainDir);
     else if (runNumber == 124120) sprintf(Pedestal_fC_FileName,"%s/pedestal_fC_data_124120.steer",MainDir);
     else sprintf(Pedestal_fC_FileName,"%s/pedestal_fC_data_all.steer",MainDir); //-- use data all for mc sample
     //-- from run 124020 - 124022 - 124023 - 124024 - 124027 -124030

     ifstream pedestal_fC_fin;
     pedestal_fC_fin.open(Pedestal_fC_FileName,ios::in);
     
     if(DebugPedestal) {
       cout<<"reading pedestal in fC from file: "<<Pedestal_fC_FileName<<endl;
       if (pedestal_fC_fin.is_open()) cout<<"file open"<<endl;
       if (!pedestal_fC_fin.is_open()) cout<<"could not open file!"<<endl;
       getchar();
     }
     
     for (Int_t k=0;k<224;k++) {
       pedestal_fC_fin >> pedestalfC[k];
       if(DebugPedestal) cout<<"channel: "<<k+1<<" ,pedestal: "<<pedestalfC[k]<<endl;
     }
     
     if(DebugPedestal) getchar();
     pedestal_fC_fin.close();
   }
   
   /////////////////////////
   // start CASTOR digi part
   /////////////////////////
  
   Handle<CastorDigiCollection> digiCollection;
   const CastorDigiCollection* castordigis = 0;
   iEvent.getByLabel(castordigis_, digiCollection);
   
   ESHandle<CastorDbService> conditions;
   iSetup.get<CastorDbRecord>().get(conditions);
   
   const CastorQIEShape* shape = conditions->getCastorShape();

   for (Int_t i = 0 ; i < 224; i++) {
     sumADC[i]=0;
     sumfC[i]=0;
     signal[i] =0;
     fCsignal[i]=0;
     //-- do not initialize the pedestal for each event
     module[i]=0;
     sector[i]=0;
     channel[i]=0;
     for(Int_t j = 0; j < 6; j++) {
       ADC[i][j]=0;
       fC[i][j]=0;
     }
   }
   
   if(digiCollection.isValid()){
     castordigis = digiCollection.product();

     for (unsigned int digiItr=0; digiItr<digiCollection->size(); ++digiItr) { //loop over 224 channels
       
       CastorDataFrame castordf=(*castordigis)[digiItr];
       Int_t nrSamples = castordf.size();
       HcalCastorDetId castorid = castordf.id();
       Int_t channel_nb = 16*(castorid.module()-1) + castorid.sector();
       Int_t channel_id = channel_nb - 1;
       
       module[channel_id] = castorid.module();
       sector[channel_id] = castorid.sector();
       channel[channel_id]= channel_nb;
       
       // linearize ADC
       const CastorCalibrations& calibrations = conditions->getCastorCalibrations(castordf.id().rawId());
       const CastorQIECoder* coder = conditions->getCastorCoder(castordf.id().rawId());
       
       for (Int_t sample = 0 ; sample < nrSamples; ++sample) { //loop over 6 time slices
	 HcalQIESample mySample = castordf[sample];
	 ADC[channel_id][sample]=(mySample.adc());
	 fC[channel_id][sample] = coder->charge(*shape,mySample.adc(),mySample.capid()); 
	 if(sample > 1) sumADC[channel_id]+=ADC[channel_id][sample]; // sum 4 last time slices
	 if(sample > 1) sumfC[channel_id]+=fC[channel_id][sample]; // sum 4 last time slices
       }

       /*     
       if (runNumber == 1) {
	 // MC
	 //cout << "====== This is MC =======" << endl;
	 for (Int_t sample = 0 ; sample < nrSamples; ++sample) { //loop over 6 time slices
	   HcalQIESample mySample = castordf[sample];
	   ADC[channel_id][sample]=(mySample.adc());
	   if(sample > 1) sumADC[channel_id]+=ADC[channel_id][sample]; // sum 4 last time slices
	 }
	 for (Int_t sample = 0 ; sample < nrSamples; ++sample) { //loop over 6 time slices
	   HcalQIESample mySample = castordf[sample];
	   // fC
	   if (sample < 3) fC[channel_id][sample] = coder->charge(*shape,mySample.adc(),mySample.capid());
	   if (sample == 3) fC[channel_id][sample] = coder->charge(*shape,ADC[channel_id][3]*0.6,mySample.capid());
	   if (sample == 4) fC[channel_id][sample] = coder->charge(*shape,ADC[channel_id][sample]+ADC[channel_id][3]*0.3,mySample.capid());
	   if (sample == 5) fC[channel_id][sample] = coder->charge(*shape,ADC[channel_id][sample]+ADC[channel_id][3]*0.1,mySample.capid());
	   if(sample > 1) sumfC[channel_id]+=fC[channel_id][sample]; // sum 4 last time slices
	 }
       }
       */
   
     } //-- end loop over digiCollection 
  
     if(debug) {
       for (Int_t i = 0 ; i < 224; i++) {
	 cout<<"array entry: "<<i <<", module: "<<module[i]<<", sector: "<<sector[i]<<" ,channel: "<<channel[i] 
	     <<", 4 last time slices: "<<sumADC[i]<<endl;
	 getchar();
       }
     }
     
     if(DebugPedestal) {
       cout<<""<<endl;
       cout<<"event number: "<<eventNum<<endl;
       cout<<""<<endl;
       for(Int_t i = 0; i < 224; i++) cout<<"pedestal in ADC channel "<<i+1<<": "<<pedestalADC[i]<<endl;
       cout<<""<<endl;
       for(Int_t i = 0; i < 224; i++) cout<<"pedestal in fC channel "<<i+1<<": "<<pedestalfC[i]<<endl;
       getchar();
     }
     
     for (Int_t j=0;j<224;j++) {
       // reconstruct signal (for all channels)
       signal[j] = sumADC[j] - 4*pedestalADC[j];
       fCsignal[j] = sumfC[j] - 4*pedestalfC[j];       
     }
     
     
   } else {
     LogError("CastorDigiError") << "Failed to get CASTOR digis - skipping this part";
   }
   
   ///////////////////////
   // end CASTOR digi part
   ///////////////////////
   
   
   //////////////////////
   // start Trigger part
   //////////////////////
   
   PhysicsDeclared = 0;
   L1bit0 = 0;
   L1bit36 = 0;
   L1bit37 = 0;
   L1bit38 = 0;
   L1bit39 = 0;
   L1bit40 = 0;
   L1bit41 = 0;
   
   Handle<TriggerResults> hlTriggers;
   iEvent.getByLabel(hlTriggerResults_, hlTriggers);
   Handle<L1GlobalTriggerReadoutRecord> L1GTRR;
   Handle<L1GlobalTriggerObjectMapRecord> L1GTOMRec;
   iEvent.getByLabel(l1Trigger_, L1GTRR);
   
   // HLT
   if(hlTriggers.failedToGet()) {
     LogError("HLTriggerError") << "Failed to get trigger results - skipping this part";
   }
   else {
     TriggerNames triggerName;
     //-- triggerName.init(*hlTriggers);
     
     unsigned short int trigpos = 0;
     const unsigned short int numTriggers = triggerName.size();
     if(debug) cout << "Number of HLTriggers: " << numTriggers << std::endl;
     for(unsigned short int trig = 0; trig < numTriggers; ++trig) {
       if(debug) cout << "trigger found at position " << trig << "with name " << triggerName.triggerName(trig) << std::endl;
       if ( triggerName.triggerName(trig) == "HLT_PhysicsDeclared") {
	 trigpos = trig;
	 if(debug) cout << "HLT_PhysicsDeclared trigger found at position " << trigpos << std::endl;
       }
     }
     
     if(triggerName.triggerName(trigpos) == "HLT_PhysicsDeclared") {
       bool trigAccept = hlTriggers.product()->accept(trigpos);
       if(trigAccept == true)
	 {PhysicsDeclared = 1;}
       else
	 {PhysicsDeclared = 0;}
     }
     else {
       if (runNumber == 1) {
	 //cout << "this is MC, don't need HLT_PhysicsDeclared" << endl;
	 PhysicsDeclared = 0;
       } else {
	 LogError("HLTriggerError") << "Wrong assignment of trigger position to HLT_PhyscisDeclared";
	 PhysicsDeclared = 0;
	 LogError("HLTriggerError") << "Put HLT_PhyscisDeclared result to 0";
       }
       
     } // end else
   } // end trigger.failedToGet()
   
   
   // L1
   Int_t L1TechnicalTriggers[64];
   
   for (Int_t i=0;i<64;i++) {
     L1TechnicalTriggers[i] = 0;
   }
   
   iEvent.getByLabel(InputTag("hltL1GtObjectMap::HLT"), L1GTOMRec);
   if (L1GTRR.isValid()) {
     DecisionWord gtDecisionWord = L1GTRR->decisionWord();
     const TechnicalTriggerWord&  technicalTriggerWordBeforeMask = L1GTRR->technicalTriggerWord();
     const unsigned int numberTechnicalTriggerBits(technicalTriggerWordBeforeMask.size());
     for (unsigned int iBit = 0; iBit < numberTechnicalTriggerBits; ++iBit) {
       Int_t techTrigger = (int) technicalTriggerWordBeforeMask.at(iBit);
       L1TechnicalTriggers[iBit] = techTrigger;
     }
   } 
   else {
     LogError("L1Debug") << "Trigger L1 is not valid: " << L1GTRR.isValid() << " - skipping this part";
   }
   
   L1bit0 = L1TechnicalTriggers[0];
   L1bit36 = L1TechnicalTriggers[36];
   L1bit37 = L1TechnicalTriggers[37];
   L1bit38 = L1TechnicalTriggers[38];
   L1bit39 = L1TechnicalTriggers[39];
   L1bit40 = L1TechnicalTriggers[40];
   L1bit41 = L1TechnicalTriggers[41];
   
   ///////////////////
   // end Trigger part
   ///////////////////
   
   /////////////////////////
   // start central jet part
   /////////////////////////
   
   isCaloInclusive = 0;
   isCaloDijet = 0;
   nCaloJets = 0;
   
   for (Int_t i=0;i<4;i++) { 
     CaloJetEnergy[i] = 0;
     CaloJetPt[i] = 0;
     CaloJetEta[i] = 0;
     CaloJetPhi[i] = 0;
   }
   
   isPFInclusive = 0;
   isPFDijet = 0;
   nPFJets = 0;
   
   for (Int_t i=0;i<4;i++) { 
     PFJetEnergy[i] = 0;
     PFJetPt[i] = 0;
     PFJetEta[i] = 0;
     PFJetPhi[i] = 0;
   }
   
   // CaloJets
  
   Handle<reco::CaloJetCollection> ak5CaloJets;
   iEvent.getByLabel(caloJets_, ak5CaloJets);
   
   const JetCorrector* caloJetCorrector = JetCorrector::getJetCorrector(CaloJetCorrectionService,iSetup);
   
   if (ak5CaloJets.isValid()) {
     nCaloJets = ak5CaloJets->size();
     
     CaloJetCollection correctedJets;
     // do the jet energy scale correction
     for(CaloJetCollection::const_iterator jet = ak5CaloJets->begin(); jet < ak5CaloJets->end(); ++jet) {
       CaloJet correctedJet = *jet; // copy orignial jet
       Double_t scale = caloJetCorrector->correction(jet->p4());  //calculate the correction
       correctedJet.scaleEnergy(scale); // apply correction
       //cout << "corrected jet pt = " << correctedJet.pt() << endl;
       correctedJets.push_back(correctedJet);
     }
     
     // sort on pt
     CaloJetCollection sortedJets = correctedJets;
     stable_sort(sortedJets.begin(),sortedJets.end(), PtSorter());
     
     // fill all variables
     for(Int_t p=0;p<nCaloJets;++p) {
       if (p<4) {
	 CaloJetEnergy[p] = sortedJets[p].energy();
	 CaloJetPt[p] = sortedJets[p].pt();
	 CaloJetEta[p] = sortedJets[p].eta();
	 CaloJetPhi[p] = sortedJets[p].phi();
       }
     }
   } else {
     LogError("CentralJetError") << "Failed to get CaloJet collection - skipping this part";
   }
   
   /*
     for (Int_t i=0;i<4;i++) { 
     cout << "" << endl;
     cout << "CaloJet energy = " << CaloJetEnergy[i] << endl;
     cout << "CaloJet pt = " <<CaloJetPt[i] << endl;
     cout << "CaloJet eta = " <<CaloJetEta[i] <<endl;
     cout << "CaloJet phi = " <<CaloJetPhi[i] <<endl;
     }
   */
   
   // PFJets
   
   Handle<reco::PFJetCollection> ak5PFJets;
   iEvent.getByLabel(pfJets_, ak5PFJets);
   
   const JetCorrector* pfJetCorrector = JetCorrector::getJetCorrector(PFJetCorrectionService,iSetup);
   
   if (ak5PFJets.isValid()) {
     nPFJets = ak5PFJets->size();
     
     PFJetCollection correctedJets;
     // do the jet energy scale correction
     for(PFJetCollection::const_iterator jet = ak5PFJets->begin(); jet < ak5PFJets->end(); ++jet) {
       PFJet correctedJet = *jet; // copy orignial jet
       Double_t scale = pfJetCorrector->correction(jet->p4());  //calculate the correction
       correctedJet.scaleEnergy(scale); // apply correction
       //cout << "corrected jet pt = " << correctedJet.pt() << endl;
       correctedJets.push_back(correctedJet);
     }
     
     // sort on pt
     PFJetCollection sortedJets = correctedJets;
     stable_sort(sortedJets.begin(),sortedJets.end(), PtSorter());
     
     // fill all variables
     for(Int_t p=0;p<nPFJets;++p) {
       if (p<4) {
	 PFJetEnergy[p] = sortedJets[p].energy();
	 PFJetPt[p] = sortedJets[p].pt();
	 PFJetEta[p] = sortedJets[p].eta();
	 PFJetPhi[p] = sortedJets[p].phi();
       }
     }
   } else {
     LogError("CentralJetError") << "Failed to get PFJet collection - skipping this part";
   }
   
   /*
     for (Int_t i=0;i<4;i++) { 
     cout << "" << endl;
     cout << "PFJet energy = " << PFJetEnergy[i] << endl;
     cout << "PFJet pt = " <<PFJetPt[i] << endl;
     cout << "PFJet eta = " <<PFJetEta[i] <<endl;
     cout << "PFJet phi = " <<PFJetPhi[i] <<endl;
     }
   */
   
   
   Handle<bool> CaloDijet;
   iEvent.getByLabel("calodijetSelector","dijet", CaloDijet);
   Handle<bool> CaloInclusive;
   iEvent.getByLabel("calomonojetSelector","inclusive", CaloInclusive);
   
   if (*CaloInclusive) isCaloInclusive = 1;
   if (*CaloDijet) isCaloDijet = 1;
   
   Handle<bool> PFDijet;
   iEvent.getByLabel("pfdijetSelector","dijet", PFDijet);
   Handle<bool> PFInclusive;
   iEvent.getByLabel("pfmonojetSelector","inclusive", PFInclusive);
   
   if (*PFInclusive) isPFInclusive = 1;
   if (*PFDijet) isPFDijet = 1;
   
   //--------------------------//
   //-- Generated Kinematics --//
   //--------------------------//
   
   ProcessId = -1;
   PtHat = -1;
   
   if (runNumber == 1) { //MC  
     
     Handle<HepMCProduct> hepMChandle;
     iEvent.getByLabel(hepMCColl_,hepMChandle) ;
     
     if(hepMChandle.failedToGet()) {
       LogError("HepMCError") << "Failed to get HEPMC results - skipping this part";
     }
     
     else {
       const HepMC::GenEvent* GenEvt = hepMChandle->GetEvent() ;
       ProcessId = GenEvt->signal_process_id();
       if(DebugGenKin) cout<<"Process ID: "<<ProcessId<<endl;
       PtHat  = GenEvt->event_scale();
       if(DebugGenKin) cout<<"Pt Hat MC: "<<PtHat<<endl;
     }
   }
   
   //------------------------//
   //-- Vertex Information --//
   //------------------------//

   nPV = 0;
   nTrackPV = 0;
   for (Int_t i = 0; i < 3; i++) {
     PV[i] = 0;
     PVerr[i] = 0;
     BS[i] = 0;
     PVsim[i] = 0;
   }
   
   edm::Handle<reco::VertexCollection> PVhandle;
   iEvent.getByLabel(PrimaryVertexColl_,PVhandle);
   
   edm::Handle<reco::BeamSpot> BShandle;
   iEvent.getByLabel(BeamSpot_,BShandle);
   
   if (runNumber == 1) { //MC

     edm::Handle<reco::GenParticleCollection> GenParthandle;
     iEvent.getByLabel(GenPartColl_,GenParthandle);
     
     //-- position of the simulated primary vertex
     math::XYZPoint PositionPVsim = (*GenParthandle)[2].vertex();
     
     PVsim[0] = PositionPVsim.X();
     PVsim[1] = PositionPVsim.Y();
     PVsim[2] = PositionPVsim.Z();
   }

   //-- number of reconstructed primary vertices
   nPV = PVhandle->size();
   
   //-- if primary vertex collection not empty, use the first (highest pt^2 sum)
   if (!PVhandle->empty()) {

     const reco::Vertex &pv = (*PVhandle)[0];

     nTrackPV = pv.tracksSize();
     
     PV[0] = pv.x();
     PV[1] = pv.y();
     PV[2] = pv.z();
     
     PVerr[0] = pv.xError();
     PVerr[1] = pv.yError();
     PVerr[2] = pv.zError();
     
     BS[0] = BShandle->x0();
     BS[1] = BShandle->y0();
     BS[2] = BShandle->z0();
   }   
   
   if(DebugVertex) {
     cout<<"number of reconstructed primary vertices: "<<nPV<<endl;
     cout<<"number of associated tracks: "<<nTrackPV<<endl;

     cout<<"primary vertex x: "<<PV[0]<<endl;
     cout<<"primary vertex y: "<<PV[1]<<endl;
     cout<<"primary vertex z: "<<PV[2]<<endl;
     
     cout<<"primary vertex error x: "<<PVerr[0]<<endl;
     cout<<"primary vertex error y: "<<PVerr[1]<<endl;
     cout<<"primary vertex error z: "<<PVerr[2]<<endl;

     cout<<"beam spot x: "<<BS[0]<<endl;
     cout<<"beam spot y: "<<BS[1]<<endl;
     cout<<"beam spot z: "<<BS[2]<<endl;

     cout<<"simulated primary vertex x: "<<PVsim[0]<<endl;
     cout<<"simulated primary vertex y: "<<PVsim[1]<<endl;
     cout<<"simulated primary vertex z: "<<PVsim[2]<<endl;
     getchar();
   }

   // fill the tree
   EventTree->Fill(); 
   
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
TreeMaker::beginJob()
{
  
  //edm::Service<TFileService> fs;
  //EventTree = fs->make<TTree>();
  
  fOutputFile = new TFile(fOutputFileName.c_str(),"RECREATE") ;
  
  EventTree = new TTree("CastorDigi","CastorDigi");
  
  EventTree->Branch("ADC",ADC,"ADC[224][6]/D");
  EventTree->Branch("sumADC",sumADC,"sumADC[224]/D");
  
  EventTree->Branch("fC",fC,"fC[224][6]/D");
  EventTree->Branch("sumfC",sumfC,"sumfC[224]/D");
  
  EventTree->Branch("module",module,"module[224]/I");
  EventTree->Branch("sector",sector,"sector[224]/I");
  EventTree->Branch("channel",channel,"channel[224]/I");
  
  EventTree->Branch("signal",signal,"signal[224]/D");
  EventTree->Branch("fCsignal",fCsignal,"fCsignal[224]/D");
  
  EventTree->Branch("pedestalADC",pedestalADC,"pedestalADC[224]/D");
  EventTree->Branch("pedestalfC",pedestalfC,"pedestalfC[224]/D");
  
  EventTree->Branch("eventNum",&eventNum,"eventNum/I");
  EventTree->Branch("lumiBlock",&lumiBlock,"lumiBlock/I");
  EventTree->Branch("runNumber",&runNumber,"runNumber/I");
  EventTree->Branch("bunchCrossing",&bunchCrossing,"bunchCrossing/I");
  
  EventTree->Branch("PhysicsDeclared",&PhysicsDeclared,"PhysicsDeclared/I");
  
  EventTree->Branch("L1bit0",&L1bit0,"L1bit0/I");
  EventTree->Branch("L1bit36",&L1bit36,"L1bit36/I");
  EventTree->Branch("L1bit37",&L1bit37,"L1bit37/I");
  EventTree->Branch("L1bit38",&L1bit38,"L1bit38/I");
  EventTree->Branch("L1bit39",&L1bit39,"L1bit39/I");
  EventTree->Branch("L1bit40",&L1bit40,"L1bit40/I");
  EventTree->Branch("L1bit41",&L1bit41,"L1bit41/I");
  
  EventTree->Branch("nCaloJets",&nCaloJets,"nCaloJets/I");
  EventTree->Branch("nPFJets",&nPFJets,"nPFJets/I");
  
  EventTree->Branch("isCaloInclusive",&isCaloInclusive,"isCaloInclusive/I");
  EventTree->Branch("isPFInclusive",&isPFInclusive,"isPFInclusive/I");
  EventTree->Branch("isCaloDijet",&isCaloDijet,"isCaloDijet/I");
  EventTree->Branch("isPFDijet",&isPFDijet,"isPFDijet/I");
  
  EventTree->Branch("CaloJetEnergy",CaloJetEnergy,"CaloJetEnergy[4]/D");
  EventTree->Branch("CaloJetPt",CaloJetPt,"CaloJetPt[4]/D");
  EventTree->Branch("CaloJetEta",CaloJetEta,"CaloJetEta[4]/D");
  EventTree->Branch("CaloJetPhi",CaloJetPhi,"CaloJetPhi[4]/D");
  
  EventTree->Branch("PFJetEnergy",PFJetEnergy,"PFJetEnergy[4]/D");
  EventTree->Branch("PFJetPt",PFJetPt,"PFJetPt[4]/D");
  EventTree->Branch("PFJetEta",PFJetEta,"PFJetEta[4]/D");
  EventTree->Branch("PFJetPhi",PFJetPhi,"PFJetPhi[4]/D");
  
  EventTree->Branch("ProcessId",&ProcessId,"ProcessId/I");
  EventTree->Branch("PtHat",&PtHat,"PtHat/D");
  
  EventTree->Branch("nPV",&nPV,"nPV/I");
  EventTree->Branch("nTrackPV",&nTrackPV,"nTrackPV/I");
  EventTree->Branch("PV",PV,"PV[3]/D");
  EventTree->Branch("PVerr",PVerr,"PVerr[3]/D");
  EventTree->Branch("BS",BS,"BS[3]/D");
  EventTree->Branch("PVsim",PVsim,"PVsim[3]/D");
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TreeMaker::endJob() {
fOutputFile->Write() ;
fOutputFile->Close() ;
 return ;
}

//define this as a plug-in
DEFINE_FWK_MODULE(TreeMaker);
