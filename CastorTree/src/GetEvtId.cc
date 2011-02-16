//-- Description: Function to retrieve Evt Id information (original author: Xavier Janssen)

//--  system include files
#include <iostream>

//-- user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "UACastor/CastorTree/interface/CastorTree.h"

bool EvtIdDebug = true;

void CastorTree::GetEvtId(const edm::Event& iEvent) {
  
  using namespace std;

  EvtId.Reset();

  EvtId.Run       = iEvent.id().run() ;   
  EvtId.Evt       = iEvent.id().event() ;
  EvtId.LumiBlock  = iEvent.luminosityBlock();
 
  edm::Timestamp Time = iEvent.time();
 
  EvtId.Time      = Time.value(); 
  EvtId.IsData    = iEvent.isRealData();
  EvtId.ExpType   = iEvent.experimentType();
  EvtId.Bunch     = iEvent.bunchCrossing();
  EvtId.Orbit     = iEvent.orbitNumber();
  
  if(EvtIdDebug) EvtId.Print();
}
