//-- Description: Function to retrieve castor digi information (original author: Benoit Roland)

//--  system include files
#include <iostream>

//-- user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//-- Castor Digi
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalDigi/interface/CastorDataFrame.h"
#include "DataFormats/HcalDetId/interface/HcalCastorDetId.h"

#include "CondFormats/CastorObjects/interface/CastorQIEShape.h"
#include "CondFormats/CastorObjects/interface/CastorQIECoder.h"
#include "CalibFormats/CastorObjects/interface/CastorCoderDb.h"
#include "CalibFormats/CastorObjects/interface/CastorDbService.h"
#include "CalibFormats/CastorObjects/interface/CastorDbRecord.h"

#include "./CastorTree.h"

bool CastorDigiDebug = false;

void CastorTree::GetCastorDigi(const edm::Event& iEvent, const edm::EventSetup& iSetup, vector<MyCastorDigi>& CastorDigiVector) {
  
  using namespace std;
  using namespace edm;
  using namespace reco;
  
  CastorDigiVector.clear();
  MyCastorDigi mycastordigi;

  Handle<CastorDigiCollection> digicoll;
  iEvent.getByLabel(CastorDigiColl_,digicoll);
  
  // QIE coder to convert to fC
  // get conditions
  edm::ESHandle<CastorDbService> conditions;
  iSetup.get<CastorDbRecord>().get(conditions);
  const CastorQIEShape* shape = conditions->getCastorShape ();
  
  if (CastorDigiDebug) cout<<"number of Castor Digi: "<<digicoll->size()<<endl;
  
  //-- loop over the digi collection (224 digis)
  for(size_t i = 0; i < digicoll->size(); i++) { 
  
    CastorDataFrame digi = (*digicoll)[i];
    HcalCastorDetId castorid = digi.id();
    
    const CastorQIECoder* channelCoder = conditions->getCastorCoder (castorid);
    CastorCoderDb coder (*channelCoder, *shape);
    CaloSamples tool;
    coder.adc2fC(digi,tool);

    mycastordigi.mod = castorid.module();
    mycastordigi.sec = castorid.sector();
    mycastordigi.cha = 16*(castorid.module()-1) + castorid.sector();
      
    //-- loop over the 6 or 10 time slices for each digi
   
    for (int ts = 0; ts < digi.size(); ts++) {   
      mycastordigi.adc.push_back(digi[ts].adc());
      mycastordigi.fC.push_back(tool[ts]);
    }
    
    CastorDigiVector.push_back(mycastordigi);
    if (CastorDigiDebug) mycastordigi.Print();   
    mycastordigi.Reset();
  }
}
