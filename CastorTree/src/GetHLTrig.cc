//-- Description: Function to retrieve HLT Trigger information (original author: Xavier Janssen)

//--  system include files
#include <iostream>

//-- user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Trigger Includes
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "UACastor/CastorTree/interface/CastorTree.h"

bool HLTDebug = true;

void CastorTree::GetHLTrig(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  using namespace std;
  using namespace edm;

  //-- Find HLT Data Object Name
 
  edm::InputTag srcTriggerResults_("TriggerResults"); 
 
  if (srcTriggerResults_.process().empty()) {
 
    edm::InputTag srcTriggerEvent("hltTriggerSummaryAOD");
    edm::Handle<trigger::TriggerEvent> triggerEvent;
    iEvent.getByLabel(srcTriggerEvent,triggerEvent);
   
    string hltProcName = triggerEvent.provenance()->processName();
    if(HLTDebug) cout<<"HLT process = "<<hltProcName<<endl;
    srcTriggerResults_ = edm::InputTag(srcTriggerResults_.label()+"::"+hltProcName);
  }

  if(HLTDebug) cout<<srcTriggerResults_<<endl;
 
  //-- Fetch HLT Data Object
 
  edm::Handle<edm::TriggerResults> trigResults;
  iEvent.getByLabel(srcTriggerResults_,trigResults);
 
  const edm::TriggerNames& trigNames = iEvent.triggerNames(*trigResults);
 
  //-- Loop on triggers requested by user (config file)

  for(vector<string>::iterator hlt_name = hlt_bits.begin(); hlt_name != hlt_bits.end(); hlt_name++) {

    HLTrig.HLTmap[*hlt_name]= hasFired(*hlt_name,trigNames,*trigResults);
    HLTrig.HLTprescale[*hlt_name]= hltConfig.prescaleValue(iEvent,iSetup,*hlt_name);

    if(HLTDebug) cout<<(*hlt_name).c_str()<<" = "<<hasFired(*hlt_name,trigNames,*trigResults)<<endl;
  }
}

bool CastorTree::hasFired(const std::string& triggerName, const edm::TriggerNames& trigNames, const edm::TriggerResults& trigResults) const {

  unsigned index = trigNames.triggerIndex(triggerName);

  if (index>=trigNames.size()) {
    if(HLTDebug) cout<<"CastorTree::hasFired() ERROR: unknown trigger name"<<triggerName<<endl;
    return false;
  }

  return trigResults.accept(index);
}

