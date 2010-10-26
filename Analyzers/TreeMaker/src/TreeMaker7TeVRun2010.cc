//-- system include files
#include <memory>
#include <algorithm>
#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

//-- user include files
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

//-- vertex includes
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

//-- trigger includes
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "L1Trigger/L1ExtraFromDigis/interface/L1ExtraParticleMapProd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"


//-- jet includes
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
#include "TRandom3.h"

#define debug 0
#define DebugGenKin 0
#define DebugPedestal 0
#define DebugVertex 0

using namespace edm;
using namespace std;
using namespace reco;

//-- class declaration

class TreeMaker7TeVRun2010 : public edm::EDAnalyzer {

public:

  explicit TreeMaker7TeVRun2010(const edm::ParameterSet&);
  ~TreeMaker7TeVRun2010();
  
private:

  virtual void beginJob() ;
  virtual void beginRun(edm::Run const &, edm::EventSetup const&);
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  //-- member data
  //-- std::string fOutputFileName;

  edm::InputTag l1Trigger_;
  edm::InputTag hlTriggerResults_;
  std::string hltMenuLabel_;

  std::string PFJetCorrectionService;
  edm::InputTag pfJets_;

  edm::InputTag castordigis_;
  edm::InputTag PrimaryVertexColl_;
  edm::InputTag BeamSpot_;

  edm::InputTag hepMCColl_;
  edm::InputTag GenPartColl_;

  HLTConfigProvider hltConfig;

  bool Grid_;
  bool CentralInfo_;
  bool TriggerInfo_;
  bool MCInfo_;

  Bool_t ReadPedestal;

  edm::Service<TFileService> fs;
  TTree* EventTree;
  //-- TFile* fOutputFile;
  
  Int_t run;
  Int_t event;
  Int_t lumiblock;
  Int_t bunchcrossing;

  Double_t fC[224][10];
  Double_t sumfC[224];
  Double_t pedestalfC[224];
  Double_t signalfC[224];

  Double_t ADC[224][10];
  Double_t sumADC[224];
  Double_t pedestalADC[224];
  Double_t signalADC[224];

  Int_t module[224];
  Int_t channel[224];
  Int_t sector[224];

  Int_t L1TT[128];

  Int_t HLT_L1Tech_BSC_minBias;
  Int_t HLT_L1Tech_BSC_minBias_OR;
  Int_t HLT_MinBiasPixel_SingleTrack;
  Int_t HLT_ZeroBias;
  Int_t HLT_ZeroBiasPixel_SingleTrack;
  
  Double_t HLT_L1Tech_BSC_minBias_pres;
  Double_t HLT_L1Tech_BSC_minBias_OR_pres;
  Double_t HLT_MinBiasPixel_SingleTrack_pres;
  Double_t HLT_ZeroBias_pres;
  Double_t HLT_ZeroBiasPixel_SingleTrack_pres;

  Int_t isPFInclusive;
  Int_t isPFDijet;
  Int_t nPFJets;

  std::vector<double> PFJetEnergy, PFJetPt, PFJetEta, PFJetPhi;  
  std::vector<double> *pPFJetEnergy, *pPFJetPt, *pPFJetEta, *pPFJetPhi;

  Int_t ProcessId;
  Double_t PtHat;

  Int_t nPV;
  Int_t nTrackPV;
  Double_t PV[3];
  Double_t PVerr[3];
  Double_t BS[3];
  Double_t PVsim[3];
};


//-- constants, enums and typedefs

//-- static data member definitions

//-- constructors and destructor

TreeMaker7TeVRun2010::TreeMaker7TeVRun2010(const edm::ParameterSet& iConfig) {
  
  //-- fOutputFileName = iConfig.getParameter<std::string>("OutputFileName");

  l1Trigger_ = iConfig.getParameter<edm::InputTag>("L1Trigger");
  hlTriggerResults_ = iConfig.getParameter<edm::InputTag>("HLTriggerResults");
  hltMenuLabel_ = iConfig.getParameter<std::string>("HLTMenuLabel");

  PFJetCorrectionService = iConfig.getParameter<std::string>("PFJetCorrector");
  pfJets_ = iConfig.getParameter<edm::InputTag>("PFJets");

  castordigis_ = iConfig.getParameter<edm::InputTag>("CastorDigis");
  PrimaryVertexColl_ = iConfig.getParameter<edm::InputTag>("PrimaryVertexColl");
  BeamSpot_ = iConfig.getParameter<edm::InputTag>("BeamSpot");

  hepMCColl_ = iConfig.getParameter<edm::InputTag>("HepMCColl");
  GenPartColl_ = iConfig.getParameter<edm::InputTag>("GenPartColl");
 
  Grid_ = iConfig.getUntrackedParameter<bool>("Grid");
  CentralInfo_ = iConfig.getUntrackedParameter<bool>("CentralInfo");
  TriggerInfo_ = iConfig.getUntrackedParameter<bool>("TriggerInfo");
  MCInfo_ = iConfig.getUntrackedParameter<bool>("MCInfo");

  ReadPedestal = kTRUE;
 
  EventTree = fs->make<TTree>("CastorTree","CastorTree");
}


TreeMaker7TeVRun2010::~TreeMaker7TeVRun2010() {
  //-- do anything here that needs to be done at destruction time
  //-- e.g. close files, deallocate resources, etc.
}


//-- member functions

//-- method called to for each run

void TreeMaker7TeVRun2010::beginRun(edm::Run const & iRun, edm::EventSetup const& iSetup)
{
  using namespace std;
  using namespace edm;

  bool changed(true);

  if(hltConfig.init(iRun,iSetup,hltMenuLabel_,changed)){
    if(changed){
     
      //-- check if trigger name is in (new) config
      std::string triggerName_ = "HLT_L1Tech_BSC_minBias";
      if(triggerName_!="@") { // "@" means: analyze all triggers in config

	const unsigned int n(hltConfig.size());
	const unsigned int triggerIndex(hltConfig.triggerIndex(triggerName_));
	
	if(triggerIndex>=n){
	  cout <<"TreeMaker7TeVRun2010::analyze: TriggerName "<<triggerName_<<" not available in (new) config!" << endl;
	  if(debug) cout <<"Available TriggerNames are: "<< endl;
	  if(debug) hltConfig.dump("Triggers");
	}
      }      
      //--  hltConfig.dump("Streams");
      //--  hltConfig.dump("Datasets");
      //--  hltConfig.dump("PrescaleTable");
      //--  hltConfig.dump("ProcessPSet");
    }
  }  else {
    cout <<"TreeMaker7TeVRun2010::beginRun: config extraction failure with process name "<<hltMenuLabel_<<endl;
  }
}

//-- method called to for each event

void TreeMaker7TeVRun2010::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  if(debug) cout<<"run "<< iEvent.id().run() <<" event "<<iEvent.id().event()<<endl;
  if(debug) cout<<""<<endl;

  run = iEvent.id().run();
  event = iEvent.id().event();
  lumiblock = iEvent.luminosityBlock() ;
  bunchcrossing = iEvent.bunchCrossing();
  
  //---------------------//
  //--- read pedestal ---//
  //---------------------//
  
  if(ReadPedestal == kTRUE) {
    
    ReadPedestal = kFALSE; //-- initialize the pedestal only once
    Char_t MainDir[100];
    if(Grid_) sprintf(MainDir,"./src/Analyzers/TreeMaker/data");
    else sprintf(MainDir,"pedestal_settings");

    //-- use the same pedestal for data and mc (mean from run 124020 - 124022 - 124023 - 124024 - 124027 -124030)   
    Char_t Pedestal_ADC_FileName[200];
    sprintf(Pedestal_ADC_FileName,"%s/pedestal_ADC_data_all.steer",MainDir); 
    
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
    
    //-- use the same pedestal for data and mc (mean from run 124020 - 124022 - 124023 - 124024 - 124027 -124030)
    Char_t Pedestal_fC_FileName[200];
    sprintf(Pedestal_fC_FileName,"%s/pedestal_fC_data_all.steer",MainDir); 
    
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
   

  //---------------------------//
  //-- CASTOR digi treatment --//
  //---------------------------//

  Handle<CastorDigiCollection> digiCollection;
  const CastorDigiCollection* castordigis = 0;
  iEvent.getByLabel(castordigis_,digiCollection);
   
  ESHandle<CastorDbService> conditions;
  iSetup.get<CastorDbRecord>().get(conditions);
   
  const CastorQIEShape* shape = conditions->getCastorShape();

  for (Int_t i = 0 ; i < 224; i++) {
    
    for(Int_t j = 0; j < 10; j++) fC[i][j]=0;
    sumfC[i]=0;
    //-- do not initialize the pedestal for each event
    signalfC[i]=0;

    for(Int_t j = 0; j < 10; j++) ADC[i][j]=0;
    sumADC[i]=0;
    //-- do not initialize the pedestal for each event
    signalADC[i]=0;

    module[i]=0;
    sector[i]=0;
    channel[i]=0;
  }
   
  if(digiCollection.isValid()){
    castordigis = digiCollection.product();
    
    //-- loop over digiCollection (224 channels)
    for(unsigned int digiItr=0; digiItr<digiCollection->size(); ++digiItr) { 
       
      CastorDataFrame castordf=(*castordigis)[digiItr];
      Int_t nrSamples = castordf.size();
      HcalCastorDetId castorid = castordf.id();
      Int_t channel_nb = 16*(castorid.module()-1) + castorid.sector();
      Int_t channel_id = channel_nb - 1;
       
      module[channel_id] = castorid.module();
      sector[channel_id] = castorid.sector();
      channel[channel_id]= channel_nb;
       
      //-- signal in linearized ADC
      const CastorCalibrations& calibrations = conditions->getCastorCalibrations(castordf.id().rawId());
      const CastorQIECoder* coder = conditions->getCastorCoder(castordf.id().rawId());
      
      //-- loop over 10 time slices
      for (Int_t sample = 0 ; sample < nrSamples; ++sample) { 
	HcalQIESample mySample = castordf[sample];
	ADC[channel_id][sample]=(mySample.adc());
	fC[channel_id][sample] = coder->charge(*shape,mySample.adc(),mySample.capid()); 
	if(sample > 2 && sample < 6) sumADC[channel_id]+=ADC[channel_id][sample]; //-- sum over time slices 3 - 4 - 5
	if(sample > 2 && sample < 6) sumfC[channel_id]+=fC[channel_id][sample];   //-- sum over time slices 3 - 4 - 5
      }

    } //-- end loop over digiCollection
  
    if(debug) {
      for (Int_t i = 0 ; i < 224; i++) {
	cout<<"array entry: "<<i+1<<", module: "<<module[i]<<", sector: "<<sector[i]<<" ,channel: "<<channel[i] 
	    <<", ADC signal in time slices 3 - 4 - 5: "<<sumADC[i]
	    <<", fC signal in time slices 3 - 4 - 5: "<<sumfC[i]<<endl;
      }
      getchar();
    }
     
    if(DebugPedestal) {
      cout<<""<<endl;
      cout<<"event number: "<<event<<endl;
      cout<<""<<endl;
      for(Int_t i = 0; i < 224; i++) cout<<"pedestal in ADC channel "<<i+1<<": "<<pedestalADC[i]<<endl;
      cout<<""<<endl;
      for(Int_t i = 0; i < 224; i++) cout<<"pedestal in fC channel "<<i+1<<": "<<pedestalfC[i]<<endl;
      getchar();
    }
     
    //-- reconstruct signal (for all channels)
    for (Int_t j=0;j<224;j++){
      signalfC[j] = sumfC[j] - 3*pedestalfC[j];     //-- sum over time slices 3 - 4 - 5
      signalADC[j] = sumADC[j] - 3*pedestalADC[j];  //-- sum over time slices 3 - 4 - 5
    }

  } else {
    LogError("CastorDigiError") << "Failed to get CASTOR digis - skipping this part";
  }

  //-----------------------------//
  //--  L1 technical triggers  --//
  //-----------------------------//

  Handle<L1GlobalTriggerReadoutRecord> L1GTRR;
  iEvent.getByLabel(l1Trigger_,L1GTRR);

  for(Int_t i=0;i<128;i++) L1TT[i] = 0;
  if(debug) cout<<""<<endl;
  
  if(L1GTRR.isValid()){
    
    DecisionWord gtDecisionWord = L1GTRR->decisionWord();
    const TechnicalTriggerWord&  technicalTriggerWordBeforeMask = L1GTRR->technicalTriggerWord();
    const unsigned int numberTechnicalTriggerBits(technicalTriggerWordBeforeMask.size());
    
    for(unsigned int iBit = 0; iBit < numberTechnicalTriggerBits; ++iBit){
      Int_t techTrigger = (int) technicalTriggerWordBeforeMask.at(iBit);
      L1TT[iBit] = techTrigger;
      if(debug) cout<<"L1TT "<<iBit+1<<" has value "<<techTrigger<<endl;
    }
  }
  
  else{
    LogError("L1Debug") << "Trigger L1 is not valid: " << L1GTRR.isValid() << " - skipping this part";
  }
  
  //-----------//
  //--  HLT  --//
  //-----------//

  HLT_L1Tech_BSC_minBias = 0;
  HLT_L1Tech_BSC_minBias_OR = 0;
  HLT_MinBiasPixel_SingleTrack = 0;
  HLT_ZeroBias = 0;
  HLT_ZeroBiasPixel_SingleTrack = 0;

  HLT_L1Tech_BSC_minBias_pres = -1;
  HLT_L1Tech_BSC_minBias_OR_pres = -1;
  HLT_MinBiasPixel_SingleTrack_pres = -1;
  HLT_ZeroBias_pres = -1;
  HLT_ZeroBiasPixel_SingleTrack_pres = -1;

  Handle<TriggerResults> hlTriggers;
  iEvent.getByLabel(hlTriggerResults_,hlTriggers);

  if(hlTriggers.failedToGet()){
    LogError("HLTriggerError") << "Failed to get trigger results - skipping this part";
  }

  else{ //-- HLT triggers info available
    const TriggerNames & trigName = iEvent.triggerNames(*hlTriggers);
    const unsigned short int numTriggers = trigName.size();
    if(debug) cout<<"Number of HLTriggers: "<<numTriggers <<endl;

    for(unsigned short int itrig = 0; itrig < numTriggers; itrig++){ //-- loop over the HLT triggers
 
      if(debug) cout<<"trigger found at position " <<itrig<< " with name " <<trigName.triggerName(itrig)<< std::endl;
      
      if(trigName.triggerName(itrig) == "HLT_L1Tech_BSC_minBias"){  
	HLT_L1Tech_BSC_minBias_pres = hltConfig.prescaleValue(iEvent,iSetup,"HLT_L1Tech_BSC_minBias"); 
	if(hlTriggers->accept(itrig)) HLT_L1Tech_BSC_minBias = 1;
	else HLT_L1Tech_BSC_minBias = 0;
      }  

      if(trigName.triggerName(itrig) == "HLT_L1Tech_BSC_minBias_OR"){
        HLT_L1Tech_BSC_minBias_OR_pres = hltConfig.prescaleValue(iEvent,iSetup,"HLT_L1Tech_BSC_minBias_OR");
        if(hlTriggers->accept(itrig)) HLT_L1Tech_BSC_minBias_OR = 1;
        else HLT_L1Tech_BSC_minBias_OR = 0;
      }

      if(trigName.triggerName(itrig) == "HLT_MinBiasPixel_SingleTrack"){
        HLT_MinBiasPixel_SingleTrack_pres = hltConfig.prescaleValue(iEvent,iSetup,"HLT_MinBiasPixel_SingleTrack");
        if(hlTriggers->accept(itrig)) HLT_MinBiasPixel_SingleTrack = 1;
        else HLT_MinBiasPixel_SingleTrack = 0;
      }

      if(trigName.triggerName(itrig) == "HLT_ZeroBias"){
        HLT_ZeroBias_pres = hltConfig.prescaleValue(iEvent,iSetup,"HLT_ZeroBias");
        if(hlTriggers->accept(itrig)) HLT_ZeroBias = 1;
        else HLT_ZeroBias = 0;
      }

      if(trigName.triggerName(itrig) == "HLT_ZeroBiasPixel_SingleTrack"){
        HLT_ZeroBiasPixel_SingleTrack_pres = hltConfig.prescaleValue(iEvent,iSetup,"HLT_ZeroBiasPixel_SingleTrack");
        if(hlTriggers->accept(itrig)) HLT_ZeroBiasPixel_SingleTrack = 1;
        else HLT_ZeroBiasPixel_SingleTrack = 0;
      }

    } //-- loop over the HLT triggers    
  } //-- HLT triggers info available
    
  //----------------------------//
  //--    central jet part    --//
  //----------------------------//
   
  isPFInclusive = 0;
  isPFDijet = 0;
  nPFJets = 0;
   
  //------------------//
  //--    PFJets    --//
  //------------------//

  Handle<reco::PFJetCollection> ak5PFJets;
  iEvent.getByLabel(pfJets_,ak5PFJets);
   
  const JetCorrector* pfJetCorrector = JetCorrector::getJetCorrector(PFJetCorrectionService,iSetup);
   
  if(ak5PFJets.isValid()) {
    nPFJets = ak5PFJets->size();
     
    pPFJetEnergy=&PFJetEnergy;
    pPFJetEnergy->clear();
    pPFJetEnergy->reserve(nPFJets);

    pPFJetPt=&PFJetPt;
    pPFJetPt->clear();
    pPFJetPt->reserve(nPFJets);

    pPFJetEta=&PFJetEta;
    pPFJetEta->clear();
    pPFJetEta->reserve(nPFJets);

    pPFJetPhi=&PFJetPhi;
    pPFJetPhi->clear();
    pPFJetPhi->reserve(nPFJets);

    PFJetCollection correctedJets;
    //-- do the jet energy scale correction
    for(PFJetCollection::const_iterator jet = ak5PFJets->begin(); jet < ak5PFJets->end(); ++jet) {
      PFJet correctedJet = *jet; // copy orignial jet
      Double_t scale = pfJetCorrector->correction(jet->p4());  //calculate the correction
      correctedJet.scaleEnergy(scale); // apply correction
      //-- cout << "corrected jet pt = " << correctedJet.pt() << endl;
      correctedJets.push_back(correctedJet);
    }
     
    //-- sort on pt
    PFJetCollection sortedJets = correctedJets;
    stable_sort(sortedJets.begin(),sortedJets.end(),PtSorter());
     
    //-- fill all variables
    for(Int_t p=0;p<nPFJets;++p) {
      pPFJetEnergy->push_back(sortedJets[p].energy());
      pPFJetPt->push_back(sortedJets[p].pt());
      pPFJetEta->push_back(sortedJets[p].eta());
      pPFJetPhi->push_back(sortedJets[p].phi());
    }
  } //--  if(ak5PFJets.isValid()) 
  
  else {
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
   
  Handle<bool> PFDijet;
  iEvent.getByLabel("pfdijetSelector7TeV","dijet",PFDijet);

  Handle<bool> PFInclusive;
  iEvent.getByLabel("pfmonojetSelector7TeV","inclusive",PFInclusive);   
   
  if(*PFDijet) isPFDijet = 1;
  if(*PFInclusive) isPFInclusive = 1;
   
  //-------------------------------------//
  //-- Generated Kinematics (MC only)  --//
  //-------------------------------------//
   
  ProcessId = -1;
  PtHat = -1;
   
  if(run == 1) { //-- MC only  
     
    Handle<HepMCProduct> hepMChandle;
    iEvent.getByLabel(hepMCColl_,hepMChandle) ;
     
    if(hepMChandle.failedToGet()) LogError("HepMCError") << "Failed to get HEPMC results - skipping this part";
     
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
  }
   
  edm::Handle<reco::VertexCollection> PVhandle;
  iEvent.getByLabel(PrimaryVertexColl_,PVhandle);
   
  edm::Handle<reco::BeamSpot> BShandle;
  iEvent.getByLabel(BeamSpot_,BShandle);
   
  //-- number of reconstructed primary vertices
  nPV = PVhandle->size();
   
  //-- if primary vertex collection not empty, use the first (highest pt^2 sum)
  if(!PVhandle->empty()) {

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
   
  //---------------------------//
  //-- Vertex Information MC --//
  //---------------------------//

  for(Int_t i = 0; i < 3; i++) PVsim[i] = 0;

  if(run == 1) { //-- MC only

    edm::Handle<reco::GenParticleCollection> GenParthandle;
    iEvent.getByLabel(GenPartColl_,GenParthandle);

    //-- position of the simulated primary vertex
    math::XYZPoint PositionPVsim = (*GenParthandle)[2].vertex();

    PVsim[0] = PositionPVsim.X();
    PVsim[1] = PositionPVsim.Y();
    PVsim[2] = PositionPVsim.Z();
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

  //-- fill the tree
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


//--  method called once each job just before starting the event loop
void TreeMaker7TeVRun2010::beginJob() {
  
  //-- fOutputFile = new TFile(fOutputFileName.c_str(),"RECREATE");
  //-- EventTree = new TTree("CastorDigi","CastorDigi");
  
  EventTree->Branch("run",&run,"run/I");
  EventTree->Branch("event",&event,"event/I");
  EventTree->Branch("lumiblock",&lumiblock,"lumiblock/I");
  EventTree->Branch("bunchcrossing",&bunchcrossing,"bunchcrossing/I");

  EventTree->Branch("fC",fC,"fC[224][10]/D");
  EventTree->Branch("sumfC",sumfC,"sumfC[224]/D");
  EventTree->Branch("pedestalfC",pedestalfC,"pedestalfC[224]/D");
  EventTree->Branch("signalfC",signalfC,"signalfC[224]/D");

  EventTree->Branch("ADC",ADC,"ADC[224][10]/D");
  EventTree->Branch("sumADC",sumADC,"sumADC[224]/D");
  EventTree->Branch("pedestalADC",pedestalADC,"pedestalADC[224]/D");
  EventTree->Branch("signalADC",signalADC,"signalADC[224]/D");

  EventTree->Branch("module",module,"module[224]/I");
  EventTree->Branch("sector",sector,"sector[224]/I");
  EventTree->Branch("channel",channel,"channel[224]/I");

  if(TriggerInfo_) EventTree->Branch("L1TT",L1TT,"L1TT[128]/I"); 

  if(TriggerInfo_) EventTree->Branch("HLT_L1Tech_BSC_minBias",&HLT_L1Tech_BSC_minBias,"HLT_L1Tech_BSC_minBias/I");
  if(TriggerInfo_) EventTree->Branch("HLT_L1Tech_BSC_minBias_OR",&HLT_L1Tech_BSC_minBias_OR,"HLT_L1Tech_BSC_minBias_OR/I");
  if(TriggerInfo_) EventTree->Branch("HLT_MinBiasPixel_SingleTrack",&HLT_MinBiasPixel_SingleTrack,"HLT_MinBiasPixel_SingleTrack/I");
  if(TriggerInfo_) EventTree->Branch("HLT_ZeroBias",&HLT_ZeroBias,"HLT_ZeroBias/I");
  if(TriggerInfo_) EventTree->Branch("HLT_ZeroBiasPixel_SingleTrack",&HLT_ZeroBiasPixel_SingleTrack,"HLT_ZeroBiasPixel_SingleTrack/I");

  if(TriggerInfo_) EventTree->Branch("HLT_L1Tech_BSC_minBias_pres",&HLT_L1Tech_BSC_minBias_pres,"HLT_L1Tech_BSC_minBias_pres/D");
  if(TriggerInfo_) EventTree->Branch("HLT_L1Tech_BSC_minBias_OR_pres",&HLT_L1Tech_BSC_minBias_OR_pres,"HLT_L1Tech_BSC_minBias_OR_pres/D");
  if(TriggerInfo_) EventTree->Branch("HLT_MinBiasPixel_SingleTrack_pres",&HLT_MinBiasPixel_SingleTrack_pres,"HLT_MinBiasPixel_SingleTrack_pres/D");
  if(TriggerInfo_) EventTree->Branch("HLT_ZeroBias_pres",&HLT_ZeroBias_pres,"HLT_ZeroBias_pres/D");
  if(TriggerInfo_) EventTree->Branch("HLT_ZeroBiasPixel_SingleTrack_pres",&HLT_ZeroBiasPixel_SingleTrack_pres,"HLT_ZeroBiasPixel_SingleTrack_pres/D");

  if(CentralInfo_) EventTree->Branch("isPFInclusive",&isPFInclusive,"isPFInclusive/I");
  if(CentralInfo_) EventTree->Branch("isPFDijet",&isPFDijet,"isPFDijet/I");
  if(CentralInfo_) EventTree->Branch("nPFJets",&nPFJets,"nPFJets/I");
  
  if(CentralInfo_) EventTree->Branch("PFJetEnergy","std::vector<double>",&pPFJetEnergy);
  if(CentralInfo_) EventTree->Branch("PFJetPt","std::vector<double>",&pPFJetPt);
  if(CentralInfo_) EventTree->Branch("PFJetEta","std::vector<double>",&pPFJetEta);
  if(CentralInfo_) EventTree->Branch("PFJetPhi","std::vector<double>",&pPFJetPhi);

  if(MCInfo_) EventTree->Branch("ProcessId",&ProcessId,"ProcessId/I");
  if(MCInfo_) EventTree->Branch("PtHat",&PtHat,"PtHat/D");
  
  if(CentralInfo_) EventTree->Branch("nPV",&nPV,"nPV/I");
  if(CentralInfo_) EventTree->Branch("nTrackPV",&nTrackPV,"nTrackPV/I");

  if(CentralInfo_) EventTree->Branch("PV",PV,"PV[3]/D");
  if(CentralInfo_) EventTree->Branch("PVerr",PVerr,"PVerr[3]/D");
  if(CentralInfo_) EventTree->Branch("BS",BS,"BS[3]/D");

  if(MCInfo_) EventTree->Branch("PVsim",PVsim,"PVsim[3]/D");
}

//--  method called once each job just after ending the event loop
void TreeMaker7TeVRun2010::endJob() {
  //-- fOutputFile->Write() ;
  //-- fOutputFile->Close() ;
  return ;
}

//-- define this as a plug-in
DEFINE_FWK_MODULE(TreeMaker7TeVRun2010);
